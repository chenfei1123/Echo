#include "verify.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QJsonarray>
#include <QTimer>

Verify::Verify()
{
	//discordInitialize();
}
Verify::~Verify()
{

}

QString Verify::StartLocalHttpListener()
{
    std::cout << "\n=== 启动 Discord OAuth 回调服务器 ===" << std::endl;

    QTcpServer* tcpServer = new QTcpServer();
    QString code;
    bool codeReceived = false;  // 添加标志位

    // 监听端口
    if (!tcpServer->listen(QHostAddress::LocalHost, 8080)) {
        std::cout << "❌ 服务器启动失败: " << tcpServer->errorString().toStdString() << std::endl;
        delete tcpServer;
        return "";
    }

    std::cout << "✅ 服务器启动成功" << std::endl;
    std::cout << "✅ 地址: 127.0.0.1:" << tcpServer->serverPort() << std::endl;
    std::cout << "✅ 回调URL: http://127.0.0.1:" << tcpServer->serverPort() << "/discord/callback" << std::endl;
    std::cout << "\n等待 Discord 授权回调..." << std::endl;

    // 处理连接 - 使用成员变量或智能指针确保生命周期
    QObject::connect(tcpServer, &QTcpServer::newConnection, [tcpServer, &code, &codeReceived]() {
        QTcpSocket* socket = tcpServer->nextPendingConnection();

        std::cout << "🔗 收到浏览器连接" << std::endl;

        QObject::connect(socket, &QTcpSocket::readyRead, [socket, &code, &codeReceived]() {
            QByteArray requestData = socket->readAll();
            QString requestString = QString::fromUtf8(requestData);

            // 调试：打印请求信息
            std::cout << "📨 收到请求，长度: " << requestString.length() << " 字符" << std::endl;

            // 检查是否是 Discord 回调
            if (requestString.contains("/discord/callback")) {
                std::cout << "✅ 检测到 Discord OAuth 回调" << std::endl;

                // 更好的code提取方法
                QStringList lines = requestString.split("\r\n");
                if (lines.size() > 0) {
                    QString requestLine = lines[0];  // 第一行: "GET /discord/callback?code=xxx HTTP/1.1"
                    std::cout << "请求行: " << requestLine.toStdString() << std::endl;

                    // 提取URL路径和查询参数
                    QStringList parts = requestLine.split(' ');
                    if (parts.size() >= 2) {
                        QString path = parts[1];  // "/discord/callback?code=xxx"

                        // 解析URL
                        QUrl url("http://localhost" + path);
                        QUrlQuery query(url);
                        code = query.queryItemValue("code");

                        if (!code.isEmpty()) {
                            std::cout << "🎉 提取到授权码: " << code.toStdString() << std::endl;
                            codeReceived = true;  // 设置标志
                        }
                        else {
                            std::cout << "❌ 未找到code参数" << std::endl;
                            // 尝试直接提取
                            int codePos = requestString.indexOf("code=");
                            if (codePos > 0) {
                                int endPos = requestString.indexOf("&", codePos);
                                if (endPos == -1) endPos = requestString.indexOf(" ", codePos);
                                if (endPos == -1) endPos = requestString.indexOf("\r\n", codePos);

                                if (endPos > codePos) {
                                    code = requestString.mid(codePos + 5, endPos - codePos - 5);
                                    std::cout << "🎉 直接提取到授权码: " << code.toStdString() << std::endl;
                                    codeReceived = true;
                                }
                            }
                        }
                    }
                }

                // 发送响应给浏览器
                QString httpResponse =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "\r\n"
                    "<!DOCTYPE html>"
                    "<html lang=\"zh-CN\">"
                    "<head>"
                    "<meta charset=\"UTF-8\">"
                    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                    "<title>Discord 授权完成</title>"
                    "<style>"
                    "body {"
                    "font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Microsoft YaHei', sans-serif;"
                    "background: linear-gradient(135deg, #1a1b1e 0%, #23272a 50%, #2c2f33 100%);"
                    "color: white;"
                    "min-height: 100vh;"
                    "margin: 0;"
                    "display: flex;"
                    "align-items: center;"
                    "justify-content: center;"
                    "padding: 20px;"
                    "}"
                    ".container {"
                    "text-align: center;"
                    "max-width: 500px;"
                    "width: 100%;"
                    "animation: fadeIn 0.8s ease-out;"
                    "}"
                    ".checkmark {"
                    "width: 100px;"
                    "height: 100px;"
                    "background: #57F287;"
                    "border-radius: 50%;"
                    "display: flex;"
                    "align-items: center;"
                    "justify-content: center;"
                    "font-size: 48px;"
                    "margin: 0 auto 30px;"
                    "animation: successPulse 2s infinite;"
                    "box-shadow: 0 0 30px rgba(87, 242, 135, 0.5);"
                    "}"
                    "h1 {"
                    "font-size: 32px;"
                    "font-weight: 700;"
                    "margin: 0 0 20px;"
                    "color: white;"
                    "text-shadow: 0 2px 10px rgba(0, 0, 0, 0.3);"
                    "}"
                    ".message {"
                    "font-size: 18px;"
                    "line-height: 1.6;"
                    "color: #B9BBBE;"
                    "margin-bottom: 30px;"
                    "padding: 0 20px;"
                    "}"
                    ".discord-badge {"
                    "display: inline-block;"
                    "background: rgba(88, 101, 242, 0.2);"
                    "border: 1px solid rgba(88, 101, 242, 0.5);"
                    "border-radius: 20px;"
                    "padding: 8px 20px;"
                    "color: #7289DA;"
                    "font-size: 14px;"
                    "font-weight: 600;"
                    "letter-spacing: 0.5px;"
                    "margin-top: 20px;"
                    "}"
                    ".hint {"
                    "margin-top: 40px;"
                    "color: #72767D;"
                    "font-size: 14px;"
                    "border-top: 1px solid rgba(255, 255, 255, 0.1);"
                    "padding-top: 20px;"
                    "}"
                    "@keyframes fadeIn {"
                    "from { opacity: 0; transform: translateY(30px); }"
                    "to { opacity: 1; transform: translateY(0); }"
                    "}"
                    "@keyframes successPulse {"
                    "0%, 100% { transform: scale(1); box-shadow: 0 0 30px rgba(87, 242, 135, 0.5); }"
                    "50% { transform: scale(1.05); box-shadow: 0 0 50px rgba(87, 242, 135, 0.8); }"
                    "}"
                    "@media (max-width: 480px) {"
                    ".checkmark {"
                    "width: 80px;"
                    "height: 80px;"
                    "font-size: 40px;"
                    "}"
                    "h1 { font-size: 28px; }"
                    ".message { font-size: 16px; }"
                    "}"
                    "</style>"
                    "</head>"
                    "<body>"
                    "<div class=\"container\">"
                    "<div class=\"checkmark\">✓</div>"
                    "<h1>Discord 授权成功</h1>"
                    "<div class=\"message\">"
                    "Discord 账号授权已完成<br>"
                    "你现在可以关闭此窗口"
                    "</div>"
                    "<div class=\"discord-badge\">OAUTH 2.0 AUTHORIZED</div>"
                    "<div class=\"hint\">可以安全地关闭此标签页</div>"
                    "</div>"

                    "<script>"
                    "// 简洁的通知父窗口（如果存在）"
                    "window.addEventListener('load', () => {"
                    "try {"
                    "if (window.opener) {"
                    "window.opener.postMessage('discord_oauth_success', '*');"
                    "}"
                    "} catch (e) {"
                    "// 忽略错误"
                    "}"
                    "});"
                    "</script>"
                    "</body>"
                    "</html>";

                socket->write(httpResponse.toUtf8());
                socket->flush();
            }

            socket->disconnectFromHost();
            socket->deleteLater();
            });

        // 连接断开处理
        QObject::connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        });

    // 🔥 关键：创建事件循环等待授权码
    QEventLoop loop;
    QTimer timeoutTimer;

    // 设置超时（30秒）
    timeoutTimer.setSingleShot(true);
    QObject::connect(&timeoutTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timeoutTimer.start(30000);

    // 定期检查是否收到code
    QTimer checkTimer;
    checkTimer.setInterval(100);  // 每100ms检查一次
    QObject::connect(&checkTimer, &QTimer::timeout, [&]() {
        if (codeReceived) {
            std::cout << "✅ 收到授权码，结束等待" << std::endl;
            loop.quit();
        }
        });
    checkTimer.start();

    // 开始事件循环（阻塞等待）
    std::cout << "⏳ 等待授权码（最多30秒）..." << std::endl;
    loop.exec();

    // 清理资源
    tcpServer->close();
    delete tcpServer;

    if (codeReceived) {
        std::cout << "\n✅ OAuth 流程完成" << std::endl;
        std::cout << "授权码: " << code.toStdString() << std::endl;
        return code;
    }

    std::cout << "\n❌ 等待超时，未收到授权码" << std::endl;
    return "";
}

void Verify::OpenDiscordOAuthURL()
{
	QString clientId = "1466844739511910430";
	QString redirectUri = "http://127.0.0.1:8080/discord/callback";
	QString scope = "identify%20guilds%20email";

	////网页端discord授权
	//QString discordHttpUrl = QString("https://discord.com/oauth2/authorize?"
	//	"client_id=%1&"
	//	"redirect_uri=%2&"
	//	"response_type=code&"
	//	"scope=%3")
	//	.arg(clientId)
	//	.arg(redirectUri)
	//	.arg(scope);
	//discordHttpUrl += "&prompt=consent";
	//QDesktopServices::openUrl(discordHttpUrl);
	//std::cout << "已打开Discord OAuth授权页面，请完成授权流程。" << std::endl;
	//std::cout << discordHttpUrl.toStdString() << std::endl;

	//客户端discord授权
	QString discordAppUrl = QString("discord:///oauth2/authorize?"
		"client_id=%1&"
		"redirect_uri=%2&"
		"response_type=code&"
		"scope=identify%20guilds%20email&"
		"prompt=consent")
		.arg(clientId)
		.arg(redirectUri);
	QDesktopServices::openUrl(discordAppUrl);
	std::cout << "已打开Discord客户端OAuth授权页面，请完成授权流程。" << std::endl;
	std::cout << discordAppUrl.toStdString() << std::endl;
		
		//https://discord.com/api/oauth2/authorize?client_id=1466844739511910430&redirect_uri=http://127.0.0.1:8080/discord/callback&scope=identify&response_type=code

		
}

QString Verify::ExchangeCodeForToken(const QString& code)
{
    std::cout << "\n=== 开始交换访问令牌 ===" << std::endl;

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://discord.com/api/oauth2/token"));

    // 设置请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "MyDiscordApp/1.0");

    // 构建POST数据
    QUrlQuery postData;
    postData.addQueryItem("client_id", "1466844739511910430");
    postData.addQueryItem("client_secret", "PauZiuwYc3lq0lpHC8y8ve6U4PmZCAws");
    postData.addQueryItem("grant_type", "authorization_code");
    postData.addQueryItem("code", code);
    postData.addQueryItem("redirect_uri", "http://127.0.0.1:8080/discord/callback");

    QString postString = postData.toString(QUrl::FullyEncoded);
    std::cout << "POST数据: " << postString.toStdString() << std::endl;

    // 发送请求
    QNetworkReply* reply = manager.post(request, postString.toUtf8());

    // 等待响应完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QTimer::singleShot(10000, &loop, &QEventLoop::quit); // 10秒超时

    std::cout << "等待Discord响应..." << std::endl;
    loop.exec();

    QString accessToken;

    // 🔥 关键：获取HTTP状态码和完整响应
    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    std::cout << "HTTP状态码: " << httpCode << std::endl;

    // 读取响应
    QByteArray responseData = reply->readAll();

    // 🔥 打印完整响应（重要！）
    std::cout << "\n=== Discord服务器完整响应 ===" << std::endl;
    std::cout << responseData.toStdString() << std::endl;
    std::cout << "=== 响应结束 ===\n" << std::endl;

    // 根据状态码诊断问题
    if (httpCode == 400) {
        std::cout << "❌ 错误400: Bad Request" << std::endl;

        // 检查常见的400错误
        QString responseStr = QString::fromUtf8(responseData);
        if (responseStr.contains("invalid_grant")) {
            std::cout << "原因: 授权码无效或已过期" << std::endl;
            std::cout << "可能: 授权码已被使用或超过有效期（授权码只能使用一次）" << std::endl;
        }
        else if (responseStr.contains("invalid_client")) {
            std::cout << "原因: 客户端ID或密钥无效" << std::endl;
            std::cout << "解决方案: 需要在Discord开发者门户重置client_secret" << std::endl;
        }
        else if (responseStr.contains("invalid_request")) {
            std::cout << "原因: 请求参数缺失或格式错误" << std::endl;
        }
    }
    else if (httpCode == 401) {
        std::cout << "❌ 错误401: Unauthorized" << std::endl;
        std::cout << "原因: 客户端密钥错误" << std::endl;
    }
    else if (httpCode == 429) {
        std::cout << "❌ 错误429: Too Many Requests" << std::endl;
        std::cout << "原因: 请求太频繁，被Discord限流" << std::endl;
    }
    else if (httpCode == 200) {
        // 尝试解析JSON
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);

        if (parseError.error == QJsonParseError::NoError) {
            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();
                if (jsonObj.contains("access_token")) {
                    accessToken = jsonObj["access_token"].toString();
                    std::cout << "✅ 成功获取访问令牌!" << std::endl;
                    std::cout << "令牌: " << accessToken.left(20).toStdString() << "..." << std::endl;

                    // 打印其他信息
                    if (jsonObj.contains("token_type")) {
                        std::cout << "令牌类型: " << jsonObj["token_type"].toString().toStdString() << std::endl;
                    }
                    if (jsonObj.contains("expires_in")) {
                        int expires = jsonObj["expires_in"].toInt();
                        std::cout << "有效期: " << expires << "秒 (" << (expires / 3600) << "小时)" << std::endl;
                    }
                }
                else if (jsonObj.contains("error")) {
                    std::cout << "❌ Discord返回错误: " << jsonObj["error"].toString().toStdString() << std::endl;
                }
            }
        }
        else {
            std::cout << "❌ JSON解析错误: " << parseError.errorString().toStdString() << std::endl;
            std::cout << "错误位置: " << parseError.offset << std::endl;

            // 显示错误位置附近的文本
            int start = qMax(0, parseError.offset - 50);
            int length = qMin(100, responseData.length() - start);
            std::cout << "错误上下文: " << responseData.mid(start, length).toStdString() << std::endl;
        }
    }
    else {
        std::cout << "❌ 未知HTTP状态码: " << httpCode << std::endl;
    }

    if (reply->error() != QNetworkReply::NoError) {
        std::cout << "网络错误: " << reply->errorString().toStdString() << std::endl;
    }

    reply->deleteLater();
    std::cout << "=== 交换结束 ===\n" << std::endl;

    return accessToken;
}

