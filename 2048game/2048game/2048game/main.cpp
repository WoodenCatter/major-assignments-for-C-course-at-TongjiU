#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

void wait_for_enter();
void print_menu();
void print_help();
void print_exit();
void print_interface(int board[4][4], int score, int step);
void play_game();

struct Pair		//表示坐标方便一些
{
	int x;
	int y;
};

void moveCursor(int x, int y)		//屏幕闪动太厉害，问了下大模型，他说这样会好一些
{
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

bool inVector(vector<Pair> vec, int x, int y)		//判断某个坐标有没有被占用（感觉这个函数有点多余，后面没怎么调用）
{
	for (int i = 0; i < (int)vec.size(); i++) {
		if (vec[i].x == x && vec[i].y == y) {
			return true;
		}
	}
	return false;
}

int rdNum()		//随机生成2或者4
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 1);
	int random_num = dis(gen);
	return (random_num == 1 ? 2 : 4);
}

void play_game()
{
	//变量申明
	int board[4][4] = {};
	int score = 0;
	int step = 0;
	char choice = '\0';		// 用户选择
	string sure_to_esc;		//输入y或n用
	bool own_2048 = false;	// 是否获得2048
	bool done = false;		// 是否完成游戏
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);

	// 游戏初始化，包括生成随机数等操作
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}
	vector<Pair> occupied;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 3);
	occupied.push_back({ dis(gen), dis(gen) });
	while (1) {				//防止生成坐标相同
		int x_initial = dis(gen);
		int y_initial = dis(gen);
		if (!inVector(occupied, x_initial, y_initial)) {
			occupied.push_back({ x_initial, y_initial });
			break;
		}
	}
	board[occupied[0].x][occupied[0].y] = rdNum();
	board[occupied[1].x][occupied[1].y] = rdNum();

	// 打印游戏界面
	print_interface(board, score, step);

	//开始游戏！
	while (1)
	{
		// 获取用户输入
		choice = _getch();

		//循环内变量
		int score_more = 0;			// 分数增加
		bool has_moved = false;		// 记录是否有数字移动

		// 根据用户输入进行相应操作，上下左右Esc
		if (choice == 72) {
			for (int j = 0; j < 4; j++) {
				int i = 0;
				while (i <= 3) {
					if (board[i][j] == 0) {
						for (int k = i + 1; k <= 3; k++) {
							if (board[k][j] != 0) {
								board[i][j] = board[k][j];
								board[k][j] = 0;
								has_moved = true;
								break;
							}
						}
					}
					i++;
				}
			}
			for (int j = 0; j < 4; j++) {
				if (board[0][j] != 0 && board[1][j] == board[0][j]) {
					board[0][j] = 2 * board[0][j];
					board[1][j] = 0;
					score_more += board[0][j];
					if (!done && board[0][j] == 2048) own_2048 = true;
				}
				if (!(board[0][j] != 0 && board[1][j] == board[0][j]) && (board[1][j] != 0 && board[2][j] == board[1][j])) {
					board[1][j] = 2 * board[1][j];
					board[2][j] = 0;
					score_more += board[1][j];
					if (!done && board[1][j] == 2048) own_2048 = true;
				}
				if (!(board[1][j] != 0 && board[2][j] == board[1][j]) && (board[2][j] != 0 && board[3][j] == board[2][j]))
				{
					board[2][j] = 2 * board[2][j];
					board[3][j] = 0;
					score_more += board[2][j];
					if (!done && board[2][j] == 2048) own_2048 = true;
				}
			}
			if (score_more != 0) {
				for (int j = 0; j < 4; j++) {
					int i = 0;
					while (i <= 3) {
						if (board[i][j] == 0) {
							for (int k = i + 1; k <= 3; k++) {
								if (board[k][j] != 0) {
									board[i][j] = board[k][j];
									board[k][j] = 0;
									has_moved = true;
									break;
								}
							}
						}
						i++;
					}
				}
			}
		}
		else if (choice == 80) {
			for (int j = 0; j < 4; j++) {
				int i = 3;
				while (i >= 0) {
					if (board[i][j] == 0) {
						for (int k = i - 1; k >= 0; k--) {
							if (board[k][j] != 0) {
								board[i][j] = board[k][j];
								board[k][j] = 0;
								has_moved = true;
								break;
							}
						}
					}
					i--;
				}
			}
			for (int j = 0; j < 4; j++) {
				if (board[3][j] != 0 && board[2][j] == board[3][j]) {
					board[3][j] = 2 * board[3][j];
					board[2][j] = 0;
					score_more += board[3][j];
					if (!done && board[3][j] == 2048) own_2048 = true;
				}
				if (!(board[3][j] != 0 && board[2][j] == board[3][j]) && (board[2][j] != 0 && board[1][j] == board[2][j])) {
					board[2][j] = 2 * board[2][j];
					board[1][j] = 0;
					score_more += board[2][j];
					if (!done && board[2][j] == 2048) own_2048 = true;
				}
				if (!(board[2][j] != 0 && board[1][j] == board[2][j]) && (board[1][j] != 0 && board[0][j] == board[1][j]))
				{
					board[1][j] = 2 * board[1][j];
					board[0][j] = 0;
					score_more += board[1][j];
					if (!done && board[1][j] == 2048) own_2048 = true;
				}
			}
			if (score_more != 0) {
				for (int j = 0; j < 4; j++) {
					int i = 3;
					while (i >= 0) {
						if (board[i][j] == 0) {
							for (int k = i - 1; k >= 0; k--) {
								if (board[k][j] != 0) {
									board[i][j] = board[k][j];
									board[k][j] = 0;
									has_moved = true;
									break;
								}
							}
						}
						i--;
					}
				}
			}
		}
		else if (choice == 75) {
			for (int i = 0; i < 4; i++) {
				int j = 0;
				while (j <= 3) {
					if (board[i][j] == 0) {
						for (int k = j + 1; k <= 3; k++) {
							if (board[i][k] != 0) {
								board[i][j] = board[i][k];
								board[i][k] = 0;
								has_moved = true;
								break;
							}
						}
					}
					j++;
				}
			}
			for (int i = 0; i < 4; i++) {
				if (board[i][0] != 0 && board[i][1] == board[i][0]) {
					board[i][0] = 2 * board[i][0];
					board[i][1] = 0;
					score_more += board[i][0];
					if (!done && board[i][0] == 2048) own_2048 = true;
				}
				if (!(board[i][0] != 0 && board[i][1] == board[i][0]) && (board[i][1] != 0 && board[i][2] == board[i][1])) {
					board[i][1] = 2 * board[i][1];
					board[i][2] = 0;
					score_more += board[i][1];
					if (!done && board[i][1] == 2048) own_2048 = true;
				}
				if (!(board[i][1] != 0 && board[i][2] == board[i][1]) && (board[i][2] != 0 && board[i][3] == board[i][2]))
				{
					board[i][2] = 2 * board[i][2];
					board[i][3] = 0;
					score_more += board[i][2];
					if (!done && board[i][2] == 2048) own_2048 = true;
				}
			}
			if (score_more != 0) {
				for (int i = 0; i < 4; i++) {
					int j = 0;
					while (j <= 3) {
						if (board[i][j] == 0) {
							for (int k = j + 1; k <= 3; k++) {
								if (board[i][k] != 0) {
									board[i][j] = board[i][k];
									board[i][k] = 0;
									has_moved = true;
									break;
								}
							}
						}
						j++;
					}
				}
			}
		}
		else if (choice == 77) {
			for (int i = 0; i < 4; i++) {
				int j = 3;
				while (j >= 0) {
					if (board[i][j] == 0) {
						for (int k = j - 1; k >= 0; k--) {
							if (board[i][k] != 0) {
								board[i][j] = board[i][k];
								board[i][k] = 0;
								has_moved = true;
								break;
							}
						}
					}
					j--;
				}
			}
			for (int i = 0; i < 4; i++) {
				if (board[i][3] != 0 && board[i][2] == board[i][3]) {
					board[i][3] = 2 * board[i][3];
					board[i][2] = 0;
					score_more += board[i][3];
					if (!done && board[i][3] == 2048) own_2048 = true;
				}
				if (!(board[i][3] != 0 && board[i][2] == board[i][3]) && (board[i][2] != 0 && board[i][1] == board[i][2])) {
					board[i][2] = 2 * board[i][2];
					board[i][1] = 0;
					score_more += board[i][2];
					if (!done && board[i][2] == 2048) own_2048 = true;
				}
				if (!(board[i][2] != 0 && board[i][1] == board[i][2]) && (board[i][1] != 0 && board[i][0] == board[i][1]))
				{
					board[i][1] = 2 * board[i][1];
					board[i][0] = 0;
					score_more += board[i][1];
					if (!done && board[i][1] == 2048) own_2048 = true;
				}
			}
			if (score_more != 0) {
				for (int i = 0; i < 4; i++) {
					int j = 3;
					while (j >= 0) {
						if (board[i][j] == 0) {
							for (int k = j - 1; k >= 0; k--) {
								if (board[i][k] != 0) {
									board[i][j] = board[i][k];
									board[i][k] = 0;
									has_moved = true;
									break;
								}
							}
						}
						j--;
					}
				}
			}
		}
		else if (choice == 27) {
			cout << endl;
			cout << "你确定要退出游戏吗？(y/n):";
			while (1) {
				cin >> sure_to_esc;
				if (sure_to_esc == "y" || sure_to_esc == "Y") {
					cout << endl;
					SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "                             游戏结束！" << endl;
					SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << "            你的总分是：" << score << "               你的步数是：" << step << endl;
					cout << endl;
					wait_for_enter();
					print_exit();
					return;
				}
				else if (sure_to_esc == "n" || sure_to_esc == "N") {
					wait_for_enter();
					break;
				}
				else {
					cout << "输入错误，请重新输入(y/n):";
				}
			}
		}

		// 更新相关数据
		if (score_more != 0 || has_moved) {
			step += 1;
			score += score_more;
			vector<Pair> empty;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (board[i][j] == 0) {
						empty.push_back({ i,j });
					}
				}
			}
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, (int)empty.size() - 1);
			int x_y_temp = dis(gen);
			board[empty[x_y_temp].x][empty[x_y_temp].y] = rdNum();
		}

		// 打印游戏界面
		moveCursor(0, 0);
		print_interface(board, score, step);

		// 判断游戏是否结束，如果结束则跳出循环
		if (score_more == 0 && !has_moved) {
			vector<Pair> empty;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (board[i][j] == 0) {
						empty.push_back({ i,j });
					}
				}
			}
			if (empty.size() == 0) {
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "                             Game Over!" << endl;
				SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << "            你的总分是：" << score << "               你的步数是：" << step << endl;
				wait_for_enter();
				print_exit();
				return;
			}
		}

		if (own_2048) {
			cout << endl;
			SetConsoleTextAttribute(handle_out, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "                              恭喜通关！！！" << endl;
			SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << "            你的总分是：" << score << "               你的步数是：" << step << endl;
			cout << endl;
			cout << "你是否继续游戏？(y/n):";
			while (1) {
				cin >> sure_to_esc;
				if (sure_to_esc == "y" || sure_to_esc == "Y") {
					done = true;
					own_2048 = false;
					wait_for_enter();
					moveCursor(0, 0);
					print_interface(board, score, step);
					break;
				}
				else if (sure_to_esc == "n" || sure_to_esc == "N") {
					print_exit();
					return;
				}
				else {
					cout << "输入错误，请重新输入(y/n):";
				}
			}
		}
	}

	// 游戏结束
	print_exit();
}

