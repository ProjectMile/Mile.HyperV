/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.Guest.Protocols.h
 * PURPOSE:   Definition for Hyper-V Guest Publicized Protocols
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

// References
// - Hyper-V Generation 2 Virtual Machine UEFI Firmware
//   - MsvmPkg\MsvmPkg.dec
//   - MsvmPkg\Include\Vmbus\NtStatus.h
//   - MsvmPkg\Include\MsvmBase.h
//   - MsvmPkg\VmbusDxe\VmbusP.h
//   - MsvmPkg\VmbusDxe\ChannelMessages.h
//   - MsvmPkg\Include\Vmbus\VmbusPacketFormat.h
//   - MsvmPkg\VideoDxe\SynthVidProtocol.h
//   - MsvmPkg\VideoDxe\VramSize.h
//   - MsvmPkg\Include\Protocol\SynthKeyProtocol.h
//   - MsvmPkg\StorvscDxe\VstorageProtocol.h

#ifndef MILE_HYPERV_GUEST_PROTOCOLS
#define MILE_HYPERV_GUEST_PROTOCOLS

#include "Mile.HyperV.Guest.Interface.h"

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif
#pragma warning(disable:4201) // nameless struct/union
#endif

#ifndef TRUE
// Boolean true value. Most of cases define this value to be 1, but this form is
// more portable.
#define TRUE ((HV_UINT8)(1==1))
#endif // !TRUE

#ifndef _NTDEF_
typedef long NTSTATUS;
#endif // !_NTDEF_

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif // !NT_SUCCESS

#ifndef STATUS_REVISION_MISMATCH
// Indicates two revision levels are incompatible.
#define STATUS_REVISION_MISMATCH ((NTSTATUS)0xC0000059L)
#endif // !STATUS_REVISION_MISMATCH

#ifndef ANYSIZE_ARRAY
#define ANYSIZE_ARRAY 1
#endif // !ANYSIZE_ARRAY

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
    HV_UINT32 Data1;
    HV_UINT16 Data2;
    HV_UINT16 Data3;
    HV_UINT8 Data4[8];
} GUID;
#endif // !GUID_DEFINED

#ifndef OFFSET_OF
// Macro that returns the byte offset of a field in a data structure.
#define OFFSET_OF(TYPE, Field) ((HV_UINT64)&(((TYPE*)0)->Field))
#endif // !OFFSET_OF

#ifndef FIELD_SIZE
#define FIELD_SIZE(TYPE, Field) (sizeof(((TYPE*)0)->Field))
#endif // !FIELD_SIZE

#ifndef SIZEOF_THROUGH_FIELD
#define SIZEOF_THROUGH_FIELD(TYPE, Field) \
    (OFFSET_OF(TYPE, Field) + FIELD_SIZE(TYPE, Field))
#endif // !SIZEOF_THROUGH_FIELD

//CONTAINS_FIELD usage:
//  if (CONTAINS_FIELD(pBlock, pBlock->cbSize, dwMumble))
//  {
//      // safe to use pBlock->dwMumble
//  }
#ifndef CONTAINS_FIELD
#define CONTAINS_FIELD(Struct, Size, Field) ( \
    (((PHV_UINT8)(&(Struct)->Field)) + sizeof((Struct)->Field)) \
    <= (((PHV_UINT8)(Struct))+(Size)))
#endif // !CONTAINS_FIELD

// *****************************************************************************
// Microsoft Hyper-V Virtual Machine Bus
//

#define MAXIMUM_SYNIC_MESSAGE_BYTES 240
#define MAX_USER_DEFINED_BYTES 120

// This structure defines a range in guest physical space that can be made to
// look virtually contiguous.
typedef struct _GPA_RANGE
{
    HV_UINT32 ByteCount;
    HV_UINT32 ByteOffset;
    HV_UINT64 PfnArray[ANYSIZE_ARRAY];
} GPA_RANGE, *PGPA_RANGE;

#define GPA_RANGE_MAX_PFN_COUNT 0xfffff

#pragma pack(push, 1)

// A revision number of vmbus that is used for ensuring both ends on a partition
// are using compatible versions.
#define VMBUS_MAKE_VERSION(Major, Minor) (((Major) << 16) | (Minor))

#define VMBUS_VERSION_V1 VMBUS_MAKE_VERSION(0, 13)
#define VMBUS_VERSION_WIN7 VMBUS_MAKE_VERSION(1, 1)
#define VMBUS_VERSION_WIN8 VMBUS_MAKE_VERSION(2, 4)
#define VMBUS_VERSION_WIN8_1 VMBUS_MAKE_VERSION(3, 0)
#define VMBUS_VERSION_WIN10 VMBUS_MAKE_VERSION(4, 0)
#define VMBUS_VERSION_WIN10RS3_0 VMBUS_MAKE_VERSION(4, 1)
#define VMBUS_VERSION_WIN10RS3_1 VMBUS_MAKE_VERSION(5, 0)
#define VMBUS_VERSION_WIN10RS4 VMBUS_MAKE_VERSION(5, 1)
#define VMBUS_VERSION_WIN10RS5 VMBUS_MAKE_VERSION(5, 2)
#define VMBUS_VERSION_IRON VMBUS_MAKE_VERSION(5, 3)
#define VMBUS_VERSION_COPPER VMBUS_MAKE_VERSION(6, 0)

#define VMBUS_VERSION_LATEST VMBUS_VERSION_COPPER
#define VMBUS_VERSION_MULTICLIENT VMBUS_VERSION_WIN10RS3_1

// Feature which allows the guest to specify an event flag and connection ID
// when opening a channel. If not used, the event flag defaults to the channel
// ID and the connection ID is specified by the host in the offer channel
// message.
#define VMBUS_FEATURE_FLAG_GUEST_SPECIFIED_SIGNAL_PARAMETERS 0x1

// Indicates the REDIRECT_INTERRUPT flag is supported in the OpenChannel flags.
#define VMBUS_FEATURE_FLAG_CHANNEL_INTERRUPT_REDIRECTION 0x2

// Indicates the ChannelMessageModifyConnection and
// ChannelMessageModifyConnectionResponse messages are supported.
#define VMBUS_FEATURE_FLAG_MODIFY_CONNECTION 0x4

