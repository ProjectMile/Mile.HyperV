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

typedef HV_UINT32 HV_VP_INDEX;
typedef HV_VP_INDEX* PHV_VP_INDEX;
typedef const HV_VP_INDEX* PCHV_VP_INDEX;

#define HV_ANY_VP ((HV_VP_INDEX)-1) 
#define HV_VP_INDEX_SELF ((HV_VP_INDEX)-2)

#define HV_MAXIMUM_PROCESSORS 2048

#define HV_MAX_VP_INDEX (HV_MAXIMUM_PROCESSORS - 1)

typedef enum _HV_REGISTER_NAME
{
    /* Suspend Registers */

    HvRegisterExplicitSuspend = 0x00000000,
    HvRegisterInterceptSuspend = 0x00000001,
    HvRegisterDispatchSuspend = 0x00000003,

    /* Version */

    /* 128-bit result same as CPUID 0x40000002 */
    HvRegisterHypervisorVersion = 0x00000100,

    /* Feature Access (registers are 128 bits) */

    /* 128-bit result same as CPUID 0x40000003 */
    HvRegisterPrivilegesAndFeaturesInfo = 0x00000200,
    /* 128-bit result same as CPUID 0x40000004 */
    HvRegisterFeaturesInfo = 0x00000201,
    /* 128-bit result same as CPUID 0x40000005 */
    HvRegisterImplementationLimitsInfo = 0x00000202,
    /* 128-bit result same as CPUID 0x40000006 */
    HvRegisterHardwareFeaturesInfo = 0x00000203,

    /* Guest Crash Registers */

    HvRegisterGuestCrashP0 = 0x00000210,
    HvRegisterGuestCrashP1 = 0x00000211,
    HvRegisterGuestCrashP2 = 0x00000212,
    HvRegisterGuestCrashP3 = 0x00000213,
    HvRegisterGuestCrashP4 = 0x00000214,
    HvRegisterGuestCrashCtl = 0x00000215,

    /* Power State Configuration */

    HvRegisterPowerStateConfigC1 = 0x00000220,
    HvRegisterPowerStateTriggerC1 = 0x00000221,
    HvRegisterPowerStateConfigC2 = 0x00000222,
    HvRegisterPowerStateTriggerC2 = 0x00000223,
    HvRegisterPowerStateConfigC3 = 0x00000224,
    HvRegisterPowerStateTriggerC3 = 0x00000225,

    /* Frequency Registers */

    HvRegisterProcessorClockFrequency = 0x00000240,
    HvRegisterInterruptClockFrequency = 0x00000241,

    /* Idle Register */

    HvRegisterGuestIdle = 0x00000250,

    /* Guest Debug */

    HvRegisterDebugDeviceOptions = 0x00000260,

    /* Pending Interruption Register */

    HvRegisterPendingInterruption = 0x00010002,

    /* Interrupt State register */

    HvRegisterInterruptState = 0x00010003,

    /* Pending Event Register */

    HvRegisterPendingEvent0 = 0x00010004,
    HvRegisterPendingEvent1 = 0x00010005,

    /* Interruptible notification register */
    HvX64RegisterDeliverabilityNotifications = 0x00010006,

    /* X64 User-Mode Registers */

    HvX64RegisterRax = 0x00020000,
    HvX64RegisterRcx = 0x00020001,
    HvX64RegisterRdx = 0x00020002,
    HvX64RegisterRbx = 0x00020003,
    HvX64RegisterRsp = 0x00020004,
    HvX64RegisterRbp = 0x00020005,
    HvX64RegisterRsi = 0x00020006,
    HvX64RegisterRdi = 0x00020007,
    HvX64RegisterR8 = 0x00020008,
    HvX64RegisterR9 = 0x00020009,
    HvX64RegisterR10 = 0x0002000A,
    HvX64RegisterR11 = 0x0002000B,
    HvX64RegisterR12 = 0x0002000C,
    HvX64RegisterR13 = 0x0002000D,
    HvX64RegisterR14 = 0x0002000E,
    HvX64RegisterR15 = 0x0002000F,
    HvX64RegisterRip = 0x00020010,
    HvX64RegisterRflags = 0x00020011,

    /* X64 Floating Point and Vector Registers */

    HvX64RegisterXmm0 = 0x00030000,
    HvX64RegisterXmm1 = 0x00030001,
    HvX64RegisterXmm2 = 0x00030002,
    HvX64RegisterXmm3 = 0x00030003,
    HvX64RegisterXmm4 = 0x00030004,
    HvX64RegisterXmm5 = 0x00030005,
    HvX64RegisterXmm6 = 0x00030006,
    HvX64RegisterXmm7 = 0x00030007,
    HvX64RegisterXmm8 = 0x00030008,
    HvX64RegisterXmm9 = 0x00030009,
    HvX64RegisterXmm10 = 0x0003000A,
    HvX64RegisterXmm11 = 0x0003000B,
    HvX64RegisterXmm12 = 0x0003000C,
    HvX64RegisterXmm13 = 0x0003000D,
    HvX64RegisterXmm14 = 0x0003000E,
    HvX64RegisterXmm15 = 0x0003000F,
    HvX64RegisterFpMmx0 = 0x00030010,
    HvX64RegisterFpMmx1 = 0x00030011,
    HvX64RegisterFpMmx2 = 0x00030012,
    HvX64RegisterFpMmx3 = 0x00030013,
    HvX64RegisterFpMmx4 = 0x00030014,
    HvX64RegisterFpMmx5 = 0x00030015,
    HvX64RegisterFpMmx6 = 0x00030016,
    HvX64RegisterFpMmx7 = 0x00030017,
    HvX64RegisterFpControlStatus = 0x00030018,
    HvX64RegisterXmmControlStatus = 0x00030019,

    /* X64 Control Registers */
 
    HvX64RegisterCr0 = 0x00040000,
    HvX64RegisterCr2 = 0x00040001,
    HvX64RegisterCr3 = 0x00040002,
    HvX64RegisterCr4 = 0x00040003,
    HvX64RegisterCr8 = 0x00040004,
    HvX64RegisterXfem = 0x00040005,

    /* X64 Intermediate Control Registers */

    HvX64RegisterIntermediateCr0 = 0x00041000,
    HvX64RegisterIntermediateCr4 = 0x00041003,
    HvX64RegisterIntermediateCr8 = 0x00041004,

    /* X64 Debug Registers */
 
    HvX64RegisterDr0 = 0x00050000,
    HvX64RegisterDr1 = 0x00050001,
    HvX64RegisterDr2 = 0x00050002,
    HvX64RegisterDr3 = 0x00050003,
    HvX64RegisterDr6 = 0x00050004,
    HvX64RegisterDr7 = 0x00050005,

    /* X64 Segment Registers */
 
    HvX64RegisterEs = 0x00060000,
    HvX64RegisterCs = 0x00060001,
    HvX64RegisterSs = 0x00060002,
    HvX64RegisterDs = 0x00060003,
    HvX64RegisterFs = 0x00060004,
    HvX64RegisterGs = 0x00060005,
    HvX64RegisterLdtr = 0x00060006,
    HvX64RegisterTr = 0x00060007,

    /* X64 Table Registers */
 
    HvX64RegisterIdtr = 0x00070000,
    HvX64RegisterGdtr = 0x00070001,

    /* X64 Virtualized MSRs */
 
    HvX64RegisterTsc = 0x00080000,
    HvX64RegisterEfer = 0x00080001,
    HvX64RegisterKernelGsBase = 0x00080002,
    HvX64RegisterApicBase = 0x00080003,
    HvX64RegisterPat = 0x00080004,
    HvX64RegisterSysenterCs = 0x00080005,
    HvX64RegisterSysenterEip = 0x00080006,
    HvX64RegisterSysenterEsp = 0x00080007,
    HvX64RegisterStar = 0x00080008,
    HvX64RegisterLstar = 0x00080009,
    HvX64RegisterCstar = 0x0008000A,
    HvX64RegisterSfmask = 0x0008000B,
    HvX64RegisterInitialApicId = 0x0008000C,

    /* X64 Cache control MSRs */

    HvX64RegisterMtrrCap = 0x0008000D,
    HvX64RegisterMtrrDefType = 0x0008000E,
    HvX64RegisterMtrrPhysBase0 = 0x00080010,
    HvX64RegisterMtrrPhysBase1 = 0x00080011,
    HvX64RegisterMtrrPhysBase2 = 0x00080012,
    HvX64RegisterMtrrPhysBase3 = 0x00080013,
    HvX64RegisterMtrrPhysBase4 = 0x00080014,
    HvX64RegisterMtrrPhysBase5 = 0x00080015,
    HvX64RegisterMtrrPhysBase6 = 0x00080016,
    HvX64RegisterMtrrPhysBase7 = 0x00080017,
    HvX64RegisterMtrrPhysBase8 = 0x00080018,
    HvX64RegisterMtrrPhysBase9 = 0x00080019,
    HvX64RegisterMtrrPhysBaseA = 0x0008001A,
    HvX64RegisterMtrrPhysBaseB = 0x0008001B,
    HvX64RegisterMtrrPhysBaseC = 0x0008001C,
    HvX64RegisterMtrrPhysBaseD = 0x0008001D,
    HvX64RegisterMtrrPhysBaseE = 0x0008001E,
    HvX64RegisterMtrrPhysBaseF = 0x0008001F,
    HvX64RegisterMtrrPhysMask0 = 0x00080040,
    HvX64RegisterMtrrPhysMask1 = 0x00080041,
    HvX64RegisterMtrrPhysMask2 = 0x00080042,
    HvX64RegisterMtrrPhysMask3 = 0x00080043,
    HvX64RegisterMtrrPhysMask4 = 0x00080044,
    HvX64RegisterMtrrPhysMask5 = 0x00080045,
    HvX64RegisterMtrrPhysMask6 = 0x00080046,
    HvX64RegisterMtrrPhysMask7 = 0x00080047,
    HvX64RegisterMtrrPhysMask8 = 0x00080048,
    HvX64RegisterMtrrPhysMask9 = 0x00080049,
    HvX64RegisterMtrrPhysMaskA = 0x0008004A,
    HvX64RegisterMtrrPhysMaskB = 0x0008004B,
    HvX64RegisterMtrrPhysMaskC = 0x0008004C,
    HvX64RegisterMtrrPhysMaskD = 0x0008004D,
    HvX64RegisterMtrrPhysMaskE = 0x0008004E,
    HvX64RegisterMtrrPhysMaskF = 0x0008004F,
    HvX64RegisterMtrrFix64k00000 = 0x00080070,
    HvX64RegisterMtrrFix16k80000 = 0x00080071,
    HvX64RegisterMtrrFix16kA0000 = 0x00080072,
    HvX64RegisterMtrrFix4kC0000 = 0x00080073,
    HvX64RegisterMtrrFix4kC8000 = 0x00080074,
    HvX64RegisterMtrrFix4kD0000 = 0x00080075,
    HvX64RegisterMtrrFix4kD8000 = 0x00080076,
    HvX64RegisterMtrrFix4kE0000 = 0x00080077,
    HvX64RegisterMtrrFix4kE8000 = 0x00080078,
    HvX64RegisterMtrrFix4kF0000 = 0x00080079,
    HvX64RegisterMtrrFix4kF8000 = 0x0008007A,
    HvX64RegisterTscAux= 0x0008007B,
    HvX64RegisterBndcfgs = 0x0008007C,
    HvX64RegisterDebugCtl = 0x0008007D,
    HvX64RegisterSgxLaunchControl0 = 0x00080080,
    HvX64RegisterSgxLaunchControl1 = 0x00080081,
    HvX64RegisterSgxLaunchControl2 = 0x00080082,
    HvX64RegisterSgxLaunchControl3 = 0x00080083,
    HvX64RegisterSpecCtrl = 0x00080084,
    HvX64RegisterPredCmd = 0x00080085,
    HvX64RegisterVirtSpecCtrl = 0x00080086,
    HvX64RegisterTscAdjust = 0x00080096,

    /* Other MSRs */
 
    HvX64RegisterMsrIa32MiscEnable = 0x000800A0,
    HvX64RegisterIa32FeatureControl = 0x000800A1,
    HvX64RegisterIa32VmxBasic = 0x000800A2,
    HvX64RegisterIa32VmxPinbasedCtls = 0x000800A3,
    HvX64RegisterIa32VmxProcbasedCtls = 0x000800A4,
    HvX64RegisterIa32VmxExitCtls = 0x000800A5,
    HvX64RegisterIa32VmxEntryCtls = 0x000800A6,
    HvX64RegisterIa32VmxMisc = 0x000800A7,
    HvX64RegisterIa32VmxCr0Fixed0 = 0x000800A8,
    HvX64RegisterIa32VmxCr0Fixed1 = 0x000800A9,
    HvX64RegisterIa32VmxCr4Fixed0 = 0x000800AA,
    HvX64RegisterIa32VmxCr4Fixed1 = 0x000800AB,
    HvX64RegisterIa32VmxVmcsEnum = 0x000800AC,
    HvX64RegisterIa32VmxProcbasedCtls2 = 0x000800AD,
    HvX64RegisterIa32VmxEptVpidCap = 0x000800AE,
    HvX64RegisterIa32VmxTruePinbasedCtls = 0x000800AF,
    HvX64RegisterIa32VmxTrueProcbasedCtls = 0x000800B0,
    HvX64RegisterIa32VmxTrueExitCtls = 0x000800B1,
    HvX64RegisterIa32VmxTrueEntryCtls = 0x000800B2,

    /* Performance monitoring MSRs */
 
    HvX64RegisterPerfGlobalCtrl = 0x00081000,
    HvX64RegisterPerfGlobalStatus = 0x00081001,
    HvX64RegisterPerfGlobalInUse = 0x00081002,
    HvX64RegisterFixedCtrCtrl = 0x00081003,
    HvX64RegisterDsArea = 0x00081004,
    HvX64RegisterPebsEnable = 0x00081005,
    HvX64RegisterPebsLdLat = 0x00081006,
    HvX64RegisterPebsFrontend = 0x00081007,
    HvX64RegisterPerfEvtSel0 = 0x00081100,
    HvX64RegisterPmc0 = 0x00081200,
    HvX64RegisterFixedCtr0 = 0x00081300,
    HvX64RegisterLbrTos = 0x00082000,
    HvX64RegisterLbrSelect = 0x00082001,
    HvX64RegisterLerFromLip = 0x00082002,
    HvX64RegisterLerToLip = 0x00082003,
    HvX64RegisterLbrFrom0 = 0x00082100,
    HvX64RegisterLbrTo0 = 0x00082200,
    HvX64RegisterLbrInfo0 = 0x00083300,

    /* Hypervisor-defined MSRs (Misc) */

    HvX64RegisterVpRuntime = 0x00090000,
    HvX64RegisterHypercall = 0x00090001,
    HvRegisterGuestOsId = 0x00090002,
    HvRegisterVpIndex = 0x00090003,
    HvRegisterTimeRefCount = 0x00090004,
    HvRegisterCpuManagementVersion = 0x00090007,

    /* Virtual APIC registers MSRs */

    HvX64RegisterEoi = 0x00090010,
    HvX64RegisterIcr = 0x00090011,
    HvX64RegisterTpr = 0x00090012,
    HvRegisterVpAssistPage = 0x00090013,
    HvRegisterVpRootSignalCount = 0x00090014,
    HvRegisterReferenceTsc = 0x00090017,
    HvX64RegisterRegPage = 0x0009001C,

    /* Performance statistics MSRs  */

    HvRegisterStatsPartitionRetail = 0x00090020,
    HvRegisterStatsPartitionInternal = 0x00090021,
    HvRegisterStatsVpRetail = 0x00090022,
    HvRegisterStatsVpInternal = 0x00090023,

    /* Partition Timer Assist Registers */

    HvX64RegisterEmulatedTimerPeriod = 0x00090030,
    HvX64RegisterEmulatedTimerControl = 0x00090031,
    HvX64RegisterPmTimerAssist = 0x00090032,

    /* Hypervisor-defined MSRs (Synic) */

    HvRegisterSint0 = 0x000A0000,
    HvRegisterSint1 = 0x000A0001,
    HvRegisterSint2 = 0x000A0002,
    HvRegisterSint3 = 0x000A0003,
    HvRegisterSint4 = 0x000A0004,
    HvRegisterSint5 = 0x000A0005,
    HvRegisterSint6 = 0x000A0006,
    HvRegisterSint7 = 0x000A0007,
    HvRegisterSint8 = 0x000A0008,
    HvRegisterSint9 = 0x000A0009,
    HvRegisterSint10 = 0x000A000A,
    HvRegisterSint11 = 0x000A000B,
    HvRegisterSint12 = 0x000A000C,
    HvRegisterSint13 = 0x000A000D,
    HvRegisterSint14 = 0x000A000E,
    HvRegisterSint15 = 0x000A000F,
    HvRegisterScontrol = 0x000A0010,
    HvRegisterSversion = 0x000A0011,
    HvRegisterSifp = 0x000A0012,
    HvRegisterSipp = 0x000A0013,
    HvRegisterEom = 0x000A0014,
    HvRegisterSirbp = 0x000A0015,

    /* Hypervisor-defined MSRs (Synthetic Timers) */

    HvRegisterStimer0Config = 0x000B0000,
    HvRegisterStimer0Count = 0x000B0001,
    HvRegisterStimer1Config = 0x000B0002,
    HvRegisterStimer1Count = 0x000B0003,
    HvRegisterStimer2Config = 0x000B0004,
    HvRegisterStimer2Count = 0x000B0005,
    HvRegisterStimer3Config = 0x000B0006,
    HvRegisterStimer3Count = 0x000B0007,
    HvRegisterStimeUnhaltedTimerConfig = 0x000B0100,
    HvRegisterStimeUnhaltedTimerCount = 0x000B0101,


    /* XSAVE/XRSTOR register names. */

    /* XSAVE AFX extended state registers.  */

    HvX64RegisterYmm0Low = 0x000C0000,
    HvX64RegisterYmm1Low = 0x000C0001,
    HvX64RegisterYmm2Low = 0x000C0002,
    HvX64RegisterYmm3Low = 0x000C0003,
    HvX64RegisterYmm4Low = 0x000C0004,
    HvX64RegisterYmm5Low = 0x000C0005,
    HvX64RegisterYmm6Low = 0x000C0006,
    HvX64RegisterYmm7Low = 0x000C0007,
    HvX64RegisterYmm8Low = 0x000C0008,
    HvX64RegisterYmm9Low = 0x000C0009,
    HvX64RegisterYmm10Low = 0x000C000A,
    HvX64RegisterYmm11Low = 0x000C000B,
    HvX64RegisterYmm12Low = 0x000C000C,
    HvX64RegisterYmm13Low = 0x000C000D,
    HvX64RegisterYmm14Low = 0x000C000E,
    HvX64RegisterYmm15Low = 0x000C000F,
    HvX64RegisterYmm0High = 0x000C0010,
    HvX64RegisterYmm1High = 0x000C0011,
    HvX64RegisterYmm2High = 0x000C0012,
    HvX64RegisterYmm3High = 0x000C0013,
    HvX64RegisterYmm4High = 0x000C0014,
    HvX64RegisterYmm5High = 0x000C0015,
    HvX64RegisterYmm6High = 0x000C0016,
    HvX64RegisterYmm7High = 0x000C0017,
    HvX64RegisterYmm8High = 0x000C0018,
    HvX64RegisterYmm9High = 0x000C0019,
    HvX64RegisterYmm10High = 0x000C001A,
    HvX64RegisterYmm11High = 0x000C001B,
    HvX64RegisterYmm12High = 0x000C001C,
    HvX64RegisterYmm13High = 0x000C001D,
    HvX64RegisterYmm14High = 0x000C001E,
    HvX64RegisterYmm15High = 0x000C001F,

    /* Synthetic VSM registers */

    HvRegisterVsmCodePageOffsets = 0x000D0002,
    HvRegisterVsmVpStatus = 0x000D0003,
    HvRegisterVsmPartitionStatus = 0x000D0004,
    HvRegisterVsmVina = 0x000D0005,
    HvRegisterVsmCapabilities = 0x000D0006,
    HvRegisterVsmPartitionConfig = 0x000D0007,
    HvRegisterVsmVpSecureConfigVtl0 = 0x000D0010,
    HvRegisterVsmVpSecureConfigVtl1 = 0x000D0011,
    HvRegisterVsmVpSecureConfigVtl2 = 0x000D0012,
    HvRegisterVsmVpSecureConfigVtl3 = 0x000D0013,
    HvRegisterVsmVpSecureConfigVtl4 = 0x000D0014,
    HvRegisterVsmVpSecureConfigVtl5 = 0x000D0015,
    HvRegisterVsmVpSecureConfigVtl6 = 0x000D0016,
    HvRegisterVsmVpSecureConfigVtl7 = 0x000D0017,
    HvRegisterVsmVpSecureConfigVtl8 = 0x000D0018,
    HvRegisterVsmVpSecureConfigVtl9 = 0x000D0019,
    HvRegisterVsmVpSecureConfigVtl10 = 0x000D001A,
    HvRegisterVsmVpSecureConfigVtl11 = 0x000D001B,
    HvRegisterVsmVpSecureConfigVtl12 = 0x000D001C,
    HvRegisterVsmVpSecureConfigVtl13 = 0x000D001D,
    HvRegisterVsmVpSecureConfigVtl14 = 0x000D001E,
    HvRegisterVsmVpWaitForTlbLock = 0x000D0020,

} HV_REGISTER_NAME;
typedef HV_REGISTER_NAME* PHV_REGISTER_NAME;
typedef const HV_REGISTER_NAME* PCHV_REGISTER_NAME;

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

typedef union _HV_CRASH_CTL_REG_CONTENTS
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT64 Reserved : 62;
        HV_UINT64 CrashMessage : 1; 
        HV_UINT64 CrashNotify : 1;
    };
} HV_CRASH_CTL_REG_CONTENTS;

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
    HvCallReserved0000 = 0x0000, /* Undocumented */
    HvCallSwitchVirtualAddressSpace = 0x0001, /* Public | Fast */
    HvCallFlushVirtualAddressSpace = 0x0002, /* Public */
    HvCallFlushVirtualAddressList = 0x0003, /* Public | Rep */
    HvCallGetLogicalProcessorRunTime = 0x0004,
    HvCallDeprecated0005 = 0x0005, /* Reserved */
    HvCallDeprecated0006 = 0x0006, /* Reserved */
    HvCallDeprecated0007 = 0x0007, /* Reserved */
    HvCallNotifyLongSpinWait = 0x0008, /* Public | Fast */
    HvCallParkedVirtualProcessors = 0x0009,
    HvCallInvokeHypervisorDebugger = 0x000A, /* Undocumented */
    HvCallSendSyntheticClusterIpi = 0x000B, /* Public */
    HvCallModifyVtlProtectionMask = 0x000C, /* Public | Rep */
    HvCallEnablePartitionVtl = 0x000D, /* Public */
    HvCallDisablePartitionVtl = 0x000E,
    HvCallEnableVpVtl = 0x000F, /* Public */
    HvCallDisableVpVtl = 0x0010,
    HvCallVtlCall = 0x0011, /* Public */
    HvCallVtlReturn = 0x0012, /* Public */
    HvCallFlushVirtualAddressSpaceEx = 0x0013, /* Public */
    HvCallFlushVirtualAddressListEx = 0x0014, /* Public */
    HvCallSendSyntheticClusterIpiEx = 0x0015, /* Public */
    HvCallReserved0016 = 0x0016, /* Reserved */
    HvCallReserved0017 = 0x0017, /* Reserved */
    HvCallReserved0018 = 0x0018, /* Reserved */
    HvCallReserved0019 = 0x0019, /* Reserved */
    HvCallReserved001a = 0x001A, /* Reserved */
    HvCallReserved001b = 0x001B, /* Reserved */
    HvCallReserved001c = 0x001C, /* Reserved */
    HvCallReserved001d = 0x001D, /* Reserved */
    HvCallReserved001e = 0x001E, /* Reserved */
    HvCallReserved001f = 0x001F, /* Reserved */
    HvCallReserved0020 = 0x0020, /* Reserved */
    HvCallReserved0021 = 0x0021, /* Reserved */
    HvCallReserved0022 = 0x0022, /* Reserved */
    HvCallReserved0023 = 0x0023, /* Reserved */
    HvCallReserved0024 = 0x0024, /* Reserved */
    HvCallReserved0025 = 0x0025, /* Reserved */
    HvCallReserved0026 = 0x0026, /* Reserved */
    HvCallReserved0027 = 0x0027, /* Reserved */
    HvCallReserved0028 = 0x0028, /* Reserved */
    HvCallReserved0029 = 0x0029, /* Reserved */
    HvCallReserved002a = 0x002A, /* Reserved */
    HvCallReserved002b = 0x002B, /* Reserved */
    HvCallReserved002c = 0x002C, /* Reserved */
    HvCallReserved002d = 0x002D, /* Reserved */
    HvCallReserved002e = 0x002E, /* Reserved */
    HvCallReserved002f = 0x002F, /* Reserved */
    HvCallReserved0030 = 0x0030, /* Reserved */
    HvCallReserved0031 = 0x0031, /* Reserved */
    HvCallReserved0032 = 0x0032, /* Reserved */
    HvCallReserved0033 = 0x0033, /* Reserved */
    HvCallReserved0034 = 0x0034, /* Reserved */
    HvCallReserved0035 = 0x0035, /* Reserved */
    HvCallReserved0036 = 0x0036, /* Reserved */
    HvCallReserved0037 = 0x0037, /* Reserved */
    HvCallReserved0038 = 0x0038, /* Reserved */
    HvCallReserved0039 = 0x0039, /* Reserved */
    HvCallReserved003a = 0x003A, /* Reserved */
    HvCallReserved003b = 0x003B, /* Reserved */
    HvCallReserved003c = 0x003C, /* Reserved */
    HvCallReserved003d = 0x003D, /* Reserved */
    HvCallReserved003e = 0x003E, /* Reserved */
    HvCallReserved003f = 0x003F, /* Reserved */
    HvCallCreatePartition = 0x0040,
    HvCallInitializePartition = 0x0041, /* Parent | Fast */
    HvCallFinalizePartition = 0x0042, /* Parent | Fast */
    HvCallDeletePartition = 0x0043, /* Parent | Fast */
    HvCallGetPartitionProperty = 0x0044, /* Parent | Root */
    HvCallSetPartitionProperty = 0x0045, /* Parent | Root */
    HvCallGetPartitionId = 0x0046,
    HvCallGetNextChildPartition = 0x0047, /* Parent */
    HvCallDepositMemory = 0x0048, /* Parent | Root | Rep */
    HvCallWithdrawMemory = 0x0049, /* Parent | Root | Rep */
    HvCallGetMemoryBalance = 0x004A, /* Parent | Root */
    HvCallMapGpaPages = 0x004B, /* Parent | Root | Rep */
    HvCallUnmapGpaPages = 0x004C, /* Parent | Rep */
    HvCallInstallIntercept = 0x004D, /* Parent */
    HvCallCreateVp = 0x004E, /* Parent */
    HvCallDeleteVp = 0x004F, /* Parent | Fast */
    HvCallGetVpRegisters = 0x0050, /* Public | Rep */
    HvCallSetVpRegisters = 0x0051, /* Public | Rep */
    HvCallTranslateVirtualAddress = 0x0052, /* Public */
    HvCallReadGpa = 0x0053, /* Parent */
    HvCallWriteGpa = 0x0054, /* Parent */
    HvCallAssertVirtualInterruptDeprecated = 0x0055, /* Parent */
    HvCallClearVirtualInterrupt = 0x0056, /* Parent | Fast */
    HvCallCreatePortDeprecated = 0x0057, /* Parent | Root */
    HvCallDeletePort = 0x0058, /* Parent | Root | Fast */
    HvCallConnectPortDeprecated = 0x0059, /* Parent | Root */
    HvCallGetPortProperty = 0x005A, /* Parent | Root */
    HvCallDisconnectPort = 0x005B, /* Parent | Root | Fast */
    HvCallPostMessage = 0x005C, /* Public */
    HvCallSignalEvent = 0x005D, /* Public | Fast */
    HvCallSavePartitionState = 0x005E, /* Parent | Root */
    HvCallRestorePartitionState = 0x005F, /* Parent | Root */
    HvCallInitializeEventLogBufferGroup = 0x0060, /* Root */
    HvCallFinalizeEventLogBufferGroup = 0x0061, /* Root | Fast */
    HvCallCreateEventLogBuffer = 0x0062, /* Root | Fast */
    HvCallDeleteEventLogBuffer = 0x0063, /* Root | Fast */
    HvCallMapEventLogBuffer = 0x0064, /* Root */
    HvCallUnmapEventLogBuffer = 0x0065, /* Root | Fast */
    HvCallSetEventLogGroupSources = 0x0066, /* Root | Fast */
    HvCallReleaseEventLogBuffer = 0x0067, /* Root | Fast */
    HvCallFlushEventLogBuffer = 0x0068, /* Root | Fast */
    HvCallPostDebugData = 0x0069,
    HvCallRetrieveDebugData = 0x006A,
    HvCallResetDebugSession = 0x006B, /* Fast */
    HvCallMapStatsPage = 0x006C, /* Parent */
    HvCallUnmapStatsPage = 0x006D, /* Parent */
    HvCallMapSparseGpaPages = 0x006E, /* Parent | Root | Rep */
    HvCallSetSystemProperty = 0x006F, /* Root */
    HvCallSetPortProperty = 0x0070, /* Parent | Root */
    HvCallOutputDebugCharacter = 0x0071, /* Reserved */
    HvCallEchoIncrement = 0x0072, /* Reserved */
    HvCallPerfNop = 0x0073, /* Reserved */
    HvCallPerfNopInput = 0x0074, /* Reserved */
    HvCallPerfNopOutput = 0x0075, /* Reserved */
    HvCallAddLogicalProcessor = 0x0076, /* Root */
    HvCallRemoveLogicalProcessor = 0x0077, /* Root */
    HvCallQueryNumaDistance = 0x0078, /* Root */
    HvCallSetLogicalProcessorProperty = 0x0079, /* Root */
    HvCallGetLogicalProcessorProperty = 0x007A, /* Root */
    HvCallGetSystemProperty = 0x007B,
    HvCallMapDeviceInterrupt = 0x007C, /* Root */
    HvCallUnmapDeviceInterrupt = 0x007D, /* Root */
    HvCallRetargetDeviceInterrupt = 0x007E, /* Public */
    HvCallReserved007f = 0x007F, /* Reserved | Root */
    HvCallMapDevicePages = 0x0080, /* Root */
    HvCallUnmapDevicePages = 0x0081, /* Root */
    HvCallAttachDevice = 0x0082, /* Root */
    HvCallDetachDevice = 0x0083, /* Root */
    HvCallNotifyStandbyTransition = 0x0084, /* Root */
    HvCallPrepareForSleep = 0x0085, /* Root */
    HvCallPrepareForHibernate = 0x0086, /* Root */
    HvCallNotifyPartitionEvent = 0x0087, /* Root */
    HvCallGetLogicalProcessorRegisters = 0x0088, /* Root */
    HvCallSetLogicalProcessorRegisters = 0x0089, /* Root */
    HvCallQueryAssociatedLpsforMca = 0x008A, /* Root */
    HvCallNotifyRingEmpty = 0x008B, /* Root */
    HvCallInjectSyntheticMachineCheck = 0x008C, /* Root */
    HvCallScrubPartition = 0x008D, /* Root */
    HvCallCollectLivedump = 0x008E, /* Root */
    HvCallDisableHypervisor = 0x008F, /* Root */
    HvCallModifySparseGpaPages = 0x0090, /* Root */
    HvCallRegisterInterceptResult = 0x0091, /* Root */
    HvCallUnregisterInterceptResult = 0x0092, /* Root */
    HvCallReserved0093 = 0x0093,
    HvCallAssertVirtualInterrupt = 0x0094, /* Public */
    HvCallCreatePort = 0x0095, /* Root */
    HvCallConnectPort = 0x0096, /* Root */
    HvCallGetSpaPageList = 0x0097, /* Root */
    HvCallReserved0098 = 0x0098, /* Reserved */
    HvCallStartVirtualProcessor = 0x0099, /* Public */
    HvCallGetVpIndexFromApicId = 0x009A, /* Public | Rep */
    HvCallReserved009b = 0x009B, /* Reserved */
    HvCallReserved009c = 0x009C, /* Reserved */
    HvCallReserved009d = 0x009D, /* Reserved */
    HvCallReserved009e = 0x009E, /* Reserved */
    HvCallReserved009f = 0x009F, /* Reserved */
    HvCallReserved00a0 = 0x00A0, /* Reserved */
    HvCallReserved00a1 = 0x00A1, /* Reserved */
    HvCallReserved00a2 = 0x00A2, /* Reserved */
    HvCallReserved00a3 = 0x00A3, /* Reserved */
    HvCallReserved00a4 = 0x00A4, /* Reserved */
    HvCallReserved00a5 = 0x00A5, /* Reserved */
    HvCallReserved00a6 = 0x00A6, /* Reserved */
    HvCallReserved00a7 = 0x00A7, /* Reserved */
    HvCallReserved00a8 = 0x00A8, /* Reserved */
    HvCallReserved00a9 = 0x00A9, /* Reserved */
    HvCallReserved00aa = 0x00AA, /* Reserved */
    HvCallReserved00ab = 0x00AB, /* Reserved */
    HvCallReserved00ac = 0x00AC, /* Reserved */
    HvCallReserved00ad = 0x00AD, /* Reserved */
    HvCallReserved00ae = 0x00AE, /* Reserved */
    HvCallFlushGuestPhysicalAddressSpace = 0x00AF, /* Public | Nested */
    HvCallFlushGuestPhysicalAddressList = 0x00B0, /* Public | Rep | Nested */
    HvCallReserved00b1 = 0x00B1, /* Undocumented */
    HvCallReserved00b2 = 0x00B2, /* Undocumented */
    HvCallReserved00b3 = 0x00B3, /* Undocumented */
    HvCallReserved00b4 = 0x00B4, /* Undocumented */
    HvCallReserved00b5 = 0x00B5, /* Undocumented */
    HvCallReserved00b6 = 0x00B6, /* Undocumented */
    HvCallReserved00b7 = 0x00B7, /* Undocumented */
    HvCallReserved00b8 = 0x00B8, /* Undocumented */
    HvCallReserved00b9 = 0x00B9, /* Undocumented */
    HvCallReserved00ba = 0x00BA, /* Undocumented */
    HvCallReserved00bb = 0x00BB, /* Undocumented */
    HvCallReserved00bc = 0x00BC, /* Undocumented */
    HvCallReserved00bd = 0x00BD, /* Undocumented */
    HvCallReserved00be = 0x00BE, /* Undocumented */
    HvCallReserved00bf = 0x00BF, /* Undocumented */
    HvCallSignalEventDirect = 0x00C0, /* Undocumented */
    HvCallPostMessageDirect = 0x00C1, /* Undocumented */
    HvCallDispatchVp = 0x00C2, /* Undocumented */
    HvCallReserved00c3 = 0x00C3, /* Undocumented */
    HvCallReserved00c4 = 0x00C4, /* Undocumented */
    HvCallReserved00c5 = 0x00C5, /* Undocumented */
    HvCallReserved00c6 = 0x00C6, /* Undocumented */
    HvCallReserved00c7 = 0x00C7, /* Undocumented */
    HvCallReserved00c8 = 0x00C8, /* Undocumented */
    HvCallGetGpaPagesAccessStates = 0x00C9, /* Undocumented */
    HvCallReserved00ca = 0x00CA, /* Undocumented */
    HvCallReserved00cb = 0x00CB, /* Undocumented */
    HvCallReserved00cc = 0x00CC, /* Undocumented */
    HvCallReserved00cd = 0x00CD, /* Undocumented */
    HvCallReserved00ce = 0x00CE, /* Undocumented */
    HvCallReserved00cf = 0x00CF, /* Undocumented */
    HvCallReserved00d0 = 0x00D0, /* Undocumented */
    HvCallReserved00d1 = 0x00D1, /* Undocumented */
    HvCallReserved00d2 = 0x00D2, /* Undocumented */
    HvCallReserved00d3 = 0x00D3, /* Undocumented */
    HvCallReserved00d4 = 0x00D4, /* Undocumented */
    HvCallReserved00d5 = 0x00D5, /* Undocumented */
    HvCallReserved00d6 = 0x00D6, /* Undocumented */
    HvCallReserved00d7 = 0x00D7, /* Undocumented */
    HvCallReserved00d8 = 0x00D8, /* Undocumented */
    HvCallReserved00d9 = 0x00D9, /* Undocumented */
    HvCallReserved00da = 0x00DA, /* Undocumented */
    HvCallReserved00db = 0x00DB, /* Undocumented */
    HvCallReserved00dc = 0x00DC, /* Undocumented */
    HvCallReserved00dd = 0x00DD, /* Undocumented */
    HvCallReserved00de = 0x00DE, /* Undocumented */
    HvCallReserved00df = 0x00DF, /* Undocumented */
    HvCallReserved00e0 = 0x00E0, /* Undocumented */
    HvCallMapVpStatePage = 0x00E1, /* Undocumented */
    HvCallUnmapVpStatePage = 0x00E2, /* Undocumented */
    HvCallGetVpState = 0x00E3, /* Undocumented */
    HvCallSetVpState = 0x00E4, /* Undocumented */
    HvCallReserved00e5 = 0x00E5, /* Undocumented */
    HvCallReserved00e6 = 0x00E6, /* Undocumented */
    HvCallReserved00e7 = 0x00E7, /* Undocumented */
    HvCallReserved00e8 = 0x00E8, /* Undocumented */
    HvCallReserved00e9 = 0x00E9, /* Undocumented */
    HvCallReserved00ea = 0x00EA, /* Undocumented */
    HvCallReserved00eb = 0x00EB, /* Undocumented */
    HvCallReserved00ec = 0x00EC, /* Undocumented */
    HvCallReserved00ed = 0x00ED, /* Undocumented */
    HvCallReserved00ee = 0x00EE, /* Undocumented */
    HvCallReserved00ef = 0x00EF, /* Undocumented */
    HvCallReserved00f0 = 0x00F0, /* Undocumented */
    HvCallReserved00f1 = 0x00F1, /* Undocumented */
    HvCallReserved00f2 = 0x00F2, /* Undocumented */
    HvCallReserved00f3 = 0x00F3, /* Undocumented */
    HvCallGetVpCpuidValues = 0x00F4, /* Undocumented */
    HvCallCount
} HV_CALL_CODE, *PHV_CALL_CODE;

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
/* nonstandard extension used : nameless struct/union */
#pragma warning(default:4201)
#endif
#endif

#endif /* !MILE_HYPERV_TLFS */
