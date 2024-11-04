import matplotlib.pyplot as plt
import math
from scipy.stats import binom
import pandas as pd


def calculate_sample_size(p0, E, Z):
    """
    根据标称次品率、允许误差和Z值计算最小样本量
    :param p0: 标称次品率
    :param E: 允许误差
    :param Z: Z值（根据置信水平）
    :return: 计算出的最小样本量
    """
    n = (Z ** 2 * p0 * (1 - p0)) / (E ** 2)
    return math.ceil(n)


def calculate_critical_value(n, p0, alpha):
    """
    根据样本量、标称次品率和显著性水平计算临界次品数
    :param n: 样本量
    :param p0: 标称次品率
    :param alpha: 显著性水平 (1 - 置信水平)
    :return: 临界次品数
    """
    k = 0
    while binom.cdf(k, n, p0) < 1 - alpha:  # 使用二项分布的累计分布函数(cdf)计算
        k += 1
    return k


def main(p0=0.10, step=0.01, conf_levels=[0.95, 0.90]):
    """
    计算不同置信水平下的最小样本量和每个k（允许误差）情况下的结果
    :param p0: 标称次品率
    :param step: 步长
    :param conf_levels: 置信水平列表
    :return: DataFrame包含所有结果
    """
    z_values = {0.95: 1.645, 0.90: 1.28}  # 不同置信水平对应的Z值
    results = []

    # 遍历不同的允许误差k，不再使用frange函数，直接生成列表
    for E in [round(i, 2) for i in [0.01 + step * x for x in range(int((0.10 - 0.01) / step + 1))]]:
        row = {'k': E}
        for conf_level in conf_levels:
            Z = z_values.get(conf_level, None)
            if Z is None:
                print(f"不支持的置信水平: {conf_level}")
                continue

            # 计算最小样本量
            n = calculate_sample_size(p0, E, Z)
            alpha = 1 - conf_level  # 显著性水平
            # 计算临界值
            k = calculate_critical_value(n, p0, alpha)
            row[f"{int(conf_level * 100)}% 信度最小检测量（个）"] = n
            row[f"{int(conf_level * 100)}% 信度允许次品数（个）"] = k

        results.append(row)

    df = pd.DataFrame(results)
    df.to_csv("不同k.csv", index=False)  # 保存结果为CSV文件
    return df


# 调用主函数，生成结果并保存
df_results = main()

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

k_values = df_results['k']
sample_95 = df_results['95% 信度最小检测量（个）']
sample_90 = df_results['90% 信度最小检测量（个）']
critical_95 = df_results['95% 信度允许次品数（个）']
critical_90 = df_results['90% 信度允许次品数（个）']

# 绘制条形图
plt.figure(figsize=(12, 6))

bar_width = 0.2  # 条形图的宽度
index = range(len(k_values))  # 横坐标索引

# 绘制四个条形图
bars_95_sample = plt.bar([i - bar_width*1.5 for i in index], sample_95, bar_width, label='95% 信度最小检测量（个）', color='blue')
bars_90_sample = plt.bar([i - bar_width/2 for i in index], sample_90, bar_width, label='90% 信度最小检测量（个）', color='orange')
bars_95_critical = plt.bar([i + bar_width/2 for i in index], critical_95, bar_width, label='95% 信度允许次品数（个）', color='red')
bars_90_critical = plt.bar([i + bar_width*1.5 for i in index], critical_90, bar_width, label='90% 信度允许次品数（个）', color='green')

# 在条形图上标出数值
for bar in bars_95_sample:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, int(yval), va='bottom', ha='center')  # 调整水平和垂直对齐

for bar in bars_90_sample:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, int(yval), va='bottom', ha='center')

for bar in bars_95_critical:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, int(yval), va='bottom', ha='center')

for bar in bars_90_critical:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval, int(yval), va='bottom', ha='center')

# 添加标签和标题
plt.xlabel('允许误差 k (%)')
plt.ylabel('数量（个）')
plt.title('不同允许误差 k 下 95% 和 90% 信度的最小检测量与允许次品数')
plt.xticks(index, [f'{k * 100:.0f}%' for k in k_values])
plt.legend()

# 显示图表
plt.tight_layout()
plt.show()
