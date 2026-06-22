#include <iostream>

int main() {
    #if defined(__GNUC__)
        std::cout << "GCC version: " << __GNUC__ << "." 
                  << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
    #elif defined(__clang__)
        std::cout << "Clang version: " << __clang_major__ << "." 
                  << __clang_minor__ << "." << __clang_patchlevel__ << std::endl;
    #elif defined(_MSC_VER)
        // _MSC_VER 的值格式为 MMNN，例如 1939 表示 Visual Studio 2022
        std::cout << "MSVC _MSC_VER: " << _MSC_VER << std::endl;
        // _MSC_FULL_VER 的值格式为 MMNNBBBBB，包含更详细的内部版本号
        // std::cout << "MSVC _MSC_FULL_VER: " << _MSC_FULL_VER << std::endl;
    #else
        std::cout << "Unknown compiler" << std::endl;
    #endif
    return 0;
}