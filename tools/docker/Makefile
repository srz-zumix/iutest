#
# help
#
help: ## show help
	@grep -E '^[a-zA-Z][a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
IMAGE_NAME=iutest

build: # docker build
	docker build -t ${IMAGE_NAME} ${ROOT_DIR}

run: # docker run
	docker run --rm -it -v "$(pwd):/work" -w /work ${IMAGE_NAME} bash

