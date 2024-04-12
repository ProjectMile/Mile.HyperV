/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.VMBus.h
 * PURPOSE:   Definition for Hyper-V VMBus devices
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef MILE_HYPERV_VMBUS
#define MILE_HYPERV_VMBUS

#include "Mile.HyperV.TLFS.h"

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif
#pragma warning(disable:4200) // zero length array
#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4324) // structure was padded due to __declspec(align())
#endif

typedef struct _HV_GUID
{
    HV_UINT32 Data1;
    HV_UINT16 Data2;
    HV_UINT16 Data3;
    HV_UINT8 Data4[8];
} HV_GUID, *PHV_GUID;

typedef struct _HV_RECT
{
    HV_INT32 Left;
    HV_INT32 Top;
    HV_INT32 Right;
    HV_INT32 Bottom;
} HV_RECT, *PHV_RECT;

// *****************************************************************************
// Microsoft Hyper-V Virtual Machine Bus
//

typedef enum _VMPIPE_PROTOCOL_MESSAGE_TYPE
{
    VmPipeMessageInvalid = 0,
    VmPipeMessageData = 1,
    VmPipeMessagePartial = 2,
    VmPipeMessageSetupGpaDirect = 3,
    VmPipeMessageTeardownGpaDirect = 4,
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
    ChannelMessageCount = 22,
} VMBUS_CHANNEL_MESSAGE_TYPE, *PVMBUS_CHANNEL_MESSAGE_TYPE;

typedef struct _VMBUS_CHANNEL_MESSAGE_HEADER
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
} VMBUS_CHANNEL_MESSAGE_HEADER, *PVMBUS_CHANNEL_MESSAGE_HEADER;

typedef struct _GPA_RANGE
{
    HV_UINT32 ByteCount;
    HV_UINT32 ByteOffset;
    HV_UINT64 PfnArray[ANYSIZE_ARRAY];
} GPA_RANGE, *PGPA_RANGE;

// ChannelMessageInvalid | 0

// ChannelMessageOfferChannel | 1

#pragma pack(1)
typedef struct _VMBUS_CHANNEL_OFFER_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_GUID InterfaceType;
    HV_GUID InterfaceInstance;
    HV_UINT64 Reserved;
    HV_UINT64 Reserved2;
    HV_UINT16 Flags;
    HV_UINT16 MmioMegabytes;
    HV_UINT8 UserDefined[120];
    HV_UINT16 SubChannelIndex;
    HV_UINT16 MmioMegabytesOptional;
    HV_UINT32 ChildRelId;
    HV_UINT8 MonitorId;
    HV_UINT8 MonitorAllocated : 1;
    HV_UINT8 Reserved4 : 7;
    union
    {
        HV_UINT8 Windows6Offset;
        struct
        {
            HV_UINT16 IsDedicatedInterrupt : 1;
            HV_UINT16 Reserved5 : 15;
        };
    };
    HV_UINT32 ConnectionId;
} VMBUS_CHANNEL_OFFER_CHANNEL, *PVMBUS_CHANNEL_OFFER_CHANNEL;
#pragma pack()

// ChannelMessageRescindChannelOffer | 2

typedef struct _VMBUS_CHANNEL_RESCIND_OFFER
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_RESCIND_OFFER, *PVMBUS_CHANNEL_RESCIND_OFFER;

// ChannelMessageRequestOffers | 3

// VMBUS_CHANNEL_MESSAGE_HEADER

// ChannelMessageAllOffersDelivered | 4

// VMBUS_CHANNEL_MESSAGE_HEADER

// ChannelMessageOpenChannel | 5

typedef struct _VMBUS_CHANNEL_OPEN_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
    HV_UINT32 OpenId;
    HV_UINT32 RingBufferGpadlHandle;
    HV_UINT32 TargetVp;
    HV_UINT32 DownstreamRingBufferPageOffset;
    HV_UINT8 UserData[120];
} VMBUS_CHANNEL_OPEN_CHANNEL, *PVMBUS_CHANNEL_OPEN_CHANNEL;

// ChannelMessageOpenChannelResult | 6

typedef struct _VMBUS_CHANNEL_OPEN_RESULT
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
    HV_UINT32 OpenId;
    HV_UINT32 Status;
} VMBUS_CHANNEL_OPEN_RESULT, *PVMBUS_CHANNEL_OPEN_RESULT;

// ChannelMessageCloseChannel | 7

typedef struct _VMBUS_CHANNEL_CLOSE_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_CLOSE_CHANNEL, *PVMBUS_CHANNEL_CLOSE_CHANNEL;

// ChannelMessageGpadlHeader | 8

#pragma pack(1)
typedef struct _VMBUS_CHANNEL_GPADL_HEADER
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
    HV_UINT16 RangeBufLen;
    HV_UINT16 RangeCount;
    GPA_RANGE Range[ANYSIZE_ARRAY];
} VMBUS_CHANNEL_GPADL_HEADER, *PVMBUS_CHANNEL_GPADL_HEADER;
#pragma pack()

// ChannelMessageGpadlBody | 9

typedef struct _VMBUS_CHANNEL_GPADL_BODY
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 MessageNumber;
    HV_UINT32 Gpadl;
    HV_UINT64 Pfn[ANYSIZE_ARRAY];
} VMBUS_CHANNEL_GPADL_BODY, *PVMBUS_CHANNEL_GPADL_BODY;

// ChannelMessageGpadlCreated | 10

typedef struct _VMBUS_CHANNEL_GPADL_CREATED
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
    HV_UINT32 CreationStatus;
} VMBUS_CHANNEL_GPADL_CREATED, *PVMBUS_CHANNEL_GPADL_CREATED;

// ChannelMessageGpadlTeardown | 11

typedef struct _VMBUS_CHANNEL_GPADL_TEARDOWN
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
    HV_UINT32 Gpadl;
} VMBUS_CHANNEL_GPADL_TEARDOWN, *PVMBUS_CHANNEL_GPADL_TEARDOWN;

// ChannelMessageGpadlTorndown | 12

