/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.VMBus.h
 * PURPOSE:    Definition for Hyper-V VMBus devices
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

// References
// - Symbols in Windows version 10.0.14347.0's HyperVideo.sys
// - Symbols in Windows version 10.0.14347.0's VMBusHID.sys
// - Symbols in Windows version 10.0.14347.0's netvsc.sys
// - Symbols in Windows version 10.0.14347.0's fcvsc.sys
// - Symbols in Windows version 10.0.14347.0's icsvc.dll
// - Symbols in Windows version 10.0.14347.0's icsvcext.dll
// - Symbols in Windows version 10.0.19041.0's rdpcorets.dll
// - Symbols in Windows version 10.0.19041.0's vmuidevices.dll
// - Symbols in Windows version 10.0.19041.0's ntoskrnl.exe

#ifndef MILE_HYPERV_VMBUS
#define MILE_HYPERV_VMBUS

#include "Mile.HyperV.Guest.Protocols.h"
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

typedef struct _HV_RECT
{
    HV_INT32 Left;
    HV_INT32 Top;
    HV_INT32 Right;
    HV_INT32 Bottom;
} HV_RECT, *PHV_RECT;

// *****************************************************************************
// Microsoft Hyper-V Video
//

#define SYNTHVID_CONTROL_CLASS_ID SYNTHVID_CLASS_ID

typedef SYNTHVID_MESSAGE_TYPE _SYNTHVID_MESSAGE_TYPE;
typedef SYNTHVID_MESSAGE_TYPE *PSYNTHVID_MESSAGE_TYPE;

typedef enum _SYNTHVID_MESSAGE_TYPE_PRIVATE
{
    SynthvidSupportedResolutionsRequest = 13,
    SynthvidSupportedResolutionsResponse = 14,
    SynthvidCapabilityRequest = 15,
    SynthvidCapabilityResponse = 16,
    SynthvidPrivateMax = 17,
} SYNTHVID_MESSAGE_TYPE_PRIVATE, *PSYNTHVID_MESSAGE_TYPE_PRIVATE;

typedef SYNTHVID_MESSAGE_HEADER _SYNTHVID_MESSAGE_HEADER;

#define SYNTHVID_MAKE_VERSION(Major, Minor) ((Minor) << 16 | (Major))
#define SYNTHVID_MAKE_VERSION_MAJOR(Version) ((Version) & 0x0000FFFF)
#define SYNTHVID_MAKE_VERSION_MINOR(Version) (((Version) & 0xFFFF0000) >> 16)

#define SYNTHVID_VERSION_WIN7 SYNTHVID_MAKE_VERSION(3, 0)
#define SYNTHVID_VERSION_WIN8 SYNTHVID_MAKE_VERSION(3, 2)
#define SYNTHVID_VERSION_WINBLUE SYNTHVID_MAKE_VERSION(3, 3)
#define SYNTHVID_VERSION_WINTHRESHOLD_M1 SYNTHVID_MAKE_VERSION(3, 4)
#define SYNTHVID_VERSION_WINTHRESHOLD_M2 SYNTHVID_MAKE_VERSION(3, 5)
#define SYNTHVID_VERSION_WIN10 SYNTHVID_VERSION_WINTHRESHOLD_M2

#define SYNTHVID_MAKE_FEATURE(Version) ( \
    (SYNTHVID_MAKE_VERSION_MAJOR(Version) << 16) | \
    SYNTHVID_MAKE_VERSION_MINOR(Version))

#define SYNTHVID_FEATURE_WIN7 \
    SYNTHVID_MAKE_FEATURE(SYNTHVID_VERSION_WIN7)
#define SYNTHVID_FEATURE_WIN8 \
    SYNTHVID_MAKE_FEATURE(SYNTHVID_VERSION_WIN8)
#define SYNTHVID_FEATURE_WINBLUE \
    SYNTHVID_MAKE_FEATURE(SYNTHVID_VERSION_WINBLUE)
#define SYNTHVID_FEATURE_WINTHRESHOLD_M1 \
    SYNTHVID_MAKE_FEATURE(SYNTHVID_VERSION_WINTHRESHOLD_M1)
#define SYNTHVID_FEATURE_WINTHRESHOLD_M2 \
    SYNTHVID_MAKE_FEATURE(SYNTHVID_VERSION_WINTHRESHOLD_M2)

typedef enum _SYNTHVID_FEATURE
{
    SynthVidFeatureWin7Rtm = SYNTHVID_FEATURE_WIN7,
    SynthVidFeatureBasic = SynthVidFeatureWin7Rtm,
    SynthVidFeatureWin8Rtm = SYNTHVID_FEATURE_WIN8,
    SynthVidFeatureHighResolutions = SynthVidFeatureWin8Rtm,
    SynthVidFeatureSupportsReinit = SynthVidFeatureWin8Rtm,
    SynthVidFeatureWinBlue = SYNTHVID_FEATURE_WINBLUE,
    SynthVidFeatureQueryBiosInfo = SynthVidFeatureWinBlue,
    SynthVidFeatureWinThresholdM1 = SYNTHVID_FEATURE_WINTHRESHOLD_M1,
    SynthVidFeatureResolutionSetByHost = SynthVidFeatureWinThresholdM1,
    SynthVidFeatureWinThresholdM2 = SYNTHVID_FEATURE_WINTHRESHOLD_M2,
    SynthVidFeatureLockOnDisconnect = SynthVidFeatureWinThresholdM2,
} SYNTHVID_FEATURE, *PSYNTHVID_FEATURE;

typedef SYNTHVID_VERSION _SYNTHVID_VERSION;

typedef VIDEO_OUTPUT_SITUATION _VIDEO_OUTPUT_SITUATION;

