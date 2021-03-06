// 1137. Final Grading (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
# include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>
#include <algorithm>

struct node {
	string id;
	int gp, gm, gf, g;
};

bool compare(node a, node b)
{
	return a.g != b.g ? a.g > b.g:a.id < b.id;
}

int main() {
	int p, m, n;
	cin >> p >> m >> n;
	map<string, node> students;
	string id;
	for (int i = 0; i < p; i++) {
		int gp;
		cin >> id >> gp;
		if (students.find(id) == students.end()) {
			students[id] = { id, -1, -1, -1, -1 };
		}
		students[id].gp = gp;
	}
	for (int i = 0; i < m; i++) {
		int gm;
		cin >> id >> gm;
		if (students.find(id) == students.end()) {
			students[id] = { id, -1, -1, -1, -1 };
		}
		students[id].gm = gm;
	}
	for (int i = 0; i < n; i++) {
		int gf;
		cin >> id >> gf;
		if (students.find(id) == students.end()) {
			students[id] = { id, -1, -1, -1, -1 };
		}
		students[id].gf = gf;
		students[id].g = gf > students[id].gm ? gf : round(students[id].gm*0.4 + gf * 0.6);
	}
	vector<node> s;
	for (auto it = students.begin(); it != students.end(); it++) {
		if (it->second.g < 60)continue;
		if (it->second.gp < 200) continue;
		s.push_back(it->second);
	}
	sort(s.begin(), s.end(), compare);
	for (auto it = s.begin(); it != s.end(); it++) {
		cout << it->id;
		printf(" %d %d %d %d\n", it->gp, it->gm, it->gf, it->g);
	}
	return 0;
}

