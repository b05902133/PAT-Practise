// 1118. Birds in Forest (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int S[10001];

int findRoot(int x)
{
	if (S[x] < 0)
		return x;
	else return S[x] = findRoot(S[x]);
}

void unionSets(int s1, int s2)
{
	int r1 = findRoot(s1);
	int r2 = findRoot(s2);
	if (S[r1] < S[r2]) {
		S[r1] += S[r2];
		S[r2] = r1;
	}
	else {
		S[r2] += S[r1];
		S[r1] = r2;
	}
}

int main()
{
	fill(S, S + 10001, -1);
	int n, k, bi, q;
	cin >> n;
	int pic[10001];
	fill(pic, pic + 10001, 0);
	int count = 0;
	for (int i = 1; i <= n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> bi;
			if (pic[bi] == 0) {
				pic[bi] = i;
				count++;
			}
			else {
				unionSets(i, pic[bi]);
			}
		}
	}
	int nTree = 0;
	for (int i = 1; i <= n; i++)
		if (S[i] < 0) nTree++;
	printf("%d %d\n", nTree, count);
	cin >> q;
	for (int i = 0; i < q; i++) {
		int b1, b2;
		cin >> b1 >> b2;
		cout << (findRoot(pic[b1]) == findRoot(pic[b2]) ? "Yes" : "No") << endl;
	}
    return 0;
}

