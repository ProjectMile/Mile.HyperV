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
// - Symbols in Windows Driver Kit version 10.0.26100.0's
//   Debuggers\ddk\samples\kdserial\lib\x64\kdhv.lib
// - Symbols in Windows version 10.0.14393.0's urlmon.dll
// - Geoff Chappell's hvgdk_mini researches hints
//   - hvgdk.h is existed from Windows Driver Kit version 7.1.0
//   - Symbols in Windows version 10.0.14393.0's urlmon.dll have HV symbols
// - Symbols in Windows version 10.0.14347.0's ntoskrnl.exe
// - Symbols in Windows version 10.0.26100.0's securekernel.exe (header dumped
//   by Mezone)

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
// actual alignment is greater than the value specified in __declspec(align())
#pragma warning(disable:4359)
#endif

// Define a 256bit type.
typedef struct HV_DECLSPEC_ALIGN(32) _HV_UINT256
{
    HV_UINT128 Low128;
    HV_UINT128 High128;
} HV_UINT256, *PHV_UINT256;

// Define a 512bit type.
typedef struct HV_DECLSPEC_ALIGN(64) _HV_UINT512
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
        HV_UINT64 Reserved8_9 : 2;
        HV_UINT64 Pasid : 1;
        HV_UINT64 CetU : 1;
        HV_UINT64 CetS : 1;
        HV_UINT64 Reserved13_16 : 4;
        HV_UINT64 XtileCfg : 1;
        HV_UINT64 XtileData : 1;
        HV_UINT64 Reserved19_63 : 45;
    };
} HV_X64_XSAVE_XFEM_REGISTER, *PHV_X64_XSAVE_XFEM_REGISTER;

// This structure represents the header area of an XSAVE area.
// This must be alligned on a 64 byte boundary.
typedef struct HV_DECLSPEC_ALIGN(64) _HV_X64_XSAVE_HEADER
{
    // Bit vector indicating which features have state store in the XSAVE area.
    HV_X64_XSAVE_XFEM_REGISTER XstateBv; // Bit 63 MBZ
    HV_X64_XSAVE_XFEM_REGISTER XcompBv;
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
    union
    {
        struct
        {
            // The version of the HV_VP_CONTEXT structure
            HV_UINT32 Version;
            // The architecture of these registers
            HV_ARCHITECTURE Architecture;
            union
            {
#if defined(_M_AMD64) || defined(_M_IX86)
                HV_X64_CONTEXT x64;
#elif defined(_M_ARM64)
                HV_ARM64_CONTEXT aa64;
#endif
            };
        };
#if defined(_M_ARM64)
        struct
        {
            HV_UINT64 Pc;
            HV_UINT64 Sctlr;
            HV_UINT64 Ttbr0;
            HV_UINT64 Ttbr1;
            HV_UINT64 Tcr;
            HV_UINT64 Mair;
        };
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
    StCounterHvLogicalProcessors = 0x1,
    StCounterHvPartitions = 0x2,
    StCounterHvTotalPages = 0x3,
    StCounterHvVirtualProcessors = 0x4,
    StCounterHvMonitoredNotifications = 0x5,
    StCounterHvModernStandbyEntries = 0x6,
    StCounterHvPlatformIdleTransitions = 0x7,
    StCounterHvHypervisorStartupCost = 0x8,
    StCounterHvIOSpacePages = 0xA,
    StCounterHvNonEssentialPagesForDump = 0xB,
    StCounterHvSubsumedPages = 0xC,
    StCounterHvMAXIMUM = 0xD,
} HV_HYPERVISOR_COUNTER, *PHV_HYPERVISOR_COUNTER;

#define HV_STATISTICS_GROUP_HVA_LENGTH 40
#define HV_STATISTICS_GROUP_HVV_LENGTH 0

// Hypervisor Logical Processor counter set
typedef enum _HV_CPU_COUNTER
{
    // Windows Driver Kit version 7.1.0 era definitions

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
    StLpCounterMAXIMUM,

    // Windows 11 Build 26100 era definitions

    StCounterLpGlobalTime = 0x1,
    StCounterLpTotalRunTime = 0x2,
    StCounterLpHypervisorRunTime = 0x3,
    StCounterLpHardwareInterrupts = 0x4,
    StCounterLpContextSwitches = 0x5,
    StCounterLpInterProcessorInterrupts = 0x6,
    StCounterLpSchedulerInterrupts = 0x7,
    StCounterLpTimerInterrupts = 0x8,
    StCounterLpInterProcessorInterruptsSent = 0x9,
    StCounterLpProcessorHalts = 0xA,
    StCounterLpMonitorTransitionCost = 0xB,
    StCounterLpContextSwitchTime = 0xC,
    StCounterLpC1TransitionsCount = 0xD,
    StCounterLpC1RunTime = 0xE,
    StCounterLpC2TransitionsCount = 0xF,
    StCounterLpC2RunTime = 0x10,
    StCounterLpC3TransitionsCount = 0x11,
    StCounterLpC3RunTime = 0x12,
    StCounterLpRootVpIndex = 0x13,
    StCounterLpIdleSequenceNumber = 0x14,
    StCounterLpGlobalTscCount = 0x15,
    StCounterLpActiveTscCount = 0x16,
    StCounterLpIdleAccumulation = 0x17,
    StCounterLpReferenceCycleCount0 = 0x18,
    StCounterLpActualCycleCount0 = 0x19,
    StCounterLpReferenceCycleCount1 = 0x1A,
    StCounterLpActualCycleCount1 = 0x1B,
    StCounterLpProximityDomainId = 0x1C,
    StCounterLpPostedInterruptNotifications = 0x1D,
    StCounterLpBranchPredictorFlushes = 0x1E,
    StCounterLpCounterRefreshSequenceNumber = 0x1F,
    StCounterLpCounterRefreshReferenceTime = 0x20,
    StCounterLpIdleAccumulationSnapshot = 0x21,
    StCounterLpActiveTscCountSnapshot = 0x22,
    StCounterLpHwpRequestContextSwitches = 0x23,
    StCounterLpPlaceholder2 = 0x24,
    StCounterLpPlaceholder3 = 0x25,
    StCounterLpPlaceholder4 = 0x26,
    StCounterLpPlaceholder5 = 0x27,
    StCounterLpPlaceholder6 = 0x28,
    StCounterLpPlaceholder7 = 0x29,
    StCounterLpPlaceholder8 = 0x2A,
    StCounterLpPlaceholder9 = 0x2B,
    StCounterLpSchLocalRunListSize = 0x2C,
    StCounterLpReserveGroupId = 0x2D,
    StCounterLpRunningPriority = 0x2E,
    StCounterLpMAXIMUM = 0x2F,
} HV_CPU_COUNTER;

#define HV_STATISTICS_GROUP_LPA_LENGTH 144
#define HV_STATISTICS_GROUP_LPV_LENGTH 0

// Partition counter set
typedef enum _HV_PROCESS_COUNTER
{
    // Windows Driver Kit version 7.1.0 era definitions

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
    StPtCounterMAXIMUM,

    // Windows 11 Build 26100 era definitions

    StCounterPtVirtualProcessors = 0x1,
    StCounterPtTlbSize = 0x3,
    StCounterPtAddressSpaces = 0x4,
    StCounterPtDepositedPages = 0x5,
    StCounterPtGpaPages = 0x6,
    StCounterPtGpaSpaceModifications = 0x7,
    StCounterPtVirtualTlbFlushEntires = 0x8,
    StCounterPtRecommendedTlbSize = 0x9,
    StCounterPtGpaPages4K = 0xA,
    StCounterPtGpaPages2M = 0xB,
    StCounterPtGpaPages1G = 0xC,
    StCounterPtGpaPages512G = 0xD,
    StCounterPtDevicePages4K = 0xE,
    StCounterPtDevicePages2M = 0xF,
    StCounterPtDevicePages1G = 0x10,
    StCounterPtDevicePages512G = 0x11,
    StCounterPtAttachedDevices = 0x12,
    StCounterPtDeviceInterruptMappings = 0x13,
    StCounterPtIoTlbFlushes = 0x14,
    StCounterPtIoTlbFlushCost = 0x15,
    StCounterPtDeviceInterruptErrors = 0x16,
    StCounterPtDeviceDmaErrors = 0x17,
    StCounterPtDeviceInterruptThrottleEvents = 0x18,
    StCounterPtSkippedTimerTicks = 0x19,
    StCounterPtPartitionId = 0x1A,
    StCounterPtHwpRequestValue = 0x1B,
    StCounterPtMAXIMUM = 0x1C,
} HV_PROCESS_COUNTER;

#define HV_STATISTICS_GROUP_PTA_LENGTH 8
#define HV_STATISTICS_GROUP_PTV_LENGTH 88

// Hypervisor Virtual Processor counter set
typedef enum _HV_THREAD_COUNTER
{
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
    StCounterVpTotalRunTime = 0x1,
    StCounterVpHypervisorRunTime = 0x2,
    StCounterVpRemoteNodeRunTime = 0x3,
    StCounterVpNormalizedRunTime = 0x4,
    StCounterVpIdealCpu = 0x5,
    StCounterVpHypercallsCount = 0x7,
    StCounterVpHypercallsTime = 0x8,
    StCounterVpSysRegAccessesCount = 0x9,
    StCounterVpSysRegAccessesTime = 0xA,
    StCounterVpSmcInstructionsCount = 0xB,
    StCounterVpSmcInstructionsTime = 0xC,
    StCounterVpOtherInterceptsCount = 0xD,
    StCounterVpOtherInterceptsTime = 0xE,
    StCounterVpExternalInterruptsCount = 0xF,
    StCounterVpExternalInterruptsTime = 0x10,
    StCounterVpPendingInterruptsCount = 0x11,
    StCounterVpPendingInterruptsTime = 0x12,
    StCounterVpGuestPageTableMaps = 0x13,
    StCounterVpLargePageTlbFills = 0x14,
    StCounterVpSmallPageTlbFills = 0x15,
    StCounterVpReflectedGuestPageFaults = 0x16,
    StCounterVpMemoryInterceptMessages = 0x17,
    StCounterVpOtherMessages = 0x18,
    StCounterVpLogicalProcessorMigrations = 0x19,
    StCounterVpAddressDomainFlushes = 0x1A,
    StCounterVpAddressSpaceFlushes = 0x1B,
    StCounterVpSyntheticInterrupts = 0x1C,
    StCounterVpVirtualInterrupts = 0x1D,
    StCounterVpApicSelfIpisSent = 0x1E,
    StCounterVpGpaSpaceHypercalls = 0x1F,
    StCounterVpLogicalProcessorHypercalls = 0x20,
    StCounterVpLongSpinWaitHypercalls = 0x21,
    StCounterVpOtherHypercalls = 0x22,
    StCounterVpSyntheticInterruptHypercalls = 0x23,
    StCounterVpVirtualInterruptHypercalls = 0x24,
    StCounterVpVirtualMmuHypercalls = 0x25,
    StCounterVpVirtualProcessorHypercalls = 0x26,
    StCounterVpHardwareInterrupts = 0x27,
    StCounterVpNestedPageFaultInterceptsCount = 0x28,
    StCounterVpNestedPageFaultInterceptsTime = 0x29,
    StCounterVpLogicalProcessorDispatches = 0x2A,
    StCounterVpWaitingForCpuTime = 0x2B,
    StCounterVpExtendedHypercalls = 0x2C,
    StCounterVpExtendedHypercallInterceptMessages = 0x2D,
    StCounterVpMbecNestedPageTableSwitches = 0x2E,
    StCounterVpOtherReflectedGuestExceptions = 0x2F,
    StCounterVpGlobalIoTlbFlushes = 0x30,
    StCounterVpGlobalIoTlbFlushCost = 0x31,
    StCounterVpLocalIoTlbFlushes = 0x32,
    StCounterVpLocalIoTlbFlushCost = 0x33,
    StCounterVpFlushGuestPhysicalAddressSpaceHypercalls = 0x34,
    StCounterVpFlushGuestPhysicalAddressListHypercalls = 0x35,
    StCounterVpPostedInterruptNotifications = 0x36,
    StCounterVpPostedInterruptScans = 0x37,
    StCounterVpTotalCoreRunTime = 0x38,
    StCounterVpMaximumRunTime = 0x39,
    StCounterVpWaitingForCpuTimeBucket0 = 0x3A,
    StCounterVpWaitingForCpuTimeBucket1 = 0x3B,
    StCounterVpWaitingForCpuTimeBucket2 = 0x3C,
    StCounterVpWaitingForCpuTimeBucket3 = 0x3D,
    StCounterVpWaitingForCpuTimeBucket4 = 0x3E,
    StCounterVpWaitingForCpuTimeBucket5 = 0x3F,
    StCounterVpWaitingForCpuTimeBucket6 = 0x40,
    StCounterVpHwpRequestContextSwitches = 0x41,
    StCounterVpPlaceholder2 = 0x42,
    StCounterVpPlaceholder3 = 0x43,
    StCounterVpPlaceholder4 = 0x44,
    StCounterVpPlaceholder5 = 0x45,
    StCounterVpPlaceholder6 = 0x46,
    StCounterVpPlaceholder7 = 0x47,
    StCounterVpPlaceholder8 = 0x48,
    StCounterVpContentionTime = 0x49,
    StCounterVpWakeUpTime = 0x4A,
    StCounterVpSchedulingPriority = 0x4B,
    StCounterVpVtl1DispatchCount = 0x4C,
    StCounterVpVtl2DispatchCount = 0x4D,
    StCounterVpVtl2DispatchBucket0 = 0x4E,
    StCounterVpVtl2DispatchBucket1 = 0x4F,
    StCounterVpVtl2DispatchBucket2 = 0x50,
    StCounterVpVtl2DispatchBucket3 = 0x51,
    StCounterVpVtl2DispatchBucket4 = 0x52,
    StCounterVpVtl2DispatchBucket5 = 0x53,
    StCounterVpVtl2DispatchBucket6 = 0x54,
    StCounterVpVtl1RunTime = 0x55,
    StCounterVpVtl2RunTime = 0x56,
    StCounterVpIommuHypercalls = 0x57,
    StCounterVpCpuGroupHypercalls = 0x58,
    StCounterVpVsmHypercalls = 0x59,
    StCounterVpEventLogHypercalls = 0x5A,
    StCounterVpDeviceDomainHypercalls = 0x5B,
    StCounterVpDepositHypercalls = 0x5C,
    StCounterVpSvmHypercalls = 0x5D,
    StCounterVpMAXIMUM = 0x5E,
#endif
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

typedef HV_UINT64 HV_PROCESSOR_HW_ID, *PHV_PROCESSOR_HW_ID;

// The HV_PROCESSOR_INFO structures contains additional information about each
// physical processor
typedef struct _HV_PROCESSOR_INFO
{
#if defined(_M_AMD64) || defined(_M_IX86)
    // The Local APIC ID for the processor.
    HV_UINT32 LocalApicId;
#elif defined(_M_ARM64)
    HV_PROCESSOR_HW_ID ProcessorHwId;
#endif
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
    union
    {
        // The proximity domain this memory range resides in.
        HV_PROXIMITY_DOMAIN_ID ProximityDomainId;
        union
        {
            HV_UINT8 AsUINT8;
            struct
            {
                HV_UINT8 IsRam : 1;
                HV_UINT8 IsNonRootRam : 1;
                HV_UINT8 IsHotAddableRam : 1;
                HV_UINT8 IsBadRam : 1;
                HV_UINT8 Reserved : 4;
            };
        } Attributes;
    };
} HV_MEMORY_RANGE_INFO, *PHV_MEMORY_RANGE_INFO;
typedef const HV_MEMORY_RANGE_INFO* PCHV_MEMORY_RANGE_INFO;

#define HV_EVENTLOG_BUFFER_INDEX_NONE 0xFFFFFFFF

// Define all the trace buffer types.
typedef HV_EVENTLOG_TYPE _HV_EVENTLOG_TYPE;

typedef enum
{
    HvEventLogTypeSystemDiagnostics = 0x00000002,
} HV_EVENTLOG_TYPE_PRIVATE;

// Define all the trace buffer states.
typedef enum
{
    HvEventLogBufferStateStandby = 0x0,
    HvEventLogBufferStateFree = 0x1,
    HvEventLogBufferStateInUse = 0x2,
    HvEventLogBufferStateComplete = 0x3,
    HvEventLogBufferStateReady = 0x4,
    HvEventLogBufferStateUnmapping = 0x5,
    HvEventLogBufferStateDeleting = 0x6,
    HvEventLogBufferStateProcessorListInUse = 0x7,
} HV_EVENTLOG_BUFFER_STATE;

// Define time source enum and structure.
typedef enum
{
    HvEventLogEntryTimeReference = 0x0,
    HvEventLogEntryTimeTsc = 0x1,
    HvEventLogEntryTimeQpc = 0x2,
} HV_EVENTLOG_ENTRY_TIME_BASIS;

typedef union
{
    HV_NANO100_TIME ReferenceTime;
    HV_TIME_STAMP TimeStamp;
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
        HV_TIME_STAMP TimeStamp;
        HV_NANO100_TIME ReferenceTime;
    };
    HV_UINT64 Reserved1;
    HV_UINT64 Reserved2;
    HV_UINT16 LogicalProcessor; // ProcessorNumber
    HV_UINT16 LoggerId;
    volatile HV_EVENTLOG_BUFFER_STATE BufferState; // (Free/GeneralLogging/Flush)
    HV_UINT32 NextBufferOffset; // Offset
    union
    {
        HV_EVENTLOG_TYPE Type; // BufferFlag and BufferType
        struct
        {
            HV_UINT16 BufferFlag;
            HV_UINT16 BufferType;
        };
    };
    HV_EVENTLOG_BUFFER_INDEX NextBufferIndex; // Padding1
    HV_UINT32 LpSequenceNumber;
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
        HV_TIME_STAMP TimeStamp;
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
#if defined(_M_AMD64) || defined(_M_IX86)
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
    HvStateProcessorXsaveSaveAreaMismatch = 34,
#elif defined(_M_ARM64)
    HvStateCorruptData = 2,
    HvStateUnsupportedVersion = 3,
    HvStateProcessorFeatureMismatch = 4,
    HvStateIncompatibleProcessor = 5,
    HvStateProcessorCacheLineFlushSizeMismatch = 6,
#endif
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
    HvProcessorVendorAmd = 0x0,
    HvProcessorVendorIntel = 0x1,
    HvProcessorVendorHygon = 0x2,
    HvProcessorVendorArm = 0x10,
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
        HV_UINT64 TGran16 : 1;
        HV_UINT64 TGran64 : 1;
        HV_UINT64 Haf : 1;
        HV_UINT64 Hdbs : 1;
        HV_UINT64 Pan : 1;
        HV_UINT64 AtS1E1 : 1;
        HV_UINT64 Uao : 1;
        HV_UINT64 El0Aarch32 : 1;
        HV_UINT64 Fp : 1;
        HV_UINT64 FpHp : 1;
        HV_UINT64 AdvSimd : 1;
        HV_UINT64 AdvSimdHp : 1;
        HV_UINT64 GicV3V4 : 1;
        HV_UINT64 GicV4P1 : 1;
        HV_UINT64 Ras : 1;
        HV_UINT64 PmuV3 : 1;
        HV_UINT64 PmuV3ArmV81 : 1;
        HV_UINT64 PmuV3ArmV84 : 1;
        HV_UINT64 PmuV3ArmV85 : 1;
        HV_UINT64 Aes : 1;
        HV_UINT64 PolyMul : 1;
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
        HV_UINT64 DcCvap : 1;
        HV_UINT64 DcCvadp : 1;
        HV_UINT64 ApaBase : 1;
        HV_UINT64 ApaEp : 1;
        HV_UINT64 ApaEp2 : 1;
        HV_UINT64 ApaEp2Fp : 1;
        HV_UINT64 ApaEp2Fpc : 1;
        HV_UINT64 Jscvt : 1;
        HV_UINT64 Fcma : 1;
        HV_UINT64 RcpcV83 : 1;
        HV_UINT64 RcpcV84 : 1;
        HV_UINT64 Gpa : 1;
        HV_UINT64 L1ipPipt : 1;
        HV_UINT64 DzPermitted : 1;
        HV_UINT64 Ssbs : 1;
        HV_UINT64 SsbsRw : 1;
        HV_UINT64 SmcccW1Supported : 1;
        HV_UINT64 SmcccW1Mitigated : 1;
        HV_UINT64 SmcccW2Supported : 1;
        HV_UINT64 SmcccW2Mitigated : 1;
        HV_UINT64 Csv2 : 1;
        HV_UINT64 Csv3 : 1;
        HV_UINT64 Sb : 1;
        HV_UINT64 Idc : 1;
        HV_UINT64 Dic : 1;
        HV_UINT64 TlbiOs : 1;
        HV_UINT64 TlbiOsRange : 1;
        HV_UINT64 FlagsM : 1;
        HV_UINT64 FlagsM2 : 1;
        HV_UINT64 Bf16 : 1;
        HV_UINT64 Ebf16 : 1;
        HV_UINT64 SveBf16 : 1;
        HV_UINT64 SveEbf16 : 1;
        HV_UINT64 I8mm : 1;
        HV_UINT64 SveI8mm : 1;
        HV_UINT64 Frintts : 1;
        HV_UINT64 Specres : 1;
        HV_UINT64 Mtpmu : 1;
        HV_UINT64 Rpres : 1;
        HV_UINT64 Exs : 1;
        HV_UINT64 SpecSei : 1;
        HV_UINT64 Ets : 1;
        HV_UINT64 Afp : 1;
        HV_UINT64 Iesb : 1;
        HV_UINT64 Rng : 1;
        HV_UINT64 Lse2 : 1;
        HV_UINT64 Idst : 1;
        HV_UINT64 RasV1P1 : 1;
        HV_UINT64 RasFracV1P1 : 1;
        HV_UINT64 Sel2 : 1;
        HV_UINT64 AmuV1 : 1;
        HV_UINT64 AmuV1P1 : 1;
        HV_UINT64 Dit : 1;
        HV_UINT64 Ccidx : 1;
        HV_UINT64 FgtForIntercepts : 1;
        HV_UINT64 L1ipVpipt : 1;
        HV_UINT64 L1ipVipt : 1;
        HV_UINT64 DebugV8 : 1;
        HV_UINT64 DebugV8P2 : 1;
        HV_UINT64 DebugV8P4 : 1;
        HV_UINT64 PmuV3ArmV87 : 1;
        HV_UINT64 DoubleLock : 1;
        HV_UINT64 Clrbhb : 1;
        HV_UINT64 Spe : 1;
        HV_UINT64 SpeV1P1 : 1;
        HV_UINT64 SpeV1P2 : 1;
        HV_UINT64 TtCnp : 1;
        HV_UINT64 Hpds : 1;
        HV_UINT64 Sve : 1;
        HV_UINT64 SveV2 : 1;
        HV_UINT64 SveV2P1 : 1;
        HV_UINT64 SpecFpacc : 1;
        HV_UINT64 ReservedBank1 : 23;
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
typedef const HV_PARTITION_PROCESSOR_FEATURES* PCHV_PARTITION_PROCESSOR_FEATURES;

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
#if defined(_M_AMD64) || defined(_M_IX86)
    struct
    {
        HV_UINT64 XsaveSupport : 1;
        HV_UINT64 XsaveoptSupport : 1;
        HV_UINT64 AvxSupport : 1;
        HV_UINT64 Reserved1 : 61;
    };
#endif
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
#if defined(_M_AMD64) || defined(_M_IX86)
        HV_UINT64 Suspended : 1;
        HV_UINT64 TlbLocked : 1;
        HV_UINT64 Reserved : 62;
#elif defined(_M_ARM64)
        HV_UINT64 Suspended : 1;
        HV_UINT64 Reserved : 63;
#endif
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
        HV_UINT64 GlobalInterruptDisable : 1;
        HV_UINT64 Reserved : 61;
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

#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef union _HV_ARM64_PENDING_EXCEPTION_EVENT
{
    HV_UINT64 AsUINT64[3];
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3;
        HV_UINT8 Reserved : 4;
        HV_UINT64 EsrElx;
        HV_UINT64 FarElx;
    };
} HV_ARM64_PENDING_EXCEPTION_EVENT, *PHV_ARM64_PENDING_EXCEPTION_EVENT;
#endif

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

#if defined(_M_ARM64)
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
        HV_UINT64 InterruptionType : 1; // HV_ARM64_PENDING_INTERRUPTION_TYPE
        HV_UINT64 Reserved : 30;
        HV_UINT64 ErrorCode : 32;
    };
} HV_ARM64_PENDING_INTERRUPTION_REGISTER, *PHV_ARM64_PENDING_INTERRUPTION_REGISTER;

typedef union _HV_ARM64_INTERRUPT_STATE_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 InterruptShadow : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_ARM64_INTERRUPT_STATE_REGISTER, *PHV_ARM64_INTERRUPT_STATE_REGISTER;

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
#endif

typedef union _HV_REGISTER_VALUE_PRIVATE
{
    HV_EXPLICIT_SUSPEND_REGISTER ExplicitSuspend;
    HV_INTERCEPT_SUSPEND_REGISTER InterceptSuspend;
    HV_DISPATCH_SUSPEND_REGISTER DispatchSuspend;
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

#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
    HvInterceptTypeException = 0x00000003,
    HvInterceptTypeReserved0 = 0x00000004,
    HvInterceptTypeMmio = 0x00000005,
    HvInterceptTypeHypercall = 0x00000008,
    HvInterceptTypeUnknownSynicConnection = 0x0000000D,
    HvInterceptTypeRetargetInterruptWithUnknownDeviceId = 0x0000000F,
    HvInterceptTypeRegister = 0x00000012,
    HvInterceptTypeMax = 0x00000013,
#endif
    HvInterceptTypeInvalid = 0xFFFFFFFF
} HV_INTERCEPT_TYPE, *PHV_INTERCEPT_TYPE;

// Define IO port type.
typedef HV_UINT16 HV_X64_IO_PORT, *PHV_X64_IO_PORT;

// Define intercept parameters.
typedef union _HV_INTERCEPT_PARAMETERS
{
    // HV_INTERCEPT_PARAMETERS is defined to be an 8-byte field.
    HV_UINT64 AsUINT64;
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
    HV_UINT16 ExceptionVector;
#endif
} HV_INTERCEPT_PARAMETERS, *PHV_INTERCEPT_PARAMETERS;

typedef union _HV_INTERCEPT_PARAMETERS_EX
{
    HV_UINT64 InterceptParamsRaw[16];
    struct
    {
        HV_REGISTER_NAME RegisterName;
        HV_UINT32 AccessTypeMask;
        HV_UINT64 WriteInterceptMask;
        HV_UINT64 Reserved[14];
    } RegisterInterceptParams;
} HV_INTERCEPT_PARAMETERS_EX, *PHV_INTERCEPT_PARAMETERS_EX;

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

// Read and write GPA access flags.
typedef union _HV_ACCESS_GPA_CONTROL_FLAGS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT8 CacheType; // Cache type for access
        HV_INPUT_VTL InputVtl;
        HV_UINT16 ReservedZ0;
        HV_UINT32 ReservedZ1;
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
    HvCacheTypeUncached = 0,
    HvCacheTypeX64WriteCombining = 1,
    HvCacheTypeWriteCombining = 1,
    HvCacheTypeX64WriteThrough = 4,
    HvCacheTypeWriteThrough = 4,
    HvCacheTypeX64WriteProtected = 5,
    HvCacheTypeX64WriteBack = 6,
    HvCacheTypeWriteBack = 6,
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
    HvMessageTypeEnablePartitionVtlIntercept = 0x80000005,

    // Opaque intercept message. The original intercept message is only
    // accessible from the mapped intercept message page.

    HvMessageTypeOpaqueIntercept = 0x8000003F,

    // SynIC intercepts

    HvMessageTypeSynicSintIntercept = 0x80000061,
    HvMessageTypeSynicSintDeliverable = 0x80000062,

    HvMessageInsufficientMemory = 0x80000071,
    HvMessageMirroringNotification = 0x80000072,
    HvMessageRestartCompletionNotification = 0x80000073,

    // Async call completion intercept

    HvMessageTypeAsyncCallCompletion = 0x80000070,

    // Platform-specific processor intercept messages

#if defined(_M_AMD64) || defined(_M_IX86)
    HvMessageTypeX64LegacyFpError = 0x80010005,
    HvMessageTypeX64ProxyInterruptIntercept = 0x8001000f,
#elif defined(_M_ARM64)
    HvMessageTypeArm64ResetInterceptUndocumented = 0x8001000C,
#endif
} HV_MESSAGE_TYPE_PRIVATE, *PHV_MESSAGE_TYPE_PRIVATE;

#define HV_MESSAGE_TYPE_HYPERVISOR_MASK (0x80000000)

// Define APIC EOI message.
typedef struct _HV_X64_APIC_EOI_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_INTERRUPT_VECTOR InterruptVector;
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
            HV_UINT64 RsvdZ;
        } MessagePortInfo;
        struct
        {
            HV_SYNIC_SINT_INDEX TargetSint;
            HV_VP_INDEX TargetVp;
            HV_UINT16 BaseFlagNumber;
            HV_UINT16 FlagCount;
            HV_UINT32 RsvdZ;
        } EventPortInfo;
        struct
        {
            HV_GPA MonitorAddress;
            HV_UINT64 RsvdZ;
        } MonitorPortInfo;
        struct
        {
            HV_UINT32 TargetSint;
            HV_VP_INDEX TargetVp;
            HV_UINT64 RsvdZ;
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
            HV_UINT64 RsvdZ;
        } MessageConnectionInfo;
        struct
        {
            HV_UINT64 RsvdZ;
        } EventConnectionInfo;
        struct
        {
            HV_GPA MonitorAddress;
        } MonitorConnectionInfo;
        struct
        {
            HV_GPA GuestPhysicalAddress;
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
    HvPortPropertyPostCount = 0x0,
    HvPortPropertyPreferredTargetVp = 0x1,
    HvPortPropertyMonitorAddress = 0x2,
    HvPortPropertyUseRingBuffer = 0x3,
    HvPortPropertyTargetVp = 0x4,
    HvPortPropertyPreferredTargetDuration = 0x5,
    HvPortPropertyRetryPostMessage = 0x6,
    HvPortPropertyInterceptOnSignal = 0x7,
    HvPortPropertySignalCount = 0x8,
    HvPortPropertyPendingRing = 0x9,
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

typedef union _HV_FAULT_DEVICE_ID
{
    HV_UINT64 AsUINT64;
    HV_UINT64 StreamId;
} HV_FAULT_DEVICE_ID, *PHV_FAULT_DEVICE_ID;

typedef struct _HV_IOMMU_FAULT_MESSAGE_PAYLOAD_PRIVATE
{
    HV_UINT64 Reserved0;
    struct
    {
        HV_UINT32 Reserved1 : 2;
        HV_UINT32 IsStage1Fault : 1;
    } Flags;
    HV_UINT64 LogicalId;
    HV_FAULT_DEVICE_ID DeviceId;
    HV_UINT64 FaultAddress;
    HV_GVA IommuBaseAddress;
} HV_IOMMU_FAULT_MESSAGE_PAYLOAD_PRIVATE, *PHV_IOMMU_FAULT_MESSAGE_PAYLOAD_PRIVATE;

typedef struct _HV_SINT_NOTIFICATION_MESSAGE_PAYLOAD
{
    HV_UINT32 SintIndex;
} HV_SINT_NOTIFICATION_MESSAGE_PAYLOAD, *PHV_SINT_NOTIFICATION_MESSAGE_PAYLOAD;

typedef struct HV_DECLSPEC_ALIGN(16) _HV_MESSAGE_PRIVATE
{
    HV_MESSAGE_HEADER_PRIVATE Header;
    union
    {
        HV_IOMMU_FAULT_MESSAGE_PAYLOAD_PRIVATE IommuFaultPayload;
        HV_SINT_NOTIFICATION_MESSAGE_PAYLOAD SintNotificationPayload;
    };
} HV_MESSAGE_PRIVATE, *PHV_MESSAGE_PRIVATE;

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
        HV_UINT32 Mda : 32;
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
    HV_UINT32 RsvdZ1;
    HV_MONITOR_TRIGGER_GROUP TriggerGroup[4];
    HV_UINT64 RsvdZ2[3];
    HV_INT32 NextCheckTime[4][32];
    HV_UINT16 Latency[4][32];
    HV_UINT64 RsvdZ3[32];
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

typedef struct _HV_CRASHDUMP_AREA_V3
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

} HV_CRASHDUMP_AREA_V3, *PHV_CRASHDUMP_AREA_V3;

typedef struct _HV_CRASHDUMP_AREA_V4
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

} HV_CRASHDUMP_AREA_V4, *PHV_CRASHDUMP_AREA_V4;

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
            HV_UINT32 NotAllProcessorsSuspended : 1;
            HV_UINT32 ExcludesNonEssentialPages : 1;
            HV_UINT32 Reserved : 29;
        };
    };

    // Loaded Module Information.
    union
    {
        struct
        {
            HV_UINT64 HypervisorBase;
            HV_UINT32 SizeOfImage;
            HV_UINT32 CheckSum;
        };
        struct
        {
            HV_UINT64 Base;
            HV_UINT32 Size;
            HV_UINT32 Checksum;
            HV_UINT32 Timestamp;
        } ImageInfo[3];
    };

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

    HV_UINT8 Partial;

} HV_CRASHDUMP_AREA, *PHV_CRASHDUMP_AREA;

// Define virtual processor execution state bitfield.
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef union _HV_ARM64_VP_EXECUTION_STATE
{
    HV_UINT16 AsUINT16;
    struct
    {
        HV_UINT16 Cpl : 2;
        HV_UINT16 DebugActive : 1;
        HV_UINT16 InterruptionPending : 1;
        HV_UINT16 Vtl : 4;
        HV_UINT16 VirtualizationFaultActive : 1;
        HV_UINT16 Reserved : 7;
    };
} HV_ARM64_VP_EXECUTION_STATE, *PHV_ARM64_VP_EXECUTION_STATE;
#endif

// Define intercept message header structure.
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_INTERCEPT_MESSAGE_HEADER
{
    HV_VP_INDEX VpIndex;
    HV_UINT8 InstructionLength;
    HV_UINT8 InterceptAccessType;
    HV_ARM64_VP_EXECUTION_STATE ExecutionState;
    HV_UINT64 Pc;
    HV_UINT64 Cpsr;
} HV_ARM64_INTERCEPT_MESSAGE_HEADER, *PHV_ARM64_INTERCEPT_MESSAGE_HEADER;
#endif

// Define memory access information structure.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_MEMORY_ACCESS_INFO
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
#elif defined(_M_ARM64)
typedef union _HV_ARM64_MEMORY_ACCESS_INFO
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 GvaValid : 1;
        HV_UINT8 GvaGpaValid : 1;
        HV_UINT8 HypercallOutputPending : 1;
        HV_UINT8 Reserved : 5;
    };
} HV_ARM64_MEMORY_ACCESS_INFO, *PHV_ARM64_MEMORY_ACCESS_INFO;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_MEMORY_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_CACHE_TYPE CacheType;
    HV_UINT8 InstructionByteCount;
    HV_ARM64_MEMORY_ACCESS_INFO MemoryAccessInfo;
    HV_UINT16 Reserved1;
    HV_UINT8 InstructionBytes[4];
    HV_UINT32 Reserved2;
    HV_UINT64 GuestVirtualAddress;
    HV_UINT64 GuestPhysicalAddress;
    HV_UINT64 Syndrome;
} HV_ARM64_MEMORY_INTERCEPT_MESSAGE, *PHV_ARM64_MEMORY_INTERCEPT_MESSAGE;
#endif

