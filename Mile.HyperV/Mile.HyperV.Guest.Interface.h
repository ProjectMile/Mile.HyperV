/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.Guest.Interface.h
 * PURPOSE:    Definition for Hyper-V Guest Publicized Interface
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

// References
// - Hyper-V Generation 2 Virtual Machine UEFI Firmware
//   - MsvmPkg\Include\Hv\HvStatus.h
//   - MsvmPkg\Include\Hv\HvGuest.h
//   - MsvmPkg\Include\Hv\HvGuestCpuid.h
//   - MsvmPkg\Include\Hv\HvGuestMsr.h
//   - MsvmPkg\Include\Hv\HvGuestSyntheticInterrupts.h
//   - MsvmPkg\Include\Hv\HvGuestHypercall.h
// - Windows Subsystem for Linux
//   - src\windows\inc\wdk.h

#ifndef MILE_HYPERV_GUEST_INTERFACE
#define MILE_HYPERV_GUEST_INTERFACE

#include "Mile.HyperV.Portable.Types.h"

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif
#pragma warning(disable:4201) // nameless struct/union
#endif

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
#elif defined(_M_AMD64) || defined(_M_IX86)
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

#if defined(_M_AMD64) || defined(_M_IX86)
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

#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_AMD64) || defined(_M_IX86)
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

#if defined(_M_AMD64) || defined(_M_IX86)
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
#if defined(_M_AMD64) || defined(_M_IX86)
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
typedef HV_X64_HYPERVISOR_FEATURES _HV_HYPERVISOR_FEATURES;
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
typedef HV_ARM64_HYPERVISOR_FEATURES _HV_HYPERVISOR_FEATURES;
typedef HV_ARM64_HYPERVISOR_FEATURES HV_HYPERVISOR_FEATURES;
typedef PHV_ARM64_HYPERVISOR_FEATURES PHV_HYPERVISOR_FEATURES;
#endif

// Enlightenment Info - HvCpuIdFunctionMsHvEnlightenmentInformation Leaf
#if defined(_M_AMD64) || defined(_M_IX86)
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
typedef HV_X64_ENLIGHTENMENT_INFORMATION _HV_ENLIGHTENMENT_INFORMATION;
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
typedef HV_ARM64_ENLIGHTENMENT_INFORMATION _HV_ENLIGHTENMENT_INFORMATION;
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
#if defined(_M_AMD64) || defined(_M_IX86)
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
    HV_UINT32 RdtAFeaturesSupported : 1;
    HV_UINT32 RdtMFeaturesSupported : 1;
    HV_UINT32 ChildPerfmonPmuSupported : 1;
    HV_UINT32 ChildPerfmonLbrSupported : 1;
    HV_UINT32 ChildPerfmonIptSupported : 1;
    HV_UINT32 ApicEmulationSupported : 1;
    HV_UINT32 ChildX2ApicRecommended : 1;
    HV_UINT32 HardwareWatchdogReserved : 1;
    HV_UINT32 DeviceAccessTrackingSupported : 1;
    HV_UINT32 Reserved : 5;

    // Ebx
    HV_UINT32 DeviceDomainInputWidth : 8;
    HV_UINT32 ReservedEbx : 24;

    // Ecx
    HV_UINT32 ReservedEcx;

    // Edx
    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_HARDWARE_FEATURES, *PHV_X64_HYPERVISOR_HARDWARE_FEATURES;
typedef HV_X64_HYPERVISOR_HARDWARE_FEATURES _HV_HYPERVISOR_HARDWARE_FEATURES;
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
typedef HV_ARM64_HYPERVISOR_HARDWARE_FEATURES _HV_HYPERVISOR_HARDWARE_FEATURES;
typedef HV_ARM64_HYPERVISOR_HARDWARE_FEATURES HV_HYPERVISOR_HARDWARE_FEATURES;
typedef PHV_ARM64_HYPERVISOR_HARDWARE_FEATURES PHV_HYPERVISOR_HARDWARE_FEATURES;
#endif

// Hypervisor Cpu Management features - HvCpuIdFunctionMsHvCpuManagementFeatures
// leaf.
#if defined(_M_AMD64) || defined(_M_IX86)
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
typedef HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES _HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
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
typedef HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES _HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES;
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
#if defined(_M_AMD64) || defined(_M_IX86)
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

