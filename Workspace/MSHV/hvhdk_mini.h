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
#ifndef _UAPI_HV_HVHDK_MINI_H
#define _UAPI_HV_HVHDK_MINI_H

#include "hvgdk_mini.h"

/*
 * Doorbell connection_info flags.
 */
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_MASK  0x00000007
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_ANY   0x00000000
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_BYTE  0x00000001
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_WORD  0x00000002
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_DWORD 0x00000003
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_QWORD 0x00000004
#define HV_DOORBELL_FLAG_TRIGGER_ANY_VALUE  0x80000000

/* Each generic set contains 64 elements */
#define HV_GENERIC_SET_SHIFT		(6)
#define HV_GENERIC_SET_MASK		(63)

enum hv_generic_set_format {
	HV_GENERIC_SET_SPARSE_4K,
	HV_GENERIC_SET_ALL,
};

/* NOTE: following two #defines are not defined in Hyper-V code */
/* The maximum number of sparse vCPU banks which can be encoded by 'struct hv_vpset' */
#define HV_MAX_SPARSE_VCPU_BANKS (64)
/* The number of vCPUs in one sparse bank */
#define HV_VCPUS_PER_SPARSE_BANK (64)

enum hv_scheduler_type {
	HV_SCHEDULER_TYPE_LP = 1, /* Classic scheduler w/o SMT */
	HV_SCHEDULER_TYPE_LP_SMT = 2, /* Classic scheduler w/ SMT */
	HV_SCHEDULER_TYPE_CORE_SMT = 3, /* Core scheduler */
	HV_SCHEDULER_TYPE_ROOT = 4, /* Root / integrated scheduler */
	HV_SCHEDULER_TYPE_MAX
};

struct hv_vpset {		/* HV_VP_SET */
	__u64 format;
	__u64 valid_bank_mask;
	__u64 bank_contents[];
} __packed;

enum hv_partition_property_code {
	/* Privilege properties */
	HV_PARTITION_PROPERTY_PRIVILEGE_FLAGS				= 0x00010000,
	HV_PARTITION_PROPERTY_SYNTHETIC_PROC_FEATURES			= 0x00010001,

	/* Resource properties */
	HV_PARTITION_PROPERTY_GPA_PAGE_ACCESS_TRACKING			= 0x00050005,
	HV_PARTITION_PROPERTY_ISOLATION_STATE				= 0x0005000c,
	HV_PARTITION_PROPERTY_UNIMPLEMENTED_MSR_ACTION                  = 0x00050017,

	/* Compatibility properties */
	HV_PARTITION_PROPERTY_PROCESSOR_XSAVE_FEATURES			= 0x00060002,
	HV_PARTITION_PROPERTY_MAX_XSAVE_DATA_SIZE			= 0x00060008,
	HV_PARTITION_PROPERTY_PROCESSOR_CLOCK_FREQUENCY			= 0x00060009,
};

enum hv_system_property {
	/* Add more values when needed */
	HV_SYSTEM_PROPERTY_SCHEDULER_TYPE = 15,
};

struct hv_input_get_system_property {
	__u32 property_id; /* enum hv_system_property */
	union {
		__u32 as_uint32;
		/* More fields to be filled in when needed */
	};
} __packed;

struct hv_output_get_system_property {
	union {
		__u32 scheduler_type; /* enum hv_scheduler_type */
	};
} __packed;

struct hv_proximity_domain_flags {
	__u32 proximity_preferred : 1;
	__u32 reserved : 30;
	__u32 proximity_info_valid : 1;
} __packed;

struct hv_proximity_domain_info {
	__u32 domain_id;
	struct hv_proximity_domain_flags flags;
} __packed;

struct hv_input_withdraw_memory {
	__u64 partition_id;
	struct hv_proximity_domain_info proximity_domain_info;
} __packed;

struct hv_output_withdraw_memory {
	/* Hack - compiler doesn't like empty array size
	 * in struct with no other members
	 */
	__u64 gpa_page_list[0];
} __packed;

/* HV Map GPA (Guest Physical Address) Flags */
#define HV_MAP_GPA_PERMISSIONS_NONE     0x0
#define HV_MAP_GPA_READABLE             0x1
#define HV_MAP_GPA_WRITABLE             0x2
#define HV_MAP_GPA_KERNEL_EXECUTABLE    0x4
#define HV_MAP_GPA_USER_EXECUTABLE      0x8
#define HV_MAP_GPA_EXECUTABLE           0xC
#define HV_MAP_GPA_PERMISSIONS_MASK     0xF

struct hv_input_map_gpa_pages {
	__u64 target_partition_id;
	__u64 target_gpa_base;
	__u32 map_flags;
	__u32 padding;
	__u64 source_gpa_page_list[];
} __packed;

union hv_gpa_page_access_state_flags {
	struct {
		__u64 clear_accessed : 1;
		__u64 set_access : 1;
		__u64 clear_dirty : 1;
		__u64 set_dirty : 1;
		__u64 reserved : 60;
	} __packed;
	__u64 as_uint64;
};

struct hv_input_get_gpa_pages_access_state {
	__u64  partition_id;
	union hv_gpa_page_access_state_flags flags;
	__u64 hv_gpa_page_number;
} __packed;

union hv_gpa_page_access_state {
	struct {
		__u8 accessed : 1;
		__u8 dirty : 1;
		__u8 reserved: 6;
	};
	__u8 as_uint8;
} __packed;

#endif /* _UAPI_HV_HVHDK_MINI_H */
