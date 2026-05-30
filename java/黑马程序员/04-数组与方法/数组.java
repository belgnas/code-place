// 数组

// 数组是一种容器，可以用来存储同种数据类型的多个值
// 数组容器在存储数据时，需要结合隐式转换考虑
// 例如：int 类型的数组容器，能存储 byte、short、int 类型的数据，不过会自动隐式转换成 int 类型
// 例如：double 类型的数组容器，能存储 byte、short、int、long、float、double 类型的数据，不过会自动转换成 double 类型

// 数组的定义

// 1. 静态初始化：数组定义时，指定数组长度，同时指定数组内容
// 完整格式：
// 数据类型[] 数组名 = new 数据类型[数组长度]{元素1, 元素2, 元素3......};
// 例如：int[] arr = new int[3]{1, 2, 3...};
// 简写（常用）格式：
// 数据类型[] 数组名 = {元素1, 元素2, 元素3......};
// 例如：int[] arr = {1, 2, 3...};

// 2. 动态初始化：数组定义时，只指定数组长度，不指定数组内容，由系统自动分配默认值
// 完整格式：
// 数据类型[] 数组名 = new 数据类型[数组长度];
// 例如：int[] arr = new int[3];
// 动态初始化时，数组内容默认值为 0
// 例如：int[] arr = new int[3];
// 数组内容为：0, 0, 0
// 数组默认初始化的规律
// 1. 整数类型的数组默认值为 0
// 2. 浮点数类型的数组默认值为 0.0
// 3. 字符类型的数组默认值为 '\u0000'
// 4. 布尔类型的数组默认值为 false
// 5. 引用类型的数组默认值为 null

// 数组的元素访问
// 利用索引对数组中的元素进行访问
// 格式：数组名[索引]
// 例如：arr[0]
// ps：不要越界访问数组

// 数组的遍历
// 遍历：就是把数组中的每个元素都访问一遍
// 格式：for 循环
// 例如：for (int i = 0; i < 数组长度; i++) {
//         数组名[索引]
//     }
// 例如：for (int i = 0; i < arr.length; i++) {
//         System.out.println(arr[i]);
//     }

// 二维数组
// 二维数组的定义
// 静态初始化
// 完整格式：
// 数据类型[][] 数组名 = new 数据类型[数组长度]{元素1, 元素2, 元素3......};
// 也可以写成：数据类型 数组名[][] = new 数据类型[数组长度]{元素1, 元素2, 元素3......};
// 简写（常用）格式：
// 数据类型[][] 数组名 = {元素1, 元素2, 元素3......};
// 例如：int[][] arr = {{1, 2, 3}, {4, 5, 6}};
// 动态初始化
// 完整格式：
// 数据类型[][] 数组名 = new 数据类型[数组长度][数组长度];
// 例如：int[][] arr = new int[2][3];
// 简写（常用）格式：
// 数据类型[][] 数组名 = new 数据类型[数组长度][];
// 例如：int[][] arr = new int[2][3];

class ArrayDemo {
    public static void main(String[] args) {
        // 静态初始化
        // 数据类型[] 数组名 = new 数据类型[数组长度]{元素1, 元素2, 元素3......};
        // 简写（常用）格式：
        // 数据类型[] 数组名 = {元素1, 元素2, 元素3......};
        int[] arr1 = new int[]{11, 12, 13};
        int[] arr2 = {11, 12, 13};
        String[] arr3 = new String[]{"张三", "李四", "王五"};
        String[] arr4 = {"zhangsan", "lisi", "wangwu"};
        double[] arr5 = new double[]{11.1, 12.2, 13.3};
        double[] arr6 = {11.1, 12.2, 13.3};

        // 直接打印数组名打印的是该数组的地址
        System.out.println(arr1); // [I@18b4aac2
        System.out.println(arr2); // [I@764c12b6
        System.out.println(arr3); // [Ljava.lang.String;@c387f44
        System.out.println(arr4); // [Ljava.lang.String;@4e0e2f2a
        System.out.println(arr5); // [D@73d16e93
        System.out.println(arr6); // [D@659e0bfd
        
        // 扩展：
        // 解释一下地址的格式含义
        // [I@18b4aac2
        // [I@764c12b6
        // [Ljava.lang.String;@c387f44
        // [Ljava.lang.String;@4e0e2f2a
        // [D@73d16e93
        // [D@659e0bfd
        // 解释：
        // [：表示这是一个数组
        // I：表示这是一个 int 类型的数组
        // Ljava.lang.String;：表示这是一个 String 类型的数组
        // D：表示这是一个 double 类型的数组
        // @：表示这是一个地址（表示一个间隔符号， 固定格式）
        // 18b4aac2：这个才是真正的地址（一个 16 进制数）
        // 平时我们习惯性的会把这个整体叫做数组的地址
    
        // 数组的元素访问
        System.out.println(arr1[0]);

        // 数组的遍历
        for (int i = 0; i < arr1.length; i++) {
            System.out.println(arr1[i]);
        }

        // 数组的动态初始化
        int[] arr7 = new int[3];

        System.out.println(arr7[0]);
        System.out.println(arr7[1]);
        System.out.println(arr7[2]);

        // 数组的元素赋值
        arr7[0] = 10;
        arr7[1] = 20;
        arr7[2] = 30;

        System.out.println(arr7[0]);
        System.out.println(arr7[1]);
        System.out.println(arr7[2]);

    }   

}
