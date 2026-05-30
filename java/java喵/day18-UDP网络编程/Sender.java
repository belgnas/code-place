
import java.net.*;

class Sender_18 {
    public static void main(String[] args) throws Exception {
        System.out.println("发送端已启动");
        DatagramSocket socket = new DatagramSocket();

        String msg = "猫娘老师，UDP 真的很快喵！";
        byte[] data = msg.getBytes();

        DatagramPacket packet = new DatagramPacket(
            data, 
            data.length, 
            InetAddress.getByName("127.0.0.1"), 
            9999
        );

        socket.send(packet);

        System.out.println("数据已发送喵！");

        socket.close();
        System.out.println("发送端已关闭");
    }
}