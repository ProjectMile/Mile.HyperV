/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.TLFS.h
 * PURPOSE:   Definition for Hyper-V Top Level Functional Specification 6.0b
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef MILE_HYPERV_TLFS
#define MILE_HYPERV_TLFS

#include <stdint.h>

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif
/* nonstandard extension used : nameless struct/union */
#pragma warning(disable:4201)
#endif

#ifndef DECLSPEC_ALIGN
#if (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#define DECLSPEC_ALIGN(x)   __declspec(align(x))
#else
#define DECLSPEC_ALIGN(x)
#endif
#endif

/*
 * Simple Scalar Types
 */

typedef int8_t HV_INT8, *PHV_INT8;
typedef int16_t HV_INT16, *PHV_INT16;
typedef int32_t HV_INT32, *PHV_INT32;
typedef int64_t HV_INT64, *PHV_INT64;

typedef uint8_t HV_UINT8, *PHV_UINT8;
typedef uint16_t HV_UINT16, *PHV_UINT16;
typedef uint32_t HV_UINT32, *PHV_UINT32;
typedef uint64_t HV_UINT64, *PHV_UINT64;

typedef struct DECLSPEC_ALIGN(16) _HV_UINT128
{
    HV_UINT64 LowPart;
    HV_UINT64 HighPart;
} HV_UINT128, *PHV_UINT128;

/*
 * Hypercall Status Code
 */

typedef HV_UINT16 HV_STATUS;

#define HV_STATUS_SUCCESS ((HV_STATUS)0x0000)
#define HV_STATUS_INVALID_HYPERCALL_CODE ((HV_STATUS)0x0002)
#define HV_STATUS_INVALID_HYPERCALL_INPUT ((HV_STATUS)0x0003)
#define HV_STATUS_INVALID_ALIGNMENT ((HV_STATUS)0x0004)
#define HV_STATUS_INVALID_PARAMETER ((HV_STATUS)0x0005)
#define HV_STATUS_ACCESS_DENIED ((HV_STATUS)0x0006)
#define HV_STATUS_INVALID_PARTITION_STATE ((HV_STATUS)0x0007)
#define HV_STATUS_OPERATION_DENIED ((HV_STATUS)0x0008)
#define HV_STATUS_UNKNOWN_PROPERTY ((HV_STATUS)0x0009)
#define HV_STATUS_PROPERTY_VALUE_OUT_OF_RANGE ((HV_STATUS)0x000A)
#define HV_STATUS_INSUFFICIENT_MEMORY ((HV_STATUS)0x000B)
#define HV_STATUS_PARTITION_TOO_DEEP ((HV_STATUS)0x000C)
#define HV_STATUS_INVALID_PARTITION_ID ((HV_STATUS)0x000D)
#define HV_STATUS_INVALID_VP_INDEX ((HV_STATUS)0x000E)
#define HV_STATUS_NOT_FOUND ((HV_STATUS)0x0010)
#define HV_STATUS_INVALID_PORT_ID ((HV_STATUS)0x0011)
#define HV_STATUS_INVALID_CONNECTION_ID ((HV_STATUS)0x0012)
#define HV_STATUS_INSUFFICIENT_BUFFERS ((HV_STATUS)0x0013)
#define HV_STATUS_NOT_ACKNOWLEDGED ((HV_STATUS)0x0014)
#define HV_STATUS_INVALID_VP_STATE ((HV_STATUS)0x0015)
#define HV_STATUS_ACKNOWLEDGED ((HV_STATUS)0x0016)
#define HV_STATUS_INVALID_SAVE_RESTORE_STATE ((HV_STATUS)0x0017)
#define HV_STATUS_INVALID_SYNIC_STATE ((HV_STATUS)0x0018)
#define HV_STATUS_OBJECT_IN_USE ((HV_STATUS)0x0019)
#define HV_STATUS_INVALID_PROXIMITY_DOMAIN_INFO ((HV_STATUS)0x001A)
#define HV_STATUS_NO_DATA ((HV_STATUS)0x001B)
#define HV_STATUS_INACTIVE ((HV_STATUS)0x001C)
#define HV_STATUS_NO_RESOURCES ((HV_STATUS)0x001D)
#define HV_STATUS_FEATURE_UNAVAILABLE ((HV_STATUS)0x001E)
#define HV_STATUS_PARTIAL_PACKET ((HV_STATUS)0x001F)
#define HV_STATUS_PROCESSOR_FEATURE_NOT_SUPPORTED ((HV_STATUS)0x0020)
#define HV_STATUS_PROCESSOR_CACHE_LINE_FLUSH_SIZE_INCOMPATIBLE ((HV_STATUS)0x0030)
#define HV_STATUS_INSUFFICIENT_BUFFER ((HV_STATUS)0x0033)
#define HV_STATUS_INCOMPATIBLE_PROCESSOR ((HV_STATUS)0x0037)
#define HV_STATUS_INSUFFICIENT_DEVICE_DOMAINS ((HV_STATUS)0x0038)
#define HV_STATUS_CPUID_FEATURE_VALIDATION_ERROR ((HV_STATUS)0x003C)
#define HV_STATUS_CPUID_XSAVE_FEATURE_VALIDATION_ERROR ((HV_STATUS)0x003D)
#define HV_STATUS_PROCESSOR_STARTUP_TIMEOUT ((HV_STATUS)0x003E)
#define HV_STATUS_SMX_ENABLED ((HV_STATUS)0x003F)
#define HV_STATUS_INVALID_LP_INDEX ((HV_STATUS)0x0041)
#define HV_STATUS_INVALID_REGISTER_VALUE ((HV_STATUS)0x0050)
#define HV_STATUS_INVALID_VTL_STATE ((HV_STATUS)0x0051)
#define HV_STATUS_NX_NOT_DETECTED ((HV_STATUS)0x0055)
#define HV_STATUS_INVALID_DEVICE_ID ((HV_STATUS)0x0057)
#define HV_STATUS_INVALID_DEVICE_STATE ((HV_STATUS)0x0058)
#define HV_STATUS_PENDING_PAGE_REQUESTS ((HV_STATUS)0x0059)
#define HV_STATUS_PAGE_REQUEST_INVALID ((HV_STATUS)0x0060)
#define HV_STATUS_KEY_ALREADY_EXISTS ((HV_STATUS)0x0065)
#define HV_STATUS_DEVICE_ALREADY_IN_DOMAIN ((HV_STATUS)0x0066)
#define HV_STATUS_INVALID_CPU_GROUP_ID ((HV_STATUS)0x006F)
#define HV_STATUS_INVALID_CPU_GROUP_STATE ((HV_STATUS)0x0070)
#define HV_STATUS_OPERATION_FAILED ((HV_STATUS)0x0071)
#define HV_STATUS_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE ((HV_STATUS)0x0072)
#define HV_STATUS_INSUFFICIENT_ROOT_MEMORY ((HV_STATUS)0x0073)
#define HV_STATUS_EVENT_BUFFER_ALREADY_FREED ((HV_STATUS)0x0074)
#define HV_STATUS_CALL_PENDING ((HV_STATUS)0x0079)
#define HV_STATUS_VTL_ALREADY_ENABLED ((HV_STATUS)0x0086)

