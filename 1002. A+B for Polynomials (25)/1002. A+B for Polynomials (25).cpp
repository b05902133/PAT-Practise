// 1002. A+B for Polynomials (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void Merge(float *Ae, float *Ac, int AL, float *Be, float *Bc, int BL)
{	/* Merge 2 polynomial */
	float *Me = new float[AL + BL];
	float *Mc = new float[AL + BL];
	int i = 0, j = 0, flag = 0, count = 0;
	while (i < AL && j < BL) {
		if (Ae[i] > Be[j]) {
			Me[count] = Ae[i];
			Mc[count++] = Ac[i++];
		}
		else if (Ae[i] < Be[j]) {
			Me[count] = Be[j];
			Mc[count++] = Bc[j++];
		}
		else {
			if (Ac[i] + Bc[j] != 0) {
				Me[count] = Ae[i];
				Mc[count++] = Ac[i] + Bc[j];
			}
			i++;
			j++;
		}
	}//while
	while (i < AL) {
		Me[count] = Ae[i];
		Mc[count++] = Ac[i++];
	}
	while (j < BL) {
		Me[count] = Be[j];
		Mc[count++] = Bc[j++];
	}
	printf("%d", count);
	for (i = 0; i < count; i++)
		printf(" %.0f %.1f", Me[i], Mc[i]);
}

int main()
{
	int i;
	/* 输入多项式Ａ：*/
	int AL;
	cin >> AL;
	float *Ae = new float[AL];
	float *Ac = new float[AL];
	for (i = 0; i < AL; i++)
		cin >> Ae[i] >> Ac[i];
	/* Input polynomial B: */
	int BL;
	cin >> BL;
	float *Be = new float[BL];
	float *Bc = new float[BL];
	for (i = 0; i < BL; i++)
		cin >> Be[i] >> Bc[i];
	Merge(Ae, Ac, AL, Be, Bc, BL);
	return 0;
}

