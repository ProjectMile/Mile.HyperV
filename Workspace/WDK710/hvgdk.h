/*++

Copyright (c) Microsoft Corporation

Module Name:

    HvGdk.h

Abstract:

    Type definitions for the hypervisor guest interface.

Author:

    Hypervisor Engineering Team (hvet) 01-May-2005

--*/

#if !defined(_HVGDK_)
#define _HVGDK_

#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning(disable:4200) // zero length array
#pragma warning(disable:4214) // bit field types other than int
#pragma warning(disable:4324) // structure was padded due to __declspec(align())

/******************************************************************************/

typedef enum _HV_PROCESSOR_VENDOR
{
    HvProcessorVendorAmd        = 0x0000,
    HvProcessorVendorIntel      = 0x0001

} HV_PROCESSOR_VENDOR, *PHV_PROCESSOR_VENDOR;


//
// Define the structure defining the processor related features
// that may be de-featured.
// 

typedef union _HV_PARTITION_PROCESSOR_FEATURES
{
    struct
    {
        UINT64 Sse3Support:1;
        UINT64 LahfSahfSupport:1;
        UINT64 Ssse3Support:1;
        UINT64 Sse4_1Support:1;
        UINT64 Sse4_2Support:1;
        UINT64 Sse4aSupport:1;
        UINT64 Sse5Support:1;
        UINT64 PopCntSupport:1;
        UINT64 Cmpxchg16bSupport:1;
        UINT64 Altmovcr8Support:1;
        UINT64 LzcntSupport:1;
        UINT64 MisAlignSseSupport:1;
        UINT64 MmxExtSupport:1;
        UINT64 Amd3DNowSupport:1;
        UINT64 ExtendedAmd3DNowSupport:1;
        UINT64 Page1GBSupport:1;
        UINT64 Reserved1:48;
    };
    UINT64 AsUINT64;

} HV_PARTITION_PROCESSOR_FEATURES, *PHV_PARTITION_PROCESSOR_FEATURES;

//
// Define the processor features avaialble in Intel and AMD compatibility mode.
//

#define HV_PARTITION_PROCESSOR_FEATURES_INTEL_COMPATIBILITY_MODE \
{   1,   /* Sse3Support */ \
    1,   /* LahfSahfSupport */ \
    0,   /* Ssse3Support */ \
    0,   /* Sse4_1Support */ \
    0,   /* Sse4_2Support */ \
    0,   /* Sse4aSupport */ \
    0,   /* Sse5Support */ \
    0,   /* PopCntSupport */ \
    1,   /* Cmpxchg16bSupport */ \
    0,   /* Altmovcr8Support */ \
    0,   /* LzcntSupport */ \
    0,   /* MisAlignSseSupport */ \
    0,   /* MmxExtSupport */ \
    0,   /* Amd3DNowSupport */ \
    0,   /* ExtendedAmd3DNowSupport */ \
    0,   /* Page1GBSupport */ \
    0    /* Reserved1 */ \
}

#define HV_PARTITION_PROCESSOR_FEATURES_AMD_COMPATIBILITY_MODE \
{ \
    1,   /* Sse3Support */ \
    1,   /* LahfSahfSupport */ \
    0,   /* Ssse3Support */ \
    0,   /* Sse4_1Support */ \
    0,   /* Sse4_2Support */ \
    0,   /* Sse4aSupport */ \
    0,   /* Sse5Support */ \
    0,   /* PopCntSupport */ \
    1,   /* Cmpxchg16bSupport */ \
    1,   /* Altmovcr8Support */ \
    0,   /* LzcntSupport */ \
    0,   /* MisAlignSseSupport */ \
    1,   /* MmxExtSupport */ \
    0,   /* Amd3DNowSupport */ \
    0,   /* ExtendedAmd3DNowSupport */ \
    0,   /* Page1GBSupport */ \
    0    /* Reserved1 */ \
}

//
// Define the structure defining the processor XSAVE related features
// that may be de-featured.
// 

typedef union _HV_PARTITION_PROCESSOR_XSAVE_FEATURES
{
    struct
    {
        UINT64 XsaveSupport:1;
        UINT64 XsaveoptSupport:1;
        UINT64 AvxSupport:1;
        UINT64 Reserved1:61;
    };
    UINT64 AsUINT64;

} HV_PARTITION_PROCESSOR_XSAVE_FEATURES, *PHV_PARTITION_PROCESSOR_XSAVE_FEATURES;

//
// Define the processor features avaialble in Intel and AMD compatibility mode.
//

#define HV_PARTITION_PROCESSOR_XSAVE_FEATURES_INTEL_COMPATIBILITY_MODE \
{ \
    0,   /* XsaveSupport */ \
    0,   /* XsaveoptSupport */ \
    0,   /* AvxSupport */ \
    0    /* Reserved1 */ \
}

#define HV_PARTITION_PROCESSOR_XSAVE_FEATURES_AMD_COMPATIBILITY_MODE \
{ \
    0,   /* XsaveSupport */ \
    0,   /* XsaveoptSupport */ \
    0,   /* AvxSupport */ \
    0    /* Reserved1 */ \
}

//
// Define the processor cache line flush size Intel and AMD compatibility mode.
//

#define HV_PARTITION_PROCESSOR_CL_FLUSHSIZE_INTEL_COMPATIBILITY_MODE (8)
#define HV_PARTITION_PROCESSOR_CL_FLUSHSIZE_AMD_COMPATIBILITY_MODE (8)


typedef union _HV_EXPLICIT_SUSPEND_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Suspended:1;
        UINT64 Reserved:63;
    };
} HV_EXPLICIT_SUSPEND_REGISTER, *PHV_EXPLICIT_SUSPEND_REGISTER;

