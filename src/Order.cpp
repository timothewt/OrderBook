//
// Created by Timothe on 03/07/2024.
//

#include "../include/Order.h"
#include <sstream>
#include <utility>

Order::Order(ID id, ID agent_id, Quantity qty, Price price, OrderType order_type):
	id(id), agent_id(agent_id), qty(qty), price(price), order_type(order_type),
	p_prev_order(nullptr), p_next_order(nullptr) {}

void Order::fill(Quantity filling_qty) {
	if (filling_qty > this->qty) throw std::logic_error("Filling quantity cannot be greater than the order quantity.");
	this->qty -= filling_qty;
}

bool Order::is_fulfilled() {
	return qty == 0;
}

ID Order::get_id() const {
	return id;
}

ID Order::get_agent_id() const {
	return this->agent_id;
}

Quantity Order::get_qty() const {
	return qty;
}

Price Order::get_price() const {
	return price;
}

OrderType Order::get_order_type() {
	return order_type;
}

std::shared_ptr<Order> Order::get_p_prev_order() {
	return this->p_prev_order;
}

std::shared_ptr<Order> Order::get_p_next_order() {
	return this->p_next_order;
}

void Order::set_p_prev_order(std::shared_ptr<Order> prev) {
	p_prev_order = std::move(prev);
}

void Order::set_p_next_order(std::shared_ptr<Order> next) {
	p_next_order = std::move(next);
}

std::string Order::to_string() {
	return "Order(ID: " + std::to_string(id) +
		   ", Agent ID: " + std::to_string(agent_id) +
		   ", Quantity: " + std::to_string(qty) +
		   ", Price: " + std::to_string(price) +
		   ", Order Type: " + (order_type == OrderType::BUY ? "BUY" : "SELL") + ")";
}

// Overloads the << operator to print the order
std::ostream& operator<<(std::ostream& os, Order order) {
	os << order.to_string();
	return os;
}