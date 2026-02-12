#pragma once
#include "Simulator.h"
#include "Memory.h"

class BallsMerge :public Memory, public Simulator
{
public:
	BallsMerge();
	~BallsMerge();

	void SendScanKey(BYTE vkCode);
	void KeyDown(BYTE vkCode);
	void KeyUp(BYTE vkCode);

	//合球
	void sanjiao1(HANDLE hProcess, HWND hWnd);
	void sanjiao2(HANDLE hProcess, HWND hWnd);
	void sanjiao3(HANDLE hProcess, HWND hWnd);
	void chongqiu(HANDLE hProcess);
	void sifen(HANDLE hProcess);
	void zhongfen(HANDLE hProcess);
	void houyang(HANDLE hProcess, HWND hWnd);
	void xuanzhuan(HANDLE hProcess);
	void banxuan(HANDLE hProcess);
	void sheshou(HANDLE hProcess);
	//宏
	void zhongfenMacro(HANDLE hProcess);
	void sifenMacro();
	void xuanzhuanMacro();
	void bafenMacro();

	//合球参数
	static int sanjiaojian1, sanjiaojian2, sanjiaojian3, chongqiujian, sifenjian, zhongfenjian, xuanzhuanjian1, banxuanjian1, xuanzhuanjian2, banxuanjian2, sheshoujian, houyangjian, tuqiujian, fenshenjian, qupijian;
	static bool sanjiao1Flag, sanjiao2Flag, sanjiao3Flag, chongqiuFlag, sifenFlag, zhongfenFlag, xuanzhuan1Flag, banxuan1Flag, xuanzhuan2Flag, banxuan2Flag, sheshouFlag, houyangFlag;
	static bool autosanjiao_1_Flag, autosanjiao_2_Flag, autosanjiao_3_Flag, autosifenFlag, autozhongfenFlag, autohouyangFlag;
	static float sj1jd, sj2jd, sj3jd, sj1hqfd, sj1zyfd, sj2hqfd, sj2zyfd, sj3hqfd, sj3zyfd, sfjcfd, zfjcfd, hyjcfd1, hyjcfd2;
	static bool sj1tqFlag, sj2tqFlag, sj3tqFlag, chongqiutqFlag, chongqiujiantouFlag, sifentqFlag, zhongfentqFlag, houyangtqFlag, xuanzhuan1tqFlag, xuanzhuan2tqFlag, banxuan1tqFlag, banxuan2tqFlag, sheshoutqFlag;
	static float jtygX, jtygY, dx, dy, shiye;
	//旋转1参数
	static float xuanzhuan1jd1, xuanzhuan1jd2, xuanzhuan1jd3, xuanzhuan1jd4, xuanzhuan1fd1, xuanzhuan1fd2, xuanzhuan1fd3, xuanzhuan1fd4;
	//半旋1参数
	static float banxuan1jd1, banxuan1jd2, banxuan1jd3, banxuan1jd4, banxuan1fd1, banxuan1fd2, banxuan1fd3, banxuan1fd4;
	//蛇手参数
	static float sheshoujd1, sheshoujd2, sheshoujd3, sheshoujd4, sheshoufd1, sheshoufd2, sheshoufd3, sheshoufd4;

	static int sj1yc1, sj1yc2, sj1yc3, sj1yc4, sj1yc5, sj1yc6, sj1cs, sj1fsjg;
	static int sj2yc1, sj2yc2, sj2yc3, sj2yc4, sj2yc5, sj2yc6, sj2cs, sj2fsjg;
	static int sj3yc1, sj3yc2, sj3yc3, sj3yc4, sj3yc5, sj3yc6, sj3cs, sj3fsjg;
	static int cqyc1, cqyc2, cqcs, cqfsjg;
	static int sfyc1, sfyc2, sfyc3, sfyc4, sfyc5, sfcs, sffsjg;
	static int zfyc1, zfyc2, zfyc3, zfyc4, zfyc5, zfcs, zffsjg;
	static int hyyc1, hyyc2, hyyc3, hyyc4, hyyc5, hycs, hyfsjg;
	static int xz1yc1, xz1yc2, xz1yc3, xz1yc4, xz1yc5, xz1yc6, xz1yc7, xz1yc8, xz1yc9, xz1cs, xz1fsjg;
	static int bx1yc1, bx1yc2, bx1yc3, bx1yc4, bx1yc5, bx1yc6, bx1yc7, bx1yc8, bx1yc9, bx1cs, bx1fsjg;
	static int ssyc1, ssyc2, ssyc3, ssyc4, ssyc5, ssyc6, ssyc7, ssyc8, ssyc9, sscs, ssfsjg;
	//宏
	static bool zhongfenMacroFlag;
	static bool sifenMacroFlag;
	static bool xuanzhuanMacroFlag;
	static bool bafenMacroFlag;
	static int zhongfenMacroKey;
	static int sifenMacroKey;
	static int xuanzhuanMacroKey;
	static int bafenMacroKey;
	static int sifenMacroInterval;
	static int xuanzhuanMacroTimes;
	static int bafenMacroInterval;

	static POINT centerPos;   //中心点坐标
	static POINT mousePos;    //合球时鼠标位置
	static POINT direction; //鼠标指向
	static POINT cursorPos_1; //落点坐标
	static POINT cursorPos_2; //松开鼠标坐标	

};