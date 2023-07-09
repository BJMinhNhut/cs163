#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <algorithm>
#include <cassert>
#include <tuple>

using namespace std;

class BTree
{
	int MaxDegree;

private:
	struct Node
	{
		int MaxDegree;
		vector<int> keys;
		vector<Node *> children;

		Node(int MaxDegree, int value) : MaxDegree(MaxDegree), keys(1, value),
										 children(MaxDegree + 1, nullptr) {}
		Node(int MaxDegree) : MaxDegree(MaxDegree), keys(0),
							  children(MaxDegree + 1, nullptr) {}
	};

	struct SplitedNode
	{
		Node *left;
		Node *right;
		int value;
		SplitedNode(Node *left, Node *right, int value) : left(left), right(right), value(value) {}
	};

	Node *root;

private:
	bool isLeaf(Node *cur)
	{
		if (cur == nullptr)
			return false;
		return cur->children[0] == nullptr;
	}

	SplitedNode split(Node *cur)
	{
		assert(cur->keys.size() == MaxDegree);
		// cout << "Spliting______\n";
		// for (int v : cur->keys)
		// 	cout << v << "/";
		// cout << '\n';
		// for (auto child : cur->children)
		// {
		// 	if (!child)
		// 		break;
		// 	for (int v : child->keys)
		// 		cout << v << "/";
		// 	cout << ' ';
		// }
		// cout << '\n';

		int mid = MaxDegree / 2;
		Node *left = new Node(MaxDegree);
		Node *right = new Node(MaxDegree);
		int value = cur->keys[mid];

		// split key values
		left->keys.resize(mid);
		right->keys.resize(MaxDegree - 1 - mid);
		for (int i = 0; i < mid; ++i)
			left->keys[i] = cur->keys[i];
		for (int i = mid + 1; i < MaxDegree; ++i)
			right->keys[i - mid - 1] = cur->keys[i];

		// split children pointers
		for (int i = 0; i <= mid; ++i)
			left->children[i] = cur->children[i];

		for (int i = mid + 1; i <= MaxDegree; ++i)
			right->children[i - mid - 1] = cur->children[i];

		delete cur;
		return SplitedNode(left, right, value);
	}

	Node *insert(Node *cur, int value)
	{
		// if (cur)
		// 	for (int v : cur->keys)
		// 		cout << v << "/";
		// cout << ' ' << value << '\n';
		if (cur == nullptr)
		{
			cur = new Node(MaxDegree, value);
			return cur;
		}

		if (!isLeaf(cur))
		{
			// recursive call to find insert position
			int pos = upper_bound(cur->keys.begin(), cur->keys.end(), value) - cur->keys.begin();
			cur->children[pos] = insert(cur->children[pos], value);

			// fix overflow node
			if (cur->children[pos]->keys.size() == MaxDegree)
			{
				// cout << "Old children:\n";
				// for (auto child : cur->children)
				// {
				// 	if (!child)
				// 		cout << "0/";
				// 	else
				// 		for (int v : child->keys)
				// 			cout << v << "/";
				// 	cout << ' ';
				// }
				// cout << '\n';
				SplitedNode splited = split(cur->children[pos]);
				int pos = upper_bound(cur->keys.begin(), cur->keys.end(), splited.value) - cur->keys.begin();
				cur->keys.insert(cur->keys.begin() + pos, splited.value);
				cur->children[pos] = splited.left;
				cur->children.insert(cur->children.begin() + pos + 1, splited.right);
				cur->children.pop_back();
				// cout << "New children:\n";
				// for (auto child : cur->children)
				// {
				// 	if (!child)
				// 		cout << "null/";
				// 	else
				// 		for (int v : child->keys)
				// 			cout << v << "/";
				// 	cout << ' ';
				// }
				// cout << '\n';
			}
		}
		else
		{
			// insert new value to the leaf found
			int pos = upper_bound(cur->keys.begin(), cur->keys.end(), value) - cur->keys.begin();
			cur->keys.insert(cur->keys.begin() + pos, value);
		}
		return cur;
	}

	bool found(Node *cur, int value)
	{
		if (cur == nullptr)
			return false;
		for (int v : cur->keys)
			if (v == value)
				return true;
		int pos = upper_bound(cur->keys.begin(), cur->keys.end(), value) - cur->keys.begin();
		return found(cur->children[pos], value);
	}

	void recursiveDelete(Node *cur)
	{
		if (cur == nullptr)
			return;
		for (int i = 0; i < cur->children.size(); ++i)
			recursiveDelete(cur->children[i]);
		delete cur;
	}

public:
	BTree(int MaxDegree) : root(nullptr), MaxDegree(MaxDegree) {}
	~BTree()
	{
		recursiveDelete(root);
	}

	void insert(int value)
	{
		root = insert(root, value);
		// fix overflow root
		if (root->keys.size() == MaxDegree)
		{
			SplitedNode splited = split(root);
			root = new Node(MaxDegree, splited.value);
			root->children[0] = splited.left;
			root->children[1] = splited.right;
		}
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
		queue<pair<Node *, int>> q;
		q.push(make_pair(root, 0));
		int last = 0;
		while (!q.empty())
		{
			Node *cur;
			int lvl;
			tie(cur, lvl) = q.front();
			q.pop();

			if (lvl > last)
				cout << "\n";
			last = lvl;
			for (int i = 0; i < cur->keys.size(); i++)
				cout << cur->keys[i] << "/";
			cout << " ";
			for (int i = 0; i <= cur->keys.size(); i++)
			{
				if (cur->children[i] != nullptr)
					q.push(make_pair(cur->children[i], lvl + 1));
			}
		}
		cout << '\n';
	}
};

int main()
{
	freopen("tree_input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int numQueries;
	cin >> numQueries;

	BTree mTree(3);
	int cnt = 0;
	while (numQueries--)
	{
		int value;
		cin >> value;
		cout << "Insert new value: " << value << '\n';
		mTree.insert(value);
		mTree.print();
	}

	mTree.find(70);
	mTree.find(96);
	mTree.find(22);
	return 0;
}