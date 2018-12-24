#include <iostream>
#include <vector>
using namespace std;

int n; //������������ͼ�Ķ�������
bool **graph; //�Գ���Ϊ�����ͼ��graph[v][w]Ϊtrue��v,w֮����ڱ�
bool *collected; //collected[v]Ϊtrue����v������
short *componentId; //componentId[v]��ʾ����v��������ͨ������id
vector<short> idNum; //idNum[i]��ʾidΪi����ͨ�����Ķ�������

//��src��ʼdfs���ѱ�����id����ͨ���������ر�������ͨ�����ڵĶ�������
short dfs(int src, short id) {
	collected[src] = true;
	componentId[src] = id;
	short size = 1;
	for (int v = 0; v < n; v++)
		if (!collected[v] && graph[src][v]) {
			size += dfs(v, id);
		}
	return size;
}

int main()
{
	scanf("%d", &n);
	//��ʼ��
	graph = new bool *[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new bool[n];
		fill(graph[i], graph[i] + n, false);
	}
	collected = new bool[n];
	fill(collected, collected + n, false);
	componentId = new short[n];
	//������������
	int m, c1, c2;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &c1, &c2);
		graph[c1][c2] = graph[c2][c1] = true;
	}
	//����ͨ����
	short id = 0;
	for (int v = 0; v < n; v++)
		if (!collected[v]) idNum.push_back(dfs(v, id++)); //��¼ÿ����ͨ�����Ķ�������
	//
	int k;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int v;
		scanf("%d", &v); //����v����ռ
		int vid = componentId[v]; //����ռ������������ͨ����
		componentId[v] = -1; //ɾ���ó���
		for (int w = 0; w < n; w++)
			graph[v][w] = graph[w][v] = false; //ɾ����
		bool isRedAlert = false; //�Ƿ���Ҫ����
		if (idNum[vid] == 1) //���ó��е���Ϊһ����ͨ���������辯��
			idNum[vid] = 0;
		else { //����ͨ������ֹ1������
			//Ѱ��һ����ͬ��ͨ�����ڵĳ���
			//���Ѹ���ͨ�����Ķ����collected��Ϊfalse
			int sameIdCity = -1;
			for (int w = 0; w < n; w++)
				if (componentId[w] == vid) {
					collected[w] = false;
					if (sameIdCity == -1) sameIdCity = w;
				}
			//����ͬ��ͨ�����ڵ�һ�����п�ʼ����,���õ��Ķ�����������ԭ������ͨ�����Ķ�������-1��
			//�����ͨ������ɾ��v��û�иı䣻�������ͨ������ɾ��v�����ֳ��˶����ͨ����
			short size = dfs(sameIdCity, vid);
			if (size == idNum[vid] - 1) 
				idNum[vid]--;
			else { //size < idNum[vid] - 1				
				if (i != k - 1) { 
					//����ԭ��ͨ�����ָ��������ͨ����
					idNum[vid] = size;
					while (1) {
						sameIdCity = -1;
						for (int w = 0; w < n; w++) //Ѱ����ԭ��ͨ�����У���û�б�֮ǰ�������Ķ���
							if (!collected[w] && componentId[w] == vid) {
								sameIdCity = w;
								break;
							}
						if (sameIdCity == -1) break; //���ж���������������µ���ͨ�����Ѽ�¼��break
						idNum.push_back(dfs(sameIdCity, id++)); //��¼�µ���ͨ�����Ķ�������
					}
				}
				printf("Red Alert: "); //��Ҫ����
				isRedAlert = true;
			}
		}
		printf("City %d is lost", v);
		printf(isRedAlert ? "!" : ".");
		printf("\n");
	}
	if (k == n) printf("Game Over."); //��k==n�������г��о�����ռ
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	free(collected);
	free(componentId);
	idNum.clear();
	vector<short>().swap(idNum);
	return 0;
}