/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.Guest.Interface.h
 * PURPOSE:   Definition for Hyper-V Guest Publicized Interface
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

// References
// - Hyper-V Generation 2 Virtual Machine UEFI Firmware
//   - MsvmPkg\Include\Hv\HvStatus.h
//   - MsvmPkg\Include\Hv\HvGuest.h
//   - MsvmPkg\Include\Hv\HvGuestCpuid.h

#ifndef MILE_HYPERV_GUEST_INTERFACE
#define MILE_HYPERV_GUEST_INTERFACE

#if !defined(_M_AMD64) && !defined(_M_ARM64)
#error [Mile.HyperV] Unknown/Unsupported architecture
#endif

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif
#pragma warning(disable:4201) // nameless struct/union
#endif

#include <stdint.h>

typedef uint8_t HV_UINT8, *PHV_UINT8;
typedef uint16_t HV_UINT16, *PHV_UINT16;
typedef uint32_t HV_UINT32, *PHV_UINT32;
typedef uint64_t HV_UINT64, *PHV_UINT64;

// *****************************************************************************
// HV_STATUS Definitions
//

// Status codes for hypervisor operations.
typedef HV_UINT16 HV_STATUS, *PHV_STATUS;

// The specified hypercall succeeded.
#define HV_STATUS_SUCCESS ((HV_STATUS)0x0000)

// The hypervisor does not support the operation because the specified hypercall
// code is not supported.
#define HV_STATUS_INVALID_HYPERCALL_CODE ((HV_STATUS)0x0002)

// The hypervisor does not support the operation because the encoding for the
// hypercall input register is not supported.
#define HV_STATUS_INVALID_HYPERCALL_INPUT ((HV_STATUS)0x0003)

// The hypervisor could not perform the operation because a parameter has an
// invalid alignment.
#define HV_STATUS_INVALID_ALIGNMENT ((HV_STATUS)0x0004)

// The hypervisor could not perform the operation because an invalid parameter
// was specified.
#define HV_STATUS_INVALID_PARAMETER ((HV_STATUS)0x0005)

// Access to the specified object was denied.
#define HV_STATUS_ACCESS_DENIED ((HV_STATUS)0x0006)

// The hypervisor could not perform the operation because the partition is
// entering or in an invalid state.
#define HV_STATUS_INVALID_PARTITION_STATE ((HV_STATUS)0x0007)

// The operation is not allowed in the current state.
#define HV_STATUS_OPERATION_DENIED ((HV_STATUS)0x0008)

// The hypervisor does not recognize the specified partition property.
#define HV_STATUS_UNKNOWN_PROPERTY ((HV_STATUS)0x0009)

// The specified value of a partition property is out of range or violates an
// invariant.
#define HV_STATUS_PROPERTY_VALUE_OUT_OF_RANGE ((HV_STATUS)0x000A)

// There is not enough memory in the hypervisor pool to complete the operation.
#define HV_STATUS_INSUFFICIENT_MEMORY ((HV_STATUS)0x000B)

// The maximum partition depth has been exceeded for the partition hierarchy.
#define HV_STATUS_PARTITION_TOO_DEEP ((HV_STATUS)0x000C)

// A partition with the specified partition ID does not exist.
#define HV_STATUS_INVALID_PARTITION_ID ((HV_STATUS)0x000D)

// The hypervisor could not perform the operation because the specified VP index
// is invalid.
#define HV_STATUS_INVALID_VP_INDEX ((HV_STATUS)0x000E)

// The iteration is complete; no addition items in the iteration could be found.
#define HV_STATUS_NOT_FOUND ((HV_STATUS)0x0010)

// The hypervisor could not perform the operation because the specified port
// identifier is invalid.
#define HV_STATUS_INVALID_PORT_ID ((HV_STATUS)0x0011)

// The hypervisor could not perform the operation because the specified
// connection identifier is invalid.
#define HV_STATUS_INVALID_CONNECTION_ID ((HV_STATUS)0x0012)

// You did not supply enough message buffers to send a message.
#define HV_STATUS_INSUFFICIENT_BUFFERS ((HV_STATUS)0x0013)

// The previous virtual interrupt has not been acknowledged.
#define HV_STATUS_NOT_ACKNOWLEDGED ((HV_STATUS)0x0014)

// A virtual processor is not in the correct state for the performance of the
// indicated operation.
#define HV_STATUS_INVALID_VP_STATE ((HV_STATUS)0x0015)

// The previous virtual interrupt has already been acknowledged.
#define HV_STATUS_ACKNOWLEDGED ((HV_STATUS)0x0016)

// The indicated partition is not in a valid state for saving or restoring.
#define HV_STATUS_INVALID_SAVE_RESTORE_STATE ((HV_STATUS)0x0017)

// The hypervisor could not complete the operation because a required feature of
// the synthetic interrupt controller (SynIC) was disabled.
#define HV_STATUS_INVALID_SYNIC_STATE ((HV_STATUS)0x0018)

// The hypervisor could not perform the operation because the object or value
// was either already in use or being used for a purpose that would not permit
// completing the operation.
#define HV_STATUS_OBJECT_IN_USE ((HV_STATUS)0x0019)

// The proximity domain information is invalid.
#define HV_STATUS_INVALID_PROXIMITY_DOMAIN_INFO ((HV_STATUS)0x001A)