typedef struct _HVD_SCREEN_INFO
{
    HV_UINT16 Width;
    HV_UINT16 Height;
} HVD_SCREEN_INFO, *PHVD_SCREEN_INFO;

// SynthvidError | 0

// SynthvidVersionRequest | 1

typedef SYNTHVID_VERSION_REQUEST_MESSAGE _SYNTHVID_VERSION_REQUEST_MESSAGE;

// SynthvidVersionResponse | 2

typedef SYNTHVID_VERSION_RESPONSE_MESSAGE _SYNTHVID_VERSION_RESPONSE_MESSAGE;

// SynthvidVramLocation | 3

typedef SYNTHVID_VRAM_LOCATION_MESSAGE _SYNTHVID_VRAM_LOCATION_MESSAGE;

// SynthvidVramLocationAck | 4

typedef SYNTHVID_VRAM_LOCATION_ACK_MESSAGE _SYNTHVID_VRAM_LOCATION_ACK_MESSAGE;

// SynthvidSituationUpdate | 5

typedef SYNTHVID_SITUATION_UPDATE_MESSAGE _SYNTHVID_SITUATION_UPDATE_MESSAGE;

// SynthvidSituationUpdateAck | 6

typedef SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE _SYNTHVID_SITUATION_UPDATE_ACK_MESSAGE;

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
    HV_UINT8 PixelData[HV_ANYSIZE_ARRAY];
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
    HV_RECT Dirt[HV_ANYSIZE_ARRAY];
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
    HVD_SCREEN_INFO SupportedResolution[HV_ANYSIZE_ARRAY];
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

#define HK_CONTROL_CLASS_ID HK_CLASS_ID

typedef HK_MESSAGE_TYPE *PHK_MESSAGE_TYPE;

#define HK_VERSION_MAJOR(Version) (((Version) & 0xFFFF0000) >> 16)
#define HK_VERSION_MINOR(Version) ((Version) & 0x0000FFFF)

#define HK_VERSION_CURRENT HK_VERSION_WIN8

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

#define SYNTHHID_CONTROL_CLASS_ID SYNTHHID_CLASS_ID

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

#define SYNTHHID_MAKE_VERSION(Major, Minor) ((Major) << 16 | (Minor))
#define SYNTHHID_VERSION_MAJOR(Version) (((Version) & 0xFFFF0000) >> 16)
#define SYNTHHID_VERSION_MINOR(Version) ((Version) & 0x0000FFFF)

#define SYNTHHID_VERSION_CURRENT SYNTHHID_MAKE_VERSION(2, 0)

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
    HV_HID_DESCRIPTOR_DESC_LIST DescriptorList[HV_ANYSIZE_ARRAY];
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
    HV_UINT8 HidDescriptorInformation[HV_ANYSIZE_ARRAY];
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
    HV_UINT8 Data[HV_ANYSIZE_ARRAY];
} SYNTHHID_MESSAGE, *PSYNTHHID_MESSAGE;
#pragma pack()

// *****************************************************************************
// Microsoft Hyper-V SCSI Controller
// Microsoft Hyper-V Fibre Channel HBA
//

// {2F9BCC4A-0069-4AF3-B76B-6FD0BE528CDA}
const HV_GUID VMFC_CLASS_ID =
{
    0x2F9BCC4A,
    0x0069,
    0x4AF3,
    { 0xB7, 0x6B, 0x6F, 0xD0, 0xBE, 0x52, 0x8C, 0xDA }
};

#define VMSCSI_CONTROL_CLASS_ID VMSCSI_CLASS_ID
#define VMFC_CONTROL_CLASS_ID VMFC_CLASS_ID

#define VSTOR_SCSI_CONTROL_CLASS_ID VMSCSI_CONTROL_CLASS_ID
#define VSTOR_FC_CONTROL_CLASS_ID VMFC_CONTROL_CLASS_ID

typedef VSTOR_PACKET_OPERATION _VSTOR_PACKET_OPERATION;
typedef VSTOR_PACKET_OPERATION *PVSTOR_PACKET_OPERATION;

#define VMSTORAGE_MAKE_VERSION VMSTOR_PROTOCOL_VERSION
#define VMSTORAGE_VERSION_MAJOR VMSTOR_PROTOCOL_MAJOR
#define VMSTORAGE_VERSION_MINOR VMSTOR_PROTOCOL_MINOR

#define VMSTORAGE_VERSION_WIN6 VMSTOR_PROTOCOL_VERSION_WIN6
#define VMSTORAGE_VERSION_WIN7 VMSTOR_PROTOCOL_VERSION_WIN7
#define VMSTORAGE_VERSION_WIN8 VMSTOR_PROTOCOL_VERSION_WIN8
#define VMSTORAGE_VERSION_WINBLUE VMSTOR_PROTOCOL_VERSION_BLUE
#define VMSTORAGE_VERSION_WIN10 VMSTOR_PROTOCOL_VERSION(6, 2)

// *****************************************************************************
// Microsoft Hyper-V Network Adapter
//

#define NVSP_CONTROL_CLASS_ID NVSP_CLASS_ID

typedef enum _NVSP_MESSAGE_TYPE_PRIVATE
{
    NvspMessage6TypePdApi = 135,
    NvspMessage6TypePdPostBatch = 136,
    NvspMessage6Max = 136,
} NVSP_MESSAGE_TYPE_PRIVATE, *PNVSP_MESSAGE_TYPE_PRIVATE;

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

#define NVSP_MAKE_VERSION NVSP_PROTOCOL_VERSION
#define NVSP_VERSION_MAJOR NVSP_PROTOCOL_MAJOR
#define NVSP_VERSION_MINOR NVSP_PROTOCOL_MINOR

