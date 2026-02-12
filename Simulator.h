#pragma once
#include <Windows.h>
class Simulator
{
public:
	static HANDLE hProcess;
	static HWND hWnd;

	HANDLE getProcessHandle(const wchar_t* processName);
	HWND getTopRectHwnd();
	POINT getTopRectCenterPoint(HWND hWnd);
};
