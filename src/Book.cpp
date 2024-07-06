#include "Book.h"

Trades Book::place_order(OrderPointer& order) {
	if (order->get_price() <= 0)
		return {};

	Trades trades;
	id_to_order[order->get_id()] = order;

	if (order->get_type() == BUY) {
		while (best_sell and order->get_price() >= best_sell and order->get_status() != FULFILLED) {
			Trades trades_at_limit = sell_limits[best_sell]->match_order(order);
			trades.insert(trades.end(), trades_at_limit.begin(), trades_at_limit.end());
			check_for_empty_sell_limit(best_sell);
		}
	} else {
		while (best_buy and order->get_price() <= best_buy and order->get_status() != FULFILLED) {
			Trades trades_at_limit = buy_limits[best_buy]->match_order(order);
			trades.insert(trades.end(), trades_at_limit.begin(), trades_at_limit.end());
			check_for_empty_buy_limit(best_buy);
		}
	}

	if (order->get_status() != FULFILLED)
		insert_order(order);
	return trades;
}

void Book::delete_order(ID id) {
	if (not id_to_order.contains(id))
		return;
	OrderPointer order = id_to_order[id];
	/*if (not buy_limits.contains(order->get_price()) and not sell_limits.contains(order->get_price()))
		return;*/
	if (order->get_status() == ACTIVE) {
		delete_order(order, order->get_type() == BUY);
	}
}


bool Book::is_in_buy_limits(Price price) {
	return buy_limits.contains(price);
}

bool Book::is_in_sell_limits(Price price) {
	return sell_limits.contains(price);
}

void Book::update_best_buy() {
	if (not buy_tree.empty())
		best_buy = *buy_tree.rbegin();
	else
		best_buy = 0;
}

void Book::update_best_sell() {
	if (not sell_tree.empty())
		best_sell = *sell_tree.begin();
	else
		best_sell = 0;
}

void Book::check_for_empty_buy_limit(Price price) {
	if (is_in_buy_limits(price) and buy_limits[price]->is_empty()) {
		buy_limits.erase(price);
		buy_tree.erase(price);
		if (price == best_buy)
			update_best_buy();
	}
}

void Book::check_for_empty_sell_limit(Price price) {
	if (is_in_sell_limits(price) and sell_limits[price]->is_empty()) {
		sell_limits.erase(price);
		sell_tree.erase(price);
		if (price == best_sell)
			update_best_sell();
	}
}

void Book::insert_order(OrderPointer& order) {
	Price price = order->get_price();
	bool is_buy = order->get_type() == BUY;

	LimitPointer limit = get_or_create_limit(price, is_buy);

	if (is_buy and (not best_buy or price > best_buy)) {
		best_buy = price;
	} else if (not is_buy and (not best_sell or price < best_sell)) {
		best_sell = price;
	}

	limit->insert_order(order);
}

LimitPointer Book::get_or_create_limit(Price price, bool is_buy) {
	LimitPointer limit;
	if (is_buy) {
		if (is_in_buy_limits(price)) {
			limit = buy_limits[price];
		} else {
			limit = std::make_shared<Limit>(price);
			buy_tree.insert(price);
			buy_limits[price] = limit;
		}
	} else {
		if (is_in_sell_limits(price)) {
			limit = sell_limits[price];
		} else {
			limit = std::make_shared<Limit>(price);
			sell_tree.insert(price);
			sell_limits[price] = limit;
		}
	}
	return limit;
}

void Book::delete_order(OrderPointer& order, bool is_buy) {
	if (is_buy) {
		if (not is_in_buy_limits(order->get_price()))
			return;
		buy_limits[order->get_price()]->delete_order(order);
		check_for_empty_buy_limit(order->get_price());
	} else {
		if (not is_in_sell_limits(order->get_price()))
			return;
		sell_limits[order->get_price()]->delete_order(order);
		check_for_empty_sell_limit(order->get_price());
	}
}

void Book::print() {
	for (Price price : buy_tree){
		buy_limits[price]->print();
	}
	std::cout << "==== BUY SIDE ===" << std::endl;
	std::cout << "Best buy: " << best_buy << std::endl;
	std::cout << "Best sell: " << best_sell << std::endl;
	std::cout << "=== SELL SIDE ===" << std::endl;
	for (Price price : sell_tree){
		sell_limits[price]->print();
	}
}

Price Book::get_spread() {
	return best_sell - best_buy;
}
double Book::get_mid_price() {
	return (best_sell + best_buy) / 2.;
}

PriceTree& Book::get_buy_tree() { return buy_tree; }
PriceLimitMap& Book::get_buy_limits() { return buy_limits; }
PriceTree& Book::get_sell_tree() { return sell_tree; }
PriceLimitMap& Book::get_sell_limits() { return sell_limits; }
Price Book::get_best_buy(){ return best_buy; }
Price Book::get_best_sell() { return best_sell; }
Orders& Book::get_id_to_order() { return id_to_order; }
OrderStatus Book::get_order_status(ID id) {
	if (id_to_order.contains(id))
		return id_to_order[id]->get_status();
	return DELETED;
}
