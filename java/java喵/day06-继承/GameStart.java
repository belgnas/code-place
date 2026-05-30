
class GameStart {
    public static void main(String[] args) {
        Warrior hero1 = new Warrior();
        Mage hero2 = new Mage();
        
        hero1.nickname = "亚瑟";
        hero2.nickname = "安琪拉";

        hero1.move();
        hero1.attack();

        hero2.move();
        hero2.fireBall();
    }
}
