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