// Define MSR intercept message structure.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_X64_MSR_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT32 MsrNumber;
    HV_UINT32 Reserved;
    HV_UINT64 Rdx;
    HV_UINT64 Rax;
} HV_X64_MSR_INTERCEPT_MESSAGE, *PHV_X64_MSR_INTERCEPT_MESSAGE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_MSR_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT64 VirtualRegisterNumber;
    HV_UINT64 X0;
    HV_UINT64 X1;
} HV_ARM64_MSR_INTERCEPT_MESSAGE, *PHV_ARM64_MSR_INTERCEPT_MESSAGE;
#endif

// Define exception information structure.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_EXCEPTION_INFO
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 ErrorCodeValid : 1;
        HV_UINT8 SoftwareException : 1;
        HV_UINT8 Reserved : 6;
    };
} HV_X64_EXCEPTION_INFO, *PHV_X64_EXCEPTION_INFO;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_EXCEPTION_INFO
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 ErrorCodeValid : 1;
        HV_UINT8 Reserved : 7;
    };
} HV_ARM64_EXCEPTION_INFO, *PHV_ARM64_EXCEPTION_INFO;
#endif

// Define exception intercept message.
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef enum _HV_ARM64_SYNTHETIC_EXCEPTION_TYPE
{
    HvArm64SyntheticExceptionTypeSmc = 0x0,
    HvArm64SyntheticExceptionTypeSecure = 0x1,
    HvArm64SyntheticExceptionTypeCrashdump = 0x2,
    HvArm64SyntheticExceptionTypeVirtualizationFault = 0x3,
    HvArm64SyntheticExceptionTypeMax = 0x40,
} HV_ARM64_SYNTHETIC_EXCEPTION_TYPE, *PHV_ARM64_SYNTHETIC_EXCEPTION_TYPE;

typedef struct _HV_ARM64_EXCEPTION_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_ARM64_SYNTHETIC_EXCEPTION_TYPE ExceptionType;
    HV_UINT64 ExceptionSyndrome;
    HV_UINT64 FaultGVA;
    HV_UINT64 FaultGPA;
    HV_UINT64 FaultSPA;
} HV_ARM64_EXCEPTION_INTERCEPT_MESSAGE, *PHV_ARM64_EXCEPTION_INTERCEPT_MESSAGE;
#endif

// Define virtual processor unrecoverable error message.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
} HV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE, *PHV_X64_UNRECOVERABLE_EXCEPTION_MESSAGE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_UNRECOVERABLE_EXCEPTION_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
} HV_ARM64_UNRECOVERABLE_EXCEPTION_MESSAGE, *PHV_ARM64_UNRECOVERABLE_EXCEPTION_MESSAGE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
#define HV_HYPERCALL_INTERCEPT_MAX_XMM_REGISTERS 6
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
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERCALL_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT16 Immediate;
    HV_UINT16 Reserved;
    HV_UINT32 Isolated : 1;
    HV_UINT32 Reserved2 : 31;
    HV_UINT64 X[18];
} HV_ARM64_HYPERCALL_INTERCEPT_MESSAGE, *PHV_ARM64_HYPERCALL_INTERCEPT_MESSAGE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_REGISTER_ACCESS_INFO
{
    HV_REGISTER_VALUE SourceValue;
    HV_REGISTER_NAME DestinationRegister;
    HV_UINT64 SourceAddress;
    HV_UINT64 DestinationAddress;
} HV_X64_REGISTER_ACCESS_INFO, *PHV_X64_REGISTER_ACCESS_INFO;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_REGISTER_ACCESS_INFO
{
    HV_REGISTER_VALUE SourceValue;
    HV_REGISTER_NAME DestinationRegister;
} HV_ARM64_REGISTER_ACCESS_INFO, *PHV_ARM64_REGISTER_ACCESS_INFO;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_X64_REGISTER_INTERCEPT_MESSAGE
{
    HV_X64_INTERCEPT_MESSAGE_HEADER Header;
    struct
    {
        HV_UINT8 IsMemoryOp : 1;
        HV_UINT8 Reserved : 7;
    };
    HV_UINT8 Reserved1[3];
    HV_REGISTER_NAME RegisterName;
    HV_X64_REGISTER_ACCESS_INFO AccessInfo;
} HV_X64_REGISTER_INTERCEPT_MESSAGE, *PHV_X64_REGISTER_INTERCEPT_MESSAGE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_REGISTER_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT8 IsMemoryOp : 1;
    HV_UINT8 Reserved : 7;
    HV_UINT8 Reserved8;
    HV_UINT16 Reserved16;
    HV_REGISTER_NAME RegisterName;
    HV_ARM64_REGISTER_ACCESS_INFO AccessInfo;
} HV_ARM64_REGISTER_INTERCEPT_MESSAGE, *PHV_ARM64_REGISTER_INTERCEPT_MESSAGE;
#endif

// Define invalid virtual processor register message.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_X64_INVALID_VP_REGISTER_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Reserved;
} HV_X64_INVALID_VP_REGISTER_MESSAGE, *PHV_X64_INVALID_VP_REGISTER_MESSAGE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_INVALID_VP_REGISTER_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Reserved;
} HV_ARM64_INVALID_VP_REGISTER_MESSAGE, *PHV_ARM64_INVALID_VP_REGISTER_MESSAGE;
#endif

// Define the unsupported feature codes.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef enum _HV_X64_UNSUPPORTED_FEATURE_CODE
{
    HvUnsupportedFeatureIntercept = 1,
    HvUnsupportedFeatureTaskSwitchTss = 2
} HV_X64_UNSUPPORTED_FEATURE_CODE, *PHV_X64_UNSUPPORTED_FEATURE_CODE;
#elif defined(_M_ARM64)
typedef enum _HV_ARM64_UNSUPPORTED_FEATURE_CODE
{
    HvUnsupportedFeatureIntercept = 0x1,
    HvUnsupportedFeatureMemoryIntercept = 0x2,
} HV_ARM64_UNSUPPORTED_FEATURE_CODE, * PHV_ARM64_UNSUPPORTED_FEATURE_CODE;
#endif

// Define unsupported feature message.
#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_X64_UNSUPPORTED_FEATURE_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_X64_UNSUPPORTED_FEATURE_CODE FeatureCode;
    HV_UINT64 FeatureParameter;
} HV_X64_UNSUPPORTED_FEATURE_MESSAGE, *PHV_X64_UNSUPPORTED_FEATURE_MESSAGE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_UNSUPPORTED_FEATURE_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_ARM64_UNSUPPORTED_FEATURE_CODE FeatureCode;
    HV_UINT64 FeatureParameter;
} HV_ARM64_UNSUPPORTED_FEATURE_MESSAGE, *PHV_ARM64_UNSUPPORTED_FEATURE_MESSAGE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
// Define IO port access information structure.
typedef union _HV_X64_IO_PORT_ACCESS_INFO
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

// Define legacy floating point error message.
typedef struct _HV_X64_LEGACY_FP_ERROR_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Reserved;
} HV_X64_LEGACY_FP_ERROR_MESSAGE, *PHV_X64_LEGACY_FP_ERROR_MESSAGE;

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
    HV_VP_INDEX TargetVpIndex;
    HV_INTERRUPT_VECTOR InterruptVector;
} HV_X64_SIPI_INTERCEPT_MESSAGE, *PHV_X64_SIPI_INTERCEPT_MESSAGE;
#elif defined(_M_ARM64)
typedef enum _HV_ARM64_RESET_TYPE
{
    HvArm64ResetTypePowerOff = 0x0,
    HvArm64ResetTypeReboot = 0x1,
    HvArm64ResetTypeMax = 0x2,
} HV_ARM64_RESET_TYPE, *PHV_ARM64_RESET_TYPE;

typedef struct _HV_ARM64_RESET_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_ARM64_RESET_TYPE ResetType;
} HV_ARM64_RESET_INTERCEPT_MESSAGE, *PHV_ARM64_RESET_INTERCEPT_MESSAGE;

typedef struct _HV_ARM64_MMIO_INTERCEPT_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT64 GuestPhysicalAddress;
    HV_UINT32 AccessSize;
    HV_UINT8 Data[32];
} HV_ARM64_MMIO_INTERCEPT_MESSAGE, *PHV_ARM64_MMIO_INTERCEPT_MESSAGE;

typedef struct _HV_SYNIC_SINT_DELIVERABLE_MESSAGE
{
    HV_ARM64_INTERCEPT_MESSAGE_HEADER Header;
    HV_UINT16 DeliverableSints;
    HV_UINT16 Rsvd1;
    HV_UINT32 Rsvd2;
} HV_SYNIC_SINT_DELIVERABLE_MESSAGE, *PHV_SYNIC_SINT_DELIVERABLE_MESSAGE;
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
    HvPartitionPropertyAllowedParentUserModeHypercalls = 0x00010002,

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
    HvPartitionPropertyApicFrequency = 0x00030004,
    HvPartitionPropertyReferenceTime = 0x00030005,

    // Debugging properties

    HvPartitionPropertyDebugChannelId = 0x00040000,

    // Resource properties

    HvPartitionPropertyVirtualTlbPageCount = 0x00050000,
    HvPartitionPropertyVsmConfig = 0x00050001,
    HvPartitionPropertyZeroMemoryOnReset = 0x00050002,
    HvPartitionPropertyProcessorsPerSocket = 0x00050003,
    HvPartitionPropertyNestedTlbSize = 0x00050004,
    HvPartitionPropertyGpaPageAccessTracking = 0x00050005,
    HvPartitionPropertyVsmPermissionsDirtySinceLastQuery = 0x00050006,
    HvPartitionPropertySgxLaunchControlConfig = 0x00050007,
    HvPartitionPropertyDefaultSgxLaunchControl0 = 0x00050008,
    HvPartitionPropertyDefaultSgxLaunchControl1 = 0x00050009,
    HvPartitionPropertyDefaultSgxLaunchControl2 = 0x0005000A,
    HvPartitionPropertyDefaultSgxLaunchControl3 = 0x0005000B,
    HvPartitionPropertyIsolationState = 0x0005000C,
    HvPartitionPropertyIsolationControl = 0x0005000D,
    HvPartitionPropertyAllocationId = 0x0005000E,
    HvPartitionPropertyMonitoringId = 0x0005000F,
    HvPartitionPropertyImplementedPhysicalAddressBits = 0x00050010,
    HvPartitionPropertyNonArchitecturalCoreSharing = 0x00050011,
    HvPartitionPropertyHypercallDoorbellPage = 0x00050012,
    HvPartitionPropertyCppcRequestValue = 0x00050013,
    HvPartitionPropertyIsolationPolicy = 0x00050014,
    HvPartitionPropertyDmaCapableDevices = 0x00050015,
    HvPartitionPropertyProcessorsPerL3 = 0x00050016,
    HvPartitionPropertyUnimplementedMsrAction = 0x00050017,
    HvPartitionPropertyAmdNodesPerSocket = 0x00050018,
    HvPartitionPropertyReferenceTscPageActive = 0x00050019,
    HvPartitionPropertyAutoEoiEnabled = 0x0005001A,
    HvPartitionPropertyL3CacheWays = 0x0005001B,
    HvPartitionPropertyIsolationType = 0x0005001C,
    HvPartitionPropertyPerfmonMode = 0x0005001D,
    HvPartitionPropertyDepositStatus = 0x0005001E,
    HvPartitionPropertyMirroring = 0x0005001F,
    HvPartitionPropertyMirrorState = 0x00050020,
    HvPartitionPropertyMgmtVtlMaxMemorySections = 0x00050021,
    HvPartitionPropertySevVmgexitOffloads = 0x00050022,
    HvPartitionPropertyPenalizeBusLock = 0x00050023,
    HvPartitionPropertyTopologyApicIdOptIn = 0x00050024,
    HvPartitionPropertyCppcResourcePrioritiesValue = 0x00050025,
    HvPartitionPropertyPartitionDiagBufferConfig = 0x00050026,
    HvPartitionPropertyTerminateOnInstructionTimeout = 0x00050027,

    // Compatibility properties

    HvPartitionPropertyProcessorVendor = 0x00060000,
    HvPartitionPropertyProcessorFeaturesDeprecated = 0x00060001,
    HvPartitionPropertyProcessorXsaveFeatures = 0x00060002,
    HvPartitionPropertyProcessorCLFlushSize = 0x00060003,
    HvPartitionPropertyEnlightenmentModifications = 0x00060004,
    HvPartitionPropertyCompatibilityVersion = 0x00060005,
    HvPartitionPropertyPhysicalAddressWidth = 0x00060006,
    HvPartitionPropertyXsaveStates = 0x00060007,
    HvPartitionPropertyMaxXsaveDataSize = 0x00060008,
    HvPartitionPropertyProcessorClockFrequency = 0x00060009,
    HvPartitionPropertyProcessorFeatures0 = 0x0006000A,
    HvPartitionPropertyProcessorFeatures1 = 0x0006000B,
    HvPartitionPropertyProcessorInstructionCLFlushSize = 0x0006000C,
    HvPartitionPropertyProcessorZeroDataCacheBs = 0x0006000D,
    HvPartitionPropertyProcessorPREbits = 0x0006000E,
    HvPartitionPropertyProcessorPRIbits = 0x0006000F,
    HvPartitionPropertyRootProcessorFeatures0 = 0x00060010,
    HvPartitionPropertyRootProcessorFeatures1 = 0x00060011,
    HvPartitionPropertyRootProcessorXsaveFeatures = 0x00060012,
    HvPartitionPropertyRootSyntheticProcFeatures = 0x00060013,
    HvPartitionPropertyPhysicalAddressSize = 0x00060014,

    HvPartitionPropertyGuestOsId = 0x00070000,

    HvPartitionPropertyProcessorVirtualizationFeatures = 0x00080000,
    HvPartitionPropertyMaxHardwareIsolatedGuests = 0x00080001,
    HvPartitionPropertySnpEnabled = 0x00080002,
    HvPartitionPropertyNestedVmxBasic = 0x00080003,
    HvPartitionPropertyNestedVmxPinbasedCtls = 0x00080004,
    HvPartitionPropertyNestedVmxProcbasedCtls = 0x00080005,
    HvPartitionPropertyNestedVmxExitCtls = 0x00080006,
    HvPartitionPropertyNestedVmxEntryCtls = 0x00080007,
    HvPartitionPropertyNestedVmxMisc = 0x00080008,
    HvPartitionPropertyNestedVmxCr0Fixed0 = 0x00080009,
    HvPartitionPropertyNestedVmxCr0Fixed1 = 0x0008000A,
    HvPartitionPropertyNestedVmxCr4Fixed0 = 0x0008000B,
    HvPartitionPropertyNestedVmxCr4Fixed1 = 0x0008000C,
    HvPartitionPropertyNestedVmxVmcsEnum = 0x0008000D,
    HvPartitionPropertyNestedVmxProcbasedCtls2 = 0x0008000E,
    HvPartitionPropertyNestedVmxEptVpidCap = 0x0008000F,
    HvPartitionPropertyNestedVmxTruePinbasedCtls = 0x00080010,
    HvPartitionPropertyNestedVmxTrueProcbasedCtls = 0x00080011,
    HvPartitionPropertyNestedVmxTrueExitCtls = 0x00080012,
    HvPartitionPropertyNestedVmxTrueEntryCtls = 0x00080013,
    HvPartitionPropertyVhChildrenState = 0x00080100,
    HvPartitionPropertyMaxHierarchicalPartitionCount = 0x00080101,
    HvPartitionPropertyMaxHierarchicalVpCount = 0x00080102,

    HvPartitionPropertyInheritedDeviceDomainReservedRegions = 0x00090000,
    HvPartitionPropertyTdMrConfigId = 0x00090001,
    HvPartitionPropertyTdMrOwner = 0x00090002,
    HvPartitionPropertyTdMrOwnerConfig = 0x00090003,
    HvPartitionPropertyExRootProcessorFeaturesExperimental = 0x00090004,
    HvPartitionPropertyRootVpSharedPages = 0x00090005,

    HVPartitionPropertyExtendedProperyMax = 0x000A0000,
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

    // Feature Access (registers are 128 bits)

    HvRegisterIptFeaturesInfo = 0x00000208,

    // System Reset

    HvRegisterSystemReset = 0x00000230,

    // Pending Event Register

    HvRegisterDeliverabilityNotifications = 0x00010006,
    HvRegisterPendingEvent2 = 0x00010008,
    HvRegisterPendingEvent3 = 0x00010009,

    // Synthetic VSM registers

    HvRegisterVsmVpVtlControl = 0x000D0000,
    HvRegisterGuestVsmPartitionConfig = 0x000D0008,

    HvRegisterHvptControl = 0xD0000009,

#if defined(_M_AMD64) || defined(_M_IX86)

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

