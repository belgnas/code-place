
class Dog {
    public void eat() {
        System.out.println("狗吃狗粮");
    }
}

// 非Main类去掉public
class Husky extends Dog {
    @Override
    public void eat() {
        System.out.println("哈士奇正在拆家...");
        super.eat();
        System.out.println("吃完了一脸满足");
    }
}