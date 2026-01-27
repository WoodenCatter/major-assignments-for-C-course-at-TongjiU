#include"Game.h"

Game::Game(GameState i)	//构造函数，根据游戏类型确定棋盘和初始棋子数目
{
	style = i;
	if (style == PLAYING_CLASSIC)
	{
		leftChesses = 32;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) ||
					(i == 1 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 5) || (i == 1 && j == 6) ||
					(i == 5 && j == 0) || (i == 5 && j == 1) || (i == 5 && j == 5) || (i == 5 && j == 6) ||
					(i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 5) || (i == 6 && j == 6))
				{
					board[i][j] = Cell(-1, -1);
				}
				else if ((i == 3 && j == 3))
				{
					board[i][j] = Cell(i, j);
				}
				else
				{
					board[i][j] = Cell(i, j, true);
				}
			}
		}
	}
	else if (style == PLAYING_PUZZLE_ONE)
	{
		leftChesses = 6;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) ||
					(i == 1 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 5) || (i == 1 && j == 6) ||
					(i == 5 && j == 0) || (i == 5 && j == 1) || (i == 5 && j == 5) || (i == 5 && j == 6) ||
					(i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 5) || (i == 6 && j == 6))
				{
					board[i][j] = Cell(-1, -1);
				}
				else if ((i == 3 && j == 1) || (i == 2 && j == 2) || (i == 3 && j == 2) || (i == 4 && j == 2) ||
					(i == 3 && j == 3) || (i == 3 && j == 4))
				{
					board[i][j] = Cell(i, j, true);
				}
				else
				{
					board[i][j] = Cell(i, j);
				}
			}
		}
	}
	else if (style == PLAYING_PUZZLE_TWO)
	{
		leftChesses = 7;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) ||
					(i == 1 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 5) || (i == 1 && j == 6) ||
					(i == 5 && j == 0) || (i == 5 && j == 1) || (i == 5 && j == 5) || (i == 5 && j == 6) ||
					(i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 5) || (i == 6 && j == 6))
				{
					board[i][j] = Cell(-1, -1);
				}
				else if ((i == 2 && j == 1) || (i == 3 && j == 1) || (i == 4 && j == 2) || (i == 3 && j == 3) ||
					(i == 4 && j == 4) || (i == 2 && j == 5) || (i == 3 && j == 5))
				{
					board[i][j] = Cell(i, j, true);
				}
				else
				{
					board[i][j] = Cell(i, j);
				}
			}
		}
	}
}

void Game::findNextMoves(Cell selected_cell)	//用于寻找被选择的棋子的可走位置，记录到nextMoves数组中
{
	for (int i = 0; i < 4; i++) nextMoves[i] = Cell(-1, -1);
	int row = selected_cell.row;
	int col = selected_cell.col;
	if (row == 2 || row == 3 || row == 4)
	{
		if (col != 0 && col != 1)
		{
			if (board[row][col - 1].isOcupied == true && board[row][col - 2].isOcupied == false)
			{
				nextMoves[0] = Cell(row, col - 2, false);
			}
		}
		if (col != 5 && col != 6)
		{
			if (board[row][col + 1].isOcupied == true && board[row][col + 2].isOcupied == false)
			{
				nextMoves[1] = Cell(row, col + 2, false);
			}
		}
	}
	else
	{
		if (col == 4)
		{
			if (board[row][col - 1].isOcupied == true && board[row][col - 2].isOcupied == false)
			{
				nextMoves[0] = Cell(row, col - 2, false);
			}
		}
		if (col == 2)
		{
			if (board[row][col + 1].isOcupied == true && board[row][col + 2].isOcupied == false)
			{
				nextMoves[1] = Cell(row, col + 2, false);
			}
		}
	}
	if (col == 2 || col == 3 || col == 4)
	{
		if (row != 0 && row != 1)
		{
			if (board[row - 1][col].isOcupied == true && board[row - 2][col].isOcupied == false)
			{
				nextMoves[2] = Cell(row - 2, col, false);
			}
		}
		if (row != 5 && row != 6)
		{
			if (board[row + 1][col].isOcupied == true && board[row + 2][col].isOcupied == false)
			{
				nextMoves[3] = Cell(row + 2, col, false);
			}
		}
	}
	else
	{
		if (row == 4)
		{
			if (board[row - 1][col].isOcupied == true && board[row - 2][col].isOcupied == false)
			{
				nextMoves[2] = Cell(row - 2, col, false);
			}
		}
		if (row == 2)
		{
			if (board[row + 1][col].isOcupied == true && board[row + 2][col].isOcupied == false)
			{
				nextMoves[3] = Cell(row + 2, col, false);
			}
		}
	}
}

