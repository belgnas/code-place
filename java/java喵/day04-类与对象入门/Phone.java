
class Phone {

    String brand;
    double price;

    public void call() {
        System.out.printf("\"正在使用 [%s] 手机打电话...\"\n", brand);
    }

    public void sendMessage() {
        System.out.printf("\"正在发送短信...\"\n");
    }
}