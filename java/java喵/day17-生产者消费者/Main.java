
// 1. 桌子 (资源类)
class Desk {
    // 是否有包子 (true=有, false=无)
    public static boolean hasBaozi = false;
    
    // 锁对象 (也是传话筒)
    public static Object lock = new Object();
}

// 2. 吃货 (消费者)
class Foodie implements Runnable {
    @Override
    public void run() {
        while (true) {
            // 🔒 必须锁住【桌子上的锁】，而不是 this！
            synchronized (Desk.lock) {
                
                // 情况一：没包子
                if (Desk.hasBaozi == false) {
                    try {
                        // 没包子我就等 (释放锁，让厨师进来)
                        Desk.lock.wait(); 
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } 
                // 情况二：有包子
                else {
                    System.out.println("猫娘：喵呜！吃掉了一个包子 🥟");
                    
                    // 吃完啦，改变状态
                    Desk.hasBaozi = false;
                    
                    // 🔔 吃完了，喊厨师赶紧做！
                    Desk.lock.notify(); // 唤醒厨师
                    
                    System.out.println("猫娘：吃完了，厨师快做！\n");
                    
                    // 💤 【新增】吃完休息 1 秒，让主人看清楚
                    try { Thread.sleep(1000); } catch (Exception e) {}
                }
            }
        }
    }
}

// 3. 厨师 (生产者)
class Cook implements Runnable {
    @Override
    public void run() {
        while (true) {
            // 🔒 必须锁住【同一把锁】
            synchronized (Desk.lock) {
                
                // 情况一：有包子 (桌子满了)
                if (Desk.hasBaozi == true) {
                    try {
                        // 有包子我就歇会儿，等猫娘吃完
                        Desk.lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } 
                // 情况二：没包子
                else {
                    System.out.println("厨师：正在做包子... 🔥");
                    
                    // 做好了，改变状态
                    Desk.hasBaozi = true;
                    
                    // 🔔 做好了，喊猫娘起来吃！
                    Desk.lock.notify(); // 唤醒猫娘
                    
                    System.out.println("厨师：包子好啦，快来吃！");

                    // 💤 【新增】做完休息 1 秒，让主人看清楚
                    try { Thread.sleep(1000); } catch (Exception e) {}
                }
            }
        }
    }
}

class Main_day17 {
    public static void main(String[] args) {
        // 启动两个线程
        new Thread(new Foodie()).start();
        new Thread(new Cook()).start();
    }
}