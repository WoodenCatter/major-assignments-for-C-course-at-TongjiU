#include "head.h"

void hadamulti()
{
	//输入矩阵
	cout << "请输入一共有几个矩阵需要进行Hadamard乘积运算：";
	int amount;
	while (true) {
		cin >> amount;
		if (cin.fail() || amount < 2) {
			cout << "请输入一个大于等于2的整数！请重新输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}
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
	vector<vector<int>> arr_out(row, vector<int>(column, 1));
	vector<vector<int>> temp(row, vector<int>(column, 0));
	for (int i = 0; i < amount; i++) {
		cout << "请输入第" << i + 1 << "个矩阵：" << endl;
		input_arr(temp, row, column);
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < column; k++) {
				arr_out[j][k] = arr_out[j][k] * temp[j][k];
			}
		}
		vector<vector<int>> temp(row, vector<int>(column, 0));
	}
	//输出结果
	cout << "相乘后的矩阵为：" << endl;
	show_arr(arr_out, row, column);
}