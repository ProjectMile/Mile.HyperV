/*
 * PROJECT:    Mouri Internal Library Essentials
 * FILE:       Mile.HyperV.Portable.Types.h
 * PURPOSE:    Definition for Hyper-V Portable Types
 *
 * LICENSE:    The MIT License
 *
 * MAINTAINER: MouriNaruto (Kenji.Mouri@outlook.com)
 */

#ifndef MILE_HYPERV_PORTABLE_TYPES
#define MILE_HYPERV_PORTABLE_TYPES

#if !defined(_M_AMD64) && !defined(_M_ARM64) && !defined(_M_IX86)
#error [Mile.HyperV] The architecture is not supported.
#endif

#ifdef MILE_MOBILITY_PORTABLE_TYPES

// TODO: Add some wrappers to Mile.Mobility.Portable.Types.

#else

#include <stdint.h>

#endif

#endif // !MILE_HYPERV_PORTABLE_TYPES
