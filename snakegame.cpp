/*2051498 ��12 �����*/
#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include <ctime>
#include<iostream>
#include<fstream>
#include "��ɫͷ�ļ�.h"
using namespace std;

#define FORWARD 0//û�м��̵�ָʾ����ǰ��
#define DOWN 1//�յ�'k'��ָ��������
#define LEFT 2//�յ�'j'��ָ��������
#define RIGHT 3//�յ�'l'��ָ��������
#define UP 4//�յ���i'��ָ��������
#define STOP 5//���ո���ͣ��Ϸ
#define N 500//ʳ���γɵ��������
#define COLOR_NUM 25//��ɫ������
#define POISON_NUM 100//��ҩ�γ���������
#define INITSPEED 90
const int radius = 10;

const int COLOR_GROUPS[COLOR_NUM] = { COLOR1, COLOR2, COLOR3, COLOR4, COLOR5,
									  COLOR1_r, COLOR2_r, COLOR3_r, COLOR4_r, COLOR5_r,
									  COLOR1_p, COLOR2_p, COLOR3_p, COLOR4_p, COLOR5_p,
									  COLOR1_b, COLOR2_b, COLOR3_b, COLOR4_b, COLOR5_b,
									  COLOR1_g, COLOR2_g, COLOR3_g, COLOR4_g, COLOR5_g };
DWORD s_time_now = 0;