// Feature which allows the guest to specify a GUID when initiating contact.
// The GUID signifies the type of VMBus client that is contacting the host,
// e.g. Windows, Linux, UEFI, minivmbus, etc.
#define VMBUS_FEATURE_FLAG_CLIENT_ID 0x8

// Indicates the CONFIDENTIAL_CHANNEL flag is supported in the OfferChannel
// flags.
// N.B. This flag is only used by paravisors offering VmBus service and is not
//      supported by the root VmBus driver.
#define VMBUS_FEATURE_FLAG_CONFIDENTIAL_CHANNELS 0x10

#define VMBUS_SUPPORTED_FEATURE_FLAGS_COPPER \
    (VMBUS_FEATURE_FLAG_GUEST_SPECIFIED_SIGNAL_PARAMETERS | \
     VMBUS_FEATURE_FLAG_CHANNEL_INTERRUPT_REDIRECTION | \
     VMBUS_FEATURE_FLAG_MODIFY_CONNECTION)

#define VMBUS_SUPPORTED_FEATURE_FLAGS_DILITHIUM \
    (VMBUS_SUPPORTED_FEATURE_FLAGS_COPPER | VMBUS_FEATURE_FLAG_CLIENT_ID)

// Version 1 messages
typedef enum _VMBUS_CHANNEL_MESSAGE_TYPE
{
    ChannelMessageInvalid = 0,
    ChannelMessageOfferChannel = 1,
    ChannelMessageRescindChannelOffer = 2,
    ChannelMessageRequestOffers = 3,
    ChannelMessageAllOffersDelivered = 4,
    ChannelMessageOpenChannel = 5,
    ChannelMessageOpenChannelResult = 6,
    ChannelMessageCloseChannel = 7,
    ChannelMessageGpadlHeader = 8,
    ChannelMessageGpadlBody = 9,
    ChannelMessageGpadlCreated = 10,
    ChannelMessageGpadlTeardown = 11,
    ChannelMessageGpadlTorndown = 12,
    ChannelMessageRelIdReleased = 13,
    ChannelMessageInitiateContact = 14,
    ChannelMessageVersionResponse = 15,
    ChannelMessageUnload = 16,
    ChannelMessageUnloadComplete = 17,
    ChannelMessageOpenReservedChannel = 18,
    ChannelMessageCloseReservedChannel = 19,
    ChannelMessageCloseReservedResponse = 20,
    ChannelMessageTlConnectRequest = 21,
    ChannelMessageModifyChannel = 22,
    ChannelMessageTlConnectRequestResult = 23,
    ChannelMessageModifyChannelResponse = 24,
    ChannelMessageModifyConnection = 25,
    ChannelMessageModifyConnectionResponse = 26,
    ChannelMessageCount
} VMBUS_CHANNEL_MESSAGE_TYPE, *PVMBUS_CHANNEL_MESSAGE_TYPE;

typedef struct _VMBUS_CHANNEL_MESSAGE_HEADER
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
} VMBUS_CHANNEL_MESSAGE_HEADER, *PVMBUS_CHANNEL_MESSAGE_HEADER;

// Offer flags. The flags parameter is 8 bits, and any undefined bits are
// available, since bits that were not defined are masked out when using an
// older protocol version.

#define VMBUS_OFFER_FLAG_ENUMERATE_DEVICE_INTERFACE 0x1
// This flag indicates that the channel is offered by the paravisor, and may
// use encrypted memory for the channel ring buffer.
#define VMBUS_OFFER_FLAG_CONFIDENTIAL_CHANNEL 0x2
#define VMBUS_OFFER_FLAG_NAMED_PIPE_MODE 0x10
#define VMBUS_OFFER_FLAG_TLNPI_PROVIDER 0x2000

#define VMBUS_OFFER_FLAGS_WIN6 ( \
    VMBUS_OFFER_FLAG_ENUMERATE_DEVICE_INTERFACE | \
    VMBUS_OFFER_FLAG_NAMED_PIPE_MODE)

#define VMBUS_OFFER_FLAGS_WIN10 \
    (VMBUS_OFFER_FLAGS_WIN6 | VMBUS_OFFER_FLAG_TLNPI_PROVIDER)

#define VMBUS_VP_INDEX_DISABLE_INTERRUPT ((HV_UINT32)-1)

// Offer Channel parameters
typedef struct _VMBUS_CHANNEL_OFFER_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    GUID InterfaceType;
    GUID InterfaceInstance;

    // These reserved fields may be non-zero before Windows 8.

    HV_UINT64 Reserved;
    HV_UINT64 Reserved2;

    HV_UINT16 Flags;
    HV_UINT16 MmioMegabytes;
    HV_UINT8 UserDefined[MAX_USER_DEFINED_BYTES];
    // Defined in Win8
    HV_UINT16 SubChannelIndex;
    // mmio memory in addition to MmioMegabytes that is optional
    HV_UINT16 MmioMegabytesOptional;
    HV_UINT32 ChildRelId;
    HV_UINT8 MonitorId;
    HV_UINT8 MonitorAllocated : 1;
    HV_UINT8 Reserved4 : 7;
    // The following fields are only available in Windows 7 and later.
    union
    {
        struct
        {
            HV_UINT16 IsDedicatedInterrupt : 1;
            HV_UINT16 Reserved5 : 15;
            HV_UINT32 ConnectionId;
        };
        HV_UINT8 Windows6Offset;
    };
} VMBUS_CHANNEL_OFFER_CHANNEL, *PVMBUS_CHANNEL_OFFER_CHANNEL;

static_assert(
    sizeof(VMBUS_CHANNEL_OFFER_CHANNEL) <= MAXIMUM_SYNIC_MESSAGE_BYTES,
    "Offer message too large");

#define VMBUS_CHANNEL_OFFER_CHANNEL_SIZE_PRE_WIN7 \
    (HV_UINT32)OFFSET_OF(VMBUS_CHANNEL_OFFER_CHANNEL, Windows6Offset)

// Rescind Offer parameters
typedef struct _VMBUS_CHANNEL_RESCIND_OFFER
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_RESCIND_OFFER, *PVMBUS_CHANNEL_RESCIND_OFFER;