typedef struct _VMBUS_CHANNEL_GPADL_TORNDOWN
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 Gpadl;
} VMBUS_CHANNEL_GPADL_TORNDOWN, *PVMBUS_CHANNEL_GPADL_TORNDOWN;

// ChannelMessageRelIdReleased | 13

typedef struct _VMBUS_CHANNEL_RELID_RELEASED
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChildRelId;
} VMBUS_CHANNEL_RELID_RELEASED, *PVMBUS_CHANNEL_RELID_RELEASED;

// ChannelMessageInitiateContact | 14

typedef struct _VMBUS_CHANNEL_INITIATE_CONTACT
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 VMBusVersionRequested;
    HV_UINT32 TargetMessageVp;
    HV_UINT64 InterruptPage;
    HV_UINT64 ParentToChildMonitorPageGpa;
    HV_UINT64 ChildToParentMonitorPageGpa;
} VMBUS_CHANNEL_INITIATE_CONTACT, *PVMBUS_CHANNEL_INITIATE_CONTACT;

// ChannelMessageVersionResponse | 15

typedef struct _VMBUS_CHANNEL_VERSION_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT8 VersionSupported;
    HV_UINT8 ConnectionState;
    HV_UINT8 Pad[2];
    HV_UINT32 SelectedVersion;
} VMBUS_CHANNEL_VERSION_RESPONSE, *PVMBUS_CHANNEL_VERSION_RESPONSE;

// ChannelMessageUnload | 16

// VMBUS_CHANNEL_MESSAGE_HEADER

// ChannelMessageUnloadComplete | 17

// VMBUS_CHANNEL_MESSAGE_HEADER

// ChannelMessageOpenReservedChannel | 18

typedef struct _VMBUS_CHANNEL_OPEN_RESERVED_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChannelId;
    HV_UINT32 TargetVp;
    HV_UINT32 TargetSint;
    HV_UINT32 RingBufferGpadl;
    HV_UINT32 DownstreamPageOffset;
} VMBUS_CHANNEL_OPEN_RESERVED_CHANNEL, *PVMBUS_CHANNEL_OPEN_RESERVED_CHANNEL;

// ChannelMessageCloseReservedChannel | 19

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChannelId;
    HV_UINT32 TargetVp;
    HV_UINT32 TargetSint;
} VMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL, *PVMBUS_CHANNEL_CLOSE_RESERVED_CHANNEL;

// ChannelMessageCloseReservedResponse | 20

typedef struct _VMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_UINT32 ChannelId;
} VMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE, *PVMBUS_CHANNEL_CLOSE_RESERVED_RESPONSE;

// ChannelMessageTlConnectRequest | 21

typedef struct _VMBUS_CHANNEL_TL_CONNECT_REQUEST
{
    VMBUS_CHANNEL_MESSAGE_TYPE MessageType;
    HV_UINT32 Padding;
    HV_GUID EndpointId;
    HV_GUID ServiceId;
} VMBUS_CHANNEL_TL_CONNECT_REQUEST, *PVMBUS_CHANNEL_TL_CONNECT_REQUEST;

typedef struct _VMRCB
{
    HV_UINT32 In;
    HV_UINT32 Out;
    HV_UINT32 InterruptMask;
    HV_UINT32 PendingSendSize;
    HV_UINT32 Reserved[12];
    union
    {
        HV_UINT32 Value;
        struct
        {
            HV_UINT32 SupportsPendingSendSize : 1;
        };
    } FeatureBits;
} VMRCB, *PVMRCB;

typedef enum _VMBUS_PACKET_TYPE
{
    VmbusPacketTypeInvalid = 0,
    VmbusPacketTypeDataInBand = 6,
    VmbusPacketTypeDataUsingTransferPages = 7,
    VmbusPacketTypeDataUsingGpaDirect = 9,
    VmbusPacketTypeCancelRequest = 10,
    VmbusPacketTypeCompletion = 11,
} VMBUS_PACKET_TYPE, *PVMBUS_PACKET_TYPE;

typedef struct _VMPACKET_DESCRIPTOR
{
    HV_UINT16 Type; // VMBUS_PACKET_TYPE
    HV_UINT16 DataOffset8;
    HV_UINT16 Length8;
    HV_UINT16 Flags;
    HV_UINT64 TransactionId;
} VMPACKET_DESCRIPTOR, *PVMPACKET_DESCRIPTOR;

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

typedef struct _VMDATA_GPA_DIRECT
{
    VMPACKET_DESCRIPTOR Descriptor;
    HV_UINT32 Reserved;
    HV_UINT32 RangeCount;
    GPA_RANGE Range[ANYSIZE_ARRAY];
} VMDATA_GPA_DIRECT, *PVMDATA_GPA_DIRECT;

// *****************************************************************************
// Microsoft Hyper-V Video
//

// {DA0A7802-E377-4AAC-8E77-0558EB1073F8}
const HV_GUID SYNTHVID_CONTROL_CLASS_ID =
{
    0xDA0A7802,
    0xE377,
    0x4AAC,
    { 0x8E, 0x77, 0x05, 0x58, 0xEB, 0x10, 0x73, 0xF8 }
};

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

typedef struct _SYNTHVID_MESSAGE_HEADER
{
    SYNTHVID_MESSAGE_TYPE Type;
    HV_UINT32 Size;
} SYNTHVID_MESSAGE_HEADER, *PSYNTHVID_MESSAGE_HEADER;

typedef enum _SYNTHVID_FEATURE
{
    SynthVidFeatureWin7Rtm = 0x00030000,
    SynthVidFeatureBasic = 0x00030000,
    SynthVidFeatureWin8Rtm = 0x00030002,
    SynthVidFeatureHighResolutions = 0x00030002,
    SynthVidFeatureSupportsReinit = 0x00030002,
    SynthVidFeatureWinBlue = 0x00030003,
    SynthVidFeatureQueryBiosInfo = 0x00030003,
    SynthVidFeatureWinThresholdM1 = 0x00030004,
    SynthVidFeatureResolutionSetByHost = 0x00030004,
    SynthVidFeatureWinThresholdM2 = 0x00030005,
    SynthVidFeatureLockOnDisconnect = 0x00030005,
} SYNTHVID_FEATURE, *PSYNTHVID_FEATURE;

