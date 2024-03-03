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

/* Bits for dirty mask of hv_vp_register_page */
#define HV_X64_REGISTER_CLASS_GENERAL	0
#define HV_X64_REGISTER_CLASS_IP	1
#define HV_X64_REGISTER_CLASS_XMM	2
#define HV_X64_REGISTER_CLASS_SEGMENT	3
#define HV_X64_REGISTER_CLASS_FLAGS	4

#define HV_VP_REGISTER_PAGE_VERSION_1	1u

struct hv_vp_register_page {
	__u16 version;
	__u8 isvalid;
	__u8 rsvdz;
	__u32 dirty;
	union {
		struct {
			/* General purpose registers
			 * (HV_X64_REGISTER_CLASS_GENERAL)
			 */
			union {
				struct {
					__u64 rax;
					__u64 rcx;
					__u64 rdx;
					__u64 rbx;
					__u64 rsp;
					__u64 rbp;
					__u64 rsi;
					__u64 rdi;
					__u64 r8;
					__u64 r9;
					__u64 r10;
					__u64 r11;
					__u64 r12;
					__u64 r13;
					__u64 r14;
					__u64 r15;
				} __packed;

				__u64 gp_registers[16];
			};
			/* Instruction pointer (HV_X64_REGISTER_CLASS_IP) */
			__u64 rip;
			/* Flags (HV_X64_REGISTER_CLASS_FLAGS) */
			__u64 rflags;
		} __packed;

		__u64 registers[18];
	};
	/* Volatile XMM registers (HV_X64_REGISTER_CLASS_XMM) */
	union {
		struct {
			struct hv_u128 xmm0;
			struct hv_u128 xmm1;
			struct hv_u128 xmm2;
			struct hv_u128 xmm3;
			struct hv_u128 xmm4;
			struct hv_u128 xmm5;
		} __packed;

		struct hv_u128 xmm_registers[6];
	};
	/* Segment registers (HV_X64_REGISTER_CLASS_SEGMENT) */
	union {
		struct {
			struct hv_x64_segment_register es;
			struct hv_x64_segment_register cs;
			struct hv_x64_segment_register ss;
			struct hv_x64_segment_register ds;
			struct hv_x64_segment_register fs;
			struct hv_x64_segment_register gs;
		} __packed;

		struct hv_x64_segment_register segment_registers[6];
	};
	/* Misc. control registers (cannot be set via this interface) */
	__u64 cr0;
	__u64 cr3;
	__u64 cr4;
	__u64 cr8;
	__u64 efer;
	__u64 dr7;
	union hv_x64_pending_interruption_register pending_interruption;
	union hv_x64_interrupt_state_register interrupt_state;
	__u64 instruction_emulation_hints;
} __packed;

#define HV_PARTITION_PROCESSOR_FEATURES_BANKS 2

union hv_partition_processor_features {
	__u64 as_uint64[HV_PARTITION_PROCESSOR_FEATURES_BANKS];
	struct {
		__u64 sse3_support:1;
		__u64 lahf_sahf_support:1;
		__u64 ssse3_support:1;
		__u64 sse4_1_support:1;
		__u64 sse4_2_support:1;
		__u64 sse4a_support:1;
		__u64 xop_support:1;
		__u64 pop_cnt_support:1;
		__u64 cmpxchg16b_support:1;
		__u64 altmovcr8_support:1;
		__u64 lzcnt_support:1;
		__u64 mis_align_sse_support:1;
		__u64 mmx_ext_support:1;
		__u64 amd3dnow_support:1;
		__u64 extended_amd3dnow_support:1;
		__u64 page_1gb_support:1;
		__u64 aes_support:1;
		__u64 pclmulqdq_support:1;
		__u64 pcid_support:1;
		__u64 fma4_support:1;
		__u64 f16c_support:1;
		__u64 rd_rand_support:1;
		__u64 rd_wr_fs_gs_support:1;
		__u64 smep_support:1;
		__u64 enhanced_fast_string_support:1;
		__u64 bmi1_support:1;
		__u64 bmi2_support:1;
		__u64 hle_support_deprecated:1;
		__u64 rtm_support_deprecated:1;
		__u64 movbe_support:1;
		__u64 npiep1_support:1;
		__u64 dep_x87_fpu_save_support:1;
		__u64 rd_seed_support:1;
		__u64 adx_support:1;
		__u64 intel_prefetch_support:1;
		__u64 smap_support:1;
		__u64 hle_support:1;
		__u64 rtm_support:1;
		__u64 rdtscp_support:1;
		__u64 clflushopt_support:1;
		__u64 clwb_support:1;
		__u64 sha_support:1;
		__u64 x87_pointers_saved_support:1;
		__u64 invpcid_support:1;
		__u64 ibrs_support:1;
		__u64 stibp_support:1;
		__u64 ibpb_support: 1;
		__u64 unrestricted_guest_support:1;
		__u64 mdd_support:1;
		__u64 fast_short_rep_mov_support:1;
		__u64 l1dcache_flush_support:1;
		__u64 rdcl_no_support:1;
		__u64 ibrs_all_support:1;
		__u64 skip_l1df_support:1;
		__u64 ssb_no_support:1;
		__u64 rsb_a_no_support:1;
		__u64 virt_spec_ctrl_support:1;
		__u64 rd_pid_support:1;
		__u64 umip_support:1;
		__u64 mbs_no_support:1;
		__u64 mb_clear_support:1;
		__u64 taa_no_support:1;
		__u64 tsx_ctrl_support:1;
		/*
		 * N.B. The final processor feature bit in bank 0 is reserved to
		 * simplify potential downlevel backports.
		 */
		__u64 reserved_bank0:1;