// Indicates the host-to-guest interrupt for this channel should be sent to the
// redirected VTL and SINT. This has no effect if the server is not using
// redirection.
#define VMBUS_OPEN_FLAG_REDIRECT_INTERRUPT 0x1

// Open Channel parameters
typedef struct _VMBUS_CHANNEL_OPEN_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER;

    // Identifies the specific VMBus channel that is being opened.
    HV_UINT32 ChildRelId;
    // ID making a particular open request at a channel offer unique.
    HV_UINT32 OpenId;
    // GPADL for the channel's ring buffer.
    HV_UINT32 RingBufferGpadlHandle;
    // Target VP index for the server-to-client interrupt. (>= Win8 only)
    HV_UINT32 TargetVp;
    // The upstream ring buffer begins at offset zero in the memory described
    // by RingBufferGpadlHandle. The downstream ring buffer follows it at this
    // offset (in pages).
    HV_UINT32 DownstreamRingBufferPageOffset;
    // User-specific data to be passed along to the server endpoint.
    HV_UINT8 UserData[MAX_USER_DEFINED_BYTES];

    // Guest-specified signal parameters; valid only if
    // VMBUS_FEATURE_FLAG_GUEST_SPECIFIED_SIGNAL_PARAMETERS is used.

    HV_UINT32 ConnectionId;
    HV_UINT16 EventFlag;

    // Valid only if VMBUS_FEATURE_FLAG_INTERRUPT_REDIRECTION is used.
    HV_UINT16 Flags;
} VMBUS_CHANNEL_OPEN_CHANNEL, *PVMBUS_CHANNEL_OPEN_CHANNEL;

#define VMBUS_CHANNEL_OPEN_CHANNEL_MIN_SIZE \
    OFFSET_OF(VMBUS_CHANNEL_OPEN_CHANNEL, ConnectionId)

// Open Channel Result parameters
typedef struct _VMBUS_CHANNEL_OPEN_RESULT
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
    HV_UINT32 OpenId;
    HV_UINT32 Status;
} VMBUS_CHANNEL_OPEN_RESULT, *PVMBUS_CHANNEL_OPEN_RESULT;

// Close channel parameters;
typedef struct _VMBUS_CHANNEL_CLOSE_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_CLOSE_CHANNEL, *PVMBUS_CHANNEL_CLOSE_CHANNEL;

typedef struct _VMBUS_CHANNEL_MODIFY_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
    // Target VP index for the server-to-client interrupt.
    HV_UINT32 TargetVp;
} VMBUS_CHANNEL_MODIFY_CHANNEL, *PVMBUS_CHANNEL_MODIFY_CHANNEL;

typedef struct _VMBUS_CHANNEL_MODIFY_CHANNEL_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
    NTSTATUS Status;
} VMBUS_CHANNEL_MODIFY_CHANNEL_RESPONSE, *PVMBUS_CHANNEL_MODIFY_CHANNEL_RESPONSE;

// The number of PFNs in a GPADL message is defined by the number of pages that
// would be spanned by ByteCount and ByteOffset. If the implied number of PFNs
// won't fit in this packet, there will be a follow-up packet that contains
// more.
typedef struct _VMBUS_CHANNEL_GPADL_HEADER
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
    HV_UINT16 RangeBufLen;
    HV_UINT16 RangeCount;
    GPA_RANGE Range[ANYSIZE_ARRAY];
} VMBUS_CHANNEL_GPADL_HEADER, *PVMBUS_CHANNEL_GPADL_HEADER;

// This is the followup packet that contains more PFNs.
typedef struct _VMBUS_CHANNEL_GPADL_BODY
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 MessageNumber;
    HV_UINT32 Gpadl;
    HV_UINT64 Pfn[ANYSIZE_ARRAY];
} VMBUS_CHANNEL_GPADL_BODY, *PVMBUS_CHANNEL_GPADL_BODY;

typedef struct _VMBUS_CHANNEL_GPADL_CREATED
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
    HV_UINT32 CreationStatus;
} VMBUS_CHANNEL_GPADL_CREATED, *PVMBUS_CHANNEL_GPADL_CREATED;

typedef struct _VMBUS_CHANNEL_GPADL_TEARDOWN
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
} VMBUS_CHANNEL_GPADL_TEARDOWN, *PVMBUS_CHANNEL_GPADL_TEARDOWN;

typedef struct _VMBUS_CHANNEL_GPADL_TORNDOWN
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 Gpadl;
} VMBUS_CHANNEL_GPADL_TORNDOWN, *PVMBUS_CHANNEL_GPADL_TORNDOWN;

typedef struct _VMBUS_CHANNEL_RELID_RELEASED
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_RELID_RELEASED, *PVMBUS_CHANNEL_RELID_RELEASED;

typedef struct _VMBUS_CHANNEL_INITIATE_CONTACT
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 VMBusVersionRequested;
    HV_UINT32 TargetMessageVp;
    union
    {
        HV_UINT64 InterruptPage;
        struct
        {
            // VMBUS_VERSION_WIN10RS3_1
            HV_UINT8 TargetSint;
            // VMBUS_VERSION_WIN10RS4
            HV_UINT8 TargetVtl;
            HV_UINT8 Reserved[2];
            // VMBUS_VERSION_COPPER
            HV_UINT32 FeatureFlags;
        };
    };
    HV_UINT64 ParentToChildMonitorPageGpa;
    HV_UINT64 ChildToParentMonitorPageGpa;
    // VMBUS_FEATURE_FLAG_CLIENT_ID
    GUID ClientId;
} VMBUS_CHANNEL_INITIATE_CONTACT, *PVMBUS_CHANNEL_INITIATE_CONTACT;

#define VMBUS_CHANNEL_INITIATE_CONTACT_MIN_SIZE \
    OFFSET_OF(VMBUS_CHANNEL_INITIATE_CONTACT, ClientId)

typedef struct _VMBUS_CHANNEL_VERSION_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    // BOOLEAN
    HV_UINT8 VersionSupported;
    HV_UINT8 ConnectionState;
    HV_UINT8 Pad[2];
    union
    {
        HV_UINT32 SelectedVersion;
        HV_UINT32 ConnectionId;
    };
    // Supported features is available with the Copper protocol.
    HV_UINT32 SupportedFeatures;
} VMBUS_CHANNEL_VERSION_RESPONSE, *PVMBUS_CHANNEL_VERSION_RESPONSE;