// Typedefs for CPUID leaves on HvMicrosoftHypercallInterface-supporting
// hypervisors.
typedef union _HV_CPUID_RESULT
{
    HV_UINT32 AsUINT32[4];
#if defined(_M_AMD64) || defined(_M_IX86)
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

// *****************************************************************************
// MSR Definitions
//

// Version info reported by guest OS's
typedef enum _HV_GUEST_OS_VENDOR
{
    HvGuestOsVendorMicrosoft = 0x0001
} HV_GUEST_OS_VENDOR, *PHV_GUEST_OS_VENDOR;

typedef enum _HV_GUEST_OS_MICROSOFT_IDS
{
    HvGuestOsMicrosoftUndefined = 0x00,
    HvGuestOsMicrosoftMSDOS = 0x01,
    HvGuestOsMicrosoftWindows3x = 0x02,
    HvGuestOsMicrosoftWindows9x = 0x03,
    HvGuestOsMicrosoftWindowsNT = 0x04,
    HvGuestOsMicrosoftWindowsCE = 0x05
} HV_GUEST_OS_MICROSOFT_IDS, *PHV_GUEST_OS_MICROSOFT_IDS;

// This enumeration collates MSR indices for ease of maintainability.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef enum _HV_X64_SYNTHETIC_MSR
{
    HvSyntheticMsrGuestOsId = 0x40000000,
    HvSyntheticMsrHypercall = 0x40000001,
    HvSyntheticMsrVpIndex = 0x40000002,
    HvSyntheticMsrReset = 0x40000003,
    HvSyntheticMsrCpuMgmtVersion = 0x40000004,
    XbSyntheticMsrTbFlushHost = 0x40000006,
    XbSyntheticMsrTbFlush = 0x40000007,
    XbSyntheticMsrCrash = 0x40000008,
    XbSyntheticMsrGuestOsType = 0x40000009,
    HvSyntheticMsrVpRuntime = 0x40000010,
    XbSyntheticMsrRefTimeOffset = 0x40000011,
    XbSyntheticMsrRefTscScale = 0x40000012,
    XbSyntheticMsrVpCount = 0x40000013,
    XbSyntheticMsrWbinvd = 0x40000014,
    XbSyntheticMsrFlushWb = 0x40000015,
    XbSyntheticMsrFlushTbCurrent = 0x40000016,
    XbSyntheticMsrKcfgDone = 0x40000017,
    HvSyntheticMsrTimeRefCount = 0x40000020,
    HvSyntheticMsrReferenceTsc = 0x40000021,
    HvSyntheticMsrTscFrequency = 0x40000022,
    HvSyntheticMsrApicFrequency = 0x40000023,
    HvSyntheticMsrNpiepConfig = 0x40000040,
    HvSyntheticMsrEoi = 0x40000070,
    HvSyntheticMsrIcr = 0x40000071,
    HvSyntheticMsrTpr = 0x40000072,
    HvSyntheticMsrVpAssistPage = 0x40000073,
    HvSyntheticMsrSControl = 0x40000080,
    HvSyntheticMsrSVersion = 0x40000081,
    HvSyntheticMsrSiefp = 0x40000082,
    HvSyntheticMsrSimp = 0x40000083,
    HvSyntheticMsrEom = 0x40000084,
    HvSyntheticMsrSirb = 0x40000085,
    HvSyntheticMsrSint0 = 0x40000090,
    HvSyntheticMsrSint1 = 0x40000091,
    HvSyntheticMsrSint2 = 0x40000092,
    HvSyntheticMsrSint3 = 0x40000093,
    HvSyntheticMsrSint4 = 0x40000094,
    HvSyntheticMsrSint5 = 0x40000095,
    HvSyntheticMsrSint6 = 0x40000096,
    HvSyntheticMsrSint7 = 0x40000097,
    HvSyntheticMsrSint8 = 0x40000098,
    HvSyntheticMsrSint9 = 0x40000099,
    HvSyntheticMsrSint10 = 0x4000009A,
    HvSyntheticMsrSint11 = 0x4000009B,
    HvSyntheticMsrSint12 = 0x4000009C,
    HvSyntheticMsrSint13 = 0x4000009D,
    HvSyntheticMsrSint14 = 0x4000009E,
    HvSyntheticMsrSint15 = 0x4000009F,
    HvSyntheticMsrSTimer0Config = 0x400000B0,
    HvSyntheticMsrSTimer0Count = 0x400000B1,
    HvSyntheticMsrSTimer1Config = 0x400000B2,
    HvSyntheticMsrSTimer1Count = 0x400000B3,
    HvSyntheticMsrSTimer2Config = 0x400000B4,
    HvSyntheticMsrSTimer2Count = 0x400000B5,
    HvSyntheticMsrSTimer3Config = 0x400000B6,
    HvSyntheticMsrSTimer3Count = 0x400000B7,
    HvSyntheticMsrPerfFeedbackTrigger = 0x400000C1,
    HvSyntheticMsrGuestSchedulerEvent = 0x400000C2,
    HvSyntheticMsrGuestIdle = 0x400000F0,
    HvSyntheticMsrSynthDebugControl = 0x400000F1,
    HvSyntheticMsrSynthDebugStatus = 0x400000F2,
    HvSyntheticMsrSynthDebugSendBuffer = 0x400000F3,
    HvSyntheticMsrSynthDebugReceiveBuffer = 0x400000F4,
    HvSyntheticMsrSynthDebugPendingBuffer = 0x400000F5,
    XbSyntheticMsrSynthDebugTransition = 0x400000F6,
    HvSyntheticMsrDebugDeviceOptions = 0x400000FF,
    HvSyntheticMsrCrashP0 = 0x40000100,
    HvSyntheticMsrCrashP1 = 0x40000101,
    HvSyntheticMsrCrashP2 = 0x40000102,
    HvSyntheticMsrCrashP3 = 0x40000103,
    HvSyntheticMsrCrashP4 = 0x40000104,
    HvSyntheticMsrCrashCtl = 0x40000105,
    HvSyntheticMsrReenlightenmentControl = 0x40000106,
    HvSyntheticMsrTscEmulationControl = 0x40000107,
    HvSyntheticMsrTscEmulationStatus = 0x40000108,
    HvSyntheticMsrSWatchdogConfig = 0x40000110,
    HvSyntheticMsrSWatchdogCount = 0x40000111,
    HvSyntheticMsrSWatchdogStatus = 0x40000112,
    HvSyntheticMsrSTimeUnhaltedTimerConfig = 0x40000114,
    HvSyntheticMsrSTimeUnhaltedTimerCount = 0x40000115,
    HvSyntheticMsrMemoryZeroingControl = 0x40000116,
    XbSyntheticMsrFsBase = 0x40000122,
    XbSyntheticMsrXOnly = 0x40000123,
    HvSyntheticMsrBelow1MbPage = 0x40000200,
    HvSyntheticMsrNestedVpIndex = 0x40001002,
    HvSyntheticMsrNestedSControl = 0x40001080,
    HvSyntheticMsrNestedSVersion = 0x40001081,
    HvSyntheticMsrNestedSiefp = 0x40001082,
    HvSyntheticMsrNestedSimp = 0x40001083,
    HvSyntheticMsrNestedEom = 0x40001084,
    HvSyntheticMsrNestedSirb = 0x40001085,
    HvSyntheticMsrNestedSint0 = 0x40001090,
    HvSyntheticMsrNestedSint1 = 0x40001091,
    HvSyntheticMsrNestedSint2 = 0x40001092,
    HvSyntheticMsrNestedSint3 = 0x40001093,
    HvSyntheticMsrNestedSint4 = 0x40001094,
    HvSyntheticMsrNestedSint5 = 0x40001095,
    HvSyntheticMsrNestedSint6 = 0x40001096,
    HvSyntheticMsrNestedSint7 = 0x40001097,
    HvSyntheticMsrNestedSint8 = 0x40001098,
    HvSyntheticMsrNestedSint9 = 0x40001099,
    HvSyntheticMsrNestedSint10 = 0x4000109A,
    HvSyntheticMsrNestedSint11 = 0x4000109B,
    HvSyntheticMsrNestedSint12 = 0x4000109C,
    HvSyntheticMsrNestedSint13 = 0x4000109D,
    HvSyntheticMsrNestedSint14 = 0x4000109E,
    HvSyntheticMsrNestedSint15 = 0x4000109F,
} HV_X64_SYNTHETIC_MSR, *PHV_X64_SYNTHETIC_MSR;
#endif

// Declare the MSR used to identify the guest OS.
#define HV_X64_MSR_GUEST_OS_ID HvSyntheticMsrGuestOsId

typedef union _HV_GUEST_OS_ID_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 BuildNumber : 16;
        // Service Pack, etc.
        HV_UINT64 ServiceVersion : 8;
        HV_UINT64 MinorVersion : 8;
        HV_UINT64 MajorVersion : 8;
        // HV_GUEST_OS_MICROSOFT_IDS (If Vendor=MS)
        HV_UINT64 OsId : 8;
        // HV_GUEST_OS_VENDOR. We only support using the least significant 15
        // bits, the top bit must be zero. If 1, refers to the open source
        // format.
        HV_UINT64 VendorId : 16;
    };
    struct
    {
        HV_UINT64 VendorSpecific1 : 16;
        HV_UINT64 Version : 32;
        HV_UINT64 VendorSpecific2 : 8;
        HV_UINT64 OsId : 7;
        HV_UINT64 IsOpenSource : 1;
    } OpenSource;
} HV_GUEST_OS_ID_CONTENTS, *PHV_GUEST_OS_ID_CONTENTS;

// Declare the MSR used to setup pages used to communicate with the hypervisor.
#define HV_X64_MSR_HYPERCALL HvSyntheticMsrHypercall

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

#define HV_CRASH_MAXIMUM_MESSAGE_SIZE 4096ull

typedef union _HV_CRASH_CTL_REG_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        // Reserved bits
        HV_UINT64 Reserved : 58;
        // Crash occurred in the preOS environment
        HV_UINT64 PreOSId : 3;
        // Crash dump will not be captured
        HV_UINT64 NoCrashDump : 1;
        // P3 is the PA of the message, P4 is the length in bytes
        HV_UINT64 CrashMessage : 1;
        // Log contents of crash parameter system registers
        HV_UINT64 CrashNotify : 1;
    };
} HV_CRASH_CTL_REG_CONTENTS, *PHV_CRASH_CTL_REG_CONTENTS;

// Define synthetic interrupt source.
typedef union _HV_SYNIC_SINT
{
    HV_UINT64 AsUINT64;
    struct
    {
#if defined(_M_ARM64)
        HV_UINT64 Vector : 10;
        HV_UINT64 ReservedP1 : 6;
#else
        HV_UINT64 Vector : 8;
        HV_UINT64 ReservedP1 : 8;
#endif
        HV_UINT64 Masked : 1;
        HV_UINT64 AutoEoi : 1;
        HV_UINT64 Polling : 1;
        HV_UINT64 AsIntercept : 1;
        HV_UINT64 Proxy : 1;
        HV_UINT64 ReservedP2 : 43;
    };
} HV_SYNIC_SINT, *PHV_SYNIC_SINT;

// Define the number of synthetic timers.
#define HV_SYNIC_STIMER_COUNT (4)

// Define port identifier type.
typedef union _HV_PORT_ID
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 Id : 24;
        HV_UINT32 Reserved : 8;
    };
} HV_PORT_ID, *PHV_PORT_ID;

// Define the synthetic interrupt source index type.
typedef HV_UINT32 HV_SYNIC_SINT_INDEX, *PHV_SYNIC_SINT_INDEX;

// Define the number of synthetic interrupt sources.
#define HV_SYNIC_SINT_COUNT (16)

// Define synthetic interrupt controller message constants.

#define HV_MESSAGE_SIZE (256)
#define HV_MESSAGE_PAYLOAD_BYTE_COUNT (240)
#define HV_MESSAGE_PAYLOAD_QWORD_COUNT (30)

//
// Define hypervisor message types.
//
typedef enum _HV_MESSAGE_TYPE
{
    HvMessageTypeNone = 0x00000000,

    // Memory access messages

    HvMessageTypeUnmappedGpa = 0x80000000,
    HvMessageTypeGpaIntercept = 0x80000001,
#if defined(_M_ARM64)
    HvMessageTypeMmioIntercept = 0x80000002,
#endif
    HvMessageTypeUnacceptedGpa = 0x80000003,
    HvMessageTypeGpaAttributeIntercept = 0x80000004,

    // Timer notifications messages
    HvMessageTimerExpired = 0x80000010,

    // Error messages

    HvMessageTypeInvalidVpRegisterValue = 0x80000020,
    HvMessageTypeUnrecoverableException = 0x80000021,
    HvMessageTypeUnsupportedFeature = 0x80000022,
    HvMessageTypeTlbPageSizeMismatch = 0x80000023,
    HvMessageTypeIommuFault = 0x80000024,

    // Trace buffer complete messages
    HvMessageTypeEventLogBufferComplete = 0x80000040,

    // Hypercall intercept
    HvMessageTypeHypercallIntercept = 0x80000050,

    // SynIC intercepts
    HvMessageTypeSynicEventIntercept = 0x80000060,

    // Integrated (root) scheduler signal VP-backing thread(s) messages.
    // N.B. Message id range [0x80000100, 0x800001FF] inclusively is reserved
    //      for the integrated (root) scheduler messages.

    HvMessageTypeSchedulerIdRangeStart = 0x80000100,
    HvMessageTypeSchedulerVpSignalBitset = 0x80000100,
    HvMessageTypeSchedulerVpSignalPair = 0x80000101,
    HvMessageTypeSchedulerIdRangeEnd = 0x800001FF,

    // Platform-specific processor intercept messages.

    HvMessageTypeMsrIntercept = 0x80010001,
    HvMessageTypeExceptionIntercept = 0x80010003,
    HvMessageTypeRegisterIntercept = 0x80010006,
#if defined(_M_AMD64) || defined(_M_IX86)
    HvMessageTypeX64IoPortIntercept = 0x80010000,
    HvMessageTypeX64CpuidIntercept = 0x80010002,
    HvMessageTypeX64ApicEoi = 0x80010004,
    HvMessageTypeX64IommuPrq = 0x80010006,
    HvMessageTypeX64Halt = 0x80010007,
    HvMessageTypeX64InterruptionDeliverable = 0x80010008,
    HvMessageTypeX64SipiIntercept = 0x80010009,
#endif
#if defined(_M_ARM64)
    HvMessageTypeArm64ResetIntercept = 0x80010000,
#endif
} HV_MESSAGE_TYPE, *PHV_MESSAGE_TYPE;