#elif defined(_M_ARM64)
    HvArm64RegisterSp = 0x0002001F,
    HvArm64RegisterSpEl0 = 0x00020020,
    HvArm64RegisterSpEl1 = 0x00020021,
    HvArm64RegisterPstate = 0x00020023,

    HvArm64RegisterSpEl2 = 0x00021000,
    HvArm64RegisterElrEl2 = 0x00021001,
    HvArm64RegisterSpsrEl2 = 0x00021002,
    HvArm64RegisterCurrentEl = 0x00021003,
    HvArm64RegisterDaif = 0x00021004,
    HvArm64RegisterDit = 0x00021005,
    HvArm64RegisterNzcv = 0x00021006,
    HvArm64RegisterPan = 0x00021007,
    HvArm64RegisterSpSel = 0x00021008,
    HvArm64RegisterSsbs = 0x00021009,
    HvArm64RegisterTco = 0x0002100A,
    HvArm64RegisterUao = 0x0002100B,
    HvArm64RegisterElrElx = 0x0002100C,
    HvArm64RegisterSpsrElx = 0x0002100D,

    HvArm64RegisterIdRes00El1 = 0x00022000,
    HvArm64RegisterIdRes01El1 = 0x00022001,
    HvArm64RegisterIdRes02El1 = 0x00022002,
    HvArm64RegisterIdRes03El1 = 0x00022003,
    HvArm64RegisterIdRes04El1 = 0x00022004,
    HvArm64RegisterIdRes05El1 = 0x00022005,
    HvArm64RegisterIdRes06El1 = 0x00022006,
    HvArm64RegisterIdRes07El1 = 0x00022007,
    HvArm64RegisterIdPfr0El1 = 0x00022008,
    HvArm64RegisterIdPfr1El1 = 0x00022009,
    HvArm64RegisterIdDfr0El1 = 0x0002200A,
    HvArm64RegisterIdRes13El1 = 0x0002200B,
    HvArm64RegisterIdMmfr0El1 = 0x0002200C,
    HvArm64RegisterIdMmfr1El1 = 0x0002200D,
    HvArm64RegisterIdMmfr2El1 = 0x0002200E,
    HvArm64RegisterIdMmfr3El1 = 0x0002200F,
    HvArm64RegisterIdIsar0El1 = 0x00022010,
    HvArm64RegisterIdIsar1El1 = 0x00022011,
    HvArm64RegisterIdIsar2El1 = 0x00022012,
    HvArm64RegisterIdIsar3El1 = 0x00022013,
    HvArm64RegisterIdIsar4El1 = 0x00022014,
    HvArm64RegisterIdIsar5El1 = 0x00022015,
    HvArm64RegisterIdRes26El1 = 0x00022016,
    HvArm64RegisterIdRes27El1 = 0x00022017,
    HvArm64RegisterIdRes30El1 = 0x00022018,
    HvArm64RegisterIdRes31El1 = 0x00022019,
    HvArm64RegisterIdRes32El1 = 0x0002201A,
    HvArm64RegisterIdRes33El1 = 0x0002201B,
    HvArm64RegisterIdPfr2El1 = 0x0002201C,
    HvArm64RegisterIdRes35El1 = 0x0002201D,
    HvArm64RegisterIdRes36El1 = 0x0002201E,
    HvArm64RegisterIdRes37El1 = 0x0002201F,
    HvArm64RegisterIdAa64Pfr0El1 = 0x00022020,
    HvArm64RegisterIdAa64Pfr1El1 = 0x00022021,
    HvArm64RegisterIdAa64Pfr2El1 = 0x00022022,
    HvArm64RegisterIdRes43El1 = 0x00022023,
    HvArm64RegisterIdAa64Zfr0El1 = 0x00022024,
    HvArm64RegisterIdAa64Smfr0El1 = 0x00022025,
    HvArm64RegisterIdRes46El1 = 0x00022026,
    HvArm64RegisterIdRes47El1 = 0x00022027,
    HvArm64RegisterIdAa64Dfr0El1 = 0x00022028,
    HvArm64RegisterIdAa64Dfr1El1 = 0x00022029,
    HvArm64RegisterIdRes52El1 = 0x0002202A,
    HvArm64RegisterIdRes53El1 = 0x0002202B,
    HvArm64RegisterIdRes54El1 = 0x0002202C,
    HvArm64RegisterIdRes55El1 = 0x0002202D,
    HvArm64RegisterIdRes56El1 = 0x0002202E,
    HvArm64RegisterIdRes57El1 = 0x0002202F,
    HvArm64RegisterIdAa64Isar0El1 = 0x00022030,
    HvArm64RegisterIdAa64Isar1El1 = 0x00022031,
    HvArm64RegisterIdAa64Isar2El1 = 0x00022032,
    HvArm64RegisterIdRes63El1 = 0x00022033,
    HvArm64RegisterIdRes64El1 = 0x00022034,
    HvArm64RegisterIdRes65El1 = 0x00022035,
    HvArm64RegisterIdRes66El1 = 0x00022036,
    HvArm64RegisterIdRes67El1 = 0x00022037,
    HvArm64RegisterIdAa64Mmfr0El1 = 0x00022038,
    HvArm64RegisterIdAa64Mmfr1El1 = 0x00022039,
    HvArm64RegisterIdAa64Mmfr2El1 = 0x0002203A,
    HvArm64RegisterIdAa64Mmfr3El1 = 0x0002203B,
    HvArm64RegisterIdAa64Mmfr4El1 = 0x0002203C,
    HvArm64RegisterIdRes75El1 = 0x0002203D,
    HvArm64RegisterIdRes76El1 = 0x0002203E,
    HvArm64RegisterIdRes77El1 = 0x0002203F,
    HvArm64RegisterIdRes80El1 = 0x00022040,
    HvArm64RegisterIdRes81El1 = 0x00022041,
    HvArm64RegisterIdRes82El1 = 0x00022042,
    HvArm64RegisterIdRes83El1 = 0x00022043,
    HvArm64RegisterIdRes84El1 = 0x00022044,
    HvArm64RegisterIdRes85El1 = 0x00022045,
    HvArm64RegisterIdRes86El1 = 0x00022046,
    HvArm64RegisterIdRes87El1 = 0x00022047,
    HvArm64RegisterIdRes90El1 = 0x00022048,
    HvArm64RegisterIdRes91El1 = 0x00022049,
    HvArm64RegisterIdRes92El1 = 0x0002204A,
    HvArm64RegisterIdRes93El1 = 0x0002204B,
    HvArm64RegisterIdRes94El1 = 0x0002204C,
    HvArm64RegisterIdRes95El1 = 0x0002204D,
    HvArm64RegisterIdRes96El1 = 0x0002204E,
    HvArm64RegisterIdRes97El1 = 0x0002204F,
    HvArm64RegisterIdRes100El1 = 0x00022050,
    HvArm64RegisterIdRes101El1 = 0x00022051,
    HvArm64RegisterIdRes102El1 = 0x00022052,
    HvArm64RegisterIdRes103El1 = 0x00022053,
    HvArm64RegisterIdRes104El1 = 0x00022054,
    HvArm64RegisterIdRes105El1 = 0x00022055,
    HvArm64RegisterIdRes106El1 = 0x00022056,
    HvArm64RegisterIdRes107El1 = 0x00022057,
    HvArm64RegisterIdRes110El1 = 0x00022058,
    HvArm64RegisterIdRes111El1 = 0x00022059,
    HvArm64RegisterIdRes112El1 = 0x0002205A,
    HvArm64RegisterIdRes113El1 = 0x0002205B,
    HvArm64RegisterIdRes114El1 = 0x0002205C,
    HvArm64RegisterIdRes115El1 = 0x0002205D,
    HvArm64RegisterIdRes116El1 = 0x0002205E,
    HvArm64RegisterIdRes117El1 = 0x0002205F,
    HvArm64RegisterIdRes120El1 = 0x00022060,
    HvArm64RegisterIdRes121El1 = 0x00022061,
    HvArm64RegisterIdRes122El1 = 0x00022062,
    HvArm64RegisterIdRes123El1 = 0x00022063,
    HvArm64RegisterIdRes124El1 = 0x00022064,
    HvArm64RegisterIdRes125El1 = 0x00022065,
    HvArm64RegisterIdRes126El1 = 0x00022066,
    HvArm64RegisterIdRes127El1 = 0x00022067,
    HvArm64RegisterIdRes130El1 = 0x00022068,
    HvArm64RegisterIdRes131El1 = 0x00022069,
    HvArm64RegisterIdRes132El1 = 0x0002206A,
    HvArm64RegisterIdRes133El1 = 0x0002206B,
    HvArm64RegisterIdRes134El1 = 0x0002206C,
    HvArm64RegisterIdRes135El1 = 0x0002206D,
    HvArm64RegisterIdRes136El1 = 0x0002206E,
    HvArm64RegisterIdRes137El1 = 0x0002206F,
    HvArm64RegisterIdRes140El1 = 0x00022070,
    HvArm64RegisterIdRes141El1 = 0x00022071,
    HvArm64RegisterIdRes142El1 = 0x00022072,
    HvArm64RegisterIdRes143El1 = 0x00022073,
    HvArm64RegisterIdRes144El1 = 0x00022074,
    HvArm64RegisterIdRes145El1 = 0x00022075,
    HvArm64RegisterIdRes146El1 = 0x00022076,
    HvArm64RegisterIdRes147El1 = 0x00022077,
    HvArm64RegisterIdRes150El1 = 0x00022078,
    HvArm64RegisterIdRes151El1 = 0x00022079,
    HvArm64RegisterIdRes152El1 = 0x0002207A,
    HvArm64RegisterIdRes153El1 = 0x0002207B,
    HvArm64RegisterIdRes154El1 = 0x0002207C,
    HvArm64RegisterIdRes155El1 = 0x0002207D,
    HvArm64RegisterIdRes156El1 = 0x0002207E,
    HvArm64RegisterIdRes157El1 = 0x0002207F,

    HvArm64RegisterXzr = 0x0002FFFE,

    HvArm64RegisterZ0 = 0x00030100,
    HvArm64RegisterZ1 = 0x00030101,
    HvArm64RegisterZ2 = 0x00030102,
    HvArm64RegisterZ3 = 0x00030103,
    HvArm64RegisterZ4 = 0x00030104,
    HvArm64RegisterZ5 = 0x00030105,
    HvArm64RegisterZ6 = 0x00030106,
    HvArm64RegisterZ7 = 0x00030107,
    HvArm64RegisterZ8 = 0x00030108,
    HvArm64RegisterZ9 = 0x00030109,
    HvArm64RegisterZ10 = 0x0003010A,
    HvArm64RegisterZ11 = 0x0003010B,
    HvArm64RegisterZ12 = 0x0003010C,
    HvArm64RegisterZ13 = 0x0003010D,
    HvArm64RegisterZ14 = 0x0003010E,
    HvArm64RegisterZ15 = 0x0003010F,
    HvArm64RegisterZ16 = 0x00030110,
    HvArm64RegisterZ17 = 0x00030111,
    HvArm64RegisterZ18 = 0x00030112,
    HvArm64RegisterZ19 = 0x00030113,
    HvArm64RegisterZ20 = 0x00030114,
    HvArm64RegisterZ21 = 0x00030115,
    HvArm64RegisterZ22 = 0x00030116,
    HvArm64RegisterZ23 = 0x00030117,
    HvArm64RegisterZ24 = 0x00030118,
    HvArm64RegisterZ25 = 0x00030119,
    HvArm64RegisterZ26 = 0x0003011A,
    HvArm64RegisterZ27 = 0x0003011B,
    HvArm64RegisterZ28 = 0x0003011C,
    HvArm64RegisterZ29 = 0x0003011D,
    HvArm64RegisterZ30 = 0x0003011E,
    HvArm64RegisterZ31 = 0x0003011F,
    HvArm64RegisterP0 = 0x00030120,
    HvArm64RegisterP1 = 0x00030121,
    HvArm64RegisterP2 = 0x00030122,
    HvArm64RegisterP3 = 0x00030123,
    HvArm64RegisterP4 = 0x00030124,
    HvArm64RegisterP5 = 0x00030125,
    HvArm64RegisterP6 = 0x00030126,
    HvArm64RegisterP7 = 0x00030127,
    HvArm64RegisterP8 = 0x00030128,
    HvArm64RegisterP9 = 0x00030129,
    HvArm64RegisterP10 = 0x0003012A,
    HvArm64RegisterP11 = 0x0003012B,
    HvArm64RegisterP12 = 0x0003012C,
    HvArm64RegisterP13 = 0x0003012D,
    HvArm64RegisterP14 = 0x0003012E,
    HvArm64RegisterP15 = 0x0003012F,
    HvArm64RegisterFFR = 0x00030130,

    // Arm64 Control Registers

    HvArm64RegisterMpidrEl1 = 0x00040001,
    HvArm64RegisterSctlrEl1 = 0x00040002,
    HvArm64RegisterActlrEl1 = 0x00040003,
    HvArm64RegisterCpacrEl1 = 0x00040004,
    HvArm64RegisterTtbr0El1 = 0x00040005,
    HvArm64RegisterTtbr1El1 = 0x00040006,
    HvArm64RegisterTcrEl1 = 0x00040007,
    HvArm64RegisterMairEl1 = 0x0004000B,
    HvArm64RegisterVbarEl1 = 0x0004000C,
    HvArm64RegisterContextidrEl1 = 0x0004000D,
    HvArm64RegisterTpidrEl1 = 0x0004000E,
    HvArm64RegisterFpcr = 0x00040012,
    HvArm64RegisterFpsr = 0x00040013,
    HvArm64RegisterAfsr0El1 = 0x00040016,
    HvArm64RegisterAfsr1El1 = 0x00040017,
    HvArm64RegisterAmairEl1 = 0x00040018,
    HvArm64RegisterAccdataEl1 = 0x00040020,
    HvArm64RegisterActlrEl2 = 0x00040021,
    HvArm64RegisterAfsr0El2 = 0x00040022,
    HvArm64RegisterAfsr1El2 = 0x00040023,
    HvArm64RegisterAidrEl1 = 0x00040024,
    HvArm64RegisterAmairEl2 = 0x00040025,
    HvArm64RegisterApdAKeyHiEl1 = 0x00040026,
    HvArm64RegisterApdAKeyLoEl1 = 0x00040027,
    HvArm64RegisterApdBKeyHiEl1 = 0x00040028,
    HvArm64RegisterApdBKeyLoEl1 = 0x00040029,
    HvArm64RegisterApgAKeyHiEl1 = 0x0004002A,
    HvArm64RegisterApgAKeyLoEl1 = 0x0004002B,
    HvArm64RegisterApiAKeyHiEl1 = 0x0004002C,
    HvArm64RegisterApiAKeyLoEl1 = 0x0004002D,
    HvArm64RegisterApiBKeyHiEl1 = 0x0004002E,
    HvArm64RegisterApiBKeyLoEl1 = 0x0004002F,
    HvArm64RegisterCcsidrEl1 = 0x00040030,
    HvArm64RegisterCcsidr2El1 = 0x00040031,
    HvArm64RegisterClidrEl1 = 0x00040032,
    HvArm64RegisterContextidrEl2 = 0x00040033,
    HvArm64RegisterCptrEl2 = 0x00040034,
    HvArm64RegisterCsselrEl1 = 0x00040035,
    HvArm64RegisterCtrEl0 = 0x00040036,
    HvArm64RegisterDacr32El2 = 0x00040037,
    HvArm64RegisterDczidEl0 = 0x00040038,
    HvArm64RegisterEsrEl2 = 0x00040039,
    HvArm64RegisterFarEl2 = 0x0004003A,
    HvArm64RegisterFpexc32El2 = 0x0004003B,
    HvArm64RegisterGcrEl1 = 0x0004003C,
    HvArm64RegisterGmidEl1 = 0x0004003D,
    HvArm64RegisterHacrEl2 = 0x0004003E,
    HvArm64RegisterHafgrtrEl2 = 0x0004003F,
    HvArm64RegisterHcrEl2 = 0x00040040,
    HvArm64RegisterHcrxEl2 = 0x00040041,
    HvArm64RegisterHdfgrtrEl2 = 0x00040042,
    HvArm64RegisterHdfgwtrEl2 = 0x00040043,
    HvArm64RegisterHfgitrEl2 = 0x00040044,
    HvArm64RegisterHfgrtrEl2 = 0x00040045,
    HvArm64RegisterHfgwtrEl2 = 0x00040046,
    HvArm64RegisterHpfarEl2 = 0x00040047,
    HvArm64RegisterHstrEl2 = 0x00040048,
    HvArm64RegisterIfsr32El2 = 0x00040049,
    HvArm64RegisterIsrEl1 = 0x0004004A,
    HvArm64RegisterLorcEl1 = 0x0004004B,
    HvArm64RegisterLoreaEl1 = 0x0004004C,
    HvArm64RegisterLoridEl1 = 0x0004004D,
    HvArm64RegisterLornEl1 = 0x0004004E,
    HvArm64RegisterLorsaEl1 = 0x0004004F,
    HvArm64RegisterMairEl2 = 0x00040050,
    HvArm64RegisterMidrEl1 = 0x00040051,
    HvArm64RegisterMvfr0El1 = 0x00040052,
    HvArm64RegisterMvfr1El1 = 0x00040053,
    HvArm64RegisterMvfr2El1 = 0x00040054,
    HvArm64RegisterRevidrEl1 = 0x00040055,
    HvArm64RegisterRgsrEl1 = 0x00040056,
    HvArm64RegisterRndr = 0x00040057,
    HvArm64RegisterRndrrs = 0x00040058,
    HvArm64RegisterSctlrEl2 = 0x00040059,
    HvArm64RegisterScxtnumEl0 = 0x0004005A,
    HvArm64RegisterScxtnumEl1 = 0x0004005B,
    HvArm64RegisterScxtnumEl2 = 0x0004005C,
    HvArm64RegisterSmcrEl1 = 0x0004005D,
    HvArm64RegisterSmcrEl2 = 0x0004005E,
    HvArm64RegisterSmidrEl1 = 0x0004005F,
    HvArm64RegisterSmpriEl1 = 0x00040060,
    HvArm64RegisterSmprimapEl2 = 0x00040061,
    HvArm64RegisterTcrEl2 = 0x00040062,
    HvArm64RegisterTfsre0El1 = 0x00040063,
    HvArm64RegisterTfsrEl1 = 0x00040064,
    HvArm64RegisterTfsrEl2 = 0x00040065,
    HvArm64RegisterTpidr2El0 = 0x00040066,
    HvArm64RegisterTpidrEl2 = 0x00040067,
    HvArm64RegisterTtbr0El2 = 0x00040068,
    HvArm64RegisterVbarEl2 = 0x00040069,
    HvArm64RegisterVmpidrEl2 = 0x0004006A,
    HvArm64RegisterVncrEl2 = 0x0004006B,
    HvArm64RegisterVpidrEl2 = 0x0004006C,
    HvArm64RegisterVstcrEl2 = 0x0004006D,
    HvArm64RegisterVsttbrEl2 = 0x0004006E,
    HvArm64RegisterVtcrEl2 = 0x0004006F,
    HvArm64RegisterVttbrEl2 = 0x00040070,
    HvArm64RegisterZcrEl1 = 0x00040071,
    HvArm64RegisterZcrEl2 = 0x00040072,
    HvArm64RegisterAfsr0Elx = 0x00040073,
    HvArm64RegisterAfsr1Elx = 0x00040074,
    HvArm64RegisterAmairElx = 0x00040075,
    HvArm64RegisterContextidrElx = 0x00040076,
    HvArm64RegisterCpacrElx = 0x00040077,
    HvArm64RegisterEsrElx = 0x00040078,
    HvArm64RegisterFarElx = 0x00040079,
    HvArm64RegisterMairElx = 0x0004007A,
    HvArm64RegisterSctlrElx = 0x0004007B,
    HvArm64RegisterTcrElx = 0x0004007C,
    HvArm64RegisterTtbr0Elx = 0x0004007D,
    HvArm64RegisterTtbr1El2 = 0x0004007E,
    HvArm64RegisterTtbr1Elx = 0x0004007F,
    HvArm64RegisterVbarElx = 0x00040080,
    HvArm64RegisterZcrElx = 0x00040081,

    HvArm64RegisterSyntheticVbarEl1 = 0x00040400,
    HvArm64RegisterSyntheticEsrEl1 = 0x00040401,

    HvArm64RegisterDbgbcr0El1 = 0x00050000,
    HvArm64RegisterDbgbcr1El1 = 0x00050001,
    HvArm64RegisterDbgbcr2El1 = 0x00050002,
    HvArm64RegisterDbgbcr3El1 = 0x00050003,
    HvArm64RegisterDbgbcr4El1 = 0x00050004,
    HvArm64RegisterDbgbcr5El1 = 0x00050005,
    HvArm64RegisterDbgbcr6El1 = 0x00050006,
    HvArm64RegisterDbgbcr7El1 = 0x00050007,
    HvArm64RegisterDbgbcr8El1 = 0x00050008,
    HvArm64RegisterDbgbcr9El1 = 0x00050009,
    HvArm64RegisterDbgbcr10El1 = 0x0005000A,
    HvArm64RegisterDbgbcr11El1 = 0x0005000B,
    HvArm64RegisterDbgbcr12El1 = 0x0005000C,
    HvArm64RegisterDbgbcr13El1 = 0x0005000D,
    HvArm64RegisterDbgbcr14El1 = 0x0005000E,
    HvArm64RegisterDbgbcr15El1 = 0x0005000F,
    HvArm64RegisterDbgwcr0El1 = 0x00050010,
    HvArm64RegisterDbgwcr1El1 = 0x00050011,
    HvArm64RegisterDbgwcr2El1 = 0x00050012,
    HvArm64RegisterDbgwcr3El1 = 0x00050013,
    HvArm64RegisterDbgwcr4El1 = 0x00050014,
    HvArm64RegisterDbgwcr5El1 = 0x00050015,
    HvArm64RegisterDbgwcr6El1 = 0x00050016,
    HvArm64RegisterDbgwcr7El1 = 0x00050017,
    HvArm64RegisterDbgwcr8El1 = 0x00050018,
    HvArm64RegisterDbgwcr9El1 = 0x00050019,
    HvArm64RegisterDbgwcr10El1 = 0x0005001A,
    HvArm64RegisterDbgwcr11El1 = 0x0005001B,
    HvArm64RegisterDbgwcr12El1 = 0x0005001C,
    HvArm64RegisterDbgwcr13El1 = 0x0005001D,
    HvArm64RegisterDbgwcr14El1 = 0x0005001E,
    HvArm64RegisterDbgwcr15El1 = 0x0005001F,
    HvArm64RegisterDbgbvr0El1 = 0x00050020,
    HvArm64RegisterDbgbvr1El1 = 0x00050021,
    HvArm64RegisterDbgbvr2El1 = 0x00050022,
    HvArm64RegisterDbgbvr3El1 = 0x00050023,
    HvArm64RegisterDbgbvr4El1 = 0x00050024,
    HvArm64RegisterDbgbvr5El1 = 0x00050025,
    HvArm64RegisterDbgbvr6El1 = 0x00050026,
    HvArm64RegisterDbgbvr7El1 = 0x00050027,
    HvArm64RegisterDbgbvr8El1 = 0x00050028,
    HvArm64RegisterDbgbvr9El1 = 0x00050029,
    HvArm64RegisterDbgbvr10El1 = 0x0005002A,
    HvArm64RegisterDbgbvr11El1 = 0x0005002B,
    HvArm64RegisterDbgbvr12El1 = 0x0005002C,
    HvArm64RegisterDbgbvr13El1 = 0x0005002D,
    HvArm64RegisterDbgbvr14El1 = 0x0005002E,
    HvArm64RegisterDbgbvr15El1 = 0x0005002F,
    HvArm64RegisterDbgwvr0El1 = 0x00050030,
    HvArm64RegisterDbgwvr1El1 = 0x00050031,
    HvArm64RegisterDbgwvr2El1 = 0x00050032,
    HvArm64RegisterDbgwvr3El1 = 0x00050033,
    HvArm64RegisterDbgwvr4El1 = 0x00050034,
    HvArm64RegisterDbgwvr5El1 = 0x00050035,
    HvArm64RegisterDbgwvr6El1 = 0x00050036,
    HvArm64RegisterDbgwvr7El1 = 0x00050037,
    HvArm64RegisterDbgwvr8El1 = 0x00050038,
    HvArm64RegisterDbgwvr9El1 = 0x00050039,
    HvArm64RegisterDbgwvr10El1 = 0x0005003A,
    HvArm64RegisterDbgwvr11El1 = 0x0005003B,
    HvArm64RegisterDbgwvr12El1 = 0x0005003C,
    HvArm64RegisterDbgwvr13El1 = 0x0005003D,
    HvArm64RegisterDbgwvr14El1 = 0x0005003E,
    HvArm64RegisterDbgwvr15El1 = 0x0005003F,
    HvArm64RegisterDbgauthstatusEl1 = 0x00050040,
    HvArm64RegisterDbgclaimclrEl1 = 0x00050041,
    HvArm64RegisterDbgclaimsetEl1 = 0x00050042,
    HvArm64RegisterDbgdtrrxEl0 = 0x00050043,
    HvArm64RegisterDbgdtrtxEl0 = 0x00050044,
    HvArm64RegisterDbgprcrEl1 = 0x00050045,
    HvArm64RegisterDbgvcr32El2 = 0x00050046,
    HvArm64RegisterDlrEl0 = 0x00050047,
    HvArm64RegisterDspsrEl0 = 0x00050048,
    HvArm64RegisterMdccintEl1 = 0x00050049,
    HvArm64RegisterMdccsrEl0 = 0x0005004A,
    HvArm64RegisterMdcrEl2 = 0x0005004B,
    HvArm64RegisterMdrarEl1 = 0x0005004C,
    HvArm64RegisterMdscrEl1 = 0x0005004D,
    HvArm64RegisterOsdlrEl1 = 0x0005004E,
    HvArm64RegisterOsdtrrxEl1 = 0x0005004F,
    HvArm64RegisterOsdtrtxEl1 = 0x00050050,
    HvArm64RegisterOseccrEl1 = 0x00050051,
    HvArm64RegisterOslarEl1 = 0x00050052,
    HvArm64RegisterOslsrEl1 = 0x00050053,
    HvArm64RegisterSder32El2 = 0x00050054,
    HvArm64RegisterTrfcrEl1 = 0x00050055,
    HvArm64RegisterTrfcrEl2 = 0x00050056,
    HvArm64RegisterTrfcrElx = 0x00050057,

    HvArm64RegisterPmccfiltrEl0 = 0x00052000,
    HvArm64RegisterPmccntrEl0 = 0x00052001,
    HvArm64RegisterPmceid0El0 = 0x00052002,
    HvArm64RegisterPmceid1El0 = 0x00052003,
    HvArm64RegisterPmcntenclrEl0 = 0x00052004,
    HvArm64RegisterPmcntensetEl0 = 0x00052005,
    HvArm64RegisterPmcrEl0 = 0x00052006,
    HvArm64RegisterPmevcntr0El0 = 0x00052007,
    HvArm64RegisterPmevcntr1El0 = 0x00052008,
    HvArm64RegisterPmevcntr2El0 = 0x00052009,
    HvArm64RegisterPmevcntr3El0 = 0x0005200A,
    HvArm64RegisterPmevcntr4El0 = 0x0005200B,
    HvArm64RegisterPmevcntr5El0 = 0x0005200C,
    HvArm64RegisterPmevcntr6El0 = 0x0005200D,
    HvArm64RegisterPmevcntr7El0 = 0x0005200E,
    HvArm64RegisterPmevcntr8El0 = 0x0005200F,
    HvArm64RegisterPmevcntr9El0 = 0x00052010,
    HvArm64RegisterPmevcntr10El0 = 0x00052011,
    HvArm64RegisterPmevcntr11El0 = 0x00052012,
    HvArm64RegisterPmevcntr12El0 = 0x00052013,
    HvArm64RegisterPmevcntr13El0 = 0x00052014,
    HvArm64RegisterPmevcntr14El0 = 0x00052015,
    HvArm64RegisterPmevcntr15El0 = 0x00052016,
    HvArm64RegisterPmevcntr16El0 = 0x00052017,
    HvArm64RegisterPmevcntr17El0 = 0x00052018,
    HvArm64RegisterPmevcntr18El0 = 0x00052019,
    HvArm64RegisterPmevcntr19El0 = 0x0005201A,
    HvArm64RegisterPmevcntr20El0 = 0x0005201B,
    HvArm64RegisterPmevcntr21El0 = 0x0005201C,
    HvArm64RegisterPmevcntr22El0 = 0x0005201D,
    HvArm64RegisterPmevcntr23El0 = 0x0005201E,
    HvArm64RegisterPmevcntr24El0 = 0x0005201F,
    HvArm64RegisterPmevcntr25El0 = 0x00052020,
    HvArm64RegisterPmevcntr26El0 = 0x00052021,
    HvArm64RegisterPmevcntr27El0 = 0x00052022,
    HvArm64RegisterPmevcntr28El0 = 0x00052023,
    HvArm64RegisterPmevcntr29El0 = 0x00052024,
    HvArm64RegisterPmevcntr30El0 = 0x00052025,
    HvArm64RegisterPmevtyper0El0 = 0x00052026,
    HvArm64RegisterPmevtyper1El0 = 0x00052027,
    HvArm64RegisterPmevtyper2El0 = 0x00052028,
    HvArm64RegisterPmevtyper3El0 = 0x00052029,
    HvArm64RegisterPmevtyper4El0 = 0x0005202A,
    HvArm64RegisterPmevtyper5El0 = 0x0005202B,
    HvArm64RegisterPmevtyper6El0 = 0x0005202C,
    HvArm64RegisterPmevtyper7El0 = 0x0005202D,
    HvArm64RegisterPmevtyper8El0 = 0x0005202E,
    HvArm64RegisterPmevtyper9El0 = 0x0005202F,
    HvArm64RegisterPmevtyper10El0 = 0x00052030,
    HvArm64RegisterPmevtyper11El0 = 0x00052031,
    HvArm64RegisterPmevtyper12El0 = 0x00052032,
    HvArm64RegisterPmevtyper13El0 = 0x00052033,
    HvArm64RegisterPmevtyper14El0 = 0x00052034,
    HvArm64RegisterPmevtyper15El0 = 0x00052035,
    HvArm64RegisterPmevtyper16El0 = 0x00052036,
    HvArm64RegisterPmevtyper17El0 = 0x00052037,
    HvArm64RegisterPmevtyper18El0 = 0x00052038,
    HvArm64RegisterPmevtyper19El0 = 0x00052039,
    HvArm64RegisterPmevtyper20El0 = 0x0005203A,
    HvArm64RegisterPmevtyper21El0 = 0x0005203B,
    HvArm64RegisterPmevtyper22El0 = 0x0005203C,
    HvArm64RegisterPmevtyper23El0 = 0x0005203D,
    HvArm64RegisterPmevtyper24El0 = 0x0005203E,
    HvArm64RegisterPmevtyper25El0 = 0x0005203F,
    HvArm64RegisterPmevtyper26El0 = 0x00052040,
    HvArm64RegisterPmevtyper27El0 = 0x00052041,
    HvArm64RegisterPmevtyper28El0 = 0x00052042,
    HvArm64RegisterPmevtyper29El0 = 0x00052043,
    HvArm64RegisterPmevtyper30El0 = 0x00052044,
    HvArm64RegisterPmintenclrEl1 = 0x00052045,
    HvArm64RegisterPmintensetEl1 = 0x00052046,
    HvArm64RegisterPmmirEl1 = 0x00052047,
    HvArm64RegisterPmovsclrEl0 = 0x00052048,
    HvArm64RegisterPmovssetEl0 = 0x00052049,
    HvArm64RegisterPmselrEl0 = 0x0005204A,
    HvArm64RegisterPmswincEl0 = 0x0005204B,
    HvArm64RegisterPmuserenrEl0 = 0x0005204C,
    HvArm64RegisterPmxevcntrEl0 = 0x0005204D,
    HvArm64RegisterPmxevtyperEl0 = 0x0005204E,

    HvArm64RegisterAmevcntr00El0 = 0x00053000,
    HvArm64RegisterAmevcntr01El0 = 0x00053001,
    HvArm64RegisterAmevcntr02El0 = 0x00053002,
    HvArm64RegisterAmevcntr03El0 = 0x00053003,

    HvArm64RegisterPmbidrEl1 = 0x00054000,
    HvArm64RegisterPmblimitrEl1 = 0x00054001,
    HvArm64RegisterPmbptrEl1 = 0x00054002,
    HvArm64RegisterPmbsrEl1 = 0x00054003,
    HvArm64RegisterPmscrEl1 = 0x00054004,
    HvArm64RegisterPmscrEl2 = 0x00054005,
    HvArm64RegisterPmsevfrEl1 = 0x00054006,
    HvArm64RegisterPmsfcrEl1 = 0x00054007,
    HvArm64RegisterPmsicrEl1 = 0x00054008,
    HvArm64RegisterPmsidrEl1 = 0x00054009,
    HvArm64RegisterPmsirrEl1 = 0x0005400A,
    HvArm64RegisterPmslatfrEl1 = 0x0005400B,
    HvArm64RegisterPmsnevfrEl1 = 0x0005400C,

    HvArm64RegisterDisrEl1 = 0x00056000,
    HvArm64RegisterErridrEl1 = 0x00056001,
    HvArm64RegisterErrselrEl1 = 0x00056002,
    HvArm64RegisterErxaddrEl1 = 0x00056003,
    HvArm64RegisterErxctlrEl1 = 0x00056004,
    HvArm64RegisterErrxfrEl1 = 0x00056005,
    HvArm64RegisterErxmisc0El1 = 0x00056006,
    HvArm64RegisterErxmisc1El1 = 0x00056007,
    HvArm64RegisterErxmisc2El1 = 0x00056008,
    HvArm64RegisterErxmisc3El1 = 0x00056009,
    HvArm64RegisterErxpfgcdnEl1 = 0x0005600A,
    HvArm64RegisterErxpfgctlEl1 = 0x0005600B,
    HvArm64RegisterErxpfgfEl1 = 0x0005600C,
    HvArm64RegisterErxstatusEl1 = 0x0005600D,
    HvArm64RegisterVdisrEl2 = 0x0005600E,
    HvArm64RegisterVsesrEl2 = 0x0005600F,

    HvArm64RegisterCntfrqEl0 = 0x00058000,
    HvArm64RegisterCnthctlEl2 = 0x00058001,
    HvArm64RegisterCnthpCtlEl2 = 0x00058002,
    HvArm64RegisterCnthpCvalEl2 = 0x00058003,
    HvArm64RegisterCnthpTvalEl2 = 0x00058004,
    HvArm64RegisterCnthvCtlEl2 = 0x00058005,
    HvArm64RegisterCnthvCvalEl2 = 0x00058006,
    HvArm64RegisterCnthvTvalEl2 = 0x00058007,
    HvArm64RegisterCntkctlEl1 = 0x00058008,
    HvArm64RegisterCntpCtlEl0 = 0x00058009,
    HvArm64RegisterCntpCvalEl0 = 0x0005800A,
    HvArm64RegisterCntpTvalEl0 = 0x0005800B,
    HvArm64RegisterCntpctEl0 = 0x0005800C,
    HvArm64RegisterCntpoffEl2 = 0x0005800D,
    HvArm64RegisterCntvCtlEl0 = 0x0005800E,
    HvArm64RegisterCntvCvalEl0 = 0x0005800F,
    HvArm64RegisterCntvTvalEl0 = 0x00058010,
    HvArm64RegisterCntvctEl0 = 0x00058011,
    HvArm64RegisterCntvoffEl2 = 0x00058012,
    HvArm64RegisterCntkctlElx = 0x00058013,
    HvArm64RegisterCntpCtlElx = 0x00058014,
    HvArm64RegisterCntpCvalElx = 0x00058015,
    HvArm64RegisterCntpTvalElx = 0x00058016,
    HvArm64RegisterCntvCtlElx = 0x00058017,
    HvArm64RegisterCntvCvalElx = 0x00058018,
    HvArm64RegisterCntvTvalElx = 0x00058019,

    HvArm64RegisterIccAp1R0El1 = 0x00060000,
    HvArm64RegisterIccAp1R1El1 = 0x00060001,
    HvArm64RegisterIccAp1R2El1 = 0x00060002,
    HvArm64RegisterIccAp1R3El1 = 0x00060003,
    HvArm64RegisterIccAsgi1REl1 = 0x00060004,
    HvArm64RegisterIccBpr1El1 = 0x00060005,
    HvArm64RegisterIccCtlrEl1 = 0x00060006,
    HvArm64RegisterIccDirEl1 = 0x00060007,
    HvArm64RegisterIccEoir1El1 = 0x00060008,
    HvArm64RegisterIccHppir1El1 = 0x00060009,
    HvArm64RegisterIccIar1El1 = 0x0006000A,
    HvArm64RegisterIccIgrpen1El1 = 0x0006000B,
    HvArm64RegisterIccPmrEl1 = 0x0006000C,
    HvArm64RegisterIccRprEl1 = 0x0006000D,
    HvArm64RegisterIccSgi1REl1 = 0x0006000E,
    HvArm64RegisterIccSreEl1 = 0x0006000F,
    HvArm64RegisterIccSreEl2 = 0x00060010,

    HvArm64RegisterIchAp1R0El2 = 0x00061000,
    HvArm64RegisterIchAp1R1El2 = 0x00061001,
    HvArm64RegisterIchAp1R2El2 = 0x00061002,
    HvArm64RegisterIchAp1R3El2 = 0x00061003,
    HvArm64RegisterIchEisrEl2 = 0x00061004,
    HvArm64RegisterIchElrsrEl2 = 0x00061005,
    HvArm64RegisterIchHcrEl2 = 0x00061006,
    HvArm64RegisterIchLr0El2 = 0x00061007,
    HvArm64RegisterIchLr1El2 = 0x00061008,
    HvArm64RegisterIchLr2El2 = 0x00061009,
    HvArm64RegisterIchLr3El2 = 0x0006100A,
    HvArm64RegisterIchLr4El2 = 0x0006100B,
    HvArm64RegisterIchLr5El2 = 0x0006100C,
    HvArm64RegisterIchLr6El2 = 0x0006100D,
    HvArm64RegisterIchLr7El2 = 0x0006100E,
    HvArm64RegisterIchLr8El2 = 0x0006100F,
    HvArm64RegisterIchLr9El2 = 0x00061010,
    HvArm64RegisterIchLr10El2 = 0x00061011,
    HvArm64RegisterIchLr11El2 = 0x00061012,
    HvArm64RegisterIchLr12El2 = 0x00061013,
    HvArm64RegisterIchLr13El2 = 0x00061014,
    HvArm64RegisterIchLr14El2 = 0x00061015,
    HvArm64RegisterIchLr15El2 = 0x00061016,
    HvArm64RegisterIchMisrEl2 = 0x00061017,
    HvArm64RegisterIchVmcrEl2 = 0x00061018,
    HvArm64RegisterIchVtrEl2 = 0x00061019,

    HvArm64RegisterMpam0El1 = 0x00071000,
    HvArm64RegisterMpam1El1 = 0x00071001,
    HvArm64RegisterMpam2El2 = 0x00071002,
    HvArm64RegisterMpamhcrEl2 = 0x00071003,
    HvArm64RegisterMpamidrEl1 = 0x00071004,
    HvArm64RegisterMpamsmEl1 = 0x00071005,
    HvArm64RegisterMpamvpm0El2 = 0x00071006,
    HvArm64RegisterMpamvpm1El2 = 0x00071007,
    HvArm64RegisterMpamvpm2El2 = 0x00071008,
    HvArm64RegisterMpamvpm3El2 = 0x00071009,
    HvArm64RegisterMpamvpm4El2 = 0x0007100A,
    HvArm64RegisterMpamvpm5El2 = 0x0007100B,
    HvArm64RegisterMpamvpm6El2 = 0x0007100C,
    HvArm64RegisterMpamvpm7El2 = 0x0007100D,
    HvArm64RegisterMpamvpmvEl2 = 0x0007100E,

    HvArm64RegisterS3ImpldefinedRegMin = 0x00072000,
    HvArm64RegisterS3ImpldefinedRegMax = 0x00072FFF,

    HvArm64RegisterGicrPropbaser = 0x00090100,
    HvArm64RegisterGicrPendbaser = 0x00090101,
#endif
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

typedef HV_UINT32 HV_SPA_PAGE_OFFSET, *PHV_SPA_PAGE_OFFSET;
typedef HV_UINT32 HV_GPA_PAGE_OFFSET, *PHV_GPA_PAGE_OFFSET;
typedef HV_UINT32 HV_GVA_PAGE_OFFSET, *PHV_GVA_PAGE_OFFSET;

typedef const HV_GPA_PAGE_OFFSET *PCHV_GPA_PAGE_OFFSET;
typedef const HV_GVA_PAGE_OFFSET *PCHV_GVA_PAGE_OFFSET;

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

typedef struct _HV_GENERIC_SET_HEADER
{
    HV_UINT64 Format;
    HV_UINT64 ValidBanksMask;
} HV_GENERIC_SET_HEADER, *PHV_GENERIC_SET_HEADER;

typedef struct _HV_GENERIC_SET
{
    HV_UINT64 Format;
    HV_UINT64 ValidBanksMask;
    HV_UINT64 BankContents[HV_ANYSIZE_ARRAY];
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

#if defined(_M_AMD64) || defined(_M_IX86)
typedef enum _HV_X64_PENDING_EVENT_TYPE
{
    HvX64PendingEventException = 0x0,
    HvX64PendingEventMemoryIntercept = 0x1,
    HvX64PendingEventNestedMemoryIntercept = 0x2,
} HV_X64_PENDING_EVENT_TYPE, *PHV_X64_PENDING_EVENT_TYPE;
#elif defined(_M_ARM64)
typedef enum _HV_ARM64_PENDING_EVENT_TYPE
{
    HvArm64PendingEventException = 0x0,
    HvArm64PendingEventSyntheticException = 0x1,
    HvArm64PendingEventHypercallOutput = 0x2,
} HV_ARM64_PENDING_EVENT_TYPE, *PHV_ARM64_PENDING_EVENT_TYPE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef union _HV_ARM64_PENDING_HYPERCALL_OUTPUT_EVENT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3;
        HV_UINT8 Reserved : 4;
        HV_UINT8 Retired : 1;
        HV_UINT8 Reserved1 : 7;
        HV_UINT16 Reserved2;
        HV_UINT32 OutputSize;
        HV_UINT64 OutputGpa;
    };
} HV_ARM64_PENDING_HYPERCALL_OUTPUT_EVENT, *PHV_ARM64_PENDING_HYPERCALL_OUTPUT_EVENT;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
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
        HV_UINT8 EventType : 3; // HV_X64_PENDING_EVENT_TYPE
        HV_UINT8 Reserved : 4;
        HV_UINT8 EventData[15];
    };
    HV_X64_PENDING_EXCEPTION_EVENT Exception;
    HV_X64_PENDING_MEMORY_INTERCEPT_EVENT MemoryIntercept;
    HV_X64_PENDING_NESTED_MEMORY_INTERCEPT_EVENT NestedMemoryIntercept;
} HV_X64_PENDING_EVENT, *PHV_X64_PENDING_EVENT;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_PENDING_EVENT
{
    struct
    {
        HV_UINT128 Reg0;
        HV_UINT128 Reg1;
    };
    struct
    {
        HV_UINT8 EventPending : 1;
        HV_UINT8 EventType : 3; // HV_ARM64_PENDING_EVENT_TYPE
        HV_UINT8 Reserved : 4;
        HV_UINT8 EventData[15];
    };
    HV_ARM64_PENDING_EXCEPTION_EVENT Exception;
    HV_ARM64_PENDING_SYNTHETIC_EXCEPTION_EVENT SyntheticException;
    HV_ARM64_PENDING_HYPERCALL_OUTPUT_EVENT HypercallOutput;
} HV_ARM64_PENDING_EVENT, *PHV_ARM64_PENDING_EVENT;
#endif

typedef struct _HV_TRANSLATE_GVA_RESULT_EX
{
    HV_TRANSLATE_GVA_RESULT_CODE ResultCode;
    HV_UINT32 CacheType : 8;
    HV_UINT32 OverlayPage : 1;
    HV_UINT32 Reserved : 23;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_X64_PENDING_EVENT EventInfo; // Not in TLFS
#elif defined(_M_ARM64)
    HV_ARM64_PENDING_EVENT EventInfo; // I guess should have that.
#endif
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
#if defined(_M_AMD64) || defined(_M_IX86)
        HV_IOAPIC_RTE IoApicRte;
        HV_UINT64 Data;
#elif defined(_M_ARM64)
        // Seemed not exist in Windows 11 Build 26100 era
        HV_GICD_ENTRY GicdEntry;
        HV_UINT64 Data[2];
#endif
    };
} HV_INTERRUPT_ENTRY, *PHV_INTERRUPT_ENTRY;

#define HV_DEVICE_INTERRUPT_TARGET_MULTICAST 1
#define HV_DEVICE_INTERRUPT_TARGET_PROCESSOR_SET 2

typedef struct _HV_DEVICE_INTERRUPT_TARGET_HEADER
{
    HV_INTERRUPT_VECTOR Vector;
    HV_UINT32 Flags;
} HV_DEVICE_INTERRUPT_TARGET_HEADER, *PHV_DEVICE_INTERRUPT_TARGET_HEADER;

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
        HV_UINT64 SupervisorShadowStackEnabledVtlSet : 4;
        HV_UINT64 ReservedZ : 24;
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
        HV_UINT64 InterceptRestorePartitionTime : 1;
        HV_UINT64 InterceptNotPresent : 1;
        HV_UINT64 ReservedZ : 49;
    };
} HV_REGISTER_VSM_PARTITION_CONFIG, *PHV_REGISTER_VSM_PARTITION_CONFIG;

typedef union _HV_REGISTER_GUEST_VSM_PARTITION_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MaximumVtl : 4;
        HV_UINT64 Vtl0InterruptInjectionPolicy : 2;
        HV_UINT64 Vtl1InterruptInjectionPolicy : 2;
        HV_UINT64 ReservedZ : 56;
    };
} HV_REGISTER_GUEST_VSM_PARTITION_CONFIG, *PHV_REGISTER_GUEST_VSM_PARTITION_CONFIG;

typedef union _HV_REGISTER_VSM_VP_SECURE_VTL_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MbecEnabled : 1;
        HV_UINT64 TlbLocked : 1;
        HV_UINT64 SupervisorShadowStackEnabled : 1;
        HV_UINT64 HardwareHvptEnabled : 1;
        HV_UINT64 ReservedZ : 60;
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
        HV_UINT64 Cr0Write : 1;
        HV_UINT64 Cr4Write : 1;
        HV_UINT64 XCr0Write : 1;
        HV_UINT64 IA32MiscEnableRead : 1;
        HV_UINT64 IA32MiscEnableWrite : 1;
        HV_UINT64 MsrLstarRead : 1;
        HV_UINT64 MsrLstarWrite : 1;
        HV_UINT64 MsrStarRead : 1;
        HV_UINT64 MsrStarWrite : 1;
        HV_UINT64 MsrCstarRead : 1;
        HV_UINT64 MsrCstarWrite : 1;
        HV_UINT64 ApicBaseMsrRead : 1;
        HV_UINT64 ApicBaseMsrWrite : 1;
        HV_UINT64 MsrEferRead : 1;
        HV_UINT64 MsrEferWrite : 1;
        HV_UINT64 GdtrWrite : 1;
        HV_UINT64 IdtrWrite : 1;
        HV_UINT64 LdtrWrite : 1;
        HV_UINT64 TrWrite : 1;
        HV_UINT64 MsrSysenterCsWrite : 1;
        HV_UINT64 MsrSysenterEipWrite : 1;
        HV_UINT64 MsrSysenterEspWrite : 1;
        HV_UINT64 MsrSfmaskWrite : 1;
        HV_UINT64 MsrTscAuxWrite : 1;
        HV_UINT64 MsrSgxLaunchControlWrite : 1;
        HV_UINT64 MsrXssWrite : 1;
        HV_UINT64 MsrSCetWrite : 1;
        HV_UINT64 MsrPlsSspWrite : 1;
        HV_UINT64 MsrInterruptSspTableAddrWrite : 1;
        HV_UINT64 RsvdZ : 35;
    };
} HV_REGISTER_CR_INTERCEPT_CONTROL, *PHV_REGISTER_CR_INTERCEPT_CONTROL;

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
    HV_UINT8 RsvdZ[2];
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
    HvPerfCounterProperty = 0x1,
    HvDeprecatedLegacyPowerPolicySettingProperty = 0x2,
    HvSleepStateProperty = 0x3,
    HvMachineCheckProperty = 0x4,
    HvIommuInitStatusProperty = 0x5,
    HvHpetConfigProperty = 0x6,
    HvHpetInterruptProperty = 0x7,
    HvHpetEnabledProperty = 0x8,
    HvHypervisorLaunchStatsProperty = 0x9,
    HvHypervisorDebugProperty = 0xA,
    HvRootPasidCapabilitiesProperty = 0xB,
    HvRootNumaCostPagesProperty = 0xC,
    HvHostPageTableRootProperty = 0xD,
    HvTscSyncStatusProperty = 0xE,
    HvSchedulerTypeProperty = 0xF,
    HvPlatformVirtualizationSupportProperty = 0x10,
    HvHostDebugTransferPages = 0x11,
    HvHostTimelineBiasProperty = 0x12,
    HvSmcDataPathProperty = 0x13,
    HvDmaInitializeBlockedProperty = 0x14,
    HvDynamicProcessorFeatureProperty = 0x15,
    HvUnusedSystemProperty_22 = 0x16,
    HvRdtCatCosBitmaskProperty_Legacy = 0x17,
    HvUnusedSystemProperty_24 = 0x18,
    HvGuestStateScrubbingStatusProperty = 0x19,
    HvDmaUnblockedProperty = 0x1A,
    HvRdtMbaCosThrottleProperty_Legacy = 0x1B,
    HvSystemDiagnosticsLogBuffers = 0x1C,
    HvSystemPageCombiningIntervalProperty = 0x1D,
    HvIommuLiveHandoffProperty = 0x1E,
    HvIommuDomainIdSelectorProperty = 0x1F,
    HvIommuRootFaultReportingReady = 0x20,
    HvGuestAssertProperty = 0x21,
    HvLogicalProcessorCountProperty = 0x22,
    HvSnpPspIdProperty = 0x23,
    HvSchedulingIntervalProperty = 0x24,
    HvSnpPspTcbVersionProperty = 0x25,
    HvSubnodeInformationProperty = 0x26,
    HvSnpPspDevicesProperty = 0x27,
    HvProcessorLiveHandoffProperty = 0x28,
    HvProcessorParkBlockProperty = 0x29,
    HvBootConfigProperty = 0x2A,
    HvVirtualizationFeaturesProperty = 0x2B,
    HvSystemRebootCountProperty = 0x2C,
    HvSystemMirroringProperty = 0x2D,
    HvSystemProtoAbiVersionProperty = 0x2E,
    HvCrashdumpAreaAddressProperty = 0x2F,
    HvMicrocodeLatencyProperty = 0x30,
    HvDefaultIoCacheBitmapProperty = 0x31,
    HvHardwareIsolationEnabledProperty = 0x32,
    HvFirmwareX2ApicProperty = 0x33,
    HvCrashdumpTrampolineAddressProperty = 0x34,
    HvResourceControlSupportProperty = 0x35,
    HvResourceControlBitmaskProperty = 0x36,
    HvResourceControlMonitorValueProperty = 0x37,
    HvSgxEUpdateSvnProperty = 0x38,
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

typedef struct _HV_VP_REGISTER_PAGE
{
    HV_UINT16 Version;
    HV_UINT8 IsValid;
    HV_VTL Vtl;
    HV_UINT32 Dirty;
#if defined(_M_AMD64) || defined(_M_IX86)
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
#endif
} HV_VP_REGISTER_PAGE, *PHV_VP_REGISTER_PAGE;

typedef struct _HV_PARTITION_CREATION_PROPERTIES_V1
{
    HV_UINT64 DisabledProcessorFeatures;
} HV_PARTITION_CREATION_PROPERTIES_V1, *PHV_PARTITION_CREATION_PROPERTIES_V1;

typedef struct _HV_PARTITION_CREATION_PROPERTIES_V2
{
    HV_PARTITION_PROCESSOR_FEATURES DisabledProcessorFeatures;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_PARTITION_PROCESSOR_XSAVE_FEATURES DisabledProcessorXsaveFeatures;
#endif
} HV_PARTITION_CREATION_PROPERTIES_V2, *PHV_PARTITION_CREATION_PROPERTIES_V2;

