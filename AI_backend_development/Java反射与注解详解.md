# Java 反射与注解详解

> 本文档面向**有 C/C++ 基础、Java 语法已掌握**的学习者，系统讲解反射与注解机制。
> 这是理解 Spring Boot（IoC、依赖注入、注解驱动）的**必备前置知识**。
> 前置：见《Java语言基础详解.md》《Java面向对象详解.md》《Java常用核心类详解.md》。
>
> **为什么要学反射和注解**：Spring、MyBatis 等框架广泛使用注解与反射机制。
> 开发者使用 `@RestController`、`@Autowired`、`@Service` 等注解描述程序结构，框架在运行时读取相关元数据，进而发现类、创建对象和完成依赖注入。
> 掌握这两个机制，有助于理解注解驱动框架的工作原理，而不只是记忆注解的用法。

## 目录

1. [反射（Reflection）：运行时操作类](#1-反射reflection运行时操作类)
   - 1.1 [为什么需要反射](#11-为什么需要反射)
   - 1.2 [Class 对象：类的"说明书"](#12-class-对象类的说明书)
   - 1.3 [用反射创建对象（Constructor）](#13-用反射创建对象constructor)
   - 1.4 [用反射读写字段（Field）](#14-用反射读写字段field)
   - 1.5 [用反射调用方法（Method）](#15-用反射调用方法method)
   - 1.6 [引号 vs 无引号：反射代码的关键规则](#16-引号-vs-无引号反射代码的关键规则)
   - 1.7 [反射 vs 直接调用：什么时候用反射](#17-反射-vs-直接调用什么时候用反射)
2. [注解（Annotation）：给代码贴标签](#2-注解annotation给代码贴标签)
   - 2.1 [注解不是普通注释，而是结构化信息](#21-注解不是普通注释而是结构化信息)
   - 2.2 [Spring 如何读标签并做事](#22-spring-如何读标签并做事)
   - 2.3 [注解为什么可以有参数](#23-注解为什么可以有参数)
   - 2.4 [`@Deprecated`：标记程序元素已经过时](#24-deprecated标记程序元素已经过时)
   - 2.5 [`@SuppressWarnings`：压制指定的编译警告](#25-suppresswarnings压制指定的编译警告)
   - 2.6 [注解是谁写的？能自己写吗？](#26-注解是谁写的能自己写吗)
   - 2.7 [元注解 `@Target`：规定注解能贴在哪里](#27-元注解-target规定注解能贴在哪里)
   - 2.8 [元注解 `@Retention`：规定注解保存到什么时候](#28-元注解-retention规定注解保存到什么时候)
   - 2.9 [注解元素：必填值、默认值与合法类型](#29-注解元素必填值默认值与合法类型)
3. [反射 + 注解：手写迷你 IoC 容器](#3-反射--注解手写迷你-ioc-容器)

---

## 1. 反射（Reflection）：运行时操作类

### 1.1 为什么需要反射

#### 问题场景：框架怎么处理"它不认识的类"？

Spring 框架发布时，不可能预先知道后来由项目开发者编写的 `BookController` 类：

```java
public class BookController {
    public void list() { System.out.println("查询图书列表"); }
}
```

Spring 需要创建这个对象并调用它的方法。但编译 Spring 框架时，项目中的 `BookController` 尚不存在，因此框架源码不能直接引用这个类。

Spring 的源码里能写出这行吗？

```java
BookController c = new BookController();   // ❌ Spring 写不出来！
c.list();                                  // ❌ 编译都过不了
```

**写不出来。** 因为编译 Spring 的时候，`BookController` 根本不存在，编译器都不认识这个类名。

#### 解决方案：反射——用"文本名字"操作类

Spring 只能在应用运行时，根据扫描得到的字符串 `"com.example.BookController"`（来源可能是包扫描、配置或注解元数据）进行后续操作：

```java
// 1. 用字符串找到这个类
Class<?> clazz = Class.forName("com.example.BookController");

// 2. 用反射创建对象
Object controller = clazz.getDeclaredConstructor().newInstance();

// 3. 用反射找到 list 方法
Method listMethod = clazz.getDeclaredMethod("list");

// 4. 用反射调用这个方法
listMethod.invoke(controller);   // 输出：查询图书列表
```

**反射的核心价值之一，是让程序能够在运行时检查并操作编译期未直接引用的类型。**

#### 生活类比

- **直接调用**（正常业务代码）：调用方在编译期已经知道类名和方法名，可以直接创建对象和调用方法。
- **反射调用**（处理运行时才确定的类型）：调用方先在运行时获得类名等元数据，再查找类、构造器和方法。步骤更多，但能够处理编译期未知的类型。

---

### 1.2 Class 对象：类的"说明书"

Java 里，**每个类在运行时都有一个对应的 `Class` 对象**，记录这个类的所有信息：

- 类名、包名
- 有哪些构造方法、字段、方法
- 父类、接口

把 `Class` 对象想象成**一本说明书**：

> `Book.class` = Book 这个类的说明书，记录了 Book 有哪些字段（title / price）、有哪些方法（getTitle / setTitle）、构造方法是什么样。

有了说明书，反射才知道怎么"造对象"、"调方法"。

#### 获取 Class 对象的三种方式

```java
// 方式 1：类名.class（编译期就确定）
Class<Book> c1 = Book.class;

// 方式 2：对象.getClass()（运行时从对象反推）
Book book = new Book();
Class<? extends Book> c2 = book.getClass();

// 方式 3：Class.forName("完整类名")（用字符串查找，框架常用）
Class<?> c3 = Class.forName("com.example.Book");

// 三者拿到的是同一个 Class 对象
System.out.println(c1 == c2);   // true
System.out.println(c2 == c3);   // true
```

| 方式 | 使用场景 | 是否需要类已加载 |
|------|---------|:---:|
| `Book.class` | **编译期**已知类名（普通直接引用场景） | 是 |
| `obj.getClass()` | 已有对象，要反推它的类型 | 是（对象都在了） |
| `Class.forName("...")` | **运行时**才知道类名（字符串）<br>**框架的核心手段** | 否（动态加载） |

> **第三种是框架的关键**：Spring 从配置文件/注解拿到类全名（字符串），用 `Class.forName` 动态加载，然后用反射操作它。

---

### 1.3 用反射创建对象（Constructor）

#### 为什么需要反射创建对象

正常情况下创建对象：

```java
Book book = new Book("Java核心", 99.0);   // 直接 new
```

但框架写代码时**不知道 Book 是什么**，只能拿着类名字符串：

```java
Class<?> clazz = Class.forName("com.example.Book");
// 现在要创建一个 Book 对象——怎么办？用反射
```

#### 核心类：`Constructor`（构造器类）

`java.lang.reflect.Constructor` 代表一个构造方法，用它来"造对象"。

```java
import java.lang.reflect.Constructor;

// 1. 获取构造方法
Constructor<?> constructor = clazz.getDeclaredConstructor(String.class, double.class);
// 意思：找到参数是 (String, double) 的那个构造方法

// 2. 如果构造方法是 private，需要"开锁"
constructor.setAccessible(true);

// 3. 用这个构造方法创建对象
Object book = constructor.newInstance("Java核心", 99.0);
System.out.println(book);   // Book{title='Java核心', price=99.0}
```

#### 生活类比

> Class 对象 = 汽车使用手册，记录了这辆车怎么启动（构造方法）。
>
> `Constructor` = 手册里"启动步骤"那一页。
>
> `constructor.newInstance(...)` = 照着这一页的步骤，真的启动车（造对象）。

#### 获取构造方法的两种 API

| 方法 | 作用 | 能拿到什么 |
|------|------|-----------|
| `getConstructor(参数类型...)` | 获取 **public** 构造方法 | 只能拿 public 的 |
| `getDeclaredConstructor(参数类型...)` | 获取**任意**构造方法（包括 private） | 全都能拿，但 private 要先 `setAccessible(true)` |

> 类比：`getConstructor` = 只能进"前门"（public）；`getDeclaredConstructor` = 能进所有门，但锁着的门（private）要先开锁。

#### 为什么构造方法也能是 private？框架怎么调？

```java
public class Book {
    private String title;

    private Book(String title) {   // 私有构造方法（单例模式常见）
        this.title = title;
    }
}
```

外部类写 `new Book("x")` **编译报错**（private 不可见）。

但框架用反射：

```java
Constructor<?> c = Book.class.getDeclaredConstructor(String.class);
c.setAccessible(true);   // 强行开锁
Object book = c.newInstance("偷偷创建");   // ✅ 成功创建
```

> **封装在框架面前是名义上的**——只要有反射 + `setAccessible(true)`，任何 private 成员都能被访问。
>
> 这也是为什么"安全敏感的代码不能只靠 private 保护"——运行时反射能绕过一切访问控制。

---

### 1.4 用反射读写字段（Field）

#### 核心类：`Field`（字段类）

`java.lang.reflect.Field` 代表一个字段（成员变量）。

```java
import java.lang.reflect.Field;

Book book = new Book();

// 1. 获取 title 字段
Field titleField = Book.class.getDeclaredField("title");

// 2. 如果字段是 private，需要开锁
titleField.setAccessible(true);

// 3. 读取字段值
Object value = titleField.get(book);
System.out.println(value);   // null（默认值）

// 4. 写入字段值
titleField.set(book, "反射写入的书名");
System.out.println(book.getTitle());   // "反射写入的书名"
```

#### 生活类比

> `Field` = 储物柜的"柜门"。
>
> `titleField.get(book)` = 打开 book 这个柜子的 title 格子，看里面放了什么。
>
> `titleField.set(book, "新值")` = 往格子里塞一个新东西。
>
> `setAccessible(true)` = 撬锁（即使柜门原本锁着，也能绕过访问检查将其打开）。

#### getDeclaredField vs getField

| 方法 | 作用 |
|------|------|
| `getField("字段名")` | 只能拿 **public** 字段 |
| `getDeclaredField("字段名")` | 能拿**所有字段**（包括 private），但 private 要先 `setAccessible(true)` |

> 规律：带 `Declared` 的能拿所有成员，不带的只能拿 public 的。Constructor / Method 同理。

---

### 1.5 用反射调用方法（Method）

#### 核心类：`Method`（方法类）

`java.lang.reflect.Method` 代表一个方法。

```java
import java.lang.reflect.Method;

Book book = new Book();

// 1. 获取 setTitle 方法（参数类型是 String）
Method setTitle = Book.class.getDeclaredMethod("setTitle", String.class);

// 2. 如果方法是 private，需要开锁
setTitle.setAccessible(true);

// 3. 调用这个方法：invoke(在哪个对象上调, 传入的参数...)
setTitle.invoke(book, "Java核心");
// 等同于：book.setTitle("Java核心");

System.out.println(book.getTitle());   // "Java核心"
```

#### 生活类比

> `Method` = 储物柜上的"按钮"（比如"打开柜门"按钮）。
>
> `getDeclaredMethod("setTitle", String.class)` = 找到标着"setTitle"的那个按钮，并且确认它接受 String 类型的输入。
>
> `setTitle.invoke(book, "Java核心")` = 按下 book 这个柜子上的 setTitle 按钮，传入"Java核心"这个参数。

#### invoke 的两个参数

```java
method.invoke(对象, 参数1, 参数2, ...);
```

- **第一个参数**：在**哪个对象**上调这个方法（相当于 C++ 的 `this` 指针）。
- **后续参数**：传给方法的**实参**。

```java
Method setTitle = Book.class.getDeclaredMethod("setTitle", String.class);
setTitle.invoke(book, "Java核心");
// 相当于：book.setTitle("Java核心");
```

#### 为什么 getDeclaredMethod 要传参数类型？

因为 Java 支持**方法重载**——同一个名字可以有多个方法：

```java
public void setTitle(String title) { }
public void setTitle(String title, String subtitle) { }
```

因此，反射查找方法时需要同时提供方法名和参数类型，才能唯一确定目标方法：

```java
Method m1 = clazz.getDeclaredMethod("setTitle", String.class);          // 一个参数的
Method m2 = clazz.getDeclaredMethod("setTitle", String.class, String.class);  // 两个参数的
```

> 类比：餐厅里只说“炒饭”可能不足以确定具体菜品，还需要说明“蛋炒饭”或“肉炒饭”。同理，方法名相同时，需要用参数类型区分不同重载。

---

### 1.6 引号 vs 无引号：反射代码的关键规则

反射代码里会看到**带双引号**和**不带引号**两种写法混在一起，初学者容易混淆。核心规则：

### 核心规则：引号 = 文本，无引号 = 标识符

| 写法 | 含义 | 编译器怎么处理 |
|------|------|---------------|
| `"getPrice"` | 一段**字符串文本** | 当成"数据"，不去理解它的含义 |
| `getPrice` | **标识符**（变量名/类名/方法名） | 当成"符号"，去查它指向谁；查不到就报错 |

#### 生活类比

> - 带引号的 `"张三"` = 我在纸上**写下"张三"这三个字**（一段文字，谁看了都只是字）。
> - 不带引号的 `张三` = 我喊的那个**真人张三**（编译器得真的找到这个人，找不到就报错）。

#### 反射代码实例

```java
Class<?> c = Class.forName("com.example.Book");   // ← "..." 字符串
Method m = c.getDeclaredMethod("setTitle", String.class);  // ← "setTitle" 字符串 + String.class 类型
m.invoke(book, "Java核心");                       // ← book 变量 + "Java核心" 字符串
```

| 写法 | 带不带引号 | 它是什么 |
|------|:---:|------|
| `"com.example.Book"` | 带 | 类的全名，一段**文本**（反射照着它找类） |
| `"setTitle"` | 带 | 方法名，一段**文本**（反射照着它找方法） |
| `"Java核心"` | 带 | 传给方法的实参，恰好是个**字符串** |
| `String.class` | 不带 | **类型对象**（String 这个类的"说明书"） |
| `book` | 不带 | **变量**（指向那个对象） |

#### 为什么反射要用"文本名字"？

**因为反射就是用来操作"编译期不认识的类"的。**

- 框架编译时，不知道以后由应用项目定义的 `BookController`，因此不能在框架源码中直接引用该标识符。
- 框架可以在应用运行时获得类的全限定名字符串，例如 `"com.example.BookController"`，再通过反射查找并操作对应类型。

如果省略双引号，写成：

```java
Method m = c.getDeclaredMethod(setTitle, String.class);   // 不带引号
```

编译器会去找"有没有一个叫 `setTitle` 的**变量**"：

- **找不到** → 报错：`cannot find symbol - variable setTitle`
- **找到了但类型不对**（比如 `int setTitle = 100;`）→ 报错：`incompatible types: int cannot be converted to String`
- **找到了且是 String**（比如 `String setTitle = "setTitle";`）→ ✅ 编译通过，等同于传 `"setTitle"`

#### 一句话总结

> **反射的特点，就是把原本的"代码符号"（方法名、类名）降级成"文本字符串"来处理**——这正是它能操作"编译期不认识的类"的原因。

---

### 1.7 反射 vs 直接调用：什么时候使用反射

#### 编译期已知目标：优先直接调用

如果类名和方法名在编译期已经确定，应优先使用普通 Java 语法：

```java
Book book = new Book("Java核心", 99.0);
book.setTitle("改名");
```

直接调用具有明显优势：

- 代码简洁，可读性强；
- 编译器能够检查类型和方法签名；
- IDE 可以安全地补全和重构；
- 通常比反射调用开销更低。

用反射完成同一操作需要更多步骤：

```java
Class<?> clazz = Class.forName("com.example.Book");
Constructor<?> constructor =
        clazz.getDeclaredConstructor(String.class, double.class);
Object book = constructor.newInstance("Java核心", 99.0);

Method setTitle = clazz.getDeclaredMethod("setTitle", String.class);
setTitle.invoke(book, "改名");
```

因此，反射不应作为普通方法调用的替代品。

#### 运行时才能确定目标：使用反射

当程序在编译期无法确定具体类型或成员，而相关信息要到运行时才能从配置、注解、插件或扫描结果中获得时，反射就有了必要性。

常见场景包括：

- Spring 等框架扫描并创建项目中的组件；
- Jackson 根据对象结构完成 JSON 序列化和反序列化；
- JUnit 发现并执行测试方法；
- 插件系统根据配置动态加载实现类；
- 通用开发工具检查类的结构。

以 Spring 为例，框架编译时无法直接引用以后由项目定义的 `BookController`，只能在应用启动时获得类的元数据，再创建对象：

```java
Class<?> clazz = Class.forName("com.example.BookController");
Object controller = clazz.getDeclaredConstructor().newInstance();
```

使用原则可以概括为：

> **编译期已知具体类型和成员时，优先直接调用；运行时才获得类型或成员信息时，考虑使用反射。**

#### 反射与代理的区别

反射和代理都引入了间接调用，但解决的问题不同：

- **反射（Reflection）**：在运行时检查类型信息，并动态创建对象、读写字段或调用方法；
- **代理（Proxy）**：在调用目标对象前后加入转发、日志、事务、权限检查等附加逻辑。

二者可以配合使用。例如，Java 动态代理最终可以通过反射调用目标对象的方法；Spring AOP 也会根据场景使用代理机制实现方法拦截。

---

## 2. 注解（Annotation）：给代码贴标签

### 2.1 注解不是普通注释，而是结构化信息

先区分两个容易混淆的概念：

```java
// 这是普通注释，只写给人看，编译器不会拿它指导程序行为

@Override   // 这是注解，能被编译器识别和检查
public void speak() { }
```

- **普通注释（comment）**：写给人看；编译器基本忽略。
- **注解（annotation）**：写给编译器、开发工具或运行中的框架读取的**结构化信息**。

所以，不能笼统地说“注解就是给编译器看的注释”。更准确的说法是：

> **注解是贴在代码上的机器可读标签；由谁读取，取决于这个注解的设计目的。**

#### 同一个标签系统，可以有不同的“读标签者”

| 注解 | 谁读取 | 读取后做什么 |
|------|--------|--------------|
| `@Override` | Java 编译器 | 检查方法是否真的重写了父类方法 |
| `@Deprecated` | 编译器、IDE 等开发工具 | 在使用过时程序元素时给出警告 |
| `@SuppressWarnings` | Java 编译器 | 不显示指定类别的编译警告 |
| `@Service` | Spring 框架 | 识别业务类，创建对象并交给 IoC 容器管理 |
| `@Autowired` | Spring 框架 | 找到需要的对象并注入到标记位置 |

#### 为什么说“注解本身不做事”？

书上的“仅限馆内阅读”标签不会自己阻止读者把书带出去。真正执行规则的是看到标签的管理员。

同理，注解只保存标签信息：

```java
@Override
public void speak() { }
```

`@Override` 自己不会执行检查。真正检查的是 Java 编译器：

1. 编译器看到 `@Override`；
2. 查找父类或接口中有没有相同方法；
3. 找到则编译通过；
4. 找不到则编译报错。

即使不写 `@Override`，只要方法签名正确，Java 的重写仍然成立。它的作用是让编译器帮助发现拼错方法名、写错参数等问题。

### 2.2 Spring 如何“读标签并做事”

以 `@Service` 为例：

```java
@Service
public class BookService { }
```

可以把 Spring 启动时的核心过程暂时理解为：

1. Spring 扫描指定包中的类；
2. 得到每个类对应的 `Class` 对象；
3. 通过反射询问：“这个类有没有 `@Service` 标签？”；
4. 如果有，就通过反射调用构造方法创建对象；
5. 把对象保存到 IoC 容器中，供其他类使用。

概念化的简化代码如下：

```java
Class<?> clazz = BookService.class;

if (clazz.isAnnotationPresent(Service.class)) {
    Object bean = clazz.getDeclaredConstructor().newInstance();
    // 把 bean 保存进 IoC 容器
}
```

这里有一个重要分工：

- Spring **不预先认识应用项目以后定义的 `BookService`**；
- Spring **认识自身定义的 `@Service` 标签**；
- 因此框架无须预先引用每一个业务类，只需在应用启动时查找自己认识的标签。

两者的分工是：开发者负责声明注解，Spring 负责读取注解并执行相应规则。

### 2.3 注解为什么可以有参数

标签不仅可以表示“有或没有”，还可以携带额外信息。

例如快递包裹上的标签不只是写“易碎品”，还可能记录：

- 易碎等级：高；
- 处理方式：轻拿轻放；
- 负责人：张三。

注解参数就是标签中携带的这些**配置数据**：

```java
@SuppressWarnings("unchecked")
```

这里：

- `@SuppressWarnings` 表示“压制编译警告”；
- `"unchecked"` 进一步告诉编译器：只压制 **unchecked（未经检查）** 这一类警告。

不同注解需要的信息不同：

```java
@Override                         // 不需要参数：检查重写即可
@SuppressWarnings("unchecked")   // 需要参数：说明压制哪类警告
@RequestMapping("/books")        // 需要参数：说明对应哪个请求路径
```

因此，**参数不是为了让注解自己执行代码，而是给读取注解的人提供更具体的处理依据。**

### 2.4 `@Deprecated`：标记程序元素已经过时

```java
public class SearchUtil {
    @Deprecated
    public static void oldSearch() {
        System.out.println("旧版搜索方式");
    }
}
```

调用它仍然可以编译和运行：

```java
SearchUtil.oldSearch();   // 可以运行，但编译器或 IDE 会给出“已过时”警告
```

`@Deprecated` 的意思不是“禁止使用”，而是：

> 这个类、方法或字段仍被保留以兼容旧代码，但不推荐新代码继续使用，将来可能删除，请改用新版 API。

它由 JDK 提供，主要由编译器和 IDE 读取。

### 2.5 `@SuppressWarnings`：压制指定的编译警告

泛型代码中可能出现“未经检查的类型转换”警告：

```java
List rawList = new ArrayList();
List<String> names = rawList;   // unchecked conversion 警告
```

如果开发者已经确认风险可控，可以写：

```java
@SuppressWarnings("unchecked")
public void loadNames() {
    List rawList = new ArrayList();
    List<String> names = rawList;
}
```

它表示：编译这个方法时，不显示 `unchecked` 类别的警告。

必须注意：

- 它只**隐藏警告提示**，不会修复代码中的问题；
- 它不能隐藏编译错误；
- 它不能阻止 `NullPointerException` 等运行时异常；
- 应尽量缩小使用范围，不要为了“界面干净”而随意压制警告。

### 2.6 注解是谁写的？能自己写吗？

注解来源通常分为三类：

1. **JDK 编写**：`@Override`、`@Deprecated`、`@SuppressWarnings`；
2. **框架编写**：Spring 的 `@Service`、`@Autowired`、`@RestController`；
3. **开发者自定义**：应用或框架开发者也可以定义新的注解。

一个最简单的自定义注解：

```java
public @interface Important {
    String reason();
}
```

逐部分理解：

- `public`：其他类可以使用它；
- `@interface`：Java 专门用于“定义注解类型”的语法，不是普通接口；
- `Important`：注解名字，使用时写成 `@Important`；
- `String reason()`：定义一个名为 `reason`、类型为 `String` 的注解参数。

使用它：

```java
@Important(reason = "涉及用户数据")
public void deleteUser() { }
```

但是，仅仅贴上这个自定义标签，程序**不会自动发生任何变化**。还必须编写一个“读标签的人”：通过反射找到 `@Important`，读取 `reason`，再执行权限检查、日志记录等规则。

自定义注解还涉及两个关键问题：

- 允许贴在类、方法还是字段上？
- 只保留到编译阶段，还是运行时也能被反射读取？

这两个问题由“元注解”控制。

### 2.7 元注解 `@Target`：规定注解能贴在哪里

#### 什么是元注解

普通注解贴在类、方法或字段等程序元素上；**元注解是专门贴在“注解定义”上的注解**，用于说明另一个注解应该怎样使用。

生活中可以把它理解成“标签的使用说明书”：

> 仓库制作了一个“易碎品”标签，同时规定它只能贴在包裹上，不能贴在员工身上。
>
> `@Target` 就负责规定一个 Java 注解允许贴在什么位置。

#### 只允许贴在方法上

```java
import java.lang.annotation.ElementType;
import java.lang.annotation.Target;

@Target(ElementType.METHOD)
public @interface Important {
    String reason();
}
```

逐项理解：

- `@Target(...)`：为 `@Important` 规定可使用的位置；
- `ElementType`：JDK 提供的枚举类型，列出了各种代码位置；
- `ElementType.METHOD`：枚举值，表示“方法”；
- 因此整句的意思是：`@Important` 只能贴在方法上。

正确使用：

```java
public class UserService {
    @Important(reason = "涉及用户数据")
    public void deleteUser() { }
}
```

错误使用：

```java
@Important(reason = "重要业务类")   // 编译报错：@Important 不允许贴在类上
public class UserService { }
```

这里不需要等到程序运行。编译器看到 `@Target(ElementType.METHOD)` 后，就能在编译阶段检查注解位置是否合法。

#### 允许贴在多个位置

如果既允许贴在类上，又允许贴在方法上，可以传入多个枚举值：

```java
@Target({ElementType.TYPE, ElementType.METHOD})
public @interface Important {
    String reason();
}
```

这里的 `{...}` 表示一个数组，即向 `@Target` 传入两个允许位置：

- `ElementType.TYPE`：类、接口、枚举等类型声明；
- `ElementType.METHOD`：方法声明。

所以以下两种写法都合法：

```java
@Important(reason = "核心业务类")
public class UserService {

    @Important(reason = "涉及用户数据")
    public void deleteUser() { }
}
```

#### `@Target(...)` 中省略了什么

下面这一行看似只有一个参数，实际上同时应用了**两条彼此独立的注解语法简化规则**：

```java
@Target(ElementType.METHOD)
```

`@Target` 在 JDK 中的定义可以简化理解为：

```java
public @interface Target {
    ElementType[] value();
}
```

这里的 `ElementType[] value()` 不是普通业务方法，而是在定义一个名为 `value`、类型为 `ElementType[]` 的**注解元素（注解参数）**。

它的完整写法是：

```java
@Target(value = {ElementType.METHOD})
```

Java 又依次提供了两条省略规则：

**规则一：注解参数名是 `value` 时，可以省略 `value =`。**

```java
@Target(value = {ElementType.METHOD})
// 等价于
@Target({ElementType.METHOD})
```

这个规则只对名为 `value` 的注解元素成立。如果参数叫 `reason`，就不能写成 `@Important("...")`，而应写成：

```java
@Important(reason = "涉及用户数据")
```

**规则二：数组只有一个元素时，可以省略数组花括号。**

```java
@Target({ElementType.METHOD})
// 等价于
@Target(ElementType.METHOD)
```

多个元素不能省略 `{}`：

```java
@Target({ElementType.TYPE, ElementType.METHOD})
```

所以，最完整形式到最常见形式的变化是：

```java
@Target(value = {ElementType.METHOD})   // 完整写法
@Target({ElementType.METHOD})           // 省略 value =
@Target(ElementType.METHOD)             // 单元素数组再省略 {}
```

> “单元素数组可以省略 `{}`”与“名为 `value` 的注解元素可以省略 `value =`”是两条独立规则，不要将二者混为一谈。

#### 常见 `ElementType` 速查

| 枚举值 | 允许标记的位置 |
|--------|----------------|
| `TYPE` | 类、接口、枚举等类型声明 |
| `METHOD` | 方法 |
| `FIELD` | 成员字段 |
| `CONSTRUCTOR` | 构造方法 |
| `PARAMETER` | 方法或构造方法的参数 |
| `LOCAL_VARIABLE` | 局部变量 |
| `ANNOTATION_TYPE` | 另一个注解定义 |

当前重点是 `TYPE`、`METHOD` 和 `FIELD`，它们也是框架注解中最常见的目标位置。

> `@Target` 只回答“允许贴在哪里”，不决定注解能保存到什么时候，也不负责执行注解对应的业务逻辑。

### 2.8 元注解 `@Retention`：规定注解保存到什么时候

#### 先理解“保存期限”

贴在代码上的注解不一定永远存在。可以把 Java 程序从源码到运行分为三个阶段：

```text
.java 源代码  →  javac 编译  →  .class 字节码  →  JVM 加载并运行
   源码阶段          编译阶段          运行阶段
```

生活中，不同标签有不同的保存期限：

- 草稿纸上的校对标记：检查完原稿就丢掉；
- 印在产品包装上的生产标记：进入仓库后仍保留；
- 设备运行时还要扫描的二维码：使用期间必须一直存在。

`@Retention` 中的 `retention` 就是“保留”的意思。它规定一个注解在 Java 的哪个阶段还存在。

#### 三种保留策略

`@Retention` 接收一个 `RetentionPolicy` 枚举值：

```java
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
```

| 策略 | `.java` 源码中 | `.class` 字节码中 | 运行时可用反射读取 | 典型用途 |
|------|:---:|:---:|:---:|------|
| `RetentionPolicy.SOURCE` | ✅ | ❌ | ❌ | 只供编译器检查 |
| `RetentionPolicy.CLASS` | ✅ | ✅ | ❌ | 写入字节码，但普通运行时反射不读取；也是默认值 |
| `RetentionPolicy.RUNTIME` | ✅ | ✅ | ✅ | 运行中的框架通过反射读取 |

可以把它们记成三个越来越长的保质期：

```text
SOURCE：只存在于源代码，编译后丢弃
CLASS：写入 .class 文件，但普通运行时反射不可见
RUNTIME：写入 .class 文件，并在运行时对反射可见
```

> **常见混淆**：`SOURCE` 与 `CLASS` 的区别不在于 JVM 是否加载业务类。无论采用哪种注解保留策略，JVM 都可以正常加载对应的业务类。区别在于**注解元数据是否写入 `.class`，以及运行时反射是否能看到它**：
>
> - `SOURCE`：注解元数据不进入 `.class`；
> - `CLASS`：注解元数据进入 `.class`，但普通反射 API 看不到；
> - `RUNTIME`：注解元数据进入 `.class`，普通反射 API 也能读取。

#### `SOURCE`：编译后就丢弃

`@Override` 的核心用途是让编译器检查方法重写。检查完成以后，JVM 运行时不再需要它，因此它采用 `SOURCE`：

```java
@Retention(RetentionPolicy.SOURCE)
public @interface Override { }
```

这里只展示与当前知识相关的简化结构。它表达的是：`@Override` 存在于源代码中，但编译后不必保留到 `.class` 文件。

#### `CLASS`：写进字节码，但运行时反射不可见

```java
@Retention(RetentionPolicy.CLASS)
public @interface BuildInfo { }
```

这种注解会写入 `.class` 文件，可供字节码工具使用，但通常不能通过下面的运行时反射 API 读到：

```java
clazz.isAnnotationPresent(BuildInfo.class);   // 通常为 false
```

如果自定义注解**完全不写 `@Retention`**，默认就是 `RetentionPolicy.CLASS`。

#### `RUNTIME`：运行时仍然保留

Spring 要在程序启动后读取 `@Service`、`@Autowired` 等标签，因此这类注解必须保留到运行时：

```java
@Retention(RetentionPolicy.RUNTIME)
public @interface Important {
    String reason();
}
```

现在，运行时程序才能通过反射查询并读取它：

```java
Method method = UserService.class.getDeclaredMethod("deleteUser");

boolean present = method.isAnnotationPresent(Important.class);
System.out.println(present);   // 贴了 @Important 时输出 true
```

如果要进一步取得标签对象和其中的参数：

```java
Important important = method.getAnnotation(Important.class);
System.out.println(important.reason());
```

这两行的含义是：

1. `getAnnotation(Important.class)`：从方法上取得 `@Important` 标签对象；
2. `important.reason()`：读取标签中保存的 `reason` 参数。

这几行构成了一个最小的运行时注解读取过程：

- `@Important(...)` 负责保存元数据；
- `Method` 反射对象代表目标方法；
- `getAnnotation(...)` 负责取得标签；
- 后续处理代码负责根据标签内容执行具体规则。

#### `@Target` 与 `@Retention` 的分工

```java
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Important {
    String reason();
}
```

| 元注解 | 回答的问题 |
|--------|------------|
| `@Target` | `@Important` **能贴在哪里**？——方法上 |
| `@Retention` | `@Important` **保存到什么时候**？——程序运行时 |

> 需要通过运行时反射读取的自定义注解，必须使用 `@Retention(RetentionPolicy.RUNTIME)`；否则注解虽然出现在源码中，运行时反射却无法获得它。

### 2.9 注解元素：必填值、默认值与合法类型

#### 注解元素是什么

自定义注解中的下面一行：

```java
String reason();
```

称为一个**注解元素（annotation element）**，也常被称为“注解属性”。它规定 `@Important` 可以携带一个名为 `reason`、类型为 `String` 的数据项。

它的外观像无参数方法，但这里不是在编写普通业务方法：

- 没有方法体；
- 不能在其中编写执行逻辑；
- 使用注解时为它提供值；
- 通过注解对象读取时使用类似方法调用的语法。

```java
@Important(reason = "涉及用户数据")   // 写入 reason
public void deleteUser() { }

String text = important.reason();      // 读取 reason
```

可以把注解类型理解为“标签模板”，把注解元素理解为模板上需要填写的栏目。

#### 没有默认值：使用时必须填写

```java
public @interface Important {
    String reason();
}
```

`reason` 没有默认值，因此每次使用 `@Important` 都必须填写：

```java
@Important(reason = "涉及用户数据")   // 正确
public void deleteUser() { }
```

如果省略：

```java
@Important   // 编译错误：缺少 reason 的值
public void deleteUser() { }
```

这类元素可以理解为标签上的“必填栏”。缺少必填值属于语法不完整，因此在编译阶段报错。

#### 使用 `default` 提供默认值

注解元素可以使用 `default` 声明默认值：

```java
public @interface Important {
    String reason() default "未说明原因";
}
```

此时既可以显式填写：

```java
@Important(reason = "涉及用户数据")
public void deleteUser() { }
```

也可以省略：

```java
@Important
public void rebuildIndex() { }
```

读取第二个注解时：

```java
Important important = method.getAnnotation(Important.class);
System.out.println(important.reason());   // 未说明原因
```

`default` 不是“读取不到时返回的兜底值”，而是注解定义中正式声明的默认配置；省略该元素时，注解对象记录并返回这个默认值。

> 注解元素使用 `default`，不是普通方法参数的 `=` 赋值语法。应写 `String reason() default "...";`，不能写 `String reason() = "...";`。

#### 多个注解元素

一个注解可以携带多个数据项：

```java
public @interface Important {
    String reason();
    int level() default 1;
}
```

使用时：

```java
@Important(reason = "删除用户", level = 3)
public void deleteUser() { }
```

多个元素之间使用逗号分隔。如果省略 `level`，它就采用默认值 `1`；`reason` 没有默认值，因此仍然必须填写。

#### 名为 `value` 的特殊省略规则

如果注解只有一个元素，并且它的名字是 `value`：

```java
public @interface Route {
    String value();
}
```

完整写法是：

```java
@Route(value = "/books")
```

由于元素名是 `value`，可以省略 `value =`：

```java
@Route("/books")
```

这也是 Spring 中常见写法的来源：

```java
@RequestMapping("/books")
```

它可以理解为省略了：

```java
@RequestMapping(value = "/books")
```

如果注解中还定义了其他带默认值的元素：

```java
public @interface Route {
    String value();
    String method() default "GET";
}
```

只填写 `value` 时，仍可使用简写：

```java
@Route("/books")   // method 使用默认值 "GET"
```

如果要同时填写多个元素，则必须为每个元素写出名称：

```java
@Route(value = "/books", method = "POST")
```

Java 不允许把上面这行写成 `@Route("/books", method = "POST")`。`@Route("/books")` 属于单元素注解语法，`@Route(value = ..., method = ...)` 属于普通注解语法，二者不能混合使用。

#### 注解元素允许哪些类型

注解数据必须能在编译阶段写入类文件，因此可使用的类型受到限制。常见合法类型包括：

| 类型类别 | 示例 |
|----------|------|
| 基本类型 | `int level()`、`boolean enabled()` |
| `String` | `String reason()` |
| `Class` | `Class<?> targetType()` |
| 枚举 | `RetentionPolicy policy()` |
| 注解类型 | `Meta meta()` |
| 上述类型的一维数组 | `String[] tags()`、`Class<?>[] types()` |

示例：

```java
public @interface TaskInfo {
    String name();
    int priority() default 1;
    boolean enabled() default true;
    Class<?> handler();
    String[] tags() default {};
}
```

以下类型不能作为注解元素类型：

```java
List<String> tags();   // 错误：不能使用集合
Object value();        // 错误：不能使用任意 Object
User user();           // 错误：不能使用普通自定义对象
```

还要注意两个限制：

- 注解元素不能使用 `null` 作为默认值；
- 数组默认值可以写成空数组 `{}`，表示没有元素。

#### 小结

| 写法 | 含义 |
|------|------|
| `String reason();` | 必填的字符串元素 |
| `int level() default 1;` | 默认值为 `1` 的整数元素 |
| `String value();` | 使用时可省略 `value =` |
| `String[] tags() default {};` | 默认是空数组的字符串数组元素 |

---

## 3. 反射 + 注解：手写迷你 IoC 容器

本章将在介绍完注解的组成、默认值、其他常用元注解和运行时读取方式后，通过完整示例模拟 IoC 容器的核心流程。
