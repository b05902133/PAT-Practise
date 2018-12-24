# L2-013 ��ɫ���� ��25 �֣�

[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805063963230208)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  

ս���б��ָ������м����ͨ�Էǳ���Ҫ������Ҫ�����дһ���������򣬵�ʧȥһ�����е��¹��ұ�����Ϊ����޷���ͨ������ʱ���ͷ�����ɫ������ע�⣺���ù������Ͳ���ȫ��ͨ���Ƿ��ѵ�k�����򣬶�ʧȥһ�����в����ı���������֮�����ͨ�ԣ���Ҫ����������

## �����ʽ��

�����ڵ�һ�и�����������N��0 < N �� 500����M���� 5000�����ֱ�Ϊ���и���������Ĭ�ϳ��д�0��N-1��ţ������������е�ͨ·���������M�У�ÿ�и���һ��ͨ·�����ӵ��������еı�ţ������1���ո�ָ����ڳ�����Ϣ֮���������ռ����Ϣ����һ��������K������K������ռ�ĳ��еı�š�

*ע�⣺���뱣֤�����ı���ռ�ĳ��б�Ŷ��ǺϷ��������ظ�����������֤������ͨ·û���ظ���*

## �����ʽ��

��ÿ������ռ�ĳ��У��������ı��������ҵ���ͨ�ԣ������Red Alert: City k is lost!������k�Ǹó��еı�ţ�����ֻ���City k is lost.���ɡ�����ù�ʧȥ�����һ�����У�������һ�����Game Over.��

## ����������

> 5 4  
> 0 1  
> 1 3  
> 3 0  
> 0 4  
> 5  
> 1 2 0 4 3  


## ���������

> City 1 is lost.  
> City 2 is lost.  
> Red Alert: City 0 is lost!  
> City 4 is lost.  
> City 3 is lost.  
> Game Over.  

## ˼·

����ͼ����ͨ��������ÿ����ͨ������ţ��������¼ÿ��������������ͨ��������ÿ����ͨ�����Ķ�������������ÿ������ռ��
���У�ɾ��������е����бߣ�Ȼ���ٱ����ó�����������ͨ����������������Ϊԭ��ͨ�����Ķ�������-1�������ͨ����������
ͨ�ģ��������ͨ������ɾ��һ����������ֳ��˶����ͨ��������ʱ��Ҫ����������������£���Ҫ�����²�������ͨ��������
¼���ǵĶ���������

## ����

[L2-013 ��ɫ���� ��25 �֣�.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-013%20%E7%BA%A2%E8%89%B2%E8%AD%A6%E6%8A%A5%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-013%20%E7%BA%A2%E8%89%B2%E8%AD%A6%E6%8A%A5%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
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
```
