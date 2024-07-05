#include <iostream>
#include <memory>
#include <cstdint>

enum OrderType { BUY, SELL };

enum Color { RED, BLACK };

using Price = std::uint32_t;
using ID = std::uint64_t;
using Volume = std::uint64_t;

struct Order {
	ID id;
	ID agent_id;
	OrderType order_type;
	Volume volume;

	std::shared_ptr<Order> prev;
	std::shared_ptr<Order> next;

	Order(int id, int agent_id, OrderType order_type, int volume):
		id(id), agent_id(agent_id), order_type(order_type), volume(volume), prev(nullptr), next(nullptr) {}
};

class Limit {
private:
	Price price; /**< Limit price */
	int size; /**< Number of orders */
	Volume volume; /**< Volume available at this limit*/

	std::shared_ptr<Order> head_order; /**< First order of the price limit */
	std::shared_ptr<Order> tail_order; /**< Last order of the price limit */

	Color color; /**< Node color in the Red-Black Tree */
	std::shared_ptr<Limit> left; /**< Left child node */
	std::shared_ptr<Limit> right;  /**< Right child node */
	std::shared_ptr<Limit> parent;  /**< Parent node */

public:
	Limit(int price, Color color = RED):
		price(price), size(0), volume(0), head_order(nullptr), tail_order(nullptr), color(color), left(nullptr), right(nullptr) {}

	Price get_price() const;
	Color get_color() const;
	std::shared_ptr<Limit> get_left();
	std::shared_ptr<Limit> get_right();
	std::shared_ptr<Limit> get_parent();
	std::shared_ptr<Limit> get_uncle();
	void set_color(Color color);
	void set_left(std::shared_ptr<Limit>& node);
	void set_right(std::shared_ptr<Limit>& node);
	void set_parent(std::shared_ptr<Limit>& node);
};

Price Limit::get_price() const {
	return price;
}

Color Limit::get_color() const {
	return color;
}

std::shared_ptr<Limit> Limit::get_left() {
	return left;
}

std::shared_ptr<Limit> Limit::get_right() {
	return right;
}

std::shared_ptr<Limit> Limit::get_parent() {
	return parent;
}

std::shared_ptr<Limit> Limit::get_uncle() {
	if (parent == nullptr) return nullptr;
	std::shared_ptr<Limit> grandparent = parent->get_parent();
	if (grandparent == nullptr) return nullptr;
	if (parent == grandparent->get_left())
		return grandparent->get_right();
	else
		return grandparent->get_left();
}

void Limit::set_color(Color c) {
	color = c;
}

void Limit::set_left(std::shared_ptr<Limit>& node) {
	left = node;
}

void Limit::set_right(std::shared_ptr<Limit>& node) {
	right = node;
}

void Limit::set_parent(std::shared_ptr<Limit>& node) {
	parent = node;
}

class RBTree {
private:
	std::shared_ptr<Limit> root; /**< Root node of the tree */

	void bst_insert(std::shared_ptr<Limit>& node);
	void fix_insertion(std::shared_ptr<Limit>& node);

public:
	void insert_limit(int price);

	std::shared_ptr<Limit> get_root();
};

void RBTree::bst_insert(std::shared_ptr<Limit>& node) {
	if (root == nullptr) {
		root = node;
		return;
	}

	std::shared_ptr<Limit> curr = root;
	std::shared_ptr<Limit> parent = nullptr;

	while (curr != nullptr) {
		parent = curr;
		if (node->get_price() < curr->get_price())
			curr = curr->get_left();
		else if (node->get_price() > curr->get_price())
			curr = curr->get_right();
		else return;
	}

	if (node->get_price() < parent->get_price())
		parent->set_left(node);
	else
		parent->set_right(node);
	node->set_parent(parent);
}


void RBTree::fix_insertion(std::shared_ptr<Limit>& node) {
	if (root == node) {
		node->set_color(BLACK);
		return;
	}
	std::shared_ptr<Limit> parent = node->get_parent();
	if (parent->get_color() == BLACK) {
		return;
	}

	std::shared_ptr<Limit> uncle = node->get_uncle();
}

void RBTree::insert_limit(int price) {
	std::shared_ptr<Limit> node = std::make_shared<Limit>(price);
	bst_insert(node);
	fix_insertion(node);
}

std::shared_ptr<Limit> RBTree::get_root() {
	return root;
}

void printBT(const std::string& prefix, std::shared_ptr<Limit> node, bool isLeft)
{
	if( node != nullptr )
	{
		std::cout << prefix;
		std::cout << (isLeft ? "|--" : "L--");
		// print the value of the node
		std::cout << node->get_price() << std::endl;
		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), node->get_right(), true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->get_left(), false);
	}
}
void printBT(std::shared_ptr<Limit> node)
{
	printBT("", node, false);
}


int main() {
	RBTree tree;

	tree.insert_limit(3);
	tree.insert_limit(21);
	tree.insert_limit(32);
	/*tree.insert_limit(15);
	tree.insert_limit(6);
	tree.insert_limit(4);
	tree.insert_limit(9);*/

	std::shared_ptr<Limit> root = tree.get_root();
	printBT(root);

	return 0;
}