/*
 * Memory Address Space Types
 */

typedef HV_UINT64 HV_SPA;
typedef HV_UINT64 HV_GPA;
typedef HV_UINT64 HV_GVA;
typedef HV_SPA* PHV_SPA;
typedef HV_GPA* PHV_GPA;
typedef HV_GVA* PHV_GVA;
typedef const HV_SPA* PCHV_SPA;
typedef const HV_GPA* PCHV_GPA;
typedef const HV_GVA* PCHV_GVA;

typedef HV_UINT64 HV_SPA_PAGE_NUMBER;
typedef HV_UINT64 HV_GPA_PAGE_NUMBER;
typedef HV_UINT64 HV_GVA_PAGE_NUMBER;
typedef HV_SPA_PAGE_NUMBER* PHV_SPA_PAGE_NUMBER;
typedef HV_GPA_PAGE_NUMBER* PHV_GPA_PAGE_NUMBER;
typedef HV_GVA_PAGE_NUMBER* PHV_GVA_PAGE_NUMBER;
typedef const HV_SPA_PAGE_NUMBER* PCHV_SPA_PAGE_NUMBER;
typedef const HV_GPA_PAGE_NUMBER* PCHV_GPA_PAGE_NUMBER;
typedef const HV_GVA_PAGE_NUMBER* PCHV_GVA_PAGE_NUMBER;

typedef HV_UINT32 HV_SPA_PAGE_OFFSET;

/* 5-level paging enabled */
#define X64_CR4_LA57 0x0000000000001000

#define X64_PTE_PRESENT 0x1
#define X64_PTE_READ_WRITE 0x2
#define X64_PTE_ACCESSED 0x20
#define X64_PTE_DIRTY 0x40
#define X64_PTE_LARGE_PAGE 0x80

#define PAGE_TABLE_ENTRY_COUNT 512

#define X64_PAGE_SHIFT 12
#define X64_PTE_BITS 9

/* Number of bytes in a page for X64. */
#define X64_PAGE_SIZE 0x1000
/* Number of bytes in a large page for X64. */
#define X64_LARGE_PAGE_SIZE 0x200000
/* Number of bytes in a 1GB page for X64. */
#define X64_1GB_PAGE_SIZE 0x40000000

#define HV_X64_MAX_PAGE_NUMBER (UINT64_MAX/X64_PAGE_SIZE)
#define HV_X64_MAX_LARGE_PAGE_NUMBER (UINT64_MAX/X64_LARGE_PAGE_SIZE)
#define HV_X64_MAX_1GB_PAGE_NUMBER (UINT64_MAX/X64_1GB_PAGE_SIZE)

#define HV_PAGE_SIZE X64_PAGE_SIZE
#define HV_LARGE_PAGE_SIZE X64_LARGE_PAGE_SIZE
#define HV_1GB_PAGE_SIZE X64_1GB_PAGE_SIZE

#define HV_PAGE_MASK (HV_PAGE_SIZE - 1)
#define HV_LARGE_PAGE_MASK (HV_LARGE_PAGE_SIZE - 1)
#define HV_1GB_PAGE_MASK (HV_1GB_PAGE_SIZE - 1)

/*
 * Partition Management Data Types
 */

typedef HV_UINT64 HV_PARTITION_ID;
typedef HV_PARTITION_ID *PHV_PARTITION_ID;
typedef const HV_PARTITION_ID* PCHV_PARTITION_ID;

#define HV_PARTITION_ID_INVALID ((HV_PARTITION_ID)0x0)
#define HV_PARTITION_ID_SELF ((HV_PARTITION_ID)-1)

