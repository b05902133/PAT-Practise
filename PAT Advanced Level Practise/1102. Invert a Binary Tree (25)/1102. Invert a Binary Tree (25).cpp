// 1102. Invert a Binary Tree (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <queue>

struct node {
	int index;
	int left, right;
};

void level(node *tree, int root)
{
	queue<int> q;
	q.push(root);
	int flag = 0;
	while (!q.empty()) {
		int n = q.front();
		q.pop();
		if (flag) putchar(' ');
		else flag = 1;
		cout << n;
		if (tree[n].left != -1) q.push(tree[n].left);
		if (tree[n].right != -1) q.push(tree[n].right);
	}
}

void inOrder(node *tree, int root)
{
	if (tree[root].left != -1) {
		inOrder(tree, tree[root].left);
		putchar(' ');
	}
	cout << root;
	if (tree[root].right != -1) {
		putchar(' ');
		inOrder(tree, tree[root].right);
	}
}

int main()
{
	int n;
	cin >> n;
	node *tree = new node[n];
	int *flag = new int[n];
	for (int i = 0; i < n; i++) {
		string l, r;
		int left, right;
		cin >> r >> l;
		left = l == "-" ? -1 : atoi(l.c_str());
		right = r == "-" ? -1 : atoi(r.c_str());
		tree[i] = {i, left, right};
		if (left != -1) flag[left] = 1;
		if (right != -1) flag[right] = 1;
	}
	int root;
	for (int i = 0; i < n; i ++)
		if (flag[i] != 1) {
			root = i; //The only node that had not appeared as a child of others is the root
			break;
		}
	level(tree, root);
	cout << endl;
	inOrder(tree, root);
    return 0;
}

