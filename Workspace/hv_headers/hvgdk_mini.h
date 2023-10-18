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

#define HV_PARTITION_ID_INVALID		((__u64) 0)
#define HV_PARTITION_ID_SELF		((__u64)-1)

/* Hyper-V specific model specific registers (MSRs) */

/* HV_X64_SYNTHETIC_MSR */
/* MSR used to identify the guest OS. */
#define HV_X64_MSR_GUEST_OS_ID			0x40000000

/* MSR used to setup pages used to communicate with the hypervisor. */
#define HV_X64_MSR_HYPERCALL			0x40000001

/* MSR used to provide vcpu index */
#define HV_X64_MSR_VP_INDEX			0x40000002

/* MSR used to reset the guest OS. */
#define HV_X64_MSR_RESET			0x40000003

/* MSR used to provide vcpu runtime in 100ns units */
#define HV_X64_MSR_VP_RUNTIME			0x40000010

/* MSR used to read the per-partition time reference counter */
#define HV_X64_MSR_TIME_REF_COUNT		0x40000020

/* A partition's reference time stamp counter (TSC) page */
#define HV_X64_MSR_REFERENCE_TSC		0x40000021

/* MSR used to retrieve the TSC frequency */
#define HV_X64_MSR_TSC_FREQUENCY		0x40000022

/* MSR used to retrieve the local APIC timer frequency */
#define HV_X64_MSR_APIC_FREQUENCY		0x40000023

/* Define the virtual APIC registers */
#define HV_X64_MSR_EOI				0x40000070
#define HV_X64_MSR_ICR				0x40000071
#define HV_X64_MSR_TPR				0x40000072
#define HV_X64_MSR_VP_ASSIST_PAGE		0x40000073

/* Define synthetic interrupt controller model specific registers. */
#define HV_X64_MSR_SCONTROL			0x40000080
#define HV_X64_MSR_SVERSION			0x40000081
#define HV_X64_MSR_SIEFP			0x40000082
#define HV_X64_MSR_SIMP				0x40000083
#define HV_X64_MSR_EOM				0x40000084
#define HV_X64_MSR_SIRBP			0x40000085
#define HV_X64_MSR_SINT0			0x40000090
#define HV_X64_MSR_SINT1			0x40000091
#define HV_X64_MSR_SINT2			0x40000092
#define HV_X64_MSR_SINT3			0x40000093
#define HV_X64_MSR_SINT4			0x40000094
#define HV_X64_MSR_SINT5			0x40000095
#define HV_X64_MSR_SINT6			0x40000096
#define HV_X64_MSR_SINT7			0x40000097
#define HV_X64_MSR_SINT8			0x40000098
#define HV_X64_MSR_SINT9			0x40000099
#define HV_X64_MSR_SINT10			0x4000009A
#define HV_X64_MSR_SINT11			0x4000009B
#define HV_X64_MSR_SINT12			0x4000009C
#define HV_X64_MSR_SINT13			0x4000009D
#define HV_X64_MSR_SINT14			0x4000009E
#define HV_X64_MSR_SINT15			0x4000009F

/* Define synthetic interrupt controller model specific registers for nested hypervisor */
#define HV_X64_MSR_NESTED_SCONTROL		0x40001080
#define HV_X64_MSR_NESTED_SVERSION		0x40001081
#define HV_X64_MSR_NESTED_SIEFP			0x40001082
#define HV_X64_MSR_NESTED_SIMP			0x40001083
#define HV_X64_MSR_NESTED_EOM			0x40001084
#define HV_X64_MSR_NESTED_SINT0			0x40001090

/*
 * Synthetic Timer MSRs. Four timers per vcpu.
 */
