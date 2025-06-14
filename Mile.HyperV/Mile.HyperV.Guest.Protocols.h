/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.Guest.Protocols.h
 * PURPOSE:    Definition for Hyper-V Guest Publicized Protocols
 *
 * LICENSE:    The MIT License
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
//   - MsvmPkg\NetvscDxe\nvspprotocol.h
//   - MsvmPkg\NetvscDxe\rndis.h
//   - MsvmPkg\VpcivscDxe\wdm.h
//   - MsvmPkg\VpcivscDxe\VpciProtocol.h
//   - MsvmPkg\VpcivscDxe\PciBars.h
//   - MsvmPkg\Include\Protocol\VmbusFileSystem.h

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
    HV_UINT64 PfnArray[HV_ANYSIZE_ARRAY];
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
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_GUID InterfaceType;
    HV_GUID InterfaceInstance;

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

HV_STATIC_ASSERT(
    sizeof(VMBUS_CHANNEL_OFFER_CHANNEL) <= MAXIMUM_SYNIC_MESSAGE_BYTES);

#define VMBUS_CHANNEL_OFFER_CHANNEL_SIZE_PRE_WIN7 \
    (HV_UINT32)HV_FIELD_OFFSET(VMBUS_CHANNEL_OFFER_CHANNEL, Windows6Offset)

// Rescind Offer parameters
typedef struct _VMBUS_CHANNEL_RESCIND_OFFER
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_RESCIND_OFFER, *PVMBUS_CHANNEL_RESCIND_OFFER;

// Indicates the host-to-guest interrupt for this channel should be sent to the
// redirected VTL and SINT. This has no effect if the server is not using
// redirection.
#define VMBUS_OPEN_FLAG_REDIRECT_INTERRUPT 0x1

// Open Channel parameters
typedef struct _VMBUS_CHANNEL_OPEN_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;

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
    HV_FIELD_OFFSET(VMBUS_CHANNEL_OPEN_CHANNEL, ConnectionId)

// Open Channel Result parameters
typedef struct _VMBUS_CHANNEL_OPEN_RESULT
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
    HV_UINT32 OpenId;
    HV_UINT32 Status;
} VMBUS_CHANNEL_OPEN_RESULT, *PVMBUS_CHANNEL_OPEN_RESULT;

// Close channel parameters;
typedef struct _VMBUS_CHANNEL_CLOSE_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_CLOSE_CHANNEL, *PVMBUS_CHANNEL_CLOSE_CHANNEL;

typedef struct _VMBUS_CHANNEL_MODIFY_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
    // Target VP index for the server-to-client interrupt.
    HV_UINT32 TargetVp;
} VMBUS_CHANNEL_MODIFY_CHANNEL, *PVMBUS_CHANNEL_MODIFY_CHANNEL;

typedef struct _VMBUS_CHANNEL_MODIFY_CHANNEL_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
    NTSTATUS Status;
} VMBUS_CHANNEL_MODIFY_CHANNEL_RESPONSE, *PVMBUS_CHANNEL_MODIFY_CHANNEL_RESPONSE;

// The number of PFNs in a GPADL message is defined by the number of pages that
// would be spanned by ByteCount and ByteOffset. If the implied number of PFNs
// won't fit in this packet, there will be a follow-up packet that contains
// more.
typedef struct _VMBUS_CHANNEL_GPADL_HEADER
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
    HV_UINT16 RangeBufLen;
    HV_UINT16 RangeCount;
    GPA_RANGE Range[HV_ANYSIZE_ARRAY];
} VMBUS_CHANNEL_GPADL_HEADER, *PVMBUS_CHANNEL_GPADL_HEADER;

// This is the followup packet that contains more PFNs.
typedef struct _VMBUS_CHANNEL_GPADL_BODY
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 MessageNumber;
    HV_UINT32 Gpadl;
    HV_UINT64 Pfn[HV_ANYSIZE_ARRAY];
} VMBUS_CHANNEL_GPADL_BODY, *PVMBUS_CHANNEL_GPADL_BODY;

typedef struct _VMBUS_CHANNEL_GPADL_CREATED
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
    HV_UINT32 CreationStatus;
} VMBUS_CHANNEL_GPADL_CREATED, *PVMBUS_CHANNEL_GPADL_CREATED;

typedef struct _VMBUS_CHANNEL_GPADL_TEARDOWN
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
} VMBUS_CHANNEL_GPADL_TEARDOWN, *PVMBUS_CHANNEL_GPADL_TEARDOWN;

typedef struct _VMBUS_CHANNEL_GPADL_TORNDOWN
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 Gpadl;
} VMBUS_CHANNEL_GPADL_TORNDOWN, *PVMBUS_CHANNEL_GPADL_TORNDOWN;

typedef struct _VMBUS_CHANNEL_RELID_RELEASED
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_RELID_RELEASED, *PVMBUS_CHANNEL_RELID_RELEASED;

typedef struct _VMBUS_CHANNEL_INITIATE_CONTACT
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
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
    HV_GUID ClientId;
} VMBUS_CHANNEL_INITIATE_CONTACT, *PVMBUS_CHANNEL_INITIATE_CONTACT;

#define VMBUS_CHANNEL_INITIATE_CONTACT_MIN_SIZE \
    HV_FIELD_OFFSET(VMBUS_CHANNEL_INITIATE_CONTACT, ClientId)

typedef struct _VMBUS_CHANNEL_VERSION_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
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
    HV_FIELD_OFFSET(VMBUS_CHANNEL_VERSION_RESPONSE, SupportedFeatures)

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
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChannelId;
    HV_UINT32 TargetVp;
    HV_UINT32 TargetSint;
    HV_UINT32 RingBufferGpadl;
    HV_UINT32 DownstreamPageOffset;
} VMBUS_CHANNEL_OPEN_RESERVED_CHANNEL, *PVMBUS_CHANNEL_OPEN_RESERVED_CHANNEL;

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChannelId;
    HV_UINT32 TargetVp;
    HV_UINT32 TargetSint;
} VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL, *PVMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL;

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChannelId;
} VMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE, *PVMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE;

typedef struct _VMBUS_CHANNEL_TL_CONNECT_REQUEST
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_GUID EndpointId;
    HV_GUID ServiceId;
    // The SiloId is available with the RS5 vmbus protocol version.
    union
    {
        HV_GUID SiloId;
        HV_UINT8 WindowsRS1Offset;
    };
} VMBUS_CHANNEL_TL_CONNECT_REQUEST, *PVMBUS_CHANNEL_TL_CONNECT_REQUEST;

#define VMBUS_CHANNEL_TL_CONNECT_REQUEST_PRE_RS5_SIZE \
    (HV_UINT32)HV_FIELD_OFFSET(VMBUS_CHANNEL_TL_CONNECT_REQUEST, WindowsRS1Offset)

typedef struct _VMBUS_CHANNEL_TL_CONNECT_RESULT
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_GUID EndpointId;
    HV_GUID ServiceId;
    NTSTATUS Status;
} VMBUS_CHANNEL_TL_CONNECT_RESULT, *PVMBUS_CHANNEL_TL_CONNECT_RESULT;

typedef struct _VMBUS_CHANNEL_MODIFY_CONNECTION
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT64 ParentToChildMonitorPageGpa;
    HV_UINT64 ChildToParentMonitorPageGpa;
} VMBUS_CHANNEL_MODIFY_CONNECTION, *PVMBUS_CHANNEL_MODIFY_CONNECTION;

typedef struct _VMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
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

HV_STATIC_ASSERT(HV_FIELD_OFFSET(VMRCB, FeatureBits) == 64);

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
    VMTRANSFER_PAGE_RANGE Ranges[HV_ANYSIZE_ARRAY];
} VMTRANSFER_PAGE_PACKET_HEADER, *PVMTRANSFER_PAGE_PACKET_HEADER;

// This is the format for a GPA-Direct packet, which contains a set of GPA
// ranges, in addition to commands and/or data.
typedef struct _VMDATA_GPA_DIRECT
{
    VMPACKET_DESCRIPTOR Descriptor;
    HV_UINT32 Reserved;
    HV_UINT32 RangeCount;
    GPA_RANGE Range[HV_ANYSIZE_ARRAY];
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
    GPA_RANGE Range[HV_ANYSIZE_ARRAY];
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
    VMTRANSFER_PAGE_RANGE Range[HV_ANYSIZE_ARRAY];
} VMTRANSFER_PAGE_RANGES, *PVMTRANSFER_PAGE_RANGES;

// *****************************************************************************
// Microsoft Hyper-V Video
//

