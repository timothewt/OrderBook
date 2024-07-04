#include "../include/BookLevel.h"

BookLevel::BookLevel() : p_level_head(nullptr), p_level_tail(nullptr), length(0) {}

void BookLevel::insert_order(std::shared_ptr<Order>& p_order) {
	if (this->length == 0) {
		this->p_level_head = this->p_level_tail = p_order;
	} else {
		p_order->set_p_prev_order(this->p_level_tail);
		this->p_level_tail->set_p_next_order(p_order);
		this->p_level_tail = p_order;
	}
	this->length++;
}

void BookLevel::delete_order(std::shared_ptr<Order>& p_order) {
	std::shared_ptr<Order> p_prev_order = p_order->get_p_prev_order();
	std::shared_ptr<Order> p_next_order = p_order->get_p_next_order();

	if (p_prev_order == nullptr and p_next_order == nullptr) { // only order in the list
		this->p_level_head = this->p_level_tail = nullptr;
	} else if (p_prev_order != nullptr and p_next_order != nullptr) { // order in middle of list
		p_prev_order->set_p_next_order(p_next_order);
		p_next_order->set_p_prev_order(p_prev_order);
	} else if (p_prev_order == nullptr) { // order at the head of the list
		p_next_order->set_p_prev_order(nullptr);
		this->p_level_head = p_next_order;
	} else { // order at the tail of the list
		p_prev_order->set_p_next_order(nullptr);
		this->p_level_tail = p_prev_order;
	}
	this->length--;
}

Trades BookLevel::match_order(std::shared_ptr<Order> &p_order) {
	Trades trades;

	while (not p_order->is_fulfilled() and this->length > 0) {
		std::shared_ptr<Order> head_order = this->p_level_head;

		Quantity fill_quantity = std::min(p_order->get_qty(), this->p_level_head->get_qty());

		p_order->fill(fill_quantity);
		head_order->fill(fill_quantity);

		trades.push_back({
								 head_order->get_id(),
								 p_order->get_id(),
								 fill_quantity,
								 head_order->get_price(),
						 });

		if (head_order->is_fulfilled()) this->delete_order(head_order);
	}

	return trades;
}

std::shared_ptr<Order> BookLevel::get_p_level_head() {
	return this->p_level_head;
}

std::uint32_t BookLevel::get_length() {
	return this->length;
}
