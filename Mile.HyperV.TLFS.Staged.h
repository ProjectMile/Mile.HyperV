/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.TLFS.Staged.h
 * PURPOSE:   Definition for Hyper-V Top Level Functional Specification 6.0b
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef MILE_HYPERV_TLFS_STAGED
#define MILE_HYPERV_TLFS_STAGED

/* Staged (unused) definitions of Mile.HyperV.TLFS */

#include "Mile.HyperV.TLFS.h"

/*
 * Microsoft Hypervisor CPUID Leaves
 */

#define HV_CPUID_FUNCTION_MS_HV_CPU_MANAGEMENT_FEATURES 0x40000007
#define HV_CPUID_FUNCTION_MS_HV_SVM_FEATURES 0x40000008
#define HV_CPUID_FUNCTION_MS_HV_NESTED_FEATURES 0x40000009
#define HV_CPUID_FUNCTION_MS_HV_NESTED_VIRTUALIZATION_FEATURES 0x4000000A

typedef struct _HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES
{
    /* EAX */

    HV_UINT32 StartLogicalProcessor : 1;
    HV_UINT32 CreateRootVirtualProcessor : 1;
    HV_UINT32 PerformanceCounterSync : 1;
    HV_UINT32 Reserved1 : 28;
    HV_UINT32 ReservedIdentityBit : 1;

    /* EBX */

    HV_UINT32 ProcessorPowerManagement : 1;
    HV_UINT32 MwaitIdleStates : 1;
    HV_UINT32 LogicalProcessorIdling : 1;
    HV_UINT32 Reserved2 : 29;

    /* ECX */

    HV_UINT32 RemapGuestUncached : 1;
    HV_UINT32 Reserved3 : 31;

    /* EDX */

    HV_UINT32 Reserved4;

} HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES, *PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES;

typedef struct _HV_HYPERVISOR_SVM_FEATURES
{
    /* EAX */

    HV_UINT32 SvmSupported : 1;
    HV_UINT32 Reserved1 : 10;
    HV_UINT32 MaxPasidSpacePasidCount : 21;

    /* EBX, ECX, EDX */

    HV_UINT32 Reserved2[3];

} HV_HYPERVISOR_SVM_FEATURES, *PHV_HYPERVISOR_SVM_FEATURES;

typedef struct _HV_HYPERVISOR_NESTED_FEATURES
{
    /* EAX */

    HV_UINT32 Reserved1 : 2;
    HV_UINT32 AccessSynicRegs : 1;
    HV_UINT32 Reserved2 : 1;
    HV_UINT32 AccessIntrCtrlRegs : 1;
    HV_UINT32 AccessHypercallMsrs : 1;
    HV_UINT32 AccessVpIndex : 1;
    HV_UINT32 Reserved3 : 5;
    HV_UINT32 AccessReenlightenmentControls : 1;
    HV_UINT32 Reserved4 : 19;

    /* EBX, ECX */

    HV_UINT32 Reserved5[2];

    /* EDX */

    HV_UINT32 Reserved6 : 4;
    HV_UINT32 XmmRegistersForFastHypercallAvailable : 1;
    HV_UINT32 Reserved7 : 10;
    HV_UINT32 FastHypercallOutputAvailable : 1;
    HV_UINT32 Reserved8 : 1;
    HV_UINT32 SintPollingModeAvailable : 1;
    HV_UINT32 Reserved9 : 14;

} HV_HYPERVISOR_NESTED_FEATURES, *PHV_HYPERVISOR_NESTED_FEATURES;

typedef struct _HV_HYPERVISOR_NESTED_VIRTUALIZATION_FEATURES
{
    /* EAX */

    HV_UINT32 EnlightenedVmcsVersionLow : 8;
    HV_UINT32 EnlightenedVmcsVersionHigh : 8;
    HV_UINT32 Reserved1 : 1;
    HV_UINT32 NestedFlushVirtualHypercall : 1;
    HV_UINT32 FlushGuestPhysicalHypercall : 1;
    HV_UINT32 MsrBitmap : 1;
    HV_UINT32 VirtualizationException : 1;
    HV_UINT32 Reserved2 : 11;

    /* EBX, ECX, EDX */

    HV_UINT32 Reserved3[3];

} HV_HYPERVISOR_NESTED_VIRTUALIZATION_FEATURES, *PHV_HYPERVISOR_NESTED_VIRTUALIZATION_FEATURES;

/*
 * Hypercall Code
 */

/* Detailed definitions in TLS, but Nested Virtualization only */

#define HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE 0x00AF
#define HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST 0x00B0

/* Defined Hypercall ID in TLFS, but have no detailed definitions */

#define HVCALL_CREATE_PARTITION 0x0040
#define HVCALL_GET_PARTITION_ID 0x0046
#define HVCALL_POST_DEBUG_DATA 0x0069
#define HVCALL_RETRIEVE_DEBUG_DATA 0x006A
#define HVCALL_RESET_DEBUG_SESSION 0x006B
#define HVCALL_GET_SYSTEM_PROPERTY 0x007B

/* Defined Hypercall ID in TLFS, but Parent / Root Partition only */

#define HVCALL_INITIALIZE_PARTITION 0x0041
#define HVCALL_FINALIZE_PARTITION 0x0042
#define HVCALL_DELETE_PARTITION 0x0043
#define HVCALL_GET_PARTITION_PROPERTY 0x0044
#define HVCALL_SET_PARTITION_PROPERTY 0x0045
#define HVCALL_DEPOSIT_MEMORY 0x0048
#define HVCALL_WITHDRAW_MEMORY 0x0049
#define HVCALL_MAP_GPA_PAGES 0x004B
#define HVCALL_UNMAP_GPA_PAGES 0x004C
#define HVCALL_INSTALL_INTERCEPT 0x004D
#define HVCALL_CREATE_VP 0x004E
#define HVCALL_CLEAR_VIRTUAL_INTERRUPT 0x0056
#define HVCALL_DELETE_PORT 0x0058
#define HVCALL_DISCONNECT_PORT 0x005B
#define HVCALL_ADD_LOGICAL_PROCESSOR 0x0076
#define HVCALL_MAP_DEVICE_INTERRUPT 0x007C
#define HVCALL_UNMAP_DEVICE_INTERRUPT 0x007D
#define HVCALL_NOTIFY_PORT_RING_EMPTY 0x008B
#define HVCALL_REGISTER_INTERCEPT_RESULT 0x0091
#define HVCALL_CREATE_PORT 0x0095
#define HVCALL_CONNECT_PORT 0x0096

/* Not even defined Hypercall ID in TLFS */

#define HVCALL_SIGNAL_EVENT_DIRECT 0x00C0
#define HVCALL_POST_MESSAGE_DIRECT 0x00C1
#define HVCALL_DISPATCH_VP 0x00C2
#define HVCALL_GET_GPA_PAGES_ACCESS_STATES 0x00C9
#define HVCALL_MAP_VP_STATE_PAGE 0x00E1
#define HVCALL_UNMAP_VP_STATE_PAGE 0x00E2
#define HVCALL_GET_VP_STATE 0x00E3
#define HVCALL_SET_VP_STATE 0x00E4
#define HVCALL_GET_VP_CPUID_VALUES 0x00F4

#endif /* !MILE_HYPERV_TLFS_STAGED */