// An attempt to retrieve debugging data failed because none was available.
#define HV_STATUS_NO_DATA ((HV_STATUS)0x001B)

// The physical connection being used for debuggging has not recorded any
// receive activity since the last operation.
#define HV_STATUS_INACTIVE ((HV_STATUS)0x001C)

// There are not enough resources to complete the operation.
#define HV_STATUS_NO_RESOURCES ((HV_STATUS)0x001D)

// A hypervisor feature is not available to the user.
#define HV_STATUS_FEATURE_UNAVAILABLE ((HV_STATUS)0x001E)

// The debug packet returned is only a partial packet due to an io error.
#define HV_STATUS_PARTIAL_PACKET ((HV_STATUS)0x001F)

// The supplied restore state requires an unsupported processor feature.
#define HV_STATUS_PROCESSOR_FEATURE_NOT_SUPPORTED ((HV_STATUS)0x0020)

// The supplied restore state requires requires a processor with a different
// cache line flush size.
#define HV_STATUS_PROCESSOR_CACHE_LINE_FLUSH_SIZE_INCOMPATIBLE ((HV_STATUS)0x0030)

// The specified buffer was too small to contain all of the requested data.
#define HV_STATUS_INSUFFICIENT_BUFFER ((HV_STATUS)0x0033)

// The supplied restore state is for an incompatible processor vendor.
#define HV_STATUS_INCOMPATIBLE_PROCESSOR ((HV_STATUS)0x0037)

// The maximum number of domains supported by the platform I/O remapping
// hardware is currently in use. No domains are available to assign this device
// to this partition.
#define HV_STATUS_INSUFFICIENT_DEVICE_DOMAINS ((HV_STATUS)0x0038)

// Generic logical processor CPUID feature set validation error.
#define HV_STATUS_CPUID_FEATURE_VALIDATION_ERROR ((HV_STATUS)0x003C)

// CPUID XSAVE feature validation error.
#define HV_STATUS_CPUID_XSAVE_FEATURE_VALIDATION_ERROR ((HV_STATUS)0x003D)

// Processor startup timed out.
#define HV_STATUS_PROCESSOR_STARTUP_TIMEOUT ((HV_STATUS)0x003E)

// SMX enabled by the BIOS.
#define HV_STATUS_SMX_ENABLED ((HV_STATUS)0x003F)

// The hypervisor could not perform the operation because the specified LP index
// is invalid.
#define HV_STATUS_INVALID_LP_INDEX ((HV_STATUS)0x0041)

// The supplied register value is invalid.
#define HV_STATUS_INVALID_REGISTER_VALUE ((HV_STATUS)0x0050)

// The supplied virtual trust level is not in the correct state to perform the
// requested operation.
#define HV_STATUS_INVALID_VTL_STATE ((HV_STATUS)0x0051)

// NX not detected on the machine.
#define HV_STATUS_NX_NOT_DETECTED ((HV_STATUS)0x0055)

// The supplied device ID is invalid.
#define HV_STATUS_INVALID_DEVICE_ID ((HV_STATUS)0x0057)

// The operation is not allowed in the current device state.
#define HV_STATUS_INVALID_DEVICE_STATE ((HV_STATUS)0x0058)

// The device had pending page requests which were discarded.
#define HV_STATUS_PENDING_PAGE_REQUESTS ((HV_STATUS)0x0059)

// The supplied page request specifies a memory access that the guest does not
// have permissions to perform.
#define HV_STATUS_PAGE_REQUEST_INVALID ((HV_STATUS)0x0060)

// The entry cannot be added as another entry with the same key already exists.
#define HV_STATUS_KEY_ALREADY_EXISTS ((HV_STATUS)0x0065)

// The device is already attached to the device domain.
#define HV_STATUS_DEVICE_ALREADY_IN_DOMAIN ((HV_STATUS)0x0066)

// A CPU group with the specified CPU group Id does not exist.
#define HV_STATUS_INVALID_CPU_GROUP_ID ((HV_STATUS)0x006F)

// The hypervisor could not perform the operation because the CPU group is
// entering or in an invalid state.
#define HV_STATUS_INVALID_CPU_GROUP_STATE ((HV_STATUS)0x0070)

// The requested operation failed.
#define HV_STATUS_OPERATION_FAILED ((HV_STATUS)0x0071)

// The requested operation is not allowed due to one or more virtual processors
// having nested virtualization active.
#define HV_STATUS_NOT_ALLOWED_WITH_NESTED_VIRT_ACTIVE ((HV_STATUS)0x0072)

// There is not enough memory in the root partition's pool to complete the
// operation.
#define HV_STATUS_INSUFFICIENT_ROOT_MEMORY ((HV_STATUS)0x0073)

// *****************************************************************************
// Basic Type Definitions
//

#define HV_MAXIMUM_PROCESSORS 2048

// Memory Types
//
// Guest physical addresses (GPAs) define the guest's view of physical memory.
// GPAs can be mapped to underlying SPAs. There is one guest physical address
// space per partition.
//
// Guest virtual addresses (GVAs) are used within the guest when it enables
// address translation and provides a valid guest page table.

typedef HV_UINT64 HV_GPA, *PHV_GPA;
typedef HV_UINT64 HV_GPA_PAGE_NUMBER, *PHV_GPA_PAGE_NUMBER;

typedef HV_UINT64 HV_GVA, *PHV_GVA;

