#include <gtest/gtest.h>
#include "../src/Book.h"

// Order Tests
TEST(order_test, fill_order_beyond_volume) {
	Order order(1, 1, BUY, 100, 50);
	EXPECT_THROW(order.fill(60), std::logic_error);
}

TEST(order_test, order_status_after_partial_fill) {
	Order order(1, 1, BUY, 100, 50);
	order.fill(20);
	EXPECT_EQ(order.get_status(), ACTIVE);
	EXPECT_EQ(order.get_volume(), 30);
}

TEST(order_test, order_status_after_full_fill) {
	Order order(1, 1, BUY, 100, 50);
	order.fill(50);
	EXPECT_EQ(order.get_status(), FULFILLED);
	EXPECT_EQ(order.get_volume(), 0);
}

TEST(order_test, set_order_status) {
	Order order(1, 1, BUY, 100, 50);
	order.set_status(DELETED);
	EXPECT_EQ(order.get_status(), DELETED);
}

TEST(order_test, order_initial_state) {
	Order order(1, 1, BUY, 100, 50);
	EXPECT_EQ(order.get_id(), 1);
	EXPECT_EQ(order.get_agent_id(), 1);
	EXPECT_EQ(order.get_type(), BUY);
	EXPECT_EQ(order.get_price(), 100);
	EXPECT_EQ(order.get_volume(), 50);
	EXPECT_EQ(order.get_status(), ACTIVE);
}

// Limit Tests
TEST(limit_test, insert_multiple_orders) {
	OrderPointer order1 = std::make_shared<Order>(1, 1, BUY, 100, 50);
	OrderPointer order2 = std::make_shared<Order>(2, 1, BUY, 100, 30);
	OrderPointer order3 = std::make_shared<Order>(3, 1, BUY, 100, 20);

	Limit limit(100);
	limit.insert_order(order1);
	limit.insert_order(order2);
	limit.insert_order(order3);

	EXPECT_EQ(limit.get_length(), 3);
	EXPECT_EQ(limit.get_total_volume(), 100);
}

TEST(limit_test, delete_order_from_limit) {
	OrderPointer order1 = std::make_shared<Order>(1, 1, BUY, 100, 50);
	OrderPointer order2 = std::make_shared<Order>(2, 1, BUY, 100, 30);
	OrderPointer order3 = std::make_shared<Order>(3, 1, BUY, 100, 20);

	Limit limit(100);
	limit.insert_order(order1);
	limit.insert_order(order2);
	limit.insert_order(order3);

	limit.delete_order(order2);

	EXPECT_EQ(limit.get_length(), 2);
	EXPECT_EQ(limit.get_total_volume(), 70);
}

TEST(limit_test, match_order_partial_fill) {
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 50);
	OrderPointer sell_order = std::make_shared<Order>(2, 2, SELL, 100, 30);

	Limit limit(100);
	limit.insert_order(sell_order);

	Trades trades = limit.match_order(buy_order);

	EXPECT_EQ(trades.size(), 1);
	EXPECT_EQ(trades[0].get_volume(), 30);
	EXPECT_EQ(buy_order->get_volume(), 20);
	EXPECT_EQ(sell_order->get_volume(), 0);
}

TEST(limit_test, match_order_full_fill) {
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 50);
	OrderPointer sell_order1 = std::make_shared<Order>(2, 2, SELL, 100, 30);
	OrderPointer sell_order2 = std::make_shared<Order>(3, 3, SELL, 100, 20);

	Limit limit(100);
	limit.insert_order(sell_order1);
	limit.insert_order(sell_order2);

	Trades trades = limit.match_order(buy_order);

	EXPECT_EQ(trades.size(), 2);
	EXPECT_EQ(trades[0].get_volume(), 30);
	EXPECT_EQ(trades[1].get_volume(), 20);
	EXPECT_EQ(buy_order->get_volume(), 0);
	EXPECT_EQ(sell_order1->get_volume(), 0);
	EXPECT_EQ(sell_order2->get_volume(), 0);
	EXPECT_EQ(limit.get_length(), 0);
	EXPECT_EQ(limit.get_total_volume(), 0);
}

