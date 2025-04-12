/******************************************************************************
 *  Compilation: javac IndexMultiwayMinPQ.java
 *  Execution:
 *
 *  An inde  multiway heap.
 *
 ******************************************************************************/

package edu.princeton.cs.algs4;

import java.util.Comparator;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * 该类实现了一个带有索引的多路最小优先队列。它支持常见的插入和删除最小值操作，
 * 以及删除和修改键值的方法。为了让客户端能够引用优先队列中的键，每个键都与一个
 * 介于 0 到 N-1 之间的整数相关联；客户端使用该整数指定要删除或修改的键。
 * 该类还支持查看最小键、测试优先队列是否为空、以及遍历所有键的方法。
 *
 * 此实现使用了多路堆和一个数组来将键与给定范围内的整数关联。
 * 由于简化记法，log-d 表示以 d 为底的对数。
 * 删除最小值、删除、修改键值和增加键值操作的时间复杂度为 O(d * log-d(n))。
 * 插入和减少键的时间复杂度为 O(log-d(n))。
 * is-empty、min-index、min-key、size、contains 和 key-of 操作的时间复杂度为 O(1)。
 * 构造函数的时间复杂度为 O(N)，其中 N 是指定的队列容量。
 *
 * 此数据结构使用的数组从索引 d 开始存储数据，这有助于提高缓存的效率。
 *
 * @author Tristan Claverie
 */
public class IndexMultiwayMinPQ<Key> implements Iterable<Integer> {
	private final int d;             // 堆的维度
	private int n;                   // 当前队列中的键数
	private int nmax;                // 队列的最大容量
	private int[] pq;                // 多路堆
	private int[] qp;                // pq 的逆数组：qp[pq[i]] = pq[qp[i]] = i
	private Key[] keys;              // keys[i] = i 对应的优先级
	private final Comparator<Key> comp; // 键值的比较器

	/**
	 * 初始化一个空的带有索引的优先队列，队列中的索引从 {@code 0} 到 {@code N-1}
	 * 最坏情况是 O(n)
	 *
	 * @param N 优先队列中键的数量，索引范围从 {@code 0} 到 {@code N-1}
	 * @param D 堆的维度
	 * @throws IllegalArgumentException 如果 {@code N < 0} 或 {@code D < 2}
	 */
	public IndexMultiwayMinPQ(int N, int D) {
		if (N < 0) throw new IllegalArgumentException("Maximum number of elements cannot be negative");
		if (D < 2) throw new IllegalArgumentException("Dimension should be 2 or over");
		this.d = D;
		nmax = N;
		pq = new int[nmax + D];       // 初始化堆数组
		qp = new int[nmax + D];       // 初始化逆数组
		keys = (Key[]) new Comparable[nmax + D]; // 初始化键值数组
		for (int i = 0; i < nmax + D; qp[i++] = -1); // 初始化逆数组
		comp = new MyComparator();   // 使用自定义的比较器
	}

	/**
	 * 使用自定义的比较器初始化一个空的带有索引的优先队列
	 * 最坏情况是 O(n)
	 *
	 * @param N 优先队列中键的数量，索引范围从 {@code 0} 到 {@code N-1}
	 * @param C 键值的比较器
	 * @param D 堆的维度
	 * @throws IllegalArgumentException 如果 {@code N < 0} 或 {@code D < 2}
	 */
	public IndexMultiwayMinPQ(int N, Comparator<Key> C, int D) {
		if (N < 0) throw new IllegalArgumentException("Maximum number of elements cannot be negative");
		if (D < 2) throw new IllegalArgumentException("Dimension should be 2 or over");
		this.d = D;
		nmax = N;
		pq = new int[nmax + D];       // 初始化堆数组
		qp = new int[nmax + D];       // 初始化逆数组
		keys = (Key[]) new Comparable[nmax + D]; // 初始化键值数组
		for (int i = 0; i < nmax + D; qp[i++] = -1); // 初始化逆数组
		comp = C; // 使用自定义的比较器
	}