bool Verify::VerifyUserInGuild(const QString& accessToken)
{
    std::cout << "\n=== 检查用户服务器成员身份 ===" << std::endl;
    std::cout << "使用令牌: " << accessToken.left(20).toStdString() << "..." << std::endl;

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QUrl userUrl("https://discord.com/api/users/@me/guilds");

    request.setUrl(userUrl);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(accessToken).toUtf8());
    request.setRawHeader("User-Agent", "MyDiscordApp/1.0");

    std::cout << "请求URL: " << userUrl.toString().toStdString() << std::endl;

    QNetworkReply* reply = manager->get(request);

    // 等待请求完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QTimer::singleShot(10000, &loop, &QEventLoop::quit);

    std::cout << "等待Discord响应..." << std::endl;
    loop.exec();

    bool isInGuild = false;

    // 获取HTTP状态码
    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    std::cout << "HTTP状态码: " << httpCode << std::endl;

    if (reply->error() == QNetworkReply::NoError && httpCode == 200)
    {
        QByteArray jsonData = reply->readAll();

        // 🔥 输出JSON表格
        std::cout << "\n=== Discord服务器列表JSON响应 ===" << std::endl;
        std::cout << jsonData.toStdString() << std::endl;
        std::cout << "=== JSON响应结束 ===\n" << std::endl;

        // 格式化输出
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error == QJsonParseError::NoError)
        {
            if (jsonDoc.isArray())
            {
                QJsonArray guildsArray = jsonDoc.array();

                std::cout << "用户所在的服务器数量: " << guildsArray.size() << std::endl;
                std::cout << "\n服务器列表:" << std::endl;
                std::cout << "========================================" << std::endl;

                for (int i = 0; i < guildsArray.size(); ++i)
                {
                    QJsonObject guildObj = guildsArray[i].toObject();

                    QString guildId = guildObj["id"].toString();
                    QString guildName = guildObj["name"].toString();
                    QString permissions = guildObj["permissions"].toString();

                    // 检查权限
                    bool isAdmin = (permissions.toULongLong() & 0x8) != 0; // ADMINISTRATOR权限
                    bool isOwner = guildObj["owner"].toBool();

                    std::cout << "[" << i + 1 << "] " << guildName.toStdString()
                        << " (ID: " << guildId.toStdString() << ")" << std::endl;
                    std::cout << "    权限: " << permissions.toStdString();
                    if (isOwner) std::cout << " [所有者]";
                    if (isAdmin) std::cout << " [管理员]";
                    std::cout << std::endl;

                    // 检查是否在指定服务器中
                    if (guildId == "1262353655261040761") // 你的服务器ID
                    {
                        isInGuild = true;
                        std::cout << "    ✅ 这是目标服务器!" << std::endl;
                    }

                    std::cout << "----------------------------------------" << std::endl;
                }

                if (isInGuild)
                {
                    std::cout << "\n✅ 用户在指定的Discord服务器中！" << std::endl;
                }
                else
                {
                    std::cout << "\n❌ 用户不在指定的Discord服务器中。" << std::endl;
                    std::cout << "目标服务器ID: 1262353655261040761" << std::endl;
                }
            }
            else if (jsonDoc.isObject())
            {
                // 可能是错误响应
                QJsonObject errorObj = jsonDoc.object();
                if (errorObj.contains("message"))
                {
                    std::cout << "❌ Discord返回错误: "
                        << errorObj["message"].toString().toStdString() << std::endl;
                }
                std::cout << "完整错误响应: " << jsonDoc.toJson().toStdString() << std::endl;
            }
        }
        else
        {
            std::cout << "❌ JSON解析错误: " << parseError.errorString().toStdString() << std::endl;
            std::cout << "原始响应: " << jsonData.toStdString() << std::endl;
        }
    }
    else
    {
        std::cout << "❌ 网络请求失败: " << reply->errorString().toStdString() << std::endl;
        std::cout << "HTTP状态码: " << httpCode << std::endl;

        // 尝试读取错误响应
        QByteArray errorData = reply->readAll();
        if (!errorData.isEmpty()) {
            std::cout << "错误响应: " << errorData.toStdString() << std::endl;
        }
    }

    manager->deleteLater();
    reply->deleteLater();

    std::cout << "=== 检查结束 ===\n" << std::endl;
    return isInGuild;
}

