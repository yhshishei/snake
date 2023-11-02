#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#define num 200//蛇的最大节数
//枚举蛇可能的运动方向
enum dir
{
	up,
	down,
	left,
	right,
};
//蛇的结构
struct snakes
{
	int size;//蛇的位置
	int direction;//蛇的运动方向
	int speed;//蛇的运动速度
	POINT loca[num];
}snake;
//食物的结构
struct Food
{
	int x, y;
	int r;
	bool flag;
	DWORD color;
}food;

//游戏初始化
void begin()
{

	//初始化图像窗口
	initgraph(500, 500);
	srand(GetTickCount());
	//初始化蛇
	snake.size = 5;
	snake.speed = 10;
	snake.direction;
	snake.loca[0].x = 200;
	snake.loca[0].y = 200;
	int i;
	for (i = 1; i < 5; i++)
	{
		snake.loca[i].x = 200;
		snake.loca[i].y = snake.loca[i - 1].y - 10;
	}
	//初始化食物
	food.x = rand() % 500;
	food.y = rand() % 500;
	food.r = 10;
	food.flag = true;
	
}
//画初始的蛇
void paint()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(283, 843, 94));
	cleardevice();
	setfillcolor(YELLOW);
	int i;
	for (i = 0; i < snake.size; i++)
	{
		solidcircle(snake.loca[i].x, snake.loca[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
		food.color = RGB(rand() & 256, rand() & 256, rand() & 256);
	}
	EndBatchDraw();
}
//蛇的移动
void move()
{
	if (_kbhit())
	{
		switch (snake.direction)
		{
		case up:
			snake.loca[0].y -= snake.speed;
			if (snake.loca[0].y == 0)
			{
				snake.loca[0].y = 500;
			}
			break;
		case down:
			snake.loca[0].y += snake.speed;
			if (snake.loca[0].y == 500)
			{
				snake.loca[0].y = 0;
			}
			break;
		case left:
			snake.loca[0].x -= snake.speed;
			if (snake.loca[0].x == 0)
			{
				snake.loca[0].x = 500;

			}
			break;
		case right:
			snake.loca[0].x += snake.speed;
			if (snake.loca[0].x == 500)
			{
				snake.loca[0].x = 0;
			}
			break;
		}
		int i;
		for (i = snake.size - 1; i > 0; i--)
		{
			snake.loca[i].x = snake.loca[i - 1].x;
			snake.loca[i].y = snake.loca[i - 1].y;
		}
	}
}
//通过按键确定蛇的运动方向
void key()
{
	if (_kbhit())
	{
		//键值72 80 75 77 上下左右
		switch (_getch())
		{
		case 72:
			if (snake.direction != down)
			{
				snake.direction = up;
			}
			break;
		case 80:
			if (snake.direction != up)
			{
				snake.direction = down;
			}
			break;
		case 75:
			if (snake.direction != right)
			{
				snake.direction = left;
			}
			break;
		case 77:
			if (snake.direction != left)
			{
				snake.direction = right;
			}
			break;
		case ' ':
			while (1)
			{
				if (_getch() == ' ')
					return;
			}
			break;

		}
	}
}
//是否吃了食物
void eat()
{
	if (food.flag && snake.loca[0].x >= food.x - food.r && snake.loca[0].x <= food.x + food.r && snake.loca[0].y >= food.y - food.r && snake.loca[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	//食物被吃，就会出现新的食物
	if (!food.flag)
	{
		food.x = rand() % 500;
		food.y = rand() % 500;
		food.r = 10;
		food.flag = true;
		food.color = RGB(rand() & 256, rand() & 256, rand() & 256);
	}
}
//主函数
int main()
{
	begin();


	while (1)
	{
		paint();
		key();
		move();
		paint();
		eat();
		Sleep(10);
	}
	return 0;
}
