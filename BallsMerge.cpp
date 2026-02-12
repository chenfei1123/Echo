#include <Windows.h>
#include "Memory.h"
#include "Simulator.h"
#include "BallsMerge.h"

#define PI 3.14159265358979323846

BallsMerge::BallsMerge()
{
	
}

BallsMerge::~BallsMerge()
{
	
}
// 发送按键扫描码
void BallsMerge::SendScanKey(BYTE vkCode) {

	int scanCode = MapVirtualKeyW(vkCode, 0);
	INPUT inputs[2] = { 0 };
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.dwFlags = KEYEVENTF_SCANCODE;
	inputs[0].ki.wScan = scanCode;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	inputs[1].ki.wScan = scanCode;

	SendInput(2, inputs, sizeof(INPUT));
}
// 按键按下
void BallsMerge::KeyDown(BYTE vkCode)
{
	int scanCode = MapVirtualKeyW(vkCode, 0);
	INPUT input = { 0 };

	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;  // 使用扫描码
	input.ki.wScan = scanCode;              // 设置扫描码

	SendInput(1, &input, sizeof(INPUT));
}
// 按键松开
void BallsMerge::KeyUp(BYTE vkCode)
{
	int scanCode = MapVirtualKeyW(vkCode, 0);
	INPUT input = { 0 };

	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;  // 使用扫描码+松开标志
	input.ki.wScan = scanCode;                         // 设置扫描码

	SendInput(1, &input, sizeof(INPUT));
}

// 合球
void BallsMerge::sanjiao1(HANDLE hProcess, HWND hWnd)
{
	if (autosanjiao_1_Flag)
	{
		centerPos = getTopRectCenterPoint(hWnd);
		GetCursorPos(&mousePos);

		float mu = sqrt((mousePos.x - centerPos.x) * (mousePos.x - centerPos.x) + (mousePos.y - centerPos.y) * (mousePos.y - centerPos.y));
		if (mu > 700) mu = 700;
		if (mu < 350) mu = 350;
		//归一后的单位向量
		float jtygX1 = (mousePos.x - centerPos.x) / mu;
		float jtygY1 = -(mousePos.y - centerPos.y) / mu;
		//落点1
		float point1X = jtygX1 * sj1zyfd * cos(sj1jd * PI / 360) - jtygY1 * sj1zyfd * sin(sj1jd * PI / 360);
		float point1Y = jtygX1 * sj1zyfd * sin(sj1jd * PI / 360) + jtygY1 * sj1zyfd * cos(sj1jd * PI / 360);
		//落点2
		float point2X = jtygX1 * sj1zyfd * cos(sj1jd * PI / 360) + jtygY1 * sj1zyfd * sin(sj1jd * PI / 360);
		float point2Y = -jtygX1 * sj1zyfd * sin(sj1jd * PI / 360) + jtygY1 * sj1zyfd * cos(sj1jd * PI / 360);
		//落点3

		float point3X = (mousePos.x - centerPos.x) / mu * mu / 700;
		float point3Y = -((mousePos.y - centerPos.y) / mu * mu / 700);

		Sleep(sj1yc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(sj1yc2);
		SendScanKey(fenshenjian);
		Sleep(sj1yc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(sj1yc4);
		SendScanKey(fenshenjian);
		Sleep(sj1yc5);
		if (sj1tqFlag)
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj1yc6);
			KeyDown(tuqiujian);
			for (int i = 0; i < sj1cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj1fsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj2yc6);
			for (int i = 0; i < sj1cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj1fsjg);
			}
		}
	}
	else
	{
		jtygX = readjtygX(hProcess);
		jtygY = readjtygY(hProcess);
		float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

		//归一后的单位向量
		float jtygX1 = jtygX / mu;
		float jtygY1 = jtygY / mu;
		//落点1
		float point1X = jtygX1 * sj1zyfd * cos(sj1jd * PI / 360) - jtygY1 * sj1zyfd * sin(sj1jd * PI / 360);
		float point1Y = jtygX1 *sj1zyfd * sin(sj1jd * PI / 360) + jtygY1 * sj1zyfd * cos(sj1jd * PI / 360);
		//落点2
		float point2X = jtygX1 * sj1zyfd * cos(sj1jd * PI / 360) + jtygY1 * sj1zyfd * sin(sj1jd * PI / 360);
		float point2Y = -jtygX1 * sj1zyfd * sin(sj1jd * PI / 360) + jtygY1 * sj1zyfd * cos(sj1jd * PI / 360);
		//落点3
		float point3X = jtygX1 * sj1hqfd;
		float point3Y = jtygY1 * sj1hqfd;

		Sleep(sj1yc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(sj1yc2);
		SendScanKey(fenshenjian);
		Sleep(sj1yc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(sj1yc4);
		SendScanKey(fenshenjian);
		Sleep(sj1yc5);
		if (sj1tqFlag)
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj1yc6);
			KeyDown(tuqiujian);
			for (int i = 0; i < sj1cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj1fsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj1yc6);
			for (int i = 0; i < sj1cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj1fsjg);
			}
		}
	}
}

