import re
import matplotlib.pyplot as plt

# result.txt 파일에서 데이터 파싱
data = {}
with open('result.txt', encoding='utf-8') as f:
    content = f.read()
    blocks = content.strip().split('======================================')
    for block in blocks:
        lines = block.strip().splitlines()
        if len(lines) < 2:
            continue
        lang = lines[0].strip()
        for line in lines:
            if 'Execution time:' in line:
                # ms 단위만 추출
                match = re.search(r'([\d.]+)\s*ms', line)
                if match:
                    data[lang] = float(match.group(1))

# 차트 그리기
langs = list(data.keys())
times = [data[lang] for lang in langs]

plt.figure(figsize=(10,6))
plt.bar(langs, times, color='skyblue')
plt.xlabel('Language')
plt.ylabel('Execution Time (ms)')
plt.title('Execution Time by Language')
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('result_chart.png')