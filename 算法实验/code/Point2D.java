/******************************************************************************
 *  编译:        javac Point2D.java
 *  执行:        java Point2D x0 y0 n
 *  依赖:        StdDraw.java StdRandom.java
 *
 *  不可变的二维点数据类型，表示平面上的一个点。
 *
 ******************************************************************************/

package edu.princeton.cs.algs4;

import java.util.Arrays;
import java.util.Comparator;

/**
 *  {@code Point2D} 类是一个不可变的数据类型，用于表示一个二维平面上的点。
 *  注意：为了处理 double 类型的 -0.0 和 +0.0 的差异，Point2D 的构造函数会将所有的 -0.0 坐标转换为 +0.0。
 *  详情参考 《算法（第 4 版）》中的第 1.2 章节。
 *  作者：Robert Sedgewick 和 Kevin Wayne
 */
public final class Point2D implements Comparable<Point2D> {

    /**
     * 按照 x 坐标比较两个点的比较器。
     */
    public static final Comparator<Point2D> X_ORDER = new XOrder();

    /**
     * 按照 y 坐标比较两个点的比较器。
     */
    public static final Comparator<Point2D> Y_ORDER = new YOrder();

    /**
     * 按照极径比较两个点的比较器。
     */
    public static final Comparator<Point2D> R_ORDER = new ROrder();

    private final double x;    // x 坐标
    private final double y;    // y 坐标

    /**
     * 初始化一个新的点 (x, y)。
     * @param x x 坐标
     * @param y y 坐标
     * @throws IllegalArgumentException 如果 x 或 y 是 Double.NaN、Double.POSITIVE_INFINITY 或 Double.NEGATIVE_INFINITY
     */
    public Point2D(double x, double y) {
        if (Double.isInfinite(x) || Double.isInfinite(y))
            throw new IllegalArgumentException("坐标必须是有限的");
        if (Double.isNaN(x) || Double.isNaN(y))
            throw new IllegalArgumentException("坐标不能是 NaN");

        // 处理 -0.0 和 +0.0 的区别，避免 -0.0 造成的浮动误差
        if (x == 0.0) this.x = 0.0;  // 将 -0.0 转换为 +0.0
        else          this.x = x;

        if (y == 0.0) this.y = 0.0;  // 将 -0.0 转换为 +0.0
        else          this.y = y;
    }

    /**
     * 返回 x 坐标。
     * @return x 坐标
     */
    public double x() {
        return x;
    }

    /**
     * 返回 y 坐标。
     * @return y 坐标
     */
    public double y() {
        return y;
    }

    /**
     * 返回点的极径。
     * @return 该点的极径，即极坐标系中的半径，计算公式为 sqrt(x^2 + y^2)
     */
    public double r() {
        return Math.sqrt(x * x + y * y);
    }

    /**
     * 返回点的极角。
     * @return 极角（以弧度表示）在 (-π, π) 之间，表示该点的角度。
     */
    public double theta() {
        return Math.atan2(y, x);
    }

    /**
     * 返回当前点与另一个点之间的夹角。
     * @param that 另一个点
     * @return 当前点与该点之间的夹角（以弧度表示，范围为 -π 到 π）。
     */
    private double angleTo(Point2D that) {
        double dx = that.x - this.x;
        double dy = that.y - this.y;
        return Math.atan2(dy, dx);
    }

    /**
     * 判断三个点是否形成一个逆时针转弯。
     * @param a 第一个点
     * @param b 第二个点
     * @param c 第三个点
     * @return 如果 a→b→c 是逆时针转弯，返回 +1；如果是顺时针转弯，返回 -1；如果是共线，返回 0。
     */
    public static int ccw(Point2D a, Point2D b, Point2D c) {
        double area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        if (area2 < 0) return -1;  // 顺时针
        else if (area2 > 0) return +1;  // 逆时针
        else return 0;  // 共线
    }

