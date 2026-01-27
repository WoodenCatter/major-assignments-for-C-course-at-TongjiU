#include "common.h"

// 黑白字符画
void test1(const char* pic_path, int scale) 
{
    try {
        // 读取图片
        PicReader reader;
        reader.readPic(pic_path);
        Array rgba_arr = reader.getData();
        cout << "图片读取完成：宽=" << rgba_arr.getShape(0) << " 高=" << rgba_arr.getShape(1) << endl;

        // 计算缩放尺寸
        int original_width = rgba_arr.getShape(0);
        int original_height = rgba_arr.getShape(1);
        int out_width = original_width / scale;
        int out_height = original_height / (scale * 2);

        // 生成黑白字符数组
        char* grayChars = new (nothrow) char[out_width * out_height];
        if (grayChars == nullptr) {
            throw runtime_error("内存不足");
        }

        // 字符映射表
        const char asciiStrength[] = { '.', ';', '-', ':', '!', '>', '7', '?', 'C', 'O', '$', 'Q', 'H', 'N', 'M' };
        const int asciiLevel = sizeof(asciiStrength) / sizeof(char);

        // 遍历像素生成字符
        for (int j = 0; j < out_height; ++j) {
            for (int i = 0; i < out_width; ++i) {
                int orig_i = min(i * scale, original_width - 1);
                int orig_j = min(j * scale * 2, original_height - 1);
                unsigned char R = rgba_arr[orig_i][orig_j][0];
                unsigned char G = rgba_arr[orig_i][orig_j][1];
                unsigned char B = rgba_arr[orig_i][orig_j][2];
                double gray_double = 0.299 * R + 0.587 * G + 0.114 * B;
                gray_double = gray_double * 1.2;
                gray_double = max(0.0, min(gray_double, 255.0));
                unsigned char gray = static_cast<unsigned char>(round(gray_double));
                int index = gray / 18;
                index = min(index, asciiLevel - 1);
                int pos = j * out_width + i;
                grayChars[pos] = asciiStrength[index];
            }
        }

        // 拼接、显示字符串
        cout << "\x1b[2J\x1b[H" << flush;
        string full_content;
        for (int j = 0; j < out_height; ++j) {
            string line;
            for (int i = 0; i < out_width; ++i) {
                int pos = j * out_width + i;
                line += "\x1b[38;2;255;255;255m";
                line += grayChars[pos];
                line += "\x1b[0m";
            }
            full_content += line + "\n";
        }
        cout << full_content << flush;

        // 释放内存+等待按键
        delete[] grayChars;
        cout << "\n按任意键继续..." << endl;
        _getch();

    }
    catch (exception& e) {
        // 异常处理（和test1完全一致）
        cout << "出错：" << e.what() << endl;
        _getch();
    }
}