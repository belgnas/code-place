// 逻辑运算符 (Logical Operators)
// 用于组合多个条件

// * && (逻辑与 / AND): 两边都为 true 时，结果才为 true。
// * || (逻辑或 / OR): 只要有一边为 true，结果就为 true。
// * ! (逻辑非 / NOT): 取反，!true 结果为 false。

// 短路特性 (Short-circuiting):
// * 对于 A && B，如果 A 为 false，则 B 不会被执行。
// * 对于 A || B，如果 A 为 true，则 B 不会被执行。

package JavaPreview;

public class p8_LogicalOperators {
    public static void main(String[] args) {
        // 逻辑与 (&&) 示例
        boolean a = true;
        boolean b = false;
        System.out.println("a && b: " + (a && b)); // false，因为 b 为 false
        System.out.println("a && true: " + (a && true)); // true，因为 a 为 true

        // 逻辑或 (||) 示例
        System.out.println("a || b: " + (a || b)); // true，因为 a 为 true
        System.out.println("a || false: " + (a || false)); // true，因为 a 为 true

        // 逻辑非 (!) 示例
        System.out.println("!a: " + (!a)); // false，因为 a 为 true
        System.out.println("!b: " + (!b)); // true，因为 b 为 false

        // 短路特性示例
        System.out.println("a && (b || true): " + (a && (b || true))); // false，因为 b 为 false
        System.out.println("a || (b && true): " + (a || (b && true))); // true，因为 a 为 true
    }
}
