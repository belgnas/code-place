import os
import sys
import tkinter as tk
from tkinter import ttk, filedialog, scrolledtext
import threading

class CPP2MDTool:
    def __init__(self, root):
        # 主窗口设置
        self.root = root
        self.root.title("CPP文件批量创建MD工具")
        self.root.geometry("700x500")  # 窗口大小：宽700，高500
        self.root.resizable(False, False)  # 禁止调整窗口大小

        # 选中的文件夹路径
        self.folder_path = tk.StringVar()

        # ========== 界面布局 ==========
        # 1. 文件夹选择区域
        frame_folder = ttk.Frame(root, padding="10")
        frame_folder.pack(fill=tk.X, padx=10, pady=10)

        ttk.Label(frame_folder, text="目标文件夹：").pack(side=tk.LEFT, padx=5)
        ttk.Entry(frame_folder, textvariable=self.folder_path, width=60).pack(side=tk.LEFT, padx=5)
        ttk.Button(frame_folder, text="选择文件夹", command=self.select_folder).pack(side=tk.LEFT, padx=5)

        # 2. 执行按钮区域
        frame_btn = ttk.Frame(root, padding="10")
        frame_btn.pack(fill=tk.X, padx=10, pady=5)

        self.run_btn = ttk.Button(frame_btn, text="开始创建MD文件", command=self.run_create_task)
        self.run_btn.pack(side=tk.LEFT, padx=5)

        # 3. 结果显示区域
        frame_result = ttk.Frame(root, padding="10")
        frame_result.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        ttk.Label(frame_result, text="执行日志：").pack(anchor=tk.W)
        # 带滚动条的文本框，显示执行结果
        self.result_text = scrolledtext.ScrolledText(frame_result, width=80, height=25, font=("Consolas", 9))
        self.result_text.pack(fill=tk.BOTH, expand=True)
        # 设置文本框只读（避免误操作）
        self.result_text.config(state=tk.DISABLED)

    def select_folder(self):
        """点击按钮选择文件夹"""
        folder = filedialog.askdirectory(title="选择目标文件夹")
        if folder:
            self.folder_path.set(folder)
            self.log(f"已选中文件夹：{folder}")

    def log(self, msg):
        """在结果框中输出日志"""
        self.result_text.config(state=tk.NORMAL)  # 临时解除只读
        self.result_text.insert(tk.END, f"{msg}\n")
        self.result_text.see(tk.END)  # 自动滚动到最后一行
        self.result_text.config(state=tk.DISABLED)  # 恢复只读

    def create_md_files(self):
        """核心：创建MD文件（放在子线程中执行，避免界面卡死）"""
        folder = self.folder_path.get().strip()
        if not folder:
            self.log("❌ 错误：请先选择目标文件夹！")
            self.run_btn.config(state=tk.NORMAL)  # 恢复按钮可用
            return

        # 校验文件夹
        if not os.path.exists(folder):
            self.log("❌ 错误：选中的文件夹路径不存在！")
            self.run_btn.config(state=tk.NORMAL)
            return
        if not os.path.isdir(folder):
            self.log("❌ 错误：选中的路径不是有效的文件夹！")
            self.run_btn.config(state=tk.NORMAL)
            return

        # 开始处理
        self.log("===== 开始处理 =====")
        created = 0
        existing = 0

        for filename in os.listdir(folder):
            if filename.lower().endswith(".cpp"):
                md_filename = filename[:-4] + ".md"
                md_filepath = os.path.join(folder, md_filename)

                if not os.path.exists(md_filepath):
                    try:
                        with open(md_filepath, 'w', encoding='utf-8'):
                            pass
                        self.log(f"✅ 创建成功：{md_filename}")
                        created += 1
                    except Exception as e:
                        self.log(f"❌ 创建失败：{md_filename} - 原因：{str(e)}")
                else:
                    self.log(f"ℹ️ 已存在：{md_filename}（跳过）")
                    existing += 1

        # 汇总结果
        self.log("\n===== 处理完成 =====")
        self.log(f"📝 新建MD文件数量：{created}")
        self.log(f"📌 已存在MD文件数量：{existing}")
        self.log(f"🔢 总计处理CPP文件数量：{created + existing}")
        self.run_btn.config(state=tk.NORMAL)  # 恢复按钮可用

    def run_create_task(self):
        """点击“开始创建”按钮的回调（启动子线程，避免界面卡死）"""
        self.run_btn.config(state=tk.DISABLED)  # 禁用按钮，防止重复点击
        self.result_text.config(state=tk.NORMAL)
        self.result_text.delete(1.0, tk.END)  # 清空之前的日志
        self.result_text.config(state=tk.DISABLED)
        # 启动子线程执行创建任务
        task_thread = threading.Thread(target=self.create_md_files)
        task_thread.daemon = True  # 主线程退出时子线程也退出
        task_thread.start()

if __name__ == "__main__":
    # 创建主窗口
    root = tk.Tk()
    # 初始化工具界面
    app = CPP2MDTool(root)
    # 运行主循环
    root.mainloop()