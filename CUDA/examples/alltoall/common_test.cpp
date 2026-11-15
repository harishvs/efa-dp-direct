// SPDX-License-Identifier: Apache-2.0
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#include <cstdio>
#include <cstdint>
#include "common.h"

static int pass;
static int fail;

#define CHECK(cond, msg)                           \
    do                                             \
    {                                              \
        if (cond)                                  \
        {                                          \
            pass++;                                \
        }                                          \
        else                                       \
        {                                          \
            fail++;                                \
            printf("    failed check: %s\n", msg); \
        }                                          \
    } while (0)

int main()
{
    CHECK(pack_imm(1, 2, 3) == 0x00001023,"pack imm failed");
    if (pass + fail == 0) {
        printf("FATAL: no checks ran\n");
        return 1;
    }
    printf("\n%s: %d checks passed, %d failed\n", fail ? "FAIL" : "PASS", pass, fail);
    return fail != 0;
}
