#!/bin/bash

# 遍历当前目录下的每个子文件夹
for folder in */; do
    # 检查是否存在.zip文件
    if [ -n "$(find "$folder" -maxdepth 1 -name '*.zip' -print -quit)" ]; then
        echo "解压 $folder 中的 .zip 文件..."
        # 解压当前文件夹内的.zip文件
        unzip -q "$folder"*.zip -d "$folder" && rm -f "$folder"*.zip
        echo "完成解压 $folder 中的 .zip 文件"
    fi
done