struct SNAKE {
	int lenth = 0;//���ߵĳ���
	int color = 0;//���ߵ���ɫ
	int X = 0;//��ͷ�ĺ�����
	int Y = 0;//��ͷ��������
	int X_tail = 0;//��ʱ��β�ĺ�����
	int Y_tail = 0;//��ʱ��β��������
	int status = 0;//�˶���״̬��ʱ
};
struct FOOD {
	int x = 0;//�����ʾ����ʳ����map_snake[40][40]�����ж�Ӧ�������±��x
	int y = 0;//�����ʾ����ʳ����map_snake[40][40]�����ж�Ӧ�������±��y
	int X = 0;//�����ʾ����ʳ������ĵط�����Ϸ�����ϵ�����X
	int Y = 0;//�����ʾ����ʳ������ĵط�����Ϸ�����ϵ�����Y
	int color = 0;//ʳ�����ɫ
	int flag = 0;//�����ж����Ƿ��Ѿ����Ե�
	int able = 0;//�Ѿ����˱��Ե���Ȩ��
};
struct POISON {//��ҩ
	int x = 0;
	int y = 0;
	int X = 0;
	int Y = 0;
	int color = 0;
	int flag = 0;//�����ж����Ƿ��Ѿ����Ե�
	int able = 0;//�Ѿ����˱��Ե���Ȩ��
};
struct S_TIME {
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
S_TIME play_time = { 0 };//������¼��һ�ε�ʱ��
struct S_HISTORY {
	int score = 0;//��ʷ��¼�ĳɼ���������ʾ���а��ʱ����Ҫ�������������һ������
	//��ʷ�������Ϸ��ʱ��
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
S_HISTORY history[100] = { 0 };//�������洢��ȥ100�ε�һ���÷ֵ����


SNAKE snake = { 3,COLOR1,60,40,20,40,RIGHT };//��ʼ������
FOOD food[N] = { 0 };
POISON poison[POISON_NUM] = { 0 };

extern char name[15];//�û�Ҫ���������
extern char tname[15];
extern char sname[15];

//�������ʾ���������±�
int s_map_x = 3;
int s_map_y = 1;//��ʾ��ͷ�������±�
int map_tail_x = 1;
int map_tail_y = 1;//��ʾ��β�������±�
//�����ж���Ϸ�Ƿ����
int s_judge_end = 0;
//���ڼ�¼�������ڵ�λ�ã���Ŀ����Ϊ�������β
int map_snake[40][40] = { 0 };
int head = 0;

int s_score = 5;
//�ж�ʳ����û�б�����
int judge_if_eat = 0;

//�ж��ǲ���ײǽ��
int die_of_wall = 0;
//�ж��ǲ����Լ�ҧ���Լ�����
int die_of_bite = 0;
//�ж��ǲ��ǳ��˶�ҩ����
int die_of_poison = 0;

wchar_t s_score_tips[50];
wchar_t s_over_tips[50];
wchar_t s_score_highest[50];

int food_num = 4;//��ʾ�Ŀ��ԳԵ�ʳ�������
int poison_num = 1;//��ʾ�Ѿ�����ӡ�����Ķ�ҩ������
int speed_num = INITSPEED;

int spe = 100;
int s_score_former[800] = { 0 };//�������ŵ��ǹ�ȥһ�ٴεĵ÷ֲ��ҽ���һ������


void s_react_if_former_right(int commend);
void s_react_if_former_left(int commend);
void s_react_if_former_up(int commend);
void s_react_if_former_down(int commend);
void s_print_food();
void s_print_poison();
void s_cleartails();

//�������������±�
void s_trans_array(int X, int Y, int& x, int& y)
{
	x = X / 20;
	y = (Y - 20) / 20;
}
//�������±�������
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
				for (int j = 0; j < i; j++) {//��֤���ɵ�λ�ú�ǰ��û���ظ���
					if (food[i].x == food[j].x && food[i].y == food[j].y) {//���ظ��ģ�˵�����ɲ��ɹ�
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
		food[i].flag = 0;//Ĭ�ϴ�ʱ��û�б���
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
				for (int j = 0; j < i; j++) {//��֤���ɵ�λ�ú�ǰ��û���ظ���
					if (poison[i].x == poison[j].x && poison[i].y == poison[j].y) {//���ظ��ģ�˵�����ɲ��ɹ�
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
		poison[i].flag = 0;//Ĭ�ϴ�ʱ��û�б���
	}
	s_print_poison();
}
void s_print_poison()
{
	for (int i = 0; i < poison_num; i++) {
		if (poison[i].flag == 0) {//û�б��Ե��ͻ�����
			poison[i].able = 1;//��ʱ�����������ˣ�˵�������Ա��Ե�����������
			s_trans_position(poison[i].x, poison[i].y, poison[i].X, poison[i].Y);//��ʳ��������±�ת���ɺ�������
			setfillcolor(poison[i].color);
			solidrectangle(poison[i].X - 5, poison[i].Y - 5, poison[i].X + 5, poison[i].Y + 5);//��ӡ����ҩ����һ��������
		}
	}

}
void s_print_food()
{
	for (int i = 0; i < food_num; i++) {
		if (food[i].flag == 0) {//û�б��Ե��ͻ�����
			food[i].able = 1;//��ʱ�����������ˣ�˵�������Ա��Ե������
			s_trans_position(food[i].x, food[i].y, food[i].X, food[i].Y);//��ʳ��������±�ת���ɺ�������
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
	snake.color = COLOR_GROUPS[c];//�������ߵ���ɫ
	//�����������
	setfillcolor(snake.color);
	solidcircle(20, 40, 10);
	solidcircle(40, 40, 10);
	solidcircle(60, 40, 10);
	//�����Ͱѵ�ͼ��������������ֵ���ˣ�������ֻ��Ҫ���ϵĸı���ͷ��λ�ú���β��λ�ü���
	map_snake[1][1] = 0;
	map_snake[1][2] = 1;
	map_snake[1][3] = 2;
	head = 2;
	map_tail_x = 1;
	map_tail_y = 1;//��ʼʱ��β������±�

}
void s_initscreen()
{
	//���ñ�����ɫΪ��ɫ
	initgraph(780, 800);
	setbkcolor(WHITE);
	cleardevice();
	//������ʼ����
	setlinecolor(RGB(136, 136, 127));
	line(9, 30 - 1, 771, 30 - 1);
	line(9, 790 + 1, 9, 30 - 1);
	line(771, 30 - 1, 771, 790 + 1);
	line(9, 790 + 1, 771, 790 + 1);
	//�ı䴰�ڱ�������
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"̰����");
	// ��ͼģʽ����
	setbkmode(TRANSPARENT);
	// ���������
	srand(time(NULL));
	//�γ�ʳ��
	//form_food();
}
void s_initscreenstart()
{
	//�����ñ�����ɫ�ǰ�ɫ
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
	cleardevice();//����

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(80, 150, L"Created by deidei");

	Sleep(2000);
	cleardevice();//����

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(80, 150, L"Put Enter To Begin");

	while (_getwch() != 13);

	cleardevice();//����
}

int s_cmd()
{
	while (1) {
		// �����ʱ��û��ָ��Ļ�����������
		DWORD time_tmp = GetTickCount();
		if (time_tmp - s_time_now >= spe)
		{
			s_time_now = time_tmp;
			return FORWARD;
		}
		// ����ָ��
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
		Sleep(10);//�������˶����ٶ�
	}
}
void s_reaction(int commend)//��Ӧ
{
	if (commend != FORWARD && commend != STOP) {//�����ʱ��ָ�����ǰ�ߵĻ�
		switch (snake.status) {//���ݴ�ʱ���ߵ�״̬�����������Ҽ��̵�ѡ��Ӧ����ô��
			case RIGHT://�����ʱ�������������ߵ�
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
	else if (commend == FORWARD) {//�����ʱ��ָ������ǰ�˶�
		switch (snake.status) {//���ݴ�ʱ���ߵ�״̬�����������Ҽ��̵�ѡ��Ӧ����ô��
			case RIGHT://�����ʱ�������������ߵ�
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

		switch (snake.status) {//���ݴ�ʱ���ߵ�״̬�����������Ҽ��̵�ѡ��Ӧ����ô��
			case RIGHT://�����ʱ�������������ߵ�
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
	else {//����ײǽ��
		die_of_wall = 1;
		s_judge_end = 1;
	}

}
void s_react_if_former_right(int commend)//�����ʱ�������������ߵ�
{
	if (commend == LEFT)
		snake.X += 20;//�˶�����
	else if (commend == RIGHT)
		snake.X += 20;//�˶�����
	else if (commend == UP) {//��Ȼ����Ҫ�ж��Ƿ���up������(�����ã�
		snake.status = UP;
		snake.Y -= 20;
	}
	else if (commend == DOWN) {
		snake.status = DOWN;
		snake.Y += 20;
	}
}
void s_react_if_former_left(int commend)//�����ʱ�������������ߵ�
{
	if (commend == LEFT)
		snake.X -= 20;//�������
	else if (commend == RIGHT)
		snake.X -= 20;//�������
	else if (commend == UP) {//��Ȼ����Ҫ�ж��Ƿ���up������(�����ã�
		snake.status = UP;
		snake.Y -= 20;
	}
	else if (commend == DOWN) {
		snake.status = DOWN;
		snake.Y += 20;
	}
}
void s_react_if_former_up(int commend)//�����ʱ�������������ߵ�
{
	if (commend == LEFT) {
		snake.status = LEFT;
		snake.X -= 20;
	}
	else if (commend == RIGHT) {
		snake.status = RIGHT;
		snake.X += 20;
	}
	else if (commend == UP) {//��Ȼ����Ҫ�ж��Ƿ���up������(�����ã�
		snake.Y -= 20;
	}
	else if (commend == DOWN)
		snake.Y -= 20;
}
void s_react_if_former_down(int commend)//�����ʱ�������������ߵ�
{
	if (commend == LEFT) {
		snake.status = LEFT;
		snake.X -= 20;
	}
	else if (commend == RIGHT) {
		snake.status = RIGHT;
		snake.X += 20;
	}
	else if (commend == UP) //��Ȼ����Ҫ�ж��Ƿ���up������(�����ã�
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
	settextstyle(15, 0, L"����");
	swprintf(s_score_tips, 29, L"Score��%d", s_score);//��һ�仰ѧ�ŵ�
	outtextxy(300 - 20, 10, s_score_tips);


	settextstyle(15, 0, L"����");
	outtextxy(418 - 20, 10, L"Poison");
	outtextxy(440 + 50 - 20, 10, L"Food");
	outtextxy(440 + 50 + 30, 10, L"j: left  k:down  l:right  i:up");


}

//���������β���ı���β�����꣬�������Ѱ����Χ������1��ֵ
void s_cleartails()
{
	int right = 0, left = 0, up = 0, down = 0;//���ĸ�������������λ�����������Ƿ���1
	if (map_snake[map_tail_y][map_tail_x + 1] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		right = 1;//��������ұߵ�ֵ����ߵ�ֵ��1����ô��˵����ȥ��ʱ��֮��tail��ֵ�ͻ����ұߵ���һ��
	}
	else if (map_snake[map_tail_y][map_tail_x - 1] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		left = 1;//���������ߵ�ֵ�ȴ�ʱ��tail��1����ô��˵����ȥ��ʱ��֮��tail�ͱ���������һ��
	}
	else if (map_snake[map_tail_y + 1][map_tail_x] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		down = 1;//��������±ߵ�ֵ�ȴ�ʱ��tail��1����ô��˵����ȥ��ʱ��֮��tail�ͱ�����±���һ��
	}
	else if (map_snake[map_tail_y - 1][map_tail_x] == map_snake[map_tail_y][map_tail_x] + 1) {
		map_snake[map_tail_y][map_tail_x] = 0;
		up = 1;//��������ϱߵ�ֵ�ȴ�ʱ��tail��1����ô��˵����ȥ��ʱ��֮��tail�ͱ�����ϱ���һ��
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
	s_trans_position(map_tail_x, map_tail_y, snake.X_tail, snake.Y_tail);//�Ѵ�ʱ�������±�������
}
void s_add_head()
{//����Ҫ�ı�ͷ�����꣬��Ҫ��ӡ�����ڵ�ͷ
	setfillcolor(snake.color);//�������������ɫ����ӡͷ
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

	solidcircle(snake.X, snake.Y, radius);//������������ͷ
	s_trans_array(snake.X, snake.Y, s_map_x, s_map_y);
	map_snake[s_map_y][s_map_x] = head + 1;
	head++;
}
void s_judge_eat()//��Ϊ�Ե�ʳ���ν�ĳԵ�ʳ����Ǵ�ʱ����ͷ��ʳ��ĺ���������ȣ��Ե�ʳ����ӡ������ͷ�ﵽ������Ŀ��
{
	for (int i = 0; i < food_num; i++) {
		if (snake.X == food[i].X && snake.Y == food[i].Y && food[i].able == 1 && food[i].flag == 0) {
			clearcircle(food[i].X, food[i].Y, 6);//���ʳ��
			snake.lenth++;//�䳤
			s_score += 25;
			s_add_head();
			food[i].flag = 1;//��ʾ���Ե���
			food[i].able = 0;//��Ȼ�Ѿ����Ե��ˣ���û�б��Եڶ��ε�Ȩ����
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
	int no_zero = 0;//����ͷǰ�����ҷ���ĸ���
	if (map_snake[s_map_y][s_map_x + 1] != 0)
		no_zero++;
	if (map_snake[s_map_y][s_map_x - 1] != 0)
		no_zero++;
	if (map_snake[s_map_y - 1][s_map_x] != 0)
		no_zero++;
	if (map_snake[s_map_y + 1][s_map_x] != 0)
		no_zero++;

	if (no_zero >= 3 || (s_map_y == map_tail_y && s_map_x == map_tail_x)) {//��ʱ˵���Լ�ҧ�����Լ�
        s_judge_end = 1;
		die_of_bite = 1;
	}
}
void s_move()//���ǲ��ϵ�����ͷ��ӡһ��ȦȦȻ������β����һ��ȦȦ
{
	int commend = 0;//���ڽ���ָ��
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
		commend = s_cmd();//����ָ��
		s_reaction(commend);//����ָ��֮����з�Ӧ
		setfillcolor(snake.color);
		solidcircle(snake.X, snake.Y, radius);
		clearcircle(snake.X_tail, snake.Y_tail, radius);
		s_print_food();
		s_print_poison();
		s_cleartails();
		s_judge_eat();//�ж�һ���Ƿ�Ե���ʳ������Ƕ�ҩ
		s_put_score();//��ʾ�÷�
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
	s_map_y = 1;//��ʾ��ͷ�������±�
	map_tail_x = 1;
	map_tail_y = 1;//��ʾ��β�������±�
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			map_snake[i][j] = 0;
		}
	}
	food_num = 4;//��ʾ�Ŀ��ԳԵ�ʳ�������
	poison_num = 1;//��ʾ�Ѿ�����ӡ�����Ķ�ҩ������
	speed_num = 2;
	spe = INITSPEED;

}

void s_record_time(const time_t input_time)
{
	struct tm* tt;	//struct tm Ϊϵͳ����Ľṹ��
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	tt = localtime(&input_time);	//localtimeΪϵͳ����
	/* tm_*** Ϊstruct tm�еĳ�Ա���ͱ����struct tj_time��������ݲ���ȫ���ϣ����庬���Լ������������ */
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

	fw.open(sname, ios::app);//���ĵ�����׷��
	fw << score << ' '
		<< play_time.year << ' ' << play_time.month << ' ' << play_time.day
		<< ' ' << play_time.hour << ' ' << play_time.minute << ' ' << play_time.second << ' ';//Ȼ��д�����û���һ�εĳɼ���֮���ڼ�¼�´˴���ˣ��ʱ��
	fw.close();//���������洢��
}
void s_paixu_spe() {
	fstream fr;
	fr.open(sname, ios::in);//���ļ��еĶ������뵽����������
	int m = 1;
	int i = 0;
	while (1) {
		if (!fr.eof()) {
			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].score = m;

			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].year = m;

			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].month = m;

			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].day = m;

			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].hour = m;

			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].minute = m;

			fr >> m;//�ѹ�ȥ�ĵ÷ֶ���history
			history[i].second = m;
		}
		else
			break;
		i++;//��¼һ�����˼�����ȥ
	}
	if (i >= 1) {
		i -= 1;
		history[i].score = 0;
	}

	//��������ÿһ�ε�score����һ������
	int max = 0, tmp = 0;//�ȼ��������ǵ�һ��
	for (int j = 0; j < i; j++) {
		max = j;
		for (int m = j; history[m].score; m++) {
			if (history[max].score < history[m].score) {
				max = m;
			}
		}//�ҵ�������������������һ��
		if (max != j) {
			tmp = history[j].score;
			history[j].score = history[max].score;
			history[max].score = tmp;
		}
	}//�����ʹӴ�С�ź�����

}

void s_put_highst()
{
	settextcolor(RGB(136, 136, 127));
	settextstyle(15, 0, L"����");
	swprintf(s_score_highest, 29, L"Highest Score��%d", history[0].score);//��һ�仰ѧ�ŵ�
	outtextxy(300 - 200 - 20, 10, s_score_highest);
}
void SnakeGame()
{
	fstream fw;
	//fw.open("s_result.txt", ios::app);//�ڻ�û�н�������ĵ���ʱ���Ƚ�������ĵ����Է�ֹ�����ȡ��ʱ����Ϊ�Ҳ����ĵ�����������
	fw.open(sname, ios::app); 
	fw.close();//������������ĵ�֮��͹ر���
	//cout << sname << endl;//��һ��ȫ�ֵ�name�Բ���
	//s_initscreenstart();
	int t =0;//ϵͳ������ȡ��ǰϵͳʱ�䣨��1970-01-01 00:00:00��ʼ��������

	while (1) {
		s_initscreen();//�ȳ�ʼ������
		s_paixu_spe();//�ѹ�ȥ�ĳɼ������ڵĳɼ�һ���������

		s_put_highst();

		s_guiling();
		s_initsnake();//��ʼ������
		s_form_food_groups();//��ʼ��ʳ����Ϣ
		s_form_poison_groups();//��ʼ����ҩ����Ϣ
		s_move();
		
		t = (int)time(0);
		s_record_time(t);
		
		s_save_try(s_score);//����һ�εĳɼ�д���浵
		s_paixu_spe();//�ѹ�ȥ�ĳɼ������ڵĳɼ�һ���������
		
		if (die_of_bite) {
			swprintf(s_over_tips, 39, L"�������յ÷֣�%d\n�Լ�ҧ���Լ�����������~~~\n����һ����", s_score);//�����𣿣�
			if (MessageBox(GetHWnd(), s_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
		else if (die_of_poison) {
			swprintf(s_over_tips, 39, L"\n�������յ÷֣�%d\n�����ж��ˣ�������~~~\n����һ����", s_score);//�����𣿣�
			if (MessageBox(GetHWnd(), s_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
		else if (die_of_wall) {
			swprintf(s_over_tips, 39, L"���е����յ÷֣�%d\n����ײǽ����������~~~\n����һ����", s_score);//�����𣿣�
			if (MessageBox(GetHWnd(), s_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
	}
	return;
}