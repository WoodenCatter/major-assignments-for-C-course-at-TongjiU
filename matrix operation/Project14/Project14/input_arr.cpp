#include"head.h"

void input_arr(vector<vector<int>>& temp ,int row,int column)
{
	for (int j = 0; j < row; j++) {
		for (int k = 0; k < column; k++) {
			cin >> temp[j][k];
			if (cin.fail()) {
				cout << "输入错误（可能是输入整数超限或输入非整数）！请再次输入：" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				k--;
			}
		}
	}
}