	/**
	 * 判断优先队列是否为空
	 * 最坏情况是 O(1)
	 *
	 * @return 如果优先队列为空，返回 {@code true}，否则返回 {@code false}
	 */
	public boolean isEmpty() {
		return n == 0; // 如果队列的大小为 0，说明为空
	}

	/**
	 * 判断优先队列中是否包含指定的索引 {@code i}
	 * 最坏情况是 O(1)
	 *
	 * @param i 索引
	 * @throws IllegalArgumentException 如果索引无效
	 * @return 如果队列中包含索引 {@code i}，返回 {@code true}，否则返回 {@code false}
	 */
	public boolean contains(int i) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		return qp[i + d] != -1; // 如果逆数组中对应位置不是 -1，说明该索引存在
	}

	/**
	 * 获取当前队列中的元素个数
	 * 最坏情况是 O(1)
	 *
	 * @return 当前队列中元素的个数
	 */
	public int size() {
		return n; // 返回当前队列中的元素个数
	}

	/**
	 * 为指定的索引 {@code i} 关联一个键值 {@code key}
	 * 最坏情况是 O(log-d(n))
	 *
	 * @param i 索引
	 * @param key 与索引 {@code i} 关联的键值
	 * @throws IllegalArgumentException 如果索引无效
	 * @throws IllegalArgumentException 如果索引已经存在于队列中
	 */
	public void insert(int i, Key key) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		if (contains(i)) throw new IllegalArgumentException("Index already in the queue"); // 如果索引已经存在，抛出异常
		keys[i + d] = key; // 设置索引 i 对应的键值
		pq[n + d] = i; // 将索引 i 放入堆
		qp[i + d] = n; // 更新逆数组
		swim(n++); // 调用 swim 操作保持堆的顺序
	}

	/**
	 * 获取与最小键关联的索引
	 * 最坏情况是 O(1)
	 *
	 * @throws NoSuchElementException 如果优先队列为空
	 * @return 与最小键关联的索引
	 */
	public int minIndex() {
		if (isEmpty()) throw new NoSuchElementException("Priority queue is empty");
		return pq[d]; // 返回堆中最小元素的索引
	}

	/**
	 * 获取当前队列中的最小键
	 * 最坏情况是 O(1)
	 *
	 * @throws NoSuchElementException 如果优先队列为空
	 * @return 当前队列中的最小键
	 */
	public Key minKey() {
		if (isEmpty()) throw new NoSuchElementException("Priority queue is empty");
		return keys[pq[d] + d]; // 返回与最小元素关联的键值
	}

	/**
	 * 删除最小键
	 * 最坏情况是 O(d * log-d(n))
	 *
	 * @throws NoSuchElementException 如果优先队列为空
	 * @return 与最小键关联的索引
	 */
	public int delMin() {
		if (isEmpty()) throw new NoSuchElementException("Priority queue is empty");
		int min = pq[d]; // 获取当前最小值的索引
		exch(0, --n); // 将最小元素与堆的最后一个元素交换，并减少队列大小
		sink(0); // 通过下沉操作恢复堆的顺序
		qp[min + d] = -1; // 在逆数组中标记该索引已被移除
		keys[pq[n + d] + d] = null; // 将对应键值设为 null
		pq[n + d] = -1; // 删除堆中的元素
		return min; // 返回与最小键关联的索引
	}

	/**
	 * 获取与指定索引 {@code i} 关联的键值
	 * 最坏情况是 O(1)
	 *
	 * @param i 索引
	 * @throws IllegalArgumentException 如果指定的索引无效
	 * @throws NoSuchElementException 如果指定的索引不在队列中
	 * @return 与索引 {@code i} 关联的键值
	 */
	public Key keyOf(int i) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		if (!contains(i)) throw new NoSuchElementException("Specified index is not in the queue");
		return keys[i + d]; // 返回与指定索引关联的键值
	}

	/**
	 * 修改指定索引 {@code i} 关联的键值
	 * 如果给定的键值较大，最坏情况是 O(d * log-d(n))。
	 * 如果给定的键值较小，最坏情况是 O(log-d(n))。
	 *
	 * @param i 索引
	 * @param key 要设置的键值
	 * @throws IllegalArgumentException 如果指定的索引无效
	 * @throws NoSuchElementException 如果指定的索引不在队列中
	 */
	public void changeKey(int i, Key key) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		if (!contains(i)) throw new NoSuchElementException("Specified index is not in the queue");
		Key tmp = keys[i + d]; // 获取当前的键值
		keys[i + d] = key; // 更新键值
		// 如果新的键值较小，需要通过上浮操作保持堆的顺序
		if (comp.compare(key, tmp) <= 0) {
			swim(qp[i + d]);
		} else {
			// 如果新的键值较大，需要通过下沉操作恢复堆顺序
			sink(qp[i + d]);
		}
	}

	/**
	 * 将指定索引 {@code i} 关联的键值减小到给定的键值
	 * 最坏情况是 O(log-d(n))
	 *
	 * @param i 索引
	 * @param key 要设置的新键值
	 * @throws IllegalArgumentException 如果指定的索引无效
	 * @throws NoSuchElementException 如果指定的索引不在队列中
	 * @throws IllegalArgumentException 如果给定的键值大于当前的键值
	 */
	public void decreaseKey(int i, Key key) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		if (!contains(i)) throw new NoSuchElementException("Specified index is not in the queue");
		if (comp.compare(keys[i + d], key) <= 0)
			throw new IllegalArgumentException("Calling with this argument would not decrease the Key");
		keys[i + d] = key; // 更新键值
		swim(qp[i + d]); // 使用上浮操作恢复堆的顺序
	}

	/**
	 * 将指定索引 {@code i} 关联的键值增加到给定的键值
	 * 最坏情况是 O(d * log-d(n))
	 *
	 * @param i 索引
	 * @param key 要设置的新键值
	 * @throws IllegalArgumentException 如果指定的索引无效
	 * @throws NoSuchElementException 如果指定的索引不在队列中
	 * @throws IllegalArgumentException 如果给定的键值小于当前的键值
	 */
	public void increaseKey(int i, Key key) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		if (!contains(i)) throw new NoSuchElementException("Specified index is not in the queue");
		if (comp.compare(keys[i + d], key) >= 0)
			throw new IllegalArgumentException("Calling with this argument would not increase the Key");
		keys[i + d] = key; // 更新键值
		sink(qp[i + d]); // 使用下沉操作恢复堆的顺序
	}

	/**
	 * 删除与给定索引 {@code i} 关联的键
	 * 最坏情况是 O(d * log-d(n))
	 *
	 * @param i 索引
	 * @throws IllegalArgumentException 如果指定的索引无效
	 * @throws NoSuchElementException 如果指定的索引不在队列中
	 */
	public void delete(int i) {
		if (i < 0 || i >= nmax) throw new IllegalArgumentException("Index out of bounds");
		if (!contains(i)) throw new NoSuchElementException("Specified index is not in the queue");
		int idx = qp[i + d]; // 获取索引在堆中的位置
		exch(idx, --n); // 将要删除的元素与堆的最后一个元素交换，并减少队列大小
		swim(idx); // 使用上浮操作恢复堆的顺序
		sink(idx); // 使用下沉操作恢复堆的顺序
		keys[i + d] = null; // 删除与索引关联的键值
		qp[i + d] = -1; // 在逆数组中标记该索引已删除
	}

	/***************************
	 * 一般辅助函数
	 **************************/

