import math
from scipy.stats import binom
import itertools
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import openpyxl


# 计算组合数C(a, b)
def comb(a, b):
    return math.comb(int(a), int(b))


# 期望计算函数
def case_generic(n, p1, p2, minn):
    Ex = 0
    start_k = int(n * (1 - p1) - n * p2)
    if minn == 0:
        end_k = int(n * (1 - p1))
    else:
        end_k = int(min(n * (1 - p1), n * (1 - p2)))

    # 遍历 k 的取值范围，累加期望值
    for k in range(start_k, end_k + 1):
        Ex += int((comb(n * (1 - p2), k) * comb(n * p2, n * (1 - p1) - k)) / comb(n, n * (1 - p1)) * k)
    return Ex


def case_m(e1, e2, e3, e4, p1, p2, p3, b1, b2, b3, d, f, n):
    previous_m = 0
    current_m = 0
    iteration = 0  # 初始化迭代次数

    while True:
        iteration += 1  # 每次循环迭代数+1
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

        if n < 1:
            break

        if current_m > 0:
            previous_m += current_m
            if e4 == 0:
                break
            else:
                n = n3
        else:
            break

    return previous_m, first_iteration_data, iteration  # 确保返回三个值


# 初始数据
n = 1000  # 零件数量
b_values = [[2, 3, 3], [2, 3, 3], [2, 3, 3], [1, 1, 2], [8, 1, 2], [2, 3, 3]]  # 零件1和2,成品的检测成本组合
p_values = [[0.153, 0.153, 0.153], [0.253, 0.253, 0.253], [0.153, 0.153, 0.153], [0.253, 0.253, 0.253],
            [0.153, 0.253, 0.153], [0.094, 0.094, 0.094]]  # 零件1和2,成品的次品率组合
d_values = [5, 5, 5, 5, 5, 40]  # 拆解成本
f_values = [6, 6, 30, 30, 10, 10]  # 调换成本

# e1, e2, e3, e4 可能的取值组合
e_values = list(itertools.product([0, 1], repeat=4))

results = []

# 遍历每个 b, p, d, f 的组合
for idx in range(len(b_values)):
    b1, b2, b3 = b_values[idx]
    p1, p2, p3 = p_values[idx]
    d = d_values[idx]
    f = f_values[idx]

    max_m = -float('inf')  # 用来记录每个组合中最大的m
    best_e_comb = None  # 用来记录对应最大m的e1~e4组合
    max_iteration = 0  # 用来记录最大的迭代轮数

    for e_comb in e_values:
        e1, e2, e3, e4 = e_comb
        # 提取返回的总利润 (previous_m) 和迭代轮数 (iteration)
        previous_m, first_iteration_data, iteration = case_m(e1, e2, e3, e4, p1, p2, p3, b1, b2, b3, d, f, n)

        # 保存结果
        results.append({
            "组合": idx + 1,
            "e1": e1, "e2": e2, "e3": e3, "e4": e4,
            "m": previous_m,
            "迭代次数": iteration
        })

        # 更新最大m及对应组合
        if previous_m > max_m:
            max_m = previous_m
            best_e_comb = e_comb
            max_iteration = iteration  # 保存最大m时的迭代次数

    # 输出当前组合的最大m值及对应的e组合和迭代次数
    print(f"组合 {idx + 1} 的最大 m 值为: {max_m}, 对应的 e 组合为: {best_e_comb}, 最大迭代次数为: {max_iteration}")