#define HV_X64_MSR_STIMER0_CONFIG		0x400000B0
#define HV_X64_MSR_STIMER0_COUNT		0x400000B1
#define HV_X64_MSR_STIMER1_CONFIG		0x400000B2
#define HV_X64_MSR_STIMER1_COUNT		0x400000B3
#define HV_X64_MSR_STIMER2_CONFIG		0x400000B4
#define HV_X64_MSR_STIMER2_COUNT		0x400000B5
#define HV_X64_MSR_STIMER3_CONFIG		0x400000B6
#define HV_X64_MSR_STIMER3_COUNT		0x400000B7

/* Hyper-V guest idle MSR */
#define HV_X64_MSR_GUEST_IDLE			0x400000F0

/* Hyper-V guest crash notification MSR's */
#define HV_X64_MSR_CRASH_P0			0x40000100
#define HV_X64_MSR_CRASH_P1			0x40000101
#define HV_X64_MSR_CRASH_P2			0x40000102
#define HV_X64_MSR_CRASH_P3			0x40000103
#define HV_X64_MSR_CRASH_P4			0x40000104
#define HV_X64_MSR_CRASH_CTL			0x40000105

/* TSC emulation after migration */
#define HV_X64_MSR_REENLIGHTENMENT_CONTROL	0x40000106
#define HV_X64_MSR_TSC_EMULATION_CONTROL	0x40000107
#define HV_X64_MSR_TSC_EMULATION_STATUS		0x40000108

/* TSC invariant control */
#define HV_X64_MSR_TSC_INVARIANT_CONTROL	0x40000118

/*
 * Version info reported by hypervisor
 * Changed to a union for convenience
 */
union hv_hypervisor_version_info {
	struct {
		__u32 build_number;

		__u32 minor_version : 16;
		__u32 major_version : 16;

		__u32 service_pack;

		__u32 service_number : 24;
		__u32 service_branch : 8;
	};
	struct {
		__u32 eax;
		__u32 ebx;
		__u32 ecx;
		__u32 edx;
	};
};

/* HV_CPUID_FUNCTION */
#define HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS	0x40000000
#define HYPERV_CPUID_VERSION			0x40000002

/* HV_X64_ENLIGHTENMENT_INFORMATION */

/* DeprecateAutoEoi */
#define HV_DEPRECATING_AEOI_RECOMMENDED		BIT(9)

#define HV_MAXIMUM_PROCESSORS       2048

#define HV_MAX_VP_INDEX			(HV_MAXIMUM_PROCESSORS - 1)
#define HV_VP_INDEX_SELF		((__u32)-2)
#define HV_ANY_VP			((__u32)-1)

