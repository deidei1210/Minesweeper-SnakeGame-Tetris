/*2051498 信12 储岱泽*/
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <fstream>
#include<iostream>
#include "俄罗斯方块头文件.h"
#include "颜色头文件.h"
using namespace std;

struct HISTORY {
	int score = 0;//历史记录的成绩，后面显示排行榜的时候，需要根据这个来进行一个排序
	//历史玩这个游戏的时间
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
HISTORY history[100] = { 0 };//可以最多存储过去100次的一个得分的情况

char name[15] = { 0 };//用户要输入的名字
char code[25] = { 0 };//用户要输入的密码

char tname[15] = { 0 };
char sname[15] = { 0 };

int score_former_main[100] = { 0 };
int score_former_unranked[100] = { 0 };
int ave = 0;//历史的平均分

wchar_t usernames[50];
wchar_t userscores[50];
wchar_t playtime[50];

void initscreenstart()
{
	//先设置背景颜色是白色
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	//改变窗口标题名字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"Have fun!");

	settextstyle(35, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(100, 150, L"HAVE FUN");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 - 3, 150 + 40, 240 + 3, 150 + 40 + 10);

	settextstyle(15, 0, L"verdana");
	outtextxy(150, 150 + 40 + 10 + 10, L"Loading...");

	for (int i = 0; i < 5; i++) {
		setfillcolor(RGB(45, 84, 117));
		solidrectangle(120 + 24 * i, 150 + 40 + 2, 120 + 24 * i + 22, 150 + 40 + 2 + 6);
		Sleep(2000);
	}
	Sleep(3000);
	cleardevice();//清屏

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(80, 150, L"Created by deidei");

	Sleep(2000);
	
}
int choose_game()
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();//清屏
	
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"Have fun!");
	settextstyle(25, 0, L"verdana");
	
	settextcolor(RGB(254, 141, 114));
	outtextxy(50, 80, L"Put '1' to play Tetris");
	outtextxy(50, 120, L"Put '2' to play Snake");
	outtextxy(50, 160, L"Put '3' to play MineSweeper");
	settextcolor(RGB(45, 84, 117));
	outtextxy(50, 200, L"Put '0' to Exit");
	outtextxy(50, 240, L"Put 'r' to check ranking list");
	outtextxy(50, 280, L"Put 'q' to log out");


	int m = 0;
	while (m != '1' && m != '2'&&m!='0'&&m!='q'&&m!='r' && m != '3') {
		m = _getwch();
	}
	cleardevice();//清屏
	return m;

}

void name_copy() {
	for (int i = 0; name[i] != '\0'; i++) {
		tname[i] = name[i];
		sname[i] = name[i];
	}
}
void s_name()
{
	char* namep = sname;
	for (int i = 0; name[i] != '\0'; i++) {
		namep++;//把指针挪到尾零的位置
	}
	*namep = 's';
	namep++;
	*namep = '.';
	namep++;
	*namep = 't';
	namep++;
	*namep = 'x';
	namep++;
	*namep = 't';


}
void t_name()
{
	char* namep = tname;
	for (int i = 0; name[i] != '\0'; i++) {
		namep++;//把指针挪到尾零的位置
	}
	*namep = 't';
	namep++;
	*namep = '.';
	namep++;
	*namep = 't';
	namep++;
	*namep = 'x';
	namep++;
	*namep = 't';


}

void exchange(int &a, int &b)//在数组中将a和b交换位置
{
	int tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}