		/* N.B. Begin bank 1 processor features. */
		__u64 acount_mcount_support:1;
		__u64 tsc_invariant_support:1;
		__u64 cl_zero_support:1;
		__u64 rdpru_support:1;
		__u64 la57_support:1;
		__u64 mbec_support:1;
		__u64 nested_virt_support:1;
		__u64 psfd_support:1;
		__u64 cet_ss_support:1;
		__u64 cet_ibt_support:1;
		__u64 vmx_exception_inject_support:1;
		__u64 enqcmd_support:1;
		__u64 umwait_tpause_support:1;
		__u64 movdiri_support:1;
		__u64 movdir64b_support:1;
		__u64 cldemote_support:1;
		__u64 serialize_support:1;
		__u64 tsc_deadline_tmr_support:1;
		__u64 tsc_adjust_support:1;
		__u64 fzlrep_movsb:1;
		__u64 fsrep_stosb:1;
		__u64 fsrep_cmpsb:1;
		__u64 reserved_bank1:42;
	} __packed;
};

union hv_partition_processor_xsave_features {
	struct {
		__u64 xsave_support : 1;
		__u64 xsaveopt_support : 1;
		__u64 avx_support : 1;
		__u64 reserved1 : 61;
	} __packed;
	__u64 as_uint64;
};

struct hv_partition_creation_properties {
	union hv_partition_processor_features disabled_processor_features;
	union hv_partition_processor_xsave_features
		disabled_processor_xsave_features;
} __packed;

/*
 * Definition of the partition isolation state. Used for
 * HV_PARTITION_PROPERTY_ISOLATION_STATE.
 *
 *
 * The isolation states (hv_partition_isolation_state) are sub-states of
 * ObPartitionActive that apply to VBS and hardware isolated partitions.
 * For VBS isolation, the trusted host VTL 1 component uses the isolation
 * state to establish a binding between a hypervisor partition and its
 * own partition context, and to enforce certain invariants.
 *
 * Hardware-isolated partitions (including partitions that simulate
 * hardware isolation) also use isolation states to track the progression
 * of the partition security state through the architectural state machine.
 * Insecure states indicate that there is no architectural state
 * associated with the partition, and Secure indicates that the partition
 * has secure architectural state.
 *
 * ObPartitionRestoring is treated differently for isolated partitions.
 * Only the trusted host component is allowed to restore partition state,
 * and ObPartitionRestoring can only transition directly to/from secure.
 *
 *
 * ..................................................................
 * .         UNINITIALIZED     FINALIZED                            .
 * .               |           ^       ^                            .
 * .    Initialize |          /         \                           .
 * .               |         /           \                          .
 * . --------------|--------/--- ACTIVE --\------------------------ .
 * . |             |       /               \                      | .
 * . |             |      / Finalize        \ Finalize            | .
 * . |             v     /                   \                    | .
 * . |       INSECURE-CLEAN <---------------- INSECURE-DIRTY      | .
 * . |                   \        Scrub      ^                    | .
 * . |                    \                 /                     | .
 * . |                     \               /                      | .
 * . |               Secure \             / Unsecure              | .
 * . |                       \           /                        | .
 * . |                        \         /                         | .
 * . |                         v       /                          | .
 * . |                           SECURE                           | .
 * . |                             ^                              | .
 * . |_____________________________|______________________________| .
 * .                               |                                .
 * .                               v                                .
 * .                           RESTORING                            .
 * ..................................................................
 */
enum hv_partition_isolation_state {
	/*
	 * Initial and final state for all non-isolated partitions.
	 */
	HV_PARTITION_ISOLATION_INVALID             = 0,

