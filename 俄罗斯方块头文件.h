#pragma once
//�������״����
#define shan 0
#define tian 1
#define yi 2
#define trans_L 3
#define L 4
#define trans_Z 5
#define Z 6

#define DOWN 7
#define LEFT 8
#define RIGHT 9
#define ROTATE 10
#define STOP 11

void t_initscreen();
void t_initscreen();
void t_initscreenstart();
void t_pause_screem();
void t_put_score();
void t_form_theme_color();
//�ú���������������������һ������˹����,����������ɵ�����ֵ����¼shape�Ľṹ��
void t_trans(int& trans_x, int& trans_y, int X, int Y, int i);
void t_over();
void t_form_shape_now(int X, int Y);
//������ǰ������һ��Ҫ�½��ķ���
void t_form_shape_next();
void t_first_round_shape();
//�ú�������������ָ����λ�û���һ��ָ������״
void t_draw_circle_group(int X, int Y);
//�ú���������ָ��λ�ò�ȥһ��ָ������״
void t_clear_circle_group(int X, int Y);
//��(X,Y)�ĵط���ʼ�½�,��speed���ٶ�
//�½���ʲô�ط�ͣ������Ҳ����Ҫ���ĵ�
void t_mark_position(int X, int Y);
void t_draw_next();
int t_cmd();
void t_react(int m, int& x, int& y);
//�������½��������ж��Ƿ��Ѿ�����(����y=310�ĵط�)
int t_bottom(int X, int Y);
//�ú�������������ʼ��
void t_guiling_per();
void t_judge_clean_hang();
void t_guiling();
void t_clear_next();
void t_end_clear();
//дһ�����԰�����ת�����ַ��ĺ���
void t_int_to_char(int num);
//�˺���������������
void TetrisGame();
void mine_sweeper();
void SnakeGame();
void SignIn();

