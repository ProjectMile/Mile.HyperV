# Mile.HyperV

The lightweight library for Hyper-V guest interfaces.

## Usage

Currently, include `Mile.HyperV.TLFS.h` to your C/C++ projects.

## Features

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
- Distributed under the MIT License

## Documents

- [License](License.md)
- [Mile.HyperV Definition References](References/ReadMe.md)
- [Release Notes](ReleaseNotes.md)

## Thanks

- Geoff Chappell, https://www.geoffchappell.com/ for researches hints
- Gerhart, https://github.com/gerhart01 for documentation archive
- Liu Wei, https://github.com/liuw for mshv existance hints
- Mezone, https://github.com/Mez0ne for revise hints
- Nuno Das Neves, https://github.com/NunoDasNeves for mshv implementation
