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

// SynthvidError | 0

// SynthvidVersionRequest | 1

typedef struct _SYNTHVID_VERSION_REQUEST_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
} SYNTHVID_VERSION_REQUEST_MESSAGE, *PSYNTHVID_VERSION_REQUEST_MESSAGE;

// SynthvidVersionResponse | 2

typedef struct _SYNTHVID_VERSION_RESPONSE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    SYNTHVID_VERSION Version;
    HV_UINT8 IsAccepted;
    HV_UINT8 MaxVideoOutputs;
} SYNTHVID_VERSION_RESPONSE_MESSAGE, *PSYNTHVID_VERSION_RESPONSE_MESSAGE;

// SynthvidVramLocation | 3

// SynthvidVramLocationAck | 4

// SynthvidSituationUpdate | 5

// SynthvidSituationUpdateAck | 6

// SynthvidPointerPosition | 7

/* 694 */
struct __unaligned __declspec(align(2)) SYNTHVID_POINTER_POSITION_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 IsVisible;
    HV_UINT8 VideoOutput;
    int ImageX;
    int ImageY;
};

// SynthvidPointerShape | 8

/* 584 */
struct __unaligned __declspec(align(1)) SYNTHVID_POINTER_SHAPE_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 PartialIndex;
    HV_UINT8 CursorFlags;
    unsigned int WidthPixels;
    unsigned int HeightPixels;
    unsigned int HotspotX;
    unsigned int HotspotY;
    HV_UINT8 PixelData[1];
};

// SynthvidFeatureChange | 9

/* 695 */
struct SYNTHVID_FEATURE_CHANGE_MESSAGE_V2
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 IsDirtNeeded;
    HV_UINT8 IsPointerPositionUpdatesNeeded;
    HV_UINT8 IsPointerShapeUpdatesNeeded;
    HV_UINT8 IsVideoSituationUpdatesNeeded;
    HV_UINT8 EdidBlock[128];
};

// SynthvidDirt | 10

/* 681 */
struct __unaligned __declspec(align(2)) SYNTHVID_DIRT_MESSAGE
{
    SYNTHVID_MESSAGE_HEADER Header;
    HV_UINT8 VideoOutput;
    HV_UINT8 DirtCount;
    tagRECT Dirt[1];
};

// SynthvidBiosInfoRequest | 11

// SynthvidBiosInfoResponse | 12

// SynthvidSupportedResolutionsRequest | 13

// SynthvidSupportedResolutionsResponse | 14

// SynthvidCapabilityRequest | 15

// SynthvidCapabilityResponse | 16

#endif // !MILE_HYPERV_VMBUS
