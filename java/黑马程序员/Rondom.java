// 随机数生成

// 使用步骤
// 1.导包：import java.util.Random;
// 2.创建对象：Random numble = new Random();
// 3.生成随机数：numble.nextInt(100); // 生成0-99的随机数
// 4.打印随机数：System.out.println(numble.nextInt(bound:100));

import java.util.Random; // 导入Random类

public class Rondom {
    public static void main(String[] args) /* String[] args作用：接收命令行参数 */ {
        for (int i = 0; i < 10; i++) {
            Random numble = new Random(); // 创建Random对象
            System.out.println(numble.nextInt(100) + 200); // 生成200-299的随机数（bound是随机数的范围，这里是100，所以生成的随机数是0-99，再加上200，就是200-299）
        }

        // 随机打乱数组
        int[] arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // 定义一个整型数组
        Random random = new Random(); // 创建Random对象
        for (int i = 0; i < arr.length; i++) { // 遍历数组
            int randomIndex = random.nextInt(arr.length); // 生成一个随机索引
            int temp = arr[i]; // 交换元素
            arr[i] = arr[randomIndex];
            arr[randomIndex] = temp;
        }
        for (int i = 0; i < arr.length; i++) { // 遍历数组，打印元素
            System.out.print(arr[i] + " ");
        }
    }
}
