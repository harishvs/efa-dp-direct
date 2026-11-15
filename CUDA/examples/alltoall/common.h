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
#define A2A_FN __host__ __device__ static inline
#else
#define A2A_FN static inline
#endif

/*
 * RDMA_WRITE_IMM delivers exactly 32 bits of immediate data per WR, and that
 * is the receiver's entire out-of-band budget: everything it learns about a
 * write besides the payload bytes themselves. Three fields share it.
 *
 *   [31:12] step      20 bits, wraps after ~1M exchanges - fine for an example
 *   [11:4]  src_rank   8 bits, 256 ranks; recoverable from the CQE's src_qp,
 *                      but carrying it explicitly makes traces readable
 *   [3:0]   kind       4 bits, only 4 message kinds today (§1); headroom free
 *
 * Host and device both include this header so the encoding cannot drift.
 */
#define A2A_IMM_KIND_SHIFT 0
#define A2A_IMM_KIND_BITS  4
#define A2A_IMM_SRC_SHIFT  4
#define A2A_IMM_SRC_BITS   8
#define A2A_IMM_STEP_SHIFT 12
#define A2A_IMM_STEP_BITS  20

/* Low-`bits` mask. Valid for 1..31; the widest field here is 20. */

#define A2A_MASK(bits) ((uint32_t)((UINT32_C(1) << (bits)) - 1))

/*
 * Each argument is masked to its field width rather than validated. Device code
 * has no error path to take, and step is specified to wrap rather than to fail.
 */
A2A_FN uint32_t pack_imm(uint32_t step, uint32_t src_rank, uint32_t kind)
{
	return ((step & A2A_MASK(A2A_IMM_STEP_BITS)) << A2A_IMM_STEP_SHIFT) |
	       ((src_rank & A2A_MASK(A2A_IMM_SRC_BITS)) << A2A_IMM_SRC_SHIFT) |
	       ((kind & A2A_MASK(A2A_IMM_KIND_BITS)) << A2A_IMM_KIND_SHIFT);
}

#endif 

