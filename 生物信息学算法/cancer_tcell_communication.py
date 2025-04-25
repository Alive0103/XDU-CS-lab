import pandas as pd
import numpy as np
from scipy import stats
import networkx as nx
import matplotlib.pyplot as plt
import seaborn as sns
from pathlib import Path
import warnings
from tqdm import tqdm
warnings.filterwarnings('ignore')

class CancerTcellCommunication:
    def __init__(self, cancer_type):
        self.cancer_type = cancer_type
        self.cancer_data = None
        self.tcell_data = None
        self.lr_pairs = None
        self.graph = None
        
    def load_data(self):
        input_dir = Path("InputData")
        cancer_file = input_dir / f"{self.cancer_type}_CancerCell_GeneExpression.csv"
        tcell_file = input_dir / f"{self.cancer_type}_TCell_GeneExpression.csv"
        
        print(f"正在加载{self.cancer_type}数据...")
        self.cancer_data = pd.read_csv(cancer_file, index_col=0).astype(np.float32)
        self.tcell_data = pd.read_csv(tcell_file, index_col=0).astype(np.float32)
        
        self.lr_pairs = pd.read_csv("LigandReceptor_Human.txt", sep='\t', 
                                  names=['Ligand', 'Receptor'])
        print(f"数据加载完成！")
        print(f"癌细胞数据形状: {self.cancer_data.shape}")
        print(f"T细胞数据形状: {self.tcell_data.shape}")
        print(f"配体-受体对数量: {len(self.lr_pairs)}")
    
    def calculate_intracellular_edges(self, cell_data, cell_type, top_n=1000):
        print(f"正在计算{cell_type}的细胞内边...")
        
        # 预处理：过滤低变异基因
        print("预处理：过滤低变异基因...")
        gene_var = cell_data.var(axis=1)
        top_variable_genes = gene_var.nlargest(5000).index
        cell_data = cell_data.loc[top_variable_genes]
        
        edges = []
        n_genes = len(cell_data.index)
        total_pairs = (n_genes * (n_genes - 1)) // 2
        
        print(f"计算{n_genes}个基因的相关性...")
        
        # 将数据转换为numpy数组并标准化
        data_array = cell_data.values
        data_array = (data_array - data_array.mean(axis=1)[:, None]) / data_array.std(axis=1)[:, None]
        
        # 使用tqdm创建进度条
        with tqdm(total=total_pairs, desc=f"计算{cell_type}基因相关性") as pbar:
            batch_size = 100  # 减小批次大小以降低内存使用
            for i in range(0, n_genes, batch_size):
                end_i = min(i + batch_size, n_genes)
                batch_array = data_array[i:end_i]
                
                # 计算这批基因与所有其他基因的相关系数
                corr = np.dot(batch_array, data_array[i:].T) / data_array.shape[1]
                
                # 处理相关系数
                for idx1 in range(len(corr)):
                    for idx2 in range(idx1 + 1, len(corr[idx1])):
                        corr_value = abs(corr[idx1, idx2])
                        if len(edges) < top_n:
                            edges.append((
                                f"{cell_data.index[i + idx1]}/{cell_type}",
                                f"{cell_data.index[i + idx2]}/{cell_type}",
                                corr_value
                            ))
                            edges.sort(key=lambda x: x[2], reverse=True)
                        elif corr_value > edges[-1][2]:
                            edges[-1] = (
                                f"{cell_data.index[i + idx1]}/{cell_type}",
                                f"{cell_data.index[i + idx2]}/{cell_type}",
                                corr_value
                            )
                            edges.sort(key=lambda x: x[2], reverse=True)
                        pbar.update(1)
                
                # 清理内存
                del corr
        
        del data_array
        return edges[:top_n]
    
    def calculate_intercellular_edges(self):
        print("正在计算细胞间通讯边...")
        intercellular_edges = []
        
        with tqdm(total=len(self.lr_pairs), desc="计算细胞间通讯") as pbar:
            for _, row in self.lr_pairs.iterrows():
                ligand, receptor = row['Ligand'], row['Receptor']
                
                if (ligand in self.cancer_data.index and 
                    receptor in self.tcell_data.index):
                    weight = self._calculate_edge_weight(
                        self.cancer_data.loc[ligand],
                        self.tcell_data.loc[receptor]
                    )
                    intercellular_edges.append((
                        f"{ligand}/CancerCell",
                        f"{receptor}/TCell",
                        weight
                    ))
                
                if (ligand in self.tcell_data.index and 
                    receptor in self.cancer_data.index):
                    weight = self._calculate_edge_weight(
                        self.tcell_data.loc[ligand],
                        self.cancer_data.loc[receptor]
                    )
                    intercellular_edges.append((
                        f"{ligand}/TCell",
                        f"{receptor}/CancerCell",
                        weight
                    ))
                
                pbar.update(1)
        
        return intercellular_edges
    
    def _calculate_edge_weight(self, ligand_expr, receptor_expr):
        ligand_mean = ligand_expr.mean()
        receptor_mean = receptor_expr.mean()
        weight = 1 - min(max(ligand_mean * receptor_mean, 0), 1)
        return weight
    
    def build_communication_network(self):
        print(f"\n开始构建{self.cancer_type}的通讯网络...")
        
        self.graph = nx.DiGraph()
        
        cancer_edges = self.calculate_intracellular_edges(
            self.cancer_data, "CancerCell")
        tcell_edges = self.calculate_intracellular_edges(
            self.tcell_data, "TCell")
        
        print("正在添加网络边...")
        with tqdm(total=len(cancer_edges) + len(tcell_edges), 
                 desc="添加细胞内边") as pbar:
            for e in cancer_edges:
                self.graph.add_edge(e[0], e[1], weight=1-e[2])
                pbar.update(1)
            
            for e in tcell_edges:
                self.graph.add_edge(e[0], e[1], weight=1-e[2])
                pbar.update(1)
        
        intercellular_edges = self.calculate_intercellular_edges()
        with tqdm(total=len(intercellular_edges), 
                 desc="添加细胞间边") as pbar:
            for e in intercellular_edges:
                self.graph.add_edge(e[0], e[1], weight=e[2])
                pbar.update(1)
        
        print(f"网络构建完成！")
        print(f"节点数量: {self.graph.number_of_nodes()}")
        print(f"边的数量: {self.graph.number_of_edges()}")
    
    def find_minimum_spanning_tree(self):
        print("正在计算最小生成树...")
        mst = nx.minimum_spanning_tree(self.graph.to_undirected())
        print(f"最小生成树计算完成！")
        print(f"最小生成树节点数量: {mst.number_of_nodes()}")
        print(f"最小生成树边的数量: {mst.number_of_edges()}")
        return mst
    
    def analyze_key_genes(self, mst, metric='degree', top_n=50):
        print(f"\n正在分析{metric}中心性前{top_n}的基因...")
        
        if metric == 'degree':
            centrality = nx.degree_centrality(mst)
        elif metric == 'betweenness':
            centrality = nx.betweenness_centrality(mst)
        
        sorted_genes = sorted(centrality.items(), 
                            key=lambda x: x[1], 
                            reverse=True)
        return sorted_genes[:top_n]
    
    def visualize_network(self, mst, output_dir="results"):
        print(f"\n正在可视化{self.cancer_type}的通讯网络...")
        
        output_path = Path(output_dir)
        output_path.mkdir(exist_ok=True)
        
        plt.figure(figsize=(15, 15))
        print("计算网络布局...")
        pos = nx.spring_layout(mst, k=2, iterations=50)
        
        cancer_nodes = [n for n in mst.nodes() if "CancerCell" in n]
        tcell_nodes = [n for n in mst.nodes() if "TCell" in n]
        
        nx.draw_networkx_nodes(mst, pos, 
                             nodelist=cancer_nodes,
                             node_color='lightcoral',
                             node_size=100,
                             label='Cancer Cells')
        nx.draw_networkx_nodes(mst, pos, 
                             nodelist=tcell_nodes,
                             node_color='lightblue',
                             node_size=100,
                             label='T Cells')
        
        nx.draw_networkx_edges(mst, pos, alpha=0.5)
        nx.draw_networkx_labels(mst, pos, font_size=6)
        
        plt.title(f"{self.cancer_type} Cancer-T Cell Communication Network")
        plt.legend()
        plt.axis('off')
        
        print(f"保存网络图...")
        plt.savefig(output_path / f"{self.cancer_type}_network.png", 
                   dpi=300, bbox_inches='tight')
        plt.close()
        
        print(f"网络图已保存至 {output_path}/{self.cancer_type}_network.png")