typedef union _HV_PARTITION_PRIVILEGE_MASK
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT64 AccessVpRunTimeMsr : 1;
        HV_UINT64 AccessPartitionReferenceCounter : 1;
        HV_UINT64 AccessSynicMsrs : 1;
        HV_UINT64 AccessSyntheticTimerMsrs : 1;
        HV_UINT64 AccessApicMsrs : 1;
        HV_UINT64 AccessHypercallMsrs : 1;
        HV_UINT64 AccessVpIndex : 1;
        HV_UINT64 AccessResetMsr : 1;
        HV_UINT64 AccessStatsMsr : 1;
        HV_UINT64 AccessPartitionReferenceTsc : 1;
        HV_UINT64 AccessGuestIdleMsr : 1;
        HV_UINT64 AccessFrequencyMsrs : 1;
        HV_UINT64 AccessDebugMsrs : 1;
        HV_UINT64 AccessReenlightenmentControls : 1;
        HV_UINT64 AccessRootSchedulerMsr : 1;
        HV_UINT64 Reserved1 : 17;
        HV_UINT64 CreatePartitions : 1;
        HV_UINT64 AccessPartitionId : 1;
        HV_UINT64 AccessMemoryPool : 1;
        HV_UINT64 AdjustMessageBuffers : 1;
        HV_UINT64 PostMessages : 1;
        HV_UINT64 SignalEvents : 1;
        HV_UINT64 CreatePort : 1;
        HV_UINT64 ConnectPort : 1;
        HV_UINT64 AccessStats : 1;
        HV_UINT64 Reserved2 : 2;
        HV_UINT64 Debugging : 1;
        HV_UINT64 CpuManagement : 1;
        HV_UINT64 ConfigureProfiler : 1;
        HV_UINT64 AccessVpExitTracing : 1;
        HV_UINT64 EnableExtendedGvaRangesFlushVaList : 1;
        HV_UINT64 AccessVsm : 1;
        HV_UINT64 AccessVpRegisters : 1;
        HV_UINT64 Reserved3 : 1;
        HV_UINT64 FastHypercallOutput : 1;
        HV_UINT64 EnableExtendedHypercalls : 1;
        HV_UINT64 StartVirtualProcessor : 1;
        HV_UINT64 PrivilegeIsolation : 1;
        HV_UINT64 Reserved4 : 9;
    };
} HV_PARTITION_PRIVILEGE_MASK, *PHV_PARTITION_PRIVILEGE_MASK;

/*
 * Microsoft Hypervisor CPUID Leaves
 */

typedef enum _HV_CPUID_FUNCTION
{
    HvCpuIdFunctionVersionAndFeatures = 0x00000001,
    HvCpuIdFunctionHvVendorAndMaxFunction = 0x40000000,
    HvCpuIdFunctionHvInterface = 0x40000001,
    HvCpuIdFunctionMsHvVersion = 0x40000002,
    HvCpuIdFunctionMsHvFeatures = 0x40000003,
    HvCpuIdFunctionMsHvEnlightenmentInformation = 0x40000004,
    HvCpuIdFunctionMsHvImplementationLimits = 0x40000005,
    HvCpuIdFunctionMsHvHardwareFeatures = 0x40000006,
    HvCpuIdFunctionMaxReserved = 0x40000006
} HV_CPUID_FUNCTION, *PHV_CPUID_FUNCTION;

#define HV_CPUID_HV_VENDOR_MICROSOFT "Microsoft Hv"
#define HV_CPUID_HV_VENDOR_MICROSOFT_EBX 'rciM'
#define HV_CPUID_HV_VENDOR_MICROSOFT_ECX 'foso'
#define HV_CPUID_HV_VENDOR_MICROSOFT_EDX 'vH t'

typedef struct _HV_VENDOR_AND_MAX_FUNCTION
{
    HV_UINT32 MaxFunction;
    HV_UINT8 VendorName[12];
} HV_VENDOR_AND_MAX_FUNCTION, *PHV_VENDOR_AND_MAX_FUNCTION;

typedef enum _HV_HYPERVISOR_INTERFACE
{
    HvMicrosoftHypervisorInterface = '1#vH',
    HvMicrosoftXboxNanovisorInterface = 'vnbX'
} HV_HYPERVISOR_INTERFACE, *PHV_HYPERVISOR_INTERFACE;

