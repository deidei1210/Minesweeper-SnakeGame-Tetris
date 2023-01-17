/*2051498 储岱泽 信12*/
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <fstream>
#include<cstring>
#include<conio.h>
#include<iostream>
using namespace std;
extern char name[15];//用户要输入的名字
extern char code[25];//用户要输入的密码

char newname[15] = { 0 };//用户注册时要输入的名字
char newcode[25] = { 0 };//用户注册时要输入的密码

MOUSEMSG mouse;//获得一条关于鼠标的信息
int i = 0;//name数组的下标

struct USERS {
	char name[15] = { 0 };//用户的名字
	char code[25] = { 0 };//用户的密码
	int registered = 0;//这个值用来显示该用户是否有效
};
USERS user[10] = { 0 };//最多可以注册10个用户
//登录界面
void c_initscreem()
{
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();

	//改变窗口标题名字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"登录");

	settextstyle(25, 0, L"verdana");
	setbkmode(TRANSPARENT);//设置背景是透明的
	settextcolor(RGB(45, 84, 117));
	outtextxy(120, 150 - 40, L"LOG IN");

	outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 + 20 - 5, 150 + 20 + 20 + 20 + 12, 120 + 20 - 5 + 40, 150 + 20 + 20 + 20 + 5 + 30);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(10, 150, L"Put your English name here：");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150, 300, 150 + 20);

	outtextxy(10, 150 + 20 + 20, L"Put your code here：");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150 + 20 + 20, 300, 150 + 20 + 20 + 20);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(10, 150 + 20 + 20 + 60, L"Have no account?");
	outtextxy(10, 150 + 20 + 20 + 60 + 20, L"Click here to get a new account!!");
}
//注册界面
void SignScreen()
{
	cleardevice();
	//改变窗口标题名字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"注册");

	settextstyle(25, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));
	outtextxy(120, 150 - 40, L"REGISTER");//注册

	outtextxy(120 + 20, 150 + 20 + 20 + 20 + 10, L"OK");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 + 20 - 5, 150 + 20 + 20 + 20 + 12, 120 + 20 - 5 + 40, 150 + 20 + 20 + 20 + 5 + 30);

	outtextxy(120 + 20 - 5 + 40 + 30, 150 + 20 + 20 + 20 + 10, L"RETURN");
	setlinecolor(RGB(45, 84, 117));
	rectangle(120 + 20 - 5 + 40 + 30, 150 + 20 + 20 + 20 + 12, 120 + 20 - 5 + 40 + 40 + 30 + 60, 150 + 20 + 20 + 20 + 5 + 30);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

	outtextxy(10, 150, L"Put your English name here：");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150, 300, 150 + 20);

	outtextxy(10, 150 + 20 + 20, L"Put your code here：");
	setlinecolor(RGB(45, 84, 117));
	rectangle(200, 150 + 20 + 20, 300, 150 + 20 + 20 + 20);

	settextstyle(15, 0, L"verdana");
	settextcolor(RGB(45, 84, 117));

}
//完成输入的函数
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
			break;//如果是回车，表示输入完毕
		else {
			name[i] = m;//把这个值赋给名字数组
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
			break;//如果是回车，表示输入完毕
		else {
			code[i] = m;//把这个值赋给名字数组
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(202 + 5 * i, 150 + 5 + 40, L"·");
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
			break;//如果是回车，表示输入完毕
		else {
			newname[i] = m;//把这个值赋给名字数组
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
			break;//如果是回车，表示输入完毕
		else {
			newcode[i] = m;//把这个值赋给名字数组
			settextstyle(15, 0, L"verdana");
			settextcolor(RGB(45, 84, 117));
			outtextxy(202 + 5 * i, 150 + 5 + 40, L"·");
		}
	}

}
//防止已经输入的东东被擦去的打印函数
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
		outtextxy(202 + 5 * i, 150 + 5 + 40, L"·");
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
		outtextxy(202 + 5 * i, 150 + 5 + 40, L"·");
	}
}
//这个函数用来录入注册者的用户信息
void record()
{
	fstream fn, fc;
	fn.open("usernames.txt", ios::app);//在文档后面追加
	fc.open("usercodes.txt", ios::app);
	for (int i = 0; newname[i] != '\0'; i++) {//把尾零前面的都给记录下来，这是这个用户的名字
		fn << newname[i];
	}
	fn << " ";

	for (int i = 0; newcode[i] != '\0'; i++) {
		fc << newcode[i];
	}
	fc << " ";
	//让user去读取此时已有用户的数据
	fn.close();
	fc.close();
}
//完成读取信息的函数
void read()
{
	FILE* fn, * fc;
	fn = fopen("usernames.txt", "rb");//在文档后面追加
	fc = fopen("usercodes.txt", "rb");
	int i_n = 0, i_u = 0,
		j_u = 0, j_c = 0;
	char c = 0;
	while (!feof(fn)) {
		c = fgetc(fn);
		if (c != ' ') {//没有遇到空格，说明还是同一个人名字的一部分
			user[i_u].registered = 1;//登记过的要改变这一项的值
			user[i_u].name[i_n] = c;
			i_n++;
		}
		else {//读到空格了，说明要开始录入下一个人的名字了,然后接下来一直读，读到出现非空格为止，在这之前要下标一直保持原来那个值
			i_n = 0;//归零
			i_u++;//下一个人了
			while (1) {
				c = fgetc(fn);
				if (c != ' ') {//没有遇到空格，说明还是同一个人名字的一部分
					user[i_u].registered = 1;//登记过的要改变这一项的值
					user[i_u].name[i_n] = c;
					i_n++;
					break;
				}
			}
		}
	}

	while (!feof(fc)) {
		c = fgetc(fc);
		if (c != ' ') {//没有遇到空格，说明还是同一个人名字的一部分
			user[j_u].code[j_c] = c;
			j_c++;
		}
		else {//读到空格了，说明要开始录入下一个人的名字了
			j_c = 0;//归零
			j_u++;//下一个人了
			while (1) {
				c = fgetc(fc);
				if (c != ' ') {//没有遇到空格，说明还是同一个人名字的一部分
					user[j_u].code[j_c] = c;
					j_c++;
					break;
				}
			}
		}
	}
	fclose(fn);
	fclose(fc);

	//输出读取的名字和密码看看自己读的对不对
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
//完成注册的函数
void signup()
{
	SignScreen();//初始化注册的界面
	while (1) {
		mouse = GetMouseMsg();//获得关于鼠标的信息
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

		if (mouse.uMsg == WM_LBUTTONDOWN)//如果得到的信息是鼠标左击，接下来看坐标范围
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
				break;//退出界面
			}
			else if (mouse.x >= 120 + 20 - 5 && mouse.x <= 120 + 20 - 5 + 40 && mouse.y >= 150 + 20 + 20 + 20 + 12 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30)
			{
				int same = 1;//用于判断姓名是否相同
				//先比较注册者的姓名是否有重复的
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
						break;//说明此时找到了一样的名字，那就需要重新注册
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
					Sleep(3000);//停顿三秒后，返回主登录界面
					setfillcolor(WHITE);
					solidrectangle(10, 150 + 20 + 20 + 60, 10 + 180, 150 + 20 + 20 + 60 + 20);
				}
				//显示注册成功
				else if (newname[0] != '\0' && newcode[0] != '\0') {
					settextstyle(15, 0, L"verdana");
					settextcolor(RGB(45, 84, 117));

					outtextxy(10, 150 + 20 + 20 + 60, L"Sign up successfully!!!");
					Sleep(3000);//停顿三秒后，返回主登录界面
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
	//先建立两个文档，一个用来存储用户的姓名，一个用来存储用户的密码
	fstream fn, fc;
	fn.open("usernames.txt", ios::app);//在还没有建立这个文档的时候先建立这个文档，以防止下面读取的时候因为找不到文档而发生错误
	fc.open("usercodes.txt", ios::app);//在还没有建立这个文档的时候先建立这个文档，以防止下面读取的时候因为找不到文档而发生错误

	fn.close();//建立好了这个文档之后就关闭它
	fc.close();//建立好了这个文档之后就关闭它

	//初始化屏幕
	c_initscreem();
	read();//先读取已有的用户的信息

	while (1) {
		mouse = GetMouseMsg();//获得关于鼠标的信息
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

		if (mouse.uMsg == WM_LBUTTONDOWN)//如果得到的信息是鼠标左击，接下来看坐标范围
		{
			if (mouse.x >= 10 && mouse.x <= 200 + 10 && mouse.y >= 150 + 20 + 20 + 60 + 20 - 10 && mouse.y <= 150 + 20 + 20 + 60 + 20 + 10) {
				//鼠标左击的位置如果实在这个范围内，说明是新用户注册
				signup();
			}
			else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 && mouse.y <= 150 + 20) {
				//鼠标左击的位置如果在这个范围之内，就要输入姓名
				putname();
			}
			else if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 150 + 40 && mouse.y <= 150 + 20 + 40) {
				//鼠标左击的位置要是在这个范围之内，就要输入密码
				putcode();
			}
			else if (mouse.x >= 120 + 20 - 5 && mouse.x <= 120 + 20 - 5 + 40 && mouse.y >= 150 + 20 + 20 + 20 + 12 && mouse.y <= 150 + 20 + 20 + 20 + 5 + 30) {
				//鼠标左击的位置要是在这个范围之内，就说明用户觉得自己已经输入完毕了，那就要去核对输入的用户名和密码是否符合
				//首先，寻找是否有这个用户
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
						break;//说明此时找到了一样的名字，那就要去比较该名字对应下的密码是否相同
				}
				cout << endl << i_u << endl << endl;
				if (same) {
					int same_c = 1;
					int j_c = 0;//用来数在遇到尾零前user[i_u].code[j_c]有多少位,以比较code的位数是否和原密码一样多
					for (j_c = 0; user[i_u].code[j_c] != '\0'; j_c++) {
						if (user[i_u].code[j_c] != code[j_c]) {
							same_c = 0;//说明密码输入错误
						}
					}

					int shuru_c = 0;
					for (int i = 0; code[i] != '\0'; i++)
						shuru_c++;//用来数输入的密码有多少位
					if (shuru_c != j_c)//说明输入的位数和密码的位数不一样多
						same_c = 0;

					if (same_c == 0) {//说明密码输入有误
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
				else {//说明不存在这个用户
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

//登录完了之后的name数组里面的名字就是此时登陆者的姓名