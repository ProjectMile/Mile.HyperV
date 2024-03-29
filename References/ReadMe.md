﻿# Mile.HyperV Definition References

Mile.HyperV uses Microsoft Hypervisor Wrappers, Microsoft Independent Guest
Virtual Machine, Hypervisor Top Level Functional Specification v6.0b, hvgdk.h
from Windows Driver Kit version 7.1.0, MIT licensed Hyper-V headers from
Microsoft, Archive of Hypervisor (Windows Drivers) documentations from Microsoft
in 2013, Geoff Chappell's hvgdk_mini researches, Windows symbols, FreeBSD and
Hyper-V integration support for macOS to create the definition headers.

## Microsoft Hypervisor Wrappers

https://github.com/rust-vmm/mshv

## Microsoft Independent Guest Virtual Machine

https://github.com/microsoft/igvm

## Hypervisor Top Level Functional Specification

- [Microsoft's all version archive]
- [Mile.HyperV's local PDF archive]

[Microsoft's all version archive]: https://github.com/MicrosoftDocs/Virtualization-Documentation/tree/live/tlfs
[Mile.HyperV's local PDF archive]: Hypervisor%20Top%20Level%20Functional%20Specification%20v6.0b.pdf

## hvgdk.h from Windows Driver Kit version 7.1.0

- [WDK710/hvgdk.h](WDK710/hvgdk.h)

## MIT licensed Hyper-V headers from Microsoft

Kenji Mouri knows these MIT licensed Hyper-V headers from Microsoft because he
had fired a GitHub issue: https://github.com/rust-vmm/mshv/issues/117

Here is the original reference from Microsoft. They create a Linux kernel patch
called "[PATCH v4 13/15] uapi: hyperv: Add mshv driver headers defining
hypervisor ABIs" to try to make their mshv implementation merge to the mainline.

- [Online version from linux-hyperv mailing list]
- [Mile.HyperV's local Outlook Unicode MSG archive]

[Online version from linux-hyperv mailing list]: https://lore.kernel.org/linux-hyperv/1696010501-24584-1-git-send-email-nunodasneves@linux.microsoft.com/T/#m265e35e841d29ec27c7e60887c1c7566585fc0ff
[Mile.HyperV's local Outlook Unicode MSG archive]: MSHV/patch-v4-1315-uapi-hyperv-add-mshv-driver-headers-defining-hypervisor-abis.msg

Here is the extracted reference from the mentioned patch created by Microsoft.

- [MSHV/hvgdk.h](MSHV/hvgdk.h)
- [MSHV/hvgdk_mini.h](MSHV/hvgdk_mini.h)
- [MSHV/hvhdk.h](MSHV/hvhdk.h)
- [MSHV/hvhdk_mini.h](MSHV/hvhdk_mini.h)

## Archive of Hypervisor (Windows Drivers) documentation from Microsoft in 2013

https://gerhart01.github.io/

## Geoff Chappell's hvgdk_mini researches

https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/shared/hvgdk_mini/hv_cpuid_function.htm

Note: This document only helps me to know hvgdk.h existance in Windows Driver
Kit version 7.1.0 and symbols in urlmon.dll have the correct name for
HV_CPUID_FUNCTION.

## Windows symbols

- Debuggers\ddk\samples\kdserial\lib\x64\kdhv.lib
  - Version: 10.0.26063.0
  - Local Archive: [Symbols/kdhv.lib](Symbols/kdhv.lib)
- urlmon.dll
  - Version: 11.0.14393.0
  - Local Archive: [Symbols/urlmon.dll](urlmon.dll), [Symbols/urlmon.pdb](urlmon.pdb)

## FreeBSD

https://github.com/freebsd/freebsd-src

## Hyper-V integration support for macOS

https://github.com/acidanthera/MacHyperVSupport

## Hyper-V Hypercall List

According to Hypervisor Top Level Functional Specification and MIT licensed 
Hyper-V headers from Microsoft, I create a list for knowing which hypercalls
need to be contained in Mile.HyperV.

All items from Appendix A of Hypervisor Top Level Functional Specification. All
yellow items are defined in MIT licensed Hyper-V headers from Microsoft. All 
green items are detail defined in Hypervisor Top Level Functional Specification.

- [HvCallList.xlsx](HvCallList.xlsx)
