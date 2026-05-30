
class PhoneDemo {
    public static void main(String[] args) {
        Phone myPhone1 = new Phone();
        Phone myPhone2 = new Phone();

        myPhone1.brand = "华为";
        myPhone1.price = 6999;
        myPhone2.brand = "苹果";
        myPhone2.price = 8999;

        myPhone1.call();
        myPhone2.call();
    }
}