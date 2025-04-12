/******************************************************************************
 *  Compilation:  javac EdgeWeightedDigraph.java
 *  Execution:    java EdgeWeightedDigraph digraph.txt
 *  Dependencies: Bag.java DirectedEdge.java
 *  Data files:   https://algs4.cs.princeton.edu/44sp/tinyEWD.txt
 *                https://algs4.cs.princeton.edu/44sp/mediumEWD.txt
 *                https://algs4.cs.princeton.edu/44sp/largeEWD.txt
 *
 *  An edge-weighted digraph, implemented using adjacency lists.
 *
 ******************************************************************************/

package edu.princeton.cs.algs4;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import java.util.NoSuchElementException;

/**
 * {@code EdgeWeightedDigraph} 类表示一个带边权重的有向图，图中的顶点命名为 0 到 V - 1，
 * 每条有向边的类型为 {@link DirectedEdge}，并且具有一个实数值的权重。
 * 该类支持以下两个主要操作：向有向图中添加一条有向边，
 * 并遍历从给定顶点出发的所有边。
 * 该类还提供了方法来返回一个顶点的入度或出度、图中顶点的数量 V，以及图中边的数量 E。
 * 允许存在平行边和自环。
 * 该实现使用了邻接表表示法，它是一个顶点索引数组，每个数组元素是一个 {@link Bag} 对象。
 * 它使用 O(E+V) 空间，其中E是边的数量，V是顶点的数量。
 * 所有实例方法的时间复杂度为 O(1)。 （不过，遍历 {@link #adj(int)} 返回的边时，
 * 所需的时间与顶点的出度成正比。）
 * 构建一个包含 V个顶点的空的带边权重的有向图需要 O(V) 时间；
 * 构建一个包含 E条边和 V个顶点的带边权重有向图需要 O(E+V) 时间。
 *
 * @author Robert Sedgewick
 * @author Kevin Wayne
 */

public class EdgeWeightedDigraph {
    private static final String NEWLINE = System.getProperty("line.separator");

    private final int V;                // 图中的顶点数
    private int E;                      // 图中的边数
    private Bag<DirectedEdge>[] adj;    // 邻接表 adj[v] 表示顶点 v 的邻接边
    private int[] indegree;             // indegree[v] 表示顶点 v 的入度



    /**
     * 初始化一个空的加权有向图，包含 {@code V} 个顶点和 0 条边。
     *
     * @param  V 顶点数
     * @throws IllegalArgumentException 如果 {@code V < 0}
     */
    public EdgeWeightedDigraph(int V) {
        if (V < 0) throw new IllegalArgumentException("一个有向图的顶点数必须是非负数");
        this.V = V;
        this.E = 0;
        this.indegree = new int[V];
        adj = (Bag<DirectedEdge>[]) new Bag[V];  // 创建邻接表数组
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<DirectedEdge>();   // 每个顶点初始化一个空的邻接表
    }

    /**
     * 初始化一个随机的加权有向图，包含 {@code V} 个顶点和 {@code E} 条边。
     *
     * @param  V 顶点数
     * @param  E 边数
     * @throws IllegalArgumentException 如果 {@code V < 0}
     * @throws IllegalArgumentException 如果 {@code E < 0}
     */
    public EdgeWeightedDigraph(int V, int E) {
        this(V);  // 调用第一个构造函数初始化顶点和邻接表
        if (E < 0) throw new IllegalArgumentException("一个有向图的边数必须是非负数");
        for (int i = 0; i < E; i++) {
            int v = StdRandom.uniformInt(V);   // 随机选择起点 v
            int w = StdRandom.uniformInt(V);   // 随机选择终点 w
            double weight = 0.01 * StdRandom.uniformInt(100);  // 随机生成边的权重
            DirectedEdge e = new DirectedEdge(v, w, weight);  // 创建有向边 e
            addEdge(e);  // 将边添加到图中
        }
    }

    /**
     * 从指定的输入流初始化一个加权有向图。
     * 输入格式为：顶点数 {@code V}，接着是边数 {@code E}，然后是 {@code E} 条边的端点和权重，
     * 每条数据之间用空格分隔。
     *
     * @param  in 输入流
     * @throws IllegalArgumentException 如果 {@code in} 为 {@code null}
     * @throws IllegalArgumentException 如果某条边的端点不在规定的范围内
     * @throws IllegalArgumentException 如果顶点数或边数为负
     */
    public EdgeWeightedDigraph(In in) {
        if (in == null) throw new IllegalArgumentException("输入流不能为空");
        try {
            this.V = in.readInt();  // 读取顶点数
            if (V < 0) throw new IllegalArgumentException("一个有向图的顶点数必须是非负数");
            indegree = new int[V];
            adj = (Bag<DirectedEdge>[]) new Bag[V];  // 创建邻接表数组
            for (int v = 0; v < V; v++) {
                adj[v] = new Bag<DirectedEdge>();  // 每个顶点初始化一个空的邻接表
            }

            int E = in.readInt();  // 读取边数
            if (E < 0) throw new IllegalArgumentException("边数必须是非负数");
            for (int i = 0; i < E; i++) {
                int v = in.readInt();  // 读取边的起点
                int w = in.readInt();  // 读取边的终点
                validateVertex(v);  // 验证顶点 v 的有效性
                validateVertex(w);  // 验证顶点 w 的有效性
                double weight = in.readDouble();  // 读取边的权重
                addEdge(new DirectedEdge(v, w, weight));  // 创建并添加边
            }
        }
        catch (NoSuchElementException e) {
            throw new IllegalArgumentException("输入格式无效，构造 EdgeWeightedDigraph 时出现错误", e);
        }
    }

