#!/bin/bash

# 判断参数个数是否正确
if [ $# -ne 2 ]; then
    echo "Usage: $0 <filename> <mode>"
    exit 1
fi

# 获取文件名和模式
filename=$1
mode=$2

# 根据模式决定操作
if [ "$mode" == "write" ]; then
    # 写入内容到文件
    echo "894 MYFILE" > "$filename"
elif [ "$mode" == "read" ]; then
    # 从文件读取内容并显示
    cat "$filename"
else
    echo "Invalid mode. Use 'write' or 'read'."
    exit 1
fi