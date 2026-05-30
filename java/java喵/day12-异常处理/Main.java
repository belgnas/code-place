
import java.util.Scanner;

class Main_day12 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        int[] arr = {10, 20, 30};

        try {
            int num = arr[x];
            System.out.println("num = " + num);
        }
        catch(ArrayIndexOutOfBoundsException e) {
            System.out.println("抓到了！你试图访问不存在的索引！");
            System.out.println("错误原因是：" + e.getMessage());
        }
        catch (Exception e) { // 这是一个万能的大网，可以捕获所有其他类型的异常
             System.out.println("4. 发生了其他未知的错误！");
             
        }
        finally {
            System.out.println("finally 部分运行完成");
        }

        System.out.println("程序继续运行...");


        sc.close();
    }
}
