package day6;

class Hero {
    String nickname;
    public void move() {
        System.out.println(nickname + " 正在移动...");
    }
}

class Warrior extends Hero {
    public void attack() {
        System.out.println(nickname + " 挥舞大剑劈砍！");
    }
}

class Mage extends Hero {
    public void fireBall() {
        System.out.println(nickname + " 释放了火球术！");
    }
}
