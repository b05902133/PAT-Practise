// 1116. Come on! Let's C (20).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

int isPrime(int n)
{
	if (n == 1) return 0;
	if (n <= 3) return 1;
	for (int i = 2; i <= sqrt(n); i++) 
		if (n % i == 0) return 0;
	return 1;
}

int main()
{
	int flag[10000];
	fill(flag, flag + 10000, 0);
	int n, id, k;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> id;
		flag[id] = i;
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> id;
		printf("%04d: ", id);
		switch (flag[id]) {
		case 0: {printf("Are you kidding?\n"); break; }
		case -1: { printf("Checked\n"); break; }
		case 1: {printf("Mystery Award\n"); flag[id] = -1; break; }
		default : {
			cout << (isPrime(flag[id]) == 1 ? "Minion\n" : "Chocolate\n");
			flag[id] = -1;
		}
		}
	}
    return 0;
}