typedef union _SYNTHVID_VERSION
{
    HV_UINT32 AsDWORD;
    struct
    {
        HV_UINT16 MajorVersion;
        HV_UINT16 MinorVersion;
    };
} SYNTHVID_VERSION, *PSYNTHVID_VERSION;

#pragma pack(1)
typedef struct _VIDEO_OUTPUT_SITUATION
{
    HV_UINT8 Active;
    HV_UINT32 PrimarySurfaceVramOffset;
    HV_UINT8 DepthBits;
    HV_UINT32 WidthPixels;
    HV_UINT32 HeightPixels;
    HV_UINT32 PitchBytes;
} VIDEO_OUTPUT_SITUATION, *PVIDEO_OUTPUT_SITUATION;
#pragma pack()

typedef struct _HVD_SCREEN_INFO
{
    HV_UINT16 Width;
    HV_UINT16 Height;
} HVD_SCREEN_INFO, *PHVD_SCREEN_INFO;

// SynthvidError | 0

// SynthvidVersionRequest | 1

typedef struct _SYNTHVID_VERSION_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
} SYNTHVID_VERSION_REQUEST_MESSAGE, *PSYNTHVID_VERSION_REQUEST_MESSAGE;

// SynthvidVersionResponse | 2

#pragma pack(1)
typedef struct _SYNTHVID_VERSION_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
    HV_UINT8 IsAccepted;
    HV_UINT8 MaxVideoOutputs;
} SYNTHVID_VERSION_RESPONSE_MESSAGE, *PSYNTHVID_VERSION_RESPONSE_MESSAGE;
#pragma pack()

// SynthvidVramLocation | 3

#pragma pack(1)
typedef struct _SYNTHVID_VRAM_LOCATION_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
    HV_UINT8 IsVramGpaAddressSpecified;
    HV_UINT64 VramGpaAddress;
} SYNTHVID_VRAM_LOCATION_MESSAGE, *PSYNTHVID_VRAM_LOCATION_MESSAGE;
#pragma pack()

// SynthvidVramLocationAck | 4

typedef struct _SYNTHVID_VRAM_LOCATION_ACK_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
} SYNTHVID_VRAM_LOCATION_ACK_MESSAGE, *PSYNTHVID_VRAM_LOCATION_ACK_MESSAGE;

// SynthvidSituationUpdate | 5

#pragma pack(1)
typedef struct _SYNTHVID_SITUATION_UPDATE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
    HV_UINT8 VideoOutputCount;
    VIDEO_OUTPUT_SITUATION VideoOutput[ANYSIZE_ARRAY];
} SYNTHVID_SITUATION_UPDATE_MESSAGE, *PSYNTHVID_SITUATION_UPDATE_MESSAGE;
#pragma pack()

// SynthvidSituationUpdateAck | 6

typedef struct _SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT64 UserContext;
} SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE, *PSYNTHVID_SITUATION_UPDATE_ACK_MESSAGE;

// SynthvidPointerPosition | 7

#pragma pack(1)
typedef struct _SYNTHVID_POINTER_POSITION_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 IsVisible;
    HV_UINT8 VideoOutput;
    HV_INT32 ImageX;
    HV_INT32 ImageY;
} SYNTHVID_POINTER_POSITION_MESSAGE, *PSYNTHVID_POINTER_POSITION_MESSAGE;
#pragma pack()

// SynthvidPointerShape | 8

#pragma pack(1)
typedef struct _SYNTHVID_POINTER_SHAPE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 PartialIndex;
    HV_UINT8 CursorFlags;
    HV_UINT32 WidthPixels;
    HV_UINT32 HeightPixels;
    HV_UINT32 HotspotX;
    HV_UINT32 HotspotY;
    HV_UINT8 PixelData[ANYSIZE_ARRAY];
} SYNTHVID_POINTER_SHAPE_MESSAGE, *PSYNTHVID_POINTER_SHAPE_MESSAGE;
#pragma pack()

// SynthvidFeatureChange | 9

typedef struct _SYNTHVID_FEATURE_CHANGE_MESSAGE_V2
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 IsDirtNeeded;
    HV_UINT8 IsPointerPositionUpdatesNeeded;
    HV_UINT8 IsPointerShapeUpdatesNeeded;
    HV_UINT8 IsVideoSituationUpdatesNeeded;
    HV_UINT8 EdidBlock[128];
} SYNTHVID_FEATURE_CHANGE_MESSAGE_V2, *PSYNTHVID_FEATURE_CHANGE_MESSAGE_V2;

// SynthvidDirt | 10

#pragma pack(1)
typedef struct _SYNTHVID_DIRT_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 VideoOutput;
    HV_UINT8 DirtCount;
    HV_RECT Dirt[ANYSIZE_ARRAY];
} SYNTHVID_DIRT_MESSAGE, *PSYNTHVID_DIRT_MESSAGE;
#pragma pack()

// SynthvidBiosInfoRequest | 11

typedef struct _SYNTHVID_BIOS_INFO_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
} SYNTHVID_BIOS_INFO_REQUEST_MESSAGE, *PSYNTHVID_BIOS_INFO_REQUEST_MESSAGE;

// SynthvidBiosInfoResponse | 12

typedef struct _SYNTHVID_BIOS_INFO_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT32 VmGeneration;
    HV_UINT32 ReservedInt32;
    HV_UINT64 ReservedInt64;
} SYNTHVID_BIOS_INFO_RESPONSE_MESSAGE, *PSYNTHVID_BIOS_INFO_RESPONSE_MESSAGE;

// SynthvidSupportedResolutionsRequest | 13

#pragma pack(1)
typedef struct _SYNTHVID_SUPPORTED_RESOLUTIONS_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 MaximumResolutionCount;
} SYNTHVID_SUPPORTED_RESOLUTIONS_REQUEST_MESSAGE, *PSYNTHVID_SUPPORTED_RESOLUTIONS_REQUEST_MESSAGE;
#pragma pack()