// {DA0A7802-E377-4AAC-8E77-0558EB1073F8}
const HV_GUID SYNTHVID_CLASS_ID =
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
    HV_UINT8 Data[HV_ANYSIZE_ARRAY];
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
    VIDEO_OUTPUT_SITUATION VideoOutput[HV_ANYSIZE_ARRAY];
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
const HV_GUID HK_CLASS_ID =
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
const HV_GUID VMSCSI_CLASS_ID =
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

HV_STATIC_ASSERT((sizeof(VMSCSI_REQUEST) % 4) == 0);

#define VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_1 \
    HV_FIELD_OFFSET(VMSCSI_REQUEST, Reserve)

HV_STATIC_ASSERT(VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_1 == 0x24);

#define VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_2 \
    HV_FIELD_SIZE_THROUGH(VMSCSI_REQUEST, QueueSortKey)

HV_STATIC_ASSERT(VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_2 == 0x34);

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

HV_STATIC_ASSERT((sizeof(VMSTORAGE_CHANNEL_PROPERTIES) % 4) == 0);

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

HV_STATIC_ASSERT((sizeof(VMSTORAGE_PROTOCOL_VERSION) % 4) == 0);

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

HV_STATIC_ASSERT((sizeof(VMFC_WWN_PACKET) % 4) == 0);

// Used to register or unregister Asynchronous Media Event Notification to the
// client
typedef struct _VSTOR_CLIENT_PROPERTIES
{
    HV_UINT32 AsyncNotifyCapable : 1;
    HV_UINT32 Reserved : 31;
} VSTOR_CLIENT_PROPERTIES, *PVSTOR_CLIENT_PROPERTIES;

HV_STATIC_ASSERT((sizeof(VSTOR_CLIENT_PROPERTIES) % 4) == 0);

typedef struct _VSTOR_ASYNC_REGISTER_PACKET
{
    HV_UINT8 Lun;
    HV_UINT8 Target;
    HV_UINT8 Path;
    // BOOLEAN
    HV_UINT8 Register;
} VSTOR_ASYNC_REGISTER_PACKET, *PVSTOR_ASYNC_REGISTER_PACKET;

HV_STATIC_ASSERT((sizeof(VSTOR_ASYNC_REGISTER_PACKET) % 4) == 0);

// Used to send notifications to StorVsc about media change events
typedef struct _VSTOR_NOTIFICATION_PACKET
{
    HV_UINT8 Lun;
    HV_UINT8 Target;
    HV_UINT8 Path;
    HV_UINT8 Flags;
} VSTOR_NOTIFICATION_PACKET, *PVSTOR_NOTIFICATION_PACKET;

HV_STATIC_ASSERT((sizeof(VSTOR_NOTIFICATION_PACKET) % 4) == 0);

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

HV_STATIC_ASSERT((sizeof(VSTOR_PACKET) % 8) == 0);

#define VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_1 ( \
    HV_FIELD_SIZE_THROUGH(VSTOR_PACKET, Status) \
    + VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_1)

HV_STATIC_ASSERT(VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_1 == 0x30);

#define VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_2 ( \
    HV_FIELD_SIZE_THROUGH(VSTOR_PACKET, Status) \
    + VMSTORAGE_SIZEOF_VMSCSI_REQUEST_REVISION_2)

HV_STATIC_ASSERT(VMSTORAGE_SIZEOF_VSTOR_PACKET_REVISION_2 == 0x40);

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
    HV_GUID ChannelInstanceGUID;

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
const HV_GUID NVSP_CLASS_ID =
{
    0xF8615163,
    0xDF3E,
    0x46C5,
    { 0x91, 0x3F, 0xF2, 0xD2, 0xF9, 0x65, 0xED, 0x0E }
};

#define NVSP_INVALID_PROTOCOL_VERSION ((HV_UINT32)0xFFFFFFFF)

#define NVSP_PROTOCOL_MAJOR(VERSION_) (((VERSION_) >> 16) & 0xFFFF)
#define NVSP_PROTOCOL_MINOR(VERSION_) (((VERSION_)) & 0xFFFF)

#define NVSP_PROTOCOL_VERSION(MAJOR_, MINOR_) \
    ((((MAJOR_) & 0xFFFF) << 16) | (((MINOR_) & 0xFFFF)))

#define NVSP_PROTOCOL_VERSION_1 NVSP_PROTOCOL_VERSION(0, 2)
#define NVSP_PROTOCOL_VERSION_2 NVSP_PROTOCOL_VERSION(3, 2)
#define NVSP_PROTOCOL_VERSION_4 NVSP_PROTOCOL_VERSION(4, 0)
#define NVSP_PROTOCOL_VERSION_5 NVSP_PROTOCOL_VERSION(5, 0)
#define NVSP_PROTOCOL_VERSION_CURRENT NVSP_PROTOCOL_VERSION_5

#define NVSP_PROTOCOL_VERSION_IS_VALID(_Version_) ( \
    (_Version_) == NVSP_PROTOCOL_VERSION_5 || \
    (_Version_) == NVSP_PROTOCOL_VERSION_4 || \
    (_Version_) == NVSP_PROTOCOL_VERSION_2 || \
    (_Version_) == NVSP_PROTOCOL_VERSION_1)

#define NVSP_OPERATIONAL_STATUS_OK ((HV_UINT32)0x00000000)
#define NVSP_OPERATIONAL_STATUS_DEGRADED ((HV_UINT32)0x00000001)
#define NVSP_OPERATIONAL_STATUS_NONRECOVERABLE ((HV_UINT32)0x00000002)
#define NVSP_OPERATIONAL_STATUS_NO_CONTACT ((HV_UINT32)0x00000003)
#define NVSP_OPERATIONAL_STATUS_LOST_COMMUNICATION ((HV_UINT32)0x00000004)

// The maximum number of transfer pages (packets) the VSP will use on on a
// receive
#define NVSP_MAX_PACKETS_PER_RECEIVE 375

// Defines the maximum number of processors that can be used by a single VMQ's
// traffic. We are storing this value here because both the VM and host needs it
// to manage the vRSS indirection table (VM needs it for send and host needs it
// for receive).
#define VMS_SWITCH_RSS_MAX_RSS_PROC_COUNT 16

typedef enum _NVSP_MESSAGE_TYPE
{
    NvspMessageTypeNone = 0,

    // Init Messages

    NvspMessageTypeInit = 1,
    NvspMessageTypeInitComplete = 2,

    NvspVersionMessageStart = 100,

    // Version 1 Messages

    NvspMessage1TypeSendNdisVersion = NvspVersionMessageStart,
    NvspMessage1TypeSendReceiveBuffer,
    NvspMessage1TypeSendReceiveBufferComplete,
    NvspMessage1TypeRevokeReceiveBuffer,
    NvspMessage1TypeSendSendBuffer,
    NvspMessage1TypeSendSendBufferComplete,
    NvspMessage1TypeRevokeSendBuffer,
    NvspMessage1TypeSendRNDISPacket,
    NvspMessage1TypeSendRNDISPacketComplete,
    // The maximum allowed message ID for the v1 protocol.
    NvspMessage1Max = NvspMessage1TypeSendRNDISPacketComplete,

    // Version 2 messages

    NvspMessage2TypeSendChimneyDelegatedBuffer,
    NvspMessage2TypeSendChimneyDelegatedBufferComplete,
    NvspMessage2TypeRevokeChimneyDelegatedBuffer,
    NvspMessage2TypeResumeChimneyRXIndication,
    NvspMessage2TypeTerminateChimney,
    NvspMessage2TypeTerminateChimneyComplete,
    NvspMessage2TypeIndicateChimneyEvent,
    NvspMessage2TypeSendChimneyPacket,
    NvspMessage2TypeSendChimneyPacketComplete,
    NvspMessage2TypePostChimneyRecvRequest,
    NvspMessage2TypePostChimneyRecvRequestComplete,
    NvspMessage2TypeAllocateReceiveBufferDeprecated,
    NvspMessage2TypeAllocateReceiveBufferCompleteDeprecated,
    NvspMessage2TypeFreeReceiveBufferDeprecated,
    NvspMessage2SendVmqRndisPacketDeprecated,
    NvspMessage2SendVmqRndisPacketCompleteDeprecated,
    NvspMessage2TypeSendNdisConfig,
    NvspMessage2TypeAllocateChimneyHandle,
    NvspMessage2TypeAllocateChimneyHandleComplete,
    // The maximum allowed message ID for the v2 protocol.
    NvspMessage2Max = NvspMessage2TypeAllocateChimneyHandleComplete,

    // Version 4 messages

    NvspMessage4TypeSendVFAssociation,
    NvspMessage4TypeSwitchDataPath,
    // Needed so that Win8 RC+ VMs don't AV when running on a Win8 Beta Host
    NvspMessage4TypeUplinkConnectStateDeprecated,
    // The maximum allowed message ID for the v4 protocol.
    NvspMessage4Max = NvspMessage4TypeUplinkConnectStateDeprecated,

    // Version 5 messages

    NvspMessage5TypeOidQueryEx,
    NvspMessage5TypeOidQueryExComplete,
    NvspMessage5TypeSubChannel,
    NvspMessage5TypeSendIndirectionTable,
    // The maximum allowed message ID for the v5 protocol.
    NvspMessage5Max = NvspMessage5TypeSendIndirectionTable
} NVSP_MESSAGE_TYPE, *PNVSP_MESSAGE_TYPE;

