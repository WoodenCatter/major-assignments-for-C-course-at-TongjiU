#include"Clock.h"

int main()
{
    initgraph(640, 480);
	pair<int, int> pos = make_pair(320, 240);   //钟表中心位置
    IMAGE plateBuffer(640, 480);

    time_t start = time(nullptr);
    tm starttime;
    localtime_s(&starttime, &start);
    const TCHAR* imgPath = nullptr;
    if (starttime.tm_hour >= 5 && starttime.tm_hour < 7) {
        imgPath = _T("清晨.png");
    }
    else if (starttime.tm_hour >= 7 && starttime.tm_hour < 17) {
        imgPath = _T("白天.png");
    }
    else if (starttime.tm_hour >= 17 && starttime.tm_hour < 19) {
        imgPath = _T("傍晚.png");
    }
    else {
        imgPath = _T("夜晚.png");
    }
	loadimage(&plateBuffer, imgPath, 640, 480); //加载背景图

    SetWorkingImage(&plateBuffer);
    Plate plate(pos, 200);
	plate.drawPlate();  //绘制表盘
    SetWorkingImage(NULL);

    BeginBatchDraw();
	time_t lastSec = starttime.tm_sec;
    while (true)
    {
		time_t now = time(nullptr); //获取当前时间
        tm nowtime;
        localtime_s(&nowtime, &now);

        if (nowtime.tm_sec != lastSec) {
            lastSec = nowtime.tm_sec;

            cleardevice();

			const TCHAR* newimgPath = nullptr;  //判断是否需要更换背景图
            if (nowtime.tm_hour >= 5 && nowtime.tm_hour < 7) {
                newimgPath = _T("清晨.png");
            }
            else if (nowtime.tm_hour >= 7 && nowtime.tm_hour < 17) {
                newimgPath = _T("白天.png");
            }
            else if (nowtime.tm_hour >= 17 && nowtime.tm_hour < 19) {
                newimgPath = _T("傍晚.png");
            }
            else {
                newimgPath = _T("夜晚.png");
            }
            if (newimgPath != imgPath) {
                imgPath = newimgPath;
                loadimage(&plateBuffer, imgPath, 640, 480);
                SetWorkingImage(&plateBuffer);
                plate.drawPlate();
                SetWorkingImage(NULL);
            }
            putimage(0, 0, &plateBuffer);

			Hand hand(pos, 200);    //绘制指针
            hand.drawHand(nowtime);

            FlushBatchDraw();
        }
        Sleep(10);
    }
    EndBatchDraw();
    closegraph();

    return 0;
}