// Define synthetic interrupt controller message flags.
typedef union _HV_MESSAGE_FLAGS
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 MessagePending : 1;
        HV_UINT8 Reserved : 7;
    };
} HV_MESSAGE_FLAGS, *PHV_MESSAGE_FLAGS;

// Define synthetic interrupt controller message header.
typedef struct _HV_MESSAGE_HEADER
{
    HV_MESSAGE_TYPE MessageType;
    HV_UINT8 PayloadSize;
    HV_MESSAGE_FLAGS MessageFlags;
    HV_UINT8 Reserved[2];
    union
    {
        HV_PARTITION_ID Sender;
        HV_PORT_ID Port;
    };
} HV_MESSAGE_HEADER, *PHV_MESSAGE_HEADER;

// Define synthetic interrupt controller flag constants.

#define HV_EVENT_FLAGS_COUNT (256 * 8)
#define HV_EVENT_FLAGS_BYTE_COUNT (256)
#define HV_EVENT_FLAGS_DWORD_COUNT (256 / sizeof(HV_UINT32))

// Define the synthetic interrupt controller event flags format.
typedef union
{
    HV_UINT8 Flags8[HV_EVENT_FLAGS_BYTE_COUNT];
    HV_UINT32 Flags32[HV_EVENT_FLAGS_DWORD_COUNT];
} HV_SYNIC_EVENT_FLAGS;

// Define the synthetic interrupt flags page layout.
typedef struct _HV_SYNIC_EVENT_FLAGS_PAGE
{
    volatile HV_SYNIC_EVENT_FLAGS SintEventFlags[HV_SYNIC_SINT_COUNT];
} HV_SYNIC_EVENT_FLAGS_PAGE, *PHV_SYNIC_EVENT_FLAGS_PAGE;

// Define the synthetic timer configuration structure
typedef struct _HV_X64_MSR_STIMER_CONFIG_CONTENTS
{
    union
    {
        HV_UINT64 AsUINT64;
        struct
        {
            HV_UINT64 Enable : 1;
            HV_UINT64 Periodic : 1;
            HV_UINT64 Lazy : 1;
            HV_UINT64 AutoEnable : 1;
            HV_UINT64 ApicVector : 8;
            HV_UINT64 DirectMode : 1;
            HV_UINT64 ReservedZ1 : 3;
            HV_UINT64 SINTx : 4;
            HV_UINT64 ReservedZ2 : 44;
        };
    };
} HV_X64_MSR_STIMER_CONFIG_CONTENTS, *PHV_X64_MSR_STIMER_CONFIG_CONTENTS;

// Define the format of the SIMP register
typedef union _HV_SYNIC_SIMP
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 SimpEnabled : 1;
        HV_UINT64 Preserved : 11;
        HV_UINT64 BaseSimpGpa : 52;
    };
} HV_SYNIC_SIMP, *PHV_SYNIC_SIMP;

// Define the trace buffer index type.
typedef HV_UINT32 HV_EVENTLOG_BUFFER_INDEX, *PHV_EVENTLOG_BUFFER_INDEX;

// Define all the trace buffer types.
typedef enum
{
    HvEventLogTypeGlobalSystemEvents = 0x00000000,
    HvEventLogTypeLocalDiagnostics = 0x00000001,
    HvEventLogTypeMaximum = 0x00000001,
} HV_EVENTLOG_TYPE;

// Define trace message header structure.
typedef struct _HV_EVENTLOG_MESSAGE_PAYLOAD
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
} HV_EVENTLOG_MESSAGE_PAYLOAD, *PHV_EVENTLOG_MESSAGE_PAYLOAD;

// Define timer message payload structure.
typedef struct _HV_TIMER_MESSAGE_PAYLOAD
{
    HV_UINT32 TimerIndex;
    HV_UINT32 Reserved;
    HV_NANO100_TIME ExpirationTime; // When the timer expired
    HV_NANO100_TIME DeliveryTime; // When the message was delivered
} HV_TIMER_MESSAGE_PAYLOAD, *PHV_TIMER_MESSAGE_PAYLOAD;

// Define IOMMU PRQ message payload structure.
typedef struct _HV_IOMMU_PRQ_MESSAGE_PAYLOAD
{
    HV_IOMMU_ID IommuId;
} HV_IOMMU_PRQ_MESSAGE_PAYLOAD, *PHV_IOMMU_PRQ_MESSAGE_PAYLOAD;

// Define IOMMU fault message payload structure.
typedef enum _HV_IOMMU_FAULT_TYPE
{
    // The IOMMU did not obtain a translation for a DMA transaction.
    HvIommuTranslationFault,
    // Translation request, translated request or untranslated request
    // explicitly blocked.
    HvIommuTranslationBlocked,
    // Hardware blocked an interrupt request.
    HvIommuInterruptFault,
#if defined(_M_ARM64)
    // The IOMMU retrieved a transation for a DMA transaction, but the
    // transaction has insufficient privileges.
    HvIommuPermissionFault,
    // An output address contained an unexpected number of bits.
    HvIommuAddressSizeFault,
    // A TLB match conflict was detected.
    HvIommuTlbMatchConflict,

    // An external abort / unsupported upstream transaction was reported to
    // the IOMMU during transaction processing.

    HvIommuExternalFault,
    HvIommuUnsupportedUpstreamTransaction,
#endif
} HV_IOMMU_FAULT_TYPE, *PHV_IOMMU_FAULT_TYPE;

typedef struct _HV_IOMMU_FAULT_MESSAGE_PAYLOAD
{
    // Indicates the type of the fault.
    HV_IOMMU_FAULT_TYPE Type;
    // Access type of the DMA transaction.
    HV_INTERCEPT_ACCESS_TYPE AccessType;
    // Fault flags.
    struct
    {
        // Indicates that the fault address is valid.
        HV_UINT32 FaultAddressValid : 1;
        // Indicates that the logical device ID is valid.
        HV_UINT32 DeviceIdValid : 1;
    } Flags;
    // Logical ID of the device that caused the fault.
    HV_UINT64 LogicalDeviceId;
    // Device virtual address that caused the fault (if known).
    HV_GVA FaultAddress;
} HV_IOMMU_FAULT_MESSAGE_PAYLOAD, *PHV_IOMMU_FAULT_MESSAGE_PAYLOAD;

// Define synthetic interrupt controller message format.
// N.B. The Payload may contain XMM registers that the compiler might expect to
// to be aligned. Therefore, this structure must be 16-byte aligned. The header
// is 16B already.
typedef struct HV_DECLSPEC_ALIGN(16) _HV_MESSAGE
{
    HV_MESSAGE_HEADER Header;
    union
    {
        HV_UINT64 Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
        HV_TIMER_MESSAGE_PAYLOAD TimerPayload;
        HV_EVENTLOG_MESSAGE_PAYLOAD TracePayload;
        HV_IOMMU_PRQ_MESSAGE_PAYLOAD IommuPrqPayload;
        HV_IOMMU_FAULT_MESSAGE_PAYLOAD IommuFaultPayload;
    };
} HV_MESSAGE, *PHV_MESSAGE;

// Define the synthetic interrupt message page layout.
typedef struct _HV_MESSAGE_PAGE
{
    volatile HV_MESSAGE SintMessage[HV_SYNIC_SINT_COUNT];
} HV_MESSAGE_PAGE, *PHV_MESSAGE_PAGE;

// Define the format of the SIEFP register
typedef union _HV_SYNIC_SIEFP
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 SiefpEnabled : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 BaseSiefpGpa : 52;
    };
} HV_SYNIC_SIEFP, *PHV_SYNIC_SIEFP;

// *****************************************************************************
// Hypercall Definitions
//

// Define a 128bit type.
typedef union HV_DECLSPEC_ALIGN(16) _HV_UINT128
{
    struct
    {
        HV_UINT64 Low64;
        HV_UINT64 High64;
    };
    HV_UINT32 Dword[4];
    HV_UINT8 AsUINT8[16];
} HV_UINT128, *PHV_UINT128;

