#include <Windows.h>   // 优先包含 Windows 头文件
#include "ui_LogIn.h"
#include "LogIn.h"
#include <QObject>
#include "MainWindow.h"
#include <iostream>
#include <QMouseEvent>
#include <QWidget>
#include "verify.h"
#include <QJsonObject>
#include <QMessageBox>

QPoint Log::offset;
QString Log::accessToken;

Log::Log()
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowIcon(QIcon(":/D:/instagram (1).svg"));
	ui.label_2->setEnabled(false);
	ui.label_3->setEnabled(false);
	
	QObject::connect(ui.pushButton, &QPushButton::clicked, [=]() {
		ui.statusBar->showMessage("请前往Discord客户端授权......");
		Log::on_logInButton_clicked();
		});
	QObject::connect(this, &Log::logInSuccess, this, [=]() {
		ui.statusBar->showMessage("登录成功!");
		Verify verify;
		//获取用户信息
		QJsonObject userInfo = verify.GetUserInfo(accessToken);

		if (!userInfo.isEmpty()) {
			QString global_name = userInfo["global_name"].toString();
			QString discriminator = userInfo["discriminator"].toString();

			ui.label_2->setEnabled(true);
			ui.label_3->setEnabled(true);

			ui.label_4->setText(global_name +"，欢迎回来");
			ui.statusBar->showMessage("即将进入软件......");
			this->close();
			MainWindow* mainWindow = new MainWindow();
			mainWindow->show();
		}
		});
	/*QObject::connect(this, &Log::errorCode, this,[=]() {
		ui.statusBar->showMessage("授权失败！");
		});
	QObject::connect(this, &Log::errorToken, this, [=]() {
		ui.statusBar->showMessage("无效令牌！");
		});
	QObject::connect(this, &Log::noInGuild, this, [=]() {
		ui.statusBar->showMessage("您当前不在Echo服务器");
		});*/
	
}

Log::~Log()
{
	
}

void Log::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		if (event->globalPosition().toPoint().y() < this->pos().y() + 30)
		{
			offset = event->globalPosition().toPoint() - this->pos();
			event->accept();
		}
		else
		{
			offset = QPoint();
			event->ignore();
		}
	}
}

void Log::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		if (offset.isNull())
		{
			event->ignore();
			return;
		}
		else
		{
			this->move(event->globalPosition().toPoint() - offset);
			event->accept();
		}
	}
}

void Log::on_logInButton_clicked()
{
	Verify verify;
	verify.OpenDiscordOAuthURL();
	QString code = verify.StartLocalHttpListener();

	if (code.isEmpty())
	{
		std::cout <<"授权失败，请重试！"<<std::endl;
		//emit errorCode;
	}
	else
	{
		std::cout <<"授权成功，正在获取用户信息..."<<std::endl;
		QString accessToken = verify.ExchangeCodeForToken(code);
		Log::accessToken = accessToken;
		if (accessToken == "")
		{
			std::cout<<"令牌交换失败，请重试！"<<std::endl;
			//emit errorToken;
		}
		else
		{
			if(verify.VerifyUserInGuild(accessToken))
			{
				std::cout<<"登录成功!"<<std::endl;
				emit logInSuccess();
			}
			else
			{
				std::cout<<"您不在指定的服务器中，无法登录!"<<std::endl;
				//emit noInGuild;
			}
		}
	}
}



