
class TicketSystem implements Runnable {
    int ticket = 10;
    // String name = ... ❌ 不要在这里获取名字，这里是 main 线程的地盘

    public void run() {
        while (true) {
            
            // 🔒 进门第一件事：先上锁！
            // 确保判断票数和卖票是一个完整的、不可打断的动作
            synchronized (this) {
                
                // 🎫 在锁里面检查票数
                if (ticket > 0) {
                    // ✅ 在这里获取当前进来的线程名字
                    String name = Thread.currentThread().getName();
                    
                    System.out.println("[ " + name + " ] 抢到了第 " + ticket + " 张票");
                    ticket--;
                } 
                else {
                    // 没票了，打印一下并退出
                    System.out.println("票卖光了喵！");
                    break; 
                }
            } // 🔓 解锁

            // 💤 睡觉要放在锁外面！
            // 如果你在锁里面睡觉，就是占着茅坑不拉屎，别的线程根本进不来
            try {
                // sleep(100) 就是100ms，也就是0.1s
                Thread.sleep(100);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

class Main_day16 {
    public static void main(String[] args) {
        TicketSystem ticketSystem = new TicketSystem();

        // 这里的名字要想显示出来，必须配合上面 run 里面正确的 getName() 写法
        Thread scalper1 = new Thread(ticketSystem, "黄牛1号");
        Thread scalper2 = new Thread(ticketSystem, "黄牛2号");
        Thread scalper3 = new Thread(ticketSystem, "黄牛3号");

        scalper1.start();
        scalper2.start();
        scalper3.start();
    }
}