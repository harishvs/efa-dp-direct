# SPDX-License-Identifier: Apache-2.0
# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

# The layout helpers in common.h are shared by the host setup and the device
# kernels, so they are unit-testable with no CUDA toolkit and no EFA device.
# That test is all this Makefile builds today; the kernels need nvcc and are
# added separately, so that `make test` keeps working on a machine with no GPU.

CXX ?= g++
CXXFLAGS ?= -O2 -Wall -Wextra -Wpedantic
INCLUDES = -I.

BUILDDIR = build

all: $(BUILDDIR)/common_test

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/common_test: common_test.cpp common.h | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

test: $(BUILDDIR)/common_test
	$(BUILDDIR)/common_test

clean:
	rm -rf $(BUILDDIR)

.PHONY: all test clean
