#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "PicReader.h"

// 自定义数学函数
template<typename T>
T myMax(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T myMin(T a, T b) {
    return (a < b) ? a : b;
}

float myAbs(float x) {
    return (x < 0) ? -x : x;
}

int myRound(float value) {
    return (value >= 0) ? (int)(value + 0.5f) : (int)(value - 0.5f);
}

// PNG编码器
class PNGEncoder {
private:
    unsigned long crc32(const unsigned char* buf, int len) {
        static unsigned long crc_table[256];
        static int crc_table_computed = 0;

        if (!crc_table_computed) {
            for (int i = 0; i < 256; i++) {
                unsigned long c = i;
                for (int k = 0; k < 8; k++) {
                    if (c & 1)
                        c = 0xedb88320L ^ (c >> 1);
                    else
                        c = c >> 1;
                }
                crc_table[i] = c;
            }
            crc_table_computed = 1;
        }

        unsigned long c = 0xffffffffL;
        for (int i = 0; i < len; i++) {
            c = crc_table[(c ^ buf[i]) & 0xff] ^ (c >> 8);
        }
        return c ^ 0xffffffffL;
    }

    void writeChunk(std::ofstream& file, const std::string& type, const std::vector<unsigned char>& data) {
        unsigned int length = data.size();
        unsigned char len[4];
        len[0] = (length >> 24) & 0xff;
        len[1] = (length >> 16) & 0xff;
        len[2] = (length >> 8) & 0xff;
        len[3] = length & 0xff;
        file.write((char*)len, 4);

        file.write(type.c_str(), 4);

        if (length > 0) {
            file.write((char*)data.data(), length);
        }

        std::vector<unsigned char> crc_data(4 + length);
        memcpy(crc_data.data(), type.c_str(), 4);
        if (length > 0) {
            memcpy(crc_data.data() + 4, data.data(), length);
        }
        unsigned long crc = crc32(crc_data.data(), 4 + length);

        unsigned char crc_bytes[4];
        crc_bytes[0] = (crc >> 24) & 0xff;
        crc_bytes[1] = (crc >> 16) & 0xff;
        crc_bytes[2] = (crc >> 8) & 0xff;
        crc_bytes[3] = crc & 0xff;
        file.write((char*)crc_bytes, 4);
    }

    void deflateStore(const std::vector<unsigned char>& input, std::vector<unsigned char>& output) {
        output.clear();

        output.push_back(0x78);
        output.push_back(0x01);

        size_t pos = 0;
        size_t remaining = input.size();

        while (remaining > 0) {
            size_t block_len = (remaining > 65535) ? 65535 : remaining;
            bool final_block = (remaining <= 65535);

            output.push_back(final_block ? 0x01 : 0x00);
            output.push_back(block_len & 0xff);
            output.push_back((block_len >> 8) & 0xff);
            output.push_back((~block_len) & 0xff);
            output.push_back(((~block_len) >> 8) & 0xff);

            for (size_t i = 0; i < block_len; i++) {
                output.push_back(input[pos + i]);
            }

            pos += block_len;
            remaining -= block_len;
        }

        output.push_back(0x00);
        output.push_back(0x00);
        output.push_back(0x00);
        output.push_back(0x01);
    }

public:
    bool encode(const char* filename, const unsigned char* image, int width, int height) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        const unsigned char png_header[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
        file.write((char*)png_header, 8);

        std::vector<unsigned char> ihdr_data(13);
        ihdr_data[0] = (width >> 24) & 0xff;
        ihdr_data[1] = (width >> 16) & 0xff;
        ihdr_data[2] = (width >> 8) & 0xff;
        ihdr_data[3] = width & 0xff;
        ihdr_data[4] = (height >> 24) & 0xff;
        ihdr_data[5] = (height >> 16) & 0xff;
        ihdr_data[6] = (height >> 8) & 0xff;
        ihdr_data[7] = height & 0xff;
        ihdr_data[8] = 8;
        ihdr_data[9] = 6;
        ihdr_data[10] = 0;
        ihdr_data[11] = 0;
        ihdr_data[12] = 0;

        writeChunk(file, "IHDR", ihdr_data);

        std::vector<unsigned char> image_data;
        for (int y = 0; y < height; y++) {
            image_data.push_back(0);
            for (int x = 0; x < width; x++) {
                int idx = (y * width + x) * 4;
                image_data.push_back(image[idx]);
                image_data.push_back(image[idx + 1]);
                image_data.push_back(image[idx + 2]);
                image_data.push_back(image[idx + 3]);
            }
        }

        std::vector<unsigned char> compressed_data;
        deflateStore(image_data, compressed_data);

        writeChunk(file, "IDAT", compressed_data);
        writeChunk(file, "IEND", std::vector<unsigned char>());

        file.close();
        return true;
    }
};

// 图像缩放类
class ImageScaler {
public:
    void downsample(const BYTE* input, UINT inputWidth, UINT inputHeight,
        std::vector<BYTE>& output, UINT& outputWidth, UINT& outputHeight,
        float scaleFactor) {

        outputWidth = static_cast<UINT>(inputWidth * scaleFactor);
        outputHeight = static_cast<UINT>(inputHeight * scaleFactor);

        if (outputWidth < 1) outputWidth = 1;
        if (outputHeight < 1) outputHeight = 1;

        output.resize(outputWidth * outputHeight * 4);

        for (UINT y = 0; y < outputHeight; y++) {
            for (UINT x = 0; x < outputWidth; x++) {
                float srcX = x / scaleFactor;
                float srcY = y / scaleFactor;

                BYTE r, g, b, a;
                bilinearInterpolate(input, inputWidth, inputHeight, srcX, srcY, r, g, b, a);

                UINT idx = (y * outputWidth + x) * 4;
                output[idx] = r;
                output[idx + 1] = g;
                output[idx + 2] = b;
                output[idx + 3] = a;
            }
        }
    }

private:
    void bilinearInterpolate(const BYTE* input, UINT width, UINT height,
        float x, float y, BYTE& r, BYTE& g, BYTE& b, BYTE& a) {
        int x1 = static_cast<int>(x);
        int y1 = static_cast<int>(y);
        int x2 = x1 + 1;
        int y2 = y1 + 1;

        x1 = myMax(0, myMin(static_cast<int>(width) - 1, x1));
        y1 = myMax(0, myMin(static_cast<int>(height) - 1, y1));
        x2 = myMax(0, myMin(static_cast<int>(width) - 1, x2));
        y2 = myMax(0, myMin(static_cast<int>(height) - 1, y2));

        float dx = x - x1;
        float dy = y - y1;
        float dx1 = 1.0f - dx;
        float dy1 = 1.0f - dy;

        UINT idx11 = (y1 * width + x1) * 4;
        UINT idx12 = (y1 * width + x2) * 4;
        UINT idx21 = (y2 * width + x1) * 4;
        UINT idx22 = (y2 * width + x2) * 4;

        r = static_cast<BYTE>(dx1 * dy1 * input[idx11] + dx * dy1 * input[idx12] +
            dx1 * dy * input[idx21] + dx * dy * input[idx22]);
        g = static_cast<BYTE>(dx1 * dy1 * input[idx11 + 1] + dx * dy1 * input[idx12 + 1] +
            dx1 * dy * input[idx21 + 1] + dx * dy * input[idx22 + 1]);
        b = static_cast<BYTE>(dx1 * dy1 * input[idx11 + 2] + dx * dy1 * input[idx12 + 2] +
            dx1 * dy * input[idx21 + 2] + dx * dy * input[idx22 + 2]);
        a = static_cast<BYTE>(dx1 * dy1 * input[idx11 + 3] + dx * dy1 * input[idx12 + 3] +
            dx1 * dy * input[idx21 + 3] + dx * dy * input[idx22 + 3]);
    }
};

// 压缩类
class Compressor {
private:
    ImageScaler scaler;

public:
    bool compressToPNG(const BYTE* inputData, UINT width, UINT height, const char* outputFilename) {
        std::vector<BYTE> scaledData;
        UINT scaledWidth, scaledHeight;
        scaler.downsample(inputData, width, height, scaledData, scaledWidth, scaledHeight, 0.5f);

        PNGEncoder encoder;
        return encoder.encode(outputFilename, scaledData.data(), scaledWidth, scaledHeight);
    }
};

// 自定义数据格式读取类
class DataReader {
public:
    bool readAndShow(const char* filename) {
        PicReader reader;
        reader.readPic(filename);
        BYTE* data = nullptr;
        UINT width, height;
        reader.getData(data, width, height);
        reader.showPic(data, width, height);
        delete[] data;
        return true;
    }
};

// 命令行参数处理
void printUsage() {
    std::cout << "指令错误！请输入：" << std::endl;
	std::cout << "1. 压缩模式: Picture_Compression -compress lena.tiff" << std::endl;
	std::cout << "2. 读取模式: Picture_Compression -read lena.png" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    std::string filename = argv[2];

    if (command == "-compress") {
        // 压缩模式
        PicReader imread;
        BYTE* data = nullptr;
        UINT x, y;

        imread.readPic(filename.c_str());
        imread.getData(data, x, y);

        Compressor compressor;
        bool success = compressor.compressToPNG(data, x, y, "lena.png");

        if (success) {
            std::cout << "压缩成功: lena.tiff -> lena.png" << std::endl;
        }
        else {
            std::cout << "压缩失败!" << std::endl;
        }

        delete[] data;
    }
    else if (command == "-read") {
        // 读取模式
        DataReader reader;
        reader.readAndShow(filename.c_str());
    }
    else {
        printUsage();
        return 1;
    }

    return 0;
}