    /**
     * 初始化一个新的加权有向图，它是 {@code G} 的深拷贝。
     *
     * @param  G 需要复制的加权有向图
     */
    public EdgeWeightedDigraph(EdgeWeightedDigraph G) {
        this(G.V());  // 调用构造函数初始化顶点数
        this.E = G.E();  // 复制边数
        for (int v = 0; v < G.V(); v++)
            this.indegree[v] = G.indegree(v);  // 复制入度数组
        for (int v = 0; v < G.V(); v++) {
            // 反向遍历，以便邻接表的顺序与原图一致
            Stack<DirectedEdge> reverse = new Stack<DirectedEdge>();
            for (DirectedEdge e : G.adj[v]) {
                reverse.push(e);  // 将边逆序压入栈中
            }
            for (DirectedEdge e : reverse) {
                adj[v].add(e);  // 将边添加到邻接表
            }
        }
    }

    /**
     * 返回该加权有向图中的顶点数。
     *
     * @return 该加权有向图中的顶点数
     */
    public int V() {
        return V;  // 返回顶点数
    }

    /**
     * 返回该加权有向图中的边数。
     *
     * @return 该加权有向图中的边数
     */
    public int E() {
        return E;  // 返回边数
    }

    // 如果顶点 v 不在合法范围内（0 <= v < V），则抛出 IllegalArgumentException 异常
    private void validateVertex(int v) {
        if (v < 0 || v >= V)  // 验证顶点 v 是否在合法范围内
            throw new IllegalArgumentException("顶点 " + v + " 不在 0 到 " + (V-1) + " 之间");
    }

    /**
     * 将有向边 {@code e} 添加到该加权有向图中。
     *
     * @param  e 要添加的边
     * @throws IllegalArgumentException 如果边的端点不在合法的范围内（0 到 V-1）
     */
    public void addEdge(DirectedEdge e) {
        int v = e.from();  // 获取边的起点
        int w = e.to();    // 获取边的终点
        validateVertex(v);  // 验证起点 v 是否有效
        validateVertex(w);  // 验证终点 w 是否有效
        adj[v].add(e);      // 将边 e 添加到起点 v 的邻接表中
        indegree[w]++;      // 增加终点 w 的入度
        E++;                // 增加边数
    }

    /**
     * 返回与顶点 {@code v} 相连的所有有向边。
     *
     * @param  v 顶点
     * @return 顶点 {@code v} 相连的所有有向边，作为一个可迭代对象
     * @throws IllegalArgumentException 如果 {@code v} 不在合法范围内（0 <= v < V）
     */
    public Iterable<DirectedEdge> adj(int v) {
        validateVertex(v);  // 验证顶点 v 是否有效
        return adj[v];      // 返回顶点 v 的邻接表
    }

    /**
     * 返回与顶点 {@code v} 相连的有向边的数量，即顶点 {@code v} 的出度。
     *
     * @param  v 顶点
     * @return 顶点 {@code v} 的出度
     * @throws IllegalArgumentException 如果 {@code v} 不在合法范围内（0 <= v < V）
     */
    public int outdegree(int v) {
        validateVertex(v);  // 验证顶点 v 是否有效
        return adj[v].size();  // 返回顶点 v 的邻接表的大小，即出度
    }

    /**
     * 返回顶点 {@code v} 的入度，即与顶点 {@code v} 相连的有向边的数量。
     *
     * @param  v 顶点
     * @return 顶点 {@code v} 的入度
     * @throws IllegalArgumentException 如果 {@code v} 不在合法范围内（0 <= v < V）
     */
    public int indegree(int v) {
        validateVertex(v);  // 验证顶点 v 是否有效
        return indegree[v]; // 返回顶点 v 的入度
    }

    /**
     * 返回该加权有向图中的所有有向边。
     * 要遍历该图中的所有边，可以使用以下方式：
     * {@code for (DirectedEdge e : G.edges())}。
     *
     * @return 该加权有向图中的所有边，作为一个可迭代对象
     */
    public Iterable<DirectedEdge> edges() {
        Bag<DirectedEdge> list = new Bag<DirectedEdge>();  // 创建一个空的边袋
        for (int v = 0; v < V; v++) {  // 遍历所有顶点
            for (DirectedEdge e : adj(v)) {  // 遍历顶点 v 的邻接边
                list.add(e);  // 将边 e 添加到边袋中
            }
        }
        return list;  // 返回所有边的集合
    }

    /**
     * 返回该加权有向图的字符串表示形式。
     * 字符串格式为：第一行显示图的顶点数和边数，
     * 接下来的每一行显示每个顶点的邻接边。
     *
     * @return 该加权有向图的字符串表示
     */
    public String toString() {
        StringBuilder s = new StringBuilder();  // 创建一个 StringBuilder 来构建字符串
        s.append(V + " " + E + NEWLINE);  // 添加顶点数和边数
        for (int v = 0; v < V; v++) {  // 遍历每个顶点
            s.append(v + ": ");  // 在字符串中添加顶点 v
            for (DirectedEdge e : adj[v]) {  // 遍历顶点 v 的所有邻接边
                s.append(e + "  ");  // 将每条边添加到字符串中
            }
            s.append(NEWLINE);  // 每个顶点的邻接边后换行
        }
        return s.toString();  // 返回最终构建的字符串
    }

    /**
     * 单元测试 {@code EdgeWeightedDigraph} 数据类型。
     *
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        In in = new In(args[0]);  // 从命令行参数中读取输入文件
        EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);  // 创建图 G
        StdOut.println(G);  // 输出图 G 的字符串表示
    }

}

