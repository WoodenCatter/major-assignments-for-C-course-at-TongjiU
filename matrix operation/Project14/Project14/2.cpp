#include "head.h"

void nummulti()
{
	//输入矩阵
	cout << "请输入矩阵的行数和列数：";
	int row, column;
	while (true) {
		cin >> row >> column;
		if (cin.fail() || row <= 0 || column <= 0) {
			cout << "请输入大于0的整数！请重新输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}
	vector<vector<int>> arr_out(row, vector<int>(column, 0));
	vector<vector<int>> temp(row, vector<int>(column, 0));
	cout << "请输入矩阵：" << endl;
	input_arr(temp, row, column);
	//输入数乘的数
	cout << "请输入数乘的数（整数）：";
	int num;
	while (true) {
		cin >> num;
		if (cin.fail()) {
			cout << "输入错误！请再次输入：" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}
	//数乘
	for (int j = 0; j < row; j++) {
		for (int k = 0; k < column; k++) {
			arr_out[j][k] = temp[j][k] * num;
		}
	}
	//输出结果
	cout << "数乘后的矩阵为：" << endl;
	show_arr(arr_out, row, column);
}