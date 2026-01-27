#include"head.h"

void  matrimulti()
{
	//输入矩阵
	cout << "请输入第一个矩阵的行数和列数：";
	int row1, column1, row2, column2;
	while (true) {
		cin >> row1 >> column1;
		if (cin.fail() || row1 <= 0 || column1 <= 0) {
			cout << "请输入大于0的整数！请重新输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}
	vector<vector<int>> temp1(row1, vector<int>(column1, 0));
	cout << "请输入第一个矩阵：" << endl;
	input_arr(temp1, row1, column1);
	cout << "请输入第二个矩阵的行数和列数：";
	while (true) {
		cin >> row2 >> column2;
		if (cin.fail() || row2 <= 0 || column2 <= 0 || row2 != column1) {
			cout << "请输入大于0的整数，且且第二个矩阵的行数要等于第一个矩阵的列数！请重新输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}
	vector<vector<int>> temp2(row2, vector<int>(column2, 0));
	cout << "请输入第二个矩阵：" << endl;
	input_arr(temp2, row2, column2);
	vector<vector<int>> arr_out(row1, vector<int>(column2, 0));
	//相乘
	for (int j = 0; j < row1; j++) {
		for (int l = 0; l < column1; l++) {
			for (int k = 0; k < column2; k++) {
				arr_out[j][k] += temp1[j][l] * temp2[l][k];
			}
		}
	}
	//输出结果
	cout << "相乘后的矩阵为：" << endl;
	show_arr(arr_out, row1, column2);
}