typedef struct _HV_PARTITION_CREATION_PROPERTIES
{
    HV_PARTITION_PROCESSOR_FEATURES DisabledProcessorFeatures;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_PARTITION_PROCESSOR_XSAVE_FEATURES DisabledProcessorXsaveFeatures;
#endif
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
        HV_UINT64 ReservedZ33 : 1;
        HV_UINT64 ReservedZ34 : 1;
        HV_UINT64 ReservedZ35 : 1;
        HV_UINT64 RegisterInterceptsV1 : 1;
        HV_UINT64 WakeVps : 1;
        HV_UINT64 AccessVpRegs : 1;
        HV_UINT64 SyncContext : 1;
        HV_UINT64 ManagementVtlSynicSupport : 1;
        HV_UINT64 Reserved : 23;
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

    HV_APIC_ID ApicId;
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
        HV_UINT32 UndeliveredMessagePending : 1;
        HV_UINT32 Reserved : 31;
    } Flags;
    HV_UINT32 Reserved;
    // Timer configuration and count.
    HV_UINT64 Config;
    HV_UINT64 Count;
    // Timer adjustment.
    HV_UINT64 Adjustment;
    // Expiration time of the undelivered message.
    HV_UINT64 UndeliveredExpirationTime;
} HV_STIMER_STATE, *PHV_STIMER_STATE;

typedef struct _HV_SYNTHETIC_TIMERS_STATE
{
    HV_STIMER_STATE Timers[HV_SYNIC_STIMER_COUNT];
    // Reserved space for time unhalted timer.
    HV_UINT64 Reserved[5];
} HV_SYNTHETIC_TIMERS_STATE, *PHV_SYNTHETIC_TIMERS_STATE;

#if defined(_M_AMD64) || defined(_M_IX86)
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
    HV_FLUSH_FLAGS Flags;
    HV_GPA_PAGE_RANGE GpaList[];
} HV_GUEST_MAPPING_FLUSH_LIST, *PHV_GUEST_MAPPING_FLUSH_LIST;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_VP_STATE_DATA_XSAVE
{
    HV_UINT64 Flags;
    HV_X64_XSAVE_XFEM_REGISTER States;
} HV_VP_STATE_DATA_XSAVE, *PHV_VP_STATE_DATA_XSAVE;
#endif

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

typedef HV_GET_SET_VP_STATE_TYPE HV_GET_SET_STATE_TYPE, *PHV_GET_SET_STATE_TYPE;

typedef struct _HV_VP_STATE_DATA
{
    HV_GET_SET_VP_STATE_TYPE Type;
    HV_UINT32 Reserved;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_VP_STATE_DATA_XSAVE Xsave;
#endif
} HV_VP_STATE_DATA, *PHV_VP_STATE_DATA;

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
    HvVpDispatchEventInvalid = 0x0,
    HvVpDispatchEventSuspend = 0x1,
    HvVpDispatchEventIntercept = 0x2,
    HvVpDispatchEventInternal = 0x3,
    HvVpDispatchEventPreempted = 0x4,
    HvVpDispatchEventCancelled = 0x5,
    HvVpDispatchEventScheduler = 0x6,
    HvVpDispatchEventLongSpinWait = 0x7,
    HvVpDispatchEventTimeSliceEnd = 0x8,
} HV_VP_DISPATCH_EVENT, *PHV_VP_DISPATCH_EVENT;

#define HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION 1024
// The maximum array size of HV_GENERIC_SET (vp_set) buffer
#define HV_GENERIC_SET_QWORD_COUNT(max) (((((max) - 1) >> 6) + 1) + 2)

typedef struct _HV_VP_SIGNAL_BITSET_SCHEDULER_MESSAGE
{
    HV_PARTITION_ID PartitionId;
    HV_UINT32 OverflowCount;
    HV_UINT16 VpCount;
#define BITSET_BUFFER_SIZE \
	HV_GENERIC_SET_QWORD_COUNT(HV_ROOT_SCHEDULER_MAX_VPS_PER_CHILD_PARTITION)
    union
    {
        HV_GENERIC_SET Bitset;
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

typedef HV_UINT64 HV_LOGICAL_DEVICE_ID, *PHV_LOGICAL_DEVICE_ID;

typedef HV_UINT32 HV_PASID, *PHV_PASID;

typedef HV_UINT32 HV_PASID_SPACE_ID, *PHV_PASID_SPACE_ID;

typedef HV_UINT8 HV_IOAPIC_ID, *PHV_IOAPIC_ID;

typedef HV_UINT16 HV_PCI_SEGMENT, *PHV_PCI_SEGMENT;

typedef HV_UINT64 HV_DEVICE_VA, *PHV_DEVICE_VA;

typedef HV_UINT16 HV_PCI_RID, *PHV_PCI_RID;

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
#if defined(_M_AMD64) || defined(_M_IX86)
    HvLogicalProcessorPerfStateConfig = 0x0,
    HvLogicalProcessorThrottleStateConfig = 0x1,
    HvLogicalProcessorPccConfig = 0x2,
    HvLogicalProcessorPerfStateCap = 0x3,
    HvLogicalProcessorMachineCheckContextInfo = 0x4,
    HvLogicalProcessorMcUpdateUpdateStatus = 0x5,
#elif defined(_M_ARM64)
    HvLogicalProcessorMachineCheckContextInfo = 0x0,
    HvLogicalProcessorMcUpdateUpdateStatus = 0x1,
    HvLogicalProcessorUpdateLpIndex = 0x2,
    HvLogicalProcessorProcHwId = 0x3,
    HvLogicalProcessorProximityDomainId = 0x4,
#endif
} HV_LOGICAL_PROCESSOR_PROPERTY_TYPE, *PHV_LOGICAL_PROCESSOR_PROPERTY_TYPE;

typedef enum _HV_LOGICAL_PROCESSOR_REGISTER_TYPE
{
#if defined(_M_AMD64) || defined(_M_IX86)
    HvX64LpRegisterTypeCpuid = 0x10000,
    HvX64LpRegisterTypeMsr = 0x10001,
    HvX64LpRegisterTypeWbinvd = 0x10002,
#elif defined(_M_ARM64)
    HvArm64LpRegisterTypeHvRegister = 0x10000,
#endif
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
    HvPowerPropertyLpCppcRequestValue = 0x6,
    HvPowerPropertyLpCppcRequestRegister = 0x7,
    HvPowerPropertyLpIdleStateConfigEx = 0x8,
} HV_POWER_PROPERTY_TYPE, *PHV_POWER_PROPERTY_TYPE;

typedef enum _HV_PARTITION_EVENT
{
    HvPartitionEventDebugDeviceAvailable = 0x1,
    HvPartitionEventRootCrashdump = 0x2,
    HvPartitionEventAcpiReenabled = 0x3,
    HvPartitionAllLogicalProcessorsStarted = 0x4,
    HvPartitionCommitLpIndices = 0x5,
} HV_PARTITION_EVENT, *PHV_PARTITION_EVENT;

typedef enum _HV_PPM_POWER_POLICY_SETTING_ID
{
    HvPowerPolicyIdleDisable = 0x0,
    HvPowerPolicyIdleTimeCheck = 0x1,
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
    HvPowerPolicyIdleScalingAllow = 0x2,
    HvPowerPolicyIdlePromoteThreshold = 0x3,
    HvPowerPolicyIdleDemoteThreshold = 0x4,
    HvPowerPolicyIdleStateMaximum = 0x5,
    HvPowerPolicyMax = 0x6,
#endif
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
    HvCrashdumpEntry = 0x4,
} HV_CRASHDUMP_ACTION, *PHV_CRASHDUMP_ACTION;

typedef enum _HV_PHYSICAL_DEVICE_PROPERTY
{
    HvPhysicalDevicePropertyCapabilities = 0x0,
    HvPhysicalDevicePropertyEnabled = 0x1,
    HvPhysicalDevicePropertyDmaEnabled = 0x1,
    HvPhysicalDevicePropertyAtsEnabled = 0x1,
    HvPhysicalDevicePropertyFaultReporting = 0x2,
    HvPhysicalDevicePropertyIrtRange = 0x4,
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
    HV_DEVICE_TYPE_LOGICAL = 0x0,
    HV_DEVICE_TYPE_PCI = 0x1,
    HV_DEVICE_TYPE_IOAPIC = 0x2,
    HV_DEVICE_TYPE_ACPI = 0x3,
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

typedef enum _HV_PPM_PERF_STATE_REGISTER_TYPE
{
    HvPerfStateRegisterNone = 0x0,
    HvPerfStateRegisterMsr = 0x1,
    HvPerfStateRegisterIo = 0x2,
    HvPerfStateRegisterMemory = 0x3,
} HV_PPM_PERF_STATE_REGISTER_TYPE;

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
        HV_UINT64 Id : 62;
        HV_UINT64 DeviceType : 2;
    } Logical;
    struct
    {
        union
        {
            HV_UINT16 Rid;
            HV_PCI_BDF Bdf;
        };
        HV_UINT16 Segment;
#if defined(_M_AMD64) || defined(_M_IX86)
        HV_UINT8 DeviceType : 2;
        HV_UINT8 SourceShadow : 2;
        HV_UINT8 PhantomFunctionBits : 2;
        HV_UINT8 RsvdZ0 : 2;
        HV_IOAPIC_ID IoApicId;
        union
        {
            HV_PCI_BDF ShadowBdf;
            HV_PCI_BUS_RANGE ShadowBusRange;
        };
#elif defined(_M_ARM64)
        HV_UINT16 RsvdZ0;
        HV_UINT16 PhantomFunctionBits : 2;
        HV_UINT16 RsvdZ1 : 12;
        HV_UINT16 DeviceType : 2;
#endif
    } Pci;
    struct
    {
        HV_UINT32 InputMappingBase;
        HV_UINT32 InputMappingsCount : 30;
        HV_UINT32 DeviceType : 2;
    } Acpi;
    struct
    {
        HV_UINT64 : 62;
        HV_UINT64 DeviceType : 2;
    };
} HV_DEVICE_ID, *PHV_DEVICE_ID;

typedef struct _HV_HPET_CONFIG_INFO
{
    HV_UINT64 BaseAddressDeprecated;
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
    HV_UINT8 Sgx;
} HV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO, *PHV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO;

typedef union _HV_SPA_PAGE_LIST_FLAGS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Deposited : 1;
        HV_UINT64 Minimal : 1;
        HV_UINT64 Hardware : 1;
        HV_UINT64 RsvdZ : 61;
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

typedef union _HV_PPM_PERF_STATE_REGISTER
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
#if defined(_M_AMD64) || defined(_M_IX86)
    struct
    {
        HV_UINT64 Address : 52;
    } Memory;
#endif
} HV_PPM_PERF_STATE_REGISTER, *PHV_PPM_PERF_STATE_REGISTER;

typedef struct _HV_X64_PPM_PERF_STATE_CONFIG_PROPERTY
{
    HV_UINT32 StateCount;
    HV_X64_PPM_PERF_STATE States[64];
    HV_UINT32 DomainId;
    HV_UINT32 NumProcInDomain;
    HV_X64_PPM_PERF_DOMAIN_COORDINATION Coordination;
    HV_PPM_PERF_STATE_REGISTER ControlRegister;
    HV_PPM_PERF_STATE_REGISTER StatusRegister;
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
    HV_PPM_PERF_STATE_REGISTER ControlRegister;
    HV_PPM_PERF_STATE_REGISTER StatusRegister;
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
    HV_PPM_PERF_STATE_REGISTER Doorbell;
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
    HV_UINT64 UpdateRevision;
    HV_UINT64 PreviousUpdateRevision;
    HV_UINT32 PlatformSpecificField1;
    HV_UINT32 PlatformSpecificField2;
} HV_MCUPDATE_UPDATE_STATUS, *PHV_MCUPDATE_UPDATE_STATUS;

typedef union _HV_LOGICAL_PROCESSOR_PROPERTY
{
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_X64_PPM_PERF_STATE_CONFIG_PROPERTY PerfStateConfig;
    HV_X64_PPM_THROTTLE_STATE_CONFIG_PROPERTY ThrottleStateConfig;
    HV_X64_PPM_PCC_CONFIG_PROPERTY PccConfig;
    HV_X64_PPM_PERF_STATE_CAP_PROPERTY PerfStateCap;
#elif defined(_M_ARM64)
    HV_UINT32 UpdateLpIndex;
    HV_PROCESSOR_HW_ID ProcHwId;
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;
#endif
    HV_MACHINE_CHECK_CONTEXT_INFO MachineCheckContextInfo;
    HV_MCUPDATE_UPDATE_STATUS UpdateStatus;
} HV_LOGICAL_PROCESSOR_PROPERTY, *PHV_LOGICAL_PROCESSOR_PROPERTY;

typedef union _HV_DEVICE_DOMAIN_ID
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 Type : 4;
        HV_UINT32 Reserved : 28;
        HV_UINT32 Id;
    };
} HV_DEVICE_DOMAIN_ID, *PHV_DEVICE_DOMAIN_ID;

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
        HV_UINT64 Supervisor : 1;
        HV_UINT64 Reserved : 10;
        HV_UINT64 PageTableRootPfn : 52;
    };
} HV_DEVICE_ADDRESS_SPACE, *PHV_DEVICE_ADDRESS_SPACE;

typedef struct _HV_DEVICE_INTERRUPT_DESCRIPTOR_HEADER
{
    HV_INTERRUPT_TYPE InterruptType;
    HV_INTERRUPT_TRIGGER_MODE TriggerMode;
    HV_UINT32 VectorCount;
    HV_UINT32 Reserved;
} HV_DEVICE_INTERRUPT_DESCRIPTOR_HEADER, *PHV_DEVICE_INTERRUPT_DESCRIPTOR_HEADER;

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
#if defined(_M_AMD64) || defined(_M_IX86)
        HV_UINT32 PasidSupported : 1;
        HV_UINT32 PasidEnabled : 1;
        HV_UINT32 Reserved : 29;
#elif defined(_M_ARM64)
        HV_UINT32 Reserved0 : 1;
        HV_UINT32 AtsEnabled : 1;
        HV_UINT32 VirtualFunction : 1;
        HV_UINT32 SharedInterruptsChild : 1;
        HV_UINT32 VirtualDevice : 1;
        HV_UINT32 AtsSupported : 1;
        HV_UINT32 SmallIrt : 1;
        HV_UINT32 Reserved1 : 24;
#endif
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
        HV_UINT32 PrgResponsePasidRequired : 1;
        HV_UINT32 Reserved : 20;
    };
} HV_DEVICE_PCI_CAPABILITIES, *PHV_DEVICE_PCI_CAPABILITIES;

#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_PROC_STATE_GP_REGS
{
    HV_UINT64 X[13];
    HV_UINT64 Sp;
    HV_UINT64 Pc;
} HV_ARM64_PROC_STATE_GP_REGS, *PHV_ARM64_PROC_STATE_GP_REGS;
#endif

typedef struct _HV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT
{
    HV_CRASHDUMP_ACTION CrashdumpAction;
} HV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT, *PHV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT;

typedef struct _HV_PARTITION_EVENT_COMMIT_PROCESSOR_INDICES_INPUT
{
    HV_UINT32 SchedulableProcessorCount;
} HV_PARTITION_EVENT_COMMIT_PROCESSOR_INDICES_INPUT, *PHV_PARTITION_EVENT_COMMIT_PROCESSOR_INDICES_INPUT;

typedef union _HV_PARTITION_EVENT_INPUT
{
    HV_PARTITION_EVENT_ROOT_CRASHDUMP_INPUT CrashdumpInput;
    HV_PARTITION_EVENT_COMMIT_PROCESSOR_INDICES_INPUT CommitLpIndicesInput;
} HV_PARTITION_EVENT_INPUT, *PHV_PARTITION_EVENT_INPUT;

typedef union _HV_PPM_IDLE_STATE_CONFIG
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
    struct
    {
        HV_UINT32 Hints;
        HV_UINT32 BreakOnMaskedInterrupt : 1;
        HV_UINT32 ReservedZ : 19;
    } Mwait;
    struct
    {
        HV_UINT32 PowerState;
        HV_UINT32 Reserved;
    } Psci;
} HV_PPM_IDLE_STATE_CONFIG, *PHV_PPM_IDLE_STATE_CONFIG;

typedef struct _HV_PPM_IDLE_STATE
{
    HV_PPM_IDLE_STATE_CONFIG Config;
    HV_UINT32 Type;
    HV_UINT32 HardwareLatency;
    HV_UINT32 PowerConsumption;
} HV_PPM_IDLE_STATE, *PHV_PPM_IDLE_STATE;

typedef struct _HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY
{
    HV_UINT32 StateCount;
    HV_PPM_IDLE_STATE States[16];
} HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY, *PHV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY;

typedef struct _HV_PPM_FEEDBACK_REGISTER_PAIR
{
    HV_PPM_PERF_STATE_REGISTER ReferenceCount;
    HV_PPM_PERF_STATE_REGISTER ActualCount;
    HV_UINT8 ResetRegisters;
} HV_PPM_FEEDBACK_REGISTER_PAIR, *PHV_PPM_FEEDBACK_REGISTER_PAIR;

typedef struct _HV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG
{
    HV_UINT32 Count;
    HV_PPM_FEEDBACK_REGISTER_PAIR FeedbackCounters[4];
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
    HV_UINT32 CounterRefreshSequenceNumber;
    HV_UINT32 CounterRefreshReferenceTime;
    HV_UINT32 IdleAccumulationSnapshot;
    HV_UINT32 ActiveTscCountSnapshot;
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

// It seems Windows 11 Build 26100 era only provides the IPv6 option.
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
    HV_UINT32 Execute : 1;
    HV_UINT32 Privileged : 1;
    HV_UINT32 IovAts : 1;
    HV_UINT32 DeviceDomains : 1;
    HV_UINT32 S1DeviceDomains : 1;
    HV_UINT32 RootAts : 1;
    HV_UINT32 DomainTransitionSupported : 1;
    HV_UINT32 La57 : 1;
    HV_UINT32 RootPasid : 1;
    HV_UINT32 RootDefaultDomainAts : 1;
    HV_UINT32 Reserved0 : 21;
    HV_UINT32 PasidCount;
    HV_UINT32 RootSvmIommuIndex;
    HV_UINT32 Reserved1;
} HV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES, *PHV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES;

typedef struct _HV_PHYSICAL_DEVICE_PROPERTY_DMA_ENABLED
{
    HV_UINT8 PasidEnabled;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_UINT32 Reserved2;
} HV_PHYSICAL_DEVICE_PROPERTY_DMA_ENABLED, *PHV_PHYSICAL_DEVICE_PROPERTY_DMA_ENABLED;
typedef HV_PHYSICAL_DEVICE_PROPERTY_DMA_ENABLED HV_PHYSICAL_DEVICE_PROPERTY_ATS_ENABLED, *PHV_PHYSICAL_DEVICE_PROPERTY_ATS_ENABLED;

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

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_REGISTER_VSM_CAPABILITIES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Dr6Shared : 1;
        HV_UINT64 MbecVtlMask : 16;
        HV_UINT64 ReservedZ : 47;
    };
} HV_X64_REGISTER_VSM_CAPABILITIES, *PHV_X64_REGISTER_VSM_CAPABILITIES;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_REGISTER_VSM_CAPABILITIES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 ReservedZ0 : 1;
        HV_UINT64 MbecVtlMask : 16;
        HV_UINT64 DenyLowerVtlStartup : 1;
        HV_UINT64 SupervisorShadowStack : 1;
        HV_UINT64 HardwareHvptAvailable : 1;
        HV_UINT64 SoftwareHvptAvailable : 1;
        HV_UINT64 HardwareHvptRangeBits : 6;
        HV_UINT64 InterceptPageAvailable : 1;
        HV_UINT64 ReturnActionAvailable : 1;
        HV_UINT64 Vtl0AliasMapAvailable : 1;
        HV_UINT64 InterceptNotPresentAvailable : 1;
        HV_UINT64 InstallInterceptEx : 1;
        HV_UINT64 ReservedZ : 32;
    };
} HV_ARM64_REGISTER_VSM_CAPABILITIES, *PHV_ARM64_REGISTER_VSM_CAPABILITIES;
#endif

typedef union _HV_VTL_RETURN_INPUT
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 FastReturn : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_VTL_RETURN_INPUT, *PHV_VTL_RETURN_INPUT;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS
{
    HV_UINT32 MsrIndex;
    struct
    {
        HV_UINT32 Eax;
        HV_UINT32 Ecx;
    };
} HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS, *PHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;
typedef const HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS *PCHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS
{
    HV_REGISTER_NAME HvRegisterName;
} HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS, *PHV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;
typedef const HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS *PCHV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;
#endif

typedef struct _HV_LOGICAL_PROCESSOR_REGISTER_ID
{
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
    HV_LOGICAL_PROCESSOR_REGISTER_TYPE Type;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS Address;
#elif defined(_M_ARM64)
    HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS Address;
#endif
} HV_LOGICAL_PROCESSOR_REGISTER_ID, *PHV_LOGICAL_PROCESSOR_REGISTER_ID;
typedef const HV_LOGICAL_PROCESSOR_REGISTER_ID *PCHV_LOGICAL_PROCESSOR_REGISTER_ID;

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
            HV_UINT32 InterfaceType;
            union
            {
                HV_UINT16 IoPort;
                HV_UINT64 RegistersSpa;
            };
            HV_UINT32 RegistersSize;
            HV_UINT32 BaudRate;
            HV_BOOLEAN ExclusiveMode;
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
            HV_UINT64 Key[4];
            HV_IPV6_ADDRESS HostIP;
            HV_IPV6_ADDRESS TargetIP;
            HV_IPV6_ADDRESS GatewayIP;
            HV_UINT16 HostRootPort;
            HV_UINT16 HostHvPort;
            HV_UINT8 DefaultTargetMacAddress[6];
            HV_UINT32 Flags;
            HV_UINT32 Bus;
            HV_UINT32 Slot;
            HV_UINT16 Segment;
            HV_UINT16 VendorID;
            HV_UINT16 DeviceID;
            HV_UINT8 BaseClass;
            HV_UINT8 SubClass;
            HV_UINT8 ProgIf;
            HV_UINT64 BaseAddressRegisterSPA[6];
            HV_UINT32 BaseAddressRegisterByteCount[6];
            HV_UINT16 BaseAddressRegisterType[6];
            HV_UINT64 KdNetPciMmCfgAddr;
            HV_UINT32 Dbg2TableIndex;
            HV_UINT16 PortType;
            HV_UINT16 PortSubtype;
            HV_UINT32 NameSpace;
            HV_UINT32 KdNetDataSize;
        } Net;
    };
} HV_BOOT_DEBUG_PARAMETERS, *PHV_BOOT_DEBUG_PARAMETERS;

typedef struct _HV_BOOT_PARAMETERS
{
    HV_BOOT_DEBUG_PARAMETERS DebugParams;
    HV_UINT64 Flags;
} HV_BOOT_PARAMETERS, *PHV_BOOT_PARAMETERS;

typedef struct _HV_HARDWARE_DETAILS
{
    HV_UINT32 ErrataType;
    HV_UINT32 SupportPsci : 1;
    HV_UINT32 Reserved : 31;
} HV_HARDWARE_DETAILS, *PHV_HARDWARE_DETAILS;

typedef struct _HV_IMAGE_SECTION_DETAIL
{
    HV_UINT64 SectionPhysicalAddress;
    HV_UINT32 SectionSize;
    HV_UINT64 Writeable : 1;
    HV_UINT64 Executable : 1;
} HV_IMAGE_SECTION_DETAIL, *PHV_IMAGE_SECTION_DETAIL;

typedef struct _HV_IMAGE_DETAIL
{
    HV_UINT32 SectionCount;
    HV_IMAGE_SECTION_DETAIL Sections[15];
} HV_IMAGE_DETAIL, *PHV_IMAGE_DETAIL;

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
    HV_UINT32 RuntimeServicesMemoryRangesCount;
    struct
    {
        HV_UINT64 BasePage;
        HV_UINT64 PageCount;
    } RuntimeServicesMemoryRanges[512];
    HV_HARDWARE_DETAILS HardwareDetails;
    HV_IMAGE_DETAIL HypervisorImageDetail;
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
        HV_LOGICAL_PROCESSOR_INDEX LpIndex;
        HV_UINT32 Reserved;
    };
} HV_MCA_FAULTING_LP_MSR, *PHV_MCA_FAULTING_LP_MSR;

