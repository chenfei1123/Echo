#define _WIN32_WINNT 0x0600
#include "Memory.h"
#include <Windows.h>
#include <mutex>
#include <thread>
#include <vector>


Memory::Memory()
{
	
}
Memory::~Memory()
{

}

//粘合
void Memory::writenianhe(HANDLE hProcess,float nianheValue)
{
	WriteProcessMemory(hProcess, (LPVOID)nianheAdress, &nianheValue, sizeof(nianheValue), NULL);
}
//变速
void Memory::writebiansu(HANDLE hProcess, float biansuValue)
{
	WriteProcessMemory(hProcess, (LPVOID)biansuAdress, &biansuValue, sizeof(float), NULL);
}
//视野
void Memory::writeshiye(HANDLE hProcess,float shiyeValue)
{
	uintptr_t newshiyeAddress = (uintptr_t)shiyeAdress + 4;

	WriteProcessMemory(
		hProcess,
		(LPVOID)shiyeAdress,
		&shiyeValue,
		sizeof(float),
		NULL
	);

	WriteProcessMemory(
		hProcess,
		(LPVOID)newshiyeAddress,
		&shiyeValue,
		sizeof(float),
		NULL
	);
}
//昵称大小
void Memory::writencdx(HANDLE hProcess, float ncdxValue)
{
	WriteProcessMemory(hProcess, (LPVOID)ncdxAdress, &ncdxValue, sizeof(float), NULL);
}
//吐球-----------------------循环写入
void Memory::writetuqiu(HANDLE hProcess, float tuqiuValue)
{
	WriteProcessMemory(hProcess, (LPVOID)tuqiuAdress, &tuqiuValue, sizeof(float), NULL);
}
//摇杆解限------------------>循环写入
void Memory::writeyaoganjiexian(HANDLE hProcess,float ygjiexianValue)
{
	WriteProcessMemory(hProcess, (LPVOID)yaoganjiexianAdress, &ygjiexianValue, sizeof(float), NULL);
}
//分身解限------------------->循环写入
void Memory::writefsjiexian(HANDLE hProcess, float fenshenjiexianValue)
{
	WriteProcessMemory(hProcess, (LPVOID)fsjiexianAdress, &fenshenjiexianValue, sizeof(float), NULL);
}
//摇杆回弹------------------>循环写入
void Memory::writeyaoganhuitan(HANDLE hProcess,float huitanValue)
{
	WriteProcessMemory(hProcess, (LPVOID)yaoganhuitanAdress_1, &huitanValue, sizeof(float), NULL);
	WriteProcessMemory(hProcess, (LPVOID)yaoganhuitanAdress_2, &huitanValue, sizeof(float), NULL);
}
//局内去皮
void Memory::writejuneiqupi(HANDLE hProcess,float juneiqupiValue)
{
	WriteProcessMemory(hProcess, (LPVOID)juneiqupiAdress, &juneiqupiValue, sizeof(float), NULL);
}
//摇杆优化（清除摇杆延迟，摇杆容差修改为0）------循环写入
void Memory::writeyaoganyouhua(HANDLE hProcess, float rongchaValue)
{
	//修改摇杆容差为0
	WriteProcessMemory(hProcess, (LPVOID)yaoganrongchaAdress, &rongchaValue, sizeof(float), NULL);
}
//摇杆延迟
void Memory::writeyaoganyanchi(HANDLE hProcess, float yaoganyanchiValue)
{
	//清除摇杆延迟
	WriteProcessMemory(hProcess, (LPVOID)ygycAdress_1, &yaoganyanchiValue, sizeof(float), NULL);
	WriteProcessMemory(hProcess, (LPVOID)ygycAdress_2, &yaoganyanchiValue, sizeof(float), NULL);
}
//摇杆一万
void Memory::writeyaogan10000(HANDLE hProcess, float yaogan10000Value)
{
	WriteProcessMemory(hProcess, (LPVOID)yaogan10000Adress_2, &yaogan10000Value, sizeof(float), NULL);
}
//写入位置，拉动摇杆
void Memory::writePos(HANDLE hProcess,float x, float y)
{
	uintptr_t newncygAdress = (uintptr_t)ncygAdress + 0x4;

	WriteProcessMemory(hProcess, (LPVOID)ncygAdress, &x, sizeof(float), NULL);
	WriteProcessMemory(hProcess, (LPVOID)newncygAdress, &y, sizeof(float), NULL);
}
//读取摇杆X
float Memory::readjtygX(HANDLE hProcess)
{
	float jtygX;
	ReadProcessMemory(hProcess, (LPVOID)ncygjsxAdress, &jtygX, sizeof(float), NULL);
	return jtygX;
}
//读取摇杆Y
float Memory::readjtygY(HANDLE hProcess)
{
	float jtygY;
	ReadProcessMemory(hProcess, (LPVOID)ncygjsyAdress, &jtygY, sizeof(float), NULL);
	return jtygY;
}


void Memory::Scanner()
{
	//待实现
}
