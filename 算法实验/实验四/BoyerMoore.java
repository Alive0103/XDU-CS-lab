package edu.princeton.cs.algs4;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;

public class BoyerMoore {
    private final int R;     // 字符集基数
    private int[] right;     // 坏字符跳过数组
    private String pat;      // 模式串

    // 构造方法，预处理模式串
    public BoyerMoore(String pat) {
        this.R = 256;  // ASCII字符集大小
        this.pat = pat;
        right = new int[R];
        for (int c = 0; c < R; c++) right[c] = -1;
        for (int j = 0; j < pat.length(); j++) right[pat.charAt(j)] = j;
    }

    // 在文本中搜索模式串的所有完整匹配
    public int search(String txt) {
        int m = pat.length();
        int n = txt.length();
        int skip;
        int count = 0;

        for (int i = 0; i <= n - m; i += skip) {
            skip = 0;
            // 从后向前逐字符检查模式串是否与文本中的字符匹配
            for (int j = m - 1; j >= 0; j--) {
                if (pat.charAt(j) != txt.charAt(i + j)) {
                    skip = Math.max(1, j - right[txt.charAt(i + j)]);
                    break;
                }
            }

            // 只有完全匹配时，才算一次匹配
            if (skip == 0) {
                count++;  // 找到一个匹配
                i++;  // 查找下一个位置
            }
        }

        return count;
    }

    // 主函数，处理文件输入和查询
    public static void main(String[] args) {
        String textFile = "D:\\代码集合\\算法\\algs4\\src\\data\\alice2.txt";  // 你可以修改为实际的文件路径
        String queryFile = "D:\\代码集合\\算法\\algs4\\src\\data\\q.txt";  // 你可以修改为实际的文件路径

        String txt = readTxt(textFile);  // 读取文本文件
        if (txt == null) {
            System.out.println("文本文件读取失败！");
            return;
        }

        File file = new File(queryFile);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)))) {
            String line;
            while ((line = reader.readLine()) != null) {
                // 创建 BoyerMoore 对象并搜索模式串在文本中的出现次数
                BoyerMoore boyermoore = new BoyerMoore(line);
                int count = boyermoore.search(txt);

                // 输出结果，按照实验要求的格式
                if (count > 0) {
                    System.out.println(count + " " + line);  // 输出出现次数和模式串
                } else {
                    System.out.println("-- " + line);  // 未找到匹配
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // 读取文本文件的内容并返回为字符串
    public static String readTxt(String filename) {
        StringBuilder stringBuilder = new StringBuilder();
        File file = new File(filename);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)))) {
            String line;
            while ((line = reader.readLine()) != null) {
                stringBuilder.append(line).append(" ");
            }
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
        return stringBuilder.toString();
    }
}
