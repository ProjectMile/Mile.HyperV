// Copyright © 2020, Microsoft Corporation
//
// SPDX-License-Identifier: Apache-2.0 OR BSD-3-Clause
//
#![allow(dead_code)]
use zerocopy::{AsBytes, FromBytes, FromZeroes};

pub const MSR_HYPERCALL_ACTIVE: u64 = 1;
pub const MSR_HYPERCALL_LOCKED: u64 = 2;
pub const MSR_HYPERCALL_ADDR_MASK: u64 = !0xfff;

pub const MSR_SIEFP_SIMP_ACTIVE: u64 = 1;
pub const MSR_SIEFP_SIMP_ADDR_MASK: u64 = !0xfff;

#[repr(C)]
#[derive(Copy, Clone, AsBytes, Debug, FromBytes, FromZeroes)]
pub struct HvMessageHeader {
    pub typ: u32,
    pub len: u8,
    pub flags: u8,
    pub rsvd: u16,
    pub id: u64,
}

pub const MESSAGE_TYPE_TIMER_EXPIRED: u32 = 0x80000010;

#[repr(C)]
#[derive(Copy, Clone, AsBytes, Debug, FromBytes, FromZeroes)]
pub struct HvMessage {
    pub header: HvMessageHeader,
    pub payload: [[u8; 24]; 10],
}

#[repr(C)]
#[derive(Copy, Clone, AsBytes, Debug, FromBytes, FromZeroes)]
pub struct TimerMessagePayload {
    pub timer_index: u32,
    pub reserved: u32,
    pub expiration_time: u64,
    pub delivery_time: u64,
}
