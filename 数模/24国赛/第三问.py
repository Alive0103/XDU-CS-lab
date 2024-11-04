import numpy as np
import pandas as pd

# 参数定义
detection_costs = [1, 1, 2, 1, 1, 2, 1, 2]  # 检测成本
assembly_cost = 8  # 每个零件的装配成本
decision_combinations = [(e1, e2, e3, e4, e5, e6, e7, e8) for e1 in [0, 1] for e2 in [0, 1] for e3 in [0, 1]
                         for e4 in [0, 1] for e5 in [0, 1] for e6 in [0, 1]
                         for e7 in [0, 1] for e8 in [0, 1]]  # 所有可能的决策组合

# 给定每个零件的次品率和初始数量
defect_rate = 0.153  # 次品率为10%
initial_count = 1000  # 初始数量
detection_effect = 1 - 0.153  # 检测后合格零件比例


# 模拟装配，返回合格和总数
def simulate_assembly(e1, e2, e3, e4, e5, e6, e7, e8):
    decisions = [e1, e2, e3, e4, e5, e6, e7, e8]
    parts = []

    for i in range(8):
        if decisions[i]:
            part = np.ones(int(initial_count * detection_effect))  # 检测后全合格
            padding = np.zeros(initial_count - len(part))  # 用0填充
            parts.append(np.concatenate([part, padding]))
        else:
            parts.append(np.random.choice([0, 1], size=initial_count, p=[defect_rate, 1 - defect_rate]))

    parts = np.array(parts)

    # 半成品1, 2, 3的合格品计算
    semi_product_1 = np.all(parts[0:3, :], axis=0)
    semi_product_1_total = 900 if any([e1, e2, e3]) else initial_count

    semi_product_2 = np.all(parts[3:6, :], axis=0)
    semi_product_2_total = 900 if any([e4, e5, e6]) else initial_count

    semi_product_3 = np.all(parts[6:8, :], axis=0)
    semi_product_3_total = 900 if any([e7, e8]) else initial_count

    return (np.sum(semi_product_1), semi_product_1_total,
            np.sum(semi_product_2), semi_product_2_total,
            np.sum(semi_product_3), semi_product_3_total)


# 计算最小成本
def calculate_cost(semi_product_qualified, semi_product_total, detection_decisions, detection_costs, assembly_cost):
    defective_count = semi_product_total - semi_product_qualified
    detection_cost = sum([d * c * 1000 for d, c in zip(detection_decisions, detection_costs)])  # 1000是数量
    if defective_count == 0:
        return detection_cost
    return defective_count * assembly_cost + detection_cost


def calc_new_defect_rate(d_rate, t_count):
    """计算新的不合格品率"""
    orig_def_count = d_rate * t_count
    add_def_count = (1 - d_rate) * t_count * 0.153
    new_def_count = orig_def_count + add_def_count
    return new_def_count / t_count


def calc_costs(e4, e5, orig_total, orig_def_rate):
    """计算新的总数、新的不合格品数以及成本"""
    # 根据 e4 的值确定 e6
    e6 = 1 - e4

    # 计算新的不合格品率
    new_def_rate = calc_new_defect_rate(orig_def_rate, orig_total)

    # 计算检测后的新总数
    if e4:  # 如果检测
        detected_total = orig_total - (new_def_rate * orig_total)
    else:  # 如果不检测
        detected_total = orig_total

    new_def_count = new_def_rate * detected_total

    # 计算成本
    det_cost = e4 * orig_total * 4  # 检测成本
    # 拆解成本 = 新的不合格品数 * 拆解成本单价
    split_cost = e5 * new_def_count * 6

    # 调换成本 = 不合格品数 * 调换成本单价 (调换针对不合格品)
    swap_cost = e6 * new_def_count * 10

    # 确保成本不为负数
    det_cost = max(det_cost, 0)
    split_cost = max(split_cost, 0)
    swap_cost = max(swap_cost, 0)

    total_cost = det_cost + split_cost + swap_cost

    return detected_total, new_def_count, det_cost, split_cost, swap_cost, total_cost


iteration = 0
total_ben = 0

results = []
for decision in decision_combinations:
    e1, e2, e3, e4, e5, e6, e7, e8 = decision
    result = simulate_assembly(e1, e2, e3, e4, e5, e6, e7, e8)

    # 成本计算
    cost1 = calculate_cost(result[0], result[1], decision[0:3], detection_costs[0:3], assembly_cost)
    cost2 = calculate_cost(result[2], result[3], decision[3:6], detection_costs[3:6], assembly_cost)
    cost3 = calculate_cost(result[4], result[5], decision[6:8], detection_costs[6:8], assembly_cost)

    total_cost = cost1 + cost2 + cost3
    results.append(
        [e1, e2, e3, e4, e5, e6, e7, e8, result[0], result[1], result[2], result[3], result[4], result[5], total_cost])

