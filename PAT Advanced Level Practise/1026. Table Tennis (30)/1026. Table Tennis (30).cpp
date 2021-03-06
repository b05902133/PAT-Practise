// 1026. Table Tennis (30).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

struct pnode {
	int arriving_time, playing_time, serving_time, vip_tag;
} * players;

struct tnode {
	int available_time, serving_number, vip_tag;
} * tables;

bool compare(pnode a, pnode b)
{
	return a.arriving_time < b.arriving_time;
}

bool compare1(pnode a, pnode b)
{
	return a.serving_time < b.serving_time;
}

void play(int player_id, int table_id)
{
	players[player_id].serving_time = max(players[player_id].arriving_time, tables[table_id].available_time);
	if (players[player_id].arriving_time > tables[table_id].available_time)
		tables[table_id].available_time = players[player_id].serving_time;
	tables[table_id].available_time += players[player_id].playing_time;
	if (players[player_id].serving_time < 21 * 3600) tables[table_id].serving_number++;
}

void waitAndPlay(int n_players, int n_tables)
{
	for (int player_id = 0; player_id < n_players; player_id++) {
		if (players[player_id].serving_time != 0) continue;
		int table_id = 0;
		if (players[player_id].vip_tag == 0) {
			int flag = 0;
			for (int i = 0; i < n_tables; i++) {
				if (tables[i].available_time < tables[table_id].available_time)
					table_id = i;
				if (tables[i].available_time <= players[player_id].arriving_time) {
					table_id = i;
					flag = 1;
					break;
				}
			}
			if (flag || tables[table_id].vip_tag == 0)
				play(player_id, table_id);
			else {
				for (int i = player_id + 1; i < n_players; i++) {
					if (players[i].arriving_time > tables[table_id].available_time) break;
					if (players[i].vip_tag == 1 && players[i].serving_time == 0) { //vip exist
						play(i, table_id);
						flag = 1;
						player_id--;
						break;
					}
				}
				if (!flag) //no vip
					play(player_id, table_id);
			}
		}//if player is not vip
		else { //player is vip
			int flag = 0, table = -1, viptable = -1;
			for (int i = 0; i < n_tables; i++) {
				if (tables[i].available_time < tables[table_id].available_time)
					table_id = i;
				if (tables[i].vip_tag == 1 && tables[i].available_time <= players[player_id].arriving_time) {
					viptable = i;
					break;
				}
				if (tables[i].vip_tag == 0 && tables[i].available_time <= players[player_id].arriving_time && flag == 0) {
					table = i;
					flag = 1;
				}
			}
			if (viptable != -1) table_id = viptable;
			else if (table != -1) table_id = table;
			play(player_id, table_id);
		}
	}
}

void print_time_string(int time)
{
	int hh, mm, ss;
	hh = time / 3600;
	time %= 3600;
	mm = time / 60;
	time %= 60;
	ss = time;
	printf("%02d:%02d:%02d", hh, mm, ss);
}

int main()
{
	int n, m, k;
	cin >> n;
	players = new pnode[n];
	for (int i = 0; i < n; i++) {
		int hh, mm, ss, playing_minutes, tag;
		scanf("%d:%d:%d %d %d", &hh, &mm, &ss, &playing_minutes, &tag);
		playing_minutes = min(playing_minutes, 120);
		players[i] = { hh * 3600 + mm * 60 + ss, playing_minutes * 60,0, tag };
	}
	sort(players, players + n, compare);
	cin >> m >> k;
	tables = new tnode[m];
	for (int i = 0; i < m; i++)
		tables[i] = { 8 * 3600, 0 , 0};
	for (int i = 0; i < k; i++) {
		int table;
		cin >> table;
		tables[table - 1].vip_tag = 1;
	}
	waitAndPlay(n, m);
	sort(players, players + n, compare1);
	for (int i = 0; i < n; i++) {
		if (players[i].serving_time >= 21 * 3600) break;
		print_time_string(players[i].arriving_time);
		printf(" ");
		print_time_string(players[i].serving_time);
		printf(" %d\n", (int)((players[i].serving_time - players[i].arriving_time)/60.0 + 0.5));
	}
	for (int i = 0; i < m; i++) {
		if (i != 0) putchar(' ');
		cout << tables[i].serving_number;
	}
    return 0;
}

