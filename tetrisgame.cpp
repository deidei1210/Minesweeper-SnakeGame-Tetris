/*2051498 信12 储岱泽*/
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <fstream>
#include "俄罗斯方块头文件.h"
#include "颜色头文件.h"
using namespace std;
DWORD t_time_now;
extern char name[15];//用户要输入的名字
extern char tname[15];
extern char sname[15];

int color[5] = { 0 };
const int radius = 10;//圆圈的半径
//基本元素圆圈的半径为10
//这一个结构体定义的是每一种基本图形的基本信息
struct CIRCLE {
	int x, y;
};
struct CIRCLE_GROUP {
	CIRCLE rotation_status[4][4];//记录该形状下每一种旋转的状态
};
struct SHAPE {//这里面定义的是此时呈现的图形
	CIRCLE circle_group[4] = { 0 };//每一个基本图形都是由四个基本的圆组成的，这里定义这四个圆的基本的坐标信息
	int shape = 0;//记录该圆圈组属于哪一种图形
	int rotation_status = 0;//旋转的状态
	int color = 0;//颜色
};
CIRCLE_GROUP shan_group = {
		{{{0,0},{20,0},{20,-20},{40,0}},//未经过旋转的状态
		{{20,0},{0,0},{0,-20},{0,20}},//顺时针转过90度的状态
		{{0,0},{20,0},{20,20},{40,0}},//顺时针转过180度的状态
		{{0,0},{20,20},{20,0},{20,-20}}//顺时针转过270度的状态
	} };
CIRCLE_GROUP tian_group = {
		{{{0,0},{0,-20},{20,-20},{20,0}},//未经过旋转的状态
		{{0,0},{0,-20},{20,-20},{20,0}},//顺时针转过90度的状态
		{{0,0},{0,-20},{20,-20},{20,0}},//顺时针转过180度的状态
		{{0,0},{0,-20},{20,-20},{20,0}}//顺时针转过270度的状态
	} };
CIRCLE_GROUP yi_group = {
		{{{0,0},{0,-20},{0,-40},{0,-60}},//未经过旋转的状态
		{{0,0},{20,0},{40,0},{60,0}},//顺时针转过90度的状态
		{{0,0},{0,-20},{0,-40},{0,-60}},//顺时针转过180度的状态
		{{0,0},{20,0},{40,0},{60,0}}//顺时针转过270度的状态
	} };
CIRCLE_GROUP trans_L_group = {
		{{{0,0},{20,0},{20,-20},{20,-40}},//未经过旋转的状态
		{{0,0},{20,0},{40,0},{0,-20}},//顺时针转过90度的状态
		{{0,0},{0,-20},{0,-40},{20,-40}},//顺时针转过180度的状态
		{{0,-20},{20,-20},{40,-20},{40,0}}//顺时针转过270度的状态
	} };
CIRCLE_GROUP L_group = {
		{{{0,0},{0,-20},{0,-40},{20,0}},//未经过旋转的状态
		{{0,0},{0,-20},{20,-20},{40,-20}},//顺时针转过90度的状态
		{{0,-40},{20,-40},{20,-20},{20,0}},//顺时针转过180度的状态
		{{0,0},{20,0},{40,0},{40,-20}}//顺时针转过270度的状态
	} };
CIRCLE_GROUP trans_Z_group = {
		{{{0,-20},{20,-20},{20,0},{40,0}},//未经过旋转的状态
		{{0,0},{0,-20},{20,-20},{20,-40}},//顺时针转过90度的状态
		{{0,-20},{20,-20},{20,0},{40,0}},//顺时针转过180度的状态
		{{0,0},{0,-20},{20,-20},{20,-40}}//顺时针转过270度的状态
	} };
CIRCLE_GROUP Z_group = {
		{{{20,-20},{20,-40},{40,0},{40,-20}},//未经过旋转的状态
		{{0,0},{20,0},{20,-20},{40,-20}},//顺时针转过90度的状态
		{{20,-20},{20,-40},{40,0},{40,-20}},//顺时针转过180度的状态
		{{0,0},{20,0},{20,-20},{40,-20}}//顺时针转过270度的状态
	} };
//这是几种基本图形，以及他们的旋转情况的数组

