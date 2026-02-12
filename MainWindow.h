#pragma once
#include <QObject>
#include <QMainWindow>
#include "ui_MainWindow.h"
#include "ui_more.h"
#include "MoreUi.h"
#include <Windows.h>
#include "Memory.h"
#include "BallsMerge.h"
#include <QGraphicsBlurEffect>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();	

	void setTable(const QString mode); //放置数据到table中
	void loadjson();
	void setCheckboxState(QTreeWidget* treeWidget, const QString& parentText,const QString& itemText, bool checked);
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	static LRESULT CALLBACK keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
	void installGlobalHook();
	void uninstallGlobalHook();
	static bool isUpdate;
	int virtualkey(QString key);
	QPoint offset;

	static HHOOK keyBoardHook; 
	static HHOOK mouseHook;
	static bool qupiState;

public slots:
	void treewidget_itemClicked(); //点击不同的items,索引stackedwidget

public:
	Ui::MainWindow ui;
	MoreUi* moreUi;
	static BallsMerge* ballsMerge;
	QGraphicsBlurEffect* graphicsBlurEffect;
};

