# L3-003 �罻��Ⱥ ��30 �֣�

[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805053141925888)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 1200 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  

�������罻����ƽ̨ע��ʱ��һ�����Ǳ�Ҫ����д��ĸ�����Ȥ���ã��Ա��ҵ�������ͬ��Ȥ���õ�Ǳ�ڵ����ѡ�һ�����罻��Ⱥ����ָ������Ȥ������ͬ���˵ļ��ϡ�����Ҫ�ҳ����е��罻��Ⱥ��

## �����ʽ��

�����ڵ�һ�и���һ�������� N����1000����Ϊ�罻����ƽ̨ע��������û���������������Щ�˴� 1 �� N ��š���� N �У�ÿ�а����¸�ʽ����һ���˵���Ȥ�����б�

> Ki: hi[1] hi[2] ... hi[Ki]

����Ki(>0)����Ȥ���õĸ�����hi[j]�ǵ�j����Ȥ���õı�ţ�Ϊ���� [1, 1000] �ڵ�������

## �����ʽ��

������һ���������ͬ���罻��Ⱥ�ĸ��������ڶ��а����������ÿ����Ⱥ�е����������ּ���һ���ո�ָ�����ĩ�����ж���ո�

## ����������

> 8  
> 3: 2 7 10  
> 1: 4  
> 2: 5 3  
> 1: 4  
> 1: 3  
> 1: 4  
> 4: 6 8 1 5  
> 1: 4  


## ���������

> 3  
> 4 3 1 

## ˼·

���鼯����������ÿ��hobby�������ˣ���ʼΪ-1������һ���˵İ���ʱ�����ð����Ѿ��������ˣ��ͽ������������ļ��Ϻϲ���

## ����

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef short ID;
bool compare(ID a, ID b) {
	return a > b;
}
class USet {
public:
	USet(int n) : n(n) {
		_set = new ID[n];
		fill(_set, _set + n, -1);
	}
	~USet() { free(_set); }
	
	void unionSets(ID a, ID b);
	void getSets(vector<ID>& sets);

private:
	ID findRoot(ID a);

	int n;
	ID *_set;
};

ID USet::findRoot(ID a) {
	if (_set[(int)a] < 0) return a;
	return _set[(int)a] = findRoot(_set[(int)a]);
}

void USet::unionSets(ID a, ID b) {
	ID root_a = findRoot(a);
	ID root_b = findRoot(b);
	if (root_a == root_b) return;
	if (_set[root_a] < _set[root_b]) {
		_set[root_a] += _set[root_b];
		_set[root_b] = root_a;
	}
	else {
		_set[root_b] += _set[root_a];
		_set[root_a] = root_b;
	}
}

void USet::getSets(vector<ID>& sets) {
	for (int i = 0; i < n; i++)
		if (_set[i] < 0) {
			sets.push_back(_set[i] * (-1));		
		}	
	sort(sets.begin(), sets.end(), compare);
}

int main() {
	int n;
	scanf("%d", &n);
	USet uset(n);
	ID hobbies[1000];
	for (int i = 0; i < 1000; i++) hobbies[i] = -1;
	int k, hobby;
	for (int i = 0; i < n; i++) {
		scanf("%d:", &k);	
		for (int j = 0; j < k; j++) {
			scanf("%d", &hobby);
			hobby--;
			if (hobbies[hobby] == -1)
				hobbies[hobby] = (ID)i;
			else {
				uset.unionSets(hobbies[hobby], (ID)i);
			}
		}
	}
	vector<ID> sets;
	uset.getSets(sets);
	printf("%d\n", sets.size());
	for (auto it = sets.begin(); it != sets.end(); it++) {
		if (it != sets.begin()) putchar(' ');
		printf("%hd", *it);
	}
	return 0;
}

```

