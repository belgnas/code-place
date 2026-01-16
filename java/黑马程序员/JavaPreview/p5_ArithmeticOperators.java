// 运算符（Operators）
// 运算符是用来对变量和值执行操作的符号

// 算数运算符（Arithmetic Operators）
// 用于执行基本的数学运算
// +(加), -(减), *(乘)
// /(除)：注意整数除法，结果为整数，小数部分被截断
// %(取余)
// ++(自增), --(自减)：
    // 前缀(Prefix)：++a, --a：先自增/自减，再使用
    // 后缀(Suffix)：a++, a--：先使用，再自增/自减


package JavaPreview;

public class p5_ArithmeticOperators {
    public static void main(String[] args) {
        int a = 10;
        int b = 3;
        System.out.println("a + b = " + (a + b)); // 13
        System.out.println("a - b = " + (a / b)); // 3 (整数除法)
        System.out.println("a % b = " + (a % b)); // 1

        int c = 5;
        System.out.println("c++ = " + (c++)); // 5（先使用，再自增）
        System.out.println("++c = " + (++c)); // 7（先自增，再使用）
    }
}