    /**
     * 计算三角形 a-b-c 的两倍有符号面积。
     * @param a 第一个点
     * @param b 第二个点
     * @param c 第三个点
     * @return 返回 a-b-c 三角形的两倍有符号面积
     */
    public static double area2(Point2D a, Point2D b, Point2D c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    /**
     * 计算当前点与另一个点之间的欧几里得距离。
     * @param that 另一个点
     * @return 当前点与该点之间的欧几里得距离
     */
    public double distanceTo(Point2D that) {
        double dx = this.x - that.x;
        double dy = this.y - that.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    /**
     * 计算当前点与另一个点之间欧几里得距离的平方。
     * @param that 另一个点
     * @return 当前点与该点之间欧几里得距离的平方
     */
    public double distanceSquaredTo(Point2D that) {
        double dx = this.x - that.x;
        double dy = this.y - that.y;
        return dx * dx + dy * dy;
    }

    /**
     * 按 y 坐标升序比较两个点，如果 y 坐标相同，则按 x 坐标升序比较。
     * 形式上，若点 (x0, y0) 小于点 (x1, y1)，当且仅当 {@code y0 < y1} 或者 {@code y0 == y1} 且 {@code x0 < x1}。
     *
     * @param  that 另一个点
     * @return 如果当前点小于另一个点，返回负整数；如果当前点等于另一个点，返回 0；如果当前点大于另一个点，返回正整数。
     */
    public int compareTo(Point2D that) {
        if (this.y < that.y) return -1;
        if (this.y > that.y) return +1;
        if (this.x < that.x) return -1;
        if (this.x > that.x) return +1;
        return 0;
    }

    /**
     * 返回以当前点为参考的极角比较器。
     *
     * @return 极角比较器
     */
    public Comparator<Point2D> polarOrder() {
        return new PolarOrder();
    }

    /**
     * 返回以当前点为参考的 atan2() 角度比较器。
     *
     * @return atan2 角度比较器
     */
    public Comparator<Point2D> atan2Order() {
        return new Atan2Order();
    }

    /**
     * 返回以当前点为参考的距离比较器。
     *
     * @return 距离比较器
     */
    public Comparator<Point2D> distanceToOrder() {
        return new DistanceToOrder();
    }

    // 按 x 坐标升序比较点的比较器
    private static class XOrder implements Comparator<Point2D> {
        public int compare(Point2D p, Point2D q) {
            return Double.compare(p.x, q.x);
        }
    }

    // 按 y 坐标升序比较点的比较器
    private static class YOrder implements Comparator<Point2D> {
        public int compare(Point2D p, Point2D q) {
            return Double.compare(p.y, q.y);
        }
    }

    // 按极径升序比较点的比较器
    private static class ROrder implements Comparator<Point2D> {
        public int compare(Point2D p, Point2D q) {
            double delta = (p.x * p.x + p.y * p.y) - (q.x * q.x + q.y * q.y);
            return Double.compare(delta, 0);
        }
    }

    // 根据 atan2 角度与当前点比较其他点的比较器
    private class Atan2Order implements Comparator<Point2D> {
        public int compare(Point2D q1, Point2D q2) {
            double angle1 = angleTo(q1);
            double angle2 = angleTo(q2);
            return Double.compare(angle1, angle2);
        }
    }

    // 根据极角与当前点比较其他点的比较器
    private class PolarOrder implements Comparator<Point2D> {
        public int compare(Point2D q1, Point2D q2) {
            double dx1 = q1.x - x;
            double dy1 = q1.y - y;
            double dx2 = q2.x - x;
            double dy2 = q2.y - y;

            if      (dy1 >= 0 && dy2 < 0) return -1;    // q1 在上方，q2 在下方
            else if (dy2 >= 0 && dy1 < 0) return +1;    // q1 在下方，q2 在上方
            else if (dy1 == 0 && dy2 == 0) {            // 两点共线且在水平方向
                if      (dx1 >= 0 && dx2 < 0) return -1;
                else if (dx2 >= 0 && dx1 < 0) return +1;
                else                          return  0;
            }
            else return -ccw(Point2D.this, q1, q2);     // 都在上方或下方
        }
    }

    // 按距离升序比较点的比较器
    private class DistanceToOrder implements Comparator<Point2D> {
        public int compare(Point2D p, Point2D q) {
            double dist1 = distanceSquaredTo(p);
            double dist2 = distanceSquaredTo(q);
            return Double.compare(dist1, dist2);
        }
    }

    /**
     * 判断当前点是否与指定点相等。
     *
     * @param  other 另一个点
     * @return 如果两个点相等，返回 {@code true}；否则返回 {@code false}
     */
    @Override
    public boolean equals(Object other) {
        if (other == this) return true;
        if (other == null) return false;
        if (other.getClass() != this.getClass()) return false;
        Point2D that = (Point2D) other;
        return this.x == that.x && this.y == that.y;
    }

    /**
     * 返回当前点的字符串表示。
     * @return 字符串形式表示当前点，例如 "(x, y)"
     */
    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }

    /**
     * 返回当前点的哈希值。
     * @return 当前点的哈希值
     */
    @Override
    public int hashCode() {
        int hashX = ((Double) x).hashCode();
        int hashY = ((Double) y).hashCode();
        return 31 * hashX + hashY;
    }

    /**
     * 使用标准绘图库绘制该点。
     */
    public void draw() {
        StdDraw.point(x, y);
    }

    /**
     * 绘制从当前点到另一个点的线段。
     * @param that 另一个点
     */
    public void drawTo(Point2D that) {
        StdDraw.line(this.x, this.y, that.x, that.y);
    }


    /**
     * 单元测试 Point2D 类。
     *
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        int x0 = Integer.parseInt(args[0]);
        int y0 = Integer.parseInt(args[1]);
        int n = Integer.parseInt(args[2]);

        // 初始化绘图界面
        StdDraw.setCanvasSize(800, 800);
        StdDraw.setXscale(0, 100);
        StdDraw.setYscale(0, 100);
        StdDraw.setPenRadius(0.005);
        StdDraw.enableDoubleBuffering();

        // 创建并绘制随机点
        Point2D[] points = new Point2D[n];
        for (int i = 0; i < n; i++) {
            int x = StdRandom.uniformInt(100);
            int y = StdRandom.uniformInt(100);
            points[i] = new Point2D(x, y);
            points[i].draw();
        }

        // 绘制固定点 x0, y0
        Point2D p = new Point2D(x0, y0);
        StdDraw.setPenColor(StdDraw.RED);
        StdDraw.setPenRadius(0.02);
        p.draw();

        // 按极角顺序绘制从点 p 到其他点的连线
        StdDraw.setPenRadius();
        StdDraw.setPenColor(StdDraw.BLUE);
        Arrays.sort(points, p.polarOrder());
        for (int i = 0; i < n; i++) {
            p.drawTo(points[i]);
            StdDraw.show();
            StdDraw.pause(100);
        }
    }
}
