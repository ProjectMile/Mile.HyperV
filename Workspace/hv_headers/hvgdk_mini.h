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

union hv_gpa_page_range {
	u64 address_space;
	struct {
		u64 additional_pages:11;
		u64 largepage:1;
		u64 basepfn:52;
	} page;
	struct {
		u64 reserved:12;
		u64 page_size:1;
		u64 reserved1:8;
		u64 base_large_pfn:43;
	};
};

/* Define the number of synthetic interrupt sources. */
#define HV_SYNIC_SINT_COUNT (16)

/* Hyper-V defined statically assigned SINTs */
#define HV_SYNIC_INTERCEPTION_SINT_INDEX 0x00000000
#define HV_SYNIC_IOMMU_FAULT_SINT_INDEX  0x00000001
#define HV_SYNIC_VMBUS_SINT_INDEX        0x00000002
#define HV_SYNIC_FIRST_UNUSED_SINT_INDEX 0x00000005

/* mshv assigned SINT for doorbell */
#define HV_SYNIC_DOORBELL_SINT_INDEX     HV_SYNIC_FIRST_UNUSED_SINT_INDEX

enum hv_interrupt_type {
	HV_X64_INTERRUPT_TYPE_FIXED		= 0x0000,
	HV_X64_INTERRUPT_TYPE_LOWESTPRIORITY	= 0x0001,
	HV_X64_INTERRUPT_TYPE_SMI		= 0x0002,
	HV_X64_INTERRUPT_TYPE_REMOTEREAD	= 0x0003,
	HV_X64_INTERRUPT_TYPE_NMI		= 0x0004,
	HV_X64_INTERRUPT_TYPE_INIT		= 0x0005,
	HV_X64_INTERRUPT_TYPE_SIPI		= 0x0006,
	HV_X64_INTERRUPT_TYPE_EXTINT		= 0x0007,
	HV_X64_INTERRUPT_TYPE_LOCALINT0		= 0x0008,
	HV_X64_INTERRUPT_TYPE_LOCALINT1		= 0x0009,
	HV_X64_INTERRUPT_TYPE_MAXIMUM		= 0x000A,
};

/* Define synthetic interrupt source. */
union hv_synic_sint {
	__u64 as_uint64;
	struct {
		__u64 vector : 8;
		__u64 reserved1 : 8;
		__u64 masked : 1;
		__u64 auto_eoi : 1;
		__u64 polling : 1;
		__u64 as_intercept : 1;
		__u64 proxy : 1;
		__u64 reserved2 : 43;
	} __packed;
};

union hv_x64_xsave_xfem_register {
	__u64 as_uint64;
	struct {
		__u32 low_uint32;
		__u32 high_uint32;
	} __packed;
	struct {
		__u64 legacy_x87 : 1;
		__u64 legacy_sse : 1;
		__u64 avx : 1;
		__u64 mpx_bndreg : 1;
		__u64 mpx_bndcsr : 1;
		__u64 avx_512_op_mask : 1;
		__u64 avx_512_zmmhi : 1;
		__u64 avx_512_zmm16_31 : 1;
		__u64 rsvd8_9 : 2;
		__u64 pasid : 1;
		__u64 cet_u : 1;
		__u64 cet_s : 1;
		__u64 rsvd13_16 : 4;
		__u64 xtile_cfg : 1;
		__u64 xtile_data : 1;
		__u64 rsvd19_63 : 45;
	} __packed;
};

/* Define the number of synthetic timers */
#define HV_SYNIC_STIMER_COUNT	(4)

/* Define port identifier type. */
union hv_port_id {
	__u32 asu32;
	struct {
		__u32 id : 24;
		__u32 reserved : 8;
	} __packed u; // TODO remove this u
};

#define HV_MESSAGE_SIZE			(256)
#define HV_MESSAGE_PAYLOAD_BYTE_COUNT	(240)
#define HV_MESSAGE_PAYLOAD_QWORD_COUNT	(30)

/* Define hypervisor message types. */
enum hv_message_type {
	HVMSG_NONE				= 0x00000000,

	/* Memory access messages. */
	HVMSG_UNMAPPED_GPA			= 0x80000000,
	HVMSG_GPA_INTERCEPT			= 0x80000001,

	/* Timer notification messages. */
	HVMSG_TIMER_EXPIRED			= 0x80000010,

	/* Error messages. */
	HVMSG_INVALID_VP_REGISTER_VALUE		= 0x80000020,
	HVMSG_UNRECOVERABLE_EXCEPTION		= 0x80000021,
	HVMSG_UNSUPPORTED_FEATURE		= 0x80000022,

	/*
	 * Opaque intercept message. The original intercept message is only
	 * accessible from the mapped intercept message page.
	 */
	HVMSG_OPAQUE_INTERCEPT			= 0x8000003F,

