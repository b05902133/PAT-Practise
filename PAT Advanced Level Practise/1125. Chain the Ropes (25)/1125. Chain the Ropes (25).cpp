// 1125. Chain the Ropes (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

int main()
{
	int n;
	cin >> n;
	int *rope = new int[n];
	for (int i = 0; i < n; i++) cin >> rope[i];
	sort(rope, rope + n);
	int sum = rope[0];
	for (int i = 1; i < n; i++)
		sum = (sum + rope[i]) / 2;
	cout << sum << endl;
    return 0;
}

