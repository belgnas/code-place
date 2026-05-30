// 关系运算符 (Relational Operators)
// 用于比较两个值之间的关系，结果为布尔值 (true 或 false)
// == (等于), != (不等于)
// > (大于), < (小于)
// >= (大于等于), <= (小于等于)

// 极其重要的一点
// * 对于基本数据类型 (int, double 等)，== 比较的是值。
// * 对于引用数据类型 (String，数组，对象等)，== 比较的是它们在内存中的地址，即是否指向同一个对象。
// * 要比较两个字符串的内容是否相等，必须使用 .equals() 方法。


class p7_RelationalOperators {
    public static void main(String[] args) {
        int num1 = 10;
        int num2 = 20;
        System.out.println("num1 == num2: " + (num1 == num2));

        String str1 = new String("hello");
        String str2 = new String("hello");
        String str3 = str1;

        System.out.println("str1 == str2: " + (str1 == str2)); // false，因为 str1 和 str2 是两个不同的对象
        System.out.println("str1 == str3: " + (str1 == str3)); // true，因为 str3 引用了 str1 指向的同一个对象
        System.out.println("str1.equals(str2): " + str1.equals(str2)); // true，因为内容相等
    }
}
