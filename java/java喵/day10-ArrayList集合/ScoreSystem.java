
import java.util.ArrayList;
import java.util.Scanner;

class ScoreSystem {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        // ✅ 修正1：左边也要加上 <Integer>，确保拿出来的是整数
        ArrayList<Integer> score = new ArrayList<Integer>();
        
        System.out.println("请输入4个成绩：");
        for (int i = 0; i < 4; i++) {
            int num = sc.nextInt();
            score.add(num);
        }

        int sumScore = 0;

        for (int i = 0; i < score.size(); i++) {
            // ✅ 修正2：获取元素要用 get(i)
            // 拿到当前分数
            int currentScore = score.get(i); 
            
            if (currentScore < 60) {
                // 这里加了 (i+1) 是为了显示更人性化（第1个而不是第0个）
                System.out.println("第" + (i + 1) + "个成绩：警告：发现不及格分数！");
            }
            sumScore += currentScore;
        }

        System.out.println("一共有 " + score.size() + " 个成绩，总分是：" + sumScore);

        sc.close();
    }
}