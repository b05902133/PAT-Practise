// 1104. Sum of Number Segments (20).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	double *list = new double[n];
	double total = 0.0;
	for (int i = 0; i < n; i++) {
		cin >> list[i];
		total += list[i] * (i + 1)*(n - i);
	}
	printf("%.2f\n", total);
    return 0;
}

