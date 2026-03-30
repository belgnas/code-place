# **【算法题】牛客周赛rating判断**

时间限制：C/C++/Rust/Pascal 1秒，其他语言2秒
空间限制：C/C++/Rust/Pascal 256 M，其他语言512 M
64bit IO Format: %lld

### 题目描述 
牛客周赛对于rating不超过1599的选手是rated的（即比赛会影响选手的rating）。
现在给定小苯当前的rating，请你判断他打这场牛客周赛是否rated。

### 输入描述:
输入一个整数 \(x(0 \leq x \leq 4×10^3)\)，表示小苯当前的rating。

### 输出描述:
如果小苯打这场比赛是rated，输出“Rated”，否则输出“Unrated”。

### 示例1
- **输入**
```
1500
```
- **输出**
```
Rated
```

### 示例2
- **输入**
```
1600
```
- **输出**
```
Unrated
```