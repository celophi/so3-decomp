.DEFAULT_GOAL := help

DOCKER ?= docker
IMAGE ?= so3-dev
PROJECT_DIR := $(CURDIR)
HOST_UID := $(shell id -u)
HOST_GID := $(shell id -g)
RUN = $(DOCKER) run --rm --user "$(HOST_UID):$(HOST_GID)" \
	--mount "type=bind,source=$(PROJECT_DIR),target=/so3" --workdir /so3

.PHONY: help image shell test extract extract-assets inventory split build verify objdiff-objects report ci-inputs compilers compiler-probe compiler-matrix analysis-tools sdk-scan sdk-symbols m2c decompile
help:
	@printf '%s\n' \
		'make image                         Build dockerfiles/dev.dockerfile' \
		'make shell                         Open the development container' \
		'make test                          Run tool tests in the container' \
		'make split                         Split main and all configured overlays with Splat' \
		'make build                         Compile, assemble, and verify main and overlays' \
		'make verify                        Check the existing main and overlay rebuilds' \
		'make report                        Build, verify, and generate the decomp.dev report' \
		'make objdiff-objects                Build original and C/C++-only comparison objects' \
		'make ci-inputs ISO_DISC1=... ISO_DISC2=...  Stage both discs for the private image' \
		'make analysis-tools                Fetch optional local SDK analysis tools' \
		'make m2c                           Fetch the pinned local m2c decompiler' \
		'make decompile MODULE=... FUNCTION=...  Save an m2c draft in working/matching' \
		'make sdk-scan                      Scan named SDK patterns after splitting' \
		'make sdk-symbols                   Recover ELF symbols with standalone CCC' \
		'make compilers                     Fetch the pinned working compiler candidate' \
		'make compiler-probe                Compile and compare five main functions' \
		'make compiler-matrix               Fetch and compare all 15 candidates' \
		'make extract ISO="/path/disc.iso"   Extract a verified disc (mounted read-only)' \
		'make extract-assets ISO="/path/disc.iso"  Extract assets and message banks to assets/<version>' \
		'  Optional: RESOURCES="75 95"      Extract selected disc resource indices' \
		'make inventory ISO="/path/disc.iso" Audit nested containers and IOPRP code' \
		'  Optional: OUTPUT=/new/path       Choose a new extraction or audit directory'

image:
	$(DOCKER) build --platform linux/amd64 -t "$(IMAGE)" -f "$(PROJECT_DIR)/dockerfiles/dev.dockerfile" "$(PROJECT_DIR)"

shell:
	$(RUN) -it "$(IMAGE)" bash

test:
	$(RUN) "$(IMAGE)" python -m unittest discover -s tools/so3 -t . -v

extract:
	@test -n "$(ISO)" || { echo 'Usage: make extract ISO="/path/disc.iso" [OUTPUT=disc/recheck]' >&2; exit 1; }
	@test -f "$(ISO)" || { echo 'ISO must name an existing file.' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO)"),target=/input/game.iso,readonly" \
		"$(IMAGE)" python -m tools.so3.disc.extract /input/game.iso $(if $(OUTPUT),--output "$(OUTPUT)")

extract-assets:
	@test -n "$(ISO)" || { echo 'Usage: make extract-assets ISO="/path/disc.iso" [OUTPUT=assets/recheck] [RESOURCES="75 95"]' >&2; exit 1; }
	@test -f "$(ISO)" || { echo 'ISO must name an existing file.' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO)"),target=/input/game.iso,readonly" \
		"$(IMAGE)" python -m tools.so3.assets.src.extract /input/game.iso $(if $(OUTPUT),--output "$(OUTPUT)") $(foreach resource,$(RESOURCES),--resource "$(resource)")

inventory:
	@test -n "$(ISO)" || { echo 'Usage: make inventory ISO="/path/disc.iso" [OUTPUT=build/inventory/recheck]' >&2; exit 1; }
	@test -f "$(ISO)" || { echo 'ISO must name an existing file.' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO)"),target=/input/game.iso,readonly" \
		"$(IMAGE)" python -m tools.so3.disc.inventory /input/game.iso $(if $(OUTPUT),--output "$(OUTPUT)")

# Original game data and compiler downloads stay under ignored directories.
split:
	$(RUN) "$(IMAGE)" python -m tools.so3.build split

build:
	$(RUN) "$(IMAGE)" python -m tools.so3.build build

objdiff-objects:
	$(RUN) "$(IMAGE)" python -m tools.so3.build objdiff-objects

report:
	$(RUN) "$(IMAGE)" python -m tools.so3.build report

ci-inputs:
	@test -f "$(ISO_DISC1)" -a -f "$(ISO_DISC2)" || { echo 'Usage: make ci-inputs ISO_DISC1="/path/disc1.iso" ISO_DISC2="/path/disc2.iso" [OUTPUT=build/ci-inputs]' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO_DISC1)"),target=/input/disc1.iso,readonly" \
		--mount "type=bind,source=$$(realpath -- "$(ISO_DISC2)"),target=/input/disc2.iso,readonly" \
		"$(IMAGE)" python -m tools.so3.disc.ci_inputs stage --disc1 /input/disc1.iso --disc2 /input/disc2.iso $(if $(OUTPUT),--output "$(OUTPUT)")

verify:
	$(RUN) "$(IMAGE)" python -m tools.so3.build.main verify
	$(RUN) "$(IMAGE)" python -m tools.so3.build.overlays verify

compilers:
	$(RUN) "$(IMAGE)" python -m tools.so3.build.compiler_probe setup

compiler-probe: compilers
	$(RUN) "$(IMAGE)" python -m tools.so3.build.compiler_probe check

compiler-matrix:
	$(RUN) "$(IMAGE)" python -m tools.so3.build.compiler_probe setup --all
	$(RUN) "$(IMAGE)" python -m tools.so3.build.compiler_probe check --all

# Optional analysis; normal builds and CI do not download these tools.
analysis-tools:
	$(RUN) "$(IMAGE)" python -m tools.so3.analysis.analysis_tools

sdk-scan: analysis-tools split
	$(RUN) "$(IMAGE)" python -m tools.so3.analysis.identify_sdk scan

sdk-symbols: analysis-tools
	$(RUN) "$(IMAGE)" python -m tools.so3.analysis.identify_sdk symbols

m2c:
	$(RUN) "$(IMAGE)" python -m tools.so3.analysis.analysis_tools --tool m2c

decompile:
	@test -n "$(MODULE)" -a -n "$(FUNCTION)" || { echo 'Usage: make decompile MODULE=1070-00 FUNCTION=func_00288650 [CONTEXT=working/context.h] [LANGUAGE=c++]' >&2; exit 1; }
	$(RUN) "$(IMAGE)" python -m tools.so3.analysis.decompile "$(MODULE)" "$(FUNCTION)" $(if $(CONTEXT),--context "$(CONTEXT)") $(if $(LANGUAGE),--language "$(LANGUAGE)")
