//#include"head.h"
//
//Mat applyConvolution(const vector<vector<int>>& input,
//    const vector<vector<int>>& kernel,
//    int divisor,
//    int padding)
//{
//    int input_size = input.size();
//    int kernel_size = kernel.size();
//    int padded_size = input_size + 2 * padding;
//    int output_size = padded_size - kernel_size + 1;
//    //填充
//    vector<vector<int>> padded(padded_size, vector<int>(padded_size, 0));
//    for (int i = 0; i < input_size; i++) {
//        for (int j = 0; j < input_size; j++) {
//            padded[i + padding][j + padding] = input[i][j];
//        }
//    }
//    //卷积结果
//    vector<vector<int>> output(output_size, vector<int>(output_size, 0));
//    for (int i = 0; i < output_size; i++) {
//        for (int j = 0; j < output_size; j++) {
//            int sum = 0;
//            for (int ki = 0; ki < kernel_size; ki++) {
//                for (int kj = 0; kj < kernel_size; kj++) {
//                    sum += padded[i + ki][j + kj] * kernel[ki][kj];
//                }
//            }
//            output[i][j] = std::min(255, std::max(0, sum / divisor));
//        }
//    }
//    //转图像
//    Mat result(output_size, output_size, CV_8UC1);
//    for (int i = 0; i < output_size; i++) {
//        for (int j = 0; j < output_size; j++) {
//            result.at<uchar>(i, j) = static_cast<uchar>(output[i][j]);
//        }
//    }
//    return result;
//}
//
//void demo()
//{
//	//读取灰度图像
//	Mat image = imread("demolena.jpg", IMREAD_GRAYSCALE);
//    if (image.empty()) {
//        cerr << "图像加载失败，请检查路径是否正确！" << endl;
//        return;
//    }
//    if (image.rows != image.cols) {
//        cerr << "当前代码仅支持正方形图像处理！" << endl;
//        return;
//    }
//    //提取灰度值
//    vector<vector<int>> A(image.rows, vector<int>(image.cols));
//    for (int i = 0; i < image.rows; i++) {
//        for (int j = 0; j < image.cols; j++) {
//            A[i][j] = image.at<uchar>(i, j);
//        }
//    }
//	//准备卷积核
//	int image_size = image.rows;
//    const int kernel_size = 3;
//    /*int B1[3][3] = { 1,1,1,1,1,1,1,1,1 };
//    int B2[3][3] = { -1,-2,-1,0,0,0,1,2,1 };
//	int B3[3][3] = { -1,0,1,-2,0,2,-1,0,1 };
//	int B4[3][3] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
//    int B5[3][3] = { -1,-1,0,-1,0,1,0,1,1 };
//    int B6[3][3] = { 1,2,1,2,4,2,1,2,1 };*/
//    vector<vector<int>> B1 = { {1,1,1}, {1,1,1}, {1,1,1} };
//    vector<vector<int>> B2 = { {-1,-2,-1}, {0,0,0}, {1,2,1} };
//    vector<vector<int>> B3 = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
//    vector<vector<int>> B4 = { {-1,-1,-1}, {-1,9,-1}, {-1,-1,-1} };
//    vector<vector<int>> B5 = { {-1,-1,0}, {-1,0,1}, {0,1,1} };
//    vector<vector<int>> B6 = { {1,2,1}, {2,4,2}, {1,2,1} };
//	int b1 = 9, b2 = 1, b3 = 1, b4 = 1, b5 = 1, b6 = 16;
//    const int padding = 1;
//	////填充A
// //   vector<vector<int>> A_padding(image_size + padding * 2, vector<int>(image_size + padding * 2, 0));
// //   for (int i = 0; i < image_size; i++) {
// //       for (int j = 0; j < image_size; j++) {
// //           A_padding[i + padding][j + padding] = A[i][j];
// //       }
// //   }
//	////卷积
// //   int size_C = image_size + padding * 2 - kernel_size + 1;
// //   vector<vector<int>> C1(size_C, vector<int>(size_C, 0));
// //   for (int i = 0; i < size_C; i++) {
// //       for (int j = 0; j < size_C; j++) {
// //           int sum = 0;
// //           for (int k = 0; k < kernel_size; k++) {
// //               for (int l = 0; l < kernel_size; l++) {
// //                   sum += A_padding[i + k][j + l] * B1[k][l];
// //               }
// //           }
//	//		C1[i][j] = min(max(sum / b1, 0), 255);
// //       }
// //   }
// //   //创建空图像
// //   Mat result(size_C, size_C, CV_8UC1);
// //   // 转成图像
// //   for (int i = 0; i < size_C; i++) {
// //       for (int j = 0; j < size_C; j++) {
// //           result.at<uchar>(i, j) = static_cast<uchar>(min(255, max(0, C1[i][j])));
// //       }
// //   }
// //   imshow("卷积结果", result);
//    //
//    Mat result1 = applyConvolution(A, B1, b1, padding);
//    Mat result2 = applyConvolution(A, B2, b2, padding);
//    Mat result3 = applyConvolution(A, B3, b3, padding);
//    Mat result4 = applyConvolution(A, B4, b4, padding);
//    Mat result5 = applyConvolution(A, B5, b5, padding);
//    Mat result6 = applyConvolution(A, B6, b6, padding);
//
//    imshow("B1 卷积", result1);
//    imshow("B2 卷积", result2);
//    imshow("B3 卷积", result3);
//    imshow("B4 卷积", result4);
//    imshow("B5 卷积", result5);
//    imshow("B6 卷积", result6);
//    waitKey(0);
//}