void BallsMerge::sanjiao2(HANDLE hProcess,HWND hWnd)
{
	if (autosanjiao_2_Flag)
	{
		centerPos = getTopRectCenterPoint(hWnd);
		GetCursorPos(&mousePos);

		float mu = sqrt((mousePos.x - centerPos.x) * (mousePos.x - centerPos.x) + (mousePos.y - centerPos.y) * (mousePos.y - centerPos.y));
		if (mu > 700) mu = 700;
		if (mu < 350) mu = 350;
		//归一后的单位向量
		float jtygX1 = (mousePos.x - centerPos.x) / mu;
		float jtygY1 = -(mousePos.y - centerPos.y) / mu;
		//落点1
		float point1X = jtygX1 * sj2zyfd * cos(sj2jd * PI / 360) - jtygY1 * sj2zyfd * sin(sj2jd * PI / 360);
		float point1Y = jtygX1 * sj2zyfd * sin(sj2jd * PI / 360) + jtygY1 * sj2zyfd * cos(sj2jd * PI / 360);
		//落点2
		float point2X = jtygX1 * sj2zyfd * cos(sj2jd * PI / 360) + jtygY1 * sj2zyfd * sin(sj2jd * PI / 360);
		float point2Y = -jtygX1 * sj2zyfd * sin(sj2jd * PI / 360) + jtygY1 * sj2zyfd * cos(sj2jd * PI / 360);
		//落点3
		float point3X = (mousePos.x - centerPos.x) / mu * mu / 700;
		float point3Y = -((mousePos.y - centerPos.y) / mu * mu / 700);

		Sleep(sj2yc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(sj2yc2);
		SendScanKey(fenshenjian);
		Sleep(sj2yc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(sj2yc4);
		SendScanKey(fenshenjian);
		Sleep(sj2yc5);
		if (sj2tqFlag)
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj2yc6);
			KeyDown(tuqiujian);
			for (int i = 0; i < sj2cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj2fsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj2yc6);
			for (int i = 0; i < sj2cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj2fsjg);
			}
		}
	}
	else
	{
		jtygX = readjtygX(hProcess);
		jtygY = readjtygY(hProcess);
		float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

		//归一后的单位向量
		float jtygX1 = jtygX / mu;
		float jtygY1 = jtygY / mu;
		//落点1
		float point1X = jtygX1 * sj2zyfd * cos(sj2jd * PI / 360) - jtygY1 * sj2zyfd * sin(sj2jd * PI / 360);
		float point1Y = jtygX1 * sj2zyfd * sin(sj2jd * PI / 360) + jtygY1 * sj2zyfd * cos(sj2jd * PI / 360);
		//落点2
		float point2X = jtygX1 * sj2zyfd * cos(sj2jd * PI / 360) + jtygY1 * sj2zyfd * sin(sj2jd * PI / 360);
		float point2Y = -jtygX1 * sj2zyfd * sin(sj2jd * PI / 360) + jtygY1 * sj2zyfd * cos(sj2jd * PI / 360);
		//落点3
		float point3X = jtygX1 * sj2hqfd;
		float point3Y = jtygY1 * sj2hqfd;

		Sleep(sj2yc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(sj2yc2);
		SendScanKey(fenshenjian);
		Sleep(sj2yc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(sj2yc4);
		SendScanKey(fenshenjian);
		Sleep(sj2yc5);
		if (sj2tqFlag)
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj2yc6);
			KeyDown(tuqiujian);
			for (int i = 0; i < sj2cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj2fsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj2yc6);
			for (int i = 0; i < sj2cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj2fsjg);
			}
		}
	}
}

