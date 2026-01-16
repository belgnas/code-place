// 键盘录入

// 1.导包：import java.util.Scanner;
// 2.创建对象：Scanner sc = new Scanner(System.in);
// 3.接收数据：int a = sc.nextInt();

// 1.导包:找到Scanner这个类在哪
// 注意：要写在类定义的上面
import java.util.Scanner;

public class study_5 {
    public static void main(String[] args) {

        // 2.创建对象：表示我现在准备要用Scanner这个类
        Scanner sc = new Scanner(System.in);

        System.out.println("请输入一个整数");
        // 3.接收数据
        // 变量i就记录了键盘录入的数据
        int i = sc.nextInt();

        // 4.输出数据
        System.out.println(i);

        // 再次接收第二个数据
        System.out.println("请再一次输入一个整数");
        int j = sc.nextInt();
        System.out.println(j);
        System.out.println(i + j);

        sc.close();
    }
}
