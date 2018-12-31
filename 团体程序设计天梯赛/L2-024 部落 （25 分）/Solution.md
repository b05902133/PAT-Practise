# L2-024 ���� ��25 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805056736444416)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 150 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  

��һ�������ÿ���˶����Լ���СȦ�ӣ�������ͬʱ���ںܶ಻ͬ������Ȧ��������Ϊ���ѵ����Ѷ�����һ�����������Ҫ����ͳ��һ�£���һ�����������У������ж��ٸ������ཻ�Ĳ��䣿���Ҽ�������������Ƿ�����ͬһ�����䡣

## �����ʽ��

�����ڵ�һ�и���һ��������N����10^4��������֪СȦ�ӵĸ��������N�У�ÿ�а����и�ʽ����һ��СȦ������ˣ�

`K P[1] P[2] ... P[K]`

����K��СȦ�����������P[i]��i=1, ... ,K����СȦ����ÿ���˵ı�š����������˵ı�Ŵ�1��ʼ������ţ�����Ų��ᳬ��10^4��

֮��һ�и���һ���Ǹ�����Q����10^4�����ǲ�ѯ���������Q�У�ÿ�и���һ�Ա���ѯ���˵ı�š�

## �����ʽ��

������һ�������������������������Լ������ཻ�Ĳ���ĸ���������ÿһ�β�ѯ�������������ͬһ�����䣬����һ�������Y���������N��

## ����������

> 4  
> 3 10 1 2  
> 2 3 4  
> 4 1 5 7 8  
> 3 9 6 4  
> 2  
> 10 5  
> 3 7  


## ���������

> 10 2  
> Y  
> N  

## ˼·

���鼯�洢Ȧ�ӡ�����ʱ��¼ÿ����������Ȧ�ӣ�������֮ǰ�������κ�һ��Ȧ�ӣ���������1������ǰȦ�������֮ǰ������Ȧ�Ӻϲ���
����ÿһ�β�ѯ���ж������Ƿ�����ͬһ��Ȧ�ӣ���Ȧ�Ӳ�ͬ���ж�����Ȧ���Ƿ��ڲ��鼯������ͬһ�����ϡ�

## ����

```cpp

#include <iostream>
using namespace std;

typedef int Set;
class USet {
public:
	USet(int n) : n(n) {
		s = new Set[n];
		fill(s, s + n, -1);
	}
	~USet() { free(s); }
	bool isSameSet(Set a, Set b);
	void unionSets(Set a, Set b);
	int numSets();
private:
	Set findRoot(Set a);
	int n;
	Set *s;
};

Set USet::findRoot(Set a) {
	if (s[a] < 0) return a;
	return s[a] = findRoot(s[a]);
}

bool USet::isSameSet(Set a, Set b) {
	return findRoot(a) == findRoot(b);
}

void USet::unionSets(Set a, Set b) {
	Set a_root = findRoot(a);
	Set b_root = findRoot(b);
	if (a_root == b_root) return;
	if (s[a_root] < s[b_root]) {
		s[a_root] += s[b_root];
		s[b_root] = a_root;
	}
	else {
		s[b_root] += s[a_root];
		s[a_root] = b_root;
	}
}

int USet::numSets() {
	int size = 0;
	for (int i = 0; i < n; i++)
		if (s[i] < 0) size++;
	return size;
}

int main()
{
	int n;
	cin >> n;
	USet uset(n);	
	int *circle = new int[10001];
	fill(circle, circle + 10001, -1);
	int num = 0;
	int k, id;
	for (int i = 0; i < n; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> id;
			if (circle[id] == -1) {
				circle[id] = i;
				num++;
			}
			else
				uset.unionSets(i, circle[id]);
		}	
	}
	cout << num << " " << uset.numSets() << endl;
	int q, id1, id2;
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> id1 >> id2;
		cout << ((circle[id1] == circle[id2] || uset.isSameSet(circle[id1], circle[id2])) ? "Y" : "N") << endl;
	}
	free(circle);
	return 0;
}

```
