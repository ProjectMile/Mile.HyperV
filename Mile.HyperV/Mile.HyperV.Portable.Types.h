/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.Portable.Types.h
 * PURPOSE:    Definition for Hyper-V Portable Types
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef MILE_HYPERV_PORTABLE_TYPES
#define MILE_HYPERV_PORTABLE_TYPES

#if !defined(_M_AMD64) && !defined(_M_ARM64) && !defined(_M_IX86)
#error [Mile.HyperV] The architecture is not supported.
#endif

#ifdef MILE_MOBILITY_PORTABLE_TYPES

typedef MO_INT8 HV_INT8, *PHV_INT8;
typedef MO_INT16 HV_INT16, *PHV_INT16;
typedef MO_INT32 HV_INT32, *PHV_INT32;
typedef MO_INT64 HV_INT64, *PHV_INT64;

typedef MO_UINT8 HV_UINT8, *PHV_UINT8;
typedef MO_UINT16 HV_UINT16, *PHV_UINT16;
typedef MO_UINT32 HV_UINT32, *PHV_UINT32;
typedef MO_UINT64 HV_UINT64, *PHV_UINT64;

typedef MO_WIDE_CHAR HV_WCHAR;

typedef MO_GUID HV_GUID, *PHV_GUID;

#ifndef HV_FIELD_OFFSET
#define HV_FIELD_OFFSET(TYPE, Field) MO_FIELD_OFFSET(TYPE, Field)
#endif // !HV_FIELD_OFFSET

#ifndef HV_FIELD_SIZE
#define HV_FIELD_SIZE(TYPE, Field) MO_FIELD_SIZE(TYPE, Field)
#endif // !HV_FIELD_SIZE

#ifndef HV_FIELD_SIZE_THROUGH
#define HV_FIELD_SIZE_THROUGH(TYPE, Field) MO_FIELD_SIZE_THROUGH(TYPE, Field)
#endif // !HV_FIELD_SIZE_THROUGH

#ifndef HV_FIELD_CONTAINS
#define HV_FIELD_CONTAINS(Struct, Size, Field) \
    MO_FIELD_CONTAINS(Struct, Size, Field)
#endif // !HV_FIELD_CONTAINS

#ifndef HV_DECLSPEC_ALIGN
#define HV_DECLSPEC_ALIGN(x) MO_DECLSPEC_ALIGN(x)
#endif // !HV_DECLSPEC_ALIGN

#ifndef HV_ANYSIZE_ARRAY
#define HV_ANYSIZE_ARRAY MO_ANYSIZE_ARRAY
#endif // !HV_ANYSIZE_ARRAY

#ifndef HV_STATIC_ASSERT
#define HV_STATIC_ASSERT(Expression) MO_C_STATIC_ASSERT(Expression)
#endif // !HV_STATIC_ASSERT

#else

#include <stdint.h>

typedef int8_t HV_INT8, *PHV_INT8;
typedef int16_t HV_INT16, *PHV_INT16;
typedef int32_t HV_INT32, *PHV_INT32;
typedef int64_t HV_INT64, *PHV_INT64;

typedef uint8_t HV_UINT8, *PHV_UINT8;
typedef uint16_t HV_UINT16, *PHV_UINT16;
typedef uint32_t HV_UINT32, *PHV_UINT32;
typedef uint64_t HV_UINT64, *PHV_UINT64;

#ifdef _WCHAR_T_DEFINED
typedef wchar_t HV_WCHAR;
#else
typedef HV_UINT16 HV_WCHAR;
#endif

#ifdef GUID_DEFINED
typedef GUID HV_GUID, *PHV_GUID;
#else
typedef struct _HV_GUID
{
    HV_UINT32 Data1;
    HV_UINT16 Data2;
    HV_UINT16 Data3;
    HV_UINT8 Data4[8];
} HV_GUID, *PHV_GUID;
#endif

#ifndef HV_FIELD_OFFSET
#define HV_FIELD_OFFSET(TYPE, Field) ((HV_UINT64)&(((TYPE*)0)->Field))
#endif // !HV_FIELD_OFFSET

#ifndef HV_FIELD_SIZE
#define HV_FIELD_SIZE(TYPE, Field) (sizeof(((TYPE*)0)->Field))
#endif // !HV_FIELD_SIZE

#ifndef HV_FIELD_SIZE_THROUGH
#define HV_FIELD_SIZE_THROUGH(TYPE, Field) \
    (HV_FIELD_OFFSET(TYPE, Field) + HV_FIELD_SIZE(TYPE, Field))
#endif // !HV_FIELD_SIZE_THROUGH

#ifndef HV_FIELD_CONTAINS
#define HV_FIELD_CONTAINS(Struct, Size, Field) ( \
    (((PHV_UINT8)(&(Struct)->Field)) + sizeof((Struct)->Field)) \
    <= (((PHV_UINT8)(Struct)) + (Size)))
#endif // !HV_FIELD_CONTAINS

#ifndef HV_DECLSPEC_ALIGN
#ifdef _MSC_VER
#if (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#define HV_DECLSPEC_ALIGN(x) __declspec(align(x))
#else
#define HV_DECLSPEC_ALIGN(x)
#endif
#else
#define HV_DECLSPEC_ALIGN(x) __attribute__ ((aligned(x)))
#endif
#endif // !HV_DECLSPEC_ALIGN

#ifndef HV_ANYSIZE_ARRAY
#define HV_ANYSIZE_ARRAY 1
#endif // !HV_ANYSIZE_ARRAY

#ifndef HV_STATIC_ASSERT
#define HV_STATIC_ASSERT(Expression) \
    typedef char __HV_STATIC_ASSERT__[(Expression) ? 1 : -1]
#endif // !HV_STATIC_ASSERT

#endif

#endif // !MILE_HYPERV_PORTABLE_TYPES
