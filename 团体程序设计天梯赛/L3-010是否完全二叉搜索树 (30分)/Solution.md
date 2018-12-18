# L3-010 �Ƿ���ȫ���������� ��30 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805049870368768)

> ����: ��Խ

> ��λ: �㽭��ѧ

> ʱ������: 400 ms

> �ڴ�����: 64 MB

> ���볤������: 16 KB


��һϵ�и�������˳�����һ����ʼΪ�յĶ���������������Ϊ��������ֵ����������ֵС��������Ҫ�ж��������Ƿ�һ����ȫ�����������Ҹ������������Ľ����

## �����ʽ��

�����һ�и���һ��������20��������N���ڶ��и���N��������ͬ��������������Կո�ָ���

## �����ʽ��

�������N��������˳�����һ����ʼΪ�յĶ������������ڵ�һ�������������Ĳ��������������ּ���1���ո�ָ����е���β�����ж���ո񡣵ڶ������YES�������������ȫ���������������NO��

## ��������1��
9  
38 45 42 24 58 30 67 12 51  


## �������1��
38 45 24 58 42 30 12 67 51  
YES  


## ��������2��
8  
38 24 12 45 58 67 42 51  


## �������2��
38 45 24 58 42 12 67 51  
NO  


## ˼·

����Ԫ�أ�����BST��BFS���������ͬʱ�ж��Ƿ�Ϊ��ȫ�����������������ʹ�ó�Աid����ʾ����Ϊ��ȫ����������ý���ڲ�����������е��±�(0~n - 1)����
```
t->left->id = (t->id) * 2 + 1; 
t->right->id = (t->id) * 2 + 2;
```

������ȫ�������Ƚ��ڴ���������id  > n - 1��nΪ�������


## ����code

[L3-010 �Ƿ���ȫ���������� ��30 �֣�.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-010%E6%98%AF%E5%90%A6%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%20(30%E5%88%86)/L3-010%20%E6%98%AF%E5%90%A6%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <queue>
using namespace std;

typedef unsigned char BYTE;
typedef struct TNode {
	int val;
	BYTE id;
	struct TNode *left, *right;
	TNode (int val) : val(val), id(0), left(NULL), right(NULL) {}
} *Tree;
typedef Tree BST;

BST insert(BST tree, int val) {
	if (tree == NULL) {
		return new TNode(val);
	}
	if (val > tree->val)
		tree->left = insert(tree->left, val);
	else
		tree->right = insert(tree->right, val);
	return tree;
}

//��id��ʾ����Ϊ��ȫ����������ý���ڲ�����������е��±꣬��
//t->left->id = (t->id) * 2 + 1; t->right->id = (t->id) * 2 + 2;
//���� id  > n - 1 <=> ������ȫ������
void bfs(Tree tree, int n) {
	if (tree == NULL) return;
	bool isComplete = true;
	queue<Tree> q;
	q.push(tree);
	cout << tree->val;
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		if (t->left != NULL) {
			q.push(t->left);
			cout << " " << t->left->val;			
			if (isComplete && (t->left->id = (t->id) * 2 + 1) > n - 1) isComplete = false;
		}
		if (t->right != NULL) {
			q.push(t->right);
			cout << " " << t->right->val;
			if (isComplete && (t->right->id = (t->id) * 2 + 2) > n - 1) isComplete = false;
		}
	}
	cout << endl;
	cout << (isComplete ? "YES" : "NO");
}

int main() {
	int n;
	cin >> n;
	BST tree = NULL;
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		tree = insert(tree, val);
	}
	bfs(tree, n);
	return 0;
}
```