CIRCLE_GROUP shape_groups[7] = { shan_group ,tian_group ,yi_group,trans_L_group ,L_group,trans_Z_group,Z_group };
SHAPE choice_shape;//定义一个此时随机生成的图形
SHAPE next_shape;//定义下一个生成的方块
SHAPE former_shape;//定义一个此时随机生成的图形

struct TIME {
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
TIME play_time = { 0 };//用来记录这一次的时间
struct T_HISTORY {
	int score = 0;//历史记录的成绩，后面显示排行榜的时候，需要根据这个来进行一个排序
	//历史玩这个游戏的时间
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
T_HISTORY history[100] = { 0 };//可以最多存储过去100次的一个得分的情况

int record_position_still[16][11] = { 0 };//用来记录哪些位置此时有已经停下来的小方块
int record_position_color[16][11] = { 0 };//用来记录哪些位置此时有已经停下来的小方块的颜色
int record_position_still_copy[16][11] = { 0 };//用来记录哪些位置此时有已经停下来的小方块
int record_position_color_copy[16][11] = { 0 };//用来记录哪些位置此时有已经停下来的小方块的颜色
int record_drop_position[2] = { 0 };

int score = 0;//用来记录分数
int judge_over = 0;//用来判断游戏是否结束
int judge_stop = 0;//用来判断此时的这个方块是否触礁需要停止了了

int rotation_now = 0;
int rotation_next = 0;

int shape_now = 0;
int shape_next = 0;

int judge_bottom = 0;//用于判断是否已经到底了

int trans_x = 0;//用来表示数组的下标，由圆心坐标转换过来的
int trans_y = 0;//用来表示数组的下标，由圆心坐标转换过来的

int count_round = 0;
int clean = 1;//一开始假设是要清行的

wchar_t over_tips[50];
wchar_t score_tips[50];
wchar_t score_highest[50];

int color_theme_former = 0;
int color_shape_former = 0;

int score_former[100] = { 0 };//这里面存放的是过去一百次的得分并且进行一个排名

const int color_groups_tetris[4][5] = {
	{COLOR1_p ,COLOR2_p, COLOR3_p,COLOR4_p, COLOR5_p },
	{COLOR1_r ,COLOR2_r, COLOR3_r,COLOR4_r, COLOR5_r },
	{COLOR1_g ,COLOR2_g, COLOR3_g,COLOR4_g, COLOR5_g },
	{COLOR1_b ,COLOR2_b, COLOR3_b,COLOR4_b, COLOR5_b }
};//自定义的颜色集合

void t_initscreen()
{

	//设置背景颜色为白色
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	//划线
	setlinecolor(RGB(138, 163, 183));
	line(221, 0, 221, 331);
	line(19, 0, 19, 331);
	line(19, 331, 221, 331);

	//改变窗口标题名字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"俄罗斯圈圈");
	// 绘图模式设置
	setbkmode(TRANSPARENT);
	// 随机数种子
	srand(time(NULL));

	//设置游戏界面
	//画出显示下一个方块的区间
	line(229, 49, 329, 49);
	line(229, 49, 229, 151);
	line(329, 49, 329, 151);
	line(229, 151, 329, 151);

	settextcolor(COLOR4_r);
	settextstyle(12, 0, L"楷体");
	swprintf(score_highest, 29, L"历史最高：%d",history[0].score);//这一句话学着点
	outtextxy(229, 49 - 30 - 15, score_highest);
	outtextxy(229, 151 + 10, L"按空格键暂停");

	settextcolor(RGB(137, 155, 169));
	settextstyle(12, 0, L"楷体");
	outtextxy(229, 49 - 30, L"下一个图形");
	outtextxy(229, 151 + 30, L"小写j <-向左运动");
	outtextxy(229, 151 + 60, L"小写l ->向右运动");
	outtextxy(229, 151 + 90, L"小写k   加速向下");
	outtextxy(229, 151 + 120, L"小写i   顺时旋转");

}
void t_initscreenstart()
{
	//先设置背景颜色是白色
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(40, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(120, 150, L"TETRIS");
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
	cleardevice();//清屏

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(80, 150, L"Put Enter To Begin");

	while (_getwch() != 13);

	cleardevice();//清屏
}
void t_pause_screem()
{
	cleardevice();

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(60, 150, L"Put Space To Continue");

	while (_getwch() != ' ');

	cleardevice();//清屏
	t_initscreen();//重新初始化界面

	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (record_position_still[j][i] == 1) {
				setfillcolor(record_position_color[j][i]);
				solidcircle(30 + 20 * i, 30 + 20 * j + 10, radius);
			}
		}
	}//把静止的那些方块补画上去
	return;

}
void t_put_score() {
	setfillcolor(WHITE);
	solidrectangle(229, 151 + 120 + 30, 340, 340);

	settextcolor(COLOR4_r);
	settextstyle(15, 0, L"楷体");
	swprintf(score_tips, 29, L"得分：%d", score);//这一句话学着点
	outtextxy(229, 151 + 120 + 40, score_tips);

}
void t_form_theme_color()
{
	int color_choice = 0;
	while (1) {
		color_choice = rand() % 4;
		if (color_choice != color_theme_former)
			break;//用来保证每一次生成的与上一次不一样
	}
	for (int i = 0; i < 5; i++) {
		color[i] = color_groups_tetris[color_choice][i];
	}
	color_choice = color_theme_former;
}
//该函数的作用是最初随机生成一个俄罗斯方块,并把随机生成的数赋值给记录shape的结构体
void t_trans(int& trans_x, int& trans_y, int X, int Y, int i)
{
	int x = 0, y = 0;
	x = X + choice_shape.circle_group[i].x;
	y = Y + choice_shape.circle_group[i].y;//此时每一个点真实的坐标

	trans_x = (x - 30) / 20;
	trans_y = (y - 30) / 20;//对应着的数组的下标

}
void t_over()
{
	for (int i = 0; i < 10; i++) {
		if (record_position_still[0][i] == 1)
			judge_over = 1;
	}
}
void t_form_shape_now(int X, int Y)
{
	for (int w = 0; w < 4; w++) {
		choice_shape.circle_group[w].x = shape_groups[shape_next].rotation_status[rotation_next][w].x;
		choice_shape.circle_group[w].y = shape_groups[shape_next].rotation_status[rotation_next][w].y;
	}
	//把随机生成的颜色赋值给这个图形
	choice_shape.color = next_shape.color;
	rotation_now = rotation_next;
	shape_now = shape_next;
}
//用于提前生成下一个要下降的方块
void t_form_shape_next()
{
	int choice_p = rand() % 7,
		choice_c = 0,//随机生成一种颜色
		choice_r = rand() % 4;//随机生成一个旋转角度

	while (1) {
		choice_c = rand() % 5;
		if (choice_c != color_shape_former)
			break;//用来保证每一次生成的与上一次不一样
	}

	color_shape_former = choice_c;

	//将随机生成的图形的参数值赋值给该定义的图形
	for (int w = 0; w < 4; w++) {
		next_shape.circle_group[w].x = shape_groups[choice_p].rotation_status[choice_r][w].x;
		next_shape.circle_group[w].y = shape_groups[choice_p].rotation_status[choice_r][w].y;
	}
	//把随机生成的颜色赋值给这个图形
	next_shape.color = color[choice_c];
	rotation_next = choice_r;
	shape_next = choice_p;
	color_shape_former = choice_c;
}
void t_first_round_shape()
{
	int choice_p = rand() % 7,
		choice_c = rand() % 5,//随机生成一种颜色
		choice_r = rand() % 4;//随机生成一个旋转角度
		//将随机生成的图形的参数值赋值给该定义的图形
	color_shape_former = choice_c;
	for (int w = 0; w < 4; w++) {
		choice_shape.circle_group[w].x = shape_groups[choice_p].rotation_status[choice_r][w].x;
		choice_shape.circle_group[w].y = shape_groups[choice_p].rotation_status[choice_r][w].y;
	}
	//把随机生成的颜色赋值给这个图形
	choice_shape.color = color[choice_c];
	rotation_now = choice_r;
	shape_now = choice_p;

}
//该函数可以用来在指定的位置画出一个指定的形状
void t_draw_circle_group(int X, int Y)
{
	setfillcolor(choice_shape.color);
	for (int i = 0; i < 4; i++) {
		solidcircle(X + choice_shape.circle_group[i].x, Y + choice_shape.circle_group[i].y, radius);
	}
	t_mark_position(X, Y);//用来标记运动数组和静止数组
}
//该函数可以在指定位置擦去一个指定的形状
void t_clear_circle_group(int X, int Y)
{
	for (int i = 0; i < 4; i++) {
		clearcircle(X + former_shape.circle_group[i].x, Y + former_shape.circle_group[i].y, radius);
		//record_position_move[former_shape.circle_group[i].x+X][Y + former_shape.circle_group[i].y] = 0;
	}

}
//从(X,Y)的地方开始下降,以speed的速度
//下降到什么地方停下来，也是需要当心的
void t_mark_position(int X, int Y)
{
	judge_bottom = t_bottom(X, Y);
	for (int i = 0; i < 4; i++) {
		t_trans(trans_x, trans_y, X, Y, i);
		//record_position_move[trans_y][trans_x] = 1;//在此时的圆心位置的对应项赋值为1，表示记录了此时此位置有圆了

		if (record_position_still[trans_y + 1][trans_x] == 1 || judge_bottom == 1) {//如果下面那个是1的话，那么就说明要触礁了
			judge_stop = 1;
			for (int m = 0; m < 4; m++) {
				t_trans(trans_x, trans_y, X, Y, m);
				record_position_still[trans_y][trans_x] = 1;//在此时的圆心位置的对应项赋值为1，表示记录了此时此位置有圆了
				record_position_color[trans_y][trans_x] = choice_shape.color;//在此时的圆心位置的对应项赋值为1，表示记录了此时此位置有圆了
			}
			score += 5;
		}
	}
}
void t_draw_next()
{
	setfillcolor(next_shape.color);
	for (int i = 0; i < 4; i++) {
		solidcircle(250 + next_shape.circle_group[i].x, 120 + next_shape.circle_group[i].y, radius);
	}

}
int t_cmd()
{
	while (1) {
		// 如果长时间没有指令的话，就向下走
		DWORD time_tmp = GetTickCount();
		if (time_tmp - t_time_now >= 1000)
		{
			t_time_now = time_tmp;
			return DOWN;
		}
		// 接受指令
		if (_kbhit()) {
			switch (_getch()) {
				case 'i':
					return ROTATE;
				case 'j':
					return LEFT;
				case 'l':
					return RIGHT;
				case 'k':
					return DOWN;
				case ' ':
					return STOP;
			}
		}
		Sleep(20);
	}
}
void t_react(int m, int& x, int& y)
{
	int commend_left = 1, commend_right = 1;
	int judge_border = 0;

	for (int w = 0; w <= 3; w++) {
		former_shape.circle_group[w].x = choice_shape.circle_group[w].x;
		former_shape.circle_group[w].y = choice_shape.circle_group[w].y;
	}
	//用来判断是否具备向左运动的资格
	for (int i = 0; i < 4; i++) {
		judge_border = x + former_shape.circle_group[i].x;//此时圆心的横坐标
		t_trans(trans_x, trans_y, x, y, i);
		if (trans_x - 1 < 0)
			commend_left = 0;
		else if (judge_border <= 30 || record_position_still[trans_y][trans_x - 1] == 1)
			commend_left = 0;
		if (judge_border >= 210 || record_position_still[trans_y][trans_x + 1] == 1)
			commend_right = 0;

	}
	switch (m) {
		case DOWN:
			y += 20;
			break;
		case LEFT:
			if (commend_left)
				x -= 20;
			break;
		case RIGHT:
			if (commend_right)
				x += 20;
			break;
		case ROTATE:
			if (rotation_now < 3)
				rotation_now++;
			else if (rotation_now == 3)
				rotation_now = 0;

			for (int i = 0; i < 4; i++) {
				judge_border = x + shape_groups[shape_now].rotation_status[rotation_now][i].x;//此时圆心的横坐标
				if (judge_border < 30)
					commend_left = 0;
				if (judge_border > 210)
					commend_right = 0;
			}

			if (commend_left && commend_right) {
				for (int w = 0; w <= 3; w++) {
					choice_shape.circle_group[w].x = shape_groups[shape_now].rotation_status[rotation_now][w].x;
					choice_shape.circle_group[w].y = shape_groups[shape_now].rotation_status[rotation_now][w].y;
				}
			}
			else {
				if (rotation_now <= 3 && rotation_now > 0)
					rotation_now--;
				else if (rotation_now == 0)
					rotation_now = 3;
			}
			break;
		case STOP:
			record_drop_position[0] = x;//此时的横坐标
			record_drop_position[1] = y;//此时的纵坐标
			t_pause_screem();
			t_put_score();//打印此时的分数
			t_draw_next();
	}
}
//用来在下降过程中判断是否已经到底(底是y=310的地方)
int t_bottom(int X, int Y)
{
	int m = 0;
	int y = 0;
	for (int w = 0; w < 4; w++) {
		y = Y + shape_groups[shape_now].rotation_status[rotation_now][w].y;
		if (y >= 310)
			m = 1;
	}
	return m;
}
void t_shape_drop(int X, int Y, int speed, int dst)
{
	int m = 0;
	int x = X, y = Y;
	int x0 = X, y0 = Y;
	char pau = '0';
	while (judge_stop != 1) {//当还没有触礁的时候
		t_clear_circle_group(x0, y0);
		y0 = y;
		x0 = x;
		t_draw_circle_group(x, y);//在这个地方来判断是否触礁？？？
		m = t_bottom(x, y);
		m = t_cmd();//获得键盘的指示，然后做出反应
		t_react(m, x, y);//将x,y传入，根据键盘的指令，改变x,y的值，得到下一次画圆的位置
		Sleep(1000 / speed);
	};
	t_form_shape_now(90, 0);
}
//该函数可以用来初始化
void t_guiling_per()
{
	judge_stop = 0;
	judge_over = 0;
	judge_bottom = 0;
	t_time_now = GetTickCount();//开始计时
	clean = 1;
}
//该函数用来判断是否可以消行
void t_cleanner(int hang)//要实现下降效果，貌似该行之上的所有行都应该被削掉
{
	int xiayihang = 0;
	score += 50;
	for (int j = 0; j < hang; j++) {
		for (int i = 0; i < 10; i++) {
			clearcircle(30 + 20 * i, 30 + 20 * j + 10, radius);
		}
	}

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			record_position_still_copy[i][j] = record_position_still[i][j];
			record_position_color_copy[i][j] = record_position_color[i][j];
		}
	}
	//全部都清完了以后，要补画上去
	for (int j = 0; j < hang - 1; j++) {
		for (int i = 0; i < 10; i++) {
			xiayihang = j + 1;
			record_position_still[xiayihang][i] = record_position_still_copy[j][i];
			record_position_color[xiayihang][i] = record_position_color_copy[j][i];
		}
	}
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (record_position_still[j][i] == 1) {
				setfillcolor(record_position_color[j][i]);
				solidcircle(30 + 20 * i, 30 + 20 * j + 10, radius);
			}
		}
	}
}
void t_judge_clean_hang()
{
	int hang = 0;
	for (int i = 0; i < 15; i++) {
		clean = 1;
		for (int j = 0; j < 10; j++) {
			if (record_position_still[i][j] == 0) {//如果这一行有一个0说明还没有满，不能清行
				clean = 0;
			}
		}
		if (clean) {//如果这一行遍历下来是满的，说明要清
			hang = i + 1;//说明是第i行需要清理
			t_cleanner(hang);
		}
	}
}
void t_guiling()
{
	score = 0;
	judge_stop = 0;
	judge_over = 0;
	judge_bottom = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 10; j++) {
			record_position_still[i][j] = 0;
		}
	}
	t_time_now = GetTickCount();//开始计时
	count_round = 0;
	clean = 1;
}
void t_clear_next()
{
	for (int i = 0; i < 4; i++) {
		clearcircle(250 + next_shape.circle_group[i].x, 120 + next_shape.circle_group[i].y, radius);
	}
}
void t_end_clear()
{
	for (int j = 0; j < 16; j++) {
		for (int i = 0; i < 10; i++) {
			clearcircle(30 + 20 * i, 10 + 20 * j + 10, radius);

			Sleep(10);
		}
		Sleep(100);
	}

}
//写一个可以把数字转换成字符的函数
void t_int_to_char(int num)
{
	char trans = '0';
	int beishu = 10;
	int num_copy = 120;
	char print_char[10] = { 0 };
	int i = 0;
	while (num_copy > 10) {
		beishu *= 10;
		num_copy /= 10;
	};
	beishu /= 10;
	while (beishu > 0) {
		trans = '0' + 120 / beishu % 10;
		print_char[i] = trans;
		beishu /= 10;
		i++;
	};
}
void t_save_try(int score)
{
	fstream fw;

	fw.open(tname, ios::app);//在文档后面追加
	fw << score << ' '
		<<play_time.year<<' '<< play_time.month<<' '<< play_time.day
		<<' '<< play_time.hour<<' '<< play_time.minute<<' '<< play_time.second<<' ';//然后写进该用户这一次的成绩，之后在记录下此次玩耍的时间
	fw.close();//可以正常存储了
}
void t_paixu_spe() {
	fstream fr;
	fr.open(tname, ios::in);//把文件中的东西输入到变量数组中
	int m = 1;
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
			tmp = history[j].score;
			history[j].score = history[max].score;
			history[max].score = tmp;
		}
	}//这样就从大到小排好序了
}

