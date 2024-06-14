/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.HyperV.Windows.VMBusPipe.h
 * PURPOSE:   Definition for Hyper-V Windows VMBus User Mode Pipe API
 *
 * LICENSE:   The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef MILE_HYPERV_WINDOWS_VMBUSPIPE
#define MILE_HYPERV_WINDOWS_VMBUSPIPE

#include <Windows.h>

#ifdef _MSC_VER
#if _MSC_VER > 1000
#pragma once
#endif
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif
#pragma warning(disable:4201) // nameless struct/union
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    typedef struct _VMBUS_PIPE_CHANNEL_INFO
    {
        // Add 4 for old Windows compatibility.
        WCHAR DevicePath[MAX_PATH + 4];
    } VMBUS_PIPE_CHANNEL_INFO, *PVMBUS_PIPE_CHANNEL_INFO;

    typedef VOID(CALLBACK* CHANNEL_OFFER_NOTIFICATION)(
        _In_opt_ LPVOID HostContext,
        _In_ LPBYTE UserDefined,
        _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo,
        _In_ LPCGUID InstanceGuid);

    DECLARE_HANDLE(HVMBUS_PIPE_NOTIFICATION);

    typedef enum _VMBUS_PIPE_CHANNEL_NOTIFICATION_TYPE
    {
        ChannelNotificationArrival = 0x1,
    } VMBUS_PIPE_CHANNEL_NOTIFICATION_TYPE, *PVMBUS_PIPE_CHANNEL_NOTIFICATION_TYPE;

    typedef VOID(CALLBACK* VMBUS_PIPE_CLIENT_CHANNEL_NOTIFICATION_CALLBACK)(
        _In_opt_ LPVOID ClientContext,
        _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo,
        _In_ VMBUS_PIPE_CHANNEL_NOTIFICATION_TYPE NotificationType);

    typedef struct _VMBUS_PIPE_SERVER_OFFER
    {
        union
        {
            GUID VmGuid;
            HANDLE VmbusHandle;
        };
        DWORD InterruptLatencyInMilliseconds;
        GUID InterfaceType;
        GUID InterfaceInstance;
        DWORD InterfaceRevision;
        USHORT MmioMegabytes;
        USHORT Flags;
        BYTE UserDefined[112];
    } VMBUS_PIPE_SERVER_OFFER, *PVMBUS_PIPE_SERVER_OFFER;

    typedef struct _VMBUS_PIPE_SERVER_OFFER_EX
    {
        DWORD Version;
        DWORD Size;
        union
        {
            GUID VmGuid;
            HANDLE VmbusHandle;
        };
        DWORD InterruptLatencyInMilliseconds;
        GUID InterfaceType;
        GUID InterfaceInstance;
        DWORD InterfaceRevision;
        USHORT MmioMegabytes;
        USHORT Flags;
        BYTE UserDefined[112];
        LPCWSTR Name;
    } VMBUS_PIPE_SERVER_OFFER_EX, *PVMBUS_PIPE_SERVER_OFFER_EX;

    typedef const VMBUS_PIPE_SERVER_OFFER_EX *PCVMBUS_PIPE_SERVER_OFFER_EX;

#define VMBUS_PIPE_CLIENT_CHANNEL_CURRENT_VERSION 1

    typedef struct _VMBUS_PIPE_CLIENT_CHANNEL_SETTINGS
    {
        DWORD Version;
        DWORD Size;
        DWORD IncomingSize;
        DWORD OutgoingSize;
    } VMBUS_PIPE_CLIENT_CHANNEL_SETTINGS, *PVMBUS_PIPE_CLIENT_CHANNEL_SETTINGS;

    BOOL WINAPI VmbusPipeClientEnumeratePipes(
        _In_ LPCGUID InterfaceType,
        _In_opt_ LPVOID UserContext,
        _In_ CHANNEL_OFFER_NOTIFICATION OnOfferNotification);

    HANDLE WINAPI VmbusPipeClientOpenChannel(
        _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo,
        _In_ DWORD OpenMode);

    BOOL WINAPI VmbusPipeClientWaitChannel(
        _In_ LPCGUID InterfaceType,
        _In_ LPCGUID InterfaceInstance,
        _In_ DWORD TimeoutInMsec,
        _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo);

    BOOL WINAPI VmbusPipeServerConnectPipe(
        _In_ HANDLE PipeHandle,
        _Inout_opt_ LPOVERLAPPED Overlapped);

    HANDLE WINAPI VmbusPipeServerOfferChannel(
        PVMBUS_PIPE_SERVER_OFFER Offer,
        DWORD OpenMode,
        DWORD PipeMode);

    VOID WINAPI VmbusPipeClientReadyForChannelNotification(
        _In_ HVMBUS_PIPE_NOTIFICATION NotificationContext,
        _In_ BOOL ReportExistingChannels);

    HVMBUS_PIPE_NOTIFICATION WINAPI VmbusPipeClientRegisterChannelNotification(
        _In_ LPCGUID InterfaceType,
        _In_ LPCGUID InterfaceInstance,
        _In_ DWORD Flags,
        _In_ VMBUS_PIPE_CLIENT_CHANNEL_NOTIFICATION_CALLBACK Callback,
        _In_opt_ LPVOID ClientContext);

    VOID WINAPI VmbusPipeClientUnregisterChannelNotification(
        _In_ HVMBUS_PIPE_NOTIFICATION NotificationContext,
        _In_ BOOL WaitForNotificationsToComplete);

    DWORD WINAPI VmbusPipeServerOfferChannelEx(
        PCVMBUS_PIPE_SERVER_OFFER_EX Offer,
        DWORD OpenMode,
        DWORD PipeMode,
        PHANDLE PipeHandle);

    HANDLE WINAPI VmbusPipeClientOpenChannelEx(
        _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo,
        _In_ DWORD OpenMode,
        _In_ PVMBUS_PIPE_CLIENT_CHANNEL_SETTINGS ChannelSettings);

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4201) // nameless struct/union
#endif
#endif

#endif // !MILE_HYPERV_WINDOWS_VMBUSPIPE
