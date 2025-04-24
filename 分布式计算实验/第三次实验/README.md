# 代码在这

lab3java
https://www.alipan.com/s/d32riFafCrb
点击链接保存，或者复制本段内容，打开「阿里云盘」APP ，无需下载极速在线查看，视频原画倍速播放。

# 分布式日志采集分析和异常检测系统

## 项目概述

本项目实现了一个基于MOM（Message-Oriented Middleware）消息队列技术的分布式日志采集分析和异常检测系统。系统能够实时采集多个设备节点的日志信息，进行统计分析，并通过可视化界面实时展示分析结果。

## 系统架构

系统由以下几个主要模块组成：

1. **日志生产模块**（log-producer）
   - 模拟多个设备节点产生日志
   - 每个设备每100毫秒生成一条日志消息
   - 使用Kafka消息队列发布日志消息

2. **日志分析模块**（log-analyzer）
   - 订阅并处理所有设备的日志消息
   - 维护每个设备最近N条日志记录
   - 计算ERROR和WARN级别日志占比
   - 记录最近一次ERROR事件信息
   - 检测严重告警情况（ERROR占比超过50%）

3. **监控展示模块**（log-web）
   - 实时展示各设备的日志分析结果
   - 显示ERROR/WARN占比趋势图
   - 展示设备状态和告警信息

4. **公共模块**（common）
   - 定义共享的数据模型和配置

## 技术栈

- 消息队列：Apache Kafka
- 后端：Spring Boot
- 前端：Bootstrap + ECharts
- 构建工具：Maven

## 功能特性

### 1. 多节点日志采集

- 支持多个日志采集节点同时运行
- 每个节点具有唯一的device_id标识
- 日志格式采用JSON格式：

```json
{
    "device_id": "device_id1",
    "timestamp": "2025-03-31 12:00:00",
    "log_level": "INFO/WARN/ERROR",
    "message": "系统状态正常"
}
```

### 2. 异常检测与统计分析

- 实时计算每个设备的：
  - ERROR级别日志占比
  - WARN级别日志占比
  - 最近一次ERROR事件记录
- 支持配置告警阈值（默认ERROR占比超过50%触发严重告警）
- 定期发布分析结果（可配置间隔时间）

### 3. 实时监控展示

- 直观的Web可视化界面
- 实时更新的ERROR/WARN占比趋势图
- 设备状态实时监控表格
- 支持多设备数据同时展示
- 告警状态实时更新

## 运行说明

### 环境要求

- JDK 11或以上
- Maven 3.6或以上
- Kafka 2.13-3.5.0或以上

### 启动步骤

1. 启动Kafka服务

```bash
# 启动ZooKeeper
bin/zookeeper-server-start.sh config/zookeeper.properties

# 启动Kafka
bin/kafka-server-start.sh config/server.properties
```

2. 编译项目

```bash
mvn clean package
```

3. 启动各个模块

```bash
# 启动Web服务
java -jar log-web/target/log-web-1.0-SNAPSHOT.jar

# 启动日志分析服务
java -jar log-analyzer/target/log-analyzer-1.0-SNAPSHOT.jar

# 启动日志生产者（可启动多个，使用不同的device_id）
java -jar log-producer/target/log-producer-1.0-SNAPSHOT.jar --device.id=device001
java -jar log-producer/target/log-producer-1.0-SNAPSHOT.jar --device.id=device002
```

4. 访问监控界面

```
http://localhost:8080
```

## 配置说明

### 通用配置（application.properties）

```properties
# Kafka配置
spring.kafka.bootstrap-servers=localhost:9092

# 日志生产者配置
log.producer.interval=100

# 日志分析器配置
log.analyzer.window-size=50
log.analyzer.alert-threshold=0.5
log.analyzer.analysis-interval=1000
```

## 项目结构

```
lab3java/
├── common/                 # 公共模块
├── log-producer/          # 日志生产者模块
├── log-analyzer/          # 日志分析模块
├── log-web/              # Web展示模块
└── pom.xml               # 父POM文件
```

## 实现效果

- 支持多个设备节点同时运行
- 实时计算和展示各项统计指标
- 直观的趋势图显示
- 及时的告警提醒
- 良好的系统可扩展性

## 注意事项

1. 确保Kafka服务正常运行
2. 检查端口占用情况
3. 注意配置文件中的参数设置
4. 多设备运行时确保device_id不重复

## 可能的改进方向

1. 添加更多的统计指标
2. 优化告警机制
3. 增加历史数据存储和查询
4. 添加用户认证和权限管理
5. 优化前端展示效果 