// SynthvidSupportedResolutionsResponse | 14

#pragma pack(1)
typedef struct _SYNTHVID_SUPPORTED_RESOLUTIONS_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 EdidBlock[128];
    HV_UINT8 ResolutionCount;
    HV_UINT8 DefaultResolutionIndex;
    HV_UINT8 IsStandard;
    HVD_SCREEN_INFO SupportedResolution[ANYSIZE_ARRAY];
} SYNTHVID_SUPPORTED_RESOLUTIONS_RESPONSE_MESSAGE, *PSYNTHVID_SUPPORTED_RESOLUTIONS_RESPONSE_MESSAGE;
#pragma pack()

// SynthvidCapabilityRequest | 15

typedef struct _SYNTHVID_CAPABILITY_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
} SYNTHVID_CAPABILITY_REQUEST_MESSAGE, *PSYNTHVID_CAPABILITY_REQUEST_MESSAGE;

// SynthvidCapabilityResponse | 16

typedef struct _SYNTHVID_CAPABILITY_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT32 LockOnDisconnect : 1;
    HV_UINT32 Reserved : 31;
    HV_UINT32 Reserved2[15];
} SYNTHVID_CAPABILITY_RESPONSE_MESSAGE, *PSYNTHVID_CAPABILITY_RESPONSE_MESSAGE;

// *****************************************************************************
// Microsoft Hyper-V Virtual Keyboard
//

// {F912AD6D-2B17-48EA-BD65-F927A61C7684}
const HV_GUID HK_CONTROL_CLASS_ID =
{
    0xF912AD6D,
    0x2B17,
    0x48EA,
    { 0xBD, 0x65, 0xF9, 0x27, 0xA6, 0x1C, 0x76, 0x84 }
};

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

// HkMessageProtocolRequest | 1

typedef struct _HK_MESSAGE_PROTOCOL_REQUEST
{
    HK_MESSAGE_HEADER Header;
    HV_UINT32 Version;
} HK_MESSAGE_PROTOCOL_REQUEST, *PHK_MESSAGE_PROTOCOL_REQUEST;

// HkMessageProtocolResponse | 2

typedef struct _HK_MESSAGE_PROTOCOL_RESPONSE
{
    HK_MESSAGE_HEADER Header;
    HV_UINT32 Accepted : 1;
    HV_UINT32 Reserved : 31;
} HK_MESSAGE_PROTOCOL_RESPONSE, *PHK_MESSAGE_PROTOCOL_RESPONSE;

// HkMessageEvent | 3

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

// HkMessageSetLedIndicators | 4

typedef struct _HK_MESSAGE_LED_INDICATORS_STATE
{
    HK_MESSAGE_HEADER Header;
    HV_UINT16 LedFlags;
} HK_MESSAGE_LED_INDICATORS_STATE, *PHK_MESSAGE_LED_INDICATORS_STATE;

// *****************************************************************************
// Microsoft Hyper-V Input
//

// {CFA8B69E-5B4A-4CC0-B98B-8BA1A1F3F95A}
const HV_GUID SYNTHHID_CONTROL_CLASS_ID =
{
    0xCFA8B69E,
    0x5B4A,
    0x4CC0,
    { 0xB9, 0x8B, 0x8B, 0xA1, 0xA1, 0xF3, 0xF9, 0x5A }
};

typedef enum _SYNTHHID_MESSAGE_TYPE
{
    SynthHidProtocolRequest = 0,
    SynthHidProtocolResponse = 1,
    SynthHidInitialDeviceInfo = 2,
    SynthHidInitialDeviceInfoAck = 3,
    SynthHidInputReport = 4,
    SynthHidMax = 5,
} SYNTHHID_MESSAGE_TYPE, *PSYNTHHID_MESSAGE_TYPE;

typedef struct _SYNTHHID_MESSAGE_HEADER
{
    SYNTHHID_MESSAGE_TYPE Type;
    HV_UINT32 Size;
} SYNTHHID_MESSAGE_HEADER, *PSYNTHHID_MESSAGE_HEADER;

typedef union _SYNTHHID_VERSION
{
    HV_UINT32 AsDWord;
    struct
    {
        HV_UINT16 Minor;
        HV_UINT16 Major;
    };
} SYNTHHID_VERSION, *PSYNTHHID_VERSION;

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
    HV_HID_DESCRIPTOR_DESC_LIST DescriptorList[ANYSIZE_ARRAY];
} HV_HID_DESCRIPTOR, *PHV_HID_DESCRIPTOR;
#pragma pack()

// SynthHidProtocolRequest | 0

typedef struct _SYNTHHID_PROTOCOL_REQUEST
{
    SYNTHHID_MESSAGE_HEADER Header;
    SYNTHHID_VERSION VersionRequested;
} SYNTHHID_PROTOCOL_REQUEST, *PSYNTHHID_PROTOCOL_REQUEST;

// SynthHidProtocolResponse | 1

#pragma pack(1)
typedef struct _SYNTHHID_PROTOCOL_RESPONSE
{
    SYNTHHID_MESSAGE_HEADER Header;
    SYNTHHID_VERSION VersionRequested;
    HV_UINT8 Approved;
} SYNTHHID_PROTOCOL_RESPONSE, *PSYNTHHID_PROTOCOL_RESPONSE;
#pragma pack()

// SynthHidInitialDeviceInfo | 2

#pragma pack(1)
typedef struct _SYNTHHID_DEVICE_INFO
{
    SYNTHHID_MESSAGE_HEADER Header;
    HV_HID_DEVICE_ATTRIBUTES HidDeviceAttributes;
    HV_UINT8 HidDescriptorInformation[ANYSIZE_ARRAY];
} SYNTHHID_DEVICE_INFO, *PSYNTHHID_DEVICE_INFO;
#pragma pack()

// SynthHidInitialDeviceInfoAck | 3

