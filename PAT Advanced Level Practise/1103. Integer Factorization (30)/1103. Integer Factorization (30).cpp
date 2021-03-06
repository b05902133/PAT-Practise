// 1103. Integer Factorization (30)_2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

vector<int> factors;
vector<int> bestPath;
vector<int> currentPath;
int n, k, p, maxFace = 0;

void init()
{
	for (int i = 0; i <= n; i++) {
		int factor = pow(i, p);
		if (factor > n) break;
		factors.push_back(factor);
	}
}

void dfs(int index, int level, int sum, int face)
{
	if (level == k) {
		if (sum == n && face > maxFace) {
			bestPath = currentPath;
			maxFace = face;
		}
		return;
	}
	if (sum >= n) return;
	for (int i = 0; index - i > 0; i++) {
		currentPath.push_back(index - i);
		dfs(index - i, level + 1, sum + factors[index - i], face + index - i);
		currentPath.pop_back();
	}
}

int main()
{
	cin >> n >> k >> p;
	init();
	dfs(factors.size() - 1, 0, 0, 0);
	if (maxFace == 0) {
		printf("Impossible\n");
		return 0;
	}
	printf("%d = ", n);
	for (auto it = bestPath.begin(); it != bestPath.end(); it++) {
		if (it != bestPath.begin()) printf(" + ");
		printf("%d^%d", *it, p);
	}
    return 0;
}