	/*
	 * An "Insecure" partition is not being used by the trusted host
	 * component. In this state, VPs can be created and deleted. VPs cannot
	 * be started, and VP registers cannot be modified.

	 * Initial state of an isolated partition as result of Initialize or
	 * Scrub hypercalls. Guest-visible partition and VP state is considered
	 * "clean", in the sense that a call to ObScrubPartition should not
	 * result in any changes. Also, there are no accepted or confidential
	 * pages assigned to the partition. InsecureRundown is enabled.
	 */
	HV_PARTITION_ISOLATION_INSECURE_CLEAN       = 1,

	/*
	 * Guest-visible partition and VP state is not "clean". Hence it must
	 * be scrubbed first. One of 2 explicit states the trusted host
	 * component can request. It cannot transition the state to Secure. In
	 * this state,
	 *  - IsolationControl is clear.
	 *  - Secure rundowns are completely disabled.
	 *  - No assigned pages exist.
	 */
	HV_PARTITION_ISOLATION_INSECURE_DIRTY       = 2,

	/*
	 * The partition is being used by the trusted host component (and is
	 * typically bound to a single partition context in that component).
	 * One of 2 explicit states the trusted host component can request. In
	 * this state,
	 *  - VPs cannot be created or deleted.
	 *  - Partition cannot be finalized, scrubbed.
	 *  - Insecure rundowns are completely disabled.
	 */
	HV_PARTITION_ISOLATION_SECURE              = 3,

	/*
	 * Represents a failed attempt to transition to Secure state. Partition
	 * in this state cannot be finalized, scrubbed since one or more pages
	 * may be assigned.
	 */
	HV_PARTITION_ISOLATION_SECURE_DIRTY         = 4,

	/*
	 * An internal state indicating that a partition is in the process of
	 * transitioning from Secure to InsecureDirty.
	 */
	HV_PARTITION_ISOLATION_SECURE_TERMINATING   = 5,
};

#define HV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES_BANKS 1

union hv_partition_synthetic_processor_features {
	__u64 as_uint64[HV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES_BANKS];

	struct {
		/* Report a hypervisor is present. CPUID leaves
		 * 0x40000000 and 0x40000001 are supported.
		 */
		__u64 hypervisor_present:1;

		/*
		 * Features associated with HV#1:
		 */

		/* Report support for Hv1 (CPUID leaves 0x40000000 - 0x40000006). */
		__u64 hv1:1;

		/* Access to HV_X64_MSR_VP_RUNTIME.
		 * Corresponds to access_vp_run_time_reg privilege.
		 */
		__u64 access_vp_run_time_reg:1;

		/* Access to HV_X64_MSR_TIME_REF_COUNT.
		 * Corresponds to access_partition_reference_counter privilege.
		 */
		__u64 access_partition_reference_counter:1;

		/* Access to SINT-related registers (HV_X64_MSR_SCONTROL through
		 * HV_X64_MSR_EOM and HV_X64_MSR_SINT0 through HV_X64_MSR_SINT15).
		 * Corresponds to access_synic_regs privilege.
		 */
		__u64 access_synic_regs:1;

		/* Access to synthetic timers and associated MSRs
		 * (HV_X64_MSR_STIMER0_CONFIG through HV_X64_MSR_STIMER3_COUNT).
		 * Corresponds to access_synthetic_timer_regs privilege.
		 */
		__u64 access_synthetic_timer_regs:1;

		/* Access to APIC MSRs (HV_X64_MSR_EOI, HV_X64_MSR_ICR and HV_X64_MSR_TPR)
		 * as well as the VP assist page.
		 * Corresponds to access_intr_ctrl_regs privilege.
		 */
		__u64 access_intr_ctrl_regs:1;

		/* Access to registers associated with hypercalls (HV_X64_MSR_GUEST_OS_ID
		 * and HV_X64_MSR_HYPERCALL).
		 * Corresponds to access_hypercall_msrs privilege.
		 */
		__u64 access_hypercall_regs:1;

		/* VP index can be queried. corresponds to access_vp_index privilege. */
		__u64 access_vp_index:1;

		/* Access to the reference TSC. Corresponds to access_partition_reference_tsc
		 * privilege.
		 */
		__u64 access_partition_reference_tsc:1;

		/* Partition has access to the guest idle reg. Corresponds to
		 * access_guest_idle_reg privilege.
		 */
		__u64 access_guest_idle_reg:1;

		/* Partition has access to frequency regs. corresponds to access_frequency_regs
		 * privilege.
		 */
		__u64 access_frequency_regs:1;

		__u64 reserved_z12:1; /* Reserved for access_reenlightenment_controls. */
		__u64 reserved_z13:1; /* Reserved for access_root_scheduler_reg. */
		__u64 reserved_z14:1; /* Reserved for access_tsc_invariant_controls. */

