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
// - OpenVMM
//   - vm\devices\vmbus\vmbfs\src\protocol.rs
//   - vm\devices\vmbus\vmbus_ring\src\lib.rs
//   - vm\devices\vmbus\vmbus_core\src\protocol.rs
//   - vm\devices\hyperv_ic_protocol\src\lib.rs
//   - vm\devices\hyperv_ic_protocol\src\heartbeat.rs
//   - vm\devices\hyperv_ic_protocol\src\kvp.rs
//   - vm\devices\hyperv_ic_protocol\src\shutdown.rs
//   - vm\devices\hyperv_ic_protocol\src\timesync.rs
//   - vm\devices\hyperv_ic_protocol\src\vss.rs
//   - vm\devices\uidevices\src\video\protocol.rs
//   - vm\devices\uidevices\src\keyboard\protocol.rs
//   - vm\devices\uidevices\src\mouse\protocol.rs
//   - vm\devices\storage\storvsp_protocol\src\lib.rs
//   - vm\devices\net\netvsp\src\protocol.rs
//   - vm\devices\net\netvsp\src\rndisprot.rs
// - Symbols in Windows version 10.0.14347.0's icsvc.dll
// - Symbols in Windows version 10.0.14347.0's icsvcext.dll
// - Symbols in Windows version 10.0.14347.0's HyperVideo.sys
// - Symbols in Windows version 10.0.14347.0's VMBusHID.sys
// - Symbols in Windows version 10.0.14347.0's netvsc.sys

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
#pragma warning(disable:4200) // zero length array
#pragma warning(disable:4201) // nameless struct/union
#endif

#ifndef TRUE
// Boolean true value. Most of cases define this value to be 1, but this form is
// more portable.
#define TRUE ((HV_UINT8)(1==1))
#endif // !TRUE

#ifndef _NTDEF_
#ifdef _WIN32
typedef long NTSTATUS;
#else
typedef HV_INT32 NTSTATUS;
#endif
#endif // !_NTDEF_

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif // !NT_SUCCESS

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif // !STATUS_SUCCESS

#ifndef STATUS_PENDING
// The operation that was requested is pending completion.
#define STATUS_PENDING ((NTSTATUS)0x00000103L)
#endif // !STATUS_PENDING

#ifndef STATUS_BUFFER_OVERFLOW
// The data was too large to fit into the specified buffer.
#define STATUS_BUFFER_OVERFLOW ((NTSTATUS)0x80000005L)
#endif // !STATUS_BUFFER_OVERFLOW

#ifndef STATUS_DEVICE_BUSY
// The device is currently busy.
#define STATUS_DEVICE_BUSY ((NTSTATUS)0x80000011L)
#endif // !STATUS_DEVICE_BUSY

#ifndef STATUS_UNSUCCESSFUL
// The requested operation was unsuccessful.
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001L)
#endif // !STATUS_UNSUCCESSFUL

#ifndef STATUS_INVALID_PARAMETER
// An invalid parameter was passed to a service or function.
#define STATUS_INVALID_PARAMETER ((NTSTATUS)0xC000000DL)
#endif // !STATUS_INVALID_PARAMETER

#ifndef STATUS_INVALID_DEVICE_REQUEST
// The specified request is not a valid operation for the target device.
#define STATUS_INVALID_DEVICE_REQUEST ((NTSTATUS)0xC0000010L)
#endif // !STATUS_INVALID_DEVICE_REQUEST

#ifndef STATUS_REVISION_MISMATCH
// Indicates two revision levels are incompatible.
#define STATUS_REVISION_MISMATCH ((NTSTATUS)0xC0000059L)
#endif // !STATUS_REVISION_MISMATCH

#ifndef STATUS_INSUFFICIENT_RESOURCES
// Insufficient system resources exist to complete the API.
#define STATUS_INSUFFICIENT_RESOURCES ((NTSTATUS)0xC000009AL)
#endif // !STATUS_INSUFFICIENT_RESOURCES

#ifndef STATUS_DEVICE_NOT_CONNECTED
#define STATUS_DEVICE_NOT_CONNECTED ((NTSTATUS)0xC000009DL)
#endif // !STATUS_DEVICE_NOT_CONNECTED

#ifndef STATUS_IO_TIMEOUT
// The specified I/O operation on %hs was not completed before the time-out
// period expired.
#define STATUS_IO_TIMEOUT ((NTSTATUS)0xC00000B5L)
#endif // !STATUS_IO_TIMEOUT

#ifndef STATUS_NOT_SUPPORTED
// The request is not supported.
#define STATUS_NOT_SUPPORTED ((NTSTATUS)0xC00000BBL)
#endif // !STATUS_NOT_SUPPORTED

#ifndef STATUS_DEVICE_DOES_NOT_EXIST
// This device does not exist.
#define STATUS_DEVICE_DOES_NOT_EXIST ((NTSTATUS)0xC00000C0L)
#endif // !STATUS_DEVICE_DOES_NOT_EXIST

#ifndef STATUS_CANCELLED
// The I/O request was canceled.
#define STATUS_CANCELLED ((NTSTATUS)0xC0000120L)
#endif // !STATUS_CANCELLED

#ifndef STATUS_INVALID_DEVICE_STATE
// The device is not in a valid state to perform this request.
#define STATUS_INVALID_DEVICE_STATE ((NTSTATUS)0xC0000184L)
#endif // !STATUS_INVALID_DEVICE_STATE

#ifndef STATUS_IO_DEVICE_ERROR
// The I/O device reported an I/O error.
#define STATUS_IO_DEVICE_ERROR ((NTSTATUS)0xC0000185L)
#endif // !STATUS_IO_DEVICE_ERROR

#ifndef STATUS_CONNECTION_REFUSED
// The transport connection attempt was refused by the remote system.
#define STATUS_CONNECTION_REFUSED ((NTSTATUS)0xC0000236L)
#endif // !STATUS_CONNECTION_REFUSED

// Definition from Windows Software Development Kit
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_RECT
{
    HV_INT32 Left;
    HV_INT32 Top;
    HV_INT32 Right;
    HV_INT32 Bottom;
} HV_RECT, *PHV_RECT;

// HID Protocol Structs

// Definition from Windows Driver Kit
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_HID_DEVICE_ATTRIBUTES
{
    // sizeof (struct _HV_HID_DEVICE_ATTRIBUTES)

    HV_UINT32 Size;

    // Vendor ids of this hid device

    HV_UINT16 VendorID;
    HV_UINT16 ProductID;
    HV_UINT16 VersionNumber;
    HV_UINT16 Reserved[11];
} HV_HID_DEVICE_ATTRIBUTES, *PHV_HID_DEVICE_ATTRIBUTES;

#pragma pack(1)
// Definition from Windows Driver Kit
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_HID_DESCRIPTOR_DESC_LIST
{
    HV_UINT8 bReportType;
    HV_UINT16 wReportLength;
} HV_HID_DESCRIPTOR_DESC_LIST, *PHV_HID_DESCRIPTOR_DESC_LIST;
#pragma pack()

#pragma pack(1)
// Definition from Windows Driver Kit
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_HID_DESCRIPTOR
{
    HV_UINT8 bLength;
    HV_UINT8 bDescriptorType;
    HV_UINT16 bcdHID;
    HV_UINT8 bCountry;
    HV_UINT8 bNumDescriptors;
    // An array of one OR MORE descriptors.
    HV_HID_DESCRIPTOR_DESC_LIST DescriptorList[HV_ANYSIZE_ARRAY];
} HV_HID_DESCRIPTOR, *PHV_HID_DESCRIPTOR;
#pragma pack()

// Definition from Windows Driver Kit
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_GROUP_AFFINITY
{
    HV_UINT32 Mask;
    HV_UINT16 Group;
    HV_UINT16 Reserved[3];
} HV_GROUP_AFFINITY, *PHV_GROUP_AFFINITY;

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

// Feature which allows a client (Windows, Linux, MiniVMBus, etc) to specify a
// well-known GUID to identify itself when initiating contact. If not used, the
// client ID is zero.
#define VMBUS_FEATURE_FLAG_CLIENT_ID 0x8

// Indicates the CONFIDENTIAL_CHANNEL flag is supported in the OfferChannel
// flags.
// N.B. This flag is only used by paravisors offering VmBus service and is not
//      supported by the root VmBus driver.
#define VMBUS_FEATURE_FLAG_CONFIDENTIAL_CHANNELS 0x10

// The server supports messages to pause and resume additional control messages.
#define VMBUS_FEATURE_FLAG_PAUSE_RESUME 0x20

// The guest supports having the server (host or paravisor) provide monitor page
// GPAs.
// If this flag is present in the `InitiateContact` message, the guest may still
// provide its own monitor pages, which the server may ignore if it supports the
// flag. The server will only set this flag in the `VersionResponse` message if
// it is actually providing monitor pages, which the guest must then use instead
// of its own.
// If the server sets the flag in the `VersionResponse` message, it must provide
// a non-zero value for the `ChildToParentMonitorPageGpa`; the
// `ParentToChildMonitorPageGpa` is optional and may be zero, in which case the
// guest cannot cancel MNF interrupts from the host.
#define VMBUS_FEATURE_FLAG_SERVER_SPECIFIED_MONITOR_PAGES 0x40

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

    // Since VMBUS_VERSION_V1

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

    // Since VMBUS_VERSION_WIN7

    ChannelMessageUnloadComplete = 17,

    // Since VMBUS_VERSION_WIN10

    ChannelMessageOpenReservedChannel = 18,
    ChannelMessageCloseReservedChannel = 19,
    ChannelMessageCloseReservedResponse = 20,
    // Some clients send the old message even for newer protocols, so check the
    // size to allow the old version to match if it's smaller.
    ChannelMessageTlConnectRequest = 21,

    // Since VMBUS_VERSION_WIN10RS3_0

    ChannelMessageModifyChannel = 22,
    ChannelMessageTlConnectRequestResult = 23,

    // Since VMBUS_VERSION_IRON

    ChannelMessageModifyChannelResponse = 24,

    // Since VMBUS_VERSION_COPPER

    ChannelMessageModifyConnection = 25,
    ChannelMessageModifyConnectionResponse = 26,
    ChannelMessagePause = 27,
    ChannelMessagePauseResponse = 28,
    ChannelMessageResume = 29,

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
// This flag indicates that the channel is offered by the paravisor, and must
// use encrypted memory for the channel ring buffer.
#define VMBUS_OFFER_FLAG_CONFIDENTIAL_RING_BUFFER       0x2
// This flag indicates that the channel is offered by the paravisor, and must
// use encrypted memory for GPA direct packets and additional GPADLs.
#define VMBUS_OFFER_FLAG_CONFIDENTIAL_EXTERNAL_MEMORY   0x4
#define VMBUS_OFFER_FLAG_NAMED_PIPE_MODE 0x10
#define VMBUS_OFFER_FLAG_TLNPI_PROVIDER 0x2000

#define VMBUS_OFFER_FLAGS_WIN6 ( \
    VMBUS_OFFER_FLAG_ENUMERATE_DEVICE_INTERFACE | \
    VMBUS_OFFER_FLAG_NAMED_PIPE_MODE)

#define VMBUS_OFFER_FLAGS_WIN10 \
    (VMBUS_OFFER_FLAGS_WIN6 | VMBUS_OFFER_FLAG_TLNPI_PROVIDER)

// Target VP index value that indicates that interrupts should be disabled for
// the channel.
#define VMBUS_VP_INDEX_DISABLE_INTERRUPT ((HV_UINT32)-1)

typedef enum _HVSOCK_PIPE_TYPE
{
    VmbusHvsockPipeTypeByte = 0,
    VmbusHvsockPipeTypeMessage = 4,
} HVSOCK_PIPE_TYPE, *PHVSOCK_PIPE_TYPE;

typedef struct _HVSOCK_PIPE_USER_DEFINED_PARAMETERS
{
    HVSOCK_PIPE_TYPE PipeType;
} HVSOCK_PIPE_USER_DEFINED_PARAMETERS, *PHVSOCK_PIPE_USER_DEFINED_PARAMETERS;

typedef enum _HVSOCK_PARAMETERS_VERSION
{
    HvsockParametersVersionPreRS5 = 0,
    HvsockParametersVersionRS5 = 1,
} HVSOCK_PARAMETERS_VERSION, *PHVSOCK_PARAMETERS_VERSION;

typedef struct _HVSOCK_USER_DEFINED_PARAMETERS
{
    HVSOCK_PIPE_USER_DEFINED_PARAMETERS PipeParameters;
    HV_UINT8 IsForGuestAccept; // HV_BOOLEAN
    HV_UINT8 IsForGuestContainer; // HV_BOOLEAN
    HVSOCK_PARAMETERS_VERSION Version;
    HV_GUID SiloId;
    HV_UINT8 Padding[2];
} HVSOCK_USER_DEFINED_PARAMETERS, *PHVSOCK_USER_DEFINED_PARAMETERS;

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
            HV_CONNECTION_ID ConnectionId;
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

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_REQUEST_OFFERS, *PVMBUS_CHANNEL_REQUEST_OFFERS;

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_ALL_OFFERS_DELIVERED, *PVMBUS_CHANNEL_ALL_OFFERS_DELIVERED;

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
    HV_VP_INDEX TargetVp;
    // The upstream ring buffer begins at offset zero in the memory described
    // by RingBufferGpadlHandle. The downstream ring buffer follows it at this
    // offset (in pages).
    HV_UINT32 DownstreamRingBufferPageOffset;
    // User-specific data to be passed along to the server endpoint.
    HV_UINT8 UserData[MAX_USER_DEFINED_BYTES];

    // Guest-specified signal parameters; valid only if
    // VMBUS_FEATURE_FLAG_GUEST_SPECIFIED_SIGNAL_PARAMETERS is used.

    HV_CONNECTION_ID ConnectionId;
    HV_UINT16 EventFlag;

    // VMBUS_OPEN_FLAG_*
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
    HV_VP_INDEX TargetVp;
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
    HV_VP_INDEX TargetMessageVp;
    union
    {
        HV_UINT64 InterruptPage;
        struct
        {
            HV_UINT8 TargetSint; // VMBUS_VERSION_WIN10RS3_1
            HV_VTL TargetVtl; // VMBUS_VERSION_WIN10RS4
            HV_UINT8 Reserved[2];
            HV_UINT32 FeatureFlags; // VMBUS_VERSION_COPPER
        };
    };
    HV_GPA ParentToChildMonitorPageGpa;
    HV_GPA ChildToParentMonitorPageGpa; 
    // Used with `VMBUS_FEATURE_FLAG_CLIENT_ID` when the feature is supported
    // (Copper and above).
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
        HV_CONNECTION_ID ConnectionId;
    };

    // Available with VMBUS_VERSION_COPPER.

    HV_UINT32 SupportedFeatures;
    HV_UINT32 Padding;
    // Only valid if VMBUS_FEATURE_FLAG_SERVER_SPECIFIED_MONITOR_PAGES is set.
    HV_GPA ParentToChildMonitorPageGpa;
    // Only valid if VMBUS_FEATURE_FLAG_SERVER_SPECIFIED_MONITOR_PAGES is set.
    HV_GPA ChildToParentMonitorPageGpa;
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
    HV_VP_INDEX TargetVp;
    HV_UINT32 TargetSint;
    HV_UINT32 RingBufferGpadl;
    HV_UINT32 DownstreamPageOffset;
} VMBUS_CHANNEL_OPEN_RESERVED_CHANNEL, *PVMBUS_CHANNEL_OPEN_RESERVED_CHANNEL;

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    HV_UINT32 ChannelId;
    HV_VP_INDEX TargetVp;
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
    HV_GPA ParentToChildMonitorPageGpa;
    HV_GPA ChildToParentMonitorPageGpa;
} VMBUS_CHANNEL_MODIFY_CONNECTION, *PVMBUS_CHANNEL_MODIFY_CONNECTION;

