#pragma once
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QMainWindow>
#include "ui_LogIn.h"

class Log :public QMainWindow
{
	Q_OBJECT
public:
	Log();
	~Log();

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void on_logInButton_clicked();

	static QPoint offset;
	static QString accessToken;

	Ui::LogIn ui;

signals:
	void logInSuccess();
	/*void errorCode();
	void errorToken();
	void noInGuild();*/

};
