#ifndef ORDERBOOK_TRADE_H
#define ORDERBOOK_TRADE_H

#include <vector>
#include <iostream>
#include "Types.h"

class Trade {
private:
	ID incoming_order; /**< Incoming order in the book */
	ID matched_order; /**< Matched order (previously in book) */
	Price price; /**< Price at which the trade is done */
	Volume volume; /**< Trade volume / number of shares traded */

public:
	Trade(ID incoming_order, ID matched_order, Price price, Volume volume):
		incoming_order(incoming_order), matched_order(matched_order), price(price), volume(volume) {}

	/** Getters */
	ID get_incoming_order() const { return incoming_order; }
	ID get_matched_order() const { return matched_order; }
	Price get_price() const { return price; }
	Volume get_volume() const { return volume; }

	/** Print method */
	void print() {
		std::cout << "Trade(Incoming order: " << incoming_order << ", Matched order: " << matched_order << ", Price: " << price << ", Volume: " << volume << ")" << std::endl;
	}
};

using Trades = std::vector<Trade>;

#endif //ORDERBOOK_TRADE_H
