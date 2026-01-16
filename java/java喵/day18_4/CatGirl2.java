package day18_4;

public class CatGirl2 {
    public static void main(String[] args) {
        // 监听 9999，发送给 9998
        new Thread(new Receiver(9999)).start();
        new Thread(new Sender(9998)).start();
    }
}