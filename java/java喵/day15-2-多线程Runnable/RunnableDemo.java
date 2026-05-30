
// 1. 定义任务类（实现 Runnable 接口）
// 这不是线程，这只是一张“任务单”
class RunTask implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println("任务进行中... " + i);
        }
    }
}

class RunnableDemo {
    public static void main(String[] args) {
        // 2. 创建任务对象
        RunTask task = new RunTask();
        
        // 3. 创建线程对象（工人），把任务交给它
        // 格式：new Thread(任务对象)
        Thread t = new Thread(task);
        
        // 4. 启动工人
        t.start(); 
        
        System.out.println("主线程结束");
    }
}