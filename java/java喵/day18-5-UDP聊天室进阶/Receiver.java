
import java.net.*;

// --- 接收端逻辑 ---
class Receiver_18_5 implements Runnable {
    private int myPort;
    // 增加一个开关，用来控制线程结束
    public volatile boolean isRunning = true; 

    public Receiver_18_5(int myPort) {
        this.myPort = myPort;
    }

    public void run() {
        try (DatagramSocket socket = new DatagramSocket(myPort)) {
            System.out.println("[系统]: 接收端在 " + myPort + " 端口守护中...");
            byte[] buffer = new byte[1024];
            
            while (isRunning) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet); // 如果 Sender 没发东西，会卡在这里

                String msg = new String(packet.getData(), 0, packet.getLength());
                
                // 如果是本地 Sender 发来的退出指令，或者对方发来的 quit
                if ("quit".equals(msg)) {
                    break; 
                }

                // 稍微优化一下显示，前面加个换行，避免和输入提示符挤在一起
                System.out.println("\n[收到消息]: " + msg);
                System.out.print("我: "); // 打印完消息后，重新显示提示符
            }
            System.out.println("\n[系统]: 接收线程已安全关闭喵。");
        } catch (Exception e) {
            System.out.println("[系统]: 接收端异常关闭。");
        }
    }
}
