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
#ifndef _UAPI_HV_HVHDK_H
#define _UAPI_HV_HVHDK_H

#include "hvhdk_mini.h"
#include "hvgdk.h"

struct hv_input_map_vp_state_page
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT32 type; /* enum hv_vp_state_page_type */
} __packed;

struct hv_output_map_vp_state_page
{
	HV_UINT64 map_location; /* GPA page number */
} __packed;

struct hv_input_unmap_vp_state_page
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT32 type; /* enum hv_vp_state_page_type */
} __packed;

struct hv_cpuid_leaf_info
{
	HV_UINT32 eax;
	HV_UINT32 ecx;
	HV_UINT64 xfem;
	HV_UINT64 xss;
} __packed;

union hv_get_vp_cpuid_values_flags
{
	HV_UINT32 AsUINT32;
	struct
    {
		HV_UINT32 use_vp_xfem_xss: 1;
		HV_UINT32 apply_registered_values: 1;
		HV_UINT32 reserved: 30;
	} __packed;
} __packed;

struct hv_input_get_vp_cpuid_values
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	union hv_get_vp_cpuid_values_flags flags;
	HV_UINT32 reserved;
	HV_UINT32 padding;
	struct hv_cpuid_leaf_info cpuid_leaf_info[];
} __packed;

// NOTE: Not in hvhdk headers
union hv_output_get_vp_cpuid_values
{
	HV_UINT32 AsUINT32[4];
	struct
    {
		HV_UINT32 eax;
		HV_UINT32 ebx;
		HV_UINT32 ecx;
		HV_UINT32 edx;
	} __packed;
};

struct hv_opaque_intercept_message
{
	HV_UINT32 vp_index;
} __packed;

#define HV_SYNIC_EVENT_RING_MESSAGE_COUNT 63

struct hv_synic_event_ring
{
	HV_UINT8  signal_masked;
	HV_UINT8  ring_full;
	HV_UINT16 reserved_z;
	HV_UINT32 data[HV_SYNIC_EVENT_RING_MESSAGE_COUNT];
} __packed;

struct hv_synic_event_ring_page
{
	struct hv_synic_event_ring sint_event_ring[HV_SYNIC_SINT_COUNT];
};

union hv_synic_sirbp
{
	HV_UINT64 AsUINT64;
	struct
    {
		HV_UINT64 sirbp_enabled:1;
		HV_UINT64 preserved:11;
		HV_UINT64 base_sirbp_gpa:52;
	} __packed;
};

struct hv_local_interrupt_controller_state
{
	/* HV_X64_INTERRUPT_CONTROLLER_STATE */
	HV_UINT32 apic_id;
	HV_UINT32 apic_version;
	HV_UINT32 apic_ldr;
	HV_UINT32 apic_dfr;
	HV_UINT32 apic_spurious;
	HV_UINT32 apic_isr[8];
	HV_UINT32 apic_tmr[8];
	HV_UINT32 apic_irr[8];
	HV_UINT32 apic_esr;
	HV_UINT32 apic_icr_high;
	HV_UINT32 apic_icr_low;
	HV_UINT32 apic_lvt_timer;
	HV_UINT32 apic_lvt_thermal;
	HV_UINT32 apic_lvt_perfmon;
	HV_UINT32 apic_lvt_lint0;
	HV_UINT32 apic_lvt_lint1;
	HV_UINT32 apic_lvt_error;
	HV_UINT32 apic_lvt_cmci;
	HV_UINT32 apic_error_status;
	HV_UINT32 apic_initial_count;
	HV_UINT32 apic_counter_value;
	HV_UINT32 apic_divide_configuration;
	HV_UINT32 apic_remote_read;
} __packed;

struct hv_stimer_state
{
	struct
    {
		/*
		 * Indicates if there is an undelivered timer expiry message.
		 */
		HV_UINT32 undelivered_msg_pending:1;
		HV_UINT32 reserved:31;
	} __packed flags;

	HV_UINT32 resvd;

	/* Timer configuration and count. */
	HV_UINT64 config;
	HV_UINT64 count;

