
// CatGirl2.java
class CatGirl2_18_5 {
    public static void main(String[] args) {
        Receiver_18_5 r = new Receiver_18_5(9999);
        new Thread(r).start();
        new Thread(new Sender_18_5(9998, 9999, r)).start();
    }
}