// Define an alignment for structures passed via hypercall.
#define HV_CALL_ALIGNMENT 8
#define HV_CALL_ATTRIBUTES HV_DECLSPEC_ALIGN(HV_CALL_ALIGNMENT)

// Address spaces presented by the guest.
typedef HV_UINT64 HV_ADDRESS_SPACE_ID, *PHV_ADDRESS_SPACE_ID;

// Definition of the HvCallSwitchVirtualAddressSpace hypercall input structure.
// This call switches the guest's virtual address space.
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SWITCH_VIRTUAL_ADDRESS_SPACE
{
    HV_ADDRESS_SPACE_ID AddressSpace;
} HV_INPUT_SWITCH_VIRTUAL_ADDRESS_SPACE, *PHV_INPUT_SWITCH_VIRTUAL_ADDRESS_SPACE;

// Define connection identifier type.
typedef union _HV_CONNECTION_ID
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 Id : 24;
        HV_UINT32 Reserved : 8;
        HV_UINT32 Scope : 2;
    };
} HV_CONNECTION_ID, *PHV_CONNECTION_ID;

// Declare the various hypercall operations.
// Read References\HvCallList.xlsx in https://github.com/ProjectMile/Mile.HyperV
// for more information.
typedef enum _HV_CALL_CODE
{
    // Reserved Feature Code
    HvCallReserved0000 = 0x0000,

    // V1 Address space enlightment IDs

    HvCallSwitchVirtualAddressSpace = 0x0001,
    HvCallFlushVirtualAddressSpace = 0x0002,
    HvCallFlushVirtualAddressList = 0x0003,

    // V1 Power Management and Run time metrics IDs
    HvCallGetLogicalProcessorRunTime = 0x0004,

    // Deprectated index, now repurposed for updating processor features.
    HvCallUpdateHvProcessorFeatures = 0x0005,

    // Deprecated index, now repurposed for switching to and from alias map.
    HvCallSwitchAliasMap = 0x0006,

    // Deprecated index, now repurposed for dynamic microcode updates.
    HvCallUpdateMicrocode = 0x0007,

    // V1 Spinwait enlightenment IDs
    HvCallNotifyLongSpinWait = 0x0008,

    // V2 Core parking IDs.
    // Reused Hypercall code: Previously was HvCallParkLogicalProcessors.
    HvCallParkedVirtualProcessors = 0x0009,

    // V2 Invoke Hypervisor debugger
    HvCallInvokeHypervisorDebugger = 0x000a,

    // V4 Send Synthetic Cluster Ipi
    HvCallSendSyntheticClusterIpi = 0x000b,

    // V5 Virtual Secure Mode (VSM) hypercalls.

    HvCallModifyVtlProtectionMask = 0x000c,
    HvCallEnablePartitionVtl = 0x000d,
    HvCallDisablePartitionVtl = 0x000e,
    HvCallEnableVpVtl = 0x000f,
    HvCallDisableVpVtl = 0x0010,
    HvCallVtlCall = 0x0011,
    HvCallVtlReturn = 0x0012,

    // V5 Extended Flush Routines and Cluster IPIs.

    HvCallFlushVirtualAddressSpaceEx = 0x0013,
    HvCallFlushVirtualAddressListEx = 0x0014,
    HvCallSendSyntheticClusterIpiEx = 0x0015,

    // V1 enlightenment name space reservation.

    HvCallQueryImageInfo = 0x0016,
    HvCallMapImagePages = 0x0017,
    HvCallCommitPatch = 0x0018,
    HvCallReserved0019 = 0x0019,
    HvCallReserved001a = 0x001a,
    HvCallReserved001b = 0x001b,
    HvCallReserved001c = 0x001c,
    HvCallReserved001d = 0x001d,
    HvCallReserved001e = 0x001e,
    HvCallReserved001f = 0x001f,
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
    HvCallReserved002a = 0x002a,
    HvCallReserved002b = 0x002b,
    HvCallReserved002c = 0x002c,
    HvCallReserved002d = 0x002d,
    HvCallReserved002e = 0x002e,
    HvCallReserved002f = 0x002f,
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
    HvCallReserved003a = 0x003a,
    HvCallReserved003b = 0x003b,
    HvCallReserved003c = 0x003c,
    HvCallReserved003d = 0x003d,
    HvCallReserved003e = 0x003e,
    HvCallReserved003f = 0x003f,

    // V1 Partition Management IDs

    HvCallCreatePartition = 0x0040,
    HvCallInitializePartition = 0x0041,
    HvCallFinalizePartition = 0x0042,
    HvCallDeletePartition = 0x0043,
    HvCallGetPartitionProperty = 0x0044,
    HvCallSetPartitionProperty = 0x0045,
    HvCallGetPartitionId = 0x0046,
    HvCallGetNextChildPartition = 0x0047,

    // V1 Resource Management IDs

    HvCallDepositMemory = 0x0048,
    HvCallWithdrawMemory = 0x0049,
    HvCallGetMemoryBalance = 0x004a,

    // V1 Guest Physical Address Space Management IDs

    HvCallMapGpaPages = 0x004b,
    HvCallUnmapGpaPages = 0x004c,

    // V1 Intercept Management IDs
    HvCallInstallIntercept = 0x004d,

    // V1 Virtual Processor Management IDs

    HvCallCreateVp = 0x004e,
    HvCallDeleteVp = 0x004f,
    HvCallGetVpRegisters = 0x0050,
    HvCallSetVpRegisters = 0x0051,

    // V1 Virtual TLB IDs

    HvCallTranslateVirtualAddress = 0x0052,
    HvCallReadGpa = 0x0053,
    HvCallWriteGpa = 0x0054,

    // V1 Interrupt Management IDs

    HvCallAssertVirtualInterruptDeprecated = 0x0055,
    HvCallClearVirtualInterrupt = 0x0056,

    // V1 Port IDs

    HvCallCreatePortDeprecated = 0x0057,
    HvCallDeletePort = 0x0058,
    HvCallConnectPortDeprecated = 0x0059,
    HvCallGetPortProperty = 0x005a,
    HvCallDisconnectPort = 0x005b,
    HvCallPostMessage = 0x005c,
    HvCallSignalEvent = 0x005d,

    // V1 Partition State IDs

    HvCallSavePartitionState = 0x005e,
    HvCallRestorePartitionState = 0x005f,

    // V1 Trace IDs

    HvCallInitializeEventLogBufferGroup = 0x0060,
    HvCallFinalizeEventLogBufferGroup = 0x0061,
    HvCallCreateEventLogBuffer = 0x0062,
    HvCallDeleteEventLogBuffer = 0x0063,
    HvCallMapEventLogBuffer = 0x0064,
    HvCallUnmapEventLogBuffer = 0x0065,
    HvCallSetEventLogGroupSources = 0x0066,
    HvCallReleaseEventLogBuffer = 0x0067,
    HvCallFlushEventLogBuffer = 0x0068,

    // V1 Dbg Call IDs

    HvCallPostDebugData = 0x0069,
    HvCallRetrieveDebugData = 0x006a,
    HvCallResetDebugSession = 0x006b,

    // V1 Stats IDs

    HvCallMapStatsPage = 0x006c,
    HvCallUnmapStatsPage = 0x006d,

    // V2 Guest Physical Address Space Management IDs
    HvCallMapSparseGpaPages = 0x006e,

    // V2 Set System Property
    HvCallSetSystemProperty = 0x006f,

    // V2 Port Ids.
    HvCallSetPortProperty = 0x0070,

    // V2 Test IDs

    HvCallOutputDebugCharacter = 0x0071,
    HvCallEchoIncrement = 0x0072,

    // V2 Performance IDs

    HvCallPerfNop = 0x0073,
    HvCallPerfNopInput = 0x0074,
    HvCallPerfNopOutput = 0x0075,

    // V3 Logical Processor Management IDs

    HvCallAddLogicalProcessor = 0x0076,
    HvCallRemoveLogicalProcessor = 0x0077,
    HvCallQueryNumaDistance = 0x0078,
    HvCallSetLogicalProcessorProperty = 0x0079,
    HvCallGetLogicalProcessorProperty = 0x007a,

    // V3 Get System Property
    HvCallGetSystemProperty = 0x007b,

    // V3 IOMMU hypercalls

    HvCallMapDeviceInterrupt = 0x007c,
    HvCallUnmapDeviceInterrupt = 0x007d,

    // V5 IOMMU hypercalls

    HvCallRetargetDeviceInterrupt = 0x007e,
    HvCallRetargetRootDeviceInterrupt = 0x007f,

    // V6 IOMMU hypercalls
    HvCallAssertDeviceInterrupt = 0x0080,

    // V3 IOMMU hypercalls

    HvCallReserved0081 = 0x0081,
    HvCallAttachDevice = 0x0082,
    HvCallDetachDevice = 0x0083,

    // V3 Sleep state transition hypercall

    HvCallEnterSleepState = 0x0084,
    HvCallNotifyStandbyTransition = 0x0085,
    HvCallPrepareForHibernate = 0x0086,
    HvCallNotifyPartitionEvent = 0x0087,

    // V3 Logical Processor State IDs

    HvCallGetLogicalProcessorRegisters = 0x0088,
    HvCallSetLogicalProcessorRegisters = 0x0089,

    // V3 MCA specific Hypercall IDs
    HvCallQueryAssociatedLpsForMca = 0x008A,

    // V3 Event ring flush.
    HvCallNotifyPortRingEmpty = 0x008B,

    // V3 Synthetic machine check injection
    HvCallInjectSyntheticMachineCheck = 0x008C,

    // V4 Parition Management IDs
    HvCallScrubPartition = 0x008D,

    // V4 Debugger and livedump hypercalls.
    HvCallCollectLivedump = 0x008E,

    // V4 Turn off virtualization.
    HvCallDisableHypervisor = 0x008F,

    // V4 Guest Physical Address Space Management IDs
    HvCallModifySparseGpaPages = 0x0090,

    // V4 Intercept result registration hypercalls.

    HvCallRegisterInterceptResult = 0x0091,
    HvCallUnregisterInterceptResult = 0x0092,

    // V5 Test Only Coverage Hypercall
    HvCallGetCoverageData = 0x0093,

    // V5 Synic Hypercalls (slightly extended from V1)

    HvCallAssertVirtualInterrupt = 0x0094,
    HvCallCreatePort = 0x0095,
    HvCallConnectPort = 0x0096,

    // V5 Resource Management Hypercalls.
    HvCallGetSpaPageList = 0x0097,

    // V5 ARM64 Startup Stub interface
    HvCallArm64GetStartStub = 0x0098,

    // V5 VP Startup Enlightment
    HvCallStartVirtualProcessor = 0x0099,

    // V5 VP Index retrieval for VP startup
    HvCallGetVpIndexFromApicId = 0x009A,

    // V5 Power management

    HvCallGetPowerProperty = 0x009B,
    HvCallSetPowerProperty = 0x009C,

    // V5 SVM hypercalls

    HvCallCreatePasidSpace = 0x009D,
    HvCallDeletePasidSpace = 0x009E,
    HvCallSetPasidAddressSpace = 0x009F,
    HvCallFlushPasidAddressSpace = 0x00A0,
    HvCallFlushPasidAddressList = 0x00A1,
    HvCallAttachPasidSpace = 0x00A2,
    HvCallDetachPasidSpace = 0x00A3,
    HvCallEnablePasid = 0x00A4,
    HvCallDisablePasid = 0x00A5,
    HvCallAcknowledgeDevicePageRequest = 0x00A6,
    HvCallCreateDevicePrQueue = 0x00A7,
    HvCallDeleteDevicePrQueue = 0x00A8,
    HvCallSetDevicePrqProperty = 0x00A9,
    HvCallGetPhysicalDeviceProperty = 0x00AA,
    HvCallSetPhysicalDeviceProperty = 0x00AB,

    // V5 Virtual TLB IDs
    HvCallTranslateVirtualAddressEx = 0x00AC,

    // V5 I/O port intercepts
    HvCallCheckForIoIntercept = 0x00AD,

    // V5 GPA page attributes.
    HvCallSetGpaPageAttributes = 0x00AE,

    // V5 Enlightened nested page table flush.

    HvCallFlushGuestPhysicalAddressSpace = 0x00AF,
    HvCallFlushGuestPhysicalAddressList = 0x00B0,

    // V5 Device Domains.

    HvCallCreateDeviceDomain = 0x00B1,
    HvCallAttachDeviceDomain = 0x00B2,
    HvCallMapDeviceGpaPages = 0x00B3,
    HvCallUnmapDeviceGpaPages = 0x00B4,

    // V5 CPU group management.

    HvCallCreateCpuGroup = 0x00B5,
    HvCallDeleteCpuGroup = 0x00B6,
    HvCallGetCpuGroupProperty = 0x00B7,
    HvCallSetCpuGroupProperty = 0x00B8,
    HvCallGetCpuGroupAffinity = 0x00B9,
    HvCallGetNextCpuGroup = 0x00BA,
    HvCallGetNextCpuGroupPartition = 0x00BB,

    // V5 Nested Dynamic Memory.
    HvCallAddPhysicalMemory = 0x00BC,

    // V6 Intercept Completion.
    HvCallCompleteIntercept = 0x00BD,

    // V6 Guest Physical Address Space Management IDs

    HvCallPrecommitGpaPages = 0x00BE,
    HvCallUncommitGpaPages = 0x00BF,

    // ARM64 Parent asserted interrupt hypercalls.

    HvCallConfigureVirtualInterruptLine = 0x00C0,
    HvCallSetVirtualInterruptLineState = 0x00C1,

    // V6 Integrated (Root) Scheduler

    HvCallDispatchVp = 0x00C2,
    HvCallProcessIommuPrq = 0x00C3,

    // V6 Device Domains.

    HvCallDetachDeviceDomain = 0x00C4,
    HvCallDeleteDeviceDomain = 0x00C5,
    HvCallQueryDeviceDomain = 0x00C6,
    HvCallMapSparseDeviceGpaPages = 0x00C7,
    HvCallUnmapSparseDeviceGpaPages = 0x00C8,

    // V6 Page Access Tracking.

    HvCallGetGpaPagesAccessState = 0x00C9,
    HvCallGetSparseGpaPagesAccessState = 0x00CA,

    // V6 TestFramework hypercall
    HvCallInvokeTestFramework = 0x00CB,

    // V7 Virtual Secure Mode (VSM) hypercalls.

    HvCallQueryVtlProtectionMaskRange = 0x00CC,
    HvCallModifyVtlProtectionMaskRange = 0x00CD,

    // V7 Device Domains.

    HvCallConfigureDeviceDomain = 0x00CE,
    HvCallQueryDeviceDomainProperties = 0x00CF,
    HvCallFlushDeviceDomain = 0x00D0,
    HvCallFlushDeviceDomainList = 0x00D1,

    // V7 Virtual Secure Mode (VSM) hypercalls.

    HvCallAcquireSparseGpaPageHostAccess = 0x00D2,
    HvCallReleaseSparseGpaPageHostAccess = 0x00D3,
    HvCallCheckSparseGpaPageVtlAccess = 0x00D4,

    // V7 Device Domains.
    HvCallEnableDeviceInterrupt = 0x00D5,

    // V7 ARM enlightened TLB flush.
    HvCallFlushTlb = 0x00D6,

    // V8 Isolated VM (IVM)

    HvCallAcquireSparseSpaPageHostAccess = 0x00D7,
    HvCallReleaseSparseSpaPageHostAccess = 0x00D8,
    HvCallAcceptGpaPages = 0x00D9,
    HvCallUnacceptGpaPages = 0x00DA,
    HvCallModifySparseGpaPageHostVisibility = 0x00DB,
    HvCallLockSparseGpaPageMapping = 0x00DC,
    HvCallUnlockSparseGpaPageMapping = 0x00DD,

    // V8 Hypervisor Idle State Management hypercalls.
    HvCallRequestProcessorHalt = 0x00DE,

    // V8 Intercept Completion.
    HvCallGetInterceptData = 0x00DF,

    // Total of all hypercalls
    HvCallCount
} HV_CALL_CODE, *PHV_CALL_CODE;

