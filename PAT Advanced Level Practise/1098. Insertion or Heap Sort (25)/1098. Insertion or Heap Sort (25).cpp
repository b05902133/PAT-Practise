// 1098. Insertion or Heap Sort (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void Insert_Element(int *list, int k)
{
	int tmp = list[k], i;
	for (i = k - 1; i >= 0; i--) {
		if (list[i] > tmp)
			list[i + 1] = list[i];
		else break;
	}
	list[i + 1] = tmp;
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void percDown(int *list, int n)
{
	int parent, child, x = list[0];
	for (parent = 0; parent < n; parent = child) {
		child = parent * 2 + 1;
		if (child >= n) break;
		if (child + 1 < n && list[child + 1] > list[child])
			child++;
		if (x >= list[child]) break;
		list[parent] = list[child];
	}
	list[parent] = x;
}

int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	int *sorted = new int[n];
	for (int i = 0; i < n; i++) cin >> list[i];
	for (int i = 0; i < n; i++) cin >> sorted[i];
	int k = 0;
	for (int i = 0; i < n - 1; i++)
		if (sorted[i] > sorted[i + 1]) {
			k = i + 1;
			break;
		}
	for (int i = k; i < n; i ++)
		if (sorted[i] != list[i]) {
			printf("Heap Sort\n");
			for (int i = n - 1; i >= 0; i--)
				if (sorted[i] < sorted[0]) {
					swap(sorted + i, sorted);
					percDown(sorted, i);
					break;
				}
			goto PRINT;
		}
	printf("Insertion Sort\n");
	Insert_Element(sorted, k);
PRINT: {
	for (int i = 0; i < n; i++) {
		if (i != 0) putchar(' ');
		cout << sorted[i];
	}
	}
	return 0;
}