typedef union _HV_DEVICE_PAGE_REQUEST
{
    HV_UINT64 AsUINT64[4];
    struct
    {
        HV_DEVICE_ID DeviceId;
        struct
        {
            HV_UINT64 GroupIndex : 9;
            HV_UINT64 LastInGroup : 1;
            HV_UINT64 Virtual : 1;
            HV_UINT64 Pasid : 20;
            HV_UINT64 Reserved0 : 33;
            HV_UINT64 Read : 1;
            HV_UINT64 Write : 1;
            HV_UINT64 Execute : 1;
            HV_UINT64 Privileged : 1;
            HV_UINT64 Reserved2 : 8;
            HV_UINT64 PageNumber : 52;
            HV_UINT64 Reserved3;
        };
        struct
        {
            HV_UINT64 : 31;
            HV_UINT64 Reserved1 : 30;
            HV_UINT64 InvalidRequest : 1;
            HV_UINT64 ValidateGpa : 1;
            HV_UINT64 Overflow : 1;
        };
        struct
        {
            HV_UINT64 : 63;
            HV_UINT64 SendResponse : 1;
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

typedef HV_UINT64 HV_CPU_GROUP_ID, *PHV_CPU_GROUP_ID;

typedef HV_UINT64 HV_CPU_GROUP_PROPERTY, *PHV_CPU_GROUP_PROPERTY;

typedef HV_UINT32 HV_DEVICE_PR_QUEUE_ID, *PHV_DEVICE_PR_QUEUE_ID;

typedef HV_UINT64 HV_INPUT_PARTITION_PROPERTY_ARG, *PHV_INPUT_PARTITION_PROPERTY_ARG;

typedef HV_UINT64 HV_DEVICE_VA_PAGE_NUMBER, *PHV_DEVICE_VA_PAGE_NUMBER;

typedef HV_UINT64 HV_MSI_ADDRESS, *PHV_MSI_ADDRESS;

typedef HV_UINT32 HV_MODIFY_SPA_PAGE_HOST_ACCESS_FLAGS, *PHV_MODIFY_SPA_PAGE_HOST_ACCESS_FLAGS;

typedef HV_UINT32 HV_LOCK_GPA_PAGE_MAPPING_FLAGS, *PHV_LOCK_GPA_PAGE_MAPPING_FLAGS;

typedef HV_UINT32 HV_UNMAP_GPA_FLAGS, *PHV_UNMAP_GPA_FLAGS;

typedef HV_UINT64 HV_KEY_ID, *PHV_KEY_ID;

typedef HV_UINT8 HV_IOMMU_STATUS_SEVERITY, *PHV_IOMMU_STATUS_SEVERITY;

typedef HV_UINT32 HV_PRECOMMIT_GPA_FLAGS, *PHV_PRECOMMIT_GPA_FLAGS;

typedef HV_UINT16 HV_IOMMU_STATUS, *PHV_IOMMU_STATUS;

#if defined(_M_ARM64)
typedef enum _HV_PARTITION_PROCESSOR_FEATURES_FIELD_INDEX
{
    HvPartitionProcessorFeaturesAsid16Index = 0x0,
    HvPartitionProcessorFeaturesTGran16Index = 0x1,
    HvPartitionProcessorFeaturesTGran64Index = 0x2,
    HvPartitionProcessorFeaturesHafIndex = 0x3,
    HvPartitionProcessorFeaturesHdbsIndex = 0x4,
    HvPartitionProcessorFeaturesPanIndex = 0x5,
    HvPartitionProcessorFeaturesAtS1E1Index = 0x6,
    HvPartitionProcessorFeaturesUaoIndex = 0x7,
    HvPartitionProcessorFeaturesEl0Aarch32Index = 0x8,
    HvPartitionProcessorFeaturesFpIndex = 0x9,
    HvPartitionProcessorFeaturesFpHpIndex = 0xA,
    HvPartitionProcessorFeaturesAdvSimdIndex = 0xB,
    HvPartitionProcessorFeaturesAdvSimdHpIndex = 0xC,
    HvPartitionProcessorFeaturesGicV3V4Index = 0xD,
    HvPartitionProcessorFeaturesGicV4P1Index = 0xE,
    HvPartitionProcessorFeaturesRasIndex = 0xF,
    HvPartitionProcessorFeaturesPmuV3Index = 0x10,
    HvPartitionProcessorFeaturesPmuV3ArmV81Index = 0x11,
    HvPartitionProcessorFeaturesPmuV3ArmV84Index = 0x12,
    HvPartitionProcessorFeaturesPmuV3ArmV85Index = 0x13,
    HvPartitionProcessorFeaturesAesIndex = 0x14,
    HvPartitionProcessorFeaturesPolyMulIndex = 0x15,
    HvPartitionProcessorFeaturesSha1Index = 0x16,
    HvPartitionProcessorFeaturesSha256Index = 0x17,
    HvPartitionProcessorFeaturesSha512Index = 0x18,
    HvPartitionProcessorFeaturesCrc32Index = 0x19,
    HvPartitionProcessorFeaturesAtomicIndex = 0x1A,
    HvPartitionProcessorFeaturesRdmIndex = 0x1B,
    HvPartitionProcessorFeaturesSha3Index = 0x1C,
    HvPartitionProcessorFeaturesSm3Index = 0x1D,
    HvPartitionProcessorFeaturesSm4Index = 0x1E,
    HvPartitionProcessorFeaturesDpIndex = 0x1F,
    HvPartitionProcessorFeaturesFhmIndex = 0x20,
    HvPartitionProcessorFeaturesDcCvapIndex = 0x21,
    HvPartitionProcessorFeaturesDcCvadpIndex = 0x22,
    HvPartitionProcessorFeaturesApaBaseIndex = 0x23,
    HvPartitionProcessorFeaturesApaEpIndex = 0x24,
    HvPartitionProcessorFeaturesApaEp2Index = 0x25,
    HvPartitionProcessorFeaturesApaEp2FpIndex = 0x26,
    HvPartitionProcessorFeaturesApaEp2FpcIndex = 0x27,
    HvPartitionProcessorFeaturesJscvtIndex = 0x28,
    HvPartitionProcessorFeaturesFcmaIndex = 0x29,
    HvPartitionProcessorFeaturesRcpcV83Index = 0x2A,
    HvPartitionProcessorFeaturesRcpcV84Index = 0x2B,
    HvPartitionProcessorFeaturesGpaIndex = 0x2C,
    HvPartitionProcessorFeaturesL1ipPiptIndex = 0x2D,
    HvPartitionProcessorFeaturesDzPermittedIndex = 0x2E,
    HvPartitionProcessorFeaturesSsbsIndex = 0x2F,
    HvPartitionProcessorFeaturesSsbsRwIndex = 0x30,
    HvPartitionProcessorFeaturesSmcccW1SupportedIndex = 0x31,
    HvPartitionProcessorFeaturesSmcccW1MitigatedIndex = 0x32,
    HvPartitionProcessorFeaturesSmcccW2SupportedIndex = 0x33,
    HvPartitionProcessorFeaturesSmcccW2MitigatedIndex = 0x34,
    HvPartitionProcessorFeaturesCsv2Index = 0x35,
    HvPartitionProcessorFeaturesCsv3Index = 0x36,
    HvPartitionProcessorFeaturesSbIndex = 0x37,
    HvPartitionProcessorFeaturesIdcIndex = 0x38,
    HvPartitionProcessorFeaturesDicIndex = 0x39,
    HvPartitionProcessorFeaturesTlbiOsIndex = 0x3A,
    HvPartitionProcessorFeaturesTlbiOsRangeIndex = 0x3B,
    HvPartitionProcessorFeaturesFlagsMIndex = 0x3C,
    HvPartitionProcessorFeaturesFlagsM2Index = 0x3D,
    HvPartitionProcessorFeaturesBf16Index = 0x3E,
    HvPartitionProcessorFeaturesEbf16Index = 0x3F,
    HvPartitionProcessorFeaturesSveBf16Index = 0x40,
    HvPartitionProcessorFeaturesSveEbf16Index = 0x41,
    HvPartitionProcessorFeaturesI8mmIndex = 0x42,
    HvPartitionProcessorFeaturesSveI8mmIndex = 0x43,
    HvPartitionProcessorFeaturesFrinttsIndex = 0x44,
    HvPartitionProcessorFeaturesSpecresIndex = 0x45,
    HvPartitionProcessorFeaturesMtpmuIndex = 0x46,
    HvPartitionProcessorFeaturesRpresIndex = 0x47,
    HvPartitionProcessorFeaturesExsIndex = 0x48,
    HvPartitionProcessorFeaturesSpecSeiIndex = 0x49,
    HvPartitionProcessorFeaturesEtsIndex = 0x4A,
    HvPartitionProcessorFeaturesAfpIndex = 0x4B,
    HvPartitionProcessorFeaturesIesbIndex = 0x4C,
    HvPartitionProcessorFeaturesRngIndex = 0x4D,
    HvPartitionProcessorFeaturesLse2Index = 0x4E,
    HvPartitionProcessorFeaturesIdstIndex = 0x4F,
    HvPartitionProcessorFeaturesRasV1P1Index = 0x50,
    HvPartitionProcessorFeaturesRasFracV1P1Index = 0x51,
    HvPartitionProcessorFeaturesSel2Index = 0x52,
    HvPartitionProcessorFeaturesAmuV1Index = 0x53,
    HvPartitionProcessorFeaturesAmuV1P1Index = 0x54,
    HvPartitionProcessorFeaturesDitIndex = 0x55,
    HvPartitionProcessorFeaturesCcidxIndex = 0x56,
    HvPartitionProcessorFeaturesFgtForInterceptsIndex = 0x57,
    HvPartitionProcessorFeaturesL1ipVpiptIndex = 0x58,
    HvPartitionProcessorFeaturesL1ipViptIndex = 0x59,
    HvPartitionProcessorFeaturesDebugV8Index = 0x5A,
    HvPartitionProcessorFeaturesDebugV8P2Index = 0x5B,
    HvPartitionProcessorFeaturesDebugV8P4Index = 0x5C,
    HvPartitionProcessorFeaturesPmuV3ArmV87Index = 0x5D,
    HvPartitionProcessorFeaturesDoubleLockIndex = 0x5E,
    HvPartitionProcessorFeaturesClrbhbIndex = 0x5F,
    HvPartitionProcessorFeaturesSpeIndex = 0x60,
    HvPartitionProcessorFeaturesSpeV1P1Index = 0x61,
    HvPartitionProcessorFeaturesSpeV1P2Index = 0x62,
    HvPartitionProcessorFeaturesTtCnpIndex = 0x63,
    HvPartitionProcessorFeaturesHpdsIndex = 0x64,
    HvPartitionProcessorFeaturesSveIndex = 0x65,
    HvPartitionProcessorFeaturesSveV2Index = 0x66,
    HvPartitionProcessorFeaturesSveV2P1Index = 0x67,
    HvPartitionProcessorFeaturesSpecFpaccIndex = 0x68,
} HV_PARTITION_PROCESSOR_FEATURES_FIELD_INDEX, *PHV_PARTITION_PROCESSOR_FEATURES_FIELD_INDEX;
#endif

typedef enum _HV_PARTITION_MIRRORING_POLICY
{
    HvPartitionMirroringNone = 0x0,
    HvPartitionMirroringInclude = 0x1,
    HvPartitionMirroringExclude = 0x2,
    HvPartitionMirroringMax = 0x2,
} HV_PARTITION_MIRRORING_POLICY, *PHV_PARTITION_MIRRORING_POLICY;

typedef enum _HV_IMAGE_QUERY_TYPE
{
    ImageQueryTypeModuleCount = 0x0,
    ImageQueryTypeModuleTraits = 0x1,
    ImageQueryTypeSlotVaMappings = 0x2,
    ImageQueryTypeMax = 0x3,
} HV_IMAGE_QUERY_TYPE, *PHV_IMAGE_QUERY_TYPE;

typedef enum _HV_COMPATIBILITY_VERSION
{
    HvCompatibilityVersionRedstone1 = 0x600,
    HvCompatibilityVersionRedstone2 = 0x601,
    HvCompatibilityVersionRedstone3 = 0x602,
    HvCompatibilityVersionRedstone4 = 0x603,
    HvCompatibilityVersionRedstone5 = 0x604,
    HvCompatibilityVersion19H1 = 0x605,
    HvCompatibilityVersionVibranium = 0x606,
    HvCompatibilityVersionManganese = 0x607,
    HvCompatibilityVersionIron = 0x608,
    HvCompatibilityVersionNickel = 0x609,
    HvCompatibilityVersionCopper = 0x60A,
    HvCompatibilityVersionGermanium = 0x1000,
    HvCompatibilityVersionPrerelease = 0xFE00,
    HvCompatibilityVersionExperiment = 0xFF00,
} HV_COMPATIBILITY_VERSION, *PHV_COMPATIBILITY_VERSION;

#if defined(_M_ARM64)
typedef enum _HV_SMC_DATA_PATH_LOCK_STATE
{
    HvSmcDataPathUnlocked = 0x0,
    HvSmcDataPathLockedByHvx = 0x1,
    HvSmcDataPathLockedByVtl1 = 0x2,
} HV_SMC_DATA_PATH_LOCK_STATE, *PHV_SMC_DATA_PATH_LOCK_STATE;
#endif

typedef enum _HV_NON_ARCH_CORE_SHARING_TYPE
{
    HvNonArchCoreSharingUnreported = 0x0,
    HvNonArchCoreSharingOff = 0x1,
    HvNonArchCoreSharingOn = 0x2,
    HvNonArchCoreSharingMax = 0x2,
} HV_NON_ARCH_CORE_SHARING_TYPE, *PHV_NON_ARCH_CORE_SHARING_TYPE;

typedef enum _HV_CPU_GROUP_PROPERTY_CODE
{
    HvCpuGroupPropertyCpuCap = 0x10000,
    HvCpuGroupPropertySchedulingPriority = 0x20000,
    HvCpuGroupPropertyIdleLpReserve = 0x30000,
} HV_CPU_GROUP_PROPERTY_CODE, *PHV_CPU_GROUP_PROPERTY_CODE;

typedef enum _HV_SNP_STATUS
{
    HvSnpStatusNone = 0x0,
    HvSnpStatusAvailable = 0x1,
    HvSnpStatusIncompatible = 0x2,
    HvSnpStatusPspUnavailable = 0x3,
    HvSnpStatusPspInitFailed = 0x4,
    HvSnpStatusPspBadFwVersion = 0x5,
    HvSnpStatusBadConfiguration = 0x6,
    HvSnpStatusPspFwUpdateInProgress = 0x7,
    HvSnpStatusPspRbInitFailed = 0x8,
    HvSnpStatusPspPlatformStatusFailed = 0x9,
    HvSnpStatusPspInitLateFailed = 0xA,
    HvSnpStatusPspInitEarlyFailed = 0xB,
    HvSnpStatusPspUnexpectedState = 0xC,
    HvSnpStatusDisabled = 0xD,
} HV_SNP_STATUS, *PHV_SNP_STATUS;

typedef enum _HV_PARTITION_PERFMON_MODE
{
    HvPartitionPerfmonModeUnsupported = 0x0,
    HvPartitionPerfmonModeDynamicSystem = 0x1,
    HvPartitionPerfmonModeGuest = 0x2,
    HvPartitionPerfmonModeRemote = 0x3,
} HV_PARTITION_PERFMON_MODE, *PHV_PARTITION_PERFMON_MODE;

typedef enum _HV_RESTART_COMPLETION_TYPE
{
    HvRestartCompletionSuccess = 0x0,
    HvRestartCompletionCancelled = 0x1,
} HV_RESTART_COMPLETION_TYPE, *PHV_RESTART_COMPLETION_TYPE;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef enum _HV_X64_PPM_CPPC_CONTEXT_SWITCH_POLICY
{
    HvX64CppcContextSwitchUnsupported = 0x0,
    HvX64CppcContextSwitchLazy = 0x1,
    HvX64CppcContextSwitchAggressive = 0x2,
} HV_X64_PPM_CPPC_CONTEXT_SWITCH_POLICY, *PHV_X64_PPM_CPPC_CONTEXT_SWITCH_POLICY;
#endif

typedef enum _HV_PARTITION_VH_TARGET_CHILDREN_STATE
{
    HvVhDeleteChildren = 0x0,
    HvVhSuspendChildren = 0x1,
    HvVhResumeChildren = 0x2,
} HV_PARTITION_VH_TARGET_CHILDREN_STATE, *PHV_PARTITION_VH_TARGET_CHILDREN_STATE;

typedef enum _HV_SEC_FW_UPDATE_STATUS
{
    HvSecFwUpdateStatusNone = 0x0,
    HvSecFwUpdateStatusSuccess = 0x1,
    HvSecFwUpdateStatusMissing = 0x2,
    HvSecFwUpdateStatusOlder = 0x3,
    HvSecFwUpdateStatusRejected = 0x4,
    HvSecFwUpdateStatusSvnTooLow = 0x5,
    HvSecFwUpdateStatusRollbackWrongVersion = 0x6,
    HvSecFwUpdateStatusPreservingUnsupported = 0x7,
} HV_SEC_FW_UPDATE_STATUS, *PHV_SEC_FW_UPDATE_STATUS;

typedef enum _HV_THREAD_HYPERCALLBASED_COUNTER
{
    StCounterHcVpGuestRunTime = 0x1,
    StCounterHcVpTotalRunTimePercent = 0x2,
    StCounterHcVpHypervisorRunTimePercent = 0x3,
    StCounterHcVpGuestRunTimePercent = 0x4,
    StCounterHcVpGuestRelativeUtilizationPercent = 0x5,
    StCounterHcVpTotalCoreRunTimePercent = 0x6,
    StCounterHcVpTotalMessages = 0x7,
    StCounterHcVpTotalInterceptsBase = 0x8,
    StCounterHcVpTotalIntercepts = 0x9,
    StCounterHcVpTotalInterceptsCost = 0xA,
    StCounterHcVpRemoteRunTimePercent = 0xB,
    StCounterHcVpVtl1RunTimePercent = 0xC,
    StCounterHcVpVtl2RunTimePercent = 0xD,
    StCounterHcVpGlobalReferenceTime = 0xE,
    StCounterHcVpMAXIMUM = 0xF,
} HV_THREAD_HYPERCALLBASED_COUNTER;

typedef enum _HV_EXT_MEMORY_HEAT_HINT_TYPE
{
    HvExtMemoryHeatHintTypeCold = 0x0,
    HvExtMemoryHeatHintTypeHot = 0x1,
    HvExtMemoryHeatHintTypeColdDiscard = 0x2,
    HvExtMemoryHeatHintTypeMax = 0x3,
} HV_EXT_MEMORY_HEAT_HINT_TYPE;

typedef enum _HV_VP_DISPATCH_LOOP_EVENT
{
    HvVpDispatchLoopEventInvalid = 0x0,
    HvVpDispatchLoopEventIntercept = 0x1,
    HvVpDispatchLoopEventCancelled = 0x2,
    HvVpDispatchLoopEventTerminated = 0x3,
} HV_VP_DISPATCH_LOOP_EVENT, *PHV_VP_DISPATCH_LOOP_EVENT;

typedef enum _HV_PAGE_ACCESS_TRACKING_GRANULARITY
{
    HvPageAccessTrackingGranularitySmallPage = 0x0,
    HvPageAccessTrackingGranularityLargePage = 0x1,
} HV_PAGE_ACCESS_TRACKING_GRANULARITY, *PHV_PAGE_ACCESS_TRACKING_GRANULARITY;

typedef enum _HV_TDX_STATUS
{
    HvTdxStatusNone = 0x0,
    HvTdxStatusAvailable = 0x1,
} HV_TDX_STATUS, *PHV_TDX_STATUS;

#if defined(_M_ARM64)
typedef enum _HV_ARM64_SYNTHETIC_MSR
{
    HvSyntheticMsrGuestOsId = 0x40000000,
    HvSyntheticMsrHypercall = 0x40000001,
    HvSyntheticMsrVpIndex = 0x40000002,
    HvSyntheticMsrReset = 0x40000003,
    HvSyntheticMsrCpuMgmtVersion = 0x40000004,
    HvSyntheticMsrTimeRefCount = 0x40000020,
    HvSyntheticMsrReferenceTsc = 0x40000021,
    HvSyntheticMsrTscFrequency = 0x40000022,
    HvSyntheticMsrVpAssistPage = 0x40000073,
    HvSyntheticMsrSControl = 0x40000080,
    HvSyntheticMsrSVersion = 0x40000081,
    HvSyntheticMsrSiefp = 0x40000082,
    HvSyntheticMsrSimp = 0x40000083,
    HvSyntheticMsrEom = 0x40000084,
    HvSyntheticMsrSirb = 0x40000085,
    HvSyntheticMsrSint0 = 0x40000090,
    HvSyntheticMsrSint1 = 0x40000091,
    HvSyntheticMsrSint2 = 0x40000092,
    HvSyntheticMsrSint3 = 0x40000093,
    HvSyntheticMsrSint4 = 0x40000094,
    HvSyntheticMsrSint5 = 0x40000095,
    HvSyntheticMsrSint6 = 0x40000096,
    HvSyntheticMsrSint7 = 0x40000097,
    HvSyntheticMsrSint8 = 0x40000098,
    HvSyntheticMsrSint9 = 0x40000099,
    HvSyntheticMsrSint10 = 0x4000009A,
    HvSyntheticMsrSint11 = 0x4000009B,
    HvSyntheticMsrSint12 = 0x4000009C,
    HvSyntheticMsrSint13 = 0x4000009D,
    HvSyntheticMsrSint14 = 0x4000009E,
    HvSyntheticMsrSint15 = 0x4000009F,
    HvSyntheticMsrSTimer0Config = 0x400000B0,
    HvSyntheticMsrSTimer0Count = 0x400000B1,
    HvSyntheticMsrSTimer1Config = 0x400000B2,
    HvSyntheticMsrSTimer1Count = 0x400000B3,
    HvSyntheticMsrSTimer2Config = 0x400000B4,
    HvSyntheticMsrSTimer2Count = 0x400000B5,
    HvSyntheticMsrSTimer3Config = 0x400000B6,
    HvSyntheticMsrSTimer3Count = 0x400000B7,
    HvSyntheticMsrReserved400000C1 = 0x400000C1,
    HvSyntheticMsrGuestSchedulerEvent = 0x400000C2,
    HvSyntheticMsrGuestIdle = 0x400000F0,
    HvSyntheticMsrDebugDeviceOptions = 0x400000FF,
    HvSyntheticMsrCrashP0 = 0x40000100,
    HvSyntheticMsrCrashP1 = 0x40000101,
    HvSyntheticMsrCrashP2 = 0x40000102,
    HvSyntheticMsrCrashP3 = 0x40000103,
    HvSyntheticMsrCrashP4 = 0x40000104,
    HvSyntheticMsrCrashCtl = 0x40000105,
    HvSyntheticMsrReenlightenmentControl = 0x40000106,
    HvSyntheticMsrTscEmulationControl = 0x40000107,
    HvSyntheticMsrTscEmulationStatus = 0x40000108,
    HvSyntheticMsrSWatchdogConfig = 0x40000110,
    HvSyntheticMsrSWatchdogCount = 0x40000111,
    HvSyntheticMsrSWatchdogStatus = 0x40000112,
    HvSyntheticMsrSTimeUnhaltedTimerConfig = 0x40000114,
    HvSyntheticMsrSTimeUnhaltedTimerCount = 0x40000115,
    HvSyntheticMsrMemoryZeroingControl = 0x40000116,
} HV_ARM64_SYNTHETIC_MSR, *PHV_ARM64_SYNTHETIC_MSR;
#endif

typedef enum _HV_PARTITION_PERFMON_CONFIGURATION_STATUS
{
    HvPartitionPerfmonSuccess = 0x0,
    HvPartitionPerfmonInUse = 0x1,
    HvPartitionPerfmonInterrupted = 0x2,
} HV_PARTITION_PERFMON_CONFIGURATION_STATUS, *PHV_PARTITION_PERFMON_CONFIGURATION_STATUS;

typedef enum _HV_ACCEPT_MEMORY_TYPE
{
    HvAcceptMemoryTypeAny = 0x0,
    HvAcceptMemoryTypeRam = 0x1,
    HvAcceptMemoryTypeCount = 0x2,
} HV_ACCEPT_MEMORY_TYPE;

typedef enum _HV_GPA_ACCESS_TRACKING_RANGE_SIZE
{
    HvGpaAccessTrackingRange4k = 0x0,
    HvGpaAccessTrackingRange2m = 0x1,
    HvGpaAccessTrackingRange1g = 0x2,
    HvGpaAccessTrackingRange512g = 0x3,
    HvGpaAccessTrackingRange256t = 0x4,
    HvGpaAccessTrackingRangeMax = 0x5,
} HV_GPA_ACCESS_TRACKING_RANGE_SIZE, *PHV_GPA_ACCESS_TRACKING_RANGE_SIZE;

typedef enum _HV_CPU_HYPERCALLBASED_COUNTER
{
    StCounterHcLpGuestRunTime = 0x1,
    StCounterHcLpIdleTime = 0x2,
    StCounterHcLpTotalRunTimePercent = 0x3,
    StCounterHcLpHypervisorRunTimePercent = 0x4,
    StCounterHcLpGuestRunTimePercent = 0x5,
    StCounterHcLpIdleTimePercent = 0x6,
    StCounterHcLpTotalInterrupts = 0x7,
    StCounterHcLpMAXIMUM = 0x8,
} HV_CPU_HYPERCALLBASED_COUNTER;

typedef enum _HV_PARTITION_MIRROR_STATE
{
    HvPartitionMirrorNotStarted = 0x0,
    HvPartitionMirrorInProgress = 0x1,
    HvPartitionMirrorComplete = 0x2,
} HV_PARTITION_MIRROR_STATE, *PHV_PARTITION_MIRROR_STATE;

typedef enum _HV_EVENTLOG_EXTENDED_TRACE_MODE
{
    HvEventLogExtendedModeNone = 0x0,
    HvEventLogExtendedModeLegacy = 0x1,
    HvEventLogExtendedModeScenario = 0x2,
    HvEventLogExtendedModeGranular = 0x3,
    HvEventLogExtendedModeCount = 0x4,
} HV_EVENTLOG_EXTENDED_TRACE_MODE, *PHV_EVENTLOG_EXTENDED_TRACE_MODE;

typedef enum _HV_EXT_VIRTUALIZATION_FAULT_CODE
{
    HvExtVirtualizationFaultNone = 0x0,
    HvExtVirtualizationFaultEpf = 0x1,
    HvExtVirtualizationFaultMax = 0x2,
} HV_EXT_VIRTUALIZATION_FAULT_CODE, *PHV_EXT_VIRTUALIZATION_FAULT_CODE;

typedef enum _HV_PLATFORM_STATE_INDEX
{
    HvPlatformStateNonIdle = 0x0,
    HvPlatformStateIdle = 0x1,
} HV_PLATFORM_STATE_INDEX;

typedef enum _HV_EVENTLOG_MODE
{
    HvEventLogModeRegular = 0x0,
    HvEventLogModeCircular = 0x1,
    HvEventLogModeMaximum = 0x1,
} HV_EVENTLOG_MODE, *PHV_EVENTLOG_MODE;

typedef enum _HV_EVENTLOG_EXTENDED_GRANULAR_OPERATION
{
    HvEventLogGranularSet = 0x0,
    HvEventLogGranularAdd = 0x1,
    HvEventLogGranularRemove = 0x2,
    HvEventLogGranularOperationCount = 0x3,
} HV_EVENTLOG_EXTENDED_GRANULAR_OPERATION, *PHV_EVENTLOG_EXTENDED_GRANULAR_OPERATION;

typedef enum _HV_SPA_PAGE_OWNERSHIP
{
    HvSpaPageOwnershipShared = 0x0,
    HvSpaPageOwnershipExclusive = 0x1,
} HV_SPA_PAGE_OWNERSHIP, *PHV_SPA_PAGE_OWNERSHIP;

typedef enum _HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT_CODE
{
    HvCheckGpaPageVtlAccessSuccess = 0x0,
    HvCheckGpaPageVtlAccessMemoryIntercept = 0x1,
} HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT_CODE, *PHV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT_CODE;

typedef enum _HV_RESOURCE_CONTROL_TYPE
{
    HvResourceControlProcessorCache = 0x0,
    HvResourceControlMemoryBandwidth = 0x1,
    HvResourceControlProcessorCacheMonitor = 0x2,
} HV_RESOURCE_CONTROL_TYPE, *PHV_RESOURCE_CONTROL_TYPE;

typedef enum _HV_PPM_IDLE_STATE_CHANGE_METHOD
{
    HvPowerChangeIssueHlt = 0x0,
    HvPowerChangeReadIoThenIssueHlt = 0x1,
    HvPowerChangeReadIo = 0x2,
    HvPowerChangeIssueMwait = 0x3,
    HvPowerChangeIssueWfi = 0x4,
    HvPowerChangeIssuePsci = 0x5,
} HV_PPM_IDLE_STATE_CHANGE_METHOD, *PHV_PPM_IDLE_STATE_CHANGE_METHOD;

typedef enum _HV_HW_WATCHDOG_STATUS
{
    HvHwWatchdogUnsupported = 0x0,
    HvHwWatchdogReady = 0x1,
    HvHwWatchdogStaticAvailable = 0x2,
    HvHwWatchdogDynamicAvailable = 0x3,
    HvHwWatchdogStaticActive = 0x4,
    HvHwWatchdogDynamicActive = 0x5,
} HV_HW_WATCHDOG_STATUS, *PHV_HW_WATCHDOG_STATUS;

typedef enum _HV_PSP_STATUS
{
    HvPspStatusSuccess = 0x0,
    HvPspStatusInvalidPlatformState = 0x1,
    HvPspStatusInvalidGuestState = 0x2,
    HvPspStatusInvalidConfig = 0x3,
    HvPspStatusInvalidLength = 0x4,
    HvPspStatusAlreadyOwned = 0x5,
    HvPspStatusInvalidCertificate = 0x6,
    HvPspStatusPolicyFailure = 0x7,
    HvPspStatusInactive = 0x8,
    HvPspStatusInvalidAddress = 0x9,
    HvPspStatusBadSignature = 0xA,
    HvPspStatusBadMeasurement = 0xB,
    HvPspStatusAsidOwned = 0xC,
    HvPspStatusInvalidAsid = 0xD,
    HvPspStatusWbinvdRequired = 0xE,
    HvPspStatusDfflushRequired = 0xF,
    HvPspStatusInvalidGuest = 0x10,
    HvPspStatusInvalidCommand = 0x11,
    HvPspStatusActive = 0x12,
    HvPspStatusHwerrorPlatform = 0x13,
    HvPspStatusHwerrorUnsafe = 0x14,
    HvPspStatusUnsupported = 0x15,
    HvPspStatusInvalidParam = 0x16,
    HvPspStatusNoResources = 0x17,
    HvPspStatusSecureDataInvalid = 0x18,
    HvPspStatusInvalidPageSize = 0x19,
    HvPspStatusInvalidPageState = 0x1A,
    HvPspStatusInvalidMdataEntry = 0x1B,
    HvPspStatusInvalidPageOwner = 0x1C,
    HvPspStatusAeadOverflow = 0x1D,
    HvPspStatusRingbufferModeExited = 0x1F,
    HvPspStatusRmpInitRequired = 0x20,
    HvPspStatusBadSvn = 0x21,
    HvPspStatusBadVersion = 0x22,
    HvPspStatusShutdownRequired = 0x23,
    HvPspStatusUpdateFailed = 0x24,
} HV_PSP_STATUS, *PHV_PSP_STATUS;

typedef struct HV_DECLSPEC_ALIGN(8) _HV_SUBNODE
{
    HV_UINT64 SubnodeId;
    HV_SUBNODE_TYPE SubnodeType;
} HV_SUBNODE, *PHV_SUBNODE;

typedef struct _HV_PARTITION_PROPERTY_INHERITED_DEVICE_DOMAIN_REGIONS
{
    HV_UINT64 UnitSizePages;
    HV_UINT32 ReservedUnitMap[16];
} HV_PARTITION_PROPERTY_INHERITED_DEVICE_DOMAIN_REGIONS, *PHV_PARTITION_PROPERTY_INHERITED_DEVICE_DOMAIN_REGIONS;

typedef struct _HV_PARTITION_PROPERTY_SHA384
{
    HV_UINT8 Data[48];
} HV_PARTITION_PROPERTY_SHA384, *PHV_PARTITION_PROPERTY_SHA384;

typedef struct _HV_PARTITION_PROPERTY_EX_ROOT_PROCESSOR_FEATURES_EXPERIMENTAL
{
    HV_UINT64 Banks[2];
} HV_PARTITION_PROPERTY_EX_ROOT_PROCESSOR_FEATURES_EXPERIMENTAL, *PHV_PARTITION_PROPERTY_EX_ROOT_PROCESSOR_FEATURES_EXPERIMENTAL;

typedef struct _HV_PARTITION_PROPERTY_VP_SHARED_PAGES
{
    HV_UINT32 Flags;
    HV_UINT64 VpAssistPage;
    HV_UINT64 SimPage;
} HV_PARTITION_PROPERTY_VP_SHARED_PAGES, *PHV_PARTITION_PROPERTY_VP_SHARED_PAGES;

typedef union _HV_PARTITION_PROPERTY_EX
{
    HV_UINT8 Buffer[4096];
    HV_PARTITION_PROPERTY CommonProperty;
    HV_PARTITION_PROPERTY_INHERITED_DEVICE_DOMAIN_REGIONS InheritedDeviceDomainRegions;
    HV_PARTITION_PROPERTY_SHA384 Sha384;
    HV_PARTITION_PROPERTY_EX_ROOT_PROCESSOR_FEATURES_EXPERIMENTAL RootProcessorFeaturesExp;
    HV_PARTITION_PROPERTY_VP_SHARED_PAGES VpSharedPages;
} HV_PARTITION_PROPERTY_EX, *PHV_PARTITION_PROPERTY_EX;

typedef struct _HV_HOST_TIMELINE_INFO
{
    HV_UINT64 TimelineBias;
} HV_HOST_TIMELINE_INFO, *PHV_HOST_TIMELINE_INFO;

typedef struct _HV_SMC_DATA_PATH_PROPERTY
{
    HV_UINT16 LockState;
    HV_UINT16 Reserved;
} HV_SMC_DATA_PATH_PROPERTY, *PHV_SMC_DATA_PATH_PROPERTY;

typedef union _HV_SYSTEM_MIRRORING_PROPERTY
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MirroringPolicy : 1;
        HV_UINT64 HypervisorHotRestart : 1;
        HV_UINT64 Reserved : 62;
    };
} HV_SYSTEM_MIRRORING_PROPERTY, *PHV_SYSTEM_MIRRORING_PROPERTY;

typedef struct _HV_RESOURCE_CONTROL_MONITOR
{
    HV_UINT16 PartId;
    HV_UINT8 Pmg;
    HV_UINT8 Enable;
    HV_UINT32 Reserved;
} HV_RESOURCE_CONTROL_MONITOR, *PHV_RESOURCE_CONTROL_MONITOR;

typedef struct _HV_RESOURCE_CONTROL_VALUE_PROPERTY
{
    HV_RESOURCE_CONTROL_TYPE Type;
    HV_UINT32 Index;
    union
    {
        HV_UINT64 Value;
        HV_RESOURCE_CONTROL_MONITOR Monitor;
    };
} HV_RESOURCE_CONTROL_VALUE_PROPERTY, *PHV_RESOURCE_CONTROL_VALUE_PROPERTY;

typedef struct _HV_RESOURCE_CONTROL_MONITOR_DATA
{
    struct
    {
        HV_UINT8 Valid;
        HV_UINT64 L3OccupancyBytes;
        HV_UINT64 L3TotalBwBytes;
        HV_UINT64 L3LocalBwBytes;
    } ProcessorCache;
} HV_RESOURCE_CONTROL_MONITOR_DATA, *PHV_RESOURCE_CONTROL_MONITOR_DATA;

typedef struct _HV_RESOURCE_CONTROL_SUPPORT_PROPERTY
{
    HV_UINT32 ProcessorCacheAllocationSupport : 1;
    HV_UINT32 ProcessorCacheMonitoringSupport : 1;
    HV_UINT32 ProcessorCacheOccupancySupport : 1;
    HV_UINT32 ProcessorCacheTotalBwSupport : 1;
    HV_UINT32 ProcessorCacheLocalBwSupport : 1;
    HV_UINT32 MemoryBandwidthAllocationSupport : 1;
    HV_UINT32 Reserved1 : 26;
    HV_UINT32 ProcessorCacheMaskWidth;
    HV_UINT32 ProcessorCacheMaskHwReserved;
    HV_UINT32 ProcessorCacheMaskSlots;
    HV_UINT32 ProcessorCacheMonitorSlots;
    HV_UINT32 MemoryBandwidthSlots;
    HV_UINT32 MemoryBandwidthMaxValue;
    HV_UINT32 MemoryBandwidthLinear : 1;
    HV_UINT32 Reserved2 : 31;
} HV_RESOURCE_CONTROL_SUPPORT_PROPERTY, *PHV_RESOURCE_CONTROL_SUPPORT_PROPERTY;

typedef struct _HV_RESOURCE_CONTROL_VALUES_PROPERTY
{
    HV_UINT32 NumValues;
    union
    {
        HV_UINT64 Values[128];
        HV_RESOURCE_CONTROL_MONITOR Monitors[128];
    };
} HV_RESOURCE_CONTROL_VALUES_PROPERTY, *PHV_RESOURCE_CONTROL_VALUES_PROPERTY;

typedef struct _HV_SYSTEM_DIAG_LOG_BUFFER_CONFIG
{
    HV_UINT32 BufferCount;
    HV_UINT32 BufferSizeInPages;
} HV_SYSTEM_DIAG_LOG_BUFFER_CONFIG, *PHV_SYSTEM_DIAG_LOG_BUFFER_CONFIG;

typedef struct _HV_SCHEDULING_INTERVAL_INFO
{
    HV_UINT32 MaxSchedulingIntervalInUs;
    HV_UINT32 MinimumSupportedSchedulingIntervalInUs;
    HV_UINT32 MaximumSupportedSchedulingIntervalInUs;
} HV_SCHEDULING_INTERVAL_INFO, *PHV_SCHEDULING_INTERVAL_INFO;

typedef union _HV_VIRTUALIZATION_FEATURE_SET
{
    HV_UINT64 AsUINT64[4];
    struct
    {
        HV_UINT64 ValFeatureSet;
        union
        {
            struct
            {
                HV_UINT64 FeatureSet;
            } Intel;
            struct
            {
                HV_UINT64 FeatureSet;
            } Amd;
            struct
            {
                HV_UINT64 FeatureSet;
            } Arm;
        };
    };
} HV_VIRTUALIZATION_FEATURE_SET, *PHV_VIRTUALIZATION_FEATURE_SET;

typedef struct _HV_BOOT_CONFIG_PROPERTY
{
    HV_UINT64 BootFlags;
    HV_UINT64 StartupModeNormal;
} HV_BOOT_CONFIG_PROPERTY, *PHV_BOOT_CONFIG_PROPERTY;

#if defined(_M_ARM64)
typedef union _HV_SYNMC_ARM64_EVENT
{
    HV_UINT16 ModelSpecificErrorCode;
    struct
    {
        HV_UINT16 ErrorDetail : 14;
        HV_UINT16 HypervisorError : 1;
        HV_UINT16 SoftwareError : 1;
    };
} HV_SYNMC_ARM64_EVENT, *PHV_SYNMC_ARM64_EVENT;
typedef HV_SYNMC_ARM64_EVENT HV_SYNMC_EVENT, *PHV_SYNMC_EVENT;
#endif

typedef struct _HV_PPM_IDLE_STATE_EX
{
    union
    {
        HV_PPM_IDLE_STATE LegacyHvIdleState;
        struct
        {
            HV_PPM_IDLE_STATE_CONFIG Config;
            unsigned int Type;
            unsigned int HardwareLatency;
            unsigned int PowerConsumption;
        };
    };
    unsigned int MinimumResidency;
} HV_PPM_IDLE_STATE_EX, *PHV_PPM_IDLE_STATE_EX;

typedef struct _HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY_EX
{
    HV_UINT32 Version;
    HV_UINT32 StateCount;
    HV_PPM_IDLE_STATE_EX States[16];
} HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY_EX, *PHV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY_EX;

typedef struct _HV_PROCESSOR_CPPC_REQUEST_REGISTER
{
    HV_UINT64 PhysicalAddress;
    HV_UINT64 Address;
    HV_UINT64 Mask;
    HV_UINT8 AccessSize;
} HV_PROCESSOR_CPPC_REQUEST_REGISTER, *PHV_PROCESSOR_CPPC_REQUEST_REGISTER;

typedef union _HV_PHYSICAL_DEVICE_FLAGS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 VirtualFunction : 1;
        HV_UINT64 PhysicalFunctionRid : 16;
        HV_UINT64 Reserved : 47;
    };
} HV_PHYSICAL_DEVICE_FLAGS, *PHV_PHYSICAL_DEVICE_FLAGS;

typedef struct _HV_PHYSICAL_DEVICE_PROPERTY_FAULT_REPORTING
{
    HV_UINT8 FaultReportingEnabled;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_UINT32 Reserved2;
} HV_PHYSICAL_DEVICE_PROPERTY_FAULT_REPORTING, *PHV_PHYSICAL_DEVICE_PROPERTY_FAULT_REPORTING;

typedef struct _HV_PHYSICAL_DEVICE_PROPERTY_IRT_RANGE
{
    HV_UINT32 BaseIrtIndex;
    HV_UINT32 Count;
} HV_PHYSICAL_DEVICE_PROPERTY_IRT_RANGE, *PHV_PHYSICAL_DEVICE_PROPERTY_IRT_RANGE;

typedef union _HV_VTL_PERMISSION_SET
{
    HV_UINT32 AsUINT32;
    HV_UINT16 VtlPermissionFrom1[2];
} HV_VTL_PERMISSION_SET, *PHV_VTL_PERMISSION_SET;

typedef union _HV_GPA_PAGE_MAPPING_DATA
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Acceptance : 2;
        HV_UINT64 Vtl1Permission : 16;
        HV_UINT64 Vtl2Permission : 16;
    };
} HV_GPA_PAGE_MAPPING_DATA, *PHV_GPA_PAGE_MAPPING_DATA;

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 NmiNotification : 1;
        HV_UINT64 InterruptNotification : 1;
        HV_UINT64 InterruptPriority : 4;
        HV_UINT64 RsvdZ : 42;
        HV_UINT64 Sint : 16;
    };
} HV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER, *PHV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 RsvdZ : 48;
        HV_UINT64 Sint : 16;
    };
} HV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER, *PHV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER;
#endif

typedef union _HV_INTERNAL_ACTIVITY_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 StartupSuspend : 1;
        HV_UINT64 HaltSuspend : 1;
        HV_UINT64 IdleSuspend : 1;
        HV_UINT64 RsvdZ : 61;
    };
} HV_INTERNAL_ACTIVITY_REGISTER, *PHV_INTERNAL_ACTIVITY_REGISTER;

typedef struct _HV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD
{
    HV_UINT16 Status;
} HV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD, *PHV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD;

typedef union _HV_X64_REGISTER_SEV_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 EnableEncryptedState : 1;
        HV_UINT64 ReservedZ : 11;
        HV_UINT64 VmsaGpaPageNumber : 52;
    };
} HV_X64_REGISTER_SEV_CONTROL, *PHV_X64_REGISTER_SEV_CONTROL;

typedef union _HV_PARTITION_VSM_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 MaximumVtl : 4;
        HV_UINT64 Vtl0InterruptInjectionPolicy : 2;
        HV_UINT64 Vtl1InterruptInjectionPolicy : 2;
        HV_UINT64 ReservedZ : 56;
    };
} HV_PARTITION_VSM_CONFIG, *PHV_PARTITION_VSM_CONFIG;

typedef struct _HV_RDT_CAT_COS_BITMASK_PROPERTY
{
    HV_UINT32 CosIndex;
    HV_UINT32 CosBitmask;
} HV_RDT_CAT_COS_BITMASK_PROPERTY, *PHV_RDT_CAT_COS_BITMASK_PROPERTY;

typedef struct _HV_PARK_BLOCK_INFO
{
    HV_UINT32 ParkBlockOffset;
    HV_UINT32 ParkBlockSize;
} HV_PARK_BLOCK_INFO, *PHV_PARK_BLOCK_INFO;

typedef struct _HV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA
{
    HV_UINT16 Status;
} HV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA, *PHV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA;

typedef struct _HV_X64_IO_PORT_READ_COMPLETION_DATA
{
    HV_UINT32 Value;
} HV_X64_IO_PORT_READ_COMPLETION_DATA, *PHV_X64_IO_PORT_READ_COMPLETION_DATA;

typedef union _HV_PICO100_DURATION
{
    HV_UINT64 AsUINT64;
} HV_PICO100_DURATION;

typedef struct _HV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 RangeCount : 5;
    HV_UINT32 Adjust : 1;
    HV_UINT32 HostVisibility : 2;
    HV_UINT32 MemoryType : 6;
    HV_UINT32 Reserved : 18;
    _HV_GPA_PAGE_RANGE Ranges[29];
} HV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE, *PHV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE;

typedef union _HV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Wait : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK, *PHV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK;

typedef struct _HV_SNP_PSP_TCB_VERSION
{
    union
    {
        struct
        {
            HV_UINT64 BootLoader : 8;
            HV_UINT64 Tee : 8;
            HV_UINT64 ReservedZ : 32;
            HV_UINT64 Snp : 8;
            HV_UINT64 Microcode : 8;
        };
        HV_UINT64 AsUINT64;
    };
} HV_SNP_PSP_TCB_VERSION, *PHV_SNP_PSP_TCB_VERSION;

typedef struct _HV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP
{
    HV_CPU_GROUP_ID CpuGroupId;
    HV_UINT16 LpIndexSetSize;
    HV_UINT16 LpIndexSetOffset;
} HV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP, *PHV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP;

