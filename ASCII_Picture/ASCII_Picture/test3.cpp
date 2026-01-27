#include "common.h"

// 彩色字符视频（没声音）
void test3(const char* frame_dir, int total_frames, int fps, int scale) 
{
    // 16:9
    int char_width = 10;   // 单个字符宽度
    int char_height = 20;  // 单个字符高度
    int win_width = (640 / scale) * char_width;   // 窗口宽度（640/8*10=800）
    int win_height = (360 / (scale * 2)) * char_height; // 窗口高度（360/16*20=450）
    initgraph(win_width, win_height);
    setbkcolor(BLACK);
    cleardevice();
    SetConsoleOutputCP(CP_ACP);

    // 帧率控制参数
    int frame_delay_ms = 1000 / fps; // 每帧理论延迟
    bool is_playing = true; // 播放状态标记

    // 逐帧播放核心循环
    for (int frame_idx = 1; frame_idx <= total_frames && is_playing; frame_idx++) {
        clock_t frame_start = clock();
        char frame_path[256];
        sprintf_s(frame_path, sizeof(frame_path), "%s/frame_%04d.jpg", frame_dir, frame_idx);
        PicReader reader;
        try {
            reader.readPic(frame_path);
        }
        catch (exception& e) {
            cerr << "读取帧失败：" << frame_path << " → " << e.what() << endl;
            continue;
        }
        Array rgba_arr = reader.getData();
        if (rgba_arr.getShape(0) == 0 || rgba_arr.getShape(1) == 0) {
            cerr << "帧图片数据为空：" << frame_path << endl;
            continue;
        }
        int orig_w = rgba_arr.getShape(0);
        int orig_h = rgba_arr.getShape(1);
        int out_w = orig_w / scale;
        int out_h = orig_h / (scale * 2);
        ColorChar* color_chars = new (nothrow) ColorChar[out_w * out_h];
        if (color_chars == nullptr) {
            cerr << "内存不足，无法生成字符数组" << endl;
            continue;
        }
        const char ascii_strength[] = { '.', ';', '-', ':', '!', '>', '7', '?', 'C', 'O', '$', 'Q', 'H', 'N', 'M' };
        const int ascii_level = sizeof(ascii_strength) / sizeof(char);

        // 生成彩色字符
        for (int j = 0; j < out_h; j++) {
            for (int i = 0; i < out_w; i++) {
                int pix_i = min(i * scale, orig_w - 1);
                int pix_j = min(j * scale * 2, orig_h - 1);
                unsigned char R = rgba_arr[pix_i][pix_j][0];
                unsigned char G = rgba_arr[pix_i][pix_j][1];
                unsigned char B = rgba_arr[pix_i][pix_j][2];
                double gray = 0.299 * R + 0.587 * G + 0.114 * B;
                gray = gray * 1.2;
                gray = max(0.0, min(gray, 255.0));
                unsigned char gray_u8 = static_cast<unsigned char>(round(gray));
                int char_idx = gray_u8 / 18;
                char_idx = min(char_idx, ascii_level - 1);
                int pos = j * out_w + i;
                color_chars[pos].ch = ascii_strength[char_idx];
                color_chars[pos].R = R;
                color_chars[pos].G = G;
                color_chars[pos].B = B;
            }
        }

        // 绘制字符画
        BeginBatchDraw();
        cleardevice();
        for (int j = 0; j < out_h; j++) {
            for (int i = 0; i < out_w; i++) {
                int pos = j * out_w + i;
                ColorChar& cc = color_chars[pos];
                setcolor(RGB(cc.R, cc.G, cc.B));
                setbkcolor(BLACK);
                outtextxy(i * char_width, j * char_height, cc.ch);
            }
        }
        EndBatchDraw();

        // 释放内存
        delete[] color_chars;

        // 补足延迟
        clock_t frame_cost = clock() - frame_start;
        int sleep_ms = frame_delay_ms - (frame_cost * 1000 / CLOCKS_PER_SEC);
        if (sleep_ms > 0) {
            Sleep(sleep_ms);
        }

        // 退出播放
        if (_kbhit()) {  // 检测是否有按键
            char key = _getch();
            if (key == 27) {  // ESC 键（ASCII 27）
                is_playing = false;
                cout << "\n播放已手动停止" << endl;
            }
        }

        // 打印播放进度
        printf("播放进度：%d/%d 帧（%.1f%%）\r", frame_idx, total_frames, (float)frame_idx / total_frames * 100);
    }

    // 播放结束处理
    cleardevice();
    setcolor(WHITE);
    outtextxy(win_width / 2 - 80, win_height / 2, _T("播放完成！按任意键退出..."));
    _getch();
    closegraph();
    cout << "\n播放结束" << endl;
}