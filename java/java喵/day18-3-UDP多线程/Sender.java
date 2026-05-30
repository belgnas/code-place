
import java.net.*;
import java.util.Scanner;

class Sender_18_3 implements Runnable {
    public void run() {
        try {
            System.out.println("发送端已持续启动");
            int port = Integer.parseInt(Thread.currentThread().getName());
            DatagramSocket socket = new DatagramSocket();

            Scanner sc = new Scanner(System.in);

            while (true) {
                String msg = sc.nextLine();

                byte[] data = msg.getBytes();

                DatagramPacket packet = new DatagramPacket (
                    data, 
                    data.length, 
                    InetAddress.getByName("127.0.0.1"), 
                    port
                );

                socket.send(packet);

                if (msg.equals("quit")) {
                    break;
                }

                System.out.println("数据已发送喵！");
            }
            sc.close();

            socket.close();
            System.out.println("发送端已关闭");
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        
    }
}