typedef union _HV_INTERCEPT_SUSPEND_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Suspended:1;
        UINT64 TlbLocked:1;
        UINT64 Reserved:62;
    };
} HV_INTERCEPT_SUSPEND_REGISTER, *PHV_INTERCEPT_SUSPEND_REGISTER;

typedef union _HV_X64_INTERRUPT_STATE_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 InterruptShadow:1;
        UINT64 NmiMasked:1;
        UINT64 Reserved:62;
    };
} HV_X64_INTERRUPT_STATE_REGISTER, *PHV_X64_INTERRUPT_STATE_REGISTER;

typedef enum _HV_X64_PENDING_INTERRUPTION_TYPE
{
    HvX64PendingInterrupt           = 0,
    HvX64PendingNmi                 = 2,
    HvX64PendingException           = 3
} HV_X64_PENDING_INTERRUPTION_TYPE, *PHV_X64_PENDING_INTERRUPTION_TYPE;

typedef union _HV_X64_PENDING_INTERRUPTION_REGISTER
{
    UINT64 AsUINT64;
    struct
    {
        UINT32 InterruptionPending:1;
        UINT32 InterruptionType:3;
        UINT32 DeliverErrorCode:1;
        UINT32 Reserved:11;
        UINT32 InterruptionVector:16;
        UINT32 ErrorCode;
    };
} HV_X64_PENDING_INTERRUPTION_REGISTER, *PHV_X64_PENDING_INTERRUPTION_REGISTER;

typedef union _HV_REGISTER_VALUE
{
    HV_UINT128                              Reg128;
    UINT64                                  Reg64;
    UINT32                                  Reg32;
    UINT16                                  Reg16;
    UINT8                                   Reg8;
    HV_X64_FP_REGISTER                      Fp;
    HV_X64_FP_CONTROL_STATUS_REGISTER       FpControlStatus;
    HV_X64_XMM_CONTROL_STATUS_REGISTER      XmmControlStatus;
    HV_X64_SEGMENT_REGISTER                 Segment;
    HV_X64_TABLE_REGISTER                   Table;
    HV_EXPLICIT_SUSPEND_REGISTER            ExplicitSuspend;
    HV_INTERCEPT_SUSPEND_REGISTER           InterceptSuspend;
    HV_X64_INTERRUPT_STATE_REGISTER         InterruptState;
    HV_X64_PENDING_INTERRUPTION_REGISTER    PendingInterruption;
} HV_REGISTER_VALUE, *PHV_REGISTER_VALUE;
typedef const HV_REGISTER_VALUE *PCHV_REGISTER_VALUE;

//
// Define the intercept access types.
//

typedef UINT8 HV_INTERCEPT_ACCESS_TYPE;

#define HV_INTERCEPT_ACCESS_READ    0
#define HV_INTERCEPT_ACCESS_WRITE   1
#define HV_INTERCEPT_ACCESS_EXECUTE 2

typedef UINT32 HV_INTERCEPT_ACCESS_TYPE_MASK;

#define HV_INTERCEPT_ACCESS_MASK_NONE       0x00
#define HV_INTERCEPT_ACCESS_MASK_READ       0X01
#define HV_INTERCEPT_ACCESS_MASK_WRITE      0x02
#define HV_INTERCEPT_ACCESS_MASK_EXECUTE    0x04


//
// Define intercept types.
//
typedef enum _HV_INTERCEPT_TYPE
{
    //
    // Platform-specific intercept types.
    //
    HvInterceptTypeX64IoPort = 0x00000000,
    HvInterceptTypeX64Msr = 0x00000001,
    HvInterceptTypeX64Cpuid = 0x00000002,
    HvInterceptTypeX64Exception = 0x00000003,

} HV_INTERCEPT_TYPE, *PHV_INTERCEPT_TYPE;


//
// Define IO port type.
//
typedef UINT16 HV_X64_IO_PORT, *PHV_X64_IO_PORT;


//
// Define intercept parameters.
//
typedef union _HV_INTERCEPT_PARAMETERS
{
    //
    // HV_INTERCEPT_PARAMETERS is defined to be an 8-byte field.
    //
    UINT64 AsUINT64;

    //
    // HvInterceptTypeX64IoPort.
    //
    HV_X64_IO_PORT IoPort;

    //
    // HvInterceptTypeX64Cpuid.
    //
    UINT32 CpuidIndex;

    //
    // HvInterceptTypeX64Exception.
    //
    UINT16 ExceptionVector;

    //
    // N.B. Other intercept types do not have any paramaters.
    //

} HV_INTERCEPT_PARAMETERS, *PHV_INTERCEPT_PARAMETERS;


//
// Define intercept descriptor structure.
//
typedef struct  _HV_INTERCEPT_DESCRIPTOR
{
    HV_INTERCEPT_TYPE Type;
    HV_INTERCEPT_PARAMETERS Parameters;
} HV_INTERCEPT_DESCRIPTOR, *PHV_INTERCEPT_DESCRIPTOR;
typedef const HV_INTERCEPT_DESCRIPTOR *PCHV_INTERCEPT_DESCRIPTOR;

//
// Virtual Processor Indices
//
typedef UINT32 HV_VP_INDEX, *PHV_VP_INDEX;

#define HV_MAX_VP_INDEX (63)

//
// Address spaces presented by the guest.
//
typedef UINT64 HV_ADDRESS_SPACE_ID, *PHV_ADDRESS_SPACE_ID;

//
// Address space flush flags.
//
typedef UINT64 HV_FLUSH_FLAGS, *PHV_FLUSH_FLAGS;

#define HV_FLUSH_ALL_PROCESSORS              (0x00000001)
#define HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES  (0x00000002)
#define HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY    (0x00000004)
#define HV_FLUSH_MASK                        (HV_FLUSH_ALL_PROCESSORS | \
                                              HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES | \
                                              HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY)