typedef struct _VMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_HEADER Header;
    // This accepts the same values as in VMBUS_CHANNEL_VERSION_RESPONSE.
    HV_UINT8 ConnectionState;
} VMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE, *PVMBUS_CHANNEL_MODIFY_CONNECTION_RESPONSE;

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_PAUSE, *PVMBUS_CHANNEL_PAUSE;

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_PAUSE_RESPONSE, *PVMBUS_CHANNEL_PAUSE_RESPONSE;

typedef VMBUS_CHANNEL_MESSAGE_HEADER
VMBUS_CHANNEL_RESUME, *PVMBUS_CHANNEL_RESUME;

#pragma pack(pop)

#define VMBUS_MESSAGE_CONNECTION_ID 1
#define VMBUS_MESSAGE_REDIRECT_CONNECTION_ID 0x800074
#define VMBUS_MESSAGE_TYPE 1
#define VMBUS_MAX_GPADLS 256
#define VMBUS_MAX_CHANNELS HV_EVENT_FLAGS_COUNT

typedef enum _ENDPOINT_TYPE {
    VmbusServerEndpoint = 0,
    VmbusClientEndpoint,
    VmbusEndpointMaximum
} ENDPOINT_TYPE, *PENDPOINT_TYPE;

#pragma pack(push, 1)

// VMBus ring buffers are sized in multiples 4KB pages, with a 4KB control page.

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
            // If set, the endpoint supports sending signals when the number of
            // free bytes in the ring reaches or exceeds `PendingSendSize`.
            HV_UINT32 SupportsPendingSendSize : 1;
        };
        HV_UINT32 Value;
    } FeatureBits;
} VMRCB, *PVMRCB;

HV_STATIC_ASSERT(HV_FIELD_OFFSET(VMRCB, FeatureBits) == 64);

// The descriptor header on every packet.
typedef struct _VMPACKET_DESCRIPTOR
{
    HV_UINT16 Type; // VMBUS_PACKET_TYPE
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

// A transfer range specifying a length and offset within a transfer page set.
// Only used by NetVSP.
typedef struct _VMTRANSFER_PAGE_RANGE
{
    HV_UINT32 ByteCount;
    HV_UINT32 ByteOffset;
} VMTRANSFER_PAGE_RANGE, *PVMTRANSFER_PAGE_RANGE;

// The extended portion of the packet descriptor that describes a transfer page
// packet.
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
    // may have garbage non-zero values
    HV_UINT32 Reserved;
    HV_UINT32 RangeCount;
    GPA_RANGE Range[HV_ANYSIZE_ARRAY];
} VMDATA_GPA_DIRECT, *PVMDATA_GPA_DIRECT;

typedef enum _VMPIPE_PROTOCOL_MESSAGE_TYPE
{
    VmPipeMessageInvalid = 0,
    // Regular data packet.
    VmPipeMessageData = 1,
    // Data packet that has been partially consumed, in which case the
    // `DataSize` field's high word is the number of bytes already read.
    // The opposite endpoint will never write this type.
    VmPipeMessagePartial = 2,
    // Setup a GPA direct buffer for RDMA.
    VmPipeMessageSetupGpaDirect = 3,
    // Tear down a GPA direct buffer.
    VmPipeMessageTeardownGpaDirect = 4,
    VmPipeMessageIndicationComplete = 5,
} VMPIPE_PROTOCOL_MESSAGE_TYPE, *PVMPIPE_PROTOCOL_MESSAGE_TYPE;

// The maximum size of a pipe packet's payload.
#define VMPIPE_MAXIMUM_PIPE_PACKET_SIZE 16384

// Pipe channel packets are prefixed with this header to allow for
// non-8-multiple lengths.
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

#define SYNTHVID_MAX_VMBUS_PACKET_SIZE 0x4000

// The maximum amount of data we'll send for a cursor in one packet is 8 k.
#define SYNTHVID_CURSOR_MAX_PAYLOAD_SIZE (SYNTHVID_MAX_VMBUS_PACKET_SIZE / 2)

// Maximum supported cursor is 96 pixels x 96 pixels in ARGB 32-bit format.

#define SYNTHVID_CURSOR_MAX_X 96
#define SYNTHVID_CURSOR_MAX_Y 96
#define SYNTHVID_CURSOR_ARGB_PIXEL_SIZE 4
#define SYNTHVID_CURSOR_MAX_SIZE ( \
    SYNTHVID_CURSOR_MAX_X * \
    SYNTHVID_CURSOR_MAX_Y * \
    SYNTHVID_CURSOR_ARGB_PIXEL_SIZE)

// Only use bottom 24bits of target id to be compatible with WDDM 2.0 and DWM
// clone

#define HVD_CHILD_ID 0x00545648
#define HVD_CHILD_ID2 0x00325648
#define HVD_CHILD_ID3 0x00335648

const HV_UINT8 SYNTHVID_EDID_BLOCK[] =
{
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
    0x36, 0x68, 0x2E, 0x06, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0x15, 0x01, 0x04, 0x80, 0x00, 0x00, 0x78,
    0x22, 0xEE, 0x95, 0xA3, 0x54, 0x4C, 0x99, 0x26,
    0x0F, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x6C, 0x20,
    0x00, 0x30, 0x42, 0x00, 0x32, 0x30, 0x40, 0xC0,
    0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E,
    0x00, 0x00, 0x00, 0xFC, 0x00, 0x48, 0x79, 0x70,
    0x65, 0x72, 0x56, 0x4D, 0x6F, 0x6E, 0x69, 0x74,
    0x6F, 0x72, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6,
};

// Maximum supported number of dirty regions in a single dirt message
#define SYNTHVID_MAX_DIRTY_REGIONS 255

#pragma pack(push, 1)

typedef struct _HVD_SCREEN_INFO
{
    HV_UINT16 Width;
    HV_UINT16 Height;
} HVD_SCREEN_INFO, *PHVD_SCREEN_INFO;

// Maximum number of resolutions supported. Please refer to StandardResolutions
// in VideoSynthDevice.cpp (vm\dv\video\core) for list of standard resolutions
// supported.
#define SYNTHVID_MAXIMUM_RESOLUTIONS_COUNT 64

// Emergency reset notification I/O Port
#define SYNTHVID_EMERGENCY_RESET_IO_PORT 0x100

typedef union _SYNTHVID_VERSION
{
    struct
    {
        HV_UINT16 MajorVersion;
        HV_UINT16 MinorVersion;
    };
    HV_UINT32 AsDWORD;
} SYNTHVID_VERSION, *PSYNTHVID_VERSION;

#define SYNTHVID_MAKE_VERSION(Major, Minor) (((Minor) << 16) | (Major))
#define SYNTHVID_MAKE_VERSION_MAJOR(Version) ((Version) & 0x0000FFFF)
#define SYNTHVID_MAKE_VERSION_MINOR(Version) (((Version) & 0xFFFF0000) >> 16)

// Latest version of the SynthVid protocol.

#define SYNTHVID_VERSION_MAJOR 3
#define SYNTHVID_VERSION_MINOR 5

#define SYNTHVID_VERSION_MAJOR_THRESHOLD 3
#define SYNTHVID_VERSION_MINOR_BLUE 3
#define SYNTHVID_VERSION_MINOR_THRESHOLD_M1 4
#define SYNTHVID_VERSION_MINOR_THRESHOLD_M2 5

#define SYNTHVID_VERSION_CURRENT \
    ((SYNTHVID_VERSION_MINOR << 16) | (SYNTHVID_VERSION_MAJOR))
#define TRUE_WITH_VERSION_EXCHANGE (TRUE + 1)

// Mask to be applied to the minor version to determine feature support.
#define SYNTHVID_FEATURE_MINOR_MASK 0xFF

#define SYNTHVID_MAKE_FEATURE(Major, Minor) \
    (((Major) << 16) | (Minor & SYNTHVID_FEATURE_MINOR_MASK))

#define SYNTHVID_EDID_BLOCK_SIZE 128

// SynthVid features by version.
typedef enum _SYNTHVID_FEATURE
{
    // Win7 RTM.
    SynthVidFeatureWin7Rtm = SYNTHVID_MAKE_FEATURE(3, 0),
    SynthVidFeatureBasic = SynthVidFeatureWin7Rtm,
    // Win8 RTM.
    SynthVidFeatureWin8Rtm = SYNTHVID_MAKE_FEATURE(3, 2),
    // Support for resolutions above 1600W or 1200H.
    SynthVidFeatureHighResolutions = SynthVidFeatureWin8Rtm,
    // Support for protocol version reinitialization.
    SynthVidFeatureSupportsReinit = SynthVidFeatureWin8Rtm,
    // Win BLUE
    SynthVidFeatureWinBlue = SYNTHVID_MAKE_FEATURE(3, 3),
    SynthVidFeatureQueryBiosInfo = SynthVidFeatureWinBlue,
    // Win THRESHOLD M1
    SynthVidFeatureWinThresholdM1 = SYNTHVID_MAKE_FEATURE(3, 4),
    SynthVidFeatureResolutionSetByHost = SynthVidFeatureWinThresholdM1,
    // Win THRESHOLD M2
    SynthVidFeatureWinThresholdM2 = SYNTHVID_MAKE_FEATURE(3, 5),
    SynthVidFeatureLockOnDisconnect = SynthVidFeatureWinThresholdM2,
} SYNTHVID_FEATURE, *PSYNTHVID_FEATURE;

// SynthVid Message Types
typedef enum _SYNTHVID_MESSAGE_TYPE
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
    SynthvidSupportedResolutionsRequest = 13,
    SynthvidSupportedResolutionsResponse = 14,
    SynthvidCapabilityRequest = 15,
    SynthvidCapabilityResponse = 16,
    SynthvidMax = 17,
} SYNTHVID_MESSAGE_TYPE, *PSYNTHVID_MESSAGE_TYPE;

// Basic message structures.
typedef struct _SYNTHVID_MESSAGE_HEADER
{
    // Type of the enclosed message
    SYNTHVID_MESSAGE_TYPE Type;
    // Size of the enclosed message (size of the data payload)
    HV_UINT32 Size;
} SYNTHVID_MESSAGE_HEADER, *PSYNTHVID_MESSAGE_HEADER;

typedef struct _SYNTHVID_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    // Enclosed message
    HV_UINT8 Data[HV_ANYSIZE_ARRAY];
} SYNTHVID_MESSAGE, *PSYNTHVID_MESSAGE;

// The following messages are listed in order of occurance during startup and
// handshaking.

// VSC to VSP
typedef struct _SYNTHVID_VERSION_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
} SYNTHVID_VERSION_REQUEST_MESSAGE, *PSYNTHVID_VERSION_REQUEST_MESSAGE;

// VSP to VSC
typedef struct _SYNTHVID_VERSION_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
    // BOOLEAN
    HV_UINT8 IsAccepted;
    // 1 in Veridian 1.0
    HV_UINT8 MaxVideoOutputs;
} SYNTHVID_VERSION_RESPONSE_MESSAGE, *PSYNTHVID_VERSION_RESPONSE_MESSAGE;

// VSC to VSP
typedef struct _SYNTHVID_SUPPORTED_RESOLUTIONS_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 MaximumResolutionCount;
} SYNTHVID_SUPPORTED_RESOLUTIONS_REQUEST_MESSAGE, *PSYNTHVID_SUPPORTED_RESOLUTIONS_REQUEST_MESSAGE;

// VSP to VSC
typedef struct _SYNTHVID_SUPPORTED_RESOLUTIONS_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 EdidBlock[SYNTHVID_EDID_BLOCK_SIZE];
    HV_UINT8 ResolutionCount;
    HV_UINT8 DefaultResolutionIndex;
    HV_UINT8 IsStandard;
    // Max legal value is SYNTHVID_MAXIMUM_RESOLUTIONS_COUNT.
    HVD_SCREEN_INFO SupportedResolution[HV_ANYSIZE_ARRAY];
} SYNTHVID_SUPPORTED_RESOLUTIONS_RESPONSE_MESSAGE, *PSYNTHVID_SUPPORTED_RESOLUTIONS_RESPONSE_MESSAGE;

// VSC to VSP
typedef struct _SYNTHVID_CAPABILITY_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
} SYNTHVID_CAPABILITY_REQUEST_MESSAGE, *PSYNTHVID_CAPABILITY_REQUEST_MESSAGE;

// VSP to VSC
typedef struct _SYNTHVID_CAPABILITY_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT32 LockOnDisconnect : 1;
    HV_UINT32 Reserved : 31;
    HV_UINT32 Reserved2[15];
} SYNTHVID_CAPABILITY_RESPONSE_MESSAGE, *PSYNTHVID_CAPABILITY_RESPONSE_MESSAGE;

// VSC to VSP
typedef struct _SYNTHVID_VRAM_LOCATION_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
    // BOOLEAN
    HV_UINT8 IsVramGpaAddressSpecified;
    HV_GPA VramGpaAddress;
} SYNTHVID_VRAM_LOCATION_MESSAGE, *PSYNTHVID_VRAM_LOCATION_MESSAGE;

// VSP to VSC
// This is called "acknowledge", but in addition, it indicates to the VSC
// that the new physical address location is backed with a memory block
// that the guest can safely write to, knowing that the writes will actually
// be reflected in the VRAM memory block.
typedef struct _SYNTHVID_VRAM_LOCATION_ACK_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
} SYNTHVID_VRAM_LOCATION_ACK_MESSAGE, *PSYNTHVID_VRAM_LOCATION_ACK_MESSAGE;

