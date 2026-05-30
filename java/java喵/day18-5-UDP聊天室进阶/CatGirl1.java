
// CatGirl1.java
class CatGirl1_18_5 {
    public static void main(String[] args) {
        Receiver_18_5 r = new Receiver_18_5(9998);
        // 把接收者的对象传给发送者，这样发送者才能控制它退出
        new Thread(r).start();
        new Thread(new Sender_18_5(9999, 9998, r)).start();
    }
}
