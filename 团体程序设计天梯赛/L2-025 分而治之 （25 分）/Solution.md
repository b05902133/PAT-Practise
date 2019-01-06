L2-025 �ֶ���֮ ��25 �֣�

[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805056195379200)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 600 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  

�ֶ���֮�����������Ǳ��ҳ��õĲ���֮һ����ս���У�����ϣ�����ȹ��µз��Ĳ��ֳ��У�ʹ��ʣ��ĳ��б�ɹ�����Ԯ��Ȼ���ٷ�ͷ�������ơ�Ϊ�˲�ı���ṩ�����ɴ������������������д�����ж�ÿ�������Ŀ����ԡ�

## �����ʽ��

�����ڵ�һ�и������������� N �� M����������10 000�����ֱ�Ϊ�з����и���������Ĭ�ϳ��д� 1 �� N ��ţ������������е�ͨ·��������� M �У�ÿ�и���һ��ͨ·�����ӵ��������еı�ţ������һ���ո�ָ����ڳ�����Ϣ֮�������ı����ϵ�з�������һ�������� K ���� 100�������� K �з�����ÿ�а����¸�ʽ������

> Np v[1] v[2] ... v[Np]


���� Np �Ǹ÷����мƻ����µĳ��������������ϵ�� v[i] �Ǽƻ����µĳ��б�š�

## �����ʽ��

��ÿһ�׷�����������о����YES���������NO��

## ����������

> 10 11  
> 8 7  
> 6 8  
> 4 5  
> 8 4  
> 8 1  
> 1 2  
> 1 4 
> 9 8  
> 9 1  
> 1 10  
> 2 4  
> 5  
> 4 10 3 8 4  
> 6 6 1 7 5 4 9  
> 3 1 8 4  
> 2 2 8  
> 7 9 8 7 6 5 4 2  


## ���������

NO  
YES  
YES  
NO  
NO  

## ˼·

�ڽӱ��ʾ��ͼ�洢���С���ÿһ����������Ǳ����µĳ��У���������δ�����µĳ��У��������ڽӵ��л�����δ�����µĳ��У��򲻿��С�

## ����

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> *graph = new vector<int>[n];
	for (int i = 0; i < m; i++) {
		int city1, city2;
		scanf("%d %d", &city1, &city2);
		city1--;
		city2--;
		graph[city1].push_back(city2);
		graph[city2].push_back(city1);
	}
	int k, nv, destroyedCity;
	scanf("%d", &k);
	bool *hasDestroyed = new bool[n];
	for (int i = 0; i < k; i++) {
		fill(hasDestroyed, hasDestroyed + n, false);
		scanf("%d", &nv);
		for (int j = 0; j < nv; j++) {
			scanf("%d", &destroyedCity);
			destroyedCity--;
			hasDestroyed[destroyedCity] = true;
		}
		bool flag = true;	
		for (int city = 0; city < n; city++) {
			if (hasDestroyed[city]) continue;
			if (graph[city].empty()) continue;
			for (int neighborCity : graph[city])
				if (!hasDestroyed[neighborCity]) {
					flag = false;
					break;
				}
			if (flag == false) break;
		}
		cout << (flag ? "YES" : "NO") << endl;
	}
	free(hasDestroyed);
	for (int i = 0; i < n; i++) {
		graph[i].clear();
		vector<int>().swap(graph[i]);
	}
	//free(graph); //pat�ύruntime error 
	return 0;
}

```

