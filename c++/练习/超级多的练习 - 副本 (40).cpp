#include <iostream>
#include <vector>

using namespace std;

// 高精度加法函数，用于计算两个大整数的和，大整数以vector<int>形式存储，每个元素表示一位数字（从低位到高位）
vector<int> add(vector<int> &A, vector<int> &B)
{
    // 如果A的位数小于B的位数，交换A和B，确保A的位数不小于B的位数，方便后续计算
    if (A.size() < B.size()) return add(B, A);

    vector<int> C;  // 创建一个向量C，用于存储相加的结果
    int t = 0;      // 初始化进位变量t为0

    // 遍历A的每一位，因为A的位数不小于B的位数，所以以A的位数为准进行计算
    for (int i = 0; i < static_cast<int>(A.size()); i++)
    {
        t += A[i];  // 将A当前位的值加到进位变量t上

        // 如果B当前位存在（即i < B的位数），将B当前位的值也加到进位变量t上
        if (i < static_cast<int>(B.size())) t += B[i];

        C.push_back(t % 10);  // 将t对10取余的结果作为当前位的结果存入C中
        t /= 10;             // 更新进位变量t，将t除以10，得到新的进位值
    }

    // 如果最后还有进位（即t不为0），将进位值存入C中
    if (t) C.push_back(t);

    return C;  // 返回存储相加结果的向量C
}

int main()
{
    // 输入两个大整数的字符串形式
    string a, b;
    cin >> a >> b;//123456789 -> {9, 8, 7, 6, 5, 4, 3, 2, 1}


    // 将输入的字符串转换为vector<int>存储，每个字符减去'0'得到对应的整数值，从低位到高位存储在向量中
    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

//测试代码
    // for(int i = 0; i < static_cast<int>(a.size()); i++)
    // {
    //     cout << a[i] << " ";
    // }
    // cout << endl;
    // for(int i = 0; i < static_cast<int>(b.size()); i++)
    // {
    //     cout << b[i] << " ";
    // }
    // cout << endl;

    // 调用高精度加法函数计算两个大整数的和
    vector<int> result = add(A, B);

    // 输出结果，从高位到低位输出向量中的每个元素
    for (int i = result.size() - 1; i >= 0; i--) cout << result[i];
    cout << endl;

    return 0;
}