#if defined(_M_ARM64)

#define HV_ARM64_PAGE_SIZE 4096
#define HV_ARM64_LARGE_PAGE_SIZE 0x200000
#define HV_ARM64_LARGE_PAGE_SIZE_1GB 0x40000000
#define HV_PAGE_SIZE HV_ARM64_PAGE_SIZE
#define HV_LARGE_PAGE_SIZE HV_ARM64_LARGE_PAGE_SIZE
#define HV_LARGE_PAGE_SIZE_1GB HV_ARM64_LARGE_PAGE_SIZE_1GB

#define HV_ARM64_HVC_IMM16 1
#define HV_ARM64_HVC_VTLENTRY_IMM16 2
#define HV_ARM64_HVC_VTLEXIT_IMM16 3
#define HV_ARM64_HVC_LAUNCH_IMM16 4
#define HV_ARM64_HVC_LAUNCH_SL_IMM16 5

// The HVC immediate below is handled by the Microvisor for GICv3 support in the
// absence of the full Hypervisor.
#define HV_ARM64_ENABLE_SRE 2

#elif defined(_M_AMD64)

#define HV_X64_PAGE_SIZE 4096
#define HV_X64_LARGE_PAGE_SIZE 0x200000
#define HV_X64_LARGE_PAGE_SIZE_1GB 0x40000000
#define HV_PAGE_SIZE HV_X64_PAGE_SIZE
#define HV_LARGE_PAGE_SIZE HV_X64_LARGE_PAGE_SIZE
#define HV_LARGE_PAGE_SIZE_1GB HV_X64_LARGE_PAGE_SIZE_1GB

#endif

// Define partition identifier type.
typedef HV_UINT64 HV_PARTITION_ID, *PHV_PARTITION_ID;

// Define invalid partition identifier and "self" partition identifier.

#define HV_PARTITION_ID_INVALID ((HV_PARTITION_ID)0x0)
#define HV_PARTITION_ID_SELF ((HV_PARTITION_ID)-1)

// Time in the hypervisor is measured in 100 nanosecond units.

typedef HV_UINT64 HV_NANO100_TIME, *PHV_NANO100_TIME;
typedef HV_UINT64 HV_NANO100_DURATION, *PHV_NANO100_DURATION;

#define HV_NANO100_TIME_NEVER ((HV_NANO100_TIME)-1)

typedef HV_UINT32 HV_IOMMU_ID, *PHV_IOMMU_ID;

// Define the intercept access types.
typedef HV_UINT8 HV_INTERCEPT_ACCESS_TYPE;

// Virtual Processor Indices
typedef HV_UINT32 HV_VP_INDEX, *PHV_VP_INDEX;

// VSM Definitions
// Define a virtual trust level (VTL)
typedef HV_UINT8 HV_VTL, *PHV_VTL;

// Flags to describe the access a partition has to a GPA page.
typedef HV_UINT32 HV_MAP_GPA_FLAGS, *PHV_MAP_GPA_FLAGS;

#if defined(_M_AMD64)
typedef struct _HV_X64_SEGMENT_REGISTER
{
    HV_UINT64 Base;
    HV_UINT32 Limit;
    HV_UINT16 Selector;
    union
    {
        struct
        {
            HV_UINT16 SegmentType : 4;
            HV_UINT16 NonSystemSegment : 1;
            HV_UINT16 DescriptorPrivilegeLevel : 2;
            HV_UINT16 Present : 1;
            HV_UINT16 Reserved : 4;
            HV_UINT16 Available : 1;
            HV_UINT16 Long : 1;
            HV_UINT16 Default : 1;
            HV_UINT16 Granularity : 1;
        };
        HV_UINT16 Attributes;
    };
} HV_X64_SEGMENT_REGISTER, *PHV_X64_SEGMENT_REGISTER;
#endif

#if defined(_M_AMD64)
typedef struct _HV_X64_TABLE_REGISTER
{
    HV_UINT16 Pad[3];
    HV_UINT16 Limit;
    HV_UINT64 Base;
} HV_X64_TABLE_REGISTER, *PHV_X64_TABLE_REGISTER;
#endif

// Initial X64 VP context for a newly enabled VTL
typedef struct _HV_INITIAL_VP_CONTEXT
{
#if defined(_M_ARM64)

    HV_UINT64 Pc;
    HV_UINT64 Sp_ELh;
    HV_UINT64 SCTLR_EL1;
    HV_UINT64 MAIR_EL1;
    HV_UINT64 TCR_EL1;
    HV_UINT64 VBAR_EL1;
    HV_UINT64 TTBR0_EL1;
    HV_UINT64 TTBR1_EL1;
    HV_UINT64 X18;

#elif defined(_M_AMD64)

    HV_UINT64 Rip;
    HV_UINT64 Rsp;
    HV_UINT64 Rflags;

    // Segment selector registers together with their hidden state.

    HV_X64_SEGMENT_REGISTER Cs;
    HV_X64_SEGMENT_REGISTER Ds;
    HV_X64_SEGMENT_REGISTER Es;
    HV_X64_SEGMENT_REGISTER Fs;
    HV_X64_SEGMENT_REGISTER Gs;
    HV_X64_SEGMENT_REGISTER Ss;
    HV_X64_SEGMENT_REGISTER Tr;
    HV_X64_SEGMENT_REGISTER Ldtr;

    // Global and Interrupt Descriptor tables

    HV_X64_TABLE_REGISTER Idtr;
    HV_X64_TABLE_REGISTER Gdtr;

    // Control registers and MSR's

    HV_UINT64 Efer;
    HV_UINT64 Cr0;
    HV_UINT64 Cr3;
    HV_UINT64 Cr4;
    HV_UINT64 MsrCrPat;

#endif
} HV_INITIAL_VP_CONTEXT, *PHV_INITIAL_VP_CONTEXT;

