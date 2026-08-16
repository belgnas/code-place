# XPath 语法详解

XPath（XML Path Language）是一种在 XML、HTML 文档中定位节点的查询语言，常用于网页爬虫、XML 数据处理和 Selenium 等自动化测试工具。

可以把 HTML 看作一棵树，XPath 就是节点在这棵树中的“地址”。

## 1. 基本路径

### `/`：从根节点逐层查找

```xpath
/html/body/div/h1
```

这种写法要求层级完全准确，页面结构变化后容易失效。

### `//`：在任意位置查找

```xpath
//h1
//div//a
```

- `//h1`：查找文档中所有 `h1`。
- `//div//a`：查找所有 `div` 后代中的 `a`，不要求 `a` 是直接子节点。

### `.`：当前节点

```xpath
./a
.//a
```

- `./a`：当前节点的直接子节点 `a`。
- `.//a`：当前节点内任意层级的 `a`。

在循环处理元素时，应使用相对 XPath：

```python
items = tree.xpath('//li[@class="item"]')

for item in items:
    name = item.xpath('string(./a)').strip()
```

如果在循环中写 `item.xpath('//a')`，某些库会从整个文档重新搜索，而不是只搜索当前 `li`。

### `..`：父节点

```xpath
//span[@class="price"]/..
```

表示找到价格 `span` 后返回其父节点。

### `*`：任意元素

```xpath
//div/*
//*[@id="main"]
```

## 2. 属性定位

XPath 使用 `@属性名` 表示属性。

### 属性完全匹配

```xpath
//div[@id="main"]
//li[@class="item"]
//a[@href="/product/1"]
```

### 多个条件

```xpath
//input[@type="text" and @name="username"]
//input[@type="text" or @type="password"]
```

### 判断属性是否存在

```xpath
//a[@href]
//input[not(@disabled)]
```

- `[@href]`：存在 `href` 属性。
- `[not(@disabled)]`：不存在 `disabled` 属性。

## 3. 文本与属性获取

### 获取直接文本

```xpath
//h1/text()
//li/a/text()
```

`text()` 只获取元素的直接文本节点。例如：

```html
<div>价格：<span>10元</span></div>
```

`//div/text()` 主要得到“价格：”，不会包含 `span` 中的“10元”。

如果需要元素及其后代的完整文本，可使用：

```xpath
string(//div)
```

在当前元素中：

```python
text = element.xpath('string(.)').strip()
```

### 获取属性值

```xpath
//a/@href
//li/@class
//img/@src
```

## 4. 条件筛选

方括号 `[]` 称为谓词，用于按位置、属性、文本或子节点筛选。

### 按位置选择

```xpath
//li[1]
//li[2]
(//li)[1]
```

XPath 的位置索引从 `1` 开始。

注意：

- `//ul/li[1]`：每个 `ul` 下的第一个 `li`。
- `(//ul/li)[1]`：所有匹配结果中的第一个 `li`。

### 最后一个节点

```xpath
//li[last()]
//li[last()-1]
```

### 根据子元素筛选

```xpath
//li[a]
//li[span[@class="price"]]
```

### 根据文本筛选

```xpath
//a[text()="苹果"]
//a[normalize-space(.)="苹果"]
```

页面文本可能带有缩进、换行或嵌套标签，因此 `normalize-space(.)` 通常更稳健。

## 5. 常用函数

### `contains()`：包含

```xpath
//*[contains(@class, "item")]
//a[contains(text(), "苹果")]
//a[contains(@href, "product")]
```

### `starts-with()`：以指定内容开头

```xpath
//a[starts-with(@href, "/product/")]
```

### `normalize-space()`：规整空白

```xpath
//button[normalize-space(.)="登录"]
```

它会删除首尾空白，并将连续空白合并为一个空格。

## 6. class 属性的正确匹配

HTML 元素可能包含多个 class：

```html
<div class="item active selected"></div>
```

下面的写法无法匹配：

```xpath
//div[@class="item"]
```

简单使用 `contains()` 又可能误匹配 `item-detail`：

```xpath
//div[contains(@class, "item")]
```

严谨写法是：

```xpath
//div[contains(concat(" ", normalize-space(@class), " "), " item ")]
```

它给 class 值补上空格边界，再查找完整的类名，避免子串误匹配。

## 7. 节点关系与轴

### 子节点与后代

```xpath
//ul/li
//ul//a
```

- `/`：直接子节点。
- `//`：任意深度的后代节点。

### 父节点

```xpath
//span[@class="price"]/parent::li
//span[@class="price"]/..
```

### 祖先节点

```xpath
//span[@class="price"]/ancestor::div
//span[@class="price"]/ancestor::div[1]
```

`ancestor::div[1]` 表示最近的祖先 `div`。

### 兄弟节点

```xpath
//label[normalize-space(.)="用户名"]/following-sibling::input[1]
//span[@class="price"]/preceding-sibling::a
```

### 前置与后续节点

```xpath
//h1/following::a
//span[@class="price"]/preceding::h1
```

常见轴包括：

| 轴 | 含义 |
|---|---|
| `child::` | 直接子节点 |
| `parent::` | 父节点 |
| `ancestor::` | 所有祖先节点 |
| `descendant::` | 所有后代节点 |
| `following-sibling::` | 后面的兄弟节点 |
| `preceding-sibling::` | 前面的兄弟节点 |
| `following::` | 文档中后续的节点 |
| `preceding::` | 文档中前置的节点 |
| `self::` | 当前节点 |
| `attribute::` | 属性节点 |

## 8. 比较运算

假设页面中有：

```html
<div class="product" data-price="100">商品A</div>
<div class="product" data-price="200">商品B</div>
```

选择价格大于 100 的商品：