typedef union _HV_VP_ASSIST_PAGE_ACTION
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Type : 8;
        HV_UINT64 Reserved : 56;
    };
} HV_VP_ASSIST_PAGE_ACTION, *PHV_VP_ASSIST_PAGE_ACTION;

typedef struct _HV_MINROOT_NUMA_LPS
{
    HV_UINT32 NodeIndex;
    HV_UINT64 Mask[32];
} HV_MINROOT_NUMA_LPS, *PHV_MINROOT_NUMA_LPS;

typedef union _HV_X64_MSR_VP_EXIT_REASON_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 AdditionalReason;
        HV_UINT8 Reason;
        HV_UINT8 ReservedZ[3];
    };
} HV_X64_MSR_VP_EXIT_REASON_CONTENTS, *PHV_X64_MSR_VP_EXIT_REASON_CONTENTS;

typedef struct _HV_PARTITION_PROPERTY_ASSOC
{
    HV_PARTITION_PROPERTY_CODE PropertyCode;
    HV_PARTITION_PROPERTY PropertyValue;
} HV_PARTITION_PROPERTY_ASSOC, *PHV_PARTITION_PROPERTY_ASSOC;

typedef struct _HV_ROOT_PASID_CAPABILITIES_PROPERTY
{
    HV_UINT32 SvmIommuCount;
    HV_UINT32 MinIommuPasidCount;
} HV_ROOT_PASID_CAPABILITIES_PROPERTY, *PHV_ROOT_PASID_CAPABILITIES_PROPERTY;

typedef struct _HV_PSP_DEVICE
{
    union
    {
        struct
        {
            HV_UINT64 MmConfigAddress;
            _HV_PCI_ID PciId;
            HV_UINT64 BridgeMmConfigAddress;
            _HV_PCI_ID BridgePciId;
            struct
            {
                HV_UINT32 Spa;
                HV_UINT32 PageCount;
            } Bar[6];
        } Pci;
        struct
        {
            HV_UINT64 FeatureRegister;
            HV_UINT64 InterruptEnableRegister;
            HV_UINT64 InterruptStatusRegister;
            HV_UINT8 SevMailboxInterruptId;
            HV_UINT8 RsvdZ[7];
            HV_UINT64 SevCmdRespRegister;
            HV_UINT64 SevCmdBufAddrLoRegister;
            HV_UINT64 SevCmdBufAddrHiRegister;
            HV_UINT64 AcpiCmdRespRegister;
        } AcpiV1;
        struct
        {
            HV_UINT64 RegisterBase;
            HV_UINT32 RegisterPages;
            HV_UINT32 FeatureRegister;
            HV_UINT32 InterruptEnableRegister;
            HV_UINT32 InterruptStatusRegister;
            HV_UINT8 SevMailboxInterruptId;
            HV_UINT8 RsvdZ[3];
            HV_UINT32 SevCmdRespRegister;
            HV_UINT32 SevCmdBufAddrLoRegister;
            HV_UINT32 SevCmdBufAddrHiRegister;
            HV_UINT32 AcpiCmdRespRegister;
        } AcpiV2;
    };
    HV_UINT32 IsInitialized : 1;
    HV_UINT32 IsPci : 1;
    HV_UINT32 Reserved0 : 2;
    HV_UINT32 AcpiRevision : 4;
    HV_UINT32 Reserved1 : 24;
} HV_PSP_DEVICE, *PHV_PSP_DEVICE;

typedef struct _HV_SNP_PSP_DEVICES
{
    HV_UINT8 Count;
    HV_PSP_DEVICE PspDevice[2];
} HV_SNP_PSP_DEVICES, *PHV_SNP_PSP_DEVICES;

typedef struct HV_EVENTLOG_EVENTGROUP_CONFIGURATION
{
    HV_UINT32 GroupId;
    HV_UINT16 RsvdZ;
    HV_UINT16 EventCount;
    HV_UINT8 EventId[256];
} *PHV_EVENTLOG_EVENTGROUP_CONFIGURATION;

typedef struct _HV_INPUT_EVENTLOG_SET_EVENTS
{
    HV_EVENTLOG_TYPE EventLogType;
    HV_UINT32 GroupCount;
    HV_UINT64 ConfigurationFlags;
    HV_EVENTLOG_EVENTGROUP_CONFIGURATION Groups[2];
} HV_INPUT_EVENTLOG_SET_EVENTS, *PHV_INPUT_EVENTLOG_SET_EVENTS;

typedef union _HV_REGISTER_HVPT_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 HardwareEnforced : 1;
        HV_UINT64 HardwareRangeBits : 6;
        HV_UINT64 ReservedZ : 4;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_REGISTER_HVPT_CONTROL, *PHV_REGISTER_HVPT_CONTROL;

typedef union _HV_PARTITION_PERFMON_MODE_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 PerfmonMode : 8;
        HV_UINT64 DisableCounting : 1;
        HV_UINT64 Reserved : 55;
    };
} HV_PARTITION_PERFMON_MODE_CONFIG, *PHV_PARTITION_PERFMON_MODE_CONFIG;

typedef union _HV_REGISTER_REFERENCE_TSC
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enable : 1;
        HV_UINT64 ReservedP : 11;
        HV_UINT64 GpaPageNumber : 52;
    };
} HV_REGISTER_REFERENCE_TSC, *PHV_REGISTER_REFERENCE_TSC;

typedef struct _HV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_VTL TargetVtl;
    HV_UINT8 EnableMbec : 1;
    HV_UINT8 EnableSupervisorShadowStack : 1;
    HV_UINT8 EnableHardwareHvpt : 1;
} HV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE, *PHV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE;

typedef union _HV_REGISTER_PARTITION_INFO_PAGE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 Reserved : 11;
        HV_UINT64 GpaPage : 52;
    };
} HV_REGISTER_PARTITION_INFO_PAGE, *PHV_REGISTER_PARTITION_INFO_PAGE;

typedef struct _HV_SEAM_TDMR_RESERVATION
{
    HV_UINT64 BaseAddress;
    HV_UINT64 Size;
} HV_SEAM_TDMR_RESERVATION, *PHV_SEAM_TDMR_RESERVATION;

typedef struct _HV_SEAM_TDMR
{
    HV_UINT64 BaseAddress;
    HV_UINT64 Size;
    HV_UINT64 Pamt1GBaseAddress;
    HV_UINT64 Pamt1GSize;
    HV_UINT64 Pamt2MBaseAddress;
    HV_UINT64 Pamt2MSize;
    HV_UINT64 Pamt4KBaseAddress;
    HV_UINT64 Pamt4KSize;
    HV_UINT64 NumReservedRegions;
    HV_SEAM_TDMR_RESERVATION ReservedRegions[];
} HV_SEAM_TDMR, *PHV_SEAM_TDMR;

typedef union _HV_X64_REGISTER_SEV_HV_DOORBELL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 ReservedZ : 11;
        HV_UINT64 PageNumber : 52;
    };
} HV_X64_REGISTER_SEV_HV_DOORBELL, *PHV_X64_REGISTER_SEV_HV_DOORBELL;

typedef union _HV_X64_REGISTER_SEV_GHCB
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 ReservedZ : 11;
        HV_UINT64 PageNumber : 52;
    };
} HV_X64_REGISTER_SEV_GHCB, *PHV_X64_REGISTER_SEV_GHCB;

typedef struct _HV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA
{
    HV_UINT16 Status;
} HV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA, *PHV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA;

typedef union _HV_EVENTLOG_EXTENDED_TRACE_FLAGS
{
    struct
    {
        HV_UINT64 Rsvd : 8;
        HV_UINT64 Id : 8;
        HV_UINT64 RsvdZ : 48;
    } Scenario;
    struct
    {
        HV_UINT64 Rsvd : 8;
        HV_UINT64 Operation : 8;
        HV_UINT64 RsvdZ : 48;
    } Granular;
    struct
    {
        HV_UINT64 Flags;
    } Legacy;
    struct
    {
        HV_UINT64 Extended : 1;
        HV_UINT64 Mode : 7;
        HV_UINT64 Rsvd : 56;
    } Common;
    HV_UINT64 AsUINT64;
} HV_EVENTLOG_EXTENDED_TRACE_FLAGS, *PHV_EVENTLOG_EXTENDED_TRACE_FLAGS;

typedef union _HV_PARTITION_DIAG_LOG_BUFFER_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 BufferCount;
        HV_UINT32 BufferSizeInPages;
    };
} HV_PARTITION_DIAG_LOG_BUFFER_CONFIG, *PHV_PARTITION_DIAG_LOG_BUFFER_CONFIG;

typedef union _HV_PARTITION_ENLIGHTENMENT_MODIFICATIONS
{
    struct
    {
        HV_UINT64 FavorAutoEoi : 1;
        HV_UINT64 FavorAutoEoiLegacyOs : 1;
        HV_UINT64 Rsvd : 62;
    };
    HV_UINT64 AsUINT64;
} HV_PARTITION_ENLIGHTENMENT_MODIFICATIONS, *PHV_PARTITION_ENLIGHTENMENT_MODIFICATIONS;

typedef struct _HV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD
{
    HV_VP_INDEX VpIndex;
    HV_UINT16 Status;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD, *PHV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD;

typedef union _HV_ARM64_REGISTER_TLBI_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 TlbiEnlightened : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_ARM64_REGISTER_TLBI_CONTROL, *PHV_ARM64_REGISTER_TLBI_CONTROL;

typedef union _HV_SGX_LAUNCH_CONTROL_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Readable : 1;
        HV_UINT64 Writable : 1;
        HV_UINT64 Reserved : 62;
    };
} HV_SGX_LAUNCH_CONTROL_CONFIG, *PHV_SGX_LAUNCH_CONTROL_CONFIG;

typedef struct _HV_LOADER_PCI_SEGMENT_ENTRY
{
    HV_UINT16 SegmentNumber;
    HV_UINT64 ReservedDeviceBitmap[1024];
    struct
    {
        HV_UINT64 AtsBusBitmap[4];
        HV_UINT64 SecureIntegratedAtsDeviceBitmap[1024];
    } Intel;
} HV_LOADER_PCI_SEGMENT_ENTRY, *PHV_LOADER_PCI_SEGMENT_ENTRY;

typedef union _HV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT
{
    HV_UINT64 AsUINT64[2];
    struct
    {
        HV_UINT64 Type : 8;
        HV_UINT64 Reserved : 56;
        HV_UINT32 TargetVp;
        HV_UINT8 TargetVtl;
        HV_UINT8 TargetSint;
        HV_UINT16 FlagNumber;
    };
} HV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT, *PHV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT;

typedef struct _HV_SYNIC_EVENT_INTERCEPT_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Vtl : 4;
    HV_UINT32 Reserved : 28;
    HV_CONNECTION_ID ConnectionId;
    HV_UINT32 FlagNumber;
} HV_SYNIC_EVENT_INTERCEPT_MESSAGE, *PHV_SYNIC_EVENT_INTERCEPT_MESSAGE;

typedef struct _HV_INPUT_GET_PARTITION_RESERVED_PAGES
{
    HV_UINT64 PartitionId;
    union
    {
        HV_UINT64 AsUINT64;
        struct
        {
            HV_UINT64 Continue : 1;
        };
    };
} HV_INPUT_GET_PARTITION_RESERVED_PAGES, *PHV_INPUT_GET_PARTITION_RESERVED_PAGES;

typedef struct _HV_RDT_MBA_COS_VALUE_PROPERTY
{
    HV_UINT32 CosIndex;
    HV_UINT32 CosThrottleValue;
} HV_RDT_MBA_COS_VALUE_PROPERTY, *PHV_RDT_MBA_COS_VALUE_PROPERTY;

typedef union _HV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES
{
    struct
    {
        HV_UINT64 HideHypervisorPresent : 1;
        HV_UINT64 RsvdZ : 63;
    };
    HV_UINT64 AsUINT64;
} HV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES, *PHV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES;

typedef struct _HV_INPUT_GPA_PAGE_PINNING
{
    HV_UINT64 Reserved;
    HV_GPA_PAGE_RANGE GpaRangeList[];
} HV_INPUT_GPA_PAGE_PINNING, *PHV_INPUT_GPA_PAGE_PINNING;

typedef struct _HV_OUTPUT_GET_PARTITION_RESERVED_PAGES
{
    union
    {
        HV_UINT64 AsUINT64;
        HV_UINT16 RangeCount;
    };
    _HV_SPA_PAGE_RANGE RangeList[511];
} HV_OUTPUT_GET_PARTITION_RESERVED_PAGES, *PHV_OUTPUT_GET_PARTITION_RESERVED_PAGES;

typedef union _HV_PARTITION_ISOLATION_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Runnable : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_PARTITION_ISOLATION_CONTROL, *PHV_PARTITION_ISOLATION_CONTROL;

typedef union _HV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT8 Vector;
        HV_UINT8 SampleRate;
        HV_UINT8 ReservedZ[6];
    };
} HV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS, *PHV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS;

typedef struct _HV_LOADER_IOMMU_ENTRY
{
    HV_UINT16 SegmentNumber;
    HV_UINT64 RegisterBaseAddress;
    HV_UINT32 Idr0;
    HV_UINT32 Idr1;
    HV_UINT32 Idr2;
    HV_UINT32 Idr3;
    HV_UINT32 Idr4;
    HV_UINT32 Idr5;
    HV_UINT32 Aidr;
    HV_UINT64 StreamTableBase;
    HV_UINT32 StreamTableSizeInPages;
    HV_UINT32 StrTabBaseCfg;
    HV_UINT32 Mpamidr;
} HV_LOADER_IOMMU_ENTRY, *PHV_LOADER_IOMMU_ENTRY;

typedef struct _HV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES
{
    union
    {
        struct
        {
            HV_UINT32 DeviceTableSizeInPages;
            HV_UINT64 DeviceTableSpaBasePage;
        } Amd;
        struct
        {
            HV_UINT32 ContextTableCount;
            HV_UINT32 InterruptRemappingTableSizeInPages;
            HV_UINT64 RootTableSpaPage;
            HV_UINT64 ContextTableSpaPages[256];
            HV_UINT64 InterruptRemappingTableSpaBasePage;
        } Intel;
    };
    union
    {
        struct
        {
            HV_UINT32 LiveDomainIdSelector : 1;
            HV_UINT32 Reserved : 31;
        };
        HV_UINT32 AsUINT32;
    } Flags;
} HV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES, *PHV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES;

typedef union _HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 ResultCode : 8;
        HV_UINT32 DeniedAccess : 8;
        HV_UINT32 InterceptingVtl : 4;
        HV_UINT32 Reserved0 : 12;
        HV_UINT32 Reserved1;
    };
} HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT, *PHV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT;

typedef union _HV_INSTRUCTION_EMULATION_HINTS_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 PartitionSecureVtlEnabled : 1;
        HV_UINT64 MbecUserExecuteControl : 1;
    };
} HV_INSTRUCTION_EMULATION_HINTS_REGISTER, *PHV_INSTRUCTION_EMULATION_HINTS_REGISTER;

typedef union _HV_PARTITION_ISOLATION_POLICY
{
    HV_UINT64 AsUINT64;
} HV_PARTITION_ISOLATION_POLICY, *PHV_PARTITION_ISOLATION_POLICY;

typedef struct _HV_PSP_REQUEST_COMPLETION_DATA
{
    HV_PSP_STATUS PspStatus;
} HV_PSP_REQUEST_COMPLETION_DATA, *PHV_PSP_REQUEST_COMPLETION_DATA;

typedef struct _HV_SNP_PSP_ID
{
    HV_UINT8 Id[512];
    HV_UINT32 Size;
    HV_UINT8 Count;
} HV_SNP_PSP_ID, *PHV_SNP_PSP_ID;

typedef union HV_USER_MODE_HYPERCALLS
{
    struct
    {
        HV_UINT64 DispatchVp : 1;
        HV_UINT64 AssertVirtualInterrupt : 1;
        HV_UINT64 SignalEventDirect : 1;
        HV_UINT64 ReadGpa : 1;
        HV_UINT64 WriteGpa : 1;
        HV_UINT64 UnregisterInterceptResult : 1;
        HV_UINT64 TranslateVirtualAddressEx : 1;
        HV_UINT64 GetVpRegisters : 1;
        HV_UINT64 SetVpRegisters : 1;
        HV_UINT64 AssertDeviceInterrupt : 1;
        HV_UINT64 RetargetDeviceInterrupt : 1;
        HV_UINT64 PostMessageDirect : 1;
        HV_UINT64 GetVpCpuidValues : 1;
        HV_UINT64 GetVpSetFromMda : 1;
        HV_UINT64 Reserved : 50;
    };
    HV_UINT64 AsUINT64;
} *PHV_USER_MODE_HYPERCALLS;

typedef union _HV_PARTITION_DEPOSIT_STATUS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Success : 1;
        HV_UINT64 Async : 1;
        HV_UINT64 Remote : 1;
        HV_UINT64 Reserved : 61;
    };
} HV_PARTITION_DEPOSIT_STATUS, *PHV_PARTITION_DEPOSIT_STATUS;

typedef union _HV_IOMMU_GVA_RANGE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 PageMaskShift : 6;
        HV_UINT64 Reserved : 6;
        HV_UINT64 PageNumber : 52;
    };
} HV_IOMMU_GVA_RANGE, *PHV_IOMMU_GVA_RANGE;

typedef union _HV_PARTITION_INFO_PAGE
{
    HV_UINT8 Padding[4096];
    HV_UINT32 TlbInUse;
} HV_PARTITION_INFO_PAGE, *PHV_PARTITION_INFO_PAGE;

typedef struct _HV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE
{
    HV_VP_INDEX VpIndex;
    HV_UINT32 Reserved;
} HV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE, *PHV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE;

typedef struct _HV_ARM64_VOLATILE_GP_REGS
{
    HV_UINT64 X[18];
} HV_ARM64_VOLATILE_GP_REGS, *PHV_ARM64_VOLATILE_GP_REGS;

typedef union _HV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 Granularity : 2;
        HV_UINT64 RangeEnabled : 1;
        HV_UINT64 ReservedZ : 60;
    };
} HV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG, *PHV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG;

typedef struct _HV_MEMORY_PROXIMITY_INFO
{
    HV_UINT64 BaseAddress;
    HV_UINT64 EndAddress;
    HV_PROXIMITY_DOMAIN_ID ProximityDomainId;
} HV_MEMORY_PROXIMITY_INFO, *PHV_MEMORY_PROXIMITY_INFO;

typedef struct _HV_DMA_RANGE
{
    HV_UINT64 StartPage;
    HV_UINT32 PageCount;
} HV_DMA_RANGE, *PHV_DMA_RANGE;

typedef union _HV_VP_DISPATCH_LOOP_RESULT
{
    HV_UINT64 AsUINT64;
    struct
    {
        _HV_VP_DISPATCH_LOOP_EVENT ExitEvent;
        HV_UINT32 Reserved;
    };
} HV_VP_DISPATCH_LOOP_RESULT, *PHV_VP_DISPATCH_LOOP_RESULT;

typedef struct _HV_HYPERCALL_INTERCEPT_COMPLETION_DATA
{
    HV_UINT16 Status;
    HV_UINT8 OutputData[];
} HV_HYPERCALL_INTERCEPT_COMPLETION_DATA, *PHV_HYPERCALL_INTERCEPT_COMPLETION_DATA;

typedef struct _HV_INPUT_NOTIFY_EVENT_RING_EMPTY
{
    HV_UINT32 SintIndex;
    HV_UINT32 RsvdZ;
} HV_INPUT_NOTIFY_EVENT_RING_EMPTY, *PHV_INPUT_NOTIFY_EVENT_RING_EMPTY;

typedef union _HV_REGISTER_ISOLATION_CAPABILITIES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 ReservedZ : 64;
    };
} HV_REGISTER_ISOLATION_CAPABILITIES, *PHV_REGISTER_ISOLATION_CAPABILITIES;

typedef union _HV_SEC_FW_VERSION
{
    struct
    {
        HV_UINT64 Build : 32;
        HV_UINT64 MinorVersion : 8;
        HV_UINT64 MajorVersion : 8;
        HV_UINT64 Reserved : 16;
    } Snp;
    HV_UINT64 AsUINT64;
} HV_SEC_FW_VERSION, *PHV_SEC_FW_VERSION;

typedef struct _HV_RESTART_COMPLETION_MESSAGE_PAYLOAD
{
    HV_VP_INDEX VpIndex;
    _HV_RESTART_COMPLETION_TYPE CompletionType;
} HV_RESTART_COMPLETION_MESSAGE_PAYLOAD, *PHV_RESTART_COMPLETION_MESSAGE_PAYLOAD;

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

#if defined(_M_AMD64) || defined(_M_IX86)
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
typedef HV_X64_HYPERVISOR_FEATURES_PRIVATE _HV_HYPERVISOR_FEATURES_PRIVATE;
typedef HV_X64_HYPERVISOR_FEATURES_PRIVATE HV_HYPERVISOR_FEATURES_PRIVATE;
typedef PHV_X64_HYPERVISOR_FEATURES_PRIVATE PHV_HYPERVISOR_FEATURES_PRIVATE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERVISOR_FEATURES_PRIVATE
{
    HV_PARTITION_PRIVILEGE_MASK_PRIVATE PartitionPrivileges;
    HV_UINT32 Reserved0 : 16;
    HV_UINT32 CrossVtlFlushAvailable : 1;
    HV_UINT32 S1ExtendedAsidsAvailable : 1;
    HV_UINT32 Reserved1 : 14;
} HV_ARM64_HYPERVISOR_FEATURES_PRIVATE, *PHV_ARM64_HYPERVISOR_FEATURES_PRIVATE;
typedef HV_ARM64_HYPERVISOR_FEATURES_PRIVATE _HV_HYPERVISOR_FEATURES_PRIVATE;
typedef HV_ARM64_HYPERVISOR_FEATURES_PRIVATE HV_HYPERVISOR_FEATURES_PRIVATE;
typedef PHV_ARM64_HYPERVISOR_FEATURES_PRIVATE PHV_HYPERVISOR_FEATURES_PRIVATE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
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
typedef HV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE _HV_ENLIGHTENMENT_INFORMATION_PRIVATE;
typedef HV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE HV_ENLIGHTENMENT_INFORMATION_PRIVATE;
typedef PHV_X64_ENLIGHTENMENT_INFORMATION_PRIVATE PHV_ENLIGHTENMENT_INFORMATION_PRIVATE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_ENLIGHTENMENT_INFORMATION_PRIVATE
{
    HV_UINT32 Reserved01 : 21;
    HV_UINT32 UseHypercallForMmioAccess : 1;
    HV_UINT32 UseGpaPinningHypercall : 1;
    HV_UINT32 WakeVps : 1;
    HV_UINT32 SyncContext : 1;
    HV_UINT32 Reserved02 : 7;
    HV_UINT32 Reserved1;
    HV_UINT32 Reserved2;
    HV_UINT32 Reserved3;
} HV_ARM64_ENLIGHTENMENT_INFORMATION_PRIVATE, *PHV_ARM64_ENLIGHTENMENT_INFORMATION_PRIVATE;
typedef HV_ARM64_ENLIGHTENMENT_INFORMATION_PRIVATE _HV_ENLIGHTENMENT_INFORMATION_PRIVATE;
typedef HV_ARM64_ENLIGHTENMENT_INFORMATION_PRIVATE HV_ENLIGHTENMENT_INFORMATION_PRIVATE;
typedef PHV_ARM64_ENLIGHTENMENT_INFORMATION_PRIVATE PHV_ENLIGHTENMENT_INFORMATION_PRIVATE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
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
typedef HV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE _HV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
typedef HV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE HV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
typedef PHV_X64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE PHV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE
{
    HV_UINT32 Reserved0 : 8;
    HV_UINT32 ApicEmulationSupported : 1;
    HV_UINT32 DeviceAccessTrackingSupported : 1;
    HV_UINT32 DeviceDomainInputWidth : 8;
    HV_UINT32 HardwareGpaAccessTrackingSupported : 1;
    HV_UINT32 Reserved1 : 13;
    HV_UINT32 Reserved2;
    HV_UINT32 Reserved3;
    HV_UINT32 Reserved4;
} HV_ARM64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE, *PHV_ARM64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
typedef HV_ARM64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE _HV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
typedef HV_ARM64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE HV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
typedef PHV_ARM64_HYPERVISOR_HARDWARE_FEATURES_PRIVATE PHV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE;
#endif

#if defined(_M_AMD64) || defined(_M_IX86)
typedef struct _HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE
{
    HV_UINT32 ReservedEax;
    HV_UINT32 Reserved0 : 3;
    HV_UINT32 DriveIdleTransitions : 1;
    HV_UINT32 Reserved1 : 28;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE, *PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
typedef HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE _HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
typedef HV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
typedef PHV_X64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE PHV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
#elif defined(_M_ARM64)
typedef struct _HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE
{
    HV_UINT32 ReservedEax;
    HV_UINT32 ReservedEbx0 : 3;
    HV_UINT32 DriveIdleTransitions : 1;
    HV_UINT32 ReservedEbx1 : 28;
    HV_UINT32 ReservedEcx;
    HV_UINT32 ReservedEdx;
} HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE, *PHV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
typedef HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE _HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
typedef HV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
typedef PHV_ARM64_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE PHV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE;
#endif

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
    HV_HYPERVISOR_FEATURES_PRIVATE MsHvFeatures;
    HV_ENLIGHTENMENT_INFORMATION_PRIVATE MsHvEnlightenmentInformation;
    HV_HYPERVISOR_HARDWARE_FEATURES_PRIVATE MsHvHardwareFeatures;
    HV_HYPERVISOR_CPU_MANAGEMENT_FEATURES_PRIVATE MsHvCpuManagementFeatures;
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
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_CPUID_RESULT Cpuid;
#endif
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

#if defined(_M_AMD64) || defined(_M_IX86)
typedef union _HV_X64_MSR_RESET_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Reset : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_X64_MSR_RESET_CONTENTS, *PHV_X64_MSR_RESET_CONTENTS;
#elif defined(_M_ARM64)
typedef union _HV_ARM64_MSR_RESET_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Reset : 1;
        HV_UINT64 ReservedZ : 63;
    };
} HV_ARM64_MSR_RESET_CONTENTS, *PHV_ARM64_MSR_RESET_CONTENTS;
#endif

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
    volatile HV_UINT64 TimelineBias;
    volatile HV_UINT64 TscMultiplier;
    HV_UINT64 Reserved2[507];
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
    HvVtlEntryInterrupt = 2,
    HvVtlEntryIntercept = 3,
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
#if defined(_M_AMD64) || defined(_M_IX86)
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
#elif defined(_M_ARM64)
        struct
        {
            HV_UINT64 ReservedZ2;
            HV_UINT64 ReservedZ3;
        };
#endif
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
typedef union _HV_VIRTUALIZATION_FAULT_INFORMATION
{
    struct
    {
        HV_UINT16 Parameter0;
        HV_UINT16 Reserved0;
        HV_UINT32 Code;
        HV_UINT64 Parameter1;
    };
    struct
    {
        HV_UINT8 VeInformationArea[34];
        HV_UINT8 Reserved1[6];
    };
} HV_VIRTUALIZATION_FAULT_INFORMATION, *PHV_VIRTUALIZATION_FAULT_INFORMATION;

typedef struct _HV_MINIMAL_INTERCEPT_INFORMATION
{
    HV_MESSAGE_TYPE MessageType;
} HV_MINIMAL_INTERCEPT_INFORMATION, *PHV_MINIMAL_INTERCEPT_INFORMATION;

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
        HV_MESSAGE InterceptMessage;
        HV_UINT8 VtlReturnActions[256];
    };
    HV_UINT8 ReservedZBytePadding[HV_PAGE_SIZE];
    struct
    {
        HV_UINT8 Padding[112];
        HV_MINIMAL_INTERCEPT_INFORMATION MinimalIntercept;
    };
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

typedef union _HV_X64_MSR_STIME_UNHALTED_TIMER_CONFIG_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Vector : 8;
        HV_UINT64 Enabled : 1;
        HV_UINT64 Reserved : 55;
    };
} HV_X64_MSR_STIME_UNHALTED_TIMER_CONFIG_CONTENTS, *PHV_X64_MSR_STIME_UNHALTED_TIMER_CONFIG_CONTENTS;

/* HvSyntheticMsrMemoryZeroingControl | 0x40000116 */

typedef union _HV_MEMORY_ZEROING_CTRL_REG_CONTENTS
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 ZeroMemoryOnReset : 1;
        HV_UINT64 Reserved : 63;
    };
} HV_MEMORY_ZEROING_CTRL_REG_CONTENTS, *PHV_MEMORY_ZEROING_CTRL_REG_CONTENTS;

/* HvSyntheticMsrVpConfig | 0x40000117 */

typedef union _HV_REGISTER_VP_CONFIG
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Reserved : 64;
    };
} HV_REGISTER_VP_CONFIG, *PHV_REGISTER_VP_CONFIG;

// TSC invariant control

#define HV_X64_MSR_TSC_INVARIANT_CONTROL HvSyntheticMsrTscInvariantControl

typedef union _HV_TSC_INVARIANT_CONTROL
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Enabled : 1;
        HV_UINT64 RsvdZ : 63;
    };
} HV_TSC_INVARIANT_CONTROL, *PHV_TSC_INVARIANT_CONTROL;

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

typedef union _HV_NESTED_STATE_REGISTER
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 NestedVirtActive : 1;
        HV_UINT64 NestedGuestMode : 1;
        HV_UINT64 VmEntryPending : 1;
        HV_UINT64 Reserved : 61;
    };
} HV_NESTED_STATE_REGISTER, *PHV_NESTED_STATE_REGISTER;

// *****************************************************************************
// Hypervisor Hypercall Definitions
//

typedef HV_HYPERCALL_INPUT HV_X64_HYPERCALL_INPUT;

typedef HV_HYPERCALL_OUTPUT HV_X64_HYPERCALL_OUTPUT;

typedef union _HV_HYPERCALL_INPUT_PRIVATE
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT32 CallCode : 14;
        HV_UINT32 IsIsolated : 1;
        HV_UINT32 IsExtended : 1;
        HV_UINT32 IsFast : 1;
        HV_UINT32 VariableHeaderSize : 9;
        HV_UINT32 Reserved1 : 4;
        HV_UINT32 AddressesAreVirtual : 1;
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
    HvCallLaunchHypervisor = 0x008F, // Symbols
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
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
} HV_INPUT_GET_LOGICAL_PROCESSOR_RUN_TIME, *PHV_INPUT_GET_LOGICAL_PROCESSOR_RUN_TIME;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME
{
    HV_NANO100_TIME GlobalTime;
    HV_NANO100_TIME LocalRunTime;
    HV_UINT64 RsvdZ;
    HV_NANO100_TIME HypervisorTime;
} HV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME, *PHV_OUTPUT_GET_LOGICAL_PROCESSOR_RUN_TIME;

// HvCallUpdateHvProcessorFeatures | 0x0005

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UPDATE_PROCESSOR_FEATURES
{
    HV_UINT32 Property;
    HV_UINT32 RsvdZ;
    HV_UINT64 Value;
} HV_INPUT_UPDATE_PROCESSOR_FEATURES, *PHV_INPUT_UPDATE_PROCESSOR_FEATURES;

// HvCallSwitchAliasMap | 0x0006

// HvCallUpdateMicrocode | 0x0007

// HvCallNotifyLongSpinWait | 0x0008

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_NOTIFY_LONG_SPINWAIT
{
    HV_UINT64 InitialLongSpinWait;
} HV_INPUT_NOTIFY_LONG_SPINWAIT, *PHV_INPUT_NOTIFY_LONG_SPINWAIT;

// HvCallParkedVirtualProcessors | 0x0009

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PARK_LOGICAL_PROCESSORS
{
    HV_UINT64 ProcessorMask;
} HV_INPUT_PARK_LOGICAL_PROCESSORS, *PHV_INPUT_PARK_LOGICAL_PROCESSORS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PARKED_VIRTUAL_PROCESSORS
{
    HV_GENERIC_SET ProcessorSet;
} HV_INPUT_PARKED_VIRTUAL_PROCESSORS, *PHV_INPUT_PARKED_VIRTUAL_PROCESSORS;

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
        HV_UINT8 EnableSupervisorShadowStack : 1;
        HV_UINT8 EnableHardwareHvpt : 1;
        HV_UINT8 Reserved : 5;
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

typedef union _HV_DISABLE_PARTITION_VTL_FLAGS
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 ScrubOnly : 1;
        HV_UINT8 Reserved : 7;
    };
} HV_DISABLE_PARTITION_VTL_FLAGS, *PHV_DISABLE_PARTITION_VTL_FLAGS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISABLE_PARTITION_VTL
{
    HV_PARTITION_ID PartitionId;
    HV_VTL TargetVtl;
    HV_DISABLE_PARTITION_VTL_FLAGS Flags;
    HV_UINT16 ReservedZ0;
    HV_UINT32 ReservedZ1;
} HV_INPUT_DISABLE_PARTITION_VTL, *PHV_INPUT_DISABLE_PARTITION_VTL;

// HvCallEnableVpVtl | 0x000F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ENABLE_VP_VTL
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
    HV_INITIAL_VP_CONTEXT VpVtlContext;
} HV_INPUT_ENABLE_VP_VTL, *PHV_INPUT_ENABLE_VP_VTL;

// HvCallDisableVpVtl | 0x0010

typedef union _HV_DISABLE_VP_VTL_FLAGS
{
    HV_UINT8 AsUINT8;
    struct
    {
        HV_UINT8 ScrubOnly : 1;
        HV_UINT8 Reserved : 7;
    };
} HV_DISABLE_VP_VTL_FLAGS, *PHV_DISABLE_VP_VTL_FLAGS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISABLE_VP_VTL
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL TargetVtl;
    HV_DISABLE_VP_VTL_FLAGS Flags;
    HV_UINT16 ReservedZ0;
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

typedef struct _HV_SLOT_TRAITS
{
    HV_UINT64 StartVa;
    HV_UINT32 Size;
    HV_UINT32 IsPrimarySlot : 1;
    HV_UINT32 IsSlotActive : 1;
    HV_UINT32 IsSlotCommitted : 1;
    HV_UINT32 ReservedZ0 : 29;
    HV_UINT32 Checksum;
    HV_UINT32 Timestamp;
} HV_SLOT_TRAITS, *PHV_SLOT_TRAITS;

typedef struct _HV_MODULE_TRAITS
{
    HV_WCHAR ModuleName[8];
    HV_SLOT_TRAITS SlotTraits[3];
} HV_MODULE_TRAITS, *PHV_MODULE_TRAITS;