int Game::findNextMoves(Cell selected_cell, int num)	//用于在判断游戏是否结束时使用，返回这个位置棋子可走位置数目
{
	int row = selected_cell.row;
	int col = selected_cell.col;
	int blankCount = 0;
	if (row == 2 || row == 3 || row == 4)
	{
		if (col != 0 && col != 1)
		{
			if (board[row][col - 1].isOcupied == true && board[row][col - 2].isOcupied == false)
			{
				blankCount++;
			}
		}
		if (col != 5 && col != 6)
		{
			if (board[row][col + 1].isOcupied == true && board[row][col + 2].isOcupied == false)
			{
				blankCount++;
			}
		}
	}
	else
	{
		if (col == 4)
		{
			if (board[row][col - 1].isOcupied == true && board[row][col - 2].isOcupied == false)
			{
				blankCount++;
			}
		}
		if (col == 2)
		{
			if (board[row][col + 1].isOcupied == true && board[row][col + 2].isOcupied == false)
			{
				blankCount++;
			}
		}
	}
	if (col == 2 || col == 3 || col == 4)
	{
		if (row != 0 && row != 1)
		{
			if (board[row - 1][col].isOcupied == true && board[row - 2][col].isOcupied == false)
			{
				blankCount++;
			}
		}
		if (row != 5 && row != 6)
		{
			if (board[row + 1][col].isOcupied == true && board[row + 2][col].isOcupied == false)
			{
				blankCount++;
			}
		}
	}
	else
	{
		if (row == 4)
		{
			if (board[row - 1][col].isOcupied == true && board[row - 2][col].isOcupied == false)
			{
				blankCount++;
			}
		}
		if (row == 2)
		{
			if (board[row + 1][col].isOcupied == true && board[row + 2][col].isOcupied == false)
			{
				blankCount++;
			}
		}
	}
	return blankCount;
}

bool Game::gameOver()	//判断游戏是否结束
{
	bool isGameOver = true;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (board[i][j].isOcupied)
			{
				if (findNextMoves(board[i][j], 0) > 0)
				{
					isGameOver = false;
					break;
				}
			}
		}
	}
	return isGameOver;
}

void Game::resetGame()	//根据类型重置游戏
{
	if (style == PLAYING_CLASSIC)
	{
		leftChesses = 32;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) ||
					(i == 1 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 5) || (i == 1 && j == 6) ||
					(i == 5 && j == 0) || (i == 5 && j == 1) || (i == 5 && j == 5) || (i == 5 && j == 6) ||
					(i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 5) || (i == 6 && j == 6))
				{
					board[i][j] = Cell(-1, -1);
				}
				else if ((i == 3 && j == 3))
				{
					board[i][j] = Cell(i, j);
				}
				else
				{
					board[i][j] = Cell(i, j, true);
				}
			}
		}
	}
	else if (style == PLAYING_PUZZLE_ONE)
	{
		leftChesses = 6;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) ||
					(i == 1 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 5) || (i == 1 && j == 6) ||
					(i == 5 && j == 0) || (i == 5 && j == 1) || (i == 5 && j == 5) || (i == 5 && j == 6) ||
					(i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 5) || (i == 6 && j == 6))
				{
					board[i][j] = Cell(-1, -1);
				}
				else if ((i == 3 && j == 1) || (i == 2 && j == 2) || (i == 3 && j == 2) || (i == 4 && j == 2) ||
					(i == 3 && j == 3) || (i == 3 && j == 4))
				{
					board[i][j] = Cell(i, j, true);
				}
				else
				{
					board[i][j] = Cell(i, j);
				}
			}
		}
	}
	else if (style == PLAYING_PUZZLE_TWO)
	{
		leftChesses = 7;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 5) || (i == 0 && j == 6) ||
					(i == 1 && j == 0) || (i == 1 && j == 1) || (i == 1 && j == 5) || (i == 1 && j == 6) ||
					(i == 5 && j == 0) || (i == 5 && j == 1) || (i == 5 && j == 5) || (i == 5 && j == 6) ||
					(i == 6 && j == 0) || (i == 6 && j == 1) || (i == 6 && j == 5) || (i == 6 && j == 6))
				{
					board[i][j] = Cell(-1, -1);
				}
				else if ((i == 2 && j == 1) || (i == 3 && j == 1) || (i == 4 && j == 2) || (i == 3 && j == 3) ||
					(i == 4 && j == 4) || (i == 2 && j == 5) || (i == 3 && j == 5))
				{
					board[i][j] = Cell(i, j, true);
				}
				else
				{
					board[i][j] = Cell(i, j);
				}
			}
		}
	}
	moveHistory.clear();//清空悔棋记录
	steps = 0;//重置步数
}

