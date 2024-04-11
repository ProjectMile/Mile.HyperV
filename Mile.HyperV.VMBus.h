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

#endif // !MILE_HYPERV_VMBUS
