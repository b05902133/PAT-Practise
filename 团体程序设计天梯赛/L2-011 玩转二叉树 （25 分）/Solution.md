# L2-011 ��ת������ ��25 �֣�
[ԭ���ַ]()

> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  


����һ�ö����������������ǰ������������Ƚ����������淴ת���������ת��Ĳ�����������С���ν���淴ת����ָ�����з�Ҷ�������Һ��ӶԻ�����������ֵ���ǻ�����ȵ���������

## �����ʽ��

�����һ�и���һ��������N����30�����Ƕ������н��ĸ������ڶ��и���������������С������и�����ǰ��������С����ּ��Կո�ָ���

## �����ʽ��

��һ�������������ת��Ĳ�����������С����ּ���1���ո�ָ�������β�����ж���ո�

## ����������

> 7  
> 1 2 3 4 5 6 7  
> 4 1 3 2 6 5 7  


##���������

> 4 6 1 7 5 3 2

## ˼·

���ȸ���preorder��inorder��������BFS����������������������Ի�����BFSʱ���Գ����е�Ԫ�أ��Ƚ������������ӣ��ٽ������������Ӽ��ɡ�

## ����

```cpp
#include <iostream>
#include <queue>
using namespace std;

typedef struct TNode {
	int val;
	struct TNode *left;
	struct TNode *right;
	TNode(int val) : val(val), left(NULL), right(NULL) {}
} *Tree;

Tree createTree(int *preorder, int preStart, int preEnd, int *inorder, int inStart, int inEnd) {
	if (preStart > preEnd) return NULL;
	int root = preorder[preStart];
	Tree t = new TNode(root);
	int inorderIndex;
	for (inorderIndex = inStart; inorderIndex <= inEnd; inorderIndex++) 
		if (inorder[inorderIndex] == root) break;
	int leftSize = inorderIndex - inStart;
	t->left = createTree(preorder, preStart + 1, preStart + leftSize, inorder, inStart, inorderIndex - 1);
	t->right = createTree(preorder, preStart + leftSize + 1, preEnd, inorder, inorderIndex + 1, inEnd);
	return t;
}

void mirrorImageBFS(Tree t) {
	if (t == NULL) return;
	queue<Tree> q;
	cout << t->val;
	q.push(t);
	while (!q.empty()) {
		Tree tree = q.front();
		q.pop();
		if (tree->right != NULL) {
			cout << " " << tree->right->val;
			q.push(tree->right);
		}
		if (tree->left != NULL) {
			cout << " " << tree->left->val;
			q.push(tree->left);
		}
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	int *inorder = new int[n];
	int *preorder = new int[n];
	for (int i = 0; i < n; i++) cin >> inorder[i];
	for (int i = 0; i < n; i++) cin >> preorder[i];
	Tree t = createTree(preorder, 0, n - 1, inorder, 0, n - 1);
	mirrorImageBFS(t);
	return 0;
}

```
