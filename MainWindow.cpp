#include <Windows.h>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsBlurEffect>
#include <QFile>
#include <QJsonObject>
#include <QCoreApplication>
#include "Memory.h"
#include "BallsMerge.h"
#include "ui_more.h"
#include "moreUi.h"
#include <iostream>
#include <QWidget>
#include <QtConcurrent>
#include <QFuture>

BallsMerge* MainWindow::ballsMerge = nullptr;

HHOOK MainWindow::keyBoardHook;
HHOOK MainWindow::mouseHook;

bool MainWindow::isUpdate = false;

int BallsMerge::sanjiaojian1 = 0;
int BallsMerge::sanjiaojian2 = 0;
int BallsMerge::sanjiaojian3 = 0;
int BallsMerge::chongqiujian = 0;
int BallsMerge::sifenjian = 0;
int BallsMerge::zhongfenjian = 0;
int BallsMerge::xuanzhuanjian1 = 0;
int BallsMerge::banxuanjian1 = 0;
int BallsMerge::xuanzhuanjian2 = 0;
int BallsMerge::banxuanjian2 = 0;
int BallsMerge::sheshoujian = 0;
int BallsMerge::houyangjian = 0;
int BallsMerge::tuqiujian = 0;
int BallsMerge::fenshenjian = 0;
int BallsMerge::qupijian = 0;

bool BallsMerge::sanjiao1Flag = false;
bool BallsMerge::sanjiao2Flag = false;
bool BallsMerge::sanjiao3Flag = false;
bool BallsMerge::chongqiuFlag = false;
bool BallsMerge::sifenFlag = false;
bool BallsMerge::zhongfenFlag = false;
bool BallsMerge::xuanzhuan1Flag = false;
bool BallsMerge::banxuan1Flag = false;
bool BallsMerge::xuanzhuan2Flag = false;
bool BallsMerge::banxuan2Flag = false;
bool BallsMerge::sheshouFlag = false;
bool BallsMerge::houyangFlag = false;

bool BallsMerge::autosanjiao_1_Flag = true;
bool BallsMerge::autosanjiao_2_Flag = true;
bool BallsMerge::autosanjiao_3_Flag = true;
bool BallsMerge::autosifenFlag = true;
bool BallsMerge::autozhongfenFlag = true;
bool BallsMerge::autohouyangFlag = true;

float BallsMerge::sj1jd = 0.0f;
float BallsMerge::sj2jd = 0.0f;
float BallsMerge::sj3jd = 0.0f;
float BallsMerge::sj1hqfd = 0.0f;
float BallsMerge::sj1zyfd = 0.0f;
float BallsMerge::sj2hqfd = 0.0f;
float BallsMerge::sj2zyfd = 0.0f;
float BallsMerge::sj3hqfd = 0.0f;
float BallsMerge::sj3zyfd = 0.0f;
float BallsMerge::sfjcfd = 0.0f;
float BallsMerge::zfjcfd = 0.0f;
float BallsMerge::hyjcfd1 = 0.0f;
float BallsMerge::hyjcfd2 = 0.0f;

bool BallsMerge::sj1tqFlag = false;
bool BallsMerge::sj2tqFlag = false;
bool BallsMerge::sj3tqFlag = false;
bool BallsMerge::chongqiutqFlag = false;
bool BallsMerge::chongqiujiantouFlag = false;
bool BallsMerge::sifentqFlag = false;
bool BallsMerge::zhongfentqFlag = false;
bool BallsMerge::houyangtqFlag = false;
bool BallsMerge::xuanzhuan1tqFlag = false;
bool BallsMerge::xuanzhuan2tqFlag = false;
bool BallsMerge::banxuan1tqFlag = false;
bool BallsMerge::banxuan2tqFlag = false;
bool BallsMerge::sheshoutqFlag = false;

float BallsMerge::jtygX = 0.0f;
float BallsMerge::jtygY = 0.0f;
float BallsMerge::dx = 0.0f;
float BallsMerge::dy = 0.0f;
float BallsMerge::shiye = 1.0f;

float BallsMerge::xuanzhuan1jd1 = 0.0f;
float BallsMerge::xuanzhuan1jd2 = 0.0f;
float BallsMerge::xuanzhuan1jd3 = 0.0f;
float BallsMerge::xuanzhuan1jd4 = 0.0f;
float BallsMerge::xuanzhuan1fd1 = 0.0f;
float BallsMerge::xuanzhuan1fd2 = 0.0f;
float BallsMerge::xuanzhuan1fd3 = 0.0f;
float BallsMerge::xuanzhuan1fd4 = 0.0f;

float BallsMerge::banxuan1jd1 = 0.0f;
float BallsMerge::banxuan1jd2 = 0.0f;
float BallsMerge::banxuan1jd3 = 0.0f;
float BallsMerge::banxuan1jd4 = 0.0f;
float BallsMerge::banxuan1fd1 = 0.0f;
float BallsMerge::banxuan1fd2 = 0.0f;
float BallsMerge::banxuan1fd3 = 0.0f;
float BallsMerge::banxuan1fd4 = 0.0f;

float BallsMerge::sheshoujd1 = 0.0f;
float BallsMerge::sheshoujd2 = 0.0f;
float BallsMerge::sheshoujd3 = 0.0f;
float BallsMerge::sheshoujd4 = 0.0f;
float BallsMerge::sheshoufd1 = 0.0f;
float BallsMerge::sheshoufd2 = 0.0f;
float BallsMerge::sheshoufd3 = 0.0f;
float BallsMerge::sheshoufd4 = 0.0f;

int BallsMerge::sj1yc1 = 0;
int BallsMerge::sj1yc2 = 0;
int BallsMerge::sj1yc3 = 0;
int BallsMerge::sj1yc4 = 0;
int BallsMerge::sj1yc5 = 0;
int BallsMerge::sj1yc6 = 0;
int BallsMerge::sj1cs = 0;
int BallsMerge::sj1fsjg = 0;

int BallsMerge::sj2yc1 = 0;
int BallsMerge::sj2yc2 = 0;
int BallsMerge::sj2yc3 = 0;
int BallsMerge::sj2yc4 = 0;
int BallsMerge::sj2yc5 = 0;
int BallsMerge::sj2yc6 = 0;
int BallsMerge::sj2cs = 0;
int BallsMerge::sj2fsjg = 0;

int BallsMerge::sj3yc1 = 0;
int BallsMerge::sj3yc2 = 0;
int BallsMerge::sj3yc3 = 0;
int BallsMerge::sj3yc4 = 0;
int BallsMerge::sj3yc5 = 0;
int BallsMerge::sj3yc6 = 0;
int BallsMerge::sj3cs = 0;
int BallsMerge::sj3fsjg = 0;

int BallsMerge::cqyc1 = 0;
int BallsMerge::cqyc2 = 0;
int BallsMerge::cqcs = 0;
int BallsMerge::cqfsjg = 0;

int BallsMerge::sfyc1 = 0;
int BallsMerge::sfyc2 = 0;
int BallsMerge::sfyc3 = 0;
int BallsMerge::sfyc4 = 0;
int BallsMerge::sfyc5 = 0;
int BallsMerge::sfcs = 0;
int BallsMerge::sffsjg = 0;

int BallsMerge::zfyc1 = 0;
int BallsMerge::zfyc2 = 0;
int BallsMerge::zfyc3 = 0;
int BallsMerge::zfyc4 = 0;
int BallsMerge::zfyc5 = 0;
int BallsMerge::zfcs = 0;
int BallsMerge::zffsjg = 0;

int BallsMerge::hyyc1 = 0;
int BallsMerge::hyyc2 = 0;
int BallsMerge::hyyc3 = 0;
int BallsMerge::hyyc4 = 0;
int BallsMerge::hyyc5 = 0;
int BallsMerge::hycs = 0;
int BallsMerge::hyfsjg = 0;

int BallsMerge::xz1yc1 = 0;
int BallsMerge::xz1yc2 = 0;
int BallsMerge::xz1yc3 = 0;
int BallsMerge::xz1yc4 = 0;
int BallsMerge::xz1yc5 = 0;
int BallsMerge::xz1yc6 = 0;
int BallsMerge::xz1yc7 = 0;
int BallsMerge::xz1yc8 = 0;
int BallsMerge::xz1yc9 = 0;
int BallsMerge::xz1cs = 0;
int BallsMerge::xz1fsjg = 0;

int BallsMerge::bx1yc1 = 0;
int BallsMerge::bx1yc2 = 0;
int BallsMerge::bx1yc3 = 0;
int BallsMerge::bx1yc4 = 0;
int BallsMerge::bx1yc5 = 0;
int BallsMerge::bx1yc6 = 0;
int BallsMerge::bx1yc7 = 0;
int BallsMerge::bx1yc8 = 0;
int BallsMerge::bx1yc9 = 0;
int BallsMerge::bx1cs = 0;
int BallsMerge::bx1fsjg = 0;

int BallsMerge::ssyc1 = 0;
int BallsMerge::ssyc2 = 0;
int BallsMerge::ssyc3 = 0;
int BallsMerge::ssyc4 = 0;
int BallsMerge::ssyc5 = 0;
int BallsMerge::ssyc6 = 0;
int BallsMerge::ssyc7 = 0;
int BallsMerge::ssyc8 = 0;
int BallsMerge::ssyc9 = 0;
int BallsMerge::sscs = 0;
int BallsMerge::ssfsjg = 0;

bool BallsMerge::zhongfenMacroFlag = false;
bool BallsMerge::sifenMacroFlag = false;
bool BallsMerge::xuanzhuanMacroFlag = false;
bool BallsMerge::bafenMacroFlag = false;
int BallsMerge::zhongfenMacroKey = 0;
int BallsMerge::sifenMacroKey = 0;
int BallsMerge::xuanzhuanMacroKey = 0;
int BallsMerge::bafenMacroKey = 0;
int BallsMerge::sifenMacroInterval = 0;
int BallsMerge::xuanzhuanMacroTimes = 0;
int BallsMerge::bafenMacroInterval = 0;

bool MainWindow::qupiState = false;

POINT BallsMerge::centerPos = { 0, 0 };
POINT BallsMerge::mousePos = { 0, 0 };
POINT BallsMerge::direction = { 0, 0 };
POINT BallsMerge::cursorPos_1 = { 0, 0 };
POINT BallsMerge::cursorPos_2 = { 0, 0 };


DWORD_PTR Memory::patternAddresses[16] = { 0 };
long long Memory::nianheAdress = 0;
long long Memory::ncdxAdress = 0;
long long Memory::biansuAdress = 0;
long long Memory::ygycAdress_1 = 0;
long long Memory::ygycAdress_2 = 0;
long long Memory::yaoganhuitanAdress_1 = 0;
long long Memory::yaoganhuitanAdress_2 = 0;
long long Memory::yaoganrongchaAdress = 0;
long long Memory::ygrongchaAdress = 0;
long long Memory::yaogan10000Adress_1 = 0;
long long Memory::yaogan10000Adress_2 = 0;
long long Memory::yaoganjiexianAdress = 0;
long long Memory::fsjiexianAdress = 0;
long long Memory::juneiqupiAdress = 0;
long long Memory::ncygAdress = 0;
long long Memory::shiyeAdress = 0;
long long Memory::tuqiuAdress = 0;
long long Memory::ncygjsxAdress = 0;
long long Memory::ncygjsyAdress = 0;
long long Memory::tijiAdress = 0;
long long Memory::zhanjuzhiAdress = 0;
long long Memory::selfsize = 0;
long long Memory::xmin = 0;
long long Memory::xmax = 0;
long long Memory::ymin = 0;
long long Memory::ymax = 0;

float Memory::huitanValue = 0.0f;
float Memory::yaogan10000Value = 100.0f;
float Memory::step = 1.0f;
float Memory::yaoganycValue = 0.0f;

bool Memory::yaoganyouhuaFlag = false;
bool Memory::yaoganhuitanFlag = false;
bool Memory::yaoganjiexianFlag = false;
bool Memory::fsjiexianFlag = false;
bool Memory::yaogan10000Flag = false;
bool Memory::tuqiuFlag = true;
bool Memory::gunlunshiyeFlag = false;
bool Memory::juneiqupiFlag = false;
bool Memory::yaoganycFlag = false;
bool Memory::gunlunshiyeMax;
bool Memory::gunlunshiyeMin;

