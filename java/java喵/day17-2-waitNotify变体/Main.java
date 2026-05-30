
class Account {
    public static int money = 0;
    public static Object lock = new Object();
}

class Dad implements Runnable {
    @Override
    public void run() {
        while (true) {
            synchronized (Account.lock) {
                // 逻辑修正：如果有钱，爸爸应该休息 (wait)，而不是 notify
                if (Account.money > 0) {
                    try {
                        System.out.println("爸爸：卡里有钱，我不存，休息会儿...");
                        Account.lock.wait(); // ⏸️ 有钱就等待
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } 
                // 逻辑修正：没钱了，爸爸才存钱，存完喊人
                else {
                    Account.money += 1000;
                    System.out.println("爸爸：存了 1000 元，当前余额：" + Account.money);
                    
                    // 🔔 干完活了，唤醒儿子起来花钱！
                    Account.lock.notify(); 
                    
                    // 慢动作药水，方便观察
                    try { Thread.sleep(1000); } catch (Exception e) {}
                }
            }
        }
    }
}

class Son implements Runnable {
    @Override
    public void run() {
        while (true) {
            synchronized (Account.lock) {
                // 逻辑修正：如果没钱，儿子应该休息 (wait)
                if (Account.money == 0) {
                    try {
                        System.out.println("儿子：没钱了，我等老爸存钱...");
                        Account.lock.wait(); // ⏸️ 没钱就等待
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } 
                // 逻辑修正：有钱了，儿子才取钱，取完喊人
                else {
                    Account.money -= 1000;
                    System.out.println("儿子：取了 1000 元，当前余额：" + Account.money);
                    
                    // 🔔 干完活了，唤醒老爸起来存钱！
                    Account.lock.notify(); 
                    
                    // 慢动作药水
                    try { Thread.sleep(1000); } catch (Exception e) {}
                }
            }
        }
    }
}

class Main_day17_2 {
    public static void main(String[] args) {
        new Thread(new Dad()).start();
        new Thread(new Son()).start();
    }
}