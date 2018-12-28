# L2-020 ������ ��25 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805059118809088)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  

һ���书�ܷ񴫳о�Զ������������Ҫ��Ե�ֵġ�һ����˵��ʦ�����ڸ�ͽ�ܵ��书��Ҫ����ۿۣ�����Խ���󴫣������ǵĹ����Խ������ ֱ��ĳһ֧��ĳһ��ͻȻ����һ������ر�ߵĵ��ӣ������ǳԵ����鵤���ڵ����ر�����ţ����Ὣ���������һ���ӷŴ�N�� ���� ���ǳ����ֵ���Ϊ���õ��ߡ���

��������������ĳһλ��ʦү���µ�ͽ��ͽ����ף���������е�ÿ����ֻ��1λʦ����������ʦүû��ʦ������ÿλʦ�����Դ��ܶ�ͽ�ܣ����Ҽ��豲���ϸ����򣬼���ʦү�����书��ÿ����i������ֻ���ڵ�i-1�������а�1��ʦ�������Ǽ�����֪��ʦү�Ĺ���ֵΪZ��ÿ���´���һ�����ͻ����r%������ĳһ�����ӵõ����ָ���ʦ����ϵ��ϵ��Ҫ����������еõ��ߵĹ�����ֵ��

## �����ʽ��

�����ڵ�һ�и���3�����������ֱ��ǣ�N����10^5����������ʦ�ŵ�������������ÿ���˴�0��N-1��ţ���ʦү�ı��Ϊ0����Z������ʦү�Ĺ���ֵ����һ��������������������������r ����ÿ��һ������������ۿ۰ٷֱ�ֵ��������100������������������N�У���i�У�i=0,?,N?1���������Ϊi����������ͽ�ܣ���ʽΪ��

`Ki ID[1] ID[2] ID[Ki]`

����`Ki`��ͽ�ܵĸ�������������Ǹ�λͽ�ܵı�ţ����ּ��Կո�����`Ki`Ϊ���ʾ����һλ�õ��ߣ���ʱ�������һ�����ֱ�ʾ���书���Ŵ�ı�����

## �����ʽ��

��һ����������еõ��ߵĹ�����ֵ��ֻ�������������֡���Ŀ��֤�������ȷ�������������10^10��

## ����������

> 10 18.0 1.00  
> 3 2 3 5  
> 1 9  
> 1 4  
> 1 7  
> 0 7  
> 2 6 1  
> 1 8  
> 0 9  
> 0 4  
> 0 3  


## ���������

> 404 

## ˼·

�ýṹ��洢ÿ���˵�id�������Ŵ����������ǵõ�����Ϊ0�����Դ���������������ӣ���vector�����id���õ���û�е��ӣ���vectorΪ�գ���
����ʱ����ȷ��ÿ���˵�id�������Ŵ��������ӡ�����ʦү�ǵõ��ߣ������z*��ʦү�Ĺ����Ŵ������ɣ�����bfs������������ÿ���˵Ĺ�����
���ڵõ��ߣ��书������Թ����Ŵ��������������С�

## ����

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Node {
	int id;
	double multiple;
	double power;
	vector<int> disciple;
	Node(int id) : id(id), multiple(0.0), power(0.0) {}
	~Node() {};
} *Tree;

int bfs(Tree *list, int n, double z, double r) {	
	if (list[0]->multiple > 0)
		return (int)(z * list[0]->multiple);
	double result = 0;
	list[0]->power = z;
	queue<Tree> q;
	q.push(list[0]);	
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		for (int id : t->disciple) {
			list[id]->power = t->power * (100 - r) / 100;
			if (list[id]->multiple > 0) {
				list[id]->power *= list[id]->multiple;
				result += list[id]->power;
			}
			else q.push(list[id]);
		}
	}
	queue<Tree>().swap(q);
	return (int)result;
}

int main()
{
	int n;
	double z, r;
	cin >> n >> z >> r;
	Tree *list = new Tree[n];
	int k;
	for (int i = 0; i < n; i++) {
		cin >> k;
		list[i] = new Node(i);
		if (k > 0) {
			int id;
			for (int j = 0; j < k; j++) {
				cin >> id;
				list[i]->disciple.push_back(id);
			}
		}
		else {//k == 0
			double p;
			cin >> p;
			list[i]->multiple = p;
		}
	}
	printf("%d", bfs(list, n, z, r));
	for (int i = 0; i < n; i++)
		if (list[i] != NULL)
			delete list[i];
	free(list);
	return 0;
}
```

