#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

class RedBlackTree {
   private:
	const static int INDENT = 10;

	struct Node {
		int value;
		Node* left;
		Node* right;
		Node* parent;
		bool isRed;

		Node(int value)
		    : value(value), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {}
		~Node() {}

		Node* grandpa() {
			if (parent == nullptr)
				return nullptr;
			return parent->parent;
		}
	};

	Node* root;
	bool LeftLeft, RightRight, LeftRight, RightLeft;

   private:
	bool found(Node* cur, int value) {
		if (cur == nullptr)
			return false;
		if (cur->value == value)
			return true;
		if (cur->value < value)
			return found(cur->right, value);
		return found(cur->left, value);
	}

	void recursiveDelete(Node* root) {
		if (root == nullptr)
			return;
		recursiveDelete(root->left);
		recursiveDelete(root->right);
		delete root;
	}

	void printHelper(Node* root, string indent, bool last) {
		// print the tree structure on the screen
		if (root != nullptr) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			} else {
				cout << "L----";
				indent += "|    ";
			}

			string sColor = root->isRed ? "RED" : "BLACK";
			cout << root->value << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

	Node* BSTInsert(int value) {
		Node* insertNode = new Node(value);

		Node *par = nullptr, *cur = root;
		while (cur != nullptr) {
			par = cur;
			if (value < par->value)
				cur = par->left;
			else
				cur = par->right;
		}

		if (par == nullptr) {
			root = insertNode;
		} else {
			insertNode->parent = par;
			if (value < par->value)
				par->left = insertNode;
			else
				par->right = insertNode;
		}

		return insertNode;
	}

	void rotateRight(Node* cur) {
		Node* newRoot = cur->left;
		cur->left = newRoot->right;
		if (newRoot->right != nullptr)
			newRoot->right->parent = cur;

		newRoot->parent = cur->parent;
		if (cur->parent == nullptr) {
			root = newRoot;
		} else if (cur->parent->right == cur) {
			cur->parent->right = newRoot;
		} else
			cur->parent->left = newRoot;

		newRoot->right = cur;
		cur->parent = newRoot;
	}

	void rotateLeft(Node* cur) {
		Node* newRoot = cur->right;
		cur->right = newRoot->left;
		if (newRoot->left != nullptr)
			newRoot->left->parent = cur;

		newRoot->parent = cur->parent;
		if (cur->parent == nullptr) {
			root = newRoot;
		} else if (cur->parent->right == cur) {
			cur->parent->right = newRoot;
		} else
			cur->parent->left = newRoot;

		newRoot->left = cur;
		cur->parent = newRoot;
	}

	bool isRed(Node* cur) { return cur != nullptr && cur->isRed; }

	void fixInsert(Node* cur) {
		Node* uncle;
		while (isRed(cur->parent) && cur->grandpa() != nullptr) {  // red red conflict
			if (cur->parent == cur->grandpa()->right) {
				uncle = cur->grandpa()->left;
				if (isRed(uncle)) {
					// Case 1
					cur->grandpa()->isRed = true;
					uncle->isRed = false;
					cur->parent->isRed = false;
					cur = cur->grandpa();
				} else {
					if (cur == cur->parent->left) {
						// Case 2.1
						cur = cur->parent;
						rotateRight(cur);
					}
					// Case 2.2
					cur->parent->isRed = false;
					cur->grandpa()->isRed = true;
					rotateLeft(cur->grandpa());
				}
			} else {
				uncle = cur->grandpa()->right;
				if (isRed(uncle)) {
					// Case 1
					cur->grandpa()->isRed = true;
					uncle->isRed = false;
					cur->parent->isRed = false;
					cur = cur->grandpa();
				} else {
					if (cur == cur->parent->right) {
						// Case 2.1
						cur = cur->parent;
						rotateLeft(cur);
					}
					// Case 2.2
					cur->parent->isRed = false;
					cur->grandpa()->isRed = true;
					rotateRight(cur->grandpa());
				}
			}
		}
		root->isRed = false;  // Case 0
	}

   public:
	RedBlackTree()
	    : root(nullptr), RightRight(false), LeftLeft(false), LeftRight(false), RightLeft(false) {}

	~RedBlackTree() { recursiveDelete(root); }

	void insert(int value) {
		// BST Insert
		Node* insertPos = BSTInsert(value);
		// Fix
		fixInsert(insertPos);
	}

	void find(int value) {
		if (found(root, value))
			cout << "Found " << value << '\n';
		else
			cout << value << " is not found\n";
	}

	void print() { printHelper(root, "", true); }
};

int main() {
	freopen("tree_input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int numQueries;
	cin >> numQueries;

	RedBlackTree mTree;
	while (numQueries--) {
		int value;
		cin >> value;
		mTree.insert(value);
		cout << "Insert new value: " << value << '\n';
		mTree.print();
	}

	mTree.find(50);
	mTree.find(22);
	return 0;
}