// 比较两个键值
// 该方法使用外部传入的比较器 `comp` 比较两个键值对应的元素，
// 通过索引 `i` 和 `j` 获取堆中的元素，然后进行比较，
// 如果第一个键大于第二个键，返回 `true`。
	private boolean greater(int i, int j) {
		return comp.compare(keys[pq[i + d] + d], keys[pq[j + d] + d]) > 0;
	}

	// 交换两个键值对应的元素位置
// 该方法交换堆中位置 `x` 和 `y` 对应的元素位置，并更新逆数组 `qp` 中的映射关系。
	private void exch(int x, int y) {
		int i = x + d, j = y + d; // 加上偏移量 `d` 来正确定位索引
		int swap = pq[i]; // 保存元素 x 的位置
		pq[i] = pq[j]; // 将元素 j 移到位置 i
		pq[j] = swap; // 将元素 x 移到位置 j
		qp[pq[i] + d] = x; // 更新逆数组：pq[i] 在队列中的位置更新为 x
		qp[pq[j] + d] = y; // 更新逆数组：pq[j] 在队列中的位置更新为 y
	}

	/***************************
	 * 向上或向下移动的操作函数
	 **************************/

// 向上移动元素 i
// 如果元素 i 的父元素比它大，则交换它与父元素的位置，
// 递归调用该方法，直到堆序性质恢复。
// 父节点的索引为 (i-1)/d。
	private void swim(int i) {
		if (i > 0 && greater((i - 1) / d, i)) { // 如果当前元素比父元素大
			exch(i, (i - 1) / d); // 交换当前元素与父元素
			swim((i - 1) / d); // 递归上浮
		}
	}

	// 向下移动元素 i
