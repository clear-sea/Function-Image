#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<ctime>
#include<Windows.h>
#include<tchar.h>
#include<cmath>
#include<vector>

using namespace std;
/*全局变量(默认量)*/
int toolNavWidth = 100;					// 工具栏宽度(高度和窗口高度相同)
int canvasWidth = 400;					// 画布宽度(高度和窗口高度相同)
int msgNavWidth = 100;					// 消息栏的宽度
int width = canvasWidth + toolNavWidth + msgNavWidth, height = 400;				// 绘图窗口默认宽和高
int scale = 10;							// 默认缩放
int msgFontSize = 20;					// 信息文本的字体大小
int halfCW = round(canvasWidth / 2);	// 画布一半的宽度
int halfH = round(height / 2);			// 高度的一半
COLORREF functionImageColor = BLUE;		// 默认函数图像颜色
vector<string> functionsList;			// 函数列表

// 函数实现
using funp = int(*)(int);

// 查找一个字符是否在一个(C语言风格)字符串内,找到了返回下标,找不到返回-1
int find(const char* str, char c) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == c) {
			return i;  // 找到了返回下标
		}
	}
	return -1; // 找不到返回-1
}
/*把字符串表达式转化为函数并返回*/
funp getFunction(string strExpression) {
	// 如果字符串为空直接结束
	if (strExpression.empty()) {
		return nullptr;
	}
	// 字符串不为空则继续
	int length = strExpression.size();
	string expression;
	// 去除空格并储存到expreesion中
	for (int i = 0; i < length; i++) {
		if (strExpression[i] != ' ') {
			expression += strExpression[i];
		}
	}
	// 处理字符串表达式
	length = expression.size();
	string num;
	double k, b;		// k和b
	double x, y;		// 自变量x和因变量y
	// 判断字符串表达式是否符合语法规范
	if (expression[0] != 'y' || expression[1] != '=') { // 首先判断是否符合"y=..."
		return nullptr;
	}
	for (int i = 0; i < length; i++) {
		// 再判断每个字符
		if ((expression[i] < '0' || expression[i]>'9') && (expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '^' && expression[i] != '(' && expression[i] != ')')) {
			// 如果这个字符既不是数字也不是支持的运算符
			return nullptr;
		}
	}

	// 如果符合规范就继续
	if (expression.find('.') == string::npos) { // 如果没有小数点
		for (int i = 1; i < length; i++) {
			if (expression[i] < '9' && expression[i]>'0') {
				num += expression[i];
			}
			else if (expression[i] == 'x') {
				// 如果遇到自变量x，就把x前面部分的字符串转化为整数(整型k)
				k = atoi(num.c_str());
			}
			else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
				// 如果是运算符

			}
		}
	}
	else { // 如果有小数点
		for (int i = 1; i < length; i++) {
			if ((expression[i] < '9' && expression[i]>'0') || expression[i] == '.') {
				num += expression[i];
			}
			else if (expression[i] == 'x') {
				k = atof(num.c_str());
			}
		}
	}

	cout << expression << endl;
	return nullptr;
}
// 传入数学坐标系中的坐标，返回画布的坐标(横坐标)
int offsetX(int x) {
	return (x + halfCW);
}
// 传入数学坐标系中的坐标，返回画布的坐标(纵坐标)
int offsetY(int y) {
	if (y > 0) {
		return (halfH-y);
	}
	else if (y == 0) {
		return halfH;
	}
	else {
		return ((-y) + halfH);
	}
}
// 正比例函数
void positiveProportionalFunc(float k) {
	setlinecolor(BLUE);
	line(offsetX(-halfCW), offsetY(round((-halfCW) * k)), offsetX(halfCW), offsetY(round(halfCW * k)));
}
// 一次函数
void linearFunc(float k,float b) {
	b *= scale;
	for (int x = -halfCW; x < halfCW; x++){
		putpixel(offsetX(x), offsetY(round(k * x + b)), RGB(255, 184, 32));
	}
}
// 反比例函数
void inverseProportionalFunc(float k) {
	double x, y, xCanvas, yCanvas, xLast, yLast;
	setlinecolor(GREEN);
	x = -(halfCW*1.0/scale);
	y = k * 1.0 / x;
	xLast = xCanvas = offsetX(round(x * scale));
	yLast = yCanvas = offsetY(round(y * (-scale)));
	line(xCanvas, yCanvas, xCanvas, yCanvas);
	for (x = -(halfCW*1.0/scale); x <= (halfCW*1.0/scale); x += 0.1) {
		if (x != 0)
		{
			y = k * 1.0 / x;
			xCanvas = offsetX(round(x * scale));
			yCanvas = offsetY(round(y * (-scale)));
			line(xCanvas, yCanvas, xLast, yLast);
			xLast = xCanvas;
			yLast = yCanvas;
		}
	}
}
// 二次函数
void quadraticFunc(float a, float b, float c) {
	c *= scale;
	int xLast=offsetX(-halfCW), yLast=offsetY(round(a*(-halfCW)*(-halfCW)+b*(-halfCW)+c));	// 上一个点坐标
	int x=0, y=0;
	setlinecolor(RGB(255, 130, 0));
	for (int i = -halfCW+1; i <= halfCW; i++) {
		x = offsetX(i);
		y = offsetY(round(a * i * i + b * i + c));
		line(xLast, yLast, x, y);	// 连点成线
		xLast = x, yLast = y;
	}
}
// 幂函数
void powerFunc(float a) {
	int xLast = offsetX(-halfCW), yLast = offsetY(round(pow((-halfCW),a)));	// 上一个点坐标
	int x = 0, y = 0;
	setlinecolor(RED);
	for (int i = -halfCW+1; i <= halfCW; i++) {
		x = offsetX(i);
		y = offsetY(round(pow(i,a)));
		line(xLast, yLast, x, y);	// 连点成线
		xLast = x, yLast = y;
	}
}
/*Button类*/
class Button {
public:
	int posX, posY, posXRight, posYBottom;
	int btnWidth = round(toolNavWidth * 0.7), btnHeight = round(btnWidth * 0.3);
	int textX, textY;
	const char* text;
	// 构造函数——自动居中
	Button(int posY, const char* text) {
		this->posX = round((toolNavWidth - btnWidth) / 2) + canvasWidth;
		this->posY = posY;
		posXRight = posX + btnWidth;
		posYBottom = posY + btnHeight;
		this->text = text;
	}
	// 构造函数——设置位置和大小
	Button(int posX, int posY, int width, int height, const char* text) {
		this->posX = posX + canvasWidth;
		this->posY = posY;
		btnWidth = width;
		btnHeight = height;

		posXRight = posX + btnWidth;
		posYBottom = posY + btnHeight;

		this->text = text;
	}
	void show() {
		setlinecolor(RGB(127,127,127));
		setfillcolor(WHITE);
		fillrectangle(this->posX, this->posY, this->posXRight, this->posYBottom);
		showText();
	}
	void showText() {
		char text_[50] = { 0 };
		strcpy_s(text_, text);
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(round(btnWidth / 4), 0, "微软雅黑");
		textX = posX + (btnWidth - textwidth(text)) / 2;
		textY = posY + (btnHeight - textheight(text)) / 2;
		outtextxy(textX, textY, text_);
	}
	// 按钮被点击时执行传入的函数
	void onButtonClick() {
		setlinecolor(BLACK);
		setfillcolor(RGB(173, 255, 242));
		fillrectangle(this->posX, this->posY, this->posXRight, this->posYBottom);
		showText();
	}
	// 鼠标按键抬起
	void onButtonUp(void (*func)()) {
		setlinecolor(RGB(127,127,127));
		setfillcolor(WHITE);
		fillrectangle(this->posX, this->posY, this->posXRight, this->posYBottom);
		showText();
		(*func)();
	}
};
/*鼠标滚轮缩放*/
void resetScale() {

}
/*清理指定区域*/
void clearArea(int x1, int y1, int x2, int y2, COLORREF bgColor) {
	setfillcolor(bgColor);
	setlinecolor(bgColor);
	fillrectangle(x1, y1, x2, y2);
}
/*启动画面*/
void splashScreen() {
	IMAGE splashImage;
	int splashImageSize = round(min(width, height) * 0.7);
	loadimage(&splashImage, "icon.png", splashImageSize, splashImageSize);
	putimage(round((width - splashImageSize) / 2), round((height - splashImageSize) / 2), &splashImage);
	Sleep(2000);
	cleardevice();
}
/*初始化画布*/
void initCanvas() {
	clearArea(0, 0, canvasWidth, height, BLACK);
	// 画出参照点
	for (int i = 0; i <= canvasWidth; i += 10) {
		for (int j = 0; j <= height; j += 10) {
			putpixel(i, j, LIGHTBLUE);
		}
	}
	// 画出坐标轴
	setlinecolor(YELLOW);
	line(0, round(height / 2), canvasWidth, round(height / 2));	// x轴
	line(round(canvasWidth / 2), 0, round(canvasWidth / 2), height); // y轴
}
void initToolNav() {
	// 绘出基础工具栏
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(canvasWidth, 0, width - msgNavWidth, height);
}

