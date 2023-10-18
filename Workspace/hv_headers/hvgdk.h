/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2023, Microsoft Corporation.
 *
 * These files (hvhdk.h, hvhdk_mini.h, hvgdk.h, hvgdk_mini.h) define APIs for
 * communicating with the Microsoft Hypervisor.
 *
 * These definitions are subject to change across hypervisor versions, and as
 * such are separate and independent from hyperv-tlfs.h.
 *
 * The naming of these headers reflects conventions used in the Microsoft
 * Hypervisor.
 */
#ifndef _UAPI_HV_HVGDK_H
#define _UAPI_HV_HVGDK_H

#include "hvgdk_mini.h"

enum hv_unimplemented_msr_action {
	HV_UNIMPLEMENTED_MSR_ACTION_FAULT = 0,
	HV_UNIMPLEMENTED_MSR_ACTION_IGNORE_WRITE_READ_ZERO = 1,
	HV_UNIMPLEMENTED_MSR_ACTION_COUNT = 2,
};

/* Define connection identifier type. */
union hv_connection_id {
	__u32 asu32;
	struct {
		__u32 id:24;
		__u32 reserved:8;
	} __packed u;
};

struct hv_input_unmap_gpa_pages {
	__u64 target_partition_id;
	__u64 target_gpa_base;
	__u32 unmap_flags;
	__u32 padding;
} __packed;

#endif /* #ifndef _UAPI_HV_HVGDK_H */
