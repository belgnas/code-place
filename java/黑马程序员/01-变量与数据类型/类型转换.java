// 类型转换（Type Casting）
// 1. 自动类型转换（隐式转换）
// 2. 强制类型转换（显式转换）


class p4_TypeCastingExample {
    public static void main(String[] args) {
        // 自动转换
        int myInt = 100;
        long myLong = myInt; // int -> long, 自动
        double myDouble = myLong; // long -> double, 自动
        System.out.println("自动转换后的double值：" + myDouble);

        // 强制转换
        double price = 99.85;
        // int priceInt = price; // 编译错误，需要强制转换
        int priceInt = (int) price; // 强制将double转为int
        System.out.println("强制转换后的int值：" + priceInt); // 输出 99，小数部分被截断

        // 数据溢出示例
        int largeInt = 130;
        byte myByte = (byte) largeInt; // byte范围是 -128 到 127
        System.out.println("数据溢出后的byte值：" + myByte); // 输出 -126，发生了溢出
    }
    
}
