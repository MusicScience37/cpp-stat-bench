FROM musicscience37/sphinx-doxygen:clang14-v5.0

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    openssh-client gnupg2 \
    vim nano && \
    apt-get autoremove && \
    apt-get autoclean && \
    ln -s "$(command -v clangd-14)" /usr/local/bin/clangd

WORKDIR /root
RUN git clone https://github.com/include-what-you-use/include-what-you-use.git -b clang_14 && \
    cd include-what-you-use && \
    mkdir build && \
    cd build && \
    cmake -G Ninja -DCMAKE_PREFIX_PATH=/usr/lib/llvm-14 .. && \
    cmake --build . && \
    cmake --build . --target install