		/* Extended GVA ranges for HvCallFlushVirtualAddressList hypercall.
		 * Corresponds to privilege.
		 */
		__u64 enable_extended_gva_ranges_for_flush_virtual_address_list:1;

		__u64 reserved_z16:1; /* Reserved for access_vsm. */
		__u64 reserved_z17:1; /* Reserved for access_vp_registers. */

		/* Use fast hypercall output. Corresponds to privilege. */
		__u64 fast_hypercall_output:1;

		__u64 reserved_z19:1; /* Reserved for enable_extended_hypercalls. */

		/*
		 * HvStartVirtualProcessor can be used to start virtual processors.
		 * Corresponds to privilege.
		 */
		__u64 start_virtual_processor:1;

		__u64 reserved_z21:1; /* Reserved for Isolation. */

		/* Synthetic timers in direct mode. */
		__u64 direct_synthetic_timers:1;

		__u64 reserved_z23:1; /* Reserved for synthetic time unhalted timer */

		/* Use extended processor masks. */
		__u64 extended_processor_masks:1;

		/* HvCallFlushVirtualAddressSpace / HvCallFlushVirtualAddressList are supported. */
		__u64 tb_flush_hypercalls:1;

		/* HvCallSendSyntheticClusterIpi is supported. */
		__u64 synthetic_cluster_ipi:1;

		/* HvCallNotifyLongSpinWait is supported. */
		__u64 notify_long_spin_wait:1;

		/* HvCallQueryNumaDistance is supported. */
		__u64 query_numa_distance:1;

		/* HvCallSignalEvent is supported. Corresponds to privilege. */
		__u64 signal_events:1;

		/* HvCallRetargetDeviceInterrupt is supported. */
		__u64 retarget_device_interrupt:1;

		/* HvCallRestorePartitionTime is supported. */
		__u64 restore_time:1;

		/* EnlightenedVmcs nested enlightenment is supported. */
		__u64 enlightened_vmcs:1;

		__u64 reserved:31;
	} __packed;
};

#define HV_MAKE_COMPATIBILITY_VERSION(major_, minor_)	\
	((__u32)((major_) << 8 | (minor_)))

#define HV_COMPATIBILITY_21_H2		HV_MAKE_COMPATIBILITY_VERSION(0X6, 0X9)

union hv_partition_isolation_properties {
	__u64 as_uint64;
	struct {
		__u64 isolation_type: 5;
		__u64 isolation_host_type : 2;
		__u64 rsvd_z: 5;
		__u64 shared_gpa_boundary_page_number: 52;
	} __packed;
};

/*
 * Various isolation types supported by MSHV.
 */
#define HV_PARTITION_ISOLATION_TYPE_NONE            0
#define HV_PARTITION_ISOLATION_TYPE_SNP             2
#define HV_PARTITION_ISOLATION_TYPE_TDX             3

/*
 * Various host isolation types supported by MSHV.
 */
#define HV_PARTITION_ISOLATION_HOST_TYPE_NONE       0x0
#define HV_PARTITION_ISOLATION_HOST_TYPE_HARDWARE   0x1
#define HV_PARTITION_ISOLATION_HOST_TYPE_RESERVED   0x2

/* Note: Exo partition is enabled by default */
#define HV_PARTITION_CREATION_FLAG_EXO_PARTITION                    (1 << 8)
#define HV_PARTITION_CREATION_FLAG_LAPIC_ENABLED                    (1 << 13)
#define HV_PARTITION_CREATION_FLAG_INTERCEPT_MESSAGE_PAGE_ENABLED   (1 << 19)
#define HV_PARTITION_CREATION_FLAG_X2APIC_CAPABLE                   (1 << 22)

struct hv_input_create_partition {
	__u64 flags;
	struct hv_proximity_domain_info proximity_domain_info;
	__u32 compatibility_version;
	__u32 padding;
	struct hv_partition_creation_properties partition_creation_properties;
	union hv_partition_isolation_properties isolation_properties;
} __packed;

struct hv_output_create_partition {
	__u64 partition_id;
} __packed;

struct hv_input_initialize_partition {
	__u64 partition_id;
} __packed;

struct hv_input_finalize_partition {
	__u64 partition_id;
} __packed;

struct hv_input_delete_partition {
	__u64 partition_id;
} __packed;

struct hv_input_get_partition_property {
	__u64 partition_id;
	__u32 property_code; /* enum hv_partition_property_code */
	__u32 padding;
} __packed;

struct hv_output_get_partition_property {
	__u64 property_value;
} __packed;

struct hv_input_set_partition_property {
	__u64 partition_id;
	__u32 property_code; /* enum hv_partition_property_code */
	__u32 padding;
	__u64 property_value;
} __packed;