// HV Map GPA (Guest Physical Address) Flags
// Definitions of flags to describe the access a partition has to a GPA page.
// (used with HV_MAP_GPA_FLAGS).
// The first byte is reserved for permissions.

#define HV_MAP_GPA_PERMISSIONS_NONE 0x0
#define HV_MAP_GPA_READABLE 0x1
#define HV_MAP_GPA_WRITABLE 0x2

// *****************************************************************************
// CPUID Definitions
//

// Microsoft hypervisor interface signature.
typedef enum _HV_HYPERVISOR_INTERFACE
{
    HvMicrosoftHypervisorInterface = '1#vH'
} HV_HYPERVISOR_INTERFACE, *PHV_HYPERVISOR_INTERFACE;

// Version info reported by hypervisors
typedef struct _HV_HYPERVISOR_VERSION_INFO
{
    HV_UINT32 BuildNumber;

    HV_UINT32 MinorVersion : 16;
    HV_UINT32 MajorVersion : 16;

    HV_UINT32 ServicePack;

    HV_UINT32 ServiceNumber : 24;
    HV_UINT32 ServiceBranch : 8; // Type is HV_SERVICE_BRANCH
} HV_HYPERVISOR_VERSION_INFO, *PHV_HYPERVISOR_VERSION_INFO;

// VM Partition Privileges mask. Please also update the bitmask along with the
// below union.
typedef union _HV_PARTITION_PRIVILEGE_MASK
{
    HV_UINT64 AsUINT64;
    struct
    {
        // Access to virtual MSRs

        HV_UINT64 AccessVpRunTimeReg : 1;
        HV_UINT64 AccessPartitionReferenceCounter : 1;
        HV_UINT64 AccessSynicRegs : 1;
        HV_UINT64 AccessSyntheticTimerRegs : 1;
        HV_UINT64 AccessIntrCtrlRegs : 1;
        HV_UINT64 AccessHypercallMsrs : 1;
        HV_UINT64 AccessVpIndex : 1;
        HV_UINT64 AccessResetReg : 1;
        HV_UINT64 AccessStatsReg : 1;
        HV_UINT64 AccessPartitionReferenceTsc : 1;
        HV_UINT64 AccessGuestIdleReg : 1;
        HV_UINT64 AccessFrequencyRegs : 1;
        HV_UINT64 AccessDebugRegs : 1;
        HV_UINT64 AccessReenlightenmentControls : 1;
        HV_UINT64 AccessRootSchedulerReg : 1;
        HV_UINT64 Reserved1 : 17;

        // Access to hypercalls

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
        HV_UINT64 EnableExtendedGvaRangesForFlushVirtualAddressList : 1;
        HV_UINT64 AccessVsm : 1;
        HV_UINT64 AccessVpRegisters : 1;
        HV_UINT64 UnusedBit : 1;
        HV_UINT64 FastHypercallOutput : 1;
        HV_UINT64 EnableExtendedHypercalls : 1;
        HV_UINT64 StartVirtualProcessor : 1;
        HV_UINT64 Isolation : 1;
        HV_UINT64 Reserved3 : 9;
    };
} HV_PARTITION_PRIVILEGE_MASK, *PHV_PARTITION_PRIVILEGE_MASK;

