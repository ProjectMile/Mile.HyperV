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

// bunch of stuff in between

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
