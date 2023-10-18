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

#endif // !MILE_HYPERV_TLFS
