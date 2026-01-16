package day18.example;

import java.net.*;

public class Sender {
    public static void main(String[] args) throws Exception {
        // 1. 创建快递点 (DatagramSocket)
        // 发送端不需要指定端口，随便哪个都行
        DatagramSocket socket = new DatagramSocket();

        // 2. 准备数据
        String msg = "你好喵！我是来自 Day 18 的数据！";
        byte[] data = msg.getBytes(); // 必须转成字节数组

        // 3. 打包包裹 (DatagramPacket)
        // 参数：数据, 长度, 对方IP, 对方端口
        DatagramPacket packet = new DatagramPacket(
            data, 
            data.length, 
            InetAddress.getByName("127.0.0.1"), // 发给自己
            8888 // 目标端口
        );

        // 4. 发送！
        socket.send(packet);
        System.out.println("数据已发送喵！");

        // 5. 关门
        socket.close();
    }
}
