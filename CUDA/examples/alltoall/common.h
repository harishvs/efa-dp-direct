// SPDX-License-Identifier: Apache-2.0
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#ifndef EFA_ALLTOALL_COMMON_H
#define EFA_ALLTOALL_COMMON_H
#include <stdint.h>

/*
 * Qualifier prefix for the inline helpers below, so one definition serves both
 * compilers. nvcc defines __CUDACC__ and needs __device__ to make these callable
 * from a kernel; plain g++ builds (the unit test, the host setup) would reject
 * those keywords outright. static inline keeps each translation unit's copy
 * internal, so a header included from several places does not multiply-define.
 *
 * The host and the GPU must agree bit-for-bit on the imm_data encoding, so they
 * share one implementation rather than two that can drift.
 */
#ifdef __CUDACC__
#define EFA_EX_FN __host__ __device__ static inline
#else
#define EFA_EX_FN static inline
#endif

#endif 