HANDLE Memory::hProcess = nullptr;
HWND Memory::hWnd = nullptr;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/D:/Instagram, logo.svg"));
	ui.treeWidget->expandAll();
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	ballsMerge = new BallsMerge();
	
	loadjson();
	connect(ui.treeWidget, &QTreeWidget::itemClicked, this, &MainWindow::treewidget_itemClicked);
	/*connect(ui.pushButton, &QPushButton::clicked, [=] {
		ui.pushButton->setEnabled(false);
		ui.pushButton->setText("内存初始化中...");
		printf("内存初始化中");

		if (Memory::patternAddresses[0] != 0)
		{
			memory->shiyeAdress = Memory::patternAddresses[0] + 0x414;
			memory->tuqiuAdress = Memory::patternAddresses[0] + 0xA0;
			memory->ncygAdress = Memory::patternAddresses[0] + 0x40;
			memory->tijiAdress = Memory::patternAddresses[0] + 0x3A0;
			memory->zhanjuzhiAdress = Memory::patternAddresses[0] + 0x4A0;
			memory->ncygjsxAdress = Memory::patternAddresses[0] + 0x68;
			memory->ncygjsyAdress = Memory::patternAddresses[0] + 0x6C;
			memory->xmin = Memory::patternAddresses[0] + 0x408;
			memory->xmax = Memory::patternAddresses[0] + 0x40C;
			memory->ymin = Memory::patternAddresses[0] + 0x404;
			memory->ymax = Memory::patternAddresses[0] + 0x400;
			memory->selfsize = Memory::patternAddresses[0] + 0x410;
		}

		if (Memory::patternAddresses[1] != 0)
		{
			memory->biansuAdress = memory->patternAddresses[1] + 0x0;
		}
		if (Memory::patternAddresses[2] != 0)
		{
			memory->nianheAdress = memory->patternAddresses[2] + 0x10;
		}
		if (Memory::patternAddresses[3] != 0)
		{
			memory->fsjiexianAdress = memory->patternAddresses[3] + 0x9;
		}
		if (Memory::patternAddresses[4] != 0)
		{
			memory->yaoganjiexianAdress = memory->patternAddresses[4] - 0x24;
		}
		if (Memory::patternAddresses[5] != 0)
		{
			DWORD_PTR baseAddr = memory->patternAddresses[5];
			memory->yaoganhuitanAdress_1 = baseAddr + 0x20;
			memory->yaoganhuitanAdress_2 = baseAddr + 0x20 - 0x04;
			memory->yaoganrongchaAdress = baseAddr + 0x1C;
		}
		if (Memory::patternAddresses[6] != 0)
		{
			memory->yaogan10000Adress_2 = memory->patternAddresses[6] - 0x51 + 0x04;
		}
		if (Memory::patternAddresses[7] != 0)
		{
			memory->juneiqupiAdress = memory->patternAddresses[7] - 0x02;
		}
		if (Memory::patternAddresses[8] != 0)
		{
			DWORD_PTR baseAddr = memory->patternAddresses[8];
			memory->ygycAdress_1 = baseAddr + 0x30;
			memory->ygycAdress_2 = baseAddr;
		}
		if (Memory::patternAddresses[9] != 0)
		{
			memory->ncdxAdress = memory->patternAddresses[9] - 0x08;
		}
		
		});*/

	connect(ui.doubleSpinBox, &QDoubleSpinBox::valueChanged, [=]() {
		ballsMerge->writenianhe(Memory::hProcess, ui.doubleSpinBox->value());
		});
	connect(ui.doubleSpinBox_2, &QDoubleSpinBox::valueChanged, [=]() {
		ballsMerge->writeshiye(Memory::hProcess, ui.doubleSpinBox_2->value());
		});
	connect(ui.doubleSpinBox_8, &QDoubleSpinBox::valueChanged, [=]() {
		ballsMerge->writencdx(Memory::hProcess, ui.doubleSpinBox_8->value());
		});
	connect(ui.doubleSpinBox_7, &QDoubleSpinBox::valueChanged, [=]() {
		ballsMerge->writebiansu(Memory::hProcess, ui.doubleSpinBox_7->value());
		});
	connect(ui.doubleSpinBox_6, &QDoubleSpinBox::valueChanged, [=] {
		ballsMerge->huitanValue = ui.doubleSpinBox_6->value();
		});
	connect(ui.checkBox_4, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->yaogan10000Value = 99999999999999.0f;
		}
		else
		{
			ballsMerge->yaogan10000Value = 100;
		}
		});		
	connect(ui.checkBox_6, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->yaoganyouhuaFlag = true;
		}
		else
		{
			ballsMerge->yaoganyouhuaFlag = false;
		}
		});
	connect(ui.checkBox_5, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->yaoganhuitanFlag = true;
		}
		else
		{
			ballsMerge->yaoganhuitanFlag = false;
		}
		});
	connect(ui.checkBox_7, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
			{
			ballsMerge->yaoganjiexianFlag = true;
		}
		else
		{
			ballsMerge->yaoganjiexianFlag = false;
		}
		});
	connect(ui.checkBox_8, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->fsjiexianFlag = true;
		}
		else
		{
			ballsMerge->fsjiexianFlag = false;
		}
		});
	connect(ui.checkBox_4, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->yaogan10000Flag = true;
		}
		else
		{
			ballsMerge->yaogan10000Flag = false;
		}
		});
	connect(ui.checkBox, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->tuqiuFlag = true;
		}
		else
		{
			ballsMerge->tuqiuFlag = false;
		}
		});
	connect(ui.checkBox_3, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->gunlunshiyeFlag = true;
		}
		else
		{
			ballsMerge->gunlunshiyeFlag = false;
		}
		});
	connect(ui.doubleSpinBox_5, &QDoubleSpinBox::valueChanged, [=] {
		ballsMerge->step = ui.doubleSpinBox_5->value();
		});
	connect(ui.lineEdit_2, &QLineEdit::textChanged, [=] {
		ballsMerge->yaoganycValue = ui.lineEdit_2->text().toFloat();
		});
	connect(ui.comboBox, &QComboBox::currentTextChanged, [=]() {
		if (ui.comboBox->currentText() == "技战室")
		{
			QMessageBox::information(this, "提示", "当前以及切换到技战室参数");
			setTable(QString("jzs"));
		}
		else if (ui.comboBox->currentText() == "逃杀")
		{
			QMessageBox::information(this, "提示", "当前已经切换到逃杀模式\n若有合球失误，请联系群主，等待下个版本修复");
			setTable(QString("sgts"));
		}
		else if (ui.comboBox->currentText() == "自建房")
		{
			QMessageBox::information(this, "提示", "当前已经切换到自建房模式");
			setTable(QString("zjf"));
		}
		else if (ui.comboBox->currentText() == "巨行星")
		{
			QMessageBox::information(this, "提示", "当前已经切换到巨行星模式，暂时使用逃杀参数");
			setTable(QString("jxx"));
		}
		else if (ui.comboBox->currentText() == "通用")
		{
			QMessageBox::information(this, "提示", "当前已经切换到通用延迟");
			setTable(QString("tongyong"));
		}
		});
	connect(ui.comboBox_5, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sanjiaojian1 = virtualkey(ui.comboBox_5->currentText());
		});
	connect(ui.comboBox_6, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sj1jd = ui.comboBox_6->currentText().toInt();
		});
	connect(ui.doubleSpinBox_14, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sj1hqfd = ui.doubleSpinBox_14->value();
		});
	connect(ui.doubleSpinBox_15, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sj1zyfd = ui.doubleSpinBox_15->value();
		});
	connect(ui.checkBox_15, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::sj1tqFlag = true;
		}
		else
		{
			BallsMerge::sj1tqFlag = false;
		}
		});
	connect(ui.checkBox_16, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::autosanjiao_1_Flag = true;
		}
		else
		{
			BallsMerge::autosanjiao_1_Flag = false;
		}
		});
	connect(ui.comboBox_7, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sanjiaojian2 = virtualkey(ui.comboBox_7->currentText());
		});
	connect(ui.comboBox_8, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sj2jd = ui.comboBox_8->currentText().toInt();
		});
	connect(ui.doubleSpinBox_18, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sj2hqfd = ui.doubleSpinBox_18->value();
		});
	connect(ui.doubleSpinBox_16, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sj2zyfd = ui.doubleSpinBox_16->value();
		});
	connect(ui.checkBox_21, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::sj2tqFlag = true;
		}
		else
		{
			BallsMerge::sj2tqFlag = false;
		}
		});
	connect(ui.checkBox_24, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::autosanjiao_2_Flag = true;
		}
		else
		{
			BallsMerge::autosanjiao_2_Flag = false;
		}
		});
	connect(ui.comboBox_9, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sanjiaojian3 = virtualkey(ui.comboBox_9->currentText());
		});
	connect(ui.comboBox_10, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sj1jd = ui.comboBox_10->currentText().toInt();
		});
	connect(ui.doubleSpinBox_20, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sj1hqfd = ui.doubleSpinBox_20->value();
		});
	connect(ui.doubleSpinBox_21, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sj1zyfd = ui.doubleSpinBox_21->value();
		});
	connect(ui.checkBox_26, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::sj3tqFlag = true;
		}
		else
		{
			BallsMerge::sj3tqFlag = false;
		}
		});
	connect(ui.checkBox_25, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::autosanjiao_3_Flag = true;
		}
		else
		{
			BallsMerge::autosanjiao_3_Flag = false;
		}
		});
	connect(ui.comboBox_11, &QComboBox::currentTextChanged, [=] {
		BallsMerge::chongqiujian = virtualkey(ui.comboBox_11->currentText());
		});
	connect(ui.checkBox_30, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::chongqiutqFlag = true;
		}
		else
		{
			BallsMerge::chongqiutqFlag = false;
		}
		});
	connect(ui.checkBox_32, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::chongqiujiantouFlag = true;
		}
		else
		{
			BallsMerge::chongqiujiantouFlag = false;
		}
		});
	connect(ui.comboBox_12, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sifenjian = virtualkey(ui.comboBox_12->currentText());
		});
	connect(ui.checkBox_35, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::sifentqFlag = true;
		}
		else
		{
			BallsMerge::sifentqFlag = false;
		}
		});
	connect(ui.checkBox_33, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::autosifenFlag = true;
		}
		else
		{
			BallsMerge::autosifenFlag = false;
		}
		});
	connect(ui.doubleSpinBox_32, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sfjcfd = ui.doubleSpinBox_32->value();
		});
	connect(ui.comboBox_13, &QComboBox::currentTextChanged, [=] {
		BallsMerge::zhongfenjian = virtualkey(ui.comboBox_13->currentText());
		});
	connect(ui.checkBox_38, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::zhongfentqFlag = true;
		}
		else
		{
			BallsMerge::zhongfentqFlag = false;
		}
		});
	connect(ui.checkBox_36, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::autozhongfenFlag = true;
		}
		else
		{
			BallsMerge::autozhongfenFlag = false;
		}
		});
	connect(ui.doubleSpinBox_31, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::zfjcfd = ui.doubleSpinBox_31->value();
		});
	connect(ui.comboBox_14, &QComboBox::currentTextChanged, [=] {
		BallsMerge::xuanzhuanjian1 = virtualkey(ui.comboBox_14->currentText());
		});
	connect(ui.checkBox_41, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::xuanzhuan1tqFlag = true;
		}
		else
		{
			BallsMerge::xuanzhuan1tqFlag = false;
		}
		});
	connect(ui.doubleSpinBox_33, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1jd1 = ui.doubleSpinBox_33->value();
		});
	connect(ui.doubleSpinBox_39, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1jd2 = ui.doubleSpinBox_39->value();
		});
	connect(ui.doubleSpinBox_34, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1jd3 = ui.doubleSpinBox_34->value();
		});
	connect(ui.doubleSpinBox_40, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1jd4 = ui.doubleSpinBox_40->value();
		});
	connect(ui.doubleSpinBox_35, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1fd1 = ui.doubleSpinBox_35->value();
		});
	connect(ui.doubleSpinBox_37, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1fd2 = ui.doubleSpinBox_37->value();
		});
	connect(ui.doubleSpinBox_36, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1fd3 = ui.doubleSpinBox_36->value();
		});
	connect(ui.doubleSpinBox_38, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::xuanzhuan1fd4 = ui.doubleSpinBox_38->value();
		});
	connect(ui.comboBox_15, &QComboBox::currentTextChanged, [=] {
		BallsMerge::banxuanjian1 = virtualkey(ui.comboBox_15->currentText());
		});
	connect(ui.checkBox_44, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::banxuan1tqFlag = true;
		}
		else
		{
			BallsMerge::banxuan1tqFlag = false;
		}
		});
	connect(ui.doubleSpinBox_41, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1jd1 = ui.doubleSpinBox_41->value();
		});
	connect(ui.doubleSpinBox_42, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1jd2 = ui.doubleSpinBox_42->value();
		});
	connect(ui.doubleSpinBox_44, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1jd3 = ui.doubleSpinBox_44->value();
		});
	connect(ui.doubleSpinBox_46, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1jd4 = ui.doubleSpinBox_46->value();
		});
	connect(ui.doubleSpinBox_43, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1fd1 = ui.doubleSpinBox_43->value();
		});
	connect(ui.doubleSpinBox_45, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1fd2 = ui.doubleSpinBox_45->value();
		});
	connect(ui.doubleSpinBox_47, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1fd3 = ui.doubleSpinBox_47->value();
		});
	connect(ui.doubleSpinBox_48, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::banxuan1fd4 = ui.doubleSpinBox_48->value();
		});
	connect(ui.comboBox_18, &QComboBox::currentTextChanged, [=] {
		BallsMerge::sheshoujian = virtualkey(ui.comboBox_18->currentText());
		});
	connect(ui.checkBox_53, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::sheshoutqFlag = true;
		}
		else
		{
			BallsMerge::sheshoutqFlag = false;
		}
		});
	connect(ui.doubleSpinBox_65, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoujd1 = ui.doubleSpinBox_65->value();
		});
	connect(ui.doubleSpinBox_66, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoujd2 = ui.doubleSpinBox_66->value();
		});
	connect(ui.doubleSpinBox_68, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoujd3 = ui.doubleSpinBox_68->value();
		});
	connect(ui.doubleSpinBox_70, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoujd4 = ui.doubleSpinBox_70->value();
		});
	connect(ui.doubleSpinBox_67, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoufd1 = ui.doubleSpinBox_67->value();
		});
	connect(ui.doubleSpinBox_69, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoufd2 = ui.doubleSpinBox_69->value();
		});
	connect(ui.doubleSpinBox_71, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoufd3 = ui.doubleSpinBox_71->value();
		});
	connect(ui.doubleSpinBox_72, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::sheshoufd4 = ui.doubleSpinBox_72->value();
		});
	connect(ui.comboBox_19, &QComboBox::currentTextChanged, [=] {
		BallsMerge::houyangjian = virtualkey(ui.comboBox_19->currentText());
		});
	connect(ui.checkBox_56, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::houyangtqFlag = true;
		}
		else
		{
			BallsMerge::houyangtqFlag = false;
		}
		});
	connect(ui.checkBox_54, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			BallsMerge::autohouyangFlag = true;
		}
		else
		{
			BallsMerge::autohouyangFlag = false;
		}
		});
	connect(ui.doubleSpinBox_73, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::hyjcfd1 = ui.doubleSpinBox_73->value();
		});
	connect(ui.doubleSpinBox_74, &QDoubleSpinBox::valueChanged, [=] {
		BallsMerge::hyjcfd2 = ui.doubleSpinBox_74->value();
		});
	connect(ui.comboBox_2, &QComboBox::currentTextChanged, [=] {
		BallsMerge::tuqiujian = virtualkey(ui.comboBox_2->currentText());
		});
	connect(ui.comboBox_3, &QComboBox::currentTextChanged, [=] {
		BallsMerge::fenshenjian = virtualkey(ui.comboBox_3->currentText());
		});
	connect(ui.comboBox_4, &QComboBox::currentTextChanged, [=] {
		BallsMerge::qupijian = virtualkey(ui.comboBox_4->currentText());
		});
	connect(ui.checkBox_11, &QCheckBox::toggled, [=](bool checked) {
		if (checked)
		{
			ballsMerge->juneiqupiFlag = true;
		}
		else
		{
			ballsMerge->juneiqupiFlag = false;
		}
		});
	connect(ui.treeWidget, &QTreeWidget::itemChanged, [=](QTreeWidgetItem* item, int column) {
		
		if (column != 0) return;
		QString text = item->text(column);
		bool isChecked = (item->checkState(column) == Qt::Checked);

		if (text == "一键三角1") {
			BallsMerge::sanjiao1Flag = isChecked;
		}
		else if (text == "一键三角2") {
			BallsMerge::sanjiao2Flag = isChecked;
		}
		else if (text == "一键三角3") {
			BallsMerge::sanjiao3Flag = isChecked;
		}
		else if (text == "冲球-直线") {
			BallsMerge::chongqiuFlag = isChecked;
		}
		else if (text == "侧合-四分") {
			BallsMerge::sifenFlag = isChecked;
		}
		else if (text == "侧合-中分") {
			BallsMerge::zhongfenFlag = isChecked;
		}
		else if (text == "旋转") {
			BallsMerge::xuanzhuan1Flag = isChecked;
		}
		else if (text == "半旋") {
			BallsMerge::banxuan1Flag = isChecked;
		}
		else if (text == "蛇手") {
			BallsMerge::sheshouFlag = isChecked;
		}
		else if (text == "后仰") {
			BallsMerge::houyangFlag = isChecked;
		}
		});
	connect(ui.tableWidget, &QTableWidget::cellChanged, [=] {
		if(isUpdate)
		{
			if (auto item = ui.tableWidget->item(0, 1)) BallsMerge::sj1yc1 = item->text().toInt();
			if (auto item = ui.tableWidget->item(1, 1)) BallsMerge::sj1yc2 = item->text().toInt();
			if (auto item = ui.tableWidget->item(2, 1)) BallsMerge::sj1yc3 = item->text().toInt();
			if (auto item = ui.tableWidget->item(3, 1)) BallsMerge::sj1yc4 = item->text().toInt();
			if (auto item = ui.tableWidget->item(4, 1)) BallsMerge::sj1yc5 = item->text().toInt();
			if (auto item = ui.tableWidget->item(5, 1)) BallsMerge::sj1yc6 = item->text().toInt();
			if (auto item = ui.tableWidget->item(6, 1)) BallsMerge::sj1cs = item->text().toInt();
			if (auto item = ui.tableWidget->item(7, 1)) BallsMerge::sj1fsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_2, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_2->item(0, 1)) BallsMerge::sj2yc1 = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(1, 1)) BallsMerge::sj2yc2 = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(2, 1)) BallsMerge::sj2yc3 = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(3, 1)) BallsMerge::sj2yc4 = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(4, 1)) BallsMerge::sj2yc5 = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(5, 1)) BallsMerge::sj2yc6 = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(6, 1)) BallsMerge::sj2cs = item->text().toInt();
			if (auto item = ui.tableWidget_2->item(7, 1)) BallsMerge::sj2fsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_3, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_3->item(0, 1)) BallsMerge::sj3yc1 = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(1, 1)) BallsMerge::sj3yc2 = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(2, 1)) BallsMerge::sj3yc3 = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(3, 1)) BallsMerge::sj3yc4 = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(4, 1)) BallsMerge::sj3yc5 = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(5, 1)) BallsMerge::sj3yc6 = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(6, 1)) BallsMerge::sj3cs = item->text().toInt();
			if (auto item = ui.tableWidget_3->item(7, 1)) BallsMerge::sj3fsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_4, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_4->item(0, 1)) BallsMerge::cqyc1 = item->text().toInt();
			if (auto item = ui.tableWidget_4->item(1, 1)) BallsMerge::cqyc2 = item->text().toInt();
			if (auto item = ui.tableWidget_4->item(2, 1)) BallsMerge::cqcs = item->text().toInt();
			if (auto item = ui.tableWidget_4->item(3, 1)) BallsMerge::cqfsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_5, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_5->item(0, 1)) BallsMerge::sfyc1 = item->text().toInt();
			if (auto item = ui.tableWidget_5->item(1, 1)) BallsMerge::sfyc2 = item->text().toInt();
			if (auto item = ui.tableWidget_5->item(2, 1)) BallsMerge::sfyc3 = item->text().toInt();
			if (auto item = ui.tableWidget_5->item(3, 1)) BallsMerge::sfyc4 = item->text().toInt();
			if (auto item = ui.tableWidget_5->item(4, 1)) BallsMerge::sfyc5 = item->text().toInt();
			if (auto item = ui.tableWidget_5->item(5, 1)) BallsMerge::sfcs = item->text().toInt();
			if (auto item = ui.tableWidget_5->item(6, 1)) BallsMerge::sffsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_6, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_6->item(0, 1)) BallsMerge::zfyc1 = item->text().toInt();
			if (auto item = ui.tableWidget_6->item(1, 1)) BallsMerge::zfyc2 = item->text().toInt();
			if (auto item = ui.tableWidget_6->item(2, 1)) BallsMerge::zfyc3 = item->text().toInt();
			if (auto item = ui.tableWidget_6->item(3, 1)) BallsMerge::zfyc4 = item->text().toInt();
			if (auto item = ui.tableWidget_6->item(4, 1)) BallsMerge::zfyc5 = item->text().toInt();
			if (auto item = ui.tableWidget_6->item(5, 1)) BallsMerge::zfcs = item->text().toInt();
			if (auto item = ui.tableWidget_6->item(6, 1)) BallsMerge::zffsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_12, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_12->item(0, 1)) BallsMerge::hyyc1 = item->text().toInt();
			if (auto item = ui.tableWidget_12->item(1, 1)) BallsMerge::hyyc2 = item->text().toInt();
			if (auto item = ui.tableWidget_12->item(2, 1)) BallsMerge::hyyc3 = item->text().toInt();
			if (auto item = ui.tableWidget_12->item(3, 1)) BallsMerge::hyyc4 = item->text().toInt();
			if (auto item = ui.tableWidget_12->item(4, 1)) BallsMerge::hyyc5 = item->text().toInt();
			if (auto item = ui.tableWidget_12->item(5, 1)) BallsMerge::hycs = item->text().toInt();
			if (auto item = ui.tableWidget_12->item(6, 1)) BallsMerge::hyfsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_7, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_7->item(0, 1)) BallsMerge::xz1yc1 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(1, 1)) BallsMerge::xz1yc2 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(2, 1)) BallsMerge::xz1yc3 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(3, 1)) BallsMerge::xz1yc4 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(4, 1)) BallsMerge::xz1yc5 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(5, 1)) BallsMerge::xz1yc6 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(6, 1)) BallsMerge::xz1yc7 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(7, 1)) BallsMerge::xz1yc8 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(8, 1)) BallsMerge::xz1yc9 = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(9, 1)) BallsMerge::xz1cs = item->text().toInt();
			if (auto item = ui.tableWidget_7->item(10, 1)) BallsMerge::xz1fsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_8, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_8->item(0, 1)) BallsMerge::bx1yc1 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(1, 1)) BallsMerge::bx1yc2 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(2, 1)) BallsMerge::bx1yc3 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(3, 1)) BallsMerge::bx1yc4 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(4, 1)) BallsMerge::bx1yc5 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(5, 1)) BallsMerge::bx1yc6 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(6, 1)) BallsMerge::bx1yc7 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(7, 1)) BallsMerge::bx1yc8 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(8, 1)) BallsMerge::bx1yc9 = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(9, 1)) BallsMerge::bx1cs = item->text().toInt();
			if (auto item = ui.tableWidget_8->item(10, 1)) BallsMerge::bx1fsjg = item->text().toInt();
		}
		});
	connect(ui.tableWidget_11, &QTableWidget::cellChanged, [=] {
		if (isUpdate)
		{
			if (auto item = ui.tableWidget_11->item(0, 1)) BallsMerge::ssyc1 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(1, 1)) BallsMerge::ssyc2 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(2, 1)) BallsMerge::ssyc3 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(3, 1)) BallsMerge::ssyc4 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(4, 1)) BallsMerge::ssyc5 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(5, 1)) BallsMerge::ssyc6 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(6, 1)) BallsMerge::ssyc7 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(7, 1)) BallsMerge::ssyc8 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(8, 1)) BallsMerge::ssyc9 = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(9, 1)) BallsMerge::sscs = item->text().toInt();
			if (auto item = ui.tableWidget_11->item(10, 1)) BallsMerge::ssfsjg = item->text().toInt();
		}
		});
	connect(ui.groupBox_19, &QGroupBox::toggled, [=]() {
		if (ui.groupBox_19->isChecked())
		{
			BallsMerge::zhongfenMacroFlag = true;
		}
		else
		{
			BallsMerge::zhongfenMacroFlag = false;
		}
		});
	connect(ui.groupBox_20, &QGroupBox::toggled, [=]() {
		if (ui.groupBox_20->isChecked())
		{
			BallsMerge::sifenMacroFlag = true;
		}
		else
		{
			BallsMerge::sifenMacroFlag = false;
		}
		});
	connect(ui.groupBox_21, &QGroupBox::toggled, [=]() {
		if (ui.groupBox_21->isChecked())
		{
			BallsMerge::xuanzhuanMacroFlag = true;
		}
		else
		{
			BallsMerge::xuanzhuanMacroFlag = false;
		}
		});
	connect(ui.groupBox_22, &QGroupBox::toggled, [=]() {
		if (ui.groupBox_22->isChecked())
		{
			BallsMerge::bafenMacroFlag = true;
		}
		else
		{
			BallsMerge::bafenMacroFlag = false;
		}
		});
}

