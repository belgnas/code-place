// Utils.cpp — 通用工具函数实现

#include"Utils.h"
#include<iostream>
#include<sstream>
#include<algorithm>
#include<limits>

namespace Utils
{

std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

std::string trim(const std::string& str)
{
    // 找到第一个非空白字符
    auto start = std::find_if_not(str.begin(), str.end(),
        [](unsigned char ch) { return std::isspace(ch); });

    // 找到最后一个非空白字符
    auto end = std::find_if_not(str.rbegin(), str.rend(),
        [](unsigned char ch) { return std::isspace(ch); }).base();

    return (start < end) ? std::string(start, end) : std::string();
}

int readInt(const std::string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        std::cout << prompt << " (" << min << "-" << max << "): ";
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [!] 请输入有效整数！" << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < min || value > max)
        {
            std::cout << "  [!] 请输入 " << min << " 到 " << max << " 之间的值！" << std::endl;
            continue;
        }

        return value;
    }
}

double readDouble(const std::string& prompt, double min, double max)
{
    double value;
    while (true)
    {
        std::cout << prompt << " (" << min << "-" << max << "): ";
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [!] 请输入有效数字！" << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < min || value > max)
        {
            std::cout << "  [!] 请输入 " << min << " 到 " << max << " 之间的值！" << std::endl;
            continue;
        }

        return value;
    }
}

void pause()
{
    std::cout << "\n按 Enter 键继续...";
    std::cin.get();
}

} // namespace Utils
