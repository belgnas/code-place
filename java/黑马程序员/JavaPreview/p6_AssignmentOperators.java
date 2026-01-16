// 赋值运算符（Assignment Operators）
// 用于给变量分配一个值
// =（简单赋值运）
// +=, -=, *=, /=, %=：（复合赋值）先进行运算，再将结果赋给左侧的变量：a += 5 等价于 a = a + 5

package JavaPreview;

public class p6_AssignmentOperators {
    public static void main(String[] args) {
        int x = 10;
        x += 5; // 等价于 x = x + 5
        System.out.println("x = " + x); // 15
    }
}
