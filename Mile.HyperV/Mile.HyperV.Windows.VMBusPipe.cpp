/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.Windows.VMBusPipe.cpp
 * PURPOSE:    Implementation for Hyper-V Windows VMBus User Mode Pipe API
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#include "Mile.HyperV.Windows.VMBusPipe.h"

namespace
{
    static HMODULE GetVmbusPipeGuestModuleHandle()
    {
        static HMODULE CachedResult = ::LoadLibraryExW(
            L"vmbuspipe.dll",
            nullptr,
            LOAD_LIBRARY_SEARCH_SYSTEM32);
        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientEnumeratePipesProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientEnumeratePipes");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientOpenChannelProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientOpenChannel");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientWaitChannelProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientWaitChannel");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeServerConnectPipeProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeServerConnectPipe");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeServerOfferChannelProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeServerOfferChannel");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientReadyForChannelNotificationProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientReadyForChannelNotification");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientRegisterChannelNotificationProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientRegisterChannelNotification");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientUnregisterChannelNotificationProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientUnregisterChannelNotification");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeServerOfferChannelExProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeServerOfferChannelEx");
            }
            return nullptr;
        }());

        return CachedResult;
    }

    static FARPROC GetVmbusPipeClientOpenChannelExProcAddress()
    {
        static FARPROC CachedResult = ([]() -> FARPROC
        {
            HMODULE ModuleHandle = ::GetVmbusPipeGuestModuleHandle();
            if (ModuleHandle)
            {
                return ::GetProcAddress(
                    ModuleHandle,
                    "VmbusPipeClientOpenChannelEx");
            }
            return nullptr;
        }());

        return CachedResult;
    }
}

EXTERN_C BOOL WINAPI VmbusPipeClientEnumeratePipes(
    _In_ LPCGUID InterfaceType,
    _In_opt_ LPVOID UserContext,
    _In_ CHANNEL_OFFER_NOTIFICATION OnOfferNotification)
{
    using ProcType = decltype(::VmbusPipeClientEnumeratePipes)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientEnumeratePipesProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(InterfaceType, UserContext, OnOfferNotification);
    }

    return FALSE;
}

EXTERN_C HANDLE WINAPI VmbusPipeClientOpenChannel(
    _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo,
    _In_ DWORD OpenMode)
{
    using ProcType = decltype(::VmbusPipeClientOpenChannel)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientOpenChannelProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(ChannelInfo, OpenMode);
    }

    return INVALID_HANDLE_VALUE;
}

EXTERN_C BOOL WINAPI VmbusPipeClientWaitChannel(
    _In_ LPCGUID InterfaceType,
    _In_ LPCGUID InterfaceInstance,
    _In_ DWORD TimeoutInMsec,
    _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo)
{
    using ProcType = decltype(::VmbusPipeClientWaitChannel)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientWaitChannelProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(
            InterfaceType,
            InterfaceInstance,
            TimeoutInMsec,
            ChannelInfo);
    }

    return FALSE;
}

EXTERN_C BOOL WINAPI VmbusPipeServerConnectPipe(
    _In_ HANDLE PipeHandle,
    _Inout_opt_ LPOVERLAPPED Overlapped)
{
    using ProcType = decltype(::VmbusPipeServerConnectPipe)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeServerConnectPipeProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(PipeHandle, Overlapped);
    }

    return FALSE;
}

EXTERN_C HANDLE WINAPI VmbusPipeServerOfferChannel(
    PVMBUS_PIPE_SERVER_OFFER Offer,
    DWORD OpenMode,
    DWORD PipeMode)
{
    using ProcType = decltype(::VmbusPipeServerOfferChannel)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeServerOfferChannelProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(Offer, OpenMode, PipeMode);
    }

    return FALSE;
}

EXTERN_C VOID WINAPI VmbusPipeClientReadyForChannelNotification(
    _In_ HVMBUS_PIPE_NOTIFICATION NotificationContext,
    _In_ BOOL ReportExistingChannels)
{
    using ProcType = decltype(::VmbusPipeClientReadyForChannelNotification)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientReadyForChannelNotificationProcAddress());

    if (ProcAddress)
    {
        ProcAddress(NotificationContext, ReportExistingChannels);
    }
}

EXTERN_C HVMBUS_PIPE_NOTIFICATION WINAPI VmbusPipeClientRegisterChannelNotification(
    _In_ LPCGUID InterfaceType,
    _In_ LPCGUID InterfaceInstance,
    _In_ DWORD Flags,
    _In_ VMBUS_PIPE_CLIENT_CHANNEL_NOTIFICATION_CALLBACK Callback,
    _In_opt_ LPVOID ClientContext)
{
    using ProcType = decltype(::VmbusPipeClientRegisterChannelNotification)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientRegisterChannelNotificationProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(
            InterfaceType,
            InterfaceInstance,
            Flags,
            Callback,
            ClientContext);
    }

    return nullptr;
}

EXTERN_C VOID WINAPI VmbusPipeClientUnregisterChannelNotification(
    _In_ HVMBUS_PIPE_NOTIFICATION NotificationContext,
    _In_ BOOL WaitForNotificationsToComplete)
{
    using ProcType = decltype(::VmbusPipeClientUnregisterChannelNotification)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientUnregisterChannelNotificationProcAddress());

    if (ProcAddress)
    {
        ProcAddress(NotificationContext, WaitForNotificationsToComplete);
    }
}

EXTERN_C DWORD WINAPI VmbusPipeServerOfferChannelEx(
    PCVMBUS_PIPE_SERVER_OFFER_EX Offer,
    DWORD OpenMode,
    DWORD PipeMode,
    PHANDLE PipeHandle)
{
    using ProcType = decltype(::VmbusPipeServerOfferChannelEx)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeServerOfferChannelExProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(Offer, OpenMode, PipeMode, PipeHandle);
    }

    return ERROR_CALL_NOT_IMPLEMENTED;
}

EXTERN_C HANDLE WINAPI VmbusPipeClientOpenChannelEx(
    _In_ PVMBUS_PIPE_CHANNEL_INFO ChannelInfo,
    _In_ DWORD OpenMode,
    _In_ PVMBUS_PIPE_CLIENT_CHANNEL_SETTINGS ChannelSettings)
{
    using ProcType = decltype(::VmbusPipeClientOpenChannelEx)*;

    ProcType ProcAddress = reinterpret_cast<ProcType>(
        ::GetVmbusPipeClientOpenChannelExProcAddress());

    if (ProcAddress)
    {
        return ProcAddress(ChannelInfo, OpenMode, ChannelSettings);
    }

    return INVALID_HANDLE_VALUE;
}
