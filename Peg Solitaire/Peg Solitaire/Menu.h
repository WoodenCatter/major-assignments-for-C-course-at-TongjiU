#pragma once
#include"Common.h"

class Menu
{
private:
	GameState style = MENU;						//当前菜单状态
	RECT buttonOne = { 880,210,1100,270 };		//按钮一位置
	RECT buttonTwo = { 880,330,1100,390 };		//按钮二位置
	RECT buttonThree = { 880,450,1100,510 };	//按钮三位置
	RECT soundBotton = { 1120,680,1280,720 };	//声音开关按钮
	TCHAR textOne[32] = _T("");
	TCHAR textTwo[32] = _T("");
	TCHAR textThree[32] = _T("");
	IMAGE bg1;
	IMAGE bg2;
	IMAGE bg3;

public:
	Menu(GameState i = MENU);	//构造函数，初始化菜单状态，确定按键文字内容
	GameState showMenu();	//显示菜单界面
};