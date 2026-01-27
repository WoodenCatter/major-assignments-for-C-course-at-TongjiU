#include"head.h"

void drawCircleSSAA(IMAGE* buffer, int center_x, int center_y, COLORREF color, int radius)
{

    const int scale = 2;
    int scaled_radius = radius * scale;
    int sx = center_x * scale;
    int sy = center_y * scale;

    //超采样区域的范围
    int thick = 5;
    int min_x = sx - scaled_radius - thick * scale;
    int max_x = sx + scaled_radius + thick * scale;
    int min_y = sy - scaled_radius - thick * scale;
    int max_y = sy + scaled_radius + thick * scale;
    int width = max_x - min_x, height = max_y - min_y;
    IMAGE superBuffer(width, height);
    SetWorkingImage(&superBuffer);

    //复制原图背景
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int orig_x = (min_x / scale) + (x / scale);
            int orig_y = (min_y / scale) + (y / scale);
            SetWorkingImage(buffer);
            COLORREF bgColor = getpixel(orig_x, orig_y);
            SetWorkingImage(&superBuffer);
            putpixel(x, y, bgColor);
        }
    }
    SetWorkingImage(&superBuffer);
    setlinecolor(color);
    setlinestyle(PS_SOLID, thick);
    circle(sx - min_x, sy - min_y, scaled_radius);

    //绘制回原图
    for (int x = 0; x < width / scale; x++) {
        for (int y = 0; y < height / scale; y++) {
            int r = 0, g = 0, b = 0;
            SetWorkingImage(&superBuffer);
            for (int i = 0; i < scale; i++) {
                for (int j = 0; j < scale; j++) {
                    int px = x * scale + i;
                    int py = y * scale + j;
                    COLORREF c = getpixel(px, py);
                    r += GetRValue(c);
                    g += GetGValue(c);
                    b += GetBValue(c);
                }
            }
            r /= (scale * scale);
            g /= (scale * scale);
            b /= (scale * scale);
            SetWorkingImage(buffer);
            int target_x = (min_x / scale) + x;
            int target_y = (min_y / scale) + y;
            putpixel(target_x, target_y, RGB(r, g, b));
        }
    }
}

void drawLineSSAA(IMAGE* buffer, int x1, int y1, int x2, int y2, COLORREF color, int thickness)
{
    const int scale = 2;
    int sx1 = x1 * scale, sy1 = y1 * scale;
    int sx2 = x2 * scale, sy2 = y2 * scale;

    //超采样区域的范围
    int min_x = min(sx1, sx2) - thickness * scale;
    int max_x = max(sx1, sx2) + thickness * scale;
    int min_y = min(sy1, sy2) - thickness * scale;
    int max_y = max(sy1, sy2) + thickness * scale;
    int width = max_x - min_x, height = max_y - min_y;
    IMAGE superBuffer(width, height);
    SetWorkingImage(&superBuffer);

    //复制原图背景
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int orig_x = min_x / scale + x / scale;
            int orig_y = min_y / scale + y / scale;
            SetWorkingImage(buffer);
            COLORREF bgColor = getpixel(orig_x, orig_y);
            SetWorkingImage(&superBuffer);
            putpixel(x, y, bgColor);
        }
    }
    setlinecolor(color);
    setlinestyle(PS_SOLID, thickness * scale);
    line(sx1 - min_x, sy1 - min_y, sx2 - min_x, sy2 - min_y);

    //绘制回原图
    for (int x = 0; x < width / scale; x++) {
        for (int y = 0; y < height / scale; y++) {
            int r = 0, g = 0, b = 0;
            SetWorkingImage(&superBuffer);
            for (int i = 0; i < scale; i++) {
                for (int j = 0; j < scale; j++) {
                    int px = x * scale + i;
                    int py = y * scale + j;
                    COLORREF c = getpixel(px, py);
                    r += GetRValue(c);
                    g += GetGValue(c);
                    b += GetBValue(c);
                }
            }
            r /= (scale * scale);
            g /= (scale * scale);
            b /= (scale * scale);
            SetWorkingImage(buffer);
            int target_x = (min_x / scale) + x;
            int target_y = (min_y / scale) + y;
            putpixel(target_x, target_y, RGB(r, g, b));
        }
    }
}

double degrad(double deg) {
    return deg * 3.1415926 / 180.0;
}