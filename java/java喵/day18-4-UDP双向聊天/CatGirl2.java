
class CatGirl2_18_4 {
    public static void main(String[] args) {
        // 监听 9999，发送给 9998
        new Thread(new Receiver_18_4(9999)).start();
        new Thread(new Sender_18_4(9998)).start();
    }
}