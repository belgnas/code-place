package day18_5;

// CatGirl1.java
public class CatGirl1 {
    public static void main(String[] args) {
        Receiver r = new Receiver(9998);
        // 把接收者的对象传给发送者，这样发送者才能控制它退出
        new Thread(r).start();
        new Thread(new Sender(9999, 9998, r)).start();
    }
}