#pragma pack(1)
typedef struct _SYNTHHID_DEVICE_INFO_ACK
{
    SYNTHHID_MESSAGE_HEADER Header;
    HV_UINT8 Reserved;
} SYNTHHID_DEVICE_INFO_ACK, *PSYNTHHID_DEVICE_INFO_ACK;
#pragma pack()

// SynthHidInputReport | 4

#pragma pack(1)
typedef struct _SYNTHHID_MESSAGE
{
    SYNTHHID_MESSAGE_HEADER Header;
    HV_UINT8 Data[ANYSIZE_ARRAY];
} SYNTHHID_MESSAGE, *PSYNTHHID_MESSAGE;
#pragma pack()

// *****************************************************************************
// Microsoft Hyper-V SCSI Controller
//

// {BA6163D9-04A1-4D29-B605-72E2FFB1DC7F}
const HV_GUID VSTOR_CONTROL_CLASS_ID =
{
    0xBA6163D9,
    0x04A1,
    0x4D29,
    { 0xB6, 0x05, 0x72, 0xE2, 0xFF, 0xB1, 0xDC, 0x7F }
};

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
    VStorOperationMaximum = 15,
} VSTOR_PACKET_OPERATION, *PVSTOR_PACKET_OPERATION;

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
        HV_UINT8 Cdb[16];
        HV_UINT8 SenseDataEx[20];
        HV_UINT8 ReservedArray[20];
    };
    HV_UINT16 Reserve;
    HV_UINT8 QueueTag;
    HV_UINT8 QueueAction;
    HV_UINT32 SrbFlags;
    HV_UINT32 TimeOutValue;
    HV_UINT32 QueueSortKey;
} VMSCSI_REQUEST, *PVMSCSI_REQUEST;

typedef struct _VMSTORAGE_CHANNEL_PROPERTIES
{
    HV_UINT32 Reserved;
    HV_UINT16 MaximumSubChannelCount;
    HV_UINT16 Reserved2;
    HV_UINT32 Flags;
    HV_UINT32 MaxTransferBytes;
    HV_UINT64 Reserved3;
} VMSTORAGE_CHANNEL_PROPERTIES, *PVMSTORAGE_CHANNEL_PROPERTIES;

typedef struct _VMSTORAGE_PROTOCOL_VERSION
{
    HV_UINT16 MajorMinor;
    HV_UINT16 Reserved;
} VMSTORAGE_PROTOCOL_VERSION, *PVMSTORAGE_PROTOCOL_VERSION;

typedef struct _VMFC_WWN_PACKET
{
    HV_UINT8 PrimaryWwnActive;
    char Reserved1;
    HV_UINT16 Reserved2;
    char PrimaryPortWwn[8];
    char PrimaryNodeWwn[8];
    char SecondaryPortWwn[8];
    char SecondaryNodeWwn[8];
} VMFC_WWN_PACKET, *PVMFC_WWN_PACKET;

typedef struct _VSTOR_CLIENT_PROPERTIES
{
    HV_UINT32 AsyncNotifyCapable : 1;
    HV_UINT32 Reserved : 31;
} VSTOR_CLIENT_PROPERTIES, *PVSTOR_CLIENT_PROPERTIES;

typedef struct _VSTOR_NOTIFICATION_PACKET
{
    HV_UINT8 Lun;
    HV_UINT8 Target;
    HV_UINT8 Path;
    HV_UINT8 Flags;
} VSTOR_NOTIFICATION_PACKET, *PVSTOR_NOTIFICATION_PACKET;

#pragma pack(1)
typedef struct _VSTOR_PACKET
{
    VSTOR_PACKET_OPERATION Operation;
    HV_UINT32 Flags;
    HV_UINT32 Status;
    union
    {
        VMSCSI_REQUEST VmSrb;
        VMSTORAGE_CHANNEL_PROPERTIES StorageChannelProperties;
        VMSTORAGE_PROTOCOL_VERSION Version;
        VMFC_WWN_PACKET FcWwnPacket;
        HV_UINT16 SubChannelCount;
        VSTOR_CLIENT_PROPERTIES ClientProperties;
        VSTOR_NOTIFICATION_PACKET NotificationPacket;
        HV_UINT8 Buffer[52];
    };
} VSTOR_PACKET, *PVSTOR_PACKET;
#pragma pack()

// VStorOperationCompleteIo | 1

// VStorOperationRemoveDevice | 2

// VStorOperationExecuteSRB | 3

// VStorOperationResetLun | 4

// VStorOperationResetAdapter | 5

// VStorOperationResetBus | 6

// VStorOperationBeginInitialization | 7

// VStorOperationEndInitialization | 8

// VStorOperationQueryProtocolVersion | 9

// VStorOperationQueryProperties | 10

// VStorOperationEnumerateBus | 11

// VStorOperationFcHbaData | 12

// VStorOperationCreateSubChannels | 13

// VStorOperationEventNotification | 14

// *****************************************************************************
// Microsoft Hyper-V Network Adapter
//

// {F8615163-DF3E-46C5-913F-F2D2F965ED0E}
const HV_GUID NVSP_CONTROL_CLASS_ID =
{
    0xF8615163,
    0xDF3E,
    0x46C5,
    { 0x91, 0x3F, 0xF2, 0xD2, 0xF9, 0x65, 0xED, 0x0E }
};