#define VMBUS_CHANNEL_VERSION_RESPONSE_MIN_SIZE \
    OFFSET_OF(VMBUS_CHANNEL_VERSION_RESPONSE, SupportedFeatures)

// Status codes for the ConnectionState field of VMBUS_CHANNEL_VERSION_RESPONSE.
// N.B. If VersionSupported is FALSE, do not consult this value. If the
// requested version is less than VMBUS_VERSION_WIN8, these values may be
// uninitialized memory, cannot be consulted, and the effective value must be
// assumed to be VmbusChannelConnectionSuccessful.
// All non-zero values should be taken to mean a failure. The specific values
// are merely used to better provide information to the guest about the cause of
// the failure.
enum
{
    VmbusChannelConnectionSuccessful = 0,
    VmbusChannelConnectionFailedLowResources = 1,
    VmbusChannelConnectionFailedUnknownFailure = 2,
};

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_UNLOAD, *PVMBUS_CHANNEL_UNLOAD;

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_UNLOAD_COMPLETE, *PVMBUS_CHANNEL_UNLOAD_COMPLETE;

typedef struct _VMBUS_CHANNEL_OPEN_RESERVED_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChannelId;
    HV_UINT32 TargetVp;
    HV_UINT32 TargetSint;
    HV_UINT32 RingBufferGpadl;
    HV_UINT32 DownstreamPageOffset;
} VMBUS_CHANNEL_OPEN_RESERVED_CHANNEL, *PVMBUS_CHANNEL_OPEN_RESERVED_CHANNEL;

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChannelId;
    HV_UINT32 TargetVp;
    HV_UINT32 TargetSint;
} VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL, *PVMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL;

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT32 ChannelId;
} VMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE, *PVMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE;

typedef struct _VMBUS_CHANNEL_TL_CONNECT_REQUEST
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    GUID EndpointId;
    GUID ServiceId;
    // The SiloId is available with the RS5 vmbus protocol version.
    union
    {
        GUID SiloId;
        HV_UINT8 WindowsRS1Offset;
    };
} VMBUS_CHANNEL_TL_CONNECT_REQUEST, *PVMBUS_CHANNEL_TL_CONNECT_REQUEST;

#define VMBUS_CHANNEL_TL_CONNECT_REQUEST_PRE_RS5_SIZE \
    (HV_UINT32)OFFSET_OF(VMBUS_CHANNEL_TL_CONNECT_REQUEST, WindowsRS1Offset)

typedef struct _VMBUS_CHANNEL_TL_CONNECT_RESULT
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    GUID EndpointId;
    GUID ServiceId;
    NTSTATUS Status;
} VMBUS_CHANNEL_TL_CONNECT_RESULT, *PVMBUS_CHANNEL_TL_CONNECT_RESULT;

typedef struct _VMBUS_CHANNEL_MODIFY_CONNECTION
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    HV_UINT64 ParentToChildMonitorPageGpa;
    HV_UINT64 ChildToParentMonitorPageGpa;
} VMBUS_CHANNEL_MODIFY_CONNECTION, *PVMBUS_CHANNEL_MODIFY_CONNECTION;

typedef struct _VMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER;
    // This accepts the same values as in VMBUS_CHANNEL_VERSION_RESPONSE.
    HV_UINT8 ConnectionState;
} VMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE, *PVMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE;

#pragma pack(pop)

#define VMBUS_MESSAGE_CONNECTION_ID 1
#define VMBUS_MESSAGE_TYPE 1
#define VMBUS_MAX_GPADLS 256
#define VMBUS_MAX_CHANNELS HV_EVENT_FLAGS_COUNT

typedef enum _ENDPOINT_TYPE {
    VmbusServerEndpoint = 0,
    VmbusClientEndpoint,
    VmbusEndpointMaximum
} ENDPOINT_TYPE, *PENDPOINT_TYPE;

#pragma pack(push, 1)

// The VM ring control block is the control region for one direction of an
// endpoint. It is always page aligned.
typedef struct _VMRCB
{
    // Offset in bytes from the ring base
    HV_UINT32 In;
    // Offset in bytes from the ring base
    HV_UINT32 Out;
    // If the receiving endpoint sets this to some non-zero value, the sending
    // endpoint should not send any interrupts.
    HV_UINT32 InterruptMask;
    // If the sending endpoint sets this to a non-zero value, the receiving
    // endpoint should send an interrupt when the free byte count is greater
    // than this value.
    HV_UINT32 PendingSendSize;
    HV_UINT32 Reserved[12];
    union
    {
        struct
        {
            HV_UINT32 SupportsPendingSendSize : 1;
        };
        HV_UINT32 Value;
    } FeatureBits;
} VMRCB, *PVMRCB;

static_assert(OFFSET_OF(VMRCB, FeatureBits) == 64);

typedef struct _VMPACKET_DESCRIPTOR
{
    HV_UINT16 Type;
    HV_UINT16 DataOffset8;
    HV_UINT16 Length8;
    HV_UINT16 Flags;
    HV_UINT64 TransactionId;
} VMPACKET_DESCRIPTOR, *PVMPACKET_DESCRIPTOR;

typedef union _PREVIOUS_PACKET_OFFSET
{
    struct
    {
        HV_UINT32 Reserved;
        HV_UINT32 Offset;
    };
    HV_UINT64 AsUINT64;
} PREVIOUS_PACKET_OFFSET, *PPREVIOUS_PACKET_OFFSET;

typedef struct _VMTRANSFER_PAGE_RANGE
{
    HV_UINT32 ByteCount;
    HV_UINT32 ByteOffset;
} VMTRANSFER_PAGE_RANGE, *PVMTRANSFER_PAGE_RANGE;

typedef struct _VMTRANSFER_PAGE_PACKET_HEADER
{
    VMPACKET_DESCRIPTOR Descriptor;
    HV_UINT16 TransferPageSetId;
    HV_UINT8 SenderOwnsSet;
    HV_UINT8 Reserved;
    HV_UINT32 RangeCount;
    VMTRANSFER_PAGE_RANGE Ranges[ANYSIZE_ARRAY];
} VMTRANSFER_PAGE_PACKET_HEADER, *PVMTRANSFER_PAGE_PACKET_HEADER;

