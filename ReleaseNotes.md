# Mile.HyperV Release Notes

**Mile.HyperV 1.1.xxx.0**

- Introduce Mile.HyperV.Guest.Interface.h and Mile.HyperV.Guest.Protocols.h for
  including Hyper-V guest publicized interface and protocols definitions from
  https://github.com/microsoft/mu_msvm/tree/258361bd0d61320df8984705111d94af20b4d8a4.
  - Microsoft's original comments for interface and protocols.
  - More Hyper-V ARM64 guest definitions.
  - Introduce the definition of HvCallModifySparseGpaPageHostVisibility.
  - More VMBus protocol definitions for Microsoft Hyper-V Virtual Machine Bus
    device which replaced all definitions dumped from Windows 10 Build 14347's
    vmbus.sys.
  - More VMBus protocol definitions for Microsoft Hyper-V Video device.
  - More VMBus protocol definitions for Microsoft Hyper-V Virtual Keyboard
    device which replaced all definitions dumped from Windows 10 Build 14347's
    hyperkbd.sys.
  - More VMBus protocol definitions for Microsoft Hyper-V SCSI Controller device
    and Microsoft Hyper-V Fibre Channel HBA device which replaced all
    definitions dumped from Windows 10 Build 14347's storvsc.sys.
  - More VMBus protocol definitions for Microsoft Hyper-V Network Adapter device.
- Revise all Mile.HyperV definitions via the following files from
  https://github.com/microsoft/mu_msvm/tree/258361bd0d61320df8984705111d94af20b4d8a4.
  - MsvmPkg\Include\Hv\HvStatus.h
  - MsvmPkg\Include\Hv\HvGuest.h
  - MsvmPkg\Include\Hv\HvGuestCpuid.h
  - MsvmPkg\Include\Hv\HvGuestMsr.h
  - MsvmPkg\Include\Hv\HvGuestSyntheticInterrupts.h
  - MsvmPkg\Include\Hv\HvGuestHypercall.h
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
- Revise all Mile.HyperV definitions via the following files from
  https://github.com/microsoft/OHCL-Linux-Kernel/tree/e9017243ba9b424f6516c4b206f454a1c2585fd2/include/uapi/hyperv.
- Migrate from Mile.Project.Windows to Mile.Project.Configurations for
  streamlining the build toolchain of this package.

**Mile.HyperV 1.0.327.0**

- Fix definition typos for resolving issues in pure C projects.

**Mile.HyperV 1.0.272.0**

- Add 2-bytes wchar_t interoperability support via introducing HV_WCHAR type.
- Remove ANYSIZE_ARRAY dependency for Mile.HyperV.TLFS.

**Mile.HyperV 1.0.270.0**

- Add GUID interoperability support for HV_GUID.
- Add version related macro definitions for Mile.HyperV.VMBus.h.

**Mile.HyperV 1.0.268.0**

- Add Microsoft Hyper-V Fibre Channel HBA definitions from Windows 10 Build
  14347's fcvsc.sys.
- Add Microsoft Hyper-V Integration Components definitions from Windows 10 Build
  14347's icsvc.dll and icsvcext.dll.
- Add Microsoft Hyper-V Remote Desktop definitions from Windows 10 Build 19041's
  rdpcorets.dll and vmuidevices.dll.
- Start to provide NuGet package.

**Mile.HyperV 0.3.205**

- Improve the comment style via using C++ style comments which supported since
  Microsoft C/C++ 6.0 or other C compilers which supports C99.
- Revise the Mile.HyperV.TLFS definition via Build 14347 ntoskrnl.exe and Build
  26063 kdhv.lib debug symbols from Microsoft.
- Add Mile.HyperV.Windows.VMBusPipe definitions.
- Add Mile.HyperV.VMBus definitions.

**Mile.HyperV 0.2**

- Revise the Mile.HyperV.TLFS definitions via hvgdk.h from Windows Driver Kit
  version 7.1.0.
- Revise the Mile.HyperV.TLFS definitions via MIT-licensed Hyper-V headers from
  Microsoft.
- Revise the Mile.HyperV.TLFS CPUID series definitions according to urlmon.dll's
  symbols.

**Mile.HyperV 0.1**

- Initial release.
- Synchronize Mile.HyperV.TLFS to Hyper-V TLFS 6.0b definitions. (Thanks to
  gerhart01.)
- Revise the list of Hypercall codes according to Windows symbols. (Thanks to
  Mez0ne.)
- Revise HV_PARTITION_PRIVILEGE_MASK and HV_X64_HYPERVISOR_FEATURES according
  to Windows Kit symbols. (Thanks to Mez0ne.)
