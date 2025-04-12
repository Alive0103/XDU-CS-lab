import pandas as pd
from pyecharts import options as opts
from pyecharts.charts import Bar
import copy

# 读取 Excel 文件中的数据
df = pd.read_excel("CityData.xlsx")

# 初始化数据容器
data_entries = []
unique_dates = []

# 处理数据
for entry in df.groupby(["updateTime", "provinceName"]):
    # 获取当前行的数据
    entry_values = entry[1].values
    # 将省份名、日期和确诊人数总和加入列表
    data_entries.append([entry_values[0][1], str(entry_values[0][7]).split(" ")[0], entry[1].city_confirmedCount.sum()])
    date_val = str(entry_values[0][7]).split(" ")[0]
    # 仅记录唯一日期值
    if date_val not in unique_dates:
        unique_dates.append(date_val)

# 初始化每个省份的累计确诊人数
province_totals = []
for record in data_entries:
    # 去重保留省份名
    if record[0] not in [item[0] for item in province_totals]:
        province_totals.append([record[0], 0])

# 设置2020年4月1日的累计确诊数
total_4_1 = province_totals.copy()
for record in data_entries:
    for line in total_4_1:
        # 仅匹配2020-04-01日期
        if record[1] == "2020-04-01" and line[0] == record[0]:
            line[1] = int(record[2])

# 提取各省名称及其确诊数用于绘制图表
province_names = [line[0] for line in total_4_1]
confirmed_cases = [line[1] for line in total_4_1]

# 创建柱状图对象并配置选项
bar_chart = (
    Bar(init_opts=opts.InitOpts(width="1500px", height="650px"))
    .add_xaxis(province_names)
    .add_yaxis("2020年4月1日", confirmed_cases)
    .set_global_opts(
        title_opts=opts.TitleOpts(title="2020年4月1日各省累计确诊人数"),
        xaxis_opts=opts.AxisOpts(axislabel_opts=opts.LabelOpts(rotate=-30))
    )
)

# 渲染生成柱状图 HTML 文件
bar_chart.render("bar.html")
