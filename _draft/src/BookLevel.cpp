#include <iostream>
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
	if (!p_order) return;

	std::cout << "Deleting order: " << *p_order << std::endl;

	if (p_order == p_level_head) {
		p_level_head = p_order->get_p_next_order();
		if (p_level_head) {
			p_level_head->set_p_prev_order(nullptr);
		} else {
			p_level_tail = nullptr;
		}
	} else if (p_order == p_level_tail) {
		p_level_tail = p_order->get_p_prev_order();
		if (p_level_tail) {
			p_level_tail->set_p_next_order(nullptr);
		} else {
			p_level_head = nullptr;
		}
	} else {
		auto prev_order = p_order->get_p_prev_order();
		auto next_order = p_order->get_p_next_order();
		if (prev_order) {
			prev_order->set_p_next_order(next_order);
		}
		if (next_order) {
			next_order->set_p_prev_order(prev_order);
		}
	}
	p_order->set_p_prev_order(nullptr);
	p_order->set_p_next_order(nullptr);
	--length;
}


Trades BookLevel::match_order(std::shared_ptr<Order>& p_order) {
	Trades trades;

	std::cout << "Matching order: " << *p_order << " at " << this->p_level_head->get_price() << "$" << std::endl;

	while (!p_order->is_fulfilled() && this->length > 0) {
		std::shared_ptr<Order> head_order = this->p_level_head;
		Quantity fill_quantity = std::min(p_order->get_qty(), head_order->get_qty());

		p_order->fill(fill_quantity);
		head_order->fill(fill_quantity);

		trades.push_back({
			head_order->get_id(),
			p_order->get_id(),
			fill_quantity,
			head_order->get_price(),
		});

		if (head_order->is_fulfilled()) {
			this->delete_order(head_order);
		}

		std::cout << "After delete, head: " << (this->p_level_head ? this->p_level_head->to_string() : "null") << std::endl;
	}

	std::cout << "Final head: " << (this->p_level_head ? this->p_level_head->to_string() : "null") << std::endl;

	return trades;
}

std::shared_ptr<Order> BookLevel::get_p_level_head() {
	return this->p_level_head;
}

std::uint32_t BookLevel::get_length() {
	return this->length;
}
