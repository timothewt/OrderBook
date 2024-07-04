//
// Created by Timothe on 04/07/2024.
//

#ifndef ORDERBOOK_TRADE_H
#define ORDERBOOK_TRADE_H

#include "Types.h"

typedef struct {
	ID booked_order_id; // id of the order already in the book
	ID incoming_order_id; // id of the order just entered that fills the booked order
	Quantity qty;
	Price price;
} Trade;


#endif //ORDERBOOK_TRADE_H
