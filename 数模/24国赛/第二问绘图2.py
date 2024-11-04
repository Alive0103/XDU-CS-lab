import matplotlib.pyplot as plt
import numpy as np

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

# 数据定义
e_comb = ['(0,0,0,1)', '(1,1,0,1)', '(0,0,0,0)', '(1,1,0,0)']
m_values_initial = [39247, 45339, 18535, 11123, 37538, 19564]
m_values_new = [73225, 93668, 11235, 6777, 45386, 13455]
iterations_initial = [26, 17, 3, 4, 18, 1]
iterations_new = [51, 82, 4, 4, 36, 1]

# 横轴的e组合
e_comb_labels_fixed = ['(0,0,0,1)', '(0,0,0,1)', '(0,0,0,1)', '(1,1,0,1)', '(0,0,0,1)', '(0,0,0,0)']

# 图表绘制
fig, ax1 = plt.subplots(figsize=(10, 6))

# 绘制最大m值的条形图
bar_width = 0.35
index = np.arange(len(m_values_initial))
bars1 = ax1.bar(index, m_values_initial, bar_width, label='初始最大m值', color='b')
bars2 = ax1.bar(index + bar_width, m_values_new, bar_width, label='重解最大m值', color='orange')

# 设置左侧纵轴标签
ax1.set_xlabel('e组合')
ax1.set_ylabel('最大m值')
ax1.set_xticks(index + bar_width / 2)
ax1.set_xticklabels(e_comb_labels_fixed, rotation=45)

# 绘制右侧纵轴的最大迭代次数折线图
ax2 = ax1.twinx()
ax2.plot(index, iterations_initial, 'r--', marker='o', label='初始最大迭代次数')
ax2.plot(index, iterations_new, 'm--', marker='o', label='重解最大迭代次数')
ax2.set_ylabel('最大迭代次数')

# 图例设置
fig.legend(loc='upper right', bbox_to_anchor=(0.9, 0.9))

# 显示图表
plt.title("最大m值与最大迭代次数")
plt.tight_layout()
plt.show()
