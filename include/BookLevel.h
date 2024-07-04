//
// Created by Timothe on 04/07/2024.
//

#ifndef ORDERBOOK_BOOKLEVEL_H
#define ORDERBOOK_BOOKLEVEL_H


#include <vector>
#include "Order.h"
#include "Trade.h"

using Trades = std::vector<Trade>;

class BookLevel {
private:
	std::shared_ptr<Order> p_level_head;
	std::shared_ptr<Order> p_level_tail;
	std::uint32_t length;
public:
	BookLevel();

	void insert_order(std::shared_ptr<Order>& p_order);
	void delete_order(std::shared_ptr<Order>& p_order);

	Trades match_order(std::shared_ptr<Order>& p_order);

	std::shared_ptr<Order> get_p_level_head();
	std::uint32_t get_length();
};


#endif //ORDERBOOK_BOOKLEVEL_H
