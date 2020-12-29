#
# help
#
help: ## show help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'


EMPTY_DOCKERCONFIG=Dockerconfig-empty.json
SOURCE_DOCKERCONFIG=Dockerconfig.json
# SOURCE_DOCKERCONFIG=test-Dockerconfig.json

dockercfg/config.json: credentials.env Makefile
	mkdir dockercfg; \
	docker run -it --rm \
	--env-file=credentials.env \
	-v "${PWD}:/opt/data/" \
	-v "/var/run/docker.sock:/var/run/docker.sock" \
	codeship/dockercfg-generator /opt/data/dockercfg

Dockerconfig.json: Dockerconfig-sample.json dockercfg/config.json
	cat dockercfg/config.json | jq '.auths[].auth' \
		| xargs -I {} sed -e "s/REPLACE_USER_AND_TOKEN/{}/g" Dockerconfig-sample.json > Dockerconfig.json

#
# Add Secrets
#  Dockerconfig.json : Dockerhub login auth
#                      https://docs.drone.io/pipeline/docker/syntax/images/#pulling-private-images
#
setup: ${SOURCE_DOCKERCONFIG} ## setup drone.io configuration
	drone secret update --repository srz-zumix/iutest \
		--allow-pull-request \
		--name dockerconfig \
		--data @./${SOURCE_DOCKERCONFIG} || \
	drone secret add --repository srz-zumix/iutest \
		--allow-pull-request \
		--name dockerconfig \
		--data @./${SOURCE_DOCKERCONFIG}

empty:
	drone secret update --repository srz-zumix/iutest \
		--allow-pull-request \
		--name dockerconfig \
		--data @./${EMPTY_DOCKERCONFIG}
