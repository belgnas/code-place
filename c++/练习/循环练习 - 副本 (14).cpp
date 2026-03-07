#include<iostream>
#include<string>//方法1要用到
using namespace std;

int main()
{
    //方法1：
    string title;
    int a = 0;

    getline(cin, title);

    for(int i=0; i<title.length(); i++)
    {
        if(title[i]!=' ')
        {
            a++;
        }
    }

    cout << a << endl;



    /*
    方法2：

    char s;
    int n = 0;
    while(cin.get(s))
    {
        if(s=='\n')
        {
            break;
        };
        if(s!=' ')
        {
            n++;
        }
    }
    cout << n <<endl;

    */
    return 0;
}

//两种方法的比较
//方法 1 使用std::string和getline函数，更加方便地读取一整行文本，然后通过遍历字符串的方式统计非空格字符数量。这种方法适用于处理较长的字符串，并且代码相对简洁。
//方法 2 使用单个字符读取的方式，通过循环逐个读取字符并判断是否为非空格字符来统计数量。这种方法相对比较底层，适用于需要逐个处理字符的情况，但代码相对复杂一些。
//总的来说，两种方法都可以实现统计非空格字符数量的功能，可以根据具体的需求选择使用哪种方法。