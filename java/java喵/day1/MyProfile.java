package day1;

public class MyProfile { // 类名首字母大写
    public static void main(String[] args) {
        String nickName = "qiqimora"; // 变量名要有意义
        int day = 30;
        double percent = 0.3; // 拼写修正

        System.out.println("你好，我是" + nickName);
        System.out.println("我计划学习" + day + "天");
        // 这里加括号是为了阅读清晰，虽然原本的优先级也没错
        System.out.println("目前的进度是" + (percent * 100) + "%"); 
    }
}