typedef enum _NVSP_MESSAGE_TYPE
{
    NvspMessageTypeNone = 0,
    NvspMessageTypeInit = 1,
    NvspMessageTypeInitComplete = 2,
    NvspVersionMessageStart = 100,
    NvspMessage1TypeSendNdisVersion = 100,
    NvspMessage1TypeSendReceiveBuffer = 101,
    NvspMessage1TypeSendReceiveBufferComplete = 102,
    NvspMessage1TypeRevokeReceiveBuffer = 103,
    NvspMessage1TypeSendSendBuffer = 104,
    NvspMessage1TypeSendSendBufferComplete = 105,
    NvspMessage1TypeRevokeSendBuffer = 106,
    NvspMessage1TypeSendRNDISPacket = 107,
    NvspMessage1TypeSendRNDISPacketComplete = 108,
    NvspMessage1Max = 108,
    NvspMessage2TypeSendChimneyDelegatedBuffer = 109,
    NvspMessage2TypeSendChimneyDelegatedBufferComplete = 110,
    NvspMessage2TypeRevokeChimneyDelegatedBuffer = 111,
    NvspMessage2TypeResumeChimneyRXIndication = 112,
    NvspMessage2TypeTerminateChimney = 113,
    NvspMessage2TypeTerminateChimneyComplete = 114,
    NvspMessage2TypeIndicateChimneyEvent = 115,
    NvspMessage2TypeSendChimneyPacket = 116,
    NvspMessage2TypeSendChimneyPacketComplete = 117,
    NvspMessage2TypePostChimneyRecvRequest = 118,
    NvspMessage2TypePostChimneyRecvRequestComplete = 119,
    NvspMessage2TypeAllocateReceiveBufferDeprecated = 120,
    NvspMessage2TypeAllocateReceiveBufferCompleteDeprecated = 121,
    NvspMessage2TypeFreeReceiveBufferDeprecated = 122,
    NvspMessage2SendVmqRndisPacketDeprecated = 123,
    NvspMessage2SendVmqRndisPacketCompleteDeprecated = 124,
    NvspMessage2TypeSendNdisConfig = 125,
    NvspMessage2TypeAllocateChimneyHandle = 126,
    NvspMessage2TypeAllocateChimneyHandleComplete = 127,
    NvspMessage2Max = 127,
    NvspMessage4TypeSendVFAssociation = 128,
    NvspMessage4TypeSwitchDataPath = 129,
    NvspMessage4TypeUplinkConnectStateDeprecated = 130,
    NvspMessage4Max = 130,
    NvspMessage5TypeOidQueryEx = 131,
    NvspMessage5TypeOidQueryExComplete = 132,
    NvspMessage5TypeSubChannel = 133,
    NvspMessage5TypeSendIndirectionTable = 134,
    NvspMessage5Max = 134,
    NvspMessage6TypePdApi = 135,
    NvspMessage6TypePdPostBatch = 136,
    NvspMessage6Max = 136,
} NVSP_MESSAGE_TYPE, *PNVSP_MESSAGE_TYPE;

typedef struct _NVSP_MESSAGE_HEADER
{
    NVSP_MESSAGE_TYPE MessageType;
} NVSP_MESSAGE_HEADER, *PNVSP_MESSAGE_HEADER;

typedef enum _NVSP_STATUS
{
    NvspStatusNone = 0,
    NvspStatusSuccess = 1,
    NvspStatusFailure = 2,
    NvspStatusDeprecated1 = 3,
    NvspStatusDeprecated2 = 4,
    NvspStatusInvalidRndisPacket = 5,
    NvspStatusBusy = 6,
    NvspStatusProtocolVersionUnsupported = 7,
    NvspStatusMax = 8,
} NVSP_STATUS, *PNVSP_STATUS;

typedef struct _NVSP_1_RECEIVE_BUFFER_SECTION
{
    HV_UINT32 Offset;
    HV_UINT32 SubAllocationSize;
    HV_UINT32 NumSubAllocations;
    HV_UINT32 EndOffset;
} NVSP_1_RECEIVE_BUFFER_SECTION, *PNVSP_1_RECEIVE_BUFFER_SECTION;

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

typedef enum _NVSP_VM_DATA_PATH
{
    NvspDataPathSynthetic = 0,
    NvspDataPathVF = 1,
    NvspDataPathMax = 2,
} NVSP_VM_DATA_PATH, *PNVSP_VM_DATA_PATH;

// Definition from Windows Driver Kit
// Note: Add HV_ prefix to avoid conflict 
typedef struct _HV_NDIS_OBJECT_HEADER
{
    HV_UINT8 Type;
    HV_UINT8 Revision;
    HV_UINT16 Size;
} HV_NDIS_OBJECT_HEADER, *PHV_NDIS_OBJECT_HEADER;

typedef enum _NVSP_SUBCHANNEL_OPERATION
{
    NvspSubchannelNone = 0,
    NvspSubchannelAllocate = 1,
    NvspSubchannelMax = 2,
} NVSP_SUBCHANNEL_OPERATION, *PNVSP_SUBCHANNEL_OPERATION;

typedef enum _NVSP_6_MESSAGE_PD_API_OPERATION
{
    PdApiOpConfiguration = 0x1,
    PdApiOpSwitchDatapath = 0x2,
    PdApiOpOpenProvider = 0x3,
    PdApiOpCloseProvider = 0x4,
    PdApiOpCreateQueue = 0x5,
    PdApiOpFlushQueue = 0x6,
    PdApiOpFreeQueue = 0x7,
    PdApiOpAllocateCommonBuffer = 0x8,
    PdApiOpFreeCommonBuffer = 0x9,
    PdApiOpMax = 0xA,
} NVSP_6_MESSAGE_PD_API_OPERATION, *PNVSP_6_MESSAGE_PD_API_OPERATION;

// Definition from Windows Driver Kit
// Note: Add HV_ prefix to avoid conflict
typedef struct _HV_GROUP_AFFINITY
{
    HV_UINT32 Mask;
    HV_UINT16 Group;
    HV_UINT16 Reserved[3];
} HV_GROUP_AFFINITY, *PHV_GROUP_AFFINITY;

typedef struct _NVSP_6_PD_BUFFER
{
    HV_UINT32 RegionOffset;
    HV_UINT16 RegionId;
    HV_UINT16 IsPartial : 1;
    HV_UINT16 ReservedMbz : 15;
} NVSP_6_PD_BUFFER, *PNVSP_6_PD_BUFFER;

// NvspMessageTypeNone | 0

// NvspMessageTypeInit | 1

typedef struct _NVSP_MESSAGE_INIT
{
    union
    {
        HV_UINT32 ProtocolVersion;
        struct
        {
            HV_UINT16 MinorProtocolVersion;
            HV_UINT16 MajorProtocolVersion;
        };
    };
    HV_UINT32 ProtocolVersion2;
} NVSP_MESSAGE_INIT, *PNVSP_MESSAGE_INIT;