typedef struct _HV_HYPERVISOR_INTERFACE_INFO
{
    HV_UINT32 Interface;
    HV_UINT32 ReservedEbx;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_HYPERVISOR_INTERFACE_INFO, *PHV_HYPERVISOR_INTERFACE_INFO;

typedef struct _HV_HYPERVISOR_VERSION_INFO
{
    HV_UINT32 BuildNumber;
    HV_UINT32 MinorVersion : 16;
    HV_UINT32 MajorVersion : 16;
    HV_UINT32 ServicePack;
    HV_UINT32 ServiceNumber : 24;
    HV_UINT32 ServiceBranch : 8;
} HV_HYPERVISOR_VERSION_INFO, *PHV_HYPERVISOR_VERSION_INFO;

typedef struct _HV_X64_HYPERVISOR_FEATURES
{
    HV_PARTITION_PRIVILEGE_MASK PartitionPrivileges;
    HV_UINT32 MaxSupportedCState : 4;
    HV_UINT32 Reserved : 28;
    HV_UINT32 MwaitAvailableDeprecated : 1;
    HV_UINT32 GuestDebuggingAvailable : 1;
    HV_UINT32 PerformanceMonitorsAvailable : 1;
    HV_UINT32 CpuDynamicPartitioningAvailable : 1;
    HV_UINT32 XmmRegistersForFastHypercallAvailable : 1;
    HV_UINT32 GuestIdleAvailable : 1;
    HV_UINT32 HypervisorSleepStateSupportAvailable : 1;
    HV_UINT32 NumaDistanceQueryAvailable : 1;
    HV_UINT32 FrequencyRegsAvailable : 1;
    HV_UINT32 SyntheticMachineCheckAvailable : 1;
    HV_UINT32 GuestCrashRegsAvailable : 1;
    HV_UINT32 DebugRegsAvailable : 1;
    HV_UINT32 Npiep1Available : 1;
    HV_UINT32 DisableHypervisorAvailable : 1;
    HV_UINT32 ExtendedGvaRangesForFlushVirtualAddressListAvailable : 1;
    HV_UINT32 FastHypercallOutputAvailable : 1;
    HV_UINT32 SvmFeaturesAvailable : 1;
    HV_UINT32 SintPollingModeAvailable : 1;
    HV_UINT32 HypercallMsrLockAvailable : 1;
    HV_UINT32 DirectSyntheticTimers : 1;
    HV_UINT32 RegisterPatAvailable : 1;
    HV_UINT32 RegisterBndcfgsAvailable : 1;
    HV_UINT32 WatchdogTimerAvailable : 1;
    HV_UINT32 SyntheticTimeUnhaltedTimerAvailable : 1;
    HV_UINT32 DeviceDomainsAvailable : 1; /* HDK only. */
    HV_UINT32 S1DeviceDomainsAvailable : 1; /* HDK only. */
    HV_UINT32 LbrAvailable : 1;
    HV_UINT32 IptAvailable : 1;
    HV_UINT32 CrossVtlFlushAvailable : 1;
    HV_UINT32 Reserved1 : 3;
} HV_X64_HYPERVISOR_FEATURES, *PHV_X64_HYPERVISOR_FEATURES;

typedef struct _HV_X64_ENLIGHTENMENT_INFORMATION
{
    HV_UINT32 UseHypercallForAddressSpaceSwitch : 1;
    HV_UINT32 UseHypercallForLocalFlush : 1;
    HV_UINT32 UseHypercallForRemoteFlushAndLocalFlushEntire : 1;
    HV_UINT32 UseApicMsrs : 1;
    HV_UINT32 UseHvRegisterForReset : 1;
    HV_UINT32 UseRelaxedTiming : 1;
    HV_UINT32 UseDmaRemappingDeprecated : 1;
    HV_UINT32 UseInterruptRemappingDeprecated : 1;
    HV_UINT32 UseX2ApicMsrs : 1;
    HV_UINT32 DeprecateAutoEoi : 1;
    HV_UINT32 UseSyntheticClusterIpi : 1;
    HV_UINT32 UseExProcessorMasks : 1;
    HV_UINT32 Nested : 1;
    HV_UINT32 UseIntForMbecSystemCalls : 1;
    HV_UINT32 UseVmcsEnlightenments : 1;
    HV_UINT32 UseSyncedTimeline : 1;
    HV_UINT32 CoreSchedulerRequested : 1;
    HV_UINT32 UseDirectLocalFlushEntire : 1;
    HV_UINT32 NoNonArchitecturalCoreSharing : 1;
    HV_UINT32 Reserved : 13;
    HV_UINT32 LongSpinWaitCount;
    HV_UINT32 ImplementedPhysicalAddressBits : 7;
    HV_UINT32 Reserved1 : 25;
    HV_UINT32 ReservedEdx;
} HV_X64_ENLIGHTENMENT_INFORMATION, *PHV_X64_ENLIGHTENMENT_INFORMATION;

typedef struct _HV_IMPLEMENTATION_LIMITS
{
    HV_UINT32 MaxVirtualProcessorCount;
    HV_UINT32 MaxLogicalProcessorCount;
    HV_UINT32 MaxInterruptMappingCount;
    HV_UINT32 ReservedEdx;
} HV_IMPLEMENTATION_LIMITS, *PHV_IMPLEMENTATION_LIMITS;

typedef struct _HV_X64_HYPERVISOR_HARDWARE_FEATURES
{
    HV_UINT32 ApicOverlayAssistInUse : 1;
    HV_UINT32 MsrBitmapsInUse : 1;
    HV_UINT32 ArchitecturalPerformanceCountersInUse : 1;
    HV_UINT32 SecondLevelAddressTranslationInUse : 1;
    HV_UINT32 DmaRemappingInUse : 1;
    HV_UINT32 InterruptRemappingInUse : 1;
    HV_UINT32 MemoryPatrolScrubberPresent : 1;
    HV_UINT32 DmaProtectionInUse : 1;
    HV_UINT32 HpetRequested : 1;
    HV_UINT32 SyntheticTimersVolatile : 1;
    HV_UINT32 Reserved : 22;
    HV_UINT32 ReservedEbx;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_HARDWARE_FEATURES, *PHV_X64_HYPERVISOR_HARDWARE_FEATURES;

typedef union _HV_CPUID_RESULT
{
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 Ebx;
        HV_UINT32 Ecx;
        HV_UINT32 Edx;
    };

    HV_UINT32 AsUINT32[4];

    struct {
        HV_UINT32 ReservedEax;
        HV_UINT32 ReservedEbx : 24;
        HV_UINT32 InitialApicId : 8;
        HV_UINT32 ReservedEcx : 31;
        HV_UINT32 HypervisorPresent : 1;
        HV_UINT32 ReservedEdx;
    } VersionAndFeatures;

    HV_VENDOR_AND_MAX_FUNCTION HvVendorAndMaxFunction;
    HV_HYPERVISOR_INTERFACE_INFO HvInterface;
    HV_HYPERVISOR_VERSION_INFO MsHvVersion;
    HV_X64_HYPERVISOR_FEATURES MsHvFeatures;
    HV_X64_ENLIGHTENMENT_INFORMATION MsHvEnlightenmentInformation;
    HV_IMPLEMENTATION_LIMITS MsHvImplementationLimits;
    HV_X64_HYPERVISOR_HARDWARE_FEATURES MsHvHardwareFeatures;
} HV_CPUID_RESULT, *PHV_CPUID_RESULT;

/*
 * Hypervisor Synthetic MSRs
 */

/* MSR used to identify the guest OS. */

#define HV_X64_MSR_GUEST_OS_ID 0x40000000

typedef enum _HV_GUEST_OS_MICROSOFT_IDS
{ 
    HvGuestOsMicrosoftUndefined = 0x00,
    HvGuestOsMicrosoftMSDOS = 0x01,
    HvGuestOsMicrosoftWindows3x = 0x02,
    HvGuestOsMicrosoftWindows9x = 0x03,
    HvGuestOsMicrosoftWindowsNT = 0x04,
    HvGuestOsMicrosoftWindowsCE = 0x05
} HV_GUEST_OS_MICROSOFT_IDS, *PHV_GUEST_OS_MICROSOFT_IDS;

typedef enum _HV_GUEST_OS_VENDOR
{
    HvGuestOsVendorMicrosoft = 0x0001,
    HvGuestOsVendorHPE = 0x0002,
    HvGuestOsVendorLANCOM = 0x0200,
} HV_GUEST_OS_VENDOR, *PHV_GUEST_OS_VENDOR;

typedef enum _HV_GUEST_OS_OPENSOURCE_TYPES
{
    HvGuestOsOpenSourceUndefined = 0x0,
    HvGuestOsOpenSourceLinux = 0x1,
    HvGuestOsOpenSourceFreeBSD = 0x2,
    HvGuestOsOpenSourceXen = 0x3,
    HvGuestOsOpenSourceIllumos = 0x4,
} HV_GUEST_OS_OPENSOURCE_TYPES, *PHV_GUEST_OS_OPENSOURCE_TYPES;

typedef union _HV_X64_MSR_GUEST_OS_ID_CONTENTS
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT64 BuildNumber : 16;
        HV_UINT64 ServiceVersion : 8;
        HV_UINT64 MinorVersion : 8;
        HV_UINT64 MajorVersion : 8;
        HV_UINT64 OsId : 8;
        HV_UINT64 VendorId : 15;
        HV_UINT64 OpenSource : 1;
    };

    struct
    {
        HV_UINT64 BuildNumber : 16;
        HV_UINT64 Version : 32;
        HV_UINT64 OsId : 8;
        HV_UINT64 OsType : 7;
        HV_UINT64 OpenSource : 1;
    };
} HV_X64_MSR_GUEST_OS_ID_CONTENTS, *PHV_X64_MSR_GUEST_OS_ID_CONTENTS;

