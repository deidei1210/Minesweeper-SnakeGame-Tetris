/*2051498 ��12 �����*/
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <fstream>
#include<iostream>
#include "����˹����ͷ�ļ�.h"
#include "��ɫͷ�ļ�.h"
using namespace std;

struct HISTORY {
	int score = 0;//��ʷ��¼�ĳɼ���������ʾ���а��ʱ����Ҫ�������������һ������
	//��ʷ�������Ϸ��ʱ��
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};
HISTORY history[100] = { 0 };//�������洢��ȥ100�ε�һ���÷ֵ����

char name[15] = { 0 };//�û�Ҫ���������
char code[25] = { 0 };//�û�Ҫ���������

char tname[15] = { 0 };
char sname[15] = { 0 };

int score_former_main[100] = { 0 };
int score_former_unranked[100] = { 0 };
int ave = 0;//��ʷ��ƽ����

wchar_t usernames[50];
wchar_t userscores[50];
wchar_t playtime[50];

void initscreenstart()
{
	//�����ñ�����ɫ�ǰ�ɫ
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	//�ı䴰�ڱ�������
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
	cleardevice();//����

	settextstyle(30, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(80, 150, L"Created by deidei");

	Sleep(2000);
	
}
int choose_game()
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();//����
	
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
	cleardevice();//����
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
		namep++;//��ָ��Ų��β���λ��
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
		namep++;//��ָ��Ų��β���λ��
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

void exchange(int &a, int &b)//�������н�a��b����λ��
{
	int tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}
void paixu(int choice) {
	fstream fr;
	if (choice == '1')
		fr.open(tname, ios::in);//��ѡ�����1��ʱ��˵���鿴���Ƕ���˹��������а�
	else if (choice == '2')
		fr.open(sname, ios::in);//��ѡ�����2��ʱ��˵���鿴����̰���ߵ����а�

	int m= 1;
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
	}//�����ʹӴ�С�ź�����

	fr.close();//��ѡ�����2��ʱ��˵���鿴����̰���ߵ����а�
}
int RankingChoice() 
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();//����
	
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
	cleardevice();//����
	return m;

}
void RankScreen(int choice)//��ʾ���а�Ļ�������
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();//����

	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"History");
	settextstyle(35, 0, L"verdana");
	settextcolor(RGB(254, 141, 114));
	if(choice=='1')
	    outtextxy(50, 5, L"History of Tetris");
	else if(choice=='2')
		outtextxy(50, 5, L"History of Snake");

	settextstyle(25, 0, L"verdana");
	outtextxy(10, 45, L"Player");//�������
	outtextxy(130-20, 45, L"Score");//��ҷ���
	outtextxy(250, 45, L"Time");//������ʱ��

	settextstyle(20, 0, L"verdana");
	outtextxy(10, 320, L"<= put'A'");
	outtextxy(260, 320, L"put 'D'=>");//��ҳ�ı�ʶ

	settextstyle(15, 0, L"verdana");
	outtextxy(120, 320, L"put ENTER to return");//��ҳ�ı�ʶ
}
void Rank(int choice)//��ӡ��ʷ��¼��һҳ��ӡʮ����¼
{
	int count = 0;
	int page = 0;
	int page_all = 0;
	int turn = 0;
	for (int c = 0; history[c].score != 0; c++) {
		count++;//������һ����һ��ͳ�Ƶ��˶��ٸ�����
	}
	page_all = count / 10;//��ҳ��
	cout << count << endl;
	while (1) {//count����������ʾ���滹û����ʾ�����ĸ���
		if (count-10<=0) {//����ʮ��������Ҫ��ҳ
			for (int i = page * 10; i < count- page * 10; i++) {
				settextstyle(20, 0, L"verdana");
				settextcolor(RGB(45, 84, 117));

				for (int j = 0; name[j] != '\0'; j++) {
					outtextxy(10 + 10 * j, 65 + 25 * i, name[j]);//��ӡ����
				}
				//swprintf(userscores, 29, L"%d", score_former_unranked[i]);
				swprintf(userscores, 29, L"%d", history[i].score);
				outtextxy(130-20, 65 + 25 * i, userscores);//��ӡ����
				
				swprintf(playtime, 29, L"%d-%d-%d %d:%d:%d", history[i].year, history[i].month, history[i].day, history[i].hour, history[i].minute, history[i].second);
				outtextxy(200-20, 65 + 25 * (i - page * 10), playtime);//��ӡ����


			}
		}
		else if (count - 10 > 0) {//˵����ʱ���Է�ҳ��
			if (page < page_all) {
				for (int i = page * 10; i < page * 10 + 10; i++) {//һҳ��ӡʮ��
					settextstyle(20, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					for (int j = 0; name[j] != '\0'; j++) {
						outtextxy(10 + 10 * j, 65 + 25 * (i - page * 10), name[j]);//��ӡ����
					}
					//swprintf(userscores, 29, L"%d", score_former_unranked[i]);
					swprintf(userscores, 29, L"%d", history[i].score);
					outtextxy(130-20, 65 + 25 * (i - page * 10), userscores);//��ӡ����

					swprintf(playtime, 29, L"%d-%d-%d %d:%d:%d", history[i].year, history[i].month, history[i].day, history[i].hour, history[i].minute, history[i].second);
					outtextxy(200-20, 65 + 25 * (i - page * 10), playtime);//��ӡ����
				}
			}
			else {
				for (int i = page * 10; history[i].score!=0; i++) {//һҳ��ӡʮ��
					settextstyle(20, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					for (int j = 0; name[j] != '\0'; j++) {
						outtextxy(10 + 10 * j, 65 + 25 * (i - page * 10), name[j]);//��ӡ����
					}
					//swprintf(userscores, 29, L"%d", score_former_unranked[i]);
					swprintf(userscores, 29, L"%d", history[i].score);
					outtextxy(130-20, 65 + 25 * (i - page * 10), userscores);//��ӡ����

					swprintf(playtime, 29, L"%d-%d-%d %d:%d:%d", history[i].year, history[i].month, history[i].day, history[i].hour, history[i].minute, history[i].second);
					outtextxy(200-20, 65 + 25 * (i - page * 10), playtime);//��ӡ����

				}

			}
		}
		while (turn != '\n' && turn != '\r' && turn != 'A' && turn != 'D') {
			turn = _getwch();
		}

		if (turn == '\n' || turn == '\r')
			break;
		else if (turn == 'A') {
			if (page > 0) {//��ʱ������ǰ��
				page--;
			}
			RankScreen(choice);
		}
		else if (turn == 'D') {
			if (page < page_all) {//��ʱ��������
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
   initscreenstart();//��ʼ��Ļ������
	SignIn();//��¼����
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
		else if (m == 'q') {//�ǳ����л��û����µ�½
			for (int i = 0; i < 15; i++) {
				name[i] = 0;
			}
			for (int j = 0; j < 15; j++) {
				tname[j] = 0;
				sname[j] = 0;
			}//ȫ�����㣬���µ�½
			for (int m = 0; m < 25; m++) {
				code[m] = 0;
			}

			SignIn();//��¼����
			name_copy();
			t_name();
			s_name();
		}
		else if (m == 'r') {//�鿴���а�
			int choice = 0;
			choice=RankingChoice();//ѡ��鿴��һ�����а�
			if (choice != '0') {
				for (int i = 0; i < 100; i++) {
					score_former_main[i] =0;
					score_former_unranked[i] =0;
				}
				paixu(choice);//�ȶ�ѡ�����һ����Ϸ��������,���ҽ������ķ������Ӵ�С��˳�������former_score����
				RankScreen(choice);
				Rank(choice);
			}
			else
				continue;//����ѡ�����
		}
	}

	closegraph();
	return 0;
}