enum hv_vp_state_page_type {
	HV_VP_STATE_PAGE_REGISTERS = 0,
	HV_VP_STATE_PAGE_INTERCEPT_MESSAGE = 1,
	HV_VP_STATE_PAGE_COUNT
};

struct hv_input_map_vp_state_page {
	__u64 partition_id;
	__u32 vp_index;
	__u32 type; /* enum hv_vp_state_page_type */
} __packed;

struct hv_output_map_vp_state_page {
	__u64 map_location; /* GPA page number */
} __packed;

struct hv_input_unmap_vp_state_page {
	__u64 partition_id;
	__u32 vp_index;
	__u32 type; /* enum hv_vp_state_page_type */
} __packed;

struct hv_cpuid_leaf_info {
	__u32 eax;
	__u32 ecx;
	__u64 xfem;
	__u64 xss;
} __packed;

union hv_get_vp_cpuid_values_flags {
	__u32 as_uint32;
	struct {
		__u32 use_vp_xfem_xss: 1;
		__u32 apply_registered_values: 1;
		__u32 reserved: 30;
	} __packed;
} __packed;

struct hv_input_get_vp_cpuid_values {
	__u64 partition_id;
	__u32 vp_index;
	union hv_get_vp_cpuid_values_flags flags;
	__u32 reserved;
	__u32 padding;
	struct hv_cpuid_leaf_info cpuid_leaf_info[];
} __packed;

// NOTE: Not in hvhdk headers
union hv_output_get_vp_cpuid_values {
	__u32 as_uint32[4];
	struct {
		__u32 eax;
		__u32 ebx;
		__u32 ecx;
		__u32 edx;
	} __packed;
};

struct hv_x64_apic_eoi_message {
	__u32 vp_index;
	__u32 interrupt_vector;
} __packed;

struct hv_opaque_intercept_message {
	__u32 vp_index;
} __packed;

struct hv_synic_event_flags_page {
	union hv_synic_event_flags event_flags[HV_SYNIC_SINT_COUNT];
};

#define HV_SYNIC_EVENT_RING_MESSAGE_COUNT 63

struct hv_synic_event_ring {
	__u8  signal_masked;
	__u8  ring_full;
	__u16 reserved_z;
	__u32 data[HV_SYNIC_EVENT_RING_MESSAGE_COUNT];
} __packed;

struct hv_synic_event_ring_page {
	struct hv_synic_event_ring sint_event_ring[HV_SYNIC_SINT_COUNT];
};

union hv_synic_sirbp {
	__u64 as_uint64;
	struct {
		__u64 sirbp_enabled:1;
		__u64 preserved:11;
		__u64 base_sirbp_gpa:52;
	} __packed;
};

struct hv_local_interrupt_controller_state {
	/* HV_X64_INTERRUPT_CONTROLLER_STATE */
	__u32 apic_id;
	__u32 apic_version;
	__u32 apic_ldr;
	__u32 apic_dfr;
	__u32 apic_spurious;
	__u32 apic_isr[8];
	__u32 apic_tmr[8];
	__u32 apic_irr[8];
	__u32 apic_esr;
	__u32 apic_icr_high;
	__u32 apic_icr_low;
	__u32 apic_lvt_timer;
	__u32 apic_lvt_thermal;
	__u32 apic_lvt_perfmon;
	__u32 apic_lvt_lint0;
	__u32 apic_lvt_lint1;
	__u32 apic_lvt_error;
	__u32 apic_lvt_cmci;
	__u32 apic_error_status;
	__u32 apic_initial_count;
	__u32 apic_counter_value;
	__u32 apic_divide_configuration;
	__u32 apic_remote_read;
} __packed;

struct hv_stimer_state {
	struct {
		/*
		 * Indicates if there is an undelivered timer expiry message.
		 */
		__u32 undelivered_msg_pending:1;
		__u32 reserved:31;
	} __packed flags;

	__u32 resvd;

	/* Timer configuration and count. */
	__u64 config;
	__u64 count;

	/* Timer adjustment. */
	__u64 adjustment;

	/* Expiration time of the undelivered message. */
	__u64 undelivered_exp_time;
} __packed;

struct hv_synthetic_timers_state {
	struct hv_stimer_state timers[HV_SYNIC_STIMER_COUNT];

	/* Reserved space for time unhalted timer. */
	__u64 reserved[5];
} __packed;

union hv_x64_vp_execution_state {
	__u16 as_uint16;
	struct {
		__u16 cpl:2;
		__u16 cr0_pe:1;
		__u16 cr0_am:1;
		__u16 efer_lma:1;
		__u16 debug_active:1;
		__u16 interruption_pending:1;
		__u16 vtl:4;
		__u16 enclave_mode:1;
		__u16 interrupt_shadow:1;
		__u16 virtualization_fault_active:1;
		__u16 reserved:2;
	} __packed;
};

