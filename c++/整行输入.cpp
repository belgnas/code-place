//getline(cin,s)

/*
在 C++ 中，getline(cin, s)是一个用于从标准输入流（通常是键盘输入）读取一行文本并存储到字符串s中的函数调用。

以下是对其详细解释：

一、函数作用
getline是一个通用的函数，用于从输入流中读取字符序列直到遇到特定的结束条件。
在这个特定的调用中，cin是标准输入流对象，s是一个std::string类型的字符串对象。该函数会从标准输入读取字符，直到遇到换行符（'\n'）为止，并将读取到的字符序列（不包括换行符）存储到s中。

二、与其他输入方式的区别
与cin >> s相比：
cin >> s通常会读取输入直到遇到空白字符（如空格、制表符、换行符）为止，然后将读取到的内容存储到s中，但不会读取空白字符本身。
getline(cin, s)会读取一整行的内容，包括空白字符，直到遇到换行符。

三、使用示例
以下是一个使用getline(cin, s)的示例代码：*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cout << "Enter a line of text: ";
    getline(cin, s);
    cout << "You entered: " << s << endl;
    return 0;
}
//在这个例子中，程序提示用户输入一行文本，然后使用getline(cin, s)读取输入并存储到s中，最后输出用户输入的内容。