/*2051498 信12 储岱泽*/
#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include <ctime>
#include<iostream>
#include<fstream>
#include "颜色头文件.h"
using namespace std;

#define FORWARD 0//没有键盘的指示就向前走
#define DOWN 1//收到'k'的指令向下走
#define LEFT 2//收到'j'的指令向左走
#define RIGHT 3//收到'l'的指令向右走
#define UP 4//收到‘i'的指令向上走
#define STOP 5//按空格暂停游戏
#define N 500//食物形成的最多数量
#define COLOR_NUM 25//颜色的数量
#define POISON_NUM 100//毒药形成最多的数量
#define INITSPEED 90
const int radius = 10;

const int COLOR_GROUPS[COLOR_NUM] = { COLOR1, COLOR2, COLOR3, COLOR4, COLOR5,
									  COLOR1_r, COLOR2_r, COLOR3_r, COLOR4_r, COLOR5_r,
									  COLOR1_p, COLOR2_p, COLOR3_p, COLOR4_p, COLOR5_p,
									  COLOR1_b, COLOR2_b, COLOR3_b, COLOR4_b, COLOR5_b,
									  COLOR1_g, COLOR2_g, COLOR3_g, COLOR4_g, COLOR5_g };
DWORD s_time_now = 0;

struct SNAKE {
	int lenth = 0;//蛇蛇的长度
	int color = 0;//蛇蛇的颜色
	int X = 0;//蛇头的横坐标
	int Y = 0;//蛇头的纵坐标
	int X_tail = 0;//此时蛇尾的横坐标
	int Y_tail = 0;//此时蛇尾的纵坐标
	int status = 0;//运动的状态此时
};
struct FOOD {
	int x = 0;//这个表示的是食物在map_snake[40][40]数组中对应的数组下标的x
	int y = 0;//这个表示的是食物在map_snake[40][40]数组中对应的数组下标的y
	int X = 0;//这个表示的是食物产生的地方在游戏界面上的坐标X
	int Y = 0;//这个表示的是食物产生的地方在游戏界面上的坐标Y
	int color = 0;//食物的颜色
	int flag = 0;//用于判断其是否已经被吃掉
	int able = 0;//已经有了被吃掉的权利
};
struct POISON {//毒药
	int x = 0;
	int y = 0;
	int X = 0;
	int Y = 0;
	int color = 0;
	int flag = 0;//用于判断其是否已经被吃掉
	int able = 0;//已经有了被吃掉的权利
};
struct S_TIME {
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
S_TIME play_time = { 0 };//用来记录这一次的时间
struct S_HISTORY {
	int score = 0;//历史记录的成绩，后面显示排行榜的时候，需要根据这个来进行一个排序
	//历史玩这个游戏的时间
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
S_HISTORY history[100] = { 0 };//可以最多存储过去100次的一个得分的情况


SNAKE snake = { 3,COLOR1,60,40,20,40,RIGHT };//初始化蛇蛇
FOOD food[N] = { 0 };
POISON poison[POISON_NUM] = { 0 };

extern char name[15];//用户要输入的名字
extern char tname[15];
extern char sname[15];

//这两项表示的是数组下标
int s_map_x = 3;
int s_map_y = 1;//表示蛇头的数组下标
int map_tail_x = 1;
int map_tail_y = 1;//表示蛇尾的数组下标
//用于判断游戏是否结束
int s_judge_end = 0;
//用于记录蛇身现在的位置，其目的是为了清除蛇尾
int map_snake[40][40] = { 0 };
int head = 0;

int s_score = 5;
//判断食物有没有被吃完
int judge_if_eat = 0;

//判断是不是撞墙死
int die_of_wall = 0;
//判断是不是自己咬了自己而死
int die_of_bite = 0;
//判断是不是吃了毒药死的
int die_of_poison = 0;

wchar_t s_score_tips[50];
wchar_t s_over_tips[50];
wchar_t s_score_highest[50];

int food_num = 4;//显示的可以吃的食物的数量
int poison_num = 1;//显示已经被打印出来的毒药的数量
int speed_num = INITSPEED;

int spe = 100;
int s_score_former[800] = { 0 };//这里面存放的是过去一百次的得分并且进行一个排名


void s_react_if_former_right(int commend);
void s_react_if_former_left(int commend);
void s_react_if_former_up(int commend);
void s_react_if_former_down(int commend);
void s_print_food();
void s_print_poison();
void s_cleartails();

//将坐标变成数组下标
void s_trans_array(int X, int Y, int& x, int& y)
{
	x = X / 20;
	y = (Y - 20) / 20;
}
//将数组下标变成坐标
void s_trans_position(int x, int y, int& X, int& Y)
{
	X = 20 * x;
	Y = 20 + 20 * y;
}
void s_form_food_groups()
{
	int suc = 1;
	int color = 0;
	for (int i = 0; i < N; i++) {
		suc = 1;
		while (1) {
			food[i].x = 0;
			food[i].y = 0;
			suc = 1;
			while (food[i].x < 3 || food[i].x>35) {
				food[i].x = rand() % 38;
			}
			while (food[i].y < 3 || food[i].y>35) {
				food[i].y = rand() % 38;
			}
			if (i > 0) {
				for (int j = 0; j < i; j++) {//保证生成的位置和前面没有重复的
					if (food[i].x == food[j].x && food[i].y == food[j].y) {//有重复的，说明生成不成功
						suc = 0;
						break;
					}
				}
			}
			if (suc)
				break;
		}
		color = rand() % COLOR_NUM;
		food[i].color = COLOR_GROUPS[color];
		food[i].flag = 0;//默认此时还没有被吃
	}
	s_print_food();
}
void s_form_poison_groups()
{
	int suc = 1;
	int color = 0;
	for (int i = 0; i < POISON_NUM; i++) {
		suc = 1;
		while (1) {
			poison[i].x = 0;
			poison[i].y = 0;
			suc = 1;
			while (poison[i].x < 3 || poison[i].x>35) {
				poison[i].x = rand() % 38;
			}
			while (poison[i].y < 3 || poison[i].y>35) {
				poison[i].y = rand() % 38;
			}
			if (i > 0) {
				for (int j = 0; j < i; j++) {//保证生成的位置和前面没有重复的
					if (poison[i].x == poison[j].x && poison[i].y == poison[j].y) {//有重复的，说明生成不成功
						suc = 0;
						break;
					}
				}
			}
			if (suc)
				break;
		}
		color = rand() % COLOR_NUM;
		poison[i].color = COLOR_GROUPS[color];
		poison[i].flag = 0;//默认此时还没有被吃
	}
	s_print_poison();
}
void s_print_poison()
{
	for (int i = 0; i < poison_num; i++) {
		if (poison[i].flag == 0) {//没有被吃掉就画出来
			poison[i].able = 1;//此时他被画出来了，说明他可以被吃掉毒死蛇蛇了
			s_trans_position(poison[i].x, poison[i].y, poison[i].X, poison[i].Y);//把食物的数组下标转换成横纵坐标
			setfillcolor(poison[i].color);
			solidrectangle(poison[i].X - 5, poison[i].Y - 5, poison[i].X + 5, poison[i].Y + 5);//打印出毒药，是一个正方形
		}
	}

}
void s_print_food()
{
	for (int i = 0; i < food_num; i++) {
		if (food[i].flag == 0) {//没有被吃掉就画出来
			food[i].able = 1;//此时他被画出来了，说明他可以被吃掉算分了
			s_trans_position(food[i].x, food[i].y, food[i].X, food[i].Y);//把食物的数组下标转换成横纵坐标
			setfillcolor(food[i].color);
			solidcircle(food[i].X, food[i].Y, 6);
		}
	}
}

void s_initsnake()
{
	snake.lenth = 3;
	snake.status = RIGHT;
	snake.X = 60;
	snake.Y = 40;
	snake.X_tail = 20;
	snake.Y_tail = 40;
	int c = rand() % COLOR_NUM;
	snake.color = COLOR_GROUPS[c];//产生蛇蛇的颜色
	//画出最初的蛇
	setfillcolor(snake.color);
	solidcircle(20, 40, 10);
	solidcircle(40, 40, 10);
	solidcircle(60, 40, 10);
	//这样就把地图数组最初的情况赋值好了，接下来只需要不断的改变蛇头的位置和蛇尾的位置即可
	map_snake[1][1] = 0;
	map_snake[1][2] = 1;
	map_snake[1][3] = 2;
	head = 2;
	map_tail_x = 1;
	map_tail_y = 1;//初始时蛇尾数组的下标

}
void s_initscreen()
{
	//设置背景颜色为白色
	initgraph(780, 800);
	setbkcolor(WHITE);
	cleardevice();
	//画出初始横线
	setlinecolor(RGB(136, 136, 127));
	line(9, 30 - 1, 771, 30 - 1);
	line(9, 790 + 1, 9, 30 - 1);
	line(771, 30 - 1, 771, 790 + 1);
	line(9, 790 + 1, 771, 790 + 1);
	//改变窗口标题名字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"贪吃蛇");
	// 绘图模式设置
	setbkmode(TRANSPARENT);
	// 随机数种子
	srand(time(NULL));
	//形成食物
	//form_food();
}
void s_initscreenstart()
{
	//先设置背景颜色是白色
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(40, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(120, 150, L"SNAKE");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 - 3, 150 + 40, 240 + 3, 150 + 40 + 10);

	settextstyle(15, 0, L"verdana");
	outtextxy(150, 150 + 40 + 10 + 10, L"Loading...");

	for (int i = 0; i < 5; i++) {
		setfillcolor(RGB(45, 84, 117));
		solidrectangle(120 + 24 * i, 150 + 40 + 2, 120 + 24 * i + 22, 150 + 40 + 2 + 6);
		Sleep(1000);
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

int s_cmd()
{
	while (1) {
		// 如果长时间没有指令的话，就向下走
		DWORD time_tmp = GetTickCount();
		if (time_tmp - s_time_now >= spe)
		{
			s_time_now = time_tmp;
			return FORWARD;
		}
		// 接受指令
		if (_kbhit()) {
			switch (_getch()) {
				case 'i':
					return UP;
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
		Sleep(10);//决定了运动的速度
	}
}
void s_reaction(int commend)//反应
{
	if (commend != FORWARD && commend != STOP) {//如果此时的指令不是向前走的话
		switch (snake.status) {//根据此时蛇蛇的状态来决定根据我键盘的选择应该怎么走
			case RIGHT://如果此时的蛇蛇是向右走的
				s_react_if_former_right(commend);
				break;
			case LEFT:
				s_react_if_former_left(commend);
				break;
			case UP:
				s_react_if_former_up(commend);
				break;
			case DOWN:
				s_react_if_former_down(commend);
				break;
		}
	}
	else if (commend == FORWARD) {//如果此时的指令是向前运动
		switch (snake.status) {//根据此时蛇蛇的状态来决定根据我键盘的选择应该怎么走
			case RIGHT://如果此时的蛇蛇是向右走的
				snake.X += 20;
				break;
			case LEFT:
				snake.X -= 20;
				break;
			case UP:
				snake.Y -= 20;
				break;
			case DOWN:
				snake.Y += 20;
				break;
		}
	}
	else if (commend == STOP) {
		int m = 0;
		while (m != ' ') {
			m = _getch();
		}

		switch (snake.status) {//根据此时蛇蛇的状态来决定根据我键盘的选择应该怎么走
			case RIGHT://如果此时的蛇蛇是向右走的
				snake.X += 20;
				break;
			case LEFT:
				snake.X -= 20;
				break;
			case UP:
				snake.Y -= 20;
				break;
			case DOWN:
				snake.Y += 20;
				break;
		}
	}

	s_trans_array(snake.X, snake.Y, s_map_x, s_map_y);
	if (s_map_x >= 1 && s_map_x <= 37 && s_map_y >= 1 && s_map_y <= 37) {
		map_snake[s_map_y][s_map_x] = head + 1;
		head++;
	}
	else {//就是撞墙了
		die_of_wall = 1;
		s_judge_end = 1;
	}

}
void s_react_if_former_right(int commend)//如果此时的蛇蛇是向右走的
{
	if (commend == LEFT)
		snake.X += 20;//运动加速
	else if (commend == RIGHT)
		snake.X += 20;//运动加速
	else if (commend == UP) {//当然还需要判断是否有up的能力(好像不用）
		snake.status = UP;
		snake.Y -= 20;
	}
	else if (commend == DOWN) {
		snake.status = DOWN;
		snake.Y += 20;
	}
}
void s_react_if_former_left(int commend)//如果此时的蛇蛇是向左走的
{
	if (commend == LEFT)
		snake.X -= 20;//向左加速
	else if (commend == RIGHT)
		snake.X -= 20;//向左加速
	else if (commend == UP) {//当然还需要判断是否有up的能力(好像不用）
		snake.status = UP;
		snake.Y -= 20;
	}
	else if (commend == DOWN) {
		snake.status = DOWN;
		snake.Y += 20;
	}
}
void s_react_if_former_up(int commend)//如果此时的蛇蛇是向上走的
{
	if (commend == LEFT) {
		snake.status = LEFT;
		snake.X -= 20;
	}
	else if (commend == RIGHT) {
		snake.status = RIGHT;
		snake.X += 20;
	}
	else if (commend == UP) {//当然还需要判断是否有up的能力(好像不用）
		snake.Y -= 20;
	}
	else if (commend == DOWN)
		snake.Y -= 20;
}
void s_react_if_former_down(int commend)//如果此时的蛇蛇是向下走的
{
	if (commend == LEFT) {
		snake.status = LEFT;
		snake.X -= 20;
	}
	else if (commend == RIGHT) {
		snake.status = RIGHT;
		snake.X += 20;
	}
	else if (commend == UP) //当然还需要判断是否有up的能力(好像不用）
		snake.Y += 20;
	else if (commend == DOWN) {
		snake.Y += 20;
	}
}
void s_put_score() {
	setfillcolor(WHITE);
	solidrectangle(290 - 20, 5, 400, 20);

	setfillcolor(RGB(136, 136, 127));
	solidrectangle(405 - 20, 10, 415 - 20, 20);
	solidcircle(430 + 50 - 20, 15, 5);

	settextcolor(RGB(136, 136, 127));
	settextstyle(15, 0, L"楷体");
	swprintf(s_score_tips, 29, L"Score：%d", s_score);//这一句话学着点
	outtextxy(300 - 20, 10, s_score_tips);


	settextstyle(15, 0, L"楷体");
	outtextxy(418 - 20, 10, L"Poison");
	outtextxy(440 + 50 - 20, 10, L"Food");
	outtextxy(440 + 50 + 30, 10, L"j: left  k:down  l:right  i:up");


}

//用于清除蛇尾，改变蛇尾的坐标，具体就是寻找周围比他大1的值
void s_cleartails()
{
	int right = 0, left = 0, up = 0, down = 0;//这四个方向用来检测该位置上下左右是否有1
	if (map_snake[map_tail_y][map_tail_x + 1] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		right = 1;//如果满足右边的值比左边的值大1，那么就说明擦去此时的之后，tail的值就会变成右边的那一个
	}
	else if (map_snake[map_tail_y][map_tail_x - 1] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		left = 1;//如果满足左边的值比此时的tail大1，那么就说明擦去此时的之后，tail就变成了左边那一个
	}
	else if (map_snake[map_tail_y + 1][map_tail_x] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		down = 1;//如果满足下边的值比此时的tail大1，那么就说明擦去此时的之后，tail就变成了下边那一个
	}
	else if (map_snake[map_tail_y - 1][map_tail_x] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		up = 1;//如果满足上边的值比此时的tail大1，那么就说明擦去此时的之后，tail就变成了上边那一个
	}

	if (right) {
		map_tail_x++;
	}
	else if (left) {
		map_tail_x--;
	}
	else if (down) {
		map_tail_y++;
	}
	else if (up) {
		map_tail_y--;
	}
	s_trans_position(map_tail_x, map_tail_y, snake.X_tail, snake.Y_tail);//把此时的数组下标变成坐标
}
void s_add_head()
{//首先要改变头的坐标，还要打印出现在的头
	setfillcolor(snake.color);//用蛇蛇自身的颜色来打印头
	switch (snake.status) {
		case UP:
			snake.Y -= 40;
		case DOWN:
			snake.Y += 20;
			snake.X -= 20;
		case RIGHT:
			snake.X += 40;
		case LEFT:
			snake.X -= 20;
	}

	solidcircle(snake.X, snake.Y, radius);//画出新增的蛇头
	s_trans_array(snake.X, snake.Y, s_map_x, s_map_y);
	map_snake[s_map_y][s_map_x] = head + 1;
	head++;
}
void s_judge_eat()//何为吃到食物，所谓的吃到食物，就是此时的蛇头和食物的横纵坐标相等，吃到食物后打印两次蛇头达到增长的目的
{
	for (int i = 0; i < food_num; i++) {
		if (snake.X == food[i].X && snake.Y == food[i].Y && food[i].able == 1 && food[i].flag == 0) {
			clearcircle(food[i].X, food[i].Y, 6);//清除食物
			snake.lenth++;//变长
			s_score += 25;
			s_add_head();
			food[i].flag = 1;//表示被吃掉了
			food[i].able = 0;//既然已经被吃掉了，就没有被吃第二次的权利了
			snake.color = food[i].color;
		}
	}

	for (int i = 0; i < poison_num; i++) {
		if (snake.X == poison[i].X && snake.Y == poison[i].Y && poison[i].able == 1 && poison[i].flag == 0) {
			s_judge_end = 1;
			die_of_poison = 1;
		}
	}
}
void s_judge_eat_self()
{
	int no_zero = 0;//数蛇头前后左右非零的个数
	if (map_snake[s_map_y][s_map_x + 1] != 0)
		no_zero++;
	if (map_snake[s_map_y][s_map_x - 1] != 0)
		no_zero++;
	if (map_snake[s_map_y - 1][s_map_x] != 0)
		no_zero++;
	if (map_snake[s_map_y + 1][s_map_x] != 0)
		no_zero++;

	if (no_zero >= 3 || (s_map_y == map_tail_y && s_map_x == map_tail_x)) {//此时说明自己咬到了自己
        s_judge_end = 1;
		die_of_bite = 1;
	}
}
void s_move()//就是不断的在蛇头打印一个圈圈然后在蛇尾擦掉一个圈圈
{
	int commend = 0;//用于接收指令
	int count = 0;
	while (!s_judge_end) {
		if (count % 20 == 0) {
			food_num++;
		}
		if (count % 60 == 0) {
			poison_num++;
		}
		if (count % 300 == 0 && spe >= 10) {
			spe -= 10;
		}
		s_print_food();
		s_print_poison();
		commend = s_cmd();//接受指令
		s_reaction(commend);//接受指令之后进行反应
		setfillcolor(snake.color);
		solidcircle(snake.X, snake.Y, radius);
		clearcircle(snake.X_tail, snake.Y_tail, radius);
		s_print_food();
		s_print_poison();
		s_cleartails();
		s_judge_eat();//判断一下是否吃到了食物或者是毒药
		s_put_score();//显示得分
		s_judge_eat_self();
		count++;
	}
}
void s_guiling()
{
	die_of_poison = 0;
	die_of_bite = 0;
	die_of_wall = 0;
	judge_if_eat = 0;
	s_score = 5;
	head = 0;
	s_judge_end = 0;
	s_map_x = 3;
	s_map_y = 1;//表示蛇头的数组下标
	map_tail_x = 1;
	map_tail_y = 1;//表示蛇尾的数组下标
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			map_snake[i][j] = 0;
		}
	}
	food_num = 4;//显示的可以吃的食物的数量
	poison_num = 1;//显示已经被打印出来的毒药的数量
	speed_num = 2;
	spe = INITSPEED;

}

void s_record_time(const time_t input_time)
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
	play_time.second = tt->tm_sec;
}

void s_save_try(int score)
{
	fstream fw;

	fw.open(sname, ios::app);//在文档后面追加
	fw << score << ' '
		<< play_time.year << ' ' << play_time.month << ' ' << play_time.day
		<< ' ' << play_time.hour << ' ' << play_time.minute << ' ' << play_time.second << ' ';//然后写进该用户这一次的成绩，之后在记录下此次玩耍的时间
	fw.close();//可以正常存储了
}
void s_paixu_spe() {
	fstream fr;
	fr.open(sname, ios::in);//把文件中的东西输入到变量数组中
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

void s_put_highst()
{
	settextcolor(RGB(136, 136, 127));
	settextstyle(15, 0, L"楷体");
	swprintf(s_score_highest, 29, L"Highest Score：%d", history[0].score);//这一句话学着点
	outtextxy(300 - 200 - 20, 10, s_score_highest);
}
void SnakeGame()
{
	fstream fw;
	//fw.open("s_result.txt", ios::app);//在还没有建立这个文档的时候先建立这个文档，以防止下面读取的时候因为找不到文档而发生错误
	fw.open(sname, ios::app); 
	fw.close();//建立好了这个文档之后就关闭它
	//cout << sname << endl;//看一下全局的name对不对
	//s_initscreenstart();
	int t =0;//系统函数，取当前系统时间（从1970-01-01 00:00:00开始的秒数）

	while (1) {
		s_initscreen();//先初始化界面
		s_paixu_spe();//把过去的成绩和现在的成绩一起进行排序

		s_put_highst();

		s_guiling();
		s_initsnake();//初始化蛇蛇
		s_form_food_groups();//初始化食物信息
		s_form_poison_groups();//初始化毒药的信息
		s_move();
		
		t = (int)time(0);
		s_record_time(t);
		
		s_save_try(s_score);//把这一次的成绩写进存档
		s_paixu_spe();//把过去的成绩和现在的成绩一起进行排序
		
		if (die_of_bite) {
			swprintf(s_over_tips, 39, L"您的最终得分：%d\n自己咬到自己啦！呜呜呜~~~\n再来一局吗？", s_score);//弹窗吗？？
			if (MessageBox(GetHWnd(), s_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
		else if (die_of_poison) {
			swprintf(s_over_tips, 39, L"\n您的最终得分：%d\n蛇蛇中毒了，呜呜呜~~~\n再来一局吗？", s_score);//弹窗吗？？
			if (MessageBox(GetHWnd(), s_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
		else if (die_of_wall) {
			swprintf(s_over_tips, 39, L"大佬的最终得分：%d\n蛇蛇撞墙啦，呜呜呜~~~\n再来一局吗？", s_score);//弹窗吗？？
			if (MessageBox(GetHWnd(), s_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
	}
	return;
}