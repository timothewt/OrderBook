#ifndef ORDERBOOK_ORDER_H
#define ORDERBOOK_ORDER_H

#include <string>
#include <memory>
#include "OrderType.h"
#include "Types.h"

/**
 * @class Order
 * @brief Represents an order in the order book system.
 */
class Order {

private:
	ID id; /**< Unique identifier of the order. */
	ID agent_id; /**< Identifier of the agent placing the order. */
	Quantity qty; /**< Quantity of the order. */
	Price price; /**< Price of the order. */
	OrderType order_type; /**< Type of the order (BUY or SELL). */

	std::shared_ptr<Order> p_prev_order; /**< Pointer to the previous order in the linked list. */
	std::shared_ptr<Order> p_next_order; /**< Pointer to the next order in the linked list. */

public:
	/**
	 * @brief Constructor to initialize an Order object.
	 * @param id Unique identifier of the order.
	 * @param agent_id Identifier of the agent placing the order.
	 * @param qty Quantity of the order.
	 * @param price Price of the order.
	 * @param order_type Type of the order (BUY or SELL).
	 */
	Order(ID id, ID agent_id, Quantity qty, Price price, OrderType order_type);

	/**
	 * @brief Fills the order with a specified quantity.
	 * @param qty Quantity to fill in the order.
	 */
	void fill(Quantity qty);

	/**
	 * @brief Checks if the order has been completely fulfilled.
	 * @return true if the order is completely fulfilled, false otherwise.
	 */
	bool is_fulfilled();

	/**
	 * @brief Getter for the unique identifier of the order.
	 * @return ID Unique identifier of the order.
	 */
	ID get_id() const;

	/**
	 * @brief Getter for the identifier of the agent placing the order.
	 * @return ID Identifier of the agent placing the order.
	 */
	ID get_agent_id() const;

	/**
	 * @brief Getter for the quantity of the order.
	 * @return Quantity Quantity of the order.
	 */
	Quantity get_qty() const;

	/**
	 * @brief Getter for the price of the order.
	 * @return Price Price of the order.
	 */
	Price get_price() const;

	/**
	 * @brief Getter for the type of the order (BUY or SELL).
	 * @return OrderType Type of the order.
	 */
	OrderType get_order_type();

	/**
	 * @brief Getter for the pointer to the previous order in the linked list.
	 * @return std::shared_ptr<Order> Pointer to the previous order.
	 */
	std::shared_ptr<Order> get_p_prev_order();

	/**
	 * @brief Getter for the pointer to the next order in the linked list.
	 * @return std::shared_ptr<Order> Pointer to the next order.
	 */
	std::shared_ptr<Order> get_p_next_order();

	/**
	 * @brief Setter for the pointer to the previous order in the linked list.
	 * @param prev Pointer to the previous order.
	 */
	void set_p_prev_order(std::shared_ptr<Order> prev);

	/**
	 * @brief Setter for the pointer to the next order in the linked list.
	 * @param next Pointer to the next order.
	 */
	void set_p_next_order(std::shared_ptr<Order> next);

	/**
	 * @brief Generates a string representation of the order.
	 * @return std::string String representation of the order.
	 */
	std::string to_string();

};

/**
 * @brief Overloaded stream insertion operator for outputting Order object to ostream.
 * @param os Output stream.
 * @param order Order object to output.
 * @return std::ostream& Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, Order order);

#endif //ORDERBOOK_ORDER_H
