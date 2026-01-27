#include"head.h"

void extract(const string& filename, int blur_ksize)
{
    //读取图片
    Mat src = imread(filename);
    if (src.empty()) {
        cerr << "无法加载图像：" << filename << endl;
        return;
    }
    //灰度转换
    Mat gray;
    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    }
    else {
        gray = src.clone();
    }
    //高斯模糊
    Mat blur_gray, mask;
    GaussianBlur(gray, blur_gray, Size(blur_ksize, blur_ksize), 0);
    //OTSU 阈值
    threshold(blur_gray, mask, 0, 255, THRESH_BINARY | THRESH_OTSU);
    //闭操作
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    morphologyEx(mask, mask, MORPH_CLOSE, kernel);

    //找轮廓
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //创建一个新遮罩，只保留大轮廓
    Mat cleaned_mask = Mat::zeros(mask.size(), mask.type());
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > 1000) {
            drawContours(cleaned_mask, contours, static_cast<int>(i), Scalar(255), FILLED);
        }
    }
    //构造结果图像
    Mat result = Mat::zeros(src.size(), src.type());
    src.copyTo(result, cleaned_mask);
	//显示结果
	imshow("原图", src);
	imshow("结果展示", result);
	waitKey(0);
}