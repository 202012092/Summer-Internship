#include <iostream>
#include "RBTree.h"

using namespace std;


class RBTree {

public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	RBNode searchTree(const int& k) {
		return SearchTree(this->root, k);
	}

	RBNode minimum(RBNode& node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	RBNode maximum(RBNode& node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	RBNode successor(RBNode& x)
	{
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		RBNode y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
	RBNode predecessor(RBNode& x) {
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		RBNode y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	void leftRotate(RBNode x) {
		RBNode y = x->right;
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
	void rightRotate(RBNode x) {
		RBNode y = x->left;
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

	void insert(const int& key) {
		RBNode node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;

		RBNode y = nullptr;
		RBNode x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}

	RBNode getRoot() {
		return this->root;
	}

	void deleteNode(const int& data) {
		DeleteNode(this->root, data);
	}

	void inorder() {
		InorderTraversal(this->root);
	}
private:
	RBNode root;
	RBNode TNULL;

	void nullNode(const RBNode& node, const RBNode& parent) {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}


	RBNode SearchTree(const RBNode& node, const int& key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return SearchTree(node->left, key);
		}
		return SearchTree(node->right, key);
	}

	void fixDelete(RBNode& node) {
		RBNode fix;
		while (node != root && node->color == 0) {
			if (node == node->parent->left) {
				fix = node->parent->right;
				if (fix->color == 1) {
					fix->color = 0;
					node->parent->color = 1;
					leftRotate(node->parent);
					fix = node->parent->right;
				}

				if (fix->left->color == 0 && fix->right->color == 0) {
					fix->color = 1;
					node = node->parent;
				}
				else {
					if (fix->right->color == 0) {
						fix->left->color = 0;
						fix->color = 1;
						rightRotate(fix);
						fix = node->parent->right;
					}
					fix->color = node->parent->color;
					node->parent->color = 0;
					fix->right->color = 0;
					leftRotate(node->parent);
					node = root;
				}
			}
			else {
				fix = node->parent->left;
				if (fix->color == 1) {
					fix->color = 0;
					node->parent->color = 1;
					rightRotate(node->parent);
					fix = node->parent->left;
				}

				if (fix->right->color == 0 && fix->right->color == 0) {
					fix->color = 1;
					node = node->parent;
				}
				else {
					if (fix->left->color == 0) {
						fix->right->color = 0;
						fix->color = 1;
						leftRotate(fix);
						fix = node->parent->left;
					}
					fix->color = node->parent->color;
					node->parent->color = 0;
					fix->left->color = 0;
					rightRotate(node->parent);
					node = root;
				}
			}
		}
		node->color = 0;
	}


	void changeColor(const RBNode& temp1, const RBNode& temp2) {
		if (temp1->parent == nullptr) {
			root = temp2;
		}
		else if (temp1 == temp1->parent->left) {
			temp1->parent->left = temp2;
		}
		else {
			temp1->parent->right = temp2;
		}
		temp2->parent = temp1->parent;
	}

	void DeleteNode(RBNode node, const int& key) {
		RBNode leafNode = TNULL;
		RBNode x, y;
		while (node != TNULL) {
			if (node->data == key) {
				leafNode = node;
			}

			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (leafNode == TNULL) {
			cout << "Couldn't find key in the tree" << endl;
			return;
		}

		y = leafNode;
		int y_original_color = y->color;
		if (leafNode->left == TNULL) {
			x = leafNode->right;
			changeColor(leafNode, leafNode->right);
		}
		else if (leafNode->right == TNULL) {
			x = leafNode->left;
			changeColor(leafNode, leafNode->left);
		}
		else {
			y = minimum(leafNode->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == leafNode) {
				x->parent = y;
			}
			else {
				changeColor(y, y->right);
				y->right = leafNode->right;
				y->right->parent = y;
			}

			changeColor(leafNode, y);
			y->left = leafNode->left;
			y->left->parent = y;
			y->color = leafNode->color;
		}
		delete leafNode;
		if (y_original_color == 0) {
			fixDelete(x);
		}
	}

	void fixInsert(RBNode& node) {
		RBNode fix;
		while (node->parent->color == 1) {
			if (node->parent == node->parent->parent->right) {
				fix = node->parent->parent->left;
				if (fix->color == 1) {
					fix->color = 0;
					node->parent->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRotate(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					leftRotate(node->parent->parent);
				}
			}
			else {
				fix = node->parent->parent->right;

				if (fix->color == 1) {
					fix->color = 0;
					node->parent->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						leftRotate(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					rightRotate(node->parent->parent);
				}
			}
			if (node == root) {
				break;
			}
		}
		root->color = 0;
	}

	void InorderTraversal(const RBNode& node) {
		if (node != TNULL) {
			InorderTraversal(node->left);
			cout << node->data << " ";
			InorderTraversal(node->right);
		}
	}
};

int main() {
	RBTree rbtree;
	rbtree.insert(18);
	rbtree.insert(30);
	rbtree.insert(59);
	rbtree.insert(11);
	rbtree.insert(19);
	rbtree.insert(51);
	rbtree.insert(101);
	rbtree.insert(80);
	rbtree.insert(89);
	rbtree.insert(91);
	rbtree.insert(99);
	rbtree.deleteNode(101);
	rbtree.inorder();
	return 0;
}