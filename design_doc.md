# 设计文档

## 需求：

### 计算最长英语单词链

- 计算最多单词数量(-w选项)
- 计算字母最多(-c选项)
- 指定首字母(-h选项)
- 指定尾字母(-t选项)
- 允许隐藏环(-r选项)（性能）

### GUI

- 两种导入文本的方式
- 交互式按钮，分别是五个功能选项
- 异常情况界面提示
- 正确结果界面显示
- 导出结果，保存到文件
- 使用说明

## 核心计算模块：

- 从输入buffer中提取单词
    ExtractWord
- 根据指定模式进行计算，得到结果
    CalculateLongestChain
  - 生成单词图数据结构
      GenerateWordMap
  - 检查图是否有环
      CheckCircle
  - 搜索符合输入命令要求的单词链
      ChainSearch
    - 基于DFS的暴力搜索(NaiveSearch)
        Search
    - 根据头字母和尾字母在结果图中查找(NaiveSearch)
        LookUp
- 将结果单词变为指定格式存到结果buffer中
    OutputTransform

## 类功能说明:
 - SearchInterface(全局搜索接口)
   - 子类必须重写实现Search和LoopUp方法
 - NaiveSearch（基于DFS的暴力搜索）
 - DistanceElement 距离map基本元素
 - WordMapElement 单词map基本元素
 - Word 单词的基本信息 
   
  

## 命令行：

- 解析命令行选项
- 从文件中读取文本到输入buffer
- 将结果buffer中的内容输出到文件中

## GUI：

- GUI上文本导入文件，将文本导入buffer中
- GUI界面输入文本，将文本导入buffer中
- 将计算过程中可能得到的异常信息返回这会至异常界面
- 将计算的正确结果从buffer返回至结果界面
- 将计算的正确结果从buffer存入到文件中
- 显示使用说明c

## 测试：
