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

// *****************************************************************************
// Microsoft Hyper-V Video
//

#define SYNTHVID_CONTROL_CLASS_ID SYNTHVID_CLASS_ID

#define SYNTHVID_VERSION_WIN7 SYNTHVID_MAKE_VERSION(3, 0)
#define SYNTHVID_VERSION_WIN8 SYNTHVID_MAKE_VERSION(3, 2)
#define SYNTHVID_VERSION_WINBLUE SYNTHVID_MAKE_VERSION(3, 3)
#define SYNTHVID_VERSION_WINTHRESHOLD_M1 SYNTHVID_MAKE_VERSION(3, 4)
#define SYNTHVID_VERSION_WINTHRESHOLD_M2 SYNTHVID_MAKE_VERSION(3, 5)
#define SYNTHVID_VERSION_WIN10 SYNTHVID_VERSION_WINTHRESHOLD_M2

// *****************************************************************************
// Microsoft Hyper-V Virtual Keyboard
//

#define HK_CONTROL_CLASS_ID HK_CLASS_ID

#define HK_VERSION_MAJOR(Version) (((Version) & 0xFFFF0000) >> 16)
#define HK_VERSION_MINOR(Version) ((Version) & 0x0000FFFF)

#define HK_VERSION_CURRENT HK_VERSION_WIN8

// *****************************************************************************
// Microsoft Hyper-V Input
//

#define SYNTHHID_CONTROL_CLASS_ID SYNTHHID_CLASS_ID

#define SYNTHHID_VERSION_MAJOR(Version) (((Version) & 0xFFFF0000) >> 16)
#define SYNTHHID_VERSION_MINOR(Version) ((Version) & 0x0000FFFF)

#define SYNTHHID_VERSION_CURRENT SYNTHHID_MAKE_VERSION(2, 0)

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

#define VMSTORAGE_MAKE_VERSION VMSTOR_PROTOCOL_VERSION
#define VMSTORAGE_VERSION_MAJOR VMSTOR_PROTOCOL_MAJOR
#define VMSTORAGE_VERSION_MINOR VMSTOR_PROTOCOL_MINOR

#define VMSTORAGE_VERSION_WIN6 VMSTOR_PROTOCOL_VERSION_WIN6
#define VMSTORAGE_VERSION_WIN7 VMSTOR_PROTOCOL_VERSION_WIN7
#define VMSTORAGE_VERSION_WIN8 VMSTOR_PROTOCOL_VERSION_WIN8
#define VMSTORAGE_VERSION_WINBLUE VMSTOR_PROTOCOL_VERSION_BLUE
#define VMSTORAGE_VERSION_WIN10 VMSTOR_PROTOCOL_VERSION_THRESHOLD

// *****************************************************************************
// Microsoft Hyper-V Network Adapter
//

#define NVSP_CONTROL_CLASS_ID NVSP_CLASS_ID

#define NVSP_MAKE_VERSION NVSP_PROTOCOL_VERSION
#define NVSP_VERSION_MAJOR NVSP_PROTOCOL_MAJOR
#define NVSP_VERSION_MINOR NVSP_PROTOCOL_MINOR

#define NVSP_VERSION_1 NVSP_PROTOCOL_VERSION_1
#define NVSP_VERSION_2 NVSP_PROTOCOL_VERSION_2
#define NVSP_VERSION_4 NVSP_PROTOCOL_VERSION_4
#define NVSP_VERSION_5 NVSP_PROTOCOL_VERSION_5
#define NVSP_VERSION_6 NVSP_PROTOCOL_VERSION_6
#define NVSP_VERSION_61 NVSP_PROTOCOL_VERSION_61

// *****************************************************************************
// Microsoft Hyper-V Virtual PCI Bus
//

#define VPCI_CONTROL_CLASS_ID VPCI_CLASS_ID

// *****************************************************************************
// Microsoft Hyper-V Virtual Machine Bus File System
//

#define VMBFS_CONTROL_CLASS_ID VMBFS_CLASS_ID

#define VMBFS_INSTANCE_ID VMBFS_BOOT_INSTANCE_ID

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

// {FD149E91-82E0-4A7D-AFA6-2A4166CBD7C0}
const HV_GUID IC_HEARTBEAT_INSTANCE_ID =
{
    0xFD149E91,
    0x82E0,
    0x4A7D,
    { 0xAF, 0xA6, 0x2A, 0x41, 0x66, 0xCB, 0xD7, 0xC0 }
};

// {2450EE40-33BF-4FBD-892E-9FB06E9214CF}
const HV_GUID IC_VSS_INSTANCE_ID =
{
    0x2450EE40,
    0x33BF,
    0x4FBD,
    { 0x89, 0x2E, 0x9F, 0xB0, 0x6E, 0x92, 0x14, 0xCF }
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

#define IC_HEARTBEAT_VERSION_3 { 3, 0 }
#define IC_HEARTBEAT_VERSION_31 { 3, 1 }

#define IC_RDV_VERSION_1 { 1, 0 }
#define IC_RDV_VERSION_3 { 3, 0 }

#define IC_GUESTIFACE_VERSION_11 { 1, 1 }

typedef enum _IC_VSS_LUN_INFO_BUS_TYPE
{
    IcVssLunInfoBusTypeInvalid = 0,
    IcVssLunInfoBusTypeSCSI = 1,
    IcVssLunInfoBusTypeIDE = 2,
} IC_VSS_LUN_INFO_BUS_TYPE, *PIC_VSS_LUN_INFO_BUS_TYPE;

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

// Already defined in Mile.HyperV.Guest.Protocols.h.

/* ICFeatureIdxHeartbeat | 1 */

// Already defined in Mile.HyperV.Guest.Protocols.h.

/* ICFeatureIdxKvpExchange | 2 */

// Already defined in Mile.HyperV.Guest.Protocols.h.

/* ICFeatureIdxShutdown | 3 */

// Already defined in Mile.HyperV.Guest.Protocols.h.

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

/* ICFeatureIdxVss | 5 */

// Already defined in Mile.HyperV.Guest.Protocols.h.

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