#define NVSP_PROTOCOL_VERSION_1_HANDLER_COUNT \
    ((NvspMessage1Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_2_HANDLER_COUNT \
    ((NvspMessage2Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_4_HANDLER_COUNT \
    ((NvspMessage4Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_5_HANDLER_COUNT \
    ((NvspMessage5Max - NvspVersionMessageStart) + 1)

typedef enum _NVSP_STATUS
{
    NvspStatusNone = 0,
    NvspStatusSuccess,
    NvspStatusFailure,
    // was NvspStatusProtocolVersionRangeTooNew,
    NvspStatusDeprecated1,
    // was NvspStatusProtocolVersionRangeTooOld,
    NvspStatusDeprecated2,
    NvspStatusInvalidRndisPacket,
    NvspStatusBusy,
    NvspStatusProtocolVersionUnsupported,
    NvspStatusMax,
} NVSP_STATUS, *PNVSP_STATUS;

#pragma pack(push, 1)

typedef struct _NVSP_MESSAGE_HEADER
{
    // NVSP_MESSAGE_TYPE
    HV_UINT32 MessageType;
} NVSP_MESSAGE_HEADER, *PNVSP_MESSAGE_HEADER;

// The following base NDIS type is referenced by nvspprotocol.h. See
// https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/objectheader/ns-objectheader-ndis_object_header
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_NDIS_OBJECT_HEADER
{
    HV_UINT8 Type;
    HV_UINT8 Revision;
    HV_UINT16 Size;
} HV_NDIS_OBJECT_HEADER, *PHV_NDIS_OBJECT_HEADER;

// Init Messages
// This message is used by the VSC to initialize the channel after the channels
// has been opened. This message should never include anything other then
// versioning (i.e. this message will be the same for ever).
// For ever is a long time.  The values have been redefined in Win7 to indicate
// major and minor protocol version number.
typedef struct _NVSP_MESSAGE_INIT
{
    union
    {
        struct
        {
            HV_UINT16 MinorProtocolVersion;
            HV_UINT16 MajorProtocolVersion;
        };
        // was MinProtocolVersion
        HV_UINT32 ProtocolVersion;
    };
    // was MaxProtocolVersion
    HV_UINT32 ProtocolVersion2;
} NVSP_MESSAGE_INIT, *PNVSP_MESSAGE_INIT;

// This message is used by the VSP to complete the initialization of the
// channel. This message should never include anything other then versioning
// (i.e. this message will be the same for ever).
typedef struct _NVSP_MESSAGE_INIT_COMPLETE
{
    // was NegotiatedProtocolVersion (2) in Win6
    HV_UINT32 Deprecated;
    HV_UINT32 MaximumMdlChainLength;
    // NVSP_STATUS
    HV_UINT32 Status;
} NVSP_MESSAGE_INIT_COMPLETE, *PNVSP_MESSAGE_INIT_COMPLETE;

typedef union _NVSP_MESSAGE_INIT_UBER
{
    NVSP_MESSAGE_INIT Init;
    NVSP_MESSAGE_INIT_COMPLETE InitComplete;
} NVSP_MESSAGE_INIT_UBER;

// Version 1 Messages

// This message is used by the VSC to send the NDIS version to the VSP. The VSP
// can use this information when handling OIDs sent by the VSC.
typedef struct _NVSP_1_MESSAGE_SEND_NDIS_VERSION
{
    HV_UINT32 NdisMajorVersion;
    HV_UINT32 NdisMinorVersion;
} NVSP_1_MESSAGE_SEND_NDIS_VERSION, *PNVSP_1_MESSAGE_SEND_NDIS_VERSION;

// This message is used by the VSC to send a receive buffer to the VSP. The VSP
// can then use the receive buffer to send data to the VSC.
typedef struct _NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER
{
    // GPADL_HANDLE
    HV_UINT32 GpadlHandle;
    HV_UINT16 Id;
} NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER, *PNVSP_1_MESSAGE_SEND_RECEIVE_BUFFER;

typedef struct _NVSP_1_RECEIVE_BUFFER_SECTION
{
    HV_UINT32 Offset;
    HV_UINT32 SubAllocationSize;
    HV_UINT32 NumSubAllocations;
    HV_UINT32 EndOffset;
} NVSP_1_RECEIVE_BUFFER_SECTION, *PNVSP_1_RECEIVE_BUFFER_SECTION;

// This message is used by the VSP to acknowledge a receive buffer send by the
// VSC. This message must be sent by the VSP before the VSP uses the receive
// buffer.
typedef struct _NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE
{
    // NVSP_STATUS
    HV_UINT32 Status;
    HV_UINT32 NumSections;
    // The receive buffer is split into two parts, a large suballocation section
    // and a small suballocation section. These sections are then suballocated
    // by a certain size.
    // For example, the following break up of the receive buffer has 6 large
    // suballocations and 10 small suballocations.
    //
    // |            Large Section          |  |   Small Section   |
    // ------------------------------------------------------------
    // |     |     |     |     |     |     |  | | | | | | | | | | |
    // |                                      |
    // LargeOffset                            SmallOffset
    NVSP_1_RECEIVE_BUFFER_SECTION Sections[HV_ANYSIZE_ARRAY];
} NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE, *PNVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE;

// This message is sent by the VSC to revoke the receive buffer. After the VSP
// completes this transaction, the vsp should never use the receive buffer again.
typedef struct _NVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER
{
    HV_UINT16 Id;
} NVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER, *PNVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER;

// This message is used by the VSC to send a send buffer to the VSP. The VSC can
// then use the send buffer to send data to the VSP.
typedef struct _NVSP_1_MESSAGE_SEND_SEND_BUFFER
{
    // GPADL_HANDLE
    HV_UINT32 GpadlHandle;
    HV_UINT16 Id;
} NVSP_1_MESSAGE_SEND_SEND_BUFFER, *PNVSP_1_MESSAGE_SEND_SEND_BUFFER;

// This message is used by the VSP to acknowledge a send buffer sent by the VSC.
// This message must be sent by the VSP before the VSP uses the sent buffer.
typedef struct _NVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE
{
    // NVSP_STATUS
    HV_UINT32 Status;
    // The VSC gets to choose the size of the send buffer and the VSP gets to
    // choose the sections size of the buffer. This was done to enable dynamic
    // reconfigurations when the cost of GPA-direct buffers decreases.
    HV_UINT32 SectionSize;
} NVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE, *PNVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE;

// This message is sent by the VSC to revoke the send buffer. After the VSP
// completes this transaction, the vsp should never use the send buffer again.
typedef struct _NVSP_1_MESSAGE_REVOKE_SEND_BUFFER
{
    HV_UINT16 Id;
} NVSP_1_MESSAGE_REVOKE_SEND_BUFFER, *PNVSP_1_MESSAGE_REVOKE_SEND_BUFFER;

// This message is used by both the VSP and the VSC to send a RNDIS message to
// the opposite channel endpoint.
typedef struct _NVSP_1_MESSAGE_SEND_RNDIS_PACKET
{
    // This field is specified by RNIDS. They assume there's two different
    // channels of communication. However, the Network VSP only has one.
    // Therefore, the channel travels with the RNDIS packet.
    HV_UINT32 ChannelType;
    // This field is used to send part or all of the data through a send buffer.
    // This values specifies an index into the send buffer. If the index is
    // 0xFFFFFFFF, then the send buffer is not being used and all of the data
    // was sent through other VMBus mechanisms.
    HV_UINT32 SendBufferSectionIndex;
    HV_UINT32 SendBufferSectionSize;
} NVSP_1_MESSAGE_SEND_RNDIS_PACKET, *PNVSP_1_MESSAGE_SEND_RNDIS_PACKET;

// This message is used by both the VSP and the VSC to complete a RNDIS message
// to the opposite channel endpoint. At this point, the initiator of this
// message cannot use any resources associated with the original RNDIS packet.
typedef struct _NVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE
{
    // NVSP_STATUS
    HV_UINT32 Status;
} NVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE, *PNVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE;

// This message is used by the VSC to send the NDIS version to the VSP. The VSP
// can use this information when handling OIDs sent by the VSC.
typedef struct _NVSP_2_NETVSC_CAPABILITIES
{
    union
    {
        HV_UINT64 AsUINT64;
        struct
        {
            HV_UINT64 VMQ : 1;
            HV_UINT64 Chimney : 1;
            HV_UINT64 SRIOV : 1;
            HV_UINT64 Ieee8021q : 1;
            HV_UINT64 CorrelationId : 1;
            HV_UINT64 Teaming : 1;
            HV_UINT64 VirtualSubnetId : 1;
        };
    };
} NVSP_2_NETVSC_CAPABILITIES, *PNVSP_2_NETVSC_CAPABILITIES;

typedef struct _NVSP_2_MESSAGE_SEND_NDIS_CONFIG
{
    HV_UINT32 MTU;
    HV_UINT32 Reserved;
    NVSP_2_NETVSC_CAPABILITIES Capabilities;
} NVSP_2_MESSAGE_SEND_NDIS_CONFIG, *PNVSP_2_MESSAGE_SEND_NDIS_CONFIG;

// This structure is used in defining the buffers in
// NVSP_2_MESSAGE_SEND_VMQ_RNDIS_PACKET structure
typedef struct _NVSP_TRANSFER_PAGE_RANGE
{
    // Specifies the ID of the receive buffer that has the buffer. This ID can
    // be the general receive buffer ID specified in
    // NvspMessage1TypeSendReceiveBuffer or it can be the shared memory receive
    // buffer ID allocated by the VSC and specified in
    // NvspMessage2TypeAllocateReceiveBufferComplete message
    HV_UINT64 TransferPageSetId;
    // Number of bytes
    HV_UINT32 ByteCount;
    // Offset in bytes from the beginning of the buffer
    HV_UINT32 ByteOffset;
} NVSP_TRANSFER_PAGE_RANGE, *PNVSP_TRANSFER_PAGE_RANGE;

// NvspMessage4TypeSendVFAssociation
typedef struct _NVSP_4_MESSAGE_SEND_VF_ASSOCIATION
{
    // Specifies whether VF is allocated for this channel
    // If 1, SerialNumber of the VF is specified.
    // If 0, ignore SerialNumber
    HV_UINT32 VFAllocated;
    // Serial number of the VF to team with
    HV_UINT32 SerialNumber;
} NVSP_4_MESSAGE_SEND_VF_ASSOCIATION, *PNVSP_4_MESSAGE_SEND_VF_ASSOCIATION;

// This enum is used in specifying the active data path in
// NVSP_4_MESSAGE_SWITCH_DATA_PATH structure
typedef enum _NVSP_VM_DATA_PATH
{
    NvspDataPathSynthetic = 0,
    NvspDataPathVF,
    NvspDataPathMax
} NVSP_VM_DATA_PATH, *PNVSP_VM_DATA_PATH;

// NvspMessage4TypeSwitchDataPath
typedef struct _NVSP_4_MESSAGE_SWITCH_DATA_PATH
{
    // Specifies the current data path that is active in the VM
    NVSP_VM_DATA_PATH ActiveDataPath;
} NVSP_4_MESSAGE_SWITCH_DATA_PATH, *PNVSP_4_MESSAGE_SWITCH_DATA_PATH;

// NvspMessage5TypeOidQueryEx
typedef struct _NVSP_5_MESSAGE_OID_QUERY_EX
{
    // Header information for the Query OID
    HV_NDIS_OBJECT_HEADER Header;
    // OID being queried
    // NDIS_OID
    HV_UINT32 Oid;
} NVSP_5_MESSAGE_OID_QUERY_EX, *PNVSP_5_MESSAGE_OID_QUERY_EX;

// NvspMessage5TypeOidQueryExComplete
typedef struct _NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE
{
    // Result of the query.
    // NDIS_STATUS
    HV_UINT32 Status;
    union
    {
        // Bytes written to the buffer if query is successful
        HV_UINT32 BytesWritten;
        // Bytes needed if Status if NDIS_STATUS_BUFFER_TOO_SHORT;
        HV_UINT32 BytesNeeded;
    };
} NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE, *PNVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE;

// This defines the subchannel requests we can send to the host. We don't need
// the deallocate operation here as when the primary channel closes, the
// subchannels will be closed and we are cleaning up them based on their primary
// channel's channel close callback.
typedef enum _NVSP_SUBCHANNEL_OPERATION
{
    NvspSubchannelNone = 0,
    NvspSubchannelAllocate,
    NvspSubchannelMax,
} NVSP_SUBCHANNEL_OPERATION, *PNVSP_SUBCHANNEL_OPERATION;

// NvspMessage5TypeSubChannel

typedef struct _NVSP_5_MESSAGE_SUBCHANNEL_REQUEST
{
    // The subchannel operation
    NVSP_SUBCHANNEL_OPERATION Operation;
    // The number of subchannels to create, if it is a NvspSubchannelAllocate
    // operation.
    HV_UINT32 NumSubChannels;
} NVSP_5_MESSAGE_SUBCHANNEL_REQUEST, *PNVSP_5_MESSAGE_SUBCHANNEL_REQUEST;

typedef struct _NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE
{
    // The status of the subchannel operation in NT STATUS code
    HV_UINT32 Status;
    // The actual number of subchannels allocated.
    HV_UINT32 NumSubChannels;
} NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE, *PNVSP_5_MESSAGE_SUBCHANNEL_COMPLETE;

// NvspMessage5TypeSendIndirectionTable
typedef struct _NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE
{
    // The number of entries in the send indirection table.
    HV_UINT32 TableEntryCount;
    // The offset of the send indireciton table.
    // The send indirection table tells which channel to put the send traffic
    // on. Each entry is a channel number.
    HV_UINT32 TableOffset;
} NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE, *PNVSP_5_MESSAGE_SEND_INDIRECTION_TABLE;

// NVSP Messages

typedef union _NVSP_MESSAGE_1_UBER
{
    NVSP_1_MESSAGE_SEND_NDIS_VERSION SendNdisVersion;
    NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER SendReceiveBuffer;
    NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE SendReceiveBufferComplete;
    NVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER RevokeReceiveBuffer;
    NVSP_1_MESSAGE_SEND_SEND_BUFFER SendSendBuffer;
    NVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE SendSendBufferComplete;
    NVSP_1_MESSAGE_REVOKE_SEND_BUFFER RevokeSendBuffer;
    NVSP_1_MESSAGE_SEND_RNDIS_PACKET SendRNDISPacket;
    NVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE SendRNDISPacketComplete;
} NVSP_1_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_2_UBER
{
    NVSP_2_MESSAGE_SEND_NDIS_CONFIG SendNdisConfig;
} NVSP_2_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_4_UBER
{
    NVSP_4_MESSAGE_SEND_VF_ASSOCIATION VFAssociation;
    NVSP_4_MESSAGE_SWITCH_DATA_PATH SwitchDataPath;
} NVSP_4_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_5_UBER
{
    NVSP_5_MESSAGE_OID_QUERY_EX OidQueryEx;
    NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE OidQueryExComplete;
    NVSP_5_MESSAGE_SUBCHANNEL_REQUEST SubChannelRequest;
    NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE SubChannelRequestComplete;
    NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE SendTable;
} NVSP_5_MESSAGE_UBER;

typedef union _NVSP_ALL_MESSAGES
{
    NVSP_MESSAGE_INIT_UBER InitMessages;
    NVSP_1_MESSAGE_UBER Version1Messages;
    NVSP_2_MESSAGE_UBER Version2Messages;
    NVSP_4_MESSAGE_UBER Version4Messages;
    NVSP_5_MESSAGE_UBER Version5Messages;
} NVSP_ALL_MESSAGES;

// ALL Messages
typedef struct _NVSP_MESSAGE
{
    NVSP_MESSAGE_HEADER Header;
    NVSP_ALL_MESSAGES Messages;
    HV_UINT32 Padding;
} NVSP_MESSAGE, *PNVSP_MESSAGE;

HV_STATIC_ASSERT(sizeof(NVSP_MESSAGE) % 8 == 0);

#pragma pack(pop)

// Basic types

typedef HV_UINT32 RNDIS_REQUEST_ID;
typedef HV_UINT32 RNDIS_HANDLE;
typedef HV_UINT32 RNDIS_STATUS;
typedef HV_UINT32 RNDIS_REQUEST_TYPE;
typedef HV_UINT32 RNDIS_OID;
typedef HV_UINT32 RNDIS_CLASS_ID;
typedef HV_UINT32 RNDIS_MEDIUM;
typedef HV_UINT32 *PRNDIS_REQUEST_ID;
typedef HV_UINT32 *PRNDIS_HANDLE;
typedef HV_UINT32 *PRNDIS_STATUS;
typedef HV_UINT32 *PRNDIS_REQUEST_TYPE;
typedef HV_UINT32 *PRNDIS_OID;
typedef HV_UINT32 *PRNDIS_CLASS_ID;
typedef HV_UINT32 *PRNDIS_MEDIUM;

// Status codes

#define RNDIS_STATUS_SUCCESS ((RNDIS_STATUS)0x00000000L)
#define RNDIS_STATUS_MEDIA_CONNECT ((RNDIS_STATUS)0x4001000BL)
#define RNDIS_STATUS_MEDIA_DISCONNECT ((RNDIS_STATUS)0x4001000CL)
// NDIS Status value for REMOTE_NDIS_INDICATE_STATUS_MSG messages (NDIS_STATUS)
#define NDIS_STATUS_NETWORK_CHANGE ((HV_UINT32)0x40010018L)

// General Objects

#define RNDIS_OID_GEN_CURRENT_PACKET_FILTER 0x0001010E

// 802.3 Objects (Ethernet)

#define RNDIS_OID_802_3_CURRENT_ADDRESS 0x01010102

// Remote NDIS message types

#define REMOTE_NDIS_PACKET_MSG 0x00000001
#define REMOTE_NDIS_INITIALIZE_MSG 0x00000002
#define REMOTE_NDIS_HALT_MSG 0x00000003
#define REMOTE_NDIS_QUERY_MSG 0x00000004
#define REMOTE_NDIS_SET_MSG 0x00000005
#define REMOTE_NDIS_RESET_MSG 0x00000006
#define REMOTE_NDIS_INDICATE_STATUS_MSG 0x00000007
#define REMOTE_NDIS_KEEPALIVE_MSG 0x00000008
#define REMOTE_NDIS_SET_EX_MSG 0x00000009
#define REMOTE_CONDIS_MP_CREATE_VC_MSG 0x00008001
#define REMOTE_CONDIS_MP_DELETE_VC_MSG 0x00008002
#define REMOTE_CONDIS_MP_ACTIVATE_VC_MSG 0x00008005
#define REMOTE_CONDIS_MP_DEACTIVATE_VC_MSG 0x00008006
#define REMOTE_CONDIS_INDICATE_STATUS_MSG 0x00008007

// Remote NDIS message completion types

#define REMOTE_NDIS_INITIALIZE_CMPLT 0x80000002
#define REMOTE_NDIS_QUERY_CMPLT 0x80000004
#define REMOTE_NDIS_SET_CMPLT 0x80000005

// Reserved message type for private communication between lower-layer host
// driver and remote device, if necessary.
#define REMOTE_NDIS_BUS_MSG 0xff000001

// Remote NDIS version numbers

#define RNDIS_MAJOR_VERSION 0x00000001
#define RNDIS_MINOR_VERSION 0x00000000

// NdisInitialize message
typedef struct _RNDIS_INITIALIZE_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    HV_UINT32 MajorVersion;
    HV_UINT32 MinorVersion;
    HV_UINT32 MaxTransferSize;
} RNDIS_INITIALIZE_REQUEST, *PRNDIS_INITIALIZE_REQUEST;

// Response to NdisInitialize
typedef struct _RNDIS_INITIALIZE_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
    HV_UINT32 MajorVersion;
    HV_UINT32 MinorVersion;
    HV_UINT32 DeviceFlags;
    RNDIS_MEDIUM Medium;
    HV_UINT32 MaxPacketsPerMessage;
    HV_UINT32 MaxTransferSize;
    HV_UINT32 PacketAlignmentFactor;
    HV_UINT32 AFListOffset;
    HV_UINT32 AFListSize;
} RNDIS_INITIALIZE_COMPLETE, *PRNDIS_INITIALIZE_COMPLETE;

// NdisHalt message
typedef struct _RNDIS_HALT_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
} RNDIS_HALT_REQUEST, *PRNDIS_HALT_REQUEST;

// NdisQueryRequest message
typedef struct _RNDIS_QUERY_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_OID Oid;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
    RNDIS_HANDLE DeviceVcHandle;
} RNDIS_QUERY_REQUEST, *PRNDIS_QUERY_REQUEST;

// Response to NdisQueryRequest
typedef struct _RNDIS_QUERY_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
} RNDIS_QUERY_COMPLETE, *PRNDIS_QUERY_COMPLETE;

// NdisSetRequest message
typedef struct _RNDIS_SET_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_OID Oid;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
    RNDIS_HANDLE DeviceVcHandle;
} RNDIS_SET_REQUEST, *PRNDIS_SET_REQUEST;