// NvspMessageTypeInitComplete | 2

typedef struct _NVSP_MESSAGE_INIT_COMPLETE
{
    HV_UINT32 Deprecated;
    HV_UINT32 MaximumMdlChainLength;
    NVSP_STATUS Status;
} NVSP_MESSAGE_INIT_COMPLETE, *PNVSP_MESSAGE_INIT_COMPLETE;

// NvspMessage1TypeSendNdisVersion | 100

typedef struct _NVSP_1_MESSAGE_SEND_NDIS_VERSION
{
    HV_UINT32 NdisMajorVersion;
    HV_UINT32 NdisMinorVersion;
} NVSP_1_MESSAGE_SEND_NDIS_VERSION, *PNVSP_1_MESSAGE_SEND_NDIS_VERSION;

// NvspMessage1TypeSendReceiveBuffer | 101

#pragma pack(1)
typedef struct _NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER
{
    HV_UINT32 GpadlHandle;
    HV_UINT16 Id;
} NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER, *PNVSP_1_MESSAGE_SEND_RECEIVE_BUFFER;
#pragma pack()

// NvspMessage1TypeSendReceiveBufferComplete | 102

typedef struct _NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE
{
    NVSP_STATUS Status;
    HV_UINT32 NumSections;
    NVSP_1_RECEIVE_BUFFER_SECTION Sections[ANYSIZE_ARRAY];
} NVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE, *PNVSP_1_MESSAGE_SEND_RECEIVE_BUFFER_COMPLETE;

// NvspMessage1TypeRevokeReceiveBuffer | 103

typedef struct _NVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER
{
    HV_UINT16 Id;
} NVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER, *PNVSP_1_MESSAGE_REVOKE_RECEIVE_BUFFER;

// NvspMessage1TypeSendSendBuffer | 104

#pragma pack(1)
typedef struct _NVSP_1_MESSAGE_SEND_SEND_BUFFER
{
    HV_UINT32 GpadlHandle;
    HV_UINT16 Id;
} NVSP_1_MESSAGE_SEND_SEND_BUFFER, *PNVSP_1_MESSAGE_SEND_SEND_BUFFER;
#pragma pack()

// NvspMessage1TypeSendSendBufferComplete | 105

typedef struct _NVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE
{
    NVSP_STATUS Status;
    HV_UINT32 SectionSize;
} NVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE, *PNVSP_1_MESSAGE_SEND_SEND_BUFFER_COMPLETE;

// NvspMessage1TypeRevokeSendBuffer | 106

typedef struct _NVSP_1_MESSAGE_REVOKE_SEND_BUFFER
{
    HV_UINT16 Id;
} NVSP_1_MESSAGE_REVOKE_SEND_BUFFER, *PNVSP_1_MESSAGE_REVOKE_SEND_BUFFER;

// NvspMessage1TypeSendRNDISPacket | 107

typedef struct _NVSP_1_MESSAGE_SEND_RNDIS_PACKET
{
    HV_UINT32 ChannelType;
    HV_UINT32 SendBufferSectionIndex;
    HV_UINT32 SendBufferSectionSize;
} NVSP_1_MESSAGE_SEND_RNDIS_PACKET, *PNVSP_1_MESSAGE_SEND_RNDIS_PACKET;

// NvspMessage1TypeSendRNDISPacketComplete | 108

typedef struct _NVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE
{
    NVSP_STATUS Status;
} NVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE, *PNVSP_1_MESSAGE_SEND_RNDIS_PACKET_COMPLETE;

// NvspMessage2TypeSendChimneyDelegatedBuffer | 109

// NvspMessage2TypeSendChimneyDelegatedBufferComplete | 110

// NvspMessage2TypeRevokeChimneyDelegatedBuffer | 111

// NvspMessage2TypeResumeChimneyRXIndication | 112

// NvspMessage2TypeTerminateChimney | 113

// NvspMessage2TypeTerminateChimneyComplete | 114

// NvspMessage2TypeIndicateChimneyEvent | 115

// NvspMessage2TypeSendChimneyPacket | 116

// NvspMessage2TypeSendChimneyPacketComplete | 117

// NvspMessage2TypePostChimneyRecvRequest | 118

// NvspMessage2TypePostChimneyRecvRequestComplete | 119

// NvspMessage2TypeAllocateReceiveBufferDeprecated | 120

// NvspMessage2TypeAllocateReceiveBufferCompleteDeprecated | 121

// NvspMessage2TypeFreeReceiveBufferDeprecated | 122

// NvspMessage2SendVmqRndisPacketDeprecated | 123

// NvspMessage2SendVmqRndisPacketCompleteDeprecated | 124

// NvspMessage2TypeSendNdisConfig | 125

typedef struct _NVSP_2_MESSAGE_SEND_NDIS_CONFIG
{
    HV_UINT32 MTU;
    HV_UINT32 Reserved;
    NVSP_2_NETVSC_CAPABILITIES Capabilities;
} NVSP_2_MESSAGE_SEND_NDIS_CONFIG, *PNVSP_2_MESSAGE_SEND_NDIS_CONFIG;

// NvspMessage2TypeAllocateChimneyHandle | 126

// NvspMessage2TypeAllocateChimneyHandleComplete | 127

// NvspMessage4TypeSendVFAssociation | 128

typedef struct _NVSP_4_MESSAGE_SEND_VF_ASSOCIATION
{
    HV_UINT32 VFAllocated;
    HV_UINT32 SerialNumber;
} NVSP_4_MESSAGE_SEND_VF_ASSOCIATION, *PNVSP_4_MESSAGE_SEND_VF_ASSOCIATION;

// NvspMessage4TypeSwitchDataPath | 129

typedef struct _NVSP_4_MESSAGE_SWITCH_DATA_PATH
{
    NVSP_VM_DATA_PATH ActiveDataPath;
} NVSP_4_MESSAGE_SWITCH_DATA_PATH, *PNVSP_4_MESSAGE_SWITCH_DATA_PATH;

// NvspMessage4TypeUplinkConnectStateDeprecated | 130

