import geopandas as gpd
import matplotlib.pyplot as plt

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

# 定义文件路径列表和对应的中文名称
file_paths = [
    './road2-12-9road/boundaryroad_with9road.geojson',
    './road2-12-9road/crosswalkroad_with9road.geojson',
    './road2-12-9road/laneroad_with9road.geojson',
    './road2-12-9road/signalroad_with9road.geojson',
    './road2-12-9road/stoplineroad_with9road.geojson'
]

file_names = [
    '边界道路',
    '人行横道路',
    '车道线',
    '信号灯道路',
    '停车线道路'
]

# 创建子图，设定布局为 1 行 5 列
fig, axes = plt.subplots(1, 5, figsize=(20, 4))  # 可以调整 figsize 来改变图形的整体大小

# 循环读取每个文件并绘制在对应的子图中
for i, (file_path, ax) in enumerate(zip(file_paths, axes)):
    # 读取 GeoJSON 文件
    geo_df = gpd.read_file(file_path)

    # 绘制地图到子图，强制设置 aspect='equal'
    geo_df.plot(ax=ax, aspect='equal')

    # 设置子图标题
    ax.set_title(f'{file_names[i]} 可视化')

# 调整布局以避免重叠
plt.tight_layout()

# 显示图形
plt.show()
