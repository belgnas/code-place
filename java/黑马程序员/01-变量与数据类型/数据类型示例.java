// 数据类型（Data Types）

// 1. 整形（Integer Types）
// 2. 浮点型（Floating-Point Types）
// 3. 字符型（Character Type）
// 4. 布尔型（Boolean Type）
// 5. 引用类型（Reference Types）


class p2_DataTypesExample {
    public static void main(String[] args) {
        // 整形
        int myAge = 25;
        long worldPopulation = 8000000000L; // 注意L后缀

        // 浮点型
        float itemPrice = 19.99f; // 注意f后缀
        double pi = 3.141592653589793;

        // 字符型
        char grade = 'A';
        char chineseChar = '中';

        // 布尔型
        boolean isJavaFun = true;

        // 引用类型
        String greeting = "Hello, Java!";

        System.out.println("年龄：" + myAge);
        System.out.println("世界人口：" + worldPopulation);
        System.out.println("商品价格：" + itemPrice);
        System.out.println("圆周率：" + pi);
        System.out.println("等级：" + grade);
        System.out.println("中文字符：" + chineseChar);
        System.out.println("Java是否有趣：" + isJavaFun);
        System.out.println("问候语：" + greeting);
    }
}
