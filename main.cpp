#include <graphics.h>
#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <math.h>

using namespace std;

void start()
{
	setbkcolor(BLACK);
	cleardevice();
	setlinecolor(WHITE);
	line(0, 240, 640, 240);
	line(320, 0, 320, 480);
	for (int i = 0; i <= 640; i += 10)
	{
		for (int j = 0; j <= 480; j += 10)
		{
			putpixel(i, j, LIGHTGRAY);
		}
	}
}

void two(int a, int b, int c)
{
	double a1 = double(a), b1 = double(b), c1 = double(c);
	double x, y, xx, yy, xxx, yyy;
	setlinecolor(YELLOW);
	x = -32;
	y = a1 * x * x + b1 * x + c1;
	xxx = xx = round(x * 10 + 320);
	yyy = yy = round(y * (-10) + 240);
	line(xx, yy, xx, yy);
	for (x = -31.9; x <= 32; x += 0.1)
	{
		if (x != 0)
		{
			y = a1 * x * x + b1 * x + c1;
			xx = round(x * 10 + 320);
			yy = round(y * (-10) + 240);
			line(xx, yy, xxx, yyy);
			xxx = round(x * 10 + 320);
			yyy = round(y * (-10) + 240);
		}
	}
}
void one(int k, int b)
{
	b = b * 10;
	setlinecolor(GREEN);
	int x, y; int xx, yy; int xxx, yyy;
	{
		x = -320;
		y = k * x + b;
		xxx = xx = x + 320;
		yyy = yy = -y + 240;
		line(xx, yy, xx, yy);
		for (int x = -319; x <= 320; x++)
		{
			y = k * x + b;
			xx = x + 320;
			yy = -y + 240;
			line(xx, yy, xxx, yyy);
			xxx = x + 320;
			yyy = -y + 240;
		}
	}
}
void minus_one(int k)
{
	double k1 = double(k);
	double x, y, xx, yy, xxx, yyy;
	setlinecolor(LIGHTBLUE);
	x = -32;
	y = k * 1.0 / x;
	xxx = xx = round(x * 10 + 320);
	yyy = yy = round(y * (-10) + 240);
	line(xx, yy, xx, yy);
	for (x = -31.9; x <= 32; x += 0.1)
	{
		if (x != 0)
		{
			y = k / x;
			xx = round(x * 10 + 320);
			yy = round(y * (-10) + 240);
			line(xx, yy, xxx, yyy);
			xxx = round(x * 10 + 320);
			yyy = round(y * (-10) + 240);
		}
	}
}

void input()
{
	char type;
	int a, b, c;
	int k;//b
	//int k;
	cout << "输入:\n2:y=ax^2+bx+c;\n:->y=kx+b;\n0:y=k/x\n";
	cin >> type;
	switch (type)
	{
	case '2':
		cout << "y=ax^2+bx+c\n";
		cout << "a=";
		cin >> a;
		cout << '\n';
		cout << "b=";
		cin >> b;
		cout << '\n';
		cout << "c=";
		cin >> c;
		cout << '\n';
		//initgraph(640,480,SHOWCONSOLE);	
		two(a, b, c); break;

	case '1':
		cout << "k=\n";
		cin >> k;
		cout << '\n';
		cout << "b=\n";
		cin >> b;
		cout << '\n';
		//initgraph(640,480,SHOWCONSOLE);
		one(k, b);
		break;
	case '0':
		cout << "k=\n";
		cin >> k;
		cout << '\n';
		//initgraph(640,480,SHOWCONSOLE);	
		minus_one(k);
		break;
	}
}

int main()
{
	initgraph(640, 480, SHOWCONSOLE);
	/*
		SHOWCONSOLE  显示小黑窗
		NOCLOSE      no close
		NOMINIMIZE   no 最小化
		DBLCLKS      在绘图窗口中支持鼠标双击事件
	*/
	start();
	input();
	_getwch();
	closegraph();
	return 0;
}