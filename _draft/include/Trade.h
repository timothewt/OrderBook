#ifndef ORDERBOOK_TRADE_H
#define ORDERBOOK_TRADE_H

#include "Types.h"

/**
 * @struct Trade
 * @brief Represents a trade resulting from matching orders in the order book.
 */
typedef struct {
	ID booked_order_id; /**< ID of the order already in the book that is filled. */
	ID incoming_order_id; /**< ID of the order just entered that fills the booked order. */
	Quantity qty; /**< Quantity of the trade. */
	Price price; /**< Price at which the trade occurred. */
} Trade;

#endif //ORDERBOOK_TRADE_H
