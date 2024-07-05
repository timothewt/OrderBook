#include <iostream>
#include "../include/OrderBook.h"

void OrderBook::place_order(std::shared_ptr<Order>& p_order) {
	Price order_price = p_order->get_price();
	this->id_to_order[p_order->get_id()] = p_order;
	Trades trades;

	std::cout << "Placing order: " << *p_order << std::endl;

	if (p_order->get_order_type() == OrderType::BUY) {
		while (has_bids() && !p_order->is_fulfilled() && this->get_best_bid() <= order_price) {
			trades = this->get_best_bid_level().match_order(p_order);
			check_bids_level_for_empty(this->get_best_bid());
		}
		if (!p_order->is_fulfilled()) {
			this->asks[order_price].insert_order(p_order);
		}
	} else {
		while (has_asks() && !p_order->is_fulfilled() && this->get_best_ask() >= order_price) {
			trades = this->get_best_ask_level().match_order(p_order);
			check_asks_level_for_empty(this->get_best_ask());
		}
		if (!p_order->is_fulfilled()) {
			this->bids[order_price].insert_order(p_order);
		}
	}

	for (const auto& trade : trades) {
		std::cout << "\tTrade: book " << trade.booked_order_id << ", incoming " << trade.incoming_order_id
				  << ", qty " << trade.qty << ", price " << trade.price << std::endl;
	}
}

void OrderBook::cancel_order(std::shared_ptr<Order> &p_order) {
	if (p_order->is_fulfilled()) return; // as it has already been deleted when being fulfilled
	Price price = p_order->get_price();

	if (p_order->get_order_type() == OrderType::BUY) {
		this->asks[price].delete_order(p_order);
		check_asks_level_for_empty(price);
	} else {
		this->bids[price].delete_order(p_order);
		check_bids_level_for_empty(price);
	}
}

void OrderBook::check_bids_level_for_empty(Price price) {
	if (bids[price].get_length() == 0) bids.erase(price);
}

void OrderBook::check_asks_level_for_empty(Price price) {
	if (asks[price].get_length() == 0) asks.erase(price);
}

void OrderBook::cancel_order(ID order_id) {
	this->cancel_order(this->id_to_order[order_id]);
}

bool OrderBook::has_bids() {
	return not this->bids.empty();
}

bool OrderBook::has_asks() {
	return not this->asks.empty();
}

Price OrderBook::get_best_bid() {
	return this->bids.begin()->first;
}

BookLevel OrderBook::get_best_bid_level() {
	return this->bids.begin()->second;
}

Price OrderBook::get_best_ask() {
	return this->asks.begin()->first;
}

BookLevel OrderBook::get_best_ask_level() {
	return this->asks.begin()->second;
}

std::map<Price, BookLevel, std::greater<>> OrderBook::get_asks() {
	return this->asks;
}

std::map<Price, BookLevel, std::less<>> OrderBook::get_bids() {
	return this->bids;
}

std::unordered_map<ID, std::shared_ptr<Order>> OrderBook::get_id_to_order_map() {
	return this->id_to_order;
}