TEST(limit_test, match_order_with_remaining_volume) {
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 50);
	OrderPointer sell_order1 = std::make_shared<Order>(2, 2, SELL, 100, 30);
	OrderPointer sell_order2 = std::make_shared<Order>(3, 3, SELL, 100, 10);

	Limit limit(100);
	limit.insert_order(sell_order1);
	limit.insert_order(sell_order2);

	Trades trades = limit.match_order(buy_order);

	EXPECT_EQ(trades.size(), 2);
	EXPECT_EQ(trades[0].get_volume(), 30);
	EXPECT_EQ(trades[1].get_volume(), 10);
	EXPECT_EQ(buy_order->get_volume(), 10);
	EXPECT_EQ(sell_order1->get_volume(), 0);
	EXPECT_EQ(sell_order2->get_volume(), 0);
}

// Book Tests
TEST(book_test, place_buy_order_no_match) {
	Book book;
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 50);
	Trades trades = book.place_order(buy_order);

	EXPECT_EQ(trades.size(), 0);
	EXPECT_EQ(book.get_buy_tree().size(), 1);
	EXPECT_EQ(book.get_buy_limits().size(), 1);
	EXPECT_EQ(book.get_best_buy(), 100);
}

TEST(book_test, place_sell_order_no_match) {
	Book book;
	OrderPointer sell_order = std::make_shared<Order>(1, 1, SELL, 100, 50);
	Trades trades = book.place_order(sell_order);

	EXPECT_EQ(trades.size(), 0);
	EXPECT_EQ(book.get_sell_tree().size(), 1);
	EXPECT_EQ(book.get_sell_limits().size(), 1);
	EXPECT_EQ(book.get_best_sell(), 100);
}

TEST(book_test, place_buy_order_with_match) {
	Book book;
	OrderPointer sell_order = std::make_shared<Order>(1, 1, SELL, 100, 30);
	book.place_order(sell_order);

	OrderPointer buy_order = std::make_shared<Order>(2, 2, BUY, 100, 50);
	Trades trades = book.place_order(buy_order);

	EXPECT_EQ(trades.size(), 1);
	EXPECT_EQ(trades[0].get_volume(), 30);
	EXPECT_EQ(buy_order->get_volume(), 20);
	EXPECT_EQ(sell_order->get_volume(), 0);

	EXPECT_EQ(book.get_sell_tree().size(), 0);
	EXPECT_EQ(book.get_sell_limits().size(), 0);
	EXPECT_EQ(book.get_buy_tree().size(), 1);
	EXPECT_EQ(book.get_buy_limits().size(), 1);
}

TEST(book_test, place_sell_order_with_match) {
	Book book;
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 30);
	book.place_order(buy_order);

	OrderPointer sell_order = std::make_shared<Order>(2, 2, SELL, 100, 50);
	Trades trades = book.place_order(sell_order);

	EXPECT_EQ(trades.size(), 1);
	EXPECT_EQ(trades[0].get_volume(), 30);
	EXPECT_EQ(sell_order->get_volume(), 20);
	EXPECT_EQ(buy_order->get_volume(), 0);

	EXPECT_EQ(book.get_buy_tree().size(), 0);
	EXPECT_EQ(book.get_buy_limits().size(), 0);
	EXPECT_EQ(book.get_sell_tree().size(), 1);
	EXPECT_EQ(book.get_sell_limits().size(), 1);
}

