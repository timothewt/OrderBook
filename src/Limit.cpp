#include <iostream>
#include "Limit.h"

void Limit::insert_order(OrderPointer order) {
	if (length == 0) {
		head = tail = order;
	} else {
		tail->set_next(order);
		order->set_prev(tail);
		tail = order;
	}
	total_volume += order->get_volume();
	length++;
}

void Limit::delete_order(OrderPointer order) {
	if (not order) return;

	if (length == 1) { // only order in the list
		head.reset();
		tail.reset();
	} else if (order == head) { // order at head of list
		head = order->get_next();
		order->get_next()->get_prev().reset();
	} else if (order == tail) { // order at tail of list
		tail = order->get_prev();
		order->get_prev()->get_next().reset();
	} else { // order in the list
		order->get_prev()->set_next(order->get_next());
		order->get_next()->set_prev(order->get_prev());
	}

	order->get_prev().reset();
	order->get_next().reset();
	if (order->get_status() != FULFILLED)
		order->set_status(DELETED);
	total_volume -= order->get_volume();
	length--;
}

Trades Limit::match_order(OrderPointer& order) {
	Trades trades;

	while (length > 0 and not order->is_fulfilled()) {
		Volume fill_volume = std::min(head->get_volume(), order->get_volume());
		head->fill(fill_volume);
		order->fill(fill_volume);
		total_volume -= fill_volume;
		trades.emplace_back(order->get_id(), head->get_id(), price, fill_volume);
		if (head->is_fulfilled())
			delete_order(head);
	}

	return trades;
}

bool Limit::is_empty() {
	return length == 0;
}

Price Limit::get_price() const { return price; }
Length Limit::get_length() { return length; }
Volume Limit::get_total_volume() { return total_volume; }

void Limit::print() {
	std::cout << "Limit(Price: " << price << ", Total Volume: "<< total_volume << ", #Orders: " << length << "):" << std::endl;
	OrderPointer curr = head;
	while (curr) {
		std::cout << "\t";
		curr->print();
		curr = curr->get_next();
	}
}

const std::function<bool(const LimitPointer&, const LimitPointer&)> cmp_limits = [](const LimitPointer& a, const LimitPointer& b) {
	return a->get_price() < b->get_price();
};