// Declare constants and structures for submitting hypercalls.
#define HV_X64_MAX_HYPERCALL_ELEMENTS ((1<<12) - 1)

// Input: The call code, argument sizes and calling convention
typedef union _HV_HYPERCALL_INPUT
{
    struct
    {
        // Least significant bits
        HV_UINT32 CallCode : 16;
        // Uses the register based form
        HV_UINT32 IsFast : 1;
        HV_UINT32 Reserved1 : 14;
        // The outer hypervisor handles this call.
        HV_UINT32 IsNested : 1;
        HV_UINT32 CountOfElements : 12;
        HV_UINT32 Reserved2 : 4;
        HV_UINT32 RepStartIndex : 12;
        // Most significant bits
        HV_UINT32 Reserved3 : 4;
    };
    HV_UINT64 AsUINT64;
} HV_HYPERCALL_INPUT, *PHV_HYPERCALL_INPUT;

// Output: The result and returned data size
typedef union _HV_HYPERCALL_OUTPUT
{
    struct
    {
        // Least significant bits
        HV_UINT16 CallStatus;
        HV_UINT16 Reserved1;
        HV_UINT32 ElementsProcessed : 12;
        // Most significant bits
        HV_UINT32 Reserved2 : 20;
    };
    HV_UINT64 AsUINT64;
} HV_HYPERCALL_OUTPUT, *PHV_HYPERCALL_OUTPUT;

