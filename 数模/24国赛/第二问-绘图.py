import math
from scipy.stats import binom
import itertools
import matplotlib.pyplot as plt
import numpy as np

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False


# 绘制雷达图的函数，不包含图例
def plot_radar_charts(data, combination_id, ax, cmap, color_idx):
    """
    绘制雷达图，显示组合的第一次迭代数据
    :param data: 每个e组合对应的数据
    :param combination_id: 组合ID
    :param ax: 子图的axes对象
    :param cmap: 颜色映射
    :param color_idx: 当前颜色索引
    """
    labels = ['零件检测成本', '装配成本', '成品检测成本', '拆解成本', '调换成本', '营业额', '当前总利润']

    num_vars = len(labels)
    angles = np.linspace(0, 2 * np.pi, num_vars, endpoint=False).tolist()  # 均匀分布在圆周上
    angles += angles[:1]  # 闭合圆

    # 遍历每个 e 的排列组合，绘制雷达图线条
    for e_comb, values in data.items():
        values = values + values[:1]  # 闭合圆
        color = cmap(color_idx % cmap.N)  # 获取颜色
        ax.plot(angles, values, linewidth=2, color=color)  # 绘制线条
        color_idx += 1

    # 设置标签
    ax.set_yticklabels([])  # 隐藏径向坐标标签
    ax.set_xticks(angles[:-1])
    ax.set_xticklabels(labels, fontsize=12)  # 增大字体大小为12
    ax.set_title(f"组合 {combination_id}", fontsize=16)  # 增大标题字体为16


# 计算组合数C(a, b)
def comb(a, b):
    return math.comb(int(a), int(b))


# 期望计算函数
def case_generic(n, p1, p2, minn):
    Ex = 0  # 保持 Ex 为浮点数
    start_k = int(n * (1 - p1) - n * p2)  # 确保 k 计算是浮点数，并取整
    if minn == 0:
        end_k = int(n * (1 - p1))
    else:
        end_k = int(min(n * (1 - p1), n * (1 - p2)))

    for k in range(start_k, end_k + 1):
        Ex += int((comb(n * (1 - p2), k) * comb(n * p2, n * (1 - p1) - k)) / comb(n, n * (1 - p1)) * k)
    return Ex


def case_m(e1, e2, e3, e4, p1, p2, p3, b1, b2, b3, d, f, n):
    previous_m = 0
    current_m = 0
    iteration = 0

    while 1:
        iteration += 1
        m1 = int(n * 4 + n * 18)

        # 计算成本项
        m2 = int(n * e1 * b1 + n * e2 * b2)
        n2 = min(int(n - n * p1 * e1), int(n - n * p2 * e2))
        m3 = int(n2 * 6)
        m4 = int(n2 * e3 * b3)

        # 成品中不合格的数量
        if e1 == 1 and e2 == 0:
            n3 = int(p3 * case_generic(n, p1, p2, 0) + (n2 - case_generic(n, p1, p2, 0)))
        elif e2 == 1 and e1 == 0:
            n3 = int(p3 * case_generic(n, p2, p1, 0) + (n2 - case_generic(n, p2, p1, 0)))
        elif e2 == 1 and e1 == 1:
            n3 = int(p3 * n2)
        else:
            n3 = int(p3 * case_generic(n, p1, p2, 1) + (n2 - case_generic(n, p1, p2, 1)))

        nn = min(int(n2 - n3 * e3), n2)
        m5 = int(n3 * e4 * d)
        ex = int((b1 + b2 + 6 + d + (4 + 18) * 2) / 2)
        m6 = int(n3 * (f + ex) * (1 - e3))

        if iteration == 1:
            current_m = int(56 * nn - (m1 + m2 + m3 + m4 + m5 + m6))
        else:
            current_m = int(56 * nn - (m2 + m3 + m4 + m5 + m6))

        if iteration == 1:
            first_iteration_data = {
                "m2": m2, "m3": m3, "m4": m4, "m5": m5, "m6": m6,
                "营业额": 56 * nn, "总利润": current_m
            }

        if current_m > n3 * d:
            previous_m += current_m
            if e4 == 0:
                break
            else:
                n = n3
                if n < 10:
                    break
        else:
            break

    return previous_m, first_iteration_data

# 初始数据
n = 1000
b_values = [[2, 3, 3], [2, 3, 3], [2, 3, 3], [1, 1, 2], [8, 1, 2], [2, 3, 3]]
p_values = [[0.10, 0.10, 0.1], [0.2, 0.2, 0.2], [0.1, 0.1, 0.1], [0.2, 0.2, 0.2], [0.1, 0.2, 0.1], [0.05, 0.05, 0.05]]
d_values = [5, 5, 5, 5, 5, 40]
f_values = [6, 6, 30, 30, 10, 10]
e_values = list(itertools.product([0, 1], repeat=4))

# 获取颜色映射，设置更大数量的颜色
cmap = plt.colormaps['tab20']
color_idx = 0  # 颜色索引

# 遍历每个 b, p, d, f 的组合
for idx in range(len(b_values)):
    b1, b2, b3 = b_values[idx]
    p1, p2, p3 = p_values[idx]
    d = d_values[idx]
    f = f_values[idx]

    e_combination_data = {}

    # 遍历所有可能的 e1, e2, e3, e4 的组合
    for e_comb in e_values:
        e1, e2, e3, e4 = e_comb
        total_profit, first_iteration_data = case_m(e1, e2, e3, e4, p1, p2, p3, b1, b2, b3, d, f, n)

        e_combination_data[f"({e1},{e2},{e3},{e4})"] = [
            first_iteration_data["m2"], first_iteration_data["m3"], first_iteration_data["m4"],
            first_iteration_data["m5"], first_iteration_data["m6"],
            first_iteration_data["营业额"], first_iteration_data["总利润"]
        ]

    # 为当前组合绘制单独的雷达图
    fig, ax = plt.subplots(figsize=(6, 6), subplot_kw=dict(polar=True))
    plot_radar_charts(e_combination_data, idx + 1, ax, cmap, color_idx)

    # 显示单独的图
    plt.tight_layout()
    plt.show()
