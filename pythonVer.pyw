import ttkbootstrap as tk
from ttkbootstrap.constants import *
import tkinter.messagebox as msg
from PIL import Image,ImageTk
import time

toolNavWidth=100
canvasWidth=400
width=toolNavWidth+canvasWidth
height=400
halfCW=round(canvasWidth/2)
halfH=round(height/2)
buttonWidth=round(canvasWidth*0.7)

window=tk.Window("Function-Image")
window.geometry(f"{width}x{height}")
window.resizable(False,False)

canvas=tk.Canvas(window,width=canvasWidth,height=height)
canvas.place(x=0,y=0)

toolNav=tk.Frame(window,width=toolNavWidth,height=height)
toolNav.place(x=canvasWidth,y=0)

# init canvas
def initCanvas():
    canvas.create_rectangle(0,0,canvasWidth,height,fill="black")
    # 画出参照点
    for i in range(0,canvasWidth,10):
        for j in range(0,height,10):
            canvas.create_oval(i,j,i+1,j+1,fill="skyblue")
    # 画出坐标轴
    canvas.create_line(0, halfH, canvasWidth, halfH,fill="yellow");	# x轴
    canvas.create_line(halfCW, 0, halfCW, height,fill="yellow"); # y轴
# 清空画布
def clearCanvas():
    canvas.delete("all")
    initCanvas()
# 检查字符串表达式是否符合语法规范    
def drawFunction(expression:str):
    # 先判断是否为空
    if len(expression)==0:
        msg.showerror("错误","表达式为空")
        return None
    # 先去掉所有的空格
    expression.replace(" ","")
    if expression[0]!="y" or expression[1]!="=":
        msg.showerror("错误","表达式错误")
        return None
    expression.replace("^","**")

    x=y=0
    xLast=yLast=0
    canvas.create_line(x,y,x+1,y+1)
    # 如果没有除以x
    if "/x" in expression:
        for x in range(1,canvasWidth):
            eval(expression)
            canvas.create_line(xLast,yLast,x,y)
            xLast=X
            yLast=y
            
# 输入框
def inputFunction():
    inputBox=tk.Toplevel(window)
    inputBox.geometry("300x150")
    inputBox.title("输入")
    inputBox.resizable(False,False)
    inputBox.attributes("-toolwindow",True)
    inputBox.protocol("WM_DELETE_WINDOW",lambda:None)

    prompt=tk.Label(inputBox,text="输入函数表达式(y=...)")
    prompt.place(x=10,y=10,width=280,height=30)

    entry=tk.Entry(inputBox)
    entry.place(x=10,y=50,width=280,height=30)

    answer=""
    def getAnswer():
        nonlocal answer
        answer=entry.get()
        
        inputBox.destroy()
    def cancel():
        nonlocal answer
        answer=None
        inputBox.destroy()

    ansButton=tk.Button(inputBox,text="确定",command=getAnswer)
    ansButton.place(x=10,y=100)
    cancelButton=tk.Button(inputBox,text="取消",command=cancel)
    cancelButton.place(x=80,y=100)
    
    return answer

def newFunction():
    expression=inputFunction()
    print(expression)
    #drawFunction(expression)

initCanvas()

newButton=tk.Button(toolNav,text="绘制函数",command=newFunction)
newButton.place(x=round((toolNavWidth-buttonWidth)/2),y=10,width=buttonWidth,height=30)
clearButton=tk.Button(toolNav,text="清空画布",command=clearCanvas)
clearButton.place(x=round((toolNavWidth-buttonWidth)/2),y=50,width=buttonWidth,height=30)

window.mainloop()