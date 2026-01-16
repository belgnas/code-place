package day5;

public class Student {
    private String name;
    private int score;

    public Student(String name, int score) {
        this.name = name;
        // ✅ 修正点1：在构造器里调用 setScore，这样初始化时也会进行检查！
        this.setScore(score);
    }


    public void setScore(int score) {
        if (score > 100 || score < 0) {
            System.out.println("成绩无效，已归零"); // 先打印
            this.score = 0; // ✅ 修正点2：显式地修改成员变量
        }
        else {
            this.score = score;
        }
    }

    public int getScore() {
        return score;
    }              
}