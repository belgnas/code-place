
import java.util.Scanner;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

class NoteApp {
    public static void main(String[] args) {

        String path = "note.txt";
        
        try {
            FileWriter writer = new FileWriter(path);

            writer.write("明天要买猫粮\n");
            writer.write("喵！\n");
            writer.write("还有什么呢？\n");
            
            Scanner sc = new Scanner(System.in);

            String noteMessage = sc.nextLine();
            writer.write(noteMessage);

            sc.close();
            writer.close();
        }
        catch (IOException e) {
            System.out.println("保存失败：\n" + e.getMessage());
        }

        System.out.println("已保存到 note.txt，刷新项目可以查看喵！");

        System.out.println("\n2. 开始读记事本");
        try {
            File f = new File(path);

            Scanner sc = new Scanner(f);

            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                System.out.println(line);
            }

            sc.close();
        } 
        catch (IOException e) {
            System.out.println("找不到记事本：" + e.getMessage());
        }
    }
}
