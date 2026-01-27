#include "common.h"

// 帧数据结构体
struct FrameData {
    vector<ColorChar> chars; // 该帧的字符数组
    int out_w;               // 字符宽度
    int out_h;               // 字符高度
    bool valid;              // 该帧是否有效
};

// 预加载所有帧数据
vector<FrameData> preload_frames(const char* frame_dir, int total_frames, int scale) 
{
    vector<FrameData> frames(total_frames + 1); // 帧索引从1开始
    cout << "开始预加载所有帧数据..." << endl;

    for (int frame_idx = 1; frame_idx <= total_frames; frame_idx++) {
        char frame_path[256];
        sprintf_s(frame_path, sizeof(frame_path), "%s/frame_%04d.jpg", frame_dir, frame_idx);
        FrameData fd;
        fd.valid = false;

        try {
            PicReader reader;
            reader.readPic(frame_path);
            Array rgba_arr = reader.getData();
            if (rgba_arr.getShape(0) == 0 || rgba_arr.getShape(1) == 0) {
                cerr << "帧数据为空：" << frame_path << endl;
                frames[frame_idx] = fd;
                continue;
            }
            int orig_w = rgba_arr.getShape(0);
            int orig_h = rgba_arr.getShape(1);
            fd.out_w = orig_w / scale;
            fd.out_h = orig_h / (scale * 2);
            fd.chars.resize(fd.out_w * fd.out_h);
            const char ascii_strength[] = { '.', ';', '-', ':', '!', '>', '7', '?', 'C', 'O', '$', 'Q', 'H', 'N', 'M' };
            const int ascii_level = sizeof(ascii_strength) / sizeof(char);

            for (int j = 0; j < fd.out_h; j++) {
                for (int i = 0; i < fd.out_w; i++) {
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

                    int pos = j * fd.out_w + i;
                    fd.chars[pos].ch = ascii_strength[char_idx];
                    fd.chars[pos].R = R;
                    fd.chars[pos].G = G;
                    fd.chars[pos].B = B;
                }
            }
            fd.valid = true;
        }
        catch (exception& e) {
            cerr << "预加载帧失败：" << frame_path << " → " << e.what() << endl;
        }

        frames[frame_idx] = fd;
        printf("预加载进度：%d/%d 帧\r", frame_idx, total_frames);
    }

    cout << "\n预加载完成！共处理 " << total_frames << " 帧" << endl;
    return frames;
}

// 彩色字符视频（有声音）
void test4(const char* frame_dir, const char* audio_path, int total_frames, int fps, int scale) 
{
    // 初始化窗口
    int char_width = 10;
    int char_height = 20;
    int win_width = (640 / scale) * char_width;
    int win_height = (360 / (scale * 2)) * char_height;
    initgraph(win_width, win_height);
    setbkcolor(BLACK);
    cleardevice();
    SetConsoleOutputCP(CP_ACP);

    // 音频
    vector<FrameData> frames = preload_frames(frame_dir, total_frames, scale);
    if (_access(audio_path, 0) != -1) {
        BOOL audio_ok = PlaySoundA(audio_path, NULL, SND_FILENAME | SND_ASYNC);
        if (audio_ok) cout << "音频已启动播放" << endl;
        else cerr << "音频播放失败" << endl;
    }
    else {
        cerr << "音频文件不存在：" << audio_path << endl;
    }

    // 控制帧率
    const int frame_delay_ms = 1000 / fps;
    const clock_t start_total = clock();
    bool is_playing = true;
    int current_frame = 1;

    while (current_frame <= total_frames && is_playing) {
        const int target_time_ms = (current_frame - 1) * frame_delay_ms;
        const int current_time_ms = (clock() - start_total) * 1000 / CLOCKS_PER_SEC;
        if (current_time_ms < target_time_ms) {
            const int sleep_ms = target_time_ms - current_time_ms;
            if (sleep_ms > 0) Sleep(sleep_ms);
        }
        while (current_time_ms > (current_frame * frame_delay_ms) && current_frame < total_frames) {
            cout << "追帧：跳过第" << current_frame << "帧（卡顿补偿）" << endl;
            current_frame++;
        }

        // 绘制当前帧
        if (frames[current_frame].valid) {
            FrameData& fd = frames[current_frame];
            BeginBatchDraw();
            cleardevice();
            for (int j = 0; j < fd.out_h; j++) {
                for (int i = 0; i < fd.out_w; i++) {
                    int pos = j * fd.out_w + i;
                    ColorChar& cc = fd.chars[pos];
                    setcolor(RGB(cc.R, cc.G, cc.B));
                    setbkcolor(BLACK);
                    outtextxy(i * char_width, j * char_height, cc.ch);
                }
            }
            EndBatchDraw();
        }

        // 按键退出
        if (_kbhit() && _getch() == 27) {
            is_playing = false;
            PlaySoundA(NULL, NULL, SND_PURGE);
            cout << "\n播放已停止" << endl;
        }

        // 打印进度
        printf("播放进度：%d/%d 帧（%.1f%%） | 理论时间：%dms | 实际时间：%dms\r",
            current_frame, total_frames, (float)current_frame / total_frames * 100,
            target_time_ms, current_time_ms);

        current_frame++;
    }

    // 播放结束
    PlaySoundA(NULL, NULL, SND_PURGE);
    cleardevice();
    setcolor(WHITE);
    outtextxy(win_width / 2 - 80, win_height / 2, _T("播放完成！按任意键退出..."));
    _getch();
    closegraph();
    cout << "\n播放结束，音频已关闭" << endl;
}