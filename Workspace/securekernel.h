/* 3235 */
struct $3579B838F07173DE0A3D28783D55F830
{
  unsigned __int64 StartupSuspend : 1;
  unsigned __int64 HaltSuspend : 1;
  unsigned __int64 IdleSuspend : 1;
  unsigned __int64 RsvdZ : 61;
};

/* 3236 */
union _HV_INTERNAL_ACTIVITY_REGISTER
{
  unsigned __int64 AsUINT64;
  $3579B838F07173DE0A3D28783D55F830 __s1;
};

/* 3954 */
struct _HV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD
{
  unsigned __int16 Status;
};

/* 3964 */
struct $F8886E15C9EAD2E2A494244AC8F8F6E1
{
  unsigned __int64 EnableEncryptedState : 1;
  unsigned __int64 ReservedZ : 11;
  unsigned __int64 VmsaGpaPageNumber : 52;
};

/* 3965 */
union _HV_X64_REGISTER_SEV_CONTROL
{
  unsigned __int64 AsUINT64;
  $F8886E15C9EAD2E2A494244AC8F8F6E1 __s1;
};

/* 4027 */
struct $276B8E80182D9774719E08BDEC33E47A
{
  unsigned __int64 MaximumVtl : 4;
  unsigned __int64 Vtl0InterruptInjectionPolicy : 2;
  unsigned __int64 Vtl1InterruptInjectionPolicy : 2;
  unsigned __int64 ReservedZ : 56;
};

/* 4028 */
union _HV_PARTITION_VSM_CONFIG
{
  unsigned __int64 AsUINT64;
  $276B8E80182D9774719E08BDEC33E47A __s1;
};

/* 4139 */
struct _HV_ARM64_INPUT_LAUNCH_HYPERVISOR
{
  unsigned __int64 HvEntryPoint;
};

/* 4372 */
struct _HV_ARM64_INVALID_VP_REGISTER_MESSAGE
{
  unsigned int VpIndex;
  unsigned int Reserved;
};

/* 4453 */
struct _HV_RDT_CAT_COS_BITMASK_PROPERTY
{
  unsigned int CosIndex;
  unsigned int CosBitmask;
};

/* 4634 */
struct _HV_PARK_BLOCK_INFO
{
  unsigned int ParkBlockOffset;
  unsigned int ParkBlockSize;
};

/* 4677 */
struct _HV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA
{
  unsigned __int16 Status;
};

/* 4815 */
struct _HV_X64_IO_PORT_READ_COMPLETION_DATA
{
  unsigned int Value;
};

/* 4845 */
union _HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS
{
  unsigned int HvRegisterName;
};

/* 4893 */
union _HV_PICO100_DURATION
{
  unsigned __int64 AsUINT64;
};

/* 4903 */
struct _HV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE
{
  unsigned int VpIndex;
  unsigned __int32 RangeCount : 5;
  unsigned __int32 Adjust : 1;
  unsigned __int32 HostVisibility : 2;
  unsigned __int32 MemoryType : 6;
  unsigned __int32 Reserved : 18;
  _HV_GPA_PAGE_RANGE Ranges[29];
};

/* 5068 */
struct $BF3AA1AE0EC707D4A55C9DC2FC10E196
{
  unsigned __int64 Wait : 1;
  unsigned __int64 ReservedZ : 63;
};

/* 5069 */
union _HV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK
{
  unsigned __int64 AsUINT64;
  $BF3AA1AE0EC707D4A55C9DC2FC10E196 __s1;
};

/* 5114 */
struct $6D47504A244CE7AA4BEA7F6A88966273
{
  unsigned __int64 BootLoader : 8;
  unsigned __int64 Tee : 8;
  unsigned __int64 ReservedZ : 32;
  unsigned __int64 Snp : 8;
  unsigned __int64 Microcode : 8;
};

/* 5115 */
union $E9CDDE5D4B63446AB76C8E022757469D
{
  $6D47504A244CE7AA4BEA7F6A88966273 __s0;
  unsigned __int64 AsUINT64;
};

/* 5116 */
struct _HV_SNP_PSP_TCB_VERSION
{
  $E9CDDE5D4B63446AB76C8E022757469D ___u0;
};

/* 5127 */
struct __declspec(align(8)) _HV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP
{
  unsigned __int64 CpuGroupId;
  unsigned __int16 LpIndexSetSize;
  unsigned __int16 LpIndexSetOffset;
};

/* 5322 */
struct $373F0C482CA2C07D4A7B2B94C5EA8081
{
  unsigned __int64 Type : 8;
  unsigned __int64 Reserved : 56;
};

/* 5323 */
union _HV_VP_ASSIST_PAGE_ACTION
{
  unsigned __int64 AsUINT64;
  $373F0C482CA2C07D4A7B2B94C5EA8081 __s1;
};

/* 5329 */
struct _HV_MINROOT_NUMA_LPS
{
  unsigned int NodeIndex;
  unsigned __int64 Mask[32];
};

/* 5365 */
struct $F8B259AFC8FB251F2389433B1C64F122
{
  unsigned int AdditionalReason;
  unsigned __int8 Reason;
  unsigned __int8 ReservedZ[3];
};

/* 5366 */
union _HV_X64_MSR_VP_EXIT_REASON_CONTENTS
{
  unsigned __int64 AsUINT64;
  $F8B259AFC8FB251F2389433B1C64F122 __s1;
};

/* 5408 */
struct _HV_PARTITION_PROPERTY_ASSOC
{
  HV_PARTITION_PROPERTY_CODE PropertyCode;
  unsigned __int64 PropertyValue;
};

/* 5667 */
struct _HV_ROOT_PASID_CAPABILITIES_PROPERTY
{
  unsigned int SvmIommuCount;
  unsigned int MinIommuPasidCount;
};

/* 5687 */
struct $D3EE6AC1BE1D77BCDA0A720ABA5D3C01
{
  unsigned __int64 RsvdZ : 48;
  unsigned __int64 Sint : 16;
};

/* 5688 */
union _HV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER
{
  unsigned __int64 AsUINT64;
  $D3EE6AC1BE1D77BCDA0A720ABA5D3C01 __s1;
};

/* 5711 */
struct $C2E162DC0AA0A7F9EAE1A4F8297C58A7
{
  unsigned int Spa;
  unsigned int PageCount;
};

/* 5712 */
struct __declspec(align(8)) $E7874B1F7DE5BCA4C4938E3527AD899B
{
  unsigned __int64 MmConfigAddress;
  _HV_PCI_ID PciId;
  unsigned __int64 BridgeMmConfigAddress;
  _HV_PCI_ID BridgePciId;
  $C2E162DC0AA0A7F9EAE1A4F8297C58A7 Bar[6];
};

