#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

// Array类定义
class Array
{
public:
    template <typename... Args>
    Array(Args... args)
    {
        data = nullptr;
        index = 0;
        axisNum = sizeof...(args);
        nowAxis = 0;
        memset(shape, 0, sizeof(shape));

        size_t list[] = { static_cast<size_t>(args)... };
        for (int i = 0; i < axisNum; ++i)
        {
            shape[i] = static_cast<int>(list[i]);
        }

        int total = 1;
        for (int i = 0; i < axisNum; ++i)
        {
            total *= shape[i];
        }
        data = new unsigned char[total]();
    }

    // 拷贝构造
    Array(const Array& other)
    {
        axisNum = other.axisNum;
        nowAxis = other.nowAxis;
        index = other.index;
        memcpy(shape, other.shape, sizeof(shape));

        // 计算总元素数
        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];
        data = new unsigned char[total];
        memcpy(data, other.data, total * sizeof(unsigned char));
    }

    // 析构函数
    ~Array()
    {
        if (data != nullptr)
        {
            if (nowAxis == 0) delete[] data;
            data = nullptr;
        }
    }

    // 赋值运算符重载
    Array& operator=(const Array& other)
    {
        if (this == &other) return *this;
        if (data != nullptr && nowAxis == 0) delete[] data;
        axisNum = other.axisNum;
        nowAxis = other.nowAxis;
        index = other.index;
        memcpy(shape, other.shape, sizeof(shape));
        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];
        data = new unsigned char[total];
        memcpy(data, other.data, total * sizeof(unsigned char));
        return *this;
    }

    // at函数：支持多维索引，返回子数组/元素
    template <typename... Args>
    Array at(Args... args)
    {
        int argsList[] = { static_cast<int>(args)... };
        int argsCount = sizeof...(args);

        if (argsCount > axisNum - nowAxis)
        {
            throw out_of_range("at(): 索引数量超过剩余维度");
        }

        int offset = index;
        int currentAxis = nowAxis;
        for (int i = 0; i < argsCount; ++i)
        {
            if (argsList[i] < 0 || argsList[i] >= shape[currentAxis])
            {
                throw out_of_range("at(): 索引越界");
            }

            int stride = 1;
            for (int j = currentAxis + 1; j < axisNum; ++j)
            {
                stride *= shape[j];
            }
            offset += argsList[i] * stride;
            currentAxis++;
        }

        Array subArray;
        subArray.data = this->data;
        subArray.index = offset;
        subArray.axisNum = this->axisNum;
        subArray.nowAxis = currentAxis;
        memcpy(subArray.shape, this->shape, sizeof(shape));

        return subArray;
    }

    // at函数const版本
    template <typename... Args>
    Array at(Args... args) const
    {
        int argsList[] = { static_cast<int>(args)... };
        int argsCount = sizeof...(args);

        if (argsCount > axisNum - nowAxis)
        {
            throw out_of_range("at(): 索引数量超过剩余维度");
        }

        int offset = index;
        int currentAxis = nowAxis;
        for (int i = 0; i < argsCount; ++i)
        {
            if (argsList[i] < 0 || argsList[i] >= shape[currentAxis])
            {
                throw out_of_range("at(): 索引越界");
            }

            int stride = 1;
            for (int j = currentAxis + 1; j < axisNum; ++j)
            {
                stride *= shape[j];
            }
            offset += argsList[i] * stride;
            currentAxis++;
        }

        Array subArray;
        subArray.data = this->data;
        subArray.index = offset;
        subArray.axisNum = this->axisNum;
        subArray.nowAxis = currentAxis;
        memcpy(subArray.shape, this->shape, sizeof(shape));

        return subArray;
    }

    // 重载[]操作符
    Array operator[](int idx)
    {
        return this->at(idx);
    }

    // 重载[]操作符const版本
    Array operator[](int idx) const
    {
        return this->at(idx);
    }

    // set函数：给指定位置赋值
    void set(unsigned char value)
    {
        if (nowAxis != axisNum)
        {
            throw logic_error("set(): 仅能给单个元素赋值");
        }
        data[index] = value;
    }

    // reshape函数：修改数组形状
    template <typename... Args>
    void reshape(Args... args)
    {
        if (nowAxis != 0)
        {
            throw logic_error("reshape(): 仅根数组可执行reshape");
        }

        int newShape[] = { static_cast<int>(args)... };
        int newAxisNum = sizeof...(args);

        int oldTotal = 1;
        for (int i = 0; i < axisNum; ++i) oldTotal *= shape[i];

        int newTotal = 1;
        for (int i = 0; i < newAxisNum; ++i) newTotal *= newShape[i];

        if (oldTotal != newTotal)
        {
            throw invalid_argument("reshape(): 元素总数不匹配");
        }

        axisNum = newAxisNum;
        memset(shape, 0, sizeof(shape));
        for (int i = 0; i < newAxisNum; ++i)
        {
            shape[i] = newShape[i];
        }
    }

    // 获取底层数据指针
    unsigned char* get_content() const
    {
        return data;
    }

    // 赋值运算符：给单个元素赋值
    Array& operator=(unsigned char value)
    {
        if (nowAxis != axisNum)
        {
            throw logic_error("operator=: 仅能给单个元素赋值");
        }
        data[index] = value;
        return *this;
    }

    // 非const版本（修改数组后取值）
    operator unsigned char()
    {
        if (nowAxis != axisNum)
        {
            throw logic_error("operator unsigned char: 仅能获取单个元素值");
        }
        return data[index];
    }

    // 
    operator unsigned char() const
    {
        if (nowAxis != axisNum)
        {
            throw logic_error("operator unsigned char: 仅能获取单个元素值");
        }
        return data[index];
    }

    // 矩阵运算
    Array operator+(const Array& other) const
    {
        if (axisNum != other.axisNum)
        {
            throw invalid_argument("operator+: 维度数不匹配");
        }
        for (int i = 0; i < axisNum; ++i)
        {
            if (shape[i] != other.shape[i])
            {
                throw invalid_argument("operator+: 形状不匹配");
            }
        }

        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] + other.data[i];
        }

        return result;
    }

    Array operator+(unsigned char value) const
    {
        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] + value;
        }

        return result;
    }

    Array operator-(const Array& other) const
    {
        if (axisNum != other.axisNum) throw invalid_argument("operator-: 维度数不匹配");
        for (int i = 0; i < axisNum; ++i)
            if (shape[i] != other.shape[i]) throw invalid_argument("operator-: 形状不匹配");

        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] - other.data[i];
        }

        return result;
    }

    Array operator-(unsigned char value) const
    {
        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] - value;
        }

        return result;
    }

    Array operator*(const Array& other) const
    {
        if (axisNum != other.axisNum) throw invalid_argument("operator*: 维度数不匹配");
        for (int i = 0; i < axisNum; ++i)
            if (shape[i] != other.shape[i]) throw invalid_argument("operator*: 形状不匹配");

        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] * other.data[i];
        }

        return result;
    }

    Array operator*(unsigned char value) const
    {
        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] * value;
        }

        return result;
    }

    Array operator/(const Array& other) const
    {
        if (axisNum != other.axisNum) throw invalid_argument("operator/: 维度数不匹配");
        for (int i = 0; i < axisNum; ++i)
            if (shape[i] != other.shape[i]) throw invalid_argument("operator/: 形状不匹配");

        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            if (other.data[i] == 0) throw runtime_error("operator/: 除数为0");
            result.data[i] = this->data[i] / other.data[i];
        }

        return result;
    }

    Array operator/(unsigned char value) const
    {
        if (value == 0) throw runtime_error("operator/: 除数为0");

        int total = 1;
        for (int i = 0; i < axisNum; ++i) total *= shape[i];

        Array result;
        result.axisNum = axisNum;
        result.nowAxis = 0;
        memcpy(result.shape, shape, sizeof(shape));
        result.data = new unsigned char[total];

        for (int i = 0; i < total; ++i)
        {
            result.data[i] = this->data[i] / value;
        }

        return result;
    }

    // 维度获取函数
    int getShape(int index) const
    {
        if (index < 0 || index >= axisNum)
        {
            throw out_of_range("getShape(): 维度索引越界");
        }
        return shape[index];
    }

    int getAxisNum() const
    {
        return axisNum;
    }

private:
    Array() : data(nullptr), index(0), axisNum(0), nowAxis(0)
    {
        memset(shape, 0, sizeof(shape));
    }

    unsigned char* data;       // 适配像素（0-255）和字符存储
    int index;                 // 当前位置在一维数组中的偏移
    int shape[16];             // 各维度大小
    int axisNum;               // 总维度数
    int nowAxis;               // 当前操作的维度
};

#endif