// 如果元素 i 有子节点，并且它比子节点大，则交换它与最小的子节点的位置，
// 递归调用该方法，直到堆序性质恢复。
// 子节点的索引是从 d*i+1 开始的。
	private void sink(int i) {
		if (d * i + 1 >= n) return; // 如果没有子节点，直接返回
		int min = minChild(i); // 获取当前元素的最小子节点
		while (min < n && greater(i, min)) { // 如果当前元素比最小子节点大
			exch(i, min); // 交换当前元素与最小子节点
			i = min; // 更新当前索引为交换后的子节点位置
			min = minChild(i); // 继续获取新的最小子节点
		}
	}

	/***************************
	 * 删除最小子节点的操作
	 **************************/

// 获取索引 i 对应的最小子节点
// 子节点的索引从 d*i+1 到 d*i+d，返回其中最小的子节点。
	private int minChild(int i) {
		int loBound = d * i + 1, hiBound = d * i + d; // 计算子节点的索引范围
		int min = loBound; // 假设最小子节点是最左边的子节点
		for (int cur = loBound; cur <= hiBound; cur++) { // 遍历所有子节点
			if (cur < n && greater(min, cur)) min = cur; // 更新最小子节点
		}
		return min; // 返回最小子节点的索引
	}

/***************************
 * 迭代器
 **************************/

	/**
	 * 返回一个按升序排列的优先队列索引的迭代器
	 * 该迭代器不实现 remove() 方法
	 * iterator() : 最坏情况 O(n)
	 * next() : 最坏情况 O(d * log-d(n))
	 * hasNext() : 最坏情况 O(1)
	 *
	 * @return 返回按升序排列的索引的迭代器
	 */
	public Iterator<Integer> iterator() {
		return new MyIterator(); // 返回新的迭代器实例
	}

	// 该迭代器用于遍历优先队列中的索引，按升序排列
	private class MyIterator implements Iterator<Integer> {
		IndexMultiwayMinPQ<Key> clone; // 新建一个副本来进行迭代

		// 构造函数：在 O(n) 时间内构造一个新的优先队列副本
		public MyIterator() {
			clone = new IndexMultiwayMinPQ<Key>(nmax, comp, d); // 创建一个新的队列副本
			for (int i = 0; i < n; i++) {
				clone.insert(pq[i + d], keys[pq[i + d] + d]); // 将当前队列中的元素插入副本中
			}
		}

		// 判断是否还有下一个元素
		public boolean hasNext() {
			return !clone.isEmpty(); // 如果副本队列不为空，返回 true
		}

		// 返回下一个元素（即当前最小元素的索引）
		public Integer next() {
			if (!hasNext()) throw new NoSuchElementException(); // 如果没有更多元素，抛出异常
			return clone.delMin(); // 删除并返回最小元素的索引
		}

		// 不支持的操作：删除元素
		public void remove() {
			throw new UnsupportedOperationException(); // 不支持删除操作
		}
	}

	/***************************
	 * 比较器
	 **************************/

// 默认的比较器
// 用于比较两个键值，假设它们是 `Comparable` 类型的。
	private class MyComparator implements Comparator<Key> {
		@Override
		public int compare(Key key1, Key key2) {
			return ((Comparable<Key>) key1).compareTo(key2); // 比较两个键值
		}
	}

}