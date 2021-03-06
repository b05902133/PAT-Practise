// 1110. Complete Binary Tree (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <queue>

struct node {
	int index, left, right;
};

void bfs(node *tree, int root, int n)
{
	queue<int> q;
	int *flag = new int[2*n + 1];
	fill(flag, flag + 2*n + 1, 0);
	tree[root].index = 0;
	flag[0] = 1;
	q.push(root);
	int last = root;
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		if (t != root && !flag[tree[t].index - 1]) {
			printf("NO %d\n", root);
			return;
		}
		int left = tree[t].left, right = tree[t].right;
		if (left != -1) {
			tree[left].index = tree[t].index * 2 + 1;
			flag[tree[left].index] = 1;
			q.push(left);
			last = left;
		}
		if (right != -1) {
			tree[right].index = tree[t].index * 2 + 2;
			flag[tree[right].index] = 1;
			q.push(right);
			last = right;
		}
	}
	printf("YES %d\n", last);
}

int main()
{
	int n;
	cin >> n;
	node *tree = new node[n];
	int *flag = new int[n];
	fill(flag, flag + n, 0);
	for (int i = 0; i < n; i++) {
		string left, right;
		cin >> left >> right;
		int l = left == "-" ? -1 : atoi(left.c_str());
		int r = right == "-" ? -1 : atoi(right.c_str());
		tree[i] = {-1, l, r};
		if (l != -1) flag[l] = 1;
		if (r != -1) flag[r] = 1;
	}
	int root;
	for (int i = 0; i < n; i++) 
		if (!flag[i]) {
			root = i;
			break;
		}
	bfs(tree, root, n);
    return 0;
}