void BallsMerge::sanjiao3(HANDLE hProcess, HWND hWnd)
{
	if (autosanjiao_3_Flag)
	{
		centerPos = getTopRectCenterPoint(hWnd);
		GetCursorPos(&mousePos);

		float mu = sqrt((mousePos.x - centerPos.x) * (mousePos.x - centerPos.x) + (mousePos.y - centerPos.y) * (mousePos.y - centerPos.y));
		if (mu > 700) mu = 700;
		if (mu < 350) mu = 350;
		//归一后的单位向量
		float jtygX1 = (mousePos.x - centerPos.x) / mu;
		float jtygY1 = -(mousePos.y - centerPos.y) / mu;
		//落点1
		float point1X = jtygX1 * sj3zyfd * cos(sj3jd * PI / 360) - jtygY1 * sj3zyfd * sin(sj3jd * PI / 360);
		float point1Y = jtygX1 * sj3zyfd * sin(sj3jd * PI / 360) + jtygY1 * sj3zyfd * cos(sj3jd * PI / 360);
		//落点2
		float point2X = jtygX1 * sj3zyfd * cos(sj3jd * PI / 360) + jtygY1 * sj3zyfd * sin(sj3jd * PI / 360);
		float point2Y = -jtygX1 * sj3zyfd * sin(sj3jd * PI / 360) + jtygY1 * sj3zyfd * cos(sj3jd * PI / 360);
		//落点3
		float point3X = (mousePos.x - centerPos.x) / mu * mu / 700;
		float point3Y = -((mousePos.y - centerPos.y) / mu * mu / 700);

		Sleep(sj3yc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(sj3yc2);
		SendScanKey(fenshenjian);
		Sleep(sj3yc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(sj3yc4);
		SendScanKey(fenshenjian);
		Sleep(sj3yc5);
		if (sj3tqFlag)
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj3yc6);
			KeyDown(tuqiujian);
			for (int i = 0; i < sj3cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj3fsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj3yc6);
			for (int i = 0; i < sj3cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj3fsjg);
			}
		}
	}
	else
	{
		jtygX = readjtygX(hProcess);
		jtygY = readjtygY(hProcess);
		float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

		//归一后的单位向量
		float jtygX1 = jtygX / mu;
		float jtygY1 = jtygY / mu;
		//落点1
		float point1X = jtygX1 * sj3zyfd * cos(sj3jd * PI / 360) - jtygY1 * sj3zyfd * sin(sj3jd * PI / 360);
		float point1Y = jtygX1 * sj3zyfd * sin(sj3jd * PI / 360) + jtygY1 * sj3zyfd * cos(sj3jd * PI / 360);
		//落点2
		float point2X = jtygX1 * sj3zyfd * cos(sj3jd * PI / 360) + jtygY1 * sj3zyfd * sin(sj3jd * PI / 360);
		float point2Y = -jtygX1 * sj3zyfd * sin(sj3jd * PI / 360) + jtygY1 * sj3zyfd * cos(sj3jd * PI / 360);
		//落点3
		float point3X = jtygX1 * sj3hqfd;
		float point3Y = jtygY1 * sj3hqfd;

		Sleep(sj3yc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(sj3yc2);
		SendScanKey(fenshenjian);
		Sleep(sj3yc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(sj3yc4);
		SendScanKey(fenshenjian);
		Sleep(sj3yc5);
		if (sj3tqFlag)
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj3yc6);
			KeyDown(tuqiujian);
			for (int i = 0; i < sj3cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj3fsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			writePos(hProcess,(float)point3X, (float)point3Y);
			Sleep(sj3yc6);
			for (int i = 0; i < sj3cs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sj3fsjg);
			}
		}
	}
}

