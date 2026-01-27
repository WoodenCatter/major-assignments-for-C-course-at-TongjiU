#include"head.h"

Mat applyConvolution(const vector<vector<int>>& A_padding, const vector<vector<int>>& B,
    int b, int padding, int image_size_row, int image_size_column, int kernel_size)
{
    //卷积
    int size_C_row = image_size_row + padding * 2 - kernel_size + 1;
    int size_C_column = image_size_column + padding * 2 - kernel_size + 1;
    vector<vector<int>> C1(size_C_row, vector<int>(size_C_column, 0));
    for (int i = 0; i < size_C_row; i++) {
        for (int j = 0; j < size_C_column; j++) {
            int sum = 0;
            for (int k = 0; k < kernel_size; k++) {
                for (int l = 0; l < kernel_size; l++) {
                    sum += A_padding[i + k][j + l] * B[k][l];
                }
            }
            C1[i][j] = min(max(sum / b, 0), 255);
        }
    }
    //创建空图像
    Mat result(size_C_row, size_C_column, CV_8UC1);
    // 转成图像
    for (int i = 0; i < size_C_row; i++) {
        for (int j = 0; j < size_C_column; j++) {
            result.at<uchar>(i, j) = static_cast<uchar>(min(255, max(0, C1[i][j])));
        }
    }
    return result;
}