//
// Address translation flags.
//

#define HV_TRANSLATE_GVA_VALIDATE_READ       (0x0001)
#define HV_TRANSLATE_GVA_VALIDATE_WRITE      (0x0002)
#define HV_TRANSLATE_GVA_VALIDATE_EXECUTE    (0x0004)
#define HV_TRANSLATE_GVA_PRIVILEGE_EXEMPT    (0x0008)
#define HV_TRANSLATE_GVA_SET_PAGE_TABLE_BITS (0x0010)
#define HV_TRANSLATE_GVA_TLB_FLUSH_INHIBIT   (0x0020)
#define HV_TRANSLATE_GVA_CONTROL_MASK        (0x003F)

typedef UINT64 HV_TRANSLATE_GVA_CONTROL_FLAGS, *PHV_TRANSLATE_GVA_CONTROL_FLAGS;

typedef enum _HV_TRANSLATE_GVA_RESULT_CODE
{
    HvTranslateGvaSuccess                 = 0,

    // Translation Failures
    HvTranslateGvaPageNotPresent          = 1,
    HvTranslateGvaPrivilegeViolation      = 2,
    HvTranslateGvaInvalidPageTableFlags   = 3,

    // GPA access failures
    HvTranslateGvaGpaUnmapped             = 4,
    HvTranslateGvaGpaNoReadAccess         = 5,
    HvTranslateGvaGpaNoWriteAccess        = 6,
    HvTranslateGvaGpaIllegalOverlayAccess = 7

} HV_TRANSLATE_GVA_RESULT_CODE, *PHV_TRANSLATE_GVA_RESULT_CODE;

typedef union _HV_TRANSLATE_GVA_RESULT
{
    UINT64 AsUINT64;
    struct
    {
        HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
        UINT32 CacheType : 8;
        UINT32 OverlayPage : 1;
        UINT32 Reserved : 23;
    };
} HV_TRANSLATE_GVA_RESULT, *PHV_TRANSLATE_GVA_RESULT;

//
// Read and write GPA access flags.
//

typedef union _HV_ACCESS_GPA_CONTROL_FLAGS
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 CacheType : 8;  // Cache type for access
        UINT64 Reserved  : 56;
    };
} HV_ACCESS_GPA_CONTROL_FLAGS, *PHV_ACCESS_GPA_CONTROL_FLAGS;

typedef enum _HV_ACCESS_GPA_RESULT_CODE
{
    HvAccessGpaSuccess              = 0,

    // GPA access failures
    HvAccessGpaUnmapped             = 1,
    HvAccessGpaReadIntercept        = 2,
    HvAccessGpaWriteIntercept       = 3,
    HvAccessGpaIllegalOverlayAccess = 4

} HV_ACCESS_GPA_RESULT_CODE, *PHV_ACCESS_GPA_RESULT_CODE;

typedef union _HV_ACCESS_GPA_RESULT
{
    UINT64 AsUINT64;
    struct
    {
        HV_ACCESS_GPA_RESULT_CODE ResultCode;
        UINT32                    Reserved;
    };
} HV_ACCESS_GPA_RESULT, *PHV_ACCESS_GPA_RESULT;

//
// Cache types.
//
typedef enum _HV_CACHE_TYPE
{
    HvCacheTypeX64Uncached       = 0,
    HvCacheTypeX64WriteCombining = 1,
    HvCacheTypeX64WriteThrough   = 4,
    HvCacheTypeX64WriteProtected = 5,
    HvCacheTypeX64WriteBack      = 6
} HV_CACHE_TYPE, *PHV_CACHE_TYPE;

//
// Flags to describe the access a partition has to a GPA page.
//
typedef UINT32 HV_MAP_GPA_FLAGS;

#define HV_MAP_GPA_READABLE	(0x00000001)
#define HV_MAP_GPA_WRITABLE	(0x00000002)
#define HV_MAP_GPA_EXECUTABLE	(0x00000004)

//
// Gva Range
//
// The GVA range is a compressed range of GVA used by the TLB flush
// routines.
//

typedef union _HV_GVA_RANGE
{
    UINT64 AsUINT64;

    struct
    {
        //
        // Additional pages supplies the number of pages beyond one.
        //

        UINT64 AdditionalPages : 12;

        //
        // GvaPageNumber supplies the top 54 most significant bits of the
        // guest virtual address space.
        //

        UINT64 GvaPageNumber   : 52;
    };
} HV_GVA_RANGE, *PHV_GVA_RANGE;


//
// Define index of synthetic interrupt source that receives intercept messages.
//
#define HV_SYNIC_INTERCEPTION_SINT_INDEX ((HV_SYNIC_SINT_INDEX)0)

//
// Define version of the synthetic interrupt controller.
//

#define HV_SYNIC_VERSION        (1)

//
// Define the expected SynIC version.
//
#define HV_SYNIC_VERSION_1 (0x1)

//
// Define synthetic interrupt controller message constants.
//

#define HV_MESSAGE_SIZE                 (256)
#define HV_MESSAGE_PAYLOAD_BYTE_COUNT   (240)
#define HV_MESSAGE_PAYLOAD_QWORD_COUNT  (30)
#define HV_ANY_VP                       (0xFFFFFFFF)

//
// Define synthetic interrupt controller flag constants.
//

#define HV_EVENT_FLAGS_COUNT        (256 * 8)
#define HV_EVENT_FLAGS_BYTE_COUNT   (256)
#define HV_EVENT_FLAGS_DWORD_COUNT  (256 / sizeof(UINT32))

//
// Define lowest permissible vector that can be sent or received by the local
// APIC.
//
#define HV_SYNIC_APIC_MINIMUM_VECTOR    0x10

