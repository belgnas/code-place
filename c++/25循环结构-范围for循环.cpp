//循环结构-范围for循环

//可以简洁地遍历容器、数组和字符串


#include<iostream>
#include<string>
using namespace std;
int main()
{
    //普通数组
    //简洁地遍历普通数组，无需关心数组的大小。
    //例如：
    int arr[] = {10, 20, 30, 40, 50};
    for(int num : arr)
    {
        cout << num << " ";
    }

    cout << endl;


    //二维数组
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (const auto& row : matrix/*这里填名字*/) 
    //解释：const固定变量为常量；auto是自动类型推导的关键字；row是声明后面的row是引用，不是定义
/*  ai的回答：
    const auto& row：
    const： 表示row是一个常量引用，即在循环体内不能修改row所引用的内容。这确保了在遍历二维数组时不会意外地修改数组中的数据，增加了代码的安全性。
    auto：  让编译器自动推断row的类型。在这个例子中，由于matrix是一个二维数组，row的类型会被自动推导为一维数组的引用。例如，如果matrix是int[3][3]类型，那么row的类型就是int[3]&。
    &：     表示row是一个引用，而不是一个副本。这意味着row直接绑定到matrix中的每一行，而不是创建一个新的一维数组副本。这样可以避免不必要的数组拷贝，提高代码的效率。
    matrix：这指定了要遍历的对象是二维数组matrix。
*/  {
        for (int num : row)
        {
            cout << num << " ";
        }
       cout << endl;
    }


    //遍历字符串
    string str = "Hello, World!";
    for (char c : str) //一个一个的遍历字符串中的每个字符
    {
        cout << c << " ";
    }
    cout << endl;


    //遍历向量（std::vector）
    //未学
/*
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    for (int value : vec) {
        std::cout << value << " ";
    }
    return 0;
}
*/


    //遍历自定义类型容器（如果支持迭代器）
    //未学
/*
struct MyStruct {
    int data;
};

int main() {
    std::vector<MyStruct> customContainer = {{1}, {2}, {3}};
    for (const MyStruct& element : customContainer) {
        std::cout << element.data << " ";
    }
    return 0;
}
*/

   return 0;
}