/* Declare the various hypercall operations. */
/* HV_CALL_CODE */
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE	0x0002
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST	0x0003
#define HVCALL_NOTIFY_LONG_SPIN_WAIT		0x0008
#define HVCALL_SEND_IPI				0x000b
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX	0x0013
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX	0x0014
#define HVCALL_SEND_IPI_EX			0x0015
#define HVCALL_CREATE_PARTITION			0x0040
#define HVCALL_INITIALIZE_PARTITION		0x0041
#define HVCALL_FINALIZE_PARTITION		0x0042
#define HVCALL_DELETE_PARTITION			0x0043
#define HVCALL_GET_PARTITION_PROPERTY		0x0044
#define HVCALL_SET_PARTITION_PROPERTY		0x0045
#define HVCALL_GET_PARTITION_ID			0x0046
#define HVCALL_DEPOSIT_MEMORY			0x0048
#define HVCALL_WITHDRAW_MEMORY			0x0049
#define HVCALL_MAP_GPA_PAGES			0x004b
#define HVCALL_UNMAP_GPA_PAGES			0x004c
#define HVCALL_INSTALL_INTERCEPT		0x004d
#define HVCALL_CREATE_VP			0x004e
#define HVCALL_GET_VP_REGISTERS			0x0050
#define HVCALL_SET_VP_REGISTERS			0x0051
#define HVCALL_TRANSLATE_VIRTUAL_ADDRESS	0x0052
#define HVCALL_CLEAR_VIRTUAL_INTERRUPT		0x0056
#define HVCALL_DELETE_PORT			0x0058
#define HVCALL_DISCONNECT_PORT			0x005b
#define HVCALL_POST_MESSAGE			0x005c
#define HVCALL_SIGNAL_EVENT			0x005d
#define HVCALL_POST_DEBUG_DATA			0x0069
#define HVCALL_RETRIEVE_DEBUG_DATA		0x006a
#define HVCALL_RESET_DEBUG_SESSION		0x006b
#define HVCALL_ADD_LOGICAL_PROCESSOR		0x0076
#define HVCALL_GET_SYSTEM_PROPERTY		0x007b
#define HVCALL_MAP_DEVICE_INTERRUPT		0x007c
#define HVCALL_UNMAP_DEVICE_INTERRUPT		0x007d
#define HVCALL_RETARGET_INTERRUPT		0x007e
#define HVCALL_NOTIFY_PORT_RING_EMPTY		0x008b
#define HVCALL_REGISTER_INTERCEPT_RESULT	0x0091
#define HVCALL_ASSERT_VIRTUAL_INTERRUPT		0x0094
#define HVCALL_CREATE_PORT			0x0095
#define HVCALL_CONNECT_PORT			0x0096
#define HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE	0x00af
#define HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST	0x00b0
#define HVCALL_GET_GPA_PAGES_ACCESS_STATES	0x00c9
#define HVCALL_SIGNAL_EVENT_DIRECT		0x00c0
#define HVCALL_POST_MESSAGE_DIRECT		0x00c1
#define HVCALL_DISPATCH_VP			0x00c2
#define HVCALL_MAP_VP_STATE_PAGE		0x00e1
#define HVCALL_UNMAP_VP_STATE_PAGE		0x00e2
#define HVCALL_GET_VP_STATE			0x00e3
#define HVCALL_SET_VP_STATE			0x00e4
#define HVCALL_GET_VP_CPUID_VALUES		0x00f4

/*
 * Some macros - i.e. GENMASK_ULL and BIT_ULL - are not currently supported by
 * userspace rust bindings generation tool.
 * As the below are not currently needed in userspace, don't export them and
 * avoid the issue altogether for now.
 */
#if defined(__KERNEL__)

/* HV_HYPERCALL_INPUT */
#define HV_HYPERCALL_RESULT_MASK	GENMASK_ULL(15, 0)
#define HV_HYPERCALL_FAST_BIT		BIT(16)
#define HV_HYPERCALL_VARHEAD_OFFSET	17
#define HV_HYPERCALL_NESTED		BIT(31)
#define HV_HYPERCALL_REP_COMP_OFFSET	32
#define HV_HYPERCALL_REP_COMP_1		BIT_ULL(32)
#define HV_HYPERCALL_REP_COMP_MASK	GENMASK_ULL(43, 32)
#define HV_HYPERCALL_REP_START_OFFSET	48
#define HV_HYPERCALL_REP_START_MASK	GENMASK_ULL(59, 48)

#endif /* __KERNEL__ */

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

enum hv_register_name {
	/* Suspend Registers */
	HV_REGISTER_EXPLICIT_SUSPEND		= 0x00000000,
	HV_REGISTER_INTERCEPT_SUSPEND		= 0x00000001,
	HV_REGISTER_DISPATCH_SUSPEND		= 0x00000003,

	HV_REGISTER_VP_ROOT_SIGNAL_COUNT        = 0x00090014,

	/* Synthetic VSM registers */
	HV_REGISTER_VSM_CODE_PAGE_OFFSETS	= 0x000D0002,
	HV_REGISTER_VSM_CAPABILITIES		= 0x000D0006,
	HV_REGISTER_VSM_PARTITION_CONFIG	= 0x000D0007,

	/* Interruptible notification register */
	HV_X64_REGISTER_DELIVERABILITY_NOTIFICATIONS	= 0x00010006,

