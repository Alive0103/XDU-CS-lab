from pyecharts import options as opts
from pyecharts.charts import Bar3D
import pandas as pd
import datetime

# 初始化3个列表以存储不同维度的数据
x_years = []  # x轴 - 年份
y_month_day = []  # y轴 - 月日
z_temperature = []  # z轴 - 温度

# 设置温度数据列名
temperature_col = 'Daily minimum temperatures in Melbourne, Australia, 1981-1990'

def load_and_process_data(file_path):
    # 读取CSV文件到DataFrame
    data_frame = pd.read_csv(file_path)

    # 逐行处理数据，并跳过无效条目
    for _, row in data_frame.iterrows():
        # 确保Date列内容为字符串且非空，同时Unnamed: 2列为空
        if isinstance(row['Date'], str) and row['Date'].strip() and pd.isna(row['Unnamed: 2']):
            try:
                # 将日期字符串转换为日期对象
                date_obj = datetime.datetime.strptime(row['Date'], '%Y/%m/%d')
                x_years.append(date_obj.year)  # 提取年份信息
                # 格式化月日并添加到列表中
                y_month_day.append(f"{date_obj.month:02}-{date_obj.day:02}")
                # 存储日期和对应温度值
                z_temperature.append([date_obj, row[temperature_col]])
            except ValueError as error:
                print(f"日期格式错误: {row['Date']} - 错误详情: {error}")
        else:
            print(f"无效数据，跳过: {row['Date']}")

def generate_3D_bar_chart():
    global x_years
    global y_month_day

    # 去重并排序
    x_years = sorted(set(x_years))
    y_month_day = sorted(set(y_month_day))

    # 创建映射字典以映射年份和月日到索引
    year_to_index = {year: idx for idx, year in enumerate(x_years)}
    month_day_to_index = {md: idx for idx, md in enumerate(y_month_day)}

    # 构建3D图表数据
    chart_data = []
    for entry in z_temperature:
        x_index = year_to_index[entry[0].year]  # 获取年份索引
        y_index = month_day_to_index[f"{entry[0].month:02}-{entry[0].day:02}"]  # 获取月日索引
        z_value = entry[1]  # 获取温度值
        chart_data.append([x_index, y_index, z_value])  # 添加到数据集

    # 配置并渲染3D柱状图
    bar_chart = (
        Bar3D()
        .add(
            series_name="",
            data=chart_data,
            xaxis3d_opts=opts.Axis3DOpts(x_years, type_="category"),  # 设置x轴（年份）
            yaxis3d_opts=opts.Axis3DOpts(y_month_day, type_="category"),  # 设置y轴（月日）
            zaxis3d_opts=opts.Axis3DOpts(type_="value"),  # 设置z轴（温度）
            grid3d_opts=opts.Grid3DOpts(
                width=100, height=100, depth=100,
                is_rotate=True,
                rotate_speed=10,
                rotate_sensitivity=1,
            ),
            shading="color"  # 着色模式
        )
        .set_global_opts(
            title_opts=opts.TitleOpts(title="Daily minimum temperatures in Melbourne, Australia, 1981-1990"),
            visualmap_opts=opts.VisualMapOpts(min_=0, max_=20),  # 设置视觉映射
        )
        .render("temperature_3D_chart.html")  # 输出html文件
    )

if __name__ == '__main__':
    csv_file = "daily-minimum-temperatures-in-me.csv"
    # 加载并处理数据
    load_and_process_data(csv_file)
    # 生成3D柱状图
    generate_3D_bar_chart()
