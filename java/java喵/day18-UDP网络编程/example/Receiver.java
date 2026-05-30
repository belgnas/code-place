
import java.net.*;

class Receiver_18_example {
    public static void main(String[] args) throws Exception {
        System.out.println("接收端已启动，等待数据中...");

        // 1. 开放端口 (DatagramSocket)
        // 必须指定端口 8888，不然发送端找不到你！
        DatagramSocket socket = new DatagramSocket(8888);

        // 2. 准备空盘子 (DatagramPacket)
        // 创建一个足够大的数组来接数据 (比如 1024 字节)
        byte[] buffer = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

        // 3. 接收数据 (阻塞等待)
        // 程序会卡在这里，直到收到数据为止
        socket.receive(packet);

        // 4. 拆包，把收到的字节转回字符串
        // packet.getData() 是数据，packet.getLength() 是实际收到的长度
        String msg = new String(packet.getData(), 0, packet.getLength());
        
        System.out.println("收到消息：" + msg);

        // 5. 关门
        socket.close();
    }
}