/* MSR used to setup pages used to communicate with the hypervisor. */

#define HV_X64_MSR_HYPERCALL 0x40000001

typedef union _HV_X64_MSR_HYPERCALL_CONTENTS
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT64 Enable : 1;
        HV_UINT64 Locked : 1;
        HV_UINT64 ReservedP : 10;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_X64_MSR_HYPERCALL_CONTENTS, *PHV_X64_MSR_HYPERCALL_CONTENTS;

/* MSR used to provide vcpu index */

#define HV_X64_MSR_VP_INDEX 0x40000002

/* MSR used to reset the guest OS. */

#define HV_X64_MSR_RESET 0x40000003

/* MSR used to provide vcpu runtime in 100ns units */

#define HV_X64_MSR_VP_RUNTIME 0x40000010

/* MSR used to read the per-partition time reference counter */

#define HV_X64_MSR_TIME_REF_COUNT 0x40000020

/* A partition's reference time stamp counter (TSC) page */

#define HV_X64_MSR_REFERENCE_TSC 0x40000021

/* MSR used to retrieve the TSC frequency */

#define HV_X64_MSR_TSC_FREQUENCY 0x40000022

/* MSR used to retrieve the local APIC timer frequency */

#define HV_X64_MSR_APIC_FREQUENCY 0x40000023

/* Non-Privileged Instruction Execution Prevention */

#define HV_X64_MSR_NPIEP_CONFIG 0x40000040

/* Define the virtual APIC registers */

#define HV_X64_MSR_EOI 0x40000070
#define HV_X64_MSR_ICR 0x40000071
#define HV_X64_MSR_TPR 0x40000072
#define HV_X64_MSR_VP_ASSIST_PAGE 0x40000073

/* Define synthetic interrupt controller model specific registers. */

#define HV_X64_MSR_SCONTROL 0x40000080
#define HV_X64_MSR_SVERSION 0x40000081
#define HV_X64_MSR_SIEFP 0x40000082
#define HV_X64_MSR_SIMP 0x40000083
#define HV_X64_MSR_EOM 0x40000084
#define HV_X64_MSR_SIRBP 0x40000085
#define HV_X64_MSR_SINT0 0x40000090
#define HV_X64_MSR_SINT1 0x40000091
#define HV_X64_MSR_SINT2 0x40000092
#define HV_X64_MSR_SINT3 0x40000093
#define HV_X64_MSR_SINT4 0x40000094
#define HV_X64_MSR_SINT5 0x40000095
#define HV_X64_MSR_SINT6 0x40000096
#define HV_X64_MSR_SINT7 0x40000097
#define HV_X64_MSR_SINT8 0x40000098
#define HV_X64_MSR_SINT9 0x40000099
#define HV_X64_MSR_SINT10 0x4000009A
#define HV_X64_MSR_SINT11 0x4000009B
#define HV_X64_MSR_SINT12 0x4000009C
#define HV_X64_MSR_SINT13 0x4000009D
#define HV_X64_MSR_SINT14 0x4000009E
#define HV_X64_MSR_SINT15 0x4000009F

/* Synthetic Timer MSRs. Four timers per vcpu. */

#define HV_X64_MSR_STIMER0_CONFIG 0x400000B0
#define HV_X64_MSR_STIMER0_COUNT 0x400000B1
#define HV_X64_MSR_STIMER1_CONFIG 0x400000B2
#define HV_X64_MSR_STIMER1_COUNT 0x400000B3
#define HV_X64_MSR_STIMER2_CONFIG 0x400000B4
#define HV_X64_MSR_STIMER2_COUNT 0x400000B5
#define HV_X64_MSR_STIMER3_CONFIG 0x400000B6
#define HV_X64_MSR_STIMER3_COUNT 0x400000B7

/* Hyper-V guest idle MSR */

#define HV_X64_MSR_GUEST_IDLE 0x400000F0

