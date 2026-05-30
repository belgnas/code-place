// 循环语句 (Looping Statements)

// 1. for 循环: 当循环次数已知时非常有用
// 语法: for (初始化; 循环条件; 迭代) { 循环体 }

// 2. while 循环: 当循环次数未知，但知道循环的持续条件时使用。先判断再执行。
// 语法: while (循环条件) { 循环体 }

// 3. do-while 循环: 与 while 类似，但它保证循环体至少执行一次。先执行再判断。
// 语法: do { 循环体 } while (循环条件);

// 4. 增强 for 循环: 用于遍历数组或集合，代码非常简洁。
// 语法: for (元素类型 元素变量 : 数组或集合) { 循环体 }


class p11_LoopingStatements {
    public static void main(String[] args) {
        // 1. for 循环
        // 打印 0 到 4
        for (int i = 0; i < 5; i++) {
            System.out.println("i的值为: " + i);
        }

        // 2. while 循环
        // 打印 0 到 4
        int j = 0;
        while (j < 5) {
            System.out.println("j的值为: " + j);
            j++;
        }

        // 3. do-while 循环
        int k = 5;
        do {
            System.out.println("k的值为: " + k);
            k++;
        } while (k < 5); // 条件为 false, 但循环体已执行一次

        // 4. 增强 for 循环
        // 打印数组中的元素
        int[] numbers = {10, 20, 30, 40, 50};
        for (int number : numbers) {
            System.out.println("数组元素: " + number);
        }
    }
    
}
