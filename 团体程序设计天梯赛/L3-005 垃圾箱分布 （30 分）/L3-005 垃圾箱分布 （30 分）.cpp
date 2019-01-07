#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define INF 1000000

typedef short Vertex; 
typedef struct Edge { 
	Vertex v;
	Vertex w;
	double dist;
	Edge(Vertex v, Vertex w, double dist) : v(v), w(w), dist(dist) {}
} *PEdge;

typedef struct GNode { //Node of graph
	Vertex v;
	vector<PEdge> edges; //�ߵ�ָ��
	GNode(Vertex v) : v(v) {}
} *PGNode;
typedef PGNode *Graph; //ͼ��һ���洢ָ������飬ָ��ָ��ͼ������Ϣ

Graph graph;
int n, m, k, ds;

typedef int index_t; //ͼ������±�
index_t stoidx(string name) { //����һ������Ķ�����graph�е��±�
	if (name[0] != 'G') //�������Ǿ����
		return stoi(name) - 1; //�����1��ʼ
	else //�������Ǻ�ѡ������
		return n + (int)name[1] - (int)'0' - 1;
}

void input_graph() {
	scanf("%d %d %d %d", &n, &m, &k, &ds);
	graph = new PGNode[n + m];
	for (int i = 0; i < n + m; i++)
		graph[i] = new GNode((Vertex)i); //��ʼ������
	for (int i = 0; i < k; i++) {
		string p1, p2;
		double dist;
		cin >> p1 >> p2 >> dist;
		index_t idx1 = stoidx(p1), idx2 = stoidx(p2);
		PEdge pEdge = new Edge((Vertex)idx1, (Vertex)idx2, dist);
		//�����
		graph[idx1]->edges.push_back(pEdge);
		graph[idx2]->edges.push_back(pEdge);
	}
}

index_t findMin(double *dist, bool *collected) { //����δ��¼��dist��С�Ķ����±�
	index_t min_idx = -1;
	double min_dist = INF;
	for (index_t i = 0; i < n + m; i++)
		if (!collected[i] && dist[i] < min_dist) {
			min_idx = i;
			min_dist = dist[i];
		}
	return min_idx;
}

void findBestPosition() {
	index_t best_idx = -1;
	double best_min_dist = 0;
	double best_total_dist = -1;
	double *dist = new double[n + m];
	bool *collected = new bool[n + m];
	for (index_t candidate_idx = n; candidate_idx < n + m; candidate_idx++) {
		//����ÿһ����ѡ�����䣬����ΪԴ����dijkstra�������������о�������̾���
		double min_dist = INF, max_dist = 0, total_dist = 0;
		fill(dist, dist + n + m, INF);
		fill(collected, collected + n + m, false);
		dist[candidate_idx] = 0;
		int nv = 0;
		while (1) {
			index_t idx = findMin(dist, collected);
			if (idx == -1) break;
			if (idx < n) { //��idx�Ǿ����
				if (dist[idx] < min_dist) min_dist = dist[idx];
				if (dist[idx] > max_dist) max_dist = dist[idx];
				if (max_dist > ds) break; //�����볬��ds
				total_dist += dist[idx];
				nv++;
			}
			collected[idx] = true;
			for (PEdge pEdge : graph[idx]->edges) {
				index_t neighbor = (index_t)pEdge->v == idx ? (index_t)pEdge->w : (index_t)pEdge->v;
				if (!collected[neighbor])
					if (dist[idx] + pEdge->dist < dist[neighbor]) dist[neighbor] = dist[idx] + pEdge->dist;
			}
		} //while
		if (max_dist > ds || nv < n) continue; //�����볬��ds���߾���㲻��ͨ���򲻿��Ǵ˺�ѡ��
		if (min_dist > best_min_dist) {
			best_min_dist = min_dist;
			best_total_dist = total_dist;
			best_idx = candidate_idx;
		}
		else if (min_dist == best_min_dist && total_dist < best_total_dist) {
			best_total_dist = total_dist;
			best_idx = candidate_idx;
		}
		else if (min_dist == best_min_dist && total_dist == best_total_dist && candidate_idx < best_idx) {
			best_idx = candidate_idx;
		}
	}
	free(dist);
	free(collected);	
	if (best_idx == -1) 
		printf("No Solution\n");
	else 
		printf("G%d\n%.1f %.1f", best_idx - n + 1, best_min_dist, best_total_dist/n);
}

void deleteMemory() { //�ͷ��ڴ�
	map<PEdge, bool> hasDeleted; //��¼�߽���Ƿ�delete��
	for (index_t i = 0; i < n + m; i++) {
		if (graph[i] != NULL) {			
			for (auto it = graph[i]->edges.begin(); it != graph[i]->edges.end(); it++)
				if (*it != NULL && !hasDeleted[*it]) {
					delete *it;	
					hasDeleted[*it] = true; //��¼�ý���ѱ�delete�������ظ�ɾ��
					*it = NULL;
				}
			graph[i]->edges.clear();
			vector<PEdge>().swap(graph[i]->edges);
			delete graph[i];
			graph[i] = NULL;
		}
	}
	free(graph);
	hasDeleted.clear(); //map<PEdge, bool>��PEdgeָ����ڴ��ѱ��ͷ�
	map<PEdge, bool>().swap(hasDeleted);
}

int main() {
	input_graph();
	findBestPosition();
	deleteMemory();
	return 0;
}
