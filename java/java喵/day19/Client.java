package day19;

import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) throws Exception {
        System.out.println("客户端：正在准备拨号...");

        // 1. 创建客户端 Socket，连接指定 IP 和端口
        // 只要这行不报错，就说明“三次握手”成功，管道连通了！
        Socket socket = new Socket("127.0.0.1", 8888);

        // 2. 获取输出流，往管道里写数据
        // 这个 socket.getOutputStream() 就像是电话的话筒
        OutputStream os = socket.getOutputStream();

        // 3. 准备要说的话，转成字节发出去
        String msg = "猫娘老师，TCP 真的好稳喵！我感受到了连接的力量！";
        os.write(msg.getBytes());

        // 4. 释放资源
        os.close();
        socket.close();
        System.out.println("客户端：告白已送达，深藏功与名。");
    }
}