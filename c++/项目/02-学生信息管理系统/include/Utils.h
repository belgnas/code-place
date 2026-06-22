// Utils.h — 通用工具函数

#pragma once
#include<string>
#include<vector>

namespace Utils
{
    // 按分隔符拆分字符串
    std::vector<std::string> split(const std::string& str, char delimiter);

    // 去除字符串首尾空白
    std::string trim(const std::string& str);

    // 安全读取整数（带重试）
    int readInt(const std::string& prompt, int min = 0, int max = 150);

    // 安全读取浮点数
    double readDouble(const std::string& prompt, double min = 0.0, double max = 100.0);

    // 暂停等待用户回车
    void pause();
}
