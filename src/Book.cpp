#include "../include/Book.h"

void Book::insert_order(OrderPointer& order) {
	Price price = order->get_price();
	bool is_buy = order->get_type() == BUY;

	LimitPointer limit = get_or_create_limit(price, is_buy);

	if (is_buy and (not best_buy or price > best_buy->get_price())) {
		best_buy = limit;
	} else if (not is_buy and (not best_sell or price < best_sell->get_price())) {
		best_sell = limit;
	}

	limit->insert_order(order);
}

void Book::place_order(OrderPointer& order) {
	// match order for buy:
	// while (best_sell and order.price > best_sell.price)
	//     match with best_sell (which is a limit pointer)
	//     if best_sell is empty delete it
	// if (order.status != FULFILLED)
	//     insert_order(order);
}

bool Book::is_in_buy_limits(Price price) {
	return buy_limits.contains(price);
}

bool Book::is_in_sell_limits(Price price) {
	return sell_limits.contains(price);
}

LimitPointer Book::get_or_create_limit(Price price, bool is_buy) {
	LimitPointer limit;
	if (is_buy) {
		if (is_in_buy_limits(price)) {
			limit = buy_limits[price];
		} else {
			limit = std::make_shared<Limit>(price);
			buy_tree.insert(limit);
			buy_limits[price] = limit;
		}
	} else {
		if (is_in_sell_limits(price)) {
			limit = sell_limits[price];
		} else {
			limit = std::make_shared<Limit>(price);
			sell_tree.insert(limit);
			sell_limits[price] = limit;
		}
	}
	return limit;
}

void Book::print() {
	for (auto limit = buy_tree.begin(); limit != buy_tree.end(); limit++){
		limit->get()->print();
	}
	std::cout << "==== BUY SIDE ===" << std::endl;
	best_buy->print();
	best_sell->print();
	std::cout << "=== SELL SIDE ===" << std::endl;
	for (auto limit = sell_tree.begin(); limit != sell_tree.end(); limit++){
		limit->get()->print();
	}
}
