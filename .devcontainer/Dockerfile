FROM registry.gitlab.com/musicscience37projects/docker/my-cpp-env-docker:clang14

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    # For vcpkg.
    curl zip unzip tar \
    && \
    apt-get autoremove -y && \
    apt-get autoclean && \
    rm -r /var/lib/apt/lists/*