void paixu(int choice) {
	fstream fr;
	if (choice == '1')
		fr.open(tname, ios::in);//当选择的是1的时候，说明查看的是俄罗斯方块的排行榜
	else if (choice == '2')
		fr.open(sname, ios::in);//当选择的是2的时候，说明查看的是贪吃蛇的排行榜

	int m= 1;
	int i = 0;
	while (1) {
		if (!fr.eof()) {
			fr >> m;//把过去的得分读给history
			history[i].score = m;

			fr >> m;//把过去的得分读给history
			history[i].year = m;

			fr >> m;//把过去的得分读给history
			history[i].month = m;

			fr >> m;//把过去的得分读给history
			history[i].day = m;

			fr >> m;//把过去的得分读给history
			history[i].hour = m;

			fr >> m;//把过去的得分读给history
			history[i].minute = m;

			fr >> m;//把过去的得分读给history
			history[i].second = m;
		}
		else
			break;
		i++;//记录一共读了几个进去
	}
	if (i >= 1) {
		i -= 1;
		history[i].score = 0;
	}
	//接下来对每一次的score进行一个排序
	int max = 0, tmp = 0;//先假设最大的是第一项
	for (int j = 0; j < i; j++) {
		max = j;
		for (int m = j; history[m].score; m++) {
			if (history[max].score < history[m].score) {
				max = m;
			}
		}//找到后面所有项中最大的那一个
		if (max != j) {
			/*tmp = history[j].score;
			history[j].score = history[max].score;
		    history[max].score = tmp;*/
			exchange(history[j].score, history[max].score);
			exchange(history[j].year, history[max].year);
			exchange(history[j].month, history[max].month);
			exchange(history[j].day, history[max].day);
			exchange(history[j].hour, history[max].hour);
			exchange(history[j].minute, history[max].minute);
			exchange(history[j].second, history[max].second);
		}
	}//这样就从大到小排好序了

	fr.close();//当选择的是2的时候，说明查看的是贪吃蛇的排行榜
}
int RankingChoice() 
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();//清屏
	
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"Ranking");
	settextstyle(25, 0, L"verdana");

	settextcolor(RGB(254, 141, 114));
	outtextxy(50, 160-30, L"Put '1' to check Teris");
	outtextxy(50, 200-30, L"Put '2' to check Snake");
	outtextxy(50, 240-30, L"Put '0' to return");
	
	int m = 0;
	while (m != '1' && m != '2' && m != '0') {
		m = _getwch();
	}
	cleardevice();//清屏
	return m;

}
void RankScreen(int choice)//显示排行榜的基本界面
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();//清屏

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"History");
	settextstyle(35, 0, L"verdana");
	settextcolor(RGB(254, 141, 114));
	if(choice=='1')
	    outtextxy(50, 5, L"History of Tetris");
	else if(choice=='2')
		outtextxy(50, 5, L"History of Snake");

	settextstyle(25, 0, L"verdana");
	outtextxy(10, 45, L"Player");//玩家姓名
	outtextxy(130-20, 45, L"Score");//玩家分数
	outtextxy(250, 45, L"Time");//玩家玩的时间

	settextstyle(20, 0, L"verdana");
	outtextxy(10, 320, L"<= put'A'");
	outtextxy(260, 320, L"put 'D'=>");//翻页的标识

	settextstyle(15, 0, L"verdana");
	outtextxy(120, 320, L"put ENTER to return");//翻页的标识
}
void Rank(int choice)//打印历史记录，一页打印十个记录
{
	int count = 0;
	int page = 0;
	int page_all = 0;
	int turn = 0;
	for (int c = 0; history[c].score != 0; c++) {
		count++;//用来数一数，一共统计到了多少个分数
	}
	page_all = count / 10;//总页数
	cout << count << endl;
	while (1) {//count可以用来表示后面还没有显示出来的个数
		if (count-10<=0) {//不满十个，不需要翻页
			for (int i = page * 10; i < count- page * 10; i++) {
				settextstyle(20, 0, L"verdana");
				settextcolor(RGB(45, 84, 117));

				for (int j = 0; name[j] != '\0'; j++) {
					outtextxy(10 + 10 * j, 65 + 25 * i, name[j]);//打印名字
				}
				//swprintf(userscores, 29, L"%d", score_former_unranked[i]);
				swprintf(userscores, 29, L"%d", history[i].score);
				outtextxy(130-20, 65 + 25 * i, userscores);//打印分数
				
				swprintf(playtime, 29, L"%d-%d-%d %d:%d:%d", history[i].year, history[i].month, history[i].day, history[i].hour, history[i].minute, history[i].second);
				outtextxy(200-20, 65 + 25 * (i - page * 10), playtime);//打印日期


			}
		}
		else if (count - 10 > 0) {//说明此时可以翻页了
			if (page < page_all) {
				for (int i = page * 10; i < page * 10 + 10; i++) {//一页打印十个
					settextstyle(20, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					for (int j = 0; name[j] != '\0'; j++) {
						outtextxy(10 + 10 * j, 65 + 25 * (i - page * 10), name[j]);//打印名字
					}
					//swprintf(userscores, 29, L"%d", score_former_unranked[i]);
					swprintf(userscores, 29, L"%d", history[i].score);
					outtextxy(130-20, 65 + 25 * (i - page * 10), userscores);//打印分数

					swprintf(playtime, 29, L"%d-%d-%d %d:%d:%d", history[i].year, history[i].month, history[i].day, history[i].hour, history[i].minute, history[i].second);
					outtextxy(200-20, 65 + 25 * (i - page * 10), playtime);//打印日期
				}
			}
			else {
				for (int i = page * 10; history[i].score!=0; i++) {//一页打印十个
					settextstyle(20, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					for (int j = 0; name[j] != '\0'; j++) {
						outtextxy(10 + 10 * j, 65 + 25 * (i - page * 10), name[j]);//打印名字
					}
					//swprintf(userscores, 29, L"%d", score_former_unranked[i]);
					swprintf(userscores, 29, L"%d", history[i].score);
					outtextxy(130-20, 65 + 25 * (i - page * 10), userscores);//打印分数

					swprintf(playtime, 29, L"%d-%d-%d %d:%d:%d", history[i].year, history[i].month, history[i].day, history[i].hour, history[i].minute, history[i].second);
					outtextxy(200-20, 65 + 25 * (i - page * 10), playtime);//打印日期

				}

			}
		}
		while (turn != '\n' && turn != '\r' && turn != 'A' && turn != 'D') {
			turn = _getwch();
		}

		if (turn == '\n' || turn == '\r')
			break;
		else if (turn == 'A') {
			if (page > 0) {//此时可以往前翻
				page--;
			}
			RankScreen(choice);
		}
		else if (turn == 'D') {
			if (page < page_all) {//此时可以往后翻
				page++;
			}
			RankScreen(choice);
		}
		turn = 0;
		//cout << "page:"<<page << endl;
		//cout << "page all:"<<page_all << endl;
		//cout << endl;
	}

}

int main()
{
   initscreenstart();//初始屏幕，启动
	SignIn();//登录界面
	name_copy();
	t_name();
	s_name();
	while (1) {
		int m = 0;
		m = choose_game();
		if (m == '1') {
			TetrisGame();
		}
		else if (m == '2') {
			SnakeGame();
		}
		else if (m == '3') {
			mine_sweeper();
		}
		else if (m == '0') {
			break;
		}
		else if (m == 'q') {//登出，切换用户重新登陆
			for (int i = 0; i < 15; i++) {
				name[i] = 0;
			}
			for (int j = 0; j < 15; j++) {
				tname[j] = 0;
				sname[j] = 0;
			}//全部归零，重新登陆
			for (int m = 0; m < 25; m++) {
				code[m] = 0;
			}

			SignIn();//登录界面
			name_copy();
			t_name();
			s_name();
		}
		else if (m == 'r') {//查看排行榜
			int choice = 0;
			choice=RankingChoice();//选择查看哪一个排行榜
			if (choice != '0') {
				for (int i = 0; i < 100; i++) {
					score_former_main[i] =0;
					score_former_unranked[i] =0;
				}
				paixu(choice);//先对选择的那一个游戏进行排序,并且将排序后的分数按从大到小的顺序存在了former_score里面
				RankScreen(choice);
				Rank(choice);
			}
			else
				continue;//返回选择界面
		}
	}

	closegraph();
	return 0;
}