/*2051498 ��12 �����*/
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <fstream>
#include "����˹����ͷ�ļ�.h"
#include "��ɫͷ�ļ�.h"
using namespace std;
DWORD t_time_now;
extern char name[15];//�û�Ҫ���������
extern char tname[15];
extern char sname[15];

int color[5] = { 0 };
const int radius = 10;//ԲȦ�İ뾶
//����Ԫ��ԲȦ�İ뾶Ϊ10
//��һ���ṹ�嶨�����ÿһ�ֻ���ͼ�εĻ�����Ϣ
struct CIRCLE {
	int x, y;
};
struct CIRCLE_GROUP {
	CIRCLE rotation_status[4][4];//��¼����״��ÿһ����ת��״̬
};
struct SHAPE {//�����涨����Ǵ�ʱ���ֵ�ͼ��
	CIRCLE circle_group[4] = { 0 };//ÿһ������ͼ�ζ������ĸ�������Բ��ɵģ����ﶨ�����ĸ�Բ�Ļ�����������Ϣ
	int shape = 0;//��¼��ԲȦ��������һ��ͼ��
	int rotation_status = 0;//��ת��״̬
	int color = 0;//��ɫ
};
CIRCLE_GROUP shan_group = {
		{{{0,0},{20,0},{20,-20},{40,0}},//δ������ת��״̬
		{{20,0},{0,0},{0,-20},{0,20}},//˳ʱ��ת��90�ȵ�״̬
		{{0,0},{20,0},{20,20},{40,0}},//˳ʱ��ת��180�ȵ�״̬
		{{0,0},{20,20},{20,0},{20,-20}}//˳ʱ��ת��270�ȵ�״̬
	} };
CIRCLE_GROUP tian_group = {
		{{{0,0},{0,-20},{20,-20},{20,0}},//δ������ת��״̬
		{{0,0},{0,-20},{20,-20},{20,0}},//˳ʱ��ת��90�ȵ�״̬
		{{0,0},{0,-20},{20,-20},{20,0}},//˳ʱ��ת��180�ȵ�״̬
		{{0,0},{0,-20},{20,-20},{20,0}}//˳ʱ��ת��270�ȵ�״̬
	} };
CIRCLE_GROUP yi_group = {
		{{{0,0},{0,-20},{0,-40},{0,-60}},//δ������ת��״̬
		{{0,0},{20,0},{40,0},{60,0}},//˳ʱ��ת��90�ȵ�״̬
		{{0,0},{0,-20},{0,-40},{0,-60}},//˳ʱ��ת��180�ȵ�״̬
		{{0,0},{20,0},{40,0},{60,0}}//˳ʱ��ת��270�ȵ�״̬
	} };
CIRCLE_GROUP trans_L_group = {
		{{{0,0},{20,0},{20,-20},{20,-40}},//δ������ת��״̬
		{{0,0},{20,0},{40,0},{0,-20}},//˳ʱ��ת��90�ȵ�״̬
		{{0,0},{0,-20},{0,-40},{20,-40}},//˳ʱ��ת��180�ȵ�״̬
		{{0,-20},{20,-20},{40,-20},{40,0}}//˳ʱ��ת��270�ȵ�״̬
	} };
CIRCLE_GROUP L_group = {
		{{{0,0},{0,-20},{0,-40},{20,0}},//δ������ת��״̬
		{{0,0},{0,-20},{20,-20},{40,-20}},//˳ʱ��ת��90�ȵ�״̬
		{{0,-40},{20,-40},{20,-20},{20,0}},//˳ʱ��ת��180�ȵ�״̬
		{{0,0},{20,0},{40,0},{40,-20}}//˳ʱ��ת��270�ȵ�״̬
	} };
CIRCLE_GROUP trans_Z_group = {
		{{{0,-20},{20,-20},{20,0},{40,0}},//δ������ת��״̬
		{{0,0},{0,-20},{20,-20},{20,-40}},//˳ʱ��ת��90�ȵ�״̬
		{{0,-20},{20,-20},{20,0},{40,0}},//˳ʱ��ת��180�ȵ�״̬
		{{0,0},{0,-20},{20,-20},{20,-40}}//˳ʱ��ת��270�ȵ�״̬
	} };
