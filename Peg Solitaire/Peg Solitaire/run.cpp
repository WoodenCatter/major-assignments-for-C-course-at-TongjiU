#include"Game.h"
#include"Menu.h"

void run()	//伟大的运行游戏函数
{
	initgraph(1280, 720);
	GameState currentState = MENU; //初始状态
	//创建菜单和游戏对象
	Menu menu1 = Menu(MENU);
	Menu menu2 = Menu(CLASSIC_MODE);
	Game game1 = Game(PLAYING_CLASSIC);
	Menu menu3 = Menu(PUZZLE_MODE);
	Game game2 = Game(PLAYING_PUZZLE_ONE);
	Game game3 = Game(PLAYING_PUZZLE_TWO);
	while (true)
	{
		if (currentState == EXIT)
		{
			return;
		}
		else if (currentState == MENU)
		{
			currentState = menu1.showMenu();
		}
		else if (currentState == CLASSIC_MODE)
		{
			currentState = menu2.showMenu();
		}
		else if (currentState == PUZZLE_MODE)
		{
			currentState = menu3.showMenu();
		}
		else if (currentState == PLAYING_CLASSIC)
		{
			currentState = game1.playGame();
		}
		else if (currentState == PLAYING_PUZZLE_ONE)
		{
			currentState = game2.playGame();
		}
		else if (currentState == PLAYING_PUZZLE_TWO)
		{
			currentState = game3.playGame();
		}
		else
		{
			currentState = MENU;
		}
	}
}