#include <graphics.h>
#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>

using namespace std;

void start()
{
	setbkcolor(BLACK);
	cleardevice();
	setlinecolor(WHITE);
	line(0,240,640,240);
	line(320,0,320,480);
	for(int i=0;i<=640;i+=10)
	{
		for(int j=0;j<=480;j+=10)
		{
			putpixel(i,j,LIGHTGRAY);
		}
	}	
}

	void two(int a,int b,int c)
	{
		setlinecolor(YELLOW);
		int x,y;int xx,yy;int xxx,yyy;
		{
			x=-320;
			y=a*x*x+b*x+c;
			xxx=xx=x+320;
			yyy=yy=-y+240;	
			line(xx,yy,xx,yy);
			for(int x=-319;x<=320;x++)
			{
				y=a*x*x+b*x+c;
				xx=x+320;
				yy=-y+240;
				line(xx,yy,xxx,yyy);
				xxx=x+320;
				yyy=-y+240;
			}
		}
	}
	void one(int k,int b)
	{
		setlinecolor(GREEN);
		int x,y;int xx,yy;int xxx,yyy;
		{
			x=-320;
			y=k*x+b;
			xxx=xx=x+320;
			yyy=yy=-y+240;	
			line(xx,yy,xx,yy);
			for(int x=-319;x<=320;x++)
			{
				y=k*x+b;
				xx=x+320;
				yy=-y+240;
				line(xx,yy,xxx,yyy);
				xxx=x+320;
				yyy=-y+240;
			}
		}
	}
	void minus_one(int k)
	{
		setlinecolor(BLUE);
		int x,y;int xx,yy;int xxx,yyy;
		{
			x=-320;
			y=k*1.0/x;
			xxx=xx=x+320;
			yyy=yy=-y+240;	
			line(xx,yy,xx,yy);
			for(int x=-319;x<=320;x++)
			{
				y=k*1.0/x;
				xx=x+320;
				yy=-y+240;
				line(xx,yy,xxx,yyy);
				xxx=x+320;
				yyy=-y+240;
			}
		}		
	}
	
void input()
{
	char type;
	int a,b,c;
	int k;//b
	//int k;
	cout<<"type:\n2->y=ax^2+bx+c;\n1->y=kx+b;\n0->y=k/x\n";
	cin>>type;
	switch(type)
	{
		case '2':
			cout<<"y=ax^2+bx+c\n";
			cout<<"a=\n";
			cin>>a;
			cout<<'\n';
			cout<<"b=\n";
			cin>>b;
			cout<<'\n';
			cout<<"c=\n";
			cin>>c;
			cout<<'\n';
			//initgraph(640,480,SHOWCONSOLE);	
			two(a,b,c);break;
						
		case '1':
			cout<<"k=\n";
			cin>>k;
			cout<<'\n';
			cout<<"b=\n";
			cin>>b;
			cout<<'\n';
			//initgraph(640,480,SHOWCONSOLE);
			one(k,b);							
			break;
		case '0':
			cout<<"k=\n";
			cin>>k;
			cout<<'\n';
			//initgraph(640,480,SHOWCONSOLE);	
			minus_one(k);
			break;
	}
}

int main()
{
	initgraph(640,480,SHOWCONSOLE);
	/*
		SHOWCONSOLE  显示小黑窗
		NOCLOSE      no close
		NOMINIMIZE   no 最小化
		DBLCLKS      在绘图窗口中支持鼠标双击事件
	*/	
	start();	
	input();
	getch();
	closegraph();
	return 0;
}