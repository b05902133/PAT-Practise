# L2-007 ��ͥ���� ��25 �֣�

[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805068539215872)

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  


����ÿ���˵ļ�ͥ��Ա�����Լ����µķ���������ͳ�Ƴ�ÿ����ͥ���˿������˾��������������������

## �����ʽ��

�����һ�и���һ��������N����1000�������N�У�ÿ�а����и�ʽ����һ���˵ķ�����

> ��� �� ĸ k ����1 ... ����k �������� �����


���б����ÿ���˶��е�һ��4λ���ı�ţ�����ĸ�ֱ��Ǹñ�Ŷ�Ӧ������˵ĸ�ĸ�ı�ţ�����Ѿ�����������ʾ-1����k��0��k��5���Ǹ��˵���Ů�ĸ���������i������Ů�ı�š�

## �����ʽ��

�����ڵ�һ�������ͥ������������������ϵ���˶�����ͬһ����ͥ����������и�ʽ���ÿ����ͥ����Ϣ��
��ͥ��Ա����С��� ��ͥ�˿��� �˾��������� �˾��������


�����˾�ֵҪ����С�����3λ����ͥ��Ϣ���Ȱ��˾����������������в��У��򰴳�Ա��ŵ����������

##������������

> 10  
> 6666 5551 5552 1 7777 1 100  
> 1234 5678 9012 1 0002 2 300  
> 8888 -1 -1 0 1 1000  
> 2468 0001 0004 1 2222 1 500  
> 7777 6666 -1 0 2 300  
> 3721 -1 -1 1 2333 2 150  
> 9012 -1 -1 3 1236 1235 1234 1 100  
> 1235 5678 9012 0 1 50  
> 2222 1236 2468 2 6661 6662 1 300  
> 2333 -1 3721 3 6661 6662 6663 1 100  

## ���������

> 3  
> 8888 1 1.000 1000.000  
> 0001 15 0.600 100.000  
> 5551 4 0.750 100.000  


## ˼·1 ��ͼ����ͨ����

��ͼ�����ʾÿ���ˣ��丸ĸ�����������ڵĶ��㡣BFS����ͨ������


## ����1

[L2-007 ��ͥ���� ��25 �֣�_BFS.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89_BFS.cpp)

```cpp

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
PNode list[ID_INF] = {NULL};

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
	bool collected[ID_INF] = {false};
	queue<ID> q;
	for (ID id = 0; id < ID_INF; id++) { //�������п��ܵ�id
		if (list[(int)id] == NULL) continue; //��id������
		if (collected[(int)id]) continue; //��id����¼
		//BFS����ͨ����
		q.push(id);
		collected[(int)id] = true;
		ID min_id = id; //��ͨ�����е���Сid
		int size= 1; //��ͨ�����Ķ�������������¼id����sizeΪ1
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
		families.push_back(Family(min_id, size, nHouse/size, area/size));
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

```

## ˼·2 ���鼯

���鼯��װ��һ�����У���_set����洢SetData�ṹ�塣SetData�ṹ�����£�

```cpp
struct SetData { 
	ID parent;
	PFamily pFamily;
};
```

_set[id].parent��id�ĸ�����������е��±꣬Ϊ����ʾidΪ����㣬�����ľ���ֵ��ʾ���ϵĴ�С��
_set[id].pFamilyΪFamily�ṹ���ָ�룬��id���Ǹ������ΪNULL����id�Ǹ���㣬��ָ��һ���洢
�ü�����Ϣ�Ľṹ�塣
�ϲ�����ʱ����С�ļ��Ϻϲ�����ļ����ϣ�_set��������Ӧ��pFamilyָ�����Ϣ��ϲ������ϲ���
���ϣ�ɾ����ԭ��������pFamilyָ��Ľṹ��

����ʱ��������id���丸ĸ�����ӵļ��Ϻϲ������������ڵļ��ϣ���������ķ����������

_set������pFamily��NULL��Ԫ���������������������������������_set����pFamily��NUll������
ǰ��pFamily����NULL����pFamilyָ�����Ϣ������������pFamily��NULL��ָ�����Ϣ��

## ����2

[L2-007 ��ͥ���� ��25 �֣�_���鼯.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-007%20%E5%AE%B6%E5%BA%AD%E6%88%BF%E4%BA%A7%20%EF%BC%8825%20%E5%88%86%EF%BC%89_%E5%B9%B6%E6%9F%A5%E9%9B%86.cpp)