struct hv_x64_intercept_message_header {
	__u32 vp_index;
	__u8 instruction_length:4;
	__u8 cr8:4; /* Only set for exo partitions */
	__u8 intercept_access_type;
	union hv_x64_vp_execution_state execution_state;
	struct hv_x64_segment_register cs_segment;
	__u64 rip;
	__u64 rflags;
} __packed;

#define HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS 6

struct hv_x64_hypercall_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u64 rax;
	__u64 rbx;
	__u64 rcx;
	__u64 rdx;
	__u64 r8;
	__u64 rsi;
	__u64 rdi;
	struct hv_u128 xmmregisters[HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS];
	struct {
		__u32 isolated:1;
		__u32 reserved:31;
	} __packed;
} __packed;

union hv_x64_register_access_info {
	union hv_register_value source_value;
	__u32 destination_register;
	__u64 source_address;
	__u64 destination_address;
};

struct hv_x64_register_intercept_message {
	struct hv_x64_intercept_message_header header;
	struct {
		__u8 is_memory_op:1;
		__u8 reserved:7;
	} __packed;
	__u8 reserved8;
	__u16 reserved16;
	__u32 register_name;
	union hv_x64_register_access_info access_info;
} __packed;

union hv_x64_memory_access_info {
	__u8 as_uint8;
	struct {
		__u8 gva_valid:1;
		__u8 gva_gpa_valid:1;
		__u8 hypercall_output_pending:1;
		__u8 tlb_locked_no_overlay:1;
		__u8 reserved:4;
	} __packed;
};

union hv_x64_io_port_access_info {
	__u8 as_uint8;
	struct {
		__u8 access_size:3;
		__u8 string_op:1;
		__u8 rep_prefix:1;
		__u8 reserved:3;
	} __packed;
};

union hv_x64_exception_info {
	__u8 as_uint8;
	struct {
		__u8 error_code_valid:1;
		__u8 software_exception:1;
		__u8 reserved:6;
	} __packed;
};

struct hv_x64_memory_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u32 cache_type; /* enum hv_cache_type */
	__u8 instruction_byte_count;
	union hv_x64_memory_access_info memory_access_info;
	__u8 tpr_priority;
	__u8 reserved1;
	__u64 guest_virtual_address;
	__u64 guest_physical_address;
	__u8 instruction_bytes[16];
} __packed;

struct hv_x64_cpuid_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u64 rax;
	__u64 rcx;
	__u64 rdx;
	__u64 rbx;
	__u64 default_result_rax;
	__u64 default_result_rcx;
	__u64 default_result_rdx;
	__u64 default_result_rbx;
} __packed;

struct hv_x64_msr_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u32 msr_number;
	__u32 reserved;
	__u64 rdx;
	__u64 rax;
} __packed;

struct hv_x64_io_port_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u16 port_number;
	union hv_x64_io_port_access_info access_info;
	__u8 instruction_byte_count;
	__u32 reserved;
	__u64 rax;
	__u8 instruction_bytes[16];
	struct hv_x64_segment_register ds_segment;
	struct hv_x64_segment_register es_segment;
	__u64 rcx;
	__u64 rsi;
	__u64 rdi;
} __packed;

struct hv_x64_exception_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u16 exception_vector;
	union hv_x64_exception_info exception_info;
	__u8 instruction_byte_count;
	__u32 error_code;
	__u64 exception_parameter;
	__u64 reserved;
	__u8 instruction_bytes[16];
	struct hv_x64_segment_register ds_segment;
	struct hv_x64_segment_register ss_segment;
	__u64 rax;
	__u64 rcx;
	__u64 rdx;
	__u64 rbx;
	__u64 rsp;
	__u64 rbp;
	__u64 rsi;
	__u64 rdi;
	__u64 r8;
	__u64 r9;
	__u64 r10;
	__u64 r11;
	__u64 r12;
	__u64 r13;
	__u64 r14;
	__u64 r15;
} __packed;

struct hv_x64_invalid_vp_register_message {
	__u32 vp_index;
	__u32 reserved;
} __packed;

struct hv_x64_unrecoverable_exception_message {
	struct hv_x64_intercept_message_header header;
} __packed;

#define HV_UNSUPPORTED_FEATURE_INTERCEPT	1
#define HV_UNSUPPORTED_FEATURE_TASK_SWITCH_TSS	2

struct hv_x64_unsupported_feature_message {
	__u32 vp_index;
	__u32 feature_code;
	__u64 feature_parameter;
} __packed;