// NvspMessage5TypeOidQueryEx | 131

typedef struct _NVSP_5_MESSAGE_OID_QUERY_EX
{
    HV_NDIS_OBJECT_HEADER Header;
    HV_UINT32 Oid;
} NVSP_5_MESSAGE_OID_QUERY_EX, *PNVSP_5_MESSAGE_OID_QUERY_EX;

// NvspMessage5TypeOidQueryExComplete | 132

typedef struct _NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE
{
    NVSP_STATUS Status;
    union
    {
        HV_UINT32 BytesWritten;
        HV_UINT32 BytesNeeded;
    };
} NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE, *PNVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE;

// NvspMessage5TypeSubChannel | 133

typedef struct _NVSP_5_MESSAGE_SUBCHANNEL_REQUEST
{
    NVSP_SUBCHANNEL_OPERATION Operation;
    HV_UINT32 NumSubChannels;
} NVSP_5_MESSAGE_SUBCHANNEL_REQUEST, *PNVSP_5_MESSAGE_SUBCHANNEL_REQUEST;

typedef struct _NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE
{
    NVSP_STATUS Status;
    HV_UINT32 NumSubChannels;
} NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE, *PNVSP_5_MESSAGE_SUBCHANNEL_COMPLETE;

// NvspMessage5TypeSendIndirectionTable | 134

typedef struct _NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE
{
    HV_UINT32 TableEntryCount;
    HV_UINT32 TableOffset;
} NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE, *PNVSP_5_MESSAGE_SEND_INDIRECTION_TABLE;

// NvspMessage6TypePdApi | 135

#pragma pack(1)
typedef struct _NVSP_6_MESSAGE_PD_API_REQUEST
{
    NVSP_6_MESSAGE_PD_API_OPERATION Operation;
    union
    {
        struct
        {
            HV_INT64 MmioPhysicalAddress;
            HV_UINT32 MmioLength;
            HV_UINT16 NumPdQueues;
        } Configuration;
        struct
        {
            HV_UINT8 HostDatapathIsPacketDirect;
            HV_UINT8 GuestPacketDirectIsEnabled;
        } SwitchDatapath;
        struct
        {
            HV_UINT32 ProviderId;
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
#pragma pack(0)

#pragma pack(1)
typedef struct _NVSP_6_MESSAGE_PD_API_COMPLETE
{
    NVSP_6_MESSAGE_PD_API_OPERATION Operation;
    NVSP_STATUS Status;
    union
    {
        struct
        {
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
#pragma pack(0)

// NvspMessage6TypePdPostBatch | 136

typedef struct _NVSP_6_MESSAGE_PD_BATCH_MESSAGE
{
    NVSP_MESSAGE_HEADER Header;
    HV_UINT16 Count;
    HV_UINT16 GuestToHost : 1;
    HV_UINT16 IsReceive : 1;
    HV_UINT16 ReservedMbz : 14;
    NVSP_6_PD_BUFFER PdBuffer[];
} NVSP_6_MESSAGE_PD_BATCH_MESSAGE, *PNVSP_6_MESSAGE_PD_BATCH_MESSAGE;

typedef union _NVSP_MESSAGE_INIT_UBER
{
    NVSP_MESSAGE_INIT Init;
    NVSP_MESSAGE_INIT_COMPLETE InitComplete;
} NVSP_MESSAGE_INIT_UBER, *PNVSP_MESSAGE_INIT_UBER;

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
} NVSP_MESSAGE_1_UBER, *PNVSP_MESSAGE_1_UBER;

typedef union _NVSP_MESSAGE_2_UBER
{
    NVSP_2_MESSAGE_SEND_NDIS_CONFIG SendNdisConfig;
} NVSP_MESSAGE_2_UBER, *PNVSP_MESSAGE_2_UBER;

typedef union _NVSP_MESSAGE_4_UBER
{
    NVSP_4_MESSAGE_SEND_VF_ASSOCIATION VFAssociation;
    NVSP_4_MESSAGE_SWITCH_DATA_PATH SwitchDataPath;
} NVSP_MESSAGE_4_UBER, *PNVSP_MESSAGE_4_UBER;

typedef union _NVSP_MESSAGE_5_UBER
{
    NVSP_5_MESSAGE_OID_QUERY_EX OidQueryEx;
    NVSP_5_MESSAGE_OID_QUERY_EX_COMPLETE OidQueryExComplete;
    NVSP_5_MESSAGE_SUBCHANNEL_REQUEST SubChannelRequest;
    NVSP_5_MESSAGE_SUBCHANNEL_COMPLETE SubChannelRequestComplete;
    NVSP_5_MESSAGE_SEND_INDIRECTION_TABLE SendTable;
} NVSP_MESSAGE_5_UBER, *PNVSP_MESSAGE_5_UBER;

typedef union _NVSP_MESSAGE_6_UBER
{
    NVSP_6_MESSAGE_PD_API_REQUEST PdApiRequest;
    NVSP_6_MESSAGE_PD_API_COMPLETE PdApiComplete;
} NVSP_MESSAGE_6_UBER, *PNVSP_MESSAGE_6_UBER;

typedef union _NVSP_ALL_MESSAGES
{
    NVSP_MESSAGE_INIT_UBER InitMessages;
    NVSP_MESSAGE_1_UBER Version1Messages;
    NVSP_MESSAGE_2_UBER Version2Messages;
    NVSP_MESSAGE_4_UBER Version4Messages;
    NVSP_MESSAGE_5_UBER Version5Messages;
    NVSP_MESSAGE_6_UBER Version6Messages;
} NVSP_ALL_MESSAGES, *PNVSP_ALL_MESSAGES;

typedef struct _NVSP_MESSAGE
{
    NVSP_MESSAGE_HEADER Header;
    NVSP_ALL_MESSAGES Messages;
} NVSP_MESSAGE, *PNVSP_MESSAGE;

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4200) // zero length array
#pragma warning(default:4201) // nameless struct/union
#pragma warning(default:4324) // structure was padded due to __declspec(align())
#endif
#endif

#endif // !MILE_HYPERV_VMBUS