//
// Define hypervisor message types.
//
typedef enum _HV_MESSAGE_TYPE
{
    HvMessageTypeNone = 0x00000000,

    //
    // Memory access messages.
    //
    HvMessageTypeUnmappedGpa = 0x80000000,
    HvMessageTypeGpaIntercept = 0x80000001,

    //
    // Timer notification messages.
    //
    HvMessageTimerExpired = 0x80000010,

    //
    // Error messages.
    //
    HvMessageTypeInvalidVpRegisterValue = 0x80000020,
    HvMessageTypeUnrecoverableException = 0x80000021,
    HvMessageTypeUnsupportedFeature = 0x80000022,

    //
    // Trace buffer complete messages.
    //
    HvMessageTypeEventLogBufferComplete = 0x80000040,

    //
    // Platform-specific processor intercept messages.
    //
    HvMessageTypeX64IoPortIntercept = 0x80010000,
    HvMessageTypeX64MsrIntercept = 0x80010001,
    HvMessageTypeX64CpuidIntercept = 0x80010002,
    HvMessageTypeX64ExceptionIntercept = 0x80010003,
    HvMessageTypeX64ApicEoi = 0x80010004,
    HvMessageTypeX64LegacyFpError = 0x80010005

} HV_MESSAGE_TYPE, *PHV_MESSAGE_TYPE;


#define HV_MESSAGE_TYPE_HYPERVISOR_MASK (0x80000000)


//
// Define APIC EOI message.
//
typedef struct _HV_X64_APIC_EOI_MESSAGE
{
    UINT32 VpIndex;
    UINT32 InterruptVector;
} HV_X64_APIC_EOI_MESSAGE, *PHV_X64_APIC_EOI_MESSAGE;


//
// Define the number of synthetic interrupt sources.
//

#define HV_SYNIC_SINT_COUNT (16)
#define HV_SYNIC_STIMER_COUNT (4)

//
// Define the synthetic interrupt source index type.
//

typedef UINT32 HV_SYNIC_SINT_INDEX, *PHV_SYNIC_SINT_INDEX;

//
// Define partition identifier type.
//

typedef UINT64 HV_PARTITION_ID, *PHV_PARTITION_ID;

//
// Define invalid partition identifier.
//
#define HV_PARTITION_ID_INVALID ((HV_PARTITION_ID) 0x0)

//
// Define connection identifier type.
//

typedef union _HV_CONNECTION_ID
{
    UINT32 AsUINT32;

    struct
    {
        UINT32 Id:24;
        UINT32 Reserved:8;
    };

} HV_CONNECTION_ID, *PHV_CONNECTION_ID;

//
// Define port identifier type.
//

typedef union _HV_PORT_ID
{
    UINT32 AsUINT32;

    struct
    {
        UINT32 Id:24;
        UINT32 Reserved:8;
    };

} HV_PORT_ID, *PHV_PORT_ID;

//
// Define port type.
//

typedef enum _HV_PORT_TYPE
{
    HvPortTypeMessage   = 1,
    HvPortTypeEvent     = 2,
    HvPortTypeMonitor   = 3
} HV_PORT_TYPE, *PHV_PORT_TYPE;

//
// Define port information structure.
//

typedef struct _HV_PORT_INFO
{
    HV_PORT_TYPE PortType;
    UINT32 Padding;

    union
    {
        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            UINT64 RsvdZ;
        } MessagePortInfo;

        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            UINT16 BaseFlagNumber;
            UINT16 FlagCount;
            UINT32 RsvdZ;
        } EventPortInfo;

        struct
        {
            HV_GPA MonitorAddress;
            UINT64 RsvdZ;
        } MonitorPortInfo;
    };
} HV_PORT_INFO, *PHV_PORT_INFO;

typedef const HV_PORT_INFO *PCHV_PORT_INFO;

typedef struct _HV_CONNECTION_INFO
{
    HV_PORT_TYPE PortType;
    UINT32 Padding;

    union
    {
        struct
        {
            UINT64 RsvdZ;
        } MessageConnectionInfo;

        struct
        {
            UINT64 RsvdZ;
        } EventConnectionInfo;

        struct
        {
            HV_GPA MonitorAddress;
        } MonitorConnectionInfo;
    };
} HV_CONNECTION_INFO, *PHV_CONNECTION_INFO;

typedef const HV_CONNECTION_INFO *PCHV_CONNECTION_INFO;

//
// Define type of port property.
//

typedef UINT64 HV_PORT_PROPERTY, *PHV_PORT_PROPERTY;

//
// Define enumeration of port property codes.
//

typedef enum _HV_PORT_PROPERTY_CODE
{
    HvPortPropertyPostCount = 0x00000000,
    HvPortPropertyPreferredTargetVp = 0x00000001,
} HV_PORT_PROPERTY_CODE, *PHV_PORT_PROPERTY_CODE;


//
// Define synthetic interrupt controller message flags.
//

typedef union _HV_MESSAGE_FLAGS
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 MessagePending:1;
        UINT8 Reserved:7;
    };
} HV_MESSAGE_FLAGS, *PHV_MESSAGE_FLAGS;


//
// Define synthetic interrupt controller message header.
//

typedef struct _HV_MESSAGE_HEADER
{
    HV_MESSAGE_TYPE     MessageType;
    UINT8               PayloadSize;
    HV_MESSAGE_FLAGS    MessageFlags;
    UINT8               Reserved[2];
    union
    {
        HV_PARTITION_ID Sender;
        HV_PORT_ID      Port;
    };

} HV_MESSAGE_HEADER, *PHV_MESSAGE_HEADER;

