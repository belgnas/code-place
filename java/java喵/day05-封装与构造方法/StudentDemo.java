
class StudentDemo {
    public static void main(String[] args) {
        Student stu1 = new Student("学生1", 90);
        Student stu2 = new Student("学生2", 150);

        System.out.printf("学生1的成绩是%d", stu1.getScore());
        System.out.printf("学生2的成绩是%d", stu2.getScore());
    }
}