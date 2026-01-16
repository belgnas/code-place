package day8;

public class Payment {
    public void pay() {
        System.out.println("正在进行支付操作...");
    }
}

class Alipay extends Payment {
    @Override
    public void pay() {
        super.pay();
        System.out.println("使用支付宝支付：扫码成功！");
    }
}

class WeChatPay extends Payment {
    @Override
    public void pay() {
        super.pay();
        System.out.println("使用微信支付：扫码成功！");
    }
}
