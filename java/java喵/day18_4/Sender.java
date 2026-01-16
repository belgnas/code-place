package day18_4;

import java.net.*;
import java.util.Scanner;

class Sender implements Runnable {
    private int targetPort; // 对方的接收端口

    public Sender(int targetPort) {
        this.targetPort = targetPort;
    }

    public void run() {
        try {
            // 发送端不需要指定自己的端口，让系统随机分配一个就好
            DatagramSocket socket = new DatagramSocket(); 
            Scanner sc = new Scanner(System.in);
            while (true) {
                String msg = sc.nextLine();
                byte[] data = msg.getBytes();
                DatagramPacket packet = new DatagramPacket(
                    data, data.length, 
                    InetAddress.getByName("127.0.0.1"), 
                    targetPort // 填入对方的接收窗口
                );
                socket.send(packet);
                if (msg.equals("quit")) break;
            }
            sc.close();
            socket.close();
        } catch (Exception e) { e.printStackTrace(); }
    }
}