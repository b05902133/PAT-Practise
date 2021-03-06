// 1085. Perfect Sequence (25).cpp: 定义控制台应用程序的入口点。
//
/*
1085. Perfect Sequence (25)

时间限制 300 ms

内存限制 65536 kB

代码长度限制 16000 B

判题程序 Standard

作者 CAO, Peng
----------------------------------------------------------------------------------------------


Given a sequence of positive integers and another positive integer p. The sequence is said to
be a "perfect sequence" if M <= m * p where M and m are the maximum and minimum numbers in the
sequence, respectively.

Now given a sequence and a parameter p, you are supposed to find from the sequence as many numbers
as possible to form a perfect subsequence.
----------------------------------------------------------------------------------------------


Input Specification:

Each input file contains one test case. For each case, the first line contains two positive integers
N and p, where N (<= 10^5) is the number of integers in the sequence, and p (<= 10^9) is the parameter.
In the second line there are N positive integers, each is no greater than 10^9.
----------------------------------------------------------------------------------------------


Output Specification:

For each test case, print in one line the maximum number of integers that can be chosen to form a
perfect subsequence.
----------------------------------------------------------------------------------------------


Sample Input:

10 8
2 3 20 4 5 1 6 7 8 9

Sample Output:

8
----------------------------------------------------------------------------------------------


题意：

若一个正整数序列的最小的值乘以系数P( <= 10^9的正整数)，能使其大于序列中最大的元素，则此序列为一个
完美序列。输入系数P与有N个正整数的序列，求在序列中最多能选取多少个元素以构成完美序列

*/
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

int main()
{
	int n;
	long long p;
	cin >> n >> p;
	long long *sequence = new long long[n];
	for (int i = 0; i < n; i++)
		cin >> sequence[i];
	sort(sequence, sequence + n);
	int start = 0, len = 0, max = 0, i = 0;
	while (i < n) {
		if (sequence[start] * p >= sequence[i]) {
			len++;
			i++;
		}
		else {
			start++;
			len--;
		}
		if (len > max) max = len;
	}
	cout << max;
    return 0;
}

