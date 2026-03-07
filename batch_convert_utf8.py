import os
import chardet
from collections import defaultdict

# 要处理的文件类型（和统计时一致）
TARGET_SUFFIX = ('.cpp', '.c', '.h', '.hpp', '.java', '.md', '.txt')
# 编码映射：解决chardet误判，优先用GBK（兼容gb18030/GB2312）
ENCODING_MAP = {
    'gb18030': 'gbk',
    'cp1006': 'gbk',   # chardet误判，实际是GBK/ASCII
    'cp864': 'gbk',    # chardet误判，实际是GBK/ASCII
    'Windows-1252': 'gbk',
    'windows-1252': 'gbk',
    'ascii': 'utf-8',
    'utf-8': 'utf-8'
}

# 统计转换结果
convert_success = []
convert_failed = []

def safe_convert(file_path):
    """安全转码：先检测→用正确编码读取→UTF-8写入"""
    try:
        # 1. 读取文件二进制内容
        with open(file_path, 'rb') as f:
            raw_data = f.read()
        if not raw_data:  # 空文件直接跳过
            return

        # 2. 检测编码（读前2048字节，提高准确性）
        detect_res = chardet.detect(raw_data[:2048])
        detect_enc = detect_res['encoding']
        confidence = detect_res['confidence']
        
        # 3. 映射到实际要使用的编码（解决误判）
        real_enc = ENCODING_MAP.get(detect_enc.lower(), 'gbk')
        
        # 4. 已是UTF-8则跳过
        if real_enc == 'utf-8':
            return

        # 5. 用正确编码读取（关键：不乱码的核心）
        content = raw_data.decode(real_enc, errors='ignore')  # 忽略极少数无效字符
        
        # 6. 以UTF-8无BOM写入
        with open(file_path, 'w', encoding='utf-8', newline='\n') as f:
            f.write(content)
        
        convert_success.append(f"{file_path} | 原编码：{detect_enc} → 实际解码：{real_enc}")
    except Exception as e:
        convert_failed.append(f"{file_path} | 错误：{str(e)}")

# 遍历所有文件
print("开始批量转码（只处理非UTF-8文件）...")
for root, dirs, files in os.walk('.'):
    for file in files:
        if file.endswith(TARGET_SUFFIX):
            full_path = os.path.join(root, file)
            safe_convert(full_path)

# 输出转换结果
print("\n" + "="*60)
print(f"✅ 成功转换：{len(convert_success)} 个文件")
for item in convert_success[:50]:  # 最多显示50个，避免刷屏
    print(item)
if len(convert_success) > 50:
    print(f"... 还有 {len(convert_success)-50} 个文件转换成功")

print("\n❌ 转换失败（数量为0则正常）：")
for item in convert_failed:
    print(item)
print("="*60)