MainWindow::~MainWindow()
{
	QFile file("config.json");
	if (file.open(QIODevice::ReadWrite))
	{
		QByteArray data = file.readAll();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
		QJsonObject jsonObj = jsonDoc.object();

		jsonObj["checkBox"] = ui.checkBox->isChecked();
		jsonObj["doubleSpinBox"] = ui.doubleSpinBox->value();
		jsonObj["doubleSpinBox_2"] = ui.doubleSpinBox_2->value();
		jsonObj["checkBox_3"] = ui.checkBox_3->isChecked();
		jsonObj["checkBox_4"] = ui.checkBox_4->isChecked();
		jsonObj["doubleSpinBox_3"] = ui.doubleSpinBox_3->value();
		jsonObj["doubleSpinBox_4"] = ui.doubleSpinBox_4->value();
		jsonObj["doubleSpinBox_5"] = ui.doubleSpinBox_5->value();
		jsonObj["checkBox_5"] = ui.checkBox_5->isChecked();
		jsonObj["doubleSpinBox_6"] = ui.doubleSpinBox_6->value();
		jsonObj["checkBox_6"] = ui.checkBox_6->isChecked();
		jsonObj["checkBox_7"] = ui.checkBox_7->isChecked();
		jsonObj["checkBox_8"] = ui.checkBox_8->isChecked();
		jsonObj["doubleSpinBox_7"] = ui.doubleSpinBox_7->value();
		jsonObj["doubleSpinBox_8"] = ui.doubleSpinBox_8->value();
		jsonObj["checkBox_11"] = ui.checkBox_11->isChecked();
		jsonObj["comboBox_4"] = ui.comboBox_4->currentText();
		jsonObj["checkBox_4"] = ui.checkBox_4->isChecked();
		jsonObj["comboBox"] = ui.comboBox->currentText();
		jsonObj["comboBox_2"] = ui.comboBox_2->currentText();
		jsonObj["comboBox_3"] = ui.comboBox_3->currentText();
		jsonObj["checkBox_15"] = ui.checkBox_15->isChecked();
		jsonObj["checkBox_16"] = ui.checkBox_16->isChecked();
		jsonObj["checkBox_21"] = ui.checkBox_21->isChecked();
		jsonObj["checkBox_24"] = ui.checkBox_24->isChecked();
		jsonObj["checkBox_25"] = ui.checkBox_25->isChecked();
		jsonObj["checkBox_26"] = ui.checkBox_26->isChecked();
		jsonObj["checkBox_30"] = ui.checkBox_30->isChecked();
		jsonObj["checkBox_31"] = ui.checkBox_31->isChecked();
		jsonObj["checkBox_32"] = ui.checkBox_32->isChecked();
		jsonObj["checkBox_33"] = ui.checkBox_33->isChecked();
		jsonObj["checkBox_35"] = ui.checkBox_35->isChecked();
		jsonObj["checkBox_36"] = ui.checkBox_36->isChecked();
		jsonObj["checkBox_38"] = ui.checkBox_38->isChecked();
		jsonObj["checkBox_39"] = ui.checkBox_39->isChecked();
		jsonObj["checkBox_41"] = ui.checkBox_41->isChecked();
		jsonObj["checkBox_42"] = ui.checkBox_42->isChecked();
		jsonObj["checkBox_51"] = ui.checkBox_51->isChecked();
		jsonObj["checkBox_53"] = ui.checkBox_53->isChecked();
		jsonObj["checkBox_54"] = ui.checkBox_54->isChecked();
		jsonObj["checkBox_56"] = ui.checkBox_56->isChecked();
		jsonObj["comboBox_5"] = ui.comboBox_5->currentText();
		jsonObj["comboBox_6"] = ui.comboBox_6->currentText();
		jsonObj["comboBox_7"] = ui.comboBox_7->currentText();
		jsonObj["comboBox_8"] = ui.comboBox_8->currentText();
		jsonObj["comboBox_9"] = ui.comboBox_9->currentText();
		jsonObj["comboBox_10"] = ui.comboBox_10->currentText();
		jsonObj["comboBox_11"] = ui.comboBox_11->currentText();
		jsonObj["comboBox_12"] = ui.comboBox_12->currentText();
		jsonObj["comboBox_13"] = ui.comboBox_13->currentText();
		jsonObj["comboBox_14"] = ui.comboBox_14->currentText();
		jsonObj["comboBox_15"] = ui.comboBox_15->currentText();
		jsonObj["comboBox_18"] = ui.comboBox_18->currentText();
		jsonObj["comboBox_19"] = ui.comboBox_19->currentText();
		jsonObj["comboBox_20"] = ui.comboBox_20->currentText();
		jsonObj["comboBox_21"] = ui.comboBox_21->currentText();
		jsonObj["comboBox_22"] = ui.comboBox_22->currentText();
		jsonObj["comboBox_23"] = ui.comboBox_23->currentText();
		jsonObj["comboBox_24"] = ui.comboBox_24->currentText();
		jsonObj["comboBox_25"] = ui.comboBox_25->currentText();
		jsonObj["doubleSpinBox_14"] = ui.doubleSpinBox_14->value();
		jsonObj["doubleSpinBox_15"] = ui.doubleSpinBox_15->value();
		jsonObj["doubleSpinBox_16"] = ui.doubleSpinBox_16->value();
		jsonObj["doubleSpinBox_18"] = ui.doubleSpinBox_18->value();
		jsonObj["doubleSpinBox_20"] = ui.doubleSpinBox_20->value();
		jsonObj["doubleSpinBox_21"] = ui.doubleSpinBox_21->value();
		jsonObj["doubleSpinBox_31"] = ui.doubleSpinBox_31->value();
		jsonObj["doubleSpinBox_32"] = ui.doubleSpinBox_32->value();
		jsonObj["doubleSpinBox_33"] = ui.doubleSpinBox_33->value();
		jsonObj["doubleSpinBox_34"] = ui.doubleSpinBox_34->value();
		jsonObj["doubleSpinBox_35"] = ui.doubleSpinBox_35->value();
		jsonObj["doubleSpinBox_36"] = ui.doubleSpinBox_36->value();
		jsonObj["doubleSpinBox_37"] = ui.doubleSpinBox_37->value();
		jsonObj["doubleSpinBox_38"] = ui.doubleSpinBox_38->value();
		jsonObj["doubleSpinBox_39"] = ui.doubleSpinBox_39->value();
		jsonObj["doubleSpinBox_40"] = ui.doubleSpinBox_40->value();
		jsonObj["doubleSpinBox_41"] = ui.doubleSpinBox_41->value();
		jsonObj["doubleSpinBox_42"] = ui.doubleSpinBox_42->value();
		jsonObj["doubleSpinBox_43"] = ui.doubleSpinBox_43->value();
		jsonObj["doubleSpinBox_44"] = ui.doubleSpinBox_44->value();
		jsonObj["doubleSpinBox_45"] = ui.doubleSpinBox_45->value();
		jsonObj["doubleSpinBox_46"] = ui.doubleSpinBox_46->value();
		jsonObj["doubleSpinBox_47"] = ui.doubleSpinBox_47->value();
		jsonObj["doubleSpinBox_48"] = ui.doubleSpinBox_48->value();
		jsonObj["doubleSpinBox_65"] = ui.doubleSpinBox_65->value();
		jsonObj["doubleSpinBox_66"] = ui.doubleSpinBox_66->value();
		jsonObj["doubleSpinBox_67"] = ui.doubleSpinBox_67->value();
		jsonObj["doubleSpinBox_68"] = ui.doubleSpinBox_68->value();
		jsonObj["doubleSpinBox_69"] = ui.doubleSpinBox_69->value();
		jsonObj["doubleSpinBox_70"] = ui.doubleSpinBox_70->value();
		jsonObj["doubleSpinBox_71"] = ui.doubleSpinBox_71->value();
		jsonObj["doubleSpinBox_72"] = ui.doubleSpinBox_72->value();
		jsonObj["doubleSpinBox_73"] = ui.doubleSpinBox_73->value();
		jsonObj["doubleSpinBox_74"] = ui.doubleSpinBox_74->value();
		jsonObj["doubleSpinBox_75"] = ui.doubleSpinBox_75->value();
		jsonObj["doubleSpinBox_77"] = ui.doubleSpinBox_77->value();
		jsonObj["doubleSpinBox_78"] = ui.doubleSpinBox_78->value();
		jsonObj["lineEdit_2"] = ui.lineEdit_2->text();

		jsonObj["sj1yc1"] = BallsMerge::sj1yc1;
		jsonObj["sj1yc2"] = BallsMerge::sj1yc2;
		jsonObj["sj1yc3"] = BallsMerge::sj1yc3;
		jsonObj["sj1yc4"] = BallsMerge::sj1yc4;
		jsonObj["sj1yc5"] = BallsMerge::sj1yc5;
		jsonObj["sj1yc6"] = BallsMerge::sj1yc6;
		jsonObj["sj1cs"] = BallsMerge::sj1cs;
		jsonObj["sj1fsjg"] = BallsMerge::sj1fsjg;
	
		jsonObj["sj2yc1"] = BallsMerge::sj2yc1;
		jsonObj["sj2yc2"] = BallsMerge::sj2yc2;
		jsonObj["sj2yc3"] = BallsMerge::sj2yc3;
		jsonObj["sj2yc4"] = BallsMerge::sj2yc4;
		jsonObj["sj2yc5"] = BallsMerge::sj2yc5;
		jsonObj["sj2yc6"] = BallsMerge::sj2yc6;
		jsonObj["sj2cs"] = BallsMerge::sj2cs;
		jsonObj["sj2fsjg"] = BallsMerge::sj2fsjg;
		
		jsonObj["sj3yc1"] = BallsMerge::sj3yc1;
		jsonObj["sj3yc2"] = BallsMerge::sj3yc2;
		jsonObj["sj3yc3"] = BallsMerge::sj3yc3;
		jsonObj["sj3yc4"] = BallsMerge::sj3yc4;
		jsonObj["sj3yc5"] = BallsMerge::sj3yc5;
		jsonObj["sj3yc6"] = BallsMerge::sj3yc6;
		jsonObj["sj3cs"] = BallsMerge::sj3cs;
		jsonObj["sj3fsjg"] = BallsMerge::sj3fsjg;
		
		jsonObj["cqyc1"] = BallsMerge::cqyc1;
		jsonObj["cqyc2"] = BallsMerge::cqyc2;
		jsonObj["cqcs"] = BallsMerge::cqcs;
		jsonObj["cqfsjg"] = BallsMerge::cqfsjg;
		
		jsonObj["sfyc1"] = BallsMerge::sfyc1;
		jsonObj["sfyc2"] = BallsMerge::sfyc2;
		jsonObj["sfyc3"] = BallsMerge::sfyc3;
		jsonObj["sfyc4"] = BallsMerge::sfyc4;
		jsonObj["sfyc5"] = BallsMerge::sfyc5;
		jsonObj["sfcs"] = BallsMerge::sfcs;
		jsonObj["sffsjg"] = BallsMerge::sffsjg;
		
		jsonObj["zfyc1"] = BallsMerge::zfyc1;
		jsonObj["zfyc2"] = BallsMerge::zfyc2;
		jsonObj["zfyc3"] = BallsMerge::zfyc3;
		jsonObj["zfyc4"] = BallsMerge::zfyc4;
		jsonObj["zfyc5"] = BallsMerge::zfyc5;
		jsonObj["zfcs"] = BallsMerge::zfcs;
		jsonObj["zffsjg"] = BallsMerge::zffsjg;
		
		jsonObj["hyyc1"] = BallsMerge::hyyc1;
		jsonObj["hyyc2"] = BallsMerge::hyyc2;
		jsonObj["hyyc3"] = BallsMerge::hyyc3;
		jsonObj["hyyc4"] = BallsMerge::hyyc4;
		jsonObj["hyyc5"] = BallsMerge::hyyc5;
		jsonObj["hycs"] = BallsMerge::hycs;
		jsonObj["hyfsjg"] = BallsMerge::hyfsjg;
		
		jsonObj["xz1yc1"] = BallsMerge::xz1yc1;
		jsonObj["xz1yc2"] = BallsMerge::xz1yc2;
		jsonObj["xz1yc3"] = BallsMerge::xz1yc3;
		jsonObj["xz1yc4"] = BallsMerge::xz1yc4;
		jsonObj["xz1yc5"] = BallsMerge::xz1yc5;
		jsonObj["xz1yc6"] = BallsMerge::xz1yc6;
		jsonObj["xz1yc7"] = BallsMerge::xz1yc7;
		jsonObj["xz1yc8"] = BallsMerge::xz1yc8;
		jsonObj["xz1yc9"] = BallsMerge::xz1yc9;
		jsonObj["xz1cs"] = BallsMerge::xz1cs;
		jsonObj["xz1fsjg"] = BallsMerge::xz1fsjg;

		jsonObj["bx1yc1"] = BallsMerge::bx1yc1;
		jsonObj["bx1yc2"] = BallsMerge::bx1yc2;
		jsonObj["bx1yc3"] = BallsMerge::bx1yc3;
		jsonObj["bx1yc4"] = BallsMerge::bx1yc4;
		jsonObj["bx1yc5"] = BallsMerge::bx1yc5;
		jsonObj["bx1yc6"] = BallsMerge::bx1yc6;
		jsonObj["bx1yc7"] = BallsMerge::bx1yc7;
		jsonObj["bx1yc8"] = BallsMerge::bx1yc8;
		jsonObj["bx1yc9"] = BallsMerge::bx1yc9;
		jsonObj["bx1cs"] = BallsMerge::bx1cs;
		jsonObj["bx1fsjg"] = BallsMerge::bx1fsjg;

		jsonObj["ssyc1"] = BallsMerge::ssyc1;
		jsonObj["ssyc2"] = BallsMerge::ssyc2;
		jsonObj["ssyc3"] = BallsMerge::ssyc3;
		jsonObj["ssyc4"] = BallsMerge::ssyc4;
		jsonObj["ssyc5"] = BallsMerge::ssyc5;
		jsonObj["ssyc6"] = BallsMerge::ssyc6;
		jsonObj["ssyc7"] = BallsMerge::ssyc7;
		jsonObj["ssyc8"] = BallsMerge::ssyc8;
		jsonObj["ssyc9"] = BallsMerge::ssyc9;
		jsonObj["sscs"] = BallsMerge::sscs;
		jsonObj["ssfsjg"] = BallsMerge::ssfsjg;

		jsonObj["sanjiao1Flag"] = BallsMerge::sanjiao1Flag;
		jsonObj["sanjiao2Flag"] = BallsMerge::sanjiao2Flag;
		jsonObj["sanjiao3Flag"] = BallsMerge::sanjiao3Flag;
		jsonObj["chongqiuFlag"] = BallsMerge::chongqiuFlag;
		jsonObj["sifenFlag"] = BallsMerge::sifenFlag;
		jsonObj["zhongfenFlag"] = BallsMerge::zhongfenFlag;
		jsonObj["xuanzhuan1Flag"] = BallsMerge::xuanzhuan1Flag;
		jsonObj["banxuan1Flag"] = BallsMerge::banxuan1Flag;
		jsonObj["xuanzhuan2Flag"] = BallsMerge::xuanzhuan2Flag;
		jsonObj["banxuan2Flag"] = BallsMerge::banxuan2Flag;
		jsonObj["sheshouFlag"] = BallsMerge::sheshouFlag;
		jsonObj["houyangFlag"] = BallsMerge::houyangFlag;

		jsonObj["zhongfenMacroFlag"] = BallsMerge::zhongfenMacroFlag;
		jsonObj["sifenMacroFlag"] = BallsMerge::sifenMacroFlag;
		jsonObj["xuanzhuanMacroFlag"] = BallsMerge::xuanzhuanMacroFlag;
		jsonObj["bafenMacroFlag"] = BallsMerge::bafenMacroFlag;
		QJsonDocument updatedJsonDoc(jsonObj); 
		file.resize(0);
		file.write(updatedJsonDoc.toJson());

		uninstallGlobalHook();
	}
}