// Response to NdisSetRequest
typedef struct _RNDIS_SET_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
} RNDIS_SET_COMPLETE, *PRNDIS_SET_COMPLETE;

// NdisSetExRequest message
typedef struct _RNDIS_SET_EX_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_OID Oid;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
    RNDIS_HANDLE DeviceVcHandle;
} RNDIS_SET_EX_REQUEST, *PRNDIS_SET_EX_REQUEST;

// Response to NdisSetExRequest
typedef struct _RNDIS_SET_EX_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
} RNDIS_SET_EX_COMPLETE, *PRNDIS_SET_EX_COMPLETE;

// NdisReset message
typedef struct _RNDIS_RESET_REQUEST
{
    HV_UINT32 Reserved;
} RNDIS_RESET_REQUEST, *PRNDIS_RESET_REQUEST;

// Response to NdisReset
typedef struct _RNDIS_RESET_COMPLETE
{
    RNDIS_STATUS Status;
    HV_UINT32 AddressingReset;
} RNDIS_RESET_COMPLETE, *PRNDIS_RESET_COMPLETE;

// NdisMIndicateStatus message
typedef struct _RNDIS_INDICATE_STATUS
{
    RNDIS_STATUS Status;
    HV_UINT32 StatusBufferLength;
    HV_UINT32 StatusBufferOffset;
} RNDIS_INDICATE_STATUS, *PRNDIS_INDICATE_STATUS;