typedef union _HV_GPA_PAGE_PERMISSION
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Valid : 1;
        HV_UINT64 Writable : 1;
        HV_UINT64 Executable : 1;
        HV_UINT64 ReservedZ0 : 9;
        HV_UINT64 GpaPage : 40;
        HV_UINT64 ReservedZ1 : 12;
    };
} HV_GPA_PAGE_PERMISSION, *PHV_GPA_PAGE_PERMISSION;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_IMAGE_INFO
{
    HV_IMAGE_QUERY_TYPE QueryType;
    HV_UINT32 ReservedZ0;
    union
    {
        HV_UINT64 ModuleIndex;
        struct
        {
            HV_UINT64 ModuleIndex : 4;
            HV_UINT64 SlotIndex : 2;
            HV_UINT64 PageCount : 16;
            HV_UINT64 ReservedZ0 : 42;
            HV_UINT64 StartVa;
        } Mapping;
    };
} HV_INPUT_QUERY_IMAGE_INFO, *PHV_INPUT_QUERY_IMAGE_INFO;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_IMAGE_INFO
{
    HV_UINT32 ModuleCount;
    HV_MODULE_TRAITS ModuleTraits;
    HV_GPA_PAGE_PERMISSION GpaPagePerm[512];
} HV_OUTPUT_QUERY_IMAGE_INFO, *PHV_OUTPUT_QUERY_IMAGE_INFO;

// HvCallMapImagePages | 0x0017

typedef union _HV_VA_PERMISSION
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Valid : 1;
        HV_UINT64 Writable : 1;
        HV_UINT64 Executable : 1;
        HV_UINT64 ReservedZ0 : 9;
        HV_UINT64 VirtualPageFrame : 52;
    };
} HV_VA_PERMISSION, *PHV_VA_PERMISSION;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_IMAGE_PAGES
{
    HV_UINT64 ModuleIndex : 4;
    HV_UINT64 SlotIndex : 2;
    HV_UINT64 ReservedZ0 : 58;
    HV_VA_PERMISSION VirtualPageFramePerm[];
} HV_INPUT_MAP_IMAGE_PAGES, *PHV_INPUT_MAP_IMAGE_PAGES;

// HvCallCommitPatch | 0x0018

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_COMMIT_PATCH
{
    HV_UINT64 ModuleIndex : 4;
    HV_UINT64 SlotIndex : 2;
    HV_UINT64 UseTargetPatch : 1;
    HV_UINT64 ReservedZ0 : 57;
    HV_UINT64 PatchRoutineVa;
    HV_MEMORY_DESCRIPTOR Descriptor;
} HV_INPUT_COMMIT_PATCH, *PHV_INPUT_COMMIT_PATCH;

// HvCallSyncContext | 0x0019

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SYNC_CONTEXT
{
    HV_UINT64 Flags;
    HV_UINT64 ProcessorMask;
} HV_INPUT_SYNC_CONTEXT, *PHV_INPUT_SYNC_CONTEXT;

// HvCallSyncContextEx | 0x001A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SYNC_CONTEXT_EX
{
    HV_UINT64 Flags;
    HV_GENERIC_SET ProcessorSet;
} HV_INPUT_SYNC_CONTEXT_EX, *PHV_INPUT_SYNC_CONTEXT_EX;

// HvCallSetPerfRegister | 0x001B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PERF_REGISTER
{
    HV_UINT32 ProcessorIndex;
    HV_PPM_PERF_STATE_REGISTER Register;
    HV_UINT64 PreserveMask;
    HV_UINT64 Value;
} HV_INPUT_SET_PERF_REGISTER, *PHV_INPUT_SET_PERF_REGISTER;

// HvCallGetPerfRegister | 0x001C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PERF_REGISTER
{
    HV_UINT32 ProcessorIndex;
    HV_PPM_PERF_STATE_REGISTER Register;
} HV_INPUT_GET_PERF_REGISTER, *PHV_INPUT_GET_PERF_REGISTER;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PERF_REGISTER
{
    HV_UINT64 Value;
} HV_OUTPUT_GET_PERF_REGISTER, *PHV_OUTPUT_GET_PERF_REGISTER;

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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PARTITION_V1
{
    HV_UINT64 Flags;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_COMPATIBILITY_VERSION CompatibilityVersion;
    HV_PARTITION_CREATION_PROPERTIES_V1 V1Properties;
} HV_INPUT_CREATE_PARTITION_V1, *PHV_INPUT_CREATE_PARTITION_V1;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PARTITION_V2
{
    HV_UINT64 Flags;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_COMPATIBILITY_VERSION CompatibilityVersion;
    HV_PARTITION_CREATION_PROPERTIES_V2 Properties;
} HV_INPUT_CREATE_PARTITION_V2, *PHV_INPUT_CREATE_PARTITION_V2;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PARTITION
{
    HV_UINT64 Flags;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_COMPATIBILITY_VERSION CompatibilityVersion;
    HV_PARTITION_CREATION_PROPERTIES PartitionCreationProperties;
    HV_PARTITION_ISOLATION_PROPERTIES IsolationProperties;
} HV_INPUT_CREATE_PARTITION, *PHV_INPUT_CREATE_PARTITION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_CREATE_PARTITION
{
    HV_PARTITION_ID NewPartitionId;
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_VP_V1
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_UINT32 Padding;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
    HV_UINT64 Flags;
} HV_INPUT_CREATE_VP_V1, *PHV_INPUT_CREATE_VP_V1;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_UINT8 Padding[3];
    HV_UINT8 SubnodeType;
    HV_UINT64 SubnodeId;
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
    HV_UINT32 Reserved1;
    HV_UINT64 Reserved2;
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PORT
{
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_UINT32 Reserved;
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISCONNECT_PORT
{
    HV_PARTITION_ID ConnectionPartition;
    HV_CONNECTION_ID ConnectionId;
    HV_UINT32 IsDoorbell : 1;
    HV_UINT32 Reserved : 31;
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

typedef struct _HV_EVENTLOG_INIT_TYPE
{
    HV_UINT16 EventLogType; // HV_EVENTLOG_TYPE
    HV_UINT16 EventLogMode; // HV_EVENTLOG_MODE
} HV_EVENTLOG_INIT_TYPE, *PHV_EVENTLOG_INIT_TYPE;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INITIALIZE_EVENTLOG_BUFFER_GROUP
{
    HV_EVENTLOG_INIT_TYPE EventLogInitType;
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
    HV_UINT32 Reserved;
    union
    {
        struct
        {
            HV_UINT16 EventType;
            HV_UINT16 ReservedZ1;
            HV_UINT32 ReservedZ2;
            HV_UINT64 Period;
        } PerfCounter;
        HV_UINT8 IommuLiveHandoff;
        HV_SLEEP_STATE_INFO SetSleepStateInformation;
        HV_MACHINE_CHECK_PROPERTY_INFO MachineCheckStateInformation;
        HV_HYPERVISOR_DEBUG_PROPERTY Debug;
        HV_PPM_POWER_POLICY_SETTING PowerPolicySetting;
        HV_HPET_CONFIG_INFO HpetConfigInfo;
        HV_HPET_ENABLED_INFO HpetEnabledInfo;
        HV_HOST_TIMELINE_INFO HostTimeline;
        HV_SMC_DATA_PATH_PROPERTY SmcDataPath;
        HV_SYSTEM_MIRRORING_PROPERTY SystemMirroring;
        HV_RESOURCE_CONTROL_VALUE_PROPERTY ResourceControl;
        HV_UINT8 GuestAssert;
        HV_UINT32 MaxSchedulingIntervalInUs;
        HV_UINT32 ProtoAbiVersion;
        HV_SPA_PAGE_RANGE CrashdumpAreaAddress;
        HV_UINT64 DefaultIoCacheBitmap;
        HV_UINT8 HardwareIsolationEnabled;
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ADD_LOGICAL_PROCESSOR
{
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_APIC_ID ApicId;
#elif defined(_M_ARM64)
    HV_PROCESSOR_HW_ID ProcHwId;
#endif
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_UINT64 Flags;
#endif
} HV_INPUT_ADD_LOGICAL_PROCESSOR, *PHV_INPUT_ADD_LOGICAL_PROCESSOR;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_ADD_LOGICAL_PROCESSOR
{
    HV_LP_STARTUP_STATUS StartupStatus;
} HV_OUTPUT_ADD_LOGICAL_PROCESSOR, *PHV_OUTPUT_ADD_LOGICAL_PROCESSOR;

// HvCallRemoveLogicalProcessor | 0x0077

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_REMOVE_LOGICAL_PROCESSOR
{
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
    HV_UINT64 Flags;
} HV_INPUT_REMOVE_LOGICAL_PROCESSOR, *PHV_INPUT_REMOVE_LOGICAL_PROCESSOR;

// HvCallQueryNumaDistance | 0x0078

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_NUMA_DISTANCE
{
    HV_UINT32 CpuProximityId;
    HV_UINT32 MemoryProximityId;
} HV_INPUT_QUERY_NUMA_DISTANCE, *PHV_INPUT_QUERY_NUMA_DISTANCE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_NUMA_TOPOLOGY
{
    HV_UINT64 Distance;
} HV_OUTPUT_QUERY_NUMA_DISTANCE, *PHV_OUTPUT_QUERY_NUMA_DISTANCE;

// HvCallSetLogicalProcessorProperty | 0x0079

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_LOGICAL_PROCESSOR_PROPERTY
{
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
    HV_LOGICAL_PROCESSOR_PROPERTY_TYPE Type;
    HV_LOGICAL_PROCESSOR_PROPERTY Property;
} HV_INPUT_SET_LOGICAL_PROCESSOR_PROPERTY, *PHV_INPUT_SET_LOGICAL_PROCESSOR_PROPERTY;

// HvCallGetLogicalProcessorProperty | 0x007A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_LOGICAL_PROCESSOR_PROPERTY
{
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
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
#if defined(_M_ARM64)
    HV_UINT32 Reserved;
#endif
    union
    {
#if defined(_M_AMD64) || defined(_M_IX86)
        HV_PPM_POWER_POLICY_SETTING_ID SettingId;
#elif defined(_M_ARM64)
        HV_UINT64 AsUINT64;
        HV_LOGICAL_PROCESSOR_INDEX LpIndex;
        struct
        {
            HV_RESOURCE_CONTROL_TYPE Type;
            HV_UINT32 Id;
        } Resource;
#endif
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
    HV_IOMMU_INIT_STATUS IommuInitStatus;
    HV_HYPERVISOR_LAUNCH_STATS HvLaunchStats;
    HV_SCHEDULER_TYPE SchedulerType;
    HV_PLATFORM_VIRTUALIZATION_SUPPORT_INFO VirtualizationInfo;
    HV_PPM_POWER_POLICY_SETTING PowerPolicySetting;
    HV_TSC_SYNC_STATUS TscSyncStatus;
    HV_HPET_CONFIG_INFO HpetConfigInfo;
    HV_HPET_INTERRUPT_INFO HpetInterruptInfo;
    HV_HPET_ENABLED_INFO HpetEnabledInfo;
    HV_ROOT_SVM_CAPABILITIES_PROPERTY RootSvmCapabilities;
    HV_ROOT_NUMA_COST_PAGES_PROPERTY RootNumaCostPages;
    HV_UINT64 HvHostPageTableRoot;
    HV_SPA_PAGE_RANGE HvHostDbgTransferPagesRange;
    HV_SMC_DATA_PATH_PROPERTY SmcDataPath;
    HV_UINT8 DmaInitializeBlocked;
    HV_RESOURCE_CONTROL_MONITOR_DATA ResourceMonitorData;
    HV_RESOURCE_CONTROL_SUPPORT_PROPERTY ResourceControlSupport;
    HV_RESOURCE_CONTROL_VALUES_PROPERTY ResourceControlValues;
    HV_UINT32 GuestStateScrubbingStatus;
    HV_SYSTEM_DIAG_LOG_BUFFER_CONFIG SystemDiagnosticsLog;
    HV_UINT8 IommuLiveHandoff;
    HV_UINT32 IommuDomainIdSelector;
    HV_UINT8 GuestAssert;
    HV_UINT32 LogicalProcessorCount;
    HV_SCHEDULING_INTERVAL_INFO SchedulingInterval;
    HV_SUBNODE SubnodeInfo[16];
    HV_VIRTUALIZATION_FEATURE_SET VirtualizationFeatures;
    HV_BOOT_CONFIG_PROPERTY BootConfig;
    HV_UINT32 RebootCount;
    HV_UINT32 ProtoAbiVersion;
    HV_SYSTEM_MIRRORING_PROPERTY SystemMirroring;
    HV_UINT64 MicrocodeLatencyTime;
    HV_SPA_PAGE_RANGE CrashdumpAreaAddress;
} HV_OUTPUT_GET_SYSTEM_PROPERTY, *PHV_OUTPUT_GET_SYSTEM_PROPERTY;

// HvCallMapDeviceInterrupt | 0x007C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_UINT64 Flags;
#elif defined(_M_ARM64)
    HV_UINT32 Flags;
    HV_UINT32 BaseIrtIndex;
    HV_INTERRUPT_ENTRY LogicalInterruptEntry;
#endif
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
#if defined(_M_ARM64)
    HV_UINT32 Flags;
#endif
} HV_INPUT_UNMAP_DEVICE_INTERRUPT, *PHV_INPUT_UNMAP_DEVICE_INTERRUPT;

// HvCallRetargetDeviceInterrupt | 0x007E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RETARGET_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ASSERT_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_INTERRUPT_ENTRY InterruptEntry;
} HV_INPUT_ASSERT_DEVICE_INTERRUPT, *PHV_INPUT_ASSERT_DEVICE_INTERRUPT;

// HvCallReserved0081 | 0x0081

// HvCallAttachDevice | 0x0082

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ATTACH_DEVICE
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
    HV_ATTACH_DEVICE_FLAGS Flags;
    HV_VTL Vtl;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_DEVICE_PCI_CAPABILITIES PciCapabilities;
    HV_UINT32 Reserved2;
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PREPARE_FOR_SLEEP
{
    HV_BOOLEAN Entering;
    HV_BOOLEAN ModernStandby;
} HV_INPUT_PREPARE_FOR_SLEEP, *PHV_INPUT_PREPARE_FOR_SLEEP;

// HvCallPrepareForHibernate | 0x0086

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PREPARE_FOR_HIBERNATE
{
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_X64_PROC_STATE_GP_REGS ResumeGpRegs;
#elif defined(_M_ARM64)
    HV_ARM64_PROC_STATE_GP_REGS ResumeGpRegs;
#endif
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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_ASSOCIATED_LP_FOR_MCA
{
    HV_VP_INDEX VpIndex;
} HV_INPUT_QUERY_ASSOCIATED_LP_FOR_MCA, *PHV_INPUT_QUERY_ASSOCIATED_LP_FOR_MCA;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_ASSOCIATED_LP_FOR_MCA
{
    HV_UINT32 Count;
    HV_UINT16 AssociatedLpList[320];
} HV_OUTPUT_QUERY_ASSOCIATED_LP_FOR_MCA, *PHV_OUTPUT_QUERY_ASSOCIATED_LP_FOR_MCA;

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

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INJECT_SYNTHETIC_MACHINE_CHECK
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
#if defined(_M_ARM64)
    HV_SYNMC_EVENT SynmcEvent;
#endif
} HV_INPUT_INJECT_SYNTHETIC_MACHINE_CHECK, *PHV_INPUT_INJECT_SYNTHETIC_MACHINE_CHECK;

// HvCallScrubPartition | 0x008D

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SCRUB_PARTITION
{
    HV_PARTITION_ID PartitionId;
} HV_INPUT_SCRUB_PARTITION, *PHV_INPUT_SCRUB_PARTITION;

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
// HvCallLaunchHypervisor | 0x008F

typedef struct HV_CALL_ATTRIBUTES _HV_X64_INPUT_DISABLE_HYPERVISOR
{
    HV_UINT64 TrampolineCr3;
    HV_UINT64 KernelCr3;
    HV_UINT64 Rip;
} HV_X64_INPUT_DISABLE_HYPERVISOR, *PHV_X64_INPUT_DISABLE_HYPERVISOR;

typedef struct HV_CALL_ATTRIBUTES _HV_ARM64_INPUT_LAUNCH_HYPERVISOR
{
    HV_UINT64 HvEntryPoint;
} HV_ARM64_INPUT_LAUNCH_HYPERVISOR, *PHV_ARM64_INPUT_LAUNCH_HYPERVISOR;

// HvCallModifySparseGpaPages | 0x0090

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MODIFY_SPARSE_GPA_PAGES
{
    HV_PARTITION_ID TargetPartitionId;
    HV_UINT32 MapFlags;
    HV_UINT32 Rsvdz;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_MODIFY_SPARSE_GPA_PAGES, *PHV_INPUT_MODIFY_SPARSE_GPA_PAGES;

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
    HV_PARTITION_ID TargetPartition;
    HV_INTERRUPT_CONTROL InterruptControl;
    HV_UINT64 DestinationAddress;
    HV_INTERRUPT_VECTOR RequestedVector;
    HV_VTL TargetVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
} HV_INPUT_ASSERT_VIRTUAL_INTERRUPT, *PHV_INPUT_ASSERT_VIRTUAL_INTERRUPT;

// HvCallCreatePort | 0x0095

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_PORT
{
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_VTL PortVtl;
    HV_VTL MinConnectionVtl;
    HV_UINT16 ReservedZ0;
    HV_PARTITION_ID ConnectionPartition;
    HV_PORT_INFO PortInfo;
    HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
} HV_INPUT_CREATE_PORT, *PHV_INPUT_CREATE_PORT;

// HvCallConnectPort | 0x0096

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CONNECT_PORT
{
    HV_PARTITION_ID ConnectionPartition;
    HV_CONNECTION_ID ConnectionId;
    HV_VTL ConnectionVtl;
    HV_UINT8 ReservedZ0;
    HV_UINT16 ReservedZ1;
    HV_PARTITION_ID PortPartition;
    HV_PORT_ID PortId;
    HV_UINT32 ReservedZ2;
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
#if defined(_M_AMD64) || defined(_M_IX86)
    HV_APIC_ID ApicIds[];
#elif defined(_M_ARM64)
    HV_PROCESSOR_HW_ID ProcHwIds[];
#endif
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
            HV_LOGICAL_PROCESSOR_INDEX LpIndex;
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
    HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY_EX IdleStateConfigEx;
} HV_OUTPUT_GET_POWER_PROPERTY, *PHV_OUTPUT_GET_POWER_PROPERTY;

// HvCallSetPowerProperty | 0x009C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_POWER_PROPERTY
{
    HV_POWER_PROPERTY_TYPE Type;
    union
    {
        struct
        {
            HV_LOGICAL_PROCESSOR_INDEX LpIndex;
            union
            {
                HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY IdleStateConfig;
                HV_X64_PPM_IDLE_STATE_CONFIG_PROPERTY_EX IdleStateConfigEx;
                HV_UINT32 PercentFrequency;
                HV_PLATFORM_STATE_INDEX NextPlatformStateIndex;
                HV_PROCESSOR_PERF_FEEDBACK_COUNTERS_CONFIG FeedbackCounterConfig;
                HV_UINT32 CppcRequestValue;
                HV_PROCESSOR_CPPC_REQUEST_REGISTER CppcRequestRegister;
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
    HV_PARTITION_ID PartitionId;
    HV_PASID_SPACE_ID PasidSpaceId;
    HV_UINT32 PasidCount;
    HV_UINT64 Pat;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
} HV_INPUT_CREATE_PASID_SPACE, *PHV_INPUT_CREATE_PASID_SPACE;

// HvCallDeletePasidSpace | 0x009E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_PASID_SPACE
{
    HV_PARTITION_ID PartitionId;
    HV_PASID_SPACE_ID PasidSpaceId;
    HV_UINT32 Reserved;
} HV_INPUT_DELETE_PASID_SPACE, *PHV_INPUT_DELETE_PASID_SPACE;

// HvCallSetPasidAddressSpace | 0x009F

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PASID_ADDRESS_SPACE
{
    HV_PARTITION_ID PartitionId;
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
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_PASID_SPACE_ID PasidSpaceId;
    HV_UINT32 Reserved;
} HV_INPUT_ATTACH_PASID_SPACE, *PHV_INPUT_ATTACH_PASID_SPACE;

// HvCallDetachPasidSpace | 0x00A3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DETACH_PASID_SPACE
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
} HV_INPUT_DETACH_PASID_SPACE, *PHV_INPUT_DETACH_PASID_SPACE;

// HvCallEnablePasid | 0x00A4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ENABLE_PASID
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_PASID Pasid;
    HV_UINT32 Reserved;
} HV_INPUT_ENABLE_PASID, *PHV_INPUT_ENABLE_PASID;

// HvCallDisablePasid | 0x00A5

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISABLE_PASID
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_PASID Pasid;
    HV_UINT32 Reserved;
} HV_INPUT_DISABLE_PASID, *PHV_INPUT_DISABLE_PASID;

// HvCallAcknowledgeDevicePageRequest | 0x00A6

// HvCallCreateDevicePrQueue | 0x00A7

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_DEVICE_PR_QUEUE
{
    HV_PARTITION_ID PartitionId;
    HV_UINT32 QueueId;
    HV_UINT32 Size;
    HV_GPA_PAGE_NUMBER BaseGpaPage;
    HV_INTERRUPT_VECTOR InterruptVector;
    HV_VP_INDEX InterruptVpIndex;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
} HV_INPUT_CREATE_DEVICE_PR_QUEUE, *PHV_INPUT_CREATE_DEVICE_PR_QUEUE;

// HvCallDeleteDevicePrQueue | 0x00A8

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_DEVICE_PR_QUEUE
{
    HV_PARTITION_ID PartitionId;
    HV_UINT32 QueueId;
    HV_UINT32 Reserved;
} HV_INPUT_DELETE_DEVICE_PR_QUEUE, *PHV_INPUT_DELETE_DEVICE_PR_QUEUE;

// HvCallSetDevicePrqProperty | 0x00A9

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_DEVICE_PRQ_PROPERTY_HEADER
{
    HV_UINT32 QueueId;
    HV_DEVICE_PRQ_PROPERTY Property;
} HV_INPUT_SET_DEVICE_PRQ_PROPERTY_HEADER, *PHV_INPUT_SET_DEVICE_PRQ_PROPERTY_HEADER;

// HvCallGetPhysicalDeviceProperty | 0x00AA

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PHYSICAL_DEVICE_PROPERTY
{
    HV_DEVICE_ID PhysicalDeviceId;
    HV_PHYSICAL_DEVICE_FLAGS Flags;
    HV_PHYSICAL_DEVICE_PROPERTY Property;
    HV_UINT32 Reserved;
} HV_INPUT_GET_PHYSICAL_DEVICE_PROPERTY, *PHV_INPUT_GET_PHYSICAL_DEVICE_PROPERTY;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PHYSICAL_DEVICE_PROPERTY
{
    HV_PHYSICAL_DEVICE_PROPERTY_CAPABILITIES Capabilities;
    HV_PHYSICAL_DEVICE_PROPERTY_DMA_ENABLED DmaEnabled;
    HV_PHYSICAL_DEVICE_PROPERTY_ATS_ENABLED AtsEnabled;
    HV_PHYSICAL_DEVICE_PROPERTY_FAULT_REPORTING FaultReporting;
    HV_PHYSICAL_DEVICE_PROPERTY_IRT_RANGE IrtRange;
} HV_OUTPUT_GET_PHYSICAL_DEVICE_PROPERTY, *PHV_OUTPUT_GET_PHYSICAL_DEVICE_PROPERTY;

// HvCallSetPhysicalDeviceProperty | 0x00AB

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY_HEADER
{
    HV_DEVICE_ID PhysicalDeviceId;
    HV_PHYSICAL_DEVICE_PROPERTY Property;
    HV_UINT32 Reserved;
} HV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY_HEADER, *PHV_INPUT_SET_PHYSICAL_DEVICE_PROPERTY_HEADER;

// HvCallTranslateVirtualAddressEx | 0x00AC

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS_EX
{
    // Flags to indicate the disposition of the translation.
    HV_TRANSLATE_GVA_RESULT_EX TranslationResult;
    // The GPA to which the GVA translated.
    HV_GPA_PAGE_NUMBER GpaPage;
} HV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS_EX, *PHV_OUTPUT_TRANSLATE_VIRTUAL_ADDRESS_EX;

// HvCallCheckForIoIntercept | 0x00AD

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CHECK_FOR_IO_INTERCEPT
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_INPUT_VTL TargetVtl;
    HV_UINT16 Port;
    HV_UINT8 Size;
    HV_UINT8 IsWrite;
} HV_INPUT_CHECK_FOR_IO_INTERCEPT, *PHV_INPUT_CHECK_FOR_IO_INTERCEPT;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_CHECK_FOR_IO_INTERCEPT
{
    HV_UINT8 Intercept;
} HV_OUTPUT_CHECK_FOR_IO_INTERCEPT, *PHV_OUTPUT_CHECK_FOR_IO_INTERCEPT;

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
    HV_FLUSH_FLAGS Flags;
} HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE, *PHV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE;

// HvCallFlushGuestPhysicalAddressList | 0x00B0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST
{
    HV_SPA AddressSpace;
    HV_FLUSH_FLAGS Flags;
    HV_GPA_PAGE_RANGE GpaRangeList[];
} HV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST, *PHV_INPUT_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST;

// HvCallCreateDeviceDomain | 0x00B1

typedef union _HV_CREATE_DEVICE_DOMAIN_FLAGS
{
    struct
    {
        HV_UINT32 ForwardProgressRequired : 1;
        HV_UINT32 InheritOwningVtl : 1;
        HV_UINT32 Reserved : 30;
    };
    HV_UINT32 AsUINT32;
} HV_CREATE_DEVICE_DOMAIN_FLAGS, *PHV_CREATE_DEVICE_DOMAIN_FLAGS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CREATE_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_CREATE_DEVICE_DOMAIN_FLAGS CreateDeviceDomainFlags;
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

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_CREATE_CPU_GROUP
{
    HV_CPU_GROUP_ID NewCpuGroupId;
} HV_OUTPUT_CREATE_CPU_GROUP, *PHV_OUTPUT_CREATE_CPU_GROUP;

// HvCallDeleteCpuGroup | 0x00B6

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_CPU_GROUP
{
    HV_CPU_GROUP_ID CpuGroupId;
} HV_INPUT_DELETE_CPU_GROUP, *PHV_INPUT_DELETE_CPU_GROUP;

// HvCallGetCpuGroupProperty | 0x00B7

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_CPU_GROUP_PROPERTY
{
    HV_CPU_GROUP_ID CpuGroupId;
    HV_CPU_GROUP_PROPERTY_CODE PropertyCode;
} HV_INPUT_GET_CPU_GROUP_PROPERTY, *PHV_INPUT_GET_CPU_GROUP_PROPERTY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_CPU_GROUP_PROPERTY
{
    HV_CPU_GROUP_PROPERTY PropertyValue;
} HV_OUTPUT_GET_CPU_GROUP_PROPERTY, *PHV_OUTPUT_GET_CPU_GROUP_PROPERTY;

// HvCallSetCpuGroupProperty | 0x00B8

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_CPU_GROUP_PROPERTY
{
    HV_CPU_GROUP_ID CpuGroupId;
    HV_CPU_GROUP_PROPERTY_CODE PropertyCode;
    HV_CPU_GROUP_PROPERTY PropertyValue;
} HV_INPUT_SET_CPU_GROUP_PROPERTY, *PHV_INPUT_SET_CPU_GROUP_PROPERTY;

// HvCallGetCpuGroupAffinity | 0x00B9

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_CPU_GROUP_AFFINITY
{
    HV_CPU_GROUP_ID CpuGroupId;
} HV_INPUT_GET_CPU_GROUP_AFFINITY, *PHV_INPUT_GET_CPU_GROUP_AFFINITY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_CPU_GROUP_AFFINITY
{
    HV_UINT32 LpCount;
    union
    {
        HV_GENERIC_SET Bitset;
        HV_UINT64 BitsetBuffer[7];
    } CpuGroupAffinity;
} HV_OUTPUT_GET_CPU_GROUP_AFFINITY, *PHV_OUTPUT_GET_CPU_GROUP_AFFINITY;

// HvCallGetNextCpuGroup | 0x00BA

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_NEXT_CPU_GROUP
{
    HV_CPU_GROUP_ID PreviousCpuGroupId;
} HV_INPUT_GET_NEXT_CPU_GROUP, *PHV_INPUT_GET_NEXT_CPU_GROUP;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_NEXT_CPU_GROUP
{
    HV_CPU_GROUP_ID NextCpuGroupId;
} HV_OUTPUT_GET_NEXT_CPU_GROUP, *PHV_OUTPUT_GET_NEXT_CPU_GROUP;

// HvCallGetNextCpuGroupPartition | 0x00BB

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_NEXT_CPU_GROUP_PARTITION
{
    HV_CPU_GROUP_ID CpuGroupId;
    HV_PARTITION_ID PreviousPartitionId;
} HV_INPUT_GET_NEXT_CPU_GROUP_PARTITION, *PHV_INPUT_GET_NEXT_CPU_GROUP_PARTITION;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_NEXT_CPU_GROUP_PARTITION
{
    HV_PARTITION_ID NextPartitionId;
} HV_OUTPUT_GET_NEXT_CPU_GROUP_PARTITION, *PHV_OUTPUT_GET_NEXT_CPU_GROUP_PARTITION;

// HvCallAddPhysicalMemory | 0x00BC

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ADD_PHYSICAL_MEMORY
{
    HV_UINT8 Prepare;
    HV_UINT8 LargePage;
    HV_UINT16 Reserved1;
    HV_UINT32 Reserved2;
    HV_GPA_PAGE_NUMBER StartPage;
} HV_INPUT_ADD_PHYSICAL_MEMORY, *PHV_INPUT_ADD_PHYSICAL_MEMORY;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_ADD_PHYSICAL_MEMORY
{
    HV_UINT64 PagesProcessed;
} HV_OUTPUT_ADD_PHYSICAL_MEMORY, *PHV_OUTPUT_ADD_PHYSICAL_MEMORY;

// HvCallCompleteIntercept | 0x00BD

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_COMPLETE_INTERCEPT
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_UINT32 DataSize;
    HV_UINT8 Data[];
} HV_INPUT_COMPLETE_INTERCEPT, *PHV_INPUT_COMPLETE_INTERCEPT;

// HvCallPrecommitGpaPages | 0x00BE

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PRECOMMIT_GPA_PAGES
{
    HV_PARTITION_ID TargetPartitionId;
    HV_UINT32 Flags;
    HV_GPA TargetGpaBase;
} HV_INPUT_PRECOMMIT_GPA_PAGES, *PHV_INPUT_PRECOMMIT_GPA_PAGES;

// HvCallUncommitGpaPages | 0x00BF

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNCOMMIT_GPA_PAGES
{
    HV_PARTITION_ID TargetPartitionId;
    HV_GPA TargetGpaBase;
} HV_INPUT_UNCOMMIT_GPA_PAGES, *PHV_INPUT_UNCOMMIT_GPA_PAGES;

// HvCallSignalEventDirect | 0x00C0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SIGNAL_EVENT_DIRECT
{
    HV_UINT64 TargetPartition;
    HV_VP_INDEX TargetVp;
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
    HV_UINT32 SintIndex;
    HV_UINT8 Message[HV_MESSAGE_SIZE];
} HV_INPUT_POST_MESSAGE_DIRECT, *PHV_INPUT_POST_MESSAGE_DIRECT;

// HvCallDispatchVp | 0x00C2

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DISPATCH_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_UINT32 Flags;
    HV_NANO100_DURATION TimeSlice; // in 100ns
    HV_UINT64 SpecCtrl;
} HV_INPUT_DISPATCH_VP, *PHV_INPUT_DISPATCH_VP;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_DISPATCH_VP
{
    HV_VP_DISPATCH_STATE DispatchState;
    HV_VP_DISPATCH_EVENT DispatchEvent;
} HV_OUTPUT_DISPATCH_VP, *PHV_OUTPUT_DISPATCH_VP;

// HvCallProcessIommuPrq | 0x00C3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PROCESS_IOMMU_PRQ
{
    HV_IOMMU_ID IommuId;
} HV_INPUT_PROCESS_IOMMU_PRQ, *PHV_INPUT_PROCESS_IOMMU_PRQ;

// HvCallDetachDeviceDomain | 0x00C4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DETACH_DEVICE_DOMAIN
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
} HV_INPUT_DETACH_DEVICE_DOMAIN, *PHV_INPUT_DETACH_DEVICE_DOMAIN;

// HvCallDeleteDeviceDomain | 0x00C5

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DELETE_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
} HV_INPUT_DELETE_DEVICE_DOMAIN, *PHV_INPUT_DELETE_DEVICE_DOMAIN;

// HvCallQueryDeviceDomain | 0x00C6

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_DEVICE_VA TargetDeviceVaList[];
} HV_INPUT_QUERY_DEVICE_DOMAIN, *PHV_INPUT_QUERY_DEVICE_DOMAIN;

// HvCallMapSparseDeviceGpaPages | 0x00C7

typedef struct _HV_DEVICE_VA_MAPPING
{
    HV_DEVICE_VA TargetDeviceVa;
    HV_GPA_PAGE_NUMBER GpaPageNumber;
} HV_DEVICE_VA_MAPPING, *PHV_DEVICE_VA_MAPPING;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_SPARSE_DEVICE_GPA_PAGES
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_INPUT_VTL TargetVtl;
    HV_UINT32 MapFlags;
    HV_DEVICE_VA_MAPPING PageList[];
} HV_INPUT_MAP_SPARSE_DEVICE_GPA_PAGES, *PHV_INPUT_MAP_SPARSE_DEVICE_GPA_PAGES;

// HvCallUnmapSparseDeviceGpaPages | 0x00C8

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_SPARSE_DEVICE_GPA_PAGES
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_DEVICE_VA TargetDeviceVaList[];
} HV_INPUT_UNMAP_SPARSE_DEVICE_GPA_PAGES, *PHV_INPUT_UNMAP_SPARSE_DEVICE_GPA_PAGES;

// HvCallGetGpaPagesAccessState | 0x00C9

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_GPA_PAGES_ACCESS_STATE
{
    HV_PARTITION_ID TargetPartitionId;
    HV_GPA_PAGE_ACCESS_STATE_FLAGS Flags;
    HV_GPA_PAGE_NUMBER TargetGpaBase;
} HV_INPUT_GET_GPA_PAGES_ACCESS_STATE, *PHV_INPUT_GET_GPA_PAGES_ACCESS_STATE;

