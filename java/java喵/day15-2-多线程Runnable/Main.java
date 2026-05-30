
class Animal {
    // 空
}

class Rabbit_day15_2 implements Runnable {
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

class Main_day15_2 {
    public static void main(String[] args) {
        Rabbit_day15_2 rabbit = new Rabbit_day15_2();
        Thread rabbitRun1 = new Thread(rabbit);
        Thread rabbitRun2 = new Thread(rabbit);

        rabbitRun1.start();
        rabbitRun2.start();

        for (int i = 1; i <= 5; i++) {
            System.out.println("乌龟 跑了 " + i + " 步");
        }
    }
}