void MainWindow::setTable(const QString mode)
{
	QString filePath = "./config.json";
	if (QFile::exists(filePath))
	{
		QFile file(filePath);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(this, "Waring", "Can not find config.json");
		}
		else
		{
			QByteArray data = file.readAll();
			QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
			QJsonObject jsonObj = jsonDoc.object();
			QJsonObject Obj = jsonObj.value(mode).toObject();
			BallsMerge::sj1cs = Obj.value("sj1cs").toInt();
			BallsMerge::sj1fsjg = Obj.value("sj1fsjg").toInt();
			BallsMerge::sj1yc1 = Obj.value("sj1yc1").toInt();
			BallsMerge::sj1yc2 = Obj.value("sj1yc2").toInt();
			BallsMerge::sj1yc3 = Obj.value("sj1yc3").toInt();
			BallsMerge::sj1yc4 = Obj.value("sj1yc4").toInt();
			BallsMerge::sj1yc5 = Obj.value("sj1yc5").toInt();
			BallsMerge::sj1yc6 = Obj.value("sj1yc6").toInt();
			BallsMerge::sj2cs = Obj.value("sj2cs").toInt();
			BallsMerge::sj2fsjg = Obj.value("sj2fsjg").toInt();
			BallsMerge::sj2yc1 = Obj.value("sj2yc1").toInt();
			BallsMerge::sj2yc2 = Obj.value("sj2yc2").toInt();
			BallsMerge::sj2yc3 = Obj.value("sj2yc3").toInt();
			BallsMerge::sj2yc4 = Obj.value("sj2yc4").toInt();
			BallsMerge::sj2yc5 = Obj.value("sj2yc5").toInt();
			BallsMerge::sj2yc6 = Obj.value("sj2yc6").toInt();
			BallsMerge::sj3cs = Obj.value("sj3cs").toInt();
			BallsMerge::sj3fsjg = Obj.value("sj3fsjg").toInt();
			BallsMerge::sj3yc1 = Obj.value("sj3yc1").toInt();
			BallsMerge::sj3yc2 = Obj.value("sj3yc2").toInt();
			BallsMerge::sj3yc3 = Obj.value("sj3yc3").toInt();
			BallsMerge::sj3yc4 = Obj.value("sj3yc4").toInt();
			BallsMerge::sj3yc5 = Obj.value("sj3yc5").toInt();
			BallsMerge::sj3yc6 = Obj.value("sj3yc6").toInt();
			BallsMerge::sscs = Obj.value("sscs").toInt();
			BallsMerge::ssfsjg = Obj.value("ssfsjg").toInt();
			BallsMerge::ssyc1 = Obj.value("ssyc1").toInt();
			BallsMerge::ssyc2 = Obj.value("ssyc2").toInt();
			BallsMerge::ssyc3 = Obj.value("ssyc3").toInt();
			BallsMerge::ssyc4 = Obj.value("ssyc4").toInt();
			BallsMerge::ssyc5 = Obj.value("ssyc5").toInt();
			BallsMerge::ssyc6 = Obj.value("ssyc6").toInt();
			BallsMerge::ssyc7 = Obj.value("ssyc7").toInt();
			BallsMerge::ssyc8 = Obj.value("ssyc8").toInt();
			BallsMerge::ssyc9 = Obj.value("ssyc9").toInt();
			BallsMerge::xz1cs = Obj.value("xz1cs").toInt();
			BallsMerge::xz1fsjg = Obj.value("xz1fsjg").toInt();
			BallsMerge::xz1yc1 = Obj.value("xz1yc1").toInt();
			BallsMerge::xz1yc2 = Obj.value("xz1yc2").toInt();
			BallsMerge::xz1yc3 = Obj.value("xz1yc3").toInt();
			BallsMerge::xz1yc4 = Obj.value("xz1yc4").toInt();
			BallsMerge::xz1yc5 = Obj.value("xz1yc5").toInt();
			BallsMerge::xz1yc6 = Obj.value("xz1yc6").toInt();
			BallsMerge::xz1yc7 = Obj.value("xz1yc7").toInt();
			BallsMerge::xz1yc8 = Obj.value("xz1yc8").toInt();
			BallsMerge::xz1yc9 = Obj.value("xz1yc9").toInt();
			BallsMerge::zfcs = Obj.value("zfcs").toInt();
			BallsMerge::zffsjg = Obj.value("zffsjg").toInt();
			BallsMerge::zfyc1 = Obj.value("zfyc1").toInt();
			BallsMerge::zfyc2 = Obj.value("zfyc2").toInt();
			BallsMerge::zfyc3 = Obj.value("zfyc3").toInt();
			BallsMerge::zfyc4 = Obj.value("zfyc4").toInt();
			BallsMerge::zfyc5 = Obj.value("zfyc5").toInt();
			BallsMerge::hycs = Obj.value("hycs").toInt();
			BallsMerge::hyfsjg = Obj.value("hyfsjg").toInt();
			BallsMerge::hyyc1 = Obj.value("hyyc1").toInt();
			BallsMerge::hyyc2 = Obj.value("hyyc2").toInt();
			BallsMerge::hyyc3 = Obj.value("hyyc3").toInt();
			BallsMerge::hyyc4 = Obj.value("hyyc4").toInt();
			BallsMerge::hyyc5 = Obj.value("hyyc5").toInt();
			BallsMerge::bx1cs = Obj.value("bx1cs").toInt();
			BallsMerge::bx1fsjg = Obj.value("bx1fsjg").toInt();
			BallsMerge::bx1yc1 = Obj.value("bx1yc1").toInt();
			BallsMerge::bx1yc2 = Obj.value("bx1yc2").toInt();
			BallsMerge::bx1yc3 = Obj.value("bx1yc3").toInt();
			BallsMerge::bx1yc4 = Obj.value("bx1yc4").toInt();
			BallsMerge::bx1yc5 = Obj.value("bx1yc5").toInt();
			BallsMerge::bx1yc6 = Obj.value("bx1yc6").toInt();
			BallsMerge::bx1yc7 = Obj.value("bx1yc7").toInt();
			BallsMerge::bx1yc8 = Obj.value("bx1yc8").toInt();
			BallsMerge::bx1yc9 = Obj.value("bx1yc9").toInt();
			BallsMerge::sfcs = Obj.value("sfcs").toInt();
			BallsMerge::sffsjg = Obj.value("sffsjg").toInt();
			BallsMerge::sfyc1 = Obj.value("sfyc1").toInt();
			BallsMerge::sfyc2 = Obj.value("sfyc2").toInt();
			BallsMerge::sfyc3 = Obj.value("sfyc3").toInt();
			BallsMerge::sfyc4 = Obj.value("sfyc4").toInt();
			BallsMerge::sfyc5 = Obj.value("sfyc5").toInt();

			ui.tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc1)));
			ui.tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc2)));
			ui.tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc3)));
			ui.tableWidget->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc4)));
			ui.tableWidget->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc5)));
			ui.tableWidget->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc6)));
			ui.tableWidget->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1cs)));
			ui.tableWidget->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1fsjg)));
			ui.tableWidget_2->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc1)));
			ui.tableWidget_2->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc2)));
			ui.tableWidget_2->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc3)));
			ui.tableWidget_2->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc4)));
			ui.tableWidget_2->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc5)));
			ui.tableWidget_2->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc6)));
			ui.tableWidget_2->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2cs)));
			ui.tableWidget_2->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2fsjg)));
			ui.tableWidget_3->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc1)));
			ui.tableWidget_3->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc2)));
			ui.tableWidget_3->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc3)));
			ui.tableWidget_3->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc4)));
			ui.tableWidget_3->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc5)));
			ui.tableWidget_3->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc6)));
			ui.tableWidget_3->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3cs)));
			ui.tableWidget_3->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3fsjg)));
			ui.tableWidget_4->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::cqyc1)));
			ui.tableWidget_4->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::cqyc2)));
			ui.tableWidget_4->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::cqcs)));
			ui.tableWidget_4->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::cqfsjg)));
			ui.tableWidget_5->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc1)));
			ui.tableWidget_5->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc2)));
			ui.tableWidget_5->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc3)));
			ui.tableWidget_5->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc4)));
			ui.tableWidget_5->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc5)));
			ui.tableWidget_5->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sfcs)));
			ui.tableWidget_5->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sffsjg)));
			ui.tableWidget_11->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc1)));
			ui.tableWidget_11->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc2)));
			ui.tableWidget_11->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc3)));
			ui.tableWidget_11->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc4)));
			ui.tableWidget_11->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc5)));
			ui.tableWidget_11->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc6)));
			ui.tableWidget_11->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc7)));
			ui.tableWidget_11->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc8)));
			ui.tableWidget_11->setItem(8, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc9)));
			ui.tableWidget_11->setItem(9, 1, new QTableWidgetItem(QString::number(BallsMerge::sscs)));
			ui.tableWidget_11->setItem(10, 1, new QTableWidgetItem(QString::number(BallsMerge::ssfsjg)));
			ui.tableWidget_7->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc1)));
			ui.tableWidget_7->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc2)));
			ui.tableWidget_7->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc3)));
			ui.tableWidget_7->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc4)));
			ui.tableWidget_7->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc5)));
			ui.tableWidget_7->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc6)));
			ui.tableWidget_7->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc7)));
			ui.tableWidget_7->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc8)));
			ui.tableWidget_7->setItem(8, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc9)));
            ui.tableWidget_7->setItem(9, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1cs)));
            ui.tableWidget_7->setItem(10, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1fsjg)));
			ui.tableWidget_6->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc1)));
			ui.tableWidget_6->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc2)));
			ui.tableWidget_6->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc3)));
			ui.tableWidget_6->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc4)));
			ui.tableWidget_6->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc5)));
			ui.tableWidget_6->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::zfcs)));
			ui.tableWidget_6->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::zffsjg)));
			ui.tableWidget_12->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc1)));
			ui.tableWidget_12->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc2)));
			ui.tableWidget_12->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc3)));
			ui.tableWidget_12->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc4)));
			ui.tableWidget_12->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc5)));
			ui.tableWidget_12->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::hycs)));
			ui.tableWidget_12->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::hyfsjg)));
			ui.tableWidget_8->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc1)));
			ui.tableWidget_8->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc2)));
            ui.tableWidget_8->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc3)));
			ui.tableWidget_8->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc4)));
			ui.tableWidget_8->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc5)));
			ui.tableWidget_8->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc6)));
			ui.tableWidget_8->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc7)));
			ui.tableWidget_8->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc8)));
			ui.tableWidget_8->setItem(8, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc9)));
			file.close();

			isUpdate = false;	
		}
	}
}

