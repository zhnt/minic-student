# 🎓 Minic渐进式编译器教学系统 - 完整架构文档

## 🏗️ 系统总览

### 🎯 设计目标
- **渐进解锁**：12阶段逐步释放，建立学习成就感
- **零配置体验**：学生git clone即用，无需复杂配置
- **AI辅助教学**：自动检测、个性化反馈、进度监控
- **教师可控**：完全掌握发布节奏，灵活调整内容

---

## 📂 核心仓库架构

### 1. 🎯 学生代码库（单仓库多阶段）
```
zhnt/minic-student
├── stage-0/              # 加法计算器
├── stage-1/              # 词法分析观察
├── stage-2/              # 减法实现
├── stage-3/              # 乘法实现
├── stage-4/              # 括号支持
├── stage-5/              # 变量持久化
├── stage-6/              # 比较运算
├── stage-7/              # while循环
├── stage-8/              # for循环
├── stage-9/              # 函数定义
├── stage-10/             # 数组字符串
├── stage-11/             # 标准库
├── stage-12/             # 完整编译器
├── .stage-lock           # 阶段解锁配置
├── README.md             # 阶段导航
└── scripts/
    └── get-stage.sh      # 获取当前阶段
```

### 2. 📖 老师课件库
```
zhnt/minic-curriculum
├── stages/
│   ├── stage-0/
│   │   ├── README.md
│   │   ├── tasks.md
│   │   ├── slides.md
│   │   └── videos/
│   └── ...
├── templates/         # 阶段模板生成器
├── scripts/
│   ├── publish-stage.sh    # 一键发布
│   └── generate-stage.py   # 阶段生成
└── docs/
    ├── teacher-guide.md
    └── student-guide.md
```

### 3. 📝 学生作业仓库
```
zhnt/minic-submissions
├── submissions/
│   ├── stage-0/
│   │   ├── 20230001/      # 学号目录
│   │   ├── 20230002/
│   │   └── ...
│   ├── stage-1/
│   └── ...
├── reports/
│   ├── stage-0/
│   │   ├── index.html     # Web报告
│   │   ├── summary.json   # 统计摘要
│   │   └── 20230001.json  # 个人报告
│   └── ...
├── .github/workflows/
│   ├── auto-check.yml     # 自动检测CI
│   └── notify-teacher.yml # 老师通知
└── scripts/
    ├── check-stage.sh     # 批量检查
    └── generate-report.sh # 报告生成
```

### 4. 🤖 学生Agent库
```
zhnt/minic-student-agent
├── src/
│   ├── __init__.py
│   ├── cli.py            # 学生控制台
│   ├── agent.py          # 智能学习助手
│   ├── submitter.py      # 作业提交器
│   ├── progress.py       # 进度追踪
│   └── hint.py           # 智能提示
├── config/
│   ├── default.yaml
│   └── prompts.yaml
├── requirements.txt
├── setup.py
└── README.md
```

### 5. 👨‍🏫 老师Agent库
```
zhnt/minic-teacher-agent
├── src/
│   ├── __init__.py
│   ├── cli.py            # 老师控制台
│   ├── agent.py          # 智能教学助手
│   ├── publisher.py      # 阶段发布器
│   ├── monitor.py        # 进度监控
│   ├── analyzer.py       # AI代码分析
│   └── notifier.py       # 通知管理器
├── config/
│   ├── default.yaml
│   └── rules.yaml
├── requirements.txt
├── setup.py
└── README.md
```

### 6. 🎯 系统配置库
```
zhnt/minic-config
├── config/
│   ├── stages.json       # 12阶段配置
│   ├── rules.json        # 检测规则
│   └── templates.json    # 模板配置
├── scripts/
│   ├── init-system.sh    # 系统初始化
│   └── backup-data.sh    # 数据备份
└── README.md
```

---

## 🎮 完整使用流程

### 老师端：课程管理
```bash
# 安装老师Agent
pip install minic-teacher-agent

# 初始化课程
teacher-cli init --course="编译原理2024" --students=45

# 发布阶段0
teacher-cli publish --stage=0 --message="体验编译器魔力"

# 查看进度
teacher-cli progress --stage=0 --format=table

# 检查作业
teacher-cli check --stage=0 --student-id=20230001

# 生成报告
teacher-cli report --stage=1 --output=pdf
```

### 学生端：学习流程
```bash
# 安装学生Agent
pip install minic-student-agent

# 获取当前阶段
student-cli status

# 进入当前阶段
cd stage-$(student-cli get-current)

# 完成作业后提交
student-cli submit --stage=2 --message="完成减法实现"

# 查看报告
student-cli report --stage=1
```

### 作业提交自动化
```bash
# 一键提交（学生）
student-cli submit --stage=N --student-id=学号 --message="说明"

# 自动执行：
# 1. 代码质量检查
# 2. 功能测试验证
# 3. 提交到作业仓库
# 4. 触发AI检测
# 5. 生成提交回执
```

---

## 🎯 关键特性

### 渐进式体验
- ✅ **阶段锁定**：未发布的标签对学生不可见
- ✅ **即时解锁**：老师发布后自动生效
- ✅ **版本控制**：每个阶段都有完整历史

### 零配置体验
- ✅ **单仓库**：学生只需克隆一次
- ✅ **标准工具**：Git + Make即可
- ✅ **跨平台**：Linux/macOS/Windows通用

### 智能化管理
- ✅ **AI检测**：自动代码分析和评分
- ✅ **实时反馈**：提交后立即生成报告
- ✅ **个性化**：根据学生情况调整提示

### 教师可控
- ✅ **发布节奏**：完全掌控阶段解锁
- ✅ **内容调整**：可随时修改阶段内容
- ✅ **进度监控**：实时掌握全班学习情况

---

## 📊 部署计划

### 第1阶段：基础架构（第1周）
- [ ] 创建6个核心仓库
- [ ] 配置GitHub Actions
- [ ] 发布阶段0-2内容

### 第2阶段：Agent开发（第2周）
- [ ] 开发学生Agent CLI
- [ ] 开发老师Agent CLI
- [ ] 集成AI检测引擎

### 第3阶段：测试优化（第3周）
- [ ] 内测班级试点
- [ ] 收集反馈优化
- [ ] 完善使用文档

### 第4-12阶段：逐步发布（第4-12周）
- [ ] 每周发布1-2个新阶段
- [ ] 实时收集使用数据
- [ ] 持续优化体验

---

## 🎉 成功指标

### 老师效率
- **发布新阶段时间**：< 30秒
- **检查全班作业时间**：< 5分钟
- **个性化反馈覆盖率**：100%

### 学生体验
- **首次配置时间**：< 2分钟
- **阶段完成时间**：15-30分钟
- **问题解决时间**：< 5分钟

### 系统稳定性
- **可用性**：99.9%
- **响应时间**：< 1秒
- **并发支持**：1000+学生

**🎯 最终实现：零Web界面，纯CLI工具，渐进式解锁，AI辅助，教师完全可控的编译器教学系统！**