// This is the format for a GPA-Direct packet, which contains a set of GPA
// ranges, in addition to commands and/or data.
typedef struct _VMDATA_GPA_DIRECT
{
    VMPACKET_DESCRIPTOR Descriptor;
    HV_UINT32 Reserved;
    HV_UINT32 RangeCount;
    GPA_RANGE Range[ANYSIZE_ARRAY];
} VMDATA_GPA_DIRECT, *PVMDATA_GPA_DIRECT;

typedef enum _VMPIPE_PROTOCOL_MESSAGE_TYPE
{
    VmPipeMessageInvalid = 0,
    VmPipeMessageData = 1,
    VmPipeMessagePartial = 2,
    VmPipeMessageSetupGpaDirect = 3,
    VmPipeMessageTeardownGpaDirect = 4,
    VmPipeMessageIndicationComplete = 5,
} VMPIPE_PROTOCOL_MESSAGE_TYPE, *PVMPIPE_PROTOCOL_MESSAGE_TYPE;

typedef struct _VMPIPE_PROTOCOL_HEADER
{
    VMPIPE_PROTOCOL_MESSAGE_TYPE PacketType;
    union
    {
        HV_UINT32 DataSize;
        struct
        {
            HV_UINT16 DataSize;
            HV_UINT16 Offset;
        } Partial;
    };
} VMPIPE_PROTOCOL_HEADER, *PVMPIPE_PROTOCOL_HEADER;

typedef struct _VMPIPE_SETUP_GPA_DIRECT_BODY
{
    HV_UINT32 Handle;
    // BOOLEAN
    HV_UINT8 IsWritable;
    HV_UINT32 RangeCount;
    GPA_RANGE Range[ANYSIZE_ARRAY];
} VMPIPE_SETUP_GPA_DIRECT_BODY, *PVMPIPE_SETUP_GPA_DIRECT_BODY;

typedef struct _VMPIPE_TEARDOWN_GPA_DIRECT_BODY
{
    HV_UINT32 Handle;
} VMPIPE_TEARDOWN_GPA_DIRECT_BODY, *PVMPIPE_TEARDOWN_GPA_DIRECT_BODY;

typedef enum _VMBUS_PACKET_TYPE
{
    VmbusPacketTypeInvalid = 0x0,

    // 1 through 5 are reserved.

    VmbusPacketTypeDataInBand = 0x6,
    VmbusPacketTypeDataUsingTransferPages = 0x7,

    // 8 is reserved.

    VmbusPacketTypeDataUsingGpaDirect = 0x9,
    VmbusPacketTypeCancelRequest = 0xa,
    VmbusPacketTypeCompletion = 0xb,
} VMBUS_PACKET_TYPE, *PVMBUS_PACKET_TYPE;

#define VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED 1

#pragma pack(pop)

typedef struct _VMTRANSFER_PAGE_RANGES
{
    struct _VMTRANSFER_PAGE_RANGES* Next;
    HV_UINT32 RangeCount;
    VMTRANSFER_PAGE_RANGE Range[ANYSIZE_ARRAY];
} VMTRANSFER_PAGE_RANGES, *PVMTRANSFER_PAGE_RANGES;

// *****************************************************************************
// Microsoft Hyper-V Video
//

// {DA0A7802-E377-4AAC-8E77-0558EB1073F8}
const GUID SYNTHVID_CONTROL_CLASS_ID =
{
    0xDA0A7802,
    0xE377,
    0x4AAC,
    { 0x8E, 0x77, 0x05, 0x58, 0xEB, 0x10, 0x73, 0xF8 }
};

// Latest version of the SynthVid protocol.
#define SYNTHVID_VERSION_MAJOR 3
#define SYNTHVID_VERSION_MINOR 5

#define SYNTHVID_VERSION_CURRENT \
    ((SYNTHVID_VERSION_MINOR << 16) | (SYNTHVID_VERSION_MAJOR))
#define TRUE_WITH_VERSION_EXCHANGE (TRUE + 1)

#pragma pack(push, 1)

// SynthVid Message Types
typedef enum
{
    SynthvidError = 0,
    SynthvidVersionRequest = 1,
    SynthvidVersionResponse = 2,
    SynthvidVramLocation = 3,
    SynthvidVramLocationAck = 4,
    SynthvidSituationUpdate = 5,
    SynthvidSituationUpdateAck = 6,
    SynthvidPointerPosition = 7,
    SynthvidPointerShape = 8,
    SynthvidFeatureChange = 9,
    SynthvidDirt = 10,
    SynthvidBiosInfoRequest = 11,
    SynthvidBiosInfoResponse = 12,
    SynthvidMax = 13
} SYNTHVID_MESSAGE_TYPE;

// Basic message structures.
typedef struct
{
    // Type of the enclosed message
    SYNTHVID_MESSAGE_TYPE Type;
    // Size of the enclosed message (size of the data payload)
    HV_UINT32 Size;
} SYNTHVID_MESSAGE_HEADER, *PSYNTHVID_MESSAGE_HEADER;

typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    // Enclosed message
    HV_UINT8 Data[ANYSIZE_ARRAY];
} SYNTHVID_MESSAGE, *PSYNTHVID_MESSAGE;

typedef union
{
    struct
    {
        HV_UINT16 MajorVersion;
        HV_UINT16 MinorVersion;
    };
    HV_UINT32 AsDWORD;
} SYNTHVID_VERSION, *PSYNTHVID_VERSION;

// The following messages are listed in order of occurance during startup and
// handshaking.

// VSC to VSP
typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
} SYNTHVID_VERSION_REQUEST_MESSAGE, *PSYNTHVID_VERSION_REQUEST_MESSAGE;

// VSP to VSC
typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
    // BOOLEAN
    HV_UINT8 IsAccepted;
    // 1 in Veridian 1.0
    HV_UINT8 MaxVideoOutputs;
} SYNTHVID_VERSION_RESPONSE_MESSAGE, *PSYNTHVID_VERSION_RESPONSE_MESSAGE;

