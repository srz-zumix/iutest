FROM ubuntu:xenial

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

# ENV DEBCONF_NOWARNINGS yes

SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN apt-get update -q -y && \
    apt-get install -y --no-install-recommends software-properties-common && \
    apt-get update -q -y && \
    apt-get install -y --no-install-recommends \
        apt-transport-https ca-certificates \
        git build-essential curl && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# install nodejs
RUN curl -sL https://deb.nodesource.com/setup_11.x | bash - && \
    apt-get update -q -y && \
    apt-get install -y --no-install-recommends nodejs && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# install yarn
RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add - && \
    echo "deb https://dl.yarnpkg.com/debian/ stable main" | tee /etc/apt/sources.list.d/yarn.list && \
    apt-get update -q -y && \
    apt-get install -y --no-install-recommends yarn && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# RUN yarn global add codecrumbs
RUN mkdir /codecrumbs && \
    git clone https://github.com/Bogdan-Lyashenko/codecrumbs.git /codecrumbs
COPY webpack.prod.js /codecrumbs/src/public
WORKDIR /codecrumbs
RUN find ./src/server -type f -name '*.js' -print0 | xargs -0 grep -l '127.0.0.1' | xargs sed -i.bak -e 's/127\.0\.0\.1/0.0.0.0/g' && \
    yarn && yarn build && \
    yarn global add /codecrumbs

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
