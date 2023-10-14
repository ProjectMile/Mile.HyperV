# Mile.HyperV Definition References

Mile.HyperV uses both Hypervisor Top Level Functional Specification v6.0b and
MIT licensed Hyper-V headers from Microsoft to create the Hyper-V definition
headers.

## Hypervisor Top Level Functional Specification

- [Microsoft's all version archive]
- [Mile.HyperV's local PDF archive]]

[Microsoft's all version archive]: https://github.com/MicrosoftDocs/Virtualization-Documentation/tree/live/tlfs
[Mile.HyperV's local PDF archive]: Hypervisor Top Level Functional Specification v6.0b.pdf

## MIT licensed Hyper-V headers from Microsoft

Kenji Mouri knows these MIT licensed Hyper-V headers from Microsoft because he
had fired a GitHub issue: https://github.com/rust-vmm/mshv/issues/117

Here is the original reference from Microsoft. They create a Linux kernel patch
called "[PATCH v4 13/15] uapi: hyperv: Add mshv driver headers defining
hypervisor ABIs" to try to make their mshv implementation merge to the mainline.

- [Online version from linux-hyperv mailing list]
- [Mile.HyperV's local Outlook Unicode MSG archive]

[Online version from linux-hyperv mailing list]: https://lore.kernel.org/linux-hyperv/1696010501-24584-1-git-send-email-nunodasneves@linux.microsoft.com/T/#m265e35e841d29ec27c7e60887c1c7566585fc0ff
[Mile.HyperV's local Outlook Unicode MSG archive]: patch-v4-1315-uapi-hyperv-add-mshv-driver-headers-defining-hypervisor-abis.msg

Here is the extracted reference from the mentioned patch created by Microsoft.

- [hvgdk.h](hvgdk.h)
- [hvgdk_mini.h](hvgdk_mini.h)
- [hvhdk.h](hvhdk.h)
- [hvhdk_mini.h](hvhdk_mini.h)
