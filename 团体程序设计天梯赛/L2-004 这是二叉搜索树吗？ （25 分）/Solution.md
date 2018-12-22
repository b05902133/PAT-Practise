# L2-004 ���Ƕ����������� (25 �֣�
[ԭ���ַ](https://pintia.cn/problem-sets/994805046380707840/problems/994805070971912192)


> ����: ��Խ  
> ��λ: �㽭��ѧ  
> ʱ������: 400 ms  
> �ڴ�����: 64 MB  
> ���볤������: 16 KB  


һ�ö����������ɱ��ݹ�ض���Ϊ�����������ʵĶ�������������һ��㣬
* �������������н��ļ�ֵС�ڸý��ļ�ֵ��
* �������������н��ļ�ֵ���ڵ��ڸý��ļ�ֵ��
* �������������Ƕ�����������

��ν�����������ġ����񡱣��������н������������Ի�λ�ú����õ�������

����һ��������ֵ���У��������д�����ж����Ƿ��Ƕ�һ�ö������������侵�����ǰ������Ľ����

## �����ʽ��

����ĵ�һ�и��������� N����1000�������һ�и��� N ��������ֵ������Կո�ָ���

## �����ʽ��

������������Ƕ�һ�ö������������侵�����ǰ������Ľ������������һ������� YES ��Ȼ������һ�����������������Ľ�������ּ��� 1 ���ո�һ�е���β�����ж���ո������Ƿ������ NO��

## �������� 1��  

> 7  
> 8 6 5 7 10 8 11  


## ������� 1��

> YES  
> 5 7 6 8 11 10 8  


## �������� 2��

> 7  
> 8 10 11 8 6 7 5  


## ������� 2��

> YES  
> 11 8 10 7 5 6 8  


## �������� 3��
> 7  
> 8 6 8 5 10 9 11  


## ������� 3��
> NO  

## ˼·

�����ж��Ƿ����Ϊ����BST�������������ж��Ƿ����ΪBST�ľ����жϹ����еõ�������������
���ж�����BSTΪ����preorder�ĵ�һ��Ԫ��Ϊpostorder�����һ����preorder�е�һ�����ڵ���preorder
�ĵ�һ��Ԫ�صģ���Ϊ�������ĸ����������������ݹ���⡣��������������ÿһ��Ԫ����Ҫ>=preorder��
��һ��Ԫ�أ�����Ͳ���BST,����ж������贫���ݹ��������ĺ����С������жϷ���������ע�͡�

## ����

[L2-004 ���Ƕ����������� ? (25��).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-004%20%E8%BF%99%E6%98%AF%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E5%90%97%EF%BC%9F%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-004%20%E8%BF%99%E6%98%AF%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E5%90%97%EF%BC%9F%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
using namespace std;
typedef enum {
	NORMAL, //����BST����С�Ҵ�
	MIRROR_IMAGE, //����BST�������С
} BSTType; //BST����

struct Flag { //preToPost�����е�һ��flag
	BSTType type; //BST����
	bool hasFlag; //�Ƿ���flag
	int val; //��hasFlagΪtrueʱ����Ҫ����Ԫ�ش��ڵ��ڻ�С�ڵ���val
	Flag(BSTType type, bool hasFlag, int val) : type(type), hasFlag(hasFlag), val(val) {}
};

int *preorder;
int *postorder;

bool preToPost(int preStart, int preEnd, int postStart, int postEnd, Flag flag) {
	if (preStart > preEnd) return true;
	postorder[postEnd] = preorder[preStart];	
	if (preStart == preEnd) return true;
	int i;
	for (i = preStart + 1; i <= preEnd; i++) {
		if (flag.hasFlag && flag.type == NORMAL && preorder[i] < flag.val) return false; //����BST����hadFlagΪtrueʱ������С��val
		if (flag.hasFlag && flag.type == MIRROR_IMAGE && preorder[i] > flag.val) return false; //����BST����hadFlagΪtrueʱ�����ܴ���val
		if (flag.type == NORMAL && preorder[i] >= preorder[preStart]) break;
		if (flag.type == MIRROR_IMAGE && preorder[i] < preorder[preStart]) break;
	}
	//������������
	int leftSize = i - preStart - 1;
	if (!preToPost(preStart + 1, i - 1, postStart, postStart + leftSize - 1, Flag(flag.type, false, 0))) return false; //��������flag����Ҫ�ж�
	if (!preToPost(i, preEnd, postStart + leftSize, postEnd - 1, Flag(flag.type, true, preorder[preStart]))) return false;
	return true;
}

int main() {
	int n;
	cin >> n;
	preorder = new int[n];
	postorder = new int[n];
	for (int i = 0; i < n; i++)
		cin >> preorder[i];
	if (preToPost(0, n - 1, 0, n - 1, Flag(NORMAL, false, 0))) { //����BST
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			if (i != 0) putchar(' ');
			cout << postorder[i];
		}
	}
	else if (preToPost(0, n - 1, 0, n - 1, Flag(MIRROR_IMAGE, false, 0))) { //����BST
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			if (i != 0) putchar(' ');
			cout << postorder[i];
		}
	}
	else cout << "NO";
	free(preorder);
	free(postorder);
	return 0;
}
```