	/* Trace buffer complete messages. */
	HVMSG_EVENTLOG_BUFFERCOMPLETE		= 0x80000040,

	/* Hypercall intercept */
	HVMSG_HYPERCALL_INTERCEPT		= 0x80000050,

	/* SynIC intercepts */
	HVMSG_SYNIC_EVENT_INTERCEPT		= 0x80000060,
	HVMSG_SYNIC_SINT_INTERCEPT		= 0x80000061,
	HVMSG_SYNIC_SINT_DELIVERABLE	= 0x80000062,

	/* Async call completion intercept */
	HVMSG_ASYNC_CALL_COMPLETION		= 0x80000070,

	/* Root scheduler messages */
	HVMSG_SCHEDULER_VP_SIGNAL_BITSET	= 0x80000100,
	HVMSG_SCHEDULER_VP_SIGNAL_PAIR		= 0x80000101,

	/* Platform-specific processor intercept messages. */
	HVMSG_X64_IO_PORT_INTERCEPT		= 0x80010000,
	HVMSG_X64_MSR_INTERCEPT			= 0x80010001,
	HVMSG_X64_CPUID_INTERCEPT		= 0x80010002,
	HVMSG_X64_EXCEPTION_INTERCEPT		= 0x80010003,
	HVMSG_X64_APIC_EOI			= 0x80010004,
	HVMSG_X64_LEGACY_FP_ERROR		= 0x80010005,
	HVMSG_X64_IOMMU_PRQ			= 0x80010006,
	HVMSG_X64_HALT				= 0x80010007,
	HVMSG_X64_INTERRUPTION_DELIVERABLE	= 0x80010008,
	HVMSG_X64_SIPI_INTERCEPT		= 0x80010009,
};

/* Define the format of the SIMP register */
union hv_synic_simp {
	__u64 as_uint64;
	struct {
		__u64 simp_enabled : 1;
		__u64 preserved : 11;
		__u64 base_simp_gpa : 52;
	} __packed;
};

union hv_message_flags {
	__u8 asu8;
	struct {
		__u8 msg_pending : 1;
		__u8 reserved : 7;
	} __packed;
};

struct hv_message_header {
	__u32 message_type;
	__u8 payload_size;
	union hv_message_flags message_flags;
	__u8 reserved[2];
	union {
		__u64 sender;
		union hv_port_id port;
	};
} __packed;

/*
 * Message format for notifications delivered via
 * intercept message(as_intercept=1)
 */
struct hv_notification_message_payload {
	__u32 sint_index;
} __packed;

struct hv_message {
	struct hv_message_header header;
	union {
		__u64 payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
	} u;
} __packed;

/* Define the synthetic interrupt message page layout. */
struct hv_message_page {
	struct hv_message sint_message[HV_SYNIC_SINT_COUNT];
} __packed;

struct hv_x64_segment_register {
	__u64 base;
	__u32 limit;
	__u16 selector;
	union {
		struct {
			__u16 segment_type : 4;
			__u16 non_system_segment : 1;
			__u16 descriptor_privilege_level : 2;
			__u16 present : 1;
			__u16 reserved : 4;
			__u16 available : 1;
			__u16 _long : 1;
			__u16 _default : 1;
			__u16 granularity : 1;
		} __packed;
		__u16 attributes;
	};
} __packed;

struct hv_x64_table_register {
	__u16 pad[3];
	__u16 limit;
	__u64 base;
} __packed;

union hv_x64_fp_control_status_register {
	struct hv_u128 as_uint128;
	struct {
		__u16 fp_control;
		__u16 fp_status;
		__u8 fp_tag;
		__u8 reserved;
		__u16 last_fp_op;
		union {
			/* long mode */
			__u64 last_fp_rip;
			/* 32 bit mode */
			struct {
				__u32 last_fp_eip;
				__u16 last_fp_cs;
				__u16 padding;
			} __packed;
		};
	} __packed;
} __packed;

union hv_x64_xmm_control_status_register {
	struct hv_u128 as_uint128;
	struct {
		union {
			/* long mode */
			__u64 last_fp_rdp;
			/* 32 bit mode */
			struct {
				__u32 last_fp_dp;
				__u16 last_fp_ds;
				__u16 padding;
			} __packed;
		};
		__u32 xmm_status_control;
		__u32 xmm_status_control_mask;
	} __packed;
} __packed;

union hv_x64_fp_register {
	struct hv_u128 as_uint128;
	struct {
		__u64 mantissa;
		__u64 biased_exponent : 15;
		__u64 sign : 1;
		__u64 reserved : 48;
	} __packed;
} __packed;

union hv_x64_msr_npiep_config_contents {
	__u64 as_uint64;
	struct {
		/*
		 * These bits enable instruction execution prevention for
		 * specific instructions.
		 */
		__u64 prevents_gdt : 1;
		__u64 prevents_idt : 1;
		__u64 prevents_ldt : 1;
		__u64 prevents_tr : 1;

