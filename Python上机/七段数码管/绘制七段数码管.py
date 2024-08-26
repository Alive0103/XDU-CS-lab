
import time
import turtle

from matplotlib.pyplot import clf


def drawgap():
    turtle.penup()
    turtle.forward(5)


def drawline(draw):  # 绘制单段数码管
    drawgap()
    turtle.pendown() if draw else turtle.penup()
    turtle.forward(40)
    drawgap()
    turtle.right(90)


def drawdigit(digit):  # 根据数字绘制七段数码管
    drawline(True) if digit in [2, 3, 4, 5, 6, 8, 9] else drawline(False)
    drawline(True) if digit in [0, 1, 3, 4, 5, 6, 7, 8, 9] else drawline(False)
    drawline(True) if digit in [0, 2, 3, 5, 6, 8, 9] else drawline(False)
    drawline(True) if digit in [0, 2, 6, 8] else drawline(False)
    turtle.left(90)
    drawline(True) if digit in [0, 4, 5, 6, 8, 9] else drawline(False)
    drawline(True) if digit in [0, 2, 3, 5, 6, 7, 8, 9] else drawline(False)
    drawline(True) if digit in [0, 1, 2, 3, 4, 7, 8, 9] else drawline(False)
    turtle.left(180)
    turtle.penup()  # 为绘制后续数字确定位置
    turtle.forward(20)  # 未确定后续数字确定位置


def drawdate(date):  # 获得要输出的数字
    turtle.pencolor("red")
    for i in date:
        if i == "-":
            turtle.write("年", font=("Arial", 30, "normal"))
            turtle.pencolor("green")
            turtle.forward(50)
        elif i == "=":
            turtle.write("月", font=("Arial", 30, "normal"))
            turtle.pencolor("blue")
            turtle.forward(50)
        elif i == "+":
            turtle.write("日", font=("Arial", 30, "normal"))
            turtle.pencolor("black")
            turtle.forward(50)
        elif i == "*":
            turtle.write("时", font=("Arial", 30, "normal"))
            turtle.forward(50)
        elif i == "(":
            turtle.write("分", font=("Arial", 30, "normal"))
            turtle.forward(50)
        elif i == "&":
            turtle.write("秒", font=("Arial", 30, "normal"))
            turtle.forward(50)
        else:
            drawdigit(eval(i))  # 通过eval将字符串编程整数


def main():
    turtle.setup(900, 300, 200, 200)
    while 1:
        turtle.penup()
        turtle.goto(-200, 0)
        turtle.speed("fast")
        turtle.forward(-300)
        turtle.pensize(8)
        drawdate(time.strftime("%Y-%m=%d+%H*%M(%S&", time.localtime()))
        time.sleep(1)
        turtle.clearscreen()

    # turtle.done()


main()
