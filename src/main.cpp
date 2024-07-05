#include <iostream>
#include "../include/Limit.h"

int main() {
	std::cout << "Hello World!" << std::endl;
	OrderPointer o1(new Order(0, 0, OrderType::BUY, 10, 50));
	OrderPointer o2(new Order(1, 0, OrderType::BUY, 10, 40));
	OrderPointer o3(new Order(2, 0, OrderType::BUY, 10, 30));
	OrderPointer o4(new Order(3, 0, OrderType::SELL, 10, 80));

	Limit limit(10);
	limit.insert_order(o1);
	limit.insert_order(o2);
	limit.insert_order(o3);
	limit.print();

	Trades trades = limit.match_order(o4);
	limit.print();

	for(auto trade: trades) {
		trade.print();
	}

	return 0;
}