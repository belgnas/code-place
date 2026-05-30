
import java.net.*;

class Receiver_18 {
    public static void main(String[] args) throws Exception {
        System.out.println("接收端已启动");

        DatagramSocket socket = new DatagramSocket(9999);

        byte[] buffer = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

        socket.receive(packet);

        String msg = new String(packet.getData(), 0, packet.getLength());

        System.out.println("收到消息：" + msg);
        
        socket.close();
        System.out.println("接收端已关闭");
    }
}
