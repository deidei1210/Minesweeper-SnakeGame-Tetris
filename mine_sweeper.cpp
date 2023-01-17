#include<Windows.h>
#include<ctime>
#include<graphics.h>
#include<iostream>
#include<conio.h>
using namespace std;

//��߶���һ�����ֵ���ɫ����ʼ�������ɫ��չ������ɫ������������ʾ����ɫ
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
//ɨ�׵Ľ����С������ѡ���ģʽ����MAX_X��MAX_Y��ֵ
int MAX_X = 0;
int MAX_Y = 0;

//����ĳ���
int border_x = 0;
int border_y = 0;

//ɨ���ڲ����飬�����������Ϸ����������ڲ�������Ƶ�
char inner_mine[20][40] = { 0 };
// ���������ڴ��Ϊ��Ҫ��ӡ�������Ҫ��ӡ��������������ÿһ����������ӡҪ�������п�
char print[20][40] = { 0 };
//������Ų���¼Ϊ0������Ҽ�¼���Ƿ񱻼�����
int already[20][40] = { 0 };
//���ڼ�¼����ǵ���
char mark[20][40] = { 0 };

//��Ϸ���׵ĸ���������׵ĸ�������ѡ���ģʽ������
int mine_num = 9;
//ѡ����Ϸ��ģʽ
int choice_mode = 0;
//����ɨ��ÿһ��СȦȦ�İ뾶
int radius = 10;

//�жϽ������Ĳ����ǲ���չ�������Ǳ��
int UnfoldStep = 0;
int MarkStep = 0;

wchar_t y[50];
wchar_t mine[50];
wchar_t m_over_tips[50];
wchar_t mine_remain[50];


//���һ������������Ϣ
MOUSEMSG m_mouse;
int array_x = 0;//��Ϊ��굥��ʱ��ת���������±�������
int array_y = 0;
int position_x = 0;//��Ϊ�ڽ�����ʵ�ʵ�����
int position_y = 0;