/* 5713 */
struct $78B8A0117A120704892E62D78A12A3DC
{
  unsigned __int64 FeatureRegister;
  unsigned __int64 InterruptEnableRegister;
  unsigned __int64 InterruptStatusRegister;
  unsigned __int8 SevMailboxInterruptId;
  unsigned __int8 RsvdZ[7];
  unsigned __int64 SevCmdRespRegister;
  unsigned __int64 SevCmdBufAddrLoRegister;
  unsigned __int64 SevCmdBufAddrHiRegister;
  unsigned __int64 AcpiCmdRespRegister;
};

/* 5714 */
struct __declspec(align(8)) $F704F3B5E4794506E9FCDFFAE80A53A1
{
  unsigned __int64 RegisterBase;
  unsigned int RegisterPages;
  unsigned int FeatureRegister;
  unsigned int InterruptEnableRegister;
  unsigned int InterruptStatusRegister;
  unsigned __int8 SevMailboxInterruptId;
  unsigned __int8 RsvdZ[3];
  unsigned int SevCmdRespRegister;
  unsigned int SevCmdBufAddrLoRegister;
  unsigned int SevCmdBufAddrHiRegister;
  unsigned int AcpiCmdRespRegister;
};

/* 5715 */
union $0A5CDCBC30E4A7C442E9E45F53688CFE
{
  $E7874B1F7DE5BCA4C4938E3527AD899B Pci;
  $78B8A0117A120704892E62D78A12A3DC AcpiV1;
  $F704F3B5E4794506E9FCDFFAE80A53A1 AcpiV2;
};

/* 5716 */
struct __declspec(align(8)) _HV_PSP_DEVICE
{
  $0A5CDCBC30E4A7C442E9E45F53688CFE ___u0;
  unsigned __int32 IsInitialized : 1;
  unsigned __int32 IsPci : 1;
  unsigned __int32 Reserved0 : 2;
  unsigned __int32 AcpiRevision : 4;
  unsigned __int32 Reserved1 : 24;
};

/* 5717 */
struct _HV_SNP_PSP_DEVICES
{
  unsigned __int8 Count;
  _HV_PSP_DEVICE PspDevice[2];
};

/* 5718 */
struct HV_EVENTLOG_EVENTGROUP_CONFIGURATION
{
  unsigned int GroupId;
  unsigned __int16 RsvdZ;
  unsigned __int16 EventCount;
  unsigned __int8 EventId[256];
};

/* 5719 */
struct _HV_INPUT_EVENTLOG_SET_EVENTS
{
  HV_EVENTLOG_TYPE EventLogType;
  unsigned int GroupCount;
  unsigned __int64 ConfigurationFlags;
  HV_EVENTLOG_EVENTGROUP_CONFIGURATION Groups[2];
};

/* 5752 */
struct $BA274E7207FB7A8585A2F2CDC3D4C94F
{
  unsigned __int64 Enabled : 1;
  unsigned __int64 HardwareEnforced : 1;
  unsigned __int64 HardwareRangeBits : 6;
  unsigned __int64 ReservedZ : 4;
  unsigned __int64 GpaPageNumber : 52;
};

/* 5753 */
union _HV_REGISTER_HVPT_CONTROL
{
  unsigned __int64 AsUINT64;
  $BA274E7207FB7A8585A2F2CDC3D4C94F __s1;
};

/* 5815 */
struct $F8426F19995B1CF11F7128330FD97FAA
{
  unsigned __int64 PerfmonMode : 8;
  unsigned __int64 DisableCounting : 1;
  unsigned __int64 Reserved : 55;
};

/* 5816 */
union _HV_PARTITION_PERFMON_MODE_CONFIG
{
  unsigned __int64 AsUINT64;
  $F8426F19995B1CF11F7128330FD97FAA __s1;
};

/* 5959 */
struct $E40A898125F12467A4105D9FBACA6083
{
  unsigned __int64 Enable : 1;
  unsigned __int64 ReservedP : 11;
  unsigned __int64 GpaPageNumber : 52;
};

/* 5960 */
union _HV_REGISTER_REFERENCE_TSC
{
  unsigned __int64 AsUINT64;
  $E40A898125F12467A4105D9FBACA6083 __s1;
};

/* 6000 */
struct __declspec(align(4)) _HV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE
{
  unsigned int VpIndex;
  unsigned __int8 TargetVtl;
  unsigned __int8 EnableMbec : 1;
  unsigned __int8 EnableSupervisorShadowStack : 1;
  unsigned __int8 EnableHardwareHvpt : 1;
};

/* 6023 */
struct $08A6FE1115A421B05D459AE04F10E245
{
  unsigned __int64 Enabled : 1;
  unsigned __int64 Reserved : 11;
  unsigned __int64 GpaPage : 52;
};

/* 6024 */
union _HV_REGISTER_PARTITION_INFO_PAGE
{
  unsigned __int64 AsUINT64;
  $08A6FE1115A421B05D459AE04F10E245 __s1;
};

/* 6071 */
struct $C0B19948A3FAB3E4B2E5FD2C4889CE54
{
  unsigned __int8 ErrorCodeValid : 1;
  unsigned __int8 Reserved : 7;
};

/* 6072 */
union _HV_ARM64_EXCEPTION_INFO
{
  unsigned __int8 AsUINT8;
  $C0B19948A3FAB3E4B2E5FD2C4889CE54 __s1;
};

/* 6119 */
struct _HV_SEAM_TDMR_RESERVATION
{
  unsigned __int64 BaseAddress;
  unsigned __int64 Size;
};

/* 6120 */
struct _HV_SEAM_TDMR
{
  unsigned __int64 BaseAddress;
  unsigned __int64 Size;
  unsigned __int64 Pamt1GBaseAddress;
  unsigned __int64 Pamt1GSize;
  unsigned __int64 Pamt2MBaseAddress;
  unsigned __int64 Pamt2MSize;
  unsigned __int64 Pamt4KBaseAddress;
  unsigned __int64 Pamt4KSize;
  unsigned __int64 NumReservedRegions;
  _HV_SEAM_TDMR_RESERVATION ReservedRegions[];
};

/* 6152 */
struct $56B6C0C84234DF7B00E9CC99FD442D31
{
  unsigned __int64 ReservedZ0 : 1;
  unsigned __int64 MbecVtlMask : 16;
  unsigned __int64 DenyLowerVtlStartup : 1;
  unsigned __int64 SupervisorShadowStack : 1;
  unsigned __int64 HardwareHvptAvailable : 1;
  unsigned __int64 SoftwareHvptAvailable : 1;
  unsigned __int64 HardwareHvptRangeBits : 6;
  unsigned __int64 InterceptPageAvailable : 1;
  unsigned __int64 ReturnActionAvailable : 1;
  unsigned __int64 Vtl0AliasMapAvailable : 1;
  unsigned __int64 InterceptNotPresentAvailable : 1;
  unsigned __int64 InstallInterceptEx : 1;
  unsigned __int64 ReservedZ : 32;
};

