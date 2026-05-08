# Mile.HyperV Release Notes

**Mile.HyperV 1.2.960.0**

- Revise the definitions via
  https://github.com/microsoft/mu_msvm/tree/v26.0.3.
- Revise the definitions via 
  https://github.com/microsoft/openvmm/tree/8289be0034e3e2dd3d53d8eedb995e6f9112281d.
- Update Mile.Mobility to 1.1.544.
- Fix several issues for Mile.HyperV.Test project.

**Mile.HyperV 1.2.943.0**

- Add protocol definitions for Microsoft Hyper-V BIOS Virtual Device.
- Revise the definitions via
  https://github.com/microsoft/mu_msvm/tree/v26.0.0.
- Revise the definitions via 
  https://github.com/microsoft/openvmm/tree/40144a1ef9fb572abb54c745d66484de30fabb53.

**Mile.HyperV 1.2.938.0**

- Revise the definitions via 
  https://github.com/microsoft/mu_msvm/tree/3e68f1023fd09e2423060422c1320b54f5457d65.
- Revise the definitions via 
  https://github.com/microsoft/openvmm/tree/52302e44c6ec35abb8cb1d316cca43326a7495e7.

**Mile.HyperV 1.2.907.0**

- Revise all Mile.HyperV definitions via
  https://github.com/microsoft/openvmm/tree/3a79304b0705f38965a37c3cc692439050ffc94f.
- Revise all Mile.HyperV definitions via
  https://github.com/microsoft/mu_msvm/tree/e2299ff8cbb2e6fe79042be09a6b550a19957d41.
- Update Mile.Project.Configurations to 1.0.1917.
- Update Mile.Mobility to 1.0.372.
- Migrate solution from sln to slnx.

**Mile.HyperV 1.2.764.0**

- Revise all Mile.HyperV definitions via
  https://github.com/microsoft/openvmm/tree/2366cbcb0c0e170f2158dcd03253a9ab8ff5c7ca.
- Revise all Mile.HyperV definitions via
  https://github.com/microsoft/mu_msvm/tree/9dd44d82aaa513e58913616f3a5a567112039574.
- Update Mile.Project.Configurations to 1.0.1768.
- Fix several definition and documentation issues.

**Mile.HyperV 1.2.730.0**

- Revise all Mile.HyperV definitions via
  https://github.com/microsoft/openvmm/tree/0ed9ebc1d05b342aa708ef9bbbb8f8f6887cce94.
- Update Mile.Project.Configurations to 1.0.1766.
- Update Mile.Mobility to 1.0.306.

**Mile.HyperV 1.2.688.0**

- Revise the Mile.HyperV.TLFS definitions via symbols in Windows version
  10.0.26100.0's securekernel.exe. (Thanks to Mezone.)
- Revise all Mile.HyperV definitions via
  https://github.com/microsoft/mu_msvm/tree/9337285a977fbf1682e21c17800c4809ce5bcd19.
- Fix the source code file header comment format.
- Introduce Mile.HyperV.Test project for testing the definitions.

**Mile.HyperV 1.1.635.0**

- Fix HV_DECLSPEC_ALIGN fallback definition.
- Fix some definitions to improve the portability.

**Mile.HyperV 1.1.633.0**

- Introduce HV_STATIC_ASSERT to replace static_assert to improve the
  portability.

**Mile.HyperV 1.1.622.0**

- Introduce Mile.HyperV.Portable.Types.h for making Mile.HyperV more portable.
- Update HV_X64_HYPERVISOR_HARDWARE_FEATURES definition from Windows Subsystem
  for Linux source code.
- Make version to dummy value because the build project will generate that
  automatically.
- Update Mile.Project.Configurations to 1.0.1622.
- Update Definition References.
- Fix comments for Mile.HyperV header and source files.

**Mile.HyperV 1.1.575.0**

- Use HV_GUID instead of GUID for Mile.HyperV.Guest.Protocols.

**Mile.HyperV 1.1.419.0**

- Rename the definition names for VMBus Channel GUIDs.
- More VMBus protocol definitions for Microsoft Hyper-V Virtual Machine Bus File
  System device observed from the Device Manager.
- More VMBus protocol definitions for Microsoft Hyper-V Virtual SMB device
  dumped from Windows 10 Build 14347's ntoskrnl.exe.

**Mile.HyperV 1.1.399.0**

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
  - Add protocol definitions for Microsoft Hyper-V Virtual PCI Bus device.
  - Add protocol definitions for Microsoft Hyper-V Virtual Machine Bus File
    System device.
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
  - MsvmPkg\VpcivscDxe\wdm.h
  - MsvmPkg\VpcivscDxe\VpciProtocol.h
  - MsvmPkg\VpcivscDxe\PciBars.h
  - MsvmPkg\Include\Protocol\VmbusFileSystem.h
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
