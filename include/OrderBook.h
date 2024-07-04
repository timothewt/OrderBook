//
// Created by Timothe on 04/07/2024.
//

#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H

#include <cstdint>
#include <map>
#include <unordered_map>
#include "BookLevel.h"


class OrderBook {
private:
	std::map<Price, BookLevel, std::greater<>> buy_orders;
	std::map<Price, BookLevel, std::less<>> sell_orders;
	std::unordered_map<ID, std::shared_ptr<Order>> id_to_order;
public:
	OrderBook() = default;
	void place_order(std::shared_ptr<Order>& p_order);
	void cancel_order(std::shared_ptr<Order>& p_order);
	void cancel_order(ID order_id);
	void check_buy_level_for_empty(Price price);
	void check_sell_level_for_empty(Price price);
	std::map<Price, BookLevel, std::greater<>> get_buy_orders();
	std::map<Price, BookLevel, std::less<>> get_sell_orders();
	std::unordered_map<ID, std::shared_ptr<Order>> get_id_to_order_map();
};

#endif //ORDERBOOK_ORDERBOOK_H