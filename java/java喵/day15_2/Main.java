package day15_2;

class Animal {
    // 空
}

class Rabbit extends Animal implements Runnable {
    int distance = 0;
    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println("兔子 跑了 " + i + " 步");
            distance ++;
            System.out.println("当前兔子跑的总距离为：" + distance);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Rabbit rabbit = new Rabbit();
        Thread rabbitRun1 = new Thread(rabbit);
        Thread rabbitRun2 = new Thread(rabbit);

        rabbitRun1.start();
        rabbitRun2.start();

        for (int i = 1; i <= 5; i++) {
            System.out.println("乌龟 跑了 " + i + " 步");
        }
    }
}
