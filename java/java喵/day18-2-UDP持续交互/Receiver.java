
import java.net.*;

class Receiver_18_2 {
    public static void main(String[] args) throws Exception {
        System.out.println("接收端已持续启动");

        DatagramSocket socket = new DatagramSocket(9999);

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
}
