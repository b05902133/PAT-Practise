// 1006. Sign In and Sign Out (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

typedef struct Node {
	string id;
	string sign_in_time;
	string sign_out_time;
} record;

int flag;

bool compare(record a, record b)
{
	return (flag == 0) ? a.sign_in_time < b.sign_in_time : a.sign_out_time > b.sign_out_time;
}

int main()
{
	int M;
	cin >> M;
	record * records = new record[M];
	for (int i = 0; i < M; i++) 
		cin >> records[i].id >> records[i].sign_in_time >> records[i].sign_out_time;
	flag = 0;
	sort(records, records + M, compare);
	cout << records[0].id;
	flag = 1;
	sort(records, records + M, compare);
	putchar(' ');
	cout << records[0].id;
	return 0;
}

