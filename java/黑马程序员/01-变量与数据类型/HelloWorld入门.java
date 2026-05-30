
class HelloWorldDemo {
    public static void main(String[] args) {
        System.out.println("Hello World!");
        /*
         * 这是一个简单的Java程序，用于输出"Hello World!"。
         * 它是Java程序的基础，用于展示Java的语法和运行机制。
         */
    }
}

//   代码精解:
//    * /** ... */ 文档注释 (Javadoc): 这种注释非常特殊，可以通过Java的javadoc工具生成程序的官方API文档。在IDE中
//      ，鼠标悬停在类名或方法名上时，通常会显示这种注释的内容。
//    * class HelloWorld:
//    * public static void main(String[] args): 这是主方法 (main
//      method)，是整个Java程序的唯一入口。Java虚拟机(JVM)会从这里开始执行。
//    * System.out.println("Hello, World!");:
//   在VS Code中运行:
//   确保你已经安装了微软官方的 "Extension Pack for Java"。安装后，VS Code会智能地识别Java代码。
//   1.  在main方法的上方，你会看到一个 "Run" 按钮。
//   2.  点击 "Run"，VS Code会自动编译 (.java -> .class) 并在下方的 TERMINAL (终端)
//   窗口中运行程序，你将看到输出 Hello, World!。