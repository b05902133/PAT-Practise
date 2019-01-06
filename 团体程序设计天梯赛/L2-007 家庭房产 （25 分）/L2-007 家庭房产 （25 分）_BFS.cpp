#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define ID_INF 10000 //id��4λ��������idΪ9999
typedef short ID; //��short�洢id
typedef struct Node { //ͼ����
	ID id; //�����ʾ���˵�id
	vector<ID> neighbors; //���ڵĶ����id
	double nHouse; //������
	double area; //���
	Node(ID id) : id(id), nHouse(0.0), area(0.0) {}
} *PNode;
//����洢ͼ����ָ��
PNode list[ID_INF] = { NULL };

struct Family {
	ID min_id; //��Сid
	int size; //����
	double average_nHouse; //ƽ��������
	double average_area; //ƽ�����
	Family(ID min_id, int size, double nHouse, double area) : min_id(min_id), size(size), average_nHouse(nHouse), average_area(area) {}
};

bool compare(Family a, Family b) {
	return a.average_area != b.average_area ? a.average_area > b.average_area : a.min_id < b.min_id;
}

void bfs(vector<Family>& families) {
	bool collected[ID_INF] = { false };
	queue<ID> q;
	for (ID id = 0; id < ID_INF; id++) { //�������п��ܵ�id
		if (list[(int)id] == NULL) continue; //��id������
		if (collected[(int)id]) continue; //��id����¼
		//BFS����ͨ����
		q.push(id);
		collected[(int)id] = true;
		ID min_id = id; //��ͨ�����е���Сid
		int size = 1; //��ͨ�����Ķ�������������¼id����sizeΪ1
		double nHouse = list[(int)id]->nHouse, area = list[(int)id]->area; //��ͨ�������ܷ������������
		while (!q.empty()) {
			ID v = q.front();
			q.pop();
			for (ID w : list[(int)v]->neighbors) //�����ڽӵ� 
				if (!collected[(int)w]) { //��δ����¼	
					if (w < min_id) min_id = w;
					size++;
					collected[(int)w] = true; //��¼w����v���ڽӵ����ظ������ٴγ���wʱ��w����¼�������ظ�����
					q.push(w);
					nHouse += list[(int)w]->nHouse;
					area += list[(int)w]->area;
				}
		}
		//����ͨ��������Ϣ�洢��Family�ṹ���У����ѽṹ�����families��
		families.push_back(Family(min_id, size, nHouse / size, area / size));
	}
	//����
	sort(families.begin(), families.end(), compare);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		ID id, father_id, mother_id, child_id;
		int k;
		double nHouse, area;
		scanf("%hd %hd %hd %d", &id, &father_id, &mother_id, &k);
		list[(int)id] = new Node(id);
		//��ĸ��������Ϊ���ڵĶ���
		if (father_id != -1) list[(int)id]->neighbors.push_back(father_id);
		if (mother_id != -1) list[(int)id]->neighbors.push_back(mother_id);
		for (int j = 0; j < k; j++) {
			scanf("%hd", &child_id);
			list[(int)id]->neighbors.push_back(child_id);
		}
		for (ID neighbor_id : list[(int)id]->neighbors) {
			//����ߡ�֮��������neighbor_id����Ϣ����neighbor_id���ڽӵ��л��ظ�����id��BFS����ʱ��ע��
			if (list[(int)neighbor_id] == NULL) list[(int)neighbor_id] = new Node(neighbor_id);
			list[(int)neighbor_id]->neighbors.push_back(id);
		}
		scanf("%lf %lf", &nHouse, &area);
		list[(int)id]->nHouse = nHouse;
		list[(int)id]->area = area;
	}
	vector<Family> families;
	//BFS����ͨ������ÿ����ͨ����Ϊһ��Family�ṹ���洢��families��
	bfs(families);
	//���
	printf("%d\n", families.size());
	for (auto it = families.begin(); it != families.end(); it++)
		printf("%04hd %d %.3f %.3f\n", it->min_id, it->size, it->average_nHouse, it->average_area);
	//�ͷ��ڴ�
	vector<Family>().swap(families);
	for (int i = 0; i < ID_INF; i++)
		if (list[i] != NULL) {
			delete list[i];
			list[i] = NULL;
		}
	return 0;
}
