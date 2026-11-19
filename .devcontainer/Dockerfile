FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    git \
    libcurlpp-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    zlib1g-dev \
    zip \
    python3 \
    ca-certificates \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Install the exact Emscripten version used by the Unsung backend.
# Keep this pinned version in sync with Dockerfile.backend — a mismatch
# produces WASM artifacts that are not binary-compatible with the runtime.
RUN git clone https://github.com/emscripten-core/emsdk.git /opt/emsdk \
    && cd /opt/emsdk \
    && ./emsdk install 5.0.7 \
    && ./emsdk activate 5.0.7

# Make emsdk available in all future shell sessions
RUN echo 'EMSDK_QUIET=1 source /opt/emsdk/emsdk_env.sh' >> /etc/bash.bashrc

WORKDIR /workspace