#if defined(_M_AMD64)
typedef union _HV_X64_PLATFORM_CAPABILITIES
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        // Eax

        HV_UINT32 AllowRedSignedCode : 1;
        HV_UINT32 AllowKernelModeDebugging : 1;
        HV_UINT32 AllowUserModeDebugging : 1;
        HV_UINT32 AllowTelnetServer : 1;
        HV_UINT32 AllowIOPorts : 1;
        HV_UINT32 AllowFullMsrSpace : 1;
        HV_UINT32 AllowPerfCounters : 1;
        HV_UINT32 AllowHost512MB : 1;
        HV_UINT32 ReservedEax1 : 1;
        HV_UINT32 AllowRemoteRecovery : 1;
        HV_UINT32 AllowStreaming : 1;
        HV_UINT32 AllowPushDeployment : 1;
        HV_UINT32 AllowPullDeployment : 1;
        HV_UINT32 AllowProfiling : 1;
        HV_UINT32 AllowJsProfiling : 1;
        HV_UINT32 AllowCrashDump : 1;
        HV_UINT32 AllowVsCrashDump : 1;
        HV_UINT32 AllowToolFileIO : 1;
        HV_UINT32 AllowConsoleMgmt : 1;
        HV_UINT32 AllowTracing : 1;
        HV_UINT32 AllowXStudio : 1;
        HV_UINT32 AllowGestureBuilder : 1;
        HV_UINT32 AllowSpeechLab : 1;
        HV_UINT32 AllowSmartglassStudio : 1;
        HV_UINT32 AllowNetworkTools : 1;
        HV_UINT32 AllowTcrTool : 1;
        HV_UINT32 AllowHostNetworkStack : 1;
        HV_UINT32 AllowSystemUpdateTest : 1;
        HV_UINT32 AllowOffChipPerfCtrStreaming : 1;
        HV_UINT32 AllowToolingMemory : 1;
        HV_UINT32 AllowSystemDowngrade : 1;
        HV_UINT32 AllowGreenDiskLicenses : 1;

        // Ebx

        HV_UINT32 IsLiveConnected : 1;
        HV_UINT32 IsMteBoosted : 1;
        HV_UINT32 IsQaSlt : 1;
        HV_UINT32 IsStockImage : 1;
        HV_UINT32 IsMsTestLab : 1;
        HV_UINT32 IsRetailDebugger : 1;
        HV_UINT32 IsXvdSrt : 1;
        HV_UINT32 IsGreenDebug : 1;
        HV_UINT32 IsHwDevTest : 1;
        HV_UINT32 AllowDiskLicenses : 1;
        HV_UINT32 AllowInstrumentation : 1;
        HV_UINT32 AllowWifiTester : 1;
        HV_UINT32 AllowWifiTesterDFS : 1;
        HV_UINT32 IsHwTest : 1;
        HV_UINT32 AllowHostOddTest : 1;
        HV_UINT32 IsLiveUnrestricted : 1;
        HV_UINT32 AllowDiscLicensesWithoutMediaAuth : 1;
        HV_UINT32 ReservedEbx : 15;

        // Ecx

        HV_UINT32 ReservedEcx;

        // Edx

        HV_UINT32 ReservedEdx : 31;
        HV_UINT32 UseAlternateXvd : 1;
    };
} HV_X64_PLATFORM_CAPABILITIES, *PHV_X64_PLATFORM_CAPABILITIES;
#endif

// Typedefs for CPUID leaves on HvMicrosoftHypercallInterface-supporting
// hypervisors.
//
// The below CPUID leaves are present if VersionAndFeatures.HypervisorPresent is
// set by CPUID(HvCpuIdFunctionVersionAndFeatures).
typedef enum _HV_CPUID_FUNCTION
{
    HvCpuIdFunctionVersionAndFeatures = 0x00000001,
    HvCpuIdFunctionHvVendorAndMaxFunction = 0x40000000,
    HvCpuIdFunctionHvInterface = 0x40000001,

    // The remaining functions depend on the value of HvCpuIdFunctionInterface

    HvCpuIdFunctionMsHvVersion = 0x40000002,
    HvCpuIdFunctionMsHvFeatures = 0x40000003,
    HvCpuIdFunctionMsHvEnlightenmentInformation = 0x40000004,
    HvCpuIdFunctionMsHvImplementationLimits = 0x40000005,
    HvCpuIdFunctionMsHvHardwareFeatures = 0x40000006,
    HvCpuIdFunctionMsHvCpuManagementFeatures = 0x40000007,
    HvCpuIdFunctionMsHvSvmFeatures = 0x40000008,
    HvCpuIdFunctionMsHvSkipLevelFeatures = 0x40000009,
    HvCpuidFunctionMsHvNestedVirtFeatures = 0x4000000A,
    HvCpuidFunctionMsHvIsolationConfiguration = 0x4000000C,
    HvCpuIdFunctionMaxReserved = 0x4000000C
} HV_CPUID_FUNCTION, *PHV_CPUID_FUNCTION;

// Hypervisor Vendor Info - HvCpuIdFunctionHvVendorAndMaxFunction Leaf
typedef struct _HV_VENDOR_AND_MAX_FUNCTION
{
    HV_UINT32 MaxFunction;
    HV_UINT8 VendorName[12];
} HV_VENDOR_AND_MAX_FUNCTION, *PHV_VENDOR_AND_MAX_FUNCTION;

// Hypervisor Interface Info - HvCpuIdFunctionHvInterface Leaf
typedef struct _HV_HYPERVISOR_INTERFACE_INFO
{
    HV_UINT32 Interface; // HV_HYPERVISOR_INTERFACE
    HV_UINT32 Reserved1;
    HV_UINT32 Reserved2;
    HV_UINT32 Reserved3;
} HV_HYPERVISOR_INTERFACE_INFO, *PHV_HYPERVISOR_INTERFACE_INFO;

