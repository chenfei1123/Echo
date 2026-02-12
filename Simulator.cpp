#include <Simulator.h>
#include <Windows.h>
#include <TlHelp32.h>

HANDLE Simulator::hProcess;
HWND Simulator::hWnd;


//获取窗口中心坐标
POINT Simulator::getTopRectCenterPoint(HWND hWnd)
{
	POINT centerPoint;
	RECT rect;
	GetClientRect(hWnd, &rect);
	centerPoint.x = (rect.left + rect.right) / 2;
	centerPoint.y = (rect.top + rect.bottom) / 2;
	return centerPoint;
}
//获取顶层窗口句柄
HWND Simulator::getTopRectHwnd()
{
	HWND hWnd;
	hWnd = GetForegroundWindow();
	return hWnd;
}
//获取hProcess,用于读写内存
HANDLE Simulator::getProcessHandle(const wchar_t* processName)
{
	//const wchar_t* processName = L"MuMuVMMHeadless.exe";
	HANDLE hProcess = NULL;
	DWORD PID = 0;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hSnapShot, &pe32))
	{
		do
		{
			if (_wcsicmp(pe32.szExeFile, processName))
			{
				PID = pe32.th32ProcessID;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
				break;
			}
		} while (Process32Next(hSnapShot, &pe32));
		return hProcess;
	}
}