```xpath
//div[@class="product" and number(@data-price) > 100]
```

常见比较运算符：

| 运算符 | 含义 |
|---|---|
| `=` | 等于 |
| `!=` | 不等于 |
| `>` | 大于 |
| `<` | 小于 |
| `>=` | 大于等于 |
| `<=` | 小于等于 |

在 XML 源文件或某些宿主语言字符串中，`<` 可能需要转义。

## 9. 并集

竖线 `|` 用于合并多个 XPath 的结果：

```xpath
//h1 | //h2
//input[@type="text"] | //textarea
```

## 10. lxml 示例

```python
from lxml import etree

html = """
<html>
  <body>
    <ul>
      <li class="item">
        <a href="/product/1">苹果</a>
        <span class="price">10元</span>
      </li>
      <li class="item">
        <a href="/product/2">香蕉</a>
        <span class="price">8元</span>
      </li>
    </ul>
  </body>
</html>
"""

tree = etree.HTML(html)

items = tree.xpath('//li[contains(@class, "item")]')

for item in items:
    name = item.xpath('string(./a)').strip()
    price = item.xpath('string(./span[@class="price"])').strip()
    links = item.xpath('./a/@href')
    link = links[0] if links else None

    print(name, price, link)
```

`xpath()` 获取属性时通常返回列表。访问 `[0]` 前应先判断列表是否为空。

## 11. Selenium 示例

```python
from selenium.webdriver.common.by import By

login_button = driver.find_element(
    By.XPATH,
    '//button[normalize-space(.)="登录"]'
)
login_button.click()

items = driver.find_elements(
    By.XPATH,
    '//li[contains(@class, "item")]'
)

username_input = driver.find_element(
    By.XPATH,
    '//label[normalize-space(.)="用户名"]/following-sibling::input[1]'
)
```

自动化测试中应优先使用稳定的 `id`、`name`、`data-*` 属性、可访问性属性或明确的标签文本。

## 12. 绝对路径与相对路径

### 绝对 XPath

```xpath
/html/body/div[2]/div[1]/ul/li[3]/a
```

它依赖完整层级和位置，页面结构稍有变化便可能失效。

### 相对 XPath

```xpath
//div[@id="main"]//a[contains(@href, "/product/")]
```

它使用稳定属性和局部结构作为锚点，更易阅读和维护。通常应优先使用相对 XPath。

## 13. 常见错误

### `text()` 不一定包含全部可见文字

```html
<button><span>立即</span>购买</button>
```

下面的表达式可能匹配失败：

```xpath
//button[text()="立即购买"]
```

建议使用：

```xpath
//button[normalize-space(.)="立即购买"]
```

### XPath 索引从 1 开始

```xpath
//li[1]
```

不要写 `//li[0]`。

### 混淆 `//li[1]` 与 `(//li)[1]`

- `//li[1]`：所有处于同级第一位置的 `li`。
- `(//li)[1]`：整个匹配结果中的第一个 `li`。

### 在循环中从根部重新搜索

当前元素内部应使用：

```xpath
./a
.//span
```

### 属性结果为空时直接访问 `[0]`

```python
links = element.xpath('./a/@href')
link = links[0] if links else None
```

### 使用过长的绝对路径

应改用稳定属性和语义明确的相对路径，降低页面改版导致的失效概率。

## XPath 常用语法汇总表

| 语法 | 含义 | 示例 |
|---|---|---|
| `/` | 从根节点开始或选择直接子节点 | `/html/body` |
| `//` | 在任意深度查找后代节点 | `//div//a` |
| `.` | 当前节点 | `.//a` |
| `..` | 父节点 | `//span/..` |
| `*` | 任意元素 | `//*[@id="main"]` |
| `@属性名` | 表示属性 | `//a/@href` |
| `[@id="main"]` | 属性完全匹配 | `//div[@id="main"]` |
| `[@href]` | 属性存在 | `//a[@href]` |
| `[not(@disabled)]` | 属性不存在 | `//input[not(@disabled)]` |
| `and` | 同时满足多个条件 | `//input[@type="text" and @name="user"]` |
| `or` | 满足任意一个条件 | `//input[@type="text" or @type="password"]` |
| `text()` | 获取直接文本节点 | `//h1/text()` |
| `string(.)` | 获取元素及后代的完整文本 | `string(//div)` |
| `[1]` | 选择同级中的第一个 | `//li[1]` |
| `(…)[1]` | 选择整个结果集中的第一个 | `(//li)[1]` |
| `[last()]` | 选择最后一个节点 | `//li[last()]` |
| `contains()` | 判断是否包含字符串 | `//a[contains(@href, "product")]` |
| `starts-with()` | 判断是否以字符串开头 | `//a[starts-with(@href, "/p/")]` |
| `normalize-space()` | 去除首尾空白并合并连续空白 | `//button[normalize-space(.)="登录"]` |
| class 边界匹配 | 精确匹配多值 class 中的类名 | `//*[contains(concat(" ", normalize-space(@class), " "), " item ")]` |
| `parent::` | 选择父节点 | `//span/parent::li` |
| `ancestor::` | 选择祖先节点 | `//span/ancestor::div[1]` |
| `descendant::` | 选择后代节点 | `//div/descendant::a` |
| `following-sibling::` | 选择后面的兄弟节点 | `//label/following-sibling::input[1]` |
| `preceding-sibling::` | 选择前面的兄弟节点 | `//span/preceding-sibling::a` |
| `following::` | 选择文档中后续节点 | `//h1/following::a` |
| `preceding::` | 选择文档中前置节点 | `//span/preceding::h1` |
| `number()` | 转换为数字后比较 | `//*[number(@data-price) > 100]` |
| `|` | 合并多个结果集 | `//h1 \| //h2` |

