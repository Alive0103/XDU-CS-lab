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

def main(p0_list, step=0.01, conf_levels=[0.95, 0.90]):
    """
    计算不同置信水平下的最小样本量和每个k（允许误差）情况下的结果
    :param p0_list: 标称次品率列表
    :param step: 步长
    :param conf_levels: 置信水平列表
    :return: DataFrame包含所有结果
    """
    z_values = {0.95: 1.645, 0.90: 1.28}  # 不同置信水平对应的Z值
    results = []

    # 遍历每个标称次品率 p0
    for p0 in p0_list:
        # 遍历不同的允许误差E
        for E in [round(i, 2) for i in [0.01 + step * x for x in range(int((0.10 - 0.01) / step + 1))]]:
            row = {'k': E, 'p0': p0}
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
                row[f"{int(conf_level * 100)}% 信度次品率"] = k / n

            results.append(row)

    df = pd.DataFrame(results)
    df.to_csv("不同k结果.csv", index=False)
    return df

p0_values = [0.10, 0.2, 0.05]
df_results = main(p0_values)
df_results.head()
