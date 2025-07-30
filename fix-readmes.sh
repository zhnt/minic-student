#!/bin/bash

# 批量修复所有阶段的README.md文件
# 统一获取方式为Git标签系统

echo "🔄 开始修复所有阶段的README文件..."

for stage in {0..12}; do
    dir="stage-$stage"
    readme="$dir/README.md"
    
    if [ -f "$readme" ]; then
        echo "修复阶段$stage..."
        
        # 更新获取方式
        sed -i '' "s|git clone https://github.com/zhnt/minic-s$stage.git|git clone https://github.com/zhnt/minic-student.git\ncd minic-student\ngit checkout stage-$stage|g" "$readme"
        
        # 更新下一阶段解锁方式
        next_stage=$((stage + 1))
        sed -i '' "s|# 下一阶段地址.*|git checkout stage-$next_stage|g" "$readme"
        
        # 更新获取阶段的描述
        sed -i '' "s|### 获取阶段$stage代码|### 获取阶段$stage代码|g" "$readme"
        sed -i '' "s|### 获取当前阶段|### 获取当前阶段|g" "$readme"
        
        # 添加获取完整系统的提示
        sed -i '' "s|# 仅克隆当前阶段代码|# 获取完整学习系统（推荐）|g" "$readme"
    fi
done

echo "✅ 所有阶段README修复完成！"