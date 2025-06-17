/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.TLFS.h
 * PURPOSE:    Definition for Hyper-V Top Level Functional Specification 6.0b
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

// Thanks
// - Geoff Chappell, https://www.geoffchappell.com/ for researches hints
// - Gerhart, https://github.com/gerhart01 for documentation archive
// - Liu Wei, https://github.com/liuw for mshv existance hints
// - Mezone, https://github.com/Mez0ne for revise hints
// - Nuno Das Neves, https://github.com/NunoDasNeves for mshv implementation

// References
// - Hypervisor Top Level Functional Specification 6.0b
// - hvgdk.h from Windows Driver Kit version 7.1.0
// - MIT-licensed Hyper-V headers from Microsoft mshv Linux kernel module
//   - https://github.com/microsoft/OHCL-Linux-Kernel
//     /tree/e9017243ba9b424f6516c4b206f454a1c2585fd2
//     /include/uapi/hyperv
// - gerhart01's archive of Hypervisor (Windows Drivers) documentation from
//   Microsoft in 2013
// - https://github.com/rust-vmm/mshv
// - https://github.com/microsoft/igvm
// - Symbols in Windows Driver Kit version 10.0.26063.0's
//   Debuggers\ddk\samples\kdserial\lib\x64\kdhv.lib
// - Symbols in Windows version 10.0.14393.0's urlmon.dll
// - Geoff Chappell's hvgdk_mini researches hints
//   - hvgdk.h is existed from Windows Driver Kit version 7.1.0
//   - Symbols in Windows version 10.0.14393.0's urlmon.dll have HV symbols
// - Symbols in Windows version 10.0.14347.0's ntoskrnl.exe

#ifndef MILE_HYPERV_TLFS
#define MILE_HYPERV_TLFS

#include "Mile.HyperV.Guest.Interface.h"

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

// Define a 256bit type.
typedef struct HV_DECLSPEC_ALIGN(32) _HV_UINT256
{
    HV_UINT128 Low128;
    HV_UINT128 High128;
} HV_UINT256, *PHV_UINT256;

// Define a 512bit type.
typedef struct HV_DECLSPEC_ALIGN(32) _HV_UINT512
{
    HV_UINT256 Low128;
    HV_UINT256 High128;
} HV_UINT512, *PHV_UINT512;

#define HV_CALL_ATTRIBUTES_ALIGNED(__alignment__) HV_DECLSPEC_ALIGN(__alignment__)

// Memory Types
//
// System physical addresses (SPAs) define the physical address space of the
// underlying hardware. There is only one system physical address space for the
// entire machine.

typedef HV_UINT64 HV_SPA, *PHV_SPA;

#if defined(_M_AMD64) || defined(_M_IX86)

// Number of bytes in a page for X64.
#ifndef X64_PAGE_SIZE
#define X64_PAGE_SIZE HV_X64_PAGE_SIZE
#endif

// Number of bytes in a large page for X64.
#ifndef X64_LARGE_PAGE_SIZE
#define X64_LARGE_PAGE_SIZE HV_X64_LARGE_PAGE_SIZE
#endif

// Number of bytes in a 1GB page for X64.
#ifndef X64_1GB_PAGE_SIZE
#define X64_1GB_PAGE_SIZE HV_X64_LARGE_PAGE_SIZE_1GB
#endif

#define HV_X64_MAX_PAGE_NUMBER (UINT64_MAX/X64_PAGE_SIZE)
#define HV_X64_MAX_LARGE_PAGE_NUMBER (UINT64_MAX/X64_LARGE_PAGE_SIZE)
#define HV_X64_MAX_1GB_PAGE_NUMBER (UINT64_MAX/X64_1GB_PAGE_SIZE)
#define HV_1GB_PAGE_SIZE X64_1GB_PAGE_SIZE
#define HV_PAGE_MASK (HV_PAGE_SIZE - 1)
#define HV_LARGE_PAGE_MASK (HV_LARGE_PAGE_SIZE - 1)
#define HV_1GB_PAGE_MASK (HV_1GB_PAGE_SIZE - 1)

#endif

typedef HV_UINT64 HV_SPA_PAGE_NUMBER, *PHV_SPA_PAGE_NUMBER;
typedef HV_UINT64 HV_GVA_PAGE_NUMBER, *PHV_GVA_PAGE_NUMBER;

typedef const HV_SPA_PAGE_NUMBER *PCHV_SPA_PAGE_NUMBER;
typedef const HV_GPA_PAGE_NUMBER *PCHV_GPA_PAGE_NUMBER;
typedef const HV_GVA_PAGE_NUMBER *PCHV_GVA_PAGE_NUMBER;

typedef HV_UINT16 HV_IO_PORT, *PHV_IO_PORT;

// Forward declare the loader block.
typedef struct _HV_LOADER_BLOCK *PHV_LOADER_BLOCK;

#define HV_STATUS_PROCESSOR_FEATURE_SSE3_NOT_SUPPORTED ((HV_STATUS)0x0020)
#define HV_STATUS_PROCESSOR_FEATURE_LAHFSAHF_NOT_SUPPORTED ((HV_STATUS)0x0021)
#define HV_STATUS_PROCESSOR_FEATURE_SSSE3_NOT_SUPPORTED ((HV_STATUS)0x0022)
#define HV_STATUS_PROCESSOR_FEATURE_SSE4_1_NOT_SUPPORTED ((HV_STATUS)0x0023)
#define HV_STATUS_PROCESSOR_FEATURE_SSE4_2_NOT_SUPPORTED ((HV_STATUS)0x0024)
#define HV_STATUS_PROCESSOR_FEATURE_SSE4A_NOT_SUPPORTED ((HV_STATUS)0x0025)
#define HV_STATUS_PROCESSOR_FEATURE_SSE5_NOT_SUPPORTED ((HV_STATUS)0x0026)
#define HV_STATUS_PROCESSOR_FEATURE_POPCNT_NOT_SUPPORTED ((HV_STATUS)0x0027)
#define HV_STATUS_PROCESSOR_FEATURE_CMPXCHG16B_NOT_SUPPORTED ((HV_STATUS)0x0028)
#define HV_STATUS_PROCESSOR_FEATURE_ALTMOVCR8_NOT_SUPPORTED ((HV_STATUS)0x0029)
#define HV_STATUS_PROCESSOR_FEATURE_LZCNT_NOT_SUPPORTED ((HV_STATUS)0x002A)
#define HV_STATUS_PROCESSOR_FEATURE_MISALIGNED_SSE_NOT_SUPPORTED ((HV_STATUS)0x002B)
#define HV_STATUS_PROCESSOR_FEATURE_MMX_EXT_NOT_SUPPORTED ((HV_STATUS)0x002C)
#define HV_STATUS_PROCESSOR_FEATURE_3DNOW_NOT_SUPPORTED ((HV_STATUS)0x002D)
#define HV_STATUS_PROCESSOR_FEATURE_EXTENDED_3DNOW_NOT_SUPPORTED ((HV_STATUS)0x002E)
#define HV_STATUS_PROCESSOR_FEATURE_PAGE_1GB_NOT_SUPPORTED ((HV_STATUS)0x002F)
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_NOT_SUPPORTED ((HV_STATUS)0x0031)
#define HV_STATUS_PROCESSOR_FEATURE_XSAVEOPT_NOT_SUPPORTED ((HV_STATUS)0x0032)
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_LEGACY_SSE_NOT_SUPPORTED ((HV_STATUS)0x0033)
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_AVX_NOT_SUPPORTED ((HV_STATUS)0x0034)
#define HV_STATUS_PROCESSOR_FEATURE_XSAVE_UNKNOWN_FEATURE_NOT_SUPPORTED ((HV_STATUS)0x0035)
#define HV_STATUS_PROCESSOR_XSAVE_SAVE_AREA_INCOMPATIBLE ((HV_STATUS)0x0036)
#define HV_STATUS_EVENT_BUFFER_ALREADY_FREED ((HV_STATUS)0x0074)
#define HV_STATUS_CALL_PENDING ((HV_STATUS)0x0079)
#define HV_STATUS_VTL_ALREADY_ENABLED ((HV_STATUS)0x0086)

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_FP_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        HV_UINT64 Mantissa;
        HV_UINT64 BiasedExponent : 15;
        HV_UINT64 Sign : 1;
        HV_UINT64 Reserved : 48;
    };
} HV_X64_FP_REGISTER, *PHV_X64_FP_REGISTER;

typedef union _HV_X64_FP_CONTROL_STATUS_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        HV_UINT16 FpControl;
        HV_UINT16 FpStatus;
        HV_UINT8 FpTag;
        HV_UINT8 IgnNe : 1;
        HV_UINT8 Reserved : 7;
        HV_UINT16 LastFpOp;
        union
        {
            HV_UINT64 LastFpRip; // Long Mode
            struct // 32 Bit Mode
            {
                HV_UINT32 LastFpEip;
                HV_UINT16 LastFpCs;
            };
        };
    };
} HV_X64_FP_CONTROL_STATUS_REGISTER, *PHV_X64_FP_CONTROL_STATUS_REGISTER;

typedef union _HV_X64_XMM_CONTROL_STATUS_REGISTER
{
    HV_UINT128 AsUINT128;
    struct
    {
        union
        {
            HV_UINT64 LastFpRdp; // Long Mode
            struct // 32 Bit Mode
            {
                HV_UINT32 LastFpDp;
                HV_UINT16 LastFpDs;
            };
        };
        HV_UINT32 XmmStatusControl;
        HV_UINT32 XmmStatusControlMask;
    };
} HV_X64_XMM_CONTROL_STATUS_REGISTER, *PHV_X64_XMM_CONTROL_STATUS_REGISTER;
#endif

// An architecture is a set of processor instruction sets and operating modes
typedef enum _HV_ARCHITECTURE
{
    HvArchitectureX64,
    HvArchitectureX86,
    HvArchitectureARM64,
    HvArchitectureMaximum
} HV_ARCHITECTURE, *PHV_ARCHITECTURE;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_FP_MMX_REGISTER
{
    HV_UINT128 AsUINT128;
    HV_X64_FP_REGISTER Fp;
    HV_UINT64 Mmx;
} HV_X64_FP_MMX_REGISTER, *PHV_X64_FP_MMX_REGISTER;

// The FX Save Area is defined to be 512 bytes in size
#define HV_X64_FXSAVE_AREA_SIZE  512

// FX registers are legacy extended state registers managed by the FXSAVE and
// FXRSTOR instructions. This includes legacy FP and SSE registers.
typedef union HV_DECLSPEC_ALIGN(16) _HV_X64_FX_REGISTERS
{
    struct
    {
        HV_X64_FP_CONTROL_STATUS_REGISTER FpControlStatus;
        HV_X64_XMM_CONTROL_STATUS_REGISTER XmmControlStatus;
        HV_X64_FP_MMX_REGISTER FpMmx[8];
        HV_UINT128 Xmm[16];
    };
    HV_UINT8 FxSaveArea[HV_X64_FXSAVE_AREA_SIZE];
} HV_X64_FX_REGISTERS, *PHV_X64_FX_REGISTERS;

// XSAVE erea definitions.

// The XSAVE XFEM (XSAVE Feature Enabled Mask) register.
typedef union _HV_X64_XSAVE_XFEM_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 LowUINT32;
        HV_UINT32 HighUINT32;
    };
    struct
    {
        HV_UINT64 LegacyX87 : 1;
        HV_UINT64 LegacySse : 1;
        HV_UINT64 Avx : 1;
        HV_UINT64 MpxBndreg : 1;
        HV_UINT64 MpxBndcsr : 1;
        HV_UINT64 Avx512OpMask : 1;
        HV_UINT64 Avx512Zmmhi : 1;
        HV_UINT64 Avx512Zmm16_31 : 1;
        HV_UINT64 Reserved : 2;
        HV_UINT64 Pasid : 1;
        HV_UINT64 CetU : 1;
        HV_UINT64 CetS : 1;
        HV_UINT64 Reserved1 : 4;
        HV_UINT64 XtileCfg : 1;
        HV_UINT64 XtileData : 1;
        HV_UINT64 Reserved2 : 45;
    };
} HV_X64_XSAVE_XFEM_REGISTER, *PHV_X64_XSAVE_XFEM_REGISTER;

// This structure represents the header area of an XSAVE area.
// This must be alligned on a 64 byte boundary.
typedef struct HV_DECLSPEC_ALIGN(64) _HV_X64_XSAVE_HEADER
{
    // Bit vector indicating which features have state store in the XSAVE area.
    HV_X64_XSAVE_XFEM_REGISTER XstateBv; // Bit 63 MBZ
    HV_UINT64 Reserved0MBZ; // Must be 0.
    HV_UINT16 RevisionID;
    HV_UINT16 Reserved1MBZ; // Must be 0.
    HV_UINT32 Reserved2;
    HV_UINT64 Reserved3;
    HV_UINT64 Reserved4;
    HV_UINT64 Reserved5;
    HV_UINT64 Reserved6;
    HV_UINT64 Reserved7;
} HV_X64_XSAVE_HEADER, *PHV_X64_XSAVE_HEADER;

// This is the size of the legacy save area (512) plus the size of the XSAVE
// header (64) plus the size of the AVX context (16 128-bit registers).

// Extra notes from Mile.HyperV.TLFS:
// For Windows 10 ntoskrnl.exe symbol types, the HV_X64_XSAVE_AREA_SIZE should
// be 2688. So, I do some guess based on
// https://www.moritz.systems/blog/how-debuggers-work-getting-and-setting-x86-registers-part-2/

#define HV_X64_XSAVE_AREA_HEADER_SIZE 64
#define HV_X64_XSAVE_AREA_AVX_SIZE 256
#define HV_X64_XSAVE_AREA_MPX_SIZE 80
#define HV_X64_XSAVE_AREA_AVX512_SIZE 1600
#define HV_X64_XSAVE_AREA_PT_SIZE 72
#define HV_X64_XSAVE_AREA_PKRU_SIZE 4
#define HV_X64_XSAVE_AREA_HDC_SIZE 8
#define HV_X64_XSAVE_AREA_UNKNOWN_SIZE 92
#define HV_X64_XSAVE_AREA_SIZE ( \
    HV_X64_FXSAVE_AREA_SIZE + \
    HV_X64_XSAVE_AREA_HEADER_SIZE + \
    HV_X64_XSAVE_AREA_AVX_SIZE + \
    HV_X64_XSAVE_AREA_MPX_SIZE + \
    HV_X64_XSAVE_AREA_AVX512_SIZE + \
    HV_X64_XSAVE_AREA_PT_SIZE + \
    HV_X64_XSAVE_AREA_PKRU_SIZE + \
    HV_X64_XSAVE_AREA_HDC_SIZE + \
    HV_X64_XSAVE_AREA_UNKNOWN_SIZE)

// This structure defines the format of the XSAVE save area, the area used to
// save and restore the context of processor extended state (including legacy
// FP and SSE state) by the XSAVE and XRSTOR instructions.
// N.B. The XSAVE header must be aligned on a 64 byte boundary. Therefore this
// structure must be 64 byte aligned.
typedef union HV_DECLSPEC_ALIGN(64) _HV_X64_X_REGISTERS
{
    struct
    {
        HV_X64_FP_CONTROL_STATUS_REGISTER FpControlStatus;
        HV_X64_XMM_CONTROL_STATUS_REGISTER XmmControlStatus;
        HV_X64_FP_MMX_REGISTER FpMmx[8];
        union
        {
            HV_UINT128 Xmm[16];
            HV_UINT128 YmmLow[16];
        };
        HV_UINT128 Reserved[6];
        HV_X64_XSAVE_HEADER Header;
        // AVX context: the upper 128 bits of the YMM registers. The lower 128
        // bits overlay the XMM registers.
        HV_UINT128 YmmHigh[16];
    };
    HV_UINT8 XSaveArea[HV_X64_XSAVE_AREA_SIZE];
} HV_X64_X_REGISTERS, *PHV_X64_X_REGISTERS;

typedef struct _HV_X64_CONTEXT
{
    // The Initial APIC ID pseudo register. This is the value returned by CPUID.
    HV_UINT64 InitialApicId;

    // 16 64 bit general purpose registers, instruction pointer and flags

    HV_UINT64 Rax;
    HV_UINT64 Rbx;
    HV_UINT64 Rcx;
    HV_UINT64 Rdx;
    HV_UINT64 Rsi;
    HV_UINT64 Rdi;
    HV_UINT64 Rbp;
    HV_UINT64 Rsp;
    HV_UINT64 R8;
    HV_UINT64 R9;
    HV_UINT64 R10;
    HV_UINT64 R11;
    HV_UINT64 R12;
    HV_UINT64 R13;
    HV_UINT64 R14;
    HV_UINT64 R15;
    HV_UINT64 Rip;
    HV_UINT64 Rflags;

    // Control Registers - on 32 bit platforms the upper 32 bits are ignored.
    // Efer is actually an Msr but it acts as an extension to Cr4 and as such
    // is treated as a processor register. Cr8 is only valid on 64 bit systems.

    HV_UINT64 Cr0;
    HV_UINT64 Cr2;
    HV_UINT64 Cr3;
    HV_UINT64 Cr4;
    HV_UINT64 Cr8;
    HV_UINT64 Efer;

    // XSAVE Control Registers - only on platforms that support the XSAVE/XRSTOR
    // feature.

    // XCR0 is XFEM, XSAVE Feature Enabled Mask.

    HV_UINT64 Xfem;

    // Debug Registers - on 32 bit platforms the upper 32 bits are ignored

    HV_UINT64 Dr0;
    HV_UINT64 Dr1;
    HV_UINT64 Dr2;
    HV_UINT64 Dr3;
    HV_UINT64 Dr6;
    HV_UINT64 Dr7;

    // Global and Interrupt Descriptor tables

    HV_X64_TABLE_REGISTER Idtr;
    HV_X64_TABLE_REGISTER Gdtr;

    // Segment selector registers together with their hidden state.

    HV_X64_SEGMENT_REGISTER Cs;
    HV_X64_SEGMENT_REGISTER Ds;
    HV_X64_SEGMENT_REGISTER Es;
    HV_X64_SEGMENT_REGISTER Fs;
    HV_X64_SEGMENT_REGISTER Gs;
    HV_X64_SEGMENT_REGISTER Ss;
    HV_X64_SEGMENT_REGISTER Tr;
    HV_X64_SEGMENT_REGISTER Ldtr;

    // MSRs needed for virtualization

    HV_UINT64 KernelGsBase;
    HV_UINT64 Star;
    HV_UINT64 Lstar;
    HV_UINT64 Cstar;
    HV_UINT64 Sfmask;
    HV_UINT64 SysenterCs;
    HV_UINT64 SysenterEip;
    HV_UINT64 SysenterEsp;
    HV_UINT64 MsrCrPat;
    // HV_UINT64 MsrMtrrCap; // Seems not available in Windows 10 symbols
    // HV_UINT64 MsrMtrrDefType; // Seems not available in Windows 10 symbols
    // HV_UINT64 MsrMtrrFixed[11]; // Seems not available in Windows 10 symbols
    // HV_UINT64 MsrMtrrVariableBase[8]; // Seems not available in Windows 10 symbols
    // HV_UINT64 MsrMtrrVariableMask[8]; // Seems not available in Windows 10 symbols

    // Local APIC state.

    HV_UINT32 LocalApicId;
    HV_UINT32 LocalApicVersion;
    HV_UINT32 LocalApicLdr;
    HV_UINT32 LocalApicDfr;
    HV_UINT32 LocalApicSpurious;
    HV_UINT32 LocalApicIcrLow;
    HV_UINT32 LocalApicIcrHigh;
    HV_UINT32 LocalApicIsr[8];
    HV_UINT32 LocalApicTmr[8];
    HV_UINT32 LocalApicLvtTimer;
    HV_UINT32 LocalApicLvtPerfmon;
    HV_UINT32 LocalApicLvtLint0;
    HV_UINT32 LocalApicLvtLint1;
    HV_UINT32 LocalApicCurrentCount;
    HV_UINT32 LocalApicInitialCount;
    HV_UINT32 LocalApicDivider;
    HV_UINT64 LocalApicBaseMsr;

    union
    {
        // x87 Floating point, MMX and XMM registers formatted as by
        // FXSAVE/FXSTOR.
        HV_X64_FX_REGISTERS FxRegisters;
        // x87 Floating point, MMX XMM and YMM registers formatted as by
        // XSAVE/XRSTOR.
        // Only on platforms that support XSAVE/XRSTOR.
        HV_X64_X_REGISTERS XRegisters;
    };
} HV_X64_CONTEXT, *PHV_X64_CONTEXT;
#endif

#if defined(_M_ARM64)
typedef struct _HV_ARM64_CONTEXT
{
    HV_UINT64 X0;
    HV_UINT64 X1;
    HV_UINT64 X2;
    HV_UINT64 X3;
    HV_UINT64 X4;
    HV_UINT64 X5;
    HV_UINT64 X6;
    HV_UINT64 X7;
    HV_UINT64 X8;
    HV_UINT64 X9;
    HV_UINT64 X10;
    HV_UINT64 X11;
    HV_UINT64 X12;
    HV_UINT64 X13;
    HV_UINT64 X14;
    HV_UINT64 X15;
    HV_UINT128 Q0;
    HV_UINT128 Q1;
    HV_UINT128 Q2;
    HV_UINT128 Q3;
    HV_UINT128 Q4;
    HV_UINT128 Q5;
    HV_UINT128 Q6;
    HV_UINT128 Q7;
    HV_UINT128 Q16;
    HV_UINT128 Q17;
    HV_UINT128 Q18;
    HV_UINT128 Q19;
    HV_UINT128 Q20;
    HV_UINT128 Q21;
    HV_UINT128 Q22;
    HV_UINT128 Q23;
    HV_UINT128 Q24;
    HV_UINT128 Q25;
    HV_UINT128 Q26;
    HV_UINT128 Q27;
    HV_UINT128 Q28;
    HV_UINT128 Q29;
    HV_UINT128 Q30;
    HV_UINT128 Q31;
    HV_UINT64 X16;
    HV_UINT64 X17;
    HV_UINT64 X18;
    HV_UINT64 X19;
    HV_UINT64 X20;
    HV_UINT64 X21;
    HV_UINT64 X22;
    HV_UINT64 X23;
    HV_UINT64 X24;
    HV_UINT64 X25;
    HV_UINT64 X26;
    HV_UINT64 X27;
    HV_UINT64 X28;
    HV_UINT64 XFp;
    HV_UINT64 XLr;
    HV_UINT128 Q8;
    HV_UINT128 Q9;
    HV_UINT128 Q10;
    HV_UINT128 Q11;
    HV_UINT128 Q12;
    HV_UINT128 Q13;
    HV_UINT128 Q14;
    HV_UINT128 Q15;
    HV_UINT32 Cpsr;
    HV_UINT64 Sp;
    HV_UINT64 Pc;
    HV_UINT64 SCTLR_EL1;
    HV_UINT64 ACTLR_EL1;
    HV_UINT64 CPACR_EL1;
    HV_UINT64 TPIDRRO_EL0;
    HV_UINT64 TPIDR_EL0;
    HV_UINT64 TTBR0_EL1;
    HV_UINT64 TTBR1_EL1;
    HV_UINT64 TCR_EL1;
    HV_UINT64 ESR_EL1;
    HV_UINT64 FAR_EL1;
    HV_UINT64 PAR_EL1;
    HV_UINT64 MAIR_EL1;
    HV_UINT64 VBAR_EL1;
    HV_UINT64 CONTEXTIDR_EL1;
    HV_UINT64 TPIDR_EL1;
    HV_UINT64 SPSR_EL1;
    HV_UINT64 ELR_EL1;
    HV_UINT64 AFSR0_EL1;
    HV_UINT64 AFSR1_EL1;
    HV_UINT64 AMAIR_EL1;
} HV_ARM64_CONTEXT, *PHV_ARM64_CONTEXT;
#endif

#define HV_VIRTUAL_PROCESSOR_REGISTERS_VERSION 1

typedef struct _HV_VP_CONTEXT
{
    // The version of the HV_VP_CONTEXT structure
    HV_UINT32 Version;
    // The architecture of these registers
    HV_ARCHITECTURE Architecture;
    union
    {
#if defined(_M_AMD64) || defined(_M_IX86)
        HV_X64_CONTEXT x64;
#endif
#if defined(_M_ARM64)
        HV_ARM64_CONTEXT aa64;
#endif
    };
} HV_VP_CONTEXT, *PHV_VP_CONTEXT;

typedef HV_UINT16 HV_STATISTICS_GROUP_TYPE;
typedef HV_UINT16 HV_STATISTICS_GROUP_LENGTH;

typedef struct _HV_STATISTICS_GROUP_VERSION
{
    HV_UINT16 Minor;
    HV_UINT16 Major;
} HV_STATISTICS_GROUP_VERSION;

// Group header
typedef struct HV_DECLSPEC_ALIGN(2) _HV_STATISTICS_GROUP_HEADER
{
    HV_STATISTICS_GROUP_TYPE Type;
    HV_STATISTICS_GROUP_VERSION Version;
    HV_STATISTICS_GROUP_LENGTH Length;
} HV_STATISTICS_GROUP_HEADER, *PHV_STATISTICS_GROUP_HEADER;

#define HV_STATISTICS_GROUP_END_OF_LIST 0
#define HV_STATISTICS_GROUP_END_OF_PAGE 1

// Pseudo-group to use in manifest for counters accessible through  hypercalls.
#define HV_STATISTICS_GROUP_HYPERCALL_BASED 15

// Definitions for the hypervisor counters statistics page

#define HV_STATISTICS_GROUP_HVA_ID 2
#define HV_STATISTICS_GROUP_HVA_VERSION 0x00010000
#define HV_STATISTICS_GROUP_HVV_ID 3
#define HV_STATISTICS_GROUP_HVV_VERSION 0x00010000
#define HV_STATISTICS_GROUP_HVI_ID 14
#define HV_STATISTICS_GROUP_HVI_VERSION 0x00010000

// Definitions for the logical processor counters statistics page

#define HV_STATISTICS_GROUP_LPA_ID 2
#define HV_STATISTICS_GROUP_LPA_VERSION 0x00010000
#define HV_STATISTICS_GROUP_LPV_ID 3
#define HV_STATISTICS_GROUP_LPV_VERSION 0x00010000
#define HV_STATISTICS_GROUP_LPI_ID 14
#define HV_STATISTICS_GROUP_LPI_VERSION 0x00010000

// Definitions for the partition counters statistics page

#define HV_STATISTICS_GROUP_PTA_ID 2
#define HV_STATISTICS_GROUP_PTA_VERSION 0x00010000
#define HV_STATISTICS_GROUP_PTV_ID 3
#define HV_STATISTICS_GROUP_PTV_VERSION 0x00010000
#define HV_STATISTICS_GROUP_PTI_ID 14
#define HV_STATISTICS_GROUP_PTI_VERSION 0x00010000

// Definitions for the virtual processor statistics page

#define HV_STATISTICS_GROUP_VPA_ID 2
#define HV_STATISTICS_GROUP_VPA_VERSION 0x00010000
#define HV_STATISTICS_GROUP_VPV_ID 3
#define HV_STATISTICS_GROUP_VPV_VERSION 0x00010000
#define HV_STATISTICS_GROUP_VPI_ID 14
#define HV_STATISTICS_GROUP_VPI_VERSION 0x00010000

// Maximum counters allowed per group. Calculated for the case when group
// occupies full page: there will be two headers (one for the group and one
// terminating the list).
#define HV_ST_MAX_COUNTERS_PER_GROUP \
    ((HV_PAGE_SIZE - 2 * sizeof(HV_STATISTICS_GROUP_HEADER)) / sizeof(HV_UINT64))

// Definition of the counters structure.
typedef struct _HV_STATS_PAGE
{
    HV_UINT64 Data[HV_PAGE_SIZE / sizeof(HV_UINT64)];

} HV_STATS_PAGE, *PHV_STATS_PAGE;

// Definition for the stats object types.
typedef enum _HV_STATS_OBJECT_TYPE
{
    // Global stats objects

    HvStatsObjectHypervisor = 0x00000001,
    HvStatsObjectLogicalProcessor = 0x00000002,

    // Local stats objects

    HvStatsObjectPartition = 0x00010001,
    HvStatsObjectVp = 0x00010002
} HV_STATS_OBJECT_TYPE, *PHV_STATS_OBJECT_TYPE;

// Definition for the stats map/unmap MSR value.
typedef union _HV_ST_MAP_LOCATION
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MapEnabled : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 BaseMapGpaPageNumber : 52;
    };
} HV_ST_MAP_LOCATION, *PHV_ST_MAP_LOCATION;

// Hypervisor global counter set
typedef enum _HV_HYPERVISOR_COUNTER
{
    StHvCounterLogicalProcessors = 1,
    StHvCounterPartitions = 2,
    StHvCounterTotalPages = 3,
    StHvCounterVirtualProcessors = 4,
    StHvCounterMonitoredNotifications = 5,
    StHvCounterMAXIMUM
} HV_HYPERVISOR_COUNTER, *PHV_HYPERVISOR_COUNTER;

#define HV_STATISTICS_GROUP_HVA_LENGTH 40
#define HV_STATISTICS_GROUP_HVV_LENGTH 0

// Hypervisor Logical Processor counter set
typedef enum _HV_CPU_COUNTER
{
    StLpCounterGlobalTime = 1,
    StLpCounterTotalRunTime = 2,
    StLpCounterHypervisorRunTime = 3,
    StLpCounterHardwareInterrupts = 4,
    StLpCounterContextSwitches = 5,
    StLpCounterInterProcessorInterrupts = 6,
    StLpCounterSchedulerInterrupts = 7,
    StLpCounterTimerInterrupts = 8,
    StLpCounterInterProcessorInterruptsSent = 9,
    StLpCounterProcessorHalts = 10,
    StLpCounterMonitorTransitionCost = 11,
    StLpCounterContextSwitchTime = 12,
    StLpCounterC1TransitionsCount = 13,
    StLpCounterC1RunTime = 14,
    StLpCounterC2TransitionsCount = 15,
    StLpCounterC2RunTime = 16,
    StLpCounterC3TransitionsCount = 17,
    StLpCounterC3RunTime = 18,
    StLpCounterMAXIMUM
} HV_CPU_COUNTER;

#define HV_STATISTICS_GROUP_LPA_LENGTH 144
#define HV_STATISTICS_GROUP_LPV_LENGTH 0

// Partition counter set
typedef enum _HV_PROCESS_COUNTER
{
    StPtCounterVirtualProcessors = 1,
    StPtCounterTlbSize = 3,
    StPtCounterAddressSpaces = 4,
    StPtCounterDepositedPages = 5,
    StPtCounterGpaPages = 6,
    StPtCounterGpaSpaceModifications = 7,
    StPtCounterVirtualTlbFlushEntires = 8,
    StPtCounterRecommendedTlbSize = 9,
    StPtCounterGpaPages4K = 10,
    StPtCounterGpaPages2M = 11,
    StPtCounterGpaPages1G = 12,
    StPtCounterGpaPages512G = 13,
    StPtCounterMAXIMUM
} HV_PROCESS_COUNTER;

#define HV_STATISTICS_GROUP_PTA_LENGTH 8
#define HV_STATISTICS_GROUP_PTV_LENGTH 88

// Hypervisor Virtual Processor counter set
typedef enum _HV_THREAD_COUNTER
{
    StVpCounterTotalRunTime = 1,
    StVpCounterHypervisorRunTime = 2,
    StVpCounterHypercallsCount = 4,
    StVpCounterHypercallsTime = 5,
    StVpCounterPageInvalidationsCount = 6,
    StVpCounterPageInvalidationsTime = 7,
    StVpCounterControlRegisterAccessesCount = 8,
    StVpCounterControlRegisterAccessesTime = 9,
    StVpCounterIoInstructionsCount = 10,
    StVpCounterIoInstructionsTime = 11,
    StVpCounterHltInstructionsCount = 12,
    StVpCounterHltInstructionsTime = 13,
    StVpCounterMwaitInstructionsCount = 14,
    StVpCounterMwaitInstructionsTime = 15,
    StVpCounterCpuidInstructionsCount = 16,
    StVpCounterCpuidInstructionsTime = 17,
    StVpCounterMsrAccessesCount = 18,
    StVpCounterMsrAccessesTime = 19,
    StVpCounterOtherInterceptsCount = 20,
    StVpCounterOtherInterceptsTime = 21,
    StVpCounterExternalInterruptsCount = 22,
    StVpCounterExternalInterruptsTime = 23,
    StVpCounterPendingInterruptsCount = 24,
    StVpCounterPendingInterruptsTime = 25,
    StVpCounterEmulatedInstructionsCount = 26,
    StVpCounterEmulatedInstructionsTime = 27,
    StVpCounterDebugRegisterAccessesCount = 28,
    StVpCounterDebugRegisterAccessesTime = 29,
    StVpCounterPageFaultInterceptsCount = 30,
    StVpCounterPageFaultInterceptsTime = 31,
    StVpCounterGuestPageTableMaps = 32,
    StVpCounterLargePageTlbFills = 33,
    StVpCounterSmallPageTlbFills = 34,
    StVpCounterReflectedGuestPageFaults = 35,
    StVpCounterApicMmioAccesses = 36,
    StVpCounterIoInterceptMessages = 37,
    StVpCounterMemoryInterceptMessages = 38,
    StVpCounterApicEoiAccesses = 39,
    StVpCounterOtherMessages = 40,
    StVpCounterPageTableAllocations = 41,
    StVpCounterLogicalProcessorMigrations = 42,
    StVpCounterAddressSpaceEvictions = 43,
    StVpCounterAddressSpaceSwitches = 44,
    StVpCounterAddressDomainFlushes = 45,
    StVpCounterAddressSpaceFlushes = 46,
    StVpCounterGlobalGvaRangeFlushes = 47,
    StVpCounterLocalGvaRangeFlushes = 48,
    StVpCounterPageTableEvictions = 49,
    StVpCounterPageTableReclamations = 50,
    StVpCounterPageTableResets = 51,
    StVpCounterPageTableValidations = 52,
    StVpCounterApicTprAccesses = 53,
    StVpCounterPageTableWriteIntercepts = 54,
    StVpCounterSyntheticInterrupts = 55,
    StVpCounterVirtualInterrupts = 56,
    StVpCounterApicIpisSent = 57,
    StVpCounterApicSelfIpisSent = 58,
    StVpCounterGpaSpaceHypercalls = 59,
    StVpCounterLogicalProcessorHypercalls = 60,
    StVpCounterLongSpinWaitHypercalls = 61,
    StVpCounterOtherHypercalls = 62,
    StVpCounterSyntheticInterruptHypercalls = 63,
    StVpCounterVirtualInterruptHypercalls = 64,
    StVpCounterVirtualMmuHypercalls = 65,
    StVpCounterVirtualProcessorHypercalls = 66,
    StVpCounterMAXIMUM
} HV_THREAD_COUNTER;

#define HV_STATISTICS_GROUP_VPA_LENGTH 16
#define HV_STATISTICS_GROUP_VPV_LENGTH 504

// Declare the timestamp type.
typedef HV_UINT64 HV_TIME_STAMP, *PHV_TIME_STAMP;

// Logical processors are defined by a 32-bit index
typedef HV_UINT32 HV_LOGICAL_PROCESSOR_INDEX, *PHV_LOGICAL_PROCESSOR_INDEX;

// This described the various methods for changing power state
typedef enum _HV_X64_PPM_IDLE_STATE_CHANGE_METHOD
{
    HvX64PowerChangeIssueHlt,
    HvX64PowerChangeReadIoThenIssueHlt,
    HvX64PowerChangeReadIo,
    HvX64PowerChangeIssueMwait
} HV_X64_PPM_IDLE_STATE_CHANGE_METHOD, * PHV_X64_PPM_IDLE_STATE_CHANGE_METHOD;

// Define interrupt types.
typedef enum _HV_INTERRUPT_TYPE
{
#if defined(_M_ARM64)
    // Explicit interrupt types.
    HvArm64InterruptTypeFixed = 0x0000,

    // Maximum (exclusive) value of interrupt type.
    HvArm64InterruptTypeMaximum = 0x0008,
#elif defined(_M_AMD64) || defined(_M_IX86)
    // Explicit interrupt types.

    HvX64InterruptTypeFixed = 0x0000,
    HvX64InterruptTypeLowestPriority = 0x0001,
    HvX64InterruptTypeSmi = 0x0002,
    HvX64InterruptTypeRemoteRead = 0x0003,
    HvX64InterruptTypeNmi = 0x0004,
    HvX64InterruptTypeInit = 0x0005,
    HvX64InterruptTypeSipi = 0x0006,
    HvX64InterruptTypeExtInt = 0x0007,
    HvX64InterruptTypeLocalInt0 = 0x0008,
    HvX64InterruptTypeLocalInt1 = 0x0009,

    // Maximum (exclusive) value of interrupt type.
    HvX64InterruptTypeMaximum = 0x000A,
#endif
} HV_INTERRUPT_TYPE, *PHV_INTERRUPT_TYPE;

// Define interrupt vector type.
typedef HV_UINT32 HV_INTERRUPT_VECTOR, *PHV_INTERRUPT_VECTOR;

// Define special "no interrupt vector" value used by hypercalls that indicate
// whether the previous virtual interrupt was acknowledged.
#define HV_INTERRUPT_VECTOR_NONE 0xFFFFFFFF

// Define profile sources.
// N.B. The total number of profile sources is limited to 2048.
typedef enum _HV_PROFILE_SOURCE
{
    // Profile sources for all processors

    HvProfileInvalid,
    HvProfileCyclesNotHalted = 1,
    HvProfileCacheMisses,
    HvProfileBranchMispredictions,

    // Profile sources for for AMD processors.

    HvProfileDispatchedFPUOps = 64,
    HvProfileCyclesNoFPUOpsRetired,
    HvProfileDispathedFPUOpsWithFastFlag,
    HvProfileRetiredSSEOps,
    HvProfileRetiredMoveOps,
    HvProfileSegmentRegisterLoad,
    HvProfileResyncBySelfModifyingCode,
    HvProfileResyncBySnoop,
    HvProfileBuffer2Full,
    HvProfileLockedOperation,
    HvProfileRetiredCLFLUSH,
    HvProfileRetiredCPUID,
    HvProfileLSDispatch,
    HvProfileCancelledStoreToLoadFwdOperations,
    HvProfileSMIReceived,
    HvProfileDataAccess,
    HvProfileDataMiss,
    HvProfileDCRefillFromL2,
    HvProfileDCRefillFromSystem,
    HvProfileDCRefillCopyBack,
    HvProfileDCL1DTLBMissL2DTLBHit,
    HvProfileDCL1DTLBMissL2DTLBMiss,
    HvProfileDCMisalignedDataReference,
    HvProfileDCLateCancelOfAnAccess,
    HvProfileDCEarlyCancelOfAnAccess,
    HvProfileDCOneBitECCError,
    HvProfileDCDispatchedPrefetchInstructions,
    HvProfileDCacheMissByLockedInstructions,
    HvProfileL1DTLBHit,
    HvProfileL1DTLBReloadLatency,
    HvProfileIneffectiveSoftwarePrefetches,
    HvProfileGlobalTLBFlushes,
    HvProfileRetiredINVLPGAndINVLPGA,
    HvProfileMemoryAccessesToUC,
    HvProfileMemoryAccessesToWCAndWCBufferFlushToWB,
    HvProfileStreamStoreToWB,
    HvProfileDataPrefetchCancelled,
    HvProfileDataPrefetchAttempts,
    HvProfileMABRequests,
    HvProfileNBReadResponsesForForCacheRefill,
    HvProfileOctwordsWriitenToSystem,
    HvProfilePageTableWalkerPDPERefillHitInL2,
    HvProfilePageTableWalkerPDPELookupMissedInPDC,
    HvProfilePageTableWalkerPML4ERefillHitInL2,
    HvProfilePageTableWalkerPML4ELookupMissedInPDC,
    HvProfilePageTableWalkerPTERefillHitInL2,
    HvProfilePageTableWalkerPDERefillHitInL2,
    HvProfilePageTableWalkerPDELookupMissedInPDC,
    HvProfilePageTableWalkerPDELookupInPDC,
    HvProfileProbeHits,
    HvProfileCacheCrossInvalidates,
    HvProfileTLBFlushEvents,
    HvProfileL2Request,
    HvProfileL2CacheMisses,
    HvProfileL2CacheMissesICFill,
    HvProfileL2CacheMissesDCFill,
    HvProfileL2CacheMissesTLBPageTableWalk,
    HvProfileL2Fill,
    HvProfileICFetch,
    HvProfileICMiss,
    HvProfileICRefillFromL2,
    HvProfileICRefillFromSystem,
    HvProfileICL1TLBMissL2TLBHit,
    HvProfileICL1TLBMissL2TLBMiss,
    HvProfileICResyncBySnoop,
    HvProfileICInstructionFetchStall,
    HvProfileICReturnStackHit,
    HvProfileICReturnStackOverflow,
    HvProfileInstructionCacheVictims,
    HvProfileInstructionCacheLinesInvalidated,
    HvProfileITLBReloads,
    HvProfileITLBReloadsAborted,
    HvProfileRetiredInstructions,
    HvProfileRetireduops,
    HvProfileRetiredBranches,
    HvProfileRetiredBranchesMispredicted,
    HvProfileTakenBranches,
    HvProfileTakenBranchesMispredicted,
    HvProfileRetiredFarControlTransfers,
    HvProfileRetiredResyncsNonControlTransferBranches,
    HvProfileRetiredNearReturns,
    HvProfileRetiredNearReturnsMispredicted,
    HvProfileTakenBranchesMispredictedByAddressMiscompare,
    HvProfileRetiredFPUInstructions,
    HvProfileRetiredFastpathDoubleOpInstructions,
    HvProfileInterruptsMaskedCycles,
    HvProfileInterruptsMaskedWhilePendingCycles,
    HvProfileTakenHardwareInterrupts,
    HvProfileNothingToDispatch,
    HvProfileDispatchStalls,
    HvProfileDispatchStallsFromBranchAbortToRetire,
    HvProfileDispatchStallsForSerialization,
    HvProfileDispatchStallsForSegmentLoad,
    HvProfileDispatchStallsWhenReorderBufferFull,
    HvProfileDispatchStallsWhenReservationStationsFull,
    HvProfileDispatchStallsWhenFPUFull,
    HvProfileDispatchStallsWhenLSFull,
    HvProfileDispatchStallsWhenWaitingForAllQuiet,
    HvProfileDispatchStallsWhenFarControlOrResyncBranchPending,
    HvProfileFPUExceptions,
    HvProfileNumberOfBreakPointsForDR0,
    HvProfileNumberOfBreakPointsForDR1,
    HvProfileNumberOfBreakPointsForDR2,
    HvProfileNumberOfBreakPointsForDR3,
    HvProfileDRAMAccess,
    HvProfileDRAMPageTableOverflow,
    HvProfileDRAMDRAMCommandSlotsMissed,
    HvProfileMemoryControllerTurnAround,
    HvProfileMemoryControllerBypassCounter,
    HvProfileSizedCommands,
    HvProfileProbeResult,
    HvProfileUpstreamRequest,
    HvProfileHyperTransportBus0Bandwidth,
    HvProfileHyperTransportBus1Bandwidth,
    HvProfileHyperTransportBus2Bandwidth,
    HvProfileGuestTLBMissesAndInvalidates,
    HvProfileGuestTLBMisses,
    HvProfileGuestTLBInvalidates,
    HvProfileHostPageLargerThanGuestPage_RevC,
    HvProfilePageSizeMismatchCausedByMTRR_RevC,
    HvProfileGuestPageLargerThanHostPage_RevC,
    HvProfileInterruptChecks,
    HvProfileRetiredLFENCE,
    HvProfileRetiredSFENCE,
    HvProfileRetiredMFENCE,
    HvProfileCPUToDRAMRequestsLocalToNode0,
    HvProfileCPUToDRAMRequestsLocalToNode1,
    HvProfileCPUToDRAMRequestsLocalToNode2,
    HvProfileCPUToDRAMRequestsLocalToNode3,
    HvProfileCPUToDRAMRequestsLocalToNode4,
    HvProfileCPUToDRAMRequestsLocalToNode5,
    HvProfileCPUToDRAMRequestsLocalToNode6,
    HvProfileCPUToDRAMRequestsLocalToNode7,
    HvProfileIOToDRAMRequestsLocalToNode0,
    HvProfileIOToDRAMRequestsLocalToNode1,
    HvProfileIOToDRAMRequestsLocalToNode2,
    HvProfileIOToDRAMRequestsLocalToNode3,
    HvProfileIOToDRAMRequestsLocalToNode4,
    HvProfileIOToDRAMRequestsLocalToNode5,
    HvProfileIOToDRAMRequestsLocalToNode6,
    HvProfileIOToDRAMRequestsLocalToNode7,
    HvProfileCPURequestsToAPIC,

    // Profile source descriptors for Intel processors.

    HvProfileInstructionsRetired = 512,
    HvProfileUnhaltedReferenceCycles,
    HvProfileLLCReference,
    HvProfileLLCMisses,
    HvProfileBranchInstuctionRetired,
    HvProfileBranchMispredict
} HV_PROFILE_SOURCE;

// In a NUMA system processors, memory and devices may reside in different
// firmware described proximity domains.
// On a non-NUMA system everything resides in proximity domain 0.
typedef HV_UINT32 HV_PROXIMITY_DOMAIN_ID, *PHV_PROXIMITY_DOMAIN_ID;

// Define the proximity domain information flags.
typedef struct _HV_PROXIMITY_DOMAIN_FLAGS
{
    // This flag specifies whether the proximity information is preferred. If
    // so, then the memory allocations are done preferentially from the
    // specified proximity domain. In case there is insufficient memory in the
    // specified domain, other domains are tried. If this flag is false, then
    // all memory allocation must come from the specified domain.
    HV_UINT32 ProximityPreferred : 1;
    HV_UINT32 Reserved : 30;
    // This flag specifies that the specified proximity domain is valid. If this
    // flag is false then the memory allocation can come from any proximity
    // domain.
    HV_UINT32 ProximityInfoValid : 1;
} HV_PROXIMITY_DOMAIN_FLAGS, *PHV_PROXIMITY_DOMAIN_FLAGS;

// Define the proximiy domain information structure.
typedef struct _HV_PROXIMITY_DOMAIN_INFO
{
    HV_PROXIMITY_DOMAIN_ID Id;
    HV_PROXIMITY_DOMAIN_FLAGS Flags;
} HV_PROXIMITY_DOMAIN_INFO, *PHV_PROXIMITY_DOMAIN_INFO;

// The HV_PROCESSOR_INFO structures contains additional information about each
// physical processor
typedef struct _HV_PROCESSOR_INFO
{
    // The Local APIC ID for the processor.
    HV_UINT32 LocalApicId;
    // The proximity domain the processor resides in
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;
} HV_PROCESSOR_INFO, *PHV_PROCESSOR_INFO;

// The following structure contains the definition of a memory range.
typedef struct _HV_MEMORY_RANGE_INFO
{
    // The system physical address where this range begins
    HV_SPA BaseAddress;
    // The length of this range of memory in bytes.
    HV_UINT64 Length;
    // The proximity domain this memory range resides in.
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;

} HV_MEMORY_RANGE_INFO, *PHV_MEMORY_RANGE_INFO;
typedef const HV_MEMORY_RANGE_INFO* PCHV_MEMORY_RANGE_INFO;

#define HV_EVENTLOG_BUFFER_INDEX_NONE 0xFFFFFFFF

// Define all the trace buffer types.
typedef HV_EVENTLOG_TYPE _HV_EVENTLOG_TYPE;

// Define all the trace buffer states.
typedef enum
{
    HvEventLogBufferStateStandby = 0,
    HvEventLogBufferStateFree = 1,
    HvEventLogBufferStateInUse = 2,
    HvEventLogBufferStateComplete = 3,
    HvEventLogBufferStateReady = 4
} HV_EVENTLOG_BUFFER_STATE;

// Define time source enum and structure.
typedef enum
{
    HvEventLogEntryTimeReference = 0,
    HvEventLogEntryTimeTsc = 1
} HV_EVENTLOG_ENTRY_TIME_BASIS;

typedef union
{
    HV_NANO100_TIME ReferenceTime;
    HV_UINT64 TimeStamp;
} HV_EVENTLOG_ENTRY_TIME;

// Define trace buffer header.
typedef struct _HV_EVENTLOG_BUFFER_HEADER
{
    HV_UINT32 BufferSize; // BufferSize
    HV_EVENTLOG_BUFFER_INDEX BufferIndex; // SavedOffset
    HV_UINT32 EventsLost; // CurrentOffset
    volatile HV_UINT32 ReferenceCounter; // ReferenceCount
    union
    {
        HV_UINT64 TimeStamp;
        HV_NANO100_TIME ReferenceTime;
    };
    HV_UINT64 Reserved1;
    HV_UINT64 Reserved2;
    struct // ClientContext
    {
        HV_UINT8 LogicalProcessor; // ProcessorNumber
        HV_UINT8 Alignment;
        HV_UINT16 LoggerId;
    };
    volatile HV_EVENTLOG_BUFFER_STATE BufferState; // (Free/GeneralLogging/Flush)
    HV_UINT32 NextBufferOffset; // Offset
    HV_EVENTLOG_TYPE Type; // BufferFlag and BufferType
    HV_EVENTLOG_BUFFER_INDEX NextBufferIndex; // Padding1
    HV_UINT32 Reserved3; // Padding1
    HV_UINT32 Reserved4[2]; // Padding1
} HV_EVENTLOG_BUFFER_HEADER, *PHV_EVENTLOG_BUFFER_HEADER;

// Define trace entry header.
typedef struct _HV_EVENTLOG_ENTRY_HEADER
{
    HV_UINT32 Context; // Marker
    HV_UINT16 Size; // Size in WMI_TRACE_PACKET
    HV_UINT16 Type; // HookId in WMI_TRACE_PACKET
    union
    {
        HV_UINT64 TimeStamp;
        HV_NANO100_TIME ReferenceTime;
    };
} HV_EVENTLOG_ENTRY_HEADER, *PHV_EVENTLOG_ENTRY_HEADER;

// The following are the two hypervisor event groups defined by ETW. They need
// to be in sync with the two ETW constants defined in base\published\ntwmi.w:
//     #define EVENT_TRACE_GROUP_HYPERVISOR 0x1D00
//     #define EVENT_TRACE_GROUP_HYPERVISORX 0x1E00
// Note, only the high byte is used for group. The lower byte is used for the
// event types in the group.

#define HV_TR_EVENTLOG_GROUP_HYPERVISOR 0x1D00
#define HV_TR_EVENTLOG_GROUP_HYPERVISORX 0x1E00

// Event & Trace Groups.

#define HV_TR_GROUP_NONE 0x0000000000000000

// Event Groups (Admin, Operational, Audit, ...)

#define HV_EVENTLOG_ENABLE_AUDIT_SUCCESS 0x0000000000000001
#define HV_EVENTLOG_ENABLE_AUDIT_FAILURE 0x0000000000000002
#define HV_EVENTLOG_ENABLE_PARTITION 0x0000000000000004
#define HV_EVENTLOG_ENABLE_TEST 0x8000000000000000

// Diagnostic Trace Groups.

#define HV_TR_GROUP_ADMIN 0x0000000000000001
#define HV_TR_GROUP_DIAG 0x0000000000000002
#define HV_TR_GROUP_WARN 0x0000000000000003

// Retail Performance Trace Groups (starting at 0x0000000000000100)

#define HV_TR_GROUP_BM 0x0000000000000100
#define HV_TR_GROUP_DM 0x0000000000000200
#define HV_TR_GROUP_HC 0x0000000000000400
#define HV_TR_GROUP_IM 0x0000000000000800
#define HV_TR_GROUP_IC 0x0000000000001000
#define HV_TR_GROUP_OB 0x0000000000002000
#define HV_TR_GROUP_PT 0x0000000000004000
#define HV_TR_GROUP_VP 0x0000000000008000
#define HV_TR_GROUP_SYNIC 0x0000000000010000
#define HV_TR_GROUP_SYNIC_TI 0x0000000000020000
#define HV_TR_GROUP_AM_GVA 0x0000000000040000
#define HV_TR_GROUP_AM 0x0000000000080000
#define HV_TR_GROUP_VAL 0x0000000000100000
#define HV_TR_GROUP_VM 0x0000000000200000
#define HV_TR_GROUP_SCH 0x0000000000400000
#define HV_TR_GROUP_TH 0x0000000000800000
#define HV_TR_GROUP_TI 0x0000000001000000
#define HV_TR_GROUP_KE 0x0000000002000000
#define HV_TR_GROUP_MM 0x0000000004000000
#define HV_TR_GROUP_PROFILER 0x0000000008000000

#define HV_TR_ALL_GROUPS (HV_TR_GROUP_BM | HV_TR_GROUP_DM | HV_TR_GROUP_HC | \
    HV_TR_GROUP_IM | HV_TR_GROUP_IC | HV_TR_GROUP_OB | \
    HV_TR_GROUP_PT | HV_TR_GROUP_VP | HV_TR_GROUP_SYNIC | \
    HV_TR_GROUP_SYNIC_TI | HV_TR_GROUP_AM_GVA | HV_TR_GROUP_AM | \
    HV_TR_GROUP_VAL | HV_TR_GROUP_VM | HV_TR_GROUP_SCH | \
    HV_TR_GROUP_TH | HV_TR_GROUP_TI | HV_TR_GROUP_KE | \
    HV_TR_GROUP_MM | HV_TR_GROUP_PROFILER)

#define HV_TR_IS_GROUP_RETAIL(_Group_) \
    (((HV_UINT64)(_Group_) > 0) && \
    (((HV_UINT64)(_Group_) & HV_TR_ALL_GROUPS) != 0) && \
    (((HV_UINT64)(_Group_) & ((HV_UINT64)(_Group_) - 1)) == 0))

// Internal Debugging Trace Groups (starting at 0x0000010000000000)

#define HV_TR_GROUP_BM_INTERNAL 0x0000010000000000
#define HV_TR_GROUP_DM_INTERNAL 0x0000020000000000
#define HV_TR_GROUP_HC_INTERNAL 0x0000040000000000
#define HV_TR_GROUP_IM_INTERNAL 0x0000080000000000
#define HV_TR_GROUP_IC_INTERNAL 0x0000100000000000
#define HV_TR_GROUP_OB_INTERNAL 0x0000200000000000
#define HV_TR_GROUP_PT_INTERNAL 0x0000400000000000
#define HV_TR_GROUP_VP_INTERNAL 0x0000800000000000
#define HV_TR_GROUP_SYNIC_INTERNAL 0x0001000000000000
#define HV_TR_GROUP_SYNIC_TI_INTERNAL 0x0002000000000000
#define HV_TR_GROUP_AM_GVA_INTERNAL 0x0004000000000000
#define HV_TR_GROUP_AM_INTERNAL 0x0008000000000000
#define HV_TR_GROUP_VAL_INTERNAL 0x0010000000000000
#define HV_TR_GROUP_VM_INTERNAL 0x0020000000000000
#define HV_TR_GROUP_SCH_INTERNAL 0x0040000000000000
#define HV_TR_GROUP_TH_INTERNAL 0x0080000000000000
#define HV_TR_GROUP_TI_INTERNAL 0x0100000000000000
#define HV_TR_GROUP_KE_INTERNAL 0x0200000000000000
#define HV_TR_GROUP_MM_INTERNAL 0x0400000000000000

// Tf, simulate full buffers and cyclic buffers are currently only supported for
// TEST_FEATURES_ENABLED builds.

#define HV_TR_GROUP_TF 0x1000000000000000
#define HV_TR_GROUP_SIMULATE_FULL 0x2000000000000000
#define HV_TR_GROUP_CYCLIC 0x4000000000000000

// IceCap Trace Group.

#define HV_TR_GROUP_ICE 0x8000000000000000

#define HV_TR_ALL_GROUPS_INTERNAL (HV_TR_GROUP_BM_INTERNAL | \
    HV_TR_GROUP_DM_INTERNAL | HV_TR_GROUP_HC_INTERNAL | \
    HV_TR_GROUP_IM_INTERNAL | HV_TR_GROUP_IC_INTERNAL | \
    HV_TR_GROUP_OB_INTERNAL | HV_TR_GROUP_PT_INTERNAL | \
    HV_TR_GROUP_VP_INTERNAL | HV_TR_GROUP_SYNIC_INTERNAL | \
    HV_TR_GROUP_SYNIC_TI_INTERNAL | HV_TR_GROUP_AM_GVA_INTERNAL | \
    HV_TR_GROUP_AM_INTERNAL | HV_TR_GROUP_VAL_INTERNAL | \
    HV_TR_GROUP_VM_INTERNAL | HV_TR_GROUP_SCH_INTERNAL | \
    HV_TR_GROUP_TH_INTERNAL | HV_TR_GROUP_TI_INTERNAL | \
    HV_TR_GROUP_KE_INTERNAL | HV_TR_GROUP_MM_INTERNAL | \
    HV_TR_GROUP_TF | HV_TR_GROUP_SIMULATE_FULL | \
    HV_TR_GROUP_CYCLIC | HV_TR_GROUP_ICE)

#define HV_TR_IS_GROUP_INTERNAL(_Group_) \
    (((HV_UINT64)(_Group_) > 0) && \
    (((HV_UINT64)(_Group_) & HV_TR_ALL_GROUPS_INTERNAL) != 0) && \
    (((HV_UINT64)(_Group_) & ((HV_UINT64)(_Group_) - 1)) == 0))

// Trace Types for the administrative group.

#define HV_EVENTLOG_OPERATIONAL_PARTITION_CREATED 0x4101
#define HV_EVENTLOG_OPERATIONAL_PARTITION_DELETED 0x4102
#define HV_EVENTLOG_OPERATIONAL_PARTITION_CREATION_FAILED 0x2103
#define HV_EVENTLOG_ADMIN_TEST 0x4001

// Trace Types for the diagnostic group.

// Retail Bm Trace Types (0x1D 00-0F)
// None.

// Retail Dm Trace Types (0x1D 10-19).
// None.

// Retail Hc Trace Types (0x1D 1A-1F).

#define HV_TR_HC_HYPERCALL 0x1A

// Retail Im Trace Types (0x1D 20-3B).

#define HV_TR_IM_GUEST_EXCEPTION 0x20
#define HV_TR_IM_MSR_READ 0x21
#define HV_TR_IM_MSR_WRITE 0x22
#define HV_TR_IM_CR_READ 0x23
#define HV_TR_IM_CR_WRITE 0x24
#define HV_TR_IM_HLT_INSTRUCTION 0x25
#define HV_TR_IM_MWAIT_INSTRUCTION 0x26
#define HV_TR_IM_CPUID_INSTRUCTION 0x27
#define HV_TR_IM_IO_PORT_READ 0x28
#define HV_TR_IM_IO_PORT_WRITE 0x29
#define HV_TR_IM_EXTERNAL_INTERRUPT 0x2A
#define HV_TR_IM_INTERRUPT_PENDING 0x2B
#define HV_TR_IM_GUEST_SHUTDOWN 0x2C
#define HV_TR_IM_EMULATED_INSTRUCTION 0x2D
#define HV_TR_IM_NMI_INTERRUPT 0x2E
#define HV_TR_IM_INVLPG_INSTRUCTION 0x2F
#define HV_TR_IM_IRET_INSTRUCTION 0x30
#define HV_TR_IM_TASK_SWITCH 0x31
#define HV_TR_IM_INVD_INSTRUCTION 0x32
#define HV_TR_IM_DR_ACCESS 0x33
#define HV_TR_IM_FERR_FREEZE 0x34
#define HV_TR_IM_REAL_MODE_INTERRUPT 0x35
#define HV_TR_IM_MEMORY_INTERCEPT 0x36
#define HV_TR_IM_REFLECTED_EXCEPTION 0x37

// Retail Ic Trace Types (0x1D 3C-3F).
// None.

// Retail Ob Trace Types (0x1D 40-45).

#define HV_TR_OB_CREATE_PARTITION 0x40
#define HV_TR_OB_DELETE_PARTITION 0x41

// Retail Pt Trace Types (0x1D 46-4A).

#define HV_TR_PT_REFERENCE_TIME 0x46

//Retail Vp Trace Types (0x1D 4B-4F).

#define HV_TR_VP_CREATE_VP 0x4B
#define HV_TR_VP_DELETE_VP 0x4C

// Retail Synic Trace Types (0x1D 50-65).
// None.

// Retail Synic Timer Trace Types (0x1D 66-6F).
// None.

// Retail Am GVA Trace Types (0x1D 70-97).

#define HV_TR_AM_GVA_GROW_VIRTUAL_TLB 0x70
#define HV_TR_AM_GVA_SHRINK_VIRTUAL_TLB 0x71
#define HV_TR_AM_GVA_FLUSH_VIRTUAL_TLB 0x72

// Retail Am Trace Types (0x1D 98-AF).
// None.

// Retail Val Trace Types (0x1D A0-A7).
// None.

// Retail Vm Trace Types (0x1D A8-AF).
// None.

// Retail Sch Trace Types (0x1D B0-CD).

#define HV_TR_SCH_CONTEXT_SWITCH 0xB0

// Retail Th Trace Types (0x1D CE-CF).
// None.

// Retail Ti Trace Types (0x1D D0-DF).
// None.

// Retail Ke Trace Types (0x1D E0-E9).

#define HV_TR_KE_OVERRUN 0xE0
#define HV_TR_KE_OVERRUN_PARAMS 0xE1

// Retail Mm Trace Types (0x1D EA-EF).
// None.

// Retail Hypervisor Profiler traces (0x1D F0-F4)

#define HV_TR_PROFILER_SAMPLE 0xF0
#define HV_TR_PROFILER_HV_MODULE 0xF1

// Internal Bm Trace Types (0x1E 00-0F)
// None.

// Internal Dm Trace Types (0x1E 10-19).

#define HV_TR_DMP_INTERCEPT 0x10
#define HV_TR_DMP_DISPATCH_EVENTS 0x11

// Internal Hc Trace Types (0x1E 1A-1F).
// None.

// Internal Im Trace Types (0x1E 20-3B).

#define HV_TR_IMP_SEND_INTERCEPT_MESSAGE 0x20

// Internal Ic Trace Types (0x1E 3C-3F).

#define HV_TR_ICP_EMULATE_INSTR 0x3C

// Internal Ob Trace Types (0x1E 40-45).
// None.

// Internal Pt Trace Types (0x1E 46-4A).
// None.

// Internal Vp Trace Types (0x1E 4B-4F).
// None.

// Internal Synic Trace Types (0x1E 50-65).

#define HV_TR_SYNICP_ASSERT 0x50
#define HV_TR_SYNICP_EVAL_LOW_PRI 0x51
#define HV_TR_SYNICP_EVAL_IMMEDIATE 0x52
#define HV_TR_SYNICP_EVAL_QUEUE 0x53
#define HV_TR_SYNICP_PENDING 0x54
#define HV_TR_SYNICP_EOI 0x55
#define HV_TR_SYNICP_LATENCY_EXCEEDED 0x56
#define HV_TR_SYNICP_MARK_PENDING 0x57
#define HV_TR_SYNICP_EVAL_APIC_INTS 0x58
#define HV_TR_SYNICP_READ_APIC_GPA 0x59
#define HV_TR_SYNICP_WRITE_APIC_GPA 0x5A
#define HV_TR_SYNICP_READ_APIC_MSR 0x5B
#define HV_TR_SYNICP_WRITE_APIC_MSR 0x5C
#define HV_TR_SYNICP_EXTERNAL_INT 0x5D
#define HV_TR_SYNICP_APIC_IPI 0x5E
#define HV_TR_SYNICP_SIGNAL_EVENT_PORT 0x5F
#define HV_TR_SYNICP_POST_MESSAGE 0x60

// Internal Synic Timer Trace Types (0x1E 66-6F).

#define HV_TR_SYNICP_PERIODIC_TIMER_UPDATE 0x66
#define HV_TR_SYNICP_PERIODIC_TIMER_RESET 0x67
#define HV_TR_SYNICP_TIMER_SEND_MESSAGE 0x68
#define HV_TR_SYNICP_TIMER_SCAN_MESSAGE 0x69
#define HV_TR_SYNICP_TIMER_ASSIST_EXPIRE 0x6A

// Internal Am GVA Trace Types (0x1E 70-97).

#define HV_TR_AMP_GVA_PAGE_FAULT 0x70
#define HV_TR_AMP_GVA_VTLB_WRITABILITY_CHANGE 0x71
#define HV_TR_AMP_GVA_SWITCH_SPACE 0x72
#define HV_TR_AMP_GVA_FLUSH_VA_LOCAL 0x73
#define HV_TR_AMP_GVA_FLUSH_VA_GLOBAL 0x74
#define HV_TR_AMP_GVA_FLUSH_VTLB_RANGE 0x75
#define HV_TR_AMP_GVA_FLUSH_SPACE 0x76
#define HV_TR_AMP_GVA_FLUSH_DOMAIN 0x77
#define HV_TR_AMP_GVA_RESET_DOMAIN 0x78
#define HV_TR_AMP_GVA_TRANSLATE_VA 0x79
#define HV_TR_AMP_GVA_READ_VM 0x7A
#define HV_TR_AMP_GVA_WRITE_VM 0x7B
#define HV_TR_AMP_GVA_RESET_PT 0x7C
#define HV_TR_AMP_GVA_UNLINK_PT 0x7D
#define HV_TR_AMP_GVA_UNLINK_PT_VALIDATE 0x7E
#define HV_TR_AMP_GVA_UNLINK_PT_FILL 0x7F
#define HV_TR_AMP_GVA_UNLINK_PT_LINK 0x80
#define HV_TR_AMP_GVA_UNLINK_PT_RESET 0x81
#define HV_TR_AMP_GVA_UNLINK_PT_EVICT 0x82
#define HV_TR_AMP_GVA_UNLINK_PT_CLEAN 0x83
#define HV_TR_AMP_GVA_CONSTRUCT_PT 0x84
#define HV_TR_AMP_GVA_DESTRUCT_PT 0x85
#define HV_TR_AMP_GVA_WALK_PT 0x86
#define HV_TR_AMP_GVA_WAIT_FOR_PT_FILL 0x87
#define HV_TR_AMP_GVA_CLEAN_SAS 0x88
#define HV_TR_AMP_GVA_CLEAN_SAS_OVERFLOW 0x89
#define HV_TR_AMP_GVA_EVICT_PTS 0x8A
#define HV_TR_AMP_GVA_RECLAIM_PTS 0x8B
#define HV_TR_AMP_GVA_FREE_RECLAIMED_PTS 0x8C
#define HV_TR_AMP_GVA_HASH_PROCESSED 0x8D

// Internal Am Trace Types (0x1E 98-9F).

#define HV_TR_AMP_MAP_GPA 0x98
#define HV_TR_AMP_UNMAP_GPA 0x99

// Internal Val Trace Types (0x1E A0-A7).

#define HV_TR_VALP_PAUSE_LOOP_EXIT 0xA0

// Internal Vm Trace Types (0x1E A8-AF).
// None.

// Internal Sch Trace Types (0x1E B0-CD).

#define HV_TR_SCHP_NEXT_THREAD 0xB0
#define HV_TR_SCHP_ADD_LOCAL 0xB1
#define HV_TR_SCHP_EVAL_PRI 0xB2
#define HV_TR_SCHP_TIMESLICE_MIN 0xB3
#define HV_TR_SCHP_AFFINITY_CHANGE 0xB4
#define HV_TR_SCHP_ADD_DEFERRED 0xB6
#define HV_TR_SCHP_DEFERRED_READY_THREAD 0xB7
#define HV_TR_SCHP_TIMESLICE_END 0xB8
#define HV_TR_SCHP_EVAL_SEND 0xB9
#define HV_TR_SCHP_EVAL_RECV 0xBA
#define HV_TR_SCHP_YIELD 0xBB
#define HV_TR_SCHP_SET_PRI 0xBC
#define HV_TR_SCHP_COMPUTE_TIMESLICE 0xBD
#define HV_TR_SCHP_BLOCK_ON_EVENT 0xBE
#define HV_TR_SCHP_UNBLOCK_FROM_EVENT 0xBF
#define HV_TR_SCHP_SIGNAL_EVENT 0xC0
#define HV_TR_SCHP_WATCHDOG 0xC1
#define HV_TR_SCHP_LOAD_BALANCER 0xC2
#define HV_TR_SCHP_EVAL 0xC3
#define HV_TR_SCHP_CPU_IDLE 0xC4
#define HV_TR_SCHP_READY_UNBLOCKED_THREAD 0xC5
#define HV_TR_SCHP_EXPRESS_THREAD 0xC6
#define HV_TR_SCHP_EXPRESS_PROCESS 0xC7
#define HV_TR_SCHP_EVALUATE_CAPS 0xC8
#define HV_TR_SCHP_SET_CAPS_TIMER 0xC9

// Internal Th Trace Types (0x1E CE-CF).

#define HV_TR_THP_SEND_WORK 0xCE

// Internal Ti Trace Types (0x1E D0-DF).

#define HV_TR_TIP_SET_APIC 0xD0
#define HV_TR_TIP_INT 0xD1
#define HV_TR_TIP_NEW_TIMER 0xD2
#define HV_TR_TIP_INSERT_TIMER 0xD3
#define HV_TR_TIP_CALLBACK 0xD4
#define HV_TR_TIP_REMOTE_REMOVE_TIMER 0xD5

// Internal Ke Trace Types (0x1E E0-E9).

#define HV_TR_KEP_FLUSH_ENTIRE_HW_TLB 0xE0
#define HV_TR_KEP_FLUSH_HV_HW_TLB 0xE1
#define HV_TR_KEP_FLUSH_MULTIPLE_HW_TLB 0xE2
#define HV_TR_KEP_SIGNAL_PROCESSORS 0xE3
#define HV_TR_KEP_RUN_GUEST 0xE4
#define HV_TR_KEP_SEND_IPI 0xE5
#define HV_TR_KEP_SEND_IPI_NO_IPI 0xE6
#define HV_TR_KEP_WAIT_FOR_IPI_BARRIER 0xE7
#define HV_TR_KEP_FLUSH_ENTIRE_HW_CACHE 0xE8

// Internal Mm Trace Types (0x1E EA-EF).
// None.

// Internal Tf Trace Types (0x1E FA-FF).

#define HV_TR_TF_INTERCEPT 0xFA

// Internal IceCAP Trace Types (0x1E F0-F9).

#define HV_TR_ICE_CALL 0xF0 // fixed (tffastcap.asm)
#define HV_TR_ICE_RETURN 0xF1 // fixed (tffastcap.asm)
#define HV_TR_ICE_ACQUIRE 0xF2
#define HV_TR_ICE_RELEASE 0xF3

// Internal Custom Probe Type.

#define HV_TR_ICE_COMMENT 0xF8

// Thread ID for idle thread.
// HV_TR_THREAD_ID_TEST is a generic ID for all TFE-only threads.

#define HV_TR_THREAD_ID_IDLE 0
#define HV_TR_THREAD_ID_TEST 9

// Physical nodes are defined by a 32-bit index.
typedef HV_UINT32 HV_PHYSICAL_NODE_INDEX, *PHV_PHYSICAL_NODE_INDEX;

#define HV_PHYSICAL_NODE_INDEX_UNSPECIFIED 0xFFFFFFFF

typedef enum _HV_SAVE_RESTORE_STATE_RESULT
{
    HvStateComplete = 0,
    HvStateIncomplete = 1,
    HvStateRestorable = 2,
    HvStateCorruptData = 3,
    HvStateUnsupportedVersion = 4,
    HvStateProcessorFeatureMismatch = 5,
    HvStateHardwareFeatureMismatch = 6,
    HvStateProcessorCountMismatch = 7,
    HvStateProcessorFlagsMismatch = 8,
    HvStateProcessorIndexMismatch = 9,
    HvStateProcessorInsufficientMemory = 10,
    HvStateIncompatibleProcessor = 11,
    HvStateProcessorFeatureSse3Mismatch = 12,
    HvStateProcessorFeatureLahfSahfMismatch = 13,
    HvStateProcessorFeaturSsse3eMismatch = 14,
    HvStateProcessorFeatureSse41Mismatch = 15,
    HvStateProcessorFeatureSse42Mismatch = 16,
    HvStateProcessorFeatureSse4aMismatch = 17,
    HvStateProcessorFeatureSse5Mismatch = 18,
    HvStateProcessorFeaturePopcntMismatch = 19,
    HvStateProcessorFeatureCmpxchg16bMismatch = 20,
    HvStateProcessorFeatureAltmovcr8Mismatch = 21,
    HvStateProcessorFeatureLzcntMismatch = 22,
    HvStateProcessorFeatureMisalignedSseMismatch = 23,
    HvStateProcessorFeatureMmxExtMismatch = 24,
    HvStateProcessorFeature3DNowMismatch = 25,
    HvStateProcessorFeatureExtended3DNowMismatch = 26,
    HvStateProcessorFeaturePage1GBMismatch = 27,
    HvStateProcessorCacheLineFlushSizeMismatch = 28,
    HvStateProcessorFeatureXsaveMismatch = 29,
    HvStateProcessorFeatureXsaveoptMismatch = 30,
    HvStateProcessorFeatureXsaveLegacySseMismatch = 31,
    HvStateProcessorFeatureXsaveAvxMismatch = 32,
    HvStateProcessorFeatureXsaveUnknownFeatureMismatch = 33,
    HvStateProcessorXsaveSaveAreaMismatch = 34
} HV_SAVE_RESTORE_STATE_RESULT, *PHV_SAVE_RESTORE_STATE_RESULT;
typedef HV_UINT32 HV_SAVE_RESTORE_STATE_FLAGS, *PHV_SAVE_RESTORE_STATE_FLAGS;

#define HV_SAVE_RESTORE_STATE_START 0x00000001
#define HV_SAVE_RESTORE_STATE_SUMMARY 0x00000002

typedef union _HV_PARTITION_PRIVILEGE_MASK_PRIVATE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Reserved0 : 15;
        HV_UINT64 AccessTscInvariantControls : 1;
        HV_UINT64 Reserved1 : 16;
        HV_UINT64 Reserved2 : 32;
    };
} HV_PARTITION_PRIVILEGE_MASK_PRIVATE, *PHV_PARTITION_PRIVILEGE_MASK_PRIVATE;

typedef enum _HV_PROCESSOR_VENDOR
{
    HvProcessorVendorAmd = 0x0000,
    HvProcessorVendorIntel = 0x0001
} HV_PROCESSOR_VENDOR, *PHV_PROCESSOR_VENDOR;

#if defined(_M_ARM64)
#define HV_PARTITION_PROCESSOR_FEATURES_BANKS 1
#elif defined(_M_AMD64) || defined(_M_IX86)
#define HV_PARTITION_PROCESSOR_FEATURES_BANKS 2
#endif

// Define the structure defining the processor related features that may be
// de-featured.
typedef union _HV_PARTITION_PROCESSOR_FEATURES
{
    HV_UINT64 AsUINT64[HV_PARTITION_PROCESSOR_FEATURES_BANKS];
#if defined(_M_ARM64)
    struct
    {
        HV_UINT64 Asid16 : 1;
        HV_UINT64 Tgran16 : 1;
        HV_UINT64 Tgran64 : 1;
        HV_UINT64 Haf : 1;
        HV_UINT64 Hdbs : 1;
        HV_UINT64 Pan : 1;
        HV_UINT64 Ats1e1 : 1;
        HV_UINT64 Uao : 1;
        HV_UINT64 El0aarch32 : 1;
        HV_UINT64 Fp : 1;
        HV_UINT64 Fphp : 1;
        HV_UINT64 Advsimd : 1;
        HV_UINT64 Advsimdhp : 1;
        HV_UINT64 Gicv3v4 : 1;
        HV_UINT64 Gicv41 : 1;
        HV_UINT64 Ras : 1;
        HV_UINT64 Pmuv3 : 1;
        HV_UINT64 Pmuv3armv81 : 1;
        HV_UINT64 Pmuv3armv84 : 1;
        HV_UINT64 Pmuv3armv85 : 1;
        HV_UINT64 Aes : 1;
        HV_UINT64 Polymul : 1;
        HV_UINT64 Sha1 : 1;
        HV_UINT64 Sha256 : 1;
        HV_UINT64 Sha512 : 1;
        HV_UINT64 Crc32 : 1;
        HV_UINT64 Atomic : 1;
        HV_UINT64 Rdm : 1;
        HV_UINT64 Sha3 : 1;
        HV_UINT64 Sm3 : 1;
        HV_UINT64 Sm4 : 1;
        HV_UINT64 Dp : 1;
        HV_UINT64 Fhm : 1;
        HV_UINT64 Dccvap : 1;
        HV_UINT64 Dccvadp : 1;
        HV_UINT64 Apabase : 1;
        HV_UINT64 Apaep : 1;
        HV_UINT64 Apaep2 : 1;
        HV_UINT64 Apaep2fp : 1;
        HV_UINT64 Apaep2fpc : 1;
        HV_UINT64 Jscvt : 1;
        HV_UINT64 Fcma : 1;
        HV_UINT64 Rcpcv83 : 1;
        HV_UINT64 Rcpcv84 : 1;
        HV_UINT64 Gpa : 1;
        HV_UINT64 L1ippipt : 1;
        HV_UINT64 Dzpermitted : 1;
        HV_UINT64 Reserved : 17;
    };
#elif defined(_M_AMD64) || defined(_M_IX86)
    struct
    {
        HV_UINT64 Sse3Support : 1;
        HV_UINT64 LahfSahfSupport : 1;
        HV_UINT64 Ssse3Support : 1;
        HV_UINT64 Sse4_1Support : 1;
        HV_UINT64 Sse4_2Support : 1;
        HV_UINT64 Sse4aSupport : 1;
        HV_UINT64 XopSupport : 1;
        HV_UINT64 PopCntSupport : 1;
        HV_UINT64 Cmpxchg16bSupport : 1;
        HV_UINT64 Altmovcr8Support : 1;
        HV_UINT64 LzcntSupport : 1;
        HV_UINT64 MisAlignSseSupport : 1;
        HV_UINT64 MmxExtSupport : 1;
        HV_UINT64 Amd3DNowSupport : 1;
        HV_UINT64 ExtendedAmd3DNowSupport : 1;
        HV_UINT64 Page1GBSupport : 1;
        HV_UINT64 AesSupport : 1;
        HV_UINT64 PclmulqdqSupport : 1;
        HV_UINT64 PcidSupport : 1;
        HV_UINT64 Fma4Support : 1;
        HV_UINT64 F16cSupport : 1;
        HV_UINT64 RdRandSupport : 1;
        HV_UINT64 RdWrFsGsSupport : 1;
        HV_UINT64 SmepSupport : 1;
        HV_UINT64 EnhancedFastStringSupport : 1;
        HV_UINT64 Bmi1Support : 1;
        HV_UINT64 Bmi2Support : 1;
        HV_UINT64 HleSupportDeprecated : 1;
        HV_UINT64 RtmSupportDeprecated : 1;
        HV_UINT64 MovbeSupport : 1;
        HV_UINT64 Npiep1Support : 1;
        HV_UINT64 DepX87FpuSaveSupport : 1;
        HV_UINT64 RdSeedSupport : 1;
        HV_UINT64 AdxSupport : 1;
        HV_UINT64 IntelPrefetchSupport : 1;
        HV_UINT64 SmapSupport : 1;
        HV_UINT64 HleSupport : 1;
        HV_UINT64 RtmSupport : 1;
        HV_UINT64 RdtscpSupport : 1;
        HV_UINT64 ClflushoptSupport : 1;
        HV_UINT64 ClwbSupport : 1;
        HV_UINT64 ShaSupport : 1;
        HV_UINT64 X87PointersSavedSupport : 1;
        HV_UINT64 InvpcidSupport : 1;
        HV_UINT64 IbrsSupport : 1;
        HV_UINT64 StibpSupport : 1;
        HV_UINT64 IbpbSupport : 1;
        HV_UINT64 UnrestrictedGuestSupport : 1;
        HV_UINT64 MddSupport : 1;
        HV_UINT64 FastShortRepMovSupport : 1;
        HV_UINT64 L1dcacheFlushSupport : 1;
        HV_UINT64 RdclNoSupport : 1;
        HV_UINT64 IbrsAllSupport : 1;
        HV_UINT64 SkipL1dfSupport : 1;
        HV_UINT64 SsbNoSupport : 1;
        HV_UINT64 RsbANoSupport : 1;
        HV_UINT64 VirtSpecCtrlSupport : 1;
        HV_UINT64 RdPidSupport : 1;
        HV_UINT64 UmipSupport : 1;
        HV_UINT64 MbsNoSupport : 1;
        HV_UINT64 MbClearSupport : 1;
        HV_UINT64 TaaNoSupport : 1;
        HV_UINT64 TsxCtrlSupport : 1;
        // N.B. The final processor feature bit in bank 0 is reserved to
        // simplify potential downlevel backports.
        HV_UINT64 ReservedBank0 : 1;

        // N.B. Begin bank 1 processor features.
        HV_UINT64 AcountMcountSupport : 1;
        HV_UINT64 TscInvariantSupport : 1;
        HV_UINT64 ClZeroSupport : 1;
        HV_UINT64 RdpruSupport : 1;
        HV_UINT64 La57Support : 1;
        HV_UINT64 MbecSupport : 1;
        HV_UINT64 NestedVirtSupport : 1;
        HV_UINT64 PsfdSupport : 1;
        HV_UINT64 CetSsSupport : 1;
        HV_UINT64 CetIbtSupport : 1;
        HV_UINT64 VmxExceptionInjectSupport : 1;
        HV_UINT64 EnqcmdSupport : 1;
        HV_UINT64 UmwaitTpauseSupport : 1;
        HV_UINT64 MovdiriSupport : 1;
        HV_UINT64 Movdir64bSupport : 1;
        HV_UINT64 CldemoteSupport : 1;
        HV_UINT64 SerializeSupport : 1;
        HV_UINT64 TscDeadlineTmrSupport : 1;
        HV_UINT64 TscAdjustSupport : 1;
        HV_UINT64 FzlrepMovsb : 1;
        HV_UINT64 FsrepStosb : 1;
        HV_UINT64 FsrepCmpsb : 1;
        HV_UINT64 ReservedBank1 : 42;
    };
#endif
} HV_PARTITION_PROCESSOR_FEATURES, *PHV_PARTITION_PROCESSOR_FEATURES;

// Define the processor features avaialble in Intel and AMD compatibility mode.

#define HV_PARTITION_PROCESSOR_FEATURES_INTEL_COMPATIBILITY_MODE \
{   1, /* Sse3Support */ \
    1, /* LahfSahfSupport */ \
    0, /* Ssse3Support */ \
    0, /* Sse4_1Support */ \
    0, /* Sse4_2Support */ \
    0, /* Sse4aSupport */ \
    0, /* Sse5Support */ \
    0, /* PopCntSupport */ \
    1, /* Cmpxchg16bSupport */ \
    0, /* Altmovcr8Support */ \
    0, /* LzcntSupport */ \
    0, /* MisAlignSseSupport */ \
    0, /* MmxExtSupport */ \
    0, /* Amd3DNowSupport */ \
    0, /* ExtendedAmd3DNowSupport */ \
    0, /* Page1GBSupport */ \
    0  /* Reserved1 */ \
}

#define HV_PARTITION_PROCESSOR_FEATURES_AMD_COMPATIBILITY_MODE \
{ \
    1, /* Sse3Support */ \
    1, /* LahfSahfSupport */ \
    0, /* Ssse3Support */ \
    0, /* Sse4_1Support */ \
    0, /* Sse4_2Support */ \
    0, /* Sse4aSupport */ \
    0, /* Sse5Support */ \
    0, /* PopCntSupport */ \
    1, /* Cmpxchg16bSupport */ \
    1, /* Altmovcr8Support */ \
    0, /* LzcntSupport */ \
    0, /* MisAlignSseSupport */ \
    1, /* MmxExtSupport */ \
    0, /* Amd3DNowSupport */ \
    0, /* ExtendedAmd3DNowSupport */ \
    0, /* Page1GBSupport */ \
    0  /* Reserved1 */ \
}

// Define the structure defining the processor XSAVE related features that may
// be de-featured.
typedef union _HV_PARTITION_PROCESSOR_XSAVE_FEATURES
{
    struct
    {
        HV_UINT64 XsaveSupport : 1;
        HV_UINT64 XsaveoptSupport : 1;
        HV_UINT64 AvxSupport : 1;
        HV_UINT64 Reserved1 : 61;
    };
    HV_UINT64 AsUINT64;
} HV_PARTITION_PROCESSOR_XSAVE_FEATURES, *PHV_PARTITION_PROCESSOR_XSAVE_FEATURES;

// Define the processor features avaialble in Intel and AMD compatibility mode.

#define HV_PARTITION_PROCESSOR_XSAVE_FEATURES_INTEL_COMPATIBILITY_MODE \
{ \
    0, /* XsaveSupport */ \
    0, /* XsaveoptSupport */ \
    0, /* AvxSupport */ \
    0  /* Reserved1 */ \
}

#define HV_PARTITION_PROCESSOR_XSAVE_FEATURES_AMD_COMPATIBILITY_MODE \
{ \
    0, /* XsaveSupport */ \
    0, /* XsaveoptSupport */ \
    0, /* AvxSupport */ \
    0  /* Reserved1 */ \
}

// Define the processor cache line flush size Intel and AMD compatibility mode.

#define HV_PARTITION_PROCESSOR_CL_FLUSHSIZE_INTEL_COMPATIBILITY_MODE (8)
#define HV_PARTITION_PROCESSOR_CL_FLUSHSIZE_AMD_COMPATIBILITY_MODE (8)

typedef union _HV_EXPLICIT_SUSPEND_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Suspended : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_EXPLICIT_SUSPEND_REGISTER, *PHV_EXPLICIT_SUSPEND_REGISTER;

typedef union _HV_INTERCEPT_SUSPEND_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Suspended : 1;
        HV_UINT64 TlbLocked : 1;
        HV_UINT64 Reserved : 62;
    };
} HV_INTERCEPT_SUSPEND_REGISTER, *PHV_INTERCEPT_SUSPEND_REGISTER;

typedef union _HV_DISPATCH_SUSPEND_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Suspended : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_DISPATCH_SUSPEND_REGISTER, *PHV_DISPATCH_SUSPEND_REGISTER;

typedef union _HV_X64_INTERRUPT_STATE_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 InterruptShadow : 1;
        HV_UINT64 NmiMasked : 1;
        HV_UINT64 Reserved : 62;
    };
} HV_X64_INTERRUPT_STATE_REGISTER, *PHV_X64_INTERRUPT_STATE_REGISTER;

typedef enum _HV_X64_PENDING_INTERRUPTION_TYPE
{
    HvX64PendingInterrupt = 0,
    HvX64PendingNmi = 2,
    HvX64PendingException = 3,
    HvX64PendingSoftwareInterrupt = 4,
    HvX64PendingPrivilegedSoftwareException = 5,
    HvX64PendingSoftwareException = 6
} HV_X64_PENDING_INTERRUPTION_TYPE, *PHV_X64_PENDING_INTERRUPTION_TYPE;

typedef union _HV_X64_PENDING_INTERRUPTION_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 InterruptionPending : 1;
        HV_UINT32 InterruptionType : 3;
        HV_UINT32 DeliverErrorCode : 1;
        HV_UINT32 InstructionLength : 4;
        HV_UINT32 NestedEvent : 1;
        HV_UINT32 Reserved : 6;
        HV_UINT32 InterruptionVector : 16;
        HV_UINT32 ErrorCode;
    };
} HV_X64_PENDING_INTERRUPTION_REGISTER, *PHV_X64_PENDING_INTERRUPTION_REGISTER;

typedef union _HV_X64_MSR_NPIEP_CONFIG_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        // These bits enable instruction execution prevention for specific
        // instructions.

        HV_UINT64 PreventsGdt : 1;
        HV_UINT64 PreventsIdt : 1;
        HV_UINT64 PreventsLdt : 1;
        HV_UINT64 PreventsTr : 1;

        // The reserved bits must always be 0.
        HV_UINT64 Reserved : 60;
    };
} HV_X64_MSR_NPIEP_CONFIG_CONTENTS, *PHV_X64_MSR_NPIEP_CONFIG_CONTENTS;

typedef union _HV_X64_PENDING_EXCEPTION_EVENT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_UINT32 EventPending : 1;
        HV_UINT32 EventType : 3;
        HV_UINT32 Reserved0 : 4;
        HV_UINT32 DeliverErrorCode : 1;
        HV_UINT32 Reserved1 : 7;
        HV_UINT32 Vector : 16;
        HV_UINT32 ErrorCode;
        HV_UINT64 ExceptionParameter;
    };
} HV_X64_PENDING_EXCEPTION_EVENT, *PHV_X64_PENDING_EXCEPTION_EVENT;

typedef union _HV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_UINT32 EventPending : 1;
        HV_UINT32 EventType : 3;
        HV_UINT32 Reserved0 : 4;
        HV_UINT32 Reserved1 : 8;
        HV_UINT32 Parameter0 : 16;
        HV_UINT32 Code;
        HV_UINT64 Parameter1;
    };
} HV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT, *PHV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT;

typedef union _HV_ARM64_PENDING_SYNTHETIC_EXCEPTION_EVENT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3;
        HV_UINT8 Reserved : 4;
        HV_UINT32 ExceptionType;
        HV_UINT64 Context;
    };
} HV_ARM64_PENDING_SYNTHETIC_EXCEPTION_EVENT, *PHV_ARM64_PENDING_SYNTHETIC_EXCEPTION_EVENT;

typedef union _HV_ARM64_INTERRUPT_STATE_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 InterruptShadow : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_ARM64_INTERRUPT_STATE_REGISTER, *PHV_ARM64_INTERRUPT_STATE_REGISTER;

typedef enum _HV_ARM64_PENDING_INTERRUPTION_TYPE
{
    HvArm64PendingInterrupt = 0,
    HvArm64PendingException = 1
} HV_ARM64_PENDING_INTERRUPTION_TYPE, *PHV_ARM64_PENDING_INTERRUPTION_TYPE;

typedef union _HV_ARM64_PENDING_INTERRUPTION_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 InterruptionPending : 1;
        HV_UINT64 InterruptionType : 1;
        HV_UINT64 Reserved : 30;
        HV_UINT64 ErrorCode : 32;
    };
} HV_ARM64_PENDING_INTERRUPTION_REGISTER, *PHV_ARM64_PENDING_INTERRUPTION_REGISTER;

typedef union _HV_REGISTER_VALUE_PRIVATE
{
#if defined(_M_ARM64)
    HV_ARM64_PENDING_INTERRUPTION_REGISTER PendingInterruption;
    HV_ARM64_INTERRUPT_STATE_REGISTER InterruptState;
    HV_ARM64_PENDING_SYNTHETIC_EXCEPTION_EVENT PendingSyntheticExceptionEvent;
#elif defined(_M_AMD64) || defined(_M_IX86)
    HV_X64_FP_REGISTER Fp;
    HV_X64_FP_CONTROL_STATUS_REGISTER FpControlStatus;
    HV_X64_XMM_CONTROL_STATUS_REGISTER XmmControlStatus;
    HV_X64_SEGMENT_REGISTER Segment;
    HV_X64_TABLE_REGISTER Table;
    HV_EXPLICIT_SUSPEND_REGISTER ExplicitSuspend;
    HV_INTERCEPT_SUSPEND_REGISTER InterceptSuspend;
    HV_DISPATCH_SUSPEND_REGISTER DispatchSuspend;
    HV_X64_INTERRUPT_STATE_REGISTER InterruptState;
    HV_X64_PENDING_INTERRUPTION_REGISTER PendingInterruption;
    HV_X64_MSR_NPIEP_CONFIG_CONTENTS NpiepConfig;
    HV_X64_PENDING_EXCEPTION_EVENT PendingExceptionEvent;
    HV_X64_PENDING_VIRTUALIZATION_FAULT_EVENT PendingVirtualizationFaultEvent;
#endif
} HV_REGISTER_VALUE_PRIVATE, *PHV_REGISTER_VALUE_PRIVATE;
typedef const HV_REGISTER_VALUE* PCHV_REGISTER_VALUE;

// Define the intercept access types.

#define HV_INTERCEPT_ACCESS_READ 0
#define HV_INTERCEPT_ACCESS_WRITE 1
#define HV_INTERCEPT_ACCESS_EXECUTE 2

typedef HV_UINT32 HV_INTERCEPT_ACCESS_TYPE_MASK;

// Access types for the install intercept hypercall parameter

#define HV_INTERCEPT_ACCESS_MASK_NONE 0x00
#define HV_INTERCEPT_ACCESS_MASK_READ 0x01
#define HV_INTERCEPT_ACCESS_MASK_WRITE 0x02
#define HV_INTERCEPT_ACCESS_MASK_EXECUTE 0x04

// Define intercept types.
typedef enum _HV_INTERCEPT_TYPE
{
    // Platform-specific intercept types.

    HvInterceptTypeX64IoPort = 0x00000000,
    HvInterceptTypeX64Msr = 0x00000001,
    HvInterceptTypeX64Cpuid = 0x00000002,
    HvInterceptTypeX64Exception = 0x00000003,
    HvInterceptTypeRegister = 0x00000004,
    HvInterceptTypeMmio = 0x00000005,
    HvInterceptTypeX64GlobalCpuid = 0x00000006,
    HvInterceptTypeX64ApicSmi = 0x00000007,
    HvInterceptTypeHypercall = 0x00000008,
    HvInterceptTypeX64ApicInitSipi = 0x00000009,
    HvInterceptTypeX64ApicWrite = 0x0000000B,
    HvInterceptTypeX64MsrIndex = 0x0000000C,
    HvInterceptTypeMax,
    HvInterceptTypeInvalid = 0xFFFFFFFF
} HV_INTERCEPT_TYPE, *PHV_INTERCEPT_TYPE;

// Define IO port type.
typedef HV_UINT16 HV_X64_IO_PORT, *PHV_X64_IO_PORT;

// Define intercept parameters.
typedef union _HV_INTERCEPT_PARAMETERS
{
    // HV_INTERCEPT_PARAMETERS is defined to be an 8-byte field.
    HV_UINT64 AsUINT64;
    // HvInterceptTypeX64IoPort.
    HV_X64_IO_PORT IoPort;
    // HvInterceptTypeX64Cpuid.
    HV_UINT32 CpuidIndex;
    // HvInterceptTypeX64ApicWrite
    HV_UINT32 ApicWriteMask;
    // HvInterceptTypeX64Exception.
    HV_UINT16 ExceptionVector;
    // HvInterceptTypeX64MsrIndex
    HV_UINT32 MsrIndex;
    // N.B. Other intercept types do not have any paramaters.
} HV_INTERCEPT_PARAMETERS, *PHV_INTERCEPT_PARAMETERS;

// Define intercept descriptor structure.
typedef struct _HV_INTERCEPT_DESCRIPTOR
{
    HV_INTERCEPT_TYPE Type;
    HV_INTERCEPT_PARAMETERS Parameters;
} HV_INTERCEPT_DESCRIPTOR, *PHV_INTERCEPT_DESCRIPTOR;
typedef const HV_INTERCEPT_DESCRIPTOR* PCHV_INTERCEPT_DESCRIPTOR;

#define HV_MAX_VP_INDEX (HV_MAXIMUM_PROCESSORS - 1)

// Address space flush flags.
typedef HV_UINT64 HV_FLUSH_FLAGS, *PHV_FLUSH_FLAGS;

#define HV_FLUSH_ALL_PROCESSORS (0x00000001)
#define HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES (0x00000002)
#define HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY (0x00000004)
#define HV_FLUSH_USE_EXTENDED_RANGE_FORMAT (0x00000008)
#define HV_FLUSH_MASK (HV_FLUSH_ALL_PROCESSORS | \
                       HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES | \
                       HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY | \
                       HV_FLUSH_USE_EXTENDED_RANGE_FORMAT)

// The call HvTranslateVirtualAddress takes a collection of input control flags
// and returns a result code and a collection of output flags. The input control
// flags are defined as follows:

typedef HV_UINT64 HV_TRANSLATE_GVA_CONTROL_FLAGS, *PHV_TRANSLATE_GVA_CONTROL_FLAGS;

#define HV_TRANSLATE_GVA_VALIDATE_READ 0x0001
#define HV_TRANSLATE_GVA_VALIDATE_WRITE 0x0002
#define HV_TRANSLATE_GVA_VALIDATE_EXECUTE 0x0004
#define HV_TRANSLATE_GVA_PRIVILEGE_EXEMPT 0x0008
#define HV_TRANSLATE_GVA_SET_PAGE_TABLE_BITS 0x0010
#define HV_TRANSLATE_GVA_TLB_FLUSH_INHIBIT 0x0020
#define HV_TRANSLATE_GVA_CONTROL_MASK (0x003F)
#define HV_TRANSLATE_GVA_INPUT_VTL_MASK (0xFF00000000000000)

typedef enum _HV_TRANSLATE_GVA_RESULT_CODE
{
    HvTranslateGvaSuccess = 0,

    // Translation failures

    HvTranslateGvaPageNotPresent = 1,
    HvTranslateGvaPrivilegeViolation = 2,
    HvTranslateGvaInvalidPageTableFlags = 3,

    // GPA access failures

    HvTranslateGvaGpaUnmapped = 4,
    HvTranslateGvaGpaNoReadAccess = 5,
    HvTranslateGvaGpaNoWriteAccess = 6,
    HvTranslateGvaGpaIllegalOverlayAccess = 7,

    // Intercept of the memory access by either
    // - a higher VTL
    // - a nested hypervisor (due to a violation of the nested page table)
    HvTranslateGvaIntercept = 8,

    HvTranslateGvaGpaUnaccepted = 9
} HV_TRANSLATE_GVA_RESULT_CODE, *PHV_TRANSLATE_GVA_RESULT_CODE;

typedef union _HV_TRANSLATE_GVA_RESULT
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
        HV_UINT32 CacheType : 8;
        HV_UINT32 OverlayPage : 1;
        HV_UINT32 Reserved3 : 23;
    };
} HV_TRANSLATE_GVA_RESULT, *PHV_TRANSLATE_GVA_RESULT;

// Read and write GPA access flags.
typedef union _HV_ACCESS_GPA_CONTROL_FLAGS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 CacheType : 8; // Cache type for access
        HV_UINT64 Reserved : 56;
    };
} HV_ACCESS_GPA_CONTROL_FLAGS, *PHV_ACCESS_GPA_CONTROL_FLAGS;

typedef enum _HV_ACCESS_GPA_RESULT_CODE
{
    HvAccessGpaSuccess = 0,

    // GPA access failures

    HvAccessGpaUnmapped = 1,
    HvAccessGpaReadIntercept = 2,
    HvAccessGpaWriteIntercept = 3,
    HvAccessGpaIllegalOverlayAccess = 4
} HV_ACCESS_GPA_RESULT_CODE, *PHV_ACCESS_GPA_RESULT_CODE;

typedef union _HV_ACCESS_GPA_RESULT
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_ACCESS_GPA_RESULT_CODE ResultCode;
        HV_UINT32 Reserved;
    };
} HV_ACCESS_GPA_RESULT, *PHV_ACCESS_GPA_RESULT;

// Cache types.
typedef enum _HV_CACHE_TYPE
{
    HvCacheTypeX64Uncached = 0,
    HvCacheTypeX64WriteCombining = 1,
    HvCacheTypeX64WriteThrough = 4,
    HvCacheTypeX64WriteProtected = 5,
    HvCacheTypeX64WriteBack = 6
} HV_CACHE_TYPE, *PHV_CACHE_TYPE;

// HV Map GPA (Guest Physical Address) Flags

#define HV_MAP_GPA_KERNEL_EXECUTABLE 0x00000004
#define HV_MAP_GPA_USER_EXECUTABLE 0x00000008
#define HV_MAP_GPA_EXECUTABLE 0x0000000C
#define HV_MAP_GPA_PERMISSIONS_MASK 0x0000000F

typedef union _HV_GVA_RANGE_SIMPLE
{
    HV_UINT64 AsUINT64;
    struct
    {
        // Additional pages supplies the number of pages beyond one.
        HV_UINT64 AdditionalPages : 12;
        // GvaPageNumber supplies the top 54 most significant bits of the guest
        // virtual address space.
        HV_UINT64 GvaPageNumber : 52;
    };
} HV_GVA_RANGE_SIMPLE, *PHV_GVA_RANGE_SIMPLE;

typedef union _HV_GVA_RANGE_EXTENDED
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 AdditionalPages : 11;
        HV_UINT64 LargePage : 1;
        union
        {
            HV_UINT64 GvaPageNumber : 52;
            struct
            {
                HV_UINT64 PageSize : 1;
                HV_UINT64 Reserved : 8;
                HV_UINT64 GvaLargePageNumber : 43;
            };
        };
    };
} HV_GVA_RANGE_EXTENDED, *PHV_GVA_RANGE_EXTENDED;

// Gva Range
// The GVA range is a compressed range of GVA used by the TLB flush routines.
typedef union _HV_GVA_RANGE
{
    HV_UINT64 AsUINT64;
    HV_GVA_RANGE_SIMPLE Simple;
    HV_GVA_RANGE_EXTENDED Extended;
} HV_GVA_RANGE, *PHV_GVA_RANGE;

// Define index of synthetic interrupt source that receives intercept messages.

#define HV_SYNIC_INTERCEPTION_SINT_INDEX ((HV_SYNIC_SINT_INDEX)0)
#define HV_SYNIC_IOMMU_FAULT_SINT_INDEX ((HV_SYNIC_SINT_INDEX)1)
#define HV_SYNIC_VMBUS_SINT_INDEX ((HV_SYNIC_SINT_INDEX)2)
#define HV_SYNIC_FIRST_UNUSED_SINT_INDEX ((HV_SYNIC_SINT_INDEX)5)
#define HV_SYNIC_DOORBELL_SINT_INDEX     HV_SYNIC_FIRST_UNUSED_SINT_INDEX

// Define version of the synthetic interrupt controller.
#define HV_SYNIC_VERSION (1)

// Define the expected SynIC version.
#define HV_SYNIC_VERSION_1 (0x1)

// Define synthetic interrupt controller message constants.

#define HV_ANY_VP (0xFFFFFFFF)
#define HV_VP_INDEX_SELF (0xFFFFFFFE)

// Define lowest permissible vector that can be sent or received by the local
// APIC.
#define HV_SYNIC_APIC_MINIMUM_VECTOR 0x10

// Define hypervisor message types.
// SynIC messages encode the message type as a 32-bit number.
typedef enum _HV_MESSAGE_TYPE_PRIVATE
{
    // Opaque intercept message. The original intercept message is only
    // accessible from the mapped intercept message page.

    HvMessageTypeOpaqueIntercept = 0x8000003F,

    // SynIC intercepts

    HvMessageTypeSynicSintIntercept = 0x80000061,
    HvMessageTypeSynicSintDeliverable = 0x80000062,

    // Async call completion intercept

    HvMessageTypeAsyncCallCompletion = 0x80000070,

    // Platform-specific processor intercept messages

    HvMessageTypeX64LegacyFpError = 0x80010005,
    HvMessageTypeX64ProxyInterruptIntercept = 0x8001000f,
} HV_MESSAGE_TYPE_PRIVATE, *PHV_MESSAGE_TYPE_PRIVATE;

#define HV_MESSAGE_TYPE_HYPERVISOR_MASK (0x80000000)

// Define APIC EOI message.
typedef struct _HV_X64_APIC_EOI_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 InterruptVector;
} HV_X64_APIC_EOI_MESSAGE, *PHV_X64_APIC_EOI_MESSAGE;

// Define port type.
typedef enum _HV_PORT_TYPE
{
    HvPortTypeMessage = 1,
    HvPortTypeEvent = 2,
    HvPortTypeMonitor = 3,
    HvPortTypeDoorbell = 4 // Root Partition only
} HV_PORT_TYPE, *PHV_PORT_TYPE;

// Define port information structure.
typedef struct _HV_PORT_INFO
{
    HV_PORT_TYPE PortType;
    HV_UINT32 ReservedZ;
    union
    {
        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            HV_UINT64 ReservedZ;
        } MessagePortInfo;
        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            HV_UINT16 BaseFlagNumber;
            HV_UINT16 FlagCount;
            HV_UINT32 ReservedZ;
        } EventPortInfo;
        struct
        {
            HV_GPA MonitorAddress;
            HV_UINT64 ReservedZ;
        } MonitorPortInfo;
        struct
        {
            HV_UINT32 TargetSint;
            HV_UINT32 TargetVp;
            HV_UINT64 ReservedZ;
        } DoorbellPortInfo;
    };
} HV_PORT_INFO, *PHV_PORT_INFO;
typedef const HV_PORT_INFO* PCHV_PORT_INFO;

// Doorbell connection_info flags.

#define HV_DOORBELL_FLAG_TRIGGER_SIZE_MASK  0x00000007
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_ANY   0x00000000
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_BYTE  0x00000001
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_WORD  0x00000002
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_DWORD 0x00000003
#define HV_DOORBELL_FLAG_TRIGGER_SIZE_QWORD 0x00000004
#define HV_DOORBELL_FLAG_TRIGGER_ANY_VALUE  0x80000000

typedef struct _HV_CONNECTION_INFO
{
    HV_PORT_TYPE PortType;
    HV_UINT32 Padding;
    union
    {
        struct
        {
            HV_UINT64 ReservedZ;
        } MessageConnectionInfo;
        struct
        {
            HV_UINT64 ReservedZ;
        } EventConnectionInfo;
        struct
        {
            HV_GPA MonitorAddress;
        } MonitorConnectionInfo;
        struct
        {
            HV_UINT64 Gpa;
            HV_UINT64 TriggerValue;
            HV_UINT64 Flags;
        } DoorbellConnectionInfo;
    };
} HV_CONNECTION_INFO, *PHV_CONNECTION_INFO;
typedef const HV_CONNECTION_INFO* PCHV_CONNECTION_INFO;

// Define type of port property.
typedef HV_UINT64 HV_PORT_PROPERTY, *PHV_PORT_PROPERTY;

// Define enumeration of port property codes.
typedef enum _HV_PORT_PROPERTY_CODE
{
    HvPortPropertyPostCount = 0x00000000,
    HvPortPropertyPreferredTargetVp = 0x00000001
} HV_PORT_PROPERTY_CODE, *PHV_PORT_PROPERTY_CODE;

// Define synthetic interrupt controller message header.
typedef struct _HV_MESSAGE_HEADER_PRIVATE
{
    HV_UINT64 Reversed;
    union
    {
        HV_UINT64 OriginationId;
    };
} HV_MESSAGE_HEADER_PRIVATE, *PHV_MESSAGE_HEADER_PRIVATE;

// Define the number of message buffers associated with each port.
#define HV_PORT_MESSAGE_BUFFER_COUNT (16)

// Define the synthetic interrupt controller event flags format.
typedef HV_SYNIC_EVENT_FLAGS _HV_SYNIC_EVENT_FLAGS;
typedef HV_SYNIC_EVENT_FLAGS *PHV_SYNIC_EVENT_FLAGS;

// Define the format of the APIC_ASSIST register
typedef union _HV_X64_MSR_APIC_ASSIST_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enable : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_X64_MSR_APIC_ASSIST_CONTENTS, *PHV_X64_MSR_APIC_ASSIST_CONTENTS;

#define HV_VIRTUAL_APIC_NO_EOI_REQUIRED 0x0

// Format of the APIC assist page.
typedef union _HV_VIRTUAL_APIC_ASSIST
{
    HV_INT32 ApicFlags;
    struct
    {
        HV_UINT32 NoEOIRequired : 1;
    };
} HV_VIRTUAL_APIC_ASSIST, *PHV_VIRTUAL_APIC_ASSIST;

// Define virtual interrupt control structure.
typedef struct _HV_INTERRUPT_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_INTERRUPT_TYPE InterruptType;
        HV_UINT32 LevelTriggered : 1;
        HV_UINT32 LogicalDestinationMode : 1;
#if defined(_M_ARM64)
        HV_UINT32 Asserted : 1;
        HV_UINT32 Reserved : 29;
#elif defined(_M_AMD64) || defined(_M_IX86)
        HV_UINT32 Reserved : 30;
#endif
    };
} HV_INTERRUPT_CONTROL, *PHV_INTERRUPT_CONTROL;

// Emulated timer period
typedef union _HV_EMULATED_TIMER_PERIOD
{
    HV_UINT64 AsUINT64;
    HV_NANO100_DURATION Period;
} HV_EMULATED_TIMER_PERIOD, *PHV_EMULATED_TIMER_PERIOD;

// Periodic Timer route
typedef union _HV_EMULATED_TIMER_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 Vector : 8;
        HV_UINT32 DeliveryMode : 3;
        HV_UINT32 LogicalDestinationMode : 1;
        HV_UINT32 Enabled : 1;
        HV_UINT32 Reserved1 : 19;
        HV_UINT32 Reserved2 : 24;
        HV_UINT32 Mda : 8;
    };
} HV_EMULATED_TIMER_CONTROL, *PHV_EMULATED_TIMER_CONTROL;

// ACPI PM timer
typedef union _HV_PM_TIMER_INFO
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 Port : 16;
        HV_UINT32 Width24 : 1;
        HV_UINT32 Enabled : 1;
        HV_UINT32 Reserved1 : 14;
        HV_UINT32 Reserved2 : 32;
    };
} HV_PM_TIMER_INFO, *PHV_PM_TIMER_INFO;

// Definitions for the monitored notification facility

typedef union _HV_MONITOR_TRIGGER_GROUP
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 Pending;
        HV_UINT32 Armed;
    };
} HV_MONITOR_TRIGGER_GROUP, *PHV_MONITOR_TRIGGER_GROUP;

typedef struct _HV_MONITOR_PARAMETER
{
    HV_CONNECTION_ID ConnectionId;
    HV_UINT16 FlagNumber;
    HV_UINT16 ReservedZ;
} HV_MONITOR_PARAMETER, *PHV_MONITOR_PARAMETER;

typedef union _HV_MONITOR_TRIGGER_STATE
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 GroupEnable : 4;
        HV_UINT32 ReservedZ : 28;
    };
} HV_MONITOR_TRIGGER_STATE, *PHV_MONITOR_TRIGGER_STATE;

typedef struct _HV_MONITOR_PAGE
{
    HV_MONITOR_TRIGGER_STATE TriggerState;
    HV_UINT32 Reserved1;
    HV_MONITOR_TRIGGER_GROUP TriggerGroup[4];
    HV_UINT8 Reserved2[536];
    HV_UINT16 Latency[4][32];
    HV_UINT8 Reserved3[256];
    HV_MONITOR_PARAMETER Parameter[4][32];
    HV_UINT8 Reserved4[1984];
} HV_MONITOR_PAGE, *PHV_MONITOR_PAGE;
typedef volatile HV_MONITOR_PAGE* PVHV_MONITOR_PAGE;

// Debug channel identifier
typedef HV_UINT16 HV_DEBUG_CHANNEL_IDENTIFIER;

// Maximum size of the payload
#define HV_DEBUG_MAXIMUM_DATA_SIZE 4088

// Debug options for all calls
typedef HV_UINT32 HV_DEBUG_OPTIONS;

// Options flags for HvPostDebugData

#define HV_DEBUG_POST_LOOP 0x00000001

// Options flags for HvRetrieveDebugData

#define HV_DEBUG_RETRIEVE_LOOP 0x00000001
#define HV_DEBUG_RETRIEVE_TEST_ACTIVITY 0x00000002

// Options flags for HvResetDebugSession

#define HV_DEBUG_PURGE_INCOMING_DATA 0x00000001
#define HV_DEBUG_PURGE_OUTGOING_DATA 0x00000002

// Mux Protocol Defines

#define HV_MUX_PACKET_LEADER 0x11223344

#define HV_MUX_PACKET_TYPE_DATA 0x0001
#define HV_MUX_PACKET_TYPE_BREAKIN 0x0002
#define HV_MUX_PACKET_TYPE_QUERY_CHANNELS 0x0003

#define HV_MUX_PACKET_TYPE_MAXIMUM HV_MUX_PACKET_TYPE_QUERY_CHANNELS

#pragma pack(1)

typedef struct _HV_MUX_PACKET_HEADER
{
    HV_UINT32 Leader;
    HV_UINT16 Type;
    HV_UINT16 Length;
    HV_UINT32 CRC;
    HV_DEBUG_CHANNEL_IDENTIFIER Channel;
    HV_UINT16 Reserved;
} HV_MUX_PACKET_HEADER, *PHV_MUX_PACKET_HEADER;

// Channel data returned in a HV_MUX_PACKET_TYPE_QUERY_CHANNELS response.
// The ChannelIds arrays is variable length array
typedef struct
{
    HV_UINT32 Count;
    HV_DEBUG_CHANNEL_IDENTIFIER ChannelIds[1];
} MUX_CHANNEL_DATA, *PMUX_CHANNEL_DATA;

#pragma pack()

// Debug Channel Id

#define HV_DEBUG_CHANNEL_ID_HYPERVISOR 0x00000000
#define HV_DEBUG_CHANNEL_ID_ROOT 0x00000001
#define HV_DEBUG_CHANNEL_ID_DEFAULT 0x0000BADA
#define HV_DEBUG_CHANNEL_ID_ASSIGN_START 0x00000002
#define HV_DEBUG_CHANNEL_ID_FW_MAX 0x0000003E

// This structure is used to transfer crashdump information between the
// Hypervisor and the HvBoot.sys driver in the root Windows instance at the time
// of a Hypervisor BugCheck. It is allocated by HvBoot.sys during the Hypervisor
// launch process, and its SPA is handed in to the Hypervisor via the loader
// block.

#define HV_CRASHDUMP_AREA_VERSION 2
#define HV_IMAGE_NAME_MAX_LENGTH 32
#define HV_DEFAULT_CRASHDUMP_SPA_PAGES 5

typedef struct _HV_CRASHDUMP_AREA_V1
{
    // Version of the Crashdump Area structure

    HV_UINT32 Version;

    // Flags indicating content validity and other attributes of the Crashdump
    // Area

    union
    {
        HV_UINT32 FlagsAsUINT32;
        struct
        {
            // Indicates the contents of the Crashdump Area are valid
            HV_UINT32 Valid : 1;
            HV_UINT32 Reserved : 31;
        };
    };

    // Loaded Module Information

    HV_UINT64 HypervisorBase;
    HV_UINT32 SizeOfImage;
    HV_UINT16 ImageNameLength;
    HV_WCHAR ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    // Bugcheck error code fields

    HV_UINT64 BugCheckData[5];
    void* BugCheckErrorReturnAddress;

    // The root of the page table needed to lookup virtual addresses and the
    // debugger data block. The debugger data block contains all the information
    // necc. for the debugger to interpret the dump file. Of particular interest
    // within it is the prcb address that contain the processor state.

    HV_UINT64 PageTableBase;
    HV_UINT64 PfnDataBase;
    HV_UINT64 DebuggerDataBlock;
    HV_UINT32 NumberProcessors;

    // Context of the crashing thread

    HV_UINT32 ProcessorStateOffset;
    HV_UINT32 ProcessorStateSize;

    // The stack of crashing thread.

    HV_UINT32 CrashStackSize;
    HV_UINT32 CrashStackOffset;
    HV_UINT64 CrashStackAddress;
} HV_CRASHDUMP_AREA_V1, *PHV_CRASHDUMP_AREA_V1;

typedef struct _HV_CRASHDUMP_PROCESSOR_STATE
{
    // Context of the crashing thread.

    HV_UINT32 RegisterStateOffset;
    HV_UINT32 RegisterStateSize;

    // The stack of the crashing thread.

    HV_UINT32 CrashStackSize;
    HV_UINT32 CrashStackOffset;
    HV_UINT64 CrashStackAddress;

    // Platform specific data.

    HV_UINT32 PlatformStateSize;
    HV_UINT32 PlatformStateOffset;
} HV_CRASHDUMP_PROCESSOR_STATE, *PHV_CRASHDUMP_PROCESSOR_STATE;

// Size of code page to save during a crash.
#define CODE_CHUNK_SIZE 0x200

typedef struct _HV_CRASHDUMP_AREA_V2
{
    // Version of the Crashdump Area structure

    HV_UINT32 Version;

    // Flags indicating content validity and other attributes of the Crashdump
    // Area

    union
    {
        HV_UINT32 FlagsAsUINT32;
        struct
        {
            // Indicates the contents of the Crashdump Area are valid
            HV_UINT32 Valid : 1;
            HV_UINT32 Reserved : 31;
        };
    };

    // Loaded Module Information.

    HV_UINT64 HypervisorBase;
    HV_UINT32 SizeOfImage;
    HV_UINT32 CheckSum;

    // Partition State.

    HV_UINT64 CurrentPartition;
    HV_UINT64 PartitionsCreated;
    HV_UINT32 PartitionsRunning;
    HV_UINT64 CompartmentFreePfns;

    HV_UINT16 ImageNameLength;
    HV_WCHAR ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    // Bugcheck error code fields.

    HV_UINT64 BugCheckData[5];
    HV_UINT64 BugCheckErrorReturnAddress;

    // The root of the page table needed to lookup virtual addresses and the
    // debugger data block. The debugger data block contains all the information
    // necc. for the debugger to interpret the dump file. Of particular interest
    // within it is the prcb address that contain the processor state.

    HV_UINT64 PageTableBase;
    HV_UINT64 PfnDataBase;
    HV_UINT64 DebuggerDataBlock;
    HV_UINT32 NumberProcessors;
    HV_UINT32 CurrentProcessor;

    // Code page data. If we know the source of the fault this will have the in
    // memory copy of the code and its spa.

    HV_UINT64 CodeSpa;
    HV_UINT8 CodeChunk[CODE_CHUNK_SIZE];

    // Processor contexts. This is the offset to a set of
    // HV_CRASHDUMP_PROCESSOR_STATE structs. The crashing processor should
    // always be included.

    HV_UINT32 ContextCount;
    HV_UINT32 ContextOffset;
    HV_UINT32 ContextSize;

} HV_CRASHDUMP_AREA_V2, *PHV_CRASHDUMP_AREA_V2;

typedef struct _HV_CRASHDUMP_AREA
{
    // Version of the Crashdump Area structure

    HV_UINT32 Version;

    // Flags indicating content validity and other attributes of the Crashdump
    // Area

    union
    {
        HV_UINT32 FlagsAsUINT32;
        struct
        {
            // Indicates the contents of the Crashdump Area are valid
            HV_UINT32 Valid : 1;
            HV_UINT32 Reserved : 31;
        };
    };

    // Loaded Module Information.

    HV_UINT64 HypervisorBase;
    HV_UINT32 SizeOfImage;
    HV_UINT32 CheckSum;

    // Partition State.

    HV_UINT64 CurrentPartition;
    HV_UINT64 PartitionsCreated;
    HV_UINT32 PartitionsRunning;
    HV_UINT64 CompartmentFreePfns;

    HV_UINT16 ImageNameLength;
    HV_WCHAR ImageName[HV_IMAGE_NAME_MAX_LENGTH];

    // Bugcheck error code fields.

    HV_UINT64 BugCheckData[5];
    HV_UINT64 BugCheckErrorReturnAddress;

    // The root of the page table needed to lookup virtual addresses and the
    // debugger data block. The debugger data block contains all the information
    // necc. for the debugger to interpret the dump file. Of particular interest
    // within it is the prcb address that contain the processor state.

    HV_UINT64 PageTableBase;
    HV_UINT64 PfnDataBase;
    HV_UINT64 MaxPfn;
    HV_UINT64 DebuggerDataBlock;
    HV_UINT32 NumberProcessors;
    HV_UINT32 CurrentProcessor;

    // Code page data. If we know the source of the fault this will have the in
    // memory copy of the code and its spa.

    HV_UINT64 CodeSpa;
    HV_UINT8 CodeChunk[CODE_CHUNK_SIZE];

    // Processor contexts. This is the offset to a set of
    // HV_CRASHDUMP_PROCESSOR_STATE structs. The crashing processor should
    // always be included.

    HV_UINT32 ContextCount;
    HV_UINT32 ContextOffset;
    HV_UINT32 ContextSize;

    HV_UINT32 PfnEntrySize;
    HV_UINT16 AllocatedPfnEntryMask;
    HV_UINT8 Partial;

} HV_CRASHDUMP_AREA, *PHV_CRASHDUMP_AREA;

#if defined(_M_AMD64) || defined(_M_IX86)

// Define virtual processor execution state bitfield.
typedef union _HV_X64_VP_EXECUTION_STATE
{
    HV_UINT16 AsUINT16;
    struct
    {
        HV_UINT16 Cpl : 2;
        HV_UINT16 Cr0Pe : 1;
        HV_UINT16 Cr0Am : 1;
        HV_UINT16 EferLma : 1;
        HV_UINT16 DebugActive : 1;
        HV_UINT16 InterruptionPending : 1;
        HV_UINT16 Vtl : 4;
        HV_UINT16 EnclaveMode : 1;
        HV_UINT16 InterruptShadow : 1;
        HV_UINT16 VirtualizationFaultActive : 1;
        HV_UINT16 Reserved : 2;
    };
} HV_X64_VP_EXECUTION_STATE, *PHV_X64_VP_EXECUTION_STATE;

// Define intercept message header structure.
typedef struct _HV_X64_INTERCEPT_MESSAGE_HEADER
{
    HV_VP_INDEX VpIndex;
    HV_UINT8 InstructionLength : 4;
    HV_UINT8 Cr8 : 4; // Only set for exo partitions
    HV_UINT8 InterceptAccessType; // HV_INTERCEPT_ACCESS_TYPE_MASK
    HV_X64_VP_EXECUTION_STATE ExecutionState;
    HV_X64_SEGMENT_REGISTER CsSegment;
    HV_UINT64 Rip;
    HV_UINT64 Rflags;
} HV_X64_INTERCEPT_MESSAGE_HEADER, *PHV_X64_INTERCEPT_MESSAGE_HEADER;

// Define memory access information structure.
typedef struct _HV_X64_MEMORY_ACCESS_INFO
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 GvaValid : 1;
        HV_UINT8 GvaGpaValid : 1;
        HV_UINT8 HypercallOutputPending : 1;
        HV_UINT8 TlbLockedNoOverlay : 1;
        HV_UINT8 Reserved : 4;
    };
} HV_X64_MEMORY_ACCESS_INFO, *PHV_X64_MEMORY_ACCESS_INFO;

// Define IO port access information structure.
typedef struct _HV_X64_IO_PORT_ACCESS_INFO
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 AccessSize : 3;
        HV_UINT8 StringOp : 1;
        HV_UINT8 RepPrefix : 1;
        HV_UINT8 Reserved : 3;
    };
} HV_X64_IO_PORT_ACCESS_INFO, *PHV_X64_IO_PORT_ACCESS_INFO;

// Define exception information structure.
typedef struct _HV_X64_EXCEPTION_INFO
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 ErrorCodeValid : 1;
        HV_UINT8 SoftwareException : 1;
        HV_UINT8 Reserved : 6;
    };
} HV_X64_EXCEPTION_INFO, *PHV_X64_EXCEPTION_INFO;

// Define memory access message structure. This message structure is used for
// memory intercepts, GPA not present intercepts and SPA access violation
// intercepts.
typedef struct _HV_X64_MEMORY_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_CACHE_TYPE CacheType;
    HV_UINT8 InstructionByteCount;
    HV_X64_MEMORY_ACCESS_INFO MemoryAccessInfo;
    HV_UINT8 TprPriority;
    HV_UINT8 Reserved1;
    HV_UINT64 GuestVirtualAddress;
    HV_UINT64 GuestPhysicalAddress;
    HV_UINT8 InstructionBytes[16];

    // Below definition are not found in mshv MIT-licensed hv headers.

    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    HV_UINT64 Rax;
    HV_UINT64 Rcx;
    HV_UINT64 Rdx;
    HV_UINT64 Rbx;
    HV_UINT64 Rsp;
    HV_UINT64 Rbp;
    HV_UINT64 Rsi;
    HV_UINT64 Rdi;
    HV_UINT64 R8;
    HV_UINT64 R9;
    HV_UINT64 R10;
    HV_UINT64 R11;
    HV_UINT64 R12;
    HV_UINT64 R13;
    HV_UINT64 R14;
    HV_UINT64 R15;
} HV_X64_MEMORY_INTERCEPT_MESSAGE, *PHV_X64_MEMORY_INTERCEPT_MESSAGE;

// Define CPUID intercept message structure.
typedef struct _HV_X64_CPUID_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT64 Rax;
    HV_UINT64 Rcx;
    HV_UINT64 Rdx;
    HV_UINT64 Rbx;
    HV_UINT64 DefaultResultRax;
    HV_UINT64 DefaultResultRcx;
    HV_UINT64 DefaultResultRdx;
    HV_UINT64 DefaultResultRbx;
} HV_X64_CPUID_INTERCEPT_MESSAGE, *PHV_X64_CPUID_INTERCEPT_MESSAGE;

// Define MSR intercept message structure.
typedef struct _HV_X64_MSR_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT32 MsrNumber;
    HV_UINT32 Reserved;
    HV_UINT64 Rdx;
    HV_UINT64 Rax;
} HV_X64_MSR_INTERCEPT_MESSAGE, *PHV_X64_MSR_INTERCEPT_MESSAGE;

// Define IO access intercept message structure.
typedef struct _HV_X64_IO_PORT_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT16 PortNumber;
    HV_X64_IO_PORT_ACCESS_INFO AccessInfo;
    HV_UINT8 InstructionByteCount;
    HV_UINT32 Reserved;
    HV_UINT64 Rax;
    HV_UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER EsSegment;
    HV_UINT64 Rcx;
    HV_UINT64 Rsi;
    HV_UINT64 Rdi;
} HV_X64_IO_PORT_INTERCEPT_MESSAGE, *PHV_X64_IO_PORT_INTERCEPT_MESSAGE;

// Define exception intercept message.
typedef struct _HV_X64_EXCEPTION_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT16 ExceptionVector;
    HV_X64_EXCEPTION_INFO ExceptionInfo;
    HV_UINT8 InstructionByteCount;
    HV_UINT32 ErrorCode;
    HV_UINT64 ExceptionParameter;
    HV_UINT64 Reserved;
    HV_UINT8 InstructionBytes[16];
    HV_X64_SEGMENT_REGISTER DsSegment;
    HV_X64_SEGMENT_REGISTER SsSegment;
    HV_UINT64 Rax;
    HV_UINT64 Rcx;
    HV_UINT64 Rdx;
    HV_UINT64 Rbx;
    HV_UINT64 Rsp;
    HV_UINT64 Rbp;
    HV_UINT64 Rsi;
    HV_UINT64 Rdi;
    HV_UINT64 R8;
    HV_UINT64 R9;
    HV_UINT64 R10;
    HV_UINT64 R11;
    HV_UINT64 R12;
    HV_UINT64 R13;
    HV_UINT64 R14;
    HV_UINT64 R15;
} HV_X64_EXCEPTION_INTERCEPT_MESSAGE, *PHV_X64_EXCEPTION_INTERCEPT_MESSAGE;

// Define legacy floating point error message.
typedef struct _HV_X64_LEGACY_FP_ERROR_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Reserved;
} HV_X64_LEGACY_FP_ERROR_MESSAGE, *PHV_X64_LEGACY_FP_ERROR_MESSAGE;

// Define invalid virtual processor register message.
typedef struct _HV_X64_INVALID_VP_REGISTER_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Reserved;
} HV_X64_INVALID_VP_REGISTER_MESSAGE, *PHV_X64_INVALID_VP_REGISTER_MESSAGE;

// Define virtual processor unrecoverable error message.
typedef struct _HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
} HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE, *PHV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE;

// Define the unsupported feature codes.
typedef enum _HV_X64_UNSUPPORTED_FEATURE_CODE
{
    HvUnsupportedFeatureIntercept = 1,
    HvUnsupportedFeatureTaskSwitchTss = 2
}HV_X64_UNSUPPORTED_FEATURE_CODE, *PHV_X64_UNSUPPORTED_FEATURE_CODE;

// Define unsupported feature message.
typedef struct _HV_X64_UNSUPPORTED_FEATURE_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_X64_UNSUPPORTED_FEATURE_CODE FeatureCode;
    HV_UINT64 FeatureParameter;
} HV_X64_UNSUPPORTED_FEATURE_MESSAGE, *PHV_X64_UNSUPPORTED_FEATURE_MESSAGE;

#endif

// Unknown hypercall code but the hvgdk.h in WDK have that
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_REGISTER_CODE
{
    HV_PARTITION_ID PartitionId;
    HV_UINT32 RegisterIndex;
} HV_INPUT_GET_VP_REGISTER_CODE, *PHV_INPUT_GET_VP_REGISTER_CODE;

// Versioning definitions used for guests reporting themselves to the
// hypervisor, and vice versa.

typedef enum _HV_GUEST_OS_VENDOR_PRIVATE
{
    HvGuestOsVendorHPE = 0x0002,
    HvGuestOsVendorLANCOM = 0x0200,
} HV_GUEST_OS_VENDOR_PRIVATE, *PHV_GUEST_OS_VENDOR_PRIVATE;

typedef enum _HV_GUEST_OS_OPENSOURCE_IDS
{
    HvGuestOsOpenSourceUndefined = 0x0,
    HvGuestOsOpenSourceLinux = 0x1,
    HvGuestOsOpenSourceFreeBSD = 0x2,
    HvGuestOsOpenSourceXen = 0x3,
    HvGuestOsOpenSourceIllumos = 0x4,
} HV_GUEST_OS_OPENSOURCE_IDS, *PHV_GUEST_OS_OPENSOURCE_IDS;

// Partition Properties

typedef HV_UINT64 HV_PARTITION_PROPERTY, *PHV_PARTITION_PROPERTY;

typedef enum _HV_PARTITION_PROPERTY_CODE
{
    // Privilege properties

    HvPartitionPropertyPrivilegeFlags = 0x00010000,
    HvPartitionPropertySyntheticProcFeatures = 0x00010001,

    // Scheduling properties

    HvPartitionPropertySuspend = 0x00020000,
    HvPartitionPropertyCpuReserve = 0x00020001,
    HvPartitionPropertyCpuCap = 0x00020002,
    HvPartitionPropertyCpuWeight = 0x00020003,
    HvPartitionPropertyCpuGroupId = 0x00020004,

    // Timer assist properties

    HvPartitionPropertyEmulatedTimerPeriod = 0x00030000,
    HvPartitionPropertyEmulatedTimerControl = 0x00030001,
    HvPartitionPropertyPmTimerAssist = 0x00030002,
    HvPartitionPropertyTimeFreeze = 0x00030003,

    // Debugging properties

    HvPartitionPropertyDebugChannelId = 0x00040000,

    // Resource properties

    HvPartitionPropertyVirtualTlbPageCount = 0x00050000,
    HvPartitionPropertyVsmConfig = 0x00050001,
    HvPartitionPropertyZeroMemoryOnReset = 0x00050002,
    HvPartitionPropertyProcessorsPerSocket = 0x00050003,
    HvPartitionPropertyNestedTlbSize = 0x00050004,
    HvPartitionPropertyGpaPageAccessTracking = 0x00050005,
    HvPartitionPropertyIsolationState = 0x0005000C,
    HvPartitionPropertyUnimplementedMsrAction = 0x00050017,

    // Compatibility properties

    HvPartitionPropertyProcessorVendor = 0x00060000,
    HvPartitionPropertyProcessorFeatures = 0x00060001,
    HvPartitionPropertyProcessorXsaveFeatures = 0x00060002,
    HvPartitionPropertyProcessorCLFlushSize = 0x00060003,
    HvPartitionPropertyEnlightenmentModifications = 0x00060004,
    HvPartitionPropertyCompatibilityVersion = 0x00060005,
    HvPartitionPropertyPhysicalAddressWidth = 0x00060006,
    HvPartitionPropertyMaxXsaveDataSize = 0x00060008,
    HvPartitionPropertyProcessorClockFrequency = 0x00060009,

    HvPartitionPropertyGuestOsId = 0x00070000,

    HvPartitionPropertyProcessorVirtualizationFeatures = 0x00080000,
} HV_PARTITION_PROPERTY_CODE, *PHV_PARTITION_PROPERTY_CODE;

// Partition scheduling property ranges

#define HvPartitionPropertyMinimumCpuReserve (0 << 16)
#define HvPartitionPropertyMaximumCpuReserve (1 << 16)
#define HvPartitionPropertyMinimumCpuCap (0 << 16)
#define HvPartitionPropertyMaximumCpuCap (1 << 16)
#define HvPartitionPropertyMinimumCpuWeight 1
#define HvPartitionPropertyMaximumCpuWeight 10000

// External names used to manupulate registers
typedef enum _HV_REGISTER_NAME_PRIVATE
{
    // Suspend Registers

    HvRegisterInternalActivityState = 0x00000004,

    // System Reset

    HvRegisterSystemReset = 0x00000230,

    // Arm64 Control Registers

    HvArm64RegisterSctlrEl1 = 0x00040002,
    HvArm64RegisterTtbr0El1 = 0x00040005,
    HvArm64RegisterTtbr1El1 = 0x00040006,
    HvArm64RegisterTcrEl1 = 0x00040007,
    HvArm64RegisterMairEl1 = 0x0004000B,
    HvArm64RegisterVbarEl1 = 0x0004000C,

    // X64 Cache control MSRs

    HvX64RegisterMtrrCap = 0x0008000D,
    HvX64RegisterMtrrDefType = 0x0008000E,
    HvX64RegisterMtrrPhysBase0 = 0x00080010,
    HvX64RegisterMtrrPhysBase1 = 0x00080011,
    HvX64RegisterMtrrPhysBase2 = 0x00080012,
    HvX64RegisterMtrrPhysBase3 = 0x00080013,
    HvX64RegisterMtrrPhysBase4 = 0x00080014,
    HvX64RegisterMtrrPhysBase5 = 0x00080015,
    HvX64RegisterMtrrPhysBase6 = 0x00080016,
    HvX64RegisterMtrrPhysBase7 = 0x00080017,
    HvX64RegisterMtrrPhysBase8 = 0x00080018,
    HvX64RegisterMtrrPhysBase9 = 0x00080019,
    HvX64RegisterMtrrPhysBaseA = 0x0008001A,
    HvX64RegisterMtrrPhysBaseB = 0x0008001B,
    HvX64RegisterMtrrPhysBaseC = 0x0008001C,
    HvX64RegisterMtrrPhysBaseD = 0x0008001D,
    HvX64RegisterMtrrPhysBaseE = 0x0008001E,
    HvX64RegisterMtrrPhysBaseF = 0x0008001F,
    HvX64RegisterMtrrPhysMask0 = 0x00080040,
    HvX64RegisterMtrrPhysMask1 = 0x00080041,
    HvX64RegisterMtrrPhysMask2 = 0x00080042,
    HvX64RegisterMtrrPhysMask3 = 0x00080043,
    HvX64RegisterMtrrPhysMask4 = 0x00080044,
    HvX64RegisterMtrrPhysMask5 = 0x00080045,
    HvX64RegisterMtrrPhysMask6 = 0x00080046,
    HvX64RegisterMtrrPhysMask7 = 0x00080047,
    HvX64RegisterMtrrPhysMask8 = 0x00080048,
    HvX64RegisterMtrrPhysMask9 = 0x00080049,
    HvX64RegisterMtrrPhysMaskA = 0x0008004A,
    HvX64RegisterMtrrPhysMaskB = 0x0008004B,
    HvX64RegisterMtrrPhysMaskC = 0x0008004C,
    HvX64RegisterMtrrPhysMaskD = 0x0008004D,
    HvX64RegisterMtrrPhysMaskE = 0x0008004E,
    HvX64RegisterMtrrPhysMaskF = 0x0008004F,
    HvX64RegisterMtrrFix64k00000 = 0x00080070,
    HvX64RegisterMtrrFix16k80000 = 0x00080071,
    HvX64RegisterMtrrFix16kA0000 = 0x00080072,
    HvX64RegisterMtrrFix4kC0000 = 0x00080073,
    HvX64RegisterMtrrFix4kC8000 = 0x00080074,
    HvX64RegisterMtrrFix4kD0000 = 0x00080075,
    HvX64RegisterMtrrFix4kD8000 = 0x00080076,
    HvX64RegisterMtrrFix4kE0000 = 0x00080077,
    HvX64RegisterMtrrFix4kE8000 = 0x00080078,
    HvX64RegisterMtrrFix4kF0000 = 0x00080079,
    HvX64RegisterMtrrFix4kF8000 = 0x0008007A,
    HvX64RegisterMCount = 0x0008007E,
    HvX64RegisterACount = 0x0008007F,
    HvX64RegisterVirtSpecCtrl = 0x00080086,
    HvX64RegisterTscVirtualOffset = 0x00080087,
    HvX64RegisterTsxCtrl = 0x00080088,
    HvX64RegisterMsrMcUpdatePatchLevel = 0x00080089,
    HvX64RegisterAvailable1 = 0x0008008A,
    HvX64RegisterXss = 0x0008008B,
    HvX64RegisterUCet = 0x0008008C,
    HvX64RegisterSCet = 0x0008008D,
    HvX64RegisterSsp = 0x0008008E,
    HvX64RegisterPl0Ssp = 0x0008008F,
    HvX64RegisterPl1Ssp = 0x00080090,
    HvX64RegisterPl2Ssp = 0x00080091,
    HvX64RegisterPl3Ssp = 0x00080092,
    HvX64RegisterInterruptSspTableAddr = 0x00080093,
    HvX64RegisterTscVirtualMultiplier = 0x00080094,
    HvX64RegisterTscDeadline = 0x00080095,
    HvX64RegisterTscAdjust = 0x00080096,
    HvX64RegisterPasid = 0x00080097,
    HvX64RegisterUmwaitControl = 0x00080098,
    HvX64RegisterXfd = 0x00080099,
    HvX64RegisterXfdErr = 0x0008009A,

    // Hypervisor-defined MSRs (Misc)

    HvX64RegisterVpRuntime = 0x00090000,

    // Virtual APIC registers MSRs

    HvRegisterReferenceTsc = 0x00090017,
    HvRegisterVpConfig = 0x00090018,
    HvRegisterGhcb = 0x00090019,
    HvRegisterReferenceTscSequence = 0x0009001A,
    HvRegisterGuestSchedulerEvent = 0x0009001B,
    HvX64RegisterRegPage = 0x0009001C,

    // AMD SEV SNP configuration register
	HvX64RegisterSevControl = 0x00090040,

    // XSAVE/XRSTOR register names.

    // XSAVE AFX extended state registers.

    HvX64RegisterYmm0Low = 0x000C0000,
    HvX64RegisterYmm1Low = 0x000C0001,
    HvX64RegisterYmm2Low = 0x000C0002,
    HvX64RegisterYmm3Low = 0x000C0003,
    HvX64RegisterYmm4Low = 0x000C0004,
    HvX64RegisterYmm5Low = 0x000C0005,
    HvX64RegisterYmm6Low = 0x000C0006,
    HvX64RegisterYmm7Low = 0x000C0007,
    HvX64RegisterYmm8Low = 0x000C0008,
    HvX64RegisterYmm9Low = 0x000C0009,
    HvX64RegisterYmm10Low = 0x000C000A,
    HvX64RegisterYmm11Low = 0x000C000B,
    HvX64RegisterYmm12Low = 0x000C000C,
    HvX64RegisterYmm13Low = 0x000C000D,
    HvX64RegisterYmm14Low = 0x000C000E,
    HvX64RegisterYmm15Low = 0x000C000F,
    HvX64RegisterYmm0High = 0x000C0010,
    HvX64RegisterYmm1High = 0x000C0011,
    HvX64RegisterYmm2High = 0x000C0012,
    HvX64RegisterYmm3High = 0x000C0013,
    HvX64RegisterYmm4High = 0x000C0014,
    HvX64RegisterYmm5High = 0x000C0015,
    HvX64RegisterYmm6High = 0x000C0016,
    HvX64RegisterYmm7High = 0x000C0017,
    HvX64RegisterYmm8High = 0x000C0018,
    HvX64RegisterYmm9High = 0x000C0019,
    HvX64RegisterYmm10High = 0x000C001A,
    HvX64RegisterYmm11High = 0x000C001B,
    HvX64RegisterYmm12High = 0x000C001C,
    HvX64RegisterYmm13High = 0x000C001D,
    HvX64RegisterYmm14High = 0x000C001E,
    HvX64RegisterYmm15High = 0x000C001F,

    // Synthetic VSM registers

    HvRegisterVsmVpVtlControl = 0x000D0000,
    HvRegisterGuestVsmPartitionConfig = 0x000D0008,
} HV_REGISTER_NAME_PRIVATE, *PHV_REGISTER_NAME_PRIVATE;
typedef const HV_REGISTER_NAME* PCHV_REGISTER_NAME;

// Flags used for specifying the stats object when making mapping/unmapping
// stats page hypercall.

typedef HV_UINT16 HV_STATS_OBJECT_FLAG;

#define HvStatsObjectSelfStats      0x0001

// Definitions for the stats hypercall structures.
typedef union _HV_STATS_OBJECT_IDENTITY
{
    // HvStatsObjectHypervisor
    struct
    {
        HV_UINT64 ReservedZ0;
        HV_UINT32 ReservedZ1;
        HV_UINT16 ReservedZ2;
        HV_UINT8 ReservedZ3;
        HV_UINT8 ReservedZ4;
    } Hypervisor;
    // HvStatsObjectLogicalProcessor
    struct
    {
        HV_LOGICAL_PROCESSOR_INDEX LogicalProcessorIndex;
        HV_UINT32 ReservedZ0;
        HV_UINT32 ReservedZ1;
        HV_UINT16 ReservedZ2;
        HV_UINT8 ReservedZ3;
        HV_UINT8 ReservedZ4;
    } LogicalProcessor;
    // HvStatsObjectPartition
    struct
    {
        HV_PARTITION_ID PartitionId;
        HV_UINT32 ReservedZ1;
        HV_STATS_OBJECT_FLAG Flags;
        HV_UINT8 ReservedZ3;
        HV_UINT8 ReservedZ4;
    } Partition;
    // HvStatsObjectVp
    struct
    {
        HV_PARTITION_ID PartitionId;
        HV_VP_INDEX VpIndex;
        HV_STATS_OBJECT_FLAG Flags;
        HV_UINT8 ReservedZ3;
        HV_UINT8 ReservedZ4;
    } Vp;
} HV_STATS_OBJECT_IDENTITY, *PHV_STATS_OBJECT_IDENTITY;
typedef const HV_STATS_OBJECT_IDENTITY *PCHV_STATS_OBJECT_IDENTITY;

// *****************************************************************************
// Hypervisor Beyond WDK's hvgdk.h Definitions
//

typedef HV_UINT8 HV_BOOLEAN;
typedef HV_BOOLEAN* PHV_BOOLEAN;
typedef const HV_BOOLEAN* PCHV_BOOLEAN;

/* Memory Address Space Types */

typedef const HV_SPA* PCHV_SPA;
typedef const HV_GPA* PCHV_GPA;
typedef const HV_GVA* PCHV_GVA;

typedef HV_UINT32 HV_SPA_PAGE_OFFSET;

// 5-level paging enabled
#define X64_CR4_LA57 0x0000000000001000

#define X64_PTE_PRESENT 0x1
#define X64_PTE_READ_WRITE 0x2
#define X64_PTE_ACCESSED 0x20
#define X64_PTE_DIRTY 0x40
#define X64_PTE_LARGE_PAGE 0x80

#define PAGE_TABLE_ENTRY_COUNT 512

#define X64_PAGE_SHIFT 12
#define X64_PTE_BITS 9

/* Partition Management Data Types */

typedef const HV_PARTITION_ID* PCHV_PARTITION_ID;

/* Virtual Processor Management */

typedef enum _HV_GENERIC_SET_FORMAT
{
    HvGenericSetSparse4k,
    HvGenericSetAll,
    HvGenericSetInvalid
} HV_GENERIC_SET_FORMAT, *PHV_GENERIC_SET_FORMAT;

typedef struct _HV_GENERIC_SET
{
    HV_UINT64 Format;
    HV_UINT64 ValidBanksMask;
    HV_UINT64 BankContents[];
} HV_GENERIC_SET, *PHV_GENERIC_SET, HV_VP_SET, *PHV_VP_SET;

typedef HV_UINT32 HV_APIC_ID;
typedef HV_APIC_ID* PHV_APIC_ID;
typedef const HV_APIC_ID* PCHV_APIC_ID;

/* Virtual MMU */

typedef const HV_ADDRESS_SPACE_ID* PCHV_ADDRESS_SPACE_ID;

typedef const HV_FLUSH_FLAGS* PCHV_FLUSH_FLAGS;

typedef const HV_TRANSLATE_GVA_CONTROL_FLAGS* PCHV_TRANSLATE_GVA_CONTROL_FLAGS;

typedef const HV_VTL* PCHV_VTL;

#define HV_NUM_VTLS 2
#define HV_INVALID_VTL ((HV_VTL)-1)
#define HV_VTL_ALL 0xF

typedef union _HV_X64_PENDING_MEMORY_INTERCEPT_EVENT
{
    HV_UINT64 AsUINT64[4];
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3;
        HV_UINT8 Reserved0 : 4;
        HV_VTL TargetVtl;
        HV_UINT8 AccessType;
        HV_UINT8 GuestLinearAddressValid : 1;
        HV_UINT8 Reserved1 : 7;
        HV_UINT32 Reserved2;
        HV_UINT64 GuestLinearAddress;
        HV_UINT64 GuestPhysicalAddress;
        HV_UINT64 Reserved3;
    };
} HV_X64_PENDING_MEMORY_INTERCEPT_EVENT, *PHV_X64_PENDING_MEMORY_INTERCEPT_EVENT;

typedef union _HV_X64_PENDING_NESTED_MEMORY_INTERCEPT_EVENT
{
    HV_UINT64 AsUINT64[4];
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3;
        HV_UINT8 Reserved0 : 4;
        HV_UINT8 AccessType;
        HV_UINT8 GuestAccessPermission;
        HV_UINT8 GuestLinearAddressValid : 1;
        HV_UINT8 CausedByGpaAccess : 1;
        HV_UINT8 PageTableMisconfiguration : 1;
        HV_UINT8 Reserved1 : 5;
        HV_UINT32 Reserved2;
        HV_UINT64 GuestLinearAddress;
        HV_UINT64 GuestNestedPhysicalAddress;
        HV_UINT64 Reserved3;
    };
} HV_X64_PENDING_NESTED_MEMORY_INTERCEPT_EVENT, *PHV_X64_PENDING_NESTED_MEMORY_INTERCEPT_EVENT;

typedef union _HV_X64_PENDING_EVENT
{
    struct
    {
        HV_UINT128 Reg0;
        HV_UINT128 Reg1;
    };
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3;
        HV_UINT8 Reserved : 4;
        HV_UINT8 EventData[15];
    };
    HV_X64_PENDING_EXCEPTION_EVENT Exception;
    HV_X64_PENDING_MEMORY_INTERCEPT_EVENT MemoryIntercept;
    HV_X64_PENDING_NESTED_MEMORY_INTERCEPT_EVENT NestedMemoryIntercept;
} HV_X64_PENDING_EVENT, *PHV_X64_PENDING_EVENT;

typedef struct _HV_TRANSLATE_GVA_RESULT_EX
{
    HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
    HV_UINT32 CacheType : 8;
    HV_UINT32 OverlayPage : 1;
    HV_UINT32 Reserved : 23;
    HV_X64_PENDING_EVENT EventInfo; // Not in TLFS
} HV_TRANSLATE_GVA_RESULT_EX, *PHV_TRANSLATE_GVA_RESULT_EX;

/* Virtual Interrupt */

typedef const HV_INTERRUPT_VECTOR* PCHV_INTERRUPT_VECTOR;

typedef enum _HV_INTERRUPT_SOURCE
{
    HvInterruptSourceMsi = 1, // MSI and MSI-X
    HvInterruptSourceIoApic,
    HvInterruptSourceGicd
} HV_INTERRUPT_SOURCE, *PHV_INTERRUPT_SOURCE;

typedef union _HV_MSI_ADDRESS_REGISTER
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 Reserved1 : 2;
        HV_UINT32 DestinationMode : 1;
        HV_UINT32 RedirectionHint : 1;
        HV_UINT32 Reserved2 : 8;
        HV_UINT32 DestinationId : 8;
        HV_UINT32 MsiBase : 12;
    };
} HV_MSI_ADDRESS_REGISTER, *PHV_MSI_ADDRESS_REGISTER;

typedef union _HV_MSI_DATA_REGISTER
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 Vector : 8;
        HV_UINT32 DeliveryMode : 3;
        HV_UINT32 Reserved1 : 3;
        HV_UINT32 LevelAssert : 1;
        HV_UINT32 TriggerMode : 1;
        HV_UINT32 Reserved2 : 16;
    };
} HV_MSI_DATA_REGISTER, *PHV_MSI_DATA_REGISTER;

typedef union _HV_MSI_ENTRY
{
#if defined(_M_ARM64)
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_UINT64 Address;
        HV_MSI_DATA_REGISTER Data;
        HV_UINT32 Reserved;
    };
#elif defined(_M_AMD64) || defined(_M_IX86)
    HV_UINT64 AsUINT64;
    struct
    {
        HV_MSI_ADDRESS_REGISTER Address;
        HV_MSI_DATA_REGISTER Data;
    };
#endif
} HV_MSI_ENTRY, *PHV_MSI_ENTRY;

typedef union _HV_IOAPIC_RTE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 Vector : 8;
        HV_UINT32 DeliveryMode : 3;
        HV_UINT32 DestinationMode : 1;
        HV_UINT32 DeliveryStatus : 1;
        HV_UINT32 InterruptPolarity : 1;
        HV_UINT32 RemoteIRR : 1;
        HV_UINT32 TriggerMode : 1;
        HV_UINT32 InterruptMask : 1;
        HV_UINT32 Reserved1 : 15;
        HV_UINT32 Reserved2 : 24;
        HV_UINT32 DestinationId : 8;
    };
    struct
    {
        HV_UINT32 LowUINT32;
        HV_UINT32 HighUINT32;
    };
} HV_IOAPIC_RTE, *PHV_IOAPIC_RTE;

typedef union _HV_GICD_ENTRY
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 Polarity : 1;
        HV_UINT32 TriggerMode : 1;
        HV_UINT32 Line : 10;
        HV_UINT32 ProcessorTarget : 3;
        HV_UINT32 Vector : 10;
        HV_UINT32 Priority : 7;
        HV_UINT32 UnitId : 24;
        HV_UINT32 Flags : 8;
    };
    struct
    {
        HV_UINT32 LowUINT32;
        HV_UINT32 HighUINT32;
    };
} HV_GICD_ENTRY, *PHV_GICD_ENTRY;

typedef struct _HV_INTERRUPT_ENTRY
{
    HV_INTERRUPT_SOURCE InterruptSource;
    HV_UINT32 Reserved;
    union
    {
        HV_MSI_ENTRY MsiEntry;
        HV_IOAPIC_RTE IoApicRte;
        HV_GICD_ENTRY GicdEntry;
        HV_UINT64 Data;
    };
} HV_INTERRUPT_ENTRY, *PHV_INTERRUPT_ENTRY;

#define HV_DEVICE_INTERRUPT_TARGET_MULTICAST 1
#define HV_DEVICE_INTERRUPT_TARGET_PROCESSOR_SET 2

typedef struct _HV_DEVICE_INTERRUPT_TARGET
{
    HV_INTERRUPT_VECTOR Vector;
    HV_UINT32 Flags;
    union
    {
        HV_UINT64 ProcessorMask;
        HV_UINT64 ProcessorSet[HV_ANYSIZE_ARRAY];
    };
} HV_DEVICE_INTERRUPT_TARGET, *PHV_DEVICE_INTERRUPT_TARGET;

/* Inter-Partition Communication */

typedef const HV_SYNIC_SINT_INDEX* PCHV_SYNIC_SINT_INDEX;

/* Intercept Message */

typedef HV_INTERCEPT_ACCESS_TYPE_MASK* PHV_INTERCEPT_ACCESS_TYPE_MASK;
typedef const HV_INTERCEPT_ACCESS_TYPE_MASK* PCHV_INTERCEPT_ACCESS_TYPE_MASK;

typedef const HV_NANO100_TIME* PCHV_NANO100_TIME;

/* Virtual Secure Mode */

typedef union _HV_REGISTER_VSM_PARTITION_STATUS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 EnabledVtlSet : 16;
        HV_UINT64 MaximumVtl : 4;
        HV_UINT64 MbecEnabledVtlSet : 16;
        HV_UINT64 ReservedZ : 28;
    };
} HV_REGISTER_VSM_PARTITION_STATUS, *PHV_REGISTER_VSM_PARTITION_STATUS;

typedef union _HV_REGISTER_VSM_VP_STATUS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 ActiveVtl : 4;
        HV_UINT64 ActiveMbecEnabled : 1;
        HV_UINT64 ReservedZ0 : 11;
        HV_UINT64 EnabledVtlSet : 16;
        HV_UINT64 ReservedZ1 : 32;
    };
} HV_REGISTER_VSM_VP_STATUS, *PHV_REGISTER_VSM_VP_STATUS;

typedef union _HV_REGISTER_VSM_PARTITION_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 EnableVtlProtection : 1;
        HV_UINT64 DefaultVtlProtectionMask : 4;
        HV_UINT64 ZeroMemoryOnReset : 1;
        HV_UINT64 DenyLowerVtlStartup : 1;
        HV_UINT64 InterceptAcceptance : 1;
        HV_UINT64 InterceptEnableVtlProtection : 1;
        HV_UINT64 InterceptVpStartup : 1;
        HV_UINT64 InterceptCpuidUnimplemented : 1;
        HV_UINT64 InterceptUnrecoverableException : 1;
        HV_UINT64 InterceptPage : 1;
        HV_UINT64 ReservedZ : 51;
    };
} HV_REGISTER_VSM_PARTITION_CONFIG, *PHV_REGISTER_VSM_PARTITION_CONFIG;

typedef union _HV_REGISTER_VSM_VP_SECURE_VTL_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MbecEnabled : 1;
        HV_UINT64 TlbLocked : 1;
        HV_UINT64 ReservedZ : 62;
    };
} HV_REGISTER_VSM_VP_SECURE_VTL_CONFIG, *PHV_REGISTER_VSM_VP_SECURE_VTL_CONFIG;

typedef union _HV_REGISTER_VSM_CODE_PAGE_OFFSETS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 VtlCallOffset : 12;
        HV_UINT64 VtlReturnOffset : 12;
        HV_UINT64 ReservedZ : 40;
    };
} HV_REGISTER_VSM_CODE_PAGE_OFFSETS, *PHV_REGISTER_VSM_CODE_PAGE_OFFSETS;

typedef union _HV_REGISTER_VSM_VINA
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Vector : 8;
        HV_UINT64 Enabled : 1;
        HV_UINT64 AutoReset : 1;
        HV_UINT64 AutoEoi : 1;
        HV_UINT64 ReservedP : 53;
    };
} HV_REGISTER_VSM_VINA, *PHV_REGISTER_VSM_VINA;

typedef union _HV_REGISTER_CR_INTERCEPT_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Cr0Write : 1; // 0x0000000000000001
        HV_UINT64 Cr4Write : 1; // 0x0000000000000002
        HV_UINT64 XCr0Write : 1; // 0x0000000000000004
        HV_UINT64 IA32MiscEnableRead : 1; // 0x0000000000000008
        HV_UINT64 IA32MiscEnableWrite : 1; // 0x0000000000000010
        HV_UINT64 MsrLstarRead : 1; // 0x0000000000000020
        HV_UINT64 MsrLstarWrite : 1; // 0x0000000000000040
        HV_UINT64 MsrStarRead : 1; // 0x0000000000000080
        HV_UINT64 MsrStarWrite : 1; // 0x0000000000000100
        HV_UINT64 MsrCstarRead : 1; // 0x0000000000000200
        HV_UINT64 MsrCstarWrite : 1; // 0x0000000000000400
        HV_UINT64 ApicBaseMsrRead : 1; // 0x0000000000000800
        HV_UINT64 ApicBaseMsrWrite : 1; // 0x0000000000001000
        HV_UINT64 MsrEferRead : 1; // 0x0000000000002000
        HV_UINT64 MsrEferWrite : 1; // 0x0000000000004000
        HV_UINT64 GdtrWrite : 1; // 0x0000000000008000
        HV_UINT64 IdtrWrite : 1; // 0x0000000000010000
        HV_UINT64 LdtrWrite : 1; // 0x0000000000020000
        HV_UINT64 TrWrite : 1; // 0x0000000000040000
        HV_UINT64 MsrSysenterCsWrite : 1; // 0x0000000000080000
        HV_UINT64 MsrSysenterEipWrite : 1; // 0x0000000000100000
        HV_UINT64 MsrSysenterEspWrite : 1; // 0x0000000000200000
        HV_UINT64 MsrSfmaskWrite : 1; // 0x0000000000400000
        HV_UINT64 MsrTscAuxWrite : 1; // 0x0000000000800000
        HV_UINT64 MsrSgxLaunchControlWrite : 1; // 0x0000000001000000
        HV_UINT64 RsvdZ : 39;
    };
} HV_REGISTER_CR_INTERCEPT_CONTROL, *PHV_REGISTER_CR_INTERCEPT_CONTROL;

// Input for targeting a specific VTL.
typedef union _HV_INPUT_VTL
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 TargetVtl : 4;
        HV_UINT8 UseTargetVtl : 1;
        HV_UINT8 ReservedZ : 3;
    };
} HV_INPUT_VTL, *PHV_INPUT_VTL;

typedef const HV_MAP_GPA_FLAGS* PCHV_MAP_GPA_FLAGS;

/* Nested Virtualization */

typedef struct _VM_PARTITION_ASSIST_PAGE
{
    HV_UINT32 TlbLockCount;
} VM_PARTITION_ASSIST_PAGE, *PVM_PARTITION_ASSIST_PAGE;

#define HV_VMX_SYNTHETIC_EXIT_REASON_TRAP_AFTER_FLUSH 0x10000031

typedef union _HV_GPA_PAGE_RANGE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 AdditionalPages : 11;
        HV_UINT64 LargePage : 1;
        union
        {
            HV_UINT64 BasePfn : 52;
            struct
            {
                HV_UINT64 PageSize : 1;
                HV_UINT64 Reserved1 : 8;
                HV_UINT64 BaseLargePfn : 43;
            };
        };
    };
} HV_GPA_PAGE_RANGE, *PHV_GPA_PAGE_RANGE;

// Below is the type definition for the enlightened VMCS. The corresponding
// Intel physical VMCS encoding for each field can be found in 16.11.4. Note
// that some enlightened VMCS fields are synthetic, and therefore will not have
// a corresponding physical VMCS encoding.
typedef struct _HV_VMX_ENLIGHTENED_VMCS
{
    HV_UINT32 VersionNumber;
    HV_UINT32 AbortIndicator;
    HV_UINT16 HostEsSelector;
    HV_UINT16 HostCsSelector;
    HV_UINT16 HostSsSelector;
    HV_UINT16 HostDsSelector;
    HV_UINT16 HostFsSelector;
    HV_UINT16 HostGsSelector;
    HV_UINT16 HostTrSelector;
    HV_UINT64 HostPat;
    HV_UINT64 HostEfer;
    HV_UINT64 HostCr0;
    HV_UINT64 HostCr3;
    HV_UINT64 HostCr4;
    HV_UINT64 HostSysenterEspMsr;
    HV_UINT64 HostSysenterEipMsr;
    HV_UINT64 HostRip;
    HV_UINT32 HostSysenterCsMsr;
    HV_UINT32 PinControls;
    HV_UINT32 ExitControls;
    HV_UINT32 SecondaryProcessorControls;
    HV_GPA IoBitmapA;
    HV_GPA IoBitmapB;
    HV_GPA MsrBitmap;
    HV_UINT16 GuestEsSelector;
    HV_UINT16 GuestCsSelector;
    HV_UINT16 GuestSsSelector;
    HV_UINT16 GuestDsSelector;
    HV_UINT16 GuestFsSelector;
    HV_UINT16 GuestGsSelector;
    HV_UINT16 GuestLdtrSelector;
    HV_UINT16 GuestTrSelector;
    HV_UINT32 GuestEsLimit;
    HV_UINT32 GuestCsLimit;
    HV_UINT32 GuestSsLimit;
    HV_UINT32 GuestDsLimit;
    HV_UINT32 GuestFsLimit;
    HV_UINT32 GuestGsLimit;
    HV_UINT32 GuestLdtrLimit;
    HV_UINT32 GuestTrLimit;
    HV_UINT32 GuestGdtrLimit;
    HV_UINT32 GuestIdtrLimit;
    HV_UINT32 GuestEsAttributes;
    HV_UINT32 GuestCsAttributes;
    HV_UINT32 GuestSsAttributes;
    HV_UINT32 GuestDsAttributes;
    HV_UINT32 GuestFsAttributes;
    HV_UINT32 GuestGsAttributes;
    HV_UINT32 GuestLdtrAttributes;
    HV_UINT32 GuestTrAttributes;
    HV_UINT64 GuestEsBase;
    HV_UINT64 GuestCsBase;
    HV_UINT64 GuestSsBase;
    HV_UINT64 GuestDsBase;
    HV_UINT64 GuestFsBase;
    HV_UINT64 GuestGsBase;
    HV_UINT64 GuestLdtrBase;
    HV_UINT64 GuestTrBase;
    HV_UINT64 GuestGdtrBase;
    HV_UINT64 GuestIdtrBase;
    HV_UINT64 Rsvd1[3];
    HV_GPA ExitMsrStoreAddress;
    HV_GPA ExitMsrLoadAddress;
    HV_GPA EntryMsrLoadAddress;
    HV_UINT64 Cr3Target0;
    HV_UINT64 Cr3Target1;
    HV_UINT64 Cr3Target2;
    HV_UINT64 Cr3Target3;
    HV_UINT32 PfecMask;
    HV_UINT32 PfecMatch;
    HV_UINT32 Cr3TargetCount;
    HV_UINT32 ExitMsrStoreCount;
    HV_UINT32 ExitMsrLoadCount;
    HV_UINT32 EntryMsrLoadCount;
    HV_UINT64 TscOffset;
    HV_GPA VirtualApicPage;
    HV_GPA GuestWorkingVmcsPtr;
    HV_UINT64 GuestIa32DebugCtl;
    HV_UINT64 GuestPat;
    HV_UINT64 GuestEfer;
    HV_UINT64 GuestPdpte0;
    HV_UINT64 GuestPdpte1;
    HV_UINT64 GuestPdpte2;
    HV_UINT64 GuestPdpte3;
    HV_UINT64 GuestPendingDebugExceptions;
    HV_UINT64 GuestSysenterEspMsr;
    HV_UINT64 GuestSysenterEipMsr;
    HV_UINT32 GuestSleepState;
    HV_UINT32 GuestSysenterCsMsr;
    HV_UINT64 Cr0GuestHostMask;
    HV_UINT64 Cr4GuestHostMask;
    HV_UINT64 Cr0ReadShadow;
    HV_UINT64 Cr4ReadShadow;
    HV_UINT64 GuestCr0;
    HV_UINT64 GuestCr3;
    HV_UINT64 GuestCr4;
    HV_UINT64 GuestDr7;
    HV_UINT64 HostFsBase;
    HV_UINT64 HostGsBase;
    HV_UINT64 HostTrBase;
    HV_UINT64 HostGdtrBase;
    HV_UINT64 HostIdtrBase;
    HV_UINT64 HostRsp;
    HV_UINT64 EptRoot;
    HV_UINT16 Vpid;
    HV_UINT16 Rsvd2[3];
    HV_UINT64 Rsvd3[5];
    HV_UINT64 ExitEptFaultGpa;
    HV_UINT32 ExitInstructionError;
    HV_UINT32 ExitReason;
    HV_UINT32 ExitInterruptionInfo;
    HV_UINT32 ExitExceptionErrorCode;
    HV_UINT32 ExitIdtVectoringInfo;
    HV_UINT32 ExitIdtVectoringErrorCode;
    HV_UINT32 ExitInstructionLength;
    HV_UINT32 ExitInstructionInfo;
    HV_UINT64 ExitQualification;
    HV_UINT64 ExitIoInstructionEcx;
    HV_UINT64 ExitIoInstructionEsi;
    HV_UINT64 ExitIoInstructionEdi;
    HV_UINT64 ExitIoInstructionEip;
    HV_UINT64 GuestLinearAddress;
    HV_UINT64 GuestRsp;
    HV_UINT64 GuestRflags;
    HV_UINT32 GuestInterruptibility;
    HV_UINT32 ProcessorControls;
    HV_UINT32 ExceptionBitmap;
    HV_UINT32 EntryControls;
    HV_UINT32 EntryInterruptInfo;
    HV_UINT32 EntryExceptionErrorCode;
    HV_UINT32 EntryInstructionLength;
    HV_UINT32 TprThreshold;
    HV_UINT64 GuestRip;
    HV_UINT32 CleanFields;
    HV_UINT32 Rsvd4;
    HV_UINT32 SyntheticControls;
    union
    {
        HV_UINT32 AsUINT32;

        struct
        {
            HV_UINT32 NestedFlushVirtualHypercall : 1;
            HV_UINT32 MsrBitmap : 1;
            HV_UINT32 Reserved : 30;
        };
    } EnlightenmentsControl;
    HV_UINT32 VpId;
    HV_UINT64 VmId;
    HV_UINT64 PartitionAssistPage;
    HV_UINT64 Rsvd5[4];
    HV_UINT64 GuestBndcfgs;
    HV_UINT64 Rsvd6[7];
    HV_UINT64 XssExitingBitmap;
    HV_UINT64 EnclsExitingBitmap;
    HV_UINT64 Rsvd7[6];
} HV_VMX_ENLIGHTENED_VMCS, *PHV_VMX_ENLIGHTENED_VMCS;

#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_NONE (0)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_IO_BITMAP (1 << 0)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_MSR_BITMAP (1 << 1)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_GRP2 (1 << 2)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_GRP1 (1 << 3)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_PROC (1 << 4)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_EVENT (1 << 5)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_ENTRY (1 << 6)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_EXCPN (1 << 7)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CRDR (1 << 8)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_XLAT (1 << 9)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_BASIC (1 << 10)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1 (1 << 11)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP2 (1 << 12)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_HOST_POINTER (1 << 13)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_HOST_GRP1 (1 << 14)
#define HV_VMX_ENLIGHTENED_CLEAN_FIELD_ENLIGHTENMENTSCONTROL (1 << 15)

// *****************************************************************************
// Hyper-V headers from Microsoft mshv Linux kernel module Definitions
//

// Message format for notifications delivered via intercept message
// (as_intercept=1)
typedef struct _HV_NOTIFICATION_MESSAGE_PAYLOAD
{
    HV_UINT32 SintIndex;
} HV_NOTIFICATION_MESSAGE_PAYLOAD, *PHV_NOTIFICATION_MESSAGE_PAYLOAD;

typedef struct _HV_X64_PROXY_INTERRUPT_MESSAGE_PAYLOAD
{
    HV_UINT8 InterruptVtl;
    HV_UINT8 AssertMultiple;
    HV_UINT8 Reserved[2];
    union
    {
        HV_UINT32 AssertedVector;
        HV_UINT32 AssertedIrr[8];
    };
} HV_X64_PROXY_INTERRUPT_MESSAGE_PAYLOAD, *PHV_X64_PROXY_INTERRUPT_MESSAGE_PAYLOAD;

typedef enum _HV_UNIMPLEMENTED_MSR_ACTION
{
    HvUnimplementedMsrActionFault = 0,
    HvUnimplementedMsrActionIgnoreWriteReadZero = 1,
    HvUnimplementedMsrActionCount = 2
} HV_UNIMPLEMENTED_MSR_ACTION, *PHV_UNIMPLEMENTED_MSR_ACTION;

// Each generic set contains 64 elements

#define HV_GENERIC_SET_SHIFT (6)
#define HV_GENERIC_SET_MASK (63)

// NOTE: following two #defines are not defined in Hyper-V code
// The maximum number of sparse vCPU banks which can be encoded by HV_VP_SET
#define HV_MAX_SPARSE_VCPU_BANKS (64)
// The number of vCPUs in one sparse bank
#define HV_VCPUS_PER_SPARSE_BANK (64)

typedef enum _HV_SCHEDULER_TYPE
{
    HvSchedulerTypeLp = 1, // Classic scheduler w/o SMT
    HvSchedulerTypeLpSmt = 2, // Classic scheduler w/ SMT
    HvSchedulerTypeCoreSmt = 3, // Core scheduler
    HvSchedulerTypeRoot = 4, // Root / integrated scheduler
    HvSchedulerTypeMax
} HV_SCHEDULER_TYPE, *PHV_SCHEDULER_TYPE;

typedef enum _HV_SYSTEM_PROPERTY
{
    HvPerfCounterProperty = 1,
    HvLegacyPowerPolicySettingProperty = 2,
    HvSleepStateProperty = 3,
    HvMachineCheckProperty = 4,
    HvIommuInitStatusProperty = 5,
    HvHpetConfigProperty = 6,
    HvHpetInterruptProperty = 7,
    HvHpetEnabledProperty = 8,
    HvHypervisorLaunchStatsProperty = 9,
    HvHypervisorDebugProperty = 10,
    HvRootSvmCapabilitiesProperty = 11,
    HvRootNumaCostPagesProperty = 12,
    HvHostPageTableRootProperty = 13,
    HvTscSyncStatusProperty = 14,
    HvSchedulerTypeProperty = 15,
    HvPlatformVirtualizationSupportProperty = 16,
} HV_SYSTEM_PROPERTY, *PHV_SYSTEM_PROPERTY;

typedef union _HV_GPA_PAGE_ACCESS_STATE_FLAGS
{
    struct
    {
        HV_UINT64 ClearAccessed : 1;
        HV_UINT64 SetAccess : 1;
        HV_UINT64 ClearDirty : 1;
        HV_UINT64 SetDirty : 1;
        HV_UINT64 Reserved : 60;
    };
    HV_UINT64 AsUINT64;
} HV_GPA_PAGE_ACCESS_STATE_FLAGS, *PHV_GPA_PAGE_ACCESS_STATE_FLAGS;

typedef union _HV_GPA_PAGE_ACCESS_STATE
{
    struct
    {
        HV_UINT8 Accessed : 1;
        HV_UINT8 Dirty : 1;
        HV_UINT8 Reserved : 6;
    };
    HV_UINT8 AsUINT8;
} HV_GPA_PAGE_ACCESS_STATE, *PHV_GPA_PAGE_ACCESS_STATE;

// Bits for dirty mask of HV_VP_REGISTER_PAGE

#define HV_X64_REGISTER_CLASS_GENERAL 0
#define HV_X64_REGISTER_CLASS_IP 1
#define HV_X64_REGISTER_CLASS_XMM 2
#define HV_X64_REGISTER_CLASS_SEGMENT 3
#define HV_X64_REGISTER_CLASS_FLAGS 4

#define HV_VP_REGISTER_PAGE_VERSION_1 1u

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_VP_REGISTER_PAGE
{
    HV_UINT16 Version;
    HV_UINT8 IsValid;
    HV_UINT8 Rsvdz;
    HV_UINT32 Dirty;
    union
    {
        struct
        {
            // General purpose registers (HV_X64_REGISTER_CLASS_GENERAL)
            union
            {
                struct
                {
                    HV_UINT64 Rax;
                    HV_UINT64 Rcx;
                    HV_UINT64 Rdx;
                    HV_UINT64 Rbx;
                    HV_UINT64 Rsp;
                    HV_UINT64 Rbp;
                    HV_UINT64 Rsi;
                    HV_UINT64 Rdi;
                    HV_UINT64 R8;
                    HV_UINT64 R9;
                    HV_UINT64 R10;
                    HV_UINT64 R11;
                    HV_UINT64 R12;
                    HV_UINT64 R13;
                    HV_UINT64 R14;
                    HV_UINT64 R15;
                };
                HV_UINT64 GpRegisters[16];
            };
            // Instruction pointer (HV_X64_REGISTER_CLASS_IP)
            HV_UINT64 Rip;
            // Flags (HV_X64_REGISTER_CLASS_FLAGS)
            HV_UINT64 Rflags;
        };
        HV_UINT64 Registers[18];
    };
    // Volatile XMM registers (HV_X64_REGISTER_CLASS_XMM)
    union
    {
        struct
        {
            HV_UINT128 Xmm0;
            HV_UINT128 Xmm1;
            HV_UINT128 Xmm2;
            HV_UINT128 Xmm3;
            HV_UINT128 Xmm4;
            HV_UINT128 Xmm5;
        };
        HV_UINT128 XmmRegisters[6];
    };
    // Segment registers (HV_X64_REGISTER_CLASS_SEGMENT)
    union
    {
        struct
        {
            HV_X64_SEGMENT_REGISTER Es;
            HV_X64_SEGMENT_REGISTER Cs;
            HV_X64_SEGMENT_REGISTER Ss;
            HV_X64_SEGMENT_REGISTER Ds;
            HV_X64_SEGMENT_REGISTER Fs;
            HV_X64_SEGMENT_REGISTER Gs;
        };
        HV_X64_SEGMENT_REGISTER SegmentRegisters[6];
    };
    // Misc. control registers (cannot be set via this interface)
    HV_UINT64 Cr0;
    HV_UINT64 Cr3;
    HV_UINT64 Cr4;
    HV_UINT64 Cr8;
    HV_UINT64 Efer;
    HV_UINT64 Dr7;
    HV_X64_PENDING_INTERRUPTION_REGISTER PendingInterruption;
    HV_X64_INTERRUPT_STATE_REGISTER InterruptState;
    HV_UINT64 InstructionEmulationHints;
} HV_VP_REGISTER_PAGE, *PHV_VP_REGISTER_PAGE;
#endif

typedef struct _HV_PARTITION_CREATION_PROPERTIES
{
    HV_PARTITION_PROCESSOR_FEATURES DisabledProcessorFeatures;
    HV_PARTITION_PROCESSOR_XSAVE_FEATURES DisabledProcessorXsaveFeatures;
} HV_PARTITION_CREATION_PROPERTIES, *PHV_PARTITION_CREATION_PROPERTIES;

// Definition of the partition isolation state. Used for
// HV_PARTITION_PROPERTY_ISOLATION_STATE.
// The isolation states (HV_PARTITION_ISOLATION_STATE) are sub-states of
// ObPartitionActive that apply to VBS and hardware isolated partitions.
// For VBS isolation, the trusted host VTL 1 component uses the isolation
// state to establish a binding between a hypervisor partition and its own
// partition context, and to enforce certain invariants.
// Hardware-isolated partitions (including partitions that simulate hardware
// isolation) also use isolation states to track the progression of the
// partition security state through the architectural state machine.
// Insecure states indicate that there is no architectural state associated
// with the partition, and Secure indicates that the partition has secure
// architectural state.
// ObPartitionRestoring is treated differently for isolated partitions.
// Only the trusted host component is allowed to restore partition state,
// and ObPartitionRestoring can only transition directly to/from secure.
// ..................................................................
// .         UNINITIALIZED     FINALIZED                            .
// .               |           ^       ^                            .
// .    Initialize |          /         \                           .
// .               |         /           \                          .
// . --------------|--------/--- ACTIVE --\------------------------ .
// . |             |       /               \                      | .
// . |             |      / Finalize        \ Finalize            | .
// . |             v     /                   \                    | .
// . |       INSECURE-CLEAN <---------------- INSECURE-DIRTY      | .
// . |                   \        Scrub      ^                    | .
// . |                    \                 /                     | .
// . |                     \               /                      | .
// . |               Secure \             / Unsecure              | .
// . |                       \           /                        | .
// . |                        \         /                         | .
// . |                         v       /                          | .
// . |                           SECURE                           | .
// . |                             ^                              | .
// . |_____________________________|______________________________| .
// .                               |                                .
// .                               v                                .
// .                           RESTORING                            .
// ..................................................................
typedef enum _HV_PARTITION_ISOLATION_STATE
{
    // Initial and final state for all non-isolated partitions.
    HvPartitionIsolationInvalid = 0,
    // An "Insecure" partition is not being used by the trusted host component.
    // In this state, VPs can be created and deleted. VPs cannot be started, and
    // VP registers cannot be modified.
    // Initial state of an isolated partition as result of Initialize or Scrub
    // hypercalls. Guest-visible partition and VP state is considered "clean",
    // in the sense that a call to ObScrubPartition should not result in any
    // changes. Also, there are no accepted or confidential pages assigned to
    // the partition. InsecureRundown is enabled.
    HvPartitionIsolationInsecureClean = 1,
    // Guest-visible partition and VP state is not "clean". Hence it must be
    // scrubbed first. One of 2 explicit states the trusted host component can
    // request. It cannot transition the state to Secure. In this state,
    // - IsolationControl is clear.
    // - Secure rundowns are completely disabled.
    // - No assigned pages exist.
    HvPartitionIsolationInsecureDirty = 2,
    // The partition is being used by the trusted host component (and is
    // typically bound to a single partition context in that component).
    // One of 2 explicit states the trusted host component can request. In this
    // state,
    // - VPs cannot be created or deleted.
    // - Partition cannot be finalized, scrubbed.
    // - Insecure rundowns are completely disabled.
    HvPartitionIsolationSecure = 3,
    // Represents a failed attempt to transition to Secure state. Partition in
    // this state cannot be finalized, scrubbed since one or more pages may be
    // assigned.
    HvPartitionIsolationSecureDirty = 4,
    // An internal state indicating that a partition is in the process of
    // transitioning from Secure to InsecureDirty.
    HvPartitionIsolationSecureTerminating = 5,
} HV_PARTITION_ISOLATION_STATE, *PHV_PARTITION_ISOLATION_STATE;

#define HV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES_BANKS 1

typedef union _HV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES
{
    HV_UINT64 AsUINT64[HV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES_BANKS];
    struct
    {
        // Report a hypervisor is present. CPUID leaves 0x40000000 and
        // 0x40000001 are supported.
        HV_UINT64 HypervisorPresent : 1;

        // Features associated with HV#1:

        // Report support for Hv1 (CPUID leaves 0x40000000 - 0x40000006).
        HV_UINT64 Hv1 : 1;
        // Access to HV_X64_MSR_VP_RUNTIME.
        // Corresponds to AccessVpRunTimeReg privilege.
        HV_UINT64 AccessVpRunTimeReg : 1;
        // Access to HV_X64_MSR_TIME_REF_COUNT.
        // Corresponds to AccessPartitionReferenceCounter privilege.
        HV_UINT64 AccessPartitionReferenceCounter : 1;
        // Access to SINT-related registers (HV_X64_MSR_SCONTROL through
        // HV_X64_MSR_EOM and HV_X64_MSR_SINT0 through HV_X64_MSR_SINT15).
        // Corresponds to AccessSynicRegs privilege.
        HV_UINT64 AccessSynicRegs : 1;
        // Access to synthetic timers and associated MSRs
        // (HV_X64_MSR_STIMER0_CONFIG through HV_X64_MSR_STIMER3_COUNT).
        // Corresponds to AccessSyntheticTimerRegs privilege.
        HV_UINT64 AccessSyntheticTimerRegs : 1;
        // Access to APIC MSRs (HV_X64_MSR_EOI, HV_X64_MSR_ICR and
        // HV_X64_MSR_TPR) as well as the VP assist page.
        // Corresponds to AccessIntrCtrlRegs privilege.
        HV_UINT64 AccessIntrCtrlRegs : 1;
        // Access to registers associated with hypercalls
        // (HV_X64_MSR_GUEST_OS_ID and HV_X64_MSR_HYPERCALL).
        // Corresponds to AccessHypercallMsrs privilege.
        HV_UINT64 AccessHypercallMsrs : 1;
        // VP index can be queried. corresponds to AccessVpIndex privilege.
        HV_UINT64 AccessVpIndex : 1;
        // Access to the reference TSC. Corresponds to
        // AccessPartitionReferenceTsc privilege.
        HV_UINT64 AccessPartitionReferenceTsc : 1;
        // Partition has access to the guest idle reg. Corresponds to
        // AccessGuestIdleReg privilege.
        HV_UINT64 AccessGuestIdleReg : 1;
        // Partition has access to frequency regs. corresponds to
        // AccessFrequencyRegs privilege.
        HV_UINT64 AccessFrequencyRegs : 1;
        // Reserved for AccessReenlightenmentControls.
        HV_UINT64 ReservedZ12 : 1;
        // Reserved for AccessRootSchedulerReg.
        HV_UINT64 ReservedZ13 : 1;
        // Reserved for AccessTscInvariantControls.
        HV_UINT64 ReservedZ14 : 1;
        // Extended GVA ranges for HvCallFlushVirtualAddressList hypercall.
        // Corresponds to privilege.
        HV_UINT64 EnableExtendedGvaRangesForFlushVirtualAddressList : 1;
        // Reserved for AccessVsm.
        HV_UINT64 ReservedZ16 : 1;
        // Reserved for AccessVpRegisters.
        HV_UINT64 ReservedZ17 : 1;
        // Use fast hypercall output. Corresponds to privilege.
        HV_UINT64 FastHypercallOutput : 1;
        // Reserved for EnableExtendedHypercalls.
        HV_UINT64 ReservedZ19 : 1;
        // HvStartVirtualProcessor can be used to start virtual processors.
        // Corresponds to privilege.
        HV_UINT64 StartVirtualProcessor : 1;
        // Reserved for Isolation.
        HV_UINT64 ReservedZ21 : 1;
        // Synthetic timers in direct mode.
        HV_UINT64 DirectSyntheticTimers : 1;
        // Reserved for synthetic time unhalted timer
        HV_UINT64 ReservedZ23 : 1;
        // Use extended processor masks.
        HV_UINT64 ExtendedProcessorMasks : 1;
        // HvCallFlushVirtualAddressSpace / HvCallFlushVirtualAddressList are
        // supported.
        HV_UINT64 TbFlushHypercalls : 1;
        // HvCallSendSyntheticClusterIpi is supported.
        HV_UINT64 SyntheticClusterIpi : 1;
        // HvCallNotifyLongSpinWait is supported.
        HV_UINT64 NotifyLongSpinWait : 1;
        // HvCallQueryNumaDistance is supported.
        HV_UINT64 QueryNumaDistance : 1;
        // HvCallSignalEvent is supported. Corresponds to privilege.
        HV_UINT64 SignalEvents : 1;
        // HvCallRetargetDeviceInterrupt is supported.
        HV_UINT64 RetargetDeviceInterrupt : 1;
        // HvCallRestorePartitionTime is supported.
        HV_UINT64 RestoreTime : 1;
        // EnlightenedVmcs nested enlightenment is supported.
        HV_UINT64 EnlightenedVmcs : 1;
        HV_UINT64 Reserved : 31;
    };
} HV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES, *PHV_PARTITION_SYNTHETIC_PROCESSOR_FEATURES;

#define HV_MAKE_COMPATIBILITY_VERSION(Major, Minor) \
	((HV_UINT32)((Major) << 8 | (Minor)))

#define HV_COMPATIBILITY_21_H2 HV_MAKE_COMPATIBILITY_VERSION(0x6, 0x9)

typedef union _HV_PARTITION_ISOLATION_PROPERTIES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 IsolationType : 5;
        HV_UINT64 IsolationHostType : 2;
        HV_UINT64 RsvdZ : 5;
        HV_UINT64 SharedGpaBoundaryPageNumber : 52;
    };
} HV_PARTITION_ISOLATION_PROPERTIES, *PHV_PARTITION_ISOLATION_PROPERTIES;

// Various isolation types supported by MSHV.

#define HV_PARTITION_ISOLATION_TYPE_NONE 0
#define HV_PARTITION_ISOLATION_TYPE_SNP 2
#define HV_PARTITION_ISOLATION_TYPE_TDX 3

// Various host isolation types supported by MSHV.

#define HV_PARTITION_ISOLATION_HOST_TYPE_NONE 0x0
#define HV_PARTITION_ISOLATION_HOST_TYPE_HARDWARE 0x1
#define HV_PARTITION_ISOLATION_HOST_TYPE_RESERVED 0x2

// Note: Exo partition is enabled by default
#define HV_PARTITION_CREATION_FLAG_EXO_PARTITION (1 << 8)
#define HV_PARTITION_CREATION_FLAG_LAPIC_ENABLED (1 << 13)
#define HV_PARTITION_CREATION_FLAG_INTERCEPT_MESSAGE_PAGE_ENABLED (1 << 19)
#define HV_PARTITION_CREATION_FLAG_X2APIC_CAPABLE (1 << 22)

typedef enum _HV_VP_STATE_PAGE_TYPE
{
    HvVpStatePageRegisters = 0,
    HvVpStatePageInterceptMessage = 1,
    HvVpStatePageCount
} HV_VP_STATE_PAGE_TYPE, *PHV_VP_STATE_PAGE_TYPE;

typedef struct _HV_CPUID_LEAF_INFO
{
    HV_UINT32 Eax;
    HV_UINT32 Ecx;
    HV_UINT64 Xfem;
    HV_UINT64 Xss;
} HV_CPUID_LEAF_INFO, *PHV_CPUID_LEAF_INFO;

typedef union _HV_GET_VP_CPUID_VALUES_FLAGS
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 UseVpXfemXss : 1;
        HV_UINT32 ApplyRegisteredValues : 1;
        HV_UINT32 Reserved : 30;
    };
} HV_GET_VP_CPUID_VALUES_FLAGS, *PHV_GET_VP_CPUID_VALUES_FLAGS;

typedef struct _HV_OPAQUE_INTERCEPT_MESSAGE
{
    HV_VP_INDEX VpIndex;
} HV_OPAQUE_INTERCEPT_MESSAGE, *PHV_OPAQUE_INTERCEPT_MESSAGE;

#define HV_SYNIC_EVENT_RING_MESSAGE_COUNT 63

typedef struct _HV_SYNIC_EVENT_RING
{
    HV_UINT8 SignalMasked;
    HV_UINT8 RingFull;
    HV_UINT16 ReservedZ;
    HV_UINT32 Data[HV_SYNIC_EVENT_RING_MESSAGE_COUNT];
} HV_SYNIC_EVENT_RING, *PHV_SYNIC_EVENT_RING;

typedef struct _HV_SYNIC_EVENT_RING_PAGE
{
    HV_SYNIC_EVENT_RING SintEventRing[HV_SYNIC_SINT_COUNT];
} HV_SYNIC_EVENT_RING_PAGE, *PHV_SYNIC_EVENT_RING_PAGE;

typedef union _HV_SYNIC_SIRBP
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 SirbpEnabled : 1;
        HV_UINT64 Preserved : 11;
        HV_UINT64 BaseSirbpGpa : 52;
    };
} HV_SYNIC_SIRBP, *PHV_SYNIC_SIRBP;

typedef struct _HV_LOCAL_INTERRUPT_CONTROLLER_STATE
{
    // HV_X64_INTERRUPT_CONTROLLER_STATE

    HV_UINT32 ApicId;
    HV_UINT32 ApicVersion;
    HV_UINT32 ApicLdr;
    HV_UINT32 ApicDfr;
    HV_UINT32 ApicSpurious;
    HV_UINT32 ApicIsr[8];
    HV_UINT32 ApicTmr[8];
    HV_UINT32 ApicIrr[8];
    HV_UINT32 ApicEsr;
    HV_UINT32 ApicIcrHigh;
    HV_UINT32 ApicIcrLow;
    HV_UINT32 ApicLvtTimer;
    HV_UINT32 ApicLvtThermal;
    HV_UINT32 ApicLvtPerfmon;
    HV_UINT32 ApicLvtLint0;
    HV_UINT32 ApicLvtLint1;
    HV_UINT32 ApicLvtError;
    HV_UINT32 ApicLvtCmci;
    HV_UINT32 ApicErrorStatus;
    HV_UINT32 ApicInitialCount;
    HV_UINT32 ApicCounterValue;
    HV_UINT32 ApicDivideConfiguration;
    HV_UINT32 ApicRemoteRead;
} HV_LOCAL_INTERRUPT_CONTROLLER_STATE, *PHV_LOCAL_INTERRUPT_CONTROLLER_STATE;

typedef struct _HV_STIMER_STATE
{
    struct
    {
        // Indicates if there is an undelivered timer expiry message.
        HV_UINT32 UndeliveredMsgPending : 1;
        HV_UINT32 Reserved : 31;
    } Flags;
    HV_UINT32 Resvd;
    // Timer configuration and count.
    HV_UINT64 Config;
    HV_UINT64 Count;
    // Timer adjustment.
    HV_UINT64 Adjustment;
    // Expiration time of the undelivered message.
    HV_UINT64 UndeliveredExpTime;
} HV_STIMER_STATE, *PHV_STIMER_STATE;

typedef struct _HV_SYNTHETIC_TIMERS_STATE
{
    HV_STIMER_STATE Timers[HV_SYNIC_STIMER_COUNT];
    // Reserved space for time unhalted timer.
    HV_UINT64 Reserved[5];
} HV_SYNTHETIC_TIMERS_STATE, *PHV_SYNTHETIC_TIMERS_STATE;

#define HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS 6

#if defined(_M_AMD64) || defined(_M_IX86)

typedef struct _HV_X64_HYPERCALL_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT64 Rax;
    HV_UINT64 Rbx;
    HV_UINT64 Rcx;
    HV_UINT64 Rdx;
    HV_UINT64 R8;
    HV_UINT64 Rsi;
    HV_UINT64 Rdi;
    HV_UINT128 Xmmregisters[HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS];
    struct
    {
        HV_UINT32 Isolated : 1;
        HV_UINT32 Reserved : 31;
    };
} HV_X64_HYPERCALL_INTERCEPT_MESSAGE, *PHV_X64_HYPERCALL_INTERCEPT_MESSAGE;

typedef union _HV_X64_REGISTER_ACCESS_INFO
{
    HV_REGISTER_VALUE SourceValue;
    HV_UINT32 DestinationRegister;
    HV_UINT64 SourceAddress;
    HV_UINT64 DestinationAddress;
} HV_X64_REGISTER_ACCESS_INFO, *PHV_X64_REGISTER_ACCESS_INFO;

typedef struct _HV_X64_REGISTER_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    struct
    {
        HV_UINT8 IsMemoryOp : 1;
        HV_UINT8 Reserved : 7;
    };
    HV_UINT8 Reserved1[3];
    HV_UINT32 RegisterName;
    HV_X64_REGISTER_ACCESS_INFO AccessInfo;
} HV_X64_REGISTER_INTERCEPT_MESSAGE, *PHV_X64_REGISTER_INTERCEPT_MESSAGE;

typedef struct _HV_X64_HALT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
} HV_X64_HALT_MESSAGE, *PHV_X64_HALT_MESSAGE;

#define HV_X64_PENDING_INTERRUPT 0
#define HV_X64_PENDING_NMI 2
#define HV_X64_PENDING_EXCEPTION 3

typedef struct _HV_X64_INTERRUPTION_DELIVERABLE_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT32 DeliverableType; // pending interruption type
    HV_UINT32 Rsvd;
} HV_X64_INTERRUPTION_DELIVERABLE_MESSAGE, *PHV_X64_INTERRUPTION_DELIVERABLE_MESSAGE;

typedef struct _HV_X64_SINT_DELIVERABLE_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT16 DeliverableSints;
    HV_UINT8 Rsvd[6];
} HV_X64_SINT_DELIVERABLE_MESSAGE, *PHV_X64_SINT_DELIVERABLE_MESSAGE;

typedef struct _HV_X64_SIPI_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT32 TargetVpIndex;
    HV_UINT32 InterruptVector;
} HV_X64_SIPI_INTERCEPT_MESSAGE, *PHV_X64_SIPI_INTERCEPT_MESSAGE;

typedef struct _HV_REGISTER_X64_CPUID_RESULT_PARAMETERS
{
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 Ecx;
        HV_UINT8 SubleafSpecific;
        HV_UINT8 AlwaysOverride;
        HV_UINT16 Padding;
    } Input;
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 EaxMask;
        HV_UINT32 Ebx;
        HV_UINT32 EbxMask;
        HV_UINT32 Ecx;
        HV_UINT32 EcxMask;
        HV_UINT32 Edx;
        HV_UINT32 EdxMask;
    } Result;
} HV_REGISTER_X64_CPUID_RESULT_PARAMETERS, *PHV_REGISTER_X64_CPUID_RESULT_PARAMETERS;

typedef struct _HV_REGISTER_X64_MSR_RESULT_PARAMETERS
{
    HV_UINT32 MsrIndex;
    HV_UINT32 AccessType;
    HV_UNIMPLEMENTED_MSR_ACTION Action;
} HV_REGISTER_X64_MSR_RESULT_PARAMETERS, *PHV_REGISTER_X64_MSR_RESULT_PARAMETERS;

typedef union _HV_REGISTER_INTERCEPT_RESULT_PARAMETERS
{
    HV_REGISTER_X64_CPUID_RESULT_PARAMETERS Cpuid;
    HV_REGISTER_X64_MSR_RESULT_PARAMETERS Msr;
} HV_REGISTER_INTERCEPT_RESULT_PARAMETERS, *PHV_REGISTER_INTERCEPT_RESULT_PARAMETERS;

#endif

typedef struct _HV_ASYNC_COMPLETION_MESSAGE_PAYLOAD
{
    HV_PARTITION_ID PartitionId;
    HV_UINT32 Status;
    HV_UINT32 CompletionCount;
    HV_UINT64 SubStatus;
} HV_ASYNC_COMPLETION_MESSAGE_PAYLOAD, *PHV_ASYNC_COMPLETION_MESSAGE_PAYLOAD;

typedef struct _HV_GUEST_MAPPING_FLUSH_LIST
{
    // HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST

    HV_UINT64 AddressSpace;
    HV_UINT64 Flags;
    HV_GPA_PAGE_RANGE GpaList[];
} HV_GUEST_MAPPING_FLUSH_LIST, *PHV_GUEST_MAPPING_FLUSH_LIST;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_VP_STATE_DATA_XSAVE
{
    HV_UINT64 Flags;
    HV_X64_XSAVE_XFEM_REGISTER States;
} HV_VP_STATE_DATA_XSAVE, *PHV_VP_STATE_DATA_XSAVE;

// For getting and setting VP state, there are two options based on the state
// type:
//   1.) Data that is accessed by PFNs in the input hypercall page. This is used
//       for state which may not fit into the hypercall pages.
//   2.) Data that is accessed directly in the input\output hypercall pages.
//       This is used for state that will always fit into the hypercall pages.
// In the future this could be dynamic based on the size if needed.
// Note these hypercalls have an 8-byte aligned variable header size as per the
// tlfs

#define HV_GET_SET_VP_STATE_TYPE_PFN (1 << 31)

typedef enum _HV_GET_SET_VP_STATE_TYPE
{
    HvGetSetVpStateLocalInterruptControllerState = 0 | HV_GET_SET_VP_STATE_TYPE_PFN,
    HvGetSetVpStateXsave = 1 | HV_GET_SET_VP_STATE_TYPE_PFN,
    // Synthetic message page
    HvGetSetVpStateSimPage = 2 | HV_GET_SET_VP_STATE_TYPE_PFN,
    // Synthetic interrupt event flags page.
    HvGetSetVpStateSiefPage = 3 | HV_GET_SET_VP_STATE_TYPE_PFN,
    // Synthetic timers.
    HvGetSetVpStateSyntheticTimers = 4
} HV_GET_SET_VP_STATE_TYPE, *PHV_GET_SET_VP_STATE_TYPE;

typedef struct _HV_VP_STATE_DATA
{
    HV_UINT32 Type;
    HV_UINT32 Rsvd;
    HV_VP_STATE_DATA_XSAVE Xsave;
} HV_VP_STATE_DATA, *PHV_VP_STATE_DATA;

#endif

// Dispatch state for the VP communicated by the hypervisor to the
// VP-dispatching thread in the root on return from HVCALL_DISPATCH_VP.
typedef enum _HV_VP_DISPATCH_STATE
{
    HvVpDispatchStateInvalid = 0,
    HvVpDispatchStateBlocked = 1,
    HvVpDispatchStateReady = 2
} HV_VP_DISPATCH_STATE, *PHV_VP_DISPATCH_STATE;

// Dispatch event that caused the current dispatch state on return from
// HVCALL_DISPATCH_VP.
typedef enum _HV_VP_DISPATCH_EVENT
{
    HvVpDispatchEventInvalid = 0x00000000,
    HvVpDispatchEventSuspend = 0x00000001,
    HvVpDispatchEventIntercept = 0x00000002
} HV_VP_DISPATCH_EVENT, *PHV_VP_DISPATCH_EVENT;

#define HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION 1024
// The maximum array size of HV_GENERIC_SET (vp_set) buffer
#define HV_GENERIC_SET_QWORD_COUNT(max) (((((max) - 1) >> 6) + 1) + 2)

typedef struct _HV_VP_SIGNAL_BITSET_SCHEDULER_MESSAGE
{
    HV_PARTITION_ID PartitionId;
    HV_UINT32 OverflowCount;
    HV_UINT16 VpCount;
    HV_UINT16 Reserved;
#define BITSET_BUFFER_SIZE \
	HV_GENERIC_SET_QWORD_COUNT(HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION)
    union
    {
        HV_VP_SET Bitset;
        HV_UINT64 BitsetBuffer[BITSET_BUFFER_SIZE];
    } VpBitset;
#undef BITSET_BUFFER_SIZE
} HV_VP_SIGNAL_BITSET_SCHEDULER_MESSAGE, *PHV_VP_SIGNAL_BITSET_SCHEDULER_MESSAGE;

HV_STATIC_ASSERT(sizeof(HV_VP_SIGNAL_BITSET_SCHEDULER_MESSAGE) <=
    (sizeof(HV_MESSAGE) - sizeof(HV_MESSAGE_HEADER)));

#define HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT \
	(((sizeof(HV_MESSAGE) - sizeof(HV_MESSAGE_HEADER)) / \
	 (sizeof(HV_UINT64 /* partition id */) + sizeof(HV_UINT32 /* vp index */))) - 1)

typedef struct _HV_VP_SIGNAL_PAIR_SCHEDULER_MESSAGE
{
    HV_UINT32 OverflowCount;
    HV_UINT8 VpCount;
    HV_UINT8 Reserved1[3];
    HV_UINT64 PartitionIds[HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT];
    HV_VP_INDEX VpIndexes[HV_MESSAGE_MAX_PARTITION_VP_PAIR_COUNT];
    HV_UINT8 Reserved2[4];
} HV_VP_SIGNAL_PAIR_SCHEDULER_MESSAGE, *PHV_VP_SIGNAL_PAIR_SCHEDULER_MESSAGE;

HV_STATIC_ASSERT(sizeof(HV_VP_SIGNAL_PAIR_SCHEDULER_MESSAGE) ==
    (sizeof(HV_MESSAGE) - sizeof(HV_MESSAGE_HEADER)));

// Input and output structures for HVCALL_DISPATCH_VP

#define HV_DISPATCH_VP_FLAG_CLEAR_INTERCEPT_SUSPEND 0x1
#define HV_DISPATCH_VP_FLAG_ENABLE_CALLER_INTERRUPTS 0x2
#define HV_DISPATCH_VP_FLAG_SET_CALLER_SPEC_CTRL 0x4
#define HV_DISPATCH_VP_FLAG_SKIP_VP_SPEC_FLUSH 0x8
#define HV_DISPATCH_VP_FLAG_SKIP_CALLER_SPEC_FLUSH 0x10
#define HV_DISPATCH_VP_FLAG_SKIP_CALLER_USER_SPEC_FLUSH 0x20

// *****************************************************************************
// Extra Hyper-V definitions from Windows symbols
//

typedef HV_UINT32 HV_LOGICAL_DEVICE_ID, *PHV_LOGICAL_DEVICE_ID;

typedef HV_UINT32 HV_PASID, *PHV_PASID;

typedef HV_UINT32 HV_PASID_SPACE_ID, *PHV_PASID_SPACE_ID;

typedef HV_UINT8 HV_IOAPIC_ID, *PHV_IOAPIC_ID;

typedef HV_UINT16 HV_PCI_SEGMENT, *PHV_PCI_SEGMENT;

typedef HV_UINT64 HV_DEVICE_VA, *PHV_DEVICE_VA;

typedef HV_UINT16 HV_PCI_RID, *PHV_PCI_RID;

typedef HV_UINT32 HV_DEVICE_DOMAIN_ID, *PHV_DEVICE_DOMAIN_ID;

typedef HV_UINT32 HV_DEVICE_PR_QUEUE_ID, *PHV_DEVICE_PR_QUEUE_ID;

typedef enum _HV_SUBNODE_TYPE
{
    HvSubnodeAny = 0x0,
    HvSubnodeSocket = 0x1,
    HvSubnodeCluster = 0x2,
    HvSubnodeL3 = 0x3,
    HvSubnodeCount = 0x4,
    HvSubnodeInvalid = 0xFFFFFFFF,
} HV_SUBNODE_TYPE, *PHV_SUBNODE_TYPE;

typedef struct _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER
{
    HV_ADDRESS_SPACE_ID AddressSpace;
    HV_FLUSH_FLAGS Flags;
    HV_UINT64 ProcessorMask;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER;

typedef struct _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER_EX
{
    HV_ADDRESS_SPACE_ID AddressSpace;
    HV_FLUSH_FLAGS Flags;
    HV_GENERIC_SET ProcessorSet;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER_EX, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER_EX;

typedef union _HV_GPA_PAGE_ATTRIBUTES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Protectable : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_GPA_PAGE_ATTRIBUTES, *PHV_GPA_PAGE_ATTRIBUTES;

typedef enum _HV_NESTED_MSR_INTERCEPT_MODE
{
    HvNestedMsrInterceptModeSlow = 0x0,
    HvNestedMsrInterceptModeFast = 0x1,
    HvNestedMsrInterceptModeEnlightened = 0x2,
    HvNestedMsrInterceptModeCount = 0x3,
} HV_NESTED_MSR_INTERCEPT_MODE, *PHV_NESTED_MSR_INTERCEPT_MODE;

typedef enum _HV_X64_PENDING_EVENT_TYPE
{
    HvX64PendingEventException = 0x0,
    HvX64PendingEventMemoryIntercept = 0x1,
    HvX64PendingEventNestedMemoryIntercept = 0x2,
} HV_X64_PENDING_EVENT_TYPE, *PHV_X64_PENDING_EVENT_TYPE;

typedef enum _HV_STORE_DATA_RESULT
{
    StoreDataSuccess = 0x0,
    StoreDataNoWritesRequired = 0x1,
    StoreDataFailure = 0x2,
    StoreDataResultMaximum = 0x3,
} HV_STORE_DATA_RESULT, *PHV_STORE_DATA_RESULT;

typedef enum _HV_FILE_STATUS
{
    Shrunk = 0x0,
    Grown = 0x1,
    Unchanged = 0x2,
} HV_FILE_STATUS, *PHV_FILE_STATUS;

typedef enum _HV_BACKING_STORAGE_TYPE
{
    HvStorageLoader = 0x0,
    HvStoragePool = 0x1,
    HvStorageSystemCache = 0x2,
} HV_BACKING_STORAGE_TYPE, *PHV_BACKING_STORAGE_TYPE;

typedef enum _HV_LOG_SWAP_REASON
{
    HvLogSwapSpaceExhausted = 0x0,
    HvLogSwapReconcile = 0x1,
} HV_LOG_SWAP_REASON, *PHV_LOG_SWAP_REASON;

typedef enum _HV_LOGICAL_PROCESSOR_PROPERTY_TYPE
{
    HvLogicalProcessorPerfStateConfig = 0x0,
    HvLogicalProcessorThrottleStateConfig = 0x1,
    HvLogicalProcessorPccConfig = 0x2,
    HvLogicalProcessorPerfStateCap = 0x3,
    HvLogicalProcessorMachineCheckContextInfo = 0x4,
    HvLogicalProcessorMcUpdateUpdateStatus = 0x5,
} HV_LOGICAL_PROCESSOR_PROPERTY_TYPE, *PHV_LOGICAL_PROCESSOR_PROPERTY_TYPE;

typedef enum _HV_LOGICAL_PROCESSOR_REGISTER_TYPE
{
    HvX64LpRegisterTypeCpuid = 0x10000,
    HvX64LpRegisterTypeMsr = 0x10001,
    HvX64LpRegisterTypeWbinvd = 0x10002,
} HV_LOGICAL_PROCESSOR_REGISTER_TYPE, *PHV_LOGICAL_PROCESSOR_REGISTER_TYPE;
typedef const HV_LOGICAL_PROCESSOR_REGISTER_TYPE *PCHV_LOGICAL_PROCESSOR_REGISTER_TYPE;

typedef enum _HV_POWER_PROPERTY_TYPE
{
    HvPowerPropertyLpIdleStateConfig = 0x0,
    HvPowerPropertyLpPerfFeedbackCounters = 0x1,
    HvPowerPropertyLpPercentageFrequency = 0x2,
    HvPowerPropertyLpNextPlatformStateIndex = 0x3,
    HvPowerPropertyStatsOffsets = 0x4,
    HvPowerPropertyPolicySetting = 0x5,
} HV_POWER_PROPERTY_TYPE, *PHV_POWER_PROPERTY_TYPE;

typedef enum _HV_PARTITION_EVENT
{
    HvPartitionEventDebugDeviceAvailable = 0x1,
    HvPartitionEventRootCrashdump = 0x2,
    HvPartitionEventAcpiReenabled = 0x3,
} HV_PARTITION_EVENT, *PHV_PARTITION_EVENT;

typedef enum _HV_PPM_POWER_POLICY_SETTING_ID
{
    HvPowerPolicyIdleDisable = 0x0,
    HvPowerPolicyIdleTimeCheck = 0x1,
    HvPowerPolicyIdlePromoteThreshold = 0x2,
    HvPowerPolicyIdleDemoteThreshold = 0x3,
    HvPowerPolicyIdleStateMaximum = 0x4,
    HvPowerPolicyThrottleMaximum = 0x5,
    HvPowerPolicyThrottleMinimum = 0x6,
    HvPowerPolicyPerfIncreaseThreshold = 0x7,
    HvPowerPolicyPerfDecreaseThreshold = 0x8,
    HvPowerPolicyPerfIncreasePolicy = 0x9,
    HvPowerPolicyPerfDecreasePolicy = 0xA,
    HvPowerPolicyCoreParkingIncreasePolicy = 0xB,
    HvPowerPolicyCoreParkingDecreasePolicy = 0xC,
    HvPowerPolicyCoreParkingMaxCores = 0xD,
    HvPowerPolicyCoreParkingMinCores = 0xE,
    HvPowerPolicyPerfTimeCheck = 0xF,
    HvPowerPolicyPerfIncreaseTime = 0x10,
    HvPowerPolicyPerfDecreaseTime = 0x11,
    HvPowerPolicyPerfBoostPolicy = 0x12,
    HvPowerPolicyPerfBoostMode = 0x13,
    HvPowerPolicyMax = 0x14,
} HV_PPM_POWER_POLICY_SETTING_ID, *PHV_PPM_POWER_POLICY_SETTING_ID;

typedef enum _HV_BOOT_DEBUG_PORT_TYPE
{
    HvBootDbgPortNone = 0x0,
    HvBootDbgPortCom = 0x1,
    HvBootDbgPortFirewire = 0x2,
    HvBootDbgPortNet = 0x3,
} HV_BOOT_DEBUG_PORT_TYPE, *PHV_BOOT_DEBUG_PORT_TYPE;

typedef enum _HV_CRASHDUMP_ACTION
{
    HvCrashdumpNone = 0x0,
    HvCrashdumpSuspendAllVps = 0x1,
    HvCrashdumpPrepareForStateSave = 0x2,
    HvCrashdumpStateSaved = 0x3,
} HV_CRASHDUMP_ACTION, *PHV_CRASHDUMP_ACTION;

typedef enum _HV_PHYSICAL_DEVICE_PROPERTY
{
    HvPhysicalDevicePropertyCapabilities = 0x0,
    HvPhysicalDevicePropertyEnabled = 0x1,
} HV_PHYSICAL_DEVICE_PROPERTY, *PHV_PHYSICAL_DEVICE_PROPERTY;

typedef enum _HV_X64_PPM_PERF_STATE_PORT_ACCESS_SIZE
{
    HvX64PerfStatePort8Bit = 0x0,
    HvX64PerfStatePort16Bit = 0x1,
    HvX64PerfStatePort32Bit = 0x2,
} HV_X64_PPM_PERF_STATE_PORT_ACCESS_SIZE, *PHV_X64_PPM_PERF_STATE_PORT_ACCESS_SIZE;

typedef enum _HV_MACHINE_CHECK_RECOVERY_FLAG
{
    InvalidRecoveryFlag = 0x0,
    NewDeferredRecoveryQueued = 0x1,
    DeferredRecoveryCompleted = 0x2,
} HV_MACHINE_CHECK_RECOVERY_FLAG, *PHV_MACHINE_CHECK_RECOVERY_FLAG;

typedef enum _HV_MACHINE_CHECK_SOURCE
{
    HV_MACHINE_CHECK_SOURCE_NONE = 0x0,
    HV_MACHINE_CHECK_SOURCE_HV = 0x1,
    HV_MACHINE_CHECK_SOURCE_ROOT_VP = 0x2,
    HV_MACHINE_CHECK_SOURCE_NON_ROOT_VP = 0x3,
} HV_MACHINE_CHECK_SOURCE, *PHV_MACHINE_CHECK_SOURCE;

typedef enum _HV_DEVICE_TYPE
{
    HV_DEVICE_TYPE_PCI = 0x1,
    HV_DEVICE_TYPE_IOAPIC = 0x2,
} HV_DEVICE_TYPE, *PHV_DEVICE_TYPE;

typedef enum _HV_COVERAGE_OPERATION
{
    HvCoverageFetchInfo = 0x0,
    HvCoverageFetchCovHeader = 0x1,
    HvCoverageFetchCovSection = 0x2,
    HvCoverageResetCovVector = 0x3,
} HV_COVERAGE_OPERATION, *PHV_COVERAGE_OPERATION;

typedef enum _HV_BOOT_DEBUG_COM_PORT_TYPE
{
    HvBootDbgPortComIoPort = 0x0,
    HvBootDbgPortComMemoryMapped = 0x1,
} HV_BOOT_DEBUG_COM_PORT_TYPE, *PHV_BOOT_DEBUG_COM_PORT_TYPE;

typedef enum _HV_INTERRUPT_TRIGGER_MODE
{
    HvInterruptTriggerModeEdge = 0x0,
    HvInterruptTriggerModeLevel = 0x1,
} HV_INTERRUPT_TRIGGER_MODE, *PHV_INTERRUPT_TRIGGER_MODE;

typedef enum _HV_SLEEP_STATE
{
    HvSleepStateS1 = 0x1,
    HvSleepStateS2 = 0x2,
    HvSleepStateS3 = 0x3,
    HvSleepStateS4 = 0x4,
    HvSleepStateS5 = 0x5,
    HvSleepStateLock = 0x6,
} HV_SLEEP_STATE, *PHV_SLEEP_STATE;

typedef enum _HV_DEVICE_PRQ_PROPERTY
{
    HvDevicePrqPropertyStalled = 0x0,
    HvDevicePrqPropertyInterruptMasked = 0x1,
} HV_DEVICE_PRQ_PROPERTY, *PHV_DEVICE_PRQ_PROPERTY;

typedef enum _HV_MACHINE_CHECK_PROPERTY_TYPE
{
    MachineCheckHandlerState = 0x1,
    MachineCheckDeferredRecoveryState = 0x2,
} HV_MACHINE_CHECK_PROPERTY_TYPE, *PHV_MACHINE_CHECK_PROPERTY_TYPE;

typedef enum _HV_X64_PPM_PERF_STATE_REGISTER_TYPE
{
    HvX64PerfStateRegisterNone = 0x0,
    HvX64PerfStateRegisterMsr = 0x1,
    HvX64PerfStateRegisterIo = 0x2,
    HvX64PerfStateRegisterMemory = 0x3,
} HV_X64_PPM_PERF_STATE_REGISTER_TYPE, *PHV_X64_PPM_PERF_STATE_REGISTER_TYPE;

typedef enum _HV_X64_PPM_PERF_DOMAIN_COORDINATION
{
    HvX64PerfDomainCoordinationSwAll = 0x0,
    HvX64PerfDomainCoordinationSwAny = 0x1,
    HvX64PerfDomainCoordinationHwAll = 0x2,
} HV_X64_PPM_PERF_DOMAIN_COORDINATION, *PHV_X64_PPM_PERF_DOMAIN_COORDINATION;

typedef enum _HV_ERROR_TYPES
{
    HV_MISCELLANEOUS_ERROR = 0x0,
    HV_PERFORMANCE_COUNTER_DECREASED = 0x1,
    HV_PERFORMANCE_COUNTER_SKIPPED = 0x2,
    HV_FREED_TOO_MANY_COMMON_BUFFERS = 0x3,
    HV_FREED_TOO_MANY_ADAPTER_CHANNELS = 0x4,
    HV_FREED_TOO_MANY_MAP_REGISTERS = 0x5,
    HV_FREED_TOO_MANY_SCATTER_GATHER_LISTS = 0x6,
    HV_LEFTOVER_COMMON_BUFFERS = 0x7,
    HV_LEFTOVER_ADAPTER_CHANNELS = 0x8,
    HV_LEFTOVER_MAP_REGISTERS = 0x9,
    HV_LEFTOVER_SCATTER_GATHER_LISTS = 0xA,
    HV_TOO_MANY_ADAPTER_CHANNELS = 0xB,
    HV_TOO_MANY_MAP_REGISTERS = 0xC,
    HV_DID_NOT_FLUSH_ADAPTER_BUFFERS = 0xD,
    HV_DMA_BUFFER_NOT_LOCKED = 0xE,
    HV_BOUNDARY_OVERRUN = 0xF,
    HV_CANNOT_FREE_MAP_REGISTERS = 0x10,
    HV_DID_NOT_PUT_ADAPTER = 0x11,
    HV_MDL_FLAGS_NOT_SET = 0x12,
    HV_BAD_IRQL = 0x13,
    HV_BAD_IRQL_JUST_WARN = 0x14,
    HV_OUT_OF_MAP_REGISTERS = 0x15,
    HV_FLUSH_EMPTY_BUFFERS = 0x16,
    HV_MISMATCHED_MAP_FLUSH = 0x17,
    HV_ADAPTER_ALREADY_RELEASED = 0x18,
    HV_NULL_DMA_ADAPTER = 0x19,
    HV_MAP_FLUSH_NO_TRANSFER = 0x1A,
    HV_ADDRESS_NOT_IN_MDL = 0x1B,
    HV_DATA_LOSS = 0x1C,
    HV_DOUBLE_MAP_REGISTER = 0x1D,
    HV_OBSOLETE_API = 0x1E,
    HV_BAD_MDL = 0x1F,
    HV_FLUSH_NOT_MAPPED = 0x20,
    HV_MAP_ZERO_LENGTH_BUFFER = 0x21,
    HV_BUFFER_NOT_MAPPED_IN_SYSTEM_VA = 0x22,
    HV_INCOMPLETE_FLUSH = 0x23,
    HV_INSUFFICIENT_BUFFER = 0x24,
    HV_UNKNOWN_DEVICE_DESCRIPTION_VERSION = 0x25,
    HV_MAX_ERROR_TYPES = 0x26,
    HV_ERROR_HAS_SUBCODE = 0x10000000,
} HV_ERROR_TYPES, *PHV_ERROR_TYPES;

typedef struct _HV_PPM_POWER_POLICY_SETTING
{
    HV_PPM_POWER_POLICY_SETTING_ID SettingId;
    HV_UINT32 Value;
} HV_PPM_POWER_POLICY_SETTING, *PHV_PPM_POWER_POLICY_SETTING;

typedef struct _HV_IOMMU_INIT_STATUS
{
    HV_UINT8 HardwarePresent;
    HV_UINT8 Enabled;
    HV_UINT64 Policy;
    HV_UINT64 Features;
    HV_UINT64 InitStatus;
    HV_UINT64 Errors;
    HV_UINT64 Errata;
} HV_IOMMU_INIT_STATUS, *PHV_IOMMU_INIT_STATUS;

typedef struct _HV_TSC_SYNC_STATUS
{
    HV_UINT8 SyncFailed;
    HV_UINT8 SyncNeeded;
    HV_INT64 MaxDelta;
    HV_INT64 MinDelta;
} HV_TSC_SYNC_STATUS, *PHV_TSC_SYNC_STATUS;

typedef union _HV_PCI_BDF
{
    HV_UINT16 AsUINT16;
    struct
    {
        HV_UINT8 Function : 3;
        HV_UINT8 Device : 5;
        HV_UINT8 Bus;
    };
} HV_PCI_BDF, *PHV_PCI_BDF;

typedef union _HV_PCI_BUS_RANGE
{
    HV_UINT16 AsUINT16;
    struct
    {
        HV_UINT8 SubordinateBus;
        HV_UINT8 SecondaryBus;
    };
} HV_PCI_BUS_RANGE, *PHV_PCI_BUS_RANGE;

typedef union _HV_DEVICE_ID
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT16 Rid;
        HV_UINT16 Segment;
        HV_UINT8 DeviceType : 2;
        HV_UINT8 SourceShadow : 2;
        HV_UINT8 PhantomFunctionBits : 2;
        HV_UINT8 RsvdZ0 : 2;
        HV_UINT8 IoApicId;
        HV_PCI_BDF ShadowBdf;
    };
    struct
    {
        HV_PCI_BDF Bdf;
        HV_UINT8 gap2[4];
        HV_PCI_BUS_RANGE ShadowBusRange;
    };
} HV_DEVICE_ID, *PHV_DEVICE_ID;

typedef struct _HV_HPET_CONFIG_INFO
{
    HV_UINT64 BaseAddress;
    HV_UINT32 TimerIndex;
    HV_DEVICE_ID DeviceId;
    HV_UINT8 TimerInterruptPin;
} HV_HPET_CONFIG_INFO, *PHV_HPET_CONFIG_INFO;

typedef struct _HV_HPET_INTERRUPT_INFO
{
    HV_INTERRUPT_ENTRY InterruptEntry;
} HV_HPET_INTERRUPT_INFO, *PHV_HPET_INTERRUPT_INFO;

typedef struct _HV_HPET_ENABLED_INFO
{
    HV_UINT8 HpetEnabled : 1;
    HV_UINT8 Reserved : 7;
} HV_HPET_ENABLED_INFO, *PHV_HPET_ENABLED_INFO;

typedef struct _HV_HYPERVISOR_LAUNCH_STATS
{
    HV_UINT64 RootBspTscAdjustment;
} HV_HYPERVISOR_LAUNCH_STATS, *PHV_HYPERVISOR_LAUNCH_STATS;

typedef struct _HV_ROOT_SVM_CAPABILITIES_PROPERTY
{
    HV_UINT32 IommuCount;
    HV_UINT32 MinIommuPasidCount;
} HV_ROOT_SVM_CAPABILITIES_PROPERTY, *PHV_ROOT_SVM_CAPABILITIES_PROPERTY;

typedef struct _HV_NUMA_NODE_RESERVED_PAGE_INFO
{
    HV_UINT64 PhysicalAddress;
    HV_UINT32 ProximityDomainId;
} HV_NUMA_NODE_RESERVED_PAGE_INFO, *PHV_NUMA_NODE_RESERVED_PAGE_INFO;

typedef struct _HV_ROOT_NUMA_COST_PAGES_PROPERTY
{
    HV_UINT32 NumaNodeCount;
    HV_UINT32 ReservedP;
    HV_NUMA_NODE_RESERVED_PAGE_INFO NumaNodePfn[64];
} HV_ROOT_NUMA_COST_PAGES_PROPERTY, *PHV_ROOT_NUMA_COST_PAGES_PROPERTY;

typedef struct _HV_SLEEP_STATE_INFO
{
    HV_SLEEP_STATE SleepState;
    HV_UINT8 Pm1a_SLP_TYP;
    HV_UINT8 Pm1b_SLP_TYP;
} HV_SLEEP_STATE_INFO, *PHV_SLEEP_STATE_INFO;

typedef struct _HV_MACHINE_CHECK_PROPERTY_INFO
{
    HV_MACHINE_CHECK_PROPERTY_TYPE PropertyType;
    union
    {
        HV_UINT8 MachineCheckHandlerReady;
        HV_MACHINE_CHECK_RECOVERY_FLAG MachineCheckRecoveryFlag;
    };
} HV_MACHINE_CHECK_PROPERTY_INFO, *PHV_MACHINE_CHECK_PROPERTY_INFO;

typedef struct _HV_HYPERVISOR_DEBUG_PROPERTY
{
    HV_UINT8 PowerStateEnabled;
} HV_HYPERVISOR_DEBUG_PROPERTY, *PHV_HYPERVISOR_DEBUG_PROPERTY;

typedef struct _HV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO
{
    HV_UINT8 NestedVirtualization;
} HV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO, *PHV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO;

typedef union _HV_SPA_PAGE_LIST_FLAGS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Deposited : 1;
        HV_UINT64 RsvdZ : 63;
    };
} HV_SPA_PAGE_LIST_FLAGS, *PHV_SPA_PAGE_LIST_FLAGS;

typedef struct _HV_X64_PPM_PERF_STATE
{
    HV_UINT64 Control;
    HV_UINT64 Status;
    HV_UINT64 ControlMask;
    HV_UINT64 StatusMask;
    HV_UINT32 Frequency;
    HV_UINT32 TransitionLatency;
    HV_UINT32 BusMasterLatency;
    HV_UINT32 PowerConsumption;
} HV_X64_PPM_PERF_STATE, *PHV_X64_PPM_PERF_STATE;

typedef union _HV_X64_PPM_PERF_STATE_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 TypeSpecific : 52;
        HV_UINT64 RegisterType : 12;
    };
    struct
    {
        HV_UINT32 RegisterNumber;
        HV_UINT8 BitWidth;
        HV_UINT8 BitOffset;
        HV_UINT16 ReservedZ : 4;
    } Msr;
    struct
    {
        HV_UINT16 Port;
        HV_UINT16 AccessSize;
        HV_UINT8 BitWidth;
        HV_UINT8 BitOffset;
        HV_UINT16 ReservedZ : 4;
    } Io;
    struct
    {
        HV_UINT64 Address : 52;
    } Memory;
} HV_X64_PPM_PERF_STATE_REGISTER, *PHV_X64_PPM_PERF_STATE_REGISTER;

typedef struct _HV_X64_PPM_PERF_STATE_CONFIG_PROPERTY
{
    HV_UINT32 StateCount;
    HV_X64_PPM_PERF_STATE States[64];
    HV_UINT32 DomainId;
    HV_UINT32 NumProcInDomain;
    HV_X64_PPM_PERF_DOMAIN_COORDINATION Coordination;
    HV_X64_PPM_PERF_STATE_REGISTER ControlRegister;
    HV_X64_PPM_PERF_STATE_REGISTER StatusRegister;
} HV_X64_PPM_PERF_STATE_CONFIG_PROPERTY, *PHV_X64_PPM_PERF_STATE_CONFIG_PROPERTY;

typedef struct _HV_X64_PPM_THROTTLE_STATE
{
    HV_UINT64 Control;
    HV_UINT64 Status;
    HV_UINT32 PercentFrequency;
    HV_UINT32 TransitionLatency;
    HV_UINT32 PowerConsumption;
} HV_X64_PPM_THROTTLE_STATE, *PHV_X64_PPM_THROTTLE_STATE;

typedef struct _HV_X64_PPM_THROTTLE_STATE_CONFIG_PROPERTY
{
    HV_UINT32 StateCount;
    HV_X64_PPM_THROTTLE_STATE States[100];
    HV_UINT32 DomainId;
    HV_UINT32 NumProcInDomain;
    HV_X64_PPM_PERF_DOMAIN_COORDINATION Coordination;
    HV_X64_PPM_PERF_STATE_REGISTER ControlRegister;
    HV_X64_PPM_PERF_STATE_REGISTER StatusRegister;
    HV_UINT64 ControlMask;
    HV_UINT64 StatusMask;
} HV_X64_PPM_THROTTLE_STATE_CONFIG_PROPERTY, *PHV_X64_PPM_THROTTLE_STATE_CONFIG_PROPERTY;

typedef struct _HV_X64_PPM_PCC_CONFIG_PROPERTY
{
    HV_UINT32 Flags;
    HV_UINT32 DomainId;
    HV_UINT32 NumProcInDomain;
    HV_X64_PPM_PERF_DOMAIN_COORDINATION Coordination;
    HV_UINT64 SharedMemoryAddress;
    HV_UINT32 SharedMemoryLength;
    HV_X64_PPM_PERF_STATE_REGISTER Doorbell;
    HV_UINT64 DoorbellPreserve;
    HV_UINT64 DoorbellWrite;
    HV_UINT64 DoorbellMask;
    HV_UINT32 InputBufferOffset;
    HV_UINT32 OutputBufferOffset;
} HV_X64_PPM_PCC_CONFIG_PROPERTY, *PHV_X64_PPM_PCC_CONFIG_PROPERTY;

typedef struct _HV_X64_PPM_PERF_STATE_CAP_PROPERTY
{
    HV_UINT32 PStateCap;
    HV_UINT32 TStateCap;
    HV_UINT32 ThermalCap;
} HV_X64_PPM_PERF_STATE_CAP_PROPERTY, *PHV_X64_PPM_PERF_STATE_CAP_PROPERTY;

typedef struct _HV_MACHINE_CHECK_CONTEXT
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL Vtl;
} HV_MACHINE_CHECK_CONTEXT, *PHV_MACHINE_CHECK_CONTEXT;

typedef struct _HV_MACHINE_CHECK_CONTEXT_INFO
{
    HV_MACHINE_CHECK_SOURCE MachineCheckSource;
    HV_MACHINE_CHECK_CONTEXT MachineCheckContext;
} HV_MACHINE_CHECK_CONTEXT_INFO, *PHV_MACHINE_CHECK_CONTEXT_INFO;

typedef struct _HV_MCUPDATE_UPDATE_STATUS
{
    HV_BOOLEAN Valid;
    HV_UINT32 UpdateLoadStatus;
    HV_UINT32 UpdateRevision;
    HV_UINT32 PreviousUpdateRevision;
    HV_UINT32 PlatformSpecificField1;
    HV_UINT32 PlatformSpecificField2;
} HV_MCUPDATE_UPDATE_STATUS, *PHV_MCUPDATE_UPDATE_STATUS;

typedef union _HV_LOGICAL_PROCESSOR_PROPERTY
{
    HV_X64_PPM_PERF_STATE_CONFIG_PROPERTY PerfStateConfig;
    HV_X64_PPM_THROTTLE_STATE_CONFIG_PROPERTY ThrottleStateConfig;
    HV_X64_PPM_PCC_CONFIG_PROPERTY PccConfig;
    HV_X64_PPM_PERF_STATE_CAP_PROPERTY PerfStateCap;
    HV_MACHINE_CHECK_CONTEXT_INFO MachineCheckContextInfo;
    HV_MCUPDATE_UPDATE_STATUS UpdateStatus;
} HV_LOGICAL_PROCESSOR_PROPERTY, *PHV_LOGICAL_PROCESSOR_PROPERTY;

typedef struct _HV_INPUT_DEVICE_DOMAIN
{
    HV_PARTITION_ID PartitionId;
    HV_INPUT_VTL OwnerVtl;
    HV_DEVICE_DOMAIN_ID DomainId;
} HV_INPUT_DEVICE_DOMAIN, *PHV_INPUT_DEVICE_DOMAIN;

typedef union _HV_FULL_PASID
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_PASID Pasid;
        HV_PASID_SPACE_ID PasidSpaceId;
    };
} HV_FULL_PASID, *PHV_FULL_PASID;

typedef union _HV_DEVICE_ADDRESS_SPACE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Present : 1;
        HV_UINT64 Reserved : 11;
        HV_UINT64 PageTableRootPfn : 52;
    };
} HV_DEVICE_ADDRESS_SPACE, *PHV_DEVICE_ADDRESS_SPACE;

typedef struct _HV_DEVICE_INTERRUPT_DESCRIPTOR
{
    HV_INTERRUPT_TYPE InterruptType;
    HV_INTERRUPT_TRIGGER_MODE TriggerMode;
    HV_UINT32 VectorCount;
    HV_UINT32 Reserved;
    HV_DEVICE_INTERRUPT_TARGET Target;
} HV_DEVICE_INTERRUPT_DESCRIPTOR, *PHV_DEVICE_INTERRUPT_DESCRIPTOR;

typedef union _HV_ATTACH_DEVICE_FLAGS
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 LogicalId : 1;
        HV_UINT32 PasidSupported : 1;
        HV_UINT32 PasidEnabled : 1;
        HV_UINT32 Reserved : 29;
    };
} HV_ATTACH_DEVICE_FLAGS, *PHV_ATTACH_DEVICE_FLAGS;

typedef union _HV_DEVICE_PCI_CAPABILITIES
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 MaxPasidWidth : 5;
        HV_UINT32 InvalidateQueueDepth : 5;
        HV_UINT32 GlobalInvalidate : 1;
        HV_UINT32 Reserved : 21;
    };
} HV_DEVICE_PCI_CAPABILITIES, *PHV_DEVICE_PCI_CAPABILITIES;

typedef struct _HV_X64_PROC_STATE_GP_REGS
{
    HV_UINT64 Rip;
    HV_UINT64 Rsp;
    HV_UINT64 Rbp;
    HV_UINT64 Rbx;
    HV_UINT64 Rdi;
    HV_UINT64 Rsi;
    HV_UINT64 R12;
    HV_UINT64 R13;
    HV_UINT64 R14;
    HV_UINT64 R15;
} HV_X64_PROC_STATE_GP_REGS, *PHV_X64_PROC_STATE_GP_REGS;

typedef struct _HV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT
{
    HV_CRASHDUMP_ACTION CrashdumpAction;
} HV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT, *PHV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT;

typedef union _HV_PARTITION_EVENT_INPUT
{
    HV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT CrashdumpInput;
} HV_PARTITION_EVENT_INPUT, *PHV_PARTITION_EVENT_INPUT;

typedef union _HV_X64_PPM_IDLE_STATE_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 TypeSpecific : 52;
        HV_UINT64 ChangeType : 4;
        HV_UINT64 CheckBM_STS : 1;
        HV_UINT64 SetBM_RST : 1;
        HV_UINT64 ClearBM_RST : 1;
        HV_UINT64 SetARB_DIS : 1;
        HV_UINT64 ReservedZ : 4;
    };
    struct
    {
        HV_UINT64 ReservedZ : 52;
    } Hlt;
    struct
    {
        HV_UINT16 Port;
        HV_UINT16 ReservedZ1;
        HV_UINT32 ReservedZ2 : 20;
    } Io;
    struct $CCBD12C915509F5FCC777673CF5E3E97
    {
        HV_UINT32 Hints;
        HV_UINT32 BreakOnMaskedInterrupt : 1;
        HV_UINT32 ReservedZ : 19;
    } Mwait;
} HV_X64_PPM_IDLE_STATE_CONFIG, *PHV_X64_PPM_IDLE_STATE_CONFIG;

typedef struct _HV_X64_PPM_IDLE_STATE
{
    HV_X64_PPM_IDLE_STATE_CONFIG Config;
    HV_UINT32 Type;
    HV_UINT32 HardwareLatency;
    HV_UINT32 PowerConsumption;
} HV_X64_PPM_IDLE_STATE, *PHV_X64_PPM_IDLE_STATE;

typedef struct _HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY
{
    HV_UINT32 StateCount;
    HV_X64_PPM_IDLE_STATE States[16];
} HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY, *PHV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY;

typedef struct _HV_X64_PPM_FEEDBACK_REGISTER_PAIR
{
    HV_X64_PPM_PERF_STATE_REGISTER ReferenceCount;
    HV_X64_PPM_PERF_STATE_REGISTER ActualCount;
    HV_UINT8 ResetRegisters;
} HV_X64_PPM_FEEDBACK_REGISTER_PAIR, *PHV_X64_PPM_FEEDBACK_REGISTER_PAIR;

typedef struct _HV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG
{
    HV_UINT32 Count;
    HV_X64_PPM_FEEDBACK_REGISTER_PAIR FeedbackCounters[4];
} HV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG, *PHV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG;

typedef struct _HV_POWER_STATS_OFFSETS
{
    HV_UINT32 GlobalTime;
    HV_UINT32 TotalRunTime;
    HV_UINT32 IdleSequenceNumber;
    HV_UINT32 GlobalTscCount;
    HV_UINT32 ActiveTscCount;
    HV_UINT32 IdleAccumulation;
    struct
    {
        HV_UINT32 Reference;
        HV_UINT32 Actual;
    } CycleCount[2];
} HV_POWER_STATS_OFFSETS, *PHV_POWER_STATS_OFFSETS;

// Note: Add HV_ prefix to avoid conflict
typedef union _HV_IPV6_ADDRESS
{
    struct
    {
        HV_UINT64 QW0;
        HV_UINT64 QW1;
    };
    struct
    {
        HV_UINT32 DW0;
        HV_UINT32 DW1;
        HV_UINT32 DW2;
        HV_UINT32 DW3;
    };
    struct
    {
        HV_UINT16 W0;
        HV_UINT16 W1;
        HV_UINT16 W2;
        HV_UINT16 W3;
        HV_UINT16 W4;
        HV_UINT16 W5;
        HV_UINT16 W6;
        HV_UINT16 W7;
    };
} HV_IPV6_ADDRESS, *PHV_IPV6_ADDRESS;

typedef struct _HV_DEBUG_NET_DATA
{
    struct
    {
        HV_UINT32 HostIp;
        HV_UINT32 TargetIp;
        HV_UINT16 HostPort;
        HV_UINT16 TargetPort;
        HV_UINT8 HostMac[6];
        HV_UINT8 TargetMac[6];
    } Ipv4;
    struct
    {
        HV_IPV6_ADDRESS HostIp;
        HV_IPV6_ADDRESS TargetIp;
        HV_UINT16 HostPort;
        HV_UINT16 TargetPort;
        HV_UINT8 HostMac[6];
        HV_UINT8 TargetMac[6];
    } Ipv6;
} HV_DEBUG_NET_DATA, *PHV_DEBUG_NET_DATA;

typedef struct _HV_LP_STARTUP_STATUS
{
    HV_UINT16 Status;
    HV_UINT64 SubStatus1;
    HV_UINT64 SubStatus2;
    HV_UINT64 SubStatus3;
    HV_UINT64 SubStatus4;
    HV_UINT64 SubStatus5;
    HV_UINT64 SubStatus6;
} HV_LP_STARTUP_STATUS, *PHV_LP_STARTUP_STATUS;

typedef struct _HV_MEMORY_DESCRIPTOR
{
    HV_UINT64 Pages;
    HV_UINT32 Levels;
    HV_UINT64 PageTableRoot;
} HV_MEMORY_DESCRIPTOR, *PHV_MEMORY_DESCRIPTOR;

typedef struct _HV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES
{
    HV_UINT32 RootSvm : 1;
    HV_UINT32 PciExecute : 1;
    HV_UINT32 NoExecute : 1;
    HV_UINT32 Reserved0 : 28;
    HV_UINT32 OverflowPossible : 1;
    HV_UINT32 PasidCount;
    HV_UINT32 RootSvmIommuIndex;
    HV_UINT32 Reserved1;
} HV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES, *PHV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES;

typedef struct _HV_PHYSICAL_DEVICE_PROPERTY_ENABLED
{
    HV_UINT8 PasidEnabled;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_UINT32 Reserved2;
} HV_PHYSICAL_DEVICE_PROPERTY_ENABLED, *PHV_PHYSICAL_DEVICE_PROPERTY_ENABLED;

typedef struct _HV_IOMMU_EXTENDED_STATUS
{
    HV_UINT8 Severity;
    HV_UINT16 Status;
    HV_UINT64 Params[4];
} HV_IOMMU_EXTENDED_STATUS, *PHV_IOMMU_EXTENDED_STATUS;

typedef struct _HV_IMAGE_COVERAGE_INFO
{
    HV_UINT32 HeaderSize;
    HV_UINT32 Size;
    HV_WCHAR ImageName[HV_IMAGE_NAME_MAX_LENGTH];
} HV_IMAGE_COVERAGE_INFO, *PHV_IMAGE_COVERAGE_INFO;

typedef union _HV_SPA_PAGE_RANGE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 BasePfn : 40;
        HV_UINT64 AdditionalPages : 24;
    };
} HV_SPA_PAGE_RANGE, *PHV_SPA_PAGE_RANGE;

typedef union _HV_REGISTER_NESTED_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MsrInterceptMode : 2;
        HV_UINT64 MsrBitmapDirty : 1;
        HV_UINT64 RsvdZ : 61;
    };
} HV_REGISTER_NESTED_CONTROL, *PHV_REGISTER_NESTED_CONTROL;

typedef union _HV_REGISTER_VSM_VP_VTL_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Mapped : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_REGISTER_VSM_VP_VTL_CONTROL, *PHV_REGISTER_VSM_VP_VTL_CONTROL;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_XSAVE_AREA
{
    HV_X64_FX_REGISTERS LegacyFxRegisters;
    HV_X64_X_REGISTERS XRegisters;
} HV_X64_XSAVE_AREA, *PHV_X64_XSAVE_AREA;
#endif

typedef union _HV_REGISTER_VSM_CAPABILITIES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Dr6Shared : 1;
        HV_UINT64 MbecVtlMask : 16;
        HV_UINT64 ReservedZ : 47;
    };
} HV_REGISTER_VSM_CAPABILITIES, *PHV_REGISTER_VSM_CAPABILITIES;

typedef union _HV_VTL_RETURN_INPUT
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 FastReturn : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_VTL_RETURN_INPUT, *PHV_VTL_RETURN_INPUT;

typedef union _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS
{
    HV_UINT32 MsrIndex;
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 Ecx;
    };
} HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS, *PHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;
typedef const HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS* PCHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

typedef struct _HV_LOGICAL_PROCESSOR_REGISTER_ID
{
    HV_UINT32 LpIndex;
    HV_LOGICAL_PROCESSOR_REGISTER_TYPE Type;
    HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS Address;
} HV_LOGICAL_PROCESSOR_REGISTER_ID, *PHV_LOGICAL_PROCESSOR_REGISTER_ID;
typedef const HV_LOGICAL_PROCESSOR_REGISTER_ID* PCHV_LOGICAL_PROCESSOR_REGISTER_ID;

typedef struct _HV_MCUPDATE_DATA_HEADER
{
    HV_UINT32 DataSize;
    HV_UINT32 TableOffset;
} HV_MCUPDATE_DATA_HEADER, *PHV_MCUPDATE_DATA_HEADER;

typedef struct _HV_BOOT_DEBUG_PARAMETERS
{
    HV_BOOT_DEBUG_PORT_TYPE PortType;
    HV_UINT64 TransferPagesSpa;
    HV_UINT32 TransferPagesCount;
    union
    {
        struct
        {
            HV_BOOT_DEBUG_COM_PORT_TYPE ComPortType;
            union
            {
                HV_UINT16 IoPort;
                HV_UINT64 RegistersSpa;
            };
            HV_UINT32 BaudRate;
        } Com;
        struct
        {
            HV_UINT32 Bus;
            HV_UINT32 Slot;
            HV_UINT16 Flags;
            HV_UINT8 HvChannelId;
            HV_UINT8 RootChannelId;
            HV_UINT64 OhciRegistersSpa;
        } Firewire;
        struct
        {
            HV_UINT32 Bus;
            HV_UINT32 Slot;
            HV_UINT32 HostIP;
            HV_UINT32 Flags;
            HV_UINT16 VendorID;
            HV_UINT16 DeviceID;
            HV_UINT16 HostHvPort;
            HV_UINT16 HostRootPort;
            HV_UINT64 Key[4];
            HV_UINT64 BaseAddressRegisterSPA[6];
            HV_UINT32 BaseAddressRegisterByteCount[6];
            HV_UINT16 BaseAddressRegisterType[6];
            HV_UINT32 KdNetDataSize;
        } Net;
    };
} HV_BOOT_DEBUG_PARAMETERS, *PHV_BOOT_DEBUG_PARAMETERS;

typedef struct _HV_BOOT_PARAMETERS
{
    HV_BOOT_DEBUG_PARAMETERS DebugParams;
    HV_UINT32 Flags;
} HV_BOOT_PARAMETERS, *PHV_BOOT_PARAMETERS;

typedef struct _HV_MINI_LOADER_BLOCK
{
    HV_UINT32 LoaderBlockSize;
    HV_UINT32 LoaderBlockVersion;
    HV_UINT64 LoaderBlockPhysicalAddress;
    HV_UINT64 HypervisorEntryPoint;
    HV_UINT64 HypervisorTransTabBasePhys;
    HV_BOOT_PARAMETERS BootParameters;
    HV_UINT32 RootPartitionProcessorCount;
    HV_UINT32 RootPartitionProcessorsContextsOffset;
    HV_UINT32 VpContextSize;
    HV_UINT32 MiniVpContextSize;
    HV_UINT32 HypervisorCrashdumpAreaPageCount;
    HV_UINT64 HypervisorCrashdumpAreaSpa;
    HV_UINT64 Below1MbPage;
} HV_MINI_LOADER_BLOCK, *PHV_MINI_LOADER_BLOCK;

typedef union _HV_CPU_MANAGEMENT_VERSION_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 VersionNumber : 8;
        HV_UINT64 RsvdZ : 54;
        HV_UINT64 Available : 1;
        HV_UINT64 Locked : 1;
    };
} HV_CPU_MANAGEMENT_VERSION_REGISTER, *PHV_CPU_MANAGEMENT_VERSION_REGISTER;

typedef union _HV_PCI_ID
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT16 Rid;
        HV_UINT16 Segment;
    };
    HV_PCI_BDF Bdf;
} HV_PCI_ID, *PHV_PCI_ID;

typedef union _HV_MCA_FAULTING_LP_MSR
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 LpIndex;
        HV_UINT32 Reserved;
    };
} HV_MCA_FAULTING_LP_MSR, *PHV_MCA_FAULTING_LP_MSR;

typedef struct _HV_DEVICE_PAGE_REQUEST
{
    HV_UINT32 DeviceId;
    HV_UINT32 Pasid : 20;
    HV_UINT32 Virtual : 1;
    HV_UINT32 GroupIndex : 9;
    HV_UINT32 LastInGroup : 1;
    HV_UINT32 StreamRequest : 1;
    HV_UINT64 Read : 1;
    HV_UINT64 Write : 1;
    HV_UINT64 Execute : 1;
    HV_UINT64 Privileged : 1;
    HV_UINT64 Reserved0 : 8;
    HV_UINT64 PageNumber : 52;
    HV_UINT64 Reserved1;
    union
    {
        struct
        {
            HV_UINT64 Reserved2 : 61;
            HV_UINT64 InvalidRequest : 1;
            HV_UINT64 ValidateGpa : 1;
            HV_UINT64 SendResponse : 1;
        };
        struct
        {
            HV_UINT64 : 63;
            HV_UINT64 Overflow : 1;
        };
    };
} HV_DEVICE_PAGE_REQUEST, *PHV_DEVICE_PAGE_REQUEST;

typedef struct _HV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED
{
    HV_UINT8 InterruptMasked;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_UINT32 Reserved2;
} HV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED, *PHV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED;

typedef struct _HV_X64_VOLATILE_GP_REGS
{
    HV_UINT64 Rax;
    HV_UINT64 Rcx;
    HV_UINT64 Rdx;
    HV_UINT64 R8;
    HV_UINT64 R9;
    HV_UINT64 R10;
    HV_UINT64 R11;
} HV_X64_VOLATILE_GP_REGS, *PHV_X64_VOLATILE_GP_REGS;

typedef struct _HV_PCI_PATH
{
    HV_UINT8 PathLength;
    HV_UINT16 Segment;
    HV_UINT8 StartBus;
    union
    {
        HV_UINT8 AsUINT8;
        struct
        {
            HV_UINT8 Function : 3;
            HV_UINT8 Device : 5;
        };
    } Path[];
} HV_PCI_PATH, *PHV_PCI_PATH;

typedef struct _HV_DEVICE_PRQ_HEADER
{
    HV_UINT32 Head;
    HV_UINT32 Tail;
    HV_UINT8 Pending;
    HV_UINT8 Stalled;
    HV_UINT8 Error;
} HV_DEVICE_PRQ_HEADER, *PHV_DEVICE_PRQ_HEADER;

// *****************************************************************************
// Hypervisor CPUID Definitions
//

// The below CPUID leaves are present if VersionAndFeatures.HypervisorPresent is
// set by CPUID(HvCpuIdFunctionVersionAndFeatures).
typedef enum _HV_CPUID_FUNCTION_PRIVATE
{
    // The remaining functions depend on the value of HvCpuIdFunctionInterface

    HvCpuIdFunctionMsHvPasidFeatures = 0x40000008,
    HvCpuIdFunctionMsHvIsolationConfiguration = 0x40000009,
    HvCpuidFunctionMsHvIptFeatures = 0x4000000B
} HV_CPUID_FUNCTION_PRIVATE, *PHV_CPUID_FUNCTION_PRIVATE;

#define HV_CPUID_HV_VENDOR_MICROSOFT "Microsoft Hv"
#define HV_CPUID_HV_VENDOR_MICROSOFT_EBX 'rciM'
#define HV_CPUID_HV_VENDOR_MICROSOFT_ECX 'foso'
#define HV_CPUID_HV_VENDOR_MICROSOFT_EDX 'vH t'

typedef enum _HV_HYPERVISOR_INTERFACE_PRIVATE
{
    HvMicrosoftXboxNanovisor = 'vnbX'
} HV_HYPERVISOR_INTERFACE_PRIVATE, *PHV_HYPERVISOR_INTERFACE_PRIVATE;

// Version info reported by both guest OS's and hypervisors
typedef enum _HV_SERVICE_BRANCH
{
    // [General Distribution Release (GDR) Branch]
    // This branch extends main releases and service pack releases with patches
    // that are generally distributed and recommended to all customers, such as
    // critical fixes.
    // Unmodified main releases and service pack releases are members of this
    // branch.
    HvServiceBranchGdr = 0x00000000,
    // [Quality Fix Engineering (QFE) Branch]
    // This branch extends main releases and service pack releases with patches
    // that are not generally distributed to all customers, such as feature
    // enhancements.
    HvServiceBranchQfe = 0x00000001
} HV_SERVICE_BRANCH, *PHV_SERVICE_BRANCH;

typedef struct _HV_X64_HYPERVISOR_FEATURES_PRIVATE
{
    HV_PARTITION_PRIVILEGE_MASK_PRIVATE PartitionPrivileges;
    HV_UINT32 Reserved0 : 5;
    HV_UINT32 InvariantMperfAvailable : 1;
    HV_UINT32 SupervisorShadowStackAvailable : 1;
    HV_UINT32 ArchPmuAvailable : 1;
    HV_UINT32 ExceptionTrapInterceptAvailable : 1;
    HV_UINT32 Reserved1 : 23;
    HV_UINT32 Reserved2 : 26;
    HV_UINT32 LbrAvailable : 1;
    HV_UINT32 IptAvailable : 1;
    HV_UINT32 CrossVtlFlushAvailable : 1;
    HV_UINT32 IdleSpecCtrlAvailable : 1;
    HV_UINT32 TranslateGvaFlagsAvailable : 1;
    HV_UINT32 ApicEoiInterceptAvailable : 1;
} HV_X64_HYPERVISOR_FEATURES_PRIVATE, *PHV_X64_HYPERVISOR_FEATURES_PRIVATE;

typedef struct _HV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE
{
    HV_UINT32 Reserved0 : 16;
    HV_UINT32 CoreSchedulerRequested : 1;
    HV_UINT32 Reserved1 : 1;
    HV_UINT32 NoNonArchitecturalCoreSharing : 1;
    HV_UINT32 UseX2Apic : 1;
    HV_UINT32 RestoreTimeOnResume : 1;
    HV_UINT32 UseHypercallForMmioAccess : 1;
    HV_UINT32 UseGpaPinningHypercall : 1;
    HV_UINT32 WakeVps : 1;
    HV_UINT32 Reserved : 8;
    HV_UINT32 Reserved2;
    HV_UINT32 ImplementedPhysicalAddressBits : 7;
    HV_UINT32 ReservedEcx : 25;
    HV_UINT32 ReservedEdx;
} HV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE, *PHV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE;

typedef struct _HV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE
{
    HV_UINT32 Reserved0 : 18;
    HV_UINT32 L3CachePartitioningSupported : 1;
    HV_UINT32 L3CacheMonitoringSupported : 1;
    HV_UINT32 Reserved1 : 7;
    HV_UINT32 HardwareGpaAccessTrackingSupported : 1;
    HV_UINT32 Reserved2 : 4;
    HV_UINT32 ReservedEbx;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE, *PHV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;

typedef struct _HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE
{
    HV_UINT32 ReservedEax;
    HV_UINT32 Reserved0 : 3;
    HV_UINT32 DriveIdleTransitions : 1;
    HV_UINT32 Reserved1 : 28;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE, *PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;

typedef struct _HV_HYPERVISOR_PASID_FEATURES
{
    HV_UINT32 Reserved0 : 1;
    HV_UINT32 PasidSupported : 1;
    HV_UINT32 Reserved1 : 30;
    HV_UINT32 MaxDevicePrqSize;
    HV_UINT32 Reserved2;
    HV_UINT32 Reserved3;
} HV_HYPERVISOR_PASID_FEATURES, *PHV_HYPERVISOR_PASID_FEATURES;

// Merged definitions from Hypervisor Top Level Functional Specification 6.0b
// and Build 26063 kdhv.lib debug symbol from Microsoft
typedef struct _HV_HYPERVISOR_ISOLATION_CONFIGURATION_PRIVATE
{
    HV_UINT32 Reserved00 : 1;
    HV_UINT32 Reserved01 : 1; // Merged Result
    HV_UINT32 AccessSynicRegs : 1; // TLFS
    HV_UINT32 Reserved02 : 1; // TLFS
    HV_UINT32 AccessIntrCtrlRegs : 1; // TLFS
    HV_UINT32 AccessHypercallMsrs : 1; // TLFS
    HV_UINT32 AccessVpIndex : 1; // TLFS
    HV_UINT32 Reserved03 : 5; // TLFS
    HV_UINT32 AccessReenlightenmentControls : 1; // TLFS
    HV_UINT32 Reserved04 : 19; // TLFS
    HV_UINT32 Reserved1;
    HV_UINT32 Reserved2; // Symbol (Renamed)
    HV_UINT32 Reserved30 : 4; // TLFS
    HV_UINT32 XmmRegistersForFastHypercallAvailable : 1; // TLFS
    HV_UINT32 Reserved31 : 10; // TLFS
    HV_UINT32 FastHypercallOutputAvailable : 1; // TLFS
    HV_UINT32 Reserved32 : 1; // TLFS
    HV_UINT32 SintPollingModeAvailable : 1; // TLFS
    HV_UINT32 Reserved33 : 14; // TLFS
} HV_HYPERVISOR_ISOLATION_CONFIGURATION_PRIVATE, *PHV_HYPERVISOR_ISOLATION_CONFIGURATION_PRIVATE;

typedef struct _HV_HYPERVISOR_NESTED_VIRT_FEATURES_PRIVATE
{
    HV_UINT32 Reserved0 : 21;
    HV_UINT32 DebugCtl : 1;
    HV_UINT32 EnlightenedNptTlb : 1;
    HV_UINT32 NoRmpTableRequired : 1;
    HV_UINT32 EnlightenedSevSwap : 1;
    HV_UINT32 Reserved1 : 7;
    HV_UINT32 PerfGlobalCtrl : 1;
    HV_UINT32 Reserved2 : 31;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_HYPERVISOR_NESTED_VIRT_FEATURES_PRIVATE, *PHV_HYPERVISOR_NESTED_VIRT_FEATURES_PRIVATE;

typedef struct _HV_HYPERVISOR_IPT_FEATURES
{
    HV_UINT32 ChainedToPA : 1;
    HV_UINT32 Enlightened : 1;
    HV_UINT32 Reserved0 : 10;
    HV_UINT32 MaxTraceBufferSizePerVtl : 20;
    HV_UINT32 Reserved1;
    HV_UINT32 Reserved2;
    HV_UINT32 HypervisorIpt : 1;
    HV_UINT32 Reserved3 : 31;
} HV_HYPERVISOR_IPT_FEATURES, *PHV_HYPERVISOR_IPT_FEATURES;

typedef union _HV_CPUID_RESULT_PRIVATE
{
    HV_X64_HYPERVISOR_FEATURES_PRIVATE MsHvFeatures;
    HV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE MsHvEnlightenmentInformation;
    HV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE MsHvHardwareFeatures;
    HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE MsHvCpuManagementFeatures;
    HV_HYPERVISOR_PASID_FEATURES MsHvPasidFeatures;
    HV_HYPERVISOR_ISOLATION_CONFIGURATION_PRIVATE MsHvIsolationConfiguration;
    HV_HYPERVISOR_NESTED_VIRT_FEATURES_PRIVATE MsHvNestedVirtFeatures;
    HV_HYPERVISOR_IPT_FEATURES MsHvIptFeatures;
} HV_CPUID_RESULT_PRIVATE, *PHV_CPUID_RESULT_PRIVATE;

typedef union _HV_LOGICAL_PROCESSOR_REGISTER_VALUE
{
    HV_UINT128 Reg128;
    HV_UINT64 Reg64;
    HV_UINT32 Reg32;
    HV_UINT16 Reg16;
    HV_UINT8 Reg8;
    HV_CPUID_RESULT Cpuid;
} HV_LOGICAL_PROCESSOR_REGISTER_VALUE, *PHV_LOGICAL_PROCESSOR_REGISTER_VALUE;
typedef const HV_LOGICAL_PROCESSOR_REGISTER_VALUE* PCHV_LOGICAL_PROCESSOR_REGISTER_VALUE;

typedef struct _HV_LOGICAL_PROCESSOR_REGISTER_ASSOC
{
    HV_LOGICAL_PROCESSOR_REGISTER_ID Id;
    HV_LOGICAL_PROCESSOR_REGISTER_VALUE Value;
} HV_LOGICAL_PROCESSOR_REGISTER_ASSOC, *PHV_LOGICAL_PROCESSOR_REGISTER_ASSOC;
typedef const HV_LOGICAL_PROCESSOR_REGISTER_ASSOC* PCHV_LOGICAL_PROCESSOR_REGISTER_ASSOC;

// *****************************************************************************
// Hypervisor MSRs Definitions
//

typedef enum _HV_X64_SYNTHETIC_MSR_PRIVATE
{
    XbSyntheticMsrDebugOutput = 0x4000000A,
    XbSyntheticMsrFlushTbThreshold = 0x4000000B,
    XbSyntheticMsrOsFlavor = 0x4000000C,
    XbSyntheticMsrOsFrameOffset = 0x4000000E,
    XbSyntheticMsrClearSignaturePage = 0x40000018,
    XbSyntheticMsrPauseElementsCount = 0x40000019,
    XbSyntheticMsrTbFlushAll = 0x4000001A,
    XbSyntheticMsrUtcFields = 0x40000045,
    HvSyntheticMsrVpConfig = 0x40000117,
    HvSyntheticMsrTscInvariantControl = 0x40000118,
    XbSyntheticMsrBootInfo = 0x40000130,
} HV_X64_SYNTHETIC_MSR_PRIVATE, *PHV_X64_SYNTHETIC_MSR_PRIVATE;

// MSR used to provide vcpu index

#define HV_X64_MSR_VP_INDEX HvSyntheticMsrVpIndex

typedef const HV_VP_INDEX* PCHV_VP_INDEX;

typedef union _HV_X64_MSR_SYNMC_STATUS_CONTENTS
{
    HV_UINT64 AsUINT64;

    struct
    {
        HV_UINT16 McaErrorCode;
        union
        {
            HV_UINT16 ModelSpecificErrorCode;
            struct
            {
                HV_UINT16 ErrorDetail : 14;
                HV_UINT16 HypervisorError : 1;
                HV_UINT16 SoftwareError : 1;
            };
        };
        struct
        {
            HV_UINT32 Reserved : 23;
            HV_UINT32 ActionRequired : 1;
            HV_UINT32 Signaling : 1;
            // Hypervisor/virt stack context corrupt
            HV_UINT32 ContextCorrupt : 1;
            HV_UINT32 AddressValid : 1;
            HV_UINT32 MiscValid : 1;
            HV_UINT32 ErrorEnabled : 1;
            // Uncorrected error
            HV_UINT32 Uncorrected : 1;
            // Error overflow
            HV_UINT32 Overflow : 1;
            // Register valid
            HV_UINT32 Valid : 1;
        };
    };
} HV_X64_MSR_SYNMC_STATUS_CONTENTS, *PHV_X64_MSR_SYNMC_STATUS_CONTENTS;

#define HV_SYNMC_MCA_ERROR_CODE (0x0001) // Unclassified error

typedef HV_UINT64 HV_X64_MSR_SYNMC_ADDR_CONTENTS;
typedef HV_UINT64 HV_X64_MSR_SYNMC_MISC_CONTENTS;

typedef HV_X64_MSR_SYNMC_ADDR_CONTENTS *PHV_X64_MSR_SYNMC_ADDR_CONTENTS;
typedef HV_X64_MSR_SYNMC_MISC_CONTENTS *PHV_X64_MSR_SYNMC_MISC_CONTENTS;

typedef struct _HV_SYNMC_X64_EVENT
{
    HV_X64_MSR_SYNMC_STATUS_CONTENTS Status;
    HV_X64_MSR_SYNMC_ADDR_CONTENTS Addr;
    HV_X64_MSR_SYNMC_MISC_CONTENTS Misc;
    HV_BOOLEAN RipValid;
    HV_BOOLEAN EipValid;
} HV_SYNMC_X64_EVENT, *PHV_SYNMC_X64_EVENT;

// MSR used to reset the guest OS.

#define HV_X64_MSR_RESET HvSyntheticMsrReset

typedef union _HV_X64_MSR_RESET_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Reset : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_X64_MSR_RESET_CONTENTS, *PHV_X64_MSR_RESET_CONTENTS;

/* HvSyntheticMsrCpuMgmtVersion | 0x40000004 */
/* XbSyntheticMsrTbFlushHost | 0x40000006 */
/* XbSyntheticMsrTbFlush | 0x40000007 */
/* XbSyntheticMsrCrash | 0x40000008 */
/* XbSyntheticMsrGuestOsType | 0x40000009 */
/* XbSyntheticMsrDebugOutput | 0x4000000A */
/* XbSyntheticMsrFlushTbThreshold | 0x4000000B */
/* XbSyntheticMsrOsFlavor | 0x4000000C */
/* XbSyntheticMsrOsFrameOffset | 0x4000000E */

// MSR used to provide vcpu runtime in 100ns units

#define HV_X64_MSR_VP_RUNTIME HvSyntheticMsrVpRuntime

/* XbSyntheticMsrRefTimeOffset | 0x40000011 */
/* XbSyntheticMsrRefTscScale | 0x40000012 */
/* XbSyntheticMsrVpCount | 0x40000013 */
/* XbSyntheticMsrWbinvd | 0x40000014 */
/* XbSyntheticMsrFlushWb | 0x40000015 */
/* XbSyntheticMsrFlushTbCurrent | 0x40000016 */
/* XbSyntheticMsrKcfgDone | 0x40000017 */
/* XbSyntheticMsrClearSignaturePage | 0x40000018 */
/* XbSyntheticMsrPauseElementsCount | 0x40000019 */
/* XbSyntheticMsrTbFlushAll | 0x4000001A */

// MSR used to read the per-partition time reference counter

#define HV_X64_MSR_TIME_REF_COUNT HvSyntheticMsrTimeRefCount

// A partition's reference time stamp counter (TSC) page

#define HV_X64_MSR_REFERENCE_TSC HvSyntheticMsrReferenceTsc

typedef union _HV_X64_MSR_REFERENCE_TSC_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enable : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_X64_MSR_REFERENCE_TSC_CONTENTS, *PHV_X64_MSR_REFERENCE_TSC_CONTENTS;

// Define invalid and maximum values of the reference TSC sequence.
#define HV_REFERENCE_TSC_SEQUENCE_INVALID (0x00000000)

typedef struct _HV_REFERENCE_TSC_PAGE
{
    volatile HV_UINT32 TscSequence;
    HV_UINT32 Reserved1;
    volatile HV_UINT64 TscScale;
    volatile HV_INT64 TscOffset;
    HV_UINT64 Reserved2[509];
} HV_REFERENCE_TSC_PAGE, *PHV_REFERENCE_TSC_PAGE;

// MSR used to retrieve the TSC frequency

#define HV_X64_MSR_TSC_FREQUENCY HvSyntheticMsrTscFrequency

// MSR used to retrieve the local APIC timer frequency

#define HV_X64_MSR_APIC_FREQUENCY HvSyntheticMsrApicFrequency

// Non-Privileged Instruction Execution Prevention

#define HV_X64_MSR_NPIEP_CONFIG HvSyntheticMsrNpiepConfig

/* XbSyntheticMsrUtcFields | 0x40000045 */

// Define the virtual APIC registers

#define HV_X64_MSR_EOI HvSyntheticMsrEoi
#define HV_X64_MSR_ICR HvSyntheticMsrIcr
#define HV_X64_MSR_TPR HvSyntheticMsrTpr
#define HV_X64_MSR_VP_ASSIST_PAGE HvSyntheticMsrVpAssistPage

typedef enum _HV_VTL_ENTRY_REASON
{
    // This reason is reserved and is not used.
    HvVtlEntryReserved = 0,
    // Indicates entry due to a VTL call from a lower VTL.
    HvVtlEntryVtlCall = 1,
    // Indicates entry due to an interrupt targeted to the VTL.
    HvVtlEntryInterrupt = 2
} HV_VTL_ENTRY_REASON, *PHV_VTL_ENTRY_REASON;

typedef struct _HV_VP_VTL_CONTROL
{
    // The hypervisor updates the entry reason with an indication as to why the
    // VTL was entered on the virtual processor.
    HV_VTL_ENTRY_REASON EntryReason;
    // This flag determines whether the VINA interrupt line is asserted.
    union
    {
        HV_UINT8 AsUINT8;
        struct
        {
            HV_UINT8 VinaAsserted : 1;
            HV_UINT8 VinaReservedZ : 7;
        };
    } VinaStatus;
    HV_UINT8 ReservedZ00;
    HV_UINT16 ReservedZ01;
    // A guest updates the VtlReturn* fields to provide the register values to
    // restore on VTL return. The specific register values that are restored
    // will vary based on whether the VTL is 32-bit or 64-bit.
    union
    {
        struct
        {
            HV_UINT64 VtlReturnX64Rax;
            HV_UINT64 VtlReturnX64Rcx;
        };
        struct
        {
            HV_UINT32 VtlReturnX86Eax;
            HV_UINT32 VtlReturnX86Ecx;
            HV_UINT32 VtlReturnX86Edx;
            HV_UINT32 ReservedZ1;
        };
    };
} HV_VP_VTL_CONTROL, *PHV_VP_VTL_CONTROL;

// Control structure that allows a hypervisor to indicate to its parent
// hypervisor which nested enlightenment privileges are to be granted to the
// current nested guest context.
typedef struct _HV_NESTED_ENLIGHTENMENTS_CONTROL
{
    union
    {
        HV_UINT32 AsUINT32;
        struct
        {
            HV_UINT32 DirectHypercall : 1;
            HV_UINT32 VirtualizationException : 1;
            HV_UINT32 Reserved : 30;
        };
    } Features;
    union
    {
        HV_UINT32 AsUINT32;
        struct
        {
            HV_UINT32 InterPartitionCommunication : 1;
            HV_UINT32 Reserved : 31;
        };
    } HypercallControls;
} HV_NESTED_ENLIGHTENMENTS_CONTROL, *PHV_NESTED_ENLIGHTENMENTS_CONTROL;

// The virtualization fault information area contains the current fault code and
// fault parameters for the VP. It is 16 byte aligned.
// It's 40 bytes according to MIT-licensed Hyper-V headers from Microsoft.
typedef struct _HV_VIRTUALIZATION_FAULT_INFORMATION
{
    HV_UINT16 Parameter0;
    HV_UINT16 Reserved0;
    HV_UINT32 Code;
    HV_UINT64 Parameter1;
    HV_UINT64 Parameter2; // Guess according to BugCheck
    HV_UINT64 Parameter3; // Guess according to BugCheck
    HV_UINT64 Parameter4; // Guess according to BugCheck
} HV_VIRTUALIZATION_FAULT_INFORMATION, *PHV_VIRTUALIZATION_FAULT_INFORMATION;

typedef union _HV_VP_ASSIST_PAGE
{
    struct
    {
        // APIC assist for optimized EOI processing.
        HV_VIRTUAL_APIC_ASSIST ApicAssist;
        HV_UINT32 ReservedZ0;
        // VP-VTL control information
        HV_VP_VTL_CONTROL VtlControl;
        HV_NESTED_ENLIGHTENMENTS_CONTROL NestedEnlightenmentsControl;
        HV_BOOLEAN EnlightenVmEntry;
        HV_UINT8 ReservedZ1[7];
        HV_GPA CurrentNestedVmcs;
        HV_BOOLEAN SyntheticTimeUnhaltedTimerExpired;
        HV_UINT8 ReservedZ2[7];
        // VirtualizationFaultInformation must be 16 byte aligned.
        HV_VIRTUALIZATION_FAULT_INFORMATION VirtualizationFaultInformation;
        HV_UINT8 ReservedZ3[8];
        HV_UINT8 InterceptMessage[256];
        HV_UINT8 VtlReturnActions[256];
    };
    HV_UINT8 ReservedZBytePadding[HV_PAGE_SIZE];
} HV_VP_ASSIST_PAGE, *PHV_VP_ASSIST_PAGE;

typedef union _HV_REGISTER_VP_ASSIST_PAGE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enable : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_REGISTER_VP_ASSIST_PAGE, *PHV_REGISTER_VP_ASSIST_PAGE;

// Define synthetic interrupt controller model specific registers.

#define HV_X64_MSR_SCONTROL HvSyntheticMsrSControl
#define HV_X64_MSR_SVERSION HvSyntheticMsrSVersion
#define HV_X64_MSR_SIEFP HvSyntheticMsrSiefp
#define HV_X64_MSR_SIMP HvSyntheticMsrSimp
#define HV_X64_MSR_EOM HvSyntheticMsrEom
#define HV_X64_MSR_SIRBP HvSyntheticMsrSirb
#define HV_X64_MSR_SINT0 HvSyntheticMsrSint0
#define HV_X64_MSR_SINT1 HvSyntheticMsrSint1
#define HV_X64_MSR_SINT2 HvSyntheticMsrSint2
#define HV_X64_MSR_SINT3 HvSyntheticMsrSint3
#define HV_X64_MSR_SINT4 HvSyntheticMsrSint4
#define HV_X64_MSR_SINT5 HvSyntheticMsrSint5
#define HV_X64_MSR_SINT6 HvSyntheticMsrSint6
#define HV_X64_MSR_SINT7 HvSyntheticMsrSint7
#define HV_X64_MSR_SINT8 HvSyntheticMsrSint8
#define HV_X64_MSR_SINT9 HvSyntheticMsrSint9
#define HV_X64_MSR_SINT10 HvSyntheticMsrSint10
#define HV_X64_MSR_SINT11 HvSyntheticMsrSint11
#define HV_X64_MSR_SINT12 HvSyntheticMsrSint12
#define HV_X64_MSR_SINT13 HvSyntheticMsrSint13
#define HV_X64_MSR_SINT14 HvSyntheticMsrSint14
#define HV_X64_MSR_SINT15 HvSyntheticMsrSint15

// Define SynIC control register.
typedef union _HV_SYNIC_SCONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enable : 1;
        HV_UINT64 Preserved : 63;
    };
} HV_SYNIC_SCONTROL, *PHV_SYNIC_SCONTROL;

// Synthetic Timer MSRs. Four timers per vcpu.

#define HV_X64_MSR_STIMER0_CONFIG HvSyntheticMsrSTimer0Config
#define HV_X64_MSR_STIMER0_COUNT HvSyntheticMsrSTimer0Count
#define HV_X64_MSR_STIMER1_CONFIG HvSyntheticMsrSTimer1Config
#define HV_X64_MSR_STIMER1_COUNT HvSyntheticMsrSTimer1Count
#define HV_X64_MSR_STIMER2_CONFIG HvSyntheticMsrSTimer2Config
#define HV_X64_MSR_STIMER2_COUNT HvSyntheticMsrSTimer2Count
#define HV_X64_MSR_STIMER3_CONFIG HvSyntheticMsrSTimer3Config
#define HV_X64_MSR_STIMER3_COUNT HvSyntheticMsrSTimer3Count

#if defined(_M_AMD64) || defined(_M_IX86)
#define HV_MSR_EOM HV_X64_MSR_EOM
#define HV_MSR_TIME_REF_COUNT HV_X64_MSR_TIME_REF_COUNT
#define HV_MSR_STIMER0_CONFIG HV_X64_MSR_STIMER0_CONFIG
#define HV_MSR_STIMER0_COUNT HV_X64_MSR_STIMER0_COUNT
#define HV_MSR_SIMP HV_X64_MSR_SIMP
#define HV_MSR_SINT0 HV_X64_MSR_SINT0
#elif defined(_M_ARM64)
#define HV_MSR_SINT0 HvRegisterSint0
#define HV_MSR_EOM HvRegisterEom
#define HV_MSR_TIME_REF_COUNT HvRegisterTimeRefCount
#define HV_MSR_STIMER0_CONFIG HvRegisterStimer0Config
#define HV_MSR_STIMER0_COUNT HvRegisterStimer0Count
#define HV_MSR_SIMP HvRegisterSipp
#endif

/* HvSyntheticMsrReserved400000C1 | 0x400000C1 */
/* HvSyntheticMsrGuestSchedulerEvent | 0x400000C2 */

// The following virtual MSRs are used to configure and trigger the C1-C3 power
// states.  Space is reserved for power states C4-C15 should they ever be
// defined by ACPI.

#define HV_X64_MSR_POWER_STATE_TRIGGER_C1   0x400000C1
#define HV_X64_MSR_POWER_STATE_TRIGGER_C2   0x400000C2
#define HV_X64_MSR_POWER_STATE_TRIGGER_C3   0x400000C3

// Reading from the trigger register takes the processor idle from the
// perspecive of the power management partition.  Upon wakeup the value returned
// contains information on the the idle operation attempted.
typedef union _HV_X64_MSR_POWER_STATE_TRIGGER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT8 IdleEntryCount;
        HV_UINT8 Reserved[3];
        HV_UINT32 Reserved2 : 31;
        HV_UINT32 ActiveBM_STS : 1;
    };
} HV_X64_MSR_POWER_STATE_TRIGGER, *PHV_X64_MSR_POWER_STATE_TRIGGER;

#define HV_X64_MSR_POWER_STATE_CONFIG_C1    0x400000D1
#define HV_X64_MSR_POWER_STATE_CONFIG_C2    0x400000D2
#define HV_X64_MSR_POWER_STATE_CONFIG_C3    0x400000D3

// This described a recipe to take the processor to a specific low power state.
typedef union _HV_X64_MSR_POWER_STATE_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 TypeSpecific : 52;
        HV_UINT64 ChangeType : 4; // use HV_X64_POWER_CHANGE_METHOD values
        HV_UINT64 CheckBM_STS : 1;
        HV_UINT64 SetBM_RST : 1;
        HV_UINT64 ClearBM_RST : 1;
        HV_UINT64 SetARB_DIS : 1;
        HV_UINT64 ReservedZ : 4;
    };
    struct
    {
        HV_UINT64 ReservedZ : 52;
    } Hlt;
    struct
    {
        HV_UINT16 Port;
        HV_UINT16 ReservedZ1;
        HV_UINT32 ReservedZ2 : 20;
    } Io;
    struct
    {
        HV_UINT64 Address : 52; // x64 has a 52 bit physical address space
    } Memory;
    struct
    {
        HV_UINT32 Hints;
        HV_UINT32 BreakOnMaskedInterrupt : 1;
        HV_UINT32 ReservedZ : 19;
    } Mwait;
} HV_X64_MSR_POWER_STATE_CONFIG, *PHV_X64_MSR_POWER_STATE_CONFIG;

// Hyper-V guest stats MSR's

#define HV_X64_MSR_STATS_PARTITION_RETAIL_PAGE 0x400000E0
#define HV_X64_MSR_STATS_PARTITION_INTERNAL_PAGE 0x400000E1
#define HV_X64_MSR_STATS_VP_RETAIL_PAGE 0x400000E2
#define HV_X64_MSR_STATS_VP_INTERNAL_PAGE 0x400000E3

// Define guest idle MSR. A guest virtual processor can enter idle state by
// reading this MSR, and will be waken up when an interrupt arrives regardless
// interrupt is enabled or not.
// N.B. The guest idle MSR is only used by guests to enter idle state. Root uses
//      the power trigger MSRs defined above to enter idle states.

#define HV_X64_MSR_GUEST_IDLE HvSyntheticMsrGuestIdle

/* HvSyntheticMsrSynthDebugControl | 0x400000F1 */
/* HvSyntheticMsrSynthDebugStatus | 0x400000F2 */
/* HvSyntheticMsrSynthDebugSendBuffer | 0x400000F3 */
/* HvSyntheticMsrSynthDebugReceiveBuffer | 0x400000F4 */
/* HvSyntheticMsrSynthDebugPendingBuffer | 0x400000F5 */
/* XbSyntheticMsrSynthDebugTransition | 0x400000F6 */
/* HvSyntheticMsrDebugDeviceOptions | 0x400000FF */

typedef union _HV_X64_MSR_SYNTH_DEBUG_BUFFER_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 ReservedZ0 : 12;
        HV_UINT64 GpaPageNumber : 40;
        HV_UINT64 ReservedZ1 : 11;
        HV_UINT64 Disabled : 1;
    };
} HV_X64_MSR_SYNTH_DEBUG_BUFFER_CONTENTS, *PHV_X64_MSR_SYNTH_DEBUG_BUFFER_CONTENTS;

// Hyper-V guest crash notification MSR's

#define HV_X64_MSR_CRASH_P0 HvSyntheticMsrCrashP0
#define HV_X64_MSR_CRASH_P1 HvSyntheticMsrCrashP1
#define HV_X64_MSR_CRASH_P2 HvSyntheticMsrCrashP2
#define HV_X64_MSR_CRASH_P3 HvSyntheticMsrCrashP3
#define HV_X64_MSR_CRASH_P4 HvSyntheticMsrCrashP4
#define HV_X64_MSR_CRASH_CTL HvSyntheticMsrCrashCtl

// TSC emulation after migration

#define HV_X64_MSR_REENLIGHTENMENT_CONTROL HvSyntheticMsrReenlightenmentControl
#define HV_X64_MSR_TSC_EMULATION_CONTROL HvSyntheticMsrTscEmulationControl
#define HV_X64_MSR_TSC_EMULATION_STATUS HvSyntheticMsrTscEmulationStatus

typedef union _HV_REENLIGHTENMENT_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Vector : 8;
        HV_UINT64 RsvdZ1 : 8;
        HV_UINT64 Enabled : 1;
        HV_UINT64 RsvdZ2 : 15;
        HV_UINT64 TargetVp : 32;
    };
} HV_REENLIGHTENMENT_CONTROL, *PHV_REENLIGHTENMENT_CONTROL;

typedef union _HV_TSC_EMULATION_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 RsvdZ : 63;
    };
} HV_TSC_EMULATION_CONTROL, *PHV_TSC_EMULATION_CONTROL;

typedef union _HV_TSC_EMULATION_STATUS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 InProgress : 1;
        HV_UINT64 RsvdP1 : 63;
    };
} HV_TSC_EMULATION_STATUS, *PHV_TSC_EMULATION_STATUS;

/* HvSyntheticMsrSWatchdogConfig | 0x40000110 */
/* HvSyntheticMsrSWatchdogCount | 0x40000111 */
/* HvSyntheticMsrSWatchdogStatus | 0x40000112 */

// Synthetic Time-Unhalted Timer MSRs

#define HV_X64_MSR_STIME_UNHALTED_TIMER_CONFIG HvSyntheticMsrSTimeUnhaltedTimerConfig
#define HV_X64_MSR_STIME_UNHALTED_TIMER_COUNT HvSyntheticMsrSTimeUnhaltedTimerCount

/* HvSyntheticMsrMemoryZeroingControl | 0x40000116 */
/* HvSyntheticMsrVpConfig | 0x40000117 */

// TSC invariant control

#define HV_X64_MSR_TSC_INVARIANT_CONTROL HvSyntheticMsrTscInvariantControl

/* XbSyntheticMsrFsBase | 0x40000122 */
/* XbSyntheticMsrXOnly | 0x40000123 */
/* XbSyntheticMsrBootInfo | 0x40000130 */
/* HvSyntheticMsrBelow1MbPage | 0x40000200 */

// Define synthetic interrupt controller model specific registers for nested
// hypervisor

/* HvSyntheticMsrNestedVpIndex | 0x40001002 */
#define HV_X64_MSR_NESTED_SCONTROL HvSyntheticMsrNestedSControl
#define HV_X64_MSR_NESTED_SVERSION HvSyntheticMsrNestedSVersion
#define HV_X64_MSR_NESTED_SIEFP HvSyntheticMsrNestedSiefp
#define HV_X64_MSR_NESTED_SIMP HvSyntheticMsrNestedSimp
#define HV_X64_MSR_NESTED_EOM HvSyntheticMsrNestedEom
/* HvSyntheticMsrNestedSirb | 0x40001085 */
#define HV_X64_MSR_NESTED_SINT0 HvSyntheticMsrNestedSint0
#define HV_X64_MSR_NESTED_SINT1 HvSyntheticMsrNestedSint1
#define HV_X64_MSR_NESTED_SINT2 HvSyntheticMsrNestedSint2
#define HV_X64_MSR_NESTED_SINT3 HvSyntheticMsrNestedSint3
#define HV_X64_MSR_NESTED_SINT4 HvSyntheticMsrNestedSint4
#define HV_X64_MSR_NESTED_SINT5 HvSyntheticMsrNestedSint5
#define HV_X64_MSR_NESTED_SINT6 HvSyntheticMsrNestedSint6
#define HV_X64_MSR_NESTED_SINT7 HvSyntheticMsrNestedSint7
#define HV_X64_MSR_NESTED_SINT8 HvSyntheticMsrNestedSint8
#define HV_X64_MSR_NESTED_SINT9 HvSyntheticMsrNestedSint9
#define HV_X64_MSR_NESTED_SINT10 HvSyntheticMsrNestedSint10
#define HV_X64_MSR_NESTED_SINT11 HvSyntheticMsrNestedSint11
#define HV_X64_MSR_NESTED_SINT12 HvSyntheticMsrNestedSint12
#define HV_X64_MSR_NESTED_SINT13 HvSyntheticMsrNestedSint13
#define HV_X64_MSR_NESTED_SINT14 HvSyntheticMsrNestedSint14
#define HV_X64_MSR_NESTED_SINT15 HvSyntheticMsrNestedSint15

// *****************************************************************************
// Hypervisor Hypercall Definitions
//

typedef union _HV_HYPERCALL_INPUT_PRIVATE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 CallCode : 15;
        HV_UINT32 IsExtended : 1;
        HV_UINT32 IsFast : 1;
        HV_UINT32 VariableHeaderSize : 9;
        HV_UINT32 Reserved1 : 5;
        HV_UINT32 IsNested : 1;
        HV_UINT32 CountOfElements : 12;
        HV_UINT32 Reserved2 : 4;
        HV_UINT32 RepStartIndex : 12;
        HV_UINT32 Reserved3 : 4;
    };
} HV_HYPERCALL_INPUT_PRIVATE, *PHV_HYPERCALL_INPUT_PRIVATE;

// Declare the various hypercall operations
// Public: Have prototype definition in TLFS document
// Fast: Need to use Fast Hypercall calling convention
// Rep: Rep call a.k.a repeat call
// Reserved: Have mentioned reserved in TLFS document
// Undocumented: Undocumented but found in Microsoft documents and sources
// Symbols: Undocumented and only found in Windows Kit symbols
// Read References\HvCallList.xlsx in https://github.com/ProjectMile/Mile.HyperV
// for more information.
typedef enum _HV_CALL_CODE_PRIVATE
{
    HvCallSyncContext = 0x0019, // Symbols
    HvCallSyncContextEx = 0x001A, // Symbols
    HvCallSetPerfRegister = 0x001B, // Symbols
    HvCallGetPerfRegister = 0x001C, // Symbols
    HvCallFlushCache = 0x001D, // Symbols
    HvCallReserved0098 = 0x0098, // Reserved
    HvCallSignalEventDirect = 0x00C0, // Undocumented
    HvCallPostMessageDirect = 0x00C1, // Undocumented
    HvCallReserved00d5 = 0x00D5, // Symbols
    HvCallQueryDeviceInterruptTarget = 0x00E0, // Symbols
    HvCallMapVpStatePage = 0x00E1, // Undocumented
    HvCallUnmapVpStatePage = 0x00E2, // Undocumented
    HvCallGetVpState = 0x00E3, // Undocumented
    HvCallSetVpState = 0x00E4, // Undocumented
    HvCallGetVpSetFromMda = 0x00E5, // Symbols
    HvCallReserved00e6 = 0x00E6, // Symbols
    HvCallCreateIptBuffers = 0x00E7, // Symbols
    HvCallDeleteIptBuffers = 0x00E8, // Symbols
    HvCallControlHypervisorIptTrace = 0x00E9, // Symbols
    HvCallReserveDeviceInterrupt = 0x00EA, // Symbols
    HvCallPersistDevice = 0x00EB, // Symbols
    HvCallUnpersistDevice = 0x00EC, // Symbols
    HvCallPersistDeviceInterrupt = 0x00ED, // Symbols
    HvCallRefreshPerformanceCounters = 0x00EE, // Symbols
    HvCallImportIsolatedPages = 0x00EF, // Symbols
    HvCallReserved00f0 = 0x00F0, // Symbols
    HvCallCompleteIsolatedImport = 0x00F1, // Symbols
    HvCallIssueSnpPspGuestRequest = 0x00F2, // Symbols
    HvCallRootSignalEvent = 0x00F3, // Symbols
    HvCallGetVpCpuidValues = 0x00F4, // Undocumented
    HvCallReadSystemMemory = 0x00F5, // Symbols
    HvCallSetHwWatchdogConfig = 0x00F6, // Symbols
    HvCallRemovePhysicalMemory = 0x00F7, // Symbols
    HvCallLogHypervisorSystemConfig = 0x00F8, // Symbols
    HvCallIssueNestedSnpPspRequests = 0x00F9, // Symbols
    HvCallReserved00fa = 0x00FA, // Symbols
    HvCallSubsumeInitializedMemory = 0x00FB, // Symbols
    HvCallSubsumeVp = 0x00FC, // Symbols
    HvCallDestroySubsumedContext = 0x00FD, // Symbols
    HvCallWriteSysDiagEvent = 0x00FE, // Symbols
    HvCallDepositMemoryMirroring = 0x00FF, // Symbols
    HvCallSetDeviceCapabilities = 0x0100, // Symbols
    HvCallGetPartitionPropertyEx = 0x0101, // Symbols
    HvCallGetGpaRangesAccessState = 0x0102, // Symbols
    HvCallRestorePartitionTime = 0x0103, // Symbols
    HvCallQueryAssociatedLpsForMcaEx = 0x0104, // Symbols
    HvCallQueryPartitionReservedPages = 0x0105, // Symbols
    HvCallMemoryMappedIoRead = 0x0106, // Symbols
    HvCallMemoryMappedIoWrite = 0x0107, // Symbols
    HvCallMapDmaRange = 0x0108, // Symbols
    HvCallUnmapDmaRange = 0x0109, // Symbols
    HvCallSetPartitionPropertyEx = 0x010A, // Symbols
    HvCallAttachDevicePrQueue = 0x010B, // Symbols
    HvCallDetachDevicePrQueue = 0x010C, // Symbols
    HvCallReserveDeviceDomainAttachment = 0x010D, // Symbols
    HvCallUnreserveDeviceDomainAttachment = 0x010E, // Symbols
    HvCallDisableHypervisorEx = 0x010F, // Symbols
    HvCallInstallInterceptEx = 0x0110, // Symbols
    HvCallMapVpStatePageEx = 0x0111, // Symbols
    HvCallPinGpaPageRanges = 0x0112, // Symbols
    HvCallUnpinGpaPageRanges = 0x0113, // Symbols
    HvCallWakeVps = 0x0114, // Symbols
    HvCallSetCpuGroupAffinity = 0x0115, // Symbols
    HvCallMapPartitionEventLogBuffer = 0x0116, // Symbols
    HvCallPrivateCount
} HV_CALL_CODE_PRIVATE, *PHV_CALL_CODE_PRIVATE;

// Type of Normal Hypercall and Fast Hypercall calling convention.
// - Normal Hypercall
//   - HypercallParameter1: The guest physical addresses of input parameters.
//   - HypercallParameter2: The guest physical addresses of output parameters.
// - Fast Hypercall
//   - HypercallParameter1: The content of input parameters 1.
//   - HypercallParameter2: The content of input parameters 2.
typedef HV_HYPERCALL_OUTPUT(*PHVCALL_HYPERCALL_ROUTINE)(
    HV_HYPERCALL_INPUT HypercallInput,
    HV_UINT64 HypercallParameter1,
    HV_UINT64 HypercallParameter2);

// Type of XMM Fast Hypercall (Extended Fast Hypercall) calling convention
// typedef HV_HYPERCALL_OUTPUT(*__vectorcall PHVCALL_XMM_HYPERCALL_ROUTINE)(
//     HV_HYPERCALL_INPUT HypercallInput,
//     HV_UINT64 Parameter1,
//     HV_UINT64 Parameter2,
//     __m128 Parameter3,
//     __m128 Parameter4,
//     __m128 Parameter5,
//     __m128 Parameter6,
//     __m128 Parameter7,
//     __m128 Parameter8);

// HvCallReserved0000 | 0x0000

// HvCallSwitchVirtualAddressSpace | 0x0001

// Already defined in Mile.HyperV.Guest.Interface.h.

// HvCallFlushVirtualAddressSpace | 0x0002

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE
{
    HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER Header;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE;

// HvCallFlushVirtualAddressList | 0x0003

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST
{
    HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER Header;
    HV_GVA GvaList[];
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST;

// HvCallGetLogicalProcessorRunTime | 0x0004

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_LOGICAL_PROCESSOR_RUN_TIME
{
    HV_UINT32 LpIndex;
} HV_INPUT_GET_LOGICAL_PROCESSOR_RUN_TIME, *PHV_INPUT_GET_LOGICAL_PROCESSOR_RUN_TIME;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME
{
    HV_NANO100_TIME GlobalTime;
    HV_NANO100_TIME LocalRunTime;
    HV_UINT64 RsvdZ;
    HV_NANO100_TIME HypervisorTime;
} HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME, *PHV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME;

// HvCallUpdateHvProcessorFeatures | 0x0005
// HvCallSwitchAliasMap | 0x0006
// HvCallUpdateMicrocode | 0x0007

// HvCallNotifyLongSpinWait | 0x0008

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_NOTIFY_LONG_SPINWAIT
{
    HV_UINT32 InitialLongSpinWait;
    HV_UINT32 Padding;
} HV_INPUT_NOTIFY_LONG_SPINWAIT, *PHV_INPUT_NOTIFY_LONG_SPINWAIT;

// HvCallParkedVirtualProcessors | 0x0009

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PARK_LOGICAL_PROCESSORS
{
    HV_UINT64 ProcessorMask;
} HV_INPUT_PARK_LOGICAL_PROCESSORS, *PHV_INPUT_PARK_LOGICAL_PROCESSORS;

// HvCallInvokeHypervisorDebugger | 0x000A

#define HV_DEBUG_INVOKE_REASON_CLOCK_WATCHDOG 0x01
#define HV_DEBUG_INVOKE_REASON_DPC_WATCHDOG 0x02
#define HV_DEBUG_INVOKE_REASON_DPC_TIMEOUT 0x03

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INVOKE_HYPERVISOR_DEBUGGER
{
    HV_UINT64 Reason;
    HV_UINT64 SupplementalCode;
} HV_INPUT_INVOKE_HYPERVISOR_DEBUGGER, *PHV_INPUT_INVOKE_HYPERVISOR_DEBUGGER;

// HvCallSendSyntheticClusterIpi | 0x000B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SEND_SYNTHETIC_CLUSTER_IPI
{
    HV_INTERRUPT_VECTOR Vector;
    HV_INPUT_VTL TargetVtl;
    HV_UINT8 RsvdZ0;
    HV_UINT16 RsvdZ1;
    HV_UINT64 ProcessorMask;
} HV_INPUT_SEND_SYNTHETIC_CLUSTER_IPI, *PHV_INPUT_SEND_SYNTHETIC_CLUSTER_IPI;

// HvCallModifyVtlProtectionMask | 0x000C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MODIFY_VTL_PROTECTION_MASK
{
    HV_PARTITION_ID TargetPartitionId;
    HV_MAP_GPA_FLAGS MapFlags;
    HV_INPUT_VTL TargetVtl;
    HV_UINT8 RsvdZ8;
    HV_UINT16 RsvdZ16;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_MODIFY_VTL_PROTECTION_MASK, *PHV_INPUT_MODIFY_VTL_PROTECTION_MASK;

// HvCallEnablePartitionVtl | 0x000D

typedef union _HV_ENABLE_PARTITION_VTL_FLAGS
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 EnableMbec : 1;
        HV_UINT8 Reserved : 7;
    };
} HV_ENABLE_PARTITION_VTL_FLAGS, *PHV_ENABLE_PARTITION_VTL_FLAGS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ENABLE_PARTITION_VTL
{
    HV_PARTITION_ID TargetPartitionId;
    HV_VTL TargetVtl;
    HV_ENABLE_PARTITION_VTL_FLAGS Flags;
    HV_UINT16 ReservedZ0;
    HV_UINT32 ReservedZ1;
} HV_INPUT_ENABLE_PARTITION_VTL, *PHV_INPUT_ENABLE_PARTITION_VTL;

// HvCallDisablePartitionVtl | 0x000E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISABLE_PARTITION_VTL
{
    HV_PARTITION_ID PartitionId;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
    HV_UINT32 ReservedZ2;
} HV_INPUT_DISABLE_PARTITION_VTL, *PHV_INPUT_DISABLE_PARTITION_VTL;

// HvCallEnableVpVtl | 0x000F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ENABLE_VP_VTL
{
    HV_PARTITION_ID TargetPartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
    HV_INITIAL_VP_CONTEXT VpVtlContext;
} HV_INPUT_ENABLE_VP_VTL, *PHV_INPUT_ENABLE_VP_VTL;

// HvCallDisableVpVtl | 0x0010

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISABLE_VP_VTL
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
} HV_INPUT_DISABLE_VP_VTL, *PHV_INPUT_DISABLE_VP_VTL;

// HvCallVtlCall | 0x0011

/* This hypercall doesn't have input and output parameters. */

// HvCallVtlReturn | 0x0012

/* This hypercall doesn't have input and output parameters. */

// HvCallFlushVirtualAddressSpaceEx | 0x0013

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_EX
{
    HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER_EX Header;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_EX, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_EX;

// HvCallFlushVirtualAddressListEx | 0x0014

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST_EX
{
    HV_INPUT_FLUSH_VIRTUAL_ADDRESS_SPACE_HEADER_EX Header;
} HV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST_EX, *PHV_INPUT_FLUSH_VIRTUAL_ADDRESS_LIST_EX;

// HvCallSendSyntheticClusterIpiEx | 0x0015

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SEND_SYNTHETIC_CLUSTER_IPI_EX
{
    HV_INTERRUPT_VECTOR Vector;
    HV_INPUT_VTL TargetVtl;
    HV_UINT8 RsvdZ0;
    HV_UINT16 RsvdZ1;
    HV_GENERIC_SET ProcessorSet;
} HV_INPUT_SEND_SYNTHETIC_CLUSTER_IPI_EX, *PHV_INPUT_SEND_SYNTHETIC_CLUSTER_IPI_EX;

// HvCallQueryImageInfo | 0x0016
// HvCallMapImagePages | 0x0017
// HvCallCommitPatch | 0x0018
// HvCallSyncContext | 0x0019
// HvCallSyncContextEx | 0x001A
// HvCallSetPerfRegister | 0x001B
// HvCallGetPerfRegister | 0x001C
// HvCallFlushCache | 0x001D
// HvCallReserved001e | 0x001E
// HvCallReserved001f | 0x001F
// HvCallReserved0020 | 0x0020
// HvCallReserved0021 | 0x0021
// HvCallReserved0022 | 0x0022
// HvCallReserved0023 | 0x0023
// HvCallReserved0024 | 0x0024
// HvCallReserved0025 | 0x0025
// HvCallReserved0026 | 0x0026
// HvCallReserved0027 | 0x0027
// HvCallReserved0028 | 0x0028
// HvCallReserved0029 | 0x0029
// HvCallReserved002a | 0x002A
// HvCallReserved002b | 0x002B
// HvCallReserved002c | 0x002C
// HvCallReserved002d | 0x002D
// HvCallReserved002e | 0x002E
// HvCallReserved002f | 0x002F
// HvCallReserved0030 | 0x0030
// HvCallReserved0031 | 0x0031
// HvCallReserved0032 | 0x0032
// HvCallReserved0033 | 0x0033
// HvCallReserved0034 | 0x0034
// HvCallReserved0035 | 0x0035
// HvCallReserved0036 | 0x0036
// HvCallReserved0037 | 0x0037
// HvCallReserved0038 | 0x0038
// HvCallReserved0039 | 0x0039
// HvCallReserved003a | 0x003A
// HvCallReserved003b | 0x003B
// HvCallReserved003c | 0x003C
// HvCallReserved003d | 0x003D
// HvCallReserved003e | 0x003E
// HvCallReserved003f | 0x003F

// HvCallCreatePartition | 0x0040

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PARTITION
{
    HV_UINT64 Flags;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_UINT32 CompatibilityVersion;
    HV_UINT32 Padding;
    HV_PARTITION_CREATION_PROPERTIES PartitionCreationProperties;
    HV_PARTITION_ISOLATION_PROPERTIES IsolationProperties;
} HV_INPUT_CREATE_PARTITION, *PHV_INPUT_CREATE_PARTITION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_CREATE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_OUTPUT_CREATE_PARTITION, *PHV_OUTPUT_CREATE_PARTITION;

// HvCallInitializePartition | 0x0041

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INITIALIZE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_INITIALIZE_PARTITION, *PHV_INPUT_INITIALIZE_PARTITION;

// HvCallFinalizePartition | 0x0042

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FINALIZE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_FINALIZE_PARTITION, *PHV_INPUT_FINALIZE_PARTITION;

// HvCallDeletePartition | 0x0043

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_DELETE_PARTITION, *PHV_INPUT_DELETE_PARTITION;

// HvCallGetPartitionProperty | 0x0044

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PARTITION_PROPERTY
{
    HV_PARTITION_ID PartitionId;
    HV_PARTITION_PROPERTY_CODE PropertyCode;
    HV_UINT32 Padding;
} HV_INPUT_GET_PARTITION_PROPERTY, *PHV_INPUT_GET_PARTITION_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PARTITION_PROPERTY
{
    HV_PARTITION_PROPERTY PropertyValue;
} HV_OUTPUT_GET_PARTITION_PROPERTY, *PHV_OUTPUT_GET_PARTITION_PROPERTY;

// HvCallSetPartitionProperty | 0x0045

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PARTITION_PROPERTY
{
    HV_PARTITION_ID PartitionId;
    HV_PARTITION_PROPERTY_CODE PropertyCode;
    HV_PARTITION_PROPERTY PropertyValue;
} HV_INPUT_SET_PARTITION_PROPERTY, *PHV_INPUT_SET_PARTITION_PROPERTY;

// HvCallGetPartitionId | 0x0046

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PARTITION_ID
{
    HV_PARTITION_ID PartitionId;
} HV_OUTPUT_GET_PARTITION_ID, *PHV_OUTPUT_GET_PARTITION_ID;

// HvCallGetNextChildPartition | 0x0047

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_NEXT_CHILD_PARTITION
{
    HV_PARTITION_ID ParentId;
    HV_PARTITION_ID PreviousChildId;
} HV_INPUT_GET_NEXT_CHILD_PARTITION, *PHV_INPUT_GET_NEXT_CHILD_PARTITION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_NEXT_CHILD_PARTITION
{
    HV_PARTITION_ID NextChildId;
} HV_OUTPUT_GET_NEXT_CHILD_PARTITION, *PHV_OUTPUT_GET_NEXT_CHILD_PARTITION;

// HvCallDepositMemory | 0x0048

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DEPOSIT_MEMORY
{
    // Supplies the partition ID of the child partition to deposit the memory
    // into.
    HV_PARTITION_ID PartitionId;
    // Supplies the GPAs of the pages to be deposited.
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_DEPOSIT_MEMORY, *PHV_INPUT_DEPOSIT_MEMORY;

// HvCallWithdrawMemory | 0x0049

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_WITHDRAW_MEMORY
{
    // Supplies the partition ID of the child partition from which the memory
    // should be withdrawn.
    HV_PARTITION_ID PartitionId;
    // Supplies the proximity domain from which the memory should be allocated.
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INPUT_WITHDRAW_MEMORY, *PHV_INPUT_WITHDRAW_MEMORY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_WITHDRAW_MEMORY
{
    // Returns the GPA of the memory withdrawn.
    HV_GPA_PAGE_NUMBER GpaPageList[HV_ANYSIZE_ARRAY];
} HV_OUTPUT_WITHDRAW_MEMORY, *PHV_OUTPUT_WITHDRAW_MEMORY;

// HvCallGetMemoryBalance | 0x004A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_MEMORY_BALANCE
{
    // Supplies the partition ID of the child partition whose memory pool should
    // be queried.
    HV_PARTITION_ID PartitionId;
    // Supplies the proximity domain to query.
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INPUT_GET_MEMORY_BALANCE, *PHV_INPUT_GET_MEMORY_BALANCE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_MEMORY_BALANCE
{
    // Returns the number of pages available.
    HV_UINT64 PagesAvailable;
    // Returns the number of pages actively being used for hypercall data
    // structures.
    HV_UINT64 PagesInUse;
} HV_OUTPUT_GET_MEMORY_BALANCE, *PHV_OUTPUT_GET_MEMORY_BALANCE;

// HvCallMapGpaPages | 0x004B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_GPA_PAGES
{
    // Supplies the partition ID of the partition that this request is for.
    HV_PARTITION_ID TargetPartitionId;
    // Supplies the base guest physical page number where the mapping will
    // begin.
    HV_GPA_PAGE_NUMBER TargetGpaBase;
    // Supplies the flags to use for the mapping.
    HV_MAP_GPA_FLAGS MapFlags;
    // Supplies an array of guest physical page numbers in the calling
    // partition that the range of GPA will be mapped to.
    HV_GPA_PAGE_NUMBER SourceGpaPageList[];
} HV_INPUT_MAP_GPA_PAGES, *PHV_INPUT_MAP_GPA_PAGES;

// HvCallUnmapGpaPages | 0x004C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_GPA_PAGES
{
    // Supplies the partition ID of the partition that this request is for.
    HV_PARTITION_ID TargetPartitionId;
    // Supplies the base guest physical page number where the GPA space will be
    // removed.
    HV_GPA_PAGE_NUMBER TargetGpaBase;
    HV_UINT32 UnmapFlags;
    HV_UINT32 Padding;
} HV_INPUT_UNMAP_GPA_PAGES, *PHV_INPUT_UNMAP_GPA_PAGES;

// HvCallInstallIntercept | 0x004D

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INSTALL_INTERCEPT
{
    HV_PARTITION_ID PartitionId;
    HV_INTERCEPT_ACCESS_TYPE_MASK AccessType;
    HV_INTERCEPT_TYPE InterceptType;
    HV_INTERCEPT_PARAMETERS InterceptParameter;
} HV_INPUT_INSTALL_INTERCEPT, *PHV_INPUT_INSTALL_INTERCEPT;

// HvCallCreateVp | 0x004E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_UINT32 Padding;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_UINT64 Flags;
} HV_INPUT_CREATE_VP, *PHV_INPUT_CREATE_VP;

// HvCallDeleteVp | 0x004F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
} HV_INPUT_DELETE_VP, *PHV_INPUT_DELETE_VP;

// HvCallGetVpRegisters | 0x0050

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_REGISTERS
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_INPUT_VTL InputVtl;
    HV_UINT8 RsvdZ8;
    HV_UINT16 RsvdZ16;
    HV_REGISTER_NAME Names[];
} HV_INPUT_GET_VP_REGISTERS, *PHV_INPUT_GET_VP_REGISTERS;

typedef struct HV_CALL_ATTRIBUTES_ALIGNED(16) _HV_OUTPUT_GET_VP_REGISTERS
{
    HV_REGISTER_VALUE Values[HV_ANYSIZE_ARRAY];
} HV_OUTPUT_GET_VP_REGISTERS, *PHV_OUTPUT_GET_VP_REGISTERS;

// HvCallSetVpRegisters | 0x0051

typedef struct _HV_REGISTER_ASSOC
{
    HV_REGISTER_NAME Name;
    HV_UINT8 Pad[12];
    HV_REGISTER_VALUE Value;
} HV_REGISTER_ASSOC, *PHV_REGISTER_ASSOC;

typedef struct HV_CALL_ATTRIBUTES_ALIGNED(16) _HV_INPUT_SET_VP_REGISTERS
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_INPUT_VTL InputVtl;
    HV_UINT8 RsvdZ8;
    HV_UINT16 RsvdZ16;
    HV_REGISTER_ASSOC Elements[];
} HV_INPUT_SET_VP_REGISTERS, *PHV_INPUT_SET_VP_REGISTERS;

// HvCallTranslateVirtualAddress | 0x0052

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_TRANSLATE_VIRTUAL_ADDRESS
{
    // Supplies the partition ID of the partition in which the translation
    // should take place.
    HV_PARTITION_ID PartitionId;
    // Supplies the virtual processor whose GVA space is to be accessed.
    HV_VP_INDEX VpIndex;
    HV_UINT32 Padding;
    // Supplies the control flags governing the access.
    HV_TRANSLATE_GVA_CONTROL_FLAGS ControlFlags;
    // Supplies the GVA page number to translate.
    HV_GVA_PAGE_NUMBER GvaPage;
} HV_INPUT_TRANSLATE_VIRTUAL_ADDRESS, *PHV_INPUT_TRANSLATE_VIRTUAL_ADDRESS;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS
{
    // Flags to indicate the disposition of the translation.
    HV_TRANSLATE_GVA_RESULT TranslationResult;
    // The GPA to which the GVA translated.
    HV_GPA_PAGE_NUMBER GpaPage;
} HV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS, *PHV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS;

// HvCallReadGpa | 0x0053

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_READ_GPA
{
    // Supplies the partition ID of the partition whose GPA space is to be
    // read.
    HV_PARTITION_ID PartitionId;
    // Supplies the virtual processor whose GPA space is to be read (virtual
    // processor GPA spaces may differ, due to overlays).
    HV_VP_INDEX VpIndex;
    // Supplies the number of bytes to read.
    HV_UINT32 ByteCount;
    // Supplies the start of the GPA range to read.
    HV_GPA BaseGpa;
    // Supplies the control flags governing the read.
    HV_ACCESS_GPA_CONTROL_FLAGS ControlFlags;
} HV_INPUT_READ_GPA, *PHV_INPUT_READ_GPA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_READ_GPA
{
    // Flags to indicate the disposition of the read.
    HV_ACCESS_GPA_RESULT AccessResult;
    // The data which was read.
    HV_UINT8 Data[16];
} HV_OUTPUT_READ_GPA, *PHV_OUTPUT_READ_GPA;

// HvCallWriteGpa | 0x0054

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_WRITE_GPA
{
    // Supplies the partition ID of the partition whose GPA space is to be
    // written.
    HV_PARTITION_ID PartitionId;
    // Supplies the virtual processor whose GPA space is to be written (virtual
    // processor GPA spaces may differ, due to overlays).
    HV_VP_INDEX VpIndex;
    // Supplies the number of bytes to write.
    HV_UINT32 ByteCount;
    // Supplies the start of the GPA range to write.
    HV_GPA BaseGpa;
    // Supplies the control flags governing the write.
    HV_ACCESS_GPA_CONTROL_FLAGS ControlFlags;
    // Supplies the data to write.
    HV_UINT8 Data[16];
} HV_INPUT_WRITE_GPA, *PHV_INPUT_WRITE_GPA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_WRITE_GPA
{
    // Flags to indicate the disposition of the write.
    HV_ACCESS_GPA_RESULT AccessResult;
} HV_OUTPUT_WRITE_GPA, *PHV_OUTPUT_WRITE_GPA;

// HvCallAssertVirtualInterruptDeprecated | 0x0055

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ASSERT_VIRTUAL_INTERRUPT_DEPRECATED
{
    HV_PARTITION_ID TargetPartition;
    HV_INTERRUPT_CONTROL InterruptControl;
    HV_UINT64 DestinationAddress;
    HV_INTERRUPT_VECTOR RequestedVector;
    HV_UINT32 Reserved;
} HV_INPUT_ASSERT_VIRTUAL_INTERRUPT_DEPRECATED, *PHV_INPUT_ASSERT_VIRTUAL_INTERRUPT_DEPRECATED;

// HvCallClearVirtualInterrupt | 0x0056

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CLEAR_VIRTUAL_INTERRUPT
{
    HV_PARTITION_ID TargetPartition;
} HV_INPUT_CLEAR_VIRTUAL_INTERRUPT, *PHV_INPUT_CLEAR_VIRTUAL_INTERRUPT;

// HvCallCreatePortDeprecated | 0x0057

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PORT_DEPRECATED
{
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_UINT32 Padding;
    HV_PARTITION_ID ConnectionPartition;
    HV_PORT_INFO PortInfo;
} HV_INPUT_CREATE_PORT_DEPRECATED, *PHV_INPUT_CREATE_PORT_DEPRECATED;

// HvCallDeletePort | 0x0058

typedef union HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PORT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_PARTITION_ID PortPartition;
        HV_PORT_ID PortId;
        HV_UINT32 Reserved;
    };
} HV_INPUT_DELETE_PORT, *PHV_INPUT_DELETE_PORT;

// HvCallConnectPortDeprecated | 0x0059

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CONNECT_PORT_DEPRECATED
{
    HV_PARTITION_ID ConnectionPartition;
    HV_CONNECTION_ID ConnectionId;
    HV_UINT32 Reserved1;
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_UINT32 Reserved2;
    HV_CONNECTION_INFO ConnectionInfo;
} HV_INPUT_CONNECT_PORT_DEPRECATED, *PHV_INPUT_CONNECT_PORT_DEPRECATED;

// HvCallGetPortProperty | 0x005A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PORT_PROPERTY
{
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_UINT32 Reserved;
    HV_PORT_PROPERTY_CODE PropertyCode;
} HV_INPUT_GET_PORT_PROPERTY, *PHV_INPUT_GET_PORT_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PORT_PROPERTY
{
    HV_PORT_PROPERTY PropertyValue;
} HV_OUTPUT_GET_PORT_PROPERTY, *PHV_OUTPUT_GET_PORT_PROPERTY;

// HvCallDisconnectPort | 0x005B

typedef union HV_CALL_ATTRIBUTES _HV_INPUT_DISCONNECT_PORT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_PARTITION_ID ConnectionPartition;
        HV_CONNECTION_ID ConnectionId;
        HV_UINT32 Reserved;
    };
} HV_INPUT_DISCONNECT_PORT, *PHV_INPUT_DISCONNECT_PORT;

// HvCallPostMessage | 0x005C

// Already defined in Mile.HyperV.Guest.Interface.h.

// HvCallSignalEvent | 0x005D

// Already defined in Mile.HyperV.Guest.Interface.h.

// HvCallSavePartitionState | 0x005E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SAVE_PARTITION_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_SAVE_RESTORE_STATE_FLAGS Flags;
} HV_INPUT_SAVE_PARTITION_STATE, *PHV_INPUT_SAVE_PARTITION_STATE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_SAVE_PARTITION_STATE
{
    HV_UINT32 SaveDataCount;
    HV_SAVE_RESTORE_STATE_RESULT SaveState;
    HV_UINT8 SaveData[4080];
} HV_OUTPUT_SAVE_PARTITION_STATE, *PHV_OUTPUT_SAVE_PARTITION_STATE;

// HvCallRestorePartitionState | 0x005F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESTORE_PARTITION_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_SAVE_RESTORE_STATE_FLAGS Flags;
    HV_UINT32 RestoreDataCount;
    HV_UINT8 RestoreData[4080];
} HV_INPUT_RESTORE_PARTITION_STATE, *PHV_INPUT_RESTORE_PARTITION_STATE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RESTORE_PARTITION_STATE
{
    HV_SAVE_RESTORE_STATE_RESULT RestoreState;
    HV_UINT32 RestoreDataConsumed;
} HV_OUTPUT_RESTORE_PARTITION_STATE, *PHV_OUTPUT_RESTORE_PARTITION_STATE;

// HvCallInitializeEventLogBufferGroup | 0x0060

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_UINT32 MaximumBufferCount;
    HV_UINT32 BufferSizeInPages;
    HV_UINT32 Threshold;
    HV_EVENTLOG_ENTRY_TIME_BASIS TimeBasis;
    HV_NANO100_TIME SystemTime;
} HV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP, *PHV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP;

// HvCallFinalizeEventLogBufferGroup | 0x0061

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FINALIZE_EVENTLOG_BUFFER_GROUP
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_UINT32 Padding;
} HV_INPUT_FINALIZE_EVENTLOG_BUFFER_GROUP, *PHV_INPUT_FINALIZE_EVENTLOG_BUFFER_GROUP;

// HvCallCreateEventLogBuffer | 0x0062

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_EVENTLOG_BUFFER
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
    HV_PROXIMITY_DOMAIN_INFO ProximityInfo;
} HV_INPUT_CREATE_EVENTLOG_BUFFER, *PHV_INPUT_CREATE_EVENTLOG_BUFFER;

// HvCallDeleteEventLogBuffer | 0x0063

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_EVENTLOG_BUFFER
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
} HV_INPUT_DELETE_EVENTLOG_BUFFER, *PHV_INPUT_DELETE_EVENTLOG_BUFFER;

// HvCallMapEventLogBuffer | 0x0064

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_EVENTLOG_BUFFER
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
} HV_INPUT_MAP_EVENTLOG_BUFFER, *PHV_INPUT_MAP_EVENTLOG_BUFFER;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_MAP_EVENTLOG_BUFFER
{
    HV_GPA_PAGE_NUMBER GpaPageNumbers[512];
} HV_OUTPUT_MAP_EVENTLOG_BUFFER, *PHV_OUTPUT_MAP_EVENTLOG_BUFFER;

// HvCallUnmapEventLogBuffer | 0x0065

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_EVENTLOG_BUFFER
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
} HV_INPUT_UNMAP_EVENTLOG_BUFFER, *PHV_INPUT_UNMAP_EVENTLOG_BUFFER;

// HvCallSetEventLogGroupSources | 0x0066

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_EVENTLOG_GROUP_EVENTS
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_UINT64 EnableFlags;
} HV_INPUT_EVENTLOG_GROUP_EVENTS, *PHV_INPUT_EVENTLOG_GROUP_EVENTS;

// HvCallReleaseEventLogBuffer | 0x0067

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_EVENTLOG_RELEASE_BUFFER
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
} HV_INPUT_EVENTLOG_RELEASE_BUFFER, *PHV_INPUT_EVENTLOG_RELEASE_BUFFER;

// HvCallFlushEventLogBuffer | 0x0068

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_EVENTLOG_BUFFER
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_EVENTLOG_BUFFER_INDEX BufferIndex;
} HV_INPUT_FLUSH_EVENTLOG_BUFFER, *PHV_INPUT_FLUSH_EVENTLOG_BUFFER;

// HvCallPostDebugData | 0x0069

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_POST_DEBUG_DATA
{
    HV_UINT32 Count;
    HV_DEBUG_OPTIONS Options;
    HV_UINT8 Data[HV_DEBUG_MAXIMUM_DATA_SIZE];
} HV_INPUT_POST_DEBUG_DATA, *PHV_INPUT_POST_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_POST_DEBUG_DATA
{
    HV_UINT32 PendingCount;
} HV_OUTPUT_POST_DEBUG_DATA, *PHV_OUTPUT_POST_DEBUG_DATA;

// HvCallRetrieveDebugData | 0x006A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RETRIEVE_DEBUG_DATA
{
    HV_UINT32 Count;
    HV_DEBUG_OPTIONS Options;
    HV_NANO100_DURATION Timeout;
} HV_INPUT_RETRIEVE_DEBUG_DATA, *PHV_INPUT_RETRIEVE_DEBUG_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RETRIEVE_DEBUG_DATA
{
    HV_UINT32 RetrievedCount;
    HV_UINT32 RemainingCount;
    HV_UINT8 Data[HV_DEBUG_MAXIMUM_DATA_SIZE];
} HV_OUTPUT_RETRIEVE_DEBUG_DATA, *PHV_OUTPUT_RETRIEVE_DEBUG_DATA;

// HvCallResetDebugSession | 0x006B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESET_DEBUG_SESSION
{
    HV_DEBUG_OPTIONS Options;
} HV_INPUT_RESET_DEBUG_SESSION, *PHV_INPUT_RESET_DEBUG_SESSION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RESET_DEBUG_SESSION
{
    HV_DEBUG_NET_DATA NetData;
} HV_OUTPUT_RESET_DEBUG_SESSION, *PHV_OUTPUT_RESET_DEBUG_SESSION;

// HvCallMapStatsPage | 0x006C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_STATS_PAGE
{
    HV_STATS_OBJECT_TYPE StatsType;
    HV_STATS_OBJECT_IDENTITY ObjectIdentity;
    HV_GPA_PAGE_NUMBER MapLocation; // Seems not available since Windows 10
} HV_INPUT_MAP_STATS_PAGE, *PHV_INPUT_MAP_STATS_PAGE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_MAP_STATS_PAGE
{
    HV_UINT64 MapLocation;
} HV_OUTPUT_MAP_STATS_PAGE, *PHV_OUTPUT_MAP_STATS_PAGE;

// HvCallUnmapStatsPage | 0x006D

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_STATS_PAGE
{
    HV_STATS_OBJECT_TYPE StatsType;
    HV_STATS_OBJECT_IDENTITY ObjectIdentity;
    HV_GPA_PAGE_NUMBER MapLocation; // Seems not available since Windows 10
} HV_INPUT_UNMAP_STATS_PAGE, *PHV_INPUT_UNMAP_STATS_PAGE;

// HvCallMapSparseGpaPages | 0x006E

typedef struct _HV_GPA_MAPPING
{
    HV_GPA_PAGE_NUMBER TargetGpaPageNumber;
    HV_GPA_PAGE_NUMBER SourceGpaPageNumber;
} HV_GPA_MAPPING, *PHV_GPA_MAPPING;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_SPARSE_GPA_PAGES
{
    // Supplies the partition ID of the partition that this request is for.
    HV_PARTITION_ID TargetPartitionId;
    // Supplies the flags to use for the mapping.
    HV_MAP_GPA_FLAGS MapFlags;
    // Supplies an array of pairs of physical page numbers.
    HV_GPA_MAPPING PageList[];
} HV_INPUT_MAP_SPARSE_GPA_PAGES, *PHV_INPUT_MAP_SPARSE_GPA_PAGES;

// HvCallSetSystemProperty | 0x006F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_SYSTEM_PROPERTY
{
    HV_SYSTEM_PROPERTY PropertyId;
    union
    {
        struct
        {
            HV_UINT16 EventType;
            HV_UINT16 ReservedZ1;
            HV_UINT32 ReservedZ2;
            HV_UINT64 Period;
        } PerfCounter;
        HV_PPM_POWER_POLICY_SETTING PowerPolicySetting;
        HV_SLEEP_STATE_INFO SetSleepStateInformation;
        HV_MACHINE_CHECK_PROPERTY_INFO MachineCheckStateInformation;
        HV_HPET_CONFIG_INFO HpetConfigInfo;
        HV_HPET_ENABLED_INFO HpetEnabledInfo;
        HV_HYPERVISOR_DEBUG_PROPERTY Debug;
    } Property;
} HV_INPUT_SET_SYSTEM_PROPERTY, *PHV_INPUT_SET_SYSTEM_PROPERTY;

// HvCallSetPortProperty | 0x0070

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PORT_PROPERTY
{
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_UINT32 Reserved;
    HV_PORT_PROPERTY_CODE PropertyCode;
    HV_PORT_PROPERTY PropertyValue;
} HV_INPUT_SET_PORT_PROPERTY, *PHV_INPUT_SET_PORT_PROPERTY;

// HvCallOutputDebugCharacter | 0x0071

// HvCallEchoIncrement | 0x0072

// HvCallPerfNop | 0x0073

// HvCallPerfNopInput | 0x0074

// HvCallPerfNopOutput | 0x0075

// HvCallAddLogicalProcessor | 0x0076

/* 6259 */
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ADD_LOGICAL_PROCESSOR
{
    HV_UINT32 LpIndex;
    HV_UINT32 ApicId;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_UINT64 Flags;
} HV_INPUT_ADD_LOGICAL_PROCESSOR, *PHV_INPUT_ADD_LOGICAL_PROCESSOR;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_ADD_LOGICAL_PROCESSOR
{
    HV_LP_STARTUP_STATUS StartupStatus;
} HV_OUTPUT_ADD_LOGICAL_PROCESSOR, *PHV_OUTPUT_ADD_LOGICAL_PROCESSOR;

// HvCallRemoveLogicalProcessor | 0x0077

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_REMOVE_LOGICAL_PROCESSOR
{
    HV_UINT32 LpIndex;
    HV_UINT64 Flags;
} HV_INPUT_REMOVE_LOGICAL_PROCESSOR, *PHV_INPUT_REMOVE_LOGICAL_PROCESSOR;

// HvCallQueryNumaDistance | 0x0078

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_NUMA_DISTANCE
{
    HV_UINT32 CpuProximityId;
    HV_UINT32 MemoryProximityId;
} HV_INPUT_QUERY_NUMA_DISTANCE, *PHV_INPUT_QUERY_NUMA_DISTANCE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_NUMA_DISTANCE
{
    HV_UINT64 Distance;
} HV_OUTPUT_QUERY_NUMA_DISTANCE, *PHV_OUTPUT_QUERY_NUMA_DISTANCE;

// HvCallSetLogicalProcessorProperty | 0x0079

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_LOGICAL_PROCESSOR_PROPERTY
{
    HV_UINT32 LpIndex;
    HV_LOGICAL_PROCESSOR_PROPERTY_TYPE Type;
    HV_LOGICAL_PROCESSOR_PROPERTY Property;
} HV_INPUT_SET_LOGICAL_PROCESSOR_PROPERTY, *PHV_INPUT_SET_LOGICAL_PROCESSOR_PROPERTY;

// HvCallGetLogicalProcessorProperty | 0x007A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_LOGICAL_PROCESSOR_PROPERTY
{
    HV_UINT32 LpIndex;
    HV_LOGICAL_PROCESSOR_PROPERTY_TYPE Type;
} HV_INPUT_GET_LOGICAL_PROCESSOR_PROPERTY, *PHV_INPUT_GET_LOGICAL_PROCESSOR_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_LOGICAL_PROCESSOR_PROPERTY
{
    HV_LOGICAL_PROCESSOR_PROPERTY Property;
} HV_OUTPUT_GET_LOGICAL_PROCESSOR_PROPERTY, *PHV_OUTPUT_GET_LOGICAL_PROCESSOR_PROPERTY;

// HvCallGetSystemProperty | 0x007B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_SYSTEM_PROPERTY
{
    HV_SYSTEM_PROPERTY PropertyId;
    union
    {
        HV_PPM_POWER_POLICY_SETTING_ID SettingId;
    } Property;
} HV_INPUT_GET_SYSTEM_PROPERTY, *PHV_INPUT_GET_SYSTEM_PROPERTY;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_SYSTEM_PROPERTY
{
    struct
    {
        HV_UINT16 EventType;
        HV_UINT16 ReservedZ1;
        HV_UINT32 ReservedZ2;
        HV_UINT64 Period;
    } PerfCounter;
    HV_PPM_POWER_POLICY_SETTING PowerPolicySetting;
    HV_IOMMU_INIT_STATUS IommuInitStatus;
    HV_TSC_SYNC_STATUS TscSyncStatus;
    HV_HPET_CONFIG_INFO HpetConfigInfo;
    HV_HPET_INTERRUPT_INFO HpetInterruptInfo;
    HV_HPET_ENABLED_INFO HpetEnabledInfo;
    HV_HYPERVISOR_LAUNCH_STATS HvLaunchStats;
    HV_ROOT_SVM_CAPABILITIES_PROPERTY RootSvmCapabilities;
    HV_ROOT_NUMA_COST_PAGES_PROPERTY RootNumaCostPages;
    HV_UINT64 HvHostPageTableRoot;
    HV_SCHEDULER_TYPE SchedulerType;
    HV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO VirtualizationInfo;
} HV_OUTPUT_GET_SYSTEM_PROPERTY, *PHV_OUTPUT_GET_SYSTEM_PROPERTY;

// HvCallMapDeviceInterrupt | 0x007C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
    HV_UINT64 Flags;
    HV_DEVICE_INTERRUPT_DESCRIPTOR InterruptDescriptor;
} HV_INPUT_MAP_DEVICE_INTERRUPT, *PHV_INPUT_MAP_DEVICE_INTERRUPT;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_MAP_DEVICE_INTERRUPT
{
    HV_INTERRUPT_ENTRY InterruptEntry;
    HV_IOMMU_EXTENDED_STATUS ExtendedStatus;
} HV_OUTPUT_MAP_DEVICE_INTERRUPT, *PHV_OUTPUT_MAP_DEVICE_INTERRUPT;

// HvCallUnmapDeviceInterrupt | 0x007D

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
    HV_INTERRUPT_ENTRY InterruptEntry;
} HV_INPUT_UNMAP_DEVICE_INTERRUPT, *PHV_INPUT_UNMAP_DEVICE_INTERRUPT;

// HvCallRetargetDeviceInterrupt | 0x007E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RETARGET_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_UINT64 DeviceId;
    HV_INTERRUPT_ENTRY InterruptEntry;
    HV_UINT64 Reserved;
    HV_DEVICE_INTERRUPT_TARGET InterruptTarget;
} HV_INPUT_RETARGET_DEVICE_INTERRUPT, *PHV_INPUT_RETARGET_DEVICE_INTERRUPT;

// HvCallRetargetRootDeviceInterrupt | 0x007F

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_RETARGET_ROOT_DEVICE_INTERRUPT
{
    HV_INTERRUPT_ENTRY InterruptEntry;
} HV_OUTPUT_RETARGET_ROOT_DEVICE_INTERRUPT, *PHV_OUTPUT_RETARGET_ROOT_DEVICE_INTERRUPT;

// HvCallAssertDeviceInterrupt | 0x0080
// HvCallReserved0081 | 0x0081

// HvCallAttachDevice | 0x0082

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ATTACH_DEVICE
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
    HV_ATTACH_DEVICE_FLAGS Flags;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_DEVICE_PCI_CAPABILITIES PciCapabilities;
    HV_UINT32 Reserved;
} HV_INPUT_ATTACH_DEVICE, *PHV_INPUT_ATTACH_DEVICE;

// HvCallDetachDevice | 0x0083

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DETACH_DEVICE
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
} HV_INPUT_DETACH_DEVICE, *PHV_INPUT_DETACH_DEVICE;

// HvCallEnterSleepState | 0x0084

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ENTER_SLEEP_STATE
{
    HV_SLEEP_STATE SleepState;
} HV_INPUT_ENTER_SLEEP_STATE, *PHV_INPUT_ENTER_SLEEP_STATE;

// HvCallNotifyStandbyTransition | 0x0085

// HV_INPUT_PREPARE_FOR_SLEEP
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_NOTIFY_STANDBY_TRANSITION
{
    HV_BOOLEAN Entering;
    HV_BOOLEAN ModernStandby;
} HV_INPUT_NOTIFY_STANDBY_TRANSITION, *PHV_INPUT_NOTIFY_STANDBY_TRANSITION;

// HvCallPrepareForHibernate | 0x0086

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PREPARE_FOR_HIBERNATE
{
    HV_X64_PROC_STATE_GP_REGS ResumeGpRegs;
    HV_VTL RestrictApVtl;
} HV_INPUT_PREPARE_FOR_HIBERNATE, *PHV_INPUT_PREPARE_FOR_HIBERNATE;

typedef struct HV_CALL_ATTRIBUTES _HV_X64_OUTPUT_PREPARE_FOR_HIBERNATE
{
    HV_UINT64 HvCr3;
    HV_UINT64 HvEntryPoint;
    HV_UINT64 HvReservedTransitionAddress;
    HV_UINT64 HvReservedTransitionAddressSize;
} HV_X64_OUTPUT_PREPARE_FOR_HIBERNATE, *PHV_X64_OUTPUT_PREPARE_FOR_HIBERNATE;

// HvCallNotifyPartitionEvent | 0x0087

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_NOTIFY_PARTITION_EVENT
{
    HV_PARTITION_EVENT Event;
    HV_PARTITION_EVENT_INPUT Input;
} HV_INPUT_NOTIFY_PARTITION_EVENT, *PHV_INPUT_NOTIFY_PARTITION_EVENT;

// HvCallGetLogicalProcessorRegisters | 0x0088

// HvCallSetLogicalProcessorRegisters | 0x0089

// HvCallQueryAssociatedLpsforMca | 0x008A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_ASSOCIATED_LPS_FOR_MCA
{
    HV_VP_INDEX VpIndex;
} HV_INPUT_QUERY_ASSOCIATED_LPS_FOR_MCA, *PHV_INPUT_QUERY_ASSOCIATED_LPS_FOR_MCA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_ASSOCIATED_LPS_FOR_MCA
{
    HV_UINT32 Count;
    HV_UINT32 AssociatedLpList[512];
} HV_OUTPUT_QUERY_ASSOCIATED_LPS_FOR_MCA, *PHV_OUTPUT_QUERY_ASSOCIATED_LPS_FOR_MCA;

// HvCallNotifyRingEmpty | 0x008B

typedef union HV_CALL_ATTRIBUTES _HV_INPUT_NOTIFY_PORT_RING_EMPTY
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 SintIndex;
        HV_UINT32 Reserved;
    };
} HV_INPUT_NOTIFY_PORT_RING_EMPTY, *PHV_INPUT_NOTIFY_PORT_RING_EMPTY;

// HvCallInjectSyntheticMachineCheck | 0x008C

// HvCallScrubPartition | 0x008D

// HvCallCollectLivedump | 0x008E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_COLLECT_LIVE_DUMP
{
    HV_UINT64 Flags;
    HV_MEMORY_DESCRIPTOR Descriptor;
} HV_INPUT_COLLECT_LIVE_DUMP, *PHV_INPUT_COLLECT_LIVE_DUMP;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_COLLECT_LIVE_DUMP
{
    HV_UINT64 PagesCopied;
    HV_UINT64 DepositedPages;
} HV_OUTPUT_COLLECT_LIVE_DUMP, *PHV_OUTPUT_COLLECT_LIVE_DUMP;

// HvCallDisableHypervisor | 0x008F

typedef union HV_CALL_ATTRIBUTES _HV_X64_INPUT_DISABLE_HYPERVISOR
{
    HV_UINT64 TrampolineCr3;
    HV_UINT64 KernelCr3;
    HV_UINT64 Rip;
} HV_X64_INPUT_DISABLE_HYPERVISOR, *PHV_X64_INPUT_DISABLE_HYPERVISOR;

// HvCallModifySparseGpaPages | 0x0090

// HvCallRegisterInterceptResult | 0x0091

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_REGISTER_INTERCEPT_RESULT
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_INTERCEPT_TYPE InterceptType;
    HV_REGISTER_INTERCEPT_RESULT_PARAMETERS Parameters;
} HV_INPUT_REGISTER_INTERCEPT_RESULT, *PHV_INPUT_REGISTER_INTERCEPT_RESULT;
#endif

// HvCallUnregisterInterceptResult | 0x0092

// HvCallGetCoverageData | 0x0093

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_COVERAGE_VECTOR
{
    HV_COVERAGE_OPERATION CoverageOp;
    HV_UINT32 PageCount;
    HV_GPA_PAGE_NUMBER GpaPageNumbers[128];
} HV_INPUT_GET_COVERAGE_VECTOR, *PHV_INPUT_GET_COVERAGE_VECTOR;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_COVERAGE_VECTOR
{
    HV_IMAGE_COVERAGE_INFO CoverageInfo;
} HV_OUTPUT_GET_COVERAGE_VECTOR, *PHV_OUTPUT_GET_COVERAGE_VECTOR;

// HvCallAssertVirtualInterrupt | 0x0094

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ASSERT_VIRTUAL_INTERRUPT
{
    HV_PARTITION_ID DestinationPartition;
    HV_INTERRUPT_CONTROL InterruptControl;
    HV_UINT64 DestinationAddress;
    HV_INTERRUPT_VECTOR RequestedVector;
    HV_VTL TargetVtl;
    HV_UINT8 Padding[3];
} HV_INPUT_ASSERT_VIRTUAL_INTERRUPT, *PHV_INPUT_ASSERT_VIRTUAL_INTERRUPT;

// HvCallCreatePort | 0x0095

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PORT
{
    HV_UINT64 PortPartitionId;
    HV_PORT_ID PortId;
    HV_VTL PortVtl;
    HV_VTL MinConnectionVtl;
    HV_UINT16 Padding;
    HV_UINT64 ConnectionPartitionId;
    HV_PORT_INFO PortInfo;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INPUT_CREATE_PORT, *PHV_INPUT_CREATE_PORT;

// HvCallConnectPort | 0x0096

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CONNECT_PORT
{
    HV_UINT64 Connection_partitionId;
    HV_CONNECTION_ID ConnectionId;
    HV_VTL ConnectionVtl;
    HV_UINT8 Rsvdz[3];
    HV_UINT64 PortPartitionId;
    HV_PORT_ID PortId;
    HV_UINT32 Reserved2;
    HV_CONNECTION_INFO ConnectionInfo;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INPUT_CONNECT_PORT, *PHV_INPUT_CONNECT_PORT;

// HvCallGetSpaPageList | 0x0097

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_SPA_PAGE_LIST
{
    HV_UINT64 StartPage;
    HV_UINT64 EndPage;
    HV_SPA_PAGE_LIST_FLAGS Flags;
} HV_INPUT_GET_SPA_PAGE_LIST, *PHV_INPUT_GET_SPA_PAGE_LIST;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_SPA_PAGE_LIST
{
    HV_UINT64 NextPageToScan;
    HV_UINT16 RangeCount;
    HV_UINT16 Rsvd[3];
    HV_SPA_PAGE_RANGE RangeList[510];
} HV_OUTPUT_GET_SPA_PAGE_LIST, *PHV_OUTPUT_GET_SPA_PAGE_LIST;

// HvCallReserved0098 | 0x0098

// HvCallStartVirtualProcessor | 0x0099

// Already defined in Mile.HyperV.Guest.Interface.h.

// HvCallGetVpIndexFromApicId | 0x009A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_INDEX_FROM_APIC_ID
{
    HV_PARTITION_ID PartitionId;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
    HV_UINT32 ReservedZ2;
    HV_APIC_ID ApicIds[];
} HV_INPUT_GET_VP_INDEX_FROM_APIC_ID, *PHV_INPUT_GET_VP_INDEX_FROM_APIC_ID;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_VP_INDEX_FROM_APIC_ID
{
    HV_VP_INDEX VpIndexs[HV_ANYSIZE_ARRAY];
} HV_OUTPUT_GET_VP_INDEX_FROM_APIC_ID, *PHV_OUTPUT_GET_VP_INDEX_FROM_APIC_ID;

// HvCallGetPowerProperty | 0x009B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_POWER_PROPERTY
{
    HV_POWER_PROPERTY_TYPE Type;
    union
    {
        union
        {
            HV_PPM_POWER_POLICY_SETTING_ID PolicySettingId;
        } Global;
        struct
        {
            HV_UINT32 LpIndex;
        } Processor;
    };
} HV_INPUT_GET_POWER_PROPERTY, *PHV_INPUT_GET_POWER_PROPERTY;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_POWER_PROPERTY
{
    HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY IdleStateConfig;
    HV_UINT32 PercentFrequency;
    HV_UINT32 NextPlatformStateIndex;
    HV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG FeedbackCounterConfig;
    struct
    {
        HV_UINT32 Value;
    } Policy;
    HV_POWER_STATS_OFFSETS StatsOffsets;
} HV_OUTPUT_GET_POWER_PROPERTY, *PHV_OUTPUT_GET_POWER_PROPERTY;

// HvCallSetPowerProperty | 0x009C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_POWER_PROPERTY
{
    HV_POWER_PROPERTY_TYPE Type;
    union
    {
        struct
        {
            HV_UINT32 LpIndex;
            union
            {
                HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY IdleStateConfig;
                HV_UINT32 PercentFrequency;
                HV_UINT32 NextPlatformStateIndex;
                HV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG FeedbackCounterConfig;
            };
        } Processor;
        union
        {
            HV_PPM_POWER_POLICY_SETTING Policy;
        } Global;
    };
} HV_INPUT_SET_POWER_PROPERTY, *PHV_INPUT_SET_POWER_PROPERTY;

// HvCallCreatePasidSpace | 0x009D

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PASID_SPACE
{
    HV_PASID_SPACE_ID PasidSpaceId;
    HV_UINT32 PasidCount;
} HV_INPUT_CREATE_PASID_SPACE, *PHV_INPUT_CREATE_PASID_SPACE;

// HvCallDeletePasidSpace | 0x009E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PASID_SPACE
{
    HV_PASID_SPACE_ID PasidSpaceId;
    HV_UINT32 Reserved;
} HV_INPUT_DELETE_PASID_SPACE, *PHV_INPUT_DELETE_PASID_SPACE;

// HvCallSetPasidAddressSpace | 0x009F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PASID_ADDRESS_SPACE
{
    HV_FULL_PASID FullPasid;
    HV_DEVICE_ADDRESS_SPACE AddressSpace;
} HV_INPUT_SET_PASID_ADDRESS_SPACE, *PHV_INPUT_SET_PASID_ADDRESS_SPACE;

// HvCallFlushPasidAddressSpace | 0x00A0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_PASID_ADDRESS_SPACE
{
    HV_FULL_PASID FullPasid;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
} HV_INPUT_FLUSH_PASID_ADDRESS_SPACE, *PHV_INPUT_FLUSH_PASID_ADDRESS_SPACE;

// HvCallFlushPasidAddressList | 0x00A1

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_PASID_ADDRESS_LIST
{
    HV_FULL_PASID FullPasid;
    HV_UINT32 Flags;
    HV_UINT32 VaCount;
    HV_GVA_RANGE_EXTENDED VaList[];
} HV_INPUT_FLUSH_PASID_ADDRESS_LIST, *PHV_INPUT_FLUSH_PASID_ADDRESS_LIST;

// HvCallAttachPasidSpace | 0x00A2

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ATTACH_PASID_SPACE
{
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_PASID_SPACE_ID PasidSpaceId;
    HV_UINT32 PrQueueId;
    HV_UINT32 Reserved;
} HV_INPUT_ATTACH_PASID_SPACE, *PHV_INPUT_ATTACH_PASID_SPACE;

// HvCallDetachPasidSpace | 0x00A3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DETACH_PASID_SPACE
{
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_UINT32 Reserved;
} HV_INPUT_DETACH_PASID_SPACE, *PHV_INPUT_DETACH_PASID_SPACE;

// HvCallEnablePasid | 0x00A4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ENABLE_PASID
{
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_PASID Pasid;
} HV_INPUT_ENABLE_PASID, *PHV_INPUT_ENABLE_PASID;

// HvCallDisablePasid | 0x00A5

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISABLE_PASID
{
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_PASID Pasid;
} HV_INPUT_DISABLE_PASID, *PHV_INPUT_DISABLE_PASID;

// HvCallAcknowledgeDevicePageRequest | 0x00A6

// HvCallCreateDevicePrQueue | 0x00A7

/* 6364 */
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_DEVICE_PR_QUEUE
{
    HV_UINT32 QueueId;
    HV_UINT32 Size;
    HV_GPA_PAGE_NUMBER BaseGpaPage;
    HV_UINT32 InterruptVector;
    HV_UINT32 InterruptVpIndex;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
} HV_INPUT_CREATE_DEVICE_PR_QUEUE, *PHV_INPUT_CREATE_DEVICE_PR_QUEUE;

// HvCallDeleteDevicePrQueue | 0x00A8

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_DEVICE_PR_QUEUE
{
    HV_UINT32 QueueId;
    HV_UINT32 Reserved;
} HV_INPUT_DELETE_DEVICE_PR_QUEUE, *PHV_INPUT_DELETE_DEVICE_PR_QUEUE;

// HvCallSetDevicePrqProperty | 0x00A9

// HV_INPUT_SET_DEVICE_PRQ_PROPERTY_HEADER
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_DEVICE_PRQ_PROPERTY
{
    HV_UINT32 QueueId;
    HV_DEVICE_PRQ_PROPERTY Property;
} HV_INPUT_SET_DEVICE_PRQ_PROPERTY, *PHV_INPUT_SET_DEVICE_PRQ_PROPERTY;

// HvCallGetPhysicalDeviceProperty | 0x00AA

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PHYSICAL_DEVICE_PROPERTY
{
    HV_DEVICE_ID PhysicalDeviceId;
    HV_PHYSICAL_DEVICE_PROPERTY Property;
    HV_UINT32 Reserved;
} HV_INPUT_GET_PHYSICAL_DEVICE_PROPERTY, *PHV_INPUT_GET_PHYSICAL_DEVICE_PROPERTY;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PHYSICAL_DEVICE_PROPERTY
{
    HV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES Capabilities;
    HV_PHYSICAL_DEVICE_PROPERTY_ENABLED Enabled;
} HV_OUTPUT_GET_PHYSICAL_DEVICE_PROPERTY, *PHV_OUTPUT_GET_PHYSICAL_DEVICE_PROPERTY;

// HvCallSetPhysicalDeviceProperty | 0x00AB

// HV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY_HEADER
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY
{
    HV_DEVICE_ID PhysicalDeviceId;
    HV_PHYSICAL_DEVICE_PROPERTY Property;
    HV_UINT32 Reserved;
} HV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY, *PHV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY;

// HvCallTranslateVirtualAddressEx | 0x00AC
// HvCallCheckForIoIntercept | 0x00AD

// HvCallSetGpaPageAttributes | 0x00AE

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_GPA_PAGE_ATTRIBUTES
{
    HV_PARTITION_ID PartitionId;
    HV_GPA_PAGE_ATTRIBUTES Attributes;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_SET_GPA_PAGE_ATTRIBUTES, *PHV_INPUT_SET_GPA_PAGE_ATTRIBUTES;

// HvCallFlushGuestPhysicalAddressSpace | 0x00AF

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE
{
    HV_SPA AddressSpace;
    HV_UINT64 Flags;
} HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE, *PHV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE;

// HvCallFlushGuestPhysicalAddressList | 0x00B0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST
{
    HV_SPA AddressSpace;
    HV_UINT64 Flags;
    HV_GPA_PAGE_RANGE GpaRangeList[];
} HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST, *PHV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST;

// HvCallCreateDeviceDomain | 0x00B1

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
} HV_INPUT_CREATE_DEVICE_DOMAIN, *PHV_INPUT_CREATE_DEVICE_DOMAIN;

// HvCallAttachDeviceDomain | 0x00B2

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ATTACH_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_DEVICE_ID DeviceId;
} HV_INPUT_ATTACH_DEVICE_DOMAIN, *PHV_INPUT_ATTACH_DEVICE_DOMAIN;

// HvCallMapDeviceGpaPages | 0x00B3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_DEVICE_GPA_PAGES
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_INPUT_VTL TargetVtl;
    HV_UINT32 MapFlags;
    HV_DEVICE_VA TargetDeviceVaBase;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_MAP_DEVICE_GPA_PAGES, *PHV_INPUT_MAP_DEVICE_GPA_PAGES;

// HvCallUnmapDeviceGpaPages | 0x00B4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_DEVICE_GPA_PAGES
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_DEVICE_VA TargetDeviceVaBase;
} HV_INPUT_UNMAP_DEVICE_GPA_PAGES, *PHV_INPUT_UNMAP_DEVICE_GPA_PAGES;

// HvCallCreateCpuGroup | 0x00B5
// HvCallDeleteCpuGroup | 0x00B6
// HvCallGetCpuGroupProperty | 0x00B7
// HvCallSetCpuGroupProperty | 0x00B8
// HvCallGetCpuGroupAffinity | 0x00B9
// HvCallGetNextCpuGroup | 0x00BA
// HvCallGetNextCpuGroupPartition | 0x00BB

// HvCallAddPhysicalMemory | 0x00BC

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ADD_PHYSICAL_MEMORY
{
    HV_GPA_PAGE_NUMBER StartPage;
    HV_UINT64 PageCount;
} HV_INPUT_ADD_PHYSICAL_MEMORY, *PHV_INPUT_ADD_PHYSICAL_MEMORY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_ADD_PHYSICAL_MEMORY
{
    HV_UINT64 PagesProcessed;
} HV_OUTPUT_ADD_PHYSICAL_MEMORY, *PHV_OUTPUT_ADD_PHYSICAL_MEMORY;

// HvCallCompleteIntercept | 0x00BD
// HvCallPrecommitGpaPages | 0x00BE
// HvCallUncommitGpaPages | 0x00BF

// HvCallSignalEventDirect | 0x00C0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SIGNAL_EVENT_DIRECT
{
    HV_UINT64 TargetPartition;
    HV_UINT32 TargetVp;
    HV_VTL TargetVtl;
    HV_UINT8 TargetSint;
    HV_UINT16 FlagNumber;
} HV_INPUT_SIGNAL_EVENT_DIRECT, *PHV_INPUT_SIGNAL_EVENT_DIRECT;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_SIGNAL_EVENT_DIRECT
{
    HV_UINT8 NewlySignaled;
    HV_UINT8 Reserved[7];
} HV_OUTPUT_SIGNAL_EVENT_DIRECT, *PHV_OUTPUT_SIGNAL_EVENT_DIRECT;

// HvCallPostMessageDirect | 0x00C1

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_POST_MESSAGE_DIRECT
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL Vtl;
    HV_UINT8 Padding[3];
    HV_UINT32 SintIndex;
    HV_UINT8 Message[HV_MESSAGE_SIZE];
    HV_UINT32 Padding2;
} HV_INPUT_POST_MESSAGE_DIRECT, *PHV_INPUT_POST_MESSAGE_DIRECT;

// HvCallDispatchVp | 0x00C2

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISPATCH_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_UINT32 Flags;
    HV_UINT64 TimeSlice; // in 100ns
    HV_UINT64 SpecCtrl;
} HV_INPUT_DISPATCH_VP, *PHV_INPUT_DISPATCH_VP;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_DISPATCH_VP
{
    HV_VP_DISPATCH_STATE DispatchState;
    HV_VP_DISPATCH_EVENT DispatchEvent;
} HV_OUTPUT_DISPATCH_VP, *PHV_OUTPUT_DISPATCH_VP;

// HvCallProcessIommuPrq | 0x00C3
// HvCallDetachDeviceDomain | 0x00C4
// HvCallDeleteDeviceDomain | 0x00C5
// HvCallQueryDeviceDomain | 0x00C6
// HvCallMapSparseDeviceGpaPages | 0x00C7
// HvCallUnmapSparseDeviceGpaPages | 0x00C8

// HvCallGetGpaPagesAccessState | 0x00C9

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_GPA_PAGES_ACCESS_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_GPA_PAGE_ACCESS_STATE_FLAGS Flags;
    HV_UINT64 HvGpaPageNumber;
} HV_INPUT_GET_GPA_PAGES_ACCESS_STATE, *PHV_INPUT_GET_GPA_PAGES_ACCESS_STATE;

// HvCallGetSparseGpaPagesAccessState | 0x00CA
// HvCallInvokeTestFramework | 0x00CB
// HvCallQueryVtlProtectionMaskRange | 0x00CC
// HvCallModifyVtlProtectionMaskRange | 0x00CD
// HvCallConfigureDeviceDomain | 0x00CE
// HvCallQueryDeviceDomainProperties | 0x00CF
// HvCallFlushDeviceDomain | 0x00D0
// HvCallFlushDeviceDomainList | 0x00D1
// HvCallAcquireSparseGpaPageHostAccess | 0x00D2
// HvCallReleaseSparseGpaPageHostAccess | 0x00D3
// HvCallCheckSparseGpaPageVtlAccess | 0x00D4
// HvCallReserved00d5 | 0x00D5
// HvCallFlushTlb | 0x00D6
// HvCallAcquireSparseSpaPageHostAccess | 0x00D7
// HvCallReleaseSparseSpaPageHostAccess | 0x00D8
// HvCallAcceptGpaPages | 0x00D9
// HvCallUnacceptGpaPages | 0x00DA

// HvCallModifySparseGpaPageHostVisibility | 0x00DB

// Already defined in Mile.HyperV.Guest.Interface.h.

// HvCallLockSparseGpaPageMapping | 0x00DC
// HvCallUnlockSparseGpaPageMapping | 0x00DD
// HvCallRequestProcessorHalt | 0x00DE
// HvCallGetInterceptData | 0x00DF
// HvCallQueryDeviceInterruptTarget | 0x00E0

// HvCallMapVpStatePage | 0x00E1

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_VP_STATE_PAGE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VP_STATE_PAGE_TYPE Type;
} HV_INPUT_MAP_VP_STATE_PAGE, *PHV_INPUT_MAP_VP_STATE_PAGE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_MAP_VP_STATE_PAGE
{
    HV_UINT64 MapLocation; // GPA page number
} HV_OUTPUT_MAP_VP_STATE_PAGE, *PHV_OUTPUT_MAP_VP_STATE_PAGE;

// HvCallUnmapVpStatePage | 0x00E2

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_VP_STATE_PAGE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VP_STATE_PAGE_TYPE Type;
} HV_INPUT_UNMAP_VP_STATE_PAGE, *PHV_INPUT_UNMAP_VP_STATE_PAGE;

// HvCallGetVpState | 0x00E3

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL InputVtl;
    HV_UINT8 Rsvd[3];
    HV_VP_STATE_DATA StateData;
    HV_UINT64 OutputDataPfns[];
} HV_INPUT_GET_VP_STATE, *PHV_INPUT_GET_VP_STATE;
#endif

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_VP_STATE
{
    HV_LOCAL_INTERRUPT_CONTROLLER_STATE InterruptControllerState;
    HV_SYNTHETIC_TIMERS_STATE SyntheticTimersState;
} HV_OUTPUT_GET_VP_STATE, *PHV_OUTPUT_GET_VP_STATE;

// HvCallSetVpState | 0x00E4

typedef union _HV_INPUT_SET_VP_STATE_DATA
{
    HV_UINT64 Pfns;
    HV_UINT8 Bytes;
} HV_INPUT_SET_VP_STATE_DATA, *PHV_INPUT_SET_VP_STATE_DATA;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_VP_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL InputVtl;
    HV_UINT8 Rsvd[3];
    HV_VP_STATE_DATA StateData;
    HV_INPUT_SET_VP_STATE_DATA Data[];
} HV_INPUT_SET_VP_STATE, *PHV_INPUT_SET_VP_STATE;
#endif

// HvCallGetVpSetFromMda | 0x00E5
// HvCallReserved00e6 | 0x00E6
// HvCallCreateIptBuffers | 0x00E7
// HvCallDeleteIptBuffers | 0x00E8
// HvCallControlHypervisorIptTrace | 0x00E9
// HvCallReserveDeviceInterrupt | 0x00EA
// HvCallPersistDevice | 0x00EB
// HvCallUnpersistDevice | 0x00EC
// HvCallPersistDeviceInterrupt | 0x00ED
// HvCallRefreshPerformanceCounters | 0x00EE
// HvCallImportIsolatedPages | 0x00EF
// HvCallReserved00f0 | 0x00F0
// HvCallCompleteIsolatedImport | 0x00F1
// HvCallIssueSnpPspGuestRequest | 0x00F2
// HvCallRootSignalEvent | 0x00F3

// HvCallGetVpCpuidValues | 0x00F4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_CPUID_VALUES
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_GET_VP_CPUID_VALUES_FLAGS Flags;
    HV_UINT32 Reserved;
    HV_UINT32 Padding;
    HV_CPUID_LEAF_INFO CpuidLeafInfo[];
} HV_INPUT_GET_VP_CPUID_VALUES, *PHV_INPUT_GET_VP_CPUID_VALUES;

// NOTE: Not in hvhdk headers
typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_VP_CPUID_VALUES
{
    HV_UINT32 AsUINT32[4];
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 Ebx;
        HV_UINT32 Ecx;
        HV_UINT32 Edx;
    };
} HV_OUTPUT_GET_VP_CPUID_VALUES, *PHV_OUTPUT_GET_VP_CPUID_VALUES;

// HvCallReadSystemMemory | 0x00F5
// HvCallSetHwWatchdogConfig | 0x00F6
// HvCallRemovePhysicalMemory | 0x00F7
// HvCallLogHypervisorSystemConfig | 0x00F8
// HvCallIssueNestedSnpPspRequests | 0x00F9
// HvCallReserved00fa | 0x00FA
// HvCallSubsumeInitializedMemory | 0x00FB
// HvCallSubsumeVp | 0x00FC
// HvCallDestroySubsumedContext | 0x00FD
// HvCallWriteSysDiagEvent | 0x00FE
// HvCallDepositMemoryMirroring | 0x00FF
// HvCallSetDeviceCapabilities | 0x0100
// HvCallGetPartitionPropertyEx | 0x0101
// HvCallGetGpaRangesAccessState | 0x0102
// HvCallRestorePartitionTime | 0x0103
// HvCallQueryAssociatedLpsForMcaEx | 0x0104
// HvCallQueryPartitionReservedPages | 0x0105
// HvCallMemoryMappedIoRead | 0x0106
// HvCallMemoryMappedIoWrite | 0x0107
// HvCallMapDmaRange | 0x0108
// HvCallUnmapDmaRange | 0x0109
// HvCallSetPartitionPropertyEx | 0x010A
// HvCallAttachDevicePrQueue | 0x010B
// HvCallDetachDevicePrQueue | 0x010C
// HvCallReserveDeviceDomainAttachment | 0x010D
// HvCallUnreserveDeviceDomainAttachment | 0x010E
// HvCallDisableHypervisorEx | 0x010F
// HvCallInstallInterceptEx | 0x0110
// HvCallMapVpStatePageEx | 0x0111
// HvCallPinGpaPageRanges | 0x0112
// HvCallUnpinGpaPageRanges | 0x0113
// HvCallWakeVps | 0x0114
// HvCallSetCpuGroupAffinity | 0x0115
// HvCallMapPartitionEventLogBuffer | 0x0116

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4200) // zero length array
#pragma warning(default:4201) // nameless struct/union
#pragma warning(default:4324) // structure was padded due to __declspec(align())
#endif
#endif

#endif // !MILE_HYPERV_TLFS