struct hv_x64_halt_message {
	struct hv_x64_intercept_message_header header;
} __packed;

#define HV_X64_PENDING_INTERRUPT	0
#define HV_X64_PENDING_NMI		2
#define HV_X64_PENDING_EXCEPTION	3

struct hv_x64_interruption_deliverable_message {
	struct hv_x64_intercept_message_header header;
	__u32 deliverable_type; /* pending interruption type */
	__u32 rsvd;
} __packed;

struct hv_x64_sint_deliverable_message {
	struct hv_x64_intercept_message_header header;
	__u16 deliverable_sints;
	__u16 rsvd1;
	__u32 rsvd2;
} __packed;

struct hv_x64_sipi_intercept_message {
	struct hv_x64_intercept_message_header header;
	__u32 target_vp_index;
	__u32 interrupt_vector;
} __packed;

struct hv_register_x64_cpuid_result_parameters {
	struct {
		__u32 eax;
		__u32 ecx;
		__u8 subleaf_specific;
		__u8 always_override;
		__u16 padding;
	} __packed input;
	struct {
		__u32 eax;
		__u32 eax_mask;
		__u32 ebx;
		__u32 ebx_mask;
		__u32 ecx;
		__u32 ecx_mask;
		__u32 edx;
		__u32 edx_mask;
	} __packed result;
} __packed;

struct hv_register_x64_msr_result_parameters {
	__u32 msr_index;
	__u32 access_type;
	__u32 action; /* enum hv_unimplemented_msr_action */
} __packed;

union hv_register_intercept_result_parameters {
	struct hv_register_x64_cpuid_result_parameters cpuid;
	struct hv_register_x64_msr_result_parameters msr;
} __packed;

struct hv_async_completion_message_payload {
	__u64 partition_id;
	__u32 status;
	__u32 completion_count;
	__u64 sub_status;
} __packed;

enum hv_cache_type {
	HV_CACHE_TYPE_UNCACHED		= 0,
	HV_CACHE_TYPE_WRITE_COMBINING	= 1,
	HV_CACHE_TYPE_WRITE_THROUGH	= 4,
	HV_CACHE_TYPE_WRITE_PROTECTED	= 5,
	HV_CACHE_TYPE_WRITE_BACK	= 6,
};

#define HV_SUPPORTS_REGISTER_INTERCEPT

struct hv_input_register_intercept_result {
	__u64 partition_id;
	__u32 vp_index;
	__u32 intercept_type; /* enum hv_intercept_type */
	union hv_register_intercept_result_parameters parameters;
} __packed;

struct hv_input_create_port {
	__u64 port_partition_id;
	union hv_port_id port_id;
	__u8 port_vtl;
	__u8 min_connection_vtl;
	__u16 padding;
	__u64 connection_partition_id;
	struct hv_port_info port_info;
	struct hv_proximity_domain_info proximity_domain_info;
} __packed;

union hv_input_delete_port {
	__u64 as_uint64[2];
	struct {
		__u64 port_partition_id;
		union hv_port_id port_id;
		__u32 reserved;
	};
} __packed;

struct hv_input_connect_port {
	__u64 connection_partition_id;
	union hv_connection_id connection_id;
	__u8 connection_vtl;
	__u8 rsvdz0;
	__u16 rsvdz1;
	__u64 port_partition_id;
	union hv_port_id port_id;
	__u32 reserved2;
	struct hv_connection_info connection_info;
	struct hv_proximity_domain_info proximity_domain_info;
} __packed;

union hv_input_disconnect_port {
	__u64 as_uint64[2];
	struct {
		__u64 connection_partition_id;
		union hv_connection_id connection_id;
		__u32 is_doorbell: 1;
		__u32 reserved: 31;
	} __packed;
} __packed;

union hv_input_notify_port_ring_empty {
	__u64 as_uint64;
	struct {
		__u32 sint_index;
		__u32 reserved;
	};
} __packed;

struct hv_input_signal_event_direct {
	__u64 target_partition;
	__u32 target_vp;
	__u8  target_vtl;
	__u8  target_sint;
	__u16 flag_number;
} __packed;

struct hv_output_signal_event_direct {
	__u8	newly_signaled;
	__u8	reserved[7];
} __packed;

struct hv_input_post_message_direct {
	__u64 partition_id;
	__u32 vp_index;
	__u8  vtl;
	__u8  padding[3];
	__u32 sint_index;
	__u8  message[HV_MESSAGE_SIZE];
	__u32 padding2;
} __packed;

struct hv_guest_mapping_flush_list { /* HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST */
	u64 address_space;
	u64 flags;
	union hv_gpa_page_range gpa_list[];
};

