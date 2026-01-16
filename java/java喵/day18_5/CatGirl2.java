package day18_5;

// CatGirl2.java
public class CatGirl2 {
    public static void main(String[] args) {
        Receiver r = new Receiver(9999);
        new Thread(r).start();
        new Thread(new Sender(9998, 9999, r)).start();
    }
}