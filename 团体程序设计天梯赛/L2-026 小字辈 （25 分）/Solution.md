# L2-026 С�ֱ� ��25 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805055679479808)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  


�������һ���Ӵ����ļ��ף�Ҫ���������Сһ����������

## �����ʽ��

�����ڵ�һ�и��������˿����� N�������� 100 000 ���������� ���� ����������ǰѼ����Ա�� 1 �� N ��š����ڶ��и��� N ����ţ����е� i ����Ŷ�Ӧ�� i λ��Ա�ĸ�/ĸ�������б�����ߵ������ڶ�Ӧ�ĸ�ĸ���Ϊ -1��һ���е����ּ��Կո�ָ���

## �����ʽ��

���������С�ı��֣������ڵı���Ϊ 1�������𼶵�������Ȼ���ڵڶ��а�����˳�����������С�ĳ�Ա�ı�š���ż���һ���ո�ָ�������β�����ж���ո�

## ����������

> 9  
> 2 6 5 5 -1 5 6 4 7  


## ���������
> 4  
> 1 9  

## ˼·

BFS�ֲ������������������һ��Ķ���

## ����

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct TNode{
	int id;
	vector<int> children;
	TNode(int id) : id(id) {}
} *Tree;

int main()
{
	int n;
	cin >> n;
	Tree *list = new Tree[n];
	for (int i = 0; i < n; i++)
		list[i] = new TNode(i);
	int parent_id, root_id;
	for (int i = 0; i < n; i++) {
		cin >> parent_id;
		if (parent_id == -1) {
			root_id = i;
			continue;
		}
		parent_id--;
		list[parent_id]->children.push_back(i);	
	}
	Tree root = list[root_id];
	queue<Tree> q;
	q.push(root);
	Tree last = root, tail = root;
	int level = 0;
	vector<int> lastLevel;		
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		lastLevel.push_back(t->id);
		for (int child_id : t->children) {				
			Tree tree = list[child_id];
			q.push(tree);
			last = tree;
		}
		if (t == tail) {
			level++;
			tail = last;
			if (!q.empty()) lastLevel.clear();
		}
	}
	cout << level << endl;
	for (auto it = lastLevel.begin(); it != lastLevel.end(); it++) {
		if (it != lastLevel.begin()) putchar(' ');
		cout << (*it + 1);
	}
	for (int i = 0; i < n; i++)
		if (list[i] != NULL)
			delete list[i];
	free(list);	
	return 0;
}

```