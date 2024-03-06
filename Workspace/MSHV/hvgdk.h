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

#endif /* #ifndef _UAPI_HV_HVGDK_H */
