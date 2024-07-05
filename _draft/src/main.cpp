#include <iostream>
#include <memory>
#include <cmath>
#include "../include/OrderBook.h"

int main() {
	OrderBook orderBook;

	// Add some buy orders
	for (int i = 0; i < 6; ++i) {
		Quantity quantity = 10 * (i + 1);
		Price price = 100 + (Price)std::round(i / 2);  // Prices from 100 to 102
		std::shared_ptr<Order> buy_order(new Order(i, 0, quantity, price, OrderType::BUY));
		orderBook.place_order(buy_order);
	}

	// Add some sell orders
	for (int i = 0; i < 6; ++i) {
		Quantity quantity = 10 * (i + 1);
		Price price = 102 + (Price)std::round(i / 2);  // Prices from 100 to 102
		std::shared_ptr<Order> sell_order(new Order(i + 6, 0, 50, price, OrderType::SELL));
		orderBook.place_order(sell_order);
		break;
	}

	std::cout << "BUY ORDERS:" << std::endl;
	// Display the buy orders
	auto buy_orders = orderBook.get_asks();
	for (auto& [price, book_level] : buy_orders) {
		std::cout << "Price: " << price << ", Orders at this level: " << std::endl;
		std::shared_ptr<Order> curr_order = book_level.get_p_level_head();
		while (curr_order != nullptr) {
			std::cout << "\t" << curr_order->to_string() << std::endl;
			curr_order = curr_order->get_p_next_order();
		}
	}

	std::cout << "\nSELL ORDERS:" << std::endl;
	// Display the sell orders
	auto sell_orders = orderBook.get_bids();
	for (auto& [price, book_level] : sell_orders) {
		std::cout << "Price: " << price << ", Orders at this level: " << std::endl;
		std::shared_ptr<Order> curr_order = book_level.get_p_level_head();
		while (curr_order != nullptr) {
			std::cout << "\t" << curr_order->to_string() << std::endl;
			curr_order = curr_order->get_p_next_order();
		}
	}
/*
	// Add more buy and sell orders to test matching
	std::cout << "\nADDING MATCHING ORDERS:" << std::endl;

	// Add a buy order that should match with an existing sell order
	std::shared_ptr<Order> buy_order1(new Order(12, 0, 30, 100, OrderType::BUY));
	orderBook.place_order(buy_order1);

	// Add a sell order that should match with an existing buy order
	std::shared_ptr<Order> sell_order1(new Order(13, 0, 30, 102, OrderType::SELL));
	orderBook.place_order(sell_order1);

	// Display the buy orders again
	std::cout << "BUY ORDERS AFTER MATCHING:" << std::endl;
	buy_orders = orderBook.get_asks();
	for (auto& [price, book_level] : buy_orders) {
		std::cout << "Price: " << price << ", Orders at this level: " << std::endl;
		std::shared_ptr<Order> curr_order = book_level.get_p_level_head();
		while (curr_order != nullptr) {
			std::cout << "\t" << curr_order->to_string() << std::endl;
			curr_order = curr_order->get_p_next_order();
		}
	}

	// Display the sell orders again
	std::cout << "SELL ORDERS AFTER MATCHING:" << std::endl;
	sell_orders = orderBook.get_bids();
	for (auto& [price, book_level] : sell_orders) {
		std::cout << "Price: " << price << ", Orders at this level: " << std::endl;
		std::shared_ptr<Order> curr_order = book_level.get_p_level_head();
		while (curr_order != nullptr) {
			std::cout << "\t" << curr_order->to_string() << std::endl;
			curr_order = curr_order->get_p_next_order();
		}
	}

	return 0;*/
}
