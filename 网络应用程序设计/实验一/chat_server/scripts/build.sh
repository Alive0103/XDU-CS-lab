#!/bin/bash

# 编译配置
BUILD_DIR="../bin"
SRC_DIR="../src"
TARGET="chatserver"
CXX_STANDARD="c++17"
WARNING_FLAGS="-Wall -Wextra"
OPTIMIZATION_FLAGS="-O2"

# 创建构建目录
mkdir -p "$BUILD_DIR"

# 编译命令
g++ -std=${CXX_STANDARD} ${WARNING_FLAGS} ${OPTIMIZATION_FLAGS} \
    -I"${SRC_DIR}" \
    "${SRC_DIR}/main.cpp" \
    "${SRC_DIR}/server.cpp" \
    -o "${BUILD_DIR}/${TARGET}" \
    -lpthread

# 检查编译结果
if [ $? -eq 0 ]; then
    echo "Build successful! Binary: ${BUILD_DIR}/${TARGET}"
    ls -lh "${BUILD_DIR}/${TARGET}"
else
    echo "Build failed!"
    exit 1
fi