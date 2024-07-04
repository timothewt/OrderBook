//
// Created by Timothe on 03/07/2024.
//

#ifndef ORDERBOOK_ORDER_H
#define ORDERBOOK_ORDER_H

#include <string>
#include <memory>
#include "OrderType.h"
#include "Types.h"

class Order {

private:

	ID id;
	ID agent_id;
	Quantity qty;
	Price price;
	OrderType order_type;

	std::shared_ptr<Order> p_prev_order;
	std::shared_ptr<Order> p_next_order;

public:

	Order(ID id, ID agent_id, Quantity qty, Price price, OrderType order_type);

	void fill(Quantity qty);

	bool is_fulfilled();

	ID get_id() const;
	ID get_agent_id() const;
	Quantity get_qty() const;
	Price get_price() const;
	OrderType get_order_type();
	std::shared_ptr<Order> get_p_prev_order();
	std::shared_ptr<Order> get_p_next_order();

	void set_p_prev_order(std::shared_ptr<Order> prev);
	void set_p_next_order(std::shared_ptr<Order> next);

	std::string to_string();

};

std::ostream& operator<<(std::ostream& os, Order order);

#endif //ORDERBOOK_ORDER_H