QJsonObject Verify::GetUserInfo(const QString& accessToken)
{
    std::cout << "\n=== 获取Discord用户信息 ===" << std::endl;
    std::cout << "使用令牌: " << accessToken.left(20).toStdString() << "..." << std::endl;

    QNetworkAccessManager manager;
    QNetworkRequest request;
    QUrl userUrl("https://discord.com/api/users/@me");

    request.setUrl(userUrl);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(accessToken).toUtf8());
    request.setRawHeader("User-Agent", "MyDiscordApp/1.0");

    std::cout << "请求URL: " << userUrl.toString().toStdString() << std::endl;

    QNetworkReply* reply = manager.get(request);

    // 等待请求完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QTimer::singleShot(10000, &loop, &QEventLoop::quit);

    std::cout << "等待用户信息响应..." << std::endl;
    loop.exec();

    QJsonObject userInfo;

    // 获取HTTP状态码
    int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    std::cout << "HTTP状态码: " << httpCode << std::endl;

    if (reply->error() == QNetworkReply::NoError && httpCode == 200)
    {
        QByteArray jsonData = reply->readAll();

        // 🔥 输出JSON表格
        std::cout << "\n=== Discord用户信息JSON响应 ===" << std::endl;
        std::cout << jsonData.toStdString() << std::endl;
        std::cout << "=== JSON响应结束 ===\n" << std::endl;

        // 解析和格式化显示
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error == QJsonParseError::NoError && jsonDoc.isObject())
        {
            userInfo = jsonDoc.object();

            std::cout << "\n📋 用户信息摘要:" << std::endl;
            std::cout << "========================================" << std::endl;

            // 基本信息
            QString userId = userInfo["id"].toString();
            QString username = userInfo["username"].toString();
            QString discriminator = userInfo["discriminator"].toString();
            QString avatarHash = userInfo["avatar"].toString();
            QString email = userInfo["email"].toString();
            bool verified = userInfo["verified"].toBool();
            bool mfaEnabled = userInfo["mfa_enabled"].toBool();

            std::cout << "👤 用户名: " << username.toStdString()
                << "#" << discriminator.toStdString() << std::endl;
            std::cout << "🆔 用户ID: " << userId.toStdString() << std::endl;

            if (!avatarHash.isEmpty()) {
                std::cout << "🖼️  头像Hash: " << avatarHash.toStdString() << std::endl;
                // 生成头像URL
                QString avatarUrl = QString("https://cdn.discordapp.com/avatars/%1/%2.png")
                    .arg(userId).arg(avatarHash);
                std::cout << "   头像URL: " << avatarUrl.toStdString() << std::endl;
            }
            else {
                std::cout << "🖼️  头像: 使用默认头像" << std::endl;
            }

            if (!email.isEmpty()) {
                std::cout << "📧 邮箱: " << email.toStdString() << std::endl;
            }
            else {
                std::cout << "📧 邮箱: 未授权或未设置" << std::endl;
            }

            std::cout << "✅ 已验证: " << (verified ? "是" : "否") << std::endl;
            std::cout << "🔒 MFA启用: " << (mfaEnabled ? "是" : "否") << std::endl;

            // 可选信息
            if (userInfo.contains("locale")) {
                std::cout << "🌐 语言区域: " << userInfo["locale"].toString().toStdString() << std::endl;
            }
            if (userInfo.contains("accent_color")) {
                int accentColor = userInfo["accent_color"].toInt();
                std::cout << "🎨 强调色: #" << QString::number(accentColor, 16).toUpper().toStdString() << std::endl;
            }
            if (userInfo.contains("banner")) {
                QString bannerHash = userInfo["banner"].toString();
                if (!bannerHash.isEmpty()) {
                    std::cout << "🏳️  横幅Hash: " << bannerHash.toStdString() << std::endl;
                }
            }

            std::cout << "========================================\n" << std::endl;

            // 返回JSON对象
            return userInfo;
        }
        else
        {
            std::cout << "❌ JSON解析错误: " << parseError.errorString().toStdString() << std::endl;
            std::cout << "原始响应: " << jsonData.toStdString() << std::endl;
        }
    }
    else
    {
        std::cout << "❌ 获取用户信息失败: " << reply->errorString().toStdString() << std::endl;
        std::cout << "HTTP状态码: " << httpCode << std::endl;

        // 尝试读取错误响应
        QByteArray errorData = reply->readAll();
        if (!errorData.isEmpty()) {
            std::cout << "错误响应: " << errorData.toStdString() << std::endl;
        }
    }

    reply->deleteLater();
    std::cout << "=== 用户信息获取结束 ===\n" << std::endl;

    return userInfo; // 如果失败，返回空对象
}
