//
// Created by Timothe on 04/07/2024.
//

#include "../include/OrderBook.h"

void OrderBook::place_order(std::shared_ptr<Order>& p_order) {
	Price order_price = p_order -> get_price();
	this->id_to_order[p_order->get_id()] = p_order;

	if (p_order->get_order_type() == OrderType::BUY) {
		this->buy_orders[order_price].insert_order(p_order);
	} else {
		this->sell_orders[order_price].insert_order(p_order);
	}
}

std::map<Price, BookLevel, std::greater<>> OrderBook::get_buy_orders() {
	return this->buy_orders;
}

std::map<Price, BookLevel, std::less<>> OrderBook::get_sell_orders() {
	return this->sell_orders;
}

std::unordered_map<ID, std::shared_ptr<Order>> OrderBook::get_id_to_order_map() {
	return this->id_to_order;
}

void OrderBook::cancel_order(std::shared_ptr<Order> &p_order) {
	if (p_order->is_fulfilled()) return; // as it has already been deleted when being fulfilled
	Price price = p_order->get_price();
	if (p_order->get_order_type() == OrderType::BUY) {
		this->buy_orders[price].delete_order(p_order);
		check_buy_level_for_empty(price);
	} else {
		this->sell_orders[price].delete_order(p_order);
		check_sell_level_for_empty(price);
	}
}

void OrderBook::check_sell_level_for_empty(Price price) {
	if (sell_orders[price].get_length() == 0) sell_orders.erase(price);
}

void OrderBook::check_buy_level_for_empty(Price price) {
	if (buy_orders[price].get_length() == 0) buy_orders.erase(price);
}

void OrderBook::cancel_order(ID order_id) {
	this->cancel_order(this->id_to_order[order_id]);
}
