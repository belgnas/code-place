
import java.net.*;
import java.util.Scanner;

// --- 发送端逻辑 ---
class Sender_18_5 implements Runnable {
    private int targetPort; // 对方的端口
    private int myReceiverPort; // 我自己接收端的端口（为了自杀包裹）
    private Receiver_18_5 localReceiver; // 引用本地接收者对象

    public Sender_18_5(int targetPort, int myReceiverPort, Receiver_18_5 localReceiver) {
        this.targetPort = targetPort;
        this.myReceiverPort = myReceiverPort;
        this.localReceiver = localReceiver;
    }

    public void run() {
        try (DatagramSocket socket = new DatagramSocket();
             Scanner sc = new Scanner(System.in)) {
            
            while (true) {
                System.out.print("我: ");
                String msg = sc.nextLine();

                // 问题 3：拦截空消息
                if (msg == null || msg.trim().isEmpty()) {
                    System.out.println("[提醒]: 发送失败，内容不能为空喵！");
                    continue;
                }

                // 处理退出逻辑
                if ("quit".equals(msg)) {
                    // 问题 1：关闭本地接收端
                    localReceiver.isRunning = false;
                    // 给【自己】发一个包裹，把卡在 receive() 的接收线程“撞”醒
                    byte[] quitData = "quit".getBytes();
                    DatagramPacket suicidePacket = new DatagramPacket(
                        quitData, quitData.length, InetAddress.getByName("127.0.0.1"), myReceiverPort
                    );
                    socket.send(suicidePacket);
                    
                    // 同时也给【对方】发一个退出通知（礼貌）
                    DatagramPacket notifyOpponent = new DatagramPacket(
                        quitData, quitData.length, InetAddress.getByName("127.0.0.1"), targetPort
                    );
                    socket.send(notifyOpponent);
                    
                    break; 
                }

                // 正常发送消息
                byte[] data = msg.getBytes();
                DatagramPacket packet = new DatagramPacket(
                    data, data.length, InetAddress.getByName("127.0.0.1"), targetPort
                );
                socket.send(packet);
            }
            System.out.println("[系统]: 发送线程已下班喵。");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}