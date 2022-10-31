#include <iostream>
#include <conio.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif
using namespace std;
bool gameover;
const int width = 20;	//board width
const int height = 20;	//board height
int x, y;				//position of snake
int fruitx, fruity;		//position of fruit
int score;
int tailx[100], taily[100];
int tail;				//tail size
int speed = 60;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;
void infosetup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}
void mapdraw()
{
	//DON'T DELETE
	COORD cursorPosition;	
	cursorPosition.X = 0;	
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	for (int i = 0; i < 20; i++)
	{
		cout << " ";
	}
	for (int i = 0; i <= width + 1; i++)
	{
		cout << "@";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int i = 0; i < 20; i++)
		{
			cout << " ";
		}
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "@";
			}
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruity && j == fruitx)
			{
				cout << "A";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < tail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
			if (j == width - 1)
			{
				cout << "@";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < 20; i++)
	{
		cout << " ";
	}
	for (int i = 0; i <= width + 1; i++)
	{
		cout << "@";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'w':
			dir = UP;
			break;
		case'a':
			dir = LEFT;
			break;
		case's':
			dir = DOWN;
			break;
		case'd':
			dir = RIGHT;
			break;
		}
	}
}
void controls()
{
	//adding the tail to snake
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < tail; i++)
	{
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	//moving the snake
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if snake touches the border
	if (x > width || x<0 || y>height || y < 0)
	{
		gameover = true;
	}
	//if you touch the tail
	for (int i = 0; i < tail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
		{
			gameover = true;
		}
	}
	//if fruit it eaten
	if (x == fruitx && y == fruity)
	{
		score++;
		fruitx = rand() % width;
		fruity = rand() % height;
		tail++;
	}
	//slow down
	if (dir == LEFT || dir == RIGHT || dir == UP || dir == DOWN)
	{
		Sleep(80);
	}
}
int main()
{
	infosetup();
	while (!gameover)
	{
		mapdraw();
		input();
		controls();
	}
}
