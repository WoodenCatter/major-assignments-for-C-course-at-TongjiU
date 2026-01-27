#pragma once
#include"Common.h"
#include<vector>
#include <windows.h>

struct Move		//移动结构体
{
	int initialPositionX;
	int initialPositionY;
	int finalPositionX;
	int finalPositionY;
	int countHistory;
};

class Cell		//棋盘格类
{
public:
	int row, col;
	bool isOcupied;
	int jumpCount;

	Cell() : row(-1), col(-1), isOcupied(false), jumpCount(0) {}
	Cell(int a, int b, bool c = false, int d = 0) : row(a), col(b), isOcupied(c), jumpCount(d) {}
};

class Game		//游戏类
{
private:
	GameState style = PLAYING_CLASSIC;	//初始化，经典模式
	Cell board[7][7];					//创建棋盘
	int steps = 0;						//游戏步数
	int leftChesses = 32;				//剩余棋子数目，默认初始值为32个棋子
	Cell selectedCell = Cell(-1, -1);	//被鼠标选中的棋子，如果没有选中则为(-1,-1)
	Cell nextMoves[4] = { Cell(-1, -1), Cell(-1, -1), Cell(-1, -1), Cell(-1, -1) };	//被选中棋子可以走的位置
	vector<Move> moveHistory = {};					//记录移动历史，方便悔棋功能
	RECT returnButton = { 1200,0,1280,40 };			//返回主菜单按键
	RECT undoButton = { 1200,40,1280,80 };			//悔棋按键
	RECT resetButton = { 1200,80,1280,120 };		//重置按键
	RECT stepsButton = { 760,120,1160,200 };		//步数显示
	RECT leftChessesButton = { 760,200,1160,280 };	//剩余棋子显示
	RECT biggestStepButton = { 760,280,1160,360 };	//最大跳跃次数显示
	RECT gameOverButton = { 760,380,1200,580 };		//游戏结束显示
	RECT soundBotton = { 1120,680,1280,720 };		//声音开关按键

public:
	Game(GameState i = PLAYING_CLASSIC);	//构造函数，根据游戏类型确定棋盘和初始棋子数目
	void findNextMoves(Cell selected_cell);	//用于寻找被选择的棋子的可走位置，记录到nextMoves数组中
	int findNextMoves(Cell selected_cell, int num);	//用于在判断游戏是否结束时使用，返回这个位置棋子可走位置数目
	bool gameOver();	//判断游戏是否结束
	void resetGame();	//根据类型重置游戏
	void drawChess();	//绘制棋盘、棋子和相关信息
	GameState playGame();	//运行游戏
};