//�����жϵ㿪�ĵط��ǲ�����
int judge_mine = 0;
//�����ж���Ϸ�Ƿ��Ѿ�������
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
	//�����жϵ㿪�ĵط��ǲ�����
	judge_mine = 0;
	//�����ж���Ϸ�Ƿ��Ѿ�������
	judgeend = 0;
	judgesuc = 0;
}
//�˺����������ǣ�����������ת����������±�
void trans_array(int mouse_x, int mouse_y)
{
	array_x = mouse_x / 20 - 1;
	array_y = mouse_y / 20 - 1;

	//cout << "trans_array"<<array_x << "  " << array_y << endl;
}
//�˺����������ǣ���������±�ת����ʵ�ʵ�����
void trans_position(int x, int y)
{
	position_x = x * 20 + 10 + 20;
	position_y = y * 20 + 10 + 20;

	//cout << "trans_position" << position_x << "  " << position_y << endl;

}
//��ʼ��ͼ�ν���
int m_choicescreen()
{
	border_x = 10 + MAX_X * 20 + 10 + 10;
	border_y = 10 + MAX_Y * 20 + 10 + 10;
	//��ʼ������
	//���ñ�����ɫΪ��ɫ
	initgraph(350, 340);
	setbkcolor(WHITE);
	cleardevice();
	//�ı����
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"mine_sweeper");
	// ��ͼģʽ����
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
	cleardevice();//����
	return m;


}
//���������ڲ�����
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
			&& (y != avoid_y - 1 || x != avoid_x + 1)))//�ܿ���һ�ε��λ����Χ�γɵľŹ���������
			inner_mine[y][x] = '*';
		else
			i--;
	}//�������50��*�ұ�֤ͬһλ�ò��ظ�����*
}
//������������Χָ����Χ�ڵ�����
void count(int range_x1, int range_x2, int range_y1, int range_y2, int i, int j)
{
	int jishu = 0;
	for (int n = range_y1; n <= range_y2; n++)
		for (int m = range_x1; m <= range_x2; m++)
			if (inner_mine[n][m] == '*')
				jishu++;
	inner_mine[i][j] = static_cast<char>(jishu + '0');
}
//�����ڲ����飬ɨ������Ϸʵ���������ڲ�������ʹ��
void base(int avoid_x, int avoid_y)
{
	srand((unsigned int)(time(0)));
	form_mine(avoid_x, avoid_y);
	for (int i = 0; i < MAX_Y; i++) {//��ͷ��β����һ��
		for (int j = 0; j < MAX_X; j++) {
			if (inner_mine[i][j] != '*') {//�������*��Ҫȥ����Χ�Ź�����*�ĸ���
				if (i == 0 && j == 0)//���Ͻ�
					count(0, 1, 0, 1, i, j);

				if (i == 0 && j == MAX_X - 1)//���Ͻ�
					count(MAX_X - 2, MAX_X - 1, 0, 1, i, j);

				if (i == MAX_Y - 1 && j == 0)//���½�
					count(0, 1, MAX_Y - 2, MAX_Y - 1, i, j);

				if (i == MAX_Y - 1 && j == MAX_X - 1)//���½�
					count(MAX_X - 2, MAX_X - 1, MAX_Y - 2, MAX_Y - 1, i, j);

				if (i == 0 && j >= 1 && j <= MAX_X - 2)//�ϱ�
					count(j - 1, j + 1, 0, 1, i, j);

				if (i == MAX_Y - 1 && j >= 1 && j <= MAX_X - 2)//�±�
					count(j - 1, j + 1, MAX_Y - 2, MAX_Y - 1, i, j);

				if (j == 0 && i >= 1 && i <= MAX_Y - 2)//���
					count(0, 1, i - 1, i + 1, i, j);

				if (j == MAX_X - 1 && i >= 1 && i <= MAX_Y - 2)//�ұ�
					count(MAX_X - 2, MAX_X - 1, i - 1, i + 1, i, j);
				//���ߵĴ�������

				if (i <= MAX_Y - 2 && i >= 1 && j >= 1 && j <= MAX_X - 2)//�м�
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
//��������ѡ���ģʽ���趨����
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
	}//����ѡ���ģʽѡ�����Ĵ�С

}
//������ʾʣ�µ�δɨ����������
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
	swprintf(mine_remain, 50, L"ʣ��������%d", num);
	settextcolor(C_text);
	settextstyle(15, 0, L"����");
	outtextxy(10, border_y + 5, mine_remain);
}
//������Ϸ����
void graph()
{
	border_x = 10 + MAX_X * 20 + 10 + 10;
	border_y = 10 + MAX_Y * 20 + 10 + 10;
	//��ʼ������
	//���ñ�����ɫΪ��ɫ
	initgraph(border_x, border_y + 20);
	setbkcolor(WHITE);
	cleardevice();
	//�ı����
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, L"mine_sweeper");
	// ��ͼģʽ����
	setbkmode(TRANSPARENT);

	//���������ɫ
	setfillcolor(C_fold);
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			solidcircle(j * 20 + 30, i * 20 + 30, radius);//������ʼ����
		}
	}
	//�����б��б�
	settextstyle(10, 0, L"����");
	settextcolor(C_text);
	for (int i = 0; i < MAX_Y; i++) {
		swprintf(y, 29, L"%d", i + 1);//��һ�仰ѧ�ŵ�
		outtextxy(2, i * 20 + 30, y);
	}
	for (int j = 0; j < MAX_X; j++) {
		swprintf(y, 29, L"%d", j + 1);//��һ�仰ѧ�ŵ�
		outtextxy(j * 20 + 30, 2, y);
	}
}
//����������Ҫչ������
void jiansuo(int x1, int y1)
{
	if (x1 != 0) {
		for (int i = x1 - 1; i >= 0; i--) {
			if (inner_mine[y1][i] == '0' && mark[y1][i] == '\0') {
				print[y1][i] = inner_mine[y1][i];//�����λ�����㣬����û�б���ǹ������ڼ�¼�����б��1
			}
			//�������ֿ϶������������֣��������ף����Բ����ڼ������׵����
			else {
				print[y1][i] = inner_mine[y1][i];//����һ�����������㣬�ͱ�Ǻ���һ���ַ�������ֹͣ����
				break;
			}
		}
	}
	//����������ǰ����x!=MAX_X-1
	if (x1 != MAX_X - 1) {
		for (int i = x1 + 1; i < MAX_X; i++) {
			if (inner_mine[y1][i] == '0' && mark[y1][i] == '\0') {
				print[y1][i] = inner_mine[y1][i];//�����λ�����㣬���ڼ�¼�����б��1
			}
			//�������ֿ϶������������֣��������ף����Բ����ڼ������׵����
			else {
				print[y1][i] = inner_mine[y1][i];//����һ�����������㣬�ͱ�Ǻ���һ���ַ�������ֹͣ����
				break;
			}
		}
	}
	//���ϼ�����ǰ����y!=0
	if (y1 != 0) {
		for (int j = y1 - 1; j >= 0; j--) {
			if (inner_mine[j][x1] == '0' && mark[j][x1] == '\0') {
				print[j][x1] = inner_mine[j][x1];//�����λ�����㣬���ڼ�¼�����б��1
			}
			//�������ֿ϶������������֣��������ף����Բ����ڼ������׵����
			else {
				print[j][x1] = inner_mine[j][x1];//����һ�����������㣬�ͱ�Ǻ���һ���ַ�������ֹͣ����
				break;
			}
		}
	}
	if (y1 != MAX_Y - 1) {
		for (int j = y1 + 1; j <= MAX_Y - 1; j++) {
			if (inner_mine[j][x1] == '0' && mark[j][x1] == '\0') {
				print[j][x1] = inner_mine[j][x1];//�����λ�����㣬���ڼ�¼�����б��1
			}
			//�������ֿ϶������������֣��������ף����Բ����ڼ������׵����
			else {
				print[j][x1] = inner_mine[j][x1];//����һ�����������㣬�ͱ�Ǻ���һ���ַ�������ֹͣ����
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
		judge_mine = 1;//����㿪������

	if (mark[array_y][array_x] == '\0') {//������з��ű�ǵĻ����ͽ����Ǳ�Ǿͺ��ˣ�û�б�Ҫ���м���//�ڸ���ӡ���鸳ֵ֮ǰ�����ж��˵㿪��λ���ǲ�����
		print[array_y][array_x] = inner_mine[array_y][array_x];
		while (1 && judge_mine != 1) {
			judge_ = 0;
			for (i = 0; i < MAX_Y; i++) {//����һ��zero����
				for (j = 0; j < MAX_X; j++) {
					if (print[i][j] != '\0' && already[i][j] == 0 && inner_mine[i][j] == '0') {//�����һ��Ϊ�㱻��ǹ�������ȴû�м�����
						x1 = j;
						y1 = i;
						judge_ = 1;//��ʾ������һ��û�н���sousuo�����Ҫ�˳��������Ը����������
						break;
					}
				}
				if (judge_ == 1)
					break;
			}

			if (i >= MAX_Y && j >= MAX_X) {
				break;//˵���Ѿ�ȫ�������꣬���Կ�ʼ��ӡ��
			}
			if (judge_ == 1) {
				jiansuo(x1, y1);
				already[y1][x1] = 1;//���Ϊ1����ʾ�Ѿ���һ��0�Ѿ�������
			}
		}
	}
}
//����һ��������ӡչ������ĺ���
void print_unfold()
{
	int c = 0;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (print[i][j] != '\0') {//˵������չ��
				trans_position(j, i);
				setfillcolor(C_unfold);
				solidcircle(position_x, position_y, radius);//��ӡ��չ������ɫ
				//���Ұ��ڲ������ӡ��ȥ
				if (inner_mine[i][j] != '0') {
					swprintf(mine, 29, L"%c", inner_mine[i][j]);//��һ�仰ѧ�ŵ�
					c = inner_mine[i][j] - '0' - 1;
					settextcolor(N_COLOR[c]);
					settextstyle(10, 0, L"����");
					outtextxy(position_x, position_y, mine);
				}
			}
		}
	}
	cout << "����print_unfold" << endl;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			cout << print[i][j] << "  ";
		}
		cout << endl;
	}
}
//����һ��������ȡ���λ�õĺ���,����������ת����������±�
void read_mouse_action()
{
	UnfoldStep = 0;
	UnfoldStep = 0;
	while (1) {
		m_mouse = GetMouseMsg();//��ù���������Ϣ
		if (m_mouse.uMsg == WM_LBUTTONDOWN)//����õ�����Ϣ���������������������귶Χ
			//Ҫע�������������±��ͳһ
		{
			UnfoldStep = 1;//��������������˵������������չ���Ĳ���
			cout << "UnfoldStep" << endl;
			trans_array(m_mouse.x, m_mouse.y);//����ʱ��������ת����������±�
			break;
		}
		else if (m_mouse.uMsg == WM_RBUTTONDOWN) {//����õ�����Ϣ���Ҽ����£����������Ǳ�ǵĲ���
			MarkStep = 1;
			cout << "MarkStep" << endl;
			trans_array(m_mouse.x, m_mouse.y);//����ʱ��������ת����������±�
			break;
		}
	}
}
//�����ж������λ���ǲ�������
void judge_if_mine()
{
	if (inner_mine[array_y][array_x] == '*') {
		judge_mine = 1;//����㿪������
		judgeend = 1;
	}
	cout << "����judge_if_mine" << endl;
}
//��������ˣ��Ͱ����е���ȫ��չ����
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
//�������б�ǵĲ���
void Mark() {
	if (mark[array_y][array_x] == '\0' && print[array_y][array_x] == '\0')//����һ���λ����β�㣬˵����λ����û�б���ǹ��ģ�����Ҳû��չ���ģ��Ǿͱ�ǳ�1
		mark[array_y][array_x] = '1';
	else if (mark[array_y][array_x] != '\0') {//����һ���λ�ò���β�㣬˵����ʱ�Ĳ���Ӧ���ǽ����ǣ��ǾͰ����ָ���β�㣬���Ҹ����ָ�������ɫ
		mark[array_y][array_x] = '\0';
		setfillcolor(C_fold);
		trans_position(array_x, array_y);
		solidcircle(position_x, position_y, radius);
	}
	cout << "����Mark" << endl;
}
void PrintMark()
{
	setfillcolor(C_mark);
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (mark[i][j] != '\0') {//��������ǹ�
				trans_position(j, i);
				solidcircle(position_x, position_y, radius);
			}
		}
	}
	cout << "����PrintMark" << endl;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			cout << mark[i][j] << "  ";
		}
		cout << endl;
	}
}
//������һ��
void first_step()
{
	//������Ϸ����
	graph();
	//ѡ���һ�ε㿪��λ��
	read_mouse_action();
	//�ܿ���һ�ε㿪��λ�������ף������γ��ڲ�����
	base(array_x, array_y);
	//Ȼ��Ϳ��Կ�ʼ���е�һ��չ����
	_judge_unfold();
	//Ȼ��Ͱ�print��ǵ�չ�����ͺ���
	print_unfold();

}
//�ж��Ƿ��Ѿ��ɹ��ˣ����Ƿ��Ѿ������е��׶�ɨ������
void judge_if_succeed()
{//��û�д�ӡ�ĵط����׵ĸ���һ�����ʱ���˵�������ˣ��ɹ���
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

		//��ѡ��ģʽ������ѡ���ģʽȥ���ɶ�Ӧ������
		choice_mode = m_choicescreen();
		if (choice_mode == '0')
			break;
		else {
			set_parameters(choice_mode);
			//�ڲ�����������֮�󣬾�Ҫ��������Ϸ���棬Ȼ����ѡ���һ��Ҫ�㿪���Ǹ����꣬�ܿ���һ�ε㿪�������������ڲ����飬Ȼ����չ��

			first_step();

			//���������������ڲ�����֮�����������
			while (!judgeend && !judgesuc) {
				read_mouse_action();//��ȥ�����
				if (UnfoldStep) {//����õ�����Ϣ�ǽ���չ������
					if (mark[array_y][array_x] == '\0') {//����㿪�ĵط�û�б���ǹ�
						judge_if_mine();//���жϵ㿪�ĵط��ǲ�������
						if (!judgeend) {//�㿪��λ�ò����ף���Ϸû�н���������Ҫȥ������������չ��
							_judge_unfold();
							print_unfold();
						}
						if (judgeend) {//�㿪��������
							print_mine();
						}
					}
				}
				else if (MarkStep) {//������õ�����Ϣ���һ���˵���Ǳ�ǵĲ���
					Mark();
					PrintMark();
				}
				judge_if_succeed();
			    //cout << "judgeend" << judgeend << endl;
			}
			remained_mine();
			if (judgeend) {
				swprintf(m_over_tips, 39, L"�ȵ�����\n����һ����");//�����𣿣�
				if (MessageBox(GetHWnd(), m_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
					break;
			}
			else if (judgesuc) {
				swprintf(m_over_tips, 39, L"��������ɨ��С������\n����һ����");//�����𣿣�
				if (MessageBox(GetHWnd(), m_over_tips, L"end", MB_ICONQUESTION | MB_YESNO) == IDNO)
					break;
			}
		}
	}
}
