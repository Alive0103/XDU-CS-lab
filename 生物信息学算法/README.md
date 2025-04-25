# 基于图模型的癌细胞-T细胞通讯分析

本项目实现了基于图模型的癌细胞-T细胞通讯分析，用于研究肺癌、结肠癌和乳腺癌中癌细胞与T细胞之间的相互作用。

## 功能特点

1. 分析三种癌症（肺癌、结肠癌、乳腺癌）的细胞通讯网络
2. 基于最小生成树构建细胞通讯网络
3. 识别关键基因（基于度中心性和介数中心性）
4. 可视化细胞通讯网络
5. 比较不同癌症类型的关键基因

## 环境要求

- Python 3.7+
- pandas
- numpy
- scipy
- networkx
- matplotlib
- seaborn
- matplotlib-venn

## 安装

1. 克隆项目到本地
2. 安装依赖包：

```bash
pip install -r requirements.txt
```

## 数据准备

请确保以下数据文件存在于正确的目录中：

1. 基因表达数据（放在 `InputData/` 目录下）：
   - `LungTumor_CancerCell_GeneExpression.csv`
   - `LungTumor_TCell_GeneExpression.csv`
   - `ColonTumor_CancerCell_GeneExpression.csv`
   - `ColonTumor_TCell_GeneExpression.csv`
   - `BreastTumor_CancerCell_GeneExpression.csv`
   - `BreastTumor_TCell_GeneExpression.csv`

2. 配体-受体相互作用数据：
   - `LigandReceptor_Human.txt`

## 使用方法

运行主程序：

```bash
python main.py
```

## 输出结果

所有结果将保存在 `results/` 目录下：

1. 网络可视化图：
   - `LungTumor_network.png`
   - `ColonTumor_network.png`
   - `BreastTumor_network.png`

2. 关键基因分析：
   - `key_genes_analysis.xlsx`：包含度中心性和介数中心性的详细结果
   - `degree_venn.png`：度中心性关键基因的维恩图
   - `betweenness_venn.png`：介数中心性关键基因的维恩图

## 代码结构

- `cancer_tcell_communication.py`：核心分析类
- `main.py`：主运行脚本
- `requirements.txt`：依赖包列表
- `README.md`：项目说明文档 
