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
#ifndef _UAPI_HV_HVGDK_MINI_H
#define _UAPI_HV_HVGDK_MINI_H

/* TODO not in hv headers */
#define HV_LINUX_VENDOR_ID              0x8100
#define HV_HYP_PAGE_SHIFT		12
#define HV_HYP_PAGE_SIZE		BIT(HV_HYP_PAGE_SHIFT)
#define HV_HYP_PAGE_MASK		(~(HV_HYP_PAGE_SIZE - 1))

/*
 * Message format for notifications delivered via
 * intercept message(as_intercept=1)
 */
struct hv_notification_message_payload {
	__u32 sint_index;
} __packed;

/* Note: not in hvgdk_mini.h */
#define HV_SUPPORTS_REGISTER_DELIVERABILITY_NOTIFICATIONS

/*
 * Arch compatibility regs for use with hv_set/get_register
 */
#define HV_MSR_VP_INDEX		(HV_X64_MSR_VP_INDEX)
#define HV_MSR_TIME_REF_COUNT	(HV_X64_MSR_TIME_REF_COUNT)
#define HV_MSR_REFERENCE_TSC	(HV_X64_MSR_REFERENCE_TSC)
#define HV_MSR_STIMER0_CONFIG	(HV_X64_MSR_STIMER0_CONFIG)
#define HV_MSR_STIMER0_COUNT	(HV_X64_MSR_STIMER0_COUNT)

#define HV_MSR_SCONTROL		(HV_X64_MSR_SCONTROL)
#define HV_MSR_SIEFP		(HV_X64_MSR_SIEFP)
#define HV_MSR_SIMP		(HV_X64_MSR_SIMP)
#define HV_MSR_SIRBP		(HV_X64_MSR_SIRBP)
#define HV_MSR_EOM		(HV_X64_MSR_EOM)
#define HV_MSR_SINT0		(HV_X64_MSR_SINT0)

#define HV_MSR_NESTED_SCONTROL	(HV_X64_MSR_NESTED_SCONTROL)
#define HV_MSR_NESTED_SIEFP	(HV_X64_MSR_NESTED_SIEFP)
#define HV_MSR_NESTED_SIMP	(HV_X64_MSR_NESTED_SIMP)
#define HV_MSR_NESTED_EOM	(HV_X64_MSR_NESTED_EOM)
#define HV_MSR_NESTED_SINT0	(HV_X64_MSR_NESTED_SINT0)

#define HV_MSR_CRASH_P0		(HV_X64_MSR_CRASH_P0)
#define HV_MSR_CRASH_P1		(HV_X64_MSR_CRASH_P1)
#define HV_MSR_CRASH_P2		(HV_X64_MSR_CRASH_P2)
#define HV_MSR_CRASH_P3		(HV_X64_MSR_CRASH_P3)
#define HV_MSR_CRASH_P4		(HV_X64_MSR_CRASH_P4)
#define HV_MSR_CRASH_CTL	(HV_X64_MSR_CRASH_CTL)

#endif /* _UAPI_HV_HVGDK_MINI_H */