	/* X64 User-Mode Registers */
	HV_X64_REGISTER_RAX	= 0x00020000,
	HV_X64_REGISTER_RCX	= 0x00020001,
	HV_X64_REGISTER_RDX	= 0x00020002,
	HV_X64_REGISTER_RBX	= 0x00020003,
	HV_X64_REGISTER_RSP	= 0x00020004,
	HV_X64_REGISTER_RBP	= 0x00020005,
	HV_X64_REGISTER_RSI	= 0x00020006,
	HV_X64_REGISTER_RDI	= 0x00020007,
	HV_X64_REGISTER_R8	= 0x00020008,
	HV_X64_REGISTER_R9	= 0x00020009,
	HV_X64_REGISTER_R10	= 0x0002000A,
	HV_X64_REGISTER_R11	= 0x0002000B,
	HV_X64_REGISTER_R12	= 0x0002000C,
	HV_X64_REGISTER_R13	= 0x0002000D,
	HV_X64_REGISTER_R14	= 0x0002000E,
	HV_X64_REGISTER_R15	= 0x0002000F,
	HV_X64_REGISTER_RIP	= 0x00020010,
	HV_X64_REGISTER_RFLAGS	= 0x00020011,

	/* X64 Floating Point and Vector Registers */
	HV_X64_REGISTER_XMM0			= 0x00030000,
	HV_X64_REGISTER_XMM1			= 0x00030001,
	HV_X64_REGISTER_XMM2			= 0x00030002,
	HV_X64_REGISTER_XMM3			= 0x00030003,
	HV_X64_REGISTER_XMM4			= 0x00030004,
	HV_X64_REGISTER_XMM5			= 0x00030005,
	HV_X64_REGISTER_XMM6			= 0x00030006,
	HV_X64_REGISTER_XMM7			= 0x00030007,
	HV_X64_REGISTER_XMM8			= 0x00030008,
	HV_X64_REGISTER_XMM9			= 0x00030009,
	HV_X64_REGISTER_XMM10			= 0x0003000A,
	HV_X64_REGISTER_XMM11			= 0x0003000B,
	HV_X64_REGISTER_XMM12			= 0x0003000C,
	HV_X64_REGISTER_XMM13			= 0x0003000D,
	HV_X64_REGISTER_XMM14			= 0x0003000E,
	HV_X64_REGISTER_XMM15			= 0x0003000F,
	HV_X64_REGISTER_FP_MMX0			= 0x00030010,
	HV_X64_REGISTER_FP_MMX1			= 0x00030011,
	HV_X64_REGISTER_FP_MMX2			= 0x00030012,
	HV_X64_REGISTER_FP_MMX3			= 0x00030013,
	HV_X64_REGISTER_FP_MMX4			= 0x00030014,
	HV_X64_REGISTER_FP_MMX5			= 0x00030015,
	HV_X64_REGISTER_FP_MMX6			= 0x00030016,
	HV_X64_REGISTER_FP_MMX7			= 0x00030017,
	HV_X64_REGISTER_FP_CONTROL_STATUS	= 0x00030018,
	HV_X64_REGISTER_XMM_CONTROL_STATUS	= 0x00030019,

	/* X64 Control Registers */
	HV_X64_REGISTER_CR0	= 0x00040000,
	HV_X64_REGISTER_CR2	= 0x00040001,
	HV_X64_REGISTER_CR3	= 0x00040002,
	HV_X64_REGISTER_CR4	= 0x00040003,
	HV_X64_REGISTER_CR8	= 0x00040004,
	HV_X64_REGISTER_XFEM	= 0x00040005,

	/* X64 Intermediate Control Registers */
	HV_X64_REGISTER_INTERMEDIATE_CR0	= 0x00041000,
	HV_X64_REGISTER_INTERMEDIATE_CR4	= 0x00041003,
	HV_X64_REGISTER_INTERMEDIATE_CR8	= 0x00041004,

