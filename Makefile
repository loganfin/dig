EXEC_DIR := $(patsubst %/, %, $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

BUILD_DIR := $(EXEC_DIR)/build
CMAKE_CACHE := $(BUILD_DIR)/CMakeCache.txt

CMAKE_BUILD_FLAGS := -j=$(shell nproc)

.PHONY: all
all: build

# If the CMakeCache.txt file doesn't exist, that means we need to configure the
# build
$(CMAKE_CACHE):
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(DESIRED_BUILD_TYPE)

.PHONY: build
build: $(CMAKE_CACHE)
	cmake --build $(BUILD_DIR) $(CMAKE_BUILD_FLAGS)

.PHONY: run
run: CMAKE_BUILD_TYPE = $(shell sed -n 's/^CMAKE_BUILD_TYPE:STRING=//p' $(CMAKE_CACHE))
run: build
	@if [ "$(CMAKE_BUILD_TYPE)" = "Release" ]; then \
		$(BUILD_DIR)/dig/dig; \
	else \
		$(BUILD_DIR)/launcher/launcher; \
	fi

.PHONY: dig
dig: CMAKE_BUILD_FLAGS := $(CMAKE_BUILD_FLAGS) -t dig
dig: build

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

################################################################################
# The "release" and "debug" targets will reconfigure the build for your desired
# build type After running one of those targets' you can use the other targets
# normally.

.PHONY: release
release: DESIRED_BUILD_TYPE := Release
release: clean build

# TODO: Should debug be the default build type rather than ""?
.PHONY: debug
debug: DESIRED_BUILD_TYPE := Debug
debug: clean build