	/* Timer adjustment. */
	HV_UINT64 adjustment;

	/* Expiration time of the undelivered message. */
	HV_UINT64 undelivered_exp_time;
} __packed;

struct hv_synthetic_timers_state
{
	struct hv_stimer_state timers[HV_SYNIC_STIMER_COUNT];

	/* Reserved space for time unhalted timer. */
	HV_UINT64 reserved[5];
} __packed;

#define HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS 6

struct hv_x64_hypercall_intercept_message
{
	struct hv_x64_intercept_message_header header;
	HV_UINT64 rax;
	HV_UINT64 rbx;
	HV_UINT64 rcx;
	HV_UINT64 rdx;
	HV_UINT64 r8;
	HV_UINT64 rsi;
	HV_UINT64 rdi;
	HV_UINT128 xmmregisters[HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS];
	struct
    {
		HV_UINT32 isolated:1;
		HV_UINT32 reserved:31;
	} __packed;
} __packed;

union hv_x64_register_access_info
{
	union hv_register_value source_value;
	HV_UINT32 destination_register;
	HV_UINT64 source_address;
	HV_UINT64 destination_address;
};

struct hv_x64_register_intercept_message
{
	struct hv_x64_intercept_message_header header;
	struct
    {
		HV_UINT8 is_memory_op:1;
		HV_UINT8 reserved:7;
	} __packed;
	HV_UINT8 reserved8;
	HV_UINT16 reserved16;
	HV_UINT32 register_name;
	union hv_x64_register_access_info access_info;
} __packed;

struct hv_x64_halt_message
{
	struct hv_x64_intercept_message_header header;
} __packed;

#define HV_X64_PENDING_INTERRUPT	0
#define HV_X64_PENDING_NMI		2
#define HV_X64_PENDING_EXCEPTION	3

struct hv_x64_interruption_deliverable_message
{
	struct hv_x64_intercept_message_header header;
	HV_UINT32 deliverable_type; /* pending interruption type */
	HV_UINT32 rsvd;
} __packed;

struct hv_x64_sint_deliverable_message
{
	struct hv_x64_intercept_message_header header;
	HV_UINT16 deliverable_sints;
	HV_UINT16 rsvd1;
	HV_UINT32 rsvd2;
} __packed;

struct hv_x64_sipi_intercept_message
{
	struct hv_x64_intercept_message_header header;
	HV_UINT32 target_vp_index;
	HV_UINT32 interrupt_vector;
} __packed;

struct hv_register_x64_cpuid_result_parameters
{
	struct
    {
		HV_UINT32 eax;
		HV_UINT32 ecx;
		HV_UINT8 subleaf_specific;
		HV_UINT8 always_override;
		HV_UINT16 padding;
	} __packed input;
	struct
    {
		HV_UINT32 eax;
		HV_UINT32 eax_mask;
		HV_UINT32 ebx;
		HV_UINT32 ebx_mask;
		HV_UINT32 ecx;
		HV_UINT32 ecx_mask;
		HV_UINT32 edx;
		HV_UINT32 edx_mask;
	} __packed result;
} __packed;

struct hv_register_x64_msr_result_parameters
{
	HV_UINT32 msr_index;
	HV_UINT32 access_type;
	HV_UINT32 action; /* enum hv_unimplemented_msr_action */
} __packed;

union hv_register_intercept_result_parameters
{
	struct hv_register_x64_cpuid_result_parameters cpuid;
	struct hv_register_x64_msr_result_parameters msr;
} __packed;

struct hv_async_completion_message_payload
{
	HV_UINT64 partition_id;
	HV_UINT32 status;
	HV_UINT32 completion_count;
	HV_UINT64 sub_status;
} __packed;

struct hv_input_register_intercept_result
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT32 intercept_type; /* enum hv_intercept_type */
	union hv_register_intercept_result_parameters parameters;
} __packed;

struct hv_input_create_port
{
	HV_UINT64 port_partition_id;
	union hv_port_id port_id;
	HV_UINT8 port_vtl;
	HV_UINT8 min_connection_vtl;
	HV_UINT16 padding;
	HV_UINT64 connection_partition_id;
	struct hv_port_info port_info;
	struct hv_proximity_domain_info proximity_domain_info;
} __packed;

