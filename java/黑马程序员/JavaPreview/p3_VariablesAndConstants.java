// 变量和常量（Variables and Constants）

// 变量：其值在程序运行期间可以改变
// 常量：其值在程序运行期间不能改变

package JavaPreview;

public class p3_VariablesAndConstants {
    public static void main(String[] args) {
        int score = 85;
        System.out.println("初始分数：" + score);
        score = 90;
        System.out.println("修改后分数：" + score);

        final int DAYS_IN_WEEK = 7;
        // DAYS_IN_WEEK = 8; // 这行代码会编译错误，因为常量的值不能被修改
        System.out.println("一周有 " + DAYS_IN_WEEK + " 天");
    }
}
