#include <iostream>
#include "../include/Order.h"


void Order::fill(Volume fill_volume) {
	if (fill_volume > volume) throw std::logic_error("Order cannot be filled with higher volume than its remaining volume.");
	volume -= fill_volume;
}

bool Order::is_fulfilled() {
	return volume == 0;
}

ID Order::get_id() const {
	return id;
}

ID Order::get_agent_id() const {
	return agent_id;
}

OrderType Order::get_type() const {
	return type;
}

Price Order::get_price() const {
	return price;
}

Volume Order::get_volume() {
	return volume;
}

OrderPointer &Order::get_prev() {
	return prev;
}

void Order::set_prev(OrderPointer &prev) {
	Order::prev = prev;
}

OrderPointer &Order::get_next() {
	return next;
}

void Order::set_next(OrderPointer &next) {
	Order::next = next;
}

void Order::print() {
	std::cout <<
		"Order(ID: " << id <<
		", Agent ID: " << agent_id <<
		", Type: " << (type == BUY ? "BUY" : "SELL") <<
		", Price: " << price
		<< ", Volume: " << volume
		<< ")" <<
	std::endl;
}