#pragma once
#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <mmsystem.h>
#include <io.h>
#include <iostream>
#include <string>
#include <vector>
#include "Array.h"
#include "PicReader.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

// ²ÊÉ«×Ö·û
struct ColorChar {
    char ch;
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

void test1(const char* pic_path, int scale = 8);

void test2(const char* pic_path, int scale = 8);

void test3(const char* frame_dir, int total_frames, int fps = 15, int scale = 8);

void test4(const char* frame_dir, const char* audio_path, int total_frames, int fps = 15, int scale = 8);