/* 6153 */
union _HV_ARM64_REGISTER_VSM_CAPABILITIES
{
  unsigned __int64 AsUINT64;
  $56B6C0C84234DF7B00E9CC99FD442D31 __s1;
};

/* 6185 */
union _HV_REGISTER_GUEST_VSM_PARTITION_CONFIG
{
  unsigned __int64 AsUINT64;
  $276B8E80182D9774719E08BDEC33E47A __s1;
};

/* 6229 */
struct $6D949113F7977E14EFEE177AB1B448B6
{
  unsigned __int64 Enabled : 1;
  unsigned __int64 ReservedZ : 11;
  unsigned __int64 PageNumber : 52;
};

/* 6230 */
union _HV_X64_REGISTER_SEV_HV_DOORBELL
{
  unsigned __int64 AsUINT64;
  $6D949113F7977E14EFEE177AB1B448B6 __s1;
};

/* 6315 */
struct $F42B68B65007A4989052D0B98DE4271B
{
  unsigned __int64 NmiNotification : 1;
  unsigned __int64 InterruptNotification : 1;
  unsigned __int64 InterruptPriority : 4;
  unsigned __int64 RsvdZ : 42;
  unsigned __int64 Sint : 16;
};

/* 6316 */
union _HV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER
{
  unsigned __int64 AsUINT64;
  $F42B68B65007A4989052D0B98DE4271B __s1;
};

/* 6385 */
union _HV_X64_REGISTER_SEV_GHCB
{
  unsigned __int64 AsUINT64;
  $6D949113F7977E14EFEE177AB1B448B6 __s1;
};

/* 6674 */
struct _HV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA
{
  unsigned __int16 Status;
};

/* 6768 */
struct _HV_ARM64_UNSUPPORTED_FEATURE_MESSAGE
{
  unsigned int VpIndex;
  _HV_ARM64_UNSUPPORTED_FEATURE_CODE FeatureCode;
  unsigned __int64 FeatureParameter;
};

/* 6974 */
struct $44FBF941A4EA52592961B4141A87957B
{
  unsigned __int64 Rsvd : 8;
  unsigned __int64 Id : 8;
  unsigned __int64 RsvdZ : 48;
};

/* 6975 */
struct $2AB60B0C3086C1015293421A03FFC508
{
  unsigned __int64 Rsvd : 8;
  unsigned __int64 Operation : 8;
  unsigned __int64 RsvdZ : 48;
};

/* 6976 */
struct $E7AF1F57B6D2D67BE775753423BA6D98
{
  unsigned __int64 Flags;
};

/* 6977 */
struct $40E060E1C5415F502384DBA9E6BC808E
{
  unsigned __int64 Extended : 1;
  unsigned __int64 Mode : 7;
  unsigned __int64 Rsvd : 56;
};

/* 6978 */
union _HV_EVENTLOG_EXTENDED_TRACE_FLAGS
{
  $44FBF941A4EA52592961B4141A87957B Scenario;
  $2AB60B0C3086C1015293421A03FFC508 Granular;
  $E7AF1F57B6D2D67BE775753423BA6D98 Legacy;
  $40E060E1C5415F502384DBA9E6BC808E Common;
  unsigned __int64 AsUINT64;
};

/* 7018 */
struct $08B5C80CB94E016A606701C3C8645F97
{
  unsigned int BufferCount;
  unsigned int BufferSizeInPages;
};

/* 7019 */
union _HV_PARTITION_DIAG_LOG_BUFFER_CONFIG
{
  unsigned __int64 AsUINT64;
  $08B5C80CB94E016A606701C3C8645F97 __s1;
};

/* 7053 */
struct $6598A1ABA04B72869A38412E1A9E0063
{
  unsigned __int64 FavorAutoEoi : 1;
  unsigned __int64 FavorAutoEoiLegacyOs : 1;
  unsigned __int64 Rsvd : 62;
};

/* 7054 */
union _HV_PARTITION_ENLIGHTENMENT_MODIFICATIONS
{
  $6598A1ABA04B72869A38412E1A9E0063 __s0;
  unsigned __int64 AsUINT64;
};

/* 7055 */
struct _HV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD
{
  unsigned int VpIndex;
  unsigned __int16 Status;
  _HV_PROXIMITY_DOMAIN_INFO ProximityDomainInfo;
};

/* 7119 */
struct $BAAEA4CB8E03D619390885D96A4655E5
{
  unsigned __int64 TlbiEnlightened : 1;
  unsigned __int64 Reserved : 63;
};

/* 7120 */
union _HV_ARM64_REGISTER_TLBI_CONTROL
{
  unsigned __int64 AsUINT64;
  $BAAEA4CB8E03D619390885D96A4655E5 __s1;
};

/* 7322 */
struct $D7E06751657A7CCCC9EC29CD86F6CE02
{
  unsigned __int64 Readable : 1;
  unsigned __int64 Writable : 1;
  unsigned __int64 Reserved : 62;
};

/* 7323 */
union _HV_SGX_LAUNCH_CONTROL_CONFIG
{
  unsigned __int64 AsUINT64;
  $D7E06751657A7CCCC9EC29CD86F6CE02 __s1;
};

/* 7470 */
struct $C603488A770D9546FFC72D976EE450FC
{
  unsigned __int64 AtsBusBitmap[4];
  unsigned __int64 SecureIntegratedAtsDeviceBitmap[1024];
};

/* 7471 */
struct _HV_LOADER_PCI_SEGMENT_ENTRY
{
  unsigned __int16 SegmentNumber;
  unsigned __int64 ReservedDeviceBitmap[1024];
  $C603488A770D9546FFC72D976EE450FC Intel;
};

/* 7570 */
struct $91085B31F55A1A0FA6CBFC3FCFE18279
{
  unsigned __int64 Type : 8;
  unsigned __int64 Reserved : 56;
  unsigned int TargetVp;
  unsigned __int8 TargetVtl;
  unsigned __int8 TargetSint;
  unsigned __int16 FlagNumber;
};

/* 7571 */
union _HV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT
{
  unsigned __int64 AsUINT64[2];
  $91085B31F55A1A0FA6CBFC3FCFE18279 __s1;
};

/* 7583 */
struct _HV_SYNIC_EVENT_INTERCEPT_MESSAGE
{
  unsigned int VpIndex;
  unsigned __int32 Vtl : 4;
  unsigned __int32 Reserved : 28;
  _HV_CONNECTION_ID ConnectionId;
  unsigned int FlagNumber;
};

/* 7839 */
struct $8D15A24391BB5361ACD6F6CE97ED5601
{
  unsigned __int64 Continue : 1;
};

/* 7840 */
union $E3C5FFEB8ADF63394F0456898124FAA9
{
  unsigned __int64 AsUINT64;
  $8D15A24391BB5361ACD6F6CE97ED5601 __s1;
};

