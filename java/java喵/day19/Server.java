package day19;

import java.io.*;
import java.net.*;

public class Server {
    public static void main(String[] args) throws Exception {
        System.out.println("服务端：总机已启动，正在 8888 端口等待拨号...");

        // 1. 创建服务器总机 (ServerSocket)
        ServerSocket server = new ServerSocket(8888);

        // 2. 等待客户端连接 (accept)
        // 程序运行到这里会“阻塞”，直到有客户端拨号进来
        Socket socket = server.accept(); 
        System.out.println("服务端：有人拨号进来了！管道已接通。");

        // 3. 获取输入流，读取管道里的数据
        // 这个 socket.getInputStream() 就像是电话的听筒
        InputStream is = socket.getInputStream();
        
        // 准备一个字节数组来装数据
        byte[] buffer = new byte[1024];
        int len = is.read(buffer); // 读取数据到 buffer 中
        
        // 4. 将字节数据转回字符串并打印
        String msg = new String(buffer, 0, len);
        System.out.println("服务端收到告白：" + msg);

        // 5. 释放资源，先关听筒，再关总机
        socket.close();
        server.close();
        System.out.println("服务端：通话结束，总机已关闭。");
    }
}