//用于记录玩这次游戏的时间
void t_record_time(const time_t input_time)
{
	struct tm* tt;	//struct tm 为系统定义的结构体
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	tt = localtime(&input_time);	//localtime为系统函数
	/* tm_*** 为struct tm中的成员，和本题的struct tj_time具体的内容不完全符合，具体含义自己查找相关资料 */
	play_time.year = tt->tm_year + 1900;
	play_time.month = tt->tm_mon + 1;
	play_time.day = tt->tm_mday;
	play_time.hour = tt->tm_hour;
	play_time.minute = tt->tm_min;
	play_time.second=tt->tm_sec;
}
void TetrisGame()
{
	//t_initscreenstart();//初始化界面屏幕
	fstream fw;
	fw.open(tname, ios::app);//在还没有建立这个文档的时候先建立这个文档，以防止下面读取的时候因为找不到文档而发生错误
	fw.close();//建立好了这个文档之后就关闭它
	while (1) {
		t_guiling();//数据归零
		t_paixu_spe();//把过去的成绩和现在的成绩一起进行排序
		t_initscreen();//初始化界面屏幕
		t_form_theme_color();
		t_first_round_shape();//用于生成第一回合的数据，之后生成数据的方式都是先生成下一个图形，再将下一次生成的图形付给现在的
		t_form_shape_next();
		t_paixu_spe();//把过去的成绩和现在的成绩一起进行排序
		while (judge_over != 1) {
			t_guiling_per();//数据归零
			t_draw_next();//在右边的框框中画出下一个下降的图形
			t_put_score();//打印此时的分数

			t_shape_drop(90, 40, 10, 290);//方块下降

			t_judge_clean_hang();//判断是否需要消行
			t_put_score();//
			t_over();//用来判断游戏是否结束
			t_clear_next();//把右边画出的下一个方块清除
			t_form_shape_now(90, 0);//就是把生成的下一个方块赋给现在
			t_form_shape_next();//形成下一个方块

		}

		int t = (int)time(0);//系统函数，取当前系统时间（从1970-01-01 00:00:00开始的秒数）
		t_record_time(t);//记录下此时结束的时间

		// 一局结束后的统计
		t_end_clear();//清除屏幕上现在显示的方块
		t_save_try(score);//把这一次的成绩写进存档

		t_paixu_spe();//把过去的成绩和现在的成绩一起进行排序
		//弹窗
		
	    if (score <= 1000) {
			swprintf(over_tips, 39, L"您的最终得分：%d\n想再认真来一局吗？", score);//弹窗吗？？
			if (MessageBox(GetHWnd(), over_tips, L"这不会是你的真实水平吧？", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
		else if (score > 1000 && score < 3000) {
			swprintf(over_tips, 39, L"\n您的最终得分：%d\n还不快去学习？", score);//弹窗吗？？
			if (MessageBox(GetHWnd(), over_tips, L"打算去学习了吗？", MB_ICONQUESTION | MB_YESNO) == IDYES)
				break;
		}
		else if (score >= 3000) {
			swprintf(over_tips, 39, L"不愧是你，你这巨佬！\n大佬的最终得分：%d\n再来一局吗？", score);//弹窗吗？？
			if (MessageBox(GetHWnd(), over_tips, L"My dear dalao,please daidai wo!!!", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;

		}
	}
	return;
}
