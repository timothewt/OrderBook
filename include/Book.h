#ifndef ORDERBOOK_BOOK_H
#define ORDERBOOK_BOOK_H

#include <unordered_map>
#include <set>
#include "Limit.h"

using LimitSet = std::set<LimitPointer, decltype(cmp_limits)>;
using PriceLimitMap = std::unordered_map<Price, LimitPointer>;

class Book {
public:
	LimitSet buy_tree{cmp_limits}; /**< tree containing all limits of the buy side */
	PriceLimitMap buy_limits; /**< Maps the buy limit prices to their limit objects*/

	LimitSet sell_tree{cmp_limits}; /**< tree containing all limits of the sell side */
	PriceLimitMap sell_limits; /**< Maps the sell limit prices to their limit objects*/

	LimitPointer best_buy; /**< Pointer to the best (highest) buy limit */
	LimitPointer best_sell; /**<Pointer to the best (lowest) sell limit */

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
public:
	Book() = default;

	/**
	 * @brief Places an order, tries to match it and inserts it in the book if it is not fulfilled
	 * @param order pointer to the order to place
	 */
	void place_order(OrderPointer& order);

	/** Print method */
	void print();
};


#endif //ORDERBOOK_BOOK_H