//
// Define timer message payload structure.
//
typedef struct _HV_TIMER_MESSAGE_PAYLOAD
{
    UINT32          TimerIndex;
    UINT32          Reserved;
    HV_NANO100_TIME ExpirationTime;     // When the timer expired
    HV_NANO100_TIME DeliveryTime;       // When the message was delivered
} HV_TIMER_MESSAGE_PAYLOAD, *PHV_TIMER_MESSAGE_PAYLOAD;

//
// Define synthetic interrupt controller message format.
//

typedef struct _HV_MESSAGE
{
    HV_MESSAGE_HEADER Header;
    union
    {
        UINT64 Payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
        HV_TIMER_MESSAGE_PAYLOAD TimerPayload;
        HV_EVENTLOG_MESSAGE_PAYLOAD TracePayload;
    };
} HV_MESSAGE, *PHV_MESSAGE;

//
// Define the number of message buffers associated with each port.
//

#define HV_PORT_MESSAGE_BUFFER_COUNT (16)

//
// Define the synthetic interrupt message page layout.
//

typedef struct _HV_MESSAGE_PAGE
{
    volatile HV_MESSAGE SintMessage[HV_SYNIC_SINT_COUNT];
} HV_MESSAGE_PAGE, *PHV_MESSAGE_PAGE;


//
// Define the synthetic interrupt controller event flags format.
//

typedef union _HV_SYNIC_EVENT_FLAGS
{
    UINT8 Flags8[HV_EVENT_FLAGS_BYTE_COUNT];
    UINT32 Flags32[HV_EVENT_FLAGS_DWORD_COUNT];
} HV_SYNIC_EVENT_FLAGS, *PHV_SYNIC_EVENT_FLAGS;


//
// Define the synthetic interrupt flags page layout.
//

typedef struct _HV_SYNIC_EVENT_FLAGS_PAGE
{
    volatile HV_SYNIC_EVENT_FLAGS SintEventFlags[HV_SYNIC_SINT_COUNT];
} HV_SYNIC_EVENT_FLAGS_PAGE, *PHV_SYNIC_EVENT_FLAGS_PAGE;


//
// Define SynIC control register.
//
typedef union _HV_SYNIC_SCONTROL
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Enable:1;
        UINT64 ReservedP:63;
    };
} HV_SYNIC_SCONTROL, *PHV_SYNIC_SCONTROL;

//
// Define synthetic interrupt source.
//

typedef union _HV_SYNIC_SINT
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Vector       :8;
        UINT64 ReservedP1   :8;
        UINT64 Masked       :1;
        UINT64 AutoEoi      :1;
        UINT64 ReservedP2   :46;
    };
} HV_SYNIC_SINT, *PHV_SYNIC_SINT;

//
// Define the format of the SIMP register
//

typedef union _HV_SYNIC_SIMP
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 SimpEnabled : 1;
        UINT64 Preserved   : 11;
        UINT64 BaseSimpGpa : 52;
    };
} HV_SYNIC_SIMP, *PHV_SYNIC_SIMP;

//
// Define the format of the SIEFP register
//

typedef union _HV_SYNIC_SIEFP
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 SiefpEnabled : 1;
        UINT64 ReservedP    : 11;
        UINT64 BaseSiefpGpa : 52;
    };
} HV_SYNIC_SIEFP, *PHV_SYNIC_SIEFP;

//
// Define the format of the APIC_ASSIST register
//
typedef union _HV_X64_MSR_APIC_ASSIST_CONTENTS
{
    UINT64 AsUINT64;
    struct
    {
        UINT64 Enable                   : 1;
        UINT64 ReservedP                : 11;
        UINT64 GpaPageNumber            : 52;
    };
} HV_X64_MSR_APIC_ASSIST_CONTENTS, *PHV_X64_MSR_APIC_ASSIST_CONTENTS;

//
// Format of the APIC assist page.
//
#define HV_VIRTUAL_APIC_NO_EOI_REQUIRED 0x0

typedef union _HV_VIRTUAL_APIC_ASSIST
{
    UINT32 ApicFlags;
    struct
    {
        UINT32 NoEOIRequired : 1;
    };
} HV_VIRTUAL_APIC_ASSIST, *PHV_VIRTUAL_APIC_ASSIST;

//
// Define virtual interrupt control structure.
//
typedef union _HV_INTERRUPT_CONTROL
{
    UINT64 AsUINT64;
    struct
    {
        HV_INTERRUPT_TYPE InterruptType;
        UINT32 LevelTriggered:1;
        UINT32 LogicalDestinationMode:1;
        UINT32 Reserved:30;
    };
} HV_INTERRUPT_CONTROL, *PHV_INTERRUPT_CONTROL;


//
// Emulated timer period
//
typedef union _HV_EMULATED_TIMER_PERIOD
{
    UINT64              AsUINT64;
    HV_NANO100_DURATION Period;

} HV_EMULATED_TIMER_PERIOD, *PHV_EMULATED_TIMER_PERIOD;

//
// Periodic Timer route
//
typedef union _HV_EMULATED_TIMER_CONTROL
{
    UINT64  AsUINT64;

    struct
    {
        UINT32  Vector                  :  8;
        UINT32  DeliveryMode            :  3;
        UINT32  LogicalDestinationMode  :  1;
        UINT32  Enabled                 :  1;
        UINT32  Reserved1               : 19;
        UINT32  Reserved2               : 24;
        UINT32  Mda                     :  8;
    };

} HV_EMULATED_TIMER_CONTROL, *PHV_EMULATED_TIMER_CONTROL;

//
// ACPI PM timer
//
typedef union _HV_PM_TIMER_INFO
{
    UINT64  AsUINT64;

    struct
    {
        UINT32  Port                : 16;
        UINT32  Width24             :  1;
        UINT32  Enabled             :  1;
        UINT32  Reserved1           : 14;
        UINT32  Reserved2           : 32;
    };

} HV_PM_TIMER_INFO, *PHV_PM_TIMER_INFO;

