package day18_3;

public class CatGirl2 {
    public static void main(String[] args) {
        new Thread(new Receiver(), "9998").start();
        new Thread(new Sender(), "9999").start();
    }
}
