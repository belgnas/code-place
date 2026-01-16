package day8;

public class Main {
    public static void main(String[] args) {
        Shop shop = new Shop();

        Payment p1 = new Alipay();
        Payment p2 = new WeChatPay();

        shop.checkout(p1);
        shop.checkout(p2);
    }
}