#define HV_SUPPORTS_VP_STATE

struct hv_vp_state_data_xsave {
	__u64 flags;
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

enum hv_get_set_vp_state_type {
	HV_GET_SET_VP_STATE_LOCAL_INTERRUPT_CONTROLLER_STATE = 0 | HV_GET_SET_VP_STATE_TYPE_PFN,

	HV_GET_SET_VP_STATE_XSAVE		= 1 | HV_GET_SET_VP_STATE_TYPE_PFN,
	/* Synthetic message page */
	HV_GET_SET_VP_STATE_SIM_PAGE		= 2 | HV_GET_SET_VP_STATE_TYPE_PFN,
	/* Synthetic interrupt event flags page. */
	HV_GET_SET_VP_STATE_SIEF_PAGE		= 3 | HV_GET_SET_VP_STATE_TYPE_PFN,

	/* Synthetic timers. */
	HV_GET_SET_VP_STATE_SYNTHETIC_TIMERS	= 4,
};

struct hv_vp_state_data {
	__u32 type;
	__u32 rsvd;
	struct hv_vp_state_data_xsave xsave;
} __packed;

struct hv_input_get_vp_state {
	__u64 partition_id;
	__u32 vp_index;
	__u8 input_vtl;
	__u8 rsvd0;
	__u16 rsvd1;
	struct hv_vp_state_data state_data;
	__u64 output_data_pfns[];
} __packed;

union hv_output_get_vp_state {
	struct hv_local_interrupt_controller_state interrupt_controller_state;
	struct hv_synthetic_timers_state synthetic_timers_state;
} __packed;

union hv_input_set_vp_state_data {
	__u64 pfns;
	__u8 bytes;
} __packed;

struct hv_input_set_vp_state {
	__u64 partition_id;
	__u32 vp_index;
	__u8 input_vtl;
	__u8 rsvd0;
	__u16 rsvd1;
	struct hv_vp_state_data state_data;
	union hv_input_set_vp_state_data data[];
} __packed;

/*
 * Dispatch state for the VP communicated by the hypervisor to the
 * VP-dispatching thread in the root on return from HVCALL_DISPATCH_VP.
 */
enum hv_vp_dispatch_state {
	HV_VP_DISPATCH_STATE_INVALID = 0,
	HV_VP_DISPATCH_STATE_BLOCKED = 1,
	HV_VP_DISPATCH_STATE_READY = 2,
};

/*
 * Dispatch event that caused the current dispatch state on return from
 * HVCALL_DISPATCH_VP.
 */
enum hv_vp_dispatch_event {
	HV_VP_DISPATCH_EVENT_INVALID =	0x00000000,
	HV_VP_DISPATCH_EVENT_SUSPEND = 0x00000001,
	HV_VP_DISPATCH_EVENT_INTERCEPT = 0x00000002,
};

#define HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION   1024
/* The maximum array size of HV_GENERIC_SET (vp_set) buffer */
#define HV_GENERIC_SET_QWORD_COUNT(max) (((((max) - 1) >> 6) + 1) + 2)

struct hv_vp_signal_bitset_scheduler_message {
	__u64 partition_id;
	__u32 overflow_count;
	__u16 vp_count;
	__u16 reserved;

#define BITSET_BUFFER_SIZE \
	HV_GENERIC_SET_QWORD_COUNT(HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION)
	union {
		struct hv_vpset bitset;
		__u64 bitset_buffer[BITSET_BUFFER_SIZE];
	} vp_bitset;
#undef BITSET_BUFFER_SIZE
} __packed;

#if defined(__KERNEL__)
static_assert(sizeof(struct hv_vp_signal_bitset_scheduler_message) <=
	(sizeof(struct hv_message) - sizeof(struct hv_message_header)));
#endif

#define HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT \
	(((sizeof(struct hv_message) - sizeof(struct hv_message_header)) / \
	 (sizeof(__u64 /* partition id */) + sizeof(__u32 /* vp index */))) - 1)

struct hv_vp_signal_pair_scheduler_message {
	__u32 overflow_count;
	__u8 vp_count;
	__u8 reserved1[3];

	__u64 partition_ids[HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT];
	__u32 vp_indexes[HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT];

	__u8 reserved2[4];
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

struct hv_input_dispatch_vp {
	__u64 partition_id;
	__u32 vp_index;
	__u32 flags;
	__u64 time_slice; /* in 100ns */
	__u64 spec_ctrl;
} __packed;

struct hv_output_dispatch_vp {
	__u32 dispatch_state; /* enum hv_vp_dispatch_state */
	__u32 dispatch_event; /* enum hv_vp_dispatch_event */
} __packed;

#endif /* _UAPI_HV_HVHDK_H */
