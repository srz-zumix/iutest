#
#
#
# Copyright (C) 2018-2020, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE

#
# help
#
help: ## show help
	@grep -E '^[a-zA-Z][a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

fused: ## create fused src
	make -C tools/fused

editorconfig-self-lint:
	make -C tools/python editorconfig-self-lint

DAGGER_OPTS:=--log-format=plain
dagger-ctest:
	dagger do ctest $(DAGGER_OPTS)

dagger-format:
	cue fmt -s