void Game::drawChess()	//绘制棋盘、棋子和相关信息
{
	setbkmode(TRANSPARENT);//文字填充透明
	//放棋子
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (board[i][j].isOcupied)
			{
				if (board[i][j].row == selectedCell.row && board[i][j].col == selectedCell.col)
				{
					setfillcolor(RGB(200, 200, 30));
				}
				else
				{
					setfillcolor(RGB(120, 60, 30));
				}
				solidcircle(102 * i + 51, 102 * j + 51, 40);
			}
		}
	}
	//画可走位置
	for (int i = 0; i < 4; i++)
	{
		if (nextMoves[i].isOcupied == false && nextMoves[i].row != -1 && nextMoves[i].col != -1)
		{
			setfillcolor(RED);
			solidcircle(102 * nextMoves[i].row + 51, 102 * nextMoves[i].col + 51, 10);
		}
	}
	//写文字
	TCHAR stepsText[32];
	_stprintf_s(stepsText, _T("步数：%d步"), steps);
	TCHAR leftChessesText[32];
	_stprintf_s(leftChessesText, _T("剩余棋子：%d个"), leftChesses);
	int biggestStep = 0;
	for (int i = 0; i < size(moveHistory); i++)
	{
		if (moveHistory[i].countHistory > biggestStep)
		{
			biggestStep = moveHistory[i].countHistory;
		}
	}
	TCHAR biggestStepText[20];
	_stprintf_s(biggestStepText, _T("最大跳跃：%d次"), biggestStep);
	settextstyle(30, 0, _T("楷体"));
	settextcolor(RGB(140, 140, 140));
	drawtext(stepsText, &stepsButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
	drawtext(leftChessesText, &leftChessesButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
	if (biggestStep < 5)
	{
		settextstyle(30, 0, _T("楷体"));
		settextcolor(RGB(140, 140, 140));
		drawtext(biggestStepText, &biggestStepButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
	}
	else
	{
		settextstyle(32, 0, _T("楷体"));
		settextcolor(RGB(140, 140, 140));
		drawtext(biggestStepText, &biggestStepButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
	}
	if (gameOver())
	{
		if (leftChesses > 1)
		{
			settextstyle(60, 0, _T("楷体"));
			settextcolor(RGB(200, 30, 30));
			drawtext(_T("再接再厉！"), &gameOverButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
		}
		else if (leftChesses == 1)
		{
			if (board[3][3].isOcupied)//要求剩余棋子在中心
			{
				settextstyle(60, 0, _T("楷体"));
				settextcolor(RGB(30, 200, 30));
				drawtext(_T("恭喜通关！"), &gameOverButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
			}
			else
			{
				settextstyle(60, 0, _T("楷体"));
				settextcolor(RGB(200, 30, 30));
				drawtext(_T("再接再厉！"), &gameOverButton, DT_CENTER | DT_RIGHT | DT_SINGLELINE);
			}
		}
	}
}

GameState Game::playGame()	//运行游戏
{
	cleardevice();
	ExMessage m;
	IMAGE bg2;
	loadimage(&bg2, _T("bg4.png"), 1280, 720);
	setbkmode(TRANSPARENT);
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &bg2);
		m = getmessage();
		if (m.x > soundBotton.left && m.x < soundBotton.right && m.y > soundBotton.top && m.y < soundBotton.bottom)
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(200, 200, 30));
			if (SOUND)
			{
				drawtext(_T("声音：开"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				drawtext(_T("声音：关"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			if (m.message == WM_LBUTTONDOWN)//控制音乐开关
			{
				if (SOUND)
				{
					PlaySound(NULL, NULL, 0);
				}
				else
				{
					PlaySound(TEXT("bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				}
				SOUND = !SOUND;
			}
		}
		else
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(60, 60, 60));
			if (SOUND)
			{
				drawtext(_T("声音：开"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				drawtext(_T("声音：关"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		if (m.x > returnButton.left && m.x < returnButton.right && m.y > returnButton.top && m.y < returnButton.bottom)//退出功能
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(200, 200, 30));
			drawtext(_T("返回"), &returnButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (m.message == WM_LBUTTONDOWN)
			{
				resetGame();
				return MENU;//返回主菜单
			}
		}
		else
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(60, 60, 60));
			drawtext(_T("返回"), &returnButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (m.x > undoButton.left && m.x<undoButton.right && m.y>undoButton.top && m.y < undoButton.bottom)//悔棋功能
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(200, 200, 30));
			drawtext(_T("悔棋"), &undoButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (m.message == WM_LBUTTONDOWN)
			{
				if (steps > 0)
				{
					steps--;
					leftChesses++;
					Move lastMove = moveHistory.back();
					board[lastMove.initialPositionX][lastMove.initialPositionY].isOcupied = true;
					board[lastMove.finalPositionX][lastMove.finalPositionY].isOcupied = false;
					board[(lastMove.finalPositionX + lastMove.initialPositionX) / 2][(lastMove.finalPositionY + lastMove.initialPositionY) / 2].isOcupied = true;
					board[lastMove.initialPositionX][lastMove.initialPositionY].jumpCount = lastMove.countHistory;
					board[lastMove.finalPositionX][lastMove.finalPositionY].jumpCount = lastMove.countHistory;
					moveHistory.pop_back();
				}
			}
		}
		else
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(60, 60, 60));
			drawtext(_T("悔棋"), &undoButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (m.x > resetButton.left && m.x < resetButton.right && m.y > resetButton.top && m.y < resetButton.bottom)//重置功能
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(200, 200, 30));
			drawtext(_T("重置"), &resetButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (m.message == WM_LBUTTONDOWN)
			{
				resetGame();
			}
		}
		else
		{
			settextstyle(24, 0, _T("楷体"));
			settextcolor(RGB(60, 60, 60));
			drawtext(_T("重置"), &resetButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (m.x > 0 && m.x < 714 && m.y>0 && m.y < 714)//下棋功能
		{
			if (m.message == WM_LBUTTONDOWN)
			{
				int m_i = (int)m.x / 102;
				int m_j = (int)m.y / 102;
				if (board[m_i][m_j].row != -1)
				{
					if (board[m_i][m_j].isOcupied)
					{
						if (selectedCell.row == m_i && selectedCell.col == m_j && selectedCell.isOcupied)
						{
							selectedCell = Cell(-1, -1);
							for (int i = 0; i < 4; i++) nextMoves[i] = Cell(-1, -1);
						}
						else
						{
							selectedCell = board[m_i][m_j];
							findNextMoves(selectedCell);
						}
					}
					else
					{
						for (int i = 0; i < 4; i++)
						{
							if (nextMoves[i].row == m_i && nextMoves[i].col == m_j)
							{
								if (selectedCell.row != -1 && selectedCell.col != -1)
								{
									board[selectedCell.row][selectedCell.col].isOcupied = false;
									board[(selectedCell.row + m_i) / 2][(selectedCell.col + m_j) / 2].isOcupied = false;
									board[m_i][m_j].isOcupied = true;
									Move newMove = { selectedCell.row, selectedCell.col, m_i, m_j, 1 };
									if (size(moveHistory) > 0 && selectedCell.row == moveHistory.back().finalPositionX && selectedCell.col == moveHistory.back().finalPositionY)
									{
										newMove.countHistory = moveHistory.back().countHistory + 1;
									}
									moveHistory.push_back(newMove);
									steps++;
									leftChesses--;
									board[selectedCell.row][selectedCell.col].jumpCount = 0;
									board[m_i][m_j].jumpCount = steps;
									for (int i = 0; i < 4; i++) nextMoves[i] = Cell(-1, -1);
									selectedCell = Cell(-1, -1);
									break;
								}
							}
						}
					}
				}
			}
		}
		drawChess();
		m.message = 0;
		FlushBatchDraw();
		Sleep(10);
	}
}