// Diagnostic information passed as the status buffer in RNDIS_INDICATE_STATUS
// messages signifying error conditions.
typedef struct _RNDIS_DIAGNOSTIC_INFO
{
    RNDIS_STATUS DiagStatus;
    HV_UINT32 ErrorOffset;
} RNDIS_DIAGNOSTIC_INFO, *PRNDIS_DIAGNOSTIC_INFO;

// NdisKeepAlive message
typedef struct _RNDIS_KEEPALIVE_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
} RNDIS_KEEPALIVE_REQUEST, *PRNDIS_KEEPALIVE_REQUEST;

// Response to NdisKeepAlive
typedef struct _RNDIS_KEEPALIVE_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
} RNDIS_KEEPALIVE_COMPLETE, *PRNDIS_KEEPALIVE_COMPLETE;

// Data message. All Offset fields contain byte offsets from the beginning of
// the RNDIS_PACKET structure. All Length fields are in bytes. VcHandle is set
// to 0 for connectionless data, otherwise it contains the VC handle.
typedef struct _RNDIS_PACKET
{
    HV_UINT32 DataOffset;
    HV_UINT32 DataLength;
    HV_UINT32 OOBDataOffset;
    HV_UINT32 OOBDataLength;
    HV_UINT32 NumOOBDataElements;
    HV_UINT32 PerPacketInfoOffset;
    HV_UINT32 PerPacketInfoLength;
    RNDIS_HANDLE VcHandle;
    HV_UINT32 Reserved;
} RNDIS_PACKET, *PRNDIS_PACKET;

// Format of Information buffer passed in a SetRequest for the OID
// OID_GEN_RNDIS_CONFIG_PARAMETER.
typedef struct _RNDIS_CONFIG_PARAMETER_INFO
{
    HV_UINT32 ParameterNameOffset;
    HV_UINT32 ParameterNameLength;
    HV_UINT32 ParameterType;
    HV_UINT32 ParameterValueOffset;
    HV_UINT32 ParameterValueLength;
} RNDIS_CONFIG_PARAMETER_INFO, *PRNDIS_CONFIG_PARAMETER_INFO;

