FROM mcr.microsoft.com/devcontainers/base:noble

RUN sed -i 's|http://[^/]*.ubuntu.com|https://mirrors.tuna.tsinghua.edu.cn|g' /etc/apt/sources.list.d/ubuntu.sources\
    && apt-get update

# 安装依赖
RUN apt-get install -y python3.12 python3-pip cmake clangd-19 python3-kconfiglib iputils-ping

# 清理 apt 缓存以减小镜像体积
RUN apt-get clean && rm -rf /var/lib/apt/lists/*