// Definition of the HvPostMessage hypercall input structure.
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_POST_MESSAGE
{
    HV_CONNECTION_ID ConnectionId;
    HV_UINT32 Reserved;
    HV_MESSAGE_TYPE MessageType;
    HV_UINT32 PayloadSize;
    HV_UINT64 Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
} HV_INPUT_POST_MESSAGE, *PHV_INPUT_POST_MESSAGE;

// Definition of the HvSignalEvent hypercall input structure.
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SIGNAL_EVENT
{
    HV_CONNECTION_ID ConnectionId;
    HV_UINT16 FlagNumber;
    HV_UINT16 RsvdZ[7];
} HV_INPUT_SIGNAL_EVENT, *PHV_INPUT_SIGNAL_EVENT;

// Hypervisor register names for accessing a virtual processor's registers.
typedef enum _HV_REGISTER_NAME
{
    // Suspend Registers

    HvRegisterExplicitSuspend = 0x00000000,
    HvRegisterInterceptSuspend = 0x00000001,
    HvRegisterInstructionEmulationHints = 0x00000002,
    HvRegisterDispatchSuspend = 0x00000003,

    // Version
    // 128-bit result same as CPUID 0x40000002
    HvRegisterHypervisorVersion = 0x00000100,

    // Feature Access (registers are 128 bits)

    // 128-bit result same as CPUID 0x40000003
    HvRegisterPrivilegesAndFeaturesInfo = 0x00000200,
    // 128-bit result same as CPUID 0x40000004
    HvRegisterFeaturesInfo = 0x00000201,
    // 128-bit result same as CPUID 0x40000005
    HvRegisterImplementationLimitsInfo = 0x00000202,
    // 128-bit result same as CPUID 0x40000006
    HvRegisterHardwareFeaturesInfo = 0x00000203,
    // 128-bit result same as CPUID 0x40000007
    HvRegisterCpuManagementFeaturesInfo = 0x00000204,
    // 128-bit result same as CPUID 0x40000008
    HvRegisterSvmFeaturesInfo = 0x00000205,
    // 128-bit result same as CPUID 0x40000009
    HvRegisterSkipLevelFeaturesInfo = 0x00000206,
    // 128-bit result same as CPUID 0x4000000A
    HvRegisterNestedVirtFeaturesInfo = 0x00000207,
    // 128-bit result same as CPUID 0x4000000C
    HvRegisterIsolationConfiguration = 0x00000209,

    // Guest Crash Registers

    HvRegisterGuestCrashP0 = 0x00000210,
    HvRegisterGuestCrashP1 = 0x00000211,
    HvRegisterGuestCrashP2 = 0x00000212,
    HvRegisterGuestCrashP3 = 0x00000213,
    HvRegisterGuestCrashP4 = 0x00000214,
    HvRegisterGuestCrashCtl = 0x00000215,

    // Power State Configuration

    HvRegisterPowerStateConfigC1 = 0x00000220,
    HvRegisterPowerStateTriggerC1 = 0x00000221,
    HvRegisterPowerStateConfigC2 = 0x00000222,
    HvRegisterPowerStateTriggerC2 = 0x00000223,
    HvRegisterPowerStateConfigC3 = 0x00000224,
    HvRegisterPowerStateTriggerC3 = 0x00000225,

    // Frequency Registers

    HvRegisterProcessorClockFrequency = 0x00000240,
    HvRegisterInterruptClockFrequency = 0x00000241,

    // Idle Register
    HvRegisterGuestIdle = 0x00000250,

    // Guest Debug
    HvRegisterDebugDeviceOptions = 0x00000260,

    // Memory Zeroing Conrol Register
    HvRegisterMemoryZeroingControl = 0x00000270,

    // Pending Interruption Register
    HvRegisterPendingInterruption = 0x00010002,

    // Interrupt State register
    HvRegisterInterruptState = 0x00010003,

    // Pending Event Register

    HvRegisterPendingEvent0 = 0x00010004,
    HvRegisterPendingEvent1 = 0x00010005,

    // Misc

    HvRegisterVpRuntime = 0x00090000,
    HvRegisterGuestOsId = 0x00090002,
    HvRegisterVpIndex = 0x00090003,
    HvRegisterTimeRefCount = 0x00090004,
    HvRegisterCpuManagementVersion = 0x00090007,
    HvRegisterVpAssistPage = 0x00090013,
    HvRegisterVpRootSignalCount = 0x00090014,

    // Performance statistics Registers

    HvRegisterStatsPartitionRetail = 0x00090020,
    HvRegisterStatsPartitionInternal = 0x00090021,
    HvRegisterStatsVpRetail = 0x00090022,
    HvRegisterStatsVpInternal = 0x00090023,
    HvRegisterNestedVpIndex = 0x00091003,

    // Hypervisor-defined Registers (Synic)

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
    HvRegisterNestedSint0 = 0x000A1000,
    HvRegisterNestedSint1 = 0x000A1001,
    HvRegisterNestedSint2 = 0x000A1002,
    HvRegisterNestedSint3 = 0x000A1003,
    HvRegisterNestedSint4 = 0x000A1004,
    HvRegisterNestedSint5 = 0x000A1005,
    HvRegisterNestedSint6 = 0x000A1006,
    HvRegisterNestedSint7 = 0x000A1007,
    HvRegisterNestedSint8 = 0x000A1008,
    HvRegisterNestedSint9 = 0x000A1009,
    HvRegisterNestedSint10 = 0x000A100A,
    HvRegisterNestedSint11 = 0x000A100B,
    HvRegisterNestedSint12 = 0x000A100C,
    HvRegisterNestedSint13 = 0x000A100D,
    HvRegisterNestedSint14 = 0x000A100E,
    HvRegisterNestedSint15 = 0x000A100F,
    HvRegisterNestedScontrol = 0x000A1010,
    HvRegisterNestedSversion = 0x000A1011,
    HvRegisterNestedSifp = 0x000A1012,
    HvRegisterNestedSipp = 0x000A1013,
    HvRegisterNestedEom = 0x000A1014,
    HvRegisterNestedSirbp = 0x000A1015,

    // Hypervisor-defined Registers (Synthetic Timers)

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

    // Synthetic VSM registers

    // 0x000D0000-1 are available for future use.
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
    HvRegisterIsolationCapabilities = 0x000D0100,

#if defined(_M_AMD64) || defined(_M_IX86)
    // Interruptible notification register
    HvX64RegisterDeliverabilityNotifications = 0x00010006,

    // X64 User-Mode Registers

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

    // X64 Floating Point and Vector Registers

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

    // X64 Control Registers

    HvX64RegisterCr0 = 0x00040000,
    HvX64RegisterCr2 = 0x00040001,
    HvX64RegisterCr3 = 0x00040002,
    HvX64RegisterCr4 = 0x00040003,
    HvX64RegisterCr8 = 0x00040004,
    HvX64RegisterXfem = 0x00040005,

    // X64 Intermediate Control Registers

    HvX64RegisterIntermediateCr0 = 0x00041000,
    HvX64RegisterIntermediateCr4 = 0x00041003,
    HvX64RegisterIntermediateCr8 = 0x00041004,

    // X64 Debug Registers

    HvX64RegisterDr0 = 0x00050000,
    HvX64RegisterDr1 = 0x00050001,
    HvX64RegisterDr2 = 0x00050002,
    HvX64RegisterDr3 = 0x00050003,
    HvX64RegisterDr6 = 0x00050004,
    HvX64RegisterDr7 = 0x00050005,

    // X64 Segment Registers

    HvX64RegisterEs = 0x00060000,
    HvX64RegisterCs = 0x00060001,
    HvX64RegisterSs = 0x00060002,
    HvX64RegisterDs = 0x00060003,
    HvX64RegisterFs = 0x00060004,
    HvX64RegisterGs = 0x00060005,
    HvX64RegisterLdtr = 0x00060006,
    HvX64RegisterTr = 0x00060007,

    // X64 Table Registers

    HvX64RegisterIdtr = 0x00070000,
    HvX64RegisterGdtr = 0x00070001,

    // X64 Virtualized MSRs

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

    // X64 Cache control MSRs

    HvX64RegisterMsrMtrrCap = 0x0008000D,
    HvX64RegisterMsrMtrrDefType = 0x0008000E,
    HvX64RegisterMsrMtrrPhysBase0 = 0x00080010,
    HvX64RegisterMsrMtrrPhysBase1 = 0x00080011,
    HvX64RegisterMsrMtrrPhysBase2 = 0x00080012,
    HvX64RegisterMsrMtrrPhysBase3 = 0x00080013,
    HvX64RegisterMsrMtrrPhysBase4 = 0x00080014,
    HvX64RegisterMsrMtrrPhysBase5 = 0x00080015,
    HvX64RegisterMsrMtrrPhysBase6 = 0x00080016,
    HvX64RegisterMsrMtrrPhysBase7 = 0x00080017,
    HvX64RegisterMsrMtrrPhysBase8 = 0x00080018,
    HvX64RegisterMsrMtrrPhysBase9 = 0x00080019,
    HvX64RegisterMsrMtrrPhysBaseA = 0x0008001A,
    HvX64RegisterMsrMtrrPhysBaseB = 0x0008001B,
    HvX64RegisterMsrMtrrPhysBaseC = 0x0008001C,
    HvX64RegisterMsrMtrrPhysBaseD = 0x0008001D,
    HvX64RegisterMsrMtrrPhysBaseE = 0x0008001E,
    HvX64RegisterMsrMtrrPhysBaseF = 0x0008001F,
    HvX64RegisterMsrMtrrPhysMask0 = 0x00080040,
    HvX64RegisterMsrMtrrPhysMask1 = 0x00080041,
    HvX64RegisterMsrMtrrPhysMask2 = 0x00080042,
    HvX64RegisterMsrMtrrPhysMask3 = 0x00080043,
    HvX64RegisterMsrMtrrPhysMask4 = 0x00080044,
    HvX64RegisterMsrMtrrPhysMask5 = 0x00080045,
    HvX64RegisterMsrMtrrPhysMask6 = 0x00080046,
    HvX64RegisterMsrMtrrPhysMask7 = 0x00080047,
    HvX64RegisterMsrMtrrPhysMask8 = 0x00080048,
    HvX64RegisterMsrMtrrPhysMask9 = 0x00080049,
    HvX64RegisterMsrMtrrPhysMaskA = 0x0008004A,
    HvX64RegisterMsrMtrrPhysMaskB = 0x0008004B,
    HvX64RegisterMsrMtrrPhysMaskC = 0x0008004C,
    HvX64RegisterMsrMtrrPhysMaskD = 0x0008004D,
    HvX64RegisterMsrMtrrPhysMaskE = 0x0008004E,
    HvX64RegisterMsrMtrrPhysMaskF = 0x0008004F,
    HvX64RegisterMsrMtrrFix64k00000 = 0x00080070,
    HvX64RegisterMsrMtrrFix16k80000 = 0x00080071,
    HvX64RegisterMsrMtrrFix16kA0000 = 0x00080072,
    HvX64RegisterMsrMtrrFix4kC0000 = 0x00080073,
    HvX64RegisterMsrMtrrFix4kC8000 = 0x00080074,
    HvX64RegisterMsrMtrrFix4kD0000 = 0x00080075,
    HvX64RegisterMsrMtrrFix4kD8000 = 0x00080076,
    HvX64RegisterMsrMtrrFix4kE0000 = 0x00080077,
    HvX64RegisterMsrMtrrFix4kE8000 = 0x00080078,
    HvX64RegisterMsrMtrrFix4kF0000 = 0x00080079,
    HvX64RegisterMsrMtrrFix4kF8000 = 0x0008007A,
    HvX64RegisterTscAux = 0x0008007B,
    HvX64RegisterBndcfgs = 0x0008007C,
    HvX64RegisterDebugCtl = 0x0008007D,

    // Available

    HvX64RegisterAvailable0008007E = 0x0008007E,
    HvX64RegisterAvailable0008007F = 0x0008007F,
    HvX64RegisterSgxLaunchControl0 = 0x00080080,
    HvX64RegisterSgxLaunchControl1 = 0x00080081,
    HvX64RegisterSgxLaunchControl2 = 0x00080082,
    HvX64RegisterSgxLaunchControl3 = 0x00080083,
    HvX64RegisterSpecCtrl = 0x00080084,
    HvX64RegisterPredCmd = 0x00080085,

    // Other MSRs

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

    // Performance monitoring MSRs

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

    // Hypervisor-defined registers (Misc)
    HvX64RegisterHypercall = 0x00090001,

    // X64 Virtual APIC registers MSRs

    HvX64RegisterEoi = 0x00090010,
    HvX64RegisterIcr = 0x00090011,
    HvX64RegisterTpr = 0x00090012,

    // Partition Timer Assist Registers

    HvX64RegisterEmulatedTimerPeriod = 0x00090030,
    HvX64RegisterEmulatedTimerControl = 0x00090031,
    HvX64RegisterPmTimerAssist = 0x00090032,

    // Intercept Control Registers

    HvX64RegisterCrInterceptControl = 0x000E0000,
    HvX64RegisterCrInterceptCr0Mask = 0x000E0001,
    HvX64RegisterCrInterceptCr4Mask = 0x000E0002,
    HvX64RegisterCrInterceptIa32MiscEnableMask = 0x000E0003,
#elif defined(_M_ARM64)
    // ARM64 Registers

    HvArm64RegisterX0 = 0x00020000,
    HvArm64RegisterX1 = 0x00020001,
    HvArm64RegisterX2 = 0x00020002,
    HvArm64RegisterX3 = 0x00020003,
    HvArm64RegisterX4 = 0x00020004,
    HvArm64RegisterX5 = 0x00020005,
    HvArm64RegisterX6 = 0x00020006,
    HvArm64RegisterX7 = 0x00020007,
    HvArm64RegisterX8 = 0x00020008,
    HvArm64RegisterX9 = 0x00020009,
    HvArm64RegisterX10 = 0x0002000A,
    HvArm64RegisterX11 = 0x0002000B,
    HvArm64RegisterX12 = 0x0002000C,
    HvArm64RegisterX13 = 0x0002000D,
    HvArm64RegisterX14 = 0x0002000E,
    HvArm64RegisterX15 = 0x0002000F,
    HvArm64RegisterX16 = 0x00020010,
    HvArm64RegisterX17 = 0x00020011,
    HvArm64RegisterX18 = 0x00020012,
    HvArm64RegisterX19 = 0x00020013,
    HvArm64RegisterX20 = 0x00020014,
    HvArm64RegisterX21 = 0x00020015,
    HvArm64RegisterX22 = 0x00020016,
    HvArm64RegisterX23 = 0x00020017,
    HvArm64RegisterX24 = 0x00020018,
    HvArm64RegisterX25 = 0x00020019,
    HvArm64RegisterX26 = 0x0002001A,
    HvArm64RegisterX27 = 0x0002001B,
    HvArm64RegisterX28 = 0x0002001C,
    HvArm64RegisterXFp = 0x0002001D,
    HvArm64RegisterXLr = 0x0002001E,
    // alias for either El0/x depending on Cpsr.SPSel
    HvArm64RegisterXSp = 0x0002001F,
    HvArm64RegisterXSpEl0 = 0x00020020,
    HvArm64RegisterXSpElx = 0x00020021,
    HvArm64RegisterXPc = 0x00020022,
    HvArm64RegisterCpsr = 0x00020023,
    HvArm64RegisterQ0 = 0x00030000,
    HvArm64RegisterQ1 = 0x00030001,
    HvArm64RegisterQ2 = 0x00030002,
    HvArm64RegisterQ3 = 0x00030003,
    HvArm64RegisterQ4 = 0x00030004,
    HvArm64RegisterQ5 = 0x00030005,
    HvArm64RegisterQ6 = 0x00030006,
    HvArm64RegisterQ7 = 0x00030007,
    HvArm64RegisterQ8 = 0x00030008,
    HvArm64RegisterQ9 = 0x00030009,
    HvArm64RegisterQ10 = 0x0003000A,
    HvArm64RegisterQ11 = 0x0003000B,
    HvArm64RegisterQ12 = 0x0003000C,
    HvArm64RegisterQ13 = 0x0003000D,
    HvArm64RegisterQ14 = 0x0003000E,
    HvArm64RegisterQ15 = 0x0003000F,
    HvArm64RegisterQ16 = 0x00030010,
    HvArm64RegisterQ17 = 0x00030011,
    HvArm64RegisterQ18 = 0x00030012,
    HvArm64RegisterQ19 = 0x00030013,
    HvArm64RegisterQ20 = 0x00030014,
    HvArm64RegisterQ21 = 0x00030015,
    HvArm64RegisterQ22 = 0x00030016,
    HvArm64RegisterQ23 = 0x00030017,
    HvArm64RegisterQ24 = 0x00030018,
    HvArm64RegisterQ25 = 0x00030019,
    HvArm64RegisterQ26 = 0x0003001A,
    HvArm64RegisterQ27 = 0x0003001B,
    HvArm64RegisterQ28 = 0x0003001C,
    HvArm64RegisterQ29 = 0x0003001D,
    HvArm64RegisterQ30 = 0x0003001E,
    HvArm64RegisterQ31 = 0x0003001F,
    HvArm64RegisterFpControl = 0x00030020,
    HvArm64RegisterFpStatus = 0x00030021,

    // Debug Registers

    HvArm64RegisterBcr0 = 0x00050000,
    HvArm64RegisterBcr1 = 0x00050001,
    HvArm64RegisterBcr2 = 0x00050002,
    HvArm64RegisterBcr3 = 0x00050003,
    HvArm64RegisterBcr4 = 0x00050004,
    HvArm64RegisterBcr5 = 0x00050005,
    HvArm64RegisterBcr6 = 0x00050006,
    HvArm64RegisterBcr7 = 0x00050007,
    HvArm64RegisterBcr8 = 0x00050008,
    HvArm64RegisterBcr9 = 0x00050009,
    HvArm64RegisterBcr10 = 0x0005000A,
    HvArm64RegisterBcr11 = 0x0005000B,
    HvArm64RegisterBcr12 = 0x0005000C,
    HvArm64RegisterBcr13 = 0x0005000D,
    HvArm64RegisterBcr14 = 0x0005000E,
    HvArm64RegisterBcr15 = 0x0005000F,
    HvArm64RegisterWcr0 = 0x00050010,
    HvArm64RegisterWcr1 = 0x00050011,
    HvArm64RegisterWcr2 = 0x00050012,
    HvArm64RegisterWcr3 = 0x00050013,
    HvArm64RegisterWcr4 = 0x00050014,
    HvArm64RegisterWcr5 = 0x00050015,
    HvArm64RegisterWcr6 = 0x00050016,
    HvArm64RegisterWcr7 = 0x00050017,
    HvArm64RegisterWcr8 = 0x00050018,
    HvArm64RegisterWcr9 = 0x00050019,
    HvArm64RegisterWcr10 = 0x0005001A,
    HvArm64RegisterWcr11 = 0x0005001B,
    HvArm64RegisterWcr12 = 0x0005001C,
    HvArm64RegisterWcr13 = 0x0005001D,
    HvArm64RegisterWcr14 = 0x0005001E,
    HvArm64RegisterWcr15 = 0x0005001F,
    HvArm64RegisterBvr0 = 0x00050020,
    HvArm64RegisterBvr1 = 0x00050021,
    HvArm64RegisterBvr2 = 0x00050022,
    HvArm64RegisterBvr3 = 0x00050023,
    HvArm64RegisterBvr4 = 0x00050024,
    HvArm64RegisterBvr5 = 0x00050025,
    HvArm64RegisterBvr6 = 0x00050026,
    HvArm64RegisterBvr7 = 0x00050027,
    HvArm64RegisterBvr8 = 0x00050028,
    HvArm64RegisterBvr9 = 0x00050029,
    HvArm64RegisterBvr10 = 0x0005002A,
    HvArm64RegisterBvr11 = 0x0005002B,
    HvArm64RegisterBvr12 = 0x0005002C,
    HvArm64RegisterBvr13 = 0x0005002D,
    HvArm64RegisterBvr14 = 0x0005002E,
    HvArm64RegisterBvr15 = 0x0005002F,
    HvArm64RegisterWvr0 = 0x00050030,
    HvArm64RegisterWvr1 = 0x00050031,
    HvArm64RegisterWvr2 = 0x00050032,
    HvArm64RegisterWvr3 = 0x00050033,
    HvArm64RegisterWvr4 = 0x00050034,
    HvArm64RegisterWvr5 = 0x00050035,
    HvArm64RegisterWvr6 = 0x00050036,
    HvArm64RegisterWvr7 = 0x00050037,
    HvArm64RegisterWvr8 = 0x00050038,
    HvArm64RegisterWvr9 = 0x00050039,
    HvArm64RegisterWvr10 = 0x0005003A,
    HvArm64RegisterWvr11 = 0x0005003B,
    HvArm64RegisterWvr12 = 0x0005003C,
    HvArm64RegisterWvr13 = 0x0005003D,
    HvArm64RegisterWvr14 = 0x0005003E,
    HvArm64RegisterWvr15 = 0x0005003F,

    // Control Registers

    HvArm64RegisterMidr = 0x00040000,
    HvArm64RegisterMpidr = 0x00040001,
    HvArm64RegisterSctlr = 0x00040002,
    HvArm64RegisterActlr = 0x00040003,
    HvArm64RegisterCpacr = 0x00040004,
    HvArm64RegisterTtbr0 = 0x00040005,
    HvArm64RegisterTtbr1 = 0x00040006,
    HvArm64RegisterTcr = 0x00040007,
    HvArm64RegisterEsrEl1 = 0x00040008,
    HvArm64RegisterFarEl1 = 0x00040009,
    HvArm64RegisterParEl1 = 0x0004000A,
    HvArm64RegisterMair = 0x0004000B,
    HvArm64RegisterVbar = 0x0004000C,
    HvArm64RegisterContextIdr = 0x0004000D,
    HvArm64RegisterTpidr = 0x0004000E,
    HvArm64RegisterCntkctl = 0x0004000F,
    HvArm64RegisterTpidrroEl0 = 0x00040010,
    HvArm64RegisterTpidrEl0 = 0x00040011,
    HvArm64RegisterFpcrEl1 = 0x00040012,
    HvArm64RegisterFpsrEl1 = 0x00040013,
    HvArm64RegisterSpsrEl1 = 0x00040014,
    HvArm64RegisterElrEl1 = 0x00040015,
    HvArm64RegisterAfsr0 = 0x00040016,
    HvArm64RegisterAfsr1 = 0x00040017,
    HvArm64RegisterAMair = 0x00040018,
    HvArm64RegisterMdscr = 0x00040019,

    // Trap control

    HvArm64RegisterMdcr = 0x00040101,
    HvArm64RegisterCptr = 0x00040102,
    HvArm64RegisterHstr = 0x00040103,
    HvArm64RegisterHacr = 0x00040104,

    // GIT Registers

    HvArm64RegisterCnthCtl = 0x000B0400,
    HvArm64RegisterCntkCtl = 0x000B0401,
    HvArm64RegisterCntpCtl = 0x000B0402,
    HvArm64RegisterCntpCval = 0x000B0403,
    HvArm64RegisterCntvOffset = 0x000B0404,
    HvArm64RegisterCntvCtl = 0x000B0405,
    HvArm64RegisterCntvCval = 0x000B0406,

    // Status Registers

    HvArm64RegisterCtr = 0x00040300,
    HvArm64RegisterDczid = 0x00040301,
    HvArm64RegisterRevidr = 0x00040302,
    HvArm64RegisterIdAa64pfr0 = 0x00040303,
    HvArm64RegisterIdAa64pfr1 = 0x00040304,
    HvArm64RegisterIdAa64dfr0 = 0x00040305,
    HvArm64RegisterIdAa64dfr1 = 0x00040306,
    HvArm64RegisterIdAa64afr0 = 0x00040307,
    HvArm64RegisterIdAa64afr1 = 0x00040308,
    HvArm64RegisterIdAa64isar0 = 0x00040309,
    HvArm64RegisterIdAa64isar1 = 0x0004030A,
    HvArm64RegisterIdAa64mmfr0 = 0x0004030B,
    HvArm64RegisterIdAa64mmfr1 = 0x0004030C,
    HvArm64RegisterClidr = 0x0004030D,
    HvArm64RegisterAidr = 0x0004030E,
    HvArm64RegisterCsselr = 0x0004030F,
    HvArm64RegisterCcsidr = 0x00040310,

    // Address to use for synthetic exceptions
    HvArm64RegisterSyntheticException = 0x00040400,

    // Misc

    // low 32 bits result same as CPUID 0x40000001
    HvArm64RegisterInterfaceVersion = 0x00090006,
    HvArm64RegisterPartitionInfoPage = 0x00090015,
    HvArm64RegisterTlbiControl = 0x00090016,
#endif
} HV_REGISTER_NAME, *PHV_REGISTER_NAME;

