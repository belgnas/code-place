// 判断与循环
// 判断：if、switch
// 循环：for、while、do...while

// 跳转语句
// 1.break：跳出循环
// 2.continue：跳过本次循环，继续下一次循环
// 3.return：返回

class IfLoopDemo {

    public static void main(String[] args) {
        // 判断：if
        int score = 80;
        if (score < 60) {
            System.out.println("差");
        } else if (score < 80) {
            System.out.println("及格");
        } else if (score < 90) {
            System.out.println("中等");
        } else if (score < 100) {
            System.out.println("优秀");
        } else {
            System.out.println("满分");
        }

        // 判断：switch
        int day = 1;
        switch (day) {
            case 1:
                System.out.println("星期一");
                break; // ps：不要忘记 break，如果没有 break，会导致 case 穿透，即会继续执行后面的 case 的代码，直到遇到 break
            case 2:
                System.out.println("星期二");
                break;
            default: // default可以省略，没有语法问题，但是不建议
                System.out.println("其他天");
        }
        
        int day2 = 2;
        switch (day2) {
            // 如果大括号只有一条代码的话，大括号可以省略
            case 1 -> {
                System.out.println("星期一");
            }
            case 2 -> System.out.println("星期二");
            default -> System.out.println("其他天");
        }

        // 循环：for
        for (int i = 0; i < 5; i++) {
            System.out.println(i);
        }

        // 循环：while
        int i = 0;
        while (i < 5) {
            if (i == 3) {
                System.out.println("i = " + i);
                i++;
                continue;
            }
            if (i == 5) {
                break;
            }
            System.out.println(i);
            i++;
            
        }

        // 循环：do...while
        int j = 0;
        do {
            System.out.println(j);
            j++;
        } while (j < 5);
    }
}