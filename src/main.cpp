#include <iostream>
#include "../include/Limit.h"
#include "../include/Book.h"

int main() {
	OrderPointer o1(new Order(0, 0, OrderType::BUY, 9, 50));
	OrderPointer o2(new Order(1, 0, OrderType::BUY, 9, 40));
	OrderPointer o3(new Order(2, 0, OrderType::BUY, 9, 30));
	OrderPointer o4(new Order(3, 0, OrderType::BUY, 10, 30));
	OrderPointer o5(new Order(4, 0, OrderType::SELL, 12, 40));
	OrderPointer o6(new Order(5, 0, OrderType::SELL, 12, 80));
	OrderPointer o7(new Order(6, 0, OrderType::SELL, 11, 80));
	OrderPointer o8(new Order(7, 0, OrderType::SELL, 11, 30));

	Book b;

	b.place_order(o1);
	b.place_order(o2);
	b.place_order(o3);
	b.place_order(o4);
	b.place_order(o5);
	b.place_order(o6);
	b.place_order(o7);
	b.place_order(o8);

	b.print();
	std::cout<<"=====================================" <<std::endl;
	b.delete_order(1);
	//b.delete_order(7);
	std::cout<<"=====================================" <<std::endl;

	b.print();

	return 0;
}