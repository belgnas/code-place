#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 定义一个结构体来存储每行数据及其和
struct RowData
{
    vector<int> row;
    int sum;
};

// 自定义比较函数，用于比较二维数组的两行
bool compareRows(const RowData &rowData1, const RowData &rowData2)
{
    // 优先比较行元素和
    if (rowData1.sum != rowData2.sum)
    {
        return rowData1.sum > rowData2.sum;
    }

    // 若和相同，逐位比较元素
    int n = rowData1.row.size();
    for (int i = 0; i < n; ++i)
    {
        if (rowData1.row[i] != rowData2.row[i])
        {
            return rowData1.row[i] > rowData2.row[i];
        }
    }

    // 如果所有元素都相同，可简单返回 false，因为元素完全相同不存在严格大于关系
    return false;
}

// 对二维数组进行排序的函数
void sort2DArray(vector<RowData> &arr)
{
    sort(arr.begin(), arr.end(), compareRows);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        // 使用 vector<RowData> 创建二维数组存储结构
        vector<RowData> arr(n);

        // 输入二维数组的元素并计算每行的和
        for (int i = 0; i < n; i++)
        {
            arr[i].row.resize(m);
            arr[i].sum = 0;
            for (int j = 0; j < m; j++)
            {
                cin >> arr[i].row[j];
                arr[i].sum += arr[i].row[j];
            }
        }

        // 调用排序函数
        sort2DArray(arr);

        vector<int> ans;

        // 将排序后的二维数组元素存入 ans 中
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ans.push_back(arr[i].row[j]);
            }
        }

        int answer = 0;
        int prefixSum = 0;

        // 计算最终得分
        for (int i = 0; i < n * m; i++)
        {
            prefixSum += ans[i];
            answer += prefixSum;
        }

        cout << answer << endl;
    }

    return 0;
}