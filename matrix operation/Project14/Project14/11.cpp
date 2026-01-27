#include "head.h"

void super_input_arr_11(int arr[], int row, int col) {
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

void super_show_arr_11(int arr[], int row, int column) {
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

void supermatriplus() {
    int amount;
    const int max_size = 10000;
    cout << "请输入一共有几个矩阵需要相加：";
    cin >> amount;
    if (cin.fail() || amount < 2) {
        cout << "请输入一个大于等于2的整数！" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    int row, column;
    cout << "请输入矩阵的行数和列数：";
    cin >> row >> column;
    if (cin.fail() || row <= 0 || column <= 0 || row * column > max_size) {
        cout << "请输入有效的矩阵尺寸（最大100x100）！" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    int result[max_size] = { 0 };
    int temp[max_size] = { 0 };

    for (int m = 0; m < amount; ++m) {
        cout << "请输入第 " << m + 1 << " 个矩阵（共 " << row * column << " 个数）：" << endl;
        super_input_arr_11(temp, row, column);
        for (int i = 0; i < row * column; ++i) {
            result[i] += temp[i];
        }
    }

    cout << "相加后的矩阵为：" << endl;
    super_show_arr_11(result, row, column);
}