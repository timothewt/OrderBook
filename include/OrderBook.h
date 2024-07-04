#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H

#include <cstdint>
#include <map>
#include <unordered_map>
#include "BookLevel.h"
#include "Order.h"

/**
 * @class OrderBook
 * @brief Represents an limit order book with buy and sell orders.
 */
class OrderBook {
private:
	std::map<Price, BookLevel, std::greater<>> buy_orders; /**< Map of buy orders sorted by price (limit) descending. */
	std::map<Price, BookLevel, std::less<>> sell_orders; /**< Map of sell orders sorted by price (limit) ascending. */
	std::unordered_map<ID, std::shared_ptr<Order>> id_to_order; /**< Map of order IDs to orders. */

	/**
	 * @brief Checks and removes empty buy levels from the order book.
	 * @param price The price level to check.
	 */
	void check_buy_level_for_empty(Price price);

	/**
	 * @brief Checks and removes empty sell levels from the order book.
	 * @param price The price level to check.
	 */
	void check_sell_level_for_empty(Price price);

public:
	/**
	 * @brief Default constructor for OrderBook.
	 */
	OrderBook() = default;

	/**
	 * @brief Places an order into the order book.
	 * @param p_order The pointer to the order to be placed.
	 */
	void place_order(std::shared_ptr<Order>& p_order);

	/**
	 * @brief Cancels an order from the order book.
	 * @param p_order The pointer to the order to be canceled.
	 */
	void cancel_order(std::shared_ptr<Order>& p_order);

	/**
	 * @brief Cancels an order from the order book by its ID.
	 * @param order_id The ID of the order to be canceled.
	 */
	void cancel_order(ID order_id);

	/**
	 * @brief Checks if there are currently bid orders in the book.
	 * @return true if there is at least one sell order, false otherwise.
	 */
	bool has_bids();

	/**
	 * @brief Checks if there are currently ask orders in the book.
	 * @return true if there is at least one buy order, false otherwise.
	 */
	bool has_asks();

	/**
	 * @brief Retrieves the best bid currently available, which is the lowest sell price.
	 * @return The best bid in the order book.
	 */
	Price get_best_bid();

	/**
	 * @brief Retrieves the best ask currently available, which is the highest buy price.
	 * @return The best ask in the order book.
	 */
	Price get_best_ask();

	/**
	 * @brief Retrieves the buy orders from the order book.
	 * @return A map of buy orders organized by price.
	 */
	std::map<Price, BookLevel, std::greater<>> get_buy_orders();

	/**
	 * @brief Retrieves the sell orders from the order book.
	 * @return A map of sell orders organized by price.
	 */
	std::map<Price, BookLevel, std::less<>> get_sell_orders();

	/**
	 * @brief Retrieves the map of order IDs to orders.
	 * @return An unordered map of order IDs to shared pointers of orders.
	 */
	std::unordered_map<ID, std::shared_ptr<Order>> get_id_to_order_map();
};

#endif //ORDERBOOK_ORDERBOOK_H
