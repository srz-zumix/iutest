#
# help
#
help: ## show help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'


SOURCE_DOCKERCONFIG=Dockerconfig.json
# SOURCE_DOCKERCONFIG=test-Dockerconfig.json

generate_json: Dockerconfig-sample.json
	@if [ -z "${DOCKERHUB_DRONE_USER}" ]; then echo need DOCKERHUB_DRONE_USER; exit 1; fi
	@if [ -z "${DOCKERHUB_DRONE_TOKEN}" ]; then echo need DOCKERHUB_DRONE_TOKEN; exit 1; fi
	echo '${DOCKERHUB_DRONE_USER}:${DOCKERHUB_DRONE_TOKEN}' \
		| xargs -I {} sed -e "s/REPLACE_USER_AND_TOKEN/{}/g" Dockerconfig-sample.json > Dockerconfig.json
	# echo '${DOCKERHUB_DRONE_USER}:${DOCKERHUB_DRONE_TOKEN}' | base64 \
	# 	| xargs -I {} sed -e "s/REPLACE_USER_AND_TOKEN/{}/g" Dockerconfig-sample.json > Dockerconfig.json

Dockerconfig.json: generate_json

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