struct hv_input_connect_port
{
	HV_UINT64 connection_partition_id;
	union hv_connection_id connection_id;
	HV_UINT8 connection_vtl;
	HV_UINT8 rsvdz0;
	HV_UINT16 rsvdz1;
	HV_UINT64 port_partition_id;
	union hv_port_id port_id;
	HV_UINT32 reserved2;
	struct hv_connection_info connection_info;
	struct hv_proximity_domain_info proximity_domain_info;
} __packed;

union hv_input_notify_port_ring_empty
{
	HV_UINT64 AsUINT64;
	struct
{
		HV_UINT32 sint_index;
		HV_UINT32 reserved;
	};
} __packed;

struct hv_input_signal_event_direct
{
	HV_UINT64 target_partition;
	HV_UINT32 target_vp;
	HV_UINT8  target_vtl;
	HV_UINT8  target_sint;
	HV_UINT16 flag_number;
} __packed;

struct hv_output_signal_event_direct
{
	HV_UINT8	newly_signaled;
	HV_UINT8	reserved[7];
} __packed;

struct hv_input_post_message_direct
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT8  vtl;
	HV_UINT8  padding[3];
	HV_UINT32 sint_index;
	HV_UINT8  message[HV_MESSAGE_SIZE];
	HV_UINT32 padding2;
} __packed;

struct hv_guest_mapping_flush_list
{ /* HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST */
	u64 address_space;
	u64 flags;
	union hv_gpa_page_range gpa_list[];
};

#define HV_SUPPORTS_VP_STATE

struct hv_vp_state_data_xsave
{
	HV_UINT64 flags;
	union hv_x64_xsave_xfem_register states;
} __packed;

/*
 * For getting and setting VP state, there are two options based on the state type:
 *
 *     1.) Data that is accessed by PFNs in the input hypercall page. This is used
 *         for state which may not fit into the hypercall pages.
 *     2.) Data that is accessed directly in the input\output hypercall pages.
 *         This is used for state that will always fit into the hypercall pages.
 *
 * In the future this could be dynamic based on the size if needed.
 *
 * Note these hypercalls have an 8-byte aligned variable header size as per the tlfs
 */

#define HV_GET_SET_VP_STATE_TYPE_PFN	(1 << 31)

enum hv_get_set_vp_state_type
{
	HV_GET_SET_VP_STATE_LOCAL_INTERRUPT_CONTROLLER_STATE = 0 | HV_GET_SET_VP_STATE_TYPE_PFN,

	HV_GET_SET_VP_STATE_XSAVE		= 1 | HV_GET_SET_VP_STATE_TYPE_PFN,
	/* Synthetic message page */
	HV_GET_SET_VP_STATE_SIM_PAGE		= 2 | HV_GET_SET_VP_STATE_TYPE_PFN,
	/* Synthetic interrupt event flags page. */
	HV_GET_SET_VP_STATE_SIEF_PAGE		= 3 | HV_GET_SET_VP_STATE_TYPE_PFN,

	/* Synthetic timers. */
	HV_GET_SET_VP_STATE_SYNTHETIC_TIMERS	= 4,
};

struct hv_vp_state_data
{
	HV_UINT32 type;
	HV_UINT32 rsvd;
	struct hv_vp_state_data_xsave xsave;
} __packed;

struct hv_input_get_vp_state
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT8 input_vtl;
	HV_UINT8 rsvd0;
	HV_UINT16 rsvd1;
	struct hv_vp_state_data state_data;
	HV_UINT64 output_data_pfns[];
} __packed;

union hv_output_get_vp_state
{
	struct hv_local_interrupt_controller_state interrupt_controller_state;
	struct hv_synthetic_timers_state synthetic_timers_state;
} __packed;

union hv_input_set_vp_state_data
{
	HV_UINT64 pfns;
	HV_UINT8 bytes;
} __packed;