#define NVSP_VERSION_1 NVSP_PROTOCOL_VERSION_1
#define NVSP_VERSION_2 NVSP_PROTOCOL_VERSION_2
#define NVSP_VERSION_4 NVSP_PROTOCOL_VERSION_4
#define NVSP_VERSION_5 NVSP_PROTOCOL_VERSION_5
#define NVSP_VERSION_6 NVSP_PROTOCOL_VERSION(6, 0)
#define NVSP_VERSION_61 NVSP_PROTOCOL_VERSION(6, 1)

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
#pragma pack()

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
#pragma pack()

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

typedef NVSP_MESSAGE_INIT_UBER *PNVSP_MESSAGE_INIT_UBER;

typedef NVSP_1_MESSAGE_UBER NVSP_MESSAGE_1_UBER, *PNVSP_MESSAGE_1_UBER;

typedef NVSP_2_MESSAGE_UBER NVSP_MESSAGE_2_UBER, *PNVSP_MESSAGE_2_UBER;

typedef NVSP_4_MESSAGE_UBER NVSP_MESSAGE_4_UBER, *PNVSP_MESSAGE_4_UBER;

typedef NVSP_5_MESSAGE_UBER NVSP_MESSAGE_5_UBER, *PNVSP_MESSAGE_5_UBER;

typedef union _NVSP_MESSAGE_6_UBER
{
    NVSP_6_MESSAGE_PD_API_REQUEST PdApiRequest;
    NVSP_6_MESSAGE_PD_API_COMPLETE PdApiComplete;
} NVSP_MESSAGE_6_UBER, *PNVSP_MESSAGE_6_UBER;

typedef NVSP_ALL_MESSAGES *PNVSP_ALL_MESSAGES;

typedef union _NVSP_ALL_MESSAGES_PRIVATE
{
    NVSP_MESSAGE_6_UBER Version6Messages;
} NVSP_ALL_MESSAGES_PRIVATE, *PNVSP_ALL_MESSAGES_PRIVATE;

typedef struct _NVSP_MESSAGE_PRIVATE
{
    NVSP_MESSAGE_HEADER Header;
    NVSP_ALL_MESSAGES_PRIVATE Messages;
} NVSP_MESSAGE_PRIVATE, *PNVSP_MESSAGE_PRIVATE;

// *****************************************************************************
// Microsoft Hyper-V Virtual PCI Bus
//

#define VPCI_CONTROL_CLASS_ID VPCI_CLASS_ID

// *****************************************************************************
// Microsoft Hyper-V Virtual Machine Bus File System
//

#define VMBFS_CONTROL_CLASS_ID VMBFS_CLASS_ID

// {C63C9BDF-5FA5-4208-B03F-6B458B365592}
const HV_GUID VMBFS_INSTANCE_ID =
{
    0xC63C9BDF,
    0x5FA5,
    0x4208,
    { 0xB0, 0x3F, 0x6B, 0x45, 0x8B, 0x36, 0x55, 0x92 }
};

// *****************************************************************************
// Microsoft Hyper-V Integration Components
// - Microsoft Hyper-V Heartbeat
// - Microsoft Hyper-V Data Exchange
// - Microsoft Hyper-V Guest Shutdown
// - Microsoft Hyper-V Time Synchronization
// - Microsoft Hyper-V Volume Shadow Copy
// - Microsoft Hyper-V Remote Desktop Virtualization
// - Microsoft Hyper-V Guest Service Interface
//

// {9722C3E7-8F86-456D-8B6C-6009DA4CCD0B}
const HV_GUID IC_NEGOTIATE_CLASS_ID =
{
    0x9722C3E7,
    0x8F86,
    0x456D,
    { 0x8B, 0x6C, 0x60, 0x09, 0xDA, 0x4C, 0xCD, 0x0B }
};

// {77B80A1A-C226-427B-B65B-DBA0DF85C812}
const HV_GUID IC_NEGOTIATE_INSTANCE_ID =
{
    0x77B80A1A,
    0xC226,
    0x427B,
    { 0xB6, 0x5B, 0xDB, 0xA0, 0xDF, 0x85, 0xC8, 0x12 }
};

// {57164F39-9115-4E78-AB55-382F3BD5422D}
const HV_GUID IC_HEARTBEAT_CLASS_ID =
{
    0x57164F39,
    0x9115,
    0x4E78,
    { 0xAB, 0x55, 0x38, 0x2F, 0x3B, 0xD5, 0x42, 0x2D }
};