// VSC to VSP
typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
    // BOOLEAN
    HV_UINT8 IsVramGpaAddressSpecified;
    HV_UINT64 VramGpaAddress;
} SYNTHVID_VRAM_LOCATION_MESSAGE, *PSYNTHVID_VRAM_LOCATION_MESSAGE;

// VSP to VSC
// This is called "acknowledge", but in addition, it indicates to the VSC
// that the new physical address location is backed with a memory block
// that the guest can safely write to, knowing that the writes will actually
// be reflected in the VRAM memory block.
typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
} SYNTHVID_VRAM_LOCATION_ACK_MESSAGE, *PSYNTHVID_VRAM_LOCATION_ACK_MESSAGE;

// These messages are used to communicate "situation updates" or changes in the
// layout of the primary surface.
typedef struct
{
    // BOOLEAN
    HV_UINT8 Active;
    HV_UINT32 PrimarySurfaceVramOffset;
    HV_UINT8 DepthBits;
    HV_UINT32 WidthPixels;
    HV_UINT32 HeightPixels;
    HV_UINT32 PitchBytes;
} VIDEO_OUTPUT_SITUATION, *PVIDEO_OUTPUT_SITUATION;

// VSC to VSP
typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
    // 1 in Veridian 1.0
    HV_UINT8 VideoOutputCount;
    VIDEO_OUTPUT_SITUATION VideoOutput[ANYSIZE_ARRAY];
} SYNTHVID_SITUATION_UPDATE_MESSAGE, *PSYNTHVID_SITUATION_UPDATE_MESSAGE;

// VSP to VSC
typedef struct
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
} SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE, *PSYNTHVID_SITUATION_UPDATE_ACK_MESSAGE;

#pragma pack(pop)

#define DEFAULT_VRAM_SIZE_WIN7 (4 * 1024 * 1024)

// In Win8 the synthetic video device upgraded the color depth capabilty from 16
// to 32 bits per pixel.
#define DEFAULT_VRAM_SIZE_WIN8 (2 * DEFAULT_VRAM_SIZE_WIN7)

// *****************************************************************************
// Microsoft Hyper-V Virtual Keyboard
//

// {F912AD6D-2B17-48EA-BD65-F927A61C7684}
const GUID HK_CONTROL_CLASS_ID =
{
    0xF912AD6D,
    0x2B17,
    0x48EA,
    { 0xBD, 0x65, 0xF9, 0x27, 0xA6, 0x1C, 0x76, 0x84 }
};

#define HK_MAKE_VERSION(Major, Minor) \
    ((HV_UINT32)(Major) << 16 | (HV_UINT32)(Minor))
#define HK_VERSION_WIN8 HK_MAKE_VERSION(1, 0)

typedef enum _HK_MESSAGE_TYPE
{
    HkMessageProtocolRequest = 1,
    HkMessageProtocolResponse = 2,
    HkMessageEvent = 3,
    HkMessageSetLedIndicators = 4,
} HK_MESSAGE_TYPE;

typedef struct _HK_MESSAGE_HEADER
{
    HK_MESSAGE_TYPE MessageType;
} HK_MESSAGE_HEADER, *PHK_MESSAGE_HEADER;

typedef struct _HK_MESSAGE_PROTOCOL_REQUEST
{
    HK_MESSAGE_HEADER Header;
    HV_UINT32 Version;
} HK_MESSAGE_PROTOCOL_REQUEST, *PHK_MESSAGE_PROTOCOL_REQUEST;

typedef struct _HK_MESSAGE_LED_INDICATORS_STATE
{
    HK_MESSAGE_HEADER Header;
    HV_UINT16 LedFlags;
} HK_MESSAGE_LED_INDICATORS_STATE, *PHK_MESSAGE_LED_INDICATORS_STATE;

typedef struct _HK_MESSAGE_PROTOCOL_RESPONSE
{
    HK_MESSAGE_HEADER Header;
    HV_UINT32 Accepted : 1;
    HV_UINT32 Reserved : 31;
} HK_MESSAGE_PROTOCOL_RESPONSE, *PHK_MESSAGE_PROTOCOL_RESPONSE;

typedef struct _HK_MESSAGE_KEYSTROKE
{
    HK_MESSAGE_HEADER Header;
    HV_UINT16 MakeCode;
    HV_UINT32 IsUnicode : 1;
    HV_UINT32 IsBreak : 1;
    HV_UINT32 IsE0 : 1;
    HV_UINT32 IsE1 : 1;
    HV_UINT32 Reserved : 28;
} HK_MESSAGE_KEYSTROKE, *PHK_MESSAGE_KEYSTROKE;

#define HK_MAXIMUM_MESSAGE_SIZE 256

// *****************************************************************************
// Microsoft Hyper-V SCSI Controller
//

// {BA6163D9-04A1-4D29-B605-72E2FFB1DC7F}
const GUID VMSCSI_CONTROL_CLASS_ID =
{
    0xBA6163D9,
    0x04A1,
    0x4D29,
    { 0xB6, 0x05, 0x72, 0xE2, 0xFF, 0xB1, 0xDC, 0x7F }
};

// Public interface to the server

// Protocol versions.

// Major/minor macros.  Minor version is in LSB, meaning that earlier flat
// version numbers will be interpreted as "0.x" (i.e., 1 becomes 0.1).

#define VMSTOR_PROTOCOL_MAJOR(VERSION_) (((VERSION_) >> 8) & 0xff)
#define VMSTOR_PROTOCOL_MINOR(VERSION_) (((VERSION_)) & 0xff)
#define VMSTOR_PROTOCOL_VERSION(MAJOR_, MINOR_) \
    ((((MAJOR_) & 0xff) << 8) | (((MINOR_) & 0xff)))

// Invalid version.
#define VMSTOR_INVALID_PROTOCOL_VERSION -1

// Version history:
//
// V1 (Win2k8 Server)
//   Beta              0.1
//   RC < 2008/1/31    1.0
//   RC > 2008/1/31    2.0
//   Servicing         3.0 (reserved)
// Win7
//   M3                3.0 (deprecated)
//   Beta              4.0
//   Release           4.2
// Win8
//   M3                5.0
//   Beta              5.1
//   RC                5.1 (added multi-channel support flag)
// Win Blue
//   MQ                6.0 (added Asynchronous Notification)

