#pragma once

#include <memory>
#include <vector>
#include <iostream>

// Template class implementation of red-black binary search tree (self balancing)
// (Not split into header and cpp files as doing so can cause issues with template classes)
template<class T>
class RedBlackSearchTree {
private:
	// data structure that represents a node in the tree
	struct Node {
		T key; // Holds the key
		std::vector<std::unique_ptr<T>> data; // Holds all data (including duplicates)
		std::shared_ptr<Node> parent = nullptr; // Pointer to the parent
		std::shared_ptr<Node> left = nullptr; // Pointer to left child
		std::shared_ptr<Node> right = nullptr; // Pointer to right child
		int color = 0; // 1 -> Red, 0 -> Black

		void printData() const { // Prints all data including duplicates

			for (const auto& item : data) {
				std::cout << *item;
			}
		}
	};

	// Members
	std::shared_ptr<Node> root;
	std::shared_ptr<Node> TNULL;

	// Search through tree to find Node with matching search key value
	std::shared_ptr<Node> searchTreeHelper(std::shared_ptr<Node> node, T key) const {
		if (node == TNULL || key == node->key) {
			return node;
		}

		if (key < node->key) {
			return searchTreeHelper(node->left, key);
		}
		return searchTreeHelper(node->right, key);
	}

	// Traverse through tree and print all data in order
	void inOrderTraversal(const std::shared_ptr<Node>& node) const {
		if (node != TNULL) {
			inOrderTraversal(node->left);
			for (const auto& item : node->data) {
				std::cout << *item;
			}
			inOrderTraversal(node->right);
		}
	}

	// Fix the red-black tree after a insert to the tree
	void fixInsert(std::shared_ptr<Node> k) {
		std::shared_ptr<Node> u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	// Find the node with the minimum key
	std::shared_ptr<Node> minimum(std::shared_ptr<Node> node) const {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// Find the node with the maximum key
	std::shared_ptr<Node> maximum(std::shared_ptr<Node> node) const {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	// Find the successor of a given node
	std::shared_ptr<Node> successor(std::shared_ptr<Node> x) const {
		// If the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		std::shared_ptr<Node> y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// Find the predecessor of a given node
	std::shared_ptr<Node> predecessor(std::shared_ptr<Node> x) const {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		std::shared_ptr<Node> y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// Rotate left at node x
	void leftRotate(std::shared_ptr<Node> x) {
		std::shared_ptr<Node> y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// Rotate right at node x
	void rightRotate(std::shared_ptr<Node> x) {
		std::shared_ptr<Node> y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

public:
	// Constructor that initializes member values
	RedBlackSearchTree() : TNULL(std::make_shared<Node>())
	{
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	// Search the tree for the key k and return the corresponding node
	std::shared_ptr<Node> searchTree(T k) const {
		return searchTreeHelper(this->root, k);
	}

	// Insert the key to the tree in its appropriate position and fix the tree
	void insert(std::unique_ptr<T> key) {

		// Ordinary Binary Search Insertion
		std::shared_ptr<Node> node = std::make_shared<Node>();
		node->key = *key;
		node->parent = nullptr;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1; // new node must be red

		std::shared_ptr<Node> y = nullptr;
		std::shared_ptr<Node> x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->key == x->key) { // Duplicate insert
				x->data.emplace_back(std::move(key));
				node.reset(); // Reset node as we don't need it, due to duplicate data
				return;
			}
			if (node->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->data.emplace_back(std::move(key));

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->key < y->key) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}

	// Get current root of the tree
	std::shared_ptr<Node> getRoot() const {
		return this->root;
	}

	// Prints all all data in all nodes in, in-order traversal
	void printAllNodesInOrder() const {
		inOrderTraversal(getRoot());
	}
};