TEST(book_test, multiple_orders_same_price) {
	Book book;
	OrderPointer buy_order1 = std::make_shared<Order>(1, 1, BUY, 100, 30);
	OrderPointer buy_order2 = std::make_shared<Order>(2, 1, BUY, 100, 20);
	book.place_order(buy_order1);
	book.place_order(buy_order2);

	OrderPointer sell_order = std::make_shared<Order>(3, 2, SELL, 100, 40);
	Trades trades = book.place_order(sell_order);

	EXPECT_EQ(trades.size(), 2);
	EXPECT_EQ(trades[0].get_volume(), 30);
	EXPECT_EQ(trades[1].get_volume(), 10);
	EXPECT_EQ(sell_order->get_volume(), 0);
	EXPECT_EQ(buy_order1->get_volume(), 0);
	EXPECT_EQ(buy_order2->get_volume(), 10);

	EXPECT_EQ(book.get_buy_tree().size(), 1);
	EXPECT_EQ(book.get_buy_limits().size(), 1);
	EXPECT_EQ(book.get_sell_tree().size(), 0);
	EXPECT_EQ(book.get_sell_limits().size(), 0);
}

TEST(book_test, place_order_with_different_prices) {
	Book book;
	OrderPointer buy_order1 = std::make_shared<Order>(1, 1, BUY, 100, 30);
	OrderPointer buy_order2 = std::make_shared<Order>(2, 1, BUY, 110, 20);
	book.place_order(buy_order1);
	book.place_order(buy_order2);

	OrderPointer sell_order = std::make_shared<Order>(3, 2, SELL, 105, 40);
	Trades trades = book.place_order(sell_order);

	EXPECT_EQ(trades.size(), 1);
	EXPECT_EQ(trades[0].get_volume(), 20);
	EXPECT_EQ(sell_order->get_volume(), 20);
	EXPECT_EQ(sell_order->get_status(), ACTIVE);
	EXPECT_EQ(buy_order1->get_volume(), 30);
	EXPECT_EQ(buy_order1->get_status(), ACTIVE);
	EXPECT_EQ(buy_order2->get_volume(), 0);
	EXPECT_EQ(buy_order2->get_status(), FULFILLED);

	EXPECT_EQ(book.get_buy_tree().size(), 1);
	EXPECT_EQ(book.get_buy_limits().size(), 1);
	EXPECT_EQ(book.get_sell_tree().size(), 1);
	EXPECT_EQ(book.get_sell_limits().size(), 1);
}

TEST(book_test, delete_order) {
	Book book;
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 30);
	book.place_order(buy_order);

	book.delete_order(1);

	EXPECT_EQ(book.get_buy_tree().size(), 0);
	EXPECT_EQ(book.get_buy_limits().size(), 0);
}

TEST(book_test, delete_order_not_in_book) {
	Book book;
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 100, 30);
	book.place_order(buy_order);

	book.delete_order(2);

	EXPECT_EQ(book.get_buy_tree().size(), 1);
	EXPECT_EQ(book.get_buy_limits().size(), 1);
}

TEST(book_test, place_order_with_invalid_price) {
	Book book;
	OrderPointer buy_order = std::make_shared<Order>(1, 1, BUY, 0, 30);
	Trades trades = book.place_order(buy_order);

	EXPECT_EQ(trades.size(), 0);
	EXPECT_EQ(book.get_buy_tree().size(), 0);
	EXPECT_EQ(book.get_buy_limits().size(), 0);
}

TEST(book_test, match_orders_with_multiple_limits) {
	Book book;
	OrderPointer buy_order1 = std::make_shared<Order>(1, 1, BUY, 100, 30);
	OrderPointer buy_order2 = std::make_shared<Order>(2, 1, BUY, 110, 20);
	OrderPointer sell_order1 = std::make_shared<Order>(3, 2, SELL, 105, 15);
	OrderPointer sell_order2 = std::make_shared<Order>(4, 2, SELL, 95, 30);
	book.place_order(buy_order1);
	book.place_order(buy_order2);
	book.place_order(sell_order1);
	Trades trades = book.place_order(sell_order2);

	EXPECT_EQ(trades.size(), 2);
	EXPECT_EQ(trades[0].get_volume(), 5);
	EXPECT_EQ(trades[1].get_volume(), 25);

	EXPECT_EQ(book.get_buy_tree().size(), 1);
	EXPECT_EQ(book.get_buy_limits().size(), 1);
	EXPECT_EQ(book.get_sell_tree().size(), 0);
	EXPECT_EQ(book.get_sell_limits().size(), 0);
}

// Main function to run the tests
int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}