// Hypervisor Feature Information - HvCpuIdFunctionMsHvFeatures Leaf
#if defined(_M_AMD64)
typedef struct _HV_X64_HYPERVISOR_FEATURES
{
    // Eax-Ebx

    HV_PARTITION_PRIVILEGE_MASK PartitionPrivileges;

    // Ecx - this indicates the power configuration for the current VP.

    HV_UINT32 MaxSupportedCState : 4;
    HV_UINT32 HpetNeededForC3PowerState_Deprecated : 1;
    HV_UINT32 Reserved : 27;

    // Edx

    HV_UINT32 MwaitAvailable_Deprecated : 1;
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
    HV_UINT32 PasidFeaturesAvailable : 1;
    HV_UINT32 SintPollingModeAvailable : 1;
    HV_UINT32 HypercallMsrLockAvailable : 1;
    HV_UINT32 DirectSyntheticTimers : 1;
    HV_UINT32 RegisterPatAvailable : 1;
    HV_UINT32 RegisterBndcfgsAvailable : 1;
    HV_UINT32 WatchdogTimerAvailable : 1;
    HV_UINT32 SyntheticTimeUnhaltedTimerAvailable : 1;
    HV_UINT32 DeviceDomainsAvailable : 1; // HDK only.
    HV_UINT32 S1DeviceDomainsAvailable : 1; // HDK only.
    HV_UINT32 Reserved1 : 6;
} HV_X64_HYPERVISOR_FEATURES, *PHV_X64_HYPERVISOR_FEATURES;
typedef _HV_X64_HYPERVISOR_FEATURES _HV_HYPERVISOR_FEATURES;
typedef HV_X64_HYPERVISOR_FEATURES HV_HYPERVISOR_FEATURES;
typedef PHV_X64_HYPERVISOR_FEATURES PHV_HYPERVISOR_FEATURES;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERVISOR_FEATURES
{
    HV_PARTITION_PRIVILEGE_MASK PartitionPrivileges;

    HV_UINT32 GuestDebuggingAvailable : 1;
    HV_UINT32 PerformanceMonitorsAvailable : 1;
    HV_UINT32 CpuDynamicPartitioningAvailable : 1;
    HV_UINT32 GuestIdleAvailable : 1;
    HV_UINT32 HypervisorSleepStateSupportAvailable : 1;
    HV_UINT32 NumaDistanceQueryAvailable : 1;
    HV_UINT32 FrequencyRegsAvailable : 1;
    HV_UINT32 SyntheticMachineCheckAvailable : 1;
    HV_UINT32 GuestCrashRegsAvailable : 1;
    HV_UINT32 DebugRegsAvailable : 1;
    HV_UINT32 DisableHypervisorAvailable : 1;
    HV_UINT32 ExtendedGvaRangesForFlushVirtualAddressListAvailable : 1;
    HV_UINT32 SintPollingModeAvailable : 1;
    HV_UINT32 DirectSyntheticTimers : 1;
    HV_UINT32 DeviceDomainsAvailable : 1; // HDK only.
    HV_UINT32 S1DeviceDomainsAvailable : 1; // HDK only.
    HV_UINT32 Reserved1 : 16;
} HV_ARM64_HYPERVISOR_FEATURES, *PHV_ARM64_HYPERVISOR_FEATURES;
typedef _HV_ARM64_HYPERVISOR_FEATURES _HV_HYPERVISOR_FEATURES;
typedef HV_ARM64_HYPERVISOR_FEATURES HV_HYPERVISOR_FEATURES;
typedef PHV_ARM64_HYPERVISOR_FEATURES PHV_HYPERVISOR_FEATURES;
#endif

// Enlightenment Info - HvCpuIdFunctionMsHvEnlightenmentInformation Leaf
#if defined(_M_AMD64)
typedef struct _HV_X64_ENLIGHTENMENT_INFORMATION
{
    // Eax

    HV_UINT32 UseHypercallForAddressSpaceSwitch : 1;
    HV_UINT32 UseHypercallForLocalFlush : 1;
    HV_UINT32 UseHypercallForRemoteFlushAndLocalFlushEntire : 1;
    HV_UINT32 UseApicMsrs : 1;
    HV_UINT32 UseHvRegisterForReset : 1;
    HV_UINT32 UseRelaxedTiming : 1;
    HV_UINT32 UseDmaRemapping_Deprecated : 1;
    HV_UINT32 UseInterruptRemapping_Deprecated : 1;
    HV_UINT32 UseX2ApicMsrs : 1;
    HV_UINT32 DeprecateAutoEoi : 1;
    HV_UINT32 UseSyntheticClusterIpi : 1;
    HV_UINT32 UseExProcessorMasks : 1;
    HV_UINT32 Nested : 1;
    HV_UINT32 UseIntForMbecSystemCalls : 1;
    HV_UINT32 UseVmcsEnlightenments : 1;
    HV_UINT32 UseSyncedTimeline : 1;
    // Was UseReferencePageForSyncedTimeline but never consumed.
    HV_UINT32 Available : 1;
    HV_UINT32 UseDirectLocalFlushEntire : 1;
    HV_UINT32 Reserved : 14;

    // Ebx

    HV_UINT32 LongSpinWaitCount;

    // Ecx

    HV_UINT32 ReservedEcx;

    // Edx

    HV_UINT32 ReservedEdx;
} HV_X64_ENLIGHTENMENT_INFORMATION, *PHV_X64_ENLIGHTENMENT_INFORMATION;
typedef _HV_X64_ENLIGHTENMENT_INFORMATION _HV_ENLIGHTENMENT_INFORMATION;
typedef HV_X64_ENLIGHTENMENT_INFORMATION HV_ENLIGHTENMENT_INFORMATION;
typedef PHV_X64_ENLIGHTENMENT_INFORMATION PHV_ENLIGHTENMENT_INFORMATION;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_ENLIGHTENMENT_INFORMATION
{
    HV_UINT32 UseHvRegisterForReset : 1;
    HV_UINT32 UseRelaxedTiming : 1;
    HV_UINT32 UseSyntheticClusterIpi : 1;
    HV_UINT32 UseExProcessorMasks : 1;
    HV_UINT32 Nested : 1;
    HV_UINT32 UseSyncedTimeline : 1;
    HV_UINT32 Reserved : 26;

    HV_UINT32 LongSpinWaitCount;

    HV_UINT32 Reserved0;
    HV_UINT32 Reserved1;
} HV_ARM64_ENLIGHTENMENT_INFORMATION, *PHV_ARM64_ENLIGHTENMENT_INFORMATION;
typedef _HV_ARM64_ENLIGHTENMENT_INFORMATION _HV_ENLIGHTENMENT_INFORMATION;
typedef HV_ARM64_ENLIGHTENMENT_INFORMATION HV_ENLIGHTENMENT_INFORMATION;
typedef PHV_ARM64_ENLIGHTENMENT_INFORMATION PHV_ENLIGHTENMENT_INFORMATION;
#endif

