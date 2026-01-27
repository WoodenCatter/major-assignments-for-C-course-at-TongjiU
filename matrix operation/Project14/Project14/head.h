#include<iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

Mat applyConvolution(const vector<vector<int>>& A_padding, const vector<vector<int>>& B,
    int b, int padding, int image_size_row, int image_size_column, int kernel_size);
void input_arr(vector<vector<int>>& temp, int row, int column);
void show_arr(vector<vector<int>>& arr_out, int row, int column);

void menu();
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv();
void demo();
void OTSU();
void extract(const string& filename, int blur_ksize);