#define VMSTOR_PROTOCOL_VERSION_WIN6 VMSTOR_PROTOCOL_VERSION(2, 0)
#define VMSTOR_PROTOCOL_VERSION_WIN7 VMSTOR_PROTOCOL_VERSION(4, 2)
#define VMSTOR_PROTOCOL_VERSION_WIN8 VMSTOR_PROTOCOL_VERSION(5, 1)
#define VMSTOR_PROTOCOL_VERSION_BLUE VMSTOR_PROTOCOL_VERSION(6, 0)
#define VMSTOR_PROTOCOL_VERSION_CURRENT VMSTOR_PROTOCOL_VERSION_BLUE

// The max transfer length will be published when we offer a vmbus channel.
// Max transfer bytes - this determines the reserved MDL size and how large
// requests can be that the clients will forward.
#define MAX_TRANSFER_LENGTH (8*1024*1024)

// Indicates that the device supports Asynchronous Notifications (AN)
#define VMSTOR_PROPERTY_AN_CAPABLE 0x1

// Packet structure describing virtual storage requests.
typedef enum
{
    VStorOperationCompleteIo = 1,
    VStorOperationRemoveDevice = 2,
    VStorOperationExecuteSRB = 3,
    VStorOperationResetLun = 4,
    VStorOperationResetAdapter = 5,
    VStorOperationResetBus = 6,
    VStorOperationBeginInitialization = 7,
    VStorOperationEndInitialization = 8,
    VStorOperationQueryProtocolVersion = 9,
    VStorOperationQueryProperties = 10,
    VStorOperationEnumerateBus = 11,
    VStorOperationFcHbaData = 12,
    VStorOperationCreateSubChannels = 13,
    VStorOperationEventNotification = 14,
    VStorOperationMaximum = 14,
} VSTOR_PACKET_OPERATION;

// Platform neutral description of a SCSI request

#pragma pack(push, 1)

#define CDB16GENERIC_LENGTH 0x10

#define MAX_DATA_BUFFER_LENGTH_WITH_PADDING 0x14

#define VMSCSI_SENSE_BUFFER_SIZE_REVISION_1 0x12
#define VMSCSI_SENSE_BUFFER_SIZE 0x14

typedef struct _VMSCSI_REQUEST
{
    HV_UINT16 Length;
    HV_UINT8 SrbStatus;
    HV_UINT8 ScsiStatus;
    HV_UINT8 Reserved1;
    HV_UINT8 PathId;
    HV_UINT8 TargetId;
    HV_UINT8 Lun;
    HV_UINT8 CdbLength;
    HV_UINT8 SenseInfoExLength;
    HV_UINT8 DataIn;
    HV_UINT8 Properties;
    HV_UINT32 DataTransferLength;
    union
    {
        HV_UINT8 Cdb[CDB16GENERIC_LENGTH];
        HV_UINT8 SenseDataEx[VMSCSI_SENSE_BUFFER_SIZE];
        HV_UINT8 ReservedArray[MAX_DATA_BUFFER_LENGTH_WITH_PADDING];
    };

    // The following were added in Windows 8

    HV_UINT16 Reserve;
    HV_UINT8 QueueTag;
    HV_UINT8 QueueAction;
    HV_UINT32 SrbFlags;
    HV_UINT32 TimeOutValue;
    HV_UINT32 QueueSortKey;
} VMSCSI_REQUEST, *PVMSCSI_REQUEST;

static_assert((sizeof(VMSCSI_REQUEST) % 4) == 0);

#define VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_1 \
    OFFSET_OF(VMSCSI_REQUEST, Reserve)

static_assert(VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_1 == 0x24);

#define VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_2 \
    SIZEOF_THROUGH_FIELD(VMSCSI_REQUEST, QueueSortKey)

static_assert(VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_2 == 0x34);

// This structure is sent during the intialization phase to get the different
// properties of the channel.
// The reserved properties are not guaranteed to be zero before protocol version
// 5.1.
typedef struct _VMSTORAGE_CHANNEL_PROPERTIES
{
    HV_UINT32 Reserved;
    HV_UINT16 MaximumSubChannelCount;
    HV_UINT16 Reserved2;
    HV_UINT32 Flags;
    HV_UINT32 MaxTransferBytes;
    HV_UINT64 Reserved3;
} VMSTORAGE_CHANNEL_PROPERTIES, *PVMSTORAGE_CHANNEL_PROPERTIES;

// Channel Property Flags

#define STORAGE_CHANNEL_SUPPORTS_MULTI_CHANNEL 0x1

static_assert((sizeof(VMSTORAGE_CHANNEL_PROPERTIES) % 4) == 0);

// This structure is sent as part of the channel offer. It exists for old
// versions of the VSC that used this to determine the IDE channel that matched
// up with the VMBus channel.
// The reserved properties are not guaranteed to be zero.
typedef struct _VMSTORAGE_OFFER_PROPERTIES
{
    HV_UINT16 Reserved;
    HV_UINT8 PathId;
    HV_UINT8 TargetId;
    HV_UINT32 Reserved2;
    HV_UINT32 Flags;
    HV_UINT32 Reserved3[3];
} VMSTORAGE_OFFER_PROPERTIES, *PVMSTORAGE_OFFER_PROPERTIES;

#define STORAGE_OFFER_EMULATED_IDE_FLAG 0x2

// This structure is sent during the storage protocol negotiations.
typedef struct _VMSTORAGE_PROTOCOL_VERSION
{
    // Major (MSW) and minor (LSW) version numbers.
    HV_UINT16 MajorMinor;
    // Windows build number. Purely informative.
    HV_UINT16 Build;
} VMSTORAGE_PROTOCOL_VERSION, *PVMSTORAGE_PROTOCOL_VERSION;

static_assert((sizeof(VMSTORAGE_PROTOCOL_VERSION) % 4) == 0);

