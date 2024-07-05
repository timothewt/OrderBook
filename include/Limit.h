#ifndef ORDERBOOK_LIMIT_H
#define ORDERBOOK_LIMIT_H

#include "Order.h"
#include "Trade.h"

class Limit {
private:
	Price price; /**< Limit price */
	Length length; /**< Number of orders at this limit */
	Volume total_volume; /**< Total volume at this limit */

	OrderPointer head; /**< First order in the list (oldest) */
	OrderPointer tail; /**< Last order in the list (most recent) */

public:
	Limit(Price price): price(price), length(0), total_volume(0), head(nullptr), tail(nullptr) {}

	/**
	 * @brief Inserts an order at the end of the list
	 * @param order pointer to the order to insert
	 */
	void insert_order(OrderPointer& order);
	/**
	 * @brief Deletes an order from the limit order list
	 * @param order pointer to the order to delete
	 */
	void delete_order(OrderPointer& order);
	/**
	 * @brief Matches an opposite OrderType order to the current orders in the list
	 * @param order order to match
	 * @return Trades an array of trades with the matched order
	 */
	Trades match_order(OrderPointer& order);

	/** Getters */
	Price get_price() const;
	Length get_length();
	Volume get_total_volume();

	/** Print method */
	void print();
};


#endif //ORDERBOOK_LIMIT_H
