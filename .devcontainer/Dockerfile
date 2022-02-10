FROM musicscience37/sphinx-doxygen:v3.4

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    clangd-12=1:12.0.0-3ubuntu1~20.04.4 \
    libc++-12-dev=1:12.0.0-3ubuntu1~20.04.4 \
    libc++abi-12-dev=1:12.0.0-3ubuntu1~20.04.4 \
    openssh-client=1:8.2p1-4ubuntu0.4 \
    gnupg2=2.2.19-3ubuntu2.1 \
    vim=2:8.1.2269-1ubuntu5.7 \
    nano=4.8-1ubuntu1 && \
    apt-get autoremove && \
    apt-get autoclean && \
    ln -s "$(command -v clangd-12)" /usr/local/bin/clangd
