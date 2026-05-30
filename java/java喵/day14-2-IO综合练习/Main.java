import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

class Main_day14_2 {

    static void saveWinner(String name) throws IOException {
        String path = "winner.txt";

        FileWriter writer = new FileWriter(path);
        
        writer.write(name);

        writer.close();
    }

    public static void main(String[] args) {
        ArrayList<String> petName = new ArrayList<String>();
        petName.add("小白");
        petName.add("小黑");
        petName.add("花花");
        petName.add("大黄");

        int randomNum = (int)(Math.random() * petName.size());
        String randomPetName = petName.get(randomNum);

        try {
            saveWinner(randomPetName);
            System.out.println("恭喜 [" + randomPetName + "] 中奖！名单已保存！");
        }
        catch (IOException e) {
            System.out.println("出错了喵！");
            System.out.println(e.getMessage());
        }
    }
}
