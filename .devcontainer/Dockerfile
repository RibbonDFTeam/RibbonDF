FROM mcr.microsoft.com/devcontainers/base:noble

# 创建目录并下载、解压 clangd
RUN mkdir -p /home/vscode/softs; \
    wget -P /home/vscode/softs https://github.com/clangd/clangd/releases/download/19.1.2/clangd-linux-19.1.2.zip; \
    unzip /home/vscode/softs/clangd-linux-19.1.2.zip -d /home/vscode/softs; \
    rm /home/vscode/softs/clangd-linux-19.1.2.zip

# 设置环境变量，将 clangd 可执行文件所在目录添加到 PATH 中
ENV PATH="/home/vscode/softs/clangd_19.1.2/bin:${PATH}"