```cpp


#include <iostream>
#include <algorithm>
using namespace std;

#define MIN(a, b) (a < b ? a : b)
#define ID_INF 10000
typedef short ID;
typedef struct Family {
	ID min_id;
	short size;
	double nHouse;
	double area;
	Family() {}
	Family(ID min_id, double nHouse, double area) : min_id(min_id), nHouse(nHouse), area(area) {}
} *PFamily;

struct SetData {
	ID parent;
	PFamily pFamily;
};
bool compare(SetData a, SetData b) {
	if (a.pFamily != NULL && b.pFamily != NULL) {
		return (a.pFamily->area != b.pFamily->area ? (a.pFamily->area > b.pFamily->area) : (a.pFamily->min_id < b.pFamily->min_id));
	}
	else if (a.pFamily != NULL || b.pFamily != NULL) { //��NULL������ǰ
		return a.pFamily != NULL;		
	}	
	else return a.parent < b.parent; //��ΪNULLʱ���м��ɣ�a.parent < b.parent���Ը�Ϊ�����жϾ�
}

class USet {
public:
	USet() {
		_set = new SetData[ID_INF];
		for (int i = 0; i < ID_INF; i++) {
			_set[i].parent = -1;
			_set[i].pFamily = NULL;
		}
	}
	~USet() { 
		for (int i = 0; i < ID_INF; i++) 
			if (_set[i].pFamily != NULL) {
				delete _set[i].pFamily;
				_set[i].pFamily = NULL;
			}
		free(_set);
	}

	void unionSet(ID a, ID b); //�ϲ�a��b
	void add(ID a, double nHouse, double area); //��a�����ļ�������nHouse, area
	int size(); //��������
	void printSetData(); //���
private:
	ID findRoot(ID a);
	SetData *_set;
};

ID USet::findRoot(ID a) {
	if (_set[a].parent < 0) return a;
	return _set[a].parent = findRoot(_set[a].parent);	
}

void USet::unionSet(ID a, ID b) {
	if (a == -1 || b == -1) return;
	ID root_a = findRoot(a);
	ID root_b = findRoot(b);
	if (root_a == root_b) return;
	ID root_x, root_y;
	//С���ϲ����󼯺���
	if (_set[root_a].parent < _set[root_b].parent) {
		root_x = root_a;
		root_y = root_b;
	}
	else {
		root_x = root_b;
		root_y = root_a;
	}
	_set[root_x].parent += _set[root_y].parent;
	_set[root_y].parent = root_x;
	if (_set[root_x].pFamily == NULL)
		_set[root_x].pFamily = new Family(root_x, 0.0, 0.0);
	if (_set[root_y].pFamily == NULL)
		_set[root_y].pFamily = new Family(root_y, 0.0, 0.0);
	if (_set[root_x].pFamily->min_id > _set[root_y].pFamily->min_id)
		_set[root_x].pFamily->min_id = _set[root_y].pFamily->min_id;
	_set[root_x].pFamily->nHouse += _set[root_y].pFamily->nHouse;
	_set[root_x].pFamily->area += _set[root_y].pFamily->area;
	delete _set[root_y].pFamily;
	_set[root_y].pFamily = NULL;
}

void USet::add(ID a, double nHouse, double area) {
	ID root = findRoot(a);
	if (_set[root].pFamily == NULL)
		_set[root].pFamily = new Family(root, 0.0, 0.0);
	_set[root].pFamily->nHouse += nHouse;
	_set[root].pFamily->area += area;
}

int USet::size() {
	int _size = 0;
	for (int i = 0; i < ID_INF; i++)
		if (_set[i].pFamily != NULL)
			_size++;
	return _size;
}

void USet::printSetData() {
	for (ID id = 0; id < ID_INF; id++) {
		if (_set[id].pFamily == NULL) continue;
		int size = _set[id].parent * (-1);
		_set[id].pFamily->nHouse /= size; //ƽ��ֵ
		_set[id].pFamily->area /= size;
	}
	sort(_set, _set + ID_INF, compare);
	for (ID id = 0; id < ID_INF; id++) {
		if (_set[(int)id].pFamily == NULL)continue;
		int size = _set[id].parent * (-1);
		printf("%04hd %d %.3f %.3f\n", _set[id].pFamily->min_id, size, _set[id].pFamily->nHouse, _set[id].pFamily->area);
	}	
}


int main()
{
	USet uset;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		ID id, father_id, mother_id, child_id;
		scanf("%hd %hd %hd", &id, &father_id, &mother_id);	
		uset.unionSet(id, father_id);
		uset.unionSet(id, mother_id);
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%hd", &child_id);
			uset.unionSet(id, child_id);
		}
		double nHouse, area;
		scanf("%lf %lf", &nHouse, &area);
		uset.add(id, nHouse, area);
	}
	printf("%d\n", uset.size());
	uset.printSetData();
	return 0;
}
```

