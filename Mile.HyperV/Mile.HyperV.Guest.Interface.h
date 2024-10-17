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
//   - MsvmPkg\Include\Hv\HvGuest.h
//   - MsvmPkg\Include\Hv\HvStatus.h

#ifndef MILE_HYPERV_GUEST_INTERFACE
#define MILE_HYPERV_GUEST_INTERFACE

#if !defined(_M_AMD64) && !defined(_M_ARM64)
#error [Mile.HyperV] Unknown/Unsupported architecture
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
#pragma warning(disable:4201) // nameless struct/union
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
#pragma warning(default:4201) // nameless struct/union
} HV_X64_SEGMENT_REGISTER, *PHV_X64_SEGMENT_REGISTER;

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

#endif // !MILE_HYPERV_GUEST_INTERFACE