/* Hyper-V guest crash notification MSR's */

#define HV_X64_MSR_CRASH_P0 0x40000100
#define HV_X64_MSR_CRASH_P1 0x40000101
#define HV_X64_MSR_CRASH_P2 0x40000102
#define HV_X64_MSR_CRASH_P3 0x40000103
#define HV_X64_MSR_CRASH_P4 0x40000104
#define HV_X64_MSR_CRASH_CTL 0x40000105

/* TSC emulation after migration */

#define HV_X64_MSR_REENLIGHTENMENT_CONTROL 0x40000106
#define HV_X64_MSR_TSC_EMULATION_CONTROL 0x40000107
#define HV_X64_MSR_TSC_EMULATION_STATUS 0x40000108

/* Synthetic Time-Unhalted Timer MSRs */

#define HV_X64_MSR_STIME_UNHALTED_TIMER_CONFIG 0x40000114
#define HV_X64_MSR_STIME_UNHALTED_TIMER_COUNT 0x40000115

/* TSC invariant control */

#define HV_X64_MSR_TSC_INVARIANT_CONTROL 0x40000118

/* Define synthetic interrupt controller model specific registers for nested
   hypervisor */

#define HV_X64_MSR_NESTED_SCONTROL 0x40001080
#define HV_X64_MSR_NESTED_SVERSION 0x40001081
#define HV_X64_MSR_NESTED_SIEFP 0x40001082
#define HV_X64_MSR_NESTED_SIMP 0x40001083
#define HV_X64_MSR_NESTED_EOM 0x40001084
#define HV_X64_MSR_NESTED_SINT0 0x40001090
#define HV_X64_MSR_NESTED_SINT1 0x40001091
#define HV_X64_MSR_NESTED_SINT2 0x40001092
#define HV_X64_MSR_NESTED_SINT3 0x40001093
#define HV_X64_MSR_NESTED_SINT4 0x40001094
#define HV_X64_MSR_NESTED_SINT5 0x40001095
#define HV_X64_MSR_NESTED_SINT6 0x40001096
#define HV_X64_MSR_NESTED_SINT7 0x40001097
#define HV_X64_MSR_NESTED_SINT8 0x40001098
#define HV_X64_MSR_NESTED_SINT9 0x40001099
#define HV_X64_MSR_NESTED_SINT10 0x4000109A
#define HV_X64_MSR_NESTED_SINT11 0x4000109B
#define HV_X64_MSR_NESTED_SINT12 0x4000109C
#define HV_X64_MSR_NESTED_SINT13 0x4000109D
#define HV_X64_MSR_NESTED_SINT14 0x4000109E
#define HV_X64_MSR_NESTED_SINT15 0x4000109F

/*
 * Hypercall
 */

typedef union _HV_X64_HYPERCALL_INPUT
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT32 CallCode : 16;
        HV_UINT32 IsFast : 1;
        HV_UINT32 VariableHeaderSize : 9;
        HV_UINT32 Reserved1 : 5;
        HV_UINT32 IsNested : 1;
        HV_UINT32 CountOfElements : 12;
        HV_UINT32 Reserved2 : 4;
        HV_UINT32 RepStartIndex : 12;
        HV_UINT32 Reserved3 : 4;
    }; 
} HV_X64_HYPERCALL_INPUT, *PHV_X64_HYPERCALL_INPUT;

typedef union _HV_X64_HYPERCALL_OUTPUT
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT16 CallStatus;
        HV_UINT16 Reserved1;
        HV_UINT32 ElementsProcessed : 12;
        HV_UINT32 Reserved2 : 20;
    };
} HV_X64_HYPERCALL_OUTPUT, *PHV_X64_HYPERCALL_OUTPUT;