int main()
{
	char choice = '\0';
	// 设置控制台标题为2048
	SetConsoleTitle(TEXT("2048"));
	// 主循环
	while (1)
	{
		// 调用菜单显示函数
		print_menu();
		// 获取用户选择
		choice = _getche();

		// 根据用户选择进行相应操作
		switch (choice)
		{
		case 'a':
			play_game();
			break;
		case 'b':
			print_help();
			break;
		case'c':
			print_exit();
			return 0;
		default:
			cout << "\n输入错误，请从新输入" << endl;
			wait_for_enter();
		}
	}
	return 0;
}

void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

void print_menu()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "--------------------------------------------\n";
	cout << "********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印标题
	cout << "                   2048\n";
	cout << "                a.经典模式\n";
	cout << "                b.游戏规则\n";
	cout << "                c.退出游戏\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	// 打印菜单
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";

	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n请输入你的选择(a-c):";
}

void print_help()
{
	// 清屏
	system("CLS");
	// 获取标准输出设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	// 打印游戏规则
	cout << "操作说明：\n\n";
	cout << "↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	cout << "游戏介绍：\n\n";
	cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
	cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
	cout << "如果得到数字2048，则游戏胜利!\n";
	cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	wait_for_enter();
}

void print_exit()
{
	cout << "\n退出中";
	for (int i = 4; i > 0; --i)
	{
		Sleep(200);
		cout << ".";
	}
}

void print_interface(int board[4][4], int score, int step)
{
	// 清屏
	system("CLS");
	//获取标准输入设备句柄
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	// 打印游戏界面
	cout << "            --------------------------------------------\n";
	cout << "            分数：" << setw(6) << score << "              步数：" << setw(6) << step << endl;
	cout << "            --------------------------------------------\n";
	cout << "            ********************************************\n";
	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                       |----|----|----|----|\n";

	for (int i = 0; i < 4; i++)
	{
		cout << "                       |";
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] != 0)
			{
				cout << setw(4) << board[i][j] << "|";
			}
			else
			{
				cout << "    |";
			}
		}
		cout << "\n                       |----|----|----|----|\n";
	}

	// 设置控制台文字颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            ********************************************\n";
	cout << "            --------------------------------------------\n";
	cout << "            ↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";

	// 恢复控制台文字颜色为默认颜色
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}