//
// Definitions for the monitored notification facility
//

typedef union _HV_MONITOR_TRIGGER_GROUP
{
    UINT64 AsUINT64;

    struct
    {
        UINT32 Pending;
        UINT32 Armed;
    };
    
} HV_MONITOR_TRIGGER_GROUP, *PHV_MONITOR_TRIGGER_GROUP;

typedef struct _HV_MONITOR_PARAMETER
{
    HV_CONNECTION_ID    ConnectionId;
    UINT16              FlagNumber;
    UINT16              RsvdZ;
} HV_MONITOR_PARAMETER, *PHV_MONITOR_PARAMETER;

typedef union _HV_MONITOR_TRIGGER_STATE
{
    UINT32 AsUINT32;
        
    struct
    {
        UINT32 GroupEnable : 4;
        UINT32 RsvdZ       : 28;
    };

} HV_MONITOR_TRIGGER_STATE, *PHV_MONITOR_TRIGGER_STATE;

//
// HV_MONITOR_PAGE Layout
// ------------------------------------------------------
// | 0   | TriggerState (4 bytes) | Rsvd1 (4 bytes)     |
// | 8   | TriggerGroup[0]                              |
// | 10  | TriggerGroup[1]                              |
// | 18  | TriggerGroup[2]                              |
// | 20  | TriggerGroup[3]                              |
// | 28  | Rsvd2[0]                                     |
// | 30  | Rsvd2[1]                                     |
// | 38  | Rsvd2[2]                                     |
// | 40  | NextCheckTime[0][0]    | NextCheckTime[0][1] |
// | ...                                                |
// | 240 | Latency[0][0..3]                             |
// | 340 | Rsvz3[0]                                     |
// | 440 | Parameter[0][0]                              |
// | 448 | Parameter[0][1]                              |
// | ...                                                |
// | 840 | Rsvd4[0]                                     |
// ------------------------------------------------------

typedef struct _HV_MONITOR_PAGE
{
    HV_MONITOR_TRIGGER_STATE TriggerState;
    UINT32                   RsvdZ1;

    HV_MONITOR_TRIGGER_GROUP TriggerGroup[4];
    UINT64                   RsvdZ2[3];

    INT32                    NextCheckTime[4][32];

    UINT16                   Latency[4][32];
    UINT64                   RsvdZ3[32];

    HV_MONITOR_PARAMETER     Parameter[4][32];

    UINT8                    RsvdZ4[1984];

} HV_MONITOR_PAGE, *PHV_MONITOR_PAGE;

typedef volatile HV_MONITOR_PAGE* PVHV_MONITOR_PAGE;


//
// Debug channel identifier
//
typedef UINT16 HV_DEBUG_CHANNEL_IDENTIFIER;

//
// Maximum size of the payload
//
#define HV_DEBUG_MAXIMUM_DATA_SIZE 4088

//
// Debug options for all calls
//
typedef UINT32 HV_DEBUG_OPTIONS;

//
// Options flags for HvPostDebugData
//
#define HV_DEBUG_POST_LOOP                  0x00000001

//
// Options flags for HvRetrieveDebugData
//
#define HV_DEBUG_RETRIEVE_LOOP              0x00000001
#define HV_DEBUG_RETRIEVE_TEST_ACTIVITY     0x00000002

//
// Options flags for HvResetDebugSession
//
#define HV_DEBUG_PURGE_INCOMING_DATA        0x00000001
#define HV_DEBUG_PURGE_OUTGOING_DATA        0x00000002

//
// Mux Protocol Defines
//
#define HV_MUX_PACKET_LEADER            0x11223344

#define HV_MUX_PACKET_TYPE_DATA             0x0001
#define HV_MUX_PACKET_TYPE_BREAKIN          0x0002
#define HV_MUX_PACKET_TYPE_QUERY_CHANNELS   0x0003

#define HV_MUX_PACKET_TYPE_MAXIMUM          HV_MUX_PACKET_TYPE_QUERY_CHANNELS

#pragma pack(1)
typedef struct _HV_MUX_PACKET_HEADER
{
    UINT32 Leader;
    UINT16 Type;
    UINT16 Length;
    UINT32 CRC;
    HV_DEBUG_CHANNEL_IDENTIFIER Channel;
    UINT16 Reserved;

} HV_MUX_PACKET_HEADER, *PHV_MUX_PACKET_HEADER;

//
// Channel data returned in a HV_MUX_PACKET_TYPE_QUERY_CHANNELS
// respone. The channelIds arrays is variable length array
// 

typedef struct 
{
    UINT32 Count;
    HV_DEBUG_CHANNEL_IDENTIFIER ChannelIds[1];

} MUX_CHANNEL_DATA, *PMUX_CHANNEL_DATA;

#pragma pack()

//
// Debug Channel Id
//
#define HV_DEBUG_CHANNEL_ID_HYPERVISOR      0x00000000
#define HV_DEBUG_CHANNEL_ID_ROOT            0x00000001
#define HV_DEBUG_CHANNEL_ID_DEFAULT         0x0000BADA
#define HV_DEBUG_CHANNEL_ID_ASSIGN_START    0x00000002
#define HV_DEBUG_CHANNEL_ID_FW_MAX          0x0000003E

//
// This structure is used to transfer crashdump information between the
// Hypervisor and the HvBoot.sys driver in the root Windows instance at the
// time of a Hypervisor BugCheck.  It is allocated by HvBoot.sys during the
// Hypervisor launch process, and its SPA is handed in to the Hypervisor via
// the loader block.
//

#define HV_CRASHDUMP_AREA_VERSION   2
#define HV_IMAGE_NAME_MAX_LENGTH    32
#define HV_DEFAULT_CRASHDUMP_SPA_PAGES 5

