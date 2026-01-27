#include "head.h"

void conv()
{
	//输入矩阵
	int size_a;
	const int kernel_size = 3;
	cout << "请输入矩阵A的大小：";
	while (true) {
		cin >> size_a;
		if (cin.fail() || size_a < 1) {
			cout << "输入错误（输入不满足本题要求）！请再次输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}
	vector<vector<int>> A(size_a, vector<int>(size_a, 0));
	vector<vector<int>> B(kernel_size, vector<int>(kernel_size, 0));
	cout << "请输入矩阵A：" << endl;
	input_arr(A, size_a, size_a);
	cout << "请输入卷积核3*3矩阵B：" << endl;
	input_arr(B, kernel_size, kernel_size);
	const int padding = 1;
	//填充A
	vector<vector<int>> A_padding(size_a + padding * 2, vector<int>(size_a + padding * 2, 0));
	for (int i = 0; i < size_a + padding * 2; i++) {
		for (int j = 0; j < size_a + padding * 2; j++) {
			if (i >= padding && i < size_a + padding && j >= padding && j < size_a + padding) {
				A_padding[i][j] = A[i - padding][j - padding];
			}
		}
	}
	//卷积
	int size_C = size_a + padding * 2 - kernel_size + 1;
	//vector<vector<int>> temp(kernel_size, vector<int>(kernel_size, 1));
	vector<vector<int>> C(size_C, vector<int>(size_C, 0));
	int sum = 0;
	for (int i = 0; i < size_C; i++) {
		for (int j = 0; j < size_C; j++) {
			sum = 0;
			for (int k = 0; k < kernel_size; k++) {
				for (int l = 0; l < kernel_size; l++) {
					sum += A_padding[i + k][j + l] * B[k][l];
				}
			}
			C[i][j] = sum;
		}
	}
	//输出结果
	cout << "卷积后的矩阵为：" << endl;
	show_arr(C, size_C, size_C);
}