/* 7841 */
struct _HV_INPUT_GET_PARTITION_RESERVED_PAGES
{
  unsigned __int64 PartitionId;
  $E3C5FFEB8ADF63394F0456898124FAA9 ___u1;
};

/* 7968 */
struct _HV_RDT_MBA_COS_VALUE_PROPERTY
{
  unsigned int CosIndex;
  unsigned int CosThrottleValue;
};

/* 7969 */
struct $0CADC23ACA8B1003CC2239D65B65DCCF
{
  unsigned __int64 HideHypervisorPresent : 1;
  unsigned __int64 RsvdZ : 63;
};

/* 7970 */
union _HV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES
{
  $0CADC23ACA8B1003CC2239D65B65DCCF __s0;
  unsigned __int64 AsUINT64;
};

/* 8050 */
struct _HV_INPUT_GPA_PAGE_PINNING
{
  unsigned __int64 Reserved;
  _HV_GPA_PAGE_RANGE GpaRangeList[];
};

/* 8070 */
union $A6574B3A989B380DF81931D8EA1314D6
{
  unsigned __int64 AsUINT64;
  unsigned __int16 RangeCount;
};

/* 8071 */
struct _HV_OUTPUT_GET_PARTITION_RESERVED_PAGES
{
  $A6574B3A989B380DF81931D8EA1314D6 ___u0;
  _HV_SPA_PAGE_RANGE RangeList[511];
};

/* 8076 */
struct $7E46DA35292D5E4664080844240F46C2
{
  unsigned __int64 Runnable : 1;
  unsigned __int64 ReservedZ : 63;
};

/* 8077 */
union _HV_PARTITION_ISOLATION_CONTROL
{
  unsigned __int64 AsUINT64;
  $7E46DA35292D5E4664080844240F46C2 __s1;
};

/* 8098 */
struct $494316A446F4E0456554698FB4B46BBA
{
  unsigned __int8 Vector;
  unsigned __int8 SampleRate;
  unsigned __int8 ReservedZ[6];
};

/* 8099 */
union _HV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS
{
  unsigned __int64 AsUINT64;
  $494316A446F4E0456554698FB4B46BBA __s1;
};

/* 8240 */
struct __declspec(align(8)) _HV_LOADER_IOMMU_ENTRY
{
  unsigned __int16 SegmentNumber;
  unsigned __int64 RegisterBaseAddress;
  unsigned int Idr0;
  unsigned int Idr1;
  unsigned int Idr2;
  unsigned int Idr3;
  unsigned int Idr4;
  unsigned int Idr5;
  unsigned int Aidr;
  unsigned __int64 StreamTableBase;
  unsigned int StreamTableSizeInPages;
  unsigned int StrTabBaseCfg;
  unsigned int Mpamidr;
};

/* 8274 */
struct $810EB8311A7C233DA06962FAB372D9F7
{
  unsigned int DeviceTableSizeInPages;
  unsigned __int64 DeviceTableSpaBasePage;
};

/* 8275 */
struct $038C265C4081F56516B7A556D33E2D93
{
  unsigned int ContextTableCount;
  unsigned int InterruptRemappingTableSizeInPages;
  unsigned __int64 RootTableSpaPage;
  unsigned __int64 ContextTableSpaPages[256];
  unsigned __int64 InterruptRemappingTableSpaBasePage;
};

/* 8276 */
struct $FAA987BC27EB0F2F4ED8FB1358DD0172
{
  unsigned __int32 LiveDomainIdSelector : 1;
  unsigned __int32 Reserved : 31;
};

/* 8277 */
union $135078F8A6292F4C90A20C969410121C
{
  $FAA987BC27EB0F2F4ED8FB1358DD0172 __s0;
  unsigned int AsUINT32;
};

/* 8278 */
union $3666C1D97C40BE943525DACE31A2A4BD
{
  $810EB8311A7C233DA06962FAB372D9F7 Amd;
  $038C265C4081F56516B7A556D33E2D93 Intel;
};

/* 8279 */
struct __declspec(align(8)) _HV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES
{
  $3666C1D97C40BE943525DACE31A2A4BD ___u0;
  $135078F8A6292F4C90A20C969410121C Flags;
};

/* 8300 */
struct $ED7688FFF7E1ECC95DB748AE50679A2C
{
  unsigned __int32 ResultCode : 8;
  unsigned __int32 DeniedAccess : 8;
  unsigned __int32 InterceptingVtl : 4;
  unsigned __int32 Reserved0 : 12;
  unsigned int Reserved1;
};

/* 8301 */
union _HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT
{
  unsigned __int64 AsUINT64;
  $ED7688FFF7E1ECC95DB748AE50679A2C __s1;
};

/* 8316 */
struct $6FAA47317B304685DB13952977CF5BD0
{
  unsigned __int64 PartitionSecureVtlEnabled : 1;
  unsigned __int64 MbecUserExecuteControl : 1;
};

/* 8317 */
union _HV_INSTRUCTION_EMULATION_HINTS_REGISTER
{
  unsigned __int64 AsUINT64;
  $6FAA47317B304685DB13952977CF5BD0 __s1;
};

/* 8374 */
struct $1C089F3A5C26E55215FEE3452DE544EE
{
  unsigned __int64 Reset : 1;
  unsigned __int64 ReservedZ : 63;
};

/* 8375 */
union _HV_ARM64_MSR_RESET_CONTENTS
{
  unsigned __int64 AsUINT64;
  $1C089F3A5C26E55215FEE3452DE544EE __s1;
};

/* 8443 */
union _HV_PARTITION_ISOLATION_POLICY
{
  unsigned __int64 AsUINT64;
};

/* 8674 */
struct _HV_PSP_REQUEST_COMPLETION_DATA
{
  _HV_PSP_STATUS PspStatus;
};

/* 8691 */
struct __declspec(align(4)) _HV_SNP_PSP_ID
{
  unsigned __int8 Id[512];
  unsigned int Size;
  unsigned __int8 Count;
};

/* 8796 */
struct $0FC77B171E1BF3FACDF4D2C7BC575691
{
  unsigned __int64 DispatchVp : 1;
  unsigned __int64 AssertVirtualInterrupt : 1;
  unsigned __int64 SignalEventDirect : 1;
  unsigned __int64 ReadGpa : 1;
  unsigned __int64 WriteGpa : 1;
  unsigned __int64 UnregisterInterceptResult : 1;
  unsigned __int64 TranslateVirtualAddressEx : 1;
  unsigned __int64 GetVpRegisters : 1;
  unsigned __int64 SetVpRegisters : 1;
  unsigned __int64 AssertDeviceInterrupt : 1;
  unsigned __int64 RetargetDeviceInterrupt : 1;
  unsigned __int64 PostMessageDirect : 1;
  unsigned __int64 GetVpCpuidValues : 1;
  unsigned __int64 GetVpSetFromMda : 1;
  unsigned __int64 Reserved : 50;
};

