/*2051498 ����� ��12*/
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <fstream>
#include<cstring>
#include<conio.h>
#include<iostream>
using namespace std;
extern char name[15];//�û�Ҫ���������
extern char code[25];//�û�Ҫ���������

char newname[15] = { 0 };//�û�ע��ʱҪ���������
char newcode[25] = { 0 };//�û�ע��ʱҪ���������

MOUSEMSG mouse;//���һ������������Ϣ
int i = 0;//name������±�

struct USERS {
	char name[15] = { 0 };//�û�������
	char code[25] = { 0 };//�û�������
	int registered = 0;//���ֵ������ʾ���û��Ƿ���Ч
};
USERS user[10] = { 0 };//������ע��10���û�
//��¼����
void c_initscreem()
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();

	//�ı䴰�ڱ�������
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"��¼");

	settextstyle(25, 0, L"verdana");
	setbkmode(TRANSPARENT);//���ñ�����͸����
	settextcolor(RGB(45, 84, 117));
	outtextxy(120, 150 - 40, L"LOG IN");

	outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 + 20 - 5, 150 + 20 + 20 + 20 + 12, 120 + 20 - 5 + 40, 150 + 20 + 20 + 20 + 5 + 30);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(10, 150, L"Put your English name here��");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150, 300, 150 + 20);

	outtextxy(10, 150 + 20 + 20, L"Put your code here��");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150 + 20 + 20, 300, 150 + 20 + 20 + 20);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(10, 150 + 20 + 20 + 60, L"Have no account?");
	outtextxy(10, 150 + 20 + 20 + 60 + 20, L"Click here to get a new account!!");
}
//ע�����
void SignScreen()
{
	cleardevice();
	//�ı䴰�ڱ�������
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"ע��");

	settextstyle(25, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(120, 150 - 40, L"REGISTER");//ע��

	outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 + 20 - 5, 150 + 20 + 20 + 20 + 12, 120 + 20 - 5 + 40, 150 + 20 + 20 + 20 + 5 + 30);

	outtextxy(120 + 20 - 5 + 40 + 30, 150 + 20 + 20 + 20 + 10, L"RETURN");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 + 20 - 5 + 40 + 30, 150 + 20 + 20 + 20 + 12, 120 + 20 - 5 + 40 + 40 + 30 + 60, 150 + 20 + 20 + 20 + 5 + 30);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(10, 150, L"Put your English name here��");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150, 300, 150 + 20);

	outtextxy(10, 150 + 20 + 20, L"Put your code here��");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150 + 20 + 20, 300, 150 + 20 + 20 + 20);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

}
//�������ĺ���
void putname()
{
	char m = 0;

	for (int i = 0; i < 9; i++) {
		while (1) {
			m = _getwch();
			if (m >= 'a' && m <= 'z' || m >= 'A' && m <= 'Z' || m >= '0' && m <= '9' || m == '\n' || m == '\r') {
				break;
			}
		}

		if (m == '\n' || m == '\r')
			break;//����ǻس�����ʾ�������
		else {
			name[i] = m;//�����ֵ������������
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(202 + 10 * i, 150 + 5, name[i]);
		}
	}

}
void putcode()
{
	char m = 0;
	for (i = 0; i < 20; i++) {
		while (1) {
			m = _getwch();
			if (m >= 'a' && m <= 'z' || m >= 'A' && m <= 'Z' || m >= '0' && m <= '9' || m == '\n' || m == '\r') {
				break;
			}
		}

		if (m == '\n' || m == '\r')
			break;//����ǻس�����ʾ�������
		else {
			code[i] = m;//�����ֵ������������
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(202 + 5 * i, 150 + 5 + 40, L"��");
		}
	}

}
void putnewname()
{
	char m = 0;
	for (int i = 0; i < 9; i++) {
		while (1) {
			m = _getwch();
			if (m >= 'a' && m <= 'z' || m >= 'A' && m <= 'Z' || m >= '0' && m <= '9' || m == '\n' || m == '\r') {
				break;
			}
		}

		if (m == '\n' || m == '\r')
			break;//����ǻس�����ʾ�������
		else {
			newname[i] = m;//�����ֵ������������
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(202 + 10 * i, 150 + 5, newname[i]);
		}
	}

}
void putnewcode()
{
	char m = 0;
	for (i = 0; i < 20; i++) {
		while (1) {
			m = _getwch();
			if (m >= 'a' && m <= 'z' || m >= 'A' && m <= 'Z' || m >= '0' && m <= '9' || m == '\n' || m == '\r') {
				break;
			}
		}

		if (m == '\n' || m == '\r')
			break;//����ǻس�����ʾ�������
		else {
			newcode[i] = m;//�����ֵ������������
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(202 + 5 * i, 150 + 5 + 40, L"��");
		}
	}

}
//��ֹ�Ѿ�����Ķ�������ȥ�Ĵ�ӡ����
void printname()
{
	for (int i = 0; name[i] != '\0'; i++) {
		settextstyle(15, 0, L"verdana");
		settextcolor(RGB(45, 84, 117));
		outtextxy(202 + 10 * i, 150 + 5, name[i]);
	}
}
void printcode()
{
	for (int i = 0; code[i] != '\0'; i++) {
		settextstyle(15, 0, L"verdana");
		settextcolor(RGB(45, 84, 117));
		outtextxy(202 + 5 * i, 150 + 5 + 40, L"��");
	}
}
void printnewname()
{
	for (int i = 0; newname[i] != '\0'; i++) {
		settextstyle(15, 0, L"verdana");
		settextcolor(RGB(45, 84, 117));
		outtextxy(202 + 10 * i, 150 + 5, newname[i]);
	}

}
void printnewcode()
{
	for (int i = 0; newcode[i] != '\0'; i++) {
		settextstyle(15, 0, L"verdana");
		settextcolor(RGB(45, 84, 117));
		outtextxy(202 + 5 * i, 150 + 5 + 40, L"��");
	}
}
//�����������¼��ע���ߵ��û���Ϣ
void record()
{
	fstream fn, fc;
	fn.open("usernames.txt", ios::app);//���ĵ�����׷��
	fc.open("usercodes.txt", ios::app);
	for (int i = 0; newname[i] != '\0'; i++) {//��β��ǰ��Ķ�����¼��������������û�������
		fn << newname[i];
	}
	fn << " ";

	for (int i = 0; newcode[i] != '\0'; i++) {
		fc << newcode[i];
	}
	fc << " ";
	//��userȥ��ȡ��ʱ�����û�������
	fn.close();
	fc.close();
}
//��ɶ�ȡ��Ϣ�ĺ���
void read()
{
	FILE* fn, * fc;
	fn = fopen("usernames.txt", "rb");//���ĵ�����׷��
	fc = fopen("usercodes.txt", "rb");
	int i_n = 0, i_u = 0,
		j_u = 0, j_c = 0;
	char c = 0;
	while (!feof(fn)) {
		c = fgetc(fn);
		if (c != ' ') {//û�������ո�˵������ͬһ�������ֵ�һ����
			user[i_u].registered = 1;//�Ǽǹ���Ҫ�ı���һ���ֵ
			user[i_u].name[i_n] = c;
			i_n++;
		}
		else {//�����ո��ˣ�˵��Ҫ��ʼ¼����һ���˵�������,Ȼ�������һֱ�����������ַǿո�Ϊֹ������֮ǰҪ�±�һֱ����ԭ���Ǹ�ֵ
			i_n = 0;//����
			i_u++;//��һ������
			while (1) {
				c = fgetc(fn);
				if (c != ' ') {//û�������ո�˵������ͬһ�������ֵ�һ����
					user[i_u].registered = 1;//�Ǽǹ���Ҫ�ı���һ���ֵ
					user[i_u].name[i_n] = c;
					i_n++;
					break;
				}
			}
		}
	}

	while (!feof(fc)) {
		c = fgetc(fc);
		if (c != ' ') {//û�������ո�˵������ͬһ�������ֵ�һ����
			user[j_u].code[j_c] = c;
			j_c++;
		}
		else {//�����ո��ˣ�˵��Ҫ��ʼ¼����һ���˵�������
			j_c = 0;//����
			j_u++;//��һ������
			while (1) {
				c = fgetc(fc);
				if (c != ' ') {//û�������ո�˵������ͬһ�������ֵ�һ����
					user[j_u].code[j_c] = c;
					j_c++;
					break;
				}
			}
		}
	}
	fclose(fn);
	fclose(fc);

	//�����ȡ�����ֺ����뿴���Լ����ĶԲ���
	for (int i = 0; user[i].registered == 1; i++) {
		for (int j = 0; user[i].name[j] != '\0'; j++) {
			cout << user[i].name[j];
		}
		cout << "    ";
		for (int m = 0; user[i].code[m] != '\0'; m++) {
			cout << user[i].code[m];
		}
		cout << endl;
	}

}
//���ע��ĺ���
void signup()
{
	SignScreen();//��ʼ��ע��Ľ���
	while (1) {
		mouse = GetMouseMsg();//��ù���������Ϣ
		if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 && mouse.y <= 150 + 20)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(200 + 1, 150 + 1, 300 - 1, 150 + 20 - 1);
			if (newname[0] != '\0') {
				printnewname();
			}
		}
		else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 + 40 && mouse.y <= 150 + 20 + 40)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(200 + 1, 150 + 40 + 1, 300 - 1, 150 + 20 + 40 - 1);
			if (newcode[0] != '\0') {
				printnewcode();
			}
		}
		else if (mouse.x >= 120 + 20 - 5 && mouse.x <= 120 + 20 - 5 + 40 && mouse.y >= 150 + 20 + 20 + 20 + 12 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(120 + 20 - 5 + 1, 150 + 20 + 20 + 20 + 12 + 1, 120 + 20 - 5 + 40 - 1, 150 + 20 + 20 + 20 + 5 + 30 - 1);
			settextstyle(25, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");
		}
		else if (mouse.x >= 120 + 20 - 5 + 40 + 30 - 1 && mouse.x <= 120 + 20 - 5 + 40 + 40 + 30 + 60 + 1 && mouse.y >= 150 + 20 + 20 + 20 + 12 - 1 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30 + 1)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(120 + 20 - 5 + 40 + 30 + 1, 150 + 20 + 20 + 20 + 12 + 1, 120 + 20 - 5 + 40 + 40 + 30 + 60 - 1, 150 + 20 + 20 + 20 + 5 + 30 - 1);
			settextstyle(25, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(120 + 20 - 5 + 40 + 30, 150 + 20 + 20 + 20 + 10, L"RETURN");
		}
		else {
			clearrectangle(200 + 1, 150 + 1, 300 - 1, 150 + 20 - 1);
			clearrectangle(200 + 1, 150 + 40 + 1, 300 - 1, 150 + 20 + 40 - 1);
			clearrectangle(120 + 20 - 5 + 1, 150 + 20 + 20 + 20 + 12 + 1, 120 + 20 - 5 + 40 - 1, 150 + 20 + 20 + 20 + 5 + 30 - 1);
			clearrectangle(120 + 20 - 5 + 40 + 30 + 1, 150 + 20 + 20 + 20 + 12 + 1, 120 + 20 - 5 + 40 + 40 + 30 + 60 - 1, 150 + 20 + 20 + 20 + 5 + 30 - 1);

			settextstyle(25, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");

			outtextxy(120 + 20 - 5 + 40 + 30, 150 + 20 + 20 + 20 + 10, L"RETURN");

			if (newname[0] != '\0') {
				printnewname();
			}
			if (newcode[0] != '\0') {
				printnewcode();
			}
		}

		if (mouse.uMsg == WM_LBUTTONDOWN)//����õ�����Ϣ���������������������귶Χ
		{
			if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 && mouse.y <= 150 + 20) {
				putnewname();
			}
			else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 + 40 && mouse.y <= 150 + 20 + 40) {
				putnewcode();
			}
			else if (mouse.x >= 120 + 20 - 5 + 40 + 30 - 1 && mouse.x <= 120 + 20 - 5 + 40 + 40 + 30 + 60 + 1 && mouse.y >= 150 + 20 + 20 + 20 + 12 - 1 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30 + 1) {
				c_initscreem();
				for (int i = 0; i < 10; i++) {
					newname[i] = 0;
				}
				for (int j = 0; j < 25; j++) {
					newcode[j] = 0;
				}
				break;//�˳�����
			}
			else if (mouse.x >= 120 + 20 - 5 && mouse.x <= 120 + 20 - 5 + 40 && mouse.y >= 150 + 20 + 20 + 20 + 12 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30)
			{
				int same = 1;//�����ж������Ƿ���ͬ
				//�ȱȽ�ע���ߵ������Ƿ����ظ���
				for (int i = 0; user[i].registered == 1; i++) {
					for (int j = 0; user[i].name[j] != '\0'; j++) {
						if (newname[j] != user[i].name[j]) {
							same = 0;
							break;
						}
						else {
							same = 1;
						}
					}
					if (same)
						break;//˵����ʱ�ҵ���һ�������֣��Ǿ���Ҫ����ע��
				}
				if (same) {
					for (int i = 0; i < 15; i++) {
						newname[i] = 0;
					}
					for (int j = 0; j < 25; j++) {
						newcode[j] = 0;
					}
					settextstyle(15, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					outtextxy(10, 150 + 20 + 20 + 60, L"Sign up unsuccessfully!");
					Sleep(3000);//ͣ������󣬷�������¼����
					setfillcolor(WHITE);
					solidrectangle(10, 150 + 20 + 20 + 60, 10 + 180, 150 + 20 + 20 + 60 + 20);
				}
				//��ʾע��ɹ�
				else if (newname[0] != '\0' && newcode[0] != '\0') {
					settextstyle(15, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					outtextxy(10, 150 + 20 + 20 + 60, L"Sign up successfully!!!");
					Sleep(3000);//ͣ������󣬷�������¼����
					c_initscreem();
					break;
				}
			}
		}
	}
	record();
	read();
	for (int i = 0; i < 15; i++) {
		newname[i] = 0;
	}
	for (int j = 0; j < 25; j++) {
		newcode[j] = 0;
	}
}

