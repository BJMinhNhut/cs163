#include <iostream>
#include <vector>
using namespace std;

void insertHeap(int* heap, int& n, int x);
int getTopHeap(int* heap, int& n);
void upHeap(int* heap, int index);
void downHeap(int* heap, int n, int index);
void printHeap(int* heap, int n);

int main() {
	freopen("output.txt", "w", stdout);

	int* heap;
	int n = 0;

	heap = new int[50];

	vector<int> insertValues = {6, 2, 7, 3, 4, 5, 1};
	for (int v : insertValues) {
		insertHeap(heap, n, v);
		printHeap(heap, n);
	}

	delete[] heap;
	return 0;
}

void printHeap(int* heap, int n) {
	for (int i = 0; i < n; ++i) {
		cout << heap[i] << ' ';
		if ((i + 1) & i == 0)
			cout << '\n';
	}
	cout << '\n';
}

void upHeap(int* heap, int index) {
	while (index > 0) {
		int parent = index / 2;
		if (heap[index] > heap[parent]) {
			int temp = heap[index];
			heap[index] = heap[parent];
			heap[parent] = temp;
		}
	}
}

void insertHeap(int* heap, int& n, int x) {
	++n;
	heap[n - 1] = x;
	upHeap(heap, n - 1);
}

void downHeap(int* heap, int n, int index) {
	while (index < n) {
		int leftChild = index * 2 + 1;
		int rightChild = index * 2 + 2;
		int largest = index;

		if (leftChild < n && heap[largest] < heap[leftChild])
			largest = leftChild;
		if (rightChild < n && heap[largest] < heap[leftChild])
			largest = rightChild;
		if (largest != index) {
			int temp = heap[index];
			heap[index] = heap[largest];
			heap[largest] = temp;
			index = largest;
		} else
			break;
	}
}

int getTopHeap(int* heap, int& n) {
	if (n == 0)
		return -1;
	int ans = heap[0];
	heap[0] = heap[n - 1];
	--n;
	downHeap(heap, n, 0);
	return ans;
}