#include"Menu.h"

Menu::Menu(GameState i)	//构造函数，初始化菜单状态，确定按键文字内容
{
	style = i;
	if (i == MENU)
	{
		loadimage(&bg1, _T("bg1.png"), 1280, 720);
		_stprintf_s(textOne, _T("经典模式"));
		_stprintf_s(textTwo, _T("残局模式"));
		_stprintf_s(textThree, _T("退出游戏"));
	}
	else if (i == CLASSIC_MODE)
	{
		loadimage(&bg2, _T("bg2.png"), 1280, 720);
		_stprintf_s(textOne, _T("返回主菜单"));
		_stprintf_s(textTwo, _T("开始游戏"));
		_stprintf_s(textThree, _T(""));
	}
	else if (i == PUZZLE_MODE)
	{
		loadimage(&bg3, _T("bg3.png"), 1280, 720);
		_stprintf_s(textOne, _T("返回主菜单"));
		_stprintf_s(textTwo, _T("残局1"));
		_stprintf_s(textThree, _T("残局2"));
	}
}

GameState Menu::showMenu()	//显示菜单界面
{
	cleardevice();
	ExMessage m;
	setbkmode(TRANSPARENT);//填充透明
	settextstyle(30, 0, _T("楷体"));
	while (true)
	{
		BeginBatchDraw();
		m = getmessage();
		if (style == MENU)
		{
			putimage(0, 0, &bg1);
			if (m.x > soundBotton.left && m.x < soundBotton.right && m.y > soundBotton.top && m.y < soundBotton.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				if (SOUND)
				{
					drawtext(_T("声音：开"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					drawtext(_T("声音：关"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				if (m.message == WM_LBUTTONDOWN)
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
			if (m.x > buttonOne.left && m.x < buttonOne.right && m.y > buttonOne.top && m.y < buttonOne.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textOne, &buttonOne, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return CLASSIC_MODE; //开始经典模式菜单
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textOne, &buttonOne, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			if (m.x > buttonTwo.left && m.x < buttonTwo.right && m.y > buttonTwo.top && m.y < buttonTwo.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textTwo, &buttonTwo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return PUZZLE_MODE; //进入残局模式菜单
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textTwo, &buttonTwo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			if (m.x > buttonThree.left && m.x < buttonThree.right && m.y > buttonThree.top && m.y < buttonThree.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textThree, &buttonThree, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return EXIT; //返回退出游戏
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textThree, &buttonThree, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		if (style == CLASSIC_MODE)
		{
			putimage(0, 0, &bg2);
			if (m.x > soundBotton.left && m.x < soundBotton.right && m.y > soundBotton.top && m.y < soundBotton.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				if (SOUND)
				{
					drawtext(_T("声音：开"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					drawtext(_T("声音：关"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				if (m.message == WM_LBUTTONDOWN)
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
			if (m.x > buttonOne.left && m.x < buttonOne.right && m.y > buttonOne.top && m.y < buttonOne.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textOne, &buttonOne, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return MENU; //返回主菜单
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textOne, &buttonOne, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			if (m.x > buttonTwo.left && m.x < buttonTwo.right && m.y > buttonTwo.top && m.y < buttonTwo.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textTwo, &buttonTwo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return PLAYING_CLASSIC; //开始游戏
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textTwo, &buttonTwo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		if (style == PUZZLE_MODE)
		{
			putimage(0, 0, &bg3);
			if (m.x > soundBotton.left && m.x < soundBotton.right && m.y > soundBotton.top && m.y < soundBotton.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				if (SOUND)
				{
					drawtext(_T("声音：开"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					drawtext(_T("声音：关"), &soundBotton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				if (m.message == WM_LBUTTONDOWN)
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
			if (m.x > buttonOne.left && m.x < buttonOne.right && m.y > buttonOne.top && m.y < buttonOne.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textOne, &buttonOne, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return MENU; //返回主菜单
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textOne, &buttonOne, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			if (m.x > buttonTwo.left && m.x < buttonTwo.right && m.y > buttonTwo.top && m.y < buttonTwo.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textTwo, &buttonTwo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return PLAYING_PUZZLE_ONE; //残局1
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textTwo, &buttonTwo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			if (m.x > buttonThree.left && m.x < buttonThree.right && m.y > buttonThree.top && m.y < buttonThree.bottom)
			{
				settextcolor(RGB(200, 200, 30));
				drawtext(textThree, &buttonThree, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (m.message == WM_LBUTTONDOWN)
				{
					return PLAYING_PUZZLE_TWO; //残局2
				}
			}
			else
			{
				settextcolor(RGB(60, 60, 60));
				drawtext(textThree, &buttonThree, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		m.message = 0;
		FlushBatchDraw();
		Sleep(10);
	}
}