// These messages are used to communicate "situation updates" or changes in the
// layout of the primary surface.
typedef struct _VIDEO_OUTPUT_SITUATION
{
    // Determine if the device is active or not. (BOOLEAN)
    HV_UINT8 Active;
    // Removed in Threshold -- must be zero.
    HV_UINT32 PrimarySurfaceVramOffset;
    // Number of bits used for each color component.
    HV_UINT8 DepthBits;
    // Number of pixels that represent the width of the image.
    HV_UINT32 WidthPixels;
    // Number of pixels that represent the height of the image.
    HV_UINT32 HeightPixels;
    // Number of bytes from one row of pixels in memory to the next row of
    // pixels in memory. Also called stride. If padding bytes are present after
    // the WidthPixels, the stride/pitch is wider than the width of the image.
    HV_UINT32 PitchBytes;
} VIDEO_OUTPUT_SITUATION, *PVIDEO_OUTPUT_SITUATION;

// VSC to VSP
typedef struct _SYNTHVID_SITUATION_UPDATE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
    // 1 in Veridian 1.0
    HV_UINT8 VideoOutputCount;
    VIDEO_OUTPUT_SITUATION VideoOutput[HV_ANYSIZE_ARRAY];
} SYNTHVID_SITUATION_UPDATE_MESSAGE, *PSYNTHVID_SITUATION_UPDATE_MESSAGE;

// VSP to VSC
typedef struct _SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
} SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE, *PSYNTHVID_SITUATION_UPDATE_ACK_MESSAGE;

// These messages are used to communicate the BIOS Information of the VM.

// VSC to VSP
typedef struct _SYNTHVID_BIOS_INFO_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
} SYNTHVID_BIOS_INFO_REQUEST_MESSAGE, *PSYNTHVID_BIOS_INFO_REQUEST_MESSAGE;

// VSP to VSC
// Note that the BiosFlags field used to just contain a UINT32 that indicated
// the VmGeneration.  For compatibility, we know that VM generations (0,1) map
// to the least significant bit and generation 2 (value 1) maps functionally to
// the StopDeviceSupported flag below.
typedef struct _SYNTHVID_BIOS_INFO_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT32 VmGeneration;
    HV_UINT32 ReservedInt32;
    HV_UINT64 ReservedInt64;
} SYNTHVID_BIOS_INFO_RESPONSE_MESSAGE, *PSYNTHVID_BIOS_INFO_RESPONSE_MESSAGE;

// These messages are used to communicate changes in the pointer position or
// shape.

// VSC to VSP
// This message is ignored unless we're in relative mouse mode.
typedef struct _SYNTHVID_POINTER_POSITION_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    // LDDM may specify FALSE here, XDDM generally will probably always specify
    // TRUE.
    HV_UINT8 IsVisible;
    // 0 is the only valid value for 2D Video VSP 1.0
    HV_UINT8 VideoOutput;

    // Coordinates of upper-left pixel of pointer image.

    HV_INT32 ImageX;
    HV_INT32 ImageY;
} SYNTHVID_POINTER_POSITION_MESSAGE, *PSYNTHVID_POINTER_POSITION_MESSAGE;

// VSC to VSP
typedef struct _SYNTHVID_POINTER_SHAPE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    // When a cursor is larger than the maximum VMBus payload size, it is split
    // up. This 0-based index indicates which portion of the cursor payload is
    // in this message. -1 means final portion. If the cursor is not split, this
    // field contains -1 as the completion sentinel value.
    HV_UINT8 PartialIndex;
    // VideoSynthDevice only support color cursor and monochrome cursor
    // FALSE means monochrome cursor (2 bits per pixel),
    // TRUE means color cursor (32 bits per pixel)
    HV_UINT8 CursorFlags;
    // Max legal value is SYNTHVID_CURSOR_MAX_X.
    HV_UINT32 WidthPixels;
    // Max legal value is SYNTHVID_CURSOR_MAX_Y.
    HV_UINT32 HeightPixels;

    // Stride is implicit based on smallest possible value given width in pixels
    // and format. Pointer hotspot relative to upper-left of pointer image.

    HV_UINT32 HotspotX;
    HV_UINT32 HotspotY;

    // Max length of pixel data is 16k based on CursorFlags,
    // WidthPixels == SYNTHVID_CURSOR_MAX_X,
    // HeightPixels == SYNTHVID_CURSOR_MAX_Y.
    // At this time, we can send the whole cursor shape.
    //
    // Pointer data length can be calculated as follows:
    // if (CursorFlags)
    // {
    //     pointerDataLength = WidthPixels * HeightPixels * 4
    // }
    // else
    // {
    //     pointerDataLength = (WidthPixels + 7) / 8 * HeightPixels * 2
    // }
    HV_UINT8 PixelData[HV_ANYSIZE_ARRAY];
} SYNTHVID_POINTER_SHAPE_MESSAGE, *PSYNTHVID_POINTER_SHAPE_MESSAGE;

#define SYNTHVID_CURSOR_COMPLETE 0xff

// VSP to VSC
// This message is used to squelch portions of the synthvid protocol. Can be
// sent from VSP to VSC at any time after handshaking is complete. VSC
// responsible for bringing VSP up-to-date with at least one message of the
// relevant type if one of these goes from FALSE to TRUE.
typedef struct _SYNTHVID_FEATURE_CHANGE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 IsDirtNeeded;
    HV_UINT8 IsPointerPositionUpdatesNeeded;
    HV_UINT8 IsPointerShapeUpdatesNeeded;
    HV_UINT8 IsVideoSituationUpdatesNeeded;
} SYNTHVID_FEATURE_CHANGE_MESSAGE, *PSYNTHVID_FEATURE_CHANGE_MESSAGE;

typedef struct _SYNTHVID_FEATURE_CHANGE_MESSAGE_V2
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 IsDirtNeeded;
    HV_UINT8 IsPointerPositionUpdatesNeeded;
    HV_UINT8 IsPointerShapeUpdatesNeeded;
    HV_UINT8 IsVideoSituationUpdatesNeeded;
    HV_UINT8 EdidBlock[SYNTHVID_EDID_BLOCK_SIZE];
} SYNTHVID_FEATURE_CHANGE_MESSAGE_V2, *PSYNTHVID_FEATURE_CHANGE_MESSAGE_V2;

// VSC to VSP
// This message is used to communicate dirty regions to the VSP.
typedef struct _SYNTHVID_DIRT_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    // 0 is the only valid value for 2D Video VSP 1.0
    HV_UINT8 VideoOutput;
    HV_UINT8 DirtCount;
    HV_RECT Dirt[HV_ANYSIZE_ARRAY];
} SYNTHVID_DIRT_MESSAGE, *PSYNTHVID_DIRT_MESSAGE;

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

// {D34B2567-B9B6-42B9-8778-0A4EC0B955BF}
const HV_GUID HK_INSTANCE_ID =
{
    0xD34B2567,
    0xB9B6,
    0x42B9,
    { 0x87, 0x78, 0x0A, 0x4E, 0xC0, 0xB9, 0x55, 0xBF }
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
} HK_MESSAGE_TYPE, *PHK_MESSAGE_TYPE;

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
// Microsoft Hyper-V Input
//

// {CFA8B69E-5B4A-4CC0-B98B-8BA1A1F3F95A}
const HV_GUID SYNTHHID_CLASS_ID =
{
    0xCFA8B69E,
    0x5B4A,
    0x4CC0,
    { 0xB9, 0x8B, 0x8B, 0xA1, 0xA1, 0xF3, 0xF9, 0x5A }
};

// {58F75A6D-D949-4320-99E1-A2A2576D581C}
const HV_GUID SYNTHHID_INSTANCE_ID =
{
    0x58F75A6D,
    0xD949,
    0x4320,
    { 0x99, 0xE1, 0xA2, 0xA2, 0x57, 0x6D, 0x58, 0x1C }
};

typedef union _SYNTHHID_VERSION
{
    HV_UINT32 AsDWord;
    struct
    {
        HV_UINT16 Minor;
        HV_UINT16 Major;
    };
} SYNTHHID_VERSION, *PSYNTHHID_VERSION;

#define SYNTHHID_MAKE_VERSION(Major, Minor) \
    ((HV_UINT32)(Major) << 16 | (HV_UINT32)(Minor))
#define SYNTHHID_INPUT_VERSION SYNTHHID_MAKE_VERSION(2, 0)

typedef enum _SYNTHHID_MESSAGE_TYPE
{
    SynthHidProtocolRequest = 0,
    SynthHidProtocolResponse = 1,
    SynthHidInitialDeviceInfo = 2,
    SynthHidInitialDeviceInfoAck = 3,
    SynthHidInputReport = 4,
    SynthHidMax = 5,
} SYNTHHID_MESSAGE_TYPE, *PSYNTHHID_MESSAGE_TYPE;

#define SYNTHHID_HID_VENDOR_ID 0x045e
#define SYNTHHID_HID_PRODUCT_ID 0x0621
#define SYNTHHID_HID_VERSION_ID 0x0001

#define SYNTHHID_INPUT_REPORT_SIZE 16
#define SYNTHHID_MAX_HID_MESSAGE_SIZE 512
#define SYNTHHID_MAX_HID_REPORT_DESCRIPTOR 256

typedef struct _SYNTHHID_MESSAGE_HEADER
{
    SYNTHHID_MESSAGE_TYPE Type;
    HV_UINT32 Size;
} SYNTHHID_MESSAGE_HEADER, *PSYNTHHID_MESSAGE_HEADER;

typedef struct _SYNTHHID_PROTOCOL_REQUEST
{
    SYNTHHID_MESSAGE_HEADER Header;
    SYNTHHID_VERSION VersionRequested;
} SYNTHHID_PROTOCOL_REQUEST, *PSYNTHHID_PROTOCOL_REQUEST;

#pragma pack(1)
typedef struct _SYNTHHID_PROTOCOL_RESPONSE
{
    SYNTHHID_MESSAGE_HEADER Header;
    SYNTHHID_VERSION VersionRequested;
    HV_UINT8 Approved;
} SYNTHHID_PROTOCOL_RESPONSE, *PSYNTHHID_PROTOCOL_RESPONSE;
#pragma pack()

#pragma pack(1)
typedef struct _SYNTHHID_DEVICE_INFO
{
    SYNTHHID_MESSAGE_HEADER Header;
    HV_HID_DEVICE_ATTRIBUTES HidDeviceAttributes;
    HV_HID_DESCRIPTOR HidDescriptorInformation;
    HV_UINT8 HidReportDescriptorInformation[128];
} SYNTHHID_DEVICE_INFO, *PSYNTHHID_DEVICE_INFO;
#pragma pack()

#pragma pack(1)
typedef struct _SYNTHHID_DEVICE_INFO_ACK
{
    SYNTHHID_MESSAGE_HEADER Header;
    HV_UINT8 Acknowledged;
} SYNTHHID_DEVICE_INFO_ACK, *PSYNTHHID_DEVICE_INFO_ACK;
#pragma pack()

#define SYNTHHID_HID_MOUSE_BUTTON_LEFT 0x01
#define SYNTHHID_HID_MOUSE_BUTTON_RIGHT 0x02
#define SYNTHHID_HID_MOUSE_BUTTON_MIDDLE 0x04

#define SYNTHHID_MOUSE_NUMBER_BUTTONS 5

typedef enum _SYNTHHID_MOUSE_BUTTON
{
    SynthHidMouseButtonLeft = 0,
    SynthHidMouseButtonRight = 1,
    SynthHidMouseButtonMiddle = 2,
    SynthHidMouseButtonFourth = 3,
    SynthHidMouseButtonFifth = 4,
} SYNTHHID_MOUSE_BUTTON, *PSYNTHHID_MOUSE_BUTTON;

typedef enum _SYNTHHID_SCROLL_TYPE
{
    // we use -1, 1, because we want to increment the z-value (i16) in the
    // corresponding direction

    SynthHidScrollTypeDown = -1,
    SynthHidScrollTypeNoChange = 0,
    SynthHidScrollTypeUp = 1,
} SYNTHHID_SCROLL_TYPE, *PSYNTHHID_SCROLL_TYPE;

#define SYNTHHID_MOUSE_EVENT_FLAG_XY_ABSOLUTE (1 << 0)

#define SYNTHHID_MOUSE_EVENT_NO_CHANGE(Button) (1 << (((HV_UINT32)Button) + 1))

#define SYNTHHID_MOUSE_EVENT_FLAG_LEFT_BUTTON_NO_CHANGE \
    SYNTHHID_MOUSE_EVENT_NO_CHANGE(SynthHidMouseButtonLeft)
#define SYNTHHID_MOUSE_EVENT_FLAG_RIGHT_BUTTON_NO_CHANGE \
    SYNTHHID_MOUSE_EVENT_NO_CHANGE(SynthHidMouseButtonRight)
#define SYNTHHID_MOUSE_EVENT_FLAG_MIDDLE_BUTTON_NO_CHANGE \
    SYNTHHID_MOUSE_EVENT_NO_CHANGE(SynthHidMouseButtonMiddle)
#define SYNTHHID_MOUSE_EVENT_FLAG_FOURTH_BUTTON_NO_CHANGE \
    SYNTHHID_MOUSE_EVENT_NO_CHANGE(SynthHidMouseButtonFourth)
#define SYNTHHID_MOUSE_EVENT_FLAG_FIFTH_BUTTON_NO_CHANGE \
    SYNTHHID_MOUSE_EVENT_NO_CHANGE(SynthHidMouseButtonFifth)

#define SYNTHHID_MOUSE_EVENT_FLAG_ALL_BUTTONS_NO_CHANGE ( \
    SYNTHHID_MOUSE_EVENT_FLAG_LEFT_BUTTON_NO_CHANGE | \
    SYNTHHID_MOUSE_EVENT_FLAG_MIDDLE_BUTTON_NO_CHANGE | \
    SYNTHHID_MOUSE_EVENT_FLAG_RIGHT_BUTTON_NO_CHANGE | \
    SYNTHHID_MOUSE_EVENT_FLAG_FOURTH_BUTTON_NO_CHANGE | \
    SYNTHHID_MOUSE_EVENT_FLAG_FIFTH_BUTTON_NO_CHANGE)

#define SYNTHHID_MOUSE_EVENT_SINGLE_CHANGE(Button) ( \
    SYNTHHID_MOUSE_EVENT_FLAG_ALL_BUTTONS_NO_CHANGE & \
    ~SYNTHHID_MOUSE_EVENT_NO_CHANGE(Button))

#define SYNTHHID_MOUSE_EVENT_FLAG_FORCE_REPORT_EVENT (1 << 8)

#pragma pack(1)
typedef struct _SYNTHHID_MOUSE_PACKET
{
    HV_UINT8 ButtonData;
    HV_INT16 X;
    HV_INT16 Y;
    HV_INT16 Z;
} SYNTHHID_MOUSE_PACKET, *PSYNTHHID_MOUSE_PACKET;
#pragma pack()