void BallsMerge::chongqiu(HANDLE hProcess)
{
	if (chongqiujiantouFlag)
	{
		if (chongqiutqFlag)
		{
			KeyDown(tuqiujian);
			for (int i = 0; i < cqcs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(cqfsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			for (int i = 0; i < cqcs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(cqfsjg);
			}
		}
	}
	else
	{
		Sleep(cqyc1);
		Sleep(cqyc2);
		SendScanKey(fenshenjian);
	}
}

void BallsMerge::sifen(HANDLE hProcess)
{
	if (autosifenFlag)
	{
		jtygX = readjtygX(hProcess);
		jtygY = readjtygY(hProcess);
		float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

		//归一后的单位向量
		float jtygX1 = jtygX / mu;
		float jtygY1 = jtygY / mu;

		Sleep(sfyc1);
		writePos(hProcess,(float)jtygX1, (float)jtygY1);
		Sleep(sfyc2);
		SendScanKey(fenshenjian);
		Sleep(sfyc3);
		SendScanKey(fenshenjian);
		Sleep(sfyc4);
		writePos(hProcess,(float)jtygX1 * sfjcfd, (float)jtygY1 * sfjcfd);
		Sleep(sfyc5);
		if (sifentqFlag)
		{
			KeyDown(tuqiujian);
			for (int i = 0; i < sfcs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sffsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			for (int i = 0; i < sfcs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(sffsjg);
			}
		}
	}
}

void BallsMerge::zhongfen(HANDLE hProcess)
{
	if (autozhongfenFlag)
	{
		jtygX = readjtygX(hProcess);
		jtygY = readjtygY(hProcess);
		float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

		//归一后的单位向量
		float jtygX1 = jtygX / mu;
		float jtygY1 = jtygY / mu;

		Sleep(zfyc1);
		writePos(hProcess,(float)jtygX1, (float)jtygY1);
		Sleep(zfyc2);
		SendScanKey(fenshenjian);
		Sleep(zfyc3);
		writePos(hProcess,(float)jtygX1 * zfjcfd, (float)jtygY1 * zfjcfd);
		Sleep(zfyc4);
		SendScanKey(fenshenjian);
		Sleep(zfyc5);
		if (zhongfentqFlag)
		{
			KeyDown(tuqiujian);
			for (int i = 0; i < zfcs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(zffsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			for (int i = 0; i < zfcs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(zffsjg);
			}
		}
	}
}

void BallsMerge::houyang(HANDLE hProcess, HWND hWnd)
{
	if (autohouyangFlag)
	{
		centerPos = getTopRectCenterPoint(hWnd);
		GetCursorPos(&mousePos);

		float mu = sqrt((mousePos.x - centerPos.x) * (mousePos.x - centerPos.x) + (mousePos.y - centerPos.y) * (mousePos.y - centerPos.y));
		if (mu > 700) mu = 700;
		if (mu < 350) mu = 350;
		//归一后的单位向量
		float jtygX1 = (mousePos.x - centerPos.x) / mu;
		float jtygY1 = -(mousePos.y - centerPos.y) / mu;

		Sleep(hyyc1);
		writePos(hProcess,(float)jtygX1 * hyjcfd1, (float)jtygY1 * hyjcfd1);
		Sleep(hyyc2);
		SendScanKey(fenshenjian);
		Sleep(hyyc3);
		writePos(hProcess,(float)jtygX1 * hyjcfd2, (float)jtygY1 * hyjcfd2);
		Sleep(hyyc4);
		SendScanKey(fenshenjian);
		Sleep(hyyc5);
		if (houyangtqFlag)
		{
			KeyDown(tuqiujian);
			for (int i = 0; i < hycs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(hyfsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			for (int i = 0; i < hycs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(hyfsjg);
			}
		}
	}
}

void BallsMerge::xuanzhuan(HANDLE hProcess)
{
	jtygX = readjtygX(hProcess);
	jtygY = readjtygY(hProcess);
	float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

	//归一后的单位向量
	float jtygX1 = jtygX / mu;
	float jtygY1 = jtygY / mu;

	//先逆时针旋转一次(计算第一次开分身的坐标)，然后顺时针旋转3次(计算三次的旋转坐标)
	float point1X = jtygX1 * xuanzhuan1fd1 * cos(xuanzhuan1jd1 * PI / 180) - jtygY1 * xuanzhuan1fd1 * sin(xuanzhuan1jd1 * PI / 180);
	float point1Y = jtygX1 * xuanzhuan1fd1 * sin(xuanzhuan1jd1 * PI / 180) + jtygY1 * xuanzhuan1fd1 * cos(xuanzhuan1jd1 * PI / 180);
	float point2X = jtygX1 * xuanzhuan1fd2 * cos(xuanzhuan1jd2 * PI / 180) - jtygY1 * xuanzhuan1fd2 * sin(xuanzhuan1jd2 * PI / 180);
	float point2Y = jtygX1 * xuanzhuan1fd2 * sin(xuanzhuan1jd2 * PI / 180) + jtygY1 * xuanzhuan1fd2 * cos(xuanzhuan1jd2 * PI / 180);
	float point3X = jtygX1 * xuanzhuan1fd3 * cos(xuanzhuan1jd3 * PI / 180) - jtygY1 * xuanzhuan1fd3 * sin(xuanzhuan1jd3 * PI / 180);
	float point3Y = jtygX1 * xuanzhuan1fd3 * sin(xuanzhuan1jd3 * PI / 180) + jtygY1 * xuanzhuan1fd3 * cos(xuanzhuan1jd3 * PI / 180);
	float point4X = jtygX1 * xuanzhuan1fd4 * cos(xuanzhuan1jd4 * PI / 180) - jtygY1 * xuanzhuan1fd4 * sin(xuanzhuan1jd4 * PI / 180);
	float point4Y = jtygX1 * xuanzhuan1fd4 * sin(xuanzhuan1jd4 * PI / 180) + jtygY1 * xuanzhuan1fd4 * cos(xuanzhuan1jd4 * PI / 180);
	SendScanKey(fenshenjian);
	Sleep(xz1yc1);
	writePos(hProcess,(float)point1X, (float)point1Y);
	Sleep(xz1yc2);
	SendScanKey(fenshenjian);
	Sleep(xz1yc3);
	writePos(hProcess,(float)point2X, (float)point2Y);
	Sleep(xz1yc4);
	SendScanKey(fenshenjian);
	Sleep(xz1yc5);
	writePos(hProcess,(float)point3X, (float)point3Y);
	Sleep(xz1yc6);
	SendScanKey(fenshenjian);
	Sleep(xz1yc7);
	writePos(hProcess,(float)point4X, (float)point4Y);
	Sleep(xz1yc8);
	SendScanKey(fenshenjian);
	Sleep(xz1yc9);
	if (xuanzhuan1tqFlag)
	{
		KeyDown(tuqiujian);
		for (int i = 0; i < xz1cs; i++)
		{
			SendScanKey(fenshenjian);
			Sleep(xz1fsjg);
		}
		KeyUp(tuqiujian);
	}
	else
	{
		for (int i = 0; i < xz1cs; i++)
		{
			SendScanKey(fenshenjian);
			Sleep(xz1fsjg);
		}
	}
}


void BallsMerge::banxuan(HANDLE hProcess)
{
	jtygX = readjtygX(hProcess);
	jtygY = readjtygY(hProcess);
	float mu = sqrt(jtygX * jtygX + jtygY * jtygY);

	//归一后的单位向量
	float jtygX1 = jtygX / mu;
	float jtygY1 = jtygY / mu;

	//先逆时针旋转一次(计算第一次开分身的坐标)，然后顺时针旋转3次(计算三次的旋转坐标)
	float point1X = jtygX1 * banxuan1fd1 * cos(banxuan1jd1 * PI / 180) - jtygY1 * banxuan1fd1 * sin(banxuan1jd1 * PI / 180);
	float point1Y = jtygX1 * banxuan1fd1 * sin(banxuan1jd1 * PI / 180) + jtygY1 * banxuan1fd1 * cos(banxuan1jd1 * PI / 180);
	float point2X = jtygX1 * banxuan1fd2 * cos(banxuan1jd2 * PI / 180) - jtygY1 * banxuan1fd2 * sin(banxuan1jd2 * PI / 180);
	float point2Y = jtygX1 * banxuan1fd2 * sin(banxuan1jd2 * PI / 180) + jtygY1 * banxuan1fd2 * cos(banxuan1jd2 * PI / 180);
	float point3X = jtygX1 * banxuan1fd3 * cos(banxuan1jd3 * PI / 180) - jtygY1 * banxuan1fd3 * sin(banxuan1jd3 * PI / 180);
	float point3Y = jtygX1 * banxuan1fd3 * sin(banxuan1jd3 * PI / 180) + jtygY1 * banxuan1fd3 * cos(banxuan1jd3 * PI / 180);
	float point4X = jtygX1 * banxuan1fd4 * cos(banxuan1jd4 * PI / 180) - jtygY1 * banxuan1fd4 * sin(banxuan1jd4 * PI / 180);
	float point4Y = jtygX1 * banxuan1fd4 * sin(banxuan1jd4 * PI / 180) + jtygY1 * banxuan1fd4 * cos(banxuan1jd4 * PI / 180);
	SendScanKey(fenshenjian);
	Sleep(bx1yc1);
	writePos(hProcess,(float)point1X, (float)point1Y);
	Sleep(bx1yc2);
	SendScanKey(fenshenjian);
	Sleep(bx1yc3);
	writePos(hProcess,(float)point2X, (float)point2Y);
	Sleep(bx1yc4);
	SendScanKey(fenshenjian);
	Sleep(bx1yc5);
	writePos(hProcess,(float)point3X, (float)point3Y);
	Sleep(bx1yc6);
	SendScanKey(fenshenjian);
	Sleep(bx1yc7);
	writePos(hProcess,(float)point4X, (float)point4Y);
	Sleep(bx1yc8);
	SendScanKey(fenshenjian);
	Sleep(bx1yc9);
	if (banxuan1tqFlag)
	{
		KeyDown(tuqiujian);
		for (int i = 0; i < bx1cs; i++)
		{
			SendScanKey(fenshenjian);
			Sleep(bx1fsjg);
		}
		KeyUp(tuqiujian);
	}
	else
	{
		for (int i = 0; i < bx1cs; i++)
		{
			SendScanKey(fenshenjian);
			Sleep(bx1fsjg);
		}
	}
}


void BallsMerge::sheshou(HANDLE hProcess)
{
	jtygX = readjtygX(hProcess);
	jtygY = readjtygY(hProcess);
	float mu = sqrt(jtygX * jtygX + jtygY * jtygY);
	float cross = jtygX * 0 - jtygY * 1;
	
	//归一后的单位向量
	float jtygX1 = jtygX / mu;
	float jtygY1 = jtygY / mu;

	if (cross > 0)
	{
		//先逆时针旋转一次(计算第一次开分身的坐标)，然后顺时针旋转3次(计算三次的旋转坐标)
		float point1X = jtygX1 * sheshoufd1 * cos(sheshoujd1 * PI / 180) - jtygY1 * sheshoufd1 * sin(sheshoujd1 * PI / 180);
		float point1Y = jtygX1 * sheshoufd1 * sin(sheshoujd1 * PI / 180) + jtygY1 * sheshoufd1 * cos(sheshoujd1 * PI / 180);
		float point2X = jtygX1 * sheshoufd2 * cos(sheshoujd2 * PI / 180) - jtygY1 * sheshoufd2 * sin(sheshoujd2 * PI / 180);
		float point2Y = jtygX1 * sheshoufd2 * sin(sheshoujd2 * PI / 180) + jtygY1 * sheshoufd2 * cos(sheshoujd2 * PI / 180);
		float point3X = jtygX1 * sheshoufd3 * cos(sheshoujd3 * PI / 180) - jtygY1 * sheshoufd3 * sin(sheshoujd3 * PI / 180);
		float point3Y = jtygX1 * sheshoufd3 * sin(sheshoujd3 * PI / 180) + jtygY1 * sheshoufd3 * cos(sheshoujd3 * PI / 180);
		float point4X = jtygX1 * sheshoufd4 * cos(sheshoujd4 * PI / 180) - jtygY1 * sheshoufd4 * sin(sheshoujd4 * PI / 180);
		float point4Y = jtygX1 * sheshoufd4 * sin(sheshoujd4 * PI / 180) + jtygY1 * sheshoufd4 * cos(sheshoujd4 * PI / 180);
		SendScanKey(fenshenjian);
		Sleep(ssyc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(ssyc2);
		SendScanKey(fenshenjian);
		Sleep(ssyc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(ssyc4);
		SendScanKey(fenshenjian);
		Sleep(ssyc5);
		writePos(hProcess,(float)point3X, (float)point3Y);
		Sleep(ssyc6);
		SendScanKey(fenshenjian);
		Sleep(ssyc7);
		writePos(hProcess,(float)point4X, (float)point4Y);
		Sleep(ssyc8);
		SendScanKey(fenshenjian);
		Sleep(ssyc9);
		if (sheshoutqFlag)
		{
			KeyDown(tuqiujian);
			for (int i = 0; i < sscs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(ssfsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			for (int i = 0; i < sscs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(ssfsjg);
			}
		}
	}
	else
	{
		//先顺时针旋转一次(计算第一次开分身的坐标)，然后逆时针旋转3次(计算三次的旋转坐标)
		float point1X = jtygX1 * sheshoufd1 * cos(-sheshoujd1 * PI / 180) - jtygY1 * sheshoufd1 * sin(-sheshoujd1 * PI / 180);
		float point1Y = jtygX1 * sheshoufd1 * sin(-sheshoujd1 * PI / 180) + jtygY1 * sheshoufd1 * cos(-sheshoujd1 * PI / 180);
		float point2X = jtygX1 * sheshoufd2 * cos(-sheshoujd2 * PI / 180) - jtygY1 * sheshoufd2 * sin(-sheshoujd2 * PI / 180);
		float point2Y = jtygX1 * sheshoufd2 * sin(-sheshoujd2 * PI / 180) + jtygY1 * sheshoufd2 * cos(-sheshoujd2 * PI / 180);
		float point3X = jtygX1 * sheshoufd3 * cos(-sheshoujd3 * PI / 180) - jtygY1 * sheshoufd3 * sin(-sheshoujd3 * PI / 180);
		float point3Y = jtygX1 * sheshoufd3 * sin(-sheshoujd3 * PI / 180) + jtygY1 * sheshoufd3 * cos(-sheshoujd3 * PI / 180);
		float point4X = jtygX1 * sheshoufd4 * cos(-sheshoujd4 * PI / 180) - jtygY1 * sheshoufd4 * sin(-sheshoujd4 * PI / 180);
		float point4Y = jtygX1 * sheshoufd4 * sin(-sheshoujd4 * PI / 180) + jtygY1 * sheshoufd4 * cos(-sheshoujd4 * PI / 180);
		SendScanKey(fenshenjian);
		Sleep(ssyc1);
		writePos(hProcess,(float)point1X, (float)point1Y);
		Sleep(ssyc2);
		SendScanKey(fenshenjian);
		Sleep(ssyc3);
		writePos(hProcess,(float)point2X, (float)point2Y);
		Sleep(ssyc4);
		SendScanKey(fenshenjian);
		Sleep(ssyc5);
		writePos(hProcess,(float)point3X, (float)point3Y);
		Sleep(ssyc6);
		SendScanKey(fenshenjian);
		Sleep(ssyc7);
		writePos(hProcess,(float)point4X, (float)point4Y);
		Sleep(ssyc8);
		SendScanKey(fenshenjian);
		Sleep(ssyc9);
		if (sheshoutqFlag)
		{
			KeyDown(tuqiujian);
			for (int i = 0; i < sscs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(ssfsjg);
			}
			KeyUp(tuqiujian);
		}
		else
		{
			for (int i = 0; i < sscs; i++)
			{
				SendScanKey(fenshenjian);
				Sleep(ssfsjg);
			}
		}
	}
}

void BallsMerge::zhongfenMacro(HANDLE hProcess)
{
	BallsMerge::SendScanKey(fenshenjian);
	writePos(hProcess, 0, 0);
	Sleep(40);
	BallsMerge::SendScanKey(fenshenjian);
}

void BallsMerge::sifenMacro()
{
	BallsMerge::SendScanKey(fenshenjian);
	Sleep(sifenMacroInterval);
	BallsMerge::SendScanKey(fenshenjian);
}

void BallsMerge::xuanzhuanMacro()
{
	for(int i=0 ; i < xuanzhuanMacroTimes ; i++)
	{
		BallsMerge::SendScanKey(fenshenjian);
		Sleep(35);
	}
}

void BallsMerge::bafenMacro()
{
	for(int i=0 ; i < 8; i++)
	{
		BallsMerge::SendScanKey(fenshenjian);
		Sleep(bafenMacroInterval);
	}
}