# 转换为DataFrame并展示
df_results_with_cost = pd.DataFrame(results, columns=[
    'e1', 'e2', 'e3', 'e4', 'e5', 'e6', 'e7', 'e8',
    '半成品1_合格数', '半成品1_总数',
    '半成品2_合格数', '半成品2_总数',
    '半成品3_合格数', '半成品3_总数', '总成本'
])

# 找出总成本最小的行
min_cost_row = df_results_with_cost.loc[df_results_with_cost['总成本'].idxmin()]
total_ben += min_cost_row['总成本']


def calc_new_defect_rate(d_rate, t_count):
    orig_def_count = d_rate * t_count
    add_def_count = (1 - d_rate) * t_count * 0.153
    new_def_count = orig_def_count + add_def_count
    return new_def_count / t_count


def simulate_assembly(e1, e2, e3, t_counts, d_rates):
    decs = [e1, e2, e3]
    parts = []

    for i in range(3):
        t_count = t_counts[i]
        d_rate = d_rates[i]

        new_d_rate = calc_new_defect_rate(d_rate, t_count)

        if decs[i]:
            part = np.ones(int(t_count * (1 - new_d_rate)))
            parts.append(part)
        else:
            parts.append(np.random.choice([0, 1], size=t_count, p=[new_d_rate, 1 - new_d_rate]))

    min_count = min(len(p) for p in parts)
    parts = [p[:min_count] for p in parts]

    semi_prod = np.all(parts[0:3], axis=0)
    total_count = min_count

    return np.sum(semi_prod), total_count


t_counts = [min_cost_row['半成品1_总数'], min_cost_row['半成品2_总数'], min_cost_row['半成品3_总数']]
d_rates = [(min_cost_row['半成品1_总数'] - min_cost_row['半成品1_合格数']) / min_cost_row['半成品1_总数'],
           (min_cost_row['半成品2_总数'] - min_cost_row['半成品2_合格数']) / min_cost_row['半成品2_总数'],
           (min_cost_row['半成品3_总数'] - min_cost_row['半成品3_合格数']) / min_cost_row['半成品3_总数']]

# 生成所有 e1、e2、e3 组合
results = []
for e1 in [0, 1]:
    for e2 in [0, 1]:
        for e3 in [0, 1]:
            q_count, t_count = simulate_assembly(e1, e2, e3, t_counts, d_rates)

            # 计算成本
            det_cost = (e1 * t_counts[0] * 4 +
                        e2 * t_counts[1] * 4 +
                        e3 * t_counts[2] * 4)

            assem_cost = (t_count - q_count) * 8
            split_cost = (t_count - q_count) * 6

            total_cost = split_cost + assem_cost + det_cost

            results.append({
                'e1': e1,
                'e2': e2,
                'e3': e3,
                '总成本': total_cost,
                '装配总数': t_count,
                '合格数': q_count,
                '拆解成本': split_cost,
                '检测成本': det_cost,
                '装配花费': assem_cost
            })

# 保存结果
df_results = pd.DataFrame(results)

# 找到最小花费
min_cost_idx = df_results['总成本'].idxmin()
min_cost_row2 = df_results.loc[min_cost_idx]
total_ben += min_cost_row2['总成本']

print("所有结果：")
print(df_results)
print("\n最小半成品->成本花费情况：")
print(min_cost_row2)

orig_total = min_cost_row2['装配总数']
orig_def_rate = (min_cost_row2['装配总数'] - min_cost_row2['合格数']) / min_cost_row2['装配总数']

# 生成所有 e4、e5 组合
results = []
for e4 in [0, 1]:  # 检测
    e6 = 1 - e4  # 动态确定 e6 的值
    for e5 in [0, 1]:  # 拆解
        detected_total, new_def_count, det_cost, split_cost, swap_cost, total_cost = calc_costs(e4, e5, orig_total,
                                                                                                orig_def_rate)

        results.append({
            'e4': e4,
            'e5': e5,
            'e6': e6,
            '新总数': detected_total,
            '新不合格品数': new_def_count,
            '检测成本': det_cost,
            '拆解成本': split_cost,
            '调换成本': swap_cost,
            '总成本': total_cost
        })

# 保存结果
df_results = pd.DataFrame(results)

# 找到最小花费
min_cost_idx = df_results['总成本'].idxmin()
min_cost_row3 = df_results.loc[min_cost_idx]
total_ben += min_cost_row3['总成本']

print("所有结果：")
print(df_results)
print("\n最小总成本花费情况：")
print(min_cost_row)
