#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
	registerGen(argc, argv, 1);
	freopen("tree_input.txt", "w", stdout);
	int n = rnd.next(1, 40);
	cout << n << '\n';
	vector<int> a(n, 0);
	for (int i = 0; i < n; ++i)
		a[i] = rnd.next(1, 100);
	println(a);
	int m = rnd.next(1, 10);
	cout << m << '\n';
	for (int i = 0; i < n; ++i)
		cout << rnd.any(a) << ' ';
	return 0;
}