// CONDIS Miniport messages for connection oriented devices that do not
// implement a call manager.

// CoNdisMiniportCreateVc message
typedef struct _RCONDIS_MP_CREATE_VC
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_HANDLE NdisVcHandle;
} RCONDIS_MP_CREATE_VC, *PRCONDIS_MP_CREATE_VC;

// Response to CoNdisMiniportCreateVc
typedef struct _RCONDIS_MP_CREATE_VC_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_HANDLE DeviceVcHandle;
    RNDIS_STATUS Status;
} RCONDIS_MP_CREATE_VC_COMPLETE, *PRCONDIS_MP_CREATE_VC_COMPLETE;

// CoNdisMiniportDeleteVc message
typedef struct _RCONDIS_MP_DELETE_VC
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_HANDLE DeviceVcHandle;
} RCONDIS_MP_DELETE_VC, *PRCONDIS_MP_DELETE_VC;

// Response to CoNdisMiniportDeleteVc
typedef struct _RCONDIS_MP_DELETE_VC_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
} RCONDIS_MP_DELETE_VC_COMPLETE, *PRCONDIS_MP_DELETE_VC_COMPLETE;

// CoNdisMiniportQueryRequest message
typedef struct _RCONDIS_MP_QUERY_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_REQUEST_TYPE RequestType;
    RNDIS_OID Oid;
    RNDIS_HANDLE DeviceVcHandle;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
} RCONDIS_MP_QUERY_REQUEST, *PRCONDIS_MP_QUERY_REQUEST;

// CoNdisMiniportSetRequest message
typedef struct _RCONDIS_MP_SET_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_REQUEST_TYPE RequestType;
    RNDIS_OID Oid;
    RNDIS_HANDLE DeviceVcHandle;
    HV_UINT32 InformationBufferLength;
    HV_UINT32 InformationBufferOffset;
} RCONDIS_MP_SET_REQUEST, *PRCONDIS_MP_SET_REQUEST;

// CoNdisIndicateStatus message
typedef struct _RCONDIS_INDICATE_STATUS
{
    RNDIS_HANDLE NdisVcHandle;
    RNDIS_STATUS Status;
    HV_UINT32 StatusBufferLength;
    HV_UINT32 StatusBufferOffset;
} RCONDIS_INDICATE_STATUS, *PRCONDIS_INDICATE_STATUS;

// CONDIS Call/VC parameters

typedef struct _RCONDIS_SPECIFIC_PARAMETERS
{
    HV_UINT32 ParameterType;
    HV_UINT32 ParameterLength;
    HV_UINT32 ParameterOffset;
} RCONDIS_SPECIFIC_PARAMETERS, *PRCONDIS_SPECIFIC_PARAMETERS;

typedef struct _RCONDIS_MEDIA_PARAMETERS
{
    HV_UINT32 Flags;
    HV_UINT32 Reserved1;
    HV_UINT32 Reserved2;
    RCONDIS_SPECIFIC_PARAMETERS MediaSpecific;
} RCONDIS_MEDIA_PARAMETERS, *PRCONDIS_MEDIA_PARAMETERS;

typedef struct _RNDIS_FLOWSPEC
{
    HV_UINT32 TokenRate;
    HV_UINT32 TokenBucketSize;
    HV_UINT32 PeakBandwidth;
    HV_UINT32 Latency;
    HV_UINT32 DelayVariation;
    HV_UINT32 ServiceType;
    HV_UINT32 MaxSduSize;
    HV_UINT32 MinimumPolicedSize;
} RNDIS_FLOWSPEC, *PRNDIS_FLOWSPEC;

typedef struct _RCONDIS_CALL_MANAGER_PARAMETERS
{
    RNDIS_FLOWSPEC Transmit;
    RNDIS_FLOWSPEC Receive;
    RCONDIS_SPECIFIC_PARAMETERS CallMgrSpecific;
} RCONDIS_CALL_MANAGER_PARAMETERS, *PRCONDIS_CALL_MANAGER_PARAMETERS;

// CoNdisMiniportActivateVc message
typedef struct _RCONDIS_MP_ACTIVATE_VC_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    HV_UINT32 Flags;
    RNDIS_HANDLE DeviceVcHandle;
    HV_UINT32 MediaParamsOffset;
    HV_UINT32 MediaParamsLength;
    HV_UINT32 CallMgrParamsOffset;
    HV_UINT32 CallMgrParamsLength;
} RCONDIS_MP_ACTIVATE_VC_REQUEST, *PRCONDIS_MP_ACTIVATE_VC_REQUEST;

// Response to CoNdisMiniportActivateVc
typedef struct _RCONDIS_MP_ACTIVATE_VC_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
} RCONDIS_MP_ACTIVATE_VC_COMPLETE, *PRCONDIS_MP_ACTIVATE_VC_COMPLETE;

// CoNdisMiniportDeactivateVc message
typedef struct _RCONDIS_MP_DEACTIVATE_VC_REQUEST
{
    RNDIS_REQUEST_ID RequestId;
    HV_UINT32 Flags;
    RNDIS_HANDLE DeviceVcHandle;
} RCONDIS_MP_DEACTIVATE_VC_REQUEST, *PRCONDIS_MP_DEACTIVATE_VC_REQUEST;

// Response to CoNdisMiniportDeactivateVc
typedef struct _RCONDIS_MP_DEACTIVATE_VC_COMPLETE
{
    RNDIS_REQUEST_ID RequestId;
    RNDIS_STATUS Status;
} RCONDIS_MP_DEACTIVATE_VC_COMPLETE, *PRCONDIS_MP_DEACTIVATE_VC_COMPLETE;

// union with all of the RNDIS messages
typedef union _RNDIS_MESSAGE_CONTAINER
{
    RNDIS_PACKET Packet;
    RNDIS_INITIALIZE_REQUEST InitializeRequest;
    RNDIS_HALT_REQUEST HaltRequest;
    RNDIS_QUERY_REQUEST QueryRequest;
    RNDIS_SET_REQUEST SetRequest;
    RNDIS_SET_EX_REQUEST SetExRequest;
    RNDIS_RESET_REQUEST ResetRequest;
    RNDIS_KEEPALIVE_REQUEST KeepaliveRequest;
    RNDIS_INDICATE_STATUS IndicateStatus;
    RNDIS_INITIALIZE_COMPLETE InitializeComplete;
    RNDIS_QUERY_COMPLETE QueryComplete;
    RNDIS_SET_COMPLETE SetComplete;
    RNDIS_SET_EX_COMPLETE SetExComplete;
    RNDIS_RESET_COMPLETE ResetComplete;
    RNDIS_KEEPALIVE_COMPLETE KeepaliveComplete;
    RCONDIS_MP_CREATE_VC CoMiniportCreateVc;
    RCONDIS_MP_DELETE_VC CoMiniportDeleteVc;
    RCONDIS_INDICATE_STATUS CoIndicateStatus;
    RCONDIS_MP_ACTIVATE_VC_REQUEST CoMiniportActivateVc;
    RCONDIS_MP_DEACTIVATE_VC_REQUEST CoMiniportDeactivateVc;
    RCONDIS_MP_CREATE_VC_COMPLETE CoMiniportCreateVcComplete;
    RCONDIS_MP_DELETE_VC_COMPLETE CoMiniportDeleteVcComplete;
    RCONDIS_MP_ACTIVATE_VC_COMPLETE CoMiniportActivateVcComplete;
    RCONDIS_MP_DEACTIVATE_VC_COMPLETE CoMiniportDeactivateVcComplete;
} RNDIS_MESSAGE_CONTAINER, *PRNDIS_MESSAGE_CONTAINER;

// Remote NDIS message format
typedef struct _RNDIS_MESSAGE
{
    HV_UINT32 NdisMessageType;
    // Total length of this message, from the beginning of the RNDIS_MESSAGE
    // struct, in bytes.
    HV_UINT32 MessageLength;
    // Actual message
    RNDIS_MESSAGE_CONTAINER Message;
} RNDIS_MESSAGE, *PRNDIS_MESSAGE;

// Handy macros

// get the size of an RNDIS message. Pass in the message type,
// RNDIS_SET_REQUEST, RNDIS_PACKET for example
#define RNDIS_MESSAGE_SIZE(Message) ( \
    sizeof(Message) + (sizeof(RNDIS_MESSAGE) - sizeof(RNDIS_MESSAGE_CONTAINER)))

// *****************************************************************************
// Microsoft Hyper-V Virtual PCI Bus
//

