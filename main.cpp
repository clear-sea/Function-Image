#include<iostream>
#include<graphics.h>
#include<string>
#include<ctime>
#include<Windows.h>
#include<tchar.h>
#include<cmath>
#include<vector>
//#include "function.h"
#include "base.hpp"

using namespace std;

/*主函数*/
int main() {
	// 初始化绘图窗口
	initgraph(width, height);
	setbkcolor(BLACK);
	cleardevice();
	// 启动画面
	splashScreen();
	// 初始化
	initWindow();
	// 按钮
	Button newFunc(15, "绘制函数"), clearCanvas(50, "清空画布");
	newFunc.show();
	clearCanvas.show();
	// 循环监测鼠标键盘信息
	ExMessage m;
	while (true) {
		m = getmessage(EX_MOUSE | EX_KEY);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x>newFunc.posX&&m.x<newFunc.posXRight&&m.y>newFunc.posY&&m.y<newFunc.posYBottom) {
				newFunc.onButtonClick();
			}
			else if (m.x > clearCanvas.posX && m.x<clearCanvas.posXRight && m.y>clearCanvas.posY && m.y < clearCanvas.posYBottom) {
				clearCanvas.onButtonClick();
			}
		}
		else if (m.message == WM_LBUTTONUP) {
			if (m.x > newFunc.posX && m.x<newFunc.posXRight && m.y>newFunc.posY && m.y < newFunc.posYBottom) {
				newFunc.onButtonUp(inputFunction);
			}
			else if (m.x > clearCanvas.posX && m.x<clearCanvas.posXRight && m.y>clearCanvas.posY && m.y < clearCanvas.posYBottom) {
				clearCanvas.onButtonUp(initCanvas);
			}
		}
	}
	// 关闭绘图窗口
	getmessage(EX_KEY);
	closegraph();
	return 0;
}