void initMsgNav() {
	// 绘出基础消息栏
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(canvasWidth + toolNavWidth, 0, width, height);
}

void initWindow() {
	// 初始化
	initCanvas();
	initToolNav();
	initMsgNav();
}
/*重置窗口大小*/
void resetWindowSize(int width, int height) {
	Resize(NULL, width, height);
	initWindow();
}
/*显示消息*/
void showMsg(const char* text, COLORREF textColor) {
	char text_[50] = { 0 };
	strcpy_s(text_, text);
	settextcolor(textColor);
	setbkmode(TRANSPARENT);
	settextstyle(msgFontSize, 0, "微软雅黑");
	int textX = (msgNavWidth - textwidth(text)) / 2 + canvasWidth + toolNavWidth;
	BeginBatchDraw();
	for (int i = height; i >= 10; i -= 3) {
		FlushBatchDraw();
		initMsgNav();
		outtextxy(textX, i, text_);
		Sleep(1);
	}
	EndBatchDraw();

	initMsgNav();
}
/*输入值并返回数值(InputBox)*/
float inputNum(const char* prompt, const char* title = "输入") {
	char content[1000];
	float result;
	InputBox(content, 1000, prompt, title);
	if (strlen(content) > 0) {
		result = atof(content);
		return result;
	}
	else {
		showMsg("参数为空", RED);
	}
}
/*获取用户输入函数(InputBox)*/
void inputFunction() {
	char choice[3];
	char content[1000];
	/*InputBox(content, 1000, "输入函数表达式", "输入");
	functionsList.push_back(content);
	if (strlen(content) == 0) {
		showMsg("表达式为空", RED);
	}
	getFunction(content);*/

	int minChoice = 1, maxChoice = 5; // 最小和最大选择范围
	if (InputBox(choice, 3, "1.正比例函数\n2.一次函数\n3.反比例函数\n4.二次函数\n5.幂函数\n选择函数表达式类型:", "输入", 0, 0, 0, false)) {
		// 如果没有按"取消"
		int choiceNum = choice[0] - 48;
		if (choiceNum<minChoice||choiceNum>maxChoice) { // 判断是否在选择范围内,如果不在内就结束
			showMsg("不在选择范围内",RED);
			return;
		}
		if (choiceNum==1) {
			float k=inputNum("输入k:");
			positiveProportionalFunc(k);
		}
		else if(choiceNum==2) {
			float k = inputNum("输入k:");
			float b = inputNum("输入b:");
			linearFunc(k, b);
		}
		else if (choiceNum == 3) {
			float k = inputNum("输入k");
			inverseProportionalFunc(k);
		}
		else if (choiceNum == 4) {
			float a = inputNum("输入a:");
			float b = inputNum("输入b:");
			float c = inputNum("输入c:");
			quadraticFunc(a, b, c);
		}
		else if (choiceNum == 5) {
			float a = inputNum("输入a:");
			powerFunc(a);
		}
	}
}