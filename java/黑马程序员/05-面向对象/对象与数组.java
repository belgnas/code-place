import java.util.Scanner;

import java.util.Arrays;

class Main_hm05 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num = scanner.nextInt();

        int[] arr = new int[num];
        int sum = 0;
        for (int i = 0; i < num; i++)
        {
            arr[i] = scanner.nextInt();
            sum += arr[i];
        }

        double avg = (double) sum / num;

        Arrays.sort(arr); // 对数组进行排序

        double median = 0;
        if(num % 2 == 0)
        {
            median = (arr[num / 2 - 1] + arr[num / 2]) / 2;
        }
        else
        {
            median = arr[num / 2];
        }
        
        // 输出结果
        System.out.printf("mean=%.2f,median=%.1f", avg, median);
        scanner.close();
    }
}