// {44C4F61D-4444-4400-9D52-802E27EDE19F}
const HV_GUID VPCI_CLASS_ID =
{
    0x44C4F61D,
    0x4444,
    0x4400,
    { 0x9D, 0x52, 0x80, 0x2E, 0x27, 0xED, 0xE1, 0x9F }
};

#ifndef _WDMDDK_
#define CmResourceTypeNull 0
#define CmResourceTypeMemory 3

// Define the bit masks exclusive to type CmResourceTypeMemoryLarge.

#define CM_RESOURCE_MEMORY_LARGE_40 0x0200
#define CM_RESOURCE_MEMORY_LARGE_48 0x0400
#define CM_RESOURCE_MEMORY_LARGE_64 0x0800

// Define limits for large memory resources

#define CM_RESOURCE_MEMORY_LARGE_40_MAXLEN 0x000000FFFFFFFF00
#define CM_RESOURCE_MEMORY_LARGE_48_MAXLEN 0x0000FFFFFFFF0000
#define CM_RESOURCE_MEMORY_LARGE_64_MAXLEN 0xFFFFFFFF00000000

// Make sure alignment is made properly by compiler
#pragma pack(4)
typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR
{
    HV_UINT8 Type;
    HV_UINT8 ShareDisposition;
    HV_UINT16 Flags;
    union
    {
        struct
        {
            // PHYSICAL_ADDRESS
            HV_UINT64 Start;
            HV_UINT32 Length;
        } Generic;
        struct
        {
            HV_UINT64 First;
            HV_UINT64 Second;
        } ForSize;
    } u;
} CM_PARTIAL_RESOURCE_DESCRIPTOR, *PCM_PARTIAL_RESOURCE_DESCRIPTOR;
#pragma pack()

HV_STATIC_ASSERT(sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR) == 0x14);

#ifndef _WINNT_
typedef enum _DEVICE_POWER_STATE {
    PowerDeviceUnspecified = 0,
    PowerDeviceD0,
    PowerDeviceD1,
    PowerDeviceD2,
    PowerDeviceD3,
    PowerDeviceMaximum
} DEVICE_POWER_STATE, *PDEVICE_POWER_STATE;
#endif // !_WINNT_

typedef struct _PCI_SLOT_NUMBER
{
    union
    {
        struct
        {
            HV_UINT32 DeviceNumber : 5;
            HV_UINT32 FunctionNumber : 3;
            HV_UINT32 Reserved : 24;
        } bits;
        HV_UINT32 AsULONG;
    } u;
} PCI_SLOT_NUMBER, *PPCI_SLOT_NUMBER;
#endif // !_WDMDDK_

#ifndef ALIGN_VALUE
#define ALIGN_VALUE(Value, Alignment) \
    ((Value) + (((Alignment) - (Value)) & ((Alignment) - 1)))
#endif // !ALIGN_VALUE

#ifndef ALIGN_UP
#define ALIGN_UP(x, y) ALIGN_VALUE((x), sizeof(y))
#endif // !ALIGN_UP

#ifndef PCI_MAX_BAR
#define PCI_MAX_BAR 0x0006
#endif // !PCI_MAX_BAR

typedef struct _VPCI_PNP_ID
{
    HV_UINT16 VendorID;
    HV_UINT16 DeviceID;
    HV_UINT8 RevisionID;
    HV_UINT8 ProgIf;
    HV_UINT8 SubClass;
    HV_UINT8 BaseClass;
    HV_UINT16 SubVendorID;
    HV_UINT16 SubSystemID;
} VPCI_PNP_ID, *PVPCI_PNP_ID;

#define VPCI_PROTOCOL_VERSION_RS1 0x00010002
#define VPCI_PROTOCOL_VERSION_CURRENT VPCI_PROTOCOL_VERSION_RS1

static const HV_UINT32 VscSupportedVersions[] =
{
    VPCI_PROTOCOL_VERSION_RS1
};

// Messages between the Virtual PCI driver and its VSP
typedef enum _VPCI_MESSAGE
{
    VpciMsgBusRelations = 0x42490000,
    VpciMsgQueryBusRelations,
    VpciMsgInvalidateDevice,
    VpciMsgInvalidateBus,
    VpciMsgDevicePowerStateChange,
    VpciMsgCurrentResourceRequirements,
    VpciMsgGetResources,
    VpciMsgFdoD0Entry,
    VpciMsgFdoD0Exit,
    VpciMsgReadBlock,
    VpciMsgWriteBlock,
    VpciMsgEject,
    VpciMsgQueryStop,
    VpciMsgReEnable,
    VpciMsgQueryStopFailed,
    VpciMsgEjectComplete,
    VpciMsgAssignedResources,
    VpciMsgReleaseResources,
    VpciMsgInvalidateBlock,
    VpciMsgQueryProtocolVersion,
    VpciMsgCreateInterruptMessage,
    VpciMsgDeleteInterruptMessage,
    VpciMsgAssignedResources2,
    VpciMsgCreateInterruptMessage2,
    VpciMsgDeleteInterruptMessage2
} VPCI_MESSAGE, *PVPCI_MESSAGE;

typedef struct _VPCI_PACKET_HEADER
{
    HV_UINT32 MessageType;
} VPCI_PACKET_HEADER, *PVPCI_PACKET_HEADER;

typedef struct _VPCI_REPLY_HEADER
{
    HV_UINT32 Status;
} VPCI_REPLY_HEADER, *PVPCI_REPLY_HEADER;

typedef struct _VPCI_DEVICE_DESCRIPTION
{
    VPCI_PNP_ID IDs;
    HV_UINT32 Slot;
    HV_UINT32 SerialNumber;
} VPCI_DEVICE_DESCRIPTION, *PVPCI_DEVICE_DESCRIPTION;

typedef struct _VPCI_QUERY_BUS_RELATIONS
{
    VPCI_PACKET_HEADER Header;
    HV_UINT32 DeviceCount;
    VPCI_DEVICE_DESCRIPTION Devices[HV_ANYSIZE_ARRAY];
} VPCI_QUERY_BUS_RELATIONS, *PVPCI_QUERY_BUS_RELATIONS;

#define VPCI_MAX_DEVICES_PER_BUS 255

#define VPCI_MESSAGE_RESOURCE_2_MAX_CPU_COUNT 32

typedef struct _VPCI_MESSAGE_RESOURCE_2
{
    union
    {
        struct
        {
            HV_UINT16 Reserved;
            HV_UINT16 MessageCount;
            HV_UINT32 DataPayload;
            HV_UINT64 Address;
            HV_UINT16 Reserved2[27];
        } Remapped;
        struct
        {
            HV_UINT8 Vector;
            HV_UINT8 DeliveryMode;
            HV_UINT16 VectorCount;
            HV_UINT16 ProcessorCount;
            HV_UINT16 ProcessorArray[VPCI_MESSAGE_RESOURCE_2_MAX_CPU_COUNT];
        } Descriptor;
    };
} VPCI_MESSAGE_RESOURCE_2, *PVPCI_MESSAGE_RESOURCE_2;

typedef struct _VPCI_QUERY_PROTOCOL_VERSION
{
    VPCI_PACKET_HEADER Header;
    HV_UINT32 ProtocolVersion;
} VPCI_QUERY_PROTOCOL_VERSION, *PVPCI_QUERY_PROTOCOL_VERSION;

typedef struct _VPCI_PROTOCOL_VERSION_REPLY
{
    VPCI_REPLY_HEADER Header;
    HV_UINT32 ProtocolVersion;
} VPCI_PROTOCOL_VERSION_REPLY, *PVPCI_PROTOCOL_VERSION_REPLY;

typedef struct _VPCI_QUERY_RESOURCE_REQUIREMENTS
{
    VPCI_PACKET_HEADER Header;
    PCI_SLOT_NUMBER Slot;
} VPCI_QUERY_RESOURCE_REQUIREMENTS, *PVPCI_QUERY_RESOURCE_REQUIREMENTS;

typedef struct _VPCI_RESOURCE_REQUIREMENTS_REPLY
{
    VPCI_REPLY_HEADER Header;
    HV_UINT32 Bars[PCI_MAX_BAR];
} VPCI_RESOURCE_REQUIREMENTS_REPLY, *PVPCI_RESOURCE_REQUIREMENTS_REPLY;

typedef struct _VPCI_DEVICE_POWER_CHANGE
{
    union
    {
        VPCI_PACKET_HEADER Header;
        VPCI_REPLY_HEADER ReplyHeader;
    };
    PCI_SLOT_NUMBER Slot;
    DEVICE_POWER_STATE TargetState;
} VPCI_DEVICE_POWER_CHANGE, *PVPCI_DEVICE_POWER_CHANGE;

