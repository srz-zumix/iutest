# iutest exsample: docker run -it -v "/$(pwd)":/target iuiwyu /work/projects/cmake -Dbuild_tests=OFF

FROM srzzumix/iwyu:latest

LABEL "com.github.actions.name"="Include What You Use"
LABEL "com.github.actions.description"="Write arguments to the cmake options"
LABEL "com.github.actions.icon"="check"
LABEL "com.github.actions.color"="green"

LABEL "repository"="https://github.com/srz-zumix/iutest"
LABEL "homepage"="https://github.com/srz-zumix/iutest"
LABEL "maintainer"="https://github.com/srz-zumix"

RUN ln -s "/usr/bin/clang++-${CLANG_VERSION}" /usr/bin/clang++
RUN ln -s "/usr/bin/clang-${CLANG_VERSION}" /usr/bin/clang

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
