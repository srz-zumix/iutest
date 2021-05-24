#
# help
#
help: ## show help
	@grep -E '^[a-zA-Z][a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
IMAGE_NAME=qemu-gcc10-armv7

register: ## register binfmt
	docker run --rm --privileged multiarch/qemu-user-static:register --reset

build:
	docker build -t ${IMAGE_NAME} ${ROOT_DIR}

run: gcc-arm ## docker run

gcc-arm: build
	(cd ${ROOT_DIR}/../../../ && docker run --rm -it -e DEFS=-static -v `pwd`:/work -w /work ${IMAGE_NAME} bash)

