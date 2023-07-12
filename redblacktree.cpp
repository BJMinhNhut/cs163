#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class RedBlackTree
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
		~Node() {}
	};

	Node *root;

private:
	int getHeight(Node *root)
	{
		if (root == nullptr)
			return 0;
		return root->height;
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

		return root;
	}

	bool found(Node *root, int value)
	{
		if (root == nullptr)
			return false;
		if (root->value == value)
			return true;
		if (root->value < value)
			return found(root->right, value);
		return found(root->left, value);
	}

	void drawNode(vector<string> &output, vector<string> &linkAbove, Node *node, int level, int p, char linkChar)
	{
		if (!node)
			return;

		int h = output.size();
		string SP = " ";

		if (p < 0) // Shunt everything non-blank across
		{
			string extra(-p, ' ');
			for (string &s : output)
				if (!s.empty())
					s = extra + s;
			for (string &s : linkAbove)
				if (!s.empty())
					s = extra + s;
		}
		if (level < h - 1)
			p = max(p, (int)output[level + 1].size());
		if (level > 0)
			p = max(p, (int)output[level - 1].size());
		p = max(p, (int)output[level].size());

		// Fill in to left
		if (node->left)
		{
			string leftData = SP + to_string(node->left->value) + SP;
			drawNode(output, linkAbove, node->left, level + 1, p - leftData.size(), 'L');
			p = max(p, (int)output[level + 1].size());
		}

		// Enter this data
		int space = p - output[level].size();
		if (space > 0)
			output[level] += string(space, ' ');
		string nodeData = SP + to_string(node->value) + SP;
		output[level] += nodeData;

		// Add vertical link above
		space = p + SP.size() - linkAbove[level].size();
		if (space > 0)
			linkAbove[level] += string(space, ' ');
		linkAbove[level] += linkChar;

		// Fill in to right
		if (node->right)
			drawNode(output, linkAbove, node->right, level + 1, output[level].size(), 'R');
	}

	void recursiveDelete(Node *root)
	{
		if (root == nullptr)
			return;
		recursiveDelete(root->left);
		recursiveDelete(root->right);
		delete root;
	}

public:
	RedBlackTree() : root(nullptr) {}
	~RedBlackTree()
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

	void print()
	{
		cout << "\n";
		int h = getHeight(root);
		vector<string> output(h), linkAbove(h);
		drawNode(output, linkAbove, root, 0, 5, ' ');

		// Create link lines
		for (int i = 1; i < h; i++)
		{
			for (int j = 0; j < linkAbove[i].size(); j++)
			{
				if (linkAbove[i][j] != ' ')
				{
					int size = output[i - 1].size();
					if (size < j + 1)
						output[i - 1] += string(j + 1 - size, ' ');
					int jj = j;
					if (linkAbove[i][j] == 'L')
					{
						while (output[i - 1][jj] == ' ')
							jj++;
						for (int k = j + 1; k < jj - 1; k++)
							output[i - 1][k] = '_';
					}
					else if (linkAbove[i][j] == 'R')
					{
						while (output[i - 1][jj] == ' ')
							jj--;
						for (int k = j - 1; k > jj + 1; k--)
							output[i - 1][k] = '_';
					}
					linkAbove[i][j] = '|';
				}
			}
		}

		// Output
		for (int i = 0; i < h; i++)
		{
			if (i)
				cout << linkAbove[i] << '\n';
			cout << output[i] << '\n';
		}
	}
};

int main()
{
	freopen("tree_input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int numQueries;
	cin >> numQueries;

	RedBlackTree mTree;
	while (numQueries--)
	{
		int value;
		cin >> value;
		mTree.insert(value);
		cout << "Insert new value: " << value << '\n';
	}
	mTree.print();

	mTree.find(50);
	mTree.find(22);
	return 0;
}