#pragma pack(1)
typedef struct _SYNTHHID_INPUT_REPORT
{
    SYNTHHID_MESSAGE_HEADER Header;
    SYNTHHID_MOUSE_PACKET InputReport;
} SYNTHHID_INPUT_REPORT, *PSYNTHHID_INPUT_REPORT;
#pragma pack()

const HV_UINT8 SYNTHHID_REPORT_DESCRIPTOR[] =
{
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x02, // USAGE (Mouse)
    0xA1, 0x01, // COLLECTION (Application)
    0x09, 0x01, //   USAGE (Pointer)
    0xA1, 0x00, //   COLLECTION (Physical)
    0x05, 0x09, //     USAGE_PAGE (Buttons)
    0x19, 0x01, //     Usage Minimum (01)
    0x29, 0x05, //     Usage Maximum (05)
    0x15, 0x00, //     Logical Minimum (00)
    0x25, 0x01, //     Logical Maximum (01)
    0x95, 0x05, //     Report Count (5)
    0x75, 0x01, //     Report Size (1)
    0x81, 0x02, //     Input (Data, Variable, Absolute) ;
    //         5 button bits
    0x95, 0x01, //     Report Count (1)
    0x75, 0x03, //     Report Size (3)
    0x81, 0x01, //     Input (Constant) ; 3 bit padding
    0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30, //     USAGE (X)
    0x09, 0x31, //     USAGE (Y)
    0x15, 0x00, //     Logical Minimum (0)
    0x26, 0xFF, 0x7F, //     Logical Maximum (32767)
    0x75, 0x10, //     Report Size (16)
    0x95, 0x02, //     Report Count (2)
    0x81, 0x02, //     Input (Data, Variable, Absolute) ;
    //         2 Axes absolute data.
    0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
    0x09, 0x38, //     USAGE (Wheel)
    0x16, 0x01, 0x80, //     Logical Minimum (-32767)
    0x26, 0xFF, 0x7F, //     Logical Maximum (32767)
    0x75, 0x10, //     Report Size (16)
    0x95, 0x01, //     Report Count (1)
    0x81, 0x06, //     Input (Data, Variable, Relative) ;
    //         1 Axes relative data.
    0xC0, //   END_COLLECTION
    0xC0, // END_COLLECTION
};

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

// {32412632-86CB-44A2-9B5C-50D1417354F5}
const HV_GUID VMIDE_ACCELERATOR_CLASS_ID =
{
    0x32412632,
    0x86CB,
    0x44A2,
    { 0x9B, 0x5C, 0x50, 0xD1, 0x41, 0x73, 0x54, 0xF5 }
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
#define VMSTOR_PROTOCOL_VERSION_THRESHOLD VMSTOR_PROTOCOL_VERSION(6, 2)
#define VMSTOR_PROTOCOL_VERSION_CURRENT VMSTOR_PROTOCOL_VERSION_BLUE

// The max transfer length will be published when we offer a vmbus channel.
// Max transfer bytes - this determines the reserved MDL size and how large
// requests can be that the clients will forward.
#define MAX_TRANSFER_LENGTH (8 * 1024 * 1024)

// Indicates that the device supports Asynchronous Notifications (AN)
#define VMSTOR_PROPERTY_AN_CAPABLE 0x1

// Packet structure describing virtual storage requests.
typedef enum _VSTOR_PACKET_OPERATION
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
} VSTOR_PACKET_OPERATION, *PVSTOR_PACKET_OPERATION;

// Platform neutral description of a SCSI request

#pragma pack(push, 1)

#define CDB16GENERIC_LENGTH 0x10

#define MAX_DATA_BUFFER_LENGTH_WITH_PADDING 0x14

#define VMSCSI_SENSE_BUFFER_SIZE_REVISION_1 0x12
#define VMSCSI_SENSE_BUFFER_SIZE 0x14

#define VMSCSI_IOCTL_DATA_OUT 0
#define VMSCSI_IOCTL_DATA_IN 1

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
    // VMSCSI_IOCTL_DATA_OUT or VMSCSI_IOCTL_DATA_IN
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
// up with the VMBus channel. Newer drivers and Linux just look at instance ID.
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
    NTSTATUS Status;
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
#define NVSP_PROTOCOL_VERSION_6 NVSP_PROTOCOL_VERSION(6, 0)
#define NVSP_PROTOCOL_VERSION_61 NVSP_PROTOCOL_VERSION(6, 1)
#define NVSP_PROTOCOL_VERSION_CURRENT NVSP_PROTOCOL_VERSION_5

#define NVSP_PROTOCOL_VERSION_IS_VALID(_Version_) ( \
    (_Version_) == NVSP_PROTOCOL_VERSION_5 || \
    (_Version_) == NVSP_PROTOCOL_VERSION_4 || \
    (_Version_) == NVSP_PROTOCOL_VERSION_2 || \
    (_Version_) == NVSP_PROTOCOL_VERSION_1)

#define NVSP_PACKET_SIZE_V1 0x1c
#define NVSP_PACKET_SIZE_V61 0x28

#define NVSP_DATA_CHANNEL_TYPE 0
#define NVSP_CONTROL_CHANNEL_TYPE 1

#define NVSP_OPERATIONAL_STATUS_OK ((HV_UINT32)0x00000000)
#define NVSP_OPERATIONAL_STATUS_DEGRADED ((HV_UINT32)0x00000001)
#define NVSP_OPERATIONAL_STATUS_NONRECOVERABLE ((HV_UINT32)0x00000002)
#define NVSP_OPERATIONAL_STATUS_NO_CONTACT ((HV_UINT32)0x00000003)
#define NVSP_OPERATIONAL_STATUS_LOST_COMMUNICATION ((HV_UINT32)0x00000004)

// The maximum number of transfer pages (packets) the VSP will use on on a
// receive
#define NVSP_MAX_PACKETS_PER_RECEIVE 375

#define NVSP_MAX_IPV4_PACKET 65535
#define NVSP_IPV4_MIN_MINIMUM_MTU 352

// The maximum number of transfer pages (packets) the VSP will use on a receive
// when RSC Over VMBus is enabled. (Should be 562)
#define NVSP_MAX_PACKETS_PER_RECEIVE_RSC_OVER_VMBUS ( \
    NVSP_MAX_PACKETS_PER_RECEIVE + \
    (NVSP_MAX_IPV4_PACKET / NVSP_IPV4_MIN_MINIMUM_MTU) \
    + 1)

// Defines the maximum number of processors that can be used by a single VMQ's
// traffic. We are storing this value here because both the VM and host needs it
// to manage the vRSS indirection table (VM needs it for send and host needs it
// for receive).
#define VMS_SWITCH_RSS_MAX_RSS_PROC_COUNT 16

// Defines the maximum number of indirection table entries that can be used by a
// single VMQ's traffic. We are storing this value here because both the VM and
// host needs it to manage the vRSS indirection table (VM needs it for send and
// host needs it for receive).
#define VMS_SWITCH_RSS_MAX_INDIRECTION_TABLE_ENTRIES 128

// For vmNic, this defines the maximum number of send indirection table entries
// that can be used by a single VMQ. We are separating out the max table size
// for send and recv side indirection table, as updating send side indirection
// table size will require a bump in nvsp version.
#define VMS_SWITCH_RSS_MAX_SEND_INDIRECTION_TABLE_ENTRIES 16

// Specified the minimum number of indirection table entries that can be used by
// a single VMQ's traffic.
#define VMS_SWITCH_RSS_MIN_INDIRECTION_TABLE_ENTRIES 16

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
    NvspMessage5Max = NvspMessage5TypeSendIndirectionTable,

    // Version 6 messages

    NvspMessage6TypePdApi,
    NvspMessage6TypePdPostBatch,
    // The maximum allowed message ID for the v6 protocol.
    NvspMessage6Max = NvspMessage6TypePdPostBatch
} NVSP_MESSAGE_TYPE, *PNVSP_MESSAGE_TYPE;

