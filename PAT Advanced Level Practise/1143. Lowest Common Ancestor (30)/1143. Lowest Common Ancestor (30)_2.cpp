#include <iostream>
using namespace std;
#include <map>

int main()
{
	map<int, int>flag;
	int m, n;
	scanf("%d %d", &m, &n);
	int *pre = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &pre[i]);
		flag[pre[i]] = 1;
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		bool u_exists = flag[u] == 1;
		bool v_exists = flag[v] == 1;
		if (!u_exists && !v_exists)
			printf("ERROR: %d and %d are not found.\n", u, v);
		else if (!u_exists || !v_exists)
			printf("ERROR: %d is not found.\n", u_exists ? v : u);
		else {
			for (int j = 0; j < n; j++) {
				if ((pre[j] > u && pre[j] < v) || (pre[j] < u && pre[j] > v)) {
					printf("LCA of %d and %d is %d.\n", u, v, pre[j]);
					break;
				}
				else if (pre[j] == u || pre[j] == v) {
					printf("%d is an ancestor of %d.\n", pre[j] == u ? u : v, pre[j] == u ? v : u);
					break;
				}
			}
		}
	}
    return 0;
}

