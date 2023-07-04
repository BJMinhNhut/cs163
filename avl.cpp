#include <iostream>
using namespace std;

class AVL
{
private:
	const static int INDENT = 10;

	struct Node
	{
		int value;
		Node *left;
		Node *right;
		int height;

		Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}
		~Node()
		{
			delete left;
			delete right;
		}
	};

	Node *root;

private:
	int getHeight(Node *root)
	{
		if (root == nullptr)
			return 0;
		return root->height;
	}

	Node *rotateLeft(Node *root)
	{
		Node *newRoot = root->right;

		root->right = newRoot->left;
		newRoot->left = root;

		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

		return newRoot;
	}

	Node *rotateRight(Node *root)
	{
		Node *newRoot = root->left;

		root->left = newRoot->right;
		newRoot->right = root;

		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

		return newRoot;
	}

	Node *insert(Node *root, int value)
	{
		// Insert
		if (root == nullptr)
			return new Node(value);
		if (value == root->value)
			return root;
		if (value > root->value)
			root->right = insert(root->right, value);
		if (value < root->value)
			root->left = insert(root->left, value);

		// Set height
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));

		// Rotate
		int deltaHeight = getHeight(root->left) - getHeight(root->right);

		// Left Left
		if (deltaHeight > 1 && value < root->left->value)
			return rotateRight(root);

		// Right Right
		if (deltaHeight < -1 && value > root->right->value)
			return rotateLeft(root);

		// Left Right
		if (deltaHeight > 1 && value > root->left->value)
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}

		// Right Left
		if (deltaHeight < -1 && value < root->right->value)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}

	void print(const std::string &prefix, const Node *node, bool isLeft)
	{
		if (node != nullptr)
		{
			cout << prefix;

			cout << (isLeft ? "|--" : "L--");

			// print the value of the node
			cout << node->value << endl;

			// enter the next tree level - left and right branch
			print(prefix + (isLeft ? "|   " : "    "), node->left, true);
			print(prefix + (isLeft ? "|   " : "    "), node->right, false);
		}
	}

public:
	AVL() : root(nullptr) {}
	~AVL()
	{
		delete root;
	}

	void insert(int value)
	{
		root = insert(root, value);
	}

	void erase(int value)
	{
	}

	void print()
	{
		cout << "\n";
		print("", root, false);
	}
};

int main()
{
	freopen("tree_input.txt", "r", stdin);

	int numQueries;
	cin >> numQueries;

	AVL mAVL;
	while (numQueries--)
	{
		int value;
		cin >> value;
		mAVL.insert(value);
		cout << "Insert new value: " << value;
		mAVL.print();
	}

	return 0;
}