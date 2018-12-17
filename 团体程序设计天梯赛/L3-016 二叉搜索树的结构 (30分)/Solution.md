# L3-016 �����������Ľṹ ��30 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805047903240192)

>��Ŀ����: ��Խ
��λ: �㽭��ѧ
ʱ������: 400 ms
�ڴ�����: 64 MB
���볤������: 16 KB



����������������һ�ÿ����������Ǿ����������ʵĶ������� ���������������գ��������������н���ֵ��С�����ĸ�����ֵ�����������������գ��������������н���ֵ���������ĸ�����ֵ��������������Ҳ�ֱ�Ϊ��������������ժ�԰ٶȰٿƣ�

����һϵ�л�����ȵ�������������˳�β���һ�ó�ʼΪ�յĶ�����������Ȼ��Խ�����Ľṹ��������������Ҫ���жϸ����������Ƿ���ȷ�����罫{ 2 4 1 3 0 }����󣬵õ�һ�ö�������������������硰2�����ĸ�������1��4���ֵܽ�㡱����3��0��ͬһ���ϡ���ָ�Զ����µ������ͬ������2��4��˫�׽�㡱����3��4�����ӡ�������ȷ�ģ�����4��2�����ӡ�����1��3���ֵܽ�㡱���ǲ���ȷ�ġ�

## �����ʽ��

�����ڵ�һ�и���һ��������N����100�������һ�и���N��������ͬ�����������ּ��Կո�ָ���Ҫ��֮˳�β���һ�ó�ʼΪ�յĶ�����������֮�����һ��������M����100�������M�У�ÿ�и���һ����жϵĳ����䡣������������6�֣�

* A is the root����"A�����ĸ�"��
* A and B are siblings����"A��B���ֵܽ��"��
* A is the parent of B����"A��B��˫�׽��"��
* A is the left child of B����"A��B������"��
* A is the right child of B����"A��B���Һ���"��
* A and B are on the same level����"A��B��ͬһ����"��

��Ŀ��֤���и����������������ͷ�Χ�ڡ�

## �����ʽ��

��ÿ������������ȷ�����Yes���������No��ÿ��ռһ�С�

## ����������

5  
2 4 1 3 0  
8  
2 is the root  
1 and 4 are siblings  
3 and 0 are on the same level  
2 is the parent of 4  
3 is the left child of 4  
1 is the right child of 2  
4 and 0 are on the same level  
100 is the right child of 3  


## ���������

Yes  
Yes  
Yes  
Yes  
Yes  
No  
No  
No  

## ˼·

���Ȳ���Ԫ�أ�����BST���ֵ������룬�жϳ��Ǻ��ֳ����䡣����A��B����BST���ҵ����Ƕ�Ӧ�������ָ�룬�������ڲ����������жϡ������жϵĺ�����װ��һ��class�С�

Ҳ������map�洢Ԫ������Ӧ�������ָ�뼰�����Ķ�Ӧ��map�Ǻ��������ֱ����BST�����ѿ�һЩ�������������ܽ��������(<= 100)������û��ʹ��map��

## ����

[L3-016 �����������Ľṹ ��30 �֣�.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-016%20%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E7%BB%93%E6%9E%84%20(30%E5%88%86)/L3-016%20%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E7%BB%93%E6%9E%84%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

typedef struct TNode {
	int val;
	struct TNode *left;
	struct TNode *right;
	struct TNode *parent;
	TNode(int val) : val(val), left(NULL), right(NULL), parent(NULL) {}
} *Tree;

Tree insert(Tree t, int val) {
	if (t == NULL) {
		return new TNode(val);		
	}
	if (val < t->val) { 
		Tree left = insert(t->left, val);	
		t->left = left;
		left->parent = t;
	}
	else {
		Tree right = insert(t->right, val);
		t->right = right;
		right->parent = t;
	}
	return t;
}

class Statement {
public:
	Statement(Tree t) : t(t) {}
	~Statement() {}

	bool isRoot(int a);
	bool areSiblings(int a, int b);
	bool isParent(int a, int b);
	bool isLeftChild(int a, int b);
	bool isRightChild(int a, int b);
	bool areOnSameLevel(int a, int b);

private:
	Tree t;
	Tree findTreeByVal(Tree tree, int val);
	int getLevel(Tree tree, int val, int level);
};

bool Statement::isRoot(int a) {
	if (t == NULL) return false;
	return t->val == a;
}

bool Statement::areSiblings(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
    Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return ta->parent == tb->parent;	
}

bool Statement::isParent(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
	Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return tb->parent == ta;
}

bool Statement::isLeftChild(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
	Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return tb->left == ta;
}

bool Statement::isRightChild(int a, int b) {
	if (t == NULL) return false;
	Tree ta = findTreeByVal(t, a);
	if (ta == NULL) return false;
	Tree tb = findTreeByVal(t, b);
	if (tb == NULL) return false;
	return tb->right == ta;
}

bool Statement::areOnSameLevel(int a, int b) {
	if (t == NULL) return false;
	int al = getLevel(t, a, 0);
	if (al == -1) return false;
	int bl = getLevel(t, b, 0);
	if (bl == -1) return false;
	return al == bl;
}

Tree Statement::findTreeByVal(Tree tree, int val) {
	if (tree == NULL) return NULL;
	if (val == tree->val)
		return tree;
	else if (val < tree->val)
		return findTreeByVal(tree->left, val);
	else if (val > tree->val)
		return findTreeByVal(tree->right, val);
}

int Statement::getLevel(Tree tree, int val, int level) {
	if (tree == NULL) return -1;
	if (val == tree->val) return level;
	else if (val < tree->val)
		return getLevel(tree->left, val, level + 1);
	else if (val > tree->val)
		return getLevel(tree->right, val, level + 1);
}

int main() {
	Tree t = NULL;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		t = insert(t, val);
	}
	Statement statement(t);
	int m;
	cin >> m;
	int a, b;
	string cmd;
	for (int i = 0; i < m; i++) {
		cin >> a;
		cin >> cmd;
		if (cmd == "is") {
			cin >> cmd; //"the"
			cin >> cmd;
			if (cmd == "root") 
				cout << (statement.isRoot(a) ? "Yes" : "No") << endl;
			else if (cmd == "parent") {
				cin >> cmd; //"of"
				cin >> b;
				cout << (statement.isParent(a, b) ? "Yes" : "No") << endl;
			}
			else if (cmd == "left") {
				cin >> cmd; //"child"
				cin >> cmd; //"of"
				cin >> b;
				cout << (statement.isLeftChild(a, b) ? "Yes" : "No") << endl;
			}
			else if (cmd == "right") {
				cin >> cmd; //"child"
				cin >> cmd; //"of"
				cin >> b;
				cout << (statement.isRightChild(a, b) ? "Yes" : "No") << endl;
			}
		}
		else { //"and"
			cin >> b;
			cin >> cmd; //"are"
			cin >> cmd;
			if (cmd == "siblings") {
				cout << (statement.areSiblings(a, b) ? "Yes" : "No") << endl;
			}
			else { //"on"
				cin >> cmd; //"the"
				cin >> cmd; //"same"
				cin >> cmd; //"level"
				cout << (statement.areOnSameLevel(a, b) ? "Yes" : "No") << endl;
			}
		}
	}
	return 0;
}


```