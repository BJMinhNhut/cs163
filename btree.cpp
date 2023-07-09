#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class BTree
{
private:
	const static int INDENT = 10;

	struct Node
	{
		int leftVal, rightVal;
		int numVals;
	};

	Node *root;

private:
	Node *insert(Node *root, int value)
	{
	}

	bool found(Node *root, int value)
	{
	}

	void recursiveDelete(Node *root)
	{
		if (root == nullptr)
			return;

		delete root;
	}

public:
	BTree() : root(nullptr) {}
	~BTree()
	{
		recursiveDelete(root);
	}

	void insert(int value)
	{
		root = insert(root, value);
	}

	void find(int value)
	{
		if (found(root, value))
			cout << "Found " << value << '\n';
		else
			cout << value << " is not found\n";
	}
};

int main()
{
	freopen("tree_input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int numQueries;
	cin >> numQueries;

	BTree mTree;
	// while (numQueries--)
	// {
	// 	int value;
	// 	cin >> value;
	// 	mTree.insert(value);
	// 	cout << "Insert new value: " << value << '\n';
	// }
	// mBST.print();

	mTree.find(50);
	mTree.find(22);
	return 0;
}