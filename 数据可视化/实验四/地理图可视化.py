import pandas as pd
from pyecharts import options as opts
from pyecharts.charts import Map, Timeline

# 读取 Excel 文件的数据
df = pd.read_excel("CityData.xlsx")

# 初始化数据列表
data_list = []
date_list = []

# 遍历数据并进行处理
for entry in df.groupby(["updateTime", "provinceName"]):
    # 提取每一行的数值
    values = entry[1].values
    # 将省份名、日期和累计确诊人数加入数据列表
    data_list.append([values[0][1], str(values[0][7]).split(" ")[0], entry[1].city_confirmedCount.sum()])
    # 记录唯一日期值
    if str(values[0][7]).split(" ")[0] not in date_list:
        date_list.append(str(values[0][7]).split(" ")[0])

# 初始化累计确诊人数数据
province_totals = []
for entry in data_list:
    # 遍历省份并设置初始确诊数
    if entry[0] not in [item[0] for item in province_totals]:
        province_totals.append([entry[0], 0])

# 创建时间线对象
timeline = Timeline(init_opts=opts.InitOpts(width="1400px", height="700px"))
timeline.add_schema(play_interval=500)

# 配置颜色区间
color_pieces = [
    {'max': 1, 'label': '0', 'color': 'white'},
    {'min': 1, 'max': 20, 'label': '1-20', 'color': '#FFFAFA'},
    {'min': 20, 'max': 50, 'label': '20-50', 'color': '#FAF0E6'},
    {'min': 50, 'max': 100, 'label': '50-100', 'color': '#FFEFD5'},
    {'min': 100, 'max': 200, 'label': '100-200', 'color': '#FFDAB9'},
    {'min': 200, 'max': 500, 'label': '200-500', 'color': '#FFB6C1'},
    {'min': 500, 'max': 1000, 'label': '500-1000', 'color': '#FF69B4'},
    {'min': 1000, 'max': 5000, 'label': '1000-5000', 'color': '#FF4500'},
    {'min': 5000, 'max': 10000, 'label': '5000-10000', 'color': '#DC143C'},
    {'min': 10000, 'max': 50000, 'label': '10000-50000', 'color': '#B22222'},
    {'min': 50000, 'max': 100000, 'label': '50000-100000', 'color': '#800000'}
]

# 生成并添加每个日期的地图数据到时间线
for date in date_list:
    # 创建当日的省份累计数据
    province_data = province_totals.copy()
    for item in data_list:
        for line in province_data:
            # 匹配省份和日期，将累计确诊数更新至相应位置
            if item[1] == date and line[0] == item[0]:
                line[1] = int(item[2])

    # 创建地图并配置
    map_chart = (
        Map()
        .add(series_name=date, data_pair=province_data, maptype="china", is_map_symbol_show=False)
        .set_global_opts(
            visualmap_opts=opts.VisualMapOpts(is_piecewise=True, pieces=color_pieces, pos_top="25%", pos_left="3%")
        )
    )
    # 将地图添加到时间线上
    timeline.add(map_chart, date)

# 渲染生成 HTML 文件
timeline.render("地理图可视化.html")
