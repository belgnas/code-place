# Java 常用核心类详解

> 本文档面向**有 C/C++ 基础**的学习者，系统复习 Java 最常用的核心类。
> 重点标注与 C++ 的差异及高频陷阱，力求脱离项目也能独立学通。
> 前置：《Java语言基础详解.md》《Java面向对象详解.md》。配套项目：图书管理 API（Spring Boot）。

## 目录

1. [String：不可变字符串](#1-string不可变字符串)
2. [StringBuilder / StringBuffer](#2-stringbuilder--stringbuffer)
3. [包装类与装箱拆箱](#3-包装类与装箱拆箱)
4. [Integer 缓存陷阱](#4-integer-缓存陷阱)
5. [Math / Arrays / 常用工具类](#5-math--arrays--常用工具类)
6. [异常处理](#6-异常处理)
7. [泛型](#7-泛型)
8. [集合框架](#8-集合框架)
9. [Lambda / Stream / Optional](#9-lambda--stream--optional)

---

## 1. String：不可变字符串

### 1.1 不可变性（immutable）——核心

**String 对象一旦创建，内容永远不能改变**（与 C++ 的 `std::string` 相反）。

```java
String s = "hello";
s = s + " world";       // 不是修改原对象！
```

真相：
1. `"hello"` 对象内容永远不变。
2. `s + " world"` **创建了新对象** `"hello world"`。
3. 变量 `s` 的**引用**改指向新对象；旧的 `"hello"` 原封不动（等待回收）。

> 改变的是「变量 s 指向谁」，不是「字符串对象的内容」。

所有「修改」方法都返回新对象，原对象不变：

```java
String s = "Hello";
String upper = s.toUpperCase();   // 返回新串
System.out.println(s);            // Hello（原对象没变）
System.out.println(upper);        // HELLO
```

> `toUpperCase`/`substring`/`replace`/`trim` 等**都不改原串，只返回新串**。
> 不接收返回值等于白做（`s.toUpperCase();` 单独一行无意义）。

### 1.2 为什么不可变

- **安全**：常用作 Map key、路径、地址，不可变保证不被偷改。
- **可共享**：不可变才能安全共享（字符串常量池）。
- **线程安全**：不可变对象天生线程安全。

代价：频繁拼接产生大量临时对象 → 用 StringBuilder 解决（下一节）。

### 1.3 字符串常量池：== vs equals

**字面量创建走常量池，可能共享同一对象：**

```java
String a = "hello";
String b = "hello";
System.out.println(a == b);        // true（共享池中同一对象）
```

**new 强制建新对象，不走池：**

```java
String a = "hello";
String b = new String("hello");
System.out.println(a == b);        // false（不同对象）
System.out.println(a.equals(b));   // true（内容相同）
```

**铁律：比较字符串内容永远用 `equals()`，绝不用 `==`。**
字符串来源多样（字面量/new/输入/拼接），`==` 时对时错，是经典 bug 源。

### 1.4 equals 防 NPE 技巧：常量在前

`a.equals(b)` 会不会抛 NPE，**只取决于调用者 `a` 是否为 null**，与参数 `b` 无关：

```java
String name = null;
name.equals("tom");   // ❌ 对 null 调方法 → NullPointerException
"tom".equals(name);   // ✅ 调用者是字面量，绝不为 null；参数 null 时返回 false
```

> 实战习惯（Yoda condition）：把**确定非 null**的一方（字面量/常量）放 `.equals()` 前面：
> ```java
> if ("yes".equals(userInput)) { }   // userInput 为 null 也安全
> ```
> 原因：标准 equals 内部首步 `if (o == null) return false`，参数为 null 不崩；
> 崩溃只发生在**调用者本身是 null** 时。

---

## 2. StringBuilder / StringBuffer

### 2.1 String 拼接的性能陷阱

String 不可变，循环里每次 `+=` 都创建新对象：

```java
String s = "";
for (int i = 0; i < 1000; i++) {
    s += "x";      // 每次建新 String，约 1001 个临时对象，O(n²)
}
```

### 2.2 StringBuilder：可变缓冲区

内部维护可扩展字符数组，追加时**在原缓冲区上操作**，不建新对象（类似 C++ `vector`）：

```java
StringBuilder sb = new StringBuilder();
for (int i = 0; i < 1000; i++) {
    sb.append(i);        // 直接在缓冲区末尾追加，O(n)
}
String result = sb.toString();   // 最后一次性转 String
```

> 类比：String 拼接 = 「每加一个字就重抄整张纸」；StringBuilder = 「在同一张纸上接着写」。

### 2.3 常用方法（链式调用）

大多数方法**返回 `this`（自身）**，支持链式调用：

```java
StringBuilder sb = new StringBuilder();
sb.append("Hello").append(", ").append("world").append('!');
System.out.println(sb.toString());   // Hello, world!
```

| 方法 | 说明 |
|------|------|
| `append(x)` | 追加，返回 this |
| `insert(i, x)` | 在位置 i 插入 |
| `delete(start, end)` | 删除 [start, end) |
| `reverse()` | 反转（算法题常用） |
| `charAt(i)` | 取第 i 个字符 |
| `length()` | 长度 |
| `toString()` | 转为不可变 String |

```java
// 反转字符串（一行）
String reversed = new StringBuilder("hello").reverse().toString();  // "olleh"
```

### 2.4 StringBuilder vs StringBuffer

| | StringBuilder | StringBuffer |
|--|:---:|:---:|
| 线程安全 | ❌ | ✅（方法加 synchronized） |
| 速度 | 快 | 慢 |
| 何时用 | **绝大多数情况（默认）** | 多线程共享同一缓冲区（罕见） |

> 记忆：**Builder 快不安全，Buffer 安全但慢。单线程默认 Builder。**

### 2.5 选用原则

- **少量固定拼接** → 直接用 `+`，可读性好，编译器会自动优化。
- **循环里 / 不确定次数的动态拼接** → 用 StringBuilder。

```java
// ✅ 简单拼接，用 + 足够（编译器自动优化成 StringBuilder）
String msg = "Hello, " + name + "!";

// ✅ 循环拼接，用 StringBuilder
StringBuilder sb = new StringBuilder();
for (String item : list) sb.append(item).append(",");
```

> 判断法则：这个拼接**在循环里吗 / 次数不确定**？是 → StringBuilder；否 → 直接 `+`。

---

## 3. 包装类与装箱拆箱

### 3.1 为什么需要包装类

Java 有 8 种基本类型，它们**不是对象**——放不进集合，不能调方法，泛型也用不了：

```java
List<int> list = new ArrayList<>();   // ❌ 编译报错！泛型只接受对象
```

为此 Java 给每种基本类型配了对应的**包装类（Wrapper Class）**：

| 基本类型 | 包装类 |
|---------|--------|
| `byte` | `Byte` |
| `short` | `Short` |
| `int` | **`Integer`** |
| `long` | `Long` |
| `float` | `Float` |
| `double` | `Double` |
| `char` | **`Character`** |
| `boolean` | `Boolean` |

规律：首字母大写；`int→Integer`、`char→Character` 拼写例外，其余直接大写首字母。

### 3.2 装箱与拆箱

**装箱（boxing）**：基本类型 → 包装类对象  
**拆箱（unboxing）**：包装类对象 → 基本类型

Java 5+ 支持**自动装箱/拆箱**，编译器隐式生成转换代码：

```java
Integer a = 10;         // 自动装箱：等价于 Integer.valueOf(10)
int n = a;              // 自动拆箱：等价于 a.intValue()

List<Integer> list = new ArrayList<>();
list.add(5);            // 5 自动装箱成 Integer 对象再放入
int x = list.get(0);   // 取出时自动拆箱成 int
```

> 类比 C++：编译器帮你生成隐式类型转换代码，类似 `int` 赋给 `long` 的自动提升，但 Java 这里是基本类型与对象之间的转换。

### 3.3 ⚠️ 空指针陷阱：对 null 拆箱

```java
Integer x = null;
int n = x;   // 编译通过，运行时 NullPointerException！
```

原因：编译器把 `int n = x` 翻译成 `int n = x.intValue()`；x 是 null，调方法 → NPE。

> 后端实际场景：数据库字段允许 NULL，用 Integer 接收，直接赋给 int → 线上 NPE。**拆箱前先判 null**。

### 3.4 包装类常用方法

```java
// 字符串 → 数字（最常用，后端/算法都会用到）
int i    = Integer.parseInt("123");
double d = Double.parseDouble("3.14");

// 数字 → 字符串
String s = String.valueOf(42);      // 最通用写法
String s2 = Integer.toString(42);  // 也可

// 边界常量
System.out.println(Integer.MAX_VALUE);  // 2147483647
System.out.println(Integer.MIN_VALUE);  // -2147483648

// 进制转换（算法题常用）
System.out.println(Integer.toBinaryString(10)); // "1010"
System.out.println(Integer.toHexString(255));   // "ff"
System.out.println(Integer.parseInt("ff", 16)); // 255（按16进制解析）
```

### 3.5 选用原则

| 场景 | 用哪个 |
|------|--------|
| 集合泛型 / 返回值可能为 null | 包装类（`Integer` 等） |
| 纯数值计算 | 基本类型（无装箱开销，更快） |
| 包装类变量 → int | 先判 null 再拆箱 |

---

## 4. Integer 缓存陷阱

### 4.1 现象

```java
Integer a = 100;  Integer b = 100;
Integer c = 200;  Integer d = 200;
System.out.println(a == b);   // true
System.out.println(c == d);   // false  ← 看起来一模一样，结果却不同！
```

### 4.2 原因：Integer.valueOf() 有缓存

自动装箱调用的是 `Integer.valueOf(n)`，JVM 对 **`[-128, 127]`** 范围内的整数**预先创建好对象并缓存**，每次取的是同一个对象；超出范围每次 `new` 新对象。

```
valueOf(100) → 缓存命中，返回同一对象 → a == b 地址相同 → true
valueOf(200) → 缓存未命中，new 新对象  → c == d 地址不同 → false
```

### 4.3 `==` 的三种场景

| 比较 | 行为 | 可靠？ |
|------|------|--------|
| `Integer == Integer` | 比**对象地址** | ❌ 不可靠（取决于缓存范围） |
| `Integer == int` | 自动**拆箱**后比数值 | ✅ 可靠 |
| `int == int` | 比数值 | ✅ 永远可靠 |

### 4.4 正确做法

```java
Integer x = 200;
Integer y = 200;

// ❌ 不要用 == 比两个 Integer 的数值
System.out.println(x == y);        // false（地址不同）

// ✅ 用 equals 比数值
System.out.println(x.equals(y));   // true

// ✅ 一侧是基本类型，== 触发拆箱，比数值
int z = 200;
System.out.println(x == z);        // true
```

> 一句话：**两个包装类对象比数值 → `.equals()`；包装类和基本类型比 → `==` 自动拆箱，安全。**

### 4.5 与 String 池的类比

| | Integer 缓存 | String 池 |
|--|--|--|
| 范围 | `-128 ~ 127` | 所有字符串字面量 |
| `==` 在池内 | `true`（同一对象） | `true`（同一对象） |
| `==` 在池外 | `false`（不同对象） | `false`（`new` 出来的） |
| 安全比较方式 | `.equals()` | `.equals()` |

**根源相同**：`==` 永远比的是引用（地址），不是内容。包装类和 String 都有对象复用机制，但别依赖它——一律 `.equals()`。

---

## 5. Math / Arrays / 常用工具类

### 5.1 Math 类

`java.lang.Math`，全静态方法，无需导入、无需 `new`，直接 `Math.方法()` 调用。

> 类比 C++：和 `<cmath>` 里的 `abs()`、`pow()`、`sqrt()` 一样，直接调函数。

```java
Math.abs(-5)        // 5        绝对值
Math.max(3, 7)      // 7        最大值
Math.min(3, 7)      // 3        最小值
Math.pow(2, 10)     // 1024.0   幂（返回 double）
Math.sqrt(16)       // 4.0      平方根（返回 double）
Math.ceil(3.1)      // 4.0      向上取整（返回 double）
Math.floor(3.9)     // 3.0      向下取整（返回 double）
Math.round(3.5)     // 4        四舍五入（返回 int/long）
Math.log(Math.E)    // 1.0      自然对数

Math.PI             // 3.141592653589793
Math.E              // 2.718281828459045

// 随机数：[0.0, 1.0) 的 double
double r = Math.random();
int dice = (int)(Math.random() * 6) + 1;  // 模拟骰子 [1,6]
```

> ⚠️ `Math.pow()` 返回 `double`，如需整数结果记得强转：`(int) Math.pow(2, 10)`。

### 5.2 Arrays 工具类

`java.util.Arrays`，操作数组的静态工具类，需要 `import java.util.Arrays`。

```java
int[] arr = {5, 3, 1, 4, 2};

Arrays.sort(arr);                         // 原地升序排序 → [1, 2, 3, 4, 5]
System.out.println(Arrays.toString(arr)); // "[1, 2, 3, 4, 5]"（调试必用）

Arrays.fill(arr, 0);                      // 全部填 0 → [0, 0, 0, 0, 0]

// 复制：新长度 < 原长度 → 截断；新长度 > 原长度 → 用默认值（0/null/false）补齐，不报错
int[] a = {1, 2, 3};
int[] b = Arrays.copyOf(a, 5);           // [1, 2, 3, 0, 0]
int[] c = Arrays.copyOfRange(a, 1, 4);   // [2, 3, 0]（索引 [1, 4)）

// 比较内容
int[] x = {1, 2, 3};
int[] y = {1, 2, 3};
System.out.println(x == y);              // false（比地址）
System.out.println(Arrays.equals(x, y)); // true（比内容）
```

> ⚠️ `System.out.println(arr)` 直接打印数组会输出类似 `[I@1b6d3586` 的地址，用 `Arrays.toString(arr)` 才能看到内容。

### 5.3 Objects 工具类

`java.util.Objects`（注意有 s），用于**安全处理可能为 null 的对象**：

```java
import java.util.Objects;

String s = null;

// null 安全 equals：任意一侧为 null 都不抛 NPE
Objects.equals(s, "hello");            // false（不崩溃）
Objects.equals(null, null);            // true

// null 安全 toString：null 时返回默认值字符串
Objects.toString(s, "默认值");        // "默认值"

// 主动校验：为 null 时抛 NPE（带描述，便于定位）
Objects.requireNonNull(s, "s 不能为 null");
```

> 为什么不直接 `s.equals("hello")`？s 可能是 null，直接调实例方法 → NPE。`Objects.equals` 是防御式写法，后端开发中大量使用。

### 5.4 三个类横向对比

| 工具类 | 包 | 操作对象 | 是否需要 import |
|--------|-----|---------|----------------|
| `Math` | `java.lang` | 数学运算 | 不需要（自动导入） |
| `Arrays` | `java.util` | 数组 | 需要 |
| `Objects` | `java.util` | 任意对象（null 安全） | 需要 |

---

## 6. 异常处理

### 6.1 异常体系结构

```
Throwable
├── Error（系统级，程序无法恢复，不要捕获）
│   ├── OutOfMemoryError
│   └── StackOverflowError
└── Exception（程序级，可以处理）
    ├── RuntimeException（非受检异常）
    │   ├── NullPointerException
    │   ├── ArrayIndexOutOfBoundsException
    │   ├── ClassCastException
    │   ├── NumberFormatException
    │   └── ArithmeticException（除以零）
    └── 受检异常（Checked Exception）
        ├── IOException
        ├── SQLException
        └── FileNotFoundException
```

| | RuntimeException（非受检） | 受检异常 |
|--|--|--|
| 编译器强制处理？ | ❌ | ✅（否则编译报错） |
| 来源 | 代码逻辑 Bug | 外部资源不可控 |
| 典型例子 | NPE、越界、类转换 | 文件、网络、数据库 |

### 6.2 try-catch-finally

```java
try {
    int result = 10 / 0;
} catch (ArithmeticException e) {
    System.out.println(e.getMessage());   // "/ by zero"
    e.printStackTrace();                   // 打印完整堆栈（调试用）
} finally {
    // 无论是否异常、无论 try 里是否有 return，finally 都执行
    System.out.println("finally");
}
```

> ⚠️ `finally` 在 `return` 之前执行——Java 最常考的陷阱之一。

### 6.3 捕获多种异常

```java
// 父类 catch 必须在子类之后，否则编译报错（子类永远不会被执行）
try { ... }
catch (NullPointerException e) { ... }   // 子类在前
catch (RuntimeException e)     { ... }   // 父类在后
catch (Exception e)            { ... }   // 兜底

// Java 7+：一行捕获多种同级异常
catch (NullPointerException | NumberFormatException e) { ... }
```

### 6.4 throw 与 throws

```
throw  → 动词，写在方法体里，"现在抛出一个异常对象"
throws → 声明，写在方法签名后，"调用我时要注意，我可能抛这种异常"
```

```java
public void readFile(String path) throws IOException {
    if (path == null) {
        throw new IllegalArgumentException("path 不能为 null");
    }
    // ...文件读取逻辑
}
```

### 6.5 自定义业务异常

```java
// 继承 RuntimeException（非受检）——Spring Boot 推荐做法
public class BookNotFoundException extends RuntimeException {
    public BookNotFoundException(String message) {
        super(message);
    }
}

// 使用：直接抛，调用链上不用写任何 throws 声明
public Book findById(Long id) {
    Book book = mapper.selectById(id);
    if (book == null) {
        throw new BookNotFoundException("图书不存在，id=" + id);
    }
    return book;
}
```

**为什么继承 RuntimeException？**
业务异常属于"数据不符合预期"，是可控的逻辑错误。如果继承受检 `Exception`，调用链上每一层（Mapper→Service→Controller）都要写 `throws`，代码冗余。用非受检，异常自然冒泡到 Spring 顶层的全局异常处理器统一兜底，代码更简洁。

### 6.6 异常对象常用方法

| 方法 | 返回内容 | 适合场景 |
|------|---------|---------|
| `e.getMessage()` | 构造时传入的消息字符串（如 `"boom"`） | 展示给用户 / 写日志 |
| `e.toString()` | `类名: 消息` | 简洁调试 |
| `e.printStackTrace()` | 完整调用栈 | 开发阶段定位问题 |
| `log.error("msg", e)` | 日志框架格式化 | **生产环境的正确做法** |

---

## 7. 泛型

### 7.1 为什么需要泛型

没有泛型之前，集合只能存 `Object`，取出来必须强转，类型错误推迟到运行时：

```java
// 没有泛型（Java 5 之前）
List list = new ArrayList();
list.add("hello");
list.add(100);                       // 编译通过，可以放任何类型
String s = (String) list.get(1);    // 运行时 ClassCastException！
```

有了泛型，**类型检查在编译期完成**：

```java
List<String> list = new ArrayList<>();
list.add("hello");
list.add(100);                       // ❌ 编译报错，只能放 String
String s = list.get(0);             // 不需要强转
```

> 类比 C++ 模板：目的相同（代码适配多种类型 + 类型安全），但实现不同（Java 用类型擦除，编译后泛型信息会被擦掉）。

### 7.2 泛型类

```java
public class Box<T> {    // T 是类型参数
    private T value;

    public Box(T value) {
        this.value = value;
    }

    public T getValue() {
        return value;
    }
}

// 使用
Box<String> strBox = new Box<>("hello");
Box<Integer> intBox = new Box<>(42);
String s = strBox.getValue();  // 直接拿到 String，无需强转
```

常用类型参数命名：

| 字母 | 惯例含义 |
|------|---------|
| `T` | Type（通用类型） |
| `E` | Element（集合元素） |
| `K` / `V` | Key / Value（Map 的键值） |
| `R` | Return（返回类型） |

> ⚠️ 泛型只能接受**引用类型**，不能用基本类型：`Box<int>` ❌，要用 `Box<Integer>` ✅。

### 7.3 泛型方法

泛型也可以只用在某个方法上（`<T>` 写在返回类型之前）：

```java
public class Utils {
    public static <T> T firstElement(T[] arr) {
        return arr[0];
    }
}

String s = Utils.firstElement(new String[]{"a", "b"});   // 编译器自动推断 T=String
Integer n = Utils.firstElement(new Integer[]{1, 2, 3}); // 推断 T=Integer
```

泛型方法的 `<T>` 和泛型类的 `<T>` 是**独立的**，方法内的 T 会遮蔽类的 T（强烈不推荐同名）：

```java
public class Container<T> {
    // ❌ 不推荐：方法的 T 遮蔽类的 T，极度混乱
    public <T> T wrap(T t) { ... }
    
    // ✅ 用不同字母区分
    public <R> R transform(R r) { ... }
}
```

### 7.4 上界限定：`<T extends 类/接口>`

限制 T 必须是某个类的子类（或实现某个接口）：

```java
// T 必须实现 Comparable 接口
public static <T extends Comparable<T>> T max(T a, T b) {
    return a.compareTo(b) >= 0 ? a : b;
}

max(3, 5);             // ✅ Integer 实现了 Comparable
max("a", "b");         // ✅ String 实现了 Comparable
max(new Object(), new Object());  // ❌ Object 没实现 Comparable
```

> 注意：泛型里 `extends` 同时表示"继承类"和"实现接口"，不用 `implements`。

### 7.5 通配符 `?` 与型变

**核心问题**：`Dog extends Animal`，那 `List<Dog>` 是 `List<Animal>` 的子类吗？

答案：**不是**。Java 泛型是**不变的（invariant）**：

```java
List<Animal> list = new ArrayList<Dog>();  // ❌ 编译报错
// 若允许：你可以往 list 里加 Cat（Cat 也是 Animal），但底层是 Dog 列表 → 类型系统崩溃
```

#### 上界通配符 `? extends T` — 只读

```java
// 接受 Animal 或任何 Animal 子类的 List
public void printAll(List<? extends Animal> list) {
    for (Animal a : list) {      // ✅ 读出来肯定是 Animal
        System.out.println(a.name);
    }
    // list.add(new Dog());       // ❌ 不能写：? 可能是 Cat 的 List
}

printAll(new ArrayList<Dog>());     // ✅
printAll(new ArrayList<Cat>());     // ✅
```

#### 下界通配符 `? super T` — 只写

```java
// 接受 Integer 或任何 Integer 父类的 List（Number、Object）
public void addNumbers(List<? super Integer> list) {
    list.add(1);   // ✅ Integer 肯定是 ? 的子类，写入安全
    list.add(2);
    Object obj = list.get(0);  // 读出只能当 Object（不知道 ? 是谁）
}

addNumbers(new ArrayList<Integer>());  // ✅
addNumbers(new ArrayList<Number>());   // ✅
addNumbers(new ArrayList<Object>());   // ✅
```

#### 无界通配符 `?` — 完全未知

```java
List<?> list = new ArrayList<String>();
Object o = list.get(0);  // ✅ 只能当 Object 读
list.add("hello");       // ❌ 不能写（除了 null）
```

**记忆口诀：PECS**
```
Producer（生产者/读数据） → Extends（上界）
Consumer（消费者/写数据） → Super（下界）
```

### 7.6 `List<?>` vs `List<Object>`

| | `List<?>` | `List<Object>` |
|--|--|--|
| 可接受的实参 | `ArrayList<任意类型>` | 只能 `ArrayList<Object>` |
| add 写入 | ❌（除了 null） | ✅（任何对象） |
| get 读出 | `Object` | `Object` |

```java
List<?> a = new ArrayList<String>();    // ✅
List<Object> b = new ArrayList<String>(); // ❌ 编译报错

List<Object> c = new ArrayList<>();
c.add("hello");  // ✅ Object 是所有类的父类，什么都能加
c.add(42);
```

---

## 8. 集合框架

### 8.1 集合体系结构

```
Collection（接口，单列集合）
├── List（有序、可重复）
│   ├── ArrayList（动态数组，查询快）
│   ├── LinkedList（双向链表，增删快）
│   └── Vector（线程安全，已过时）
│
├── Set（无序、不可重复）
│   ├── HashSet（哈希表，最常用）
│   ├── LinkedHashSet（保持插入顺序）
│   └── TreeSet（红黑树，自动排序）
│
└── Queue（队列）
    ├── LinkedList（也实现了 Queue）
    └── PriorityQueue（优先队列/堆）

Map（接口，键值对，双列集合）
├── HashMap（哈希表，最常用）
├── LinkedHashMap（保持插入顺序）
├── TreeMap（红黑树，按 key 排序）
└── Hashtable（线程安全，已过时）
```

### 8.2 List — 有序可重复

**ArrayList** — 动态数组（默认选它）

```java
List<String> list = new ArrayList<>();
list.add("a");                    // 添加
list.add(0, "first");            // 在索引 0 插入
list.get(1);                     // "a"（按索引取）
list.set(1, "A");                // 修改索引 1
list.remove(0);                  // 删除索引 0
list.remove("A");                // 删除第一个匹配的元素
list.size();                     // 长度
list.contains("b");              // 是否包含

// 遍历
for (String s : list) { }
for (int i = 0; i < list.size(); i++) { }
```

> 类比 C++：和 `std::vector` 一样——底层数组、扩容翻倍、随机访问 O(1)、中间插入 O(n)。

**LinkedList** — 双向链表

```java
LinkedList<String> list = new LinkedList<>();
list.addFirst("头部");
list.addLast("尾部");
list.removeFirst();
list.removeLast();
```

> 类比 C++：和 `std::list` 一样——双向链表、头尾操作 O(1)、随机访问 O(n)。

**选用原则**：查询多用 `ArrayList`；频繁头尾插入删除用 `LinkedList`。

**⚠️ 并发修改异常**

```java
// ❌ 遍历时直接 remove 会抛 ConcurrentModificationException
for (String s : list) {
    list.remove(s);
}

// ✅ 用迭代器的 remove
Iterator<String> it = list.iterator();
while (it.hasNext()) {
    if (it.next().equals("a")) it.remove();
}

// ✅ 倒着删（索引不受影响）
for (int i = list.size() - 1; i >= 0; i--) {
    if (list.get(i).equals("a")) list.remove(i);
}

// ✅ Java 8+ 用 removeIf
list.removeIf(s -> s.equals("a"));
```

### 8.3 Set — 无序、不可重复

**HashSet** — 哈希表（最常用）

```java
Set<String> set = new HashSet<>();
set.add("a");
set.add("b");
set.add("a");   // 重复，不会加进去
System.out.println(set.size());  // 2

set.contains("a");  // true
set.remove("a");

// 遍历（无序！）
for (String s : set) { }
```

> 类比 C++：和 `std::unordered_set` 一样——哈希表、O(1) 增删查、无序、不重复。

**去重原理**：先 `hashCode()` 决定桶，桶内用 `equals()` 确认——这就是为什么重写 `equals` 必须同时重写 `hashCode`。

**详细机制（重要，易混）**：

**未重写 `equals`/`hashCode` 时**：
1. `hashCode()` 基于**内存地址**算哈希值 → 不同对象进不同桶
2. 桶内用 `equals()` 比较**地址**（等同 `==`）→ 内容相同的对象也被视为不同

```java
// 未重写 equals/hashCode
Book b1 = new Book("Java", 99);
Book b2 = new Book("Java", 99);
Set<Book> set = new HashSet<>();
set.add(b1);
set.add(b2);
System.out.println(set.size());  // 2（内容相同，地址不同 → 视为两个对象）
```

**重写 `equals`/`hashCode` 后**：
1. `hashCode()` 基于**字段内容**（如 title、price）算哈希值 → 内容相同的对象进同一个桶
2. 桶内用 `equals()` 比较**字段内容** → 内容一致视为同一对象

```java
// 重写后
@Override
public int hashCode() {
    return Objects.hash(title, price);   // 基于内容算哈希
}

@Override
public boolean equals(Object o) {
    if (this == o) return true;
    if (o == null || getClass() != o.getClass()) return false;
    Book book = (Book) o;
    return Double.compare(price, book.price) == 0
           && Objects.equals(title, book.title);   // 比较内容
}

Book b1 = new Book("Java", 99);
Book b2 = new Book("Java", 99);
set.add(b1);
set.add(b2);
System.out.println(set.size());  // 1（内容相同 → 去重）
```

> **记忆口诀**：`hashCode` 决定桶号，`equals` 桶内确认——两个方法必须基于**相同的字段**，否则 HashSet/HashMap 认不出内容相同的对象。

**TreeSet** — 红黑树（自动排序）

```java
Set<Integer> set = new TreeSet<>();
set.add(5); set.add(1); set.add(3);
System.out.println(set);  // [1, 3, 5]（自动升序）
```

> 类比 C++：和 `std::set` 一样——红黑树、O(log n)、自动排序。

### 8.4 Map — 键值对

**HashMap** — 哈希表（最常用）

```java
Map<String, Integer> map = new HashMap<>();
map.put("Tom", 18);
map.put("Jerry", 20);
map.put("Tom", 19);     // key 重复，覆盖旧值

map.get("Tom");         // 19
map.get("Alice");       // null（key 不存在）
map.getOrDefault("Alice", 0);  // 不存在返回默认值

map.containsKey("Tom");    // true
map.remove("Tom");
map.size();

// 遍历（三种方式）
for (String key : map.keySet()) {
    System.out.println(key + " -> " + map.get(key));
}

for (Map.Entry<String, Integer> entry : map.entrySet()) {
    System.out.println(entry.getKey() + " -> " + entry.getValue());
}

map.forEach((k, v) -> System.out.println(k + " -> " + v));  // Java 8+
```

> 类比 C++：和 `std::unordered_map` 一样——哈希表、O(1) 增删查、无序。

**TreeMap** — 红黑树（按 key 排序）

```java
Map<String, Integer> map = new TreeMap<>();
map.put("c", 3); map.put("a", 1); map.put("b", 2);
System.out.println(map);  // {a=1, b=2, c=3}（按 key 字典序）
```

> 类比 C++：和 `std::map` 一样——红黑树、O(log n)、按 key 排序。

### 8.5 集合工具类 Collections

```java
List<Integer> list = Arrays.asList(3, 1, 2);
Collections.sort(list);                  // [1, 2, 3]
Collections.reverse(list);               // [3, 2, 1]
Collections.shuffle(list);               // 随机打乱
Collections.max(list);                   // 3
Collections.min(list);                   // 1
Collections.frequency(list, 3);          // 元素 3 出现次数
```

### 8.6 Java 集合 vs C++ STL 对照表

| Java | C++ STL | 底层结构 | 复杂度 |
|------|---------|---------|--------|
| `ArrayList` | `vector` | 动态数组 | 随机访问 O(1) |
| `LinkedList` | `list` | 双向链表 | 头尾操作 O(1) |
| `HashSet` | `unordered_set` | 哈希表 | 增删查 O(1) |
| `TreeSet` | `set` | 红黑树 | 增删查 O(log n) |
| `HashMap` | `unordered_map` | 哈希表 | 增删查 O(1) |
| `TreeMap` | `map` | 红黑树 | 增删查 O(log n) |
| `PriorityQueue` | `priority_queue` | 堆 | 入队出队 O(log n) |

---

## 9. Lambda / Stream / Optional

Java 8 引入的函数式编程特性，让集合处理更简洁、声明式。

### 9.1 Lambda 表达式

**本质**：匿名函数，用来实现函数式接口。**语法**：`(参数) -> { 方法体 }`

```java
// 传统：匿名内部类
Runnable r1 = new Runnable() {
    @Override public void run() { System.out.println("hi"); }
};
// Lambda
Runnable r2 = () -> System.out.println("hi");
```

多种形式：
```java
() -> System.out.println("hi")    // 无参
x -> x * 2                         // 单参（括号可省）
(a, b) -> a + b                    // 多参
(a, b) -> { int s = a + b; return s * 2; }  // 多行需大括号 + return
```

> 类比 C++：`x -> x * 2` 对应 C++ 的 `[](int x){ return x*2; }`，但 Java 不需要捕获列表 `[]`。

### 9.2 函数式接口

只有**一个抽象方法**的接口（可含 default / static 方法），用 `@FunctionalInterface` 标记。

| 接口 | 方法 | 用途 | 示例 |
|------|------|------|------|
| `Predicate<T>` | `boolean test(T)` | 判断 | `x -> x > 0` |
| `Function<T,R>` | `R apply(T)` | 转换 | `x -> x * 2` |
| `Consumer<T>` | `void accept(T)` | 消费 | `x -> println(x)` |
| `Supplier<T>` | `T get()` | 生产 | `() -> new User()` |

### 9.3 方法引用

Lambda 只是调用已有方法时，可简写：

| 形式 | 语法 | 示例 |
|------|------|------|
| 静态方法 | `类::静态方法` | `Integer::parseInt` |
| 实例方法 | `对象::方法` | `System.out::println` |
| 类的实例方法 | `类::方法` | `String::length` |
| 构造器 | `类::new` | `ArrayList::new` |

```java
list.forEach(x -> System.out.println(x));  // Lambda
list.forEach(System.out::println);          // 方法引用（等价）
```

### 9.4 Stream API

把集合当"数据流"，链式处理。

**创建**：
```java
list.stream();                    // 从集合
Stream.of("a", "b", "c");         // 直接创建
```

**中间操作**（返回新 Stream，惰性，可链式）：
```java
.filter(n -> n % 2 == 0)   // 筛选（个数可能变少）
.map(n -> n * 2)           // 映射（一对一转换，个数不变）
.sorted()                  // 排序
.distinct()                // 去重
.limit(3)                  // 取前 3 个
.skip(1)                   // 跳过前 1 个
```

**终止操作**（触发计算）：
```java
.collect(Collectors.toList());   // 收集成 List
.forEach(System.out::println);   // 遍历
.count();                        // 计数
.findFirst();                    // 返回 Optional
.anyMatch(n -> n > 10);          // 是否存在满足的
.allMatch(n -> n > 0);           // 是否全部满足
.reduce(0, (a, b) -> a + b);     // 归约（求和等）
.max(Integer::compareTo);        // 最大值（返回 Optional）
```

> ⚠️ **中间操作是惰性的**：只写中间操作、不写终止操作，代码不会执行。

**完整示例**：
```java
List<String> names = Arrays.asList("Tom", "Jerry", "Alice", "Bob");
List<String> result = names.stream()
    .filter(s -> s.length() > 3)   // ["Jerry", "Alice"]
    .map(String::toUpperCase)      // ["JERRY", "ALICE"]
    .sorted()                       // ["ALICE", "JERRY"]
    .collect(Collectors.toList());

// 求和：转 IntStream
int sum = Arrays.asList(1, 2, 3, 4, 5).stream()
    .mapToInt(Integer::intValue).sum();   // 15
```

### 9.5 Optional — 优雅处理 null

包装可能为 null 的值，强制显式处理"值不存在"。

```java
// 创建
Optional.of("hello");        // 值不能为 null，否则 NPE
Optional.ofNullable(x);      // 值可以为 null
Optional.empty();            // 空

// 判断
opt.isPresent();  opt.isEmpty();

// 安全取值（不要用 get()！空时抛 NoSuchElementException）
opt.orElse("default");                 // 空时返回默认值
opt.orElseGet(() -> compute());        // 空时调 Supplier
opt.orElseThrow(() -> new RuntimeException("无值"));

// 有值时处理
opt.ifPresent(s -> System.out.println(s));
opt.map(String::length);               // 转换，返回 Optional
```

**实际场景对比**：
```java
// 传统写法
User user = userMapper.selectById(id);
if (user == null) return "未知";
return user.getName();

// Optional 写法
return Optional.ofNullable(userMapper.selectById(id))
    .map(User::getName)
    .orElse("未知");
```

---

## 📊 全文档总结：Java 核心类速查

| 主题 | 关键点 | 最易错陷阱 |
|------|--------|-----------|
| String | 不可变、常量池 | `==` 比地址，用 `equals` 比内容 |
| StringBuilder | 可变缓冲区 | 循环拼接用它，简单拼接用 `+` |
| 包装类 | int↔Integer | null 拆箱 → NPE |
| Integer 缓存 | `-128~127` | 两个 Integer 比数值用 `equals` |
| Math/Arrays | 静态工具方法 | `copyOf` 超界补默认值不报错 |
| 异常 | 受检 vs 非受检 | `finally` 在 `return` 前执行 |
| 泛型 | 编译期类型检查 | 不接受基本类型；PECS 通配符 |
| 集合 | List/Set/Map | 遍历时删除 → ConcurrentModificationException |
| 函数式 | Lambda/Stream/Optional | Stream 中间操作惰性；别用 `Optional.get()` |

*Java 语言核心复习完毕。下一阶段：Spring Boot 项目实战（从 Maven 开始）。*
