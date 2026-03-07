import os
import sys

def setup_console():
    """设置控制台编码，解决中文乱码问题"""
    if sys.platform == "win32":
        try:
            # 设置控制台编码为UTF-8
            import ctypes
            kernel32 = ctypes.windll.kernel32
            kernel32.SetConsoleOutputCP(65001)
            kernel32.SetConsoleCP(65001)
        except:
            pass

def create_corresponding_md(folder_path):
    """核心功能：为指定文件夹下的.cpp文件创建同名.md文件"""
    # 校验文件夹是否存在
    if not os.path.exists(folder_path):
        print("\n❌ 错误：输入的文件夹路径不存在！")
        return False
    
    # 校验路径是否为文件夹（而非文件）
    if not os.path.isdir(folder_path):
        print("\n❌ 错误：输入的路径不是有效的文件夹！")
        return False

    created_count = 0  # 新建md文件数
    existing_count = 0 # 已存在md文件数

    # 遍历文件夹中的所有文件
    for filename in os.listdir(folder_path):
        # 只处理.cpp后缀的文件
        if filename.lower().endswith(".cpp"):  # lower()兼容大写后缀（如.CPP）
            # 构造对应的md文件名
            md_filename = filename[:-4] + ".md"
            md_filepath = os.path.join(folder_path, md_filename)

            # 不存在则创建空md文件
            if not os.path.exists(md_filepath):
                try:
                    with open(md_filepath, 'w', encoding='utf-8') as f:
                        pass  # 创建空文件
                    print(f"✅ 已创建：{md_filename}")
                    created_count += 1
                except Exception as e:
                    print(f"❌ 创建失败：{md_filename} - 原因：{str(e)}")
            else:
                print(f"ℹ️ 已存在：{md_filename}（跳过）")
                existing_count += 1

    # 输出执行结果
    print("\n===== 执行完成 ======")
    print(f"📝 新建.md文件数量：{created_count}")
    print(f"📌 已存在.md文件数量：{existing_count}")
    print(f"🔢 总计处理.cpp文件数量：{created_count + existing_count}")
    return True

if __name__ == "__main__":
    # 初始化控制台编码，解决中文乱码
    setup_console()

    # 程序欢迎语
    print("="*40)
    print("      CPP文件对应MD文件创建工具")
    print("="*40)
    
    # 提示用户输入文件夹路径
    folder_path = input("\n请输入目标文件夹的完整路径（可直接复制粘贴）：\n").strip()
    
    # 执行创建操作
    create_corresponding_md(folder_path)
    
    # 防止程序运行完直接关闭窗口
    input("\n操作完成，按任意键退出程序...")