#include"head.h"

void OTSU()
{
	Mat src = imread("demolena.jpg", IMREAD_GRAYSCALE);
	Mat dst;
	threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("OTSU", dst);
	waitKey(0);
}