void SignIn()
{
	//�Ƚ��������ĵ���һ�������洢�û���������һ�������洢�û�������
	fstream fn, fc;
	fn.open("usernames.txt", ios::app);//�ڻ�û�н�������ĵ���ʱ���Ƚ�������ĵ����Է�ֹ�����ȡ��ʱ����Ϊ�Ҳ����ĵ�����������
	fc.open("usercodes.txt", ios::app);//�ڻ�û�н�������ĵ���ʱ���Ƚ�������ĵ����Է�ֹ�����ȡ��ʱ����Ϊ�Ҳ����ĵ�����������

	fn.close();//������������ĵ�֮��͹ر���
	fc.close();//������������ĵ�֮��͹ر���

	//��ʼ����Ļ
	c_initscreem();
	read();//�ȶ�ȡ���е��û�����Ϣ

	while (1) {
		mouse = GetMouseMsg();//��ù���������Ϣ
		if (mouse.x >= 10 && mouse.x <= 200 + 10 && mouse.y >= 150 + 20 + 20 + 60 + 20 - 10 + 5 && mouse.y <= 150 + 20 + 20 + 60 + 20 + 10 + 5)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(11, 150 + 20 + 20 + 60 + 20 - 10 + 5 + 1, 200 + 10 - 1, 150 + 20 + 20 + 60 + 20 + 10 + 5 - 1);

			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));

			outtextxy(10, 150 + 20 + 20 + 60, L"Have no account?");
			outtextxy(10, 150 + 20 + 20 + 60 + 20, L"Click here to get a new account!!");

		}
		else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 && mouse.y <= 150 + 20)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(200 + 1, 150 + 1, 300 - 1, 150 + 20 - 1);
			if (name[0] != '\0') {
				printname();
			}
		}
		else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 + 40 && mouse.y <= 150 + 20 + 40)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(200 + 1, 150 + 40 + 1, 300 - 1, 150 + 20 + 40 - 1);
			if (code[0] != '\0') {
				printcode();
			}

		}
		else if (mouse.x >= 120 + 20 - 5 && mouse.x <= 120 + 20 - 5 + 40 && mouse.y >= 150 + 20 + 20 + 20 + 12 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30)
		{
			setfillcolor(RGB(115, 171, 204));
			solidrectangle(120 + 20 - 5 + 1, 150 + 20 + 20 + 20 + 12 + 1, 120 + 20 - 5 + 40 - 1, 150 + 20 + 20 + 20 + 5 + 30 - 1);

			settextstyle(25, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");

		}
		else {
			clearrectangle(11, 150 + 20 + 20 + 60 + 20 - 10 + 5 + 1, 200 + 10 - 1, 150 + 20 + 20 + 60 + 20 + 10 + 5 - 1);
			clearrectangle(200 + 1, 150 + 1, 300 - 1, 150 + 20 - 1);
			clearrectangle(200 + 1, 150 + 40 + 1, 300 - 1, 150 + 20 + 40 - 1);
			clearrectangle(120 + 20 - 5 + 1, 150 + 20 + 20 + 20 + 12 + 1, 120 + 20 - 5 + 40 - 1, 150 + 20 + 20 + 20 + 5 + 30 - 1);
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));

			outtextxy(10, 150 + 20 + 20 + 60, L"Have no account?");
			outtextxy(10, 150 + 20 + 20 + 60 + 20, L"Click here to get a new account!!");
			settextstyle(25, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");
			if (name[0] != '\0') {
				printname();
			}
			if (code[0] != '\0') {
				printcode();
			}

		}

		if (mouse.uMsg == WM_LBUTTONDOWN)//����õ�����Ϣ���������������������귶Χ
		{
			if (mouse.x >= 10 && mouse.x <= 200 + 10 && mouse.y >= 150 + 20 + 20 + 60 + 20 - 10 && mouse.y <= 150 + 20 + 20 + 60 + 20 + 10) {
				//��������λ�����ʵ�������Χ�ڣ�˵�������û�ע��
				signup();
			}
			else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 && mouse.y <= 150 + 20) {
				//��������λ������������Χ֮�ڣ���Ҫ��������
				putname();
			}
			else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 + 40 && mouse.y <= 150 + 20 + 40) {
				//��������λ��Ҫ���������Χ֮�ڣ���Ҫ��������
				putcode();
			}
			else if (mouse.x >= 120 + 20 - 5 && mouse.x <= 120 + 20 - 5 + 40 && mouse.y >= 150 + 20 + 20 + 20 + 12 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30) {
				//��������λ��Ҫ���������Χ֮�ڣ���˵���û������Լ��Ѿ���������ˣ��Ǿ�Ҫȥ�˶�������û����������Ƿ����
				//���ȣ�Ѱ���Ƿ�������û�
				int same = 1;
				int i_u = 0;
				for (i_u = 0; user[i_u].registered == 1; i_u++) {
					for (int j = 0; user[i_u].name[j] != '\0'; j++) {
						if (name[j] != user[i_u].name[j]) {
							same = 0;
							break;
						}
						else {
							same = 1;
						}
					}
					if (same)
						break;//˵����ʱ�ҵ���һ�������֣��Ǿ�Ҫȥ�Ƚϸ����ֶ�Ӧ�µ������Ƿ���ͬ
				}
				cout << endl << i_u << endl << endl;
				if (same) {
					int same_c = 1;
					int j_c = 0;//������������β��ǰuser[i_u].code[j_c]�ж���λ,�ԱȽ�code��λ���Ƿ��ԭ����һ����
					for (j_c = 0; user[i_u].code[j_c] != '\0'; j_c++) {
						if (user[i_u].code[j_c] != code[j_c]) {
							same_c = 0;//˵�������������
						}
					}

					int shuru_c = 0;
					for (int i = 0; code[i] != '\0'; i++)
						shuru_c++;//����������������ж���λ
					if (shuru_c != j_c)//˵�������λ���������λ����һ����
						same_c = 0;

					if (same_c == 0) {//˵��������������
						settextstyle(15, 0, L"verdana");
						settextcolor(RGB(45, 84, 117));
						outtextxy(10, 150 + 20 + 20 + 60 + 20 + 30, L"Wrong Code!!");
						Sleep(3000);
						setfillcolor(WHITE);
						solidrectangle(10, 150 + 20 + 20 + 60 + 20 + 30, 10 + 100, 150 + 20 + 20 + 60 + 20 + 30 + 20);
						for (int i = 0; i < 15; i++) {
							name[i] = 0;
						}
						for (int j = 0; j < 25; j++) {
							code[j] = 0;
						}

						continue;
					}
					else {
						settextstyle(15, 0, L"verdana");
						settextcolor(RGB(45, 84, 117));
						outtextxy(10, 150 + 20 + 20 + 60 + 20 + 30, L"Welcome!!");
						Sleep(3000);
						setfillcolor(WHITE);
						solidrectangle(10, 150 + 20 + 20 + 60 + 20 + 30, 10 + 100, 150 + 20 + 20 + 60 + 20 + 30 + 20);
					}
				}
				else {//˵������������û�
					settextstyle(15, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));
					outtextxy(10, 150 + 20 + 20 + 60 + 20 + 30, L"Unregistered!!");
					Sleep(3000);
					setfillcolor(WHITE);
					solidrectangle(10, 150 + 20 + 20 + 60 + 20 + 30, 10 + 100, 150 + 20 + 20 + 60 + 20 + 30 + 20);
					for (int i = 0; i < 15; i++) {
						name[i] = 0;
					}
					for (int j = 0; j < 25; j++) {
						code[j] = 0;
					}
					continue;
				}
				break;
			}
		}
	}
}

//��¼����֮���name������������־��Ǵ�ʱ��½�ߵ�����