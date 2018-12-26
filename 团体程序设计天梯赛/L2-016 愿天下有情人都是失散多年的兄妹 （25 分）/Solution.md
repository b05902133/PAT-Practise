# L2-016 Ը���������˶���ʧɢ��������� ��25 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805061769609216)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 200 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  


�Ǻǡ���Ҷ�֪��������ڲ���ͨ�飬������������Ĺ�ͬ���������������ڣ������ˡ���ĸ���游ĸ�����游ĸ�����游ĸ���򲻿�ͨ�顣������������һ���������ж�һ�£����Ǿ����Ƿ���Գɻ飿

## �����ʽ��

�����һ�и���һ��������N��2 �� N ��10^4�������N�У�ÿ�а����¸�ʽ����һ���˵���Ϣ��

> ����ID �Ա� ����ID ĸ��ID


����ID��5λ���֣�ÿ�˲�ͬ���Ա�M�������ԡ�F����Ů�ԡ����ĳ�˵ĸ��׻�ĸ���Ѿ����ɿ�������Ӧ��IDλ���ϱ��Ϊ-1��

����������һ��������K�����K�У�ÿ�и���һ�������˵�ID������Կո�ָ���

`ע�⣺��Ŀ��֤��������ͬ����ÿ��ֻ��һ���Ա𣬲���ѪԵ��ϵ����û�����׻�����ɻ�������`

## �����ʽ��

��ÿһ�������ˣ��ж����ǵĹ�ϵ�Ƿ����ͨ�飺���������ͬ�ԣ����Never Mind����������Բ��ҹ�ϵ������������Yes��������Թ�ϵδ����������No��

## ����������

> 24  
> 00001 M 01111 -1  
> 00002 F 02222 03333  
> 00003 M 02222 03333  
> 00004 F 04444 03333  
> 00005 M 04444 05555  
> 00006 F 04444 05555  
> 00007 F 06666 07777  
> 00008 M 06666 07777  
> 00009 M 00001 00002  
> 00010 M 00003 00006  
> 00011 F 00005 00007  
> 00012 F 00008 08888  
> 00013 F 00009 00011  
> 00014 M 00010 09999  
> 00015 M 00010 09999  
> 00016 M 10000 00012  
> 00017 F -1 00012  
> 00018 F 11000 00013  
> 00019 F 11100 00018  
> 00020 F 00015 11110  
> 00021 M 11100 00020  
> 00022 M 00016 -1  
> 00023 M 10012 00017  
> 00024 M 00022 10013  
> 9  
> 00021 00024  
> 00019 00024  
> 00011 00012  
> 00022 00018  
> 00001 00004  
> 00013 00016  
> 00017 00015  
> 00019 00021  
> 00010 00011  


## ���������

Never Mind  
Yes  
Never Mind  
No  
Yes  
No  
Yes  
No  
No  

## ˼·

�ö������ṹ�洢һ���˵���Ϣ������id���Ա𣬸���id��ĸ��id���ó���Ϊ100000������洢���ṹ���ָ�루id��Ӧ�����±꣩��
��ÿһ��id�������ǵ��Ա�ͬ���жϴ����ǿ�ʼ�������5��֮�ڵĽ��������ͬ����һ��id�������ʱ����5���ڵĽ��id��map
��¼������һ��id�������ʱ���ж�5���ڵĽ��id������map�г��ֹ���

ע������ʱ����һ��id�ĸ�ĸidδ���������ҲӦ����ĸ��Ϊ�µĽṹ��洢���ο� //http://www.cnblogs.com/taozi1115402474/p/8486484.html


## ����

```cpp
#include <iostream>
#include <queue>
#include <map>
using namespace std;

typedef struct Node {
	int id;
	char gender;
	int father_id, mother_id;
	Node(int id, char gender, int father_id, int mother_id) : id(id),
		gender(gender),
		father_id(father_id),
		mother_id(mother_id)
	{

	}
	~Node() {}
} *Tree;
Tree list[100000];
map<int, bool> id_exist;

bool bfs(int id, bool flag) {
	queue<Tree> q;
	q.push(list[id]);	
	Tree last = list[id], tail = list[id];
	int level = 1;
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		if (t == NULL) continue;
		if (t->father_id != -1) {
			q.push(list[t->father_id]);
			last = list[t->father_id];
			if (flag) id_exist[t->father_id] = true;
			else if (id_exist[t->father_id]) return false;
		}
		if (t->mother_id != -1) {
			q.push(list[t->mother_id]);
			last = list[t->mother_id];
			if (flag) id_exist[t->mother_id] = true;
			else if (id_exist[t->mother_id]) return false;
		}
		if (t == tail) {
			if (++level == 5) break;
			tail = last;
		}
	}
	queue<Tree>().swap(q);
	return true;
}

int main()
{
	int n;
	scanf("%d", &n);
	int id, father_id, mother_id;
	char gender;
	for (int i = 0; i < n; i++) {
		scanf("%d %c %d %d", &id, &gender, &father_id, &mother_id);
		list[id] = new Node(id, gender, father_id, mother_id);
		if (list[father_id] == NULL) list[father_id] = new Node(father_id, 'M', -1, -1); //http://www.cnblogs.com/taozi1115402474/p/8486484.html
		if (list[mother_id] == NULL) list[mother_id] = new Node(mother_id, 'F', -1, -1);
	}
	int k, id1, id2;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &id1, &id2);
		if (list[id1]->gender == list[id2]->gender)
			printf("Never Mind\n");
		else {
			id_exist.clear();
			bfs(id1, true);
			if (bfs(id2, false)) {
				printf("Yes\n");
			}
			else printf("No\n");
		}
	}
	for (int i = 0; i < 100000; i++)
		if (list[i] != NULL)
			delete list[i];
	id_exist.clear();
	map<int, bool>().swap(id_exist);
	return 0;
}
```