// HvCallGetSparseGpaPagesAccessState | 0x00CA

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_SPARSE_GPA_PAGES_ACCESS_STATE
{
    HV_PARTITION_ID TargetPartitionId;
    HV_GPA_PAGE_ACCESS_STATE_FLAGS Flags;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_GET_SPARSE_GPA_PAGES_ACCESS_STATE, *PHV_INPUT_GET_SPARSE_GPA_PAGES_ACCESS_STATE;

// HvCallInvokeTestFramework | 0x00CB

// HvCallQueryVtlProtectionMaskRange | 0x00CC

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_VTL_PROTECTION_MASK_RANGE
{
    HV_PARTITION_ID TargetPartitionId;
    HV_GPA TargetGpaBase;
    HV_UINT16 TargetVtlSet;
    HV_UINT16 Reserved0;
    HV_UINT32 Reserved1;
} HV_INPUT_QUERY_VTL_PROTECTION_MASK_RANGE, *PHV_INPUT_QUERY_VTL_PROTECTION_MASK_RANGE;

// HvCallModifyVtlProtectionMaskRange | 0x00CD

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MODIFY_VTL_PROTECTION_MASK_RANGE
{
    HV_PARTITION_ID TargetPartitionId;
    HV_GPA TargetGpaBase;
    HV_UINT16 TargetVtlSet;
    HV_UINT16 Reserved0;
    HV_UINT32 Reserved1;
    HV_VTL_PERMISSION_SET VtlPermissionList[];
} HV_INPUT_MODIFY_VTL_PROTECTION_MASK_RANGE, *PHV_INPUT_MODIFY_VTL_PROTECTION_MASK_RANGE;

// HvCallConfigureDeviceDomain | 0x00CE

typedef struct _HV_DEVICE_DOMAIN_SETTINGS
{
    struct
    {
        HV_UINT64 TranslationEnabled : 1;
        HV_UINT64 CoherentTableWalks : 1;
        HV_UINT64 Reserved : 62;
    } Flags;
    HV_UINT64 PageTableRoot0;
    HV_UINT64 PageTableRoot1;
    HV_UINT8 InputSize0;
    HV_UINT8 InputSize1;
    HV_UINT32 Mair0;
    HV_UINT32 Mair1;
    HV_UINT16 Asid;
} HV_DEVICE_DOMAIN_SETTINGS, *PHV_DEVICE_DOMAIN_SETTINGS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CONFIGURE_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_DEVICE_DOMAIN_SETTINGS Settings;
} HV_INPUT_CONFIGURE_DEVICE_DOMAIN, *PHV_INPUT_CONFIGURE_DEVICE_DOMAIN;

// HvCallQueryDeviceDomainProperties | 0x00CF

// HvCallFlushDeviceDomain | 0x00D0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_DEVICE_DOMAIN
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
} HV_INPUT_FLUSH_DEVICE_DOMAIN, *PHV_INPUT_FLUSH_DEVICE_DOMAIN;

// HvCallFlushDeviceDomainList | 0x00D1

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_FLUSH_DEVICE_DOMAIN_LIST
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
    HV_GVA_RANGE_EXTENDED VaList[];
} HV_INPUT_FLUSH_DEVICE_DOMAIN_LIST, *PHV_INPUT_FLUSH_DEVICE_DOMAIN_LIST;

// HvCallAcquireSparseGpaPageHostAccess | 0x00D2
// HvCallReleaseSparseGpaPageHostAccess | 0x00D3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MODIFY_SPARSE_GPA_PAGE_HOST_ACCESS
{
    HV_PARTITION_ID TargetPartitionId;
    HV_UINT32 HostAccess : 2;
    HV_UINT32 Reserved0 : 30;
    HV_UINT32 Reserved1;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_MODIFY_SPARSE_GPA_PAGE_HOST_ACCESS, *PHV_INPUT_MODIFY_SPARSE_GPA_PAGE_HOST_ACCESS;

// HvCallCheckSparseGpaPageVtlAccess | 0x00D4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_CHECK_SPARSE_GPA_PAGE_VTL_ACCESS
{
    HV_PARTITION_ID TargetPartitionId;
    HV_INPUT_VTL TargetVtl;
    HV_UINT8 DesiredAccess;
    HV_UINT16 Reserved0;
    HV_UINT32 Reserved1;
    HV_GPA_PAGE_NUMBER GpaPageList[];
} HV_INPUT_CHECK_SPARSE_GPA_PAGE_VTL_ACCESS, *PHV_INPUT_CHECK_SPARSE_GPA_PAGE_VTL_ACCESS;

// HvCallReserved00d5 | 0x00D5

// HvCallFlushTlb | 0x00D6

// HvCallAcquireSparseSpaPageHostAccess | 0x00D7
// HvCallReleaseSparseSpaPageHostAccess | 0x00D8

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MODIFY_SPARSE_SPA_PAGE_HOST_ACCESS
{
    HV_UINT32 HostAccess : 2;
    HV_UINT32 Reserved : 30;
    HV_UINT32 Flags;
    HV_PARTITION_ID TargetPartitionId;
    HV_SPA_PAGE_NUMBER SpaPageList[];
} HV_INPUT_MODIFY_SPARSE_SPA_PAGE_HOST_ACCESS, *PHV_INPUT_MODIFY_SPARSE_SPA_PAGE_HOST_ACCESS;

// HvCallAcceptGpaPages | 0x00D9

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ACCEPT_GPA_PAGES
{
    HV_PARTITION_ID TargetPartitionId;
    HV_UINT32 MemoryType : 6;
    HV_UINT32 HostVisibility : 2;
    HV_UINT32 VtlSet : 3;
    HV_UINT32 Reserved : 21;
    HV_VTL_PERMISSION_SET VtlPermissionSet;
    HV_GPA_PAGE_NUMBER GpaPageBase;
} HV_INPUT_ACCEPT_GPA_PAGES, *PHV_INPUT_ACCEPT_GPA_PAGES;

// HvCallUnacceptGpaPages | 0x00DA

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNACCEPT_GPA_PAGES
{
    HV_PARTITION_ID TargetPartitionId;
    HV_UINT32 VtlSet : 3;
    HV_UINT32 Reserved : 29;
    HV_VTL_PERMISSION_SET VtlPermissionSet;
    HV_GPA_PAGE_NUMBER GpaPageBase;
} HV_INPUT_UNACCEPT_GPA_PAGES, *PHV_INPUT_UNACCEPT_GPA_PAGES;

// HvCallModifySparseGpaPageHostVisibility | 0x00DB

// Already defined in Mile.HyperV.Guest.Interface.h.

// HvCallLockSparseGpaPageMapping | 0x00DC

typedef union _HV_GPA_PAGE_MAPPING_LOCK_INPUT
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 AcceptPrivate : 1;
        HV_UINT64 Reserved0 : 11;
        HV_UINT64 GpaPage : 40;
        HV_UINT64 Reserved1 : 12;
    };
} HV_GPA_PAGE_MAPPING_LOCK_INPUT, *PHV_GPA_PAGE_MAPPING_LOCK_INPUT;

typedef struct _HV_GPA_PAGE_MAPPING_LOCK_OUTPUT
{
    HV_UINT64 SpaPageOwnership : 1;
    HV_UINT64 SpaPageMemoryType : 4;
    HV_UINT64 RootReadable : 1;
    HV_UINT64 RootWritable : 1;
    HV_UINT64 RootAdjustable : 1;
    HV_UINT64 UntrustedOverlay : 1;
    HV_UINT64 Reserved0 : 3;
    HV_UINT64 SpaPage : 40;
    HV_UINT64 Reserved1 : 12;
    HV_GPA_PAGE_MAPPING_DATA Data;
} HV_GPA_PAGE_MAPPING_LOCK_OUTPUT, *PHV_GPA_PAGE_MAPPING_LOCK_OUTPUT;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_LOCK_SPARSE_GPA_PAGE_MAPPING
{
    HV_PARTITION_ID TargetPartitionId;
    HV_UINT32 Flags;
    HV_UINT32 Reserved;
    HV_GPA_PAGE_MAPPING_LOCK_INPUT LockList[];
} HV_INPUT_LOCK_SPARSE_GPA_PAGE_MAPPING, *PHV_INPUT_LOCK_SPARSE_GPA_PAGE_MAPPING;

// HvCallUnlockSparseGpaPageMapping | 0x00DD

typedef struct _HV_GPA_PAGE_MAPPING_UNLOCK_INPUT
{
    HV_UINT64 SetAttributes : 1;
    HV_UINT64 Reserved0 : 11;
    HV_UINT64 GpaPage : 40;
    HV_UINT64 Reserved1 : 12;
    HV_GPA_PAGE_MAPPING_DATA Data;
} HV_GPA_PAGE_MAPPING_UNLOCK_INPUT, *PHV_GPA_PAGE_MAPPING_UNLOCK_INPUT;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNLOCK_SPARSE_GPA_PAGE_MAPPING
{
    HV_PARTITION_ID TargetPartitionId;
    HV_GPA_PAGE_MAPPING_UNLOCK_INPUT UnlockList[];
} HV_INPUT_UNLOCK_SPARSE_GPA_PAGE_MAPPING, *PHV_INPUT_UNLOCK_SPARSE_GPA_PAGE_MAPPING;

// HvCallRequestProcessorHalt | 0x00DE

typedef union _HV_INPUT_REQUEST_PROCESSOR_HALT_FLAGS
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 UseDefaultSuspend : 1;
        HV_UINT32 RsvdZ : 31;
    };
} HV_INPUT_REQUEST_PROCESSOR_HALT_FLAGS, *PHV_INPUT_REQUEST_PROCESSOR_HALT_FLAGS;

typedef struct _HV_PPM_IDLE_STATE_REQUEST
{
    HV_PPM_IDLE_STATE_CONFIG Config;
    HV_UINT32 CStateType;
    HV_INPUT_REQUEST_PROCESSOR_HALT_FLAGS Flags;
} HV_PPM_IDLE_STATE_REQUEST, *PHV_PPM_IDLE_STATE_REQUEST;

typedef union HV_CALL_ATTRIBUTES _HV_INPUT_REQUEST_PROCESSOR_HALT
{
    HV_PPM_IDLE_STATE_REQUEST IdleRequest;
    HV_UINT64 AsUINT64[2];
} HV_INPUT_REQUEST_PROCESSOR_HALT, *PHV_INPUT_REQUEST_PROCESSOR_HALT;

// HvCallGetInterceptData | 0x00DF

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_INTERCEPT_DATA
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
} HV_INPUT_GET_INTERCEPT_DATA, *PHV_INPUT_GET_INTERCEPT_DATA;

// HvCallQueryDeviceInterruptTarget | 0x00E0

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_QUERY_DEVICE_INTERRUPT_TARGET
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_INTERRUPT_ENTRY InterruptEntry;
} HV_INPUT_QUERY_DEVICE_INTERRUPT_TARGET, *PHV_INPUT_QUERY_DEVICE_INTERRUPT_TARGET;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_DEVICE_INTERRUPT_TARGET
{
    HV_UINT32 InterruptTargetSize;
    union
    {
        HV_DEVICE_INTERRUPT_TARGET InterruptTarget;
        struct
        {
            HV_DEVICE_INTERRUPT_TARGET_HEADER InterruptTargetHeader;
            union
            {
                HV_GENERIC_SET InterruptTargetProcessorSet;
                HV_GENERIC_SET_HEADER InterruptTargetProcessorSetHeader;
            };
        };
    };
    HV_UINT64 InterruptTargetProcessorSetBankContents[4];
    HV_INTERRUPT_ENTRY InterruptEntry;
} HV_OUTPUT_QUERY_DEVICE_INTERRUPT_TARGET, *PHV_OUTPUT_QUERY_DEVICE_INTERRUPT_TARGET;

// HvCallMapVpStatePage | 0x00E1

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_VP_STATE_PAGE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VP_STATE_PAGE_TYPE Type;
} HV_INPUT_MAP_VP_STATE_PAGE, *PHV_INPUT_MAP_VP_STATE_PAGE;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_MAP_VP_STATE_PAGE
{
    HV_GPA_PAGE_NUMBER MapLocation;
} HV_OUTPUT_MAP_VP_STATE_PAGE, *PHV_OUTPUT_MAP_VP_STATE_PAGE;

// HvCallUnmapVpStatePage | 0x00E2

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNMAP_VP_STATE_PAGE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VP_STATE_PAGE_TYPE Type;
} HV_INPUT_UNMAP_VP_STATE_PAGE, *PHV_INPUT_UNMAP_VP_STATE_PAGE;

// HvCallGetVpState | 0x00E3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL InputVtl;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_VP_STATE_DATA StateData;
    HV_UINT64 OutputDataPfns[];
} HV_INPUT_GET_VP_STATE, *PHV_INPUT_GET_VP_STATE;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_VP_STATE
{
#if defined(_M_AMD64) || defined(_M_IX86)

    HV_LOCAL_INTERRUPT_CONTROLLER_STATE InterruptControllerState;
    HV_SYNTHETIC_TIMERS_STATE SyntheticTimersState;
#elif defined(_M_ARM64)
    HV_UINT64 Reserved0;
#endif
} HV_OUTPUT_GET_VP_STATE, *PHV_OUTPUT_GET_VP_STATE;

// HvCallSetVpState | 0x00E4

typedef union _HV_INPUT_SET_VP_STATE_DATA
{
    HV_UINT64 Pfns;
    HV_UINT8 Bytes;
} HV_INPUT_SET_VP_STATE_DATA, *PHV_INPUT_SET_VP_STATE_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_VP_STATE
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_VTL InputVtl;
    HV_UINT8 Reserved0;
    HV_UINT16 Reserved1;
    HV_VP_STATE_DATA StateData;
    HV_INPUT_SET_VP_STATE_DATA Data[];
} HV_INPUT_SET_VP_STATE, *PHV_INPUT_SET_VP_STATE;

// HvCallGetVpSetFromMda | 0x00E5

// HvCallReserved00e6 | 0x00E6

// HvCallCreateIptBuffers | 0x00E7

// HvCallDeleteIptBuffers | 0x00E8

// HvCallControlHypervisorIptTrace | 0x00E9

// HvCallReserveDeviceInterrupt | 0x00EA

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESERVE_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_UINT32 VectorCount;
    HV_UINT64 Flags;
    HV_INTERRUPT_ENTRY LogicalInterruptEntry;
    HV_UINT32 BaseIrtIndex;
} HV_INPUT_RESERVE_DEVICE_INTERRUPT, *PHV_INPUT_RESERVE_DEVICE_INTERRUPT;

// HvCallPersistDevice | 0x00EB

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PERSIST_DEVICE
{
    HV_PARTITION_ID PartitionId;
    HV_DEVICE_ID DeviceId;
    HV_ATTACH_DEVICE_FLAGS Flags;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_DEVICE_PCI_CAPABILITIES PciCapabilities;
    HV_UINT16 PhysicalFunctionRid;
} HV_INPUT_PERSIST_DEVICE, *PHV_INPUT_PERSIST_DEVICE;

// HvCallUnpersistDevice | 0x00EC

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNPERSIST_DEVICE
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
} HV_INPUT_UNPERSIST_DEVICE, *PHV_INPUT_UNPERSIST_DEVICE;

// HvCallPersistDeviceInterrupt | 0x00ED

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_PERSIST_DEVICE_INTERRUPT
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_INTERRUPT_ENTRY InterruptEntry;
    HV_UINT32 VectorCount;
    HV_UINT64 Flags;
} HV_INPUT_PERSIST_DEVICE_INTERRUPT, *PHV_INPUT_PERSIST_DEVICE_INTERRUPT;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_PERSIST_DEVICE_INTERRUPT
{
    HV_UINT32 BaseIrtIndex;
} HV_OUTPUT_PERSIST_DEVICE_INTERRUPT, *PHV_OUTPUT_PERSIST_DEVICE_INTERRUPT;

// HvCallRefreshPerformanceCounters | 0x00EE

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_REFRESH_PERFORMANCE_COUNTERS
{
    HV_LOGICAL_PROCESSOR_INDEX LpIndex;
} HV_INPUT_REFRESH_PERFORMANCE_COUNTERS, *PHV_INPUT_REFRESH_PERFORMANCE_COUNTERS;

// HvCallImportIsolatedPages | 0x00EF

// HvCallReserved00f0 | 0x00F0

// HvCallCompleteIsolatedImport | 0x00F1

typedef union _HV_PARTITION_COMPLETE_ISOLATED_IMPORT_DATA
{
    HV_UINT64 Reserved;
} HV_PARTITION_COMPLETE_ISOLATED_IMPORT_DATA, *PHV_PARTITION_COMPLETE_ISOLATED_IMPORT_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_COMPLETE_ISOLATED_IMPORT
{
    HV_PARTITION_ID PartitionId;
    HV_PARTITION_COMPLETE_ISOLATED_IMPORT_DATA ImportData;
} HV_INPUT_COMPLETE_ISOLATED_IMPORT, *PHV_INPUT_COMPLETE_ISOLATED_IMPORT;

// HvCallIssueSnpPspGuestRequest | 0x00F2

// HvCallRootSignalEvent | 0x00F3

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ROOT_SIGNAL_EVENT
{
    HV_CONNECTION_ID ConnectionId;
    HV_UINT16 FlagNumber;
    HV_UINT16 RsvdZ;
} HV_INPUT_ROOT_SIGNAL_EVENT, *PHV_INPUT_ROOT_SIGNAL_EVENT;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_ROOT_SIGNAL_EVENT
{
    HV_PARTITION_ID DestinationPartitionId;
    HV_VP_INDEX DestinationVpIndex;
    HV_UINT8 NewlySignalled;
} HV_OUTPUT_ROOT_SIGNAL_EVENT, *PHV_OUTPUT_ROOT_SIGNAL_EVENT;

// HvCallGetVpCpuidValues | 0x00F4

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_VP_CPUID_VALUES
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
    HV_GET_VP_CPUID_VALUES_FLAGS Flags;
    HV_UINT32 ReservedZ;
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

typedef union HV_CALL_ATTRIBUTES _HV_INPUT_READ_SYSTEM_MEMORY
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 Spa : 52;
        HV_UINT64 Uncached : 1;
        HV_UINT64 Size : 4;
        HV_UINT64 ReservedZ0 : 7;
    };
} HV_INPUT_READ_SYSTEM_MEMORY, *PHV_INPUT_READ_SYSTEM_MEMORY;

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_READ_SYSTEM_MEMORY
{
    HV_UINT64 Reg64;
    HV_UINT32 Reg32;
    HV_UINT16 Reg16;
    HV_UINT8 Reg8;
} HV_OUTPUT_READ_SYSTEM_MEMORY, *PHV_OUTPUT_READ_SYSTEM_MEMORY;

// HvCallSetHwWatchdogConfig | 0x00F6

typedef union HV_CALL_ATTRIBUTES _HV_INPUT_SET_HW_WATCHDOG_CONFIG
{
    HV_UINT8 Data[HV_ANYSIZE_ARRAY];
} HV_INPUT_SET_HW_WATCHDOG_CONFIG, *PHV_INPUT_SET_HW_WATCHDOG_CONFIG;

// HvCallRemovePhysicalMemory | 0x00F7

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_REMOVE_PHYSICAL_MEMORY
{
    HV_UINT8 Prepare;
    HV_UINT8 LargePage;
    HV_UINT16 Reserved1;
    HV_UINT32 Reserved2;
    HV_UINT64 StartPage;
} HV_INPUT_REMOVE_PHYSICAL_MEMORY, *PHV_INPUT_REMOVE_PHYSICAL_MEMORY;

// HvCallLogHypervisorSystemConfig | 0x00F8

// HvCallIssueNestedSnpPspRequests | 0x00F9

// HvCallReserved00fa | 0x00FA

// HvCallSubsumeInitializedMemory | 0x00FB

// HvCallSubsumeVp | 0x00FC

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SUBSUME_VP
{
    HV_PARTITION_ID PartitionId;
    HV_VP_INDEX VpIndex;
} HV_INPUT_SUBSUME_VP, *PHV_INPUT_SUBSUME_VP;

// HvCallDestroySubsumedContext | 0x00FD

// HvCallWriteSysDiagEvent | 0x00FE

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_WRITE_SYS_DIAG_EVENT
{
    HV_EVENTLOG_ENTRY_HEADER Header;
    HV_UINT32 DataSize;
    HV_UINT8 Data[];
} HV_INPUT_WRITE_SYS_DIAG_EVENT, *PHV_INPUT_WRITE_SYS_DIAG_EVENT;

// HvCallDepositMemoryMirroring | 0x00FF

// HvCallSetDeviceCapabilities | 0x0100

typedef union HV_CALL_ATTRIBUTES _HV_SET_DEVICE_CAPABILITIES_FLAGS
{
    HV_UINT32 AsUINT32;
    struct
    {
        HV_UINT32 Clear : 1;
        HV_UINT32 Set : 1;
        HV_UINT32 SvmSupported : 1;
        HV_UINT32 DmaEnabled : 1;
        HV_UINT32 AtsEnabled : 1;
        HV_UINT32 PasidSupported : 1;
        HV_UINT32 Reserved : 26;
    };
} HV_SET_DEVICE_CAPABILITIES_FLAGS, *PHV_SET_DEVICE_CAPABILITIES_FLAGS;

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_DEVICE_CAPABILITIES
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_SET_DEVICE_CAPABILITIES_FLAGS Flags;
    HV_DEVICE_PCI_CAPABILITIES PciCapabilities;
} HV_INPUT_SET_DEVICE_CAPABILITIES, *PHV_INPUT_SET_DEVICE_CAPABILITIES;

// HvCallGetPartitionPropertyEx | 0x0101

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_PARTITION_PROPERTY_EX
{
    HV_PARTITION_ID PartitionId;
    HV_PARTITION_PROPERTY_CODE PropertyCode;
    HV_INPUT_PARTITION_PROPERTY_ARG Arg;
} HV_INPUT_GET_PARTITION_PROPERTY_EX, *PHV_INPUT_GET_PARTITION_PROPERTY_EX;

typedef struct HV_CALL_ATTRIBUTES _HV_OUTPUT_GET_PARTITION_PROPERTY_EX
{
    HV_PARTITION_PROPERTY_EX PropertyValue;
} HV_OUTPUT_GET_PARTITION_PROPERTY_EX, *PHV_OUTPUT_GET_PARTITION_PROPERTY_EX;

// HvCallGetGpaRangesAccessState | 0x0102

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_GET_GPA_RANGES_ACCESS_STATE
{
    HV_UINT64 PartitionId;
    HV_GPA_PAGE_ACCESS_STATE_FLAGS Flags;
    HV_UINT64 BaseGpaPage;
    HV_GPA_ACCESS_TRACKING_RANGE_SIZE RangeSize;
    HV_UINT32 Reserved;
} HV_INPUT_GET_GPA_RANGES_ACCESS_STATE, *PHV_INPUT_GET_GPA_RANGES_ACCESS_STATE;

// HvCallRestorePartitionTime | 0x0103

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESTORE_PARTITION_TIME
{
    HV_UINT64 PartitionId;
    HV_UINT32 TscSequence;
    HV_UINT32 ReservedZ;
    HV_UINT64 ReferenceTime;
    HV_UINT64 Tsc;
} HV_INPUT_RESTORE_PARTITION_TIME, *PHV_INPUT_RESTORE_PARTITION_TIME;

// HvCallQueryAssociatedLpsForMcaEx | 0x0104

typedef union HV_CALL_ATTRIBUTES _HV_OUTPUT_QUERY_ASSOCIATED_LP_FOR_MCA_EX
{
    HV_GENERIC_SET AssociatedLpSet;
    HV_UINT64 AssociatedLpSetBuffer[7];
} HV_OUTPUT_QUERY_ASSOCIATED_LP_FOR_MCA_EX, *PHV_OUTPUT_QUERY_ASSOCIATED_LP_FOR_MCA_EX;

// HvCallQueryPartitionReservedPages | 0x0105

// HvCallMemoryMappedIoRead | 0x0106

// HvCallMemoryMappedIoWrite | 0x0107

// HvCallMapDmaRange | 0x0108

// HvCallUnmapDmaRange | 0x0109

// HvCallSetPartitionPropertyEx | 0x010A

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_PARTITION_PROPERTY_EX
{
    HV_PARTITION_ID PartitionId;
    HV_PARTITION_PROPERTY_CODE PropertyCode;
    HV_INPUT_PARTITION_PROPERTY_ARG Arg;
    HV_PARTITION_PROPERTY_EX PropertyValue[];
} HV_INPUT_SET_PARTITION_PROPERTY_EX, *PHV_INPUT_SET_PARTITION_PROPERTY_EX;

// HvCallAttachDevicePrQueue | 0x010B

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_ATTACH_DEVICE_PR_QUEUE
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
    HV_DEVICE_PR_QUEUE_ID PrQueueId;
    HV_UINT32 Reserved;
} HV_INPUT_ATTACH_DEVICE_PR_QUEUE, *PHV_INPUT_ATTACH_DEVICE_PR_QUEUE;

// HvCallDetachDevicePrQueue | 0x010C

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_DETACH_DEVICE_PR_QUEUE
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
} HV_INPUT_DETACH_DEVICE_PR_QUEUE, *PHV_INPUT_DETACH_DEVICE_PR_QUEUE;

// HvCallReserveDeviceDomainAttachment | 0x010D

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_RESERVE_DEVICE_DOMAIN_ATTACHMENT
{
    HV_INPUT_DEVICE_DOMAIN DeviceDomain;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
} HV_INPUT_RESERVE_DEVICE_DOMAIN_ATTACHMENT, *PHV_INPUT_RESERVE_DEVICE_DOMAIN_ATTACHMENT;

// HvCallUnreserveDeviceDomainAttachment | 0x010E

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_UNRESERVE_DEVICE_DOMAIN_ATTACHMENT
{
    HV_PARTITION_ID PartitionId;
    HV_LOGICAL_DEVICE_ID LogicalDeviceId;
} HV_INPUT_UNRESERVE_DEVICE_DOMAIN_ATTACHMENT, *PHV_INPUT_UNRESERVE_DEVICE_DOMAIN_ATTACHMENT;

// HvCallDisableHypervisorEx | 0x010F

typedef struct HV_CALL_ATTRIBUTES _HV_X64_INPUT_DISABLE_HYPERVISOR_EX
{
    HV_UINT64 Rip;
    union
    {
        HV_UINT64 AsUINT64;
        struct
        {
            HV_UINT64 LongMode : 1;
        };
    } Flags;
    HV_UINT64 Arg;
} HV_X64_INPUT_DISABLE_HYPERVISOR_EX, *PHV_X64_INPUT_DISABLE_HYPERVISOR_EX;

// HvCallInstallInterceptEx | 0x0110

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_INSTALL_INTERCEPT_EX
{
    HV_PARTITION_ID PartitionId;
    HV_INPUT_VTL InterceptingInputVtl;
    HV_INTERCEPT_TYPE InterceptType;
    HV_UINT64 Reserved[4];
    HV_INTERCEPT_PARAMETERS_EX InterceptParameters[];
} HV_INPUT_INSTALL_INTERCEPT_EX, *PHV_INPUT_INSTALL_INTERCEPT_EX;

// HvCallMapVpStatePageEx | 0x0111

// HvCallPinGpaPageRanges | 0x0112

// HvCallUnpinGpaPageRanges | 0x0113

// HvCallWakeVps | 0x0114

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_WAKE_VPS
{
    HV_PARTITION_ID PartitionId;
    HV_GENERIC_SET VpsToWake;
} HV_INPUT_WAKE_VPS, *PHV_INPUT_WAKE_VPS;

// HvCallSetCpuGroupAffinity | 0x0115

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_SET_CPU_GROUP_AFFINITY
{
    HV_CPU_GROUP_ID CpuGroupId;
    union
    {
        HV_GENERIC_SET Bitset;
        HV_UINT64 BitsetBuffer[7];
    } CpuGroupAffinity;
} HV_INPUT_SET_CPU_GROUP_AFFINITY, *PHV_INPUT_SET_CPU_GROUP_AFFINITY;

// HvCallMapPartitionEventLogBuffer | 0x0116

typedef struct HV_CALL_ATTRIBUTES _HV_INPUT_MAP_PARTITION_EVENTLOG_BUFFER
{
    HV_PARTITION_ID PartitionId;
    HV_EVENTLOG_TYPE EventLogType;
    HV_UINT32 BufferIndex;
    HV_GPA_PAGE_RANGE GpaRange;
} HV_INPUT_MAP_PARTITION_EVENTLOG_BUFFER, *PHV_INPUT_MAP_PARTITION_EVENTLOG_BUFFER;

// *****************************************************************************
// Hypervisor Extended Hypercall Definitions
//

typedef enum _HV_EXT_CALL
{
    HvExtCallReserved = 0x8000,
    HvExtCallQueryCapabilities = 0x8001,
    HvExtCallGetBootZeroedMemory = 0x8002,
    HvExtCallMemoryHeatHint = 0x8003,
    HvExtCallEpfSetup = 0x8004,
    HvExtCallSchedulerAssistSetup = 0x8005,
    HvExtCallMemoryHeatHintAsync = 0x8006,
    HvExtCallMax = 0x8007,
} HV_EXT_CALL, *PHV_EXT_CALL;

// HvExtCallReserved | 0x8000

// HvExtCallQueryCapabilities | 0x8001

typedef union HV_CALL_ATTRIBUTES _HV_EXT_OUTPUT_QUERY_CAPABILITIES
{
    HV_UINT64 AsUINT64;
    struct
    {
        HV_UINT64 GetBootZeroedMemory : 1;
        HV_UINT64 MemoryHotHint : 1;
        HV_UINT64 MemoryColdHint : 1;
        HV_UINT64 Epf : 1;
        HV_UINT64 RootScheduler : 1;
        HV_UINT64 PowerSchedulerQos : 1;
        HV_UINT64 AsyncMemoryHint : 1;
        HV_UINT64 MemoryColdHintLargeOnly : 1;
        HV_UINT64 MemoryColdDiscardHint : 1;
        HV_UINT64 Reserved : 55;
    };
} HV_EXT_OUTPUT_QUERY_CAPABILITIES, *PHV_EXT_OUTPUT_QUERY_CAPABILITIES;

// HvExtCallGetBootZeroedMemory | 0x8002

typedef struct _HV_EXT_OUTPUT_BOOT_ZEROED_MEMORY_RANGE
{
    HV_GPA StartGpa;
    HV_UINT64 PageCount;
} HV_EXT_OUTPUT_BOOT_ZEROED_MEMORY_RANGE, *PHV_EXT_OUTPUT_BOOT_ZEROED_MEMORY_RANGE;

typedef struct HV_CALL_ATTRIBUTES _HV_EXT_OUTPUT_BOOT_ZEROED_MEMORY
{
    HV_UINT64 RangeCount;
    HV_EXT_OUTPUT_BOOT_ZEROED_MEMORY_RANGE ZeroedRanges[255];
} HV_EXT_OUTPUT_BOOT_ZEROED_MEMORY, *PHV_EXT_OUTPUT_BOOT_ZEROED_MEMORY;

// HvExtCallMemoryHeatHint | 0x8003

typedef struct HV_CALL_ATTRIBUTES _HV_EXT_INPUT_MEMORY_HEAT_HINT
{
    HV_UINT64 Heat : 2;
    HV_UINT64 Reserved : 62;
    HV_GPA_PAGE_RANGE Ranges[];
} HV_EXT_INPUT_MEMORY_HEAT_HINT, *PHV_EXT_INPUT_MEMORY_HEAT_HINT;

// HvExtCallEpfSetup | 0x8004

typedef enum _HV_EXT_EPF_MODE
{
    HvExtEpfModeMin = 0x0,
    HvExtEpfModeNt = 0x0,
    HvExtEpfModeMax = 0x1,
} HV_EXT_EPF_MODE, *PHV_EXT_EPF_MODE;

typedef struct _HV_EXT_EPF_COMPLETION_QUEUE
{
    HV_UINT64 ReadCursor;
    HV_UINT64 WriteCursor;
    HV_UINT64 Queue[HV_ANYSIZE_ARRAY];
} HV_EXT_EPF_COMPLETION_QUEUE, *PHV_EXT_EPF_COMPLETION_QUEUE;

typedef struct HV_CALL_ATTRIBUTES _HV_EXT_INPUT_EPF_SETUP
{
    HV_UINT32 Version;
    HV_EXT_EPF_MODE Mode;
    HV_GPA CompletionQueueGpaPage;
    HV_UINT64 CompletionQueuePageCount;
} HV_EXT_INPUT_EPF_SETUP, *PHV_EXT_INPUT_EPF_SETUP;

typedef struct HV_CALL_ATTRIBUTES _HV_EXT_OUTPUT_EPF_SETUP
{
    HV_UINT64 CompletionQueuePageCount;
} HV_EXT_OUTPUT_EPF_SETUP, *PHV_EXT_OUTPUT_EPF_SETUP;

// HvExtCallSchedulerAssistSetup | 0x8005

typedef enum _HV_EXT_SCHEDULER_ASSIST_MODE
{
    HvExtSchedulerAssistModeNone = 0x0,
    HvExtSchedulerAssistModeNt = 0x1,
    HvExtSchedulerAssistModeMax = 0x2,
} HV_EXT_SCHEDULER_ASSIST_MODE, *PHV_EXT_SCHEDULER_ASSIST_MODE;

typedef enum _HV_EXT_SCHEDULER_ASSIST_ACTION
{
    HvExtSchedulerAssistSetDataPage = 0x0,
    HvExtSchedulerAssistUpdateBamQos = 0x1,
    HvExtSchedulerAssistUpdatePriority = 0x2,
    HvExtSchedulerAssistRemoveSystemWorkBoost = 0x3,
    HvExtSchedulerAssistEventSignalled = 0x4,
    HvExtSchedulerAssistActionMax = 0x5,
} HV_EXT_SCHEDULER_ASSIST_ACTION, *PHV_EXT_SCHEDULER_ASSIST_ACTION;

typedef struct _HV_EXT_SCHEDULER_ASSIST_DATA
{
    union
    {
        HV_UINT32 PriorityState;
        struct
        {
            HV_UINT32 RootPriority : 8;
            HV_UINT32 GuestPriority : 8;
            HV_UINT32 Spare : 1;
            HV_UINT32 LowPriorityOverride : 1;
            HV_UINT32 RootRequiresPriorityKick : 1;
            HV_UINT32 HrTimerActive : 1;
            HV_UINT32 RootProcessingAssistData : 1;
            HV_UINT32 InterruptsDisabled : 1;
            HV_UINT32 Reserved : 10;
        };
    };
    HV_UINT32 BamQosLevel;
    HV_VP_INDEX TargetVpIndex;
    HV_EXT_SCHEDULER_ASSIST_ACTION SchedulerAssistAction;
    HV_UINT8 DoNotPreempt;
    HV_UINT32 SystemIrqlMask;
    HV_UINT32 Spare2;
    HV_UINT32 DpcInsertedCount;
    HV_UINT32 IpiInsertedCount;
    HV_UINT64 EventsSignalledCount;
    HV_UINT64 EventsAcknowledgedCount;
    HV_DECLSPEC_ALIGN(128) HV_UINT8 RootIsRunning;
    HV_UINT8 RootInHvCallDispatchVp;
} HV_EXT_SCHEDULER_ASSIST_DATA, *PHV_EXT_SCHEDULER_ASSIST_DATA;

typedef struct HV_CALL_ATTRIBUTES _HV_EXT_INPUT_SETUP_SCHEDULER_ASSIST
{
    HV_UINT32 Version;
    HV_EXT_SCHEDULER_ASSIST_MODE Mode;
    HV_GPA SchedulerAssistDataGpa;
} HV_EXT_INPUT_SETUP_SCHEDULER_ASSIST, *PHV_EXT_INPUT_SETUP_SCHEDULER_ASSIST;

// HvExtCallMemoryHeatHintAsync | 0x8006

// Should be same as HvExtCallMemoryHeatHint

#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#else
#pragma warning(default:4200) // zero length array
#pragma warning(default:4201) // nameless struct/union
#pragma warning(default:4324) // structure was padded due to __declspec(align())
// actual alignment is greater than the value specified in __declspec(align())
#pragma warning(default:4359)
#endif
#endif

#endif // !MILE_HYPERV_TLFS
