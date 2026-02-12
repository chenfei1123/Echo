#pragma once
#include <QObject>
#include <QString>
#define REDIRECT_URL = "http://127.0.0.1:8080/discord/callback";
#define APPLICATION_ID = 1466844739511910430;
#define GUILD_ID = 1262353655261040761;
#define APPLICATION_SECRET = "PauZiuwYc3lq0lpHC8y8ve6U4PmZCAws";

class Verify
{
public:
	Verify();
	~Verify();

	QString StartLocalHttpListener();//启动端口监听
	void OpenDiscordOAuthURL();//跳转到discord授权页面，网页/客户端授权后，discord会回调到本地8080端口，向8080端口发送包含code的请求
	QString ExchangeCodeForToken(const QString& code);//当8080端口收到discord的回调请求后，提取code，code与链接拼接后发送POST请求，discord会向8080端口发送json流，然后交换access_token（access_token在一段json文件里面）
	bool VerifyUserInGuild(const QString& accessToken);//使用access_token发送GET请求获取用户信息，验证用户身份
	QJsonObject GetUserInfo(const QString& accessToken);

};

