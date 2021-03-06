// 1111. Online Map (30).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

#define INF 100000

int **D, **T;
int minDist, minTime;

int findMin(int *dist, int *collected, int n)
{
	int minV = -1, min = INF;
	for (int i = 0; i < n; i ++)
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	return minV;
}

vector<int> getPath(int *path, int s, int des)
{
	vector<int> p;
	if (path[des] == s)
		p.push_back(s);
	else p = getPath(path, s, path[des]);
	p.push_back(des);
	return p;
}

vector<int> dijkstraDist(int n, int s, int des)
{
	int *collected = new int[n];
	int *dist = new int[n];
	int *time = new int[n];
	int *path = new int[n];
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		dist[i] = D[s][i];
		path[i] = dist[i] < INF ? s : -1;
		time[i] = T[s][i];
	}
	collected[s] = 1;
	dist[s] = time[s] = 0;
	path[s] = s;
	while (1) {
		int min = findMin(dist, collected, n);
		if (min == -1) break;
		if (min == des) break;
		collected[min] = 1;
		for (int v = 0; v < n; v++) 
			if (!collected[v] && D[min][v] < INF) {
				if (dist[min] + D[min][v] < dist[v]) {
					dist[v] = dist[min] + D[min][v];
					time[v] = time[min] + T[min][v];
					path[v] = min;
				}
				else if (dist[min] + D[min][v] == dist[v] && time[min] + T[min][v] < time[v]) {
					time[v] = time[min] + T[min][v];
					path[v] = min;
				}
			}
	}
	minDist = dist[des];
	return getPath(path, s, des);
}

vector<int> dijkstraTime(int n, int s, int des)
{
	int *collected = new int[n];
	int *time = new int[n];
	int *num = new int[n];
	int *path = new int[n];
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		time[i] = T[s][i];
		path[i] = time[i] < INF ? s : -1;
		num[i] = time[i] < INF ? 2 : 1;
	}
	collected[s] = 1;
	time[s] = 0;
	path[s] = s;
	while (1) {
		int min = findMin(time, collected, n);
		if (min == -1) break;
		if (min == des) break;
		collected[min] = 1;
		for (int v = 0; v < n; v ++)
			if (!collected[v] && T[min][v] < INF) {
				if (time[min] + T[min][v] < time[v]) {
					time[v] = time[min] + T[min][v];
					num[v] = num[min] + 1;
					path[v] = min;
				}
				else if (time[min] + T[min][v] == time[v] && num[min] + 1 < num[v]) {
					num[v] = num[min] + 1;
					path[v] = min;
				}
			}
	}
	minTime = time[des];
	return getPath(path, s, des);
}

void printVector(vector<int> v)
{
	for (auto it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) printf(" -> ");
		cout << *it;
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	D = new int*[n];
	T = new int*[n];
	for (int i = 0; i < n; i++) {
		D[i] = new int[n];
		T[i] = new int[n];
		for (int j = 0; j < n; j++)
			D[i][j] = T[i][j] = INF;
	}
	for (int i = 0; i < m; i++) {
		int v1, v2, flag, len, time;
		cin >> v1 >> v2 >> flag >> len >> time;
		D[v1][v2] = len;
		T[v1][v2] = time;
		if (!flag) {
			D[v2][v1] = len;
			T[v2][v1] = time;
		}
	}
	int s, des;
	cin >> s >> des;
	vector<int> shortest = dijkstraDist(n, s, des);
	vector<int>  fastest = dijkstraTime(n, s, des);
	int flag = 0;
	if (shortest.size() != fastest.size())
		flag = 1;
	else
		for (int i = 0; i < shortest.size(); i++)
			if (shortest[i] != fastest[i]) {
				flag = 1;
				break;
			}
	if (flag) {
		printf("Distance = %d: ", minDist);
		printVector(shortest);
		printf("\nTime = %d: ", minTime);
		printVector(fastest);
	}
	else {
		printf("Distance = %d; Time = %d: ", minDist, minTime);
		printVector(shortest);
	}
	return 0;
}

