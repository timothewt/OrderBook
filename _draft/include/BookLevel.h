#ifndef ORDERBOOK_BOOKLEVEL_H
#define ORDERBOOK_BOOKLEVEL_H


#include <vector>
#include "Order.h"
#include "Trade.h"

using Trades = std::vector<Trade>;

/**
 * @class BookLevel
 * @brief Represents a level of orders at a specific price (limit) in an order book.
 */
class BookLevel {
private:
	std::shared_ptr<Order> p_level_head; /**< Head of the order linked list at this price level (limit). */
	std::shared_ptr<Order> p_level_tail; /**< Tail of the order linked list at this price level (limit). */
	std::uint32_t length /**< Number of orders at this price level (limit), length of the linked list. */;

public:
	/**
	 * @brief Constructs an empty BookLevel.
	 */
	BookLevel();

	/**
	 * @brief Inserts an order into the book level.
	 * @param p_order The pointer to the order to be inserted.
	 */
	void insert_order(std::shared_ptr<Order>& p_order);

	/**
	 * @brief Deletes an order from the book level.
	 * @param p_order The pointer to the order to be deleted.
	 */
	void delete_order(std::shared_ptr<Order>& p_order);

	/**
	 * @brief Matches an incoming order against the orders in this level.
	 * @param p_order The pointer to the incoming order to be matched.
	 * @return A list of trades resulting from the match (can be empty).
	 */
	Trades match_order(std::shared_ptr<Order>& p_order);

	/**
	 * @brief Gets the head order of this book level.
	 * @return A shared pointer to the head order.
	 */
	std::shared_ptr<Order> get_p_level_head();

	/**
	 * @brief Gets the number of orders at this price level.
	 * @return The number of orders in the linked list.
	 */
	std::uint32_t get_length();
};

#endif //ORDERBOOK_BOOKLEVEL_H