typedef struct _HV_CRASHDUMP_AREA_V1
{
    //
    // Version of the Crashdump Area structure
    //

    UINT32 Version;

    //
    // Flags indicating content validity and other attributes of the
    // Crashdump Area
    //

    union
    {
        UINT32 FlagsAsUINT32;
        struct
        {
            //
            // Indicates the contents of the Crashdump Area are valid
            //

            UINT32  Valid:1;
            UINT32  Reserved:31;

        };

    };

    //
    // Loaded Module Information
    //

    UINT64 HypervisorBase;
    UINT32 SizeOfImage;
    UINT16 ImageNameLength;
    WCHAR ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    //
    // Bugcheck error code fields
    //

    UINT64 BugCheckData[5];
    void  *BugCheckErrorReturnAddress;

    //
    // The root of the page table needed to lookup virtual addresses
    // and the debugger data block. The debugger data block contains
    // all the information necc. for the debugger to interpret the 
    // dump file. Of particular interest within it is the prcb address 
    // that contain the processor state.
    //

    UINT64 PageTableBase;
    UINT64 PfnDataBase;
    UINT64 DebuggerDataBlock;
    UINT32 NumberProcessors;

    //
    // Context of the crashing thread
    //

    UINT32 ProcessorStateOffset;
    UINT32 ProcessorStateSize;

    //
    // The stack of crashing thread.
    // 

    UINT32 CrashStackSize;
    UINT32 CrashStackOffset;
    UINT64 CrashStackAddress;

} HV_CRASHDUMP_AREA_V1, *PHV_CRASHDUMP_AREA_V1;


typedef struct _HV_CRASHDUMP_PROCESSOR_STATE
{
    //
    // Context of the crashing thread.
    //

    UINT32 RegisterStateOffset;
    UINT32 RegisterStateSize;

    //
    // The stack of the crashing thread.
    // 

    UINT32 CrashStackSize;
    UINT32 CrashStackOffset;
    UINT64 CrashStackAddress;

    //
    // Platform specific data.
    //

    UINT32 PlatformStateSize;
    UINT32 PlatformStateOffset;

} HV_CRASHDUMP_PROCESSOR_STATE, *PHV_CRASHDUMP_PROCESSOR_STATE;

//
//  Size of code page to save during a crash.
// 

#define CODE_CHUNK_SIZE     0x200

typedef struct _HV_CRASHDUMP_AREA
{
    //
    // Version of the Crashdump Area structure
    //

    UINT32 Version;

    //
    // Flags indicating content validity and other attributes of the
    // Crashdump Area
    //

    union
    {
        UINT32 FlagsAsUINT32;
        struct
        {
            //
            // Indicates the contents of the Crashdump Area are valid
            //

            UINT32  Valid:1;
            UINT32  Reserved:31;

        };

    };

    //
    // Loaded Module Information.
    //

    UINT64 HypervisorBase;
    UINT32 SizeOfImage;
    UINT32 CheckSum;

    //
    // Partition State.
    // 

    UINT64 CurrentPartition;
    UINT64 PartitionsCreated;
    UINT32 PartitionsRunning;
    UINT64 CompartmentFreePfns;

    UINT16 ImageNameLength;
    WCHAR ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    //
    // Bugcheck error code fields.
    //

    UINT64 BugCheckData[5];
    UINT64 BugCheckErrorReturnAddress;

    //
    // The root of the page table needed to lookup virtual addresses
    // and the debugger data block. The debugger data block contains
    // all the information necc. for the debugger to interpret the 
    // dump file. Of particular interest within it is the prcb address 
    // that contain the processor state.
    //

    UINT64 PageTableBase;
    UINT64 PfnDataBase;
    UINT64 DebuggerDataBlock;
    UINT32 NumberProcessors;
    UINT32 CurrentProcessor;
    
    //
    // Code page data. If we know the source of the fault this
    // will have the in memory copy of the code and its spa.
    //

    UINT64 CodeSpa;
    UINT8 CodeChunk[CODE_CHUNK_SIZE];

    //
    // Processor contexts. This is the offset to a set of
    // HV_CRASHDUMP_PROCESSOR_STATE structs. The crashing processor
    // should always be included.
    // 

    UINT32 ContextCount;
    UINT32 ContextOffset;
    UINT32 ContextSize;

} HV_CRASHDUMP_AREA, *PHV_CRASHDUMP_AREA;




//
// Define virtual processor execution state bitfield.
//
typedef union _HV_X64_VP_EXECUTION_STATE
{
    UINT16 AsUINT16;
    struct
    {
        UINT16 Cpl:2;
        UINT16 Cr0Pe:1;
        UINT16 Cr0Am:1;
        UINT16 EferLma:1;
        UINT16 DebugActive:1;
        UINT16 InterruptionPending:1;
        UINT16 Reserved:9;
    };
} HV_X64_VP_EXECUTION_STATE, *PHV_X64_VP_EXECUTION_STATE;


//
// Define intercept message header structure.
//
typedef struct _HV_X64_INTERCEPT_MESSAGE_HEADER
{
    HV_VP_INDEX VpIndex;
    UINT8 InstructionLength;
    HV_INTERCEPT_ACCESS_TYPE InterceptAccessType;
    HV_X64_VP_EXECUTION_STATE ExecutionState;
    HV_X64_SEGMENT_REGISTER CsSegment;
    UINT64 Rip;
    UINT64 Rflags;
} HV_X64_INTERCEPT_MESSAGE_HEADER, *PHV_X64_INTERCEPT_MESSAGE_HEADER;


//
// Define memory access information structure.
//
typedef union _HV_X64_MEMORY_ACCESS_INFO
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 GvaValid:1;
        UINT8 Reserved:7;
    };
} HV_X64_MEMORY_ACCESS_INFO, *PHV_X64_MEMORY_ACCESS_INFO;