		/* The reserved bits must always be 0. */
		__u64 reserved : 60;
	} __packed;
};

union hv_input_vtl {
	__u8 as_uint8;
	struct {
		__u8 target_vtl : 4;
		__u8 use_target_vtl : 1;
		__u8 reserved_z : 3;
	};
} __packed;

/* Note: not in hvgdk_mini.h */
#define HV_SUPPORTS_REGISTER_DELIVERABILITY_NOTIFICATIONS

union hv_register_vsm_partition_config {
	__u64 as_u64;
	struct {
		__u64 enable_vtl_protection : 1;
		__u64 default_vtl_protection_mask : 4;
		__u64 zero_memory_on_reset : 1;
		__u64 deny_lower_vtl_startup : 1;
		__u64 intercept_acceptance : 1;
		__u64 intercept_enable_vtl_protection : 1;
		__u64 intercept_vp_startup : 1;
		__u64 intercept_cpuid_unimplemented : 1;
		__u64 intercept_unrecoverable_exception : 1;
		__u64 intercept_page : 1;
		__u64 mbz : 51;
	};
};

struct hv_nested_enlightenments_control {
	struct {
		__u32 directhypercall : 1;
		__u32 reserved : 31;
	} __packed features;
	struct {
		__u32 inter_partition_comm : 1;
		__u32 reserved : 31;
	} __packed hypercall_controls;
} __packed;

/* Define virtual processor assist page structure. */
struct hv_vp_assist_page {
	__u32 apic_assist;
	__u32 reserved1;
	__u32 vtl_entry_reason;
	__u32 vtl_reserved;
	__u64 vtl_ret_x64rax;
	__u64 vtl_ret_x64rcx;
	struct hv_nested_enlightenments_control nested_control;
	__u8 enlighten_vmentry;
	__u8 reserved2[7];
	__u64 current_nested_vmcs;
	__u8 synthetic_time_unhalted_timer_expired;
	__u8 reserved3[7];
	__u8 virtualization_fault_information[40];
	__u8 reserved4[8];
	__u8 intercept_message[256];
	__u8 vtl_ret_actions[256];
} __packed;

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

/* General Hypervisor Register Content Definitions */

union hv_explicit_suspend_register {
	__u64 as_uint64;
	struct {
		__u64 suspended : 1;
		__u64 reserved : 63;
	} __packed;
};

union hv_intercept_suspend_register {
	__u64 as_uint64;
	struct {
		__u64 suspended : 1;
		__u64 reserved : 63;
	} __packed;
};

union hv_dispatch_suspend_register {
	__u64 as_uint64;
	struct {
		__u64 suspended : 1;
		__u64 reserved : 63;
	} __packed;
};

union hv_x64_interrupt_state_register {
	__u64 as_uint64;
	struct {
		__u64 interrupt_shadow : 1;
		__u64 nmi_masked : 1;
		__u64 reserved : 62;
	} __packed;
};

union hv_x64_pending_exception_event {
	__u64 as_uint64[2];
	struct {
		__u32 event_pending : 1;
		__u32 event_type : 3;
		__u32 reserved0 : 4;
		__u32 deliver_error_code : 1;
		__u32 reserved1 : 7;
		__u32 vector : 16;
		__u32 error_code;
		__u64 exception_parameter;
	} __packed;
};

union hv_x64_pending_virtualization_fault_event {
	__u64 as_uint64[2];
	struct {
		__u32 event_pending : 1;
		__u32 event_type : 3;
		__u32 reserved0 : 4;
		__u32 reserved1 : 8;
		__u32 parameter0 : 16;
		__u32 code;
		__u64 parameter1;
	} __packed;
};

// bunch of stuff in between

union hv_x64_pending_interruption_register {
	__u64 as_uint64;
	struct {
		__u32 interruption_pending : 1;
		__u32 interruption_type : 3;
		__u32 deliver_error_code : 1;
		__u32 instruction_length : 4;
		__u32 nested_event : 1;
		__u32 reserved : 6;
		__u32 interruption_vector : 16;
		__u32 error_code;
	} __packed;
};

union hv_register_value {
	struct hv_u128 reg128;
	__u64 reg64;
	__u32 reg32;
	__u16 reg16;
	__u8 reg8;

	union hv_x64_fp_register fp;
	union hv_x64_fp_control_status_register fp_control_status;
	union hv_x64_xmm_control_status_register xmm_control_status;
	struct hv_x64_segment_register segment;
	struct hv_x64_table_register table;
	union hv_explicit_suspend_register explicit_suspend;
	union hv_intercept_suspend_register intercept_suspend;
	union hv_dispatch_suspend_register dispatch_suspend;
	union hv_x64_interrupt_state_register interrupt_state;
	union hv_x64_pending_interruption_register pending_interruption;
	union hv_x64_msr_npiep_config_contents npiep_config;
	union hv_x64_pending_exception_event pending_exception_event;
	union hv_x64_pending_virtualization_fault_event
		pending_virtualization_fault_event;
};

