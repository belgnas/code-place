// 三元运算符 (Ternary Operator)
// 是 if-else 语句的紧凑形式
// 语法: condition ? expression_if_true : expression_if_false

package JavaPreview;

public class p9_TernaryOperator {
    public static void main(String[] args) {
        int score = 85;
        String result = (score >= 60) ? "及格" : "不及格";
        System.out.println("考试结果：" + result); // 及格
    }
}
