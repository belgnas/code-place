package day11;

class DiceTool {
    public static int roll() {
        // (int)(Math.random() * 个数) + 起始值
        int randomNum = (int)(Math.random() * 6) + 1;
        return randomNum;
    }
}

public class LuckyDraw {
    public static void main(String[] args) {
        int total = 0;
        for (int i = 0; i < 3; i++) {
            int tempNum = DiceTool.roll();
            total += tempNum;
        }
        total = Math.max(total, 10);

        System.out.println(total);
    }
}
