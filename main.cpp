#include <Windows.h>   // 必须放在宏定义之后
#include "LogIn.h"
#include <iostream>
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    // 设置控制台输出编码为UTF-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	QApplication app(argc, argv);
	
	Log loginWindow;
	// 直接显示主窗口，跳过登录界面
	//MainWindow mainWindow;
	loginWindow.show();
	//mainWindow.show();

	return app.exec();
}
