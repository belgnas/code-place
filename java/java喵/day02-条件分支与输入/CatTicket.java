
import java.util.Scanner;

class CatTicket {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入猫娘的年龄：");
        int catAge = sc.nextInt();
        double price = 100;
        if (catAge < 3) {
            System.out.println("她是小猫娘，门票免费！");
            price *= 0;
        }
        else if (catAge > 10) {
            System.out.println("她是老猫娘，门票半价！");
            price *= 0.5;
        }
        else {
            System.out.println("她是成年猫娘，全价票喵！");
            price *= 1;
        }

        System.out.println("这只猫娘的门票价格为：" + price + "元");

        sc.close();
    }
}
