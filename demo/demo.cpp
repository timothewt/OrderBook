#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Book.h"

std::vector<std::string> split(const std::string &line, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(line);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void write_final_order_book(Book& book) {
	std::ofstream file("C:\\Users\\Timothe\\Documents\\Projects\\OrderBook\\demo\\final_order_book.csv");
	if (!file.is_open()) {
		std::cerr << "Error opening file.\n";
		return;
	}
	file << "Price Limit,Side,Volume\n";
	for (auto& limit: book.get_buy_limits())
		file << limit.first << ",BUY,"<< limit.second->get_total_volume() << "\n";
	for (auto& limit: book.get_sell_limits())
		file << limit.first << ",SELL,"<< limit.second->get_total_volume() << "\n";
}

void demo() {
	std::ifstream file("C:\\Users\\Timothe\\Documents\\Projects\\OrderBook\\demo\\sample_operations.csv");
	if (!file.is_open()) {
		std::cerr << "Error opening file.\n";
		return;
	}

	Book book;
	std::uint64_t nb_op = 0;
	std::chrono::time_point<std::chrono::system_clock> start, end;

	std::string line;
	std::getline(file, line);

	start = std::chrono::system_clock::now();
	while (std::getline(file, line)) {
		std::vector<std::string> fields = split(line, ',');

		if (fields[0] == "PLACE") {
			OrderPointer order(new Order(stoi(fields[1]), 0, stoi(fields[2]) == BUY ? BUY : SELL, stoi(fields[3]), stoi(fields[4])));
			Trades trades = book.place_order(order);
			nb_op += trades.size() + (order->get_status() == ACTIVE); // each trade is an operation; if the order is active it has been inserted otherwise no operation
		} else {
			book.delete_order(stoi(fields[1]));
			nb_op++;
		}
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
	std::cout << "Operations per second: " << (double)nb_op / elapsed_seconds.count() << std::endl;

	file.close();

	write_final_order_book(book);
}