// {FD149E91-82E0-4A7D-AFA6-2A4166CBD7C0}
const HV_GUID IC_HEARTBEAT_INSTANCE_ID =
{
    0xFD149E91,
    0x82E0,
    0x4A7D,
    { 0xAF, 0xA6, 0x2A, 0x41, 0x66, 0xCB, 0xD7, 0xC0 }
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

// {2450EE40-33BF-4FBD-892E-9FB06E9214CF}
const HV_GUID IC_VSS_INSTANCE_ID =
{
    0x2450EE40,
    0x33BF,
    0x4FBD,
    { 0x89, 0x2E, 0x9F, 0xB0, 0x6E, 0x92, 0x14, 0xCF }
};

// {276AACF4-AC15-426C-98DD-7521AD3F01FE}
const HV_GUID IC_RDV_CLASS_ID =
{
    0x276AACF4,
    0xAC15,
    0x426C,
    { 0x98, 0xDD, 0x75, 0x21, 0xAD, 0x3F, 0x01, 0xFE }
};

// {F5BEE29C-1741-4AAD-A4C2-8FDEDB46DCC2}
const HV_GUID IC_RDV_INSTANCE_ID =
{
    0xF5BEE29C,
    0x1741,
    0x4AAD,
    { 0xA4, 0xC2, 0x8F, 0xDE, 0xDB, 0x46, 0xDC, 0xC2 }
};

// {34D14BE3-DEE4-41C8-9AE7-6B174977C192}
const HV_GUID IC_GUESTSVC_CLASS_ID =
{
    0x34D14BE3,
    0xDEE4,
    0x41C8,
    { 0x9A, 0xE7, 0x6B, 0x17, 0x49, 0x77, 0xC1, 0x92 }
};

// {EB765408-105F-49B6-B4AA-C123B64D17D4}
const HV_GUID IC_GUESTSVC_INSTANCE_ID =
{
    0xEB765408,
    0x105F,
    0x49B6,
    { 0xB4, 0xAA, 0xC1, 0x23, 0xB6, 0x4D, 0x17, 0xD4 }
};

#define IC_NEGOTIATE_CONTROL_CLASS_ID IC_NEGOTIATE_CLASS_ID
#define IC_HEARTBEAT_CONTROL_CLASS_ID IC_HEARTBEAT_CLASS_ID
#define IC_KVP_EXCHANGE_CONTROL_CLASS_ID IC_KVP_EXCHANGE_CLASS_ID
#define IC_SHUTDOWN_CONTROL_CLASS_ID IC_SHUTDOWN_CLASS_ID
#define IC_TIMESYNC_CONTROL_CLASS_ID IC_TIMESYNC_CLASS_ID
#define IC_VSS_CONTROL_CLASS_ID IC_VSS_CLASS_ID
#define IC_RDV_CONTROL_CLASS_ID IC_RDV_CLASS_ID
#define IC_GUESTSVC_CONTROL_CLASS_ID IC_GUESTSVC_CLASS_ID

typedef HV_UINT16 IC_VERSION_FIELD, *PIC_VERSION_FIELD;

typedef struct _IC_VERSION
{
    IC_VERSION_FIELD Major;
    IC_VERSION_FIELD Minor;
} IC_VERSION, *PIC_VERSION;

#define IC_VERSION_NULL { 0, 0 }

#define IC_FRAMEWORK_VERSION_1 { 1, 0 }
#define IC_FRAMEWORK_VERSION_3 { 3, 0 }

#define IC_HEARTBEAT_VERSION_3 { 3, 0 }
#define IC_HEARTBEAT_VERSION_31 { 3, 1 }

#define IC_KVP_EXCHANGE_VERSION_3 { 3, 0 }
#define IC_KVP_EXCHANGE_VERSION_4 { 4, 0 }
#define IC_KVP_EXCHANGE_VERSION_5 { 5, 0 }

#define IC_SHUTDOWN_VERSION_1 { 1, 0 }
#define IC_SHUTDOWN_VERSION_3 { 3, 0 }
#define IC_SHUTDOWN_VERSION_31 { 3, 1 }

#define IC_TIMESYNC_VERSION_1 { 1, 0 }
#define IC_TIMESYNC_VERSION_3 { 3, 0 }
#define IC_TIMESYNC_VERSION_4 { 4, 0 }

#define IC_VSS_VERSION_6 { 6, 0 }
#define IC_VSS_VERSION_7 { 7, 0 }

#define IC_RDV_VERSION_1 { 1, 0 }
#define IC_RDV_VERSION_3 { 3, 0 }

#define IC_GUESTIFACE_VERSION_11 { 1, 1 }

typedef enum _IC_FEATURE_IDX
{
    ICFeatureVersionNegotiation = 0,
    ICFeatureIdxHeartbeat = 1,
    ICFeatureIdxKvpExchange = 2,
    ICFeatureIdxShutdown = 3,
    ICFeatureIdxTimeSync = 4,
    ICFeatureIdxVss = 5,
    ICFeatureIdxRdv = 6,
    ICFeatureIdxGuestInterface = 7,
    ICFeatureIdxVMSession = 8,
    ICFeatureCount = 9,
} IC_FEATURE_IDX, *PIC_FEATURE_IDX;

typedef HV_UINT16 IC_MSG_TYPE, *PIC_MSG_TYPE;

typedef HV_UINT8 IC_MSG_TRANS_ID, *PIC_MSG_TRANS_ID;

typedef HV_UINT8 IC_MSG_HDR_FLAG, *PIC_MSG_HDR_FLAG;

typedef struct _IC_MSG_HDR
{
    IC_VERSION ICVerFramework;
    IC_MSG_TYPE ICMsgType; // IC_FEATURE_IDX
    IC_VERSION ICVerMessage;
    HV_UINT16 ICMsgSize;
    HV_UINT32 Status;
    IC_MSG_TRANS_ID ICTransactionId;
    IC_MSG_HDR_FLAG ICFlags;
    HV_UINT8 RESERVED[2];
} IC_MSG_HDR, *PIC_MSG_HDR;

typedef enum _GUEST_APPLICATION_STATE
{
    GuestApplicationStateUnknown = 0,
    GuestApplicationStateHealthy = 1,
    GuestApplicationStateCritical = 2,
} GUEST_APPLICATION_STATE, *PGUEST_APPLICATION_STATE;

typedef enum _IC_KVP_EXCHANGE_OPERATION
{
    ICKvpExchangeOperationGet = 0,
    ICKvpExchangeOperationSet = 1,
    ICKvpExchangeOperationDelete = 2,
    ICKvpExchangeOperationEnumerate = 3,
    ICKvpExchangeOperationGetIpAddressInfo = 4,
    ICKvpExchangeOperationSetIpAddressInfo = 5,
    ICKvpExchangeOperationCount = 6,
} IC_KVP_EXCHANGE_OPERATION, *PIC_KVP_EXCHANGE_OPERATION;

typedef struct _IC_KVP_EXCHANGE_MSG_HDR
{
    HV_UINT8 Operation; // IC_KVP_EXCHANGE_OPERATION
    HV_UINT8 Pool;
} IC_KVP_EXCHANGE_MSG_HDR, *PIC_KVP_EXCHANGE_MSG_HDR;

typedef struct _IC_KVP_EXCHANGE_MSG_VALUE
{
    HV_UINT32 ValueType;
    HV_UINT32 KeySize;
    HV_UINT32 ValueSize;
    HV_UINT8 Key[512];
    HV_UINT8 Value[2048];
} IC_KVP_EXCHANGE_MSG_VALUE, *PIC_KVP_EXCHANGE_MSG_VALUE;

typedef struct _IC_KVP_EXCHANGE_MSG_GET
{
    IC_KVP_EXCHANGE_MSG_VALUE Value;
} IC_KVP_EXCHANGE_MSG_GET, *PIC_KVP_EXCHANGE_MSG_GET;

typedef struct _IC_KVP_EXCHANGE_MSG_SET
{
    IC_KVP_EXCHANGE_MSG_VALUE Value;
} IC_KVP_EXCHANGE_MSG_SET, *PIC_KVP_EXCHANGE_MSG_SET;

typedef struct _IC_KVP_EXCHANGE_MSG_DELETE
{
    HV_UINT32 KeySize;
    HV_UINT8 Key[512];
} IC_KVP_EXCHANGE_MSG_DELETE, *PIC_KVP_EXCHANGE_MSG_DELETE;

typedef struct _IC_KVP_EXCHANGE_MSG_ENUMERATE
{
    HV_UINT32 Index;
    IC_KVP_EXCHANGE_MSG_VALUE Value;
} IC_KVP_EXCHANGE_MSG_ENUMERATE, *PIC_KVP_EXCHANGE_MSG_ENUMERATE;

typedef struct _IC_KVP_EXCHANGE_IP_ADDRESS_VALUE
{
    HV_WCHAR AdapterId[128];
    HV_UINT8 AddressFamily;
    HV_UINT8 DHCPEnabled;
    HV_WCHAR IPAddress[1024];
    HV_WCHAR Subnet[1024];
    HV_WCHAR Gateway[512];
    HV_WCHAR DNSServerAddresses[1024];
} IC_KVP_EXCHANGE_IP_ADDRESS_VALUE, *PIC_KVP_EXCHANGE_IP_ADDRESS_VALUE;

typedef struct _IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO
{
    IC_KVP_EXCHANGE_MSG_HDR Header;
    IC_KVP_EXCHANGE_IP_ADDRESS_VALUE Value;
} IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO, *PIC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO;

typedef struct _IC_KVP_EXCHANGE_IP_ADDRESS_BINARY_HEADER
{
    HV_UINT32 IPv4AddressCount;
    HV_UINT32 IPv6AddressCount;
    HV_UINT32 IPv4GatewayCount;
    HV_UINT32 IPv6GatewayCount;
    HV_UINT32 IPv4DNSServerCount;
    HV_UINT32 IPv6DNSServerCount;
} IC_KVP_EXCHANGE_IP_ADDRESS_BINARY_HEADER, *PIC_KVP_EXCHANGE_IP_ADDRESS_BINARY_HEADER;

typedef struct _IC_KVP_EXCHANGE_IP_ADDRESS_VALUE_BINARY
{
    IC_KVP_EXCHANGE_IP_ADDRESS_BINARY_HEADER Header;
    HV_WCHAR AdapterId[128];
    HV_UINT8 AddressFamily;
    HV_UINT8 DHCPEnabled;
    HV_UINT32 IPv4Addresses[64];
    HV_IPV6_ADDRESS IPv6Addresses[64];
    HV_UINT32 IPv4Subnets[64];
    HV_UINT32 IPv6Subnets[64];
    HV_UINT32 IPv4Gateways[5];
    HV_IPV6_ADDRESS IPv6Gateways[5];
    HV_UINT32 IPv4DNSServers[64];
    HV_IPV6_ADDRESS IPv6DNSServers[64];
    HV_UINT16 IPAddressOrigins[128];
} IC_KVP_EXCHANGE_IP_ADDRESS_VALUE_BINARY, *PIC_KVP_EXCHANGE_IP_ADDRESS_VALUE_BINARY;

typedef struct _IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY
{
    IC_KVP_EXCHANGE_MSG_HDR Header;
    IC_KVP_EXCHANGE_IP_ADDRESS_VALUE_BINARY Value;
} IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY, *PIC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY;

typedef enum _IC_VSS_OPERATION
{
    ICVssOperationCreate = 0,
    ICVssOperationDelete = 1,
    ICVssOperationCheckHotBackup = 2,
    ICVssOperationGetDirectMappedDevicesInfo = 3,
    ICVssOperationBackupComplete = 4,
    ICVssOperationFreezeApplications = 5,
    ICVssOperationThawApplications = 6,
    ICVssOperationAutoRecover = 7,
    ICVssOperationQueryGuestClusterInformation = 8,
    ICVssOperationCount = 9,
} IC_VSS_OPERATION, *PIC_VSS_OPERATION;

typedef struct _IC_VSS_MSG_HDR
{
    HV_UINT8 Operation; // IC_VSS_OPERATION
    HV_UINT8 Reserved[4];
} IC_VSS_MSG_HDR, *PIC_VSS_MSG_HDR;

typedef struct _IC_VSS_MSG_DELETE
{
    HV_GUID SnapshotSetId;
} IC_VSS_MSG_DELETE, *PIC_VSS_MSG_DELETE;

typedef struct _IC_VSS_MSG_CHECK_HOT_BACKUP
{
    HV_UINT32 Flags;
} IC_VSS_MSG_CHECK_HOT_BACKUP, *PIC_VSS_MSG_CHECK_HOT_BACKUP;

typedef struct _IC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO
{
    HV_UINT32 Flags;
} IC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO, *PIC_VSS_MSG_DIRECT_MAPPED_DEVICES_INFO;

typedef struct _IC_VSS_MSG_BACKUP_COMPLETE
{
    HV_UINT32 Flags;
} IC_VSS_MSG_BACKUP_COMPLETE, *PIC_VSS_MSG_BACKUP_COMPLETE;

typedef struct _IC_VSS_MSG_CREATE_V2
{
    HV_GUID SnapshotSetId;
    HV_UINT32 BackupType;
} IC_VSS_MSG_CREATE_V2, *PIC_VSS_MSG_CREATE_V2;

typedef struct _IC_VSS_MSG_THAW_APPLICATIONS
{
    HV_UINT32 Flags;
} IC_VSS_MSG_THAW_APPLICATIONS, *PIC_VSS_MSG_THAW_APPLICATIONS;

typedef enum _IC_VSS_LUN_INFO_BUS_TYPE
{
    IcVssLunInfoBusTypeInvalid = 0,
    IcVssLunInfoBusTypeSCSI = 1,
    IcVssLunInfoBusTypeIDE = 2,
} IC_VSS_LUN_INFO_BUS_TYPE, *PIC_VSS_LUN_INFO_BUS_TYPE;

typedef struct _IC_VSS_LUN_INFO
{
    HV_UINT8 BusType; // IC_VSS_LUN_INFO_BUS_TYPE
    HV_GUID Controller;
    HV_UINT8 Port;
    HV_UINT8 Target;
    HV_UINT8 Lun;
} IC_VSS_LUN_INFO, *PIC_VSS_LUN_INFO;

typedef struct _IC_VSS_LUN_OFFSET
{
    HV_UINT32 DiskNumber;
    HV_INT64 StartingOffset;
} IC_VSS_LUN_OFFSET, *PIC_VSS_LUN_OFFSET;

typedef struct _IC_VSS_DISK_SIGNATURE
{
    HV_UINT32 PartitionStyle;
    union
    {
        struct
        {
            HV_UINT32 Signature;
        } Mbr;
        struct
        {
            HV_GUID DiskId;
        } Gpt;
    };
} IC_VSS_DISK_SIGNATURE, *PIC_VSS_DISK_SIGNATURE;

typedef enum _IC_VSS_FREEZE_FLAGS
{
    IcVssFreezeFlagNone = 0,
    IcVssFreezeFlagAutoRecovery = 1,
    IcVssFreezeFlagIncludesSharedLuns = 2,
} IC_VSS_FREEZE_FLAGS ,*PIC_VSS_FREEZE_FLAGS;

typedef enum _IC_VSS_CLIENT_STATE
{
    ICVssClientStateNone = 0,
    ICVssClientStateFreeze = 1,
    ICVssClientStateThaw = 2,
    ICVssClientStateAutoRecovery = 3,
    ICVssClientStateBackupComplete = 4,
    ICVssClientStateCount = 5,
} IC_VSS_CLIENT_STATE, *PIC_VSS_CLIENT_STATE;

typedef enum _IC_TRANSPORT_ROLE
{
    ICTransportRoleClient = 0x0,
    ICTransportRoleServer = 0x1,
    ICTransportRoleCount = 0x2,
} IC_TRANSPORT_ROLE, *PIC_TRANSPORT_ROLE;

typedef enum _IC_TRANSPORT_PROTO
{
    ICTransportProtoVMBus = 0x0,
    ICTransportProtoNamed = 0x1,
    ICTransportProtoCount = 0x2,
} IC_TRANSPORT_PROTO, *PIC_TRANSPORT_PROTO;

typedef HV_UINT8 IC_TRANSPORT_FLAG, *PIC_TRANSPORT_FLAG;

/* ICFeatureVersionNegotiation | 0 */

typedef struct _IC_MSG_NEGOTIATE
{
    HV_UINT16 ICFrameworkVersionCount;
    HV_UINT16 ICMessageVersionCount;
    HV_UINT32 Reserved;
    IC_VERSION ICVersionData[HV_ANYSIZE_ARRAY];
} IC_MSG_NEGOTIATE, *PIC_MSG_NEGOTIATE;

/* ICFeatureIdxHeartbeat | 1 */

typedef struct _IC_HEARTBEAT_MSG_DATA
{
    HV_UINT64 SeqNum;
    GUEST_APPLICATION_STATE ApplicationState;
    HV_UINT8 Reserved[4];
} IC_HEARTBEAT_MSG_DATA, *PIC_HEARTBEAT_MSG_DATA;

/* ICFeatureIdxKvpExchange | 2 */

typedef struct _IC_KVP_EXCHANGE_MSG
{
    IC_KVP_EXCHANGE_MSG_HDR Header;
    union
    {
        IC_KVP_EXCHANGE_MSG_GET Get;
        IC_KVP_EXCHANGE_MSG_SET Set;
        IC_KVP_EXCHANGE_MSG_DELETE Delete;
        IC_KVP_EXCHANGE_MSG_ENUMERATE Enumerate;
    } Body;
} IC_KVP_EXCHANGE_MSG, *PIC_KVP_EXCHANGE_MSG;

typedef struct _IC_KVP_EXCHANGE_MSG2
{
    union
    {
        IC_KVP_EXCHANGE_MSG_HDR Header;
        IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO IpAddressInfo;
        IC_KVP_EXCHANGE_MSG_IP_ADDRESS_INFO_BINARY IpAddressInfoBinary;
    } IpMsg;
} IC_KVP_EXCHANGE_MSG2, *PIC_KVP_EXCHANGE_MSG2;

/* ICFeatureIdxShutdown | 3 */

typedef struct _IC_SHUTDOWN_MSG_DATA
{
    HV_UINT32 ReasonCode;
    HV_UINT32 TimeoutInSeconds;
    HV_UINT32 Flags;
    HV_UINT8 Message[2048];
} IC_SHUTDOWN_MSG_DATA, *PIC_SHUTDOWN_MSG_DATA;

/* ICFeatureIdxTimeSync | 4 */

typedef struct _IC_TIMESYNC_PROVIDER_MSG_DATA
{
    HV_INT64 Offset;
    HV_UINT64 Delay;
    HV_UINT64 Dispersion;
    HV_UINT32 Flags;
    HV_UINT8 LeapFlags;
    HV_UINT8 Stratum;
    HV_UINT8 Reserved[3];
} IC_TIMESYNC_PROVIDER_MSG_DATA, *PIC_TIMESYNC_PROVIDER_MSG_DATA;

typedef struct _IC_TIMESYNC_MSG_DATA
{
    HV_UINT64 ParentTime; // FILETIME
    HV_UINT64 ChildTime; // FILETIME
    HV_UINT64 RoundTripTime; // FILETIME
    HV_UINT8 Flags;
} IC_TIMESYNC_MSG_DATA, *PIC_TIMESYNC_MSG_DATA;

typedef struct _IC_TIMESYNC_REFERENCE_MSG_DATA
{
    HV_UINT64 ParentTime; // FILETIME
    HV_UINT64 VmReferenceTime;
    HV_UINT8 Flags;
    HV_UINT8 LeapFlags;
    HV_UINT8 Stratum;
    HV_UINT8 Reserved[3];
} IC_TIMESYNC_REFERENCE_MSG_DATA, *PIC_TIMESYNC_REFERENCE_MSG_DATA;

/* ICFeatureIdxVss | 5 */

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

typedef struct _IC_VSS_MSG2
{
    IC_VSS_MSG_HDR Header;
    HV_UINT32 BackupType;
    HV_UINT32 Flags;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO Luns[260];
} IC_VSS_MSG2, *PIC_VSS_MSG2;

typedef struct _IC_VSS_MSG2_EX
{
    IC_VSS_MSG_HDR Header;
    HV_UINT32 BackupType;
    HV_UINT32 Flags;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO Luns[260];
    IC_VSS_LUN_INFO ShadowLuns[260];
} IC_VSS_MSG2_EX, *PIC_VSS_MSG2_EX;

typedef struct _IC_VSS_MSG3
{
    IC_VSS_MSG_HDR Header;
    HV_GUID ClusterId;
    HV_UINT32 ClusterSize;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO SharedLuns[260];
    HV_UINT32 SharedLunStatus[260];
} IC_VSS_MSG3, *PIC_VSS_MSG3;

typedef struct _IC_VSS_MSG3_EX
{
    IC_VSS_MSG_HDR Header;
    HV_GUID ClusterId;
    HV_UINT32 ClusterSize;
    HV_UINT32 LunCount;
    IC_VSS_LUN_INFO SharedLuns[260];
    HV_UINT32 SharedLunStatus[260];
    HV_UINT64 LastMoveTime;
} IC_VSS_MSG3_EX, *PIC_VSS_MSG3_EX;

/* ICFeatureIdxRdv | 6 */

typedef struct _IC_RDV_MSG_DATA
{
    HV_UINT32 Flags;
    HV_UINT8 Message[2048];
} IC_RDV_MSG_DATA, *PIC_RDV_MSG_DATA;

/* ICFeatureIdxGuestInterface | 7 */

typedef enum _IC_GUESTSVC_OPERATION
{
    ICGuestSvcOperationStartFileCopy = 0,
    ICGuestSvcOperationWriteToFile = 1,
    ICGuestSvcOperationCompleteFileCopy = 2,
    ICGuestSvcOperationCancelFileCopy = 3,
} IC_GUESTSVC_OPERATION, *PIC_GUESTSVC_OPERATION;

typedef struct _IC_GUESTSVC_MSG_HEADER
{
    IC_GUESTSVC_OPERATION Operation;
    HV_GUID ServiceID;
    HV_GUID SessionID;
} IC_GUESTSVC_MSG_HEADER, *PIC_GUESTSVC_MSG_HEADER;

typedef enum _IC_GUESTSVC_FLAGS
{
    ICGuestSvcStartFileCopyFlagsOverwrite = 1,
    ICGuestSvcStartFileCopyFlagsCreateFullPath = 2,
} IC_GUESTSVC_FLAGS, *PIC_GUESTSVC_FLAGS;

typedef struct _IC_GUESTIFACE_START_OPERATION_MESSAGE
{
    IC_GUESTSVC_MSG_HEADER Header;
    HV_WCHAR SourceFileName[260];
    HV_WCHAR DestinationFilePath[260];
    IC_GUESTSVC_FLAGS Flags;
    HV_UINT64 FileSizeInBytes;
} IC_GUESTIFACE_START_OPERATION_MESSAGE, *PIC_GUESTIFACE_START_OPERATION_MESSAGE;

typedef struct _IC_GUESTIFACE_COPY_OPERATION_MESSAGE
{
    IC_GUESTSVC_MSG_HEADER Header;
    HV_INT64 Offset;
    HV_UINT32 Size;
    HV_UINT8 Data[6144];
} IC_GUESTIFACE_COPY_OPERATION_MESSAGE, *PIC_GUESTIFACE_COPY_OPERATION_MESSAGE;

/* ICFeatureIdxVMSession | 8 */

// *****************************************************************************
// Microsoft Hyper-V Remote Desktop Control Channel
// Microsoft Hyper-V Remote Desktop Data Channel
//

// {F8E65716-3CB3-4A06-9A60-1889C5CCCAB5}
const HV_GUID SYNTHRDP_CONTROL_CLASS_ID =
{
    0xF8E65716,
    0x3CB3,
    0x4A06,
    { 0x9A, 0x60, 0x18, 0x89, 0xC5, 0xCC, 0xCA, 0xB5 }
};

// {99221FA0-24AD-11E2-BE98-001AA01BBF6E}
const HV_GUID SYNTHRDP_CONTROL_INSTANCE_ID =
{
    0x99221FA0,
    0x24AD,
    0x11E2,
    { 0xBE, 0x98, 0x00, 0x1A, 0xA0, 0x1B, 0xBF, 0x6E }
};

// {F9E9C0D3-B511-4A48-8046-D38079A8830C}
const HV_GUID SYNTHRDP_DATA_CLASS_ID =
{
    0xF9E9C0D3,
    0xB511,
    0x4A48,
    { 0x80, 0x46, 0xD3, 0x80, 0x79, 0xA8, 0x83, 0x0C }
};

// {99221FA1-24AD-11E2-BE98-001AA01BBF6E}
const HV_GUID SYNTHRDP_DATA_INSTANCE_ID_1 =
{
    0x99221FA1,
    0x24AD,
    0x11E2,
    { 0xBE, 0x98, 0x00, 0x1A, 0xA0, 0x1B, 0xBF, 0x6E }
};

// {99221FA2-24AD-11E2-BE98-001AA01BBF6E}
const HV_GUID SYNTHRDP_DATA_INSTANCE_ID_2 =
{
    0x99221FA2,
    0x24AD,
    0x11E2,
    { 0xBE, 0x98, 0x00, 0x1A, 0xA0, 0x1B, 0xBF, 0x6E }
};

// {99221FA3-24AD-11E2-BE98-001AA01BBF6E}
const HV_GUID SYNTHRDP_DATA_INSTANCE_ID_3 =
{
    0x99221FA3,
    0x24AD,
    0x11E2,
    { 0xBE, 0x98, 0x00, 0x1A, 0xA0, 0x1B, 0xBF, 0x6E }
};

// {99221FA4-24AD-11E2-BE98-001AA01BBF6E}
const HV_GUID SYNTHRDP_DATA_INSTANCE_ID_4 =
{
    0x99221FA4,
    0x24AD,
    0x11E2,
    { 0xBE, 0x98, 0x00, 0x1A, 0xA0, 0x1B, 0xBF, 0x6E }
};

// {99221FA5-24AD-11E2-BE98-001AA01BBF6E}
const HV_GUID SYNTHRDP_DATA_INSTANCE_ID_5 =
{
    0x99221FA5,
    0x24AD,
    0x11E2,
    { 0xBE, 0x98, 0x00, 0x1A, 0xA0, 0x1B, 0xBF, 0x6E }
};

typedef enum _SYNTHRDP_MESSAGE_TYPE
{
    SynthrdpError = 0,
    SynthrdpVersionRequest = 1,
    SynthrdpVersionResponse = 2,
    SynthrdpMax = 3,
} SYNTHRDP_MESSAGE_TYPE, *PSYNTHRDP_MESSAGE_TYPE;

typedef struct _SYNTHRDP_MESSAGE_HEADER
{
    SYNTHRDP_MESSAGE_TYPE Type;
    HV_UINT32 Size;
} SYNTHRDP_MESSAGE_HEADER, *PSYNTHRDP_MESSAGE_HEADER;

#define SYNTHRDP_MAKE_VERSION(Major, Minor) ((Minor) << 16 | (Major))
#define SYNTHRDP_VERSION_MAJOR(Version) ((Version) & 0x0000FFFF)
#define SYNTHRDP_VERSION_MINOR(Version) (((Version) & 0xFFFF0000) >> 16)

#define SYNTHRDP_VERSION_WINBLUE SYNTHRDP_MAKE_VERSION(1, 0)

typedef union _SYNTHRDP_VERSION
{
    HV_UINT32 AsDWORD;
    struct
    {
        HV_UINT16 MajorVersion;
        HV_UINT16 MinorVersion;
    };
} SYNTHRDP_VERSION, *PSYNTHRDP_VERSION;

// SynthrdpError | 0

// SynthrdpVersionRequest | 1

typedef struct _SYNTHRDP_VERSION_REQUEST_MESSAGE
{
    SYNTHRDP_MESSAGE_HEADER Header;
    SYNTHRDP_VERSION Version;
    HV_UINT32 Reserved;
} SYNTHRDP_VERSION_REQUEST_MESSAGE, *PSYNTHRDP_VERSION_REQUEST_MESSAGE;

// SynthrdpVersionResponse | 2

#define SYNTHRDP_TRUE_WITH_VERSION_EXCHANGE TRUE_WITH_VERSION_EXCHANGE

#pragma pack(1)
typedef struct _SYNTHRDP_VERSION_RESPONSE_MESSAGE
{
    SYNTHRDP_MESSAGE_HEADER Header;
    SYNTHRDP_VERSION Version;
    HV_UINT32 Reserved;
    HV_UINT8 IsAccepted;
} SYNTHRDP_VERSION_RESPONSE_MESSAGE, *PSYNTHRDP_VERSION_RESPONSE_MESSAGE;
#pragma pack()

// *****************************************************************************
// Microsoft Hyper-V Virtual SMB
//

// {4D12E519-17A0-4AE4-8EAA-5270FC6ABDB7}
const HV_GUID VSMB_CLASS_ID =
{
    0x4D12E519,
    0x17A0,
    0x4AE4,
    { 0x8E, 0xAA, 0x52, 0x70, 0xFC, 0x6A, 0xBD, 0xB7 }
};

// {DCC079AE-60BA-4D07-847C-3493609C0870}
const HV_GUID VSMB_INSTANCE_ID =
{
    0xDCC079AE,
    0x60BA,
    0x4D07,
    { 0x84, 0x7C, 0x34, 0x93, 0x60, 0x9C, 0x08, 0x70 }
};

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