//
// Define IO port access information structure.
//
typedef union _HV_X64_IO_PORT_ACCESS_INFO
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 AccessSize:3;
        UINT8 StringOp:1;
        UINT8 RepPrefix:1;
        UINT8 Reserved:3;
    };
} HV_X64_IO_PORT_ACCESS_INFO, *PHV_X64_IO_PORT_ACCESS_INFO;


//
// Define exception information structure.
//
typedef union _HV_X64_EXCEPTION_INFO
{
    UINT8 AsUINT8;
    struct
    {
        UINT8 ErrorCodeValid:1;
        UINT8 Reserved:7;
    };
} HV_X64_EXCEPTION_INFO, *PHV_X64_EXCEPTION_INFO;


//
// Define memory access message structure. This message structure is used
// for memory intercepts, GPA not present intercepts and SPA access violation
// intercepts.
//
typedef struct _HV_X64_MEMORY_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_CACHE_TYPE CacheType;
    UINT8 InstructionByteCount;
    HV_X64_MEMORY_ACCESS_INFO MemoryAccessInfo;
    UINT16 Reserved1;
    UINT64 GuestVirtualAddress;
    UINT64 GuestPhysicalAddress;
    UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rbx;
    UINT64 Rsp;
    UINT64 Rbp;
    UINT64 Rsi;
    UINT64 Rdi;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;
} HV_X64_MEMORY_INTERCEPT_MESSAGE, *PHV_X64_MEMORY_INTERCEPT_MESSAGE;


//
// Define CPUID intercept message structure.
//
typedef struct _HV_X64_CPUID_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rbx;
    UINT64 DefaultResultRax;
    UINT64 DefaultResultRcx;
    UINT64 DefaultResultRdx;
    UINT64 DefaultResultRbx;
} HV_X64_CPUID_INTERCEPT_MESSAGE, *PHV_X64_CPUID_INTERCEPT_MESSAGE;


//
// Define MSR intercept message structure.
//
typedef struct _HV_X64_MSR_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT32 MsrNumber;
    UINT32 Reserved;
    UINT64 Rdx;
    UINT64 Rax;
} HV_X64_MSR_INTERCEPT_MESSAGE, *PHV_X64_MSR_INTERCEPT_MESSAGE;


//
// Define IO access intercept message structure.
//
typedef struct _HV_X64_IO_PORT_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT16 PortNumber;
    HV_X64_IO_PORT_ACCESS_INFO AccessInfo;
    UINT8 InstructionByteCount;
    UINT32 Reserved;
    UINT64 Rax;
    UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER EsSegment;
    UINT64 Rcx;
    UINT64 Rsi;
    UINT64 Rdi;
} HV_X64_IO_PORT_INTERCEPT_MESSAGE, *PHV_X64_IO_PORT_INTERCEPT_MESSAGE;


//
// Define exception intercept message.
//
typedef struct _HV_X64_EXCEPTION_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    UINT16 ExceptionVector;
    HV_X64_EXCEPTION_INFO ExceptionInfo;
    UINT8 InstructionByteCount;
    UINT32 ErrorCode;
    UINT64 ExceptionParameter;
    UINT64 Reserved;
    UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    UINT64 Rax;
    UINT64 Rcx;
    UINT64 Rdx;
    UINT64 Rbx;
    UINT64 Rsp;
    UINT64 Rbp;
    UINT64 Rsi;
    UINT64 Rdi;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;
} HV_X64_EXCEPTION_INTERCEPT_MESSAGE, *PHV_X64_EXCEPTION_INTERCEPT_MESSAGE;


//
// Define legacy floating point error message.
//
typedef struct _HV_X64_LEGACY_FP_ERROR_MESSAGE
{
    UINT32 VpIndex;
    UINT32 Reserved;
} HV_X64_LEGACY_FP_ERROR_MESSAGE, *PHV_X64_LEGACY_FP_ERROR_MESSAGE;


//
// Define invalid virtual processor register message.
//
typedef struct _HV_X64_INVALID_VP_REGISTER_MESSAGE
{
    UINT32 VpIndex;
    UINT32 Reserved;
} HV_X64_INVALID_VP_REGISTER_MESSAGE, *PHV_X64_INVALID_VP_REGISTER_MESSAGE;


//
// Define virtual processor unrecoverable error message.
//
typedef struct _HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
} HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE, *PHV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE;


//
// Define the unsupported feature codes.
//
typedef enum _HV_X64_UNSUPPORTED_FEATURE_CODE
{
    HvUnsupportedFeatureIntercept = 1,
    HvUnsupportedFeatureTaskSwitchTss = 2
}HV_X64_UNSUPPORTED_FEATURE_CODE, *PHV_X64_UNSUPPORTED_FEATURE_CODE;


//
// Define unsupported feature message.
//
typedef struct _HV_X64_UNSUPPORTED_FEATURE_MESSAGE
{
    UINT32 VpIndex;
    HV_X64_UNSUPPORTED_FEATURE_CODE FeatureCode;
    UINT64 FeatureParameter;
} HV_X64_UNSUPPORTED_FEATURE_MESSAGE, *PHV_X64_UNSUPPORTED_FEATURE_MESSAGE;

//
// Hypercall structures, enumerations, and constants.
// ==================================================
//

//
// Definition of the HvCallGetVpRegisterCode hypercall input
// structure.  This call retrieves the valid Vp register codes.
//

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_REGISTER_CODE
{
    HV_PARTITION_ID PartitionId;
    UINT32          RegisterIndex;
} HV_INPUT_GET_VP_REGISTER_CODE, *PHV_INPUT_GET_VP_REGISTER_CODE;

#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4200)
#pragma warning(default:4214)
#pragma warning(default:4324)
#endif

#endif //_HVGDK_
