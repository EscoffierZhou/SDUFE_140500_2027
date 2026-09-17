# EscoffierZhou SDUFE 140500 in 2027

<p align="center">
  <a href="https://escoffierzhou.github.io/SDUFE_140500_2027/">
    <img src="https://img.shields.io/badge/📖_在线知识库门户-免下载·即点即看-8b5cf6?style=for-the-badge&logo=githubpages&logoColor=white" alt="Online Knowledge Base" />
  </a>
  <a href="https://github.com/EscoffierZhou/SDUFE_140500_2027">
    <img src="https://img.shields.io/badge/Target-2027_SDUFE_140500-3b82f6?style=for-the-badge&logo=google-scholar&logoColor=white" alt="Target" />
  </a>
</p>

> 🚀 **全景在线阅读直达：** [https://escoffierzhou.github.io/SDUFE_140500_2027/](https://escoffierzhou.github.io/SDUFE_140500_2027/)  
> **特性：** 手机/iPad/电脑跨端免下载阅读，支持多级折叠侧边栏自由切换章节、全局实时搜索、HTML / PDF / Markdown 格式无缝切换与暗色主题。

> **Target:** 2027 考研 140500 智能科学与技术 (学术型硕士) | 山东财经大学 (SDUFE)  
> **战略决策:** 聚焦“一战成硕”与最高 ROI 人生发展，锁定 2027 首届招生大盘（20 个学硕名额）与主场作战优势！  
> **初试科目配置:**  
> - **[101] 思想政治理论**（全国统考，目标 70+，主抓 50 分客观选择题）  
> - **[201] 英语(一)**（全国统考，目标 70+，真题精读长难句 + 图画大作文）  
> - **[302] 数学(二)**（全国统考，目标 120+，死磕高数算力与证明 + 线代解题体系）  
> - **[自命题] 数据科学基础**（学院自命题，拟招 20 人，难度适中，国庆后更新权威考纲）  
> - **[备用资料库] 备用/408 计算机基础**（保留作为核心算法底座与工科计算机素养拓展资料库）

![cover2](./assets/cover2.png)

![cover](./assets/cover.png)

---

### 知识库体系全景速览

```text
SDUFE 140500 智能科学与技术 考研备考总库
├── 101 思想政治/              # 马原、毛中特新思想、史纲、思修法治选择题高频考点与客观题突破
├── 201 英语一/                # 历年真题精读(2015-2024)、核心高频词汇与熟词生义、图画大作文模板
├── 204 英语二/                # 历史英语资料库归档 (保留备用，零删除)
├── 302 数学二/                # 考研数学二王牌冲分体系 (高等数学 Chap01~Chap15 + 线性代数 Chap00~Chap06)
│   ├── 高等数学/              # 高数 15 章手写真实解题笔记、精选题解、强化专题 (已全量同步HTML/PDF)
│   ├── 线性代数/              # 行列式、矩阵、向量组、方程组、特征值、二次型深度笔记
│   └── code/                 # 自动化导出排版自检与构建脚本
├── 自命题 数据科学基础/        # 140500 自命题专栏 (国庆后上线官方考纲细则与教材笔记)
│   ├── 01_核心数据结构与算法储备/ # 树/图/查找/排序等自命题必背高频算法手撕代码
│   ├── 02_Python与数据分析基础预备/ # NumPy/Pandas 与数据科学基本建模素养
│   └── 官方考纲与参考书目跟踪(国庆后待更新).md
├── 备用/                      # 【备用资料库】408 计算机基础四门核心知识图谱归档 (保留备用)
│   └── 408 计算机基础/
│       ├── 11408数据结构/         # 线性表、树与二叉树、图、查找、排序及算法模板
│       ├── 11408计算机组成及原理/  # 数据表示、运算电路、存储器层次、指令系统、CPU、总线与IO
│       ├── 11408操作系统/         # 进程与线程、内存管理、文件系统、设备IO与死锁
│       └── 11408计算机网络/       # 物理层、数据链路层、网络层、传输层、应用层协议栈
├── Leetcode/                 # 核心高频算法题型手写模板与解题复盘
├── NOTICE.md                 # 备考战略思维修正、时间节点、真实应试铁律与140500战略决策档案
├── README.md                 # 仓库主页与备考指南
├── index.html                # 全库在线阅读门户 (GitHub Pages 部署即用)
├── catalog.js                # 自动提取的全库结构化章节索引数据
└── generate_catalog.py       # 知识库目录一键自动扫描生成脚本
```

---

### 🌐 在线阅读与目录同步指引

1. **直接在线阅读**：
   - 访问 [https://escoffierzhou.github.io/SDUFE_140500_2027/](https://escoffierzhou.github.io/SDUFE_140500_2027/) 即可即点即看，无需下载任何 HTML 或 PDF。
2. **新增笔记后一键更新目录**：
   - 当你在各科目添加了新章节的 Markdown、HTML 或 PDF 后，只需在仓库根目录执行一行命令：
     ```bash
     python generate_catalog.py
     ```
   - 脚本将自动扫描全库并更新 `catalog.js`，推送代码至 GitHub 后网页端秒级生效同步。
