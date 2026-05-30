
class Animal2 {
    // 空
}

class Rabbit2 extends Animal2 implements Runnable {
    // 共享的距离
    int distance = 0;

    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            // 1. 【重点】获取当前线程的名字（小白？小黑？）
            String name = Thread.currentThread().getName();
            
            // 2. 累加距离
            distance++; 
            
            // 3. 【重点】合并打印！
            // 不要分两行打印，分两行就会被插队！
            // 把名字(name)、步数(i)、总距离(distance) 拼在这一句话里！
            System.out.println(name + " 跑了第 " + i + " 步，当前总距离：" + distance);
            
            // 稍微睡一下，让输出慢一点，你也看得清一点
            try {
                Thread.sleep(100); 
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Main2 {
    public static void main(String[] args) {
        Rabbit2 rabbit2 = new Rabbit2(); // 只有一份任务，一份 distance

        // 给线程起名字： "小白", "小黑"
        Thread rabbitRun1 = new Thread(rabbit2, "小白 🐇");
        Thread rabbitRun2 = new Thread(rabbit2, "小黑 🐈‍⬛");

        rabbitRun1.start();
        rabbitRun2.start();

        // 乌龟也来凑热闹
        for (int i = 1; i <= 5; i++) {
            System.out.println("乌龟 🐢 跑了 " + i + " 步");
             try { Thread.sleep(100); } catch (Exception e) {}
        }
    }
}