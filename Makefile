.DEFAULT_GOAL := help

DOCKER ?= docker
IMAGE ?= so3-dev
PROJECT_DIR := $(CURDIR)
HOST_UID := $(shell id -u)
HOST_GID := $(shell id -g)
RUN = $(DOCKER) run --rm --user "$(HOST_UID):$(HOST_GID)" \
	--mount "type=bind,source=$(PROJECT_DIR),target=/so3" --workdir /so3

.PHONY: help image shell test extract inventory split build verify objdiff-objects report ci-inputs compilers compiler-probe compiler-matrix
help:
	@printf '%s\n' \
		'make image                         Build dockerfiles/dev.dockerfile' \
		'make shell                         Open the development container' \
		'make test                          Run tool tests in the container' \
		'make split                         Split boot and all configured overlays with Splat' \
		'make build                         Compile, assemble, and verify boot and overlays' \
		'make verify                        Check the existing boot and overlay rebuilds' \
		'make report                        Build, verify, and generate the decomp.dev report' \
		'make objdiff-objects                Build original and C/C++-only comparison objects' \
		'make ci-inputs ISO_DISC1=... ISO_DISC2=...  Stage both discs for the private image' \
		'make compilers                     Fetch the pinned working compiler candidate' \
		'make compiler-probe                Compile and compare five boot functions' \
		'make compiler-matrix               Fetch and compare all 15 candidates' \
		'make extract ISO="/path/disc.iso"   Extract a verified disc (mounted read-only)' \
		'make inventory ISO="/path/disc.iso" Audit nested containers and IOPRP code' \
		'  Optional: OUTPUT=/new/path       Choose a new extraction or audit directory'

image:
	$(DOCKER) build --platform linux/amd64 -t "$(IMAGE)" -f "$(PROJECT_DIR)/dockerfiles/dev.dockerfile" "$(PROJECT_DIR)"

shell:
	$(RUN) -it "$(IMAGE)" bash

test:
	$(RUN) "$(IMAGE)" python -m unittest discover -s tools/tests -v

extract:
	@test -n "$(ISO)" || { echo 'Usage: make extract ISO="/path/disc.iso" [OUTPUT=disc/recheck]' >&2; exit 1; }
	@test -f "$(ISO)" || { echo 'ISO must name an existing file.' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO)"),target=/input/game.iso,readonly" \
		"$(IMAGE)" python tools/extract.py /input/game.iso $(if $(OUTPUT),--output "$(OUTPUT)")

inventory:
	@test -n "$(ISO)" || { echo 'Usage: make inventory ISO="/path/disc.iso" [OUTPUT=build/inventory/recheck]' >&2; exit 1; }
	@test -f "$(ISO)" || { echo 'ISO must name an existing file.' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO)"),target=/input/game.iso,readonly" \
		"$(IMAGE)" python tools/inventory.py /input/game.iso $(if $(OUTPUT),--output "$(OUTPUT)")

# Original game data and compiler downloads stay under ignored directories.
split:
	$(RUN) "$(IMAGE)" python tools/build.py split

build:
	$(RUN) "$(IMAGE)" python tools/build.py build

objdiff-objects:
	$(RUN) "$(IMAGE)" python tools/build.py objdiff-objects

report:
	$(RUN) "$(IMAGE)" python tools/build.py report

ci-inputs:
	@test -f "$(ISO_DISC1)" -a -f "$(ISO_DISC2)" || { echo 'Usage: make ci-inputs ISO_DISC1="/path/disc1.iso" ISO_DISC2="/path/disc2.iso" [OUTPUT=build/ci-inputs]' >&2; exit 1; }
	$(RUN) --mount "type=bind,source=$$(realpath -- "$(ISO_DISC1)"),target=/input/disc1.iso,readonly" \
		--mount "type=bind,source=$$(realpath -- "$(ISO_DISC2)"),target=/input/disc2.iso,readonly" \
		"$(IMAGE)" python tools/ci_inputs.py stage --disc1 /input/disc1.iso --disc2 /input/disc2.iso $(if $(OUTPUT),--output "$(OUTPUT)")

verify:
	$(RUN) "$(IMAGE)" python tools/boot.py verify
	$(RUN) "$(IMAGE)" python tools/overlays.py verify

compilers:
	$(RUN) "$(IMAGE)" python tools/compiler_probe.py setup

compiler-probe: compilers
	$(RUN) "$(IMAGE)" python tools/compiler_probe.py check

compiler-matrix:
	$(RUN) "$(IMAGE)" python tools/compiler_probe.py setup --all
	$(RUN) "$(IMAGE)" python tools/compiler_probe.py check --all
