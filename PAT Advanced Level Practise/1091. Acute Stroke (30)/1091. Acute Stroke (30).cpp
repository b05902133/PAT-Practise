// 1091. Acute Stroke (30).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>
#include <vector>

int m, n, l, t;

struct node {
	int i, j, k;
	int value;
	int flag;
};

vector<node> nodesAround(node ***graph, node v)
{	/* 返回与v相邻的顶点*/
	vector<node>nodes;
	int i = v.i, j = v.j, k = v.k;
	if (i - 1 >= 0 && graph[i - 1][j][k].value == 1 && !graph[i - 1][j][k].flag) 
		nodes.push_back(graph[i - 1][j][k]);
	if (i + 1 < l && graph[i + 1][j][k].value == 1 && !graph[i + 1][j][k].flag)
		nodes.push_back(graph[i + 1][j][k]);
	if (j - 1 >= 0 && graph[i][j - 1][k].value == 1 && !graph[i][j - 1][k].flag)
		nodes.push_back(graph[i][j - 1][k]);
	if (j + 1 < m && graph[i][j + 1][k].value == 1 && !graph[i][j + 1][k].flag)
		nodes.push_back(graph[i][j + 1][k]);
	if (k - 1 >= 0 && graph[i][j][k - 1].value == 1 && !graph[i][j][k - 1].flag)
		nodes.push_back(graph[i][j][k - 1]);
	if (k + 1 < n && graph[i][j][k + 1].value == 1 && !graph[i][j][k + 1].flag)
		nodes.push_back(graph[i][j][k + 1]);
	return nodes;
}

int bfs(node ***graph, node s)
{
	if (s.flag || !s.value) return 0;
	int count = 0;
	queue<node> q;
	q.push(s);
	graph[s.i][s.j][s.k].flag = 1;
	count++;
	while (!q.empty()) {
		node v = q.front();
		q.pop();
		vector<node> nodes = nodesAround(graph, v);
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			q.push(*it);
			graph[it->i][it->j][it->k].flag = 1;
			count++;
		}
	}
	return count;
}

int main()
{
	cin >> m >> n >> l >> t;
	node ***graph = new node**[l]; //三维数组表示L层M*N矩阵
	for (int i = 0; i < l; i++) {
		graph[i] = new node*[m];
		for (int j = 0; j < m; j++) {
			graph[i][j] = new node[n];
			int value;
			for (int k = 0; k < n; k++) {
				cin >> value;
				graph[i][j][k] = {i, j, k, value, 0};
			}
		}
	}
	int total = 0;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++) {
				int count = bfs(graph, graph[i][j][k]); //BFS求连通分量中的元素数量
				if (count >= t) total += count;
			}
	cout << total;
    return 0;
}

