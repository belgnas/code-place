# Markdown 语法示范文章

> **文档说明**：本文是一篇 Markdown 语法示范文章，尽可能涵盖常用 Markdown 语法的实际使用场景。
> 阅读本文可以直观地了解 Markdown 的排版效果与格式规范。

---

## 📑 目录

- [1. 标题层级](#1-标题层级)
- [2. 文本样式](#2-文本样式)
- [3. 列表](#3-列表)
- [4. 链接与图片](#4-链接与图片)
- [5. 代码](#5-代码)
- [6. 表格](#6-表格)
- [7. 引用块](#7-引用块)
- [8. 分割线与换行](#8-分割线与换行)
- [9. 任务列表](#9-任务列表)
- [10. 脚注](#10-脚注)
- [11. 数学公式](#11-数学公式)
- [12. HTML 混用](#12-html-混用)
- [13. 表情与特殊字符](#13-表情与特殊字符)
- [14. 定义列表与缩写](#14-定义列表与缩写)

---

## 1. 标题层级

Markdown 支持六级标题，分别对应 HTML 的 `<h1>` ~ `<h6>`。

# 一级标题 — 文章标题

## 二级标题 — 章节标题

### 三级标题 — 小节标题

#### 四级标题 — 子小节标题

##### 五级标题 — 细节标题

###### 六级标题 — 最细粒度标题

---

## 2. 文本样式

### 2.1 基本样式

这是一段**加粗文字**，这是*斜体文字*，这是***加粗斜体***，这是~~删除线文字~~。

这是 `行内代码` 的样式，常用于在段落中标注变量名或命令。

### 2.2 高亮与上下标

部分 Markdown 引擎支持 ==高亮/标记文本==，以及 H~2~O（下标）和 E = mc^2^（上标）。

### 2.3 换行与分段

这是第一行。  
这是同一段落的第二行（行尾两个空格实现软换行）。

这是一个新段落（空行分隔）。

---

## 3. 列表

### 3.1 无序列表

- C++ 基础语法
- Java 面向对象
- 数据结构与算法
  - 排序算法
    - 快速排序
    - 归并排序
  - 搜索算法
- 计算机网络

### 3.2 有序列表

1. 学习编程语言基础
2. 掌握数据结构与算法
3. 参加算法竞赛积累经验
   1. Codeforces 上分
   2. 牛客周赛打卡
4. 学习系统设计

### 3.3 混合嵌套

1. 第一季
   - 第 1 集：启程
   - 第 2 集：初遇
2. 第二季
   - 第 1 集：归来
   - 第 2 集：决战

---

## 4. 链接与图片

### 4.1 超链接

#### 行内式链接

[GitHub](https://github.com "悬停显示标题") 是全球最大的代码托管平台。

#### 参考式链接

本文使用 [Markdown][md] 编写，语法参考自 [CommonMark][cm] 规范。

[md]: https://daringfireball.net/projects/markdown/ "Markdown 官方说明"
[cm]: https://commonmark.org/ "CommonMark 规范"

#### 自动链接

访问 <https://www.google.com> 了解更多。

#### 锚点链接（页内跳转）

[回到目录](#📑-目录)

### 4.2 图片

#### 行内式图片

![C++ Logo](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

#### 带链接的图片

[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=github)](https://github.com)

#### 图片尺寸控制（HTML）

<img src="https://img.shields.io/badge/Markdown-000000?style=for-the-badge&logo=markdown" width="150" alt="Markdown" />

---

## 5. 代码

### 5.1 行内代码

使用 `printf()` 函数输出内容，通过 `std::vector<int>` 存储动态数组。

### 5.2 围栏代码块

#### C++ 示例

```cpp
#include <iostream>
using namespace std;

int main() {
    // 快读优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &x : arr) cin >> x;

    cout << "Hello, World!" << endl;
    return 0;
}
```

#### Python 示例

```python
def binary_search(arr: list[int], target: int) -> int:
    """二分查找，返回目标索引，未找到返回 -1"""
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1
```

#### 命令行示例

```bash
# 编译并运行 C++ 程序
g++ -std=c++17 -O2 main.cpp -o main
./main < input.txt > output.txt

# Git 常用命令
git add .
git commit -m "feat: 添加二分查找模板"
git push origin main
```

#### JSON 配置示例

```json
{
    "name": "algorithm-template",
    "version": "1.0.0",
    "config": {
        "language": "C++",
        "standard": "c++17",
        "optimize": true
    }
}
```

### 5.3 缩进代码块

    这是一个缩进代码块（每行前面有四个空格或一个制表符）。
    适用于纯文本展示。
    它不会进行语法高亮。

### 5.4 diff 代码块

```diff
- int old_value = 42;
+ int new_value = 100;

-   // 旧方法
-   cout << "Done." << endl;
+   // 新方法：使用快读
+   ios::sync_with_stdio(false);
```

---

## 6. 表格

### 6.1 基本表格

| 算法 | 时间复杂度 | 空间复杂度 | 稳定性 |
| :--- | :---: | ---: | :--- |
| 冒泡排序 | O(n²) | O(1) | 稳定 |
| 快速排序 | O(n log n) | O(log n) | 不稳定 |
| 归并排序 | O(n log n) | O(n) | 稳定 |
| 堆排序 | O(n log n) | O(1) | 不稳定 |

> 对齐方式：`:---` 左对齐，`:---:` 居中，`---:` 右对齐。

### 6.2 含特殊字符的表格

| 转义字符 | 含义 | 示例 |
| --- | --- | --- |
| `\|` | 管道符（表格中需要用 `\|` 转义） | `a \| b` |

---

## 7. 引用块

### 7.1 基础引用

> 这是单行引用，常用于引用他人观点或强调内容。

### 7.2 多行引用

> "We cannot solve our problems with the same thinking we used when we created them."
>
> — Albert Einstein

### 7.3 嵌套引用

> 一级引用
>> 二级引用
>>> 三级引用
>>
>> 回到二级引用
>
> 回到一级引用

### 7.4 引用内包含其他元素

> **重要提示**：引用块内可以包含其他 Markdown 元素。
>
> 1. 第一条
> 2. 第二条
>
> ```cpp
> cout << "代码也可以放在引用中" << endl;
> ```
>
> | 列 A | 列 B |
> | --- | --- |
> | 1 | 2 |

---

## 8. 分割线与换行

### 8.1 分割线

使用三个以上的 `*`、`-` 或 `_` 创建分割线：

---

***

___

### 8.2 强制换行

行尾两个空格 + 回车 = 软换行（同一段落）。  
这是软换行的效果。

行尾反斜杠 + 回车 = 硬换行。\
这是硬换行的效果。

---

## 9. 任务列表

### 本周学习计划

- [x] 完成 C++ STL 学习
- [x] Codeforces Round #920（Div. 3）题解整理
- [ ] 复习操作系统第三章
- [ ] 整理 10 道动态规划题目
- [ ] 阅读《Effective Modern C++》第一章
- [ ] ~~完成牛客周赛~~（已取消）

### 嵌套任务列表

- [ ] 算法学习
  - [x] 排序算法
  - [x] 二分查找
  - [ ] 动态规划
- [ ] 项目开发
  - [ ] 通讯录管理系统
  - [ ] 算法可视化工具

---

## 10. 脚注

本文使用脚注来标注引用来源。

快速排序由 Tony Hoare 于 1960 年提出[^1]，它采用分治策略来对序列进行排序。

STL（Standard Template Library）是 C++ 标准库的核心组成部分[^2]，包含了容器、算法、迭代器和函数对象。

[^1]: Hoare, C. A. R. (1961). "Algorithm 64: Quicksort." *Communications of the ACM*, 4(7), 321.
[^2]: STL 最初由 Alexander Stepanov 和 Meng Lee 在惠普实验室开发，后于 1994 年被采纳为 C++ 标准库的一部分。

---

## 11. 数学公式

### 11.1 行内公式

欧拉公式：$e^{i\pi} + 1 = 0$

时间复杂度通常表示为 $O(n \log n)$、$O(n^2)$ 等。

### 11.2 块级公式

#### 求和公式

$$
\sum_{i=1}^{n} i = \frac{n(n+1)}{2}
$$

#### 矩阵

$$
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
7 & 8 & 9
\end{bmatrix}
$$

#### 分段函数

$$
f(n) =
\begin{cases}
n/2, & \text{如果 } n \text{ 为偶数} \\
3n+1, & \text{如果 } n \text{ 为奇数}
\end{cases}
$$

#### 递推公式（DP 状态转移）

$$
dp[i][j] = \max
\begin{cases}
dp[i-1][j], & \text{不选第 } i \text{ 个物品} \\
dp[i-1][j-w_i] + v_i, & \text{选第 } i \text{ 个物品}
\end{cases}
$$

---

## 12. HTML 混用

Markdown 支持内嵌 HTML 标签，适用于 Markdown 原生语法无法覆盖的场景。

### 12.1 折叠面板

<details>
<summary><b>点击展开：查看完整题解</b></summary>

#### 题目分析

本题要求计算两个大整数的和，不能使用内置大数类型。

#### 解题思路

1. 将两个字符串逆序存储
2. 逐位相加，处理进位
3. 最后逆序输出结果

```cpp
string addStrings(string num1, string num2) {
    string result;
    int carry = 0;
    int i = num1.size() - 1, j = num2.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(result.begin(), result.end());
    return result;
}
```

</details>

### 12.2 键盘按键

按 <kbd>Ctrl</kbd> + <kbd>C</kbd> 复制，按 <kbd>Ctrl</kbd> + <kbd>V</kbd> 粘贴。

### 12.3 文本对齐

<p align="center">
  <b>这是居中对齐的文本</b>
</p>

<p align="right">
  <i>这是右对齐的文本</i>
</p>

### 12.4 下划线

Markdown 原生不支持下划线，可使用 <u>HTML 标签实现下划线</u>。

---

## 13. 表情与特殊字符

### 13.1 Emoji 表情（短代码）

:smile: :rocket: :star: :fire: :warning: :bulb: :memo: :tada: :bug: :zap:

常用学习类 emoji：:white_check_mark: :x: :hourglass: :books: :pencil2: :brain:

### 13.2 转义字符

| 字符 | 转义写法 | 说明 |
| --- | --- | --- |
| \* | `\*` | 星号 |
| \_ | `\_` | 下划线 |
| \# | `\#` | 井号（标题符号） |
| \` | `` \` `` | 反引号 |
| \~ | `\~` | 波浪线 |
| \\ | `\\` | 反斜杠自身 |
| \| | `\|` | 管道符（表格中） |
| \< | `\<` | 小于号 |
| \> | `\>` | 大于号 |

---

## 14. 定义列表与缩写

### 14.1 定义列表

<dl>
  <dt>算法竞赛（Competitive Programming）</dt>
  <dd>在规定时间内编写程序解决特定算法问题的一种竞赛形式，常见平台包括 Codeforces、AtCoder 和牛客。</dd>

  <dt>时间复杂度</dt>
  <dd>用于衡量算法运行时间随输入规模增长的变化趋势，通常使用大 O 表示法（Big O Notation）表示。</dd>

  <dt>ACM-ICPC</dt>
  <dd>国际大学生程序设计竞赛，由美国计算机协会主办，是世界上规模最大、水平最高的编程竞赛。</dd>
</dl>

### 14.2 缩写

<abbr title="Standard Template Library">STL</abbr>
<abbr title="Depth First Search">DFS</abbr>
<abbr title="Application Programming Interface">API</abbr>

---

> **📝 本文结束** — 以上涵盖了 Markdown 绝大多数常用语法。您可以将本文作为格式参考，对照学习每种语法的写法与呈现效果。