struct hv_register_assoc {
	__u32 name;			/* enum hv_register_name */
	__u32 reserved1;
	__u64 reserved2;
	union hv_register_value value;
} __packed;

struct hv_input_get_vp_registers {
	__u64 partition_id;
	__u32 vp_index;
	union hv_input_vtl input_vtl;
	__u8  rsvd_z8;
	__u16 rsvd_z16;
	__u32 names[];
} __packed;

struct hv_input_set_vp_registers {
	__u64 partition_id;
	__u32 vp_index;
	union hv_input_vtl input_vtl;
	__u8  rsvd_z8;
	__u16 rsvd_z16;
	struct hv_register_assoc elements[];
} __packed;

union hv_msi_entry {
	u64 as_uint64;
	struct {
		u32 address;
		u32 data;
	} __packed;
};

enum hv_interrupt_source {
	HV_INTERRUPT_SOURCE_MSI = 1, /* MSI and MSI-X */
	HV_INTERRUPT_SOURCE_IOAPIC,
};

union hv_ioapic_rte {
	u64 as_uint64;

	struct {
		u32 vector:8;
		u32 delivery_mode:3;
		u32 destination_mode:1;
		u32 delivery_status:1;
		u32 interrupt_polarity:1;
		u32 remote_irr:1;
		u32 trigger_mode:1;
		u32 interrupt_mask:1;
		u32 reserved1:15;

		u32 reserved2:24;
		u32 destination_id:8;
	};

	struct {
		u32 low_uint32;
		u32 high_uint32;
	};
} __packed;

struct hv_interrupt_entry {
	u32 source; /* enum hv_interrupt_source */
	u32 reserved1;
	union {
		union hv_msi_entry msi_entry;
		union hv_ioapic_rte ioapic_rte;
	};
} __packed;

enum hv_intercept_type {
	HV_INTERCEPT_TYPE_X64_IO_PORT			= 0X00000000,
	HV_INTERCEPT_TYPE_X64_MSR			= 0X00000001,
	HV_INTERCEPT_TYPE_X64_CPUID			= 0X00000002,
	HV_INTERCEPT_TYPE_EXCEPTION			= 0X00000003,
	HV_INTERCEPT_TYPE_REGISTER			= 0X00000004,
	HV_INTERCEPT_TYPE_MMIO				= 0X00000005,
	HV_INTERCEPT_TYPE_X64_GLOBAL_CPUID		= 0X00000006,
	HV_INTERCEPT_TYPE_X64_APIC_SMI			= 0X00000007,
	HV_INTERCEPT_TYPE_HYPERCALL			= 0X00000008,
	HV_INTERCEPT_TYPE_X64_APIC_INIT_SIPI		= 0X00000009,
	HV_INTERCEPT_TYPE_X64_APIC_WRITE		= 0X0000000B,
	HV_INTERCEPT_TYPE_X64_MSR_INDEX			= 0X0000000C,
	HV_INTERCEPT_TYPE_MAX,
	HV_INTERCEPT_TYPE_INVALID			= 0XFFFFFFFF,
};

union hv_intercept_parameters {
	/*  HV_INTERCEPT_PARAMETERS is defined to be an 8-byte field. */
	__u64 as_uint64;
	/* HV_INTERCEPT_TYPE_X64_IO_PORT */
	__u16 io_port;
	/* HV_INTERCEPT_TYPE_X64_CPUID */
	__u32 cpuid_index;
	/* HV_INTERCEPT_TYPE_X64_APIC_WRITE */
	__u32 apic_write_mask;
	/* HV_INTERCEPT_TYPE_EXCEPTION */
	__u16 exception_vector;
	/* HV_INTERCEPT_TYPE_X64_MSR_INDEX */
	__u32 msr_index;
	/* N.B. Other intercept types do not have any parameters. */
};

/* Access types for the install intercept hypercall parameter */
#define HV_INTERCEPT_ACCESS_MASK_NONE		0x00
#define HV_INTERCEPT_ACCESS_MASK_READ		0X01
#define HV_INTERCEPT_ACCESS_MASK_WRITE		0x02
#define HV_INTERCEPT_ACCESS_MASK_EXECUTE	0x04

struct hv_input_install_intercept {
	__u64 partition_id;
	__u32 access_type;	/* mask */
	__u32 intercept_type;	/* hv_intercept_type */
	union hv_intercept_parameters intercept_parameter;
} __packed;

#endif /* _UAPI_HV_HVGDK_MINI_H */
