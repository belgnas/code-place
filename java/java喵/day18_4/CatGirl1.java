package day18_4;

public class CatGirl1 {
    public static void main(String[] args) {
        // 监听 9998，发送给 9999
        new Thread(new Receiver(9998)).start();
        new Thread(new Sender(9999)).start();
    }
}
