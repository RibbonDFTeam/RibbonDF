FROM mcr.microsoft.com/devcontainers/base:noble

RUN sed -i 's@http://archive.ubuntu.com@https://mirrors.tuna.tsinghua.edu.cn@g' /etc/apt/sources.list.d/ubuntu.sources\
    && apt-get update

# 创建目录并下载、解压 clangd
RUN mkdir -p /home/vscode/softs; \
    wget -P /home/vscode/softs https://github.com/clangd/clangd/releases/download/19.1.2/clangd-linux-19.1.2.zip; \
    unzip /home/vscode/softs/clangd-linux-19.1.2.zip -d /home/vscode/softs; \
    rm /home/vscode/softs/clangd-linux-19.1.2.zip

# 设置环境变量，将 clangd 可执行文件所在目录添加到 PATH 中
ENV PATH="/home/vscode/softs/clangd_19.1.2/bin:${PATH}"

RUN apt-get install -y python3.12 python3-pip
RUN ln -s /usr/bin/python3 /usr/bin/python

RUN apt install -y python3-kconfiglib

# 清理 apt 缓存以减小镜像体积
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
