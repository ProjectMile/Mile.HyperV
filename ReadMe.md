﻿# Mile.HyperV

[![NuGet Package](https://img.shields.io/nuget/vpre/Mile.HyperV)](https://www.nuget.org/packages/Mile.HyperV)

The lightweight library for Hyper-V guest interfaces.

## Usage

Currently, include `Mile.HyperV.*.h` in `Mile.HyperV` or `Mile.HyperV.Windows`
folder which you actually needed to your C/C++ projects.

## Features

- Mile.HyperV.Portable.Types.h
  - Only depend on Mile.Mobility.Portable.Types.h if available.
  - Only depend on stdint.h if Mile.Mobility.Portable.Types.h if not available.
- Mile.HyperV.Guest.Interface.h
  - Include Hyper-V related definitions from
    https://github.com/microsoft/mu_msvm/tree/258361bd0d61320df8984705111d94af20b4d8a4
    - MsvmPkg\Include\Hv\HvStatus.h
    - MsvmPkg\Include\Hv\HvGuest.h
    - MsvmPkg\Include\Hv\HvGuestCpuid.h
    - MsvmPkg\Include\Hv\HvGuestMsr.h
    - MsvmPkg\Include\Hv\HvGuestSyntheticInterrupts.h
    - MsvmPkg\Include\Hv\HvGuestHypercall.h
  - Include definitions from MIT-licensed Hyper-V headers from Microsoft mshv 
    Linux kernel module
    - https://github.com/microsoft/OHCL-Linux-Kernel/tree/e9017243ba9b424f6516c4b206f454a1c2585fd2/include/uapi/hyperv
  - Include Hyper-V related definitions from
    https://github.com/microsoft/WSL/tree/697572d664c9371abbc53cab9cf7b4b32be1980e
    - src\windows\inc\wdk.h
- Mile.HyperV.Guest.Protocols.h
  - Include Hyper-V related definitions from
    https://github.com/microsoft/mu_msvm/tree/258361bd0d61320df8984705111d94af20b4d8a4
    - MsvmPkg\MsvmPkg.dec
    - MsvmPkg\Include\Vmbus\NtStatus.h
    - MsvmPkg\Include\MsvmBase.h
    - MsvmPkg\VmbusDxe\VmbusP.h
    - MsvmPkg\VmbusDxe\ChannelMessages.h
    - MsvmPkg\Include\Vmbus\VmbusPacketFormat.h
    - MsvmPkg\VideoDxe\SynthVidProtocol.h
    - MsvmPkg\VideoDxe\VramSize.h
    - MsvmPkg\Include\Protocol\SynthKeyProtocol.h
    - MsvmPkg\StorvscDxe\VstorageProtocol.h
    - MsvmPkg\NetvscDxe\nvspprotocol.h
    - MsvmPkg\NetvscDxe\rndis.h
    - MsvmPkg\VpcivscDxe\wdm.h
    - MsvmPkg\VpcivscDxe\VpciProtocol.h
    - MsvmPkg\VpcivscDxe\PciBars.h
    - MsvmPkg\Include\Protocol\VmbusFileSystem.h
- Mile.HyperV.TLFS.h
  - Definitions conform with Hypervisor Top Level Functional Specification 6.0b
  - Include definitions from hvgdk.h from Windows Driver Kit version 7.1.0
  - Include definitions from MIT-licensed Hyper-V headers from Microsoft mshv 
    Linux kernel module
  - Include definitions from gerhart01's archive of Hypervisor (Windows Drivers)
    documentation from Microsoft in 2013
  - Include Hyper-V related definitions from https://github.com/rust-vmm/mshv
  - Include Hyper-V related definitions from https://github.com/microsoft/igvm
  - Include Hyper-V related definitions from symbols in Windows Driver Kit
    version 10.0.26063.0's Debuggers\ddk\samples\kdserial\lib\x64\kdhv.lib
  - Include Hyper-V related definitions from symbols in Windows version
    10.0.14393.0's urlmon.dll
  - Include Hyper-V related definitions from symbols in Windows version
    10.0.14347.0's ntoskrnl.exe
- Mile.HyperV.Windows.VMBusPipe.h and Mile.HyperV.Windows.VMBusPipe.cpp
  - Definitions conform with Windows 10 Build 19041's vmbuspipe.dll
  - Include Hyper-V related definitions from symbols in Windows version
    10.0.14347.0's vmbuspipe.dll
- Mile.HyperV.VMBus.h
  - Definitions conform with Windows 10 Build 14347's HyperVideo.sys
  - Definitions conform with Windows 10 Build 14347's VMBusHID.sys
  - Definitions conform with Windows 10 Build 14347's netvsc.sys
  - Definitions conform with Windows 10 Build 14347's fcvsc.sys
  - Definitions conform with Windows 10 Build 14347's icsvc.dll
  - Definitions conform with Windows 10 Build 14347's icsvcext.dll
  - Definitions conform with Windows 10 Build 19041's rdpcorets.dll
  - Definitions conform with Windows 10 Build 19041's vmuidevices.dll
  - Definitions conform with Windows 10 Build 14347's ntoskrnl.exe
- Distributed under the MIT License
- Provide NuGet package.

## NuGet Package Usage

### How to enable the Windows specific wrappers in the property group.

```
<MileHyperVEnableWindowsPlatformSupport>true</MileHyperVEnableWindowsPlatformSupport>
```

## Documents

- [License](License.md)
- [Mile.HyperV Definition References](References/ReadMe.md)
- [Release Notes](ReleaseNotes.md)
- [Versioning](Versioning.md)

## Thanks

- Geoff Chappell, https://www.geoffchappell.com/ for researches hints
- Gerhart, https://github.com/gerhart01 for documentation archive
- Liu Wei, https://github.com/liuw for mshv existance hints
- Mezone, https://github.com/Mez0ne for revise hints
- Nuno Das Neves, https://github.com/NunoDasNeves for mshv implementation
