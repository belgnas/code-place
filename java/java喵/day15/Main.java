package day15;

class Rabbit extends Thread {
    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("兔子 🐇 跑了 " + i + " 步");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Rabbit rabbit = new Rabbit();

        rabbit.start();

        for (int i = 1; i <= 5; i++) {
            System.out.println("乌龟 🐢 跑了 " + i + " 步");
        }
    }
}
