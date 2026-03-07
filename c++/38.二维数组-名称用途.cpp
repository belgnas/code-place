//二维数组-名称用途

//作用：
//1.可以查看二维数组所占用内存空间
//2.获取二维数组首地址

#include<iostream>
using namespace std;

int main()
{
    int arr[2][3] =
    //这里的int可以改成其他的，但是内存空间就会变化，比如说double，内存空间翻倍
    {
        {1,2,3},
        {4,5,6}
    };
    //1.可以查看二维数组所占用内存空间 以及行数，列数和元素总数
    cout << "二维数组所占用的内存空间为：" << sizeof(arr) << endl;
    cout << "二维数组第一行占用的内存空间为：" <<sizeof(arr[0])<<endl;
    cout << "二维数组第一个元素占用的内存空间为：" <<sizeof(arr[0][0])<<endl;

    cout << "二维数组行数为：" <<sizeof(arr) / sizeof(arr[0])<<endl;
    cout << "二维数组列数为：" <<sizeof(arr[0]) / sizeof(arr[0][0])<<endl;
    cout << "二维数组元素总数为：" <<sizeof(arr) / sizeof(arr[0][0])<<endl;

    //2.获取二维数组首地址
    cout << "二维数组的默认16进制的首地址为：" << arr << endl;
    //下面使用long long是因为长度超了
    //ps:&是取址符，若是需要查看具体元素的地址，必须要加&
    cout << "二维数组的10进制的首地址为：" << (long long)arr << endl;
    cout << "二维数组第一行的10进制的首地址为：" << (long long)arr[0] << endl;
    cout << "二维数组第二行的10进制的首地址为：" << (long long)arr[1] << endl;
    cout << "二维数组第一个元素的10进制的首地址为：" << (long long)&arr[0][0] << endl;
    cout << "二维数组第二个元素的10进制的首地址为：" << (long long)&arr[0][1] << endl;

    system("pause");

    return 0;   
}