#define NVSP_PROTOCOL_VERSION_1_HANDLER_COUNT \
    ((NvspMessage1Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_2_HANDLER_COUNT \
    ((NvspMessage2Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_4_HANDLER_COUNT \
    ((NvspMessage4Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_5_HANDLER_COUNT \
    ((NvspMessage5Max - NvspVersionMessageStart) + 1)

// Unfortunately, KDNET MiniVSC took a dependency on buggy version 6 of protocol
// (which has number of messages as in protocol version 5). Since all VMs with
// kdnet debugger are be out there, we must handle this version as well.

#define NVSP_PROTOCOL_VERSION_6_HANDLER_COUNT \
    ((NvspMessage5Max - NvspVersionMessageStart) + 1)

#define NVSP_PROTOCOL_VERSION_61_HANDLER_COUNT \
    ((NvspMessage6Max - NvspVersionMessageStart) + 1)

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
    // not actually used
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
    NVSP_STATUS Status;
} NVSP_MESSAGE_INIT_COMPLETE, *PNVSP_MESSAGE_INIT_COMPLETE;

typedef union _NVSP_MESSAGE_INIT_UBER
{
    NVSP_MESSAGE_INIT Init;
    NVSP_MESSAGE_INIT_COMPLETE InitComplete;
} NVSP_MESSAGE_INIT_UBER, *PNVSP_MESSAGE_INIT_UBER;

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
    NVSP_STATUS Status;
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
    NVSP_STATUS Status;
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
    NVSP_STATUS Status;
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
            HV_UINT64 RscOverVmbus : 1;
            HV_UINT64 Reserved : 56;
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

typedef HV_UINT32 NDIS_OID, *PNDIS_OID;

// NvspMessage5TypeOidQueryEx
typedef struct _NVSP_5_MESSAGE_OID_QUERY_EX
{
    // Header information for the Query OID
    HV_NDIS_OBJECT_HEADER Header;
    // OID being queried
    NDIS_OID Oid;
} NVSP_5_MESSAGE_OID_QUERY_EX, *PNVSP_5_MESSAGE_OID_QUERY_EX;

// NvspMessage5TypeOidQueryExComplete
typedef struct _NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE
{
    // Result of the query. (NDIS_STATUS)
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

// NvspMessage6TypePdApi

typedef enum _NVSP_6_MESSAGE_PD_API_OPERATION
{
    PdApiOpConfiguration = 1,
    PdApiOpSwitchDatapath,
    PdApiOpOpenProvider,
    PdApiOpCloseProvider,
    PdApiOpCreateQueue,
    PdApiOpFlushQueue,
    PdApiOpFreeQueue,
    PdApiOpAllocateCommonBuffer,
    PdApiOpFreeCommonBuffer,
    PdApiOpMax
} NVSP_6_MESSAGE_PD_API_OPERATION, *PNVSP_6_MESSAGE_PD_API_OPERATION;

typedef struct _NVSP_6_MESSAGE_PD_API_REQUEST
{
    HV_UINT32 Operation; // NVSP_6_MESSAGE_PD_API_OPERATION
    union
    {
        struct
        {
            // MMIO information is sent from the VM to VSP.

            HV_INT64 MmioPhysicalAddress;
            HV_UINT32 MmioLength;

            // This is a hint to NVSP: how many PD queues a VM can support.
            HV_UINT16 NumPdQueues;
        } Configuration;
        struct
        {
            HV_UINT8 HostDatapathIsPacketDirect; // BOOLEAN
            HV_UINT8 GuestPacketDirectIsEnabled; // BOOLEAN
        } SwitchDatapath;
        struct
        {
            HV_UINT32 ProviderId;
            // This are the flags from OPEN_PROVIDER structure.
            HV_UINT32 Flags;
        } OpenProvider;
        struct
        {
            HV_UINT32 ProviderId;
        } CloseProvider;
        struct
        {
            HV_UINT32 ProviderId;
            HV_UINT16 QueueId;
            HV_UINT16 QueueSize;
            HV_UINT8 IsReceiveQueue;
            HV_UINT8 IsRssQueue;
            HV_UINT32 ReceiveDataLength;
            HV_GROUP_AFFINITY Affinity;
        } CreateQueue;
        struct
        {
            HV_UINT32 ProviderId;
            HV_UINT16 QueueId;
        } DeleteQueue;
        struct
        {
            HV_UINT32 ProviderId;
            HV_UINT16 QueueId;
        } FlushQueue;
        struct
        {
            HV_UINT32 Length;
            HV_UINT32 PreferredNode;
            HV_UINT16 RegionId;
        } AllocateCommonBuffer;
        struct
        {
            HV_UINT32 Length;
            HV_UINT64 PhysicalAddress;
            HV_UINT32 PreferredNode;
            HV_UINT16 RegionId;
            HV_UINT8 CacheType;
        } FreeCommonBuffer;
    };
} NVSP_6_MESSAGE_PD_API_REQUEST, *PNVSP_6_MESSAGE_PD_API_REQUEST;

typedef struct _NVSP_6_MESSAGE_PD_API_COMPLETE
{
    HV_UINT32 Operation; // NVSP_6_MESSAGE_PD_API_OPERATION
    // The status of the PD operation in NT STATUS code
    HV_UINT32 Status;
    // Operation specific completion data.
    union
    {
        struct
        {
            // This is the actual number of PD queues allocated to the VM.
            HV_UINT16 NumPdQueues;
            HV_UINT8 NumReceiveRssPDQueues;
            HV_UINT8 IsSupportedByVSP;
            HV_UINT8 IsEnabledByVSP;
        } Configuration;
        struct
        {
            HV_UINT32 ProviderId;
        } OpenProvider;
        struct
        {
            HV_UINT32 ProviderId;
            HV_UINT16 QueueId;
            HV_UINT16 QueueSize;
            HV_UINT32 ReceiveDataLength;
            HV_GROUP_AFFINITY Affinity;
        } CreateQueue;
        struct
        {
            HV_UINT64 PhysicalAddress;
            HV_UINT32 Length;
            HV_UINT32 PreferredNode;
            HV_UINT16 RegionId;
            HV_UINT8 CacheType;
        } AllocateCommonBuffer;
    };
} NVSP_6_MESSAGE_PD_API_COMPLETE, *PNVSP_6_MESSAGE_PD_API_COMPLETE;

typedef struct _NVSP_6_PD_BUFFER
{
    HV_UINT32 RegionOffset;
    HV_UINT16 RegionId;
    HV_UINT16 IsPartial : 1;
    HV_UINT16 ReservedMbz : 15;
} NVSP_6_PD_BUFFER, *PNVSP_6_PD_BUFFER;
HV_STATIC_ASSERT(sizeof(NVSP_6_PD_BUFFER) == sizeof(HV_UINT64));

typedef struct _NVSP_6_MESSAGE_PD_BATCH_MESSAGE
{
    NVSP_MESSAGE_HEADER Header;
    HV_UINT16 Count;
    HV_UINT16 GuestToHost : 1;
    HV_UINT16 IsReceive : 1;
    HV_UINT16 ReservedMbz : 14;
    NVSP_6_PD_BUFFER PdBuffer[0];
} NVSP_6_MESSAGE_PD_BATCH_MESSAGE, *PNVSP_6_MESSAGE_PD_BATCH_MESSAGE;
HV_STATIC_ASSERT(sizeof(NVSP_6_MESSAGE_PD_BATCH_MESSAGE) == sizeof(HV_UINT64));

// Request from the VSC to switch over to NvIo protocol. VSP can reject the
// request.
typedef struct _NVSP_7_MESSAGE_USE_NVIO_REQUEST
{
    NVSP_MESSAGE_HEADER Header; // Type == NvspMessage7TypeUseNvIo
    HV_UINT32 ReservedMbz1;
    HV_UINT64 ReservedMbz2;
} NVSP_7_MESSAGE_USE_NVIO_REQUEST, *PNVSP_7_MESSAGE_USE_NVIO_REQUEST;

typedef struct _NVSP_7_MESSAGE_USE_NVIO_COMPLETE
{
    HV_UINT32 Status;
    HV_UINT32 ControlChannelIndex;
} NVSP_7_MESSAGE_USE_NVIO_COMPLETE, *PNVSP_7_MESSAGE_USE_NVIO_COMPLETE;

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
} NVSP_1_MESSAGE_UBER, *PNVSP_1_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_2_UBER
{
    NVSP_2_MESSAGE_SEND_NDIS_CONFIG SendNdisConfig;
} NVSP_2_MESSAGE_UBER, *PNVSP_2_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_4_UBER
{
    NVSP_4_MESSAGE_SEND_VF_ASSOCIATION VFAssociation;
    NVSP_4_MESSAGE_SWITCH_DATA_PATH SwitchDataPath;
} NVSP_4_MESSAGE_UBER, *PNVSP_4_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_5_UBER
{
    NVSP_5_MESSAGE_OID_QUERY_EX OidQueryEx;
    NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE OidQueryExComplete;
    NVSP_5_MESSAGE_SUBCHANNEL_REQUEST SubChannelRequest;
    NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE SubChannelRequestComplete;
    NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE SendTable;
} NVSP_5_MESSAGE_UBER, *PNVSP_5_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_6_UBER
{
    NVSP_6_MESSAGE_PD_API_REQUEST PdApiRequest;
    NVSP_6_MESSAGE_PD_API_COMPLETE PdApiComplete;
} NVSP_6_MESSAGE_UBER, *PNVSP_6_MESSAGE_UBER;

typedef union _NVSP_MESSAGE_7_UBER
{
    NVSP_7_MESSAGE_USE_NVIO_REQUEST UseNvIoRequest;
    NVSP_7_MESSAGE_USE_NVIO_COMPLETE UseNvIoComplete;
} NVSP_7_MESSAGE_UBER, *PNVSP_7_MESSAGE_UBER;

typedef union _NVSP_ALL_MESSAGES
{
    NVSP_MESSAGE_INIT_UBER InitMessages;
    NVSP_1_MESSAGE_UBER Version1Messages;
    NVSP_2_MESSAGE_UBER Version2Messages;
    NVSP_4_MESSAGE_UBER Version4Messages;
    NVSP_5_MESSAGE_UBER Version5Messages;
    NVSP_6_MESSAGE_UBER Version6Messages;
    NVSP_7_MESSAGE_UBER Version7Messages;
} NVSP_ALL_MESSAGES, *PNVSP_ALL_MESSAGES;

// ALL Messages
typedef struct _NVSP_MESSAGE
{
    NVSP_MESSAGE_HEADER Header;
    NVSP_ALL_MESSAGES Messages;
    HV_UINT32 Padding;
} NVSP_MESSAGE, *PNVSP_MESSAGE;

HV_STATIC_ASSERT(sizeof(NVSP_MESSAGE) % 8 == 0);

// Message of the protocol version 1 is the biggest of all the legacy messages.
#define NVSP_LEGACY_MESSAGE_SIZE \
    (sizeof(NVSP_MESSAGE_HEADER) + sizeof(NVSP_1_MESSAGE_UBER))

// Version 6.1 of protocol is the first one that increases the message size.
#define NVSP_61_MESSAGE_SIZE \
    (sizeof(NVSP_MESSAGE_HEADER) + sizeof(NVSP_6_MESSAGE_UBER))

HV_STATIC_ASSERT(NVSP_61_MESSAGE_SIZE > NVSP_LEGACY_MESSAGE_SIZE);

// Version 7 of protocol
#define NVSP_7_MESSAGE_SIZE NVSP_61_MESSAGE_SIZE
HV_STATIC_ASSERT(NVSP_7_MESSAGE_SIZE == NVSP_61_MESSAGE_SIZE);

typedef struct _NVSP_SEND_INDIRECTION_TABLE_MESSAGE
{
    NVSP_MESSAGE NvspMessage;
    HV_UINT32 SendIndirectionTable[VMS_SWITCH_RSS_MAX_SEND_INDIRECTION_TABLE_ENTRIES];
} NVSP_SEND_INDIRECTION_TABLE_MESSAGE, *PNVSP_SEND_INDIRECTION_TABLE_MESSAGE;

// The indirection table message is the largest message we send right now
// without using an external MDL. VMBUS requires us to specify the max packet
// size using VmbChannelInitSetMaximumPacketSize. We will not be able to receive
// packets that are larger than this.
#define NVSP_MAX_VMBUS_MESSAGE_SIZE (sizeof(NVSP_SEND_INDIRECTION_TABLE_MESSAGE))

// Ensure the send indirection table size is equal to 16. This defines the
// legacy NVSP message size (which cannot be changed).
// Increasing VMS_SWITCH_RSS_MAX_SEND_INDIRECTION_TABLE_ENTRIES will also
// increase the size of NVSP_SEND_INDIRECTION_TABLE_MESSAGE, which is the
// largest message we currently send without using an external MDL.
HV_STATIC_ASSERT(VMS_SWITCH_RSS_MAX_SEND_INDIRECTION_TABLE_ENTRIES == 16);

#pragma pack(pop)

// Basic types

typedef HV_UINT32 RNDIS_REQUEST_ID, *PRNDIS_REQUEST_ID;
typedef HV_UINT32 RNDIS_HANDLE, *PRNDIS_HANDLE;
typedef HV_UINT32 RNDIS_STATUS, *PRNDIS_STATUS;
typedef HV_UINT32 RNDIS_REQUEST_TYPE, *PRNDIS_REQUEST_TYPE;
typedef HV_UINT32 RNDIS_OID, *PRNDIS_OID;
typedef HV_UINT32 RNDIS_CLASS_ID, *PRNDIS_CLASS_ID;
typedef HV_UINT32 RNDIS_MEDIUM, *PRNDIS_MEDIUM;
typedef HV_UINT32 RNDIS_AF, *PRNDIS_AF;

// Status codes

#define RNDIS_STATUS_SUCCESS ((RNDIS_STATUS)STATUS_SUCCESS)
#define RNDIS_STATUS_PENDING ((RNDIS_STATUS)STATUS_PENDING)
#define RNDIS_STATUS_NOT_RECOGNIZED ((RNDIS_STATUS)0x00010001L)
#define RNDIS_STATUS_NOT_COPIED ((RNDIS_STATUS)0x00010002L)
#define RNDIS_STATUS_NOT_ACCEPTED ((RNDIS_STATUS)0x00010003L)
#define RNDIS_STATUS_CALL_ACTIVE ((RNDIS_STATUS)0x00010007L)
#define RNDIS_STATUS_ONLINE ((RNDIS_STATUS)0x40010003L)
#define RNDIS_STATUS_RESET_START ((RNDIS_STATUS)0x40010004L)
#define RNDIS_STATUS_RESET_END ((RNDIS_STATUS)0x40010005L)
#define RNDIS_STATUS_RING_STATUS ((RNDIS_STATUS)0x40010006L)
#define RNDIS_STATUS_CLOSED ((RNDIS_STATUS)0x40010007L)
#define RNDIS_STATUS_WAN_LINE_UP ((RNDIS_STATUS)0x40010008L)
#define RNDIS_STATUS_WAN_LINE_DOWN ((RNDIS_STATUS)0x40010009L)
#define RNDIS_STATUS_WAN_FRAGMENT ((RNDIS_STATUS)0x4001000AL)
#define RNDIS_STATUS_MEDIA_CONNECT ((RNDIS_STATUS)0x4001000BL)
#define RNDIS_STATUS_MEDIA_DISCONNECT ((RNDIS_STATUS)0x4001000CL)
#define RNDIS_STATUS_HARDWARE_LINE_UP ((RNDIS_STATUS)0x4001000DL)
#define RNDIS_STATUS_HARDWARE_LINE_DOWN ((RNDIS_STATUS)0x4001000EL)
#define RNDIS_STATUS_INTERFACE_UP ((RNDIS_STATUS)0x4001000FL)
#define RNDIS_STATUS_INTERFACE_DOWN ((RNDIS_STATUS)0x40010010L)
#define RNDIS_STATUS_MEDIA_BUSY ((RNDIS_STATUS)0x40010011L)
#define RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION ((RNDIS_STATUS)0x40010012L)
#define RNDIS_STATUS_WW_INDICATION RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION
#define RNDIS_STATUS_LINK_SPEED_CHANGE ((RNDIS_STATUS)0x40010013L)
// NDIS Status value for REMOTE_NDIS_INDICATE_STATUS_MSG messages (NDIS_STATUS)
#define RNDIS_STATUS_NETWORK_CHANGE ((RNDIS_STATUS)0x40010018L)
#define RNDIS_STATUS_TASK_OFFLOAD_CURRENT_CONFIG ((RNDIS_STATUS)0x40020006L)
#define RNDIS_STATUS_NOT_RESETTABLE ((RNDIS_STATUS)0x80010001L)
#define RNDIS_STATUS_SOFT_ERRORS ((RNDIS_STATUS)0x80010003L)
#define RNDIS_STATUS_HARD_ERRORS ((RNDIS_STATUS)0x80010004L)
#define RNDIS_STATUS_BUFFER_OVERFLOW ((RNDIS_STATUS)STATUS_BUFFER_OVERFLOW)
#define RNDIS_STATUS_FAILURE ((RNDIS_STATUS)STATUS_UNSUCCESSFUL)
#define RNDIS_STATUS_RESOURCES ((RNDIS_STATUS)STATUS_INSUFFICIENT_RESOURCES)
#define RNDIS_STATUS_CLOSING ((RNDIS_STATUS)0xC0010002L)
#define RNDIS_STATUS_BAD_VERSION ((RNDIS_STATUS)0xC0010004L)
#define RNDIS_STATUS_BAD_CHARACTERISTICS ((RNDIS_STATUS)0xC0010005L)
#define RNDIS_STATUS_ADAPTER_NOT_FOUND ((RNDIS_STATUS)0xC0010006L)
#define RNDIS_STATUS_OPEN_FAILED ((RNDIS_STATUS)0xC0010007L)
#define RNDIS_STATUS_DEVICE_FAILED ((RNDIS_STATUS)0xC0010008L)
#define RNDIS_STATUS_MULTICAST_FULL ((RNDIS_STATUS)0xC0010009L)
#define RNDIS_STATUS_MULTICAST_EXISTS ((RNDIS_STATUS)0xC001000AL)
#define RNDIS_STATUS_MULTICAST_NOT_FOUND ((RNDIS_STATUS)0xC001000BL)
#define RNDIS_STATUS_REQUEST_ABORTED ((RNDIS_STATUS)0xC001000CL)
#define RNDIS_STATUS_RESET_IN_PROGRESS ((RNDIS_STATUS)0xC001000DL)
#define RNDIS_STATUS_CLOSING_INDICATING ((RNDIS_STATUS)0xC001000EL)
#define RNDIS_STATUS_NOT_SUPPORTED ((RNDIS_STATUS)STATUS_NOT_SUPPORTED)
#define RNDIS_STATUS_INVALID_PACKET ((RNDIS_STATUS)0xC001000FL)
#define RNDIS_STATUS_OPEN_LIST_FULL ((RNDIS_STATUS)0xC0010010L)
#define RNDIS_STATUS_ADAPTER_NOT_READY ((RNDIS_STATUS)0xC0010011L)
#define RNDIS_STATUS_ADAPTER_NOT_OPEN ((RNDIS_STATUS)0xC0010012L)
#define RNDIS_STATUS_NOT_INDICATING ((RNDIS_STATUS)0xC0010013L)
#define RNDIS_STATUS_INVALID_LENGTH ((RNDIS_STATUS)0xC0010014L)
#define RNDIS_STATUS_INVALID_DATA ((RNDIS_STATUS)0xC0010015L)
#define RNDIS_STATUS_BUFFER_TOO_SHORT ((RNDIS_STATUS)0xC0010016L)
#define RNDIS_STATUS_INVALID_OID ((RNDIS_STATUS)0xC0010017L)
#define RNDIS_STATUS_ADAPTER_REMOVED ((RNDIS_STATUS)0xC0010018L)
#define RNDIS_STATUS_UNSUPPORTED_MEDIA ((RNDIS_STATUS)0xC0010019L)
#define RNDIS_STATUS_GROUP_ADDRESS_IN_USE ((RNDIS_STATUS)0xC001001AL)
#define RNDIS_STATUS_FILE_NOT_FOUND ((RNDIS_STATUS)0xC001001BL)
#define RNDIS_STATUS_ERROR_READING_FILE ((RNDIS_STATUS)0xC001001CL)
#define RNDIS_STATUS_ALREADY_MAPPED ((RNDIS_STATUS)0xC001001DL)
#define RNDIS_STATUS_RESOURCE_CONFLICT ((RNDIS_STATUS)0xC001001EL)
#define RNDIS_STATUS_NO_CABLE ((RNDIS_STATUS)0xC001001FL)
#define RNDIS_STATUS_INVALID_SAP ((RNDIS_STATUS)0xC0010020L)
#define RNDIS_STATUS_SAP_IN_USE ((RNDIS_STATUS)0xC0010021L)
#define RNDIS_STATUS_INVALID_ADDRESS ((RNDIS_STATUS)0xC0010022L)
#define RNDIS_STATUS_VC_NOT_ACTIVATED ((RNDIS_STATUS)0xC0010023L)
#define RNDIS_STATUS_DEST_OUT_OF_ORDER ((RNDIS_STATUS)0xC0010024L)
#define RNDIS_STATUS_VC_NOT_AVAILABLE ((RNDIS_STATUS)0xC0010025L)
#define RNDIS_STATUS_CELLRATE_NOT_AVAILABLE ((RNDIS_STATUS)0xC0010026L)
#define RNDIS_STATUS_INCOMPATIBLE_QOS ((RNDIS_STATUS)0xC0010027L)
#define RNDIS_STATUS_AAL_PARAMS_UNSUPPORTED ((RNDIS_STATUS)0xC0010028L)
#define RNDIS_STATUS_NO_ROUTE_TO_DESTINATION ((RNDIS_STATUS)0xC0010029L)
#define RNDIS_STATUS_TOKEN_RING_OPEN_ERROR ((RNDIS_STATUS)0xC0011000L)

// Object Identifiers used by NdisRequest Query/Set Information

// General Objects

#define RNDIS_OID_GEN_SUPPORTED_LIST 0x00010101
#define RNDIS_OID_GEN_HARDWARE_STATUS 0x00010102
#define RNDIS_OID_GEN_MEDIA_SUPPORTED 0x00010103
#define RNDIS_OID_GEN_MEDIA_IN_USE 0x00010104
#define RNDIS_OID_GEN_MAXIMUM_LOOKAHEAD 0x00010105
#define RNDIS_OID_GEN_MAXIMUM_FRAME_SIZE 0x00010106
#define RNDIS_OID_GEN_LINK_SPEED 0x00010107
#define RNDIS_OID_GEN_TRANSMIT_BUFFER_SPACE 0x00010108
#define RNDIS_OID_GEN_RECEIVE_BUFFER_SPACE 0x00010109
#define RNDIS_OID_GEN_TRANSMIT_BLOCK_SIZE 0x0001010A
#define RNDIS_OID_GEN_RECEIVE_BLOCK_SIZE 0x0001010B
#define RNDIS_OID_GEN_VENDOR_ID 0x0001010C
#define RNDIS_OID_GEN_VENDOR_DESCRIPTION 0x0001010D
#define RNDIS_OID_GEN_CURRENT_PACKET_FILTER 0x0001010E
#define RNDIS_OID_GEN_CURRENT_LOOKAHEAD 0x0001010F
#define RNDIS_OID_GEN_DRIVER_VERSION 0x00010110
#define RNDIS_OID_GEN_MAXIMUM_TOTAL_SIZE 0x00010111
#define RNDIS_OID_GEN_PROTOCOL_OPTIONS 0x00010112
#define RNDIS_OID_GEN_MAC_OPTIONS 0x00010113
#define RNDIS_OID_GEN_MEDIA_CONNECT_STATUS 0x00010114
#define RNDIS_OID_GEN_MAXIMUM_SEND_PACKETS 0x00010115
#define RNDIS_OID_GEN_VENDOR_DRIVER_VERSION 0x00010116
#define RNDIS_OID_GEN_NETWORK_LAYER_ADDRESSES 0x00010118 // Set only
#define RNDIS_OID_GEN_TRANSPORT_HEADER_OFFSET 0x00010119 // Set only
#define RNDIS_OID_GEN_RECEIVE_SCALE_CAPABILITIES 0x00010203 // query only
#define RNDIS_OID_GEN_RECEIVE_SCALE_PARAMETERS 0x00010204 // query and set
#define RNDIS_OID_GEN_MAX_LINK_SPEED 0x00010206 // query only
#define RNDIS_OID_GEN_LINK_STATE 0x00010207 // query only
#define RNDIS_OID_GEN_LINK_PARAMETERS 0x00010208 // set only
#define RNDIS_OID_GEN_INTERRUPT_MODERATION 0x00010209 // query and set
#define RNDIS_OID_GEN_MACHINE_NAME 0x0001021A // set only
#define RNDIS_OID_GEN_RNDIS_CONFIG_PARAMETER 0x0001021B // Set only
#define RNDIS_OID_GEN_XMIT_OK 0x00020101
#define RNDIS_OID_GEN_RCV_OK 0x00020102
#define RNDIS_OID_GEN_XMIT_ERROR 0x00020103
#define RNDIS_OID_GEN_RCV_ERROR 0x00020104
#define RNDIS_OID_GEN_RCV_NO_BUFFER 0x00020105
#define RNDIS_OID_GEN_DIRECTED_BYTES_XMIT 0x00020201
#define RNDIS_OID_GEN_DIRECTED_FRAMES_XMIT 0x00020202
#define RNDIS_OID_GEN_MULTICAST_BYTES_XMIT 0x00020203
#define RNDIS_OID_GEN_MULTICAST_FRAMES_XMIT 0x00020204
#define RNDIS_OID_GEN_BROADCAST_BYTES_XMIT 0x00020205
#define RNDIS_OID_GEN_BROADCAST_FRAMES_XMIT 0x00020206
#define RNDIS_OID_GEN_DIRECTED_BYTES_RCV 0x00020207
#define RNDIS_OID_GEN_DIRECTED_FRAMES_RCV 0x00020208
#define RNDIS_OID_GEN_MULTICAST_BYTES_RCV 0x00020209
#define RNDIS_OID_GEN_MULTICAST_FRAMES_RCV 0x0002020A
#define RNDIS_OID_GEN_BROADCAST_BYTES_RCV 0x0002020B
#define RNDIS_OID_GEN_BROADCAST_FRAMES_RCV 0x0002020C
#define RNDIS_OID_GEN_RCV_CRC_ERROR 0x0002020D
#define RNDIS_OID_GEN_TRANSMIT_QUEUE_LENGTH 0x0002020E
#define RNDIS_OID_GEN_GET_TIME_CAPS 0x0002020F
#define RNDIS_OID_GEN_GET_NETCARD_TIME 0x00020210
#define RNDIS_OID_GEN_FRIENDLY_NAME 0x00020216
#define RNDIS_OID_GEN_BYTES_RCV 0x00020219
#define RNDIS_OID_GEN_BYTES_XMIT 0x0002021A
#define RNDIS_OID_GEN_RCV_DISCARDS 0x0002021B
#define RNDIS_OID_GEN_XMIT_DISCARDS 0x0002021C
#define RNDIS_OID_TCP_RSC_STATISTICS 0x0002021D

// 802.3 Objects (Ethernet)

#define RNDIS_OID_802_3_PERMANENT_ADDRESS 0x01010101
#define RNDIS_OID_802_3_CURRENT_ADDRESS 0x01010102
#define RNDIS_OID_802_3_MULTICAST_LIST 0x01010103
#define RNDIS_OID_802_3_MAXIMUM_LIST_SIZE 0x01010104
#define RNDIS_OID_802_3_MAC_OPTIONS 0x01010105 // deprecated
#define RNDIS_OID_OFFLOAD_ENCAPSULATION 0x0101010A
#define RNDIS_OID_802_3_ADD_MULTICAST_ADDRESS 0x01010208
#define RNDIS_OID_802_3_DELETE_MULTICAST_ADDRESS 0x01010209
#define RNDIS_OID_802_3_RCV_ERROR_ALIGNMENT 0x01020101
#define RNDIS_OID_802_3_XMIT_ONE_COLLISION 0x01020102
#define RNDIS_OID_802_3_XMIT_MORE_COLLISIONS 0x01020103
#define RNDIS_OID_802_3_XMIT_DEFERRED 0x01020201
#define RNDIS_OID_802_3_XMIT_MAX_COLLISIONS 0x01020202
#define RNDIS_OID_802_3_RCV_OVERRUN 0x01020203
#define RNDIS_OID_802_3_XMIT_UNDERRUN 0x01020204
#define RNDIS_OID_802_3_XMIT_HEARTBEAT_FAILURE 0x01020205
#define RNDIS_OID_802_3_XMIT_TIMES_CRS_LOST 0x01020206
#define RNDIS_OID_802_3_XMIT_LATE_COLLISIONS 0x01020207
// query only, handled by NDIS
#define RNDIS_OID_TCP_OFFLOAD_CURRENT_CONFIG 0xFC01020B
#define RNDIS_OID_TCP_OFFLOAD_PARAMETERS 0xFC01020C // set only
#define RNDIS_OID_TCP_OFFLOAD_HARDWARE_CAPABILITIES 0xFC01020D // query only
#define RNDIS_OID_TCP_CONNECTION_OFFLOAD_CURRENT_CONFIG 0xFC01020E // query only
// query only
#define RNDIS_OID_TCP_CONNECTION_OFFLOAD_HARDWARE_CAPABILITIES 0xFC01020F

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
#define REMOTE_NDIS_RESET_CMPLT 0x80000006
#define REMOTE_NDIS_KEEPALIVE_CMPLT 0x80000008
#define REMOTE_NDIS_SET_EX_CMPLT 0x80000009

// Reserved message type for private communication between lower-layer host
// driver and remote device, if necessary.
#define REMOTE_NDIS_BUS_MSG 0xff000001

// Defines for DeviceFlags in RNDIS_INITIALIZE_COMPLETE

#define RNDIS_DF_CONNECTIONLESS 0x00000001
#define RNDIS_DF_CONNECTION_ORIENTED 0x00000002
#define RNDIS_DF_RAW_DATA 0x00000004

// Remote NDIS medium types.

#define RNDIS_MEDIUM_802_3 0x00000000
#define RNDIS_MEDIUM_802_5 0x00000001
#define RNDIS_MEDIUM_FDDI 0x00000002
#define RNDIS_MEDIUM_WAN 0x00000003
#define RNDIS_MEDIUM_LOCAL_TALK 0x00000004
#define RNDIS_MEDIUM_ARCNET_RAW 0x00000006
#define RNDIS_MEDIUM_ARCNET878_2 0x00000007
#define RNDIS_MEDIUM_ATM 0x00000008
#define RNDIS_MEDIUM_WIRELESS_WAN 0x00000009
#define RNDIS_MEDIUM_IRDA 0x0000000a
#define RNDIS_MEDIUM_CO_WAN 0x0000000b
// Not a real medium, defined as an upper-bound
#define RNDIS_MEDIUM_MAX 0x0000000d

// Remote NDIS medium connection states.

#define RNDIS_MEDIA_STATE_CONNECTED 0x00000000
#define RNDIS_MEDIA_STATE_DISCONNECTED 0x00000001

// Remote NDIS version numbers

#define RNDIS_MAJOR_VERSION 0x00000001
#define RNDIS_MINOR_VERSION 0x00000000

// Ndis MAC option bits (OID_GEN_MAC_OPTIONS).

#define RNDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA 0x00000001
#define RNDIS_MAC_OPTION_RECEIVE_SERIALIZED 0x00000002
#define RNDIS_MAC_OPTION_TRANSFERS_NOT_PEND 0x00000004
#define RNDIS_MAC_OPTION_NO_LOOPBACK 0x00000008
#define RNDIS_MAC_OPTION_FULL_DUPLEX 0x00000010
#define RNDIS_MAC_OPTION_EOTX_INDICATION 0x00000020
#define RNDIS_MAC_OPTION_8021P_PRIORITY 0x00000040
#define RNDIS_MAC_OPTION_SUPPORTS_MAC_ADDRESS_OVERWRITE 0x00000080
#define RNDIS_MAC_OPTION_RECEIVE_AT_DPC 0x00000100
#define RNDIS_MAC_OPTION_8021Q_VLAN 0x00000200

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

// Values for ParameterType in ConfigParameterInfo

#define RNDIS_CONFIG_PARAM_TYPE_INTEGER 0
#define RNDIS_CONFIG_PARAM_TYPE_STRING 2

// Format of Information buffer passed in a SetRequest for the OID
// OID_GEN_RNDIS_CONFIG_PARAMETER.
typedef struct _RNDIS_CONFIG_PARAMETER_INFO
{
    HV_UINT32 ParameterNameOffset;
    HV_UINT32 ParameterNameLength;
    HV_UINT32 ParameterType; // RNDIS_CONFIG_PARAM_TYPE_*
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

// {C4E5E7D1-D748-4AFC-979D-683167910A55}
const HV_GUID VMBFS_IMC_INSTANCE_ID =
{
    0xC4E5E7D1,
    0xD748,
    0x4AFC,
    { 0x97, 0x9D, 0x68, 0x31, 0x67, 0x91, 0x0A, 0x55 }
};

// {C63C9BDF-5FA5-4208-B03F-6B458B365592}
const HV_GUID VMBFS_BOOT_INSTANCE_ID =
{
    0xC63C9BDF,
    0x5FA5,
    0x4208,
    { 0xB0, 0x3F, 0x6B, 0x45, 0x8B, 0x36, 0x55, 0x92 }
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
    HV_UINT32 RequestedVersion; // VMBFS_VERSION_*
} VMBFS_MESSAGE_VERSION_REQUEST, *PVMBFS_MESSAGE_VERSION_REQUEST;

typedef enum _VMBFS_STATUS_VERSION_RESPONSE
{
    VmbfsVersionSupported = 0,
    VmbfsVersionUnsupported = 1
} VMBFS_STATUS_VERSION_RESPONSE, *PVMBFS_STATUS_VERSION_RESPONSE;

typedef struct _VMBFS_MESSAGE_VERSION_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status; // VMBFS_STATUS_VERSION_RESPONSE
} VMBFS_MESSAGE_VERSION_RESPONSE, *PVMBFS_MESSAGE_VERSION_RESPONSE;

typedef struct _VMBFS_MESSAGE_GET_FILE_INFO
{
    VMBFS_MESSAGE_HEADER Header;
    HV_WCHAR FilePath[HV_ANYSIZE_ARRAY]; // UTF-16
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
    HV_UINT32 Status; // VMBFS_STATUS_FILE_RESPONSE
    HV_UINT32 Flags; // VMBFS_GET_FILE_INFO_FLAG_*
    HV_UINT64 FileSize;
} VMBFS_MESSAGE_GET_FILE_INFO_RESPONSE, *PVMBFS_MESSAGE_GET_FILE_INFO_RESPONSE;

typedef struct _VMBFS_MESSAGE_READ_FILE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 ByteCount;
    HV_UINT64 Offset;
    HV_WCHAR FilePath[HV_ANYSIZE_ARRAY]; // UTF-16
} VMBFS_MESSAGE_READ_FILE, *PVMBFS_MESSAGE_READ_FILE;

typedef struct _VMBFS_MESSAGE_READ_FILE_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status; // VMBFS_STATUS_FILE_RESPONSE
    HV_UINT8 Payload[HV_ANYSIZE_ARRAY]; // Data
} VMBFS_MESSAGE_READ_FILE_RESPONSE, *PVMBFS_MESSAGE_READ_FILE_RESPONSE;

typedef struct _VMBFS_MESSAGE_READ_FILE_RDMA
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Handle;
    HV_UINT32 ByteCount;
    HV_UINT64 FileOffset;
    HV_UINT64 TokenOffset;
    HV_WCHAR FilePath[HV_ANYSIZE_ARRAY]; // UTF-16
} VMBFS_MESSAGE_READ_FILE_RDMA, *PVMBFS_MESSAGE_READ_FILE_RDMA;

typedef struct _VMBFS_MESSAGE_READ_FILE_RDMA_RESPONSE
{
    VMBFS_MESSAGE_HEADER Header;
    HV_UINT32 Status; // VMBFS_STATUS_FILE_RESPONSE
    HV_UINT32 ByteCount;
} VMBFS_MESSAGE_READ_FILE_RDMA_RESPONSE, *PVMBFS_MESSAGE_READ_FILE_RDMA_RESPONSE;

#pragma pack(pop)

// *****************************************************************************
// Microsoft Hyper-V Integration Components
// - Microsoft Hyper-V Heartbeat
// - Microsoft Hyper-V Data Exchange
// - Microsoft Hyper-V Guest Shutdown
// - Microsoft Hyper-V Time Synchronization
// - Microsoft Hyper-V Volume Shadow Copy
// - Microsoft Hyper-V Remote Desktop Virtualization
//

// {57164F39-9115-4E78-AB55-382F3BD5422D}
const HV_GUID IC_HEARTBEAT_CLASS_ID =
{
    0x57164F39,
    0x9115,
    0x4E78,
    { 0xAB, 0x55, 0x38, 0x2F, 0x3B, 0xD5, 0x42, 0x2D }
};

// {A9A0F4E7-5A45-4D96-B827-8A841E8C03E6}
const HV_GUID IC_KVP_EXCHANGE_CLASS_ID =
{
    0xA9A0F4E7,
    0x5A45,
    0x4D96,
    { 0xB8, 0x27, 0x8A, 0x84, 0x1E, 0x8C, 0x03, 0xE6 }
};

// {242FF919-07DB-4180-9C2E-B86CB68C8C55}
const HV_GUID IC_KVP_EXCHANGE_INSTANCE_ID =
{
    0x242FF919,
    0x07DB,
    0x4180,
    { 0x9C, 0x2E, 0xB8, 0x6C, 0xB6, 0x8C, 0x8C, 0x55 }
};

// {0E0B6031-5213-4934-818B-38D90CED39DB}
const HV_GUID IC_SHUTDOWN_CLASS_ID =
{
    0x0E0B6031,
    0x5213,
    0x4934,
    { 0x81, 0x8B, 0x38, 0xD9, 0x0C, 0xED, 0x39, 0xDB }
};

// {B6650FF7-33BC-4840-8048-E0676786F393}
const HV_GUID IC_SHUTDOWN_INSTANCE_ID =
{
    0xB6650FF7,
    0x33BC,
    0x4840,
    { 0x80, 0x48, 0xE0, 0x67, 0x67, 0x86, 0xF3, 0x93 }
};

// {9527E630-D0AE-497B-ADCE-E80AB0175CAF}
const HV_GUID IC_TIMESYNC_CLASS_ID =
{
    0x9527E630,
    0xD0AE,
    0x497B,
    { 0xAD, 0xCE, 0xE8, 0x0A, 0xB0, 0x17, 0x5C, 0xAF }
};

// {2DD1CE17-079E-403C-B352-A1921EE207EE}
const HV_GUID IC_TIMESYNC_INSTANCE_ID =
{
    0x2DD1CE17,
    0x079E,
    0x403C,
    { 0xB3, 0x52, 0xA1, 0x92, 0x1E, 0xE2, 0x07, 0xEE }
};

// {35FA2E29-EA23-4236-96AE-3A6EBACBA440}
const HV_GUID IC_VSS_CLASS_ID =
{
    0x35FA2E29,
    0xEA23,
    0x4236,
    { 0x96, 0xAE, 0x3A, 0x6E, 0xBA, 0xCB, 0xA4, 0x40 }
};

// {276AACF4-AC15-426C-98DD-7521AD3F01FE}
const HV_GUID IC_RDV_CLASS_ID =
{
    0x276AACF4,
    0xAC15,
    0x426C,
    { 0x98, 0xDD, 0x75, 0x21, 0xAD, 0x3F, 0x01, 0xFE }
};

// Maximum message size between guest and host for IC devices.
#define IC_MAXIMUM_MESSAGE_SIZE 13312

typedef HV_UINT16 IC_VERSION_FIELD, *PIC_VERSION_FIELD;

// Protocol version.
typedef struct _IC_VERSION
{
    IC_VERSION_FIELD Major;
    IC_VERSION_FIELD Minor;
} IC_VERSION, *PIC_VERSION;

#define IC_VERSION_NULL { 0, 0 }

#define IC_FRAMEWORK_VERSION_1 { 1, 0 }
#define IC_FRAMEWORK_VERSION_3 { 3, 0 }

#define IC_KVP_EXCHANGE_VERSION_3 { 3, 0 }
#define IC_KVP_EXCHANGE_VERSION_4 { 4, 0 }
#define IC_KVP_EXCHANGE_VERSION_5 { 5, 0 }

#define IC_SHUTDOWN_VERSION_1 { 1, 0 }
#define IC_SHUTDOWN_VERSION_3 { 3, 0 }
#define IC_SHUTDOWN_VERSION_31 { 3, 1 }
#define IC_SHUTDOWN_VERSION_32 { 3, 2 }

#define IC_TIMESYNC_VERSION_1 { 1, 0 }
#define IC_TIMESYNC_VERSION_3 { 3, 0 }
#define IC_TIMESYNC_VERSION_4 { 4, 0 }

#define IC_VSS_VERSION_4 { 4, 0 }
#define IC_VSS_VERSION_5 { 5, 0 }
#define IC_VSS_VERSION_6 { 6, 0 }
#define IC_VSS_VERSION_7 { 7, 0 }

// Type of message
typedef enum _IC_FEATURE_IDX
{
    // Initial version negotiation between host and guest.
    ICFeatureVersionNegotiation = 0,
    // Heartbeat / check if alive.
    ICFeatureIdxHeartbeat = 1,
    // KVP exchange.
    ICFeatureIdxKvpExchange = 2,
    // Request shutdown.
    ICFeatureIdxShutdown = 3,
    // Synchronize time.
    ICFeatureIdxTimeSync = 4,
    // VSS
    ICFeatureIdxVss = 5,
    // RDV
    ICFeatureIdxRdv = 6,
    // Guest interface.
    ICFeatureIdxGuestInterface = 7,
    // VM Session.
    ICFeatureIdxVMSession = 8,
    ICFeatureCount = 9,
} IC_FEATURE_IDX, *PIC_FEATURE_IDX;

typedef HV_UINT16 IC_MSG_TYPE, *PIC_MSG_TYPE;

// Status code for a message response.

// Message was processed successfully. (S_OK)
#define IC_STATUS_SUCCESS 0x00000000
// There are no more items to process. (HRESULT_FROM_WIN32(ERROR_NO_MORE_ITEMS))
#define IC_STATUS_NO_MORE_ITEMS 0x80070103
// Generic failure. (E_FAIL)
#define IC_STATUS_FAIL 0x80004005
// The operation is not supported. (HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED))
#define IC_STATUS_NOT_SUPPORTED 0x80070032
// Not found. (WBEM_E_NOT_FOUND)
#define IC_STATUS_NOT_FOUND 0x80041002

typedef HV_UINT8 IC_MSG_TRANS_ID, * PIC_MSG_TRANS_ID;

// Flags for IC messages.
typedef HV_UINT8 IC_MSG_HDR_FLAG, * PIC_MSG_HDR_FLAG;

// Message expects a response.
#define IC_MSG_FLAG_TRANSACTION 0x01
// Message is a request.
#define IC_MSG_FLAG_REQUEST 0x02
// Message is a response.
#define IC_MSG_FLAG_RESPONSE 0x04

// Common message header for IC messages.
typedef struct _IC_MSG_HDR
{
    // Version of the IC framework.
    IC_VERSION ICVerFramework;
    // Type of message. (IC_FEATURE_IDX)
    IC_MSG_TYPE ICMsgType;
    // Version of message content.
    IC_VERSION ICVerMessage;
    // Size in bytes of the message.
    HV_UINT16 ICMsgSize;
    // Status code used for message response. (IC_STATUS_*)
    HV_UINT32 Status;
    // Transaction ID; should be matched by response message.
    IC_MSG_TRANS_ID ICTransactionId;
    // Message flags. (IC_MSG_FLAG_*)
    IC_MSG_HDR_FLAG ICFlags;
    // Reserved -- should be zero.
    HV_UINT8 RESERVED[2];
} IC_MSG_HDR, *PIC_MSG_HDR;

// Version negotiation message.
typedef struct _IC_MSG_NEGOTIATE
{
    // The number of supported framework versions, located directly after this
    // structure.
    HV_UINT16 ICFrameworkVersionCount;
    // The number of supported message versions, located after the framework
    // versions.
    HV_UINT16 ICMessageVersionCount;
    // Reserved -- must be zero.
    HV_UINT32 Reserved;
    IC_VERSION ICVersionData[HV_ANYSIZE_ARRAY];
} IC_MSG_NEGOTIATE, *PIC_MSG_NEGOTIATE;

// Current state of guest.
typedef enum _GUEST_APPLICATION_STATE
{
    // Guest is in an unknown state.
    GuestApplicationStateUnknown = 0,
    // Guest is healthy.
    GuestApplicationStateHealthy = 1,
    // Guest encountered a critical error.
    GuestApplicationStateCritical = 2,
    // Guest is no longer running.
    GuestApplicationStateStopped = 3,
} GUEST_APPLICATION_STATE, *PGUEST_APPLICATION_STATE;

// Heartbeat message from guest to host.
typedef struct _IC_HEARTBEAT_MSG_DATA
{
    // Incrementing sequence counter.
    HV_UINT64 SeqNum;
    // Current state of the guest.
    GUEST_APPLICATION_STATE ApplicationState;
    // Reserved.
    HV_UINT8 Reserved[4];
} IC_HEARTBEAT_MSG_DATA, *PIC_HEARTBEAT_MSG_DATA;

// The operation to perform.
typedef enum _IC_KVP_EXCHANGE_OPERATION
{
    // Get a value.
    ICKvpExchangeOperationGet = 0,
    // Set a value.
    ICKvpExchangeOperationSet = 1,
    // Delete a value.
    ICKvpExchangeOperationDelete = 2,
    // Enumerate values.
    ICKvpExchangeOperationEnumerate = 3,
    // Get IP address information.
    ICKvpExchangeOperationGetIpAddressInfo = 4,
    // Set IP address information.
    ICKvpExchangeOperationSetIpAddressInfo = 5,
    ICKvpExchangeOperationCount = 6,
} IC_KVP_EXCHANGE_OPERATION, *PIC_KVP_EXCHANGE_OPERATION;

// The pool to use for a value.
typedef enum _IC_KVP_EXCHANGE_POOL
{
    ICKvpExchangePoolExternal = 0,
    ICKvpExchangePoolGuest = 1,
    ICKvpExchangePoolAuto = 2,
    ICKvpExchangePoolAutoExternal = 3,
    // There is an "internal" pool defined in some places, but this is never
    // exchanged between host and guest.
} IC_KVP_EXCHANGE_POOL, *PIC_KVP_EXCHANGE_POOL;

// The header for KVP messages.
typedef struct _IC_KVP_EXCHANGE_MSG_HDR
{
    // The operation to perform. (IC_KVP_EXCHANGE_OPERATION)
    HV_UINT8 Operation;
    // The pool to use. (IC_KVP_EXCHANGE_POOL)
    HV_UINT8 Pool;
} IC_KVP_EXCHANGE_MSG_HDR, *PIC_KVP_EXCHANGE_MSG_HDR;

// The maximum key size, in bytes.
#define IC_KVP_EXCHANGE_MAX_KEY_BYTES 512
// The maximum value size, in bytes.
#define IC_KVP_EXCHANGE_MAX_VALUE_BYTES 2048

// The type of the value.
typedef enum _IC_KVP_EXCHANGE_VALUE_TYPE
{
    // A UTF-16 string. (REG_SZ)
    ICKvpExchangeValueTypeString = 1,
    // A UTF-16 string, with environment variables expanded. (REG_EXPAND_SZ)
    ICKvpExchangeValueTypeExpandString = 2,
    // A 32-bit integer. (REG_DWORD)
    ICKvpExchangeValueTypeDword = 4,
    // A 64-bit integer. (REG_QWORD)
    ICKvpExchangeValueTypeQword = 11,
} IC_KVP_EXCHANGE_VALUE_TYPE, *PIC_KVP_EXCHANGE_VALUE_TYPE;

// A value request or response.
typedef struct _IC_KVP_EXCHANGE_MSG_VALUE
{
    // The type of the value.
    IC_KVP_EXCHANGE_VALUE_TYPE ValueType;
    // The size of the key, in bytes (including the null terminator).
    HV_UINT32 KeySize;
    // The size of the value, in bytes.
    HV_UINT32 ValueSize;
    // The key, as a null-terminated UTF-16 string.
    HV_WCHAR Key[IC_KVP_EXCHANGE_MAX_KEY_BYTES / 2];
    // The value.
    HV_UINT8 Value[IC_KVP_EXCHANGE_MAX_VALUE_BYTES];
} IC_KVP_EXCHANGE_MSG_VALUE, *PIC_KVP_EXCHANGE_MSG_VALUE;

// A message to get or set a key-value pair.
typedef struct _IC_KVP_EXCHANGE_MSG_GET_SET
{
    // The value.
    IC_KVP_EXCHANGE_MSG_VALUE Value;
} IC_KVP_EXCHANGE_MSG_GET_SET, *PIC_KVP_EXCHANGE_MSG_GET_SET;

// A message to delete a key-value pair.
typedef struct _IC_KVP_EXCHANGE_MSG_DELETE
{
    // The size of the key, in bytes (including the null terminator).
    HV_UINT32 KeySize;
    // The key, as a null-terminated UTF-16 string.
    HV_WCHAR Key[IC_KVP_EXCHANGE_MAX_KEY_BYTES / 2];
} IC_KVP_EXCHANGE_MSG_DELETE, *PIC_KVP_EXCHANGE_MSG_DELETE;

// A message to enumerate key-value pairs.
typedef struct _IC_KVP_EXCHANGE_MSG_ENUMERATE
{
    // The index of the enumeration.
    HV_UINT32 Index;
    // The value.
    IC_KVP_EXCHANGE_MSG_VALUE Value;
} IC_KVP_EXCHANGE_MSG_ENUMERATE, *PIC_KVP_EXCHANGE_MSG_ENUMERATE;

// A get, set, enumerate, or delete message.
typedef struct _IC_KVP_EXCHANGE_MSG
{
    // The header.
    IC_KVP_EXCHANGE_MSG_HDR Header;
    // The body of the message. The actual message may start at a different
    // offset, depending on alignment.
    union
    {
        IC_KVP_EXCHANGE_MSG_GET_SET Get;
        IC_KVP_EXCHANGE_MSG_GET_SET Set;
        IC_KVP_EXCHANGE_MSG_DELETE Delete;
        IC_KVP_EXCHANGE_MSG_ENUMERATE Enumerate;
    };
} IC_KVP_EXCHANGE_MSG, *PIC_KVP_EXCHANGE_MSG;

// The address family of a network protocol, for specifying the scope of a
// request.
typedef enum _IC_KVP_EXCHANGE_ADDRESS_FAMILY
{
    // No protocol.
    ICKvpExchangeAddressFamilyNone = 0,
    // IPv4.
    ICKvpExchangeAddressFamilyIpv4 = 1,
    // IPv6.
    ICKvpExchangeAddressFamilyIpv6 = 2,
    // Both IPv4 and IPv6.
    ICKvpExchangeAddressFamilyIpv4v6 = 3,
} IC_KVP_EXCHANGE_ADDRESS_FAMILY, *PIC_KVP_EXCHANGE_ADDRESS_FAMILY;

// IP address information, in UTF-16 string form.
typedef struct _IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO
{
    // The adapter ID, as a null-terminated UTF-16 string.
    HV_WCHAR AdapterId[128];
    // The protocols this message applies to. (IC_KVP_EXCHANGE_ADDRESS_FAMILY)
    HV_UINT8 AddressFamily;
    // Whether DHCP is enabled for the adapter.
    HV_UINT8 DHCPEnabled;
    // The IP addresses, as a semicolon-delimited, null-terminated UTF-16
    // string.
    HV_WCHAR IPAddress[1024];
    // The subnets, as a semicolon-delimited, null-terminated UTF-16 string.
    HV_WCHAR Subnet[1024];
    // The gateways, as a semicolon-delimited, null-terminated UTF-16 string.
    HV_WCHAR Gateway[512];
    // The DNS server addresses, as a semicolon-delimited, null-terminated
    // UTF-16 string.
    HV_WCHAR DNSServerAddresses[1024];
} IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO, *PIC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO;

// The origin of an IP address.
typedef enum _IC_KVP_EXCHANGE_IP_ADDRESS_ORIGIN
{
    // Unknown origin.
    ICKvpExchangeIpAddressOriginUnknown = 0,
    // Non-static assignment (probably DHCP).
    ICKvpExchangeIpAddressOriginOther = 1,
    // Static assignment.
    ICKvpExchangeIpAddressOriginStatic = 2,
} IC_KVP_EXCHANGE_IP_ADDRESS_ORIGIN, * PIC_KVP_EXCHANGE_IP_ADDRESS_ORIGIN;

// An IPv4 address, encoded as four octets in network byte order.
typedef struct _IC_KVP_EXCHANGE_IPV4_ADDRESS
{
    HV_UINT8 Octets[4];
} IC_KVP_EXCHANGE_IPV4_ADDRESS, *PIC_KVP_EXCHANGE_IPV4_ADDRESS;

// An IPv6 address, encoded as sixteen octets in network byte order.
typedef struct _IC_KVP_EXCHANGE_IPV6_ADDRESS
{
    HV_UINT8 Octets[16];
} IC_KVP_EXCHANGE_IPV6_ADDRESS, *PIC_KVP_EXCHANGE_IPV6_ADDRESS;

// IP address information, in binary form.
typedef struct _IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY
{
    // The number of IPv4 addresses.
    HV_UINT32 IPv4AddressCount;
    // The number of IPv6 addresses.
    HV_UINT32 IPv6AddressCount;
    // The number of IPv4 gateways.
    HV_UINT32 IPv4GatewayCount;
    // The number of IPv6 gateways.
    HV_UINT32 IPv6GatewayCount;
    // The number of IPv4 DNS servers.
    HV_UINT32 IPv4DNSServerCount;
    // The number of IPv6 DNS servers.
    HV_UINT32 IPv6DNSServerCount;
    // The adapter ID, as a null-terminated UTF-16 string.
    HV_WCHAR AdapterId[128];
    // The protocols this message applies to. (IC_KVP_EXCHANGE_ADDRESS_FAMILY)
    HV_UINT8 AddressFamily;
    // Whether DHCP is enabled for the adapter.
    HV_UINT8 DHCPEnabled;
    // Zero padding.
    HV_UINT16 Padding;
    // The IPv4 addresses.
    IC_KVP_EXCHANGE_IPV4_ADDRESS IPv4Addresses[64];
    // The IPv6 addresses.
    IC_KVP_EXCHANGE_IPV6_ADDRESS IPv6Addresses[64];
    // The IPv4 subnets.
    IC_KVP_EXCHANGE_IPV4_ADDRESS IPv4Subnets[64];
    // The IPv6 subnets.
    HV_UINT32 IPv6Subnets[64];
    // The IPv4 gateways.
    IC_KVP_EXCHANGE_IPV4_ADDRESS IPv4Gateways[5];
    // The IPv6 gateways.
    IC_KVP_EXCHANGE_IPV6_ADDRESS IPv6Gateways[5];
    // The IPv4 DNS servers.
    IC_KVP_EXCHANGE_IPV4_ADDRESS IPv4DNSServers[64];
    // The IPv6 DNS servers.
    IC_KVP_EXCHANGE_IPV6_ADDRESS IPv6DNSServers[64];
    // The IPv4 and IPv6 address origins. This is flattened into a single array,
    // without gaps between the IPv4 and IPv6 addresses.
    // (IC_KVP_EXCHANGE_IP_ADDRESS_ORIGIN)
    HV_UINT16 IPAddressOrigins[128];
} IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY, *PIC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY;

// The message for exchanging IP address information.
typedef struct _IC_KVP_EXCHANGE_MSG2
{
    // The message header.
    IC_KVP_EXCHANGE_MSG_HDR Header;
    // The body of the message. The actual message may start at a different
    // offset, depending on alignment.
    union
    {
        IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO IpAddressInfo;
        IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY IpAddressInfoBinary;
    };
} IC_KVP_EXCHANGE_MSG2, *PIC_KVP_EXCHANGE_MSG2;

// Whether the shutdown operation is being forced.
#define IC_SHUTDOWN_FLAG_FORCE 0x1
// Flag indicating the shutdown behavior is guest restart.
#define IC_SHUTDOWN_FLAG_RESTART 0x2
// Flag indicating the shutdown behavior is guest hibernate.
#define IC_SHUTDOWN_FLAG_HIBERNATE 0x4

// Reason code for IC_SHUTDOWN_MSG_DATA.
// The value is as same as SHTDN_REASON_FLAG_PLANNED in Windows SDK.
#define IC_SHUTDOWN_REASON_FLAG_PLANNED 0x80000000

// The message for shutdown initiated from the host.
typedef struct _IC_SHUTDOWN_MSG_DATA
{
    // The shutdown reason.
    HV_UINT32 ReasonCode;
    // The maximum amount of time allotted to the guest to perform the shutdown.
    HV_UINT32 TimeoutInSeconds;
    // Flags for the shutdown request. (IC_SHUTDOWN_FLAG_*)
    HV_UINT32 Flags;
    // Friendly text string for the shutdown request.
    HV_UINT8 Message[2048];
} IC_SHUTDOWN_MSG_DATA, *PIC_SHUTDOWN_MSG_DATA;

// Flags for timesync messages.

// This is a sync message.
#define IC_TIMESYNC_FLAG_SYNC 0x1
// This is a sample message.
#define IC_TIMESYNC_FLAG_SAMPLE 0x2

#pragma pack(4)
// Timesync messages used before version 4.0.
typedef struct _IC_TIMESYNC_MSG_DATA
{
    // The wall clock time measured in the parent, in UTC (without leap
    // seconds), measured in 100ns units since 1 Jan 1601. (FILETIME)
    HV_UINT64 ParentTime;
    // Unused. (FILETIME)
    HV_UINT64 ChildTime;
    // The measured round trip time by the parent. (FILETIME)
    HV_UINT64 RoundTripTime;
    // Flags indicating the message's purpose.
    HV_UINT8 Flags;
    // Reserved.
    HV_UINT8 Reserved[3];
} IC_TIMESYNC_MSG_DATA, *PIC_TIMESYNC_MSG_DATA;
#pragma pack()

// Timesync messages used in version 4.0 and later.
typedef struct _IC_TIMESYNC_REFERENCE_MSG_DATA
{
    // The wall clock time measured in the parent, in UTC (without leap
    // seconds), measured in 100ns units since 1 Jan 1601. (FILETIME)
    HV_UINT64 ParentTime;
    // The VM reference time of the child, at the time the parent measured the
    // wall clock time.
    HV_UINT64 VmReferenceTime;
    // Flags indicating the message's purpose.
    HV_UINT8 Flags;
    // The NTP leap indicator.
    HV_UINT8 LeapFlags;
    // The NTP stratum.
    HV_UINT8 Stratum;
    // Reserved.
    HV_UINT8 Reserved[5];
} IC_TIMESYNC_REFERENCE_MSG_DATA, *PIC_TIMESYNC_REFERENCE_MSG_DATA;

#define IC_VSS_MAX_VHD_COUNT 260

typedef enum _IC_VSS_OPERATION
{
    ICVssOperationCreate = 0,
    ICVssOperationDelete = 1,
    ICVssOperationCheckHotBackup = 2,
    ICVssOperationGetDirectMappedDevicesInfo = 3,

    // Messages below this are only valid for message version >= 4.0

    ICVssOperationBackupComplete = 4,

    // Messages below this are only valid for message version >= 5.0

    ICVssOperationFreezeApplications = 5,
    ICVssOperationThawApplications = 6,
    ICVssOperationAutoRecover = 7,

    // Messages below this are only valid for message version >= 6.0

    ICVssOperationQueryGuestClusterInformation = 8,

    ICVssOperationCount = 9,
} IC_VSS_OPERATION, *PIC_VSS_OPERATION;

typedef struct _IC_VSS_MSG_HDR
{
    HV_UINT8 Operation; // IC_VSS_OPERATION
    HV_UINT8 Reserved[4];
} IC_VSS_MSG_HDR, *PIC_VSS_MSG_HDR;

typedef struct _IC_VSS_MSG_CHECK_HOT_BACKUP
{
    HV_UINT32 Flags;
} IC_VSS_MSG_CHECK_HOT_BACKUP, *PIC_VSS_MSG_CHECK_HOT_BACKUP;

typedef struct _IC_VSS_MSG_CREATE
{
    HV_GUID SnapshotSetId;
} IC_VSS_MSG_CREATE, *PIC_VSS_MSG_CREATE;

typedef struct _IC_VSS_MSG_CREATE_V2
{
    HV_GUID SnapshotSetId;
    HV_UINT32 BackupType;
} IC_VSS_MSG_CREATE_V2, *PIC_VSS_MSG_CREATE_V2;

typedef struct _IC_VSS_MSG_DELETE
{
    HV_GUID SnapshotSetId;
} IC_VSS_MSG_DELETE, *PIC_VSS_MSG_DELETE;

typedef struct _IC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO
{
    HV_UINT32 Flags;
} IC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO, *PIC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO;

typedef struct _IC_VSS_MSG_BACKUP_COMPLETE
{
    HV_UINT32 Flags;
} IC_VSS_MSG_BACKUP_COMPLETE, *PIC_VSS_MSG_BACKUP_COMPLETE;

typedef struct _IC_VSS_MSG_THAW_APPLICATIONS
{
    HV_UINT32 Flags;
} IC_VSS_MSG_THAW_APPLICATIONS, *PIC_VSS_MSG_THAW_APPLICATIONS;

typedef struct _IC_VSS_MSG
{
    IC_VSS_MSG_HDR Header;
    union
    {
        IC_VSS_MSG_DELETE Delete;
        IC_VSS_MSG_CHECK_HOT_BACKUP CheckHotBackup;
        IC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO DirectMapInfo;
        IC_VSS_MSG_BACKUP_COMPLETE BackupComplete;
        IC_VSS_MSG_CREATE_V2 CreateV2;
        IC_VSS_MSG_THAW_APPLICATIONS ThawApplications;
    } Body;
    HV_UINT8 Reserved[4];
} IC_VSS_MSG, *PIC_VSS_MSG;

typedef struct _IC_VSS_LUN_INFO
{
    HV_UINT8 BusType; // IC_VSS_LUN_INFO_BUS_TYPE
    HV_UINT8 Reserved[3];
    HV_GUID Controller;
    HV_UINT8 Port;
    HV_UINT8 Target;
    HV_UINT8 Lun;
    HV_UINT8 Reserved2;
} IC_VSS_LUN_INFO, *PIC_VSS_LUN_INFO;

typedef struct _IC_VSS_MSG2
{
    IC_VSS_MSG_HDR Header;
    HV_UINT32 BackupType;
    HV_UINT32 Flags;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO Luns[IC_VSS_MAX_VHD_COUNT];
} IC_VSS_MSG2, *PIC_VSS_MSG2;

typedef struct _IC_VSS_MSG2_EX
{
    IC_VSS_MSG_HDR Header;
    HV_UINT32 BackupType;
    HV_UINT32 Flags;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO Luns[IC_VSS_MAX_VHD_COUNT];
    IC_VSS_LUN_INFO ShadowLuns[IC_VSS_MAX_VHD_COUNT];
} IC_VSS_MSG2_EX, *PIC_VSS_MSG2_EX;

typedef struct _IC_VSS_MSG3
{
    IC_VSS_MSG_HDR Header;
    HV_GUID ClusterId;
    HV_UINT32 ClusterSize;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO SharedLuns[IC_VSS_MAX_VHD_COUNT];
    HV_UINT32 SharedLunStatus[IC_VSS_MAX_VHD_COUNT];
} IC_VSS_MSG3, *PIC_VSS_MSG3;

typedef struct _IC_VSS_MSG3_EX
{
    IC_VSS_MSG_HDR Header;
    HV_GUID ClusterId;
    HV_UINT32 ClusterSize;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO SharedLuns[IC_VSS_MAX_VHD_COUNT];
    HV_UINT32 SharedLunStatus[IC_VSS_MAX_VHD_COUNT];
    HV_UINT64 LastMoveTime;
} IC_VSS_MSG3_EX, *PIC_VSS_MSG3_EX;

// *****************************************************************************
// Unknown VMBus devices
//

// {3375BAF4-9E15-4B30-B765-67ACB10D607B}
const HV_GUID INHERITED_ACTIVATION_CLASS_ID =
{
    0x3375BAF4,
    0x9E15,
    0x4B30,
    { 0xB7, 0x65, 0x67, 0xAC, 0xB1, 0x0D, 0x60, 0x7B }
};

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4200) // zero length array
#pragma warning(default:4201) // nameless struct/union
#endif
#endif

#endif // !MILE_HYPERV_GUEST_PROTOCOLS