CIRCLE_GROUP Z_group = {
		{{{20,-20},{20,-40},{40,0},{40,-20}},//δ������ת��״̬
		{{0,0},{20,0},{20,-20},{40,-20}},//˳ʱ��ת��90�ȵ�״̬
		{{20,-20},{20,-40},{40,0},{40,-20}},//˳ʱ��ת��180�ȵ�״̬
		{{0,0},{20,0},{20,-20},{40,-20}}//˳ʱ��ת��270�ȵ�״̬
	} };
//���Ǽ��ֻ���ͼ�Σ��Լ����ǵ���ת���������

CIRCLE_GROUP shape_groups[7] = { shan_group ,tian_group ,yi_group,trans_L_group ,L_group,trans_Z_group,Z_group };
SHAPE choice_shape;//����һ����ʱ������ɵ�ͼ��
SHAPE next_shape;//������һ�����ɵķ���
SHAPE former_shape;//����һ����ʱ������ɵ�ͼ��

struct TIME {
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
TIME play_time = { 0 };//������¼��һ�ε�ʱ��
struct T_HISTORY {
	int score = 0;//��ʷ��¼�ĳɼ���������ʾ���а��ʱ����Ҫ�������������һ������
	//��ʷ�������Ϸ��ʱ��
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
T_HISTORY history[100] = { 0 };//�������洢��ȥ100�ε�һ���÷ֵ����

int record_position_still[16][11] = { 0 };//������¼��Щλ�ô�ʱ���Ѿ�ͣ������С����
int record_position_color[16][11] = { 0 };//������¼��Щλ�ô�ʱ���Ѿ�ͣ������С�������ɫ
int record_position_still_copy[16][11] = { 0 };//������¼��Щλ�ô�ʱ���Ѿ�ͣ������С����
int record_position_color_copy[16][11] = { 0 };//������¼��Щλ�ô�ʱ���Ѿ�ͣ������С�������ɫ
int record_drop_position[2] = { 0 };

int score = 0;//������¼����
int judge_over = 0;//�����ж���Ϸ�Ƿ����
int judge_stop = 0;//�����жϴ�ʱ����������Ƿ񴥽���Ҫֹͣ����

int rotation_now = 0;
int rotation_next = 0;

int shape_now = 0;
int shape_next = 0;

int judge_bottom = 0;//�����ж��Ƿ��Ѿ�������

int trans_x = 0;//������ʾ������±꣬��Բ������ת��������
int trans_y = 0;//������ʾ������±꣬��Բ������ת��������

int count_round = 0;
int clean = 1;//һ��ʼ������Ҫ���е�

wchar_t over_tips[50];
wchar_t score_tips[50];
wchar_t score_highest[50];

int color_theme_former = 0;
int color_shape_former = 0;

int score_former[100] = { 0 };//�������ŵ��ǹ�ȥһ�ٴεĵ÷ֲ��ҽ���һ������

const int color_groups_tetris[4][5] = {
	{COLOR1_p ,COLOR2_p, COLOR3_p,COLOR4_p, COLOR5_p },
	{COLOR1_r ,COLOR2_r, COLOR3_r,COLOR4_r, COLOR5_r },
	{COLOR1_g ,COLOR2_g, COLOR3_g,COLOR4_g, COLOR5_g },
	{COLOR1_b ,COLOR2_b, COLOR3_b,COLOR4_b, COLOR5_b }
};//�Զ������ɫ����

void t_initscreen()
{

	//���ñ�����ɫΪ��ɫ
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	//����
	setlinecolor(RGB(138, 163, 183));
	line(221, 0, 221, 331);
	line(19, 0, 19, 331);
	line(19, 331, 221, 331);

	//�ı䴰�ڱ�������
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"����˹ȦȦ");
	// ��ͼģʽ����
	setbkmode(TRANSPARENT);
	// ���������
	srand(time(NULL));

	//������Ϸ����
	//������ʾ��һ�����������
	line(229, 49, 329, 49);
	line(229, 49, 229, 151);
	line(329, 49, 329, 151);
	line(229, 151, 329, 151);

	settextcolor(COLOR4_r);
	settextstyle(12, 0, L"����");
	swprintf(score_highest, 29, L"��ʷ��ߣ�%d",history[0].score);//��һ�仰ѧ�ŵ�
	outtextxy(229, 49 - 30 - 15, score_highest);
	outtextxy(229, 151 + 10, L"���ո����ͣ");

