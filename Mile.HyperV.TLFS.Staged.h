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

#endif /* !MILE_HYPERV_TLFS_STAGED */
