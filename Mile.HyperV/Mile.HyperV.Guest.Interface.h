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

typedef uint16_t HV_UINT16, *PHV_UINT16;
typedef uint64_t HV_UINT64, *PHV_UINT64;

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

#endif // !MILE_HYPERV_GUEST_INTERFACE