/* 8797 */
union HV_USER_MODE_HYPERCALLS
{
  $0FC77B171E1BF3FACDF4D2C7BC575691 __s0;
  unsigned __int64 AsUINT64;
};

/* 8846 */
struct $5DB327F9F35BDD3D6A2CE937E2C24141
{
  unsigned __int64 Success : 1;
  unsigned __int64 Async : 1;
  unsigned __int64 Remote : 1;
  unsigned __int64 Reserved : 61;
};

/* 8847 */
union _HV_PARTITION_DEPOSIT_STATUS
{
  unsigned __int64 AsUINT64;
  $5DB327F9F35BDD3D6A2CE937E2C24141 __s1;
};

/* 8894 */
struct $CDE9BFE87BD54B12596E1109949B8227
{
  unsigned __int64 PageMaskShift : 6;
  unsigned __int64 Reserved : 6;
  unsigned __int64 PageNumber : 52;
};

/* 8895 */
union _HV_IOMMU_GVA_RANGE
{
  unsigned __int64 AsUINT64;
  $CDE9BFE87BD54B12596E1109949B8227 __s1;
};

/* 8984 */
union _HV_PARTITION_INFO_PAGE
{
  unsigned __int8 Padding[4096];
  unsigned int TlbInUse;
};

/* 9039 */
struct _HV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE
{
  unsigned int VpIndex;
  unsigned int Reserved;
};

/* 9125 */
struct _HV_ARM64_VOLATILE_GP_REGS
{
  unsigned __int64 X[18];
};

/* 9137 */
struct $2898B859C5850A7C55E8BE6C6C2E0ED6
{
  unsigned __int64 Enabled : 1;
  unsigned __int64 Granularity : 2;
  unsigned __int64 RangeEnabled : 1;
  unsigned __int64 ReservedZ : 60;
};

/* 9138 */
union _HV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG
{
  unsigned __int64 AsUINT64;
  $2898B859C5850A7C55E8BE6C6C2E0ED6 __s1;
};

/* 9199 */
struct __declspec(align(8)) _HV_MEMORY_PROXIMITY_INFO
{
  unsigned __int64 BaseAddress;
  unsigned __int64 EndAddress;
  unsigned int ProximityDomainId;
};

/* 9409 */
struct __declspec(align(8)) _HV_DMA_RANGE
{
  unsigned __int64 StartPage;
  unsigned int PageCount;
};

/* 9444 */
struct $9116744C2D119A7E16E700E69A843A53
{
  _HV_VP_DISPATCH_LOOP_EVENT ExitEvent;
  unsigned int Reserved;
};

/* 9445 */
union _HV_VP_DISPATCH_LOOP_RESULT
{
  unsigned __int64 AsUINT64;
  $9116744C2D119A7E16E700E69A843A53 __s1;
};

/* 9458 */
struct _HV_HYPERCALL_INTERCEPT_COMPLETION_DATA
{
  unsigned __int16 Status;
  unsigned __int8 OutputData[];
};

/* 9461 */
struct _HV_INPUT_NOTIFY_EVENT_RING_EMPTY
{
  unsigned int SintIndex;
  unsigned int RsvdZ;
};

/* 9529 */
struct $72F7B631C15D7F62E69397D550170776
{
  unsigned __int64 ReservedZ : 64;
};

/* 9530 */
union _HV_REGISTER_ISOLATION_CAPABILITIES
{
  unsigned __int64 AsUINT64;
  $72F7B631C15D7F62E69397D550170776 __s1;
};

/* 9580 */
struct $4AC33E5542FDBF2A1BAACA89D1E916BA
{
  unsigned __int64 Build : 32;
  unsigned __int64 MinorVersion : 8;
  unsigned __int64 MajorVersion : 8;
  unsigned __int64 Reserved : 16;
};

/* 9581 */
union _HV_SEC_FW_VERSION
{
  $4AC33E5542FDBF2A1BAACA89D1E916BA Snp;
  unsigned __int64 AsUINT64;
};

/* 9616 */
struct _HV_RESTART_COMPLETION_MESSAGE_PAYLOAD
{
  unsigned int VpIndex;
  _HV_RESTART_COMPLETION_TYPE CompletionType;
};

/* 9893 */
typedef _HV_REGISTER_PARTITION_INFO_PAGE HV_REGISTER_PARTITION_INFO_PAGE;

/* 9966 */
typedef _HV_PARTITION_DIAG_LOG_BUFFER_CONFIG HV_PARTITION_DIAG_LOG_BUFFER_CONFIG;

/* 10088 */
typedef _HV_INPUT_EVENTLOG_SET_EVENTS HV_INPUT_EVENTLOG_SET_EVENTS;

/* 10287 */
typedef _HV_SNP_PSP_ID *PHV_SNP_PSP_ID;

/* 10315 */
typedef _HV_ARM64_EXCEPTION_INFO *PHV_ARM64_EXCEPTION_INFO;

/* 10522 */
typedef _HV_RESTART_COMPLETION_MESSAGE_PAYLOAD *PHV_RESTART_COMPLETION_MESSAGE_PAYLOAD;

/* 10526 */
typedef _HV_IOMMU_GVA_RANGE *PHV_IOMMU_GVA_RANGE;

/* 10588 */
typedef _HV_MEMORY_PROXIMITY_INFO HV_MEMORY_PROXIMITY_INFO;

/* 10782 */
typedef _HV_ARM64_REGISTER_TLBI_CONTROL HV_ARM64_REGISTER_TLBI_CONTROL;

/* 10886 */
typedef _HV_PARTITION_INFO_PAGE HV_PARTITION_INFO_PAGE;

/* 10943 */
typedef _HV_ARM64_INPUT_LAUNCH_HYPERVISOR HV_ARM64_INPUT_LAUNCH_HYPERVISOR;

/* 11040 */
typedef _HV_INTERNAL_ACTIVITY_REGISTER *PHV_INTERNAL_ACTIVITY_REGISTER;

/* 11108 */
typedef unsigned __int64 HV_DEVICE_VA_PAGE_NUMBER;

/* 11235 */
typedef _HV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA HV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA;

/* 11254 */
typedef unsigned __int64 *PHV_MSI_ADDRESS;

/* 11323 */
typedef _HV_SNP_PSP_DEVICES HV_SNP_PSP_DEVICES;

/* 11517 */
typedef _HV_SEC_FW_VERSION HV_SEC_FW_VERSION;

/* 12026 */
typedef _HV_PARTITION_VSM_CONFIG *PHV_PARTITION_VSM_CONFIG;

/* 12044 */
typedef _HV_REGISTER_REFERENCE_TSC *PHV_REGISTER_REFERENCE_TSC;

/* 12169 */
typedef _HV_EVENTLOG_EXTENDED_TRACE_FLAGS *PHV_EVENTLOG_EXTENDED_TRACE_FLAGS;

/* 12242 */
typedef _HV_SGX_LAUNCH_CONTROL_CONFIG *PHV_SGX_LAUNCH_CONTROL_CONFIG;

