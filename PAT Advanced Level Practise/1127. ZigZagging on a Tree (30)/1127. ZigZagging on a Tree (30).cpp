// 1127. ZigZagging on a Tree (30).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>
#include <vector>

int *inOrder;
int *postOrder;
int rootIndex;

typedef struct node {
	int data;
	node *left, *right;
} *tree;

tree getTree(int l, int r)
{
	if (l > r) return NULL;
	int rootData = postOrder[rootIndex--];
	int index = -1;
	for (int i = l; i <= r; i ++)
		if (inOrder[i] == rootData) {
			index = i;
			break;
		}
	tree T = new node;
	T->data = rootData;
	T->right = getTree(index + 1, r);
	T->left = getTree(l, index - 1);
	return T;
}

void bfs(tree T)
{
	queue<tree> q;
	tree tail, last;
	q.push(T);
	tail = T;
	last = T;
	vector<tree> level;
	int count = 0;
	while (!q.empty()) {
		tree t = q.front();
		q.pop();
		level.push_back(t);
		if (t->left != NULL) {
			q.push(t->left);
			last = t->left;
		}
		if (t->right != NULL) {
			q.push(t->right);
			last = t->right;
		}
		if (t == tail) {
			if (t == T) 
				cout << t->data;
			else if (count % 2 == 0) {
				for (int i = level.size() - 1; i >= 0; i--)
					printf(" %d", level[i]->data);
			}
			else {
				for (int i = 0; i < level.size(); i++)
					printf(" %d", level[i]->data);
			}
			level.clear();
			count++;
			tail = last;
		}
	}
}

int main()
{
	int n;
	cin >> n;
	inOrder = new int[n];
	postOrder = new int[n];
	for (int i = 0; i < n; i++) cin >> inOrder[i];
	for (int i = 0; i < n; i++) cin >> postOrder[i];
	rootIndex = n - 1;
	tree T = getTree(0, n - 1);
	bfs(T);
    return 0;
}

