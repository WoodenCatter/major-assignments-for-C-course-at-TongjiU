#pragma once
#include <graphics.h>
#include <conio.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
void run();
extern bool SOUND;

enum GameState	//Ò³Ãæ×´Ì¬
{
	MENU,
	CLASSIC_MODE,
	PUZZLE_MODE,
	PLAYING_CLASSIC,
	PLAYING_PUZZLE_ONE,
	PLAYING_PUZZLE_TWO,
	EXIT
};

