
import java.net.*;

class Receiver_18_4 implements Runnable {
    private int myPort; // 我自己的监听端口

    public Receiver_18_4(int myPort) {
        this.myPort = myPort;
    }

    public void run() {
        try {
            DatagramSocket socket = new DatagramSocket(myPort); // 守住我的窗口
            byte[] buffer = new byte[1024];
            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);
                String msg = new String(packet.getData(), 0, packet.getLength());
                System.out.println("\n[收到消息]: " + msg); // 换行打印，防止和输入重叠
                if (msg.equals("quit")) break;
            }
            socket.close();
        } catch (Exception e) { e.printStackTrace(); }
    }
}
