#include"head.h"

void super_input_arr_16(int arr[], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			while (!(cin >> arr[i * col + j])) {
				cout << "输入错误（可能是输入整数超限或输入非整数）！请再次输入：" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
}

void super_show_arr(int arr[], int row, int column) {
    int max_len = 1;
    for (int i = 0; i < row * column; i++) {
        int len = 1;
        for (int l = 10; arr[i] / l != 0; l *= 10) len++;
        if (len > max_len) max_len = len;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            int val = arr[i * column + j];
            cout << val;
            int len = 1;
            for (int l = 10; val / l != 0; l *= 10) len++;
            for (int k = 0; k < max_len - len + 1; k++) cout << " ";
        }
        cout << endl;
    }
}

void super_conv() {
	const int max_size = 10000;
	const int kernel_size = 3;
	const int padding = 1;
	int size_a;
	cout << "请输入矩阵A的大小：";
	while (cin >> size_a) {
		if (cin.fail() || size_a < 1 || size_a * size_a > max_size / 4) {
			cout << "输入错误（输入不满足要求或超出容量限制）！请再次输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else break;
	}

	int A[max_size] = { 0 };
	int B[kernel_size * kernel_size] = { 0 };
	int A_padding[max_size] = { 0 };
	int C[max_size] = { 0 };

	cout << "请输入矩阵A：" << endl;
	super_input_arr_16(A, size_a, size_a);

	cout << "请输入卷积核3*3矩阵B：" << endl;
	super_input_arr_16(B, kernel_size, kernel_size);

	int size_pad = size_a + 2 * padding;

	for (int i = 0; i < size_a; i++) {
		for (int j = 0; j < size_a; j++) {
			A_padding[(i + padding) * size_pad + (j + padding)] = A[i * size_a + j];
		}
	}

	int size_C = size_pad - kernel_size + 1;

	for (int i = 0; i < size_C; i++) {
		for (int j = 0; j < size_C; j++) {
			int sum = 0;
			for (int k = 0; k < kernel_size; k++) {
				for (int l = 0; l < kernel_size; l++) {
					sum += A_padding[(i + k) * size_pad + (j + l)] * B[k * kernel_size + l];
				}
			}
			C[i * size_C + j] = sum;
		}
	}

	cout << "卷积后的矩阵为：" << endl;
	super_show_arr(C, size_C, size_C);
}