// This message indicates which resources the device is "decoding" within the
// child partition at the moment that it is sent. It is valid for the device to
// be decoding no resources. Mmio resources are configured using Base Address
// Registers which are limited to 6. Unused registers and registers that are
// used at the high part of 64-bit addresses are encoded as CmResourceTypeNull.
// The completion packet uses the same structure to return the translated MSI
// resources.
typedef struct _VPCI_DEVICE_TRANSLATE_2
{
    union
    {
        VPCI_PACKET_HEADER         Header;
        VPCI_REPLY_HEADER          ReplyHeader;
    };
    PCI_SLOT_NUMBER                Slot;
    CM_PARTIAL_RESOURCE_DESCRIPTOR MmioResources[PCI_MAX_BAR];
    HV_UINT32                         MsiResourceCount;
    VPCI_MESSAGE_RESOURCE_2        MsiResources[HV_ANYSIZE_ARRAY];
} VPCI_DEVICE_TRANSLATE_2, *PVPCI_DEVICE_TRANSLATE_2;

// NOTE: This doesn't exist in the windows header. Normally we'd use the the
// same packet as above for the response as it gives us the remapped MSI
// interrupts, but in UEFI we don't care about interrupts. Thus we only care
// about the status, so this is a nice partial packet for that.
typedef struct _VPCI_DEVICE_TRANSLATE_2_REPLY
{
    VPCI_REPLY_HEADER Header;
    PCI_SLOT_NUMBER Slot;
}  VPCI_DEVICE_TRANSLATE_2_REPLY, *PVPCI_DEVICE_TRANSLATE_2_REPLY;

typedef struct _VPCI_FDO_D0_ENTRY
{
    VPCI_PACKET_HEADER Header;
    HV_UINT32 Padding;
    HV_UINT64 MmioStart;
} VPCI_FDO_D0_ENTRY, *PVPCI_FDO_D0_ENTRY;

// NOTE: This doesn't exist in the corresponding windows header. But it's nicer
// to have this way, as this is what the response is.
typedef struct _VPCI_FDO_D0_ENTRY_REPLY
{
    HV_UINT32 NtStatus;
    HV_UINT32 Pad;
} VPCI_FDO_D0_ENTRY_REPLY, *PVPCI_FDO_D0_ENTRY_REPLY;

// Attribute types for BARs. See PCI Local Bus Specification Revision 3.0, section
// 6.2.5.1
typedef struct _PCI_BAR_FORMAT
{
    union
    {
        struct
        {
            HV_UINT32 MemorySpaceIndicator : 1;
            HV_UINT32 MemoryType : 2;
            HV_UINT32 Prefetchable : 1;
            HV_UINT32 Address : 28;
        } Memory;
        struct
        {
            HV_UINT32 IoSpaceIndicator : 1;
            HV_UINT32 Reserved : 1;
            HV_UINT32 Address : 30;
        };
        HV_UINT32 AsUINT32;
    };
} PCI_BAR_FORMAT;

#define PCI_BAR_MEMORY_TYPE_64BIT 0x2

// *****************************************************************************
// Microsoft Hyper-V Virtual Machine Bus File System
//

// {C376C1C3-D276-48D2-90A9-C04748072C60}
const HV_GUID VMBFS_CLASS_ID =
{
    0xC376C1C3,
    0xD276,
    0x48D2,
    { 0x90, 0xA9, 0xC0, 0x47, 0x48, 0x07, 0x2C, 0x60 }
};

#define VMBFS_MAXIMUM_MESSAGE_SIZE 12288
#define VMBFS_MAXIMUM_PAYLOAD_SIZE(_Header_) \
    (VMBFS_MAXIMUM_MESSAGE_SIZE - sizeof(_Header_))

#define VMBFS_MAKE_VERSION(Major, Minor) ((HV_UINT32)((Major) << 16) | (Minor))

#define VMBFS_VERSION_WIN10 VMBFS_MAKE_VERSION(1, 0)

typedef enum _VMBFS_MESSAGE_TYPE
{
    VmbfsMessageTypeInvalid = 0,
    VmbfsMessageTypeVersionRequest,
    VmbfsMessageTypeVersionResponse,
    VmbfsMessageTypeGetFileInfo,
    VmbfsMessageTypeGetFileInfoResponse,
    VmbfsMessageTypeReadFile,
    VmbfsMessageTypeReadFileResponse,
    VmbfsMessageTypeReadFileRdma,
    VmbfsMessageTypeReadFileRdmaResponse,
    VmbfsMessageTypeMax
} VMBFS_MESSAGE_TYPE, *PVMBFS_MESSAGE_TYPE;

#define VMBFS_GET_FILE_INFO_FLAG_DIRECTORY 0x1
#define VMBFS_GET_FILE_INFO_FLAG_RDMA_CAPABLE 0x2

#define VMBFS_GET_FILE_INFO_FLAGS \
    (VMBFS_GET_FILE_INFO_FLAG_DIRECTORY | VMBFS_GET_FILE_INFO_FLAG_RDMA_CAPABLE)

#pragma pack(push)
#pragma pack(1)

typedef struct _VMBFS_MESSAGE_HEADER
{
    VMBFS_MESSAGE_TYPE Type;
    HV_UINT32 Reserved;
} VMBFS_MESSAGE_HEADER, *PVMBFS_MESSAGE_HEADER;

typedef struct _VMBFS_MESSAGE_VERSION_REQUEST
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 RequestedVersion;
} VMBFS_MESSAGE_VERSION_REQUEST, *PVMBFS_MESSAGE_VERSION_REQUEST;

typedef enum _VMBFS_STATUS_VERSION_RESPONSE
{
    VmbfsVersionSupported = 0,
    VmbfsVersionUnsupported = 1
} VMBFS_STATUS_VERSION_RESPONSE, *PVMBFS_STATUS_VERSION_RESPONSE;

typedef struct _VMBFS_MESSAGE_VERSION_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status;
} VMBFS_MESSAGE_VERSION_RESPONSE, *PVMBFS_MESSAGE_VERSION_RESPONSE;

typedef struct _VMBFS_MESSAGE_GET_FILE_INFO
{
    VMBFS_MESSAGE_HEADER Header;
    HV_WCHAR FilePath[HV_ANYSIZE_ARRAY];
} VMBFS_MESSAGE_GET_FILE_INFO, *PVMBFS_MESSAGE_GET_FILE_INFO;

typedef enum _VMBFS_STATUS_FILE_RESPONSE
{
    VmbfsFileSuccess = 0,
    VmbfsFileNotFound = 1,
    VmbfsFileEndOfFile = 2,
    VmbfsFileError = 3
} VMBFS_STATUS_FILE_RESPONSE, *PVMBFS_STATUS_FILE_RESPONSE;

typedef struct _VMBFS_MESSAGE_GET_FILE_INFO_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status;
    HV_UINT32 Flags;
    HV_UINT64 FileSize;
} VMBFS_MESSAGE_GET_FILE_INFO_RESPONSE, *PVMBFS_MESSAGE_GET_FILE_INFO_RESPONSE;

typedef struct _VMBFS_MESSAGE_READ_FILE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 ByteCount;
    HV_UINT64 Offset;
    HV_WCHAR FilePath[HV_ANYSIZE_ARRAY];
} VMBFS_MESSAGE_READ_FILE, *PVMBFS_MESSAGE_READ_FILE;

typedef struct _VMBFS_MESSAGE_READ_FILE_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status;
    HV_UINT8 Payload[HV_ANYSIZE_ARRAY];
} VMBFS_MESSAGE_READ_FILE_RESPONSE, *PVMBFS_MESSAGE_READ_FILE_RESPONSE;

typedef struct _VMBFS_MESSAGE_READ_FILE_RDMA
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Handle;
    HV_UINT32 ByteCount;
    HV_UINT64 FileOffset;
    HV_UINT64 TokenOffset;
    HV_WCHAR FilePath[HV_ANYSIZE_ARRAY];
} VMBFS_MESSAGE_READ_FILE_RDMA, *PVMBFS_MESSAGE_READ_FILE_RDMA;

typedef struct _VMBFS_MESSAGE_READ_FILE_RDMA_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status;
    HV_UINT32 ByteCount;
} VMBFS_MESSAGE_READ_FILE_RDMA_RESPONSE, *PVMBFS_MESSAGE_READ_FILE_RDMA_RESPONSE;

#pragma pack(pop)

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4201) // nameless struct/union
#endif
#endif

#endif // !MILE_HYPERV_GUEST_PROTOCOLS