	/* X64 Debug Registers */
	HV_X64_REGISTER_DR0	= 0x00050000,
	HV_X64_REGISTER_DR1	= 0x00050001,
	HV_X64_REGISTER_DR2	= 0x00050002,
	HV_X64_REGISTER_DR3	= 0x00050003,
	HV_X64_REGISTER_DR6	= 0x00050004,
	HV_X64_REGISTER_DR7	= 0x00050005,

	/* X64 Segment Registers */
	HV_X64_REGISTER_ES	= 0x00060000,
	HV_X64_REGISTER_CS	= 0x00060001,
	HV_X64_REGISTER_SS	= 0x00060002,
	HV_X64_REGISTER_DS	= 0x00060003,
	HV_X64_REGISTER_FS	= 0x00060004,
	HV_X64_REGISTER_GS	= 0x00060005,
	HV_X64_REGISTER_LDTR	= 0x00060006,
	HV_X64_REGISTER_TR	= 0x00060007,

	/* X64 Table Registers */
	HV_X64_REGISTER_IDTR	= 0x00070000,
	HV_X64_REGISTER_GDTR	= 0x00070001,

	/* X64 Virtualized MSRs */
	HV_X64_REGISTER_TSC		= 0x00080000,
	HV_X64_REGISTER_EFER		= 0x00080001,
	HV_X64_REGISTER_KERNEL_GS_BASE	= 0x00080002,
	HV_X64_REGISTER_APIC_BASE	= 0x00080003,
	HV_X64_REGISTER_PAT		= 0x00080004,
	HV_X64_REGISTER_SYSENTER_CS	= 0x00080005,
	HV_X64_REGISTER_SYSENTER_EIP	= 0x00080006,
	HV_X64_REGISTER_SYSENTER_ESP	= 0x00080007,
	HV_X64_REGISTER_STAR		= 0x00080008,
	HV_X64_REGISTER_LSTAR		= 0x00080009,
	HV_X64_REGISTER_CSTAR		= 0x0008000A,
	HV_X64_REGISTER_SFMASK		= 0x0008000B,
	HV_X64_REGISTER_INITIAL_APIC_ID	= 0x0008000C,

	/* X64 Cache control MSRs */
	HV_X64_REGISTER_MSR_MTRR_CAP		= 0x0008000D,
	HV_X64_REGISTER_MSR_MTRR_DEF_TYPE	= 0x0008000E,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE0	= 0x00080010,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE1	= 0x00080011,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE2	= 0x00080012,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE3	= 0x00080013,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE4	= 0x00080014,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE5	= 0x00080015,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE6	= 0x00080016,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE7	= 0x00080017,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE8	= 0x00080018,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASE9	= 0x00080019,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASEA	= 0x0008001A,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASEB	= 0x0008001B,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASEC	= 0x0008001C,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASED	= 0x0008001D,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASEE	= 0x0008001E,
	HV_X64_REGISTER_MSR_MTRR_PHYS_BASEF	= 0x0008001F,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK0	= 0x00080040,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK1	= 0x00080041,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK2	= 0x00080042,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK3	= 0x00080043,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK4	= 0x00080044,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK5	= 0x00080045,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK6	= 0x00080046,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK7	= 0x00080047,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK8	= 0x00080048,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASK9	= 0x00080049,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASKA	= 0x0008004A,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASKB	= 0x0008004B,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASKC	= 0x0008004C,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASKD	= 0x0008004D,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASKE	= 0x0008004E,
	HV_X64_REGISTER_MSR_MTRR_PHYS_MASKF	= 0x0008004F,
	HV_X64_REGISTER_MSR_MTRR_FIX64K00000	= 0x00080070,
	HV_X64_REGISTER_MSR_MTRR_FIX16K80000	= 0x00080071,
	HV_X64_REGISTER_MSR_MTRR_FIX16KA0000	= 0x00080072,
	HV_X64_REGISTER_MSR_MTRR_FIX4KC0000	= 0x00080073,
	HV_X64_REGISTER_MSR_MTRR_FIX4KC8000	= 0x00080074,
	HV_X64_REGISTER_MSR_MTRR_FIX4KD0000	= 0x00080075,
	HV_X64_REGISTER_MSR_MTRR_FIX4KD8000	= 0x00080076,
	HV_X64_REGISTER_MSR_MTRR_FIX4KE0000	= 0x00080077,
	HV_X64_REGISTER_MSR_MTRR_FIX4KE8000	= 0x00080078,
	HV_X64_REGISTER_MSR_MTRR_FIX4KF0000	= 0x00080079,
	HV_X64_REGISTER_MSR_MTRR_FIX4KF8000	= 0x0008007A,

