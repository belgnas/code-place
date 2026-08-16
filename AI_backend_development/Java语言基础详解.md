# Java 语言基础详解

> 本文档面向**有 C/C++ 基础**的学习者，系统复习 Java 语言基础。
> 重点标注 Java 与 C/C++ 的差异，力求脱离具体项目也能独立学通。
> 配套项目：图书管理 API（Spring Boot 学习项目）。

## 目录

1. [Java 运行机制](#1-java-运行机制)
2. [数据类型](#2-数据类型)
3. [类型转换](#3-类型转换)
4. 变量与运算符（待补）
5. 流程控制（待补）
6. 数组（待补）

---

## 1. Java 运行机制

### 1.1 与 C/C++ 的根本区别

C++ 的执行链路：

```
.cpp  --(编译器 g++)-->  机器码 .exe  --(CPU 直接执行)-->  结果
```

C++ 编译产物是**特定平台的机器码**，Windows 编的 exe 到 Linux 跑不了。

Java 的执行链路：

```
.java  --(javac 编译)-->  .class(字节码)  --(JVM 解释/JIT 执行)-->  结果
```

核心差异在中间的**字节码（bytecode）**：

- `javac` 不生成机器码，而是生成**中间码**（字节码，存于 `.class` 文件）。
- 字节码 CPU **读不懂**，只有 **JVM（Java 虚拟机）** 能执行。
- 每个平台都有自己的 JVM，负责把字节码翻译成本平台机器码。

由此得到 Java 的口号：**Write Once, Run Anywhere（一次编写，到处运行）**。

> **类比**：字节码像「普通话」，JVM 像各地「翻译官」。你只写一份普通话（`.class`），
> 到广东有粤语翻译官、到四川有川话翻译官（不同平台的 JVM），当地都能听懂。
> C++ 的 exe 相当于直接说「粤语」，出了广东没人懂。

### 1.2 关键澄清：`.class` 是字节码，不是机器码

初学最易错的点：以为 `.class` 和 `.exe` 一样是机器码。**不是。**

| | C++ 的 `.exe` | Java 的 `.class` |
|---|---|---|
| 内容 | **机器码**（CPU 能直接读） | **字节码**（CPU 读不懂，只有 JVM 能读） |
| 谁执行 | CPU **直接**执行 | JVM 翻译后再交给 CPU |
| 跨平台 | ❌ 不能 | ✅ 能（只要有对应 JVM） |

**为什么 Java 能跨平台、C++ 不能？**
> C++ 把「翻译」放在编译期一次做完（编到机器码）；
> Java 把「翻译」推迟到运行期由 JVM 完成（字节码 → 机器码）。
> 正因为 `.class` **不是**机器码、需要 JVM 翻译，它才能到处运行。

### 1.3 JDK / JRE / JVM

三者是包含关系：**JDK ⊃ JRE ⊃ JVM**。

```
┌───────────────── JDK（开发工具包）─────────────────┐
│  javac、jar、javadoc、jdb… 一堆开发工具             │
│  ┌─────────────── JRE（运行环境）──────────────┐   │
│  │  Java 核心类库（String、集合、IO…）          │   │
│  │  ┌──────────── JVM（虚拟机）───────────┐    │   │
│  │  │  真正执行字节码的引擎                 │    │   │
│  │  └──────────────────────────────────────┘    │   │
│  └────────────────────────────────────────────────┘   │
└──────────────────────────────────────────────────────────┘
```

| 缩写 | 全称 | 作用 | 类比 |
|------|------|------|------|
| **JVM** | Java Virtual Machine | 执行字节码 | 发动机 |
| **JRE** | Java Runtime Environment | JVM + 核心类库，**只能运行** | 整车（能开不能造） |
| **JDK** | Java Development Kit | JRE + 开发工具，**能开发** | 整车 + 修车厂 |

要点：
- **开发**装 **JDK**（含编译器 `javac`）。
- **只运行**别人给的 `.class`/`.jar`，有 **JRE** 即可。
- JDK 11 起 Oracle 不再单独发布 JRE，可用 JDK 的 `jlink` 按需裁剪运行时，装 JDK 即够用。

### 1.4 一个完整的编译-运行示例

```java
// Hello.java
public class Hello {
    public static void main(String[] args) {
        System.out.println("Hello, Java!");
    }
}
```

命令行操作（Windows PowerShell 同样适用）：

```bash
javac Hello.java     # 编译，生成 Hello.class（字节码）
java Hello           # 运行（注意：不带 .class 后缀，写类名）
# 输出：Hello, Java!
```

> **易错点**：`java Hello.class` 是错的，应写 `java Hello`（JVM 要的是**类名**，不是文件名）。
> JDK 11+ 也支持 `java Hello.java` 单文件直接运行（内部先编译再执行），适合练手。

---

## 2. 数据类型

Java 数据类型分两大类，比 C++ 严格得多：

```
Java 数据类型
├── 基本类型 (primitive type)  ——  8 种，存的是「值本身」
│   ├── 整数：byte  short  int  long
│   ├── 浮点：float  double
│   ├── 字符：char
│   └── 布尔：boolean
└── 引用类型 (reference type)  ——  存的是「对象的地址」
    ├── 类（String、自定义类…）
    ├── 接口
    └── 数组
```

### 2.1 八种基本类型

| 类型 | 字节数 | 取值范围 | 与 C++ 的差异 |
|------|--------|---------|--------------|
| `byte` | 1 | -128 ~ 127 | C++ 没有此类型 |
| `short` | 2 | -32768 ~ 32767 | 同 C++ |
| `int` | **4（固定）** | 约 ±21 亿 | ⚠️ C++ 中 int 大小依平台而定，Java 锁死 4 字节 |
| `long` | **8（固定）** | 约 ±9.2×10¹⁸ | ⚠️ C++ 的 long 在 Windows 是 4 字节，Java 永远 8 |
| `float` | 4 | 单精度浮点 | 字面量要加 `f`：`3.14f` |
| `double` | 8 | 双精度浮点 | 小数**默认**是 double |
| `char` | **2** | 0 ~ 65535 | ⚠️ C++ 的 char 是 1 字节，Java 是 2 字节（存 Unicode） |
| `boolean` | 未明确定义 | `true` / `false` | ⚠️ **不能和 0/1 互换** |

### 2.2 四个关键差异（C++ 老手易踩的坑）

**① 基本类型大小与平台无关。**
C++ 中 `sizeof(int)` 可能是 2 或 4，`long` 在 Windows 是 4、Linux 64 位是 8。
Java 彻底锁死：`int` 永远 4 字节，`long` 永远 8 字节。这是「一次编写到处运行」的一部分。

**② `char` 是 2 字节，存 Unicode（UTF-16），可直接放中文。**

```java
char c = 'A';      // 可以
char z = '中';     // 也可以！C++ 的 1 字节 char 存不下
```

**③ `boolean` 与整数彻底隔离，不能互相转换。**
C++ 里「非 0 即真」，Java 完全禁止：

```java
int x = 5;
if (x) { }          // ❌ 编译报错，Java 不认 int 当条件
if (x != 0) { }     // ✅ 必须是明确的布尔表达式
boolean b = 1;      // ❌ 编译报错，1 不是 boolean
if (x == true) { }  // ❌ 依然报错！int 和 boolean 不能用 == 比较
```

> 这是**故意**的设计，防止 C 里经典 bug `if (a = b)`（误把 == 写成 =）。
> **判断法则：`if ( )` 括号里必须是结果为 `boolean` 的表达式**——
> 判断非零写 `!= 0`，判断非空写 `!= null`。

**④ 字面量默认类型：小数默认 `double`，整数默认 `int`。**

```java
float f = 3.14;            // ❌ 3.14 是 double，塞进 float 丢精度
float f = 3.14f;           // ✅ 加 f 后缀
long big = 10000000000;    // ❌ 超 int 范围，字面量默认 int
long big = 10000000000L;   // ✅ 加 L 后缀
```

---

## 3. 类型转换

只讨论**基本类型之间**的转换（引用类型转换见 OOP 章节）。

### 3.1 自动类型转换（隐式）——小转大，安全

范围小 → 范围大，自动完成：

```
byte → short → int → long → float → double
              char ↗
```

```java
int i = 100;
long l = i;        // ✅ int → long，自动
double d = l;      // ✅ long → double，自动
```

> 类比「小水杯倒进大水杯，不会溢出」。`int → float` 也自动（float 表示范围更大）。

### 3.2 强制类型转换（显式）——大转小，可能丢数据

范围大 → 范围小，必须手动加 `(类型)`：

```java
double d = 3.99;
int i = (int) d;       // ✅ i = 3（截断小数，不是四舍五入！）

long big = 300;
byte b = (byte) big;   // ⚠️ 300 超 byte 范围，溢出 = 44
```

两个坑：
- **小数转整数是「截断」不是「四舍五入」**：`(int)3.99` = 3。
- **超范围会溢出**成意外的值。

### 3.3 高频陷阱

**① byte/short/char 参与运算会先提升为 int：**

```java
byte a = 10, b = 20;
byte c = a + b;           // ❌ a+b 结果是 int，塞不回 byte
byte c = (byte)(a + b);   // ✅ 强制转回
int  c = a + b;           // ✅ 用 int 接收
```

**② 整数除法舍去小数（同 C++）：**

```java
System.out.println(7 / 2);      // 3    两个 int，整数除法
System.out.println(7.0 / 2);    // 3.5  有一个 double，按 double 算
System.out.println((int) 5.99); // 5    强制转换是截断
```

---

## 4. 变量与运算符

### 4.1 变量：与 C++ 的差异

**① 局部变量必须先初始化才能使用**（比 C++ 严格）：

```java
int x;
System.out.println(x);   // ❌ 编译报错：variable x might not have been initialized
```

C++ 里这样只是「未定义值」（能编译、运行出垃圾值），Java 直接**编译不过**，把 bug 挡在编译期。
注意：只有**局部变量**（方法内）有此限制；类的**成员变量**会自动赋默认值
（`int`→0，`boolean`→false，引用→null），详见 OOP 章节。

**② `var` 类型推断（Java 10+，类似 C++ 的 `auto`）：**

```java
var name = "Tom";                    // 推断为 String
var age  = 20;                       // 推断为 int
var list = new ArrayList<String>();  // 少写一遍类型
```

只能用于**局部变量**，不能用于成员变量、方法参数、返回值。

**③ `final` = C++ 的 `const`：**

```java
final int MAX = 100;
MAX = 200;            // ❌ final 变量不可再赋值
```

### 4.2 运算符：与 C++ 的差异点

绝大部分（`+ - * / %`、`++ --`、比较、逻辑、位运算）与 C++ 相同，只列不同处。

**① `%` 支持浮点，符号跟被除数：**

```java
System.out.println(-7 % 3);    // -1（同 C++）
System.out.println(7.5 % 2);   // 1.5（Java 的 % 支持浮点，C++ 需 fmod）
```

**② Java 特有：`>>>` 无符号右移**（C++ 没有）：

```java
int n = -8;
System.out.println(n >> 3);    // -1   算术右移，高位补符号位(1)
System.out.println(n >>> 3);   // 很大的正数，高位补 0
```
- `>>`：高位补**符号位**（负数补 1）。
- `>>>`：高位一律补 **0**。

**③ `+` 用于字符串是拼接，从左往右求值：**

```java
System.out.println("结果=" + 3 + 4);   // 结果=34（开头是字符串，后面全拼接）
System.out.println(3 + 4 + "=结果");   // 7=结果（先算 3+4=7，再拼接）
```

**④ 自增自减求值顺序（Java 有严格规范，C++ 是未定义行为）：**

```java
int i = 5;
int a = i++;    // 先取值后自增：a=5, i=6
int b = ++i;    // 先自增后取值：i=7, b=7
```

**⑤ 复合赋值暗含强制转换（隐藏坑）：**

```java
byte b = 10;
b = b + 1;      // ❌ b+1 是 int，塞不回 byte
b += 1;         // ✅ 可以！等价于 b = (byte)(b + 1)，编译器偷偷加了强转

byte c = 127;
c += 1;         // 不报错，但溢出成 -128
```

### 4.3 char 参与运算

`char` 是 2 字节整数（Unicode 码），可直接参与算术，算完需强转回 char：

```java
char ch = 'A';
int code = ch;               // 65（char 自动提升为 int）
char next = (char)(ch + 1);  // 'B'
System.out.println('a' - 'A');    // 32
int val = '7' - '0';              // 7（数字字符转数值，算法题常用）
```

### 4.4 类型提升规则（易错点）

`byte`、`short`、`char` 参与算术运算时会**先自动提升为 `int`** 再计算，
所以结果是 int，塞回小类型需强转：

```java
byte m = 10;
byte n = m + 5;         // ❌ m+5 结果是 int（大），转 byte（小）需显式强转
byte n = (byte)(m + 5); // ✅
```

> 口诀：**小转大自动、大转小手动**。byte→int 自动，int→byte 需要 `(byte)`。

---

## 5. 流程控制

分支（`if`/`switch`）与循环（`for`/`while`/`do-while`）的基本用法同 C++，此处只讲差异。

### 5.1 switch 的两种形态

**传统 switch（同 C++，有贯穿陷阱）：**

```java
int x = 2;
switch (x) {
    case 1: System.out.println("A");   // x=2 时不执行
    case 2: System.out.println("B");   // ← 从这里开始执行
    case 3: System.out.println("C"); break;  // 贯穿到这，遇 break 停
    default: System.out.println("D");
}
// 输出：B  C
```

**两条铁律**：
1. switch **直接跳到命中的 case** 开始执行，不从第一个 case 走。
2. 每个 case 结尾不写 `break` 会**贯穿**到下面的 case，直到遇到 break。

**新版 switch（Java 12+，箭头语法，推荐）：**

```java
int day = 3;
String name = switch (day) {
    case 1 -> "周一";
    case 2 -> "周二";
    case 3, 4, 5 -> "工作日";     // 多值用逗号合并
    default -> "其他";
};                                // 注意有分号（它是表达式）
```

三大优势：
- **`->` 自动 break，永不贯穿**。
- **多值合并**：`case 3, 4, 5 ->`。
- **可作表达式**：整体有返回值，直接赋给变量。

多行逻辑用 `{}` + `yield` 返回值：

```java
String level = switch (score / 10) {
    case 10, 9 -> "优秀";
    default -> {
        System.out.println("需努力");
        yield "及格以下";       // 块内用 yield 返回
    }
};
```

### 5.2 switch 支持 String（C++ 不行）

```java
String cmd = "start";
switch (cmd) {
    case "start" -> System.out.println("启动");
    case "stop"  -> System.out.println("停止");
    default      -> System.out.println("未知命令");
}
```

Java 的 switch 可匹配 **String、char、int、枚举**；C++ 只能用整数/枚举。

### 5.3 增强 for（for-each）

类似 C++11 的 range-for，遍历数组/集合更简洁：

```java
int[] arr = {10, 20, 30};
for (int x : arr) {
    System.out.println(x);
}
```

**两个关键限制：**
- **拿不到下标**。需要下标、或要修改元素时，只能用传统 `for`。
- **循环变量是副本，改它不影响原数组：**

```java
for (int x : arr) {
    x = x * 2;      // 只改副本，arr 不变
}
// arr 仍是 {10, 20, 30}
```

> Java 没有 C++ 的 `for (int& x : arr)` 引用语法。想改原数组元素，
> **必须用传统 for + 下标**：`arr[i] = arr[i] * 2;`

### 5.4 带标签的 break/continue（替代 goto）

跳出/跳过**多层嵌套循环**，C++ 需 goto 或标志位，Java 用标签：

```java
outer:                              // 标签
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        if (i + j == 4) continue outer;  // 跳到外层下一次迭代
        System.out.println(i + "," + j);
    }
}
// 输出：1,1  1,2  2,1
```

- `break 标签;`：一次跳出到标签所在循环之外。
- `continue 标签;`：跳到标签所在循环的下一次迭代。
- 注意：`continue` 在 `println` **之前**触发时，当前这轮就不打印。

---

## 6. 数组

Java 数组与 C++ 差异极大：**数组是堆上的对象，变量只是指向它的引用**。

### 6.1 根本差异：数组是对象，变量是引用

```java
int[] arr = new int[5];
```

```
栈(stack)          堆(heap)
┌─────────┐       ┌───────────────────────┐
│ arr ────┼─────▶│ [0][0][0][0][0]  长度5 │
└─────────┘       └───────────────────────┘
   引用               真正的数组对象
```

C++ 的 `int arr[5]` 是栈上一块连续内存，数组名≈首地址；
Java 的 `arr` 只是指向堆的引用（类似指针）。

### 6.2 声明与创建

```java
int[] a;                        // ✅ 推荐（[] 放类型侧）
int b[];                        // 也合法但不推荐

int[] arr = new int[5];         // 必须 new，元素自动初始化为 0
int[] c = {1, 2, 3, 4};         // 静态初始化（简写）
int[] d = new int[]{1, 2, 3};   // 完整写法
```

与 C++ 的差异：
- 长度写在 `new int[5]`，**不能** `int arr[5]`。
- 创建即**自动初始化**（数值→0，boolean→false，引用→null）；C++ 是垃圾值。
- 取长度用属性 **`arr.length`**（无括号），不是 `arr.length()`。

### 6.3 长度固定 + 自动越界检查

```java
int[] arr = new int[3];
System.out.println(arr.length);   // 3
arr[5] = 10;   // ❌ 运行时抛 ArrayIndexOutOfBoundsException
```

- 长度创建后**不可变**（要变长用 `ArrayList`）。
- 越界**抛异常**兜底；C++ 越界是未定义行为（可能默默写坏内存）。

### 6.4 引用语义：赋值 / 传参不是拷贝（易错）

```java
int[] a = {1, 2, 3};
int[] b = a;          // 复制的是引用！b、a 指向同一数组
b[0] = 99;
System.out.println(a[0]);   // 99

// 真正拷贝：
int[] c = a.clone();
int[] d = Arrays.copyOf(a, a.length);
```

数组作方法参数也是传引用，方法内改元素会影响外部（相当于 C++ 传指针）。

### 6.5 遍历与 Arrays 工具类

```java
import java.util.Arrays;

int[] arr = {30, 10, 20};
for (int i = 0; i < arr.length; i++) { }   // 要下标
for (int x : arr) { }                       // 不要下标

Arrays.sort(arr);                    // 排序
Arrays.toString(arr);                // "[10, 20, 30]" 便于打印
Arrays.fill(arr, 0);                 // 全填 0
int[] copy = Arrays.copyOf(arr, 5);  // 复制并调整长度（不足补 0）
Arrays.binarySearch(arr, 20);        // 二分查找（需先排序）
```

> **打印坑**：`System.out.println(arr)` 输出地址哈希（如 `[I@1b6d3586`），
> 不是内容！看内容必须用 `Arrays.toString(arr)`。

### 6.6 二维数组（数组的数组，可锯齿）

```java
int[][] grid = new int[3][4];        // 3 行 4 列，全 0
int[][] m = {{1, 2}, {3, 4, 5}};     // 各行可不等长（锯齿数组）

m.length        // 2   → 行数
m[1].length     // 3   → 第 1 行（{3,4,5}）的列数
```

- Java 二维数组本质是**「数组的数组」**，每行是独立的一维数组对象。
- 各行**可不等长**（锯齿数组）；C++ 的 `int m[3][4]` 是规整连续内存。
- `m.length` 是行数，`m[i].length` 是**第 i 行自己的**列数。

---

## 模块小结：Java 语言基础 vs C++ 速查

| 主题 | C++ | Java |
|------|-----|------|
| 编译产物 | 机器码 exe（不跨平台） | 字节码 .class（JVM 跨平台） |
| 基本类型大小 | 依平台 | 固定（int=4、long=8、char=2） |
| char | 1 字节 | 2 字节（Unicode） |
| boolean | 非 0 即真 | 与整数隔离，if 必须是 boolean 表达式 |
| 局部变量 | 可不初始化（垃圾值） | 必须先初始化（否则编译错） |
| switch | 仅整数/枚举 | 支持 String；有箭头语法 `->` |
| 数组本质 | 栈上连续内存 | 堆上对象，变量是引用 |
| 数组赋值 | 值拷贝 | 复制引用（共享同一数组） |
| 数组越界 | 未定义行为 | 抛 ArrayIndexOutOfBoundsException |
| 数组长度 | 自己记 | `arr.length` 属性 |
| 二维数组 | 规整连续 | 数组的数组，可锯齿 |

**核心记忆点：**
1. `.class` 是字节码不是机器码，靠 JVM 跨平台。
2. 基本类型大小固定；`char` 2 字节；`boolean` 与整数彻底隔离。
3. `if ( )` 里必须是 boolean 表达式。
4. 局部变量必须先初始化。
5. switch 从命中的 case 起跳、会贯穿；新版 `->` 不贯穿、可作表达式、支持 String。
6. 数组是**引用类型**：赋值/传参共享同一对象，`b=a` 不是拷贝。
7. 数组自动初始化、自动越界检查；打印用 `Arrays.toString()`。

---

*模块 1（语言基础）完成。下一模块：面向对象。*
