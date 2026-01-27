#include"head.h"

void demo()
{
    //读取灰度图像
    Mat image = imread("demolena.jpg", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cerr << "图像加载失败，请检查路径是否正确！" << endl;
        return;
    }
    //提取灰度值
    vector<vector<int>> A(image.rows, vector<int>(image.cols));
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            A[i][j] = image.at<uchar>(i, j);
        }
    }
    //准备卷积核
    int image_size_row = image.rows;
	int image_size_column = image.cols;
    const int kernel_size = 3;
    vector<vector<int>> B1 = { {1,1,1}, {1,1,1}, {1,1,1} };
    vector<vector<int>> B2 = { {-1,-2,-1}, {0,0,0}, {1,2,1} };
    vector<vector<int>> B3 = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
    vector<vector<int>> B4 = { {-1,-1,-1}, {-1,9,-1}, {-1,-1,-1} };
    vector<vector<int>> B5 = { {-1,-1,0}, {-1,0,1}, {0,1,1} };
    vector<vector<int>> B6 = { {1,2,1}, {2,4,2}, {1,2,1} };
    int b1 = 9, b2 = 1, b3 = 1, b4 = 1, b5 = 1, b6 = 16;
    const int padding = 1;
    //填充A
    vector<vector<int>> A_padding(image_size_row + padding * 2, vector<int>(image_size_column + padding * 2, 0));
    for (int i = 0; i < image_size_row; i++) {
        for (int j = 0; j < image_size_column; j++) {
            A_padding[i + padding][j + padding] = A[i][j];
        }
    }
	//卷积
    Mat result1 = applyConvolution(A_padding, B1, b1, padding, image_size_row, image_size_column, kernel_size);
    Mat result2 = applyConvolution(A_padding, B2, b2, padding, image_size_row, image_size_column, kernel_size);
    Mat result3 = applyConvolution(A_padding, B3, b3, padding, image_size_row, image_size_column, kernel_size);
    Mat result4 = applyConvolution(A_padding, B4, b4, padding, image_size_row, image_size_column, kernel_size);
    Mat result5 = applyConvolution(A_padding, B5, b5, padding, image_size_row, image_size_column, kernel_size);
    Mat result6 = applyConvolution(A_padding, B6, b6, padding, image_size_row, image_size_column, kernel_size);
    //图像展示
	imshow("原图", image);
    imshow("B1 卷积", result1);
    imshow("B2 卷积", result2);
    imshow("B3 卷积", result3);
    imshow("B4 卷积", result4);
    imshow("B5 卷积", result5);
    imshow("B6 卷积", result6);
    cout << "已为您展示结果" << endl;
    waitKey(0);
}