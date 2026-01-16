package day3;

public class CatDiet {
    public static void main(String[] args) {
        for (int i = 1; i <= 21; i++) {
            if (i % 7 == 0 || i % 7 == 6) {
                System.out.printf("第 %d 天：今天是周日，奖励一条鱼！\n", i);
                continue;
            }
            if (i == 15) {
                System.out.println("第 15 天：太累了，本喵不减了！");
                break;
            }

            System.out.printf("第 %d 天：跑步减肥中...\n", i);
        }
    }
}