// Implementation Limits - HvCpuIdFunctionMsHvImplementationLimits Leaf
typedef struct _HV_IMPLEMENTATION_LIMITS
{
    // Eax

    HV_UINT32 MaxVirtualProcessorCount;

    // Ebx

    HV_UINT32 MaxLogicalProcessorCount;

    // Ecx

    HV_UINT32 MaxInterruptMappingCount;

    // Edx

    HV_UINT32 Reserved;
} HV_IMPLEMENTATION_LIMITS, *PHV_IMPLEMENTATION_LIMITS;

// Hypervisor Hardware Features Info - HvCpuIdFunctionMsHvHardwareFeatures Leaf
#if defined(_M_AMD64)
typedef struct _HV_X64_HYPERVISOR_HARDWARE_FEATURES
{
    // Eax

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
    HV_UINT32 HypervisorLevel : 4;
    HV_UINT32 PhysicalDestinationModeRequired : 1;
    HV_UINT32 UseVmfuncForAliasMapSwitch : 1;
    HV_UINT32 HvRegisterForMemoryZeroingSupported : 1;
    HV_UINT32 UnrestrictedGuestSupported : 1;
    HV_UINT32 L3CachePartitioningSupported : 1;
    HV_UINT32 L3CacheMonitoringSupported : 1;
    HV_UINT32 Reserved : 12;

    // Ebx

    HV_UINT32 ReservedEbx;

    // Ecx

    HV_UINT32 ReservedEcx;

    // Edx

    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_HARDWARE_FEATURES, *PHV_X64_HYPERVISOR_HARDWARE_FEATURES;
typedef _HV_X64_HYPERVISOR_HARDWARE_FEATURES _HV_HYPERVISOR_HARDWARE_FEATURES;
typedef HV_X64_HYPERVISOR_HARDWARE_FEATURES HV_HYPERVISOR_HARDWARE_FEATURES;
typedef PHV_X64_HYPERVISOR_HARDWARE_FEATURES PHV_HYPERVISOR_HARDWARE_FEATURES;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERVISOR_HARDWARE_FEATURES
{
    HV_UINT32 ArchitecturalPerformanceCountersInUse : 1;
    HV_UINT32 SecondLevelAddressTranslationInUse : 1;
    HV_UINT32 DmaRemappingInUse : 1;
    HV_UINT32 InterruptRemappingInUse : 1;
    HV_UINT32 MemoryPatrolScrubberPresent : 1;
    HV_UINT32 DmaProtectionInUse : 1;
    HV_UINT32 SyntheticTimersVolatile : 1;
    HV_UINT32 HvRegisterForMemoryZeroingSupported : 1;
    HV_UINT32 Reserved : 24;

    HV_UINT32 Reserved0;
    HV_UINT32 Reserved1;
    HV_UINT32 Reserved2;
} HV_ARM64_HYPERVISOR_HARDWARE_FEATURES, *PHV_ARM64_HYPERVISOR_HARDWARE_FEATURES;
typedef _HV_ARM64_HYPERVISOR_HARDWARE_FEATURES _HV_HYPERVISOR_HARDWARE_FEATURES;
typedef HV_ARM64_HYPERVISOR_HARDWARE_FEATURES HV_HYPERVISOR_HARDWARE_FEATURES;
typedef PHV_ARM64_HYPERVISOR_HARDWARE_FEATURES PHV_HYPERVISOR_HARDWARE_FEATURES;
#endif

// Hypervisor Cpu Management features - HvCpuIdFunctionMsHvCpuManagementFeatures
// leaf.
#if defined(_M_AMD64)
typedef struct _HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES
{
    // Eax

    HV_UINT32 StartLogicalProcessor : 1;
    HV_UINT32 CreateRootVirtualProcessor : 1;
    HV_UINT32 PerformanceCounterSync : 1;
    HV_UINT32 Reserved0 : 28;
    HV_UINT32 ReservedIdentityBit : 1;

    // Ebx

    HV_UINT32 ProcessorPowerManagement : 1;
    HV_UINT32 MwaitIdleStates : 1;
    HV_UINT32 LogicalProcessorIdling : 1;
    HV_UINT32 Reserved1 : 29;

    // Ecx

    HV_UINT32 RemapGuestUncached : 1;
    HV_UINT32 ReservedZ2 : 31;

    // Edx

    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES, *PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
typedef _HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES _HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
typedef HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
typedef PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES PHV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES
{
    HV_UINT32 StartLogicalProcessor : 1;
    HV_UINT32 CreateRootVirtualProcessor : 1;
    HV_UINT32 PerformanceCounterSync : 1;
    HV_UINT32 Reserved0 : 28;
    HV_UINT32 ReservedIdentityBit : 1;

    HV_UINT32 ProcessorPowerManagement : 1;
    HV_UINT32 RootManagedIdleStates : 1;
    HV_UINT32 Reserved1 : 30;

    HV_UINT32 Reserved2;

    HV_UINT32 Reserved3;
} HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES, *PHV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
typedef _HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES _HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
typedef HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
typedef PHV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES PHV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
#endif

// SVM features - HvCpuIdFunctionMsHvSvmFeatures leaf.
typedef struct _HV_HYPERVISOR_SVM_FEATURES
{
    // Eax

    HV_UINT32 SvmSupported : 1;
    HV_UINT32 Reserved0 : 10;
    HV_UINT32 MaxPasidSpacePasidCount : 21;

    // Ebx

    HV_UINT32 MaxPasidSpaceCount;

    // Ecx

    HV_UINT32 MaxDevicePrqSize;

    // Edx

    HV_UINT32 Reserved1;
} HV_HYPERVISOR_SVM_FEATURES, *PHV_HYPERVISOR_SVM_FEATURES;

// Nested virtualization features (Vmx) - HvCpuidFunctionMsHvNestedVirtFeatures
// leaf.
#if defined(_M_AMD64)
typedef struct _HV_HYPERVISOR_NESTED_VIRT_FEATURES
{
    // Eax

    HV_UINT32 EnlightenedVmcsVersionLow : 8;
    HV_UINT32 EnlightenedVmcsVersionHigh : 8;
    HV_UINT32 FlushGuestPhysicalHypercall_Deprecated : 1;
    HV_UINT32 NestedFlushVirtualHypercall : 1;
    HV_UINT32 FlushGuestPhysicalHypercall : 1;
    HV_UINT32 MsrBitmap : 1;
    HV_UINT32 VirtualizationException : 1;
    HV_UINT32 Reserved0 : 11;

    // Ebx

    HV_UINT32 ReservedEbx;

    // Ecx

    HV_UINT32 ReservedEcx;

    // Edx

    HV_UINT32 ReservedEdx;
} HV_HYPERVISOR_NESTED_VIRT_FEATURES, *PHV_HYPERVISOR_NESTED_VIRT_FEATURES;
#endif

// Isolated VM configuration - HvCpuidFunctionMsHvIsolationConfiguration leaf.
typedef struct _HV_HYPERVISOR_ISOLATION_CONFIGURATION
{
    // Eax

    HV_UINT32 ParavisorPresent : 1;
    HV_UINT32 Reserved0 : 31;

    // Ebx

    HV_UINT32 IsolationType : 4;
    HV_UINT32 Reserved11 : 1;
    HV_UINT32 SharedGpaBoundaryActive : 1;
    HV_UINT32 SharedGpaBoundaryBits : 6;
    HV_UINT32 Reserved12 : 20;

    // Ecx

    HV_UINT32 Reserved2;

    // Edx

    HV_UINT32 Reserved3;
} HV_HYPERVISOR_ISOLATION_CONFIGURATION, *PHV_HYPERVISOR_ISOLATION_CONFIGURATION;

#define HV_PARTITION_ISOLATION_TYPE_NONE 0
#define HV_PARTITION_ISOLATION_TYPE_VBS 1
#define HV_PARTITION_ISOLATION_TYPE_SNP 2
#define HV_PARTITION_ISOLATION_TYPE_TDX 3

//
// Typedefs for CPUID leaves on HvMicrosoftHypercallInterface-supporting
// hypervisors.
//
typedef union _HV_CPUID_RESULT
{
    HV_UINT32 AsUINT32[4];
#if defined(_M_AMD64)
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 Ebx;
        HV_UINT32 Ecx;
        HV_UINT32 Edx;
    };
    struct
    {
        // Eax

        HV_UINT32 ReservedEax;

        // Ebx

        HV_UINT32 ReservedEbx : 24;
        HV_UINT32 InitialApicId : 8;

        // Ecx

        HV_UINT32 ReservedEcx : 31;
        HV_UINT32 HypervisorPresent : 1;

        // Edx

        HV_UINT32 ReservedEdx;
    } VersionAndFeatures;
    HV_X64_PLATFORM_CAPABILITIES MsHvPlatformCapabilities;
    HV_HYPERVISOR_NESTED_VIRT_FEATURES MsHvNestedVirtFeatures;
#endif

    // Eax-Edx on x86/x64

    HV_VENDOR_AND_MAX_FUNCTION HvVendorAndMaxFunction;
    HV_HYPERVISOR_INTERFACE_INFO HvInterface;
    HV_HYPERVISOR_VERSION_INFO MsHvVersion;
    HV_HYPERVISOR_FEATURES MsHvFeatures;
    HV_ENLIGHTENMENT_INFORMATION MsHvEnlightenmentInformation;
    HV_IMPLEMENTATION_LIMITS MsHvImplementationLimits;
    HV_HYPERVISOR_HARDWARE_FEATURES MsHvHardwareFeatures;
    HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES MsHvCpuManagementFeatures;
    HV_HYPERVISOR_SVM_FEATURES MsHvSvmFeatures;
    HV_HYPERVISOR_ISOLATION_CONFIGURATION MsHvIsolationConfiguration;
} HV_CPUID_RESULT, *PHV_CPUID_RESULT;

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4201) // nameless struct/union
#endif
#endif

#endif // !MILE_HYPERV_GUEST_INTERFACE
