import os
import chardet
from collections import defaultdict

# 你要统计的文件类型（代码+笔记）
TARGET_SUFFIX = ('.cpp', '.c', '.h', '.hpp', '.java', '.md', '.txt')

# 编码统计
encoding_count = defaultdict(int)
encoding_files = defaultdict(list)

def check_encoding(file_path):
    try:
        with open(file_path, 'rb') as f:
            raw = f.read(1024 * 100)  # 读前100k足够判断编码
        if not raw:
            return
        
        res = chardet.detect(raw)
        enc = res['encoding']
        confidence = res['confidence']

        encoding_count[enc] += 1
        encoding_files[enc].append(file_path)

    except Exception as e:
        pass

# 遍历当前文件夹（就是你的 code 文件夹）
for root, dirs, files in os.walk('.'):
    for f in files:
        if f.endswith(TARGET_SUFFIX):
            full_path = os.path.join(root, f)
            check_encoding(full_path)

# 输出结果
print("=" * 50)
print("编码格式统计结果（只看代码/笔记文件）")
print("=" * 50)

for enc, cnt in sorted(encoding_count.items(), key=lambda x: -x[1]):
    print(f"{enc:<12} : {cnt:>3} 个文件")

print("\n按编码查看文件路径（可直接复制）：")
print("-" * 50)

for enc, files in encoding_files.items():
    if not files:
        continue
    print(f"\n【{enc}】")
    for f in files[:20]:  # 每种最多显示20个，避免刷屏
        print(f"  {f}")
    if len(files) > 20:
        print(f"  ... 还有 {len(files)-20} 个")