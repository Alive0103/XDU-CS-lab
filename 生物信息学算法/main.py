from cancer_tcell_communication import CancerTcellCommunication
import matplotlib.pyplot as plt
from matplotlib_venn import venn3
from pathlib import Path
import pandas as pd

def analyze_cancer_type(cancer_type):
    """分析单个癌症类型的细胞通讯"""
    # 初始化分析器
    analyzer = CancerTcellCommunication(cancer_type)
    
    # 加载数据
    analyzer.load_data()
    
    # 构建通讯网络
    analyzer.build_communication_network()
    
    # 获取最小生成树
    mst = analyzer.find_minimum_spanning_tree()
    
    # 可视化网络
    analyzer.visualize_network(mst)
    
    # 分析关键基因
    degree_centrality = analyzer.analyze_key_genes(mst, 'degree')
    betweenness_centrality = analyzer.analyze_key_genes(mst, 'betweenness')
    
    return {
        'degree': degree_centrality,
        'betweenness': betweenness_centrality
    }

def compare_key_genes(results, output_dir="results"):
    """比较不同癌症类型的关键基因"""
    output_path = Path(output_dir)
    output_path.mkdir(exist_ok=True)
    
    # 保存结果到Excel文件
    excel_data = {}
    for metric in ['degree', 'betweenness']:
        print(f"\n比较{metric}中心性前50名基因：")
        
        # 创建结果DataFrame
        all_results = {}
        for cancer_type, result in results.items():
            # 提取基因名和分数，确保基因名唯一
            genes_scores = {}
            for gene_cell, score in result[metric]:
                gene = gene_cell.split('/')[0]
                if gene not in genes_scores or score > genes_scores[gene]:
                    genes_scores[gene] = score
            
            # 转换为Series
            all_results[cancer_type] = pd.Series(genes_scores)
        
        # 创建DataFrame并填充NaN
        df = pd.DataFrame(all_results).fillna(0)
        excel_data[f"{metric}_centrality"] = df
        
        # 创建维恩图
        gene_sets = {
            cancer_type: set(genes_scores.keys())
            for cancer_type, genes_scores in all_results.items()
        }
        
        plt.figure(figsize=(10, 10))
        venn3([gene_sets[ct] for ct in results.keys()], 
              set_labels=list(results.keys()))
        plt.title(f"Top 50 genes by {metric} centrality")
        plt.savefig(output_path / f"{metric}_venn.png", 
                   dpi=300, bbox_inches='tight')
        plt.close()
        
        print(f"维恩图已保存至 {output_path}/{metric}_venn.png")
    
    # 保存所有结果到Excel
    with pd.ExcelWriter(output_path / "key_genes_analysis.xlsx") as writer:
        for sheet_name, df in excel_data.items():
            df.to_excel(writer, sheet_name=sheet_name)
    print(f"详细结果已保存至 {output_path}/key_genes_analysis.xlsx")

def main():
    """主函数"""
    # 分析三种癌症类型
    cancer_types = ['LungTumor', 'ColonTumor', 'BreastTumor']
    results = {}
    
    for cancer_type in cancer_types:
        print(f"\n{'='*50}")
        print(f"开始分析 {cancer_type}")
        print(f"{'='*50}")
        results[cancer_type] = analyze_cancer_type(cancer_type)
    
    # 比较关键基因
    compare_key_genes(results)

if __name__ == "__main__":
    main()