	settextcolor(RGB(137, 155, 169));
	settextstyle(12, 0, L"����");
	outtextxy(229, 49 - 30, L"��һ��ͼ��");
	outtextxy(229, 151 + 30, L"Сдj <-�����˶�");
	outtextxy(229, 151 + 60, L"Сдl ->�����˶�");
	outtextxy(229, 151 + 90, L"Сдk   ��������");
	outtextxy(229, 151 + 120, L"Сдi   ˳ʱ��ת");

}
void t_initscreenstart()
{
	//�����ñ�����ɫ�ǰ�ɫ
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
void t_pause_screem()
{
	cleardevice();

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(60, 150, L"Put Space To Continue");

	while (_getwch() != ' ');

	cleardevice();//����
	t_initscreen();//���³�ʼ������

	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 10; i++) {
			if (record_position_still[j][i] == 1) {
				setfillcolor(record_position_color[j][i]);
				solidcircle(30 + 20 * i, 30 + 20 * j + 10, radius);
			}
		}
	}//�Ѿ�ֹ����Щ���鲹����ȥ
	return;

}
void t_put_score() {
	setfillcolor(WHITE);
	solidrectangle(229, 151 + 120 + 30, 340, 340);

	settextcolor(COLOR4_r);
	settextstyle(15, 0, L"����");
	swprintf(score_tips, 29, L"�÷֣�%d", score);//��һ�仰ѧ�ŵ�
	outtextxy(229, 151 + 120 + 40, score_tips);

}
void t_form_theme_color()
{
	int color_choice = 0;
	while (1) {
		color_choice = rand() % 4;
		if (color_choice != color_theme_former)
			break;//������֤ÿһ�����ɵ�����һ�β�һ��
	}
	for (int i = 0; i < 5; i++) {
		color[i] = color_groups_tetris[color_choice][i];
	}
	color_choice = color_theme_former;
}
//�ú���������������������һ������˹����,����������ɵ�����ֵ����¼shape�Ľṹ��
void t_trans(int& trans_x, int& trans_y, int X, int Y, int i)
{
	int x = 0, y = 0;
	x = X + choice_shape.circle_group[i].x;
	y = Y + choice_shape.circle_group[i].y;//��ʱÿһ������ʵ������

	trans_x = (x - 30) / 20;
	trans_y = (y - 30) / 20;//��Ӧ�ŵ�������±�

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
	//��������ɵ���ɫ��ֵ�����ͼ��
	choice_shape.color = next_shape.color;
	rotation_now = rotation_next;
	shape_now = shape_next;
}
//������ǰ������һ��Ҫ�½��ķ���
void t_form_shape_next()
{
	int choice_p = rand() % 7,
		choice_c = 0,//�������һ����ɫ
		choice_r = rand() % 4;//�������һ����ת�Ƕ�

	while (1) {
		choice_c = rand() % 5;
		if (choice_c != color_shape_former)
			break;//������֤ÿһ�����ɵ�����һ�β�һ��
	}

	color_shape_former = choice_c;

	//��������ɵ�ͼ�εĲ���ֵ��ֵ���ö����ͼ��
	for (int w = 0; w < 4; w++) {
		next_shape.circle_group[w].x = shape_groups[choice_p].rotation_status[choice_r][w].x;
		next_shape.circle_group[w].y = shape_groups[choice_p].rotation_status[choice_r][w].y;
	}
	//��������ɵ���ɫ��ֵ�����ͼ��
	next_shape.color = color[choice_c];
	rotation_next = choice_r;
	shape_next = choice_p;
	color_shape_former = choice_c;
}
void t_first_round_shape()
{
	int choice_p = rand() % 7,
		choice_c = rand() % 5,//�������һ����ɫ
		choice_r = rand() % 4;//�������һ����ת�Ƕ�
		//��������ɵ�ͼ�εĲ���ֵ��ֵ���ö����ͼ��
	color_shape_former = choice_c;
	for (int w = 0; w < 4; w++) {
		choice_shape.circle_group[w].x = shape_groups[choice_p].rotation_status[choice_r][w].x;
		choice_shape.circle_group[w].y = shape_groups[choice_p].rotation_status[choice_r][w].y;
	}
	//��������ɵ���ɫ��ֵ�����ͼ��
	choice_shape.color = color[choice_c];
	rotation_now = choice_r;
	shape_now = choice_p;

}
//�ú�������������ָ����λ�û���һ��ָ������״
void t_draw_circle_group(int X, int Y)
{
	setfillcolor(choice_shape.color);
	for (int i = 0; i < 4; i++) {
		solidcircle(X + choice_shape.circle_group[i].x, Y + choice_shape.circle_group[i].y, radius);
	}
	t_mark_position(X, Y);//��������˶�����;�ֹ����
}
//�ú���������ָ��λ�ò�ȥһ��ָ������״
void t_clear_circle_group(int X, int Y)
{
	for (int i = 0; i < 4; i++) {
		clearcircle(X + former_shape.circle_group[i].x, Y + former_shape.circle_group[i].y, radius);
		//record_position_move[former_shape.circle_group[i].x+X][Y + former_shape.circle_group[i].y] = 0;
	}

}
//��(X,Y)�ĵط���ʼ�½�,��speed���ٶ�
//�½���ʲô�ط�ͣ������Ҳ����Ҫ���ĵ�
void t_mark_position(int X, int Y)
{
	judge_bottom = t_bottom(X, Y);
	for (int i = 0; i < 4; i++) {
		t_trans(trans_x, trans_y, X, Y, i);
		//record_position_move[trans_y][trans_x] = 1;//�ڴ�ʱ��Բ��λ�õĶ�Ӧ�ֵΪ1����ʾ��¼�˴�ʱ��λ����Բ��

		if (record_position_still[trans_y + 1][trans_x] == 1 || judge_bottom == 1) {//��������Ǹ���1�Ļ�����ô��˵��Ҫ������
			judge_stop = 1;
			for (int m = 0; m < 4; m++) {
				t_trans(trans_x, trans_y, X, Y, m);
				record_position_still[trans_y][trans_x] = 1;//�ڴ�ʱ��Բ��λ�õĶ�Ӧ�ֵΪ1����ʾ��¼�˴�ʱ��λ����Բ��
				record_position_color[trans_y][trans_x] = choice_shape.color;//�ڴ�ʱ��Բ��λ�õĶ�Ӧ�ֵΪ1����ʾ��¼�˴�ʱ��λ����Բ��
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
		// �����ʱ��û��ָ��Ļ�����������
		DWORD time_tmp = GetTickCount();
		if (time_tmp - t_time_now >= 1000)
		{
			t_time_now = time_tmp;
			return DOWN;
		}
		// ����ָ��
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
	//�����ж��Ƿ�߱������˶����ʸ�
	for (int i = 0; i < 4; i++) {
		judge_border = x + former_shape.circle_group[i].x;//��ʱԲ�ĵĺ�����
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
				judge_border = x + shape_groups[shape_now].rotation_status[rotation_now][i].x;//��ʱԲ�ĵĺ�����
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
			record_drop_position[0] = x;//��ʱ�ĺ�����
			record_drop_position[1] = y;//��ʱ��������
			t_pause_screem();
			t_put_score();//��ӡ��ʱ�ķ���
			t_draw_next();
	}
}
//�������½��������ж��Ƿ��Ѿ�����(����y=310�ĵط�)
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
	while (judge_stop != 1) {//����û�д�����ʱ��
		t_clear_circle_group(x0, y0);
		y0 = y;
		x0 = x;
		t_draw_circle_group(x, y);//������ط����ж��Ƿ񴥽�������
		m = t_bottom(x, y);
		m = t_cmd();//��ü��̵�ָʾ��Ȼ��������Ӧ
		t_react(m, x, y);//��x,y���룬���ݼ��̵�ָ��ı�x,y��ֵ���õ���һ�λ�Բ��λ��
		Sleep(1000 / speed);
	};
	t_form_shape_now(90, 0);
}
//�ú�������������ʼ��
void t_guiling_per()
{
	judge_stop = 0;
	judge_over = 0;
	judge_bottom = 0;
	t_time_now = GetTickCount();//��ʼ��ʱ
	clean = 1;
}
//�ú��������ж��Ƿ��������
void t_cleanner(int hang)//Ҫʵ���½�Ч����ò�Ƹ���֮�ϵ������ж�Ӧ�ñ�����
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
	//ȫ�����������Ժ�Ҫ������ȥ
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
			if (record_position_still[i][j] == 0) {//�����һ����һ��0˵����û��������������
				clean = 0;
			}
		}
		if (clean) {//�����һ�б������������ģ�˵��Ҫ��
			hang = i + 1;//˵���ǵ�i����Ҫ����
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
	t_time_now = GetTickCount();//��ʼ��ʱ
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
//дһ�����԰�����ת�����ַ��ĺ���
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

	fw.open(tname, ios::app);//���ĵ�����׷��
	fw << score << ' '
		<<play_time.year<<' '<< play_time.month<<' '<< play_time.day
		<<' '<< play_time.hour<<' '<< play_time.minute<<' '<< play_time.second<<' ';//Ȼ��д�����û���һ�εĳɼ���֮���ڼ�¼�´˴���ˣ��ʱ��
	fw.close();//���������洢��
}
void t_paixu_spe() {
	fstream fr;
	fr.open(tname, ios::in);//���ļ��еĶ������뵽����������
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

//���ڼ�¼�������Ϸ��ʱ��
void t_record_time(const time_t input_time)
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
	play_time.second=tt->tm_sec;
}
void TetrisGame()
{
	//t_initscreenstart();//��ʼ��������Ļ
	fstream fw;
	fw.open(tname, ios::app);//�ڻ�û�н�������ĵ���ʱ���Ƚ�������ĵ����Է�ֹ�����ȡ��ʱ����Ϊ�Ҳ����ĵ�����������
	fw.close();//������������ĵ�֮��͹ر���
	while (1) {
		t_guiling();//���ݹ���
		t_paixu_spe();//�ѹ�ȥ�ĳɼ������ڵĳɼ�һ���������
		t_initscreen();//��ʼ��������Ļ
		t_form_theme_color();
		t_first_round_shape();//�������ɵ�һ�غϵ����ݣ�֮���������ݵķ�ʽ������������һ��ͼ�Σ��ٽ���һ�����ɵ�ͼ�θ������ڵ�
		t_form_shape_next();
		t_paixu_spe();//�ѹ�ȥ�ĳɼ������ڵĳɼ�һ���������
		while (judge_over != 1) {
			t_guiling_per();//���ݹ���
			t_draw_next();//���ұߵĿ���л�����һ���½���ͼ��
			t_put_score();//��ӡ��ʱ�ķ���

			t_shape_drop(90, 40, 10, 290);//�����½�

			t_judge_clean_hang();//�ж��Ƿ���Ҫ����
			t_put_score();//
			t_over();//�����ж���Ϸ�Ƿ����
			t_clear_next();//���ұ߻�������һ���������
			t_form_shape_now(90, 0);//���ǰ����ɵ���һ�����鸳������
			t_form_shape_next();//�γ���һ������

		}

		int t = (int)time(0);//ϵͳ������ȡ��ǰϵͳʱ�䣨��1970-01-01 00:00:00��ʼ��������
		t_record_time(t);//��¼�´�ʱ������ʱ��

		// һ�ֽ������ͳ��
		t_end_clear();//�����Ļ��������ʾ�ķ���
		t_save_try(score);//����һ�εĳɼ�д���浵

		t_paixu_spe();//�ѹ�ȥ�ĳɼ������ڵĳɼ�һ���������
		//����
		
	    if (score <= 1000) {
			swprintf(over_tips, 39, L"�������յ÷֣�%d\n����������һ����", score);//�����𣿣�
			if (MessageBox(GetHWnd(), over_tips, L"�ⲻ���������ʵˮƽ�ɣ�", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;
		}
		else if (score > 1000 && score < 3000) {
			swprintf(over_tips, 39, L"\n�������յ÷֣�%d\n������ȥѧϰ��", score);//�����𣿣�
			if (MessageBox(GetHWnd(), over_tips, L"����ȥѧϰ����", MB_ICONQUESTION | MB_YESNO) == IDYES)
				break;
		}
		else if (score >= 3000) {
			swprintf(over_tips, 39, L"�������㣬������У�\n���е����յ÷֣�%d\n����һ����", score);//�����𣿣�
			if (MessageBox(GetHWnd(), over_tips, L"My dear dalao,please daidai wo!!!", MB_ICONQUESTION | MB_YESNO) == IDNO)
				break;

		}
	}
	return;
}
