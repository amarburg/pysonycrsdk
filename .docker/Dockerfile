# It turns out there isn't much of a "Sony SDK" to install, it's just some
# pre-compiled libraries.
#
# So this docker image consists largely of a few apt packages and Aaron's opinionated
# development environment (fixuid)...

FROM ubuntu:24.04 AS deps
ARG TARGETPLATFORM

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        cmake \
        git \
        libpython3-dev \
        python3-venv \
        python3-pip \
        sudo \
        wget \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ENV USERNAME=ubuntu

# Install fixuid to help with permissions when bind mounting.
WORKDIR /etc/fixuid
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers && \
    if [ "$TARGETPLATFORM" = "linux/arm64" ]; then ARCH="arm64"; \
    elif [ "$TARGETPLATFORM" = "linux/amd64" ]; then ARCH="amd64"; \
    else exit 1; fi  && \
    wget -O - --progress=dot:giga "https://github.com/boxboat/fixuid/releases/download/v0.6.0/fixuid-0.6.0-linux-$ARCH.tar.gz" | tar -C /usr/local/bin -xzf - && \
    chown root:root /usr/local/bin/fixuid && \
    chmod 4755 /usr/local/bin/fixuid && \
    printf "user: %s\ngroup: %s\n" "${USERNAME}" "${USERNAME}" > /etc/fixuid/config.yml

ENTRYPOINT ["fixuid"]
CMD ["/bin/bash"]

USER ${USERNAME}
WORKDIR /home/${USERNAME}

# Create venv and activate automatically

# Python in Ubuntu is now marked as a "Externally managed environment",
# Per best practice, create a venv for local python packages
#
# These two ENVs effectively "activate" the venv for subsequent calls to
# python/pip within this Dockerfile

ENV VIRTUAL_ENV=/home/${USERNAME}/.venv/bluerov_oakd
# Venv needs to be established in an environment which already contains the ROS paths
RUN python3 -m venv --system-site-packages ${VIRTUAL_ENV}
ENV PATH="${VIRTUAL_ENV}/bin:${PATH}"
RUN python3 -m pip install nanobind

RUN  echo "source /${VIRTUAL_ENV}/bin/activate" >> /home/${USERNAME}/.bashrc

# This isnt' very satisfying, should install the .so in a system location
ENV LD_LIBRARY_PATH=/home/${USERNAME}/pysonycrsdk/Sony_Camera_Remote/linux_aarch64/crsdk/

FROM deps AS deploy
