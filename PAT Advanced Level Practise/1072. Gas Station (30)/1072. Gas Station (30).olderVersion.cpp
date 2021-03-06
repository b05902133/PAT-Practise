// 1072. Gas Station (30).cpp: 定义控制台应用程序的入口点。
//
/*
1072. Gas Station (30)

时间限制 200 ms

内存限制 65536 kB

代码长度限制 16000 B

判题程序 Standard

作者 CHEN, Yue
--------------------------------------------------------------------------------------------------


A gas station has to be built at such a location that the minimum distance between the station and
any of the residential housing is as far away as possible. However it must guarantee that all the
houses are in its service range.

Now given the map of the city and several candidate locations for the gas station, you are supposed
to give the best recommendation. If there are more than one solution, output the one with the smallest
average distance to all the houses. If such a solution is still not unique, output the one with the
smallest index number.
--------------------------------------------------------------------------------------------------


Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive integers: N (<= 103),
the total number of houses; M (<= 10), the total number of the candidate locations for the gas stations; K (<= 104),
the number of roads connecting the houses and the gas stations; and DS, the maximum service range of the gas station.
It is hence assumed that all the houses are numbered from 1 to N, and all the candidate locations are numbered from
G1 to GM.

Then K lines follow, each describes a road in the format
P1 P2 Dist
where P1 and P2 are the two ends of a road which can be either house numbers or gas station numbers, and Dist is the
integer length of the road.
--------------------------------------------------------------------------------------------------


Output Specification:

For each test case, print in the first line the index number of the best location. In the next line, print the minimum
and the average distances between the solution and all the houses. The numbers in a line must be separated by a space
and be accurate up to 1 decimal place. If the solution does not exist, simply output “No Solution”.
--------------------------------------------------------------------------------------------------


Sample Input 1:

4 3 11 5
1 2 2
1 4 2
1 G1 4
1 G2 3
2 3 2
2 G2 1
3 4 2
3 G3 2
4 G1 3
G2 G1 1
G3 G2 2

Sample Output 1:

G1
2.0 3.3
----------------------------

Sample Input 2:

2 1 2 10
1 G1 9
2 G1 20

Sample Output 2:

No Solution
--------------------------------------------------------------------------------------------------


题意：

N个居住地，M个候选修建加油站的地点，K条路。输入N、M、K以及DS（加油站的最远服务距离），输入每条路的起点、终点
与长度，起点和终点可以是一个居住地或候选地点。求在哪个候选地点修建加油站，可以使与加油站距离最近的居住地的距
离最远，且每个居住地都在加油站的服务距离内。若有多个加油站符合条件，则输出与每个居住地距离的平均值最小的，若
仍不唯一，输出序号最小的。若不存在符合条件的加油站，输出"No Solution"

思路：

居住地与候选地一起作为图的顶点，设与加油站距离最近的居住地的距离为max_min，初始化为0。对于每个候选地，将其作
为源调用dijkstra算法，得到与除源自己外每个顶点的最短距离，对于居住地，若有距离大于DS，则此候选地被排除，居住
地与源的最短距离中的最小值若大于max_min则更新，若不大于max_min但源与各居住地的距离之和减小也更新，若其他不变，
序号减小也更新


*/
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <string>
#define INF 10000

int get_id(string city, int n)
{	/* 返回城市在图中的编号 */
	if (isalpha(city[0])) {
		city.erase(city.begin());
		return n - 1 + atoi(city.c_str());
	}
	else return atoi(city.c_str()) - 1;
}

int minDist(int *dist, int *collected, int n)
{	/* 返回未受录的顶点中dist值最小的 */
	int min = INF, minV = -1;
	for (int i = 0; i < n; i++) 
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	return minV;
}

int * dijkstra(int **graph, int s, int n)
{	/* 最短路径 */
	int *collected = new int[n]; /* 是否被收录过 */
	int *dist = new int[n]; /* 当前最短距离 */
	int *path = new int[n]; /* 当前最短路径 */
	for (int i = 0; i < n; i++) {
		dist[i] = graph[s][i];
		path[i] = graph[s][i] < INF ? s : -1;
		collected[i] = 0;
	}
	collected[s] = 1;
	dist[s] = 0;
	path[s] = s;
	while (1) {
		int min = minDist(dist, collected, n);
		if (min == -1) break;
		collected[min] = 1;
		for (int v = 0; v < n; v++) /* 遍历每个顶点 */
			if (!collected[v] && graph[min][v] < INF) /* 未收录&&与min相邻 */ 
				if (dist[min] + graph[min][v] < dist[v]) { /* 若通过min使路径更短 */
					dist[v] = dist[min] + graph[min][v]; /* 更新 */
					path[v] = min;
				}
	}
	return dist;
}

int main()
{
	int n, m, k, ds;
	cin >> n >> m >> k >> ds;
	int nVertexes = n + m; //图的顶点数
	int **graph = new int *[nVertexes];
	for (int i = 0; i < nVertexes; i++) {
		graph[i] = new int[nVertexes];
		for (int j = 0; j < nVertexes; j++)
			graph[i][j] = INF;
	}
	for (int i = 0; i < k; i++) {
		string c1, c2;
		int dist;
		cin >> c1 >> c2 >> dist;
		int id1 = get_id(c1, n);
		int id2 = get_id(c2, n);
		graph[id1][id2] = graph[id2][id1] = dist;
	}
	double max_min = 0, finalTotal; //max_min是最远的最短距离
	int station;
	for (int i = 0; i < m; i++) { /* G1 ~ Gm (n ~ n + m - 1) */
		int *dist = dijkstra(graph, n + i, nVertexes);
		double min = INF, total = 0;
		int flag = 0;
		for (int j = 0; j < n; j++) { //0 ~ n-1
			if (dist[j] > ds) { flag = 1; break; }
			if (dist[j] < min) min = dist[j];
			total += dist[j];
		}
		if (flag) continue;
		if (min > max_min) { //min更大
			max_min = min;
			station = i;
			finalTotal = total;
		}
		else if (min == max_min) { //min相同
			if (total < finalTotal) { //total更小，故平均值更小
				station = i;
				finalTotal = total;
			}
			else if (total == finalTotal && i < station) station = i; //序号更小
		}
	}
	if (max_min == 0) cout << "No Solution" << endl;
	else {
		printf("G%d\n%.1f %.1f\n", station + 1, max_min, finalTotal/n);
	}
    return 0;
}

