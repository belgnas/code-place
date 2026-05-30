
import java.net.*;
import java.lang.Integer;

class Receiver_18_3 implements Runnable {

    @Override
    public void run() {
        try {
            System.out.println("接收端已持续启动");
            int port = Integer.parseInt(Thread.currentThread().getName());
            DatagramSocket socket = new DatagramSocket(port);

            byte[] buffer = new byte[1024];
            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

                socket.receive(packet);

                String msg = new String(packet.getData(), 0, packet.getLength());

                if (msg.equals("quit")) {
                    break;
                }

                System.out.println("收到消息：" + msg);
            }
            
            socket.close();
            System.out.println("接收端已关闭");
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    // public static void main(String[] args) throws Exception {
    //     System.out.println("接收端已持续启动");

    //     DatagramSocket socket = new DatagramSocket(9999);

    //     byte[] buffer = new byte[1024];
    //     while (true) {
    //         DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

    //         socket.receive(packet);

    //         String msg = new String(packet.getData(), 0, packet.getLength());

    //         if (msg.equals("quit")) {
    //             break;
    //         }

    //         System.out.println("收到消息：" + msg);
    //     }
        
    //     socket.close();
    //     System.out.println("接收端已关闭");
    // }
}
