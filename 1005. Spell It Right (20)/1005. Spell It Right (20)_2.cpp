// 1005. Spell It Right (20)_2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string input;
	cin >> input;
	int sum = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		sum += input[i] - '0';
	}
	string str = to_string(sum);
	string hash[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	cout << hash[str[0] - '0'];
	for (int i = 1; i <str.length(); i++) {
		cout << " " + hash[str[i] - '0'];
	}
    return 0;
}