// This structure is for fibre channel Wwn Packets.
typedef struct _VMFC_WWN_PACKET
{
    // BOOLEAN
    HV_UINT8 PrimaryWwnActive;
    HV_UINT8 Reserved1;
    HV_UINT16 Reserved2;
    HV_UINT8 PrimaryPortWwn[8];
    HV_UINT8 PrimaryNodeWwn[8];
    HV_UINT8 SecondaryPortWwn[8];
    HV_UINT8 SecondaryNodeWwn[8];
} VMFC_WWN_PACKET, *PVMFC_WWN_PACKET;

static_assert((sizeof(VMFC_WWN_PACKET) % 4) == 0);

// Used to register or unregister Asynchronous Media Event Notification to the
// client
typedef struct _VSTOR_CLIENT_PROPERTIES
{
    HV_UINT32 AsyncNotifyCapable : 1;
    HV_UINT32 Reserved : 31;
} VSTOR_CLIENT_PROPERTIES, *PVSTOR_CLIENT_PROPERTIES;

static_assert((sizeof(VSTOR_CLIENT_PROPERTIES) % 4) == 0);

typedef struct _VSTOR_ASYNC_REGISTER_PACKET
{
    HV_UINT8 Lun;
    HV_UINT8 Target;
    HV_UINT8 Path;
    // BOOLEAN
    HV_UINT8 Register;
} VSTOR_ASYNC_REGISTER_PACKET, *PVSTOR_ASYNC_REGISTER_PACKET;

static_assert((sizeof(VSTOR_ASYNC_REGISTER_PACKET) % 4) == 0);

// Used to send notifications to StorVsc about media change events
typedef struct _VSTOR_NOTIFICATION_PACKET
{
    HV_UINT8 Lun;
    HV_UINT8 Target;
    HV_UINT8 Path;
    HV_UINT8 Flags;
} VSTOR_NOTIFICATION_PACKET, *PVSTOR_NOTIFICATION_PACKET;

static_assert((sizeof(VSTOR_NOTIFICATION_PACKET) % 4) == 0);

typedef struct _VSTOR_PACKET
{
    // Requested operation type
    VSTOR_PACKET_OPERATION Operation;
    // Flags - see below for values
    HV_UINT32 Flags;
    // Status of the request returned from the server side.
    HV_UINT32 Status;
    // Data payload area
    union
    {
        // Structure used to forward SCSI commands from the client to the
        // server. (0x34 bytes)
        VMSCSI_REQUEST VmSrb;
        // Structure used to query channel properties.
        VMSTORAGE_CHANNEL_PROPERTIES StorageChannelProperties;
        // Used during version negotiations.
        VMSTORAGE_PROTOCOL_VERSION Version;
        // Used for fibre Channel address packet.
        VMFC_WWN_PACKET FcWwnPacket;
        // Number of subchannels to create via VStorOperationCreateSubChannel.
        HV_UINT16 SubChannelCount;

        // Used to perform Asynchronous Event Notifications

        VSTOR_CLIENT_PROPERTIES ClientProperties;
        VSTOR_NOTIFICATION_PACKET NotificationPacket;

        // Buffer. The buffer size will be the maximun of union members. It is
        // used to transfer data.
        HV_UINT8 Buffer[0x34];
    };
} VSTOR_PACKET, *PVSTOR_PACKET;

static_assert((sizeof(VSTOR_PACKET) % 8) == 0);

#define VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_1 ( \
    SIZEOF_THROUGH_FIELD(VSTOR_PACKET, Status) \
    + VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_1)

static_assert(VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_1 == 0x30);

#define VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_2 ( \
    SIZEOF_THROUGH_FIELD(VSTOR_PACKET, Status) \
    + VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_2)

static_assert(VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_2 == 0x40);

// Packet flags

// This flag indicates that the server should send back a completion for this
// packet.
#define REQUEST_COMPLETION_FLAG 0x1

// This is the set of flags that the VSC can set in any packets it sends
#define VSC_LEGAL_FLAGS (REQUEST_COMPLETION_FLAG)

#pragma pack(pop)

typedef struct _ADAPTER_ADDRESS
{
    HV_UINT64 PartitionId;
    GUID ChannelInstanceGUID;

    // SCSI address

    HV_UINT8 Reserved;
    HV_UINT8 PathId;
    HV_UINT8 TargetId;
    HV_UINT8 Lun;

    // Flags

    HV_UINT32 Flags;

    // World wide names for SynthFc

    // BOOLEAN
    HV_UINT8 PrimaryWwnActive;
    HV_UINT8 PrimaryPortWwn[8];
    HV_UINT8 PrimaryNodeWwn[8];
    HV_UINT8 SecondaryPortWwn[8];
    HV_UINT8 SecondaryNodeWwn[8];
} ADAPTER_ADDRESS, *PADAPTER_ADDRESS;

// Flags for ADAPTER_ADDRESS

#define ADAPTER_ADDRESS_EMULATED_DEVICE 0x1
#define ADAPTER_ADDRESS_SYNTHFC_DEVICE 0x2

// Alignment information
#define VSTORAGE_ALIGNMENT_MASK 0x01

// *****************************************************************************
// Microsoft Hyper-V Network Adapter
//

// {F8615163-DF3E-46C5-913F-F2D2F965ED0E}
const GUID NVSP_CONTROL_CLASS_ID =
{
    0xF8615163,
    0xDF3E,
    0x46C5,
    { 0x91, 0x3F, 0xF2, 0xD2, 0xF9, 0x65, 0xED, 0x0E }
};

// *****************************************************************************
// Microsoft Hyper-V Virtual PCI Bus
//

// {44C4F61D-4444-4400-9D52-802E27EDE19F}
const GUID VPCI_CONTROL_CLASS_ID =
{
    0x44C4F61D,
    0x4444,
    0x4400,
    { 0x9D, 0x52, 0x80, 0x2E, 0x27, 0xED, 0xE1, 0x9F }
};

// *****************************************************************************
// Microsoft Hyper-V Virtual Machine Bus File System
//

// {C376C1C3-D276-48D2-90A9-C04748072C60}
const GUID VMBFS_CONTROL_CLASS_ID =
{
    0xC376C1C3,
    0xD276,
    0x48D2,
    { 0x90, 0xA9, 0xC0, 0x47, 0x48, 0x07, 0x2C, 0x60 }
};

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4201) // nameless struct/union
#endif
#endif

#endif // !MILE_HYPERV_GUEST_PROTOCOLS
