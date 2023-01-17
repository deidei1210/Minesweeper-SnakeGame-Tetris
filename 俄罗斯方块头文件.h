#pragma once
//定义的形状名称
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
//该函数的作用是最初随机生成一个俄罗斯方块,并把随机生成的数赋值给记录shape的结构体
void t_trans(int& trans_x, int& trans_y, int X, int Y, int i);
void t_over();
void t_form_shape_now(int X, int Y);
//用于提前生成下一个要下降的方块
void t_form_shape_next();
void t_first_round_shape();
//该函数可以用来在指定的位置画出一个指定的形状
void t_draw_circle_group(int X, int Y);
//该函数可以在指定位置擦去一个指定的形状
void t_clear_circle_group(int X, int Y);
//从(X,Y)的地方开始下降,以speed的速度
//下降到什么地方停下来，也是需要当心的
void t_mark_position(int X, int Y);
void t_draw_next();
int t_cmd();
void t_react(int m, int& x, int& y);
//用来在下降过程中判断是否已经到底(底是y=310的地方)
int t_bottom(int X, int Y);
//该函数可以用来初始化
void t_guiling_per();
void t_judge_clean_hang();
void t_guiling();
void t_clear_next();
void t_end_clear();
//写一个可以把数字转换成字符的函数
void t_int_to_char(int num);
//此函数可以用来排序
void TetrisGame();
void mine_sweeper();
void SnakeGame();
void SignIn();

