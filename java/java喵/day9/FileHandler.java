package day9;

import java.util.Scanner;

public class FileHandler {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入文件名：");
        String fileName = sc.nextLine();

        // 1. 先清理空格 (保留原始大小写)
        String originalClean = fileName.trim();

        // 2. 制作一个小写副本 (专门用来检查后缀)
        String lowerCheck = originalClean.toLowerCase();

        // 3. 使用 endsWith 安全检查
        if (lowerCheck.endsWith(".jpg") || lowerCheck.endsWith(".png")) {
            System.out.println("检测到图片文件");

            // 4. 提取文件名 (使用原始字符串操作)
            int idx = originalClean.lastIndexOf('.'); // 建议用 lastIndexOf，防止文件名里有点号（如 my.photo.jpg）

            if (idx != -1) { // 安全检查：万一没有点号呢？
                String photoName = originalClean.substring(0, idx);
                System.out.println("文件名主体是：" + photoName);
            }
        } else {
            System.out.println("文件格式不支持");
        }

        sc.close();
    }
}