/* 12252 */
typedef _HV_INPUT_GET_PARTITION_RESERVED_PAGES *PHV_INPUT_GET_PARTITION_RESERVED_PAGES;

/* 12515 */
typedef _HV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES *PHV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES;

/* 12552 */
typedef HV_EVENTLOG_EVENTGROUP_CONFIGURATION *PHV_EVENTLOG_EVENTGROUP_CONFIGURATION;

/* 12588 */
typedef _HV_INTERNAL_ACTIVITY_REGISTER HV_INTERNAL_ACTIVITY_REGISTER;

/* 12659 */
typedef _HV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER HV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER;

/* 12671 */
typedef _HV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG HV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG;

/* 12702 */
typedef _HV_PARK_BLOCK_INFO *PHV_PARK_BLOCK_INFO;

/* 12727 */
typedef _HV_SEAM_TDMR HV_SEAM_TDMR;

/* 12816 */
typedef unsigned int *PHV_MODIFY_SPA_PAGE_HOST_ACCESS_FLAGS;

/* 12858 */
typedef _HV_PARTITION_PROPERTY_ASSOC *PHV_PARTITION_PROPERTY_ASSOC;

/* 12868 */
typedef unsigned __int64 *PHV_DEVICE_VA_PAGE_NUMBER;

/* 12874 */
typedef _HV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT HV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT;

/* 12887 */
typedef _HV_SEAM_TDMR_RESERVATION *PHV_SEAM_TDMR_RESERVATION;

/* 12922 */
typedef _HV_X64_MSR_VP_EXIT_REASON_CONTENTS HV_X64_MSR_VP_EXIT_REASON_CONTENTS;

/* 13138 */
typedef _HV_X64_REGISTER_SEV_HV_DOORBELL HV_X64_REGISTER_SEV_HV_DOORBELL;

/* 13164 */
typedef _HV_ROOT_PASID_CAPABILITIES_PROPERTY HV_ROOT_PASID_CAPABILITIES_PROPERTY;

/* 13250 */
typedef _HV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG *PHV_PARTITION_PAGE_ACCESS_TRACKING_CONFIG;

/* 13341 */
typedef _HV_VP_ASSIST_PAGE_ACTION *PHV_VP_ASSIST_PAGE_ACTION;

/* 13357 */
typedef _HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT;

/* 13368 */
typedef _HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS *PHV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 13416 */
typedef _HV_X64_REGISTER_SEV_GHCB HV_X64_REGISTER_SEV_GHCB;

/* 13470 */
typedef _HV_SNP_PSP_ID HV_SNP_PSP_ID;

/* 13502 */
typedef _HV_PARTITION_PROPERTY_ASSOC HV_PARTITION_PROPERTY_ASSOC;

/* 13533 */
typedef _HV_SGX_LAUNCH_CONTROL_CONFIG HV_SGX_LAUNCH_CONTROL_CONFIG;

/* 13673 */
typedef _HV_SNP_PSP_TCB_VERSION *PHV_SNP_PSP_TCB_VERSION;

/* 13692 */
typedef _HV_REGISTER_PARTITION_INFO_PAGE *PHV_REGISTER_PARTITION_INFO_PAGE;

/* 13703 */
typedef _HV_RDT_MBA_COS_VALUE_PROPERTY HV_RDT_MBA_COS_VALUE_PROPERTY;

/* 13748 */
typedef _HV_X64_IO_PORT_READ_COMPLETION_DATA HV_X64_IO_PORT_READ_COMPLETION_DATA;

/* 13857 */
typedef _HV_ARM64_MSR_RESET_CONTENTS *PHV_ARM64_MSR_RESET_CONTENTS;

/* 14070 */
typedef _HV_PARTITION_ISOLATION_CONTROL HV_PARTITION_ISOLATION_CONTROL;

/* 14071 */
typedef _HV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE *PHV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE;

/* 14132 */
typedef _HV_INPUT_NOTIFY_EVENT_RING_EMPTY *PHV_INPUT_NOTIFY_EVENT_RING_EMPTY;

/* 14153 */
typedef unsigned int *PHV_UNMAP_GPA_FLAGS;

/* 14162 */
typedef _HV_ARM64_INPUT_LAUNCH_HYPERVISOR *PHV_ARM64_INPUT_LAUNCH_HYPERVISOR;

/* 14331 */
typedef _HV_MINROOT_NUMA_LPS HV_MINROOT_NUMA_LPS;

/* 14333 */
typedef unsigned int HV_LOCK_GPA_PAGE_MAPPING_FLAGS;

/* 14473 */
typedef _HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 14517 */
typedef _HV_INSTRUCTION_EMULATION_HINTS_REGISTER *PHV_INSTRUCTION_EMULATION_HINTS_REGISTER;

/* 14530 */
typedef unsigned int HV_MODIFY_SPA_PAGE_HOST_ACCESS_FLAGS;

/* 14776 */
typedef _HV_LOADER_PCI_SEGMENT_ENTRY *PHV_LOADER_PCI_SEGMENT_ENTRY;

/* 15041 */
typedef _HV_INPUT_GET_PARTITION_RESERVED_PAGES HV_INPUT_GET_PARTITION_RESERVED_PAGES;

/* 15124 */
typedef HV_USER_MODE_HYPERCALLS *PHV_USER_MODE_HYPERCALLS;

/* 15152 */
typedef _HV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA *PHV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA;

/* 15277 */
typedef _HV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP HV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP;

/* 15396 */
typedef _HV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER *PHV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER;

/* 15416 */
typedef _HV_REGISTER_ISOLATION_CAPABILITIES *PHV_REGISTER_ISOLATION_CAPABILITIES;

/* 15454 */
typedef _HV_INSTRUCTION_EMULATION_HINTS_REGISTER HV_INSTRUCTION_EMULATION_HINTS_REGISTER;

/* 15543 */
typedef _HV_PARTITION_ISOLATION_CONTROL *PHV_PARTITION_ISOLATION_CONTROL;

/* 16155 */
typedef const _HV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS *PCHV_ARM64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 16356 */
typedef _HV_HYPERCALL_INTERCEPT_COMPLETION_DATA HV_HYPERCALL_INTERCEPT_COMPLETION_DATA;

/* 16367 */
typedef _HV_PARTITION_PERFMON_MODE_CONFIG HV_PARTITION_PERFMON_MODE_CONFIG;

/* 16400 */
typedef unsigned int *PHAL_HV_VIRTUAL_PROCESSOR_INDEX;

/* 16418 */
typedef _HV_ARM64_VOLATILE_GP_REGS *PHV_ARM64_VOLATILE_GP_REGS;

/* 16480 */
typedef _HV_VP_DISPATCH_LOOP_RESULT HV_VP_DISPATCH_LOOP_RESULT;