	HV_X64_REGISTER_TSC_AUX		= 0x0008007B,
	HV_X64_REGISTER_BNDCFGS		= 0x0008007C,
	HV_X64_REGISTER_DEBUG_CTL	= 0x0008007D,

	HV_X64_REGISTER_SGX_LAUNCH_CONTROL0	= 0x00080080,
	HV_X64_REGISTER_SGX_LAUNCH_CONTROL1	= 0x00080081,
	HV_X64_REGISTER_SGX_LAUNCH_CONTROL2	= 0x00080082,
	HV_X64_REGISTER_SGX_LAUNCH_CONTROL3	= 0x00080083,
	HV_X64_REGISTER_SPEC_CTRL		= 0x00080084,
	HV_X64_REGISTER_PRED_CMD		= 0x00080085,
	HV_X64_REGISTER_VIRT_SPEC_CTRL		= 0x00080086,
	HV_X64_REGISTER_TSC_ADJUST		= 0x00080096,

	/* Other MSRs */
	HV_X64_REGISTER_MSR_IA32_MISC_ENABLE		= 0x000800A0,
	HV_X64_REGISTER_IA32_FEATURE_CONTROL		= 0x000800A1,
	HV_X64_REGISTER_IA32_VMX_BASIC			= 0x000800A2,
	HV_X64_REGISTER_IA32_VMX_PINBASED_CTLS		= 0x000800A3,
	HV_X64_REGISTER_IA32_VMX_PROCBASED_CTLS		= 0x000800A4,
	HV_X64_REGISTER_IA32_VMX_EXIT_CTLS		= 0x000800A5,
	HV_X64_REGISTER_IA32_VMX_ENTRY_CTLS		= 0x000800A6,
	HV_X64_REGISTER_IA32_VMX_MISC			= 0x000800A7,
	HV_X64_REGISTER_IA32_VMX_CR0_FIXED0		= 0x000800A8,
	HV_X64_REGISTER_IA32_VMX_CR0_FIXED1		= 0x000800A9,
	HV_X64_REGISTER_IA32_VMX_CR4_FIXED0		= 0x000800AA,
	HV_X64_REGISTER_IA32_VMX_CR4_FIXED1		= 0x000800AB,
	HV_X64_REGISTER_IA32_VMX_VMCS_ENUM		= 0x000800AC,
	HV_X64_REGISTER_IA32_VMX_PROCBASED_CTLS2	= 0x000800AD,
	HV_X64_REGISTER_IA32_VMX_EPT_VPID_CAP		= 0x000800AE,
	HV_X64_REGISTER_IA32_VMX_TRUE_PINBASED_CTLS	= 0x000800AF,
	HV_X64_REGISTER_IA32_VMX_TRUE_PROCBASED_CTLS	= 0x000800B0,
	HV_X64_REGISTER_IA32_VMX_TRUE_EXIT_CTLS		= 0x000800B1,
	HV_X64_REGISTER_IA32_VMX_TRUE_ENTRY_CTLS	= 0x000800B2,

	HV_X64_REGISTER_REG_PAGE	= 0x0009001C,
};

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