typedef union _HV_REGISTER_VALUE
{
    HV_UINT128 Reg128;
    HV_UINT64 Reg64;
    HV_UINT32 Reg32;
    HV_UINT16 Reg16;
    HV_UINT8 Reg8;
} HV_REGISTER_VALUE, *PHV_REGISTER_VALUE;

// Definition for HvStartVirtualProcessor hypercall input structure.
// This sets the values provided in VpContext and makes the said Vp runnable.
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_START_VIRTUAL_PROCESSOR
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
    HV_INITIAL_VP_CONTEXT VpContext;
} HV_INPUT_START_VIRTUAL_PROCESSOR, *PHV_INPUT_START_VIRTUAL_PROCESSOR;

// Definitions for the HvCallModifySparseGpaPageHostVisibility hypercall.
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MODIFY_SPARSE_GPA_PAGE_HOST_VISIBILITY
{
    // Supplies the partition ID of the partition this request is for.
    HV_PARTITION_ID TargetPartitionId;
    // Supplies the new host visibility.
    HV_UINT32 HostVisibility : 2;
    HV_UINT32 Reserved0 : 30;
    HV_UINT32 Reserved1;
    // Supplies an array of GPA page numbers to modify.
    HV_CALL_ATTRIBUTES HV_GPA_PAGE_NUMBER GpaPageList[HV_ANYSIZE_ARRAY];
} HV_INPUT_MODIFY_SPARSE_GPA_PAGE_HOST_VISIBILITY, *PHV_INPUT_MODIFY_SPARSE_GPA_PAGE_HOST_VISIBILITY;

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4201) // nameless struct/union
#endif
#endif

#endif // !MILE_HYPERV_GUEST_INTERFACE
