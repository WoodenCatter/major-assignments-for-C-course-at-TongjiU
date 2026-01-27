#pragma once
#include<iostream>
#include<ctime>
#include<graphics.h>
#include<conio.h>
#include<utility>
#include<cmath>
#include<math.h>
#include<algorithm>
#include<cassert>
using namespace std;

void drawCircleSSAA(IMAGE* buffer, int center_x, int center_y, COLORREF color, int radius);
void drawLineSSAA(IMAGE* buffer, int x1, int y1, int x2, int y2, COLORREF color, int thickness);
double degrad(double deg);
