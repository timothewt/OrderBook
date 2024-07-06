#ifndef ORDERBOOK_BOOK_H
#define ORDERBOOK_BOOK_H

#include <unordered_map>
#include <set>
#include "Limit.h"

using PriceTree = std::set<Price>;
using PriceLimitMap = std::unordered_map<Price, LimitPointer>;
using Orders = std::unordered_map<ID, OrderPointer>;

class Book {
private:
	PriceTree buy_tree; /**< tree containing all limits of the buy side */
	PriceLimitMap buy_limits; /**< Maps the buy limit prices to their limit objects*/

	PriceTree sell_tree; /**< tree containing all limits of the sell side */
	PriceLimitMap sell_limits; /**< Maps the sell limit prices to their limit objects*/

	Price best_buy; /**< Pointer to the best (highest) buy limit */
	Price best_sell; /**<Pointer to the best (lowest) sell limit */

	Orders id_to_order; /**< Maps IDs to the corresponding order */

	/**
	 * @brief Checks if a limit is already in the buy book
	 * @param price price limit to check
	 * @return true if the limit is in the buy book false otherwise
	 */
	bool is_in_buy_limits(Price price);
	/**
	 * @brief Checks if a limit is already in the sell book
	 * @param price price limit to check
	 * @return true if the limit is in the sell book false otherwise
	 */
	bool is_in_sell_limits(Price price);
	/**
	 * @brief Updates the best_buy attribute after filling a limit
	 */
	void update_best_buy();
	/**
	 * @brief Updates the best_sell attribute after filling a limit
	 */
	void update_best_sell();
	/**
	 * @brief Checks for an empty buy limit (i.e. no order)
	 * @param price price limit
	 */
	void check_for_empty_buy_limit(Price price);
	/**
	 * @brief checks for an empty sell limit (i.e. no order)
	 * @param price price limit
	 */
	void check_for_empty_sell_limit(Price price);
	/**
	 * @brief Inserts an order into the book at its corresponding limit price
	 * @param order pointer to the order to place
	 */
	void insert_order(OrderPointer& order);
	/**
	 * @brief Used to get a reference to a limit at a certain price, creates it if it does not exist
	 * @param price limit price
	 * @param is_buy if it is the buy side
	 * @return the reference to the corresponding limit
	 */
	LimitPointer get_or_create_limit(Price price, bool is_buy);
	/**
	 * @brief Helper function to delete an order in the book
	 * @param order pointer to the order to delete
	 * @param is_buy true if the order is a buy order false otherwise
	 */
	void delete_order(OrderPointer& order, bool is_buy);

public:
	Book(): buy_tree(), buy_limits(), sell_tree(), sell_limits(), best_buy(0), best_sell(0) {}

	/**
	 * @brief Places an order, tries to match it and inserts it in the book if it is not fulfilled
	 * @param order pointer to the order to place
	 */
	Trades place_order(OrderPointer& order);
	/**
	 * @brief Deletes an order in the book if it is currently active
	 * @param id id of the order to delete
	 */
	void delete_order(ID id);

	/** Getters */
	Price get_spread();
	double get_mid_price();

	PriceTree& get_buy_tree();
	PriceLimitMap& get_buy_limits();
	PriceTree& get_sell_tree();
	PriceLimitMap& get_sell_limits();
	Price get_best_buy();
	Price get_best_sell();
	Orders& get_id_to_order();

	/** Print method */
	void print();

	OrderStatus get_order_status(ID i);
};


#endif //ORDERBOOK_BOOK_H
