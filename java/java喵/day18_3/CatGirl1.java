package day18_3;

public class CatGirl1 {
    public static void main(String[] args) {
        new Thread(new Receiver(), "9999").start();
        new Thread(new Sender(), "9998").start();
    }
}
