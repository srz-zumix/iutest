FROM ubuntu:xenial

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

# ENV DEBCONF_NOWARNINGS yes

SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN apt-get update -q -y && \
    apt-get install -y --no-install-recommends software-properties-common && \
    apt-get update -q -y && \
    apt-get install -y --no-install-recommends \
        apt-transport-https ca-certificates \
        build-essential curl && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# install nodejs
RUN curl -sL https://deb.nodesource.com/setup_11.x | bash - && \
    apt-get update -q -y && \
    apt-get install -y nodejs && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# install yarn
RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add - && \
    echo "deb https://dl.yarnpkg.com/debian/ stable main" | tee /etc/apt/sources.list.d/yarn.list && \
    apt-get update -q -y && \
    apt-get install -y yarn && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN yarn global add codecrumbs
RUN apt-get update -q -y && \
    apt-get install -y tcpdump && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY tools/codecrumbs/entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
