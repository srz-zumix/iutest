#!/bin/sh

BASEDIR=$(dirname $0)
wget -qO ${BASEDIR}/ci-env.sh --no-check-certificate "https://raw.githubusercontent.com/srz-zumix/ci-normalize-envvars/master/ci-env.sh"
. ${BASEDIR}/ci-env.sh
rm -f ${BASEDIR}/ci-env.sh

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
echo "$CXX_NAME"
echo "$CXX_VERSION"
echo "$STDFLAG"

if [ -z "${INTEGROMAT_WEBHOOK_URL}" ]; then
  export INTEGROMAT_WEBHOOK_URL="https://hook.integromat.com/cthwc5562x2xzx2r5ytzepi5aks9gqis"
fi

curl -k \
  -H "Content-Type: application/json" \
  -X POST \
  -d "{\"time\": \"${DATE}\", \"ci\": \"${CI_ENV_NAME}\", \"commit\": \"${CI_ENV_GIT_COMMIT}\", \"os\": \"${PLATFORM}\", \"cxx\":\"${CXX_NAME}\", \"version\":\"${CXX_VERSION}\", \"std\":\"${STDFLAG}\" }" \
  ${INTEGROMAT_WEBHOOK_URL}
