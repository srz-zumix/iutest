#!/bin/sh

BASEDIR=$(dirname $0)

if command -v wget > /dev/null ; then
  wget -qO ci-env.sh --no-check-certificate "https://raw.githubusercontent.com/srz-zumix/ci-normalize-envvars/master/ci-env.sh"
else
  curl -sOL "https://raw.githubusercontent.com/srz-zumix/ci-normalize-envvars/master/ci-env.sh"
fi
. ./ci-env.sh
rm -f ./ci-env.sh

lower() {
    if [ $# -eq 0 ]; then
        cat <&0
    elif [ $# -eq 1 ]; then
        if [ -f "$1" ] && [ -r "$1" ]; then
            cat "$1"
        else
            echo "$1"
        fi
    else
        return 1
    fi | tr "[:upper:]" "[:lower:]"
}

ostype() {
    uname | lower
}

os_detect() {
    export PLATFORM
    case "$(ostype)" in
        *'linux'*)  PLATFORM='linux'   ;;
        *'darwin'*) PLATFORM='osx'     ;;
        *'bsd'*)    PLATFORM='bsd'     ;;
        *'msys'*)   PLATFORM='windows' ;;
        *'mingw'*)  PLATFORM='windows' ;;
        *'cygwin'*) PLATFORM='windows' ;;
        *)          PLATFORM='unknown' ;;
    esac
}

os_detect
uname
echo "$PLATFORM"

DATE=$(date -u)
echo "$CI_ENV_NAME"
echo "$CI_ENV_GIT_COMMIT"
echo "$CI_ENV_PULL_REQUEST"
echo "$CXX_NAME"
echo "$CXX_VERSION"
echo "$STDFLAG"

if ${CI_ENV_PULL_REQUEST}; then
  return
fi
if [ "${CI_ENV_GIT_BRANCH}" != "master" ]; then
  if [ "${CI_ENV_GIT_BRANCH}" != "develop" ]; then
    return
  fi
fi

if [ -z "${INTEGROMAT_WEBHOOK_URL}" ]; then
  export INTEGROMAT_WEBHOOK_URL="https://hook.integromat.com/cthwc5562x2xzx2r5ytzepi5aks9gqis"
fi

curl -k \
  -H "Content-Type: application/json" \
  -X POST \
  -d "{\"time\": \"${DATE}\", \"ci\": \"${CI_ENV_NAME}\", \"commit\": \"${CI_ENV_GIT_COMMIT}\", \"os\": \"${PLATFORM}\", \"cxx\":\"${CXX_NAME}\", \"version\":\"${CXX_VERSION}\", \"std\":\"${STDFLAG}\" }" \
  ${INTEGROMAT_WEBHOOK_URL}