/* 16515 */
typedef _HV_PARTITION_DEPOSIT_STATUS *PHV_PARTITION_DEPOSIT_STATUS;

/* 16620 */
typedef _HV_ARM64_INVALID_VP_REGISTER_MESSAGE *PHV_ARM64_INVALID_VP_REGISTER_MESSAGE;

/* 16628 */
typedef _HV_PSP_REQUEST_COMPLETION_DATA *PHV_PSP_REQUEST_COMPLETION_DATA;

/* 16629 */
typedef _HV_REGISTER_GUEST_VSM_PARTITION_CONFIG *PHV_REGISTER_GUEST_VSM_PARTITION_CONFIG;

/* 16635 */
typedef _HV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD HV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD;

/* 16754 */
typedef _HV_ARM64_MSR_RESET_CONTENTS HV_ARM64_MSR_RESET_CONTENTS;

/* 16784 */
typedef _HV_DMA_RANGE HV_DMA_RANGE;

/* 16842 */
typedef _HV_X64_REGISTER_SEV_CONTROL *PHV_X64_REGISTER_SEV_CONTROL;

/* 16890 */
typedef unsigned int *PHV_PRECOMMIT_GPA_FLAGS;

/* 16979 */
typedef _HV_SNP_PSP_DEVICES *PHV_SNP_PSP_DEVICES;

/* 17008 */
typedef _HV_ARM64_EXCEPTION_INFO HV_ARM64_EXCEPTION_INFO;

/* 17012 */
typedef _HV_ARM64_REGISTER_VSM_CAPABILITIES *PHV_ARM64_REGISTER_VSM_CAPABILITIES;

/* 17020 */
typedef _HV_ARM64_REGISTER_TLBI_CONTROL *PHV_ARM64_REGISTER_TLBI_CONTROL;

/* 17147 */
typedef _HV_RDT_CAT_COS_BITMASK_PROPERTY *PHV_RDT_CAT_COS_BITMASK_PROPERTY;

/* 17218 */
typedef _HV_REGISTER_REFERENCE_TSC HV_REGISTER_REFERENCE_TSC;

/* 17325 */
typedef _HV_OUTPUT_GET_PARTITION_RESERVED_PAGES HV_OUTPUT_GET_PARTITION_RESERVED_PAGES;

/* 17490 */
typedef _HV_ARM64_INVALID_VP_REGISTER_MESSAGE HV_ARM64_INVALID_VP_REGISTER_MESSAGE;

/* 17565 */
typedef _HV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA HV_ENABLE_PARTITION_VTL_INTERCEPT_COMPLETION_DATA;

/* 17962 */
typedef _HV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT *PHV_CHECK_GPA_PAGE_VTL_ACCESS_RESULT;

/* 18041 */
typedef unsigned int HV_UNMAP_GPA_FLAGS;

/* 18046 */
typedef _HV_INPUT_GPA_PAGE_PINNING HV_INPUT_GPA_PAGE_PINNING;

/* 18180 */
typedef _HV_REGISTER_HVPT_CONTROL *PHV_REGISTER_HVPT_CONTROL;

/* 18250 */
typedef _HV_SEAM_TDMR *PHV_SEAM_TDMR;

/* 18488 */
typedef _HV_VP_DISPATCH_LOOP_RESULT *PHV_VP_DISPATCH_LOOP_RESULT;

/* 18603 */
typedef _HV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE *PHV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE;

/* 18687 */
typedef _HV_X64_REGISTER_SEV_GHCB *PHV_X64_REGISTER_SEV_GHCB;

/* 19054 */
typedef _HV_INPUT_NOTIFY_EVENT_RING_EMPTY HV_INPUT_NOTIFY_EVENT_RING_EMPTY;

/* 19058 */
typedef _HV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK *PHV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK;

/* 19231 */
typedef _HV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD *PHV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD;

/* 19251 */
typedef _HV_MINROOT_NUMA_LPS *PHV_MINROOT_NUMA_LPS;

/* 19321 */
typedef _HV_VP_ASSIST_PAGE_ACTION HV_VP_ASSIST_PAGE_ACTION;

/* 19334 */
typedef unsigned __int64 HV_KEY_ID;

/* 19347 */
typedef _HV_RDT_CAT_COS_BITMASK_PROPERTY HV_RDT_CAT_COS_BITMASK_PROPERTY;

/* 19562 */
typedef _HV_PARTITION_DEPOSIT_STATUS HV_PARTITION_DEPOSIT_STATUS;

/* 19584 */
typedef _HV_MEMORY_PROXIMITY_INFO *PHV_MEMORY_PROXIMITY_INFO;

/* 19616 */
typedef _HV_RESTART_COMPLETION_MESSAGE_PAYLOAD HV_RESTART_COMPLETION_MESSAGE_PAYLOAD;

/* 19617 */
typedef _HV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE HV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE;

/* 19792 */
typedef _HV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE *PHV_ARM64_TLB_PAGE_SIZE_MISMATCH_MESSAGE;

/* 20039 */
typedef unsigned __int8 HV_IOMMU_STATUS_SEVERITY;

/* 20114 */
typedef _HV_PARTITION_VSM_CONFIG HV_PARTITION_VSM_CONFIG;

/* 20255 */
typedef _HV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE HV_ENABLE_PARTITION_VTL_INTERCEPT_MESSAGE;

/* 20293 */
typedef _HV_LOADER_IOMMU_ENTRY *PHV_LOADER_IOMMU_ENTRY;

/* 20511 */
typedef unsigned int HV_PRECOMMIT_GPA_FLAGS;

/* 20515 */
typedef _HV_PSP_DEVICE HV_PSP_DEVICE;

/* 20916 */
typedef unsigned int *PHV_LOCK_GPA_PAGE_MAPPING_FLAGS;

/* 21112 */
typedef _HV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA *PHV_GPA_ATTRIBUTE_INTERCEPT_COMPLETION_DATA;

/* 21203 */
typedef _HV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT *PHV_VP_ASSIST_PAGE_ACTION_SIGNAL_EVENT;

/* 21378 */
typedef _HV_OUTPUT_GET_PARTITION_RESERVED_PAGES *PHV_OUTPUT_GET_PARTITION_RESERVED_PAGES;

/* 21603 */
typedef _HV_ARM64_REGISTER_VSM_CAPABILITIES HV_ARM64_REGISTER_VSM_CAPABILITIES;

/* 21641 */
typedef _HV_X64_MSR_VP_EXIT_REASON_CONTENTS *PHV_X64_MSR_VP_EXIT_REASON_CONTENTS;

/* 21718 */
typedef _HV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD *PHV_MIRRORING_NOTIFICATION_MESSAGE_PAYLOAD;

/* 21835 */
typedef _HV_ARM64_VOLATILE_GP_REGS HV_ARM64_VOLATILE_GP_REGS;

/* 22057 */
typedef _HV_PARTITION_ISOLATION_POLICY HV_PARTITION_ISOLATION_POLICY;

