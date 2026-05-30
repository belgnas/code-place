// 数据类型
// 1.基本数据类型 2.引用数据类型

// 基本数据类型
// 1.整数类型 byte short int long
// 2.浮点数类型 float double
// 3.字符类型 char
// 4.布尔类型 boolean

// 引用数据类型（后面会学）
// 1.类
// 2.接口
// 3.数组
class DataTypeDemo {
    public static void main(String[] args) {
        // byte 1字节 -128~127
        byte a = 10;
        System.out.println(a);

        // short 2字节 -32768~32767
        short b = 20;
        System.out.println(b);

        // int 4字节 -2147483648~2147483647（10位数）
        int c = 30;
        System.out.println(c);

        // long 8字节 -9223372036854775808~9223372036854775807（19位数）
        long d = 40L;
        System.out.println(d);
        // 建议在long类型数字后面加一个 L 作为后缀
        // L 可以是大写的，也可以是小写的
        // 建议使用大写，因为更容易辨别

        // float 4字节 -3.403E38~3.403E38
        float e = 50.0F;
        System.out.println(e);
        // 建议在float类型数字后面加一个 F 作为后缀
        // F 可以是大写的，也可以是小写的
        // 建议使用大写，因为更容易辨别

        // double 8字节 -4
        double f = 60.0;
        System.out.println(f);

        // char 2字节 0~65535
        char g = '中';
        System.out.println(g);

        // boolean 1字节 true false
        boolean h = true;
        System.out.println(h);
    }
}
