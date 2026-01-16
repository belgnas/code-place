// 控制流（Control Flow）
// 控制流语句决定了程序的执行路径

// 选择结构（Selection Statements）
// 选择结构用于根据条件执行不同的代码块
// 1. if-else 语句
// 2. switch 语句
//     适用于对一个变量的多个固定值进行判断。
//     传统 switch (Java 11 及之前):
//         * case: 匹配的值。
//         * break: 非常重要！ 如果没有 break，程序会继续执行下一个 case，直到遇到 break 或 switch 结束，这被称为"穿透
//             (fall-through)"。
//         * default: 所有 case 都不匹配时执行。
//     现代 switch (Java 14+):
//         * 使用箭头 -> 和代码块，不再需要 break，代码更简洁且不会意外穿透。

// IDE 提示：在 vscode 或者 IntelliJ IDEA 中，当你写传统的 switch，会提示你可以使用增强型的 switch 表达式 (箭头 -> 语法)

package JavaPreview;

public class p10_SelectionStatements {
    public static void main(String[] args) {
        // if-else 语句
        int score = 85;
        String result;
        if (score >= 60) {
            result = "及格";
        } else {
            result = "不及格";
        }
        System.out.println("考试结果：" + result); // 及格

        // switch 语句
        int day = 3;
        // 传统 switch 语句
        String dayName;
        switch (day) {
            case 1:
                dayName = "星期一";
                break;
            case 2:
                dayName = "星期二";
                break;
            case 3:
                dayName = "星期三";
                break;
            default:
                dayName = "未知";
        }
        System.out.println(dayName); // 星期三

        // 现代 switch 表达式
        String dayNameModern = switch (day) {
            case 1 -> "星期一";
            case 2 -> "星期二";
            case 3 -> "星期三";
            default -> "未知";
        };
        System.out.println(dayNameModern); // 星期三
    }
}
