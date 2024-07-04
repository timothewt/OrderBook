#include "../include/OrderBook.h"
#include <iostream>
#include <cmath>

int main() {
	OrderBook order_book;

	// Add 12 buy orders with increasing prices and quantities
	for (int i = 0; i < 12; ++i) {
		Quantity quantity = 10 * (i + 1);
		Price price = 100 + (Price)std::round(i / 2);  // Prices from 100 to 111
		std::shared_ptr<Order> buy_order(new Order(i, 0, quantity, price, OrderType::BUY));
		order_book.place_order(buy_order);
	}

	order_book.cancel_order(2);
	order_book.cancel_order(3);
	order_book.cancel_order(7);

	std::cout << "BUY ORDERS:" << std::endl;
	// Display the buy orders
	auto buy_orders = order_book.get_buy_orders();
	for (auto& [price, book_level] : buy_orders) {
		std::cout << "Price: " << price << ", Orders at this level: " << std::endl;
		std::shared_ptr<Order> curr_order = book_level.get_p_level_head();
		while (curr_order!= nullptr) {
			std::cout << "\t" << curr_order->to_string() << std::endl;
			curr_order = curr_order->get_p_next_order();
		}
	}

	// Add 12 sell orders with decreasing prices and quantities
	for (int i = 0; i < 12; ++i) {
		Quantity quantity = 10 * (i + 1);
		Price price = 110 - (Price)std::round(i / 2);  // Prices from 110 to 99
		std::shared_ptr<Order> sell_order(new Order(i + 12, 0, quantity, price, OrderType::SELL));
		order_book.place_order(sell_order);
	}

	order_book.cancel_order(14);
	order_book.cancel_order(15);
	order_book.cancel_order(19);

	std::cout << "\nSELL ORDERS:" << std::endl;
	// Display the sell orders
	auto sell_orders = order_book.get_sell_orders();
	for (auto& [price, book_level] : sell_orders) {
		std::cout << "Price: " << price << ", Orders at this level: " << std::endl;
		std::shared_ptr<Order> curr_order = book_level.get_p_level_head();
		while (curr_order!= nullptr) {
			std::cout << "\t" << curr_order->to_string() << std::endl;
			curr_order = curr_order->get_p_next_order();
		}
	}

	return 0;
}
