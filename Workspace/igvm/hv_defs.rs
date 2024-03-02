// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

//! A subset of the Microsoft hypervisor definitions used by the igvm crate.
//!
//! These types are defined in the Microsoft Hypervisor Top Level Funtional
//! Specification (TLFS), which can be found
//! [here](https://learn.microsoft.com/en-us/virtualization/hyper-v-on-windows/tlfs/tlfs).

use core::fmt::Debug;
use open_enum::open_enum;
use zerocopy::AsBytes;
use zerocopy::FromBytes;
use zerocopy::FromZeroes;

/// A Virtual Trust Level (VTL) defined by Virtual Secure Mode (VSM).
#[repr(u8)]
#[derive(Debug, Copy, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub enum Vtl {
    /// VTL0.
    Vtl0 = 0,
    /// VTL1.
    Vtl1 = 1,
    /// VTL2.
    Vtl2 = 2,
}

impl TryFrom<u8> for Vtl {
    type Error = HvError;

    fn try_from(value: u8) -> Result<Self, Self::Error> {
        Ok(match value {
            0 => Self::Vtl0,
            1 => Self::Vtl1,
            2 => Self::Vtl2,
            _ => return Err(HvError::InvalidParameter),
        })
    }
}

impl From<Vtl> for u8 {
    fn from(value: Vtl) -> Self {
        value as u8
    }
}

/// An aligned u128 value.
#[repr(C, align(16))]
#[derive(Copy, Clone, PartialEq, Eq, AsBytes, FromBytes, FromZeroes)]
pub struct AlignedU128([u8; 16]);

impl AlignedU128 {
    pub fn to_ne_bytes(&self) -> [u8; 16] {
        self.0
    }

    pub fn from_ne_bytes(val: [u8; 16]) -> Self {
        Self(val)
    }
}

impl Debug for AlignedU128 {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        Debug::fmt(&u128::from_ne_bytes(self.0), f)
    }
}

impl From<u128> for AlignedU128 {
    fn from(v: u128) -> Self {
        Self(v.to_ne_bytes())
    }
}

impl From<u64> for AlignedU128 {
    fn from(v: u64) -> Self {
        (v as u128).into()
    }
}

impl From<u32> for AlignedU128 {
    fn from(v: u32) -> Self {
        (v as u128).into()
    }
}

impl From<u16> for AlignedU128 {
    fn from(v: u16) -> Self {
        (v as u128).into()
    }
}

impl From<u8> for AlignedU128 {
    fn from(v: u8) -> Self {
        (v as u128).into()
    }
}

impl From<AlignedU128> for u128 {
    fn from(v: AlignedU128) -> Self {
        u128::from_ne_bytes(v.0)
    }
}

/// A `HV_REGISTER_VALUE` that represents virtual processor registers.
#[repr(C)]
#[derive(Clone, Copy, Debug, Eq, PartialEq, AsBytes, FromBytes, FromZeroes)]
pub struct HvRegisterValue(pub AlignedU128);

impl HvRegisterValue {
    pub fn as_u128(&self) -> u128 {
        self.0.into()
    }

    pub fn as_u64(&self) -> u64 {
        self.as_u128() as u64
    }

    pub fn as_u32(&self) -> u32 {
        self.as_u128() as u32
    }

    pub fn as_u16(&self) -> u16 {
        self.as_u128() as u16
    }

    pub fn as_u8(&self) -> u8 {
        self.as_u128() as u8
    }

    pub fn as_table(&self) -> HvX64TableRegister {
        HvX64TableRegister::read_from_prefix(self.as_bytes()).unwrap()
    }

    pub fn as_segment(&self) -> HvX64SegmentRegister {
        HvX64SegmentRegister::read_from_prefix(self.as_bytes()).unwrap()
    }
}

impl From<u8> for HvRegisterValue {
    fn from(val: u8) -> Self {
        (val as u128).into()
    }
}

impl From<u16> for HvRegisterValue {
    fn from(val: u16) -> Self {
        (val as u128).into()
    }
}

impl From<u32> for HvRegisterValue {
    fn from(val: u32) -> Self {
        (val as u128).into()
    }
}

impl From<u64> for HvRegisterValue {
    fn from(val: u64) -> Self {
        (val as u128).into()
    }
}

impl From<u128> for HvRegisterValue {
    fn from(val: u128) -> Self {
        Self(val.into())
    }
}

#[repr(C)]
#[derive(Clone, Copy, Debug, Eq, PartialEq, AsBytes, FromBytes, FromZeroes)]
pub struct HvX64TableRegister {
    pub pad: [u16; 3],
    pub limit: u16,
    pub base: u64,
}

impl From<HvX64TableRegister> for HvRegisterValue {
    fn from(val: HvX64TableRegister) -> Self {
        Self::read_from_prefix(val.as_bytes()).unwrap()
    }
}

impl From<HvRegisterValue> for HvX64TableRegister {
    fn from(val: HvRegisterValue) -> Self {
        Self::read_from_prefix(val.as_bytes()).unwrap()
    }
}

#[repr(C)]
#[derive(Clone, Copy, Debug, Eq, PartialEq, AsBytes, FromBytes, FromZeroes)]
pub struct HvX64SegmentRegister {
    pub base: u64,
    pub limit: u32,
    pub selector: u16,
    pub attributes: u16,
}

impl From<HvX64SegmentRegister> for HvRegisterValue {
    fn from(val: HvX64SegmentRegister) -> Self {
        Self::read_from_prefix(val.as_bytes()).unwrap()
    }
}

impl From<HvRegisterValue> for HvX64SegmentRegister {
    fn from(val: HvRegisterValue) -> Self {
        Self::read_from_prefix(val.as_bytes()).unwrap()
    }
}