struct hv_input_set_vp_state
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT8 input_vtl;
	HV_UINT8 rsvd0;
	HV_UINT16 rsvd1;
	struct hv_vp_state_data state_data;
	union hv_input_set_vp_state_data data[];
} __packed;

/*
 * Dispatch state for the VP communicated by the hypervisor to the
 * VP-dispatching thread in the root on return from HVCALL_DISPATCH_VP.
 */
enum hv_vp_dispatch_state
{
	HV_VP_DISPATCH_STATE_INVALID = 0,
	HV_VP_DISPATCH_STATE_BLOCKED = 1,
	HV_VP_DISPATCH_STATE_READY = 2,
};

/*
 * Dispatch event that caused the current dispatch state on return from
 * HVCALL_DISPATCH_VP.
 */
enum hv_vp_dispatch_event
{
	HV_VP_DISPATCH_EVENT_INVALID =	0x00000000,
	HV_VP_DISPATCH_EVENT_SUSPEND = 0x00000001,
	HV_VP_DISPATCH_EVENT_INTERCEPT = 0x00000002,
};

#define HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION   1024
/* The maximum array size of HV_GENERIC_SET (vp_set) buffer */
#define HV_GENERIC_SET_QWORD_COUNT(max) (((((max) - 1) >> 6) + 1) + 2)

struct hv_vp_signal_bitset_scheduler_message
{
	HV_UINT64 partition_id;
	HV_UINT32 overflow_count;
	HV_UINT16 vp_count;
	HV_UINT16 reserved;

#define BITSET_BUFFER_SIZE \
	HV_GENERIC_SET_QWORD_COUNT(HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION)
	union
{
		struct hv_vpset bitset;
		HV_UINT64 bitset_buffer[BITSET_BUFFER_SIZE];
	} vp_bitset;
#undef BITSET_BUFFER_SIZE
} __packed;

#if defined(__KERNEL__)
static_assert(sizeof(struct hv_vp_signal_bitset_scheduler_message) <=
	(sizeof(struct hv_message) - sizeof(struct hv_message_header)));
#endif

#define HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT \
	(((sizeof(struct hv_message) - sizeof(struct hv_message_header)) / \
	 (sizeof(HV_UINT64 /* partition id */) + sizeof(HV_UINT32 /* vp index */))) - 1)

struct hv_vp_signal_pair_scheduler_message
{
	HV_UINT32 overflow_count;
	HV_UINT8 vp_count;
	HV_UINT8 reserved1[3];

	HV_UINT64 partition_ids[HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT];
	HV_UINT32 vp_indexes[HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT];

	HV_UINT8 reserved2[4];
} __packed;

#if defined(__KERNEL__)
static_assert(sizeof(struct hv_vp_signal_pair_scheduler_message) ==
	(sizeof(struct hv_message) - sizeof(struct hv_message_header)));
#endif

/* Input and output structures for HVCALL_DISPATCH_VP */
#define HV_DISPATCH_VP_FLAG_CLEAR_INTERCEPT_SUSPEND 0x1
#define HV_DISPATCH_VP_FLAG_ENABLE_CALLER_INTERRUPTS 0x2
#define HV_DISPATCH_VP_FLAG_SET_CALLER_SPEC_CTRL 0x4
#define HV_DISPATCH_VP_FLAG_SKIP_VP_SPEC_FLUSH 0x8
#define HV_DISPATCH_VP_FLAG_SKIP_CALLER_SPEC_FLUSH 0x10
#define HV_DISPATCH_VP_FLAG_SKIP_CALLER_USER_SPEC_FLUSH 0x20

struct hv_input_dispatch_vp
{
	HV_UINT64 partition_id;
	HV_UINT32 vp_index;
	HV_UINT32 flags;
	HV_UINT64 time_slice; /* in 100ns */
	HV_UINT64 spec_ctrl;
} __packed;

struct hv_output_dispatch_vp
{
	HV_UINT32 dispatch_state; /* enum hv_vp_dispatch_state */
	HV_UINT32 dispatch_event; /* enum hv_vp_dispatch_event */
} __packed;

#endif /* _UAPI_HV_HVHDK_H */