/* 22244 */
typedef _HV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER *PHV_X64_DELIVERABILITY_NOTIFICATIONS_REGISTER;

/* 22279 */
typedef _HV_PARK_BLOCK_INFO HV_PARK_BLOCK_INFO;

/* 22298 */
typedef _HV_X64_REGISTER_SEV_CONTROL HV_X64_REGISTER_SEV_CONTROL;

/* 22428 */
typedef _HV_INPUT_GPA_PAGE_PINNING *PHV_INPUT_GPA_PAGE_PINNING;

/* 22463 */
typedef _HV_X64_IO_PORT_READ_COMPLETION_DATA *PHV_X64_IO_PORT_READ_COMPLETION_DATA;

/* 22482 */
typedef _HV_X64_REGISTER_SEV_HV_DOORBELL *PHV_X64_REGISTER_SEV_HV_DOORBELL;

/* 22518 */
typedef _HV_PSP_DEVICE *PHV_PSP_DEVICE;

/* 22601 */
typedef _HV_SEAM_TDMR_RESERVATION HV_SEAM_TDMR_RESERVATION;

/* 22612 */
typedef _HV_DMA_RANGE *PHV_DMA_RANGE;

/* 22626 */
typedef unsigned __int8 *PHV_IOMMU_STATUS_SEVERITY;

/* 22627 */
typedef _HV_INPUT_EVENTLOG_SET_EVENTS *PHV_INPUT_EVENTLOG_SET_EVENTS;

/* 22656 */
typedef _HV_PICO100_DURATION HV_PICO100_DURATION;

/* 22780 */
typedef _HV_PSP_REQUEST_COMPLETION_DATA HV_PSP_REQUEST_COMPLETION_DATA;

/* 22808 */
typedef _HV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE HV_GPA_ATTRIBUTE_INTERCEPT_MESSAGE;

/* 22850 */
typedef _HV_ARM64_UNSUPPORTED_FEATURE_MESSAGE *PHV_ARM64_UNSUPPORTED_FEATURE_MESSAGE;

/* 22855 */
typedef unsigned __int64 *PHV_KEY_ID;

/* 22965 */
typedef unsigned __int16 HV_IOMMU_STATUS;

/* 22974 */
typedef _HV_HYPERCALL_INTERCEPT_COMPLETION_DATA *PHV_HYPERCALL_INTERCEPT_COMPLETION_DATA;

/* 23091 */
typedef _HV_IOMMU_GVA_RANGE HV_IOMMU_GVA_RANGE;

/* 23209 */
typedef _HV_SYNIC_EVENT_INTERCEPT_MESSAGE HV_SYNIC_EVENT_INTERCEPT_MESSAGE;

/* 23598 */
typedef _HV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES *PHV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES;

/* 23748 */
typedef _HV_REGISTER_HVPT_CONTROL HV_REGISTER_HVPT_CONTROL;

/* 23759 */
typedef _HV_REGISTER_GUEST_VSM_PARTITION_CONFIG HV_REGISTER_GUEST_VSM_PARTITION_CONFIG;

/* 23933 */
typedef _HV_REGISTER_ISOLATION_CAPABILITIES HV_REGISTER_ISOLATION_CAPABILITIES;

/* 23954 */
typedef _HV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD HV_INSUFFICIENT_MEMORY_MESSAGE_PAYLOAD;

/* 24085 */
typedef _HV_PARTITION_ENLIGHTENMENT_MODIFICATIONS HV_PARTITION_ENLIGHTENMENT_MODIFICATIONS;

/* 24124 */
typedef _HV_ROOT_PASID_CAPABILITIES_PROPERTY *PHV_ROOT_PASID_CAPABILITIES_PROPERTY;

/* 24216 */
typedef _HV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES HV_PARTITION_PROCESSOR_VIRTUALIZATION_FEATURES;

/* 24387 */
typedef _HV_SNP_PSP_TCB_VERSION HV_SNP_PSP_TCB_VERSION;

/* 24439 */
typedef _HV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK HV_REGISTER_VSM_VP_WAIT_FOR_TLB_LOCK;

/* 24447 */
typedef _HV_LOADER_IOMMU_ENTRY HV_LOADER_IOMMU_ENTRY;

/* 24613 */
typedef _HV_RDT_MBA_COS_VALUE_PROPERTY *PHV_RDT_MBA_COS_VALUE_PROPERTY;

/* 24713 */
typedef _HV_SEC_FW_VERSION *PHV_SEC_FW_VERSION;

/* 24745 */
typedef _HV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES HV_DEPRECATED_OUTPUT_QUERY_IOMMU_PROPERTIES;

/* 24871 */
typedef _HV_EVENTLOG_EXTENDED_TRACE_FLAGS HV_EVENTLOG_EXTENDED_TRACE_FLAGS;

/* 24897 */
typedef _HV_ARM64_UNSUPPORTED_FEATURE_MESSAGE HV_ARM64_UNSUPPORTED_FEATURE_MESSAGE;

/* 24930 */
typedef unsigned __int16 *PHV_IOMMU_STATUS;

/* 24978 */
typedef _HV_PARTITION_ISOLATION_POLICY *PHV_PARTITION_ISOLATION_POLICY;

/* 25156 */
typedef _HV_PARTITION_ENLIGHTENMENT_MODIFICATIONS *PHV_PARTITION_ENLIGHTENMENT_MODIFICATIONS;

/* 25278 */
typedef _HV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER HV_ARM64_DELIVERABILITY_NOTIFICATIONS_REGISTER;

/* 25296 */
typedef _HV_LOADER_PCI_SEGMENT_ENTRY HV_LOADER_PCI_SEGMENT_ENTRY;

/* 25313 */
typedef unsigned __int64 HV_MSI_ADDRESS;

/* 25358 */
typedef _HV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS HV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS;

/* 25445 */
typedef unsigned int *PHAL_HV_LOGICAL_PROCESSOR_INDEX;

/* 25686 */
typedef _HV_PARTITION_INFO_PAGE *PHV_PARTITION_INFO_PAGE;

/* 25869 */
typedef _HV_PARTITION_DIAG_LOG_BUFFER_CONFIG *PHV_PARTITION_DIAG_LOG_BUFFER_CONFIG;

/* 25873 */
typedef _HV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP *PHV_INPUT_PROTO_CREATE_PERSISTED_CPU_GROUP;

/* 25916 */
typedef _HV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS *PHV_X64_MSR_VP_EXIT_INTERRUPT_CONTROL_CONTENTS;

/* 26022 */
typedef _HV_SYNIC_EVENT_INTERCEPT_MESSAGE *PHV_SYNIC_EVENT_INTERCEPT_MESSAGE;

/* 26048 */
typedef _HV_PARTITION_PERFMON_MODE_CONFIG *PHV_PARTITION_PERFMON_MODE_CONFIG;
