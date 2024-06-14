# Mile.HyperV Release Notes

**Mile.HyperV 1.0.267.0**

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
