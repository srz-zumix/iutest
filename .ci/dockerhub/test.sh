if [ -z "${DOCKERHUB_USER_NAME}" ]; then echo need DOCKERHUB_USER_NAME; exit 1; fi
if [ -z "${DOCKERHUB_USER_PASS}" ]; then echo need DOCKERHUB_USER_PASS; exit 1; fi
TOKEN=$(curl --user "${DOCKERHUB_USER_NAME}:${DOCKERHUB_USER_PASS}" "https://auth.docker.io/token?service=registry.docker.io&scope=repository:ratelimitpreview/test:pull"	| jq -r .token)
curl --head -H "Authorization: Bearer ${TOKEN}" -H "Docker-Distribution-Api-Version: registry/2.0" https://registry-1.docker.io/v2/ratelimitpreview/test/manifests/latest
