FROM mcr.microsoft.com/vscode/devcontainers/base:jammy

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install git \
    curl build-essential make cmake libc6-dev \
    gcc g++ gfortran intel-mkl-full \
    python3 python3-pip python3-pytest \
    python3-numpy python3-scipy python3-pandas python3-matplotlib \
    jupyter

RUN cd /usr/bin ; ln -sf py.test-3 py.test