void MainWindow::loadjson()
{
	QString filePath = "config.json";
	if (QFile::exists(filePath))
	{
		QFile file(filePath);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(this, "警告", "找不到config.json文件");
		}
		else
		{
			QByteArray data = file.readAll();
			QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
			QJsonObject jsonObj = jsonDoc.object();

			bool checkBox = jsonObj.value("checkBox").toBool();
			bool checkBox_2 = jsonObj.value("checkBox_2").toBool();
			float doubleSpinBox = jsonObj.value("doubleSpinBox").toDouble();
			float doubleSpinBox_2 = jsonObj.value("doubleSpinBox_2").toDouble();
			bool checkBox_3 = jsonObj.value("checkBox_3").toBool();
			bool checkBox_4 = jsonObj.value("checkBox_4").toBool();
			float doubleSpinBox_3 = jsonObj.value("doubleSpinBox_3").toDouble();
			float doubleSpinBox_4 = jsonObj.value("doubleSpinBox_4").toDouble();
			float doubleSpinBox_5 = jsonObj.value("doubleSpinBox_5").toDouble();
			bool checkBox_5 = jsonObj.value("checkBox_5").toBool();
			float doubleSpinBox_6 = jsonObj.value("doubleSpinBox_6").toDouble();
			bool checkBox_6 = jsonObj.value("checkBox_6").toBool();
			bool checkBox_7 = jsonObj.value("checkBox_7").toBool();
			bool checkBox_8 = jsonObj.value("checkBox_8").toBool();
			float doubleSpinBox_7 = jsonObj.value("doubleSpinBox_7").toDouble();
			float doubleSpinBox_8 = jsonObj.value("doubleSpinBox_8").toDouble();
			bool checkBox_11 = jsonObj.value("checkBox_11").toBool();
			QString comboBox_4 = jsonObj.value("comboBox_4").toString();
			bool checkBox_12 = jsonObj.value("checkBox_12").toBool();
			bool checkBox_13 = jsonObj.value("checkBox_13").toBool();
			bool checkBox_14 = jsonObj.value("checkBox_14").toBool();
			float doubleSpinBox_10 = jsonObj.value("doubleSpinBox_10").toDouble();
			float doubleSpinBox_11 = jsonObj.value("doubleSpinBox_11").toDouble();
			float doubleSpinBox_12 = jsonObj.value("doubleSpinBox_12").toDouble();
			bool checkBox_15 = jsonObj.value("checkBox_15").toBool();
			bool checkBox_16 = jsonObj.value("checkBox_16").toBool();
			bool checkBox_18 = jsonObj.value("checkBox_18").toBool();
			bool checkBox_21 = jsonObj.value("checkBox_21").toBool();
			bool checkBox_22 = jsonObj.value("checkBox_22").toBool();
			bool checkBox_24 = jsonObj.value("checkBox_24").toBool();
			bool checkBox_25 = jsonObj.value("checkBox_25").toBool();
			bool checkBox_26 = jsonObj.value("checkBox_26").toBool();
			bool checkBox_28 = jsonObj.value("checkBox_28").toBool();
			bool checkBox_30 = jsonObj.value("checkBox_30").toBool();
			bool checkBox_31 = jsonObj.value("checkBox_31").toBool();
			bool checkBox_32 = jsonObj.value("checkBox_32").toBool();
			bool checkBox_33 = jsonObj.value("checkBox_33").toBool();
			bool checkBox_34 = jsonObj.value("checkBox_34").toBool();
			bool checkBox_35 = jsonObj.value("checkBox_35").toBool();
			bool checkBox_36 = jsonObj.value("checkBox_36").toBool();
			bool checkBox_37 = jsonObj.value("checkBox_37").toBool();
			bool checkBox_38 = jsonObj.value("checkBox_38").toBool();
			bool checkBox_39 = jsonObj.value("checkBox_39").toBool();
			bool checkBox_40 = jsonObj.value("checkBox_40").toBool();
			bool checkBox_41 = jsonObj.value("checkBox_41").toBool();
			bool checkBox_42 = jsonObj.value("checkBox_42").toBool();
			bool checkBox_43 = jsonObj.value("checkBox_43").toBool();
			bool checkBox_44 = jsonObj.value("checkBox_44").toBool();
			bool checkBox_45 = jsonObj.value("checkBox_45").toBool();
			bool checkBox_46 = jsonObj.value("checkBox_46").toBool();
			bool checkBox_47 = jsonObj.value("checkBox_47").toBool();
			bool checkBox_48 = jsonObj.value("checkBox_48").toBool();
			bool checkBox_49 = jsonObj.value("checkBox_49").toBool();
			bool checkBox_50 = jsonObj.value("checkBox_50").toBool();
			bool checkBox_51 = jsonObj.value("checkBox_51").toBool();
			bool checkBox_52 = jsonObj.value("checkBox_52").toBool();
			bool checkBox_53 = jsonObj.value("checkBox_53").toBool();
			bool checkBox_54 = jsonObj.value("checkBox_54").toBool();
			bool checkBox_56 = jsonObj.value("checkBox_56").toBool();
			QString comboBox_10 = jsonObj.value("comboBox_10").toString();
			QString comboBox = jsonObj.value("comboBox").toString();
			QString comboBox_11 = jsonObj.value("comboBox_11").toString();
			QString comboBox_12 = jsonObj.value("comboBox_12").toString();
			QString comboBox_13 = jsonObj.value("comboBox_13").toString();
			QString comboBox_14 = jsonObj.value("comboBox_14").toString();
			QString comboBox_15 = jsonObj.value("comboBox_15").toString();
			QString comboBox_16 = jsonObj.value("comboBox_16").toString();
			QString comboBox_17 = jsonObj.value("comboBox_17").toString();
			QString comboBox_18 = jsonObj.value("comboBox_18").toString();
			QString comboBox_19 = jsonObj.value("comboBox_19").toString();
			QString comboBox_2 = jsonObj.value("comboBox_2").toString();
			QString comboBox_20 = jsonObj.value("comboBox_20").toString();
			QString comboBox_21 = jsonObj.value("comboBox_21").toString();
			QString comboBox_22 = jsonObj.value("comboBox_22").toString();
			QString comboBox_23 = jsonObj.value("comboBox_23").toString();
			QString comboBox_24 = jsonObj.value("comboBox_24").toString();
			QString comboBox_25 = jsonObj.value("comboBox_25").toString();
			QString comboBox_26 = jsonObj.value("comboBox_26").toString();
			QString comboBox_27 = jsonObj.value("comboBox_27").toString();
			QString comboBox_3 = jsonObj.value("comboBox_3").toString();
			QString comboBox_5 = jsonObj.value("comboBox_5").toString();
			QString comboBox_6 = jsonObj.value("comboBox_6").toString();
			QString comboBox_7 = jsonObj.value("comboBox_7").toString();
			QString comboBox_8 = jsonObj.value("comboBox_8").toString();
			QString comboBox_9 = jsonObj.value("comboBox_9").toString();
			float doubleSpinBox_14 = jsonObj.value("doubleSpinBox_14").toDouble();
			float doubleSpinBox_15 = jsonObj.value("doubleSpinBox_15").toDouble();
			float doubleSpinBox_16 = jsonObj.value("doubleSpinBox_16").toDouble();
			float doubleSpinBox_18 = jsonObj.value("doubleSpinBox_18").toDouble();
			float doubleSpinBox_20 = jsonObj.value("doubleSpinBox_20").toDouble();
			float doubleSpinBox_21 = jsonObj.value("doubleSpinBox_21").toDouble();
			float doubleSpinBox_31 = jsonObj.value("doubleSpinBox_31").toDouble();
			float doubleSpinBox_32 = jsonObj.value("doubleSpinBox_32").toDouble();
			float doubleSpinBox_33 = jsonObj.value("doubleSpinBox_33").toDouble();
			float doubleSpinBox_34 = jsonObj.value("doubleSpinBox_34").toDouble();
			float doubleSpinBox_35 = jsonObj.value("doubleSpinBox_35").toDouble();
			float doubleSpinBox_36 = jsonObj.value("doubleSpinBox_36").toDouble();
			float doubleSpinBox_37 = jsonObj.value("doubleSpinBox_37").toDouble();
			float doubleSpinBox_38 = jsonObj.value("doubleSpinBox_38").toDouble();
			float doubleSpinBox_39 = jsonObj.value("doubleSpinBox_39").toDouble();
			float doubleSpinBox_40 = jsonObj.value("doubleSpinBox_40").toDouble();
			float doubleSpinBox_41 = jsonObj.value("doubleSpinBox_41").toDouble();
			float doubleSpinBox_42 = jsonObj.value("doubleSpinBox_42").toDouble();
			float doubleSpinBox_43 = jsonObj.value("doubleSpinBox_43").toDouble();
			float doubleSpinBox_44 = jsonObj.value("doubleSpinBox_44").toDouble();
			float doubleSpinBox_45 = jsonObj.value("doubleSpinBox_45").toDouble();
			float doubleSpinBox_46 = jsonObj.value("doubleSpinBox_46").toDouble();
			float doubleSpinBox_47 = jsonObj.value("doubleSpinBox_47").toDouble();
			float doubleSpinBox_48 = jsonObj.value("doubleSpinBox_48").toDouble();
			float doubleSpinBox_49 = jsonObj.value("doubleSpinBox_49").toDouble();
			float doubleSpinBox_50 = jsonObj.value("doubleSpinBox_50").toDouble();
			float doubleSpinBox_51 = jsonObj.value("doubleSpinBox_51").toDouble();
			float doubleSpinBox_52 = jsonObj.value("doubleSpinBox_52").toDouble();
			float doubleSpinBox_53 = jsonObj.value("doubleSpinBox_53").toDouble();
			float doubleSpinBox_54 = jsonObj.value("doubleSpinBox_54").toDouble();
			float doubleSpinBox_55 = jsonObj.value("doubleSpinBox_55").toDouble();
			float doubleSpinBox_56 = jsonObj.value("doubleSpinBox_56").toDouble();
			float doubleSpinBox_57 = jsonObj.value("doubleSpinBox_57").toDouble();
			float doubleSpinBox_58 = jsonObj.value("doubleSpinBox_58").toDouble();
			float doubleSpinBox_59 = jsonObj.value("doubleSpinBox_59").toDouble();
			float doubleSpinBox_60 = jsonObj.value("doubleSpinBox_60").toDouble();
			float doubleSpinBox_61 = jsonObj.value("doubleSpinBox_61").toDouble();
			float doubleSpinBox_62 = jsonObj.value("doubleSpinBox_62").toDouble();
			float doubleSpinBox_63 = jsonObj.value("doubleSpinBox_63").toDouble();
			float doubleSpinBox_64 = jsonObj.value("doubleSpinBox_64").toDouble();
			float doubleSpinBox_65 = jsonObj.value("doubleSpinBox_65").toDouble();
			float doubleSpinBox_66 = jsonObj.value("doubleSpinBox_66").toDouble();
			float doubleSpinBox_67 = jsonObj.value("doubleSpinBox_67").toDouble();
			float doubleSpinBox_68 = jsonObj.value("doubleSpinBox_68").toDouble();
			float doubleSpinBox_69 = jsonObj.value("doubleSpinBox_69").toDouble();
			float doubleSpinBox_70 = jsonObj.value("doubleSpinBox_70").toDouble();
			float doubleSpinBox_71 = jsonObj.value("doubleSpinBox_71").toDouble();
			float doubleSpinBox_72 = jsonObj.value("doubleSpinBox_72").toDouble();
			float doubleSpinBox_73 = jsonObj.value("doubleSpinBox_73").toDouble();
			float doubleSpinBox_74 = jsonObj.value("doubleSpinBox_74").toDouble();
			float doubleSpinBox_75 = jsonObj.value("doubleSpinBox_75").toDouble();
			float doubleSpinBox_76 = jsonObj.value("doubleSpinBox_76").toDouble();
			float doubleSpinBox_77 = jsonObj.value("doubleSpinBox_77").toDouble();
			float doubleSpinBox_78 = jsonObj.value("doubleSpinBox_78").toDouble();

			QString lineEdit_2 = jsonObj.value("lineEdit_2").toString();
			BallsMerge::sanjiao1Flag = jsonObj.value("sanjiao1Flag").toBool();
			BallsMerge::sanjiao2Flag = jsonObj.value("sanjiao2Flag").toBool();
			BallsMerge::sanjiao3Flag = jsonObj.value("sanjiao3Flag").toBool();
			BallsMerge::chongqiuFlag = jsonObj.value("chongqiuFlag").toBool();
			BallsMerge::sifenFlag = jsonObj.value("sifenFlag").toBool();
			BallsMerge::zhongfenFlag = jsonObj.value("zhongfenFlag").toBool();
			BallsMerge::xuanzhuan1Flag = jsonObj.value("xuanzhuan1Flag").toBool();
			BallsMerge::banxuan1Flag = jsonObj.value("banxuan1Flag").toBool();
			BallsMerge::xuanzhuan2Flag = jsonObj.value("xuanzhuan2Flag").toBool();
			BallsMerge::banxuan2Flag = jsonObj.value("banxuan2Flag").toBool();
			BallsMerge::sheshouFlag = jsonObj.value("sheshouFlag").toBool();
			BallsMerge::houyangFlag = jsonObj.value("houyangFlag").toBool();
			
			BallsMerge::zhongfenMacroFlag = jsonObj.value("zhongfenMacroFlag").toBool();
			BallsMerge::sifenMacroFlag = jsonObj.value("sifenMacroFlag").toBool();
			BallsMerge::xuanzhuanMacroFlag = jsonObj.value("xuanzhuanMacroFlag").toBool();
			BallsMerge::bafenMacroFlag = jsonObj.value("bafenMacroFlag").toBool();

			BallsMerge::sj1yc1 = jsonObj.value("sj1yc1").toInt();
			BallsMerge::sj1yc2 = jsonObj.value("sj1yc2").toInt();
			BallsMerge::sj1yc3 = jsonObj.value("sj1yc3").toInt();
			BallsMerge::sj1yc4 = jsonObj.value("sj1yc4").toInt();
			BallsMerge::sj1yc5 = jsonObj.value("sj1yc5").toInt();
			BallsMerge::sj1yc6 = jsonObj.value("sj1yc6").toInt();
			BallsMerge::sj1cs = jsonObj.value("sj1cs").toInt();
			BallsMerge::sj1fsjg = jsonObj.value("sj1fsjg").toInt();
			
			BallsMerge::sj2yc1 = jsonObj.value("sj2yc1").toInt();
			BallsMerge::sj2yc2 = jsonObj.value("sj2yc2").toInt();
			BallsMerge::sj2yc3 = jsonObj.value("sj2yc3").toInt();
			BallsMerge::sj2yc4 = jsonObj.value("sj2yc4").toInt();
			BallsMerge::sj2yc5 = jsonObj.value("sj2yc5").toInt();
			BallsMerge::sj2yc6 = jsonObj.value("sj2yc6").toInt();
			BallsMerge::sj2cs = jsonObj.value("sj2cs").toInt();
			BallsMerge::sj2fsjg = jsonObj.value("sj2fsjg").toInt();
			
			BallsMerge::sj3yc1 = jsonObj.value("sj3yc1").toInt();
			BallsMerge::sj3yc2 = jsonObj.value("sj3yc2").toInt();
			BallsMerge::sj3yc3 = jsonObj.value("sj3yc3").toInt();
			BallsMerge::sj3yc4 = jsonObj.value("sj3yc4").toInt();
			BallsMerge::sj3yc5 = jsonObj.value("sj3yc5").toInt();
			BallsMerge::sj3yc6 = jsonObj.value("sj3yc6").toInt();
			BallsMerge::sj3cs = jsonObj.value("sj3cs").toInt();
			BallsMerge::sj3fsjg = jsonObj.value("sj3fsjg").toInt();
			
			BallsMerge::cqyc1 = jsonObj.value("cqyc1").toInt();
			BallsMerge::cqyc2 = jsonObj.value("cqyc2").toInt();
			BallsMerge::cqcs = jsonObj.value("cqcs").toInt();
			BallsMerge::cqfsjg = jsonObj.value("cqfsjg").toInt();
			
			BallsMerge::sfyc1 = jsonObj.value("sfyc1").toInt();
			BallsMerge::sfyc2 = jsonObj.value("sfyc2").toInt();
			BallsMerge::sfyc3 = jsonObj.value("sfyc3").toInt();
			BallsMerge::sfyc4 = jsonObj.value("sfyc4").toInt();
			BallsMerge::sfyc5 = jsonObj.value("sfyc5").toInt();
			BallsMerge::sfcs = jsonObj.value("sfcs").toInt();
			BallsMerge::sffsjg = jsonObj.value("sffsjg").toInt();
			
			BallsMerge::zfyc1 = jsonObj.value("zfyc1").toInt();
			BallsMerge::zfyc2 = jsonObj.value("zfyc2").toInt();
			BallsMerge::zfyc3 = jsonObj.value("zfyc3").toInt();
			BallsMerge::zfyc4 = jsonObj.value("zfyc4").toInt();
			BallsMerge::zfyc5 = jsonObj.value("zfyc5").toInt();
			BallsMerge::zfcs = jsonObj.value("zfcs").toInt();
			BallsMerge::zffsjg = jsonObj.value("zffsjg").toInt();
			
			BallsMerge::hyyc1 = jsonObj.value("hyyc1").toInt();
			BallsMerge::hyyc2 = jsonObj.value("hyyc2").toInt();
			BallsMerge::hyyc3 = jsonObj.value("hyyc3").toInt();
			BallsMerge::hyyc4 = jsonObj.value("hyyc4").toInt();
			BallsMerge::hyyc5 = jsonObj.value("hyyc5").toInt();
			BallsMerge::hycs = jsonObj.value("hycs").toInt();
			BallsMerge::hyfsjg = jsonObj.value("hyfsjg").toInt();

			BallsMerge::xz1yc1 = jsonObj.value("xz1yc1").toInt();
			BallsMerge::xz1yc2 = jsonObj.value("xz1yc2").toInt();
			BallsMerge::xz1yc3 = jsonObj.value("xz1yc3").toInt();
			BallsMerge::xz1yc4 = jsonObj.value("xz1yc4").toInt();
			BallsMerge::xz1yc5 = jsonObj.value("xz1yc5").toInt();
			BallsMerge::xz1yc6 = jsonObj.value("xz1yc6").toInt();
			BallsMerge::xz1yc7 = jsonObj.value("xz1yc7").toInt();
			BallsMerge::xz1yc8 = jsonObj.value("xz1yc8").toInt();
			BallsMerge::xz1yc9 = jsonObj.value("xz1yc9").toInt();
			BallsMerge::xz1cs = jsonObj.value("xz1cs").toInt();
			BallsMerge::xz1fsjg = jsonObj.value("xz1fsjg").toInt();

			BallsMerge::bx1yc1 = jsonObj.value("bx1yc1").toInt();
			BallsMerge::bx1yc2 = jsonObj.value("bx1yc2").toInt();
			BallsMerge::bx1yc3 = jsonObj.value("bx1yc3").toInt();
			BallsMerge::bx1yc4 = jsonObj.value("bx1yc4").toInt();
			BallsMerge::bx1yc5 = jsonObj.value("bx1yc5").toInt();
			BallsMerge::bx1yc6 = jsonObj.value("bx1yc6").toInt();
			BallsMerge::bx1yc7 = jsonObj.value("bx1yc7").toInt();
			BallsMerge::bx1yc8 = jsonObj.value("bx1yc8").toInt();
			BallsMerge::bx1yc9 = jsonObj.value("bx1yc9").toInt();
			BallsMerge::bx1cs = jsonObj.value("bx1cs").toInt();
			BallsMerge::bx1fsjg = jsonObj.value("bx1fsjg").toInt();

			BallsMerge::ssyc1 = jsonObj.value("ssyc1").toInt();
			BallsMerge::ssyc2 = jsonObj.value("ssyc2").toInt();
			BallsMerge::ssyc3 = jsonObj.value("ssyc3").toInt();
			BallsMerge::ssyc4 = jsonObj.value("ssyc4").toInt();
			BallsMerge::ssyc5 = jsonObj.value("ssyc5").toInt();
			BallsMerge::ssyc6 = jsonObj.value("ssyc6").toInt();
			BallsMerge::ssyc7 = jsonObj.value("ssyc7").toInt();
			BallsMerge::ssyc8 = jsonObj.value("ssyc8").toInt();
			BallsMerge::ssyc9 = jsonObj.value("ssyc9").toInt();
			BallsMerge::sscs = jsonObj.value("sscs").toInt();
			BallsMerge::ssfsjg = jsonObj.value("ssfsjg").toInt();	

			BallsMerge::sj1hqfd = doubleSpinBox_14;
			BallsMerge::sj1zyfd = doubleSpinBox_15;
			BallsMerge::sj1jd = comboBox_6.toInt();
			BallsMerge::sj1tqFlag = checkBox_15;
			BallsMerge::autosanjiao_1_Flag = checkBox_16;
			BallsMerge::sanjiaojian1 = virtualkey(comboBox_5);

			BallsMerge::sj2hqfd = doubleSpinBox_18;
			BallsMerge::sj2zyfd = doubleSpinBox_16;
			BallsMerge::sj2jd = comboBox_8.toInt();
			BallsMerge::sj2tqFlag = checkBox_21;
			BallsMerge::autosanjiao_2_Flag = checkBox_24;
			BallsMerge::sanjiaojian2 = virtualkey(comboBox_7);

			BallsMerge::sj3hqfd = doubleSpinBox_20;
			BallsMerge::sj3zyfd = doubleSpinBox_21;
			BallsMerge::sj3jd = comboBox_10.toInt();
			BallsMerge::sj3tqFlag = checkBox_26;
			BallsMerge::autosanjiao_3_Flag = checkBox_25;
			BallsMerge::sanjiaojian3 = virtualkey(comboBox_9);

			BallsMerge::chongqiujian = virtualkey(comboBox_11);
			BallsMerge::chongqiutqFlag = checkBox_30;
			BallsMerge::chongqiujiantouFlag = checkBox_32;
			BallsMerge::sifenjian = virtualkey(comboBox_12);
			BallsMerge::sifentqFlag = checkBox_35;
			BallsMerge::autosifenFlag = checkBox_33;
			BallsMerge::sfjcfd = doubleSpinBox_32;
		
			BallsMerge::zhongfenjian = virtualkey(comboBox_13);
			BallsMerge::zhongfentqFlag = checkBox_38;
			BallsMerge::autozhongfenFlag = checkBox_36;
			BallsMerge::zfjcfd = doubleSpinBox_31;

			BallsMerge::houyangjian = virtualkey(comboBox_19);
			BallsMerge::houyangtqFlag = checkBox_56;
			BallsMerge::autohouyangFlag = checkBox_54;
			BallsMerge::hyjcfd1 = doubleSpinBox_73;
			BallsMerge::hyjcfd2 = doubleSpinBox_74;

			BallsMerge::xuanzhuanjian1 = virtualkey(comboBox_14);
			BallsMerge::xuanzhuan1tqFlag = checkBox_41;
			BallsMerge::xuanzhuan1jd1 = doubleSpinBox_33;
			BallsMerge::xuanzhuan1jd2 = doubleSpinBox_39;
			BallsMerge::xuanzhuan1jd3 = doubleSpinBox_34;
			BallsMerge::xuanzhuan1jd4 = doubleSpinBox_40;
			BallsMerge::xuanzhuan1fd1 = doubleSpinBox_35;
			BallsMerge::xuanzhuan1fd2 = doubleSpinBox_37;
			BallsMerge::xuanzhuan1fd3 = doubleSpinBox_36;
			BallsMerge::xuanzhuan1fd4 = doubleSpinBox_38;

			BallsMerge::banxuanjian1 = virtualkey(comboBox_15);
			BallsMerge::banxuan1tqFlag = checkBox_44;
			BallsMerge::banxuan1jd1 = doubleSpinBox_41;
			BallsMerge::banxuan1jd2 = doubleSpinBox_42;
			BallsMerge::banxuan1jd3 = doubleSpinBox_44;
			BallsMerge::banxuan1jd4 = doubleSpinBox_46;
			BallsMerge::banxuan1fd1 = doubleSpinBox_43;
			BallsMerge::banxuan1fd2 = doubleSpinBox_45;
			BallsMerge::banxuan1fd3 = doubleSpinBox_47;
			BallsMerge::banxuan1fd4 = doubleSpinBox_48;

			BallsMerge::sheshoujian = virtualkey(comboBox_18);
			BallsMerge::sheshoutqFlag = checkBox_53;
			BallsMerge::sheshoujd1 = doubleSpinBox_65;
			BallsMerge::sheshoujd2 = doubleSpinBox_66;
			BallsMerge::sheshoujd3 = doubleSpinBox_68;
			BallsMerge::sheshoujd4 = doubleSpinBox_70;
			BallsMerge::sheshoufd1 = doubleSpinBox_67;
			BallsMerge::sheshoufd2 = doubleSpinBox_69;
			BallsMerge::sheshoufd3 = doubleSpinBox_71;
			BallsMerge::sheshoufd4 = doubleSpinBox_72;

			BallsMerge::tuqiuFlag = checkBox;
			BallsMerge::yaoganjiexianFlag = checkBox_7;
			BallsMerge::fsjiexianFlag = checkBox_8;
			BallsMerge::yaoganhuitanFlag = checkBox_5;
			BallsMerge::gunlunshiyeFlag = checkBox_3;
			BallsMerge::juneiqupiFlag = checkBox_11;
			BallsMerge::qupijian = virtualkey(comboBox_4);
			BallsMerge::yaoganyouhuaFlag = checkBox_6;
			BallsMerge::step = doubleSpinBox_5;

			BallsMerge::tuqiujian = virtualkey(comboBox_2);
			BallsMerge::fenshenjian = virtualkey(comboBox_3);

			ui.groupBox_19->setChecked(BallsMerge::zhongfenMacroFlag);
			ui.groupBox_20->setChecked(BallsMerge::sifenMacroFlag);
			ui.groupBox_21->setChecked(BallsMerge::xuanzhuanMacroFlag);
			ui.groupBox_22->setChecked(BallsMerge::bafenMacroFlag);

			ui.tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc1)));
			ui.tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc2)));
			ui.tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc3)));
			ui.tableWidget->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc4)));
			ui.tableWidget->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc5)));
			ui.tableWidget->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1yc6)));
			ui.tableWidget->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1cs)));
			ui.tableWidget->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::sj1fsjg)));
			
			ui.tableWidget_2->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc1)));
			ui.tableWidget_2->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc2)));
			ui.tableWidget_2->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc3)));
			ui.tableWidget_2->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc4)));
			ui.tableWidget_2->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc5)));
			ui.tableWidget_2->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2yc6)));
			ui.tableWidget_2->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2cs)));
			ui.tableWidget_2->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::sj2fsjg)));
			ui.tableWidget_3->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc1)));
			ui.tableWidget_3->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc2)));
			ui.tableWidget_3->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc3)));
			ui.tableWidget_3->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc4)));
			ui.tableWidget_3->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc5)));
			ui.tableWidget_3->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3yc6)));
			ui.tableWidget_3->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3cs)));
			ui.tableWidget_3->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::sj3fsjg)));
			ui.tableWidget_4->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::cqyc1)));
			ui.tableWidget_4->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::cqyc2)));
			ui.tableWidget_4->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::cqcs)));
			ui.tableWidget_4->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::cqfsjg)));
			ui.tableWidget_5->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc1)));
			ui.tableWidget_5->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc2)));
			ui.tableWidget_5->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc3)));
			ui.tableWidget_5->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc4)));
			ui.tableWidget_5->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::sfyc5)));
			ui.tableWidget_5->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::sfcs)));
			ui.tableWidget_5->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::sffsjg)));
			ui.tableWidget_6->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc1)));
			ui.tableWidget_6->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc2)));
			ui.tableWidget_6->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc3)));
			ui.tableWidget_6->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc4)));
			ui.tableWidget_6->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::zfyc5)));
			ui.tableWidget_6->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::zfcs)));
			ui.tableWidget_6->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::zffsjg)));
			ui.tableWidget_12->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc1)));
			ui.tableWidget_12->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc2)));
			ui.tableWidget_12->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc3)));
			ui.tableWidget_12->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc4)));
			ui.tableWidget_12->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::hyyc5)));
			ui.tableWidget_12->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::hycs)));
			ui.tableWidget_12->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::hyfsjg)));
			ui.tableWidget_7->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc1)));
			ui.tableWidget_7->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc2)));
			ui.tableWidget_7->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc3)));
			ui.tableWidget_7->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc4)));
			ui.tableWidget_7->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc5)));
			ui.tableWidget_7->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc6)));
			ui.tableWidget_7->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc7)));
			ui.tableWidget_7->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc8)));
			ui.tableWidget_7->setItem(8, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1yc9)));
			ui.tableWidget_7->setItem(9, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1cs)));
			ui.tableWidget_7->setItem(10, 1, new QTableWidgetItem(QString::number(BallsMerge::xz1fsjg)));
			ui.tableWidget_8->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc1)));
			ui.tableWidget_8->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc2)));
			ui.tableWidget_8->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc3)));
			ui.tableWidget_8->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc4)));
			ui.tableWidget_8->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc5)));
			ui.tableWidget_8->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc6)));
			ui.tableWidget_8->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc7)));
			ui.tableWidget_8->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc8)));
			ui.tableWidget_8->setItem(8, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1yc9)));
			ui.tableWidget_8->setItem(9, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1cs)));
			ui.tableWidget_8->setItem(10, 1, new QTableWidgetItem(QString::number(BallsMerge::bx1fsjg)));
			ui.tableWidget_11->setItem(0, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc1)));
			ui.tableWidget_11->setItem(1, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc2)));
			ui.tableWidget_11->setItem(2, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc3)));
			ui.tableWidget_11->setItem(3, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc4)));
			ui.tableWidget_11->setItem(4, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc5)));
			ui.tableWidget_11->setItem(5, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc6)));
			ui.tableWidget_11->setItem(6, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc7)));
			ui.tableWidget_11->setItem(7, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc8)));
			ui.tableWidget_11->setItem(8, 1, new QTableWidgetItem(QString::number(BallsMerge::ssyc9)));
			ui.tableWidget_11->setItem(9, 1, new QTableWidgetItem(QString::number(BallsMerge::sscs)));
			ui.tableWidget_11->setItem(10, 1, new QTableWidgetItem(QString::number(BallsMerge::ssfsjg)));
			ui.checkBox->setChecked(checkBox);
			ui.doubleSpinBox->setValue(doubleSpinBox);
			ui.doubleSpinBox_2->setValue(doubleSpinBox_2);
			ui.checkBox_3->setChecked(checkBox_3);
			ui.checkBox_4->setChecked(checkBox_4);
			ui.doubleSpinBox_3->setValue(doubleSpinBox_3);
			ui.doubleSpinBox_4->setValue(doubleSpinBox_4);
			ui.doubleSpinBox_5->setValue(doubleSpinBox_5);
			ui.checkBox_5->setChecked(checkBox_5);
			ui.doubleSpinBox_6->setValue(doubleSpinBox_6);
			ui.checkBox_6->setChecked(checkBox_6);
			ui.checkBox_7->setChecked(checkBox_7);
			ui.checkBox_8->setChecked(checkBox_8);
			ui.doubleSpinBox_7->setValue(doubleSpinBox_7);
			ui.doubleSpinBox_8->setValue(doubleSpinBox_8);
			ui.checkBox_11->setChecked(checkBox_11);
			ui.comboBox->setCurrentText(comboBox);
			ui.lineEdit_2->setText(lineEdit_2);
			ui.comboBox->setCurrentText(comboBox);
			ui.comboBox_2->setCurrentText(comboBox_2);
			ui.comboBox_3->setCurrentText(comboBox_3);
			ui.checkBox_15->setChecked(checkBox_15);
			ui.checkBox_16->setChecked(checkBox_16);
			ui.checkBox_21->setChecked(checkBox_21);
			ui.checkBox_24->setChecked(checkBox_24);
			ui.checkBox_25->setChecked(checkBox_25);
			ui.checkBox_26->setChecked(checkBox_26);
			ui.checkBox_30->setChecked(checkBox_30);
			ui.checkBox_31->setChecked(checkBox_31);
			ui.checkBox_32->setChecked(checkBox_32);
			ui.checkBox_33->setChecked(checkBox_33);
			ui.checkBox_35->setChecked(checkBox_35);
			ui.checkBox_36->setChecked(checkBox_36);
			ui.checkBox_38->setChecked(checkBox_38);
			ui.checkBox_39->setChecked(checkBox_39);
			ui.checkBox_41->setChecked(checkBox_41);
			ui.checkBox_42->setChecked(checkBox_42);
			ui.checkBox_44->setChecked(checkBox_44);
			ui.checkBox_51->setChecked(checkBox_51);
			ui.checkBox_53->setChecked(checkBox_53);
			ui.checkBox_54->setChecked(checkBox_54);
			ui.checkBox_56->setChecked(checkBox_56);
			ui.comboBox_4->setCurrentText(comboBox_4);
			ui.comboBox_5->setCurrentText(comboBox_5);
			ui.comboBox_6->setCurrentText(comboBox_6);
			ui.comboBox_7->setCurrentText(comboBox_7);
			ui.comboBox_8->setCurrentText(comboBox_8);
			ui.comboBox_9->setCurrentText(comboBox_9);
			ui.comboBox_10->setCurrentText(comboBox_10);
			ui.comboBox_11->setCurrentText(comboBox_11);
			ui.comboBox_12->setCurrentText(comboBox_12);
			ui.comboBox_13->setCurrentText(comboBox_13);
			ui.comboBox_14->setCurrentText(comboBox_14);
			ui.comboBox_15->setCurrentText(comboBox_15);
			ui.comboBox_18->setCurrentText(comboBox_18);
			ui.comboBox_19->setCurrentText(comboBox_19);
			ui.comboBox_20->setCurrentText(comboBox_20);
			ui.comboBox_21->setCurrentText(comboBox_21);
			ui.comboBox_22->setCurrentText(comboBox_22);
			ui.comboBox_23->setCurrentText(comboBox_23);
			ui.comboBox_24->setCurrentText(comboBox_24);
			ui.comboBox_25->setCurrentText(comboBox_25);
			ui.doubleSpinBox_14->setValue(doubleSpinBox_14);
			ui.doubleSpinBox_15->setValue(doubleSpinBox_15);
			ui.doubleSpinBox_16->setValue(doubleSpinBox_16);
			ui.doubleSpinBox_18->setValue(doubleSpinBox_18);
			ui.doubleSpinBox_20->setValue(doubleSpinBox_20);
			ui.doubleSpinBox_21->setValue(doubleSpinBox_21);
			ui.doubleSpinBox_31->setValue(doubleSpinBox_31);
			ui.doubleSpinBox_32->setValue(doubleSpinBox_32);
			ui.doubleSpinBox_33->setValue(doubleSpinBox_33);
			ui.doubleSpinBox_34->setValue(doubleSpinBox_34);
			ui.doubleSpinBox_35->setValue(doubleSpinBox_35);
			ui.doubleSpinBox_36->setValue(doubleSpinBox_36);
			ui.doubleSpinBox_37->setValue(doubleSpinBox_37);
			ui.doubleSpinBox_38->setValue(doubleSpinBox_38);
			ui.doubleSpinBox_39->setValue(doubleSpinBox_39);
			ui.doubleSpinBox_40->setValue(doubleSpinBox_40);
			ui.doubleSpinBox_41->setValue(doubleSpinBox_41);
			ui.doubleSpinBox_42->setValue(doubleSpinBox_42);
			ui.doubleSpinBox_43->setValue(doubleSpinBox_43);
			ui.doubleSpinBox_44->setValue(doubleSpinBox_44);
			ui.doubleSpinBox_45->setValue(doubleSpinBox_45);
			ui.doubleSpinBox_46->setValue(doubleSpinBox_46);
			ui.doubleSpinBox_47->setValue(doubleSpinBox_47);
			ui.doubleSpinBox_48->setValue(doubleSpinBox_48);
			ui.doubleSpinBox_65->setValue(doubleSpinBox_65);
			ui.doubleSpinBox_66->setValue(doubleSpinBox_66);
			ui.doubleSpinBox_67->setValue(doubleSpinBox_67);
			ui.doubleSpinBox_68->setValue(doubleSpinBox_68);
			ui.doubleSpinBox_69->setValue(doubleSpinBox_69);
			ui.doubleSpinBox_70->setValue(doubleSpinBox_70);
			ui.doubleSpinBox_71->setValue(doubleSpinBox_71);
			ui.doubleSpinBox_72->setValue(doubleSpinBox_72);
			ui.doubleSpinBox_73->setValue(doubleSpinBox_73);
			ui.doubleSpinBox_74->setValue(doubleSpinBox_74);
			ui.doubleSpinBox_75->setValue(doubleSpinBox_75);
			ui.doubleSpinBox_77->setValue(doubleSpinBox_77);
			ui.doubleSpinBox_78->setValue(doubleSpinBox_78);
			
			setCheckboxState(ui.treeWidget, "脚本-单方向", "一键三角1", jsonObj.value("sanjiao1Flag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-单方向", "一键三角2", jsonObj.value("sanjiao2Flag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-单方向", "一键三角3", jsonObj.value("sanjiao3Flag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-单方向", "冲球-直线", jsonObj.value("chongqiuFlag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-双方向", "侧合-四分", jsonObj.value("sifenFlag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-双方向", "侧合-中分", jsonObj.value("zhongfenFlag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-双方向", "旋转", jsonObj.value("xuanzhuan1Flag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-双方向", "半旋", jsonObj.value("banxuan1Flag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-双方向", "蛇手", jsonObj.value("sheshouFlag").toBool());
			setCheckboxState(ui.treeWidget, "脚本-双方向", "后仰", jsonObj.value("houyangFlag").toBool());
			file.close();
		}
	}
	else
	{
		QMessageBox::warning(this, "Error", "加载配置失败");
	}
}

void MainWindow::setCheckboxState(QTreeWidget* treeWidget, const QString& parentText,
	const QString& itemText, bool checked) {
	QList<QTreeWidgetItem*> parentItems = treeWidget->findItems(parentText, Qt::MatchExactly);
	if (parentItems.isEmpty()) return;

	QTreeWidgetItem* parent = parentItems.first();
	for (int i = 0; i < parent->childCount(); ++i) {
		QTreeWidgetItem* child = parent->child(i);
		if (child->text(0) == itemText) {
			child->setCheckState(0, checked ? Qt::Checked : Qt::Unchecked);
			break;
		}
	}
}

void MainWindow::treewidget_itemClicked()
{
	QTreeWidgetItem* currentItem = ui.treeWidget->currentItem();
	if (currentItem)
	{
		QString itemText = currentItem->text(0);
		if (itemText == "基础功能")
		{
			ui.stackedWidget->setCurrentIndex(0);
		}
		else if (itemText == "美化功能")
		{
			ui.stackedWidget->setCurrentIndex(1);
		}
		else if (itemText == "一键三角1")
		{
			ui.stackedWidget->setCurrentIndex(2);
		}
		else if (itemText == "一键三角2")
		{
			ui.stackedWidget->setCurrentIndex(3);
		}
		else if (itemText == "一键三角3")
		{
			ui.stackedWidget->setCurrentIndex(4);
		}
		else if (itemText == "冲球-直线")
		{
			ui.stackedWidget->setCurrentIndex(5);
		}
		else if (itemText == "侧合-四分")
		{
			ui.stackedWidget->setCurrentIndex(6);
		}
		else if (itemText == "侧合-中分")
		{
			ui.stackedWidget->setCurrentIndex(7);
		}
		else if (itemText == "旋转")
		{
			ui.stackedWidget->setCurrentIndex(8);
		}
		else if (itemText == "半旋")
		{
			ui.stackedWidget->setCurrentIndex(9);
		}
		else if (itemText == "蛇手")
		{
			ui.stackedWidget->setCurrentIndex(10);
		}
		else if (itemText == "后仰")
		{
			ui.stackedWidget->setCurrentIndex(11);
		}
		else if (itemText == "按键宏")
		{
			ui.stackedWidget->setCurrentIndex(12);
		}
		else if (itemText == "卡点功能")
		{
			ui.stackedWidget->setCurrentIndex(13);
		}
		else if (itemText == "追踪合球")
		{
			ui.stackedWidget->setCurrentIndex(14);
		}
		else if(itemText == "意见反馈")
		{
			ui.stackedWidget->setCurrentIndex(15);
		}
	}
}

int MainWindow::virtualkey(QString key)
{
	if (key == "A") return 0x41;
	if (key == "B") return 0x42;
	if (key == "C") return 0x43;
	if (key == "D") return 0x44;
	if (key == "E") return 0x45;
	if (key == "F") return 0x46;
	if (key == "G") return 0x47;
	if (key == "H") return 0x48;
	if (key == "I") return 0x49;
	if (key == "J") return 0x4A;
	if (key == "K") return 0x4B;
	if (key == "L") return 0x4C;
	if (key == "M") return 0x4D;
	if (key == "N") return 0x4E;
	if (key == "O") return 0x4F;
	if (key == "P") return 0x50;
	if (key == "Q") return 0x51;
	if (key == "R") return 0x52;
	if (key == "S") return 0x53;
	if (key == "T") return 0x54;
	if (key == "U") return 0x55;
	if (key == "V") return 0x56;
	if (key == "W") return 0x57;
	if (key == "X") return 0x58;
	if (key == "Y") return 0x59;
	if (key == "Z") return 0x5A;
	if (key == "0") return 0x30;
	if (key == "1") return 0x31;
	if (key == "2") return 0x32;
	if (key == "3") return 0x33;
	if (key == "4") return 0x34;
	if (key == "5") return 0x35;
	if (key == "6") return 0x36;
	if (key == "7") return 0x37;
	if (key == "8") return 0x38;
	if (key == "9") return 0x39;
	if (key == "~") return 0xC0;
	if (key == "空格") return 0x20;
	return 0;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		if(event->globalPosition().toPoint().y() < this->pos().y() + 36)
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

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		if(offset.isNull())
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

LRESULT CALLBACK MainWindow::keyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0 && wParam == WM_KEYDOWN)
	{
		PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
		//吐球
		if (key->vkCode == BallsMerge::tuqiujian && BallsMerge::tuqiuFlag)
		{
			while (wParam == WM_KEYDOWN)
			{
				ballsMerge->writetuqiu(Memory::hProcess, 0);
			}
		}

		//合球
		if (key->vkCode == BallsMerge::sanjiaojian1 && BallsMerge::sanjiao1Flag)
		{
			ballsMerge->sanjiao1(Memory::hProcess, Memory::hWnd);
		}
		else if (key->vkCode == BallsMerge::sanjiaojian2 && BallsMerge::sanjiao2Flag)
		{
			ballsMerge->sanjiao2(Memory::hProcess, Memory::hWnd);
		}
		else if (key->vkCode == BallsMerge::sanjiaojian3 && BallsMerge::sanjiao3Flag)
		{
			ballsMerge->sanjiao3(Memory::hProcess, Memory::hWnd);
		}
		else if (key->vkCode == BallsMerge::chongqiujian && BallsMerge::chongqiuFlag)
		{
			ballsMerge->chongqiu(Memory::hProcess);
		}
		else if (key->vkCode == BallsMerge::zhongfenjian && BallsMerge::zhongfenFlag)
		{
			ballsMerge->zhongfen(Memory::hProcess);
		}
		else if (key->vkCode == BallsMerge::sifenjian && BallsMerge::sifenFlag)
		{
			ballsMerge->sifen(Memory::hProcess);
		}
		else if (key->vkCode == BallsMerge::xuanzhuanjian1 && BallsMerge::xuanzhuan1Flag)
		{
			ballsMerge->xuanzhuan(Memory::hProcess);
		}
		else if (key->vkCode == BallsMerge::banxuanjian1 && BallsMerge::banxuan1Flag)
		{
			ballsMerge->banxuan(Memory::hProcess);
		}
		else if (key->vkCode == BallsMerge::houyangjian && BallsMerge::houyangFlag)
		{
			ballsMerge->houyang(Memory::hProcess, Memory::hWnd);
		}
		else if (key->vkCode == BallsMerge::sheshoujian && BallsMerge::sheshouFlag)
		{
			ballsMerge->sheshou(Memory::hProcess);
		}
		//宏
		if (key->vkCode == BallsMerge::sifenMacroKey && BallsMerge::sifenMacroFlag)
		{
			ballsMerge->sifenMacro();
		}
		else if (key->vkCode == BallsMerge::zhongfenMacroKey && BallsMerge::zhongfenMacroFlag)
		{
			ballsMerge->zhongfenMacro(Memory::hProcess);
		}
		else if (key->vkCode == BallsMerge::xuanzhuanMacroKey && BallsMerge::xuanzhuanMacroFlag)
		{
			ballsMerge->xuanzhuanMacro();
		}
		else if (key->vkCode == BallsMerge::bafenMacroKey && BallsMerge::bafenMacroFlag)
		{
			ballsMerge->bafenMacro();
		}
		//局内去皮
		if (key->vkCode == BallsMerge::qupijian)
		{
			qupiState = !qupiState;
			if(qupiState)
			{
				ballsMerge->writejuneiqupi(Memory::hProcess, 0);
			}
			else
			{
				ballsMerge->writejuneiqupi(Memory::hProcess, 1);
			}
		}
	}
	return CallNextHookEx(keyBoardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MainWindow::mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		if (wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL)
		{
			PMSLLHOOKSTRUCT pMouse = (PMSLLHOOKSTRUCT)lParam;
			HWND hWnd = WindowFromPoint(pMouse->pt);
			if (hWnd == Memory::hWnd && BallsMerge::gunlunshiyeFlag)
			{
				int scrollDelta = GET_WHEEL_DELTA_WPARAM(pMouse->mouseData);
				if (scrollDelta > 0)
				{
					BallsMerge::shiye += BallsMerge::step;
					float shiye = BallsMerge::shiye;
					float gunlunshiyeMax = Memory::gunlunshiyeMax;
					if (shiye > gunlunshiyeMax) 
					{
						BallsMerge::shiye = Memory::gunlunshiyeMax;
					}
					ballsMerge->writeshiye(Memory::hProcess, BallsMerge::shiye + BallsMerge::step);
				}
				else
				{
					BallsMerge::shiye -= BallsMerge::step;
					float shiye = BallsMerge::shiye;
					float gunlunshiyeMin = Memory::gunlunshiyeMin;
					if (shiye < gunlunshiyeMin) 
					{
						BallsMerge::shiye = Memory::gunlunshiyeMin;
					}
					ballsMerge->writeshiye(Memory::hProcess, BallsMerge::shiye - BallsMerge::step);
				}
				return 1;
			}
		}
	}
	
	return CallNextHookEx(keyBoardHook, nCode, wParam, lParam);
	
}

void MainWindow::installGlobalHook()
{
	keyBoardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyBoardProc, GetModuleHandle(NULL), 0);
	mouseHook = SetWindowsHookEx(WH_KEYBOARD_LL, mouseProc, GetModuleHandle(NULL), 0);
	if (!keyBoardHook)
	{
		QMessageBox::information(this, "提示", "全局钩子安装失败\n合球以及宏功能将无法使用\n请重启脚本和模拟器，以管理员身份运行");
	}
	if (!mouseHook)
	{
		QMessageBox::information(this, "提示", "视野钩子安装失败\n滚轮视野将无法使用\n请重启脚本和模拟器，以管理员身份运行");
	}
}

void MainWindow::uninstallGlobalHook()
{
	if (keyBoardHook != NULL)
	{
		BOOL unhook = UnhookWindowsHookEx(keyBoardHook);
	}
	if (mouseHook != NULL)
	{
		BOOL unhook = UnhookWindowsHookEx(mouseHook);
	}
}