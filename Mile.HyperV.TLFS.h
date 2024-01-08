/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.TLFS.h
 * PURPOSE:   Definition for Hyper-V Top Level Functional Specification 6.0b
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: MouriNaruto (Kenji.Mouri@Outlook.com)
 */

#ifndef MILE_HYPERV_TLFS
#define MILE_HYPERV_TLFS

#include <stdint.h>

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

typedef HV_SPA_PAGE_NUMBER* PHV_SPA_PAGE_NUMBER;
typedef HV_GPA_PAGE_NUMBER* PHV_GPA_PAGE_NUMBER;
typedef HV_GVA_PAGE_NUMBER* PHV_GVA_PAGE_NUMBER;
typedef HV_UINT64 HV_SPA_PAGE_NUMBER, * PHV_SPA_PAGE_NUMBER;
typedef HV_UINT64 HV_GPA_PAGE_NUMBER, * PHV_GPA_PAGE_NUMBER;
typedef HV_UINT64 HV_GVA_PAGE_NUMBER, * PHV_GVA_PAGE_NUMBER;
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

typedef struct _HV_PARTITION_PRIVILEGE_MASK
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

} HV_PARTITION_PRIVILEGE_MASK;

/*
 * Microsoft Hypervisor CPUID Leaves
 */

#define HV_CPUID_FUNCTION_VERSION_AND_FEATURES 0x00000001
#define HV_CPUID_FUNCTION_HV_VENDOR_AND_MAX_FUNCTION 0x40000000
#define HV_CPUID_FUNCTION_HV_INTERFACE 0x40000001
#define HV_CPUID_FUNCTION_MS_HV_VERSION 0x40000002
#define HV_CPUID_FUNCTION_MS_HV_FEATURES 0x40000003
#define HV_CPUID_FUNCTION_MS_HV_ENLIGHTENMENT_INFORMATION 0x40000004
#define HV_CPUID_FUNCTION_MS_HV_IMPLEMENTATION_LIMITS 0x40000005
#define HV_CPUID_FUNCTION_MS_HV_HARDWARE_FEATURES 0x40000006

#define HV_CPUID_HV_VENDOR_MICROSOFT "Microsoft Hv"
#define HV_CPUID_HV_VENDOR_MICROSOFT_EBX 0x7263694D /* "Micr" */
#define HV_CPUID_HV_VENDOR_MICROSOFT_ECX 0x666F736F /* "osof" */
#define HV_CPUID_HV_VENDOR_MICROSOFT_EDX 0x76482074 /* "t Hv" */

typedef struct _HV_VENDOR_AND_MAX_FUNCTION
{
    /* EAX */

    HV_UINT32 MaxFunction;

    /* EBX, ECX, EDX */

    HV_UINT8 VendorName[12];

} HV_VENDOR_AND_MAX_FUNCTION, *PHV_VENDOR_AND_MAX_FUNCTION;

#define HV_CPUID_INTERFACE_MICROSOFT_COMPATIBLE 0x31237648 /* "Hv#1" */
#define HV_CPUID_INTERFACE_MICROSOFT_XBOX_NANOVISOR 0x766E6258 /* "Xbnv" */

typedef struct _HV_HYPERVISOR_INTERFACE_INFO
{
    /* EAX */

    HV_UINT32 Interface;

    /* EBX, ECX, EDX */

    HV_UINT32 Reserved[3];

} HV_HYPERVISOR_INTERFACE_INFO, *PHV_HYPERVISOR_INTERFACE_INFO;

typedef struct _HV_HYPERVISOR_VERSION_INFO
{
    /* EAX */

    HV_UINT32 BuildNumber;

    /* EBX */

    HV_UINT32 MinorVersion : 16;
    HV_UINT32 MajorVersion : 16;

    /* ECX */

    HV_UINT32 ServicePack;

    /* EDX */

    HV_UINT32 ServiceNumber : 24;
    HV_UINT32 ServiceBranch : 8;

} HV_HYPERVISOR_VERSION_INFO, *PHV_HYPERVISOR_VERSION_INFO;

typedef struct _HV_X64_HYPERVISOR_FEATURES
{
    /* EAX, EBX */

    HV_PARTITION_PRIVILEGE_MASK PartitionPrivileges;

    /* ECX */

    HV_UINT32 Reserved1;

    /* EDX */

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
    HV_UINT32 Reserved2 : 3;

} HV_X64_HYPERVISOR_FEATURES, *PHV_X64_HYPERVISOR_FEATURES;

typedef struct _HV_X64_ENLIGHTENMENT_INFORMATION
{
    /* EAX */

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
    HV_UINT32 Reserved1 : 13;

    /* EBX */

    HV_UINT32 LongSpinWaitCount;

    /* ECX */

    HV_UINT32 ImplementedPhysicalAddressBits : 7;
    HV_UINT32 Reserved2 : 25;

    /* EDX */

    HV_UINT32 Reserved3;

} HV_X64_ENLIGHTENMENT_INFORMATION, * PHV_X64_ENLIGHTENMENT_INFORMATION;

typedef struct _HV_IMPLEMENTATION_LIMITS
{
    /* EAX */

    HV_UINT32 MaxVirtualProcessorCount;

    /* EBX */

    HV_UINT32 MaxLogicalProcessorCount;

    /* ECX */

    HV_UINT32 MaxInterruptMappingCount;

    /* EDX */

    HV_UINT32 Reserved;

} HV_IMPLEMENTATION_LIMITS, * PHV_IMPLEMENTATION_LIMITS;

typedef struct _HV_X64_HYPERVISOR_HARDWARE_FEATURES
{
    /* EAX */

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
    HV_UINT32 Reserved1 : 22;

    /* EBX, ECX, EDX */

    HV_UINT32 Reserved2[3];

} HV_X64_HYPERVISOR_HARDWARE_FEATURES, * PHV_X64_HYPERVISOR_HARDWARE_FEATURES;

#endif /* !MILE_HYPERV_TLFS */
