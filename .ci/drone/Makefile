#
# help
#
help: ## show help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

#
# Add Secrets
#  Dockerconfig.json : Dockerhub login auth
#                      https://docs.drone.io/pipeline/docker/syntax/images/#pulling-private-images
#
setup: ## setup drone.io configuration
	drone secret add --repository srz-zumix/iutest \
		--name dockerconfig \
		--data @./Dockerconfig.json
