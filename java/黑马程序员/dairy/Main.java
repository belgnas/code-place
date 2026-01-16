package dairy;

import java.util.Scanner;
import java.util.Queue;
// 队列是一种特殊的线性表，它只允许在表的前端进行删除操作，而在表的后端进行插入操作。
// LinkedList类实现了Queue接口，因此我们可以把LinkedList当成Queue来用。
import java.util.LinkedList;

/**
 * @qiqimora
 * 
 */
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int x = in.nextInt();
        int y = in.nextInt();
        in.nextLine();

        char[][] grid = new char[x][y];
        for (int i = 0; i < x; i++) {
            // 读取每一行并转换为字符数组
            grid[i] = in.nextLine().toCharArray(); 
        }

        boolean[][] visited = new boolean[x][y];
        // int[] 表示一个坐标，包含 x 和 y 两个元素
        Queue<int[]> queue = new LinkedList<>();
        int flooded = 0;

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (i == 0 || i == x - 1 || j == 0 || j == y - 1) {
                    if (grid[i][j] == '0') {
                        // int[]{i, j} 表示向queue中添加一个数组{i, j}，表示坐标 (i, j)
                        queue.offer(new int[]{i, j});
                        visited[i][j] = true;
                        flooded++;
                    }
                }
            }
        }

        // 定义四个方向：左、右、上、下
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int curX = current[0];
            int curY = current[1];

            for (int i = 0; i < 4; i++) {
                int newX = curX + directions[i][0];
                int newY = curY + directions[i][1];
                if (newX >= 0 && newX < x && newY >= 0 && newY < y && !visited[newX][newY] && grid[newX][newY] == '0') {
                    visited[newX][newY] = true;
                    flooded++;
                    // 向队列中添加新的坐标 (newX, newY)，继续扩散
                    queue.offer(new int[]{newX, newY});
                }
            }
        }

        int total_0 = 0;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (grid[i][j] == '0') {
                    total_0++;
                }
            }
        }

        System.out.println(total_0 - flooded);

        in.close();
    }
}