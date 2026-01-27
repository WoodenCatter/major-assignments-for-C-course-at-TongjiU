#include"head.h"

void show_arr(vector<vector<int>>& arr_out, int row, int column)
{
	int max_len = 1;
	int num_len1 = 1;
	for (int j = 0; j < row; j++) {
		for (int k = 0; k < column; k++) {
			for (int l = 10; arr_out[j][k] / l != 0; l *= 10) {
				num_len1++;
			}
			max_len = max(max_len, num_len1);
			num_len1 = 1;
		}
	}
	for (int j = 0; j < row; j++) {
		for (int k = 0; k < column; k++) {
			cout << arr_out[j][k];
			int num_len2 = 1;
			for (int l = 10; arr_out[j][k] / l != 0; l *= 10) {
				num_len2++;
			}
			for (int l = 0; l < max_len - num_len2 + 1; l++) {
				cout << " ";
			}
		}
		cout << endl;
	}
}

//void show_arr(vector<vector<int>>& arr_out, int row, int column)
//{
//	int max_len = 1;
//	for (int j = 0; j < row; j++) {
//		for (int k = 0; k < column; k++) {
//			for (int l = 10; arr_out[j][k] / l != 0; l *= 10) {
//				max_len++;
//			}
//		}
//	}
//	for (int j = 0; j < row; j++) {
//		for (int k = 0; k < column; k++) {
//			cout << arr_out[j][k];
//			int num_len = 1;
//			for (int l = 10; arr_out[j][k] / l != 0; l *= 10) {
//				num_len++;
//			}
//			for (int l = 0; l < max_len - num_len + 1; l++) {
//				cout << " ";
//			}
//		}
//		cout << endl;
//	}
//}

//void show_arr(vector<vector<int>>& arr_out, int row, int column)
//{
//	for (int j = 0; j < row; j++) {
//		for (int k = 0; k < column; k++) {
//			cout << arr_out[j][k] << " ";
//		}
//		cout << endl;
//	}
//}