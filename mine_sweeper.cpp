#include<Windows.h>
#include<ctime>
#include<graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

//这边定义一下文字的颜色，初始界面的颜色，展开的颜色，还有数字显示的颜色
const int C_text = RGB(64, 117, 157);
const int C_fold = RGB(105, 115, 170);
const int C_unfold = RGB(218, 221, 230);
const int C_mark = RGB(221, 137, 139);

const int N_1 = RGB(150, 162, 199);
const int N_2 = RGB(221, 137, 139);
const int N_3 = RGB(254, 141, 114);
const int N_4 = RGB(184, 80, 66);
const int N_5 = RGB(137, 220, 187);
const int N_6 = RGB(64, 117, 157);
const int N_7 = RGB(237, 193, 98);
const int N_8 = RGB(86, 66, 92);

const int N_COLOR[8] = { N_1,N_2,N_3,N_4,N_5,N_6,N_7,N_8 };
//扫雷的界面大小，根据选择的模式来给MAX_X和MAX_Y赋值
int MAX_X = 0;
int MAX_Y = 0;

//界面的长宽
int border_x = 0;
int border_y = 0;

//扫雷内部数组，后面的整个游戏都是由这个内部数组控制的
char inner_mine[20][40] = { 0 };
// 此数组用于存放为需要打印的项，把需要打印的项存在这里面比每一次搜索都打印要来的运行快
char print[20][40] = { 0 };
//用来存放并记录为0的项，并且记录其是否被检索过
int already[20][40] = { 0 };
//用于记录被标记的项
char mark[20][40] = { 0 };

//游戏中雷的个数，这个雷的个数是由选择的模式决定的
int mine_num = 9;
//选择游戏的模式
int choice_mode = 0;
//设置扫雷每一个小圈圈的半径
int radius = 10;

//判断接下来的操作是不是展开，还是标记
int UnfoldStep = 0;
int MarkStep = 0;

wchar_t y[50];
wchar_t mine[50];
wchar_t m_over_tips[50];
wchar_t mine_remain[50];


//获得一条关于鼠标的信息
MOUSEMSG m_mouse;
int array_x = 0;//此为鼠标单击时的转换成数组下标后的坐标
int array_y = 0;
int position_x = 0;//此为在界面中实际的坐标
int position_y = 0;

//用来判断点开的地方是不是雷
int judge_mine = 0;
//用来判断游戏是否已经结束了
int judgeend = 0;
int judgesuc = 0;

void guiling()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			inner_mine[i][j] = '\0';
			print[i][j] = '\0';
			already[i][j] = '\0';
			mark[i][j] = '\0';

		}
	}
	//用来判断点开的地方是不是雷
	judge_mine = 0;
	//用来判断游戏是否已经结束了
	judgeend = 0;
	judgesuc = 0;
}
//此函数的作用是，把鼠标的坐标转换成数组的下标
void trans_array(int mouse_x, int mouse_y)
{
	array_x = mouse_x / 20 - 1;
	array_y = mouse_y / 20 - 1;

	//cout << "trans_array"<<array_x << "  " << array_y << endl;
}
//此函数的作用是，把数组的下标转换成实际的坐标
void trans_position(int x, int y)
{
	position_x = x * 20 + 10 + 20;
	position_y = y * 20 + 10 + 20;

	//cout << "trans_position" << position_x << "  " << position_y << endl;

}
//初始化图形界面
int m_choicescreen()
{
	border_x = 10 + MAX_X * 20 + 10 + 10;
	border_y = 10 + MAX_Y * 20 + 10 + 10;
	//初始化界面
	//设置背景颜色为白色
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	//改变标题
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"mine_sweeper");
	// 绘图模式设置
	setbkmode(TRANSPARENT);

	settextcolor(RGB(254, 141, 114));
	settextstyle(25, 0, L"verdana");
	outtextxy(50 - 28, 80, L"Put '1':9*9(include 10 mines)");
	outtextxy(50 - 28, 120, L"Put '2':16*16(include 40 mines)");
	outtextxy(50 - 28, 160, L"Put '3':30*16(include 99 mines)");
	outtextxy(50 - 28, 200, L"Put '0':Exit");

	int m = 0;
	while (m != '1' && m != '2' && m != '0' && m != '3') {
		m = _getwch();
	}
	cleardevice();//清屏
	return m;


}
//用来生成内部数组
void form_mine(int avoid_x, int avoid_y)
{
	int x = 0, y = 0;
	for (int i = 0; i < mine_num; i++)
	{
		x = rand() % MAX_X;
		y = rand() % MAX_Y;
		if (inner_mine[y][x] != '*' && ((y != avoid_y || x != avoid_x)
			&& (y != avoid_y || x != avoid_x - 1)
			&& (y != avoid_y || x != avoid_x + 1)
			&& (y != avoid_y + 1 || x != avoid_x)
			&& (y != avoid_y + 1 || x != avoid_x - 1)
			&& (y != avoid_y + 1 || x != avoid_x + 1)
			&& (y != avoid_y - 1 || x != avoid_x)
			&& (y != avoid_y - 1 || x != avoid_x - 1)
			&& (y != avoid_y - 1 || x != avoid_x + 1)))//避开第一次点的位置周围形成的九宫格生成雷
			inner_mine[y][x] = '*';
		else
			i--;
	}//随机生成50个*且保证同一位置不重复出现*
}
//可以用于数周围指定范围内的雷数
void count(int range_x1, int range_x2, int range_y1, int range_y2, int i, int j)
{
	int jishu = 0;
	for (int n = range_y1; n <= range_y2; n++)
		for (int m = range_x1; m <= range_x2; m++)
			if (inner_mine[n][m] == '*')
				jishu++;
	inner_mine[i][j] = static_cast<char>(jishu + '0');
}
//生成内部数组，扫雷这游戏实际上是由内部数组驱使的
void base(int avoid_x, int avoid_y)
{
	srand((unsigned int)(time(0)));
	form_mine(avoid_x, avoid_y);
	for (int i = 0; i < MAX_Y; i++) {//从头到尾遍历一遍
		for (int j = 0; j < MAX_X; j++) {
			if (inner_mine[i][j] != '*') {//如果不是*就要去数周围九宫格中*的个数
				if (i == 0 && j == 0)//左上角
					count(0, 1, 0, 1, i, j);

				if (i == 0 && j == MAX_X - 1)//右上角
					count(MAX_X - 2, MAX_X - 1, 0, 1, i, j);

				if (i == MAX_Y - 1 && j == 0)//左下角
					count(0, 1, MAX_Y - 2, MAX_Y - 1, i, j);

				if (i == MAX_Y - 1 && j == MAX_X - 1)//右下角
					count(MAX_X - 2, MAX_X - 1, MAX_Y - 2, MAX_Y - 1, i, j);

				if (i == 0 && j >= 1 && j <= MAX_X - 2)//上边
					count(j - 1, j + 1, 0, 1, i, j);

				if (i == MAX_Y - 1 && j >= 1 && j <= MAX_X - 2)//下边
					count(j - 1, j + 1, MAX_Y - 2, MAX_Y - 1, i, j);

				if (j == 0 && i >= 1 && i <= MAX_Y - 2)//左边
					count(0, 1, i - 1, i + 1, i, j);

				if (j == MAX_X - 1 && i >= 1 && i <= MAX_Y - 2)//右边
					count(MAX_X - 2, MAX_X - 1, i - 1, i + 1, i, j);
				//靠边的处理完了

				if (i <= MAX_Y - 2 && i >= 1 && j >= 1 && j <= MAX_X - 2)//中间
					count(j - 1, j + 1, i - 1, i + 1, i, j);
			}
		}
	}
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			cout << inner_mine[i][j] << " ";
		}
		cout << endl;
	}
}
//用来根据选择的模式来设定参数
void set_parameters(int choice_mode)
{
	switch (choice_mode) {
		case '1':
			MAX_X = 9, MAX_Y = 9, mine_num = 10;
			break;
		case '2':
			MAX_X = 16, MAX_Y = 16, mine_num = 40;
			break;
		case '3':
			MAX_X = 30, MAX_Y = 16, mine_num = 99;
			break;
	}//根据选择的模式选择界面的大小

}
//用于显示剩下的未扫出来的雷数
void remained_mine()
{
	setfillcolor(WHITE);
	solidrectangle(5, border_y + 4, 5 + 100, border_y + 20);
	int num = 0;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (mark[i][j] == '\0' && inner_mine[i][j] == '*')
				num++;
		}
	}
	swprintf(mine_remain, 50, L"剩余雷数：%d", num);
	settextcolor(C_text);
	settextstyle(15, 0, L"楷体");
	outtextxy(10, border_y + 5, mine_remain);
}
//绘制游戏界面
void graph()
{
	border_x = 10 + MAX_X * 20 + 10 + 10;
	border_y = 10 + MAX_Y * 20 + 10 + 10;
	//初始化界面
	//设置背景颜色为白色
	initgraph(border_x, border_y + 20);
	setbkcolor(WHITE);
	cleardevice();
	//改变标题
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"mine_sweeper");
	// 绘图模式设置
	setbkmode(TRANSPARENT);

	//设置填充颜色
	setfillcolor(C_fold);
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			solidcircle(j * 20 + 30, i * 20 + 30, radius);//画出初始界面
		}
	}
	//画出行标列标
	settextstyle(10, 0, L"楷体");
	settextcolor(C_text);
	for (int i = 0; i < MAX_Y; i++) {
		swprintf(y, 29, L"%d", i + 1);//这一句话学着点
		outtextxy(2, i * 20 + 30, y);
	}
	for (int j = 0; j < MAX_X; j++) {
		swprintf(y, 29, L"%d", j + 1);//这一句话学着点
		outtextxy(j * 20 + 30, 2, y);
	}
}
//用来检索需要展开的项
void jiansuo(int x1, int y1)
{
	if (x1 != 0) {
		for (int i = x1 - 1; i >= 0; i--) {
			if (inner_mine[y1][i] == '0' && mark[y1][i] == '\0') {
				print[y1][i] = inner_mine[y1][i];//如果该位置是零，并且没有被标记过，就在记录数组中标记1
			}
			//雷与数字肯定是先碰到数字，再碰到雷，所以不存在检索到雷的情况
			else {
				print[y1][i] = inner_mine[y1][i];//并且一旦检索到非零，就标记后面一个字符，并且停止检索
				break;
			}
		}
	}
	//向右搜索，前提是x!=MAX_X-1
	if (x1 != MAX_X - 1) {
		for (int i = x1 + 1; i < MAX_X; i++) {
			if (inner_mine[y1][i] == '0' && mark[y1][i] == '\0') {
				print[y1][i] = inner_mine[y1][i];//如果该位置是零，就在记录数组中标记1
			}
			//雷与数字肯定是先碰到数字，再碰到雷，所以不存在检索到雷的情况
			else {
				print[y1][i] = inner_mine[y1][i];//并且一旦检索到非零，就标记后面一个字符，并且停止检索
				break;
			}
		}
	}
	//向上检索，前提是y!=0
	if (y1 != 0) {
		for (int j = y1 - 1; j >= 0; j--) {
			if (inner_mine[j][x1] == '0' && mark[j][x1] == '\0') {
				print[j][x1] = inner_mine[j][x1];//如果该位置是零，就在记录数组中标记1
			}
			//雷与数字肯定是先碰到数字，再碰到雷，所以不存在检索到雷的情况
			else {
				print[j][x1] = inner_mine[j][x1];//并且一旦检索到非零，就标记后面一个字符，并且停止检索
				break;
			}
		}
	}
	if (y1 != MAX_Y - 1) {
		for (int j = y1 + 1; j <= MAX_Y - 1; j++) {
			if (inner_mine[j][x1] == '0' && mark[j][x1] == '\0') {
				print[j][x1] = inner_mine[j][x1];//如果该位置是零，就在记录数组中标记1
			}
			//雷与数字肯定是先碰到数字，再碰到雷，所以不存在检索到雷的情况
			else {
				print[j][x1] = inner_mine[j][x1];//并且一旦检索到非零，就标记后面一个字符，并且停止检索
				break;
			}
		}
	}
}
void _judge_unfold()
{
	int x1 = 0, y1 = 0, i = 0, j = 0;
	int judge_ = 0;
	if (inner_mine[array_y][array_x] == '*')
		judge_mine = 1;//如果点开的是雷

	if (mark[array_y][array_x] == '\0') {//如果是有符号标记的话，就仅仅是标记就好了，没有必要进行检索//在给打印数组赋值之前，先判断了点开的位置是不是雷
		print[array_y][array_x] = inner_mine[array_y][array_x];
		while (1 && judge_mine != 1) {
			judge_ = 0;
			for (i = 0; i < MAX_Y; i++) {//遍历一遍zero数组
				for (j = 0; j < MAX_X; j++) {
					if (print[i][j] != '\0' && already[i][j] == 0 && inner_mine[i][j] == '0') {//如果这一项为零被标记过，但是却没有检索过
						x1 = j;
						y1 = i;
						judge_ = 1;//表示搜索到一个没有进行sousuo的项，需要退出遍历，对该项进行搜索
						break;
					}
				}
				if (judge_ == 1)
					break;
			}

			if (i >= MAX_Y && j >= MAX_X) {
				break;//说明已经全部检索完，可以开始打印了
			}
			if (judge_ == 1) {
				jiansuo(x1, y1);
				already[y1][x1] = 1;//标记为1，表示已经这一项0已经检索过
			}
		}
	}
}
//这是一个用来打印展开的项的函数
void print_unfold()
{
	int c = 0;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (print[i][j] != '\0') {//说明会有展开
				trans_position(j, i);
				setfillcolor(C_unfold);
				solidcircle(position_x, position_y, radius);//打印出展开的颜色
				//并且把内部数组打印上去
				if (inner_mine[i][j] != '0') {
					swprintf(mine, 29, L"%c", inner_mine[i][j]);//这一句话学着点
					c = inner_mine[i][j] - '0' - 1;
					settextcolor(N_COLOR[c]);
					settextstyle(10, 0, L"楷体");
					outtextxy(position_x, position_y, mine);
				}
			}
		}
	}
	cout << "运行print_unfold" << endl;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			cout << print[i][j] << "  ";
		}
		cout << endl;
	}
}
//这是一个用来读取鼠标位置的函数,将鼠标的坐标转换成数组的下标
void read_mouse_action()
{
	UnfoldStep = 0;
	UnfoldStep = 0;
	while (1) {
		m_mouse = GetMouseMsg();//获得关于鼠标的信息
		if (m_mouse.uMsg == WM_LBUTTONDOWN)//如果得到的信息是鼠标左击，接下来看坐标范围
			//要注意坐标与数组下标的统一
		{
			UnfoldStep = 1;//如果是左键单击，说明接下来的是展开的操作
			cout << "UnfoldStep" << endl;
			trans_array(m_mouse.x, m_mouse.y);//将此时鼠标的坐标转换成数组的下标
			break;
		}
		else if (m_mouse.uMsg == WM_RBUTTONDOWN) {//如果得到的信息是右键击下，接下来就是标记的操作
			MarkStep = 1;
			cout << "MarkStep" << endl;
			trans_array(m_mouse.x, m_mouse.y);//将此时鼠标的坐标转换成数组的下标
			break;
		}
	}
}
//用来判断左击的位置是不是雷区
void judge_if_mine()
{
	if (inner_mine[array_y][array_x] == '*') {
		judge_mine = 1;//如果点开的是雷
		judgeend = 1;
	}
	cout << "运行judge_if_mine" << endl;
}
//如果结束了，就把所有的雷全部展开来
void print_mine()
{
	for (int i = 0; i < MAX_X; i++) {
		for (int j = 0; j < MAX_Y; j++) {
			if (inner_mine[j][i] == '*') {
				setfillcolor(RGB(221, 137, 139));
				trans_position(i, j);
				solidcircle(position_x, position_y, radius);
				swprintf(y, 5, L"%c", '*');
				settextcolor(C_fold);
				outtextxy(position_x, position_y, y);
			}
		}
	}
}
//用来进行标记的操作
void Mark() {
	if (mark[array_y][array_x] == '\0' && print[array_y][array_x] == '\0')//如果右击的位置是尾零，说明该位置是没有被标记过的，并且也没有展开的，那就标记成1
		mark[array_y][array_x] = '1';
	else if (mark[array_y][array_x] != '\0') {//如果右击的位置不是尾零，说明此时的操作应该是解除标记，那就把它恢复成尾零，并且给他恢复正常颜色
		mark[array_y][array_x] = '\0';
		setfillcolor(C_fold);
		trans_position(array_x, array_y);
		solidcircle(position_x, position_y, radius);
	}
	cout << "运行Mark" << endl;
}
void PrintMark()
{
	setfillcolor(C_mark);
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (mark[i][j] != '\0') {//如果此项被标记过
				trans_position(j, i);
				solidcircle(position_x, position_y, radius);
			}
		}
	}
	cout << "运行PrintMark" << endl;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			cout << mark[i][j] << "  ";
		}
		cout << endl;
	}
}
//上来第一步
void first_step()
{
	//绘制游戏界面
	graph();
	//选择第一次点开的位置
	read_mouse_action();
	//避开第一次点开的位置生成雷，并且形成内部数组
	base(array_x, array_y);
	//然后就可以开始进行第一次展开了
	_judge_unfold();
	//然后就把print标记的展开来就好了
	print_unfold();

}
//判断是否已经成功了，即是否已经把所有的雷都扫出来了
void judge_if_succeed()
{//当没有打印的地方和雷的个数一样多的时候就说明结束了，成功了
	int num = 0;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (print[i][j] == '\0')
				num++;
		}
	}
	if (num == mine_num)
		judgesuc = 1;
}
void mine_sweeper()
{
	while (1) {
		guiling();

		//先选择模式，根据选择的模式去生成对应的数组
		choice_mode = m_choicescreen();
		if (choice_mode == '0')
			break;
		else {
			set_parameters(choice_mode);
			//内部数组生成了之后，就要先生成游戏界面，然后再选择第一次要点开的那个坐标，避开第一次点开的坐标来生成内部数组，然后再展开

			first_step();

			//接下来是生成了内部数组之后的连续操作
			while (!judgeend && !judgesuc) {
				read_mouse_action();//先去读鼠标
				if (UnfoldStep) {//如果得到的信息是进行展开操作
					if (mark[array_y][array_x] == '\0') {//如果点开的地方没有被标记过
						judge_if_mine();//先判断点开的地方是不是雷区
						if (!judgeend) {//点开的位置不是雷，游戏没有结束，才需要去继续检索并且展开
							_judge_unfold();
							print_unfold();
						}
						if (judgeend) {//点开的是雷区
							print_mine();
						}
					}
				}
				else if (MarkStep) {//如果鼠标得到的信息是右击，说明是标记的操作
					Mark();
					PrintMark();
				}
				judge_if_succeed();
			    //cout << "judgeend" << judgeend << endl;
			}
			remained_mine();
			if (judgeend) {
				swprintf(m_over_tips, 39, L"踩到雷啦\n再来一局吗？");//弹窗吗？？
				if (MessageBox(GetHWnd(), m_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
					break;
			}
			else if (judgesuc) {
				swprintf(m_over_tips, 39, L"您可真是扫雷小能手呢\n再来一局吗？");//弹窗吗？？
				if (MessageBox(GetHWnd(), m_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
					break;
			}
		}
	}
}
