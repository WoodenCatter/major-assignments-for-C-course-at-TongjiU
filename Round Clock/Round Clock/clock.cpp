#include"clock.h"

Plate::Plate(pair<int, int> p, int r) : pos0(p), radius(r) {}

void Plate::drawPlate() {
    //‘≤≈ÃÕ‚±Ì
    setlinecolor(WHITE);
    drawCircleSSAA(GetWorkingImage(), pos0.first, pos0.second, WHITE, radius);
    //‘≤≈Ãµ„
    for (int i = 1; i <= 12; i++) {
        double point_rad = degrad(i * 30);
        double point_x1 = pos0.first + 0.97 * radius * sin(point_rad);
        double point_y1 = pos0.second - 0.97 * radius * cos(point_rad);
        double point_x2 = pos0.first + radius * sin(point_rad);
        double point_y2 = pos0.second - radius * cos(point_rad);
        drawLineSSAA(GetWorkingImage(), (int)point_x1, (int)point_y1, (int)point_x2, (int)point_y2, WHITE, 3);
    }
}

Hand::Hand(pair<int, int> p, int l) : pos0(p), length(l) {}

void Hand::drawHand(const tm& n) {
    tm nowtime = n;
    double hour_rad = degrad((nowtime.tm_hour % 12 + nowtime.tm_min / 60.0 + nowtime.tm_sec / 3600) * 30);
    double hour_x = pos0.first + length * 0.36 * sin(hour_rad);
    double hour_y = pos0.second - length * 0.36 * cos(hour_rad);
    drawLineSSAA(GetWorkingImage(), pos0.first, pos0.second, (int)hour_x, (int)hour_y, YELLOW, 6);
    //∑÷’Î
    double min_rad = degrad((nowtime.tm_min + nowtime.tm_sec / 60.0) * 6);
    double min_x = pos0.first + length * 0.54 * sin(min_rad);
    double min_y = pos0.second - length * 0.54 * cos(min_rad);
    drawLineSSAA(GetWorkingImage(), pos0.first, pos0.second, (int)min_x, (int)min_y, GREEN, 4);
    //√Î’Î
    double sec_rad = degrad(nowtime.tm_sec * 6);
    double sec_x = pos0.first + length * 0.9 * sin(sec_rad);
    double sec_y = pos0.second - length * 0.9 * cos(sec_rad);
    drawLineSSAA(GetWorkingImage(), pos0.first, pos0.second, (int)sec_x, (int)sec_y, RED, 2);
}