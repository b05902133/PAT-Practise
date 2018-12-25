# L2-012 ���ڶѵ��ж� ��25 �֣�

[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805064676261888)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  

��һϵ�и�������˳�����һ����ʼΪ�յ�С����H[]������ж�һϵ����������Ƿ�Ϊ�档��������м��֣�
* `is the root`��x�Ǹ���㣻
* `and y are siblings`��x��y���ֵܽ�㣻
* `is the parent of y`��x��y�ĸ���㣻
* `is a child of y`��x��y��һ���ӽ�㡣

## �����ʽ��

ÿ����Ե�1�а���2��������N���� 1000����M���� 20�����ֱ��ǲ���Ԫ�صĸ������Լ���Ҫ�жϵ�����������һ�и�������[-10000,10000]�ڵ�N��Ҫ������һ����ʼΪ�յ�С���ѵ�������֮��M�У�ÿ�и���һ�����⡣��Ŀ��֤�����еĽ���ֵ���Ǵ��ڵġ�

## �����ʽ��

�������ÿ�����⣬�����Ϊ�棬����һ�������T���������F��

## ����������

> 5 4  
> 46 23 26 24 10  
> 24 is the root  
> 26 and 23 are siblings  
> 46 is the parent of 23  
> 23 is a child of 10  


## ���������

> F  
> T  
> F  
> T 

## ˼· 

��Ԫ�ز�����С�ѣ���ÿһ�����룬������Ӧ�ĺ����ж�

## ����

[L2-012 ���ڶѵ��ж� ��25 �֣�.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-012%20%E5%85%B3%E4%BA%8E%E5%A0%86%E7%9A%84%E5%88%A4%E6%96%AD%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-012%20%E5%85%B3%E4%BA%8E%E5%A0%86%E7%9A%84%E5%88%A4%E6%96%AD%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

#define PARENT(i) ((i + 1)/2 - 1)
#define OUTPUT(boolean) cout << ((boolean) ? "T" : "F") << endl

class Heap {
public:
	Heap(int capacity) : capacity(capacity), size(0) {
		list = new int[capacity];
	}
	~Heap() { free(list); }
	void insert(int item);
	bool isRoot(int item);
	bool areSiblings(int x, int y);
	bool isParentOf(int x, int y);
	bool isChildOf(int x, int y);
private:
	int getIndexOf(int item);
	map<int, int> itemToIndex;
	int *list;
	int capacity;
	int size;
};

void Heap::insert(int item) {
	if (size == capacity) return;
	int i;
	for (i = size; i != 0 && list[PARENT(i)] > item; i = PARENT(i)) {
		list[i] = list[PARENT(i)];
		itemToIndex[list[i]] = i;
	}
	list[i] = item;
	itemToIndex[item] = i;
	size++;
}

bool Heap::isRoot(int item) {
	return getIndexOf(item) == 0;
}

bool Heap::areSiblings(int x, int y) {
	int x_idx = getIndexOf(x);
	int y_idx = getIndexOf(y);
	return PARENT(x_idx) == PARENT(y_idx);
}

bool Heap::isParentOf(int x, int y) {
	int x_idx = getIndexOf(x);
	int y_idx = getIndexOf(y);
	return x_idx == PARENT(y_idx);
}

bool Heap::isChildOf(int x, int y) {
	return isParentOf(y, x);
}

int Heap::getIndexOf(int item) {
	return itemToIndex[item];
}

int main() 
{
	int n, m;
	cin >> n >> m;
	Heap heap(n);
	int item;
	for (int i = 0; i < n; i++) {
		cin >> item;
		heap.insert(item);
	}
	int x, y;
	string cmd;
	for (int i = 0; i < m; i++) {
		cin >> x;
		cin >> cmd;
		if (cmd == "and") {
			cin >> y;
			cin >> cmd; //"are"
			cin >> cmd; //"siblings"
			OUTPUT(heap.areSiblings(x, y));
		}
		else { //cmd == "is"
			cin >> cmd;
			if (cmd == "a") {
				cin >> cmd; //"child"
				cin >> cmd; //"of"
				cin >> y;
				OUTPUT(heap.isChildOf(x, y));				
			}
			else { //cmd == "the"
				cin >> cmd;
				if (cmd == "root") {
					OUTPUT(heap.isRoot(x));	
				}
				else { //cmd == "parent"
					cin >> cmd; //"of"
					cin >> y;
					OUTPUT(heap.isParentOf(x, y));
				}
			}
		}
	}
	return 0;
}

```
