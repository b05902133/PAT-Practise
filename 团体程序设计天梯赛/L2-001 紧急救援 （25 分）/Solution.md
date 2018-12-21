# L2-001 ������Ԯ ��25 �֣�

[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805073643683840)

> ����: ��Խ
> ��λ: �㽭��ѧ
> ʱ������: 200 ms
> �ڴ�����: 64 MB
> ���볤������: 16 KB

��Ϊһ�����е�Ӧ����Ԯ����ĸ����ˣ�����һ�������ȫ����ͼ���ڵ�ͼ����ʾ�ж����ɢ�ĳ��к�һЩ���ӳ��еĿ��ٵ�·��ÿ�����еľ�Ԯ��������ÿһ�������������еĿ��ٵ�·���ȶ����ڵ�ͼ�ϡ������������н��������绰�����ʱ����������Ǵ�����ľ�Ԯ�Ӿ�������·��أ�ͬʱ��һ·���ټ������ܶ�ľ�Ԯ�ӡ�

## �����ʽ:

�����һ�и���4��������N��M��S��D������N��2��N��500���ǳ��еĸ�����˳�������еı��Ϊ0 ~ (N?1)��M�ǿ��ٵ�·��������S�ǳ����صĳ��б�ţ�D��Ŀ�ĵصĳ��б�š�

�ڶ��и���N�������������е�i�����ǵ�i�����еľ�Ԯ�ӵ���Ŀ�����ּ��Կո�ָ�������M���У�ÿ�и���һ�����ٵ�·����Ϣ���ֱ��ǣ�����1������2�����ٵ�·�ĳ��ȣ��м��ÿո�ֿ������־�Ϊ�����Ҳ�����500�����뱣֤��Ԯ���������Ž�Ψһ��

## �����ʽ:

��һ��������·�����������ܹ��ټ������ľ�Ԯ���������ڶ��������S��D��·���о����ĳ��б�š����ּ��Կո�ָ��������β�����ж���ո�

## ��������:
4 5 0 3  
20 30 40 10  
0 1 1  
1 3 2  
0 3 3  
0 2 2  
2 3 2  


## �������:
2 60  
0 1 3  

## ˼·

dijkstra�����·������ÿһ�����㣬��¼��ǰ���·�������룬��ǰ����ö����·���ϵľ�Ԯ����������ǰ����ö�������·�����������ö����Ƿ���¼����

## ����

[L2-001 ������Ԯ ��25 �֣�.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-001%20%E7%B4%A7%E6%80%A5%E6%95%91%E6%8F%B4%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-001%20%E7%B4%A7%E6%80%A5%E6%95%91%E6%8F%B4%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <stack>
using namespace std;

#define INF 249501

int findMin(int *dist, bool *collected, int n) {
	int minV = -1, min = INF;
	for (int i = 0; i < n; i++) 
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	return minV;
}

void printPath(int *path, int src, int des) {
	stack<int> s;
	int v = des;
	while (v != src) {
		s.push(v);
		v = path[v];
	}
	printf("%d", src);
	while (!s.empty()) {
		printf(" %d", s.top());
		s.pop();
	}
}

void dijkstra(int **graph, int *weight, int n, int src, int des) {
	int *dist = new int[n]; 
	int *nTeams = new int[n];
	int *path = new int[n];
	int *nPaths = new int[n];
	bool *collected = new bool[n];
	for (int i = 0; i < n; i++) {
		dist[i] = graph[src][i];
		nTeams[i] = dist[i] < INF ? weight[src] + weight[i] : 0;
		path[i] = dist[i] < INF ? src : -1;
		nPaths[i] = dist[i] < INF ? 1 : 0;
		collected[i] = false;
	}
	dist[src] = 0;
	nTeams[src] = weight[src];
	path[src] = src;
	nPaths[src] = 1;
	collected[src] = true;
	while (true) {
		int minV = findMin(dist, collected, n);
		if (minV == -1) break;
		if (minV == des) break;
		collected[minV] = true;	
		for (int v = 0; v < n; v++)
			if (!collected[v] && graph[minV][v] < INF) {
				if (dist[minV] + graph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + graph[minV][v];
					nTeams[v] = nTeams[minV] + weight[v];
					path[v] = minV;
					nPaths[v] = nPaths[minV];
				}
				else if (dist[minV] + graph[minV][v] == dist[v]) {
					nPaths[v] += nPaths[minV];
					if (nTeams[minV] + weight[v] > nTeams[v]) {
						nTeams[v] = nTeams[minV] + weight[v];
						path[v] = minV;
					}
				}
			}
	}
	printf("%d %d\n", nPaths[des], nTeams[des]);
	printPath(path, src, des);
	free(dist);
	free(nTeams);
	free(path);
	free(nPaths);
	free(collected);
}

int main() {
	int n, m, s, d;
	scanf("%d %d %d %d", &n,&m, &s, &d);
	int **graph = new int*[n];
	int *weight = new int[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
		fill(graph[i], graph[i] + n, INF);
	}
	for (int i = 0; i < n; i++)
		scanf("%d", weight + i);
	int c1, c2, len;
	for (int i = 0; i < m; i++) {		
		scanf("%d %d %d", &c1, &c2, &len);		
		graph[c1][c2] = graph[c2][c1] = len;
	}		
	dijkstra(graph, weight, n, s, d);
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	free(weight);	
	return 0;
}
```
