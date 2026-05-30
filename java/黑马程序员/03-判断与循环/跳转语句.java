// 跳转语句（Jump Statements）

// 1. break: 用于跳出循环或 switch 语句
// 2. continue: 跳过本次循环的剩余部分，直接开始下一次循环。
// 3. return: 用于从方法中返回值


class p12_JumpStatements {
    public static void main(String[] args) {

        for (int i = 1; i <= 10; i++) {
            if (i % 2 != 0) {
                continue; // 如果是奇数，跳过本次循环，不打印
            }
            if (i > 8) {
                break; // 如果i大于8，跳出整个循环
            }
            System.out.println("偶数: " + i); // 只会打印 2, 4, 6, 8
        }

    }
}