typedef enum _HV_CALL_CODE
{ 
    HvCallReserved0000 = 0x0000,
    HvCallSwitchVirtualAddressSpace = 0x0001,
    HvCallFlushVirtualAddressSpace = 0x0002,
    HvCallFlushVirtualAddressList = 0x0003,
    HvCallGetLogicalProcessorRunTime = 0x0004,
    HvCallDeprecated0005 = 0x0005,
    HvCallDeprecated0006 = 0x0006,
    HvCallDeprecated0007 = 0x0007,
    HvCallNotifyLongSpinWait = 0x0008,
    HvCallParkLogicalProcessors = 0x0009,
    HvCallInvokeHypervisorDebugger = 0x000A,
    HvCallSendIpi = 0x000B,
    HvCallReserved000c = 0x000C,
    HvCallReserved000d = 0x000D,
    HvCallReserved000e = 0x000E,
    HvCallReserved000f = 0x000F,
    HvCallReserved0010 = 0x0010,
    HvCallReserved0011 = 0x0011,
    HvCallReserved0012 = 0x0012,
    HvCallFlushVirtualAddressSpaceEx = 0x0013,
    HvCallFlushVirtualAddressListEx = 0x0014,
    HvCallSendIpiEx = 0x0015,
    HvCallReserved0016 = 0x0016,
    HvCallReserved0017 = 0x0017,
    HvCallReserved0018 = 0x0018,
    HvCallReserved0019 = 0x0019,
    HvCallReserved001a = 0x001A,
    HvCallReserved001b = 0x001B,
    HvCallReserved001c = 0x001C,
    HvCallReserved001d = 0x001D,
    HvCallReserved001e = 0x001E,
    HvCallReserved001f = 0x001F,
    HvCallReserved0020 = 0x0020,
    HvCallReserved0021 = 0x0021,
    HvCallReserved0022 = 0x0022,
    HvCallReserved0023 = 0x0023,
    HvCallReserved0024 = 0x0024,
    HvCallReserved0025 = 0x0025,
    HvCallReserved0026 = 0x0026,
    HvCallReserved0027 = 0x0027,
    HvCallReserved0028 = 0x0028,
    HvCallReserved0029 = 0x0029,
    HvCallReserved002a = 0x002A,
    HvCallReserved002b = 0x002B,
    HvCallReserved002c = 0x002C,
    HvCallReserved002d = 0x002D,
    HvCallReserved002e = 0x002E,
    HvCallReserved002f = 0x002F,
    HvCallReserved0030 = 0x0030,
    HvCallReserved0031 = 0x0031,
    HvCallReserved0032 = 0x0032,
    HvCallReserved0033 = 0x0033,
    HvCallReserved0034 = 0x0034,
    HvCallReserved0035 = 0x0035,
    HvCallReserved0036 = 0x0036,
    HvCallReserved0037 = 0x0037,
    HvCallReserved0038 = 0x0038,
    HvCallReserved0039 = 0x0039,
    HvCallReserved003a = 0x003A,
    HvCallReserved003b = 0x003B,
    HvCallReserved003c = 0x003C,
    HvCallReserved003d = 0x003D,
    HvCallReserved003e = 0x003E,
    HvCallReserved003f = 0x003F,
    HvCallCreatePartition = 0x0040,
    HvCallInitializePartition = 0x0041,
    HvCallFinalizePartition = 0x0042,
    HvCallDeletePartition = 0x0043,
    HvCallGetPartitionProperty = 0x0044,
    HvCallSetPartitionProperty = 0x0045,
    HvCallGetPartitionId = 0x0046,
    HvCallGetNextChildPartition = 0x0047,
    HvCallDepositMemory = 0x0048,
    HvCallWithdrawMemory = 0x0049,
    HvCallGetMemoryBalance = 0x004A,
    HvCallMapGpaPages = 0x004B,
    HvCallUnmapGpaPages = 0x004C,
    HvCallInstallIntercept = 0x004D,
    HvCallCreateVp = 0x004E,
    HvCallDeleteVp = 0x004F,
    HvCallGetVpRegisters = 0x0050,
    HvCallSetVpRegisters = 0x0051,
    HvCallTranslateVirtualAddress = 0x0052,
    HvCallReadGpa = 0x0053,
    HvCallWriteGpa = 0x0054,
    HvCallAssertVirtualInterruptDeprecated = 0x0055,
    HvCallClearVirtualInterrupt = 0x0056,
    HvCallCreatePortDeprecated = 0x0057,
    HvCallDeletePort = 0x0058,
    HvCallConnectPortDeprecated = 0x0059,
    HvCallGetPortProperty = 0x005A,
    HvCallDisconnectPort = 0x005B,
    HvCallPostMessage = 0x005C,
    HvCallSignalEvent = 0x005D,
    HvCallSavePartitionState = 0x005E,
    HvCallRestorePartitionState = 0x005F,
    HvCallInitializeEventLogBufferGroup = 0x0060,
    HvCallFinalizeEventLogBufferGroup = 0x0061,
    HvCallCreateEventLogBuffer = 0x0062,
    HvCallDeleteEventLogBuffer = 0x0063,
    HvCallMapEventLogBuffer = 0x0064,
    HvCallUnmapEventLogBuffer = 0x0065,
    HvCallSetEventLogGroupSources = 0x0066,
    HvCallReleaseEventLogBuffer = 0x0067,
    HvCallFlushEventLogBuffer = 0x0068,
    HvCallPostDebugData = 0x0069,
    HvCallRetrieveDebugData = 0x006A,
    HvCallResetDebugSession = 0x006B,
    HvCallMapStatsPage = 0x006C,
    HvCallUnmapStatsPage = 0x006D,
    HvCallMapSparseGpaPages = 0x006E,
    HvCallSetSystemProperty = 0x006F,
    HvCallSetPortProperty = 0x0070,
    HvCallOutputDebugCharacter = 0x0071,
    HvCallEchoIncrement = 0x0072,
    HvCallPerfNop = 0x0073,
    HvCallPerfNopInput = 0x0074,
    HvCallPerfNopOutput = 0x0075,
    HvCallAddLogicalProcessor = 0x0076,
    HvCallReserved0077 = 0x0077,
    HvCallReserved0078 = 0x0078,
    HvCallReserved0079 = 0x0079,
    HvCallReserved007a = 0x007A,
    HvCallGetSystemProperty = 0x007B,
    HvCallMapDeviceInterrupt = 0x007C,
    HvCallUnmapDeviceInterrupt = 0x007D,
    HvCallRetargetInterrupt = 0x007E,
    HvCallReserved007f = 0x007F,
    HvCallReserved0080 = 0x0080,
    HvCallReserved0081 = 0x0081,
    HvCallReserved0082 = 0x0082,
    HvCallReserved0083 = 0x0083,
    HvCallReserved0084 = 0x0084,
    HvCallReserved0085 = 0x0085,
    HvCallReserved0086 = 0x0086,
    HvCallReserved0087 = 0x0087,
    HvCallReserved0088 = 0x0088,
    HvCallReserved0089 = 0x0089,
    HvCallReserved008a = 0x008A,
    HvCallNotifyPortRingEmpty = 0x008B,
    HvCallReserved008c = 0x008C,
    HvCallReserved008d = 0x008D,
    HvCallReserved008e = 0x008E,
    HvCallReserved008f = 0x008F,
    HvCallReserved0090 = 0x0090,
    HvCallRegisterInterceptResult = 0x0091,
    HvCallReserved0092 = 0x0092,
    HvCallReserved0093 = 0x0093,
    HvCallAssertVirtualInterrupt = 0x0094,
    HvCallCreatePort = 0x0095,
    HvCallConnectPort = 0x0096,
    HvCallReserved0097 = 0x0097,
    HvCallReserved0098 = 0x0098,
    HvCallReserved0099 = 0x0099,
    HvCallReserved009a = 0x009A,
    HvCallReserved009b = 0x009B,
    HvCallReserved009c = 0x009C,
    HvCallReserved009d = 0x009D,
    HvCallReserved009e = 0x009E,
    HvCallReserved009f = 0x009F,
    HvCallReserved00a0 = 0x00A0,
    HvCallReserved00a1 = 0x00A1,
    HvCallReserved00a2 = 0x00A2,
    HvCallReserved00a3 = 0x00A3,
    HvCallReserved00a4 = 0x00A4,
    HvCallReserved00a5 = 0x00A5,
    HvCallReserved00a6 = 0x00A6,
    HvCallReserved00a7 = 0x00A7,
    HvCallReserved00a8 = 0x00A8,
    HvCallReserved00a9 = 0x00A9,
    HvCallReserved00aa = 0x00AA,
    HvCallReserved00ab = 0x00AB,
    HvCallReserved00ac = 0x00AC,
    HvCallReserved00ad = 0x00AD,
    HvCallReserved00ae = 0x00AE,
    HvCallFlushGuestPhysicalAddressSpace = 0x00AF,
    HvCallFlushGuestPhysicalAddressList = 0x00B0,
    HvCallReserved00b1 = 0x00B1,
    HvCallReserved00b2 = 0x00B2,
    HvCallReserved00b3 = 0x00B3,
    HvCallReserved00b4 = 0x00B4,
    HvCallReserved00b5 = 0x00B5,
    HvCallReserved00b6 = 0x00B6,
    HvCallReserved00b7 = 0x00B7,
    HvCallReserved00b8 = 0x00B8,
    HvCallReserved00b9 = 0x00B9,
    HvCallReserved00ba = 0x00BA,
    HvCallReserved00bb = 0x00BB,
    HvCallReserved00bc = 0x00BC,
    HvCallReserved00bd = 0x00BD,
    HvCallReserved00be = 0x00BE,
    HvCallReserved00bf = 0x00BF,
    HvCallSignalEventDirect = 0x00C0,
    HvCallPostMessageDirect = 0x00C1,
    HvCallDispatchVp = 0x00C2,
    HvCallReserved00c3 = 0x00C3,
    HvCallReserved00c4 = 0x00C4,
    HvCallReserved00c5 = 0x00C5,
    HvCallReserved00c6 = 0x00C6,
    HvCallReserved00c7 = 0x00C7,
    HvCallReserved00c8 = 0x00C8,
    HvCallGetGpaPagesAccessStates = 0x00C9,
    HvCallReserved00ca = 0x00CA,
    HvCallReserved00cb = 0x00CB,
    HvCallReserved00cc = 0x00CC,
    HvCallReserved00cd = 0x00CD,
    HvCallReserved00ce = 0x00CE,
    HvCallReserved00cf = 0x00CF,
    HvCallReserved00d0 = 0x00D0,
    HvCallReserved00d1 = 0x00D1,
    HvCallReserved00d2 = 0x00D2,
    HvCallReserved00d3 = 0x00D3,
    HvCallReserved00d4 = 0x00D4,
    HvCallReserved00d5 = 0x00D5,
    HvCallReserved00d6 = 0x00D6,
    HvCallReserved00d7 = 0x00D7,
    HvCallReserved00d8 = 0x00D8,
    HvCallReserved00d9 = 0x00D9,
    HvCallReserved00da = 0x00DA,
    HvCallReserved00db = 0x00DB,
    HvCallReserved00dc = 0x00DC,
    HvCallReserved00dd = 0x00DD,
    HvCallReserved00de = 0x00DE,
    HvCallReserved00df = 0x00DF,
    HvCallReserved00e0 = 0x00E0,
    HvCallMapVpStatePage = 0x00E1,
    HvCallUnmapVpStatePage = 0x00E2,
    HvCallGetVpState = 0x00E3,
    HvCallSetVpState = 0x00E4,
    HvCallReserved00e5 = 0x00E5,
    HvCallReserved00e6 = 0x00E6,
    HvCallReserved00e7 = 0x00E7,
    HvCallReserved00e8 = 0x00E8,
    HvCallReserved00e9 = 0x00E9,
    HvCallReserved00ea = 0x00EA,
    HvCallReserved00eb = 0x00EB,
    HvCallReserved00ec = 0x00EC,
    HvCallReserved00ed = 0x00ED,
    HvCallReserved00ee = 0x00EE,
    HvCallReserved00ef = 0x00EF,
    HvCallReserved00f0 = 0x00F0,
    HvCallReserved00f1 = 0x00F1,
    HvCallReserved00f2 = 0x00F2,
    HvCallReserved00f3 = 0x00F3,
    HvCallGetVpCpuidValues = 0x00F4,
    HvCallCount
} HV_CALL_CODE, *PHV_CALL_CODE;

#define HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE 0x0002
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST 0x0003
#define HVCALL_NOTIFY_LONG_SPIN_WAIT 0x0008
#define HVCALL_SEND_IPI 0x000B
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX 0x0013
#define HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX 0x0014
#define HVCALL_SEND_IPI_EX 0x0015
#define HVCALL_GET_VP_REGISTERS 0x0050
#define HVCALL_SET_VP_REGISTERS 0x0051
#define HVCALL_TRANSLATE_VIRTUAL_ADDRESS 0x0052
#define HVCALL_POST_MESSAGE 0x005C
#define HVCALL_SIGNAL_EVENT 0x005D
#define HVCALL_RETARGET_INTERRUPT 0x007E
#define HVCALL_ASSERT_VIRTUAL_INTERRUPT 0x0094

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
/* nonstandard extension used : nameless struct/union */
#pragma warning(default:4201)
#endif
#endif

#endif /* !MILE_HYPERV_TLFS */
