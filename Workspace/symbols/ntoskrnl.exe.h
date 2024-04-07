/* 2886 */
struct $36DB9F07A37CDAA7F3A4AF928B3F4525
{
  unsigned int LowUINT32;
  unsigned int HighUINT32;
};

/* 2926 */
struct $6B81CF09F26873C195E2CE989509E704
{
  unsigned __int8 MessagePending : 1;
  unsigned __int8 Reserved : 7;
};

/* 2927 */
union _HV_MESSAGE_FLAGS
{
  unsigned __int8 AsUINT8;
  $6B81CF09F26873C195E2CE989509E704 __s1;
};

/* 2928 */
struct $8AF32EEB00CC3F214E56707D239D3B7E
{
  unsigned __int32 Id : 24;
  unsigned __int32 Reserved : 8;
};

/* 2929 */
union _HV_PORT_ID
{
  unsigned int AsUINT32;
  $8AF32EEB00CC3F214E56707D239D3B7E __s1;
};

/* 2930 */
union $D1EEE19CB71235FC67D686153E24B6B6
{
  unsigned __int64 Sender;
  _HV_PORT_ID Port;
};

/* 2931 */
struct _HV_MESSAGE_HEADER
{
  _HV_MESSAGE_TYPE MessageType;
  unsigned __int8 PayloadSize;
  _HV_MESSAGE_FLAGS MessageFlags;
  unsigned __int8 Reserved[2];
  $D1EEE19CB71235FC67D686153E24B6B6 ___u4;
};

/* 2942 */
struct $352BCEDFA7E8D0B2D79C7602DC568660
{
  unsigned __int64 MsrInterceptMode : 2;
  unsigned __int64 MsrBitmapDirty : 1;
  unsigned __int64 RsvdZ : 61;
};

/* 2943 */
union _HV_REGISTER_NESTED_CONTROL
{
  unsigned __int64 AsUINT64;
  $352BCEDFA7E8D0B2D79C7602DC568660 __s1;
};

/* 3021 */
struct $49DCC3E6D30D7C5E68A4A8C664B3CAE5
{
  unsigned __int64 MbecEnabled : 1;
  unsigned __int64 TlbLocked : 1;
  unsigned __int64 ReservedZ : 62;
};

/* 3022 */
union _HV_REGISTER_VSM_VP_SECURE_VTL_CONFIG
{
  unsigned __int64 AsUINT64;
  $49DCC3E6D30D7C5E68A4A8C664B3CAE5 __s1;
};

/* 3231 */
struct $2FEEC14B6DD1B713F0D21D95BFA4C20B
{
  unsigned __int32 NoEOIRequired : 1;
};

/* 3232 */
union $B0001D64052FD40254A2EDFA56F629F9
{
  int ApicFlags;
  $2FEEC14B6DD1B713F0D21D95BFA4C20B __s1;
};

/* 3233 */
struct _HV_VIRTUAL_APIC_ASSIST
{
  $B0001D64052FD40254A2EDFA56F629F9 ___u0;
};

/* 3337 */
struct $0266DD6D772D72DB8EC6FA01D2585088
{
  unsigned __int64 Enabled : 1;
  unsigned __int64 RsvdZ : 63;
};

/* 3338 */
union _HV_TSC_EMULATION_CONTROL
{
  unsigned __int64 AsUINT64;
  $0266DD6D772D72DB8EC6FA01D2585088 __s1;
};

/* 3441 */
struct __cppobj _HV_REFERENCE_TSC_PAGE
{
  volatile unsigned int TscSequence;
  unsigned int Reserved1;
  volatile unsigned __int64 TscScale;
  volatile __int64 TscOffset;
  unsigned __int64 Reserved2[509];
};

/* 3473 */
struct $6C884DCBC9CF7BF40AA6A5621E034C3A
{
  unsigned __int64 Cr0Write : 1;
  unsigned __int64 Cr4Write : 1;
  unsigned __int64 XCr0Write : 1;
  unsigned __int64 IA32MiscEnableRead : 1;
  unsigned __int64 IA32MiscEnableWrite : 1;
  unsigned __int64 MsrLstarRead : 1;
  unsigned __int64 MsrLstarWrite : 1;
  unsigned __int64 MsrStarRead : 1;
  unsigned __int64 MsrStarWrite : 1;
  unsigned __int64 MsrCstarRead : 1;
  unsigned __int64 MsrCstarWrite : 1;
  unsigned __int64 ApicBaseMsrRead : 1;
  unsigned __int64 ApicBaseMsrWrite : 1;
  unsigned __int64 MsrEferRead : 1;
  unsigned __int64 MsrEferWrite : 1;
  unsigned __int64 GdtrWrite : 1;
  unsigned __int64 IdtrWrite : 1;
  unsigned __int64 LdtrWrite : 1;
  unsigned __int64 TrWrite : 1;
  unsigned __int64 MsrSysenterCsWrite : 1;
  unsigned __int64 MsrSysenterEipWrite : 1;
  unsigned __int64 MsrSysenterEspWrite : 1;
  unsigned __int64 MsrSfmaskWrite : 1;
  unsigned __int64 MsrTscAuxWrite : 1;
  unsigned __int64 RsvdZ : 40;
};

/* 3474 */
union _HV_REGISTER_CR_INTERCEPT_CONTROL
{
  unsigned __int64 AsUINT64;
  $6C884DCBC9CF7BF40AA6A5621E034C3A __s1;
};

/* 3667 */
struct $22F2B92E971F267BB4D786C0AE79BEE0
{
  unsigned __int8 EnableMbec : 1;
  unsigned __int8 Reserved : 7;
};

/* 3668 */
union _HV_ENABLE_PARTITION_VTL_FLAGS
{
  unsigned __int8 AsUINT8;
  $22F2B92E971F267BB4D786C0AE79BEE0 __s1;
};

/* 3724 */
struct $92560E5375D4F6A085E11034DE5E6882
{
  unsigned __int64 Mapped : 1;
  unsigned __int64 ReservedP : 11;
  unsigned __int64 GpaPageNumber : 52;
};

/* 3725 */
union _HV_REGISTER_VSM_VP_VTL_CONTROL
{
  unsigned __int64 AsUINT64;
  $92560E5375D4F6A085E11034DE5E6882 __s1;
};

/* 3905 */
struct $B70A472D9CC7CC52192E08F5AB511E1F
{
  unsigned __int64 LegacyX87 : 1;
  unsigned __int64 LegacySse : 1;
  unsigned __int64 Avx : 1;
  unsigned __int64 Bndreg : 1;
  unsigned __int64 Bndcsr : 1;
  unsigned __int64 Opmask : 1;
  unsigned __int64 Zmmhi256 : 1;
  unsigned __int64 Zmm16_31 : 1;
  unsigned __int64 Reserved : 56;
};

/* 3906 */
union _HV_X64_XSAVE_XFEM_REGISTER
{
  unsigned __int64 AsUINT64;
  $36DB9F07A37CDAA7F3A4AF928B3F4525 __s1;
  $B70A472D9CC7CC52192E08F5AB511E1F __s2;
};

/* 3907 */
struct _HV_X64_XSAVE_HEADER
{
  _HV_X64_XSAVE_XFEM_REGISTER XstateBv;
  unsigned __int64 Reserved0MBZ;
  unsigned __int16 RevisionID;
  unsigned __int16 Reserved1MBZ;
  unsigned int Reserved2;
  unsigned __int64 Reserved3;
  unsigned __int64 Reserved4;
  unsigned __int64 Reserved5;
  unsigned __int64 Reserved6;
  unsigned __int64 Reserved7;
};

/* 4012 */
struct _HV_TIMER_MESSAGE_PAYLOAD
{
  unsigned int TimerIndex;
  unsigned int Reserved;
  unsigned __int64 ExpirationTime;
  unsigned __int64 DeliveryTime;
};

/* 4013 */
union $40B801FA4C5C97758D5A5A923734C8F7
{
  unsigned __int64 Payload[30];
  _HV_TIMER_MESSAGE_PAYLOAD TimerPayload;
  _HV_EVENTLOG_MESSAGE_PAYLOAD TracePayload;
};

/* 4014 */
volatile struct _HV_MESSAGE
{
  _HV_MESSAGE_HEADER Header;
  $40B801FA4C5C97758D5A5A923734C8F7 ___u1;
};

/* 4015 */
struct _HV_MESSAGE_PAGE
{
  volatile _HV_MESSAGE SintMessage[16];
};

/* 4335 */
struct $811FDB4F6923FD2366AF1D10536D4891
{
  unsigned __int64 SimpEnabled : 1;
  unsigned __int64 Preserved : 11;
  unsigned __int64 BaseSimpGpa : 52;
};

/* 4336 */
union _HV_SYNIC_SIMP
{
  unsigned __int64 AsUINT64;
  $811FDB4F6923FD2366AF1D10536D4891 __s1;
};

/* 4541 */
struct $2954D343275FA966F67CA07F4BE3DD3E
{
  unsigned __int64 Vector : 8;
  unsigned __int64 ReservedP1 : 8;
  unsigned __int64 Masked : 1;
  unsigned __int64 AutoEoi : 1;
  unsigned __int64 Polling : 1;
  unsigned __int64 ReservedP2 : 45;
};

/* 4542 */
union _HV_SYNIC_SINT
{
  unsigned __int64 AsUINT64;
  $2954D343275FA966F67CA07F4BE3DD3E __s1;
};

/* 4588 */
union _HV_X64_XSAVE_AREA
{
  _HV_X64_FX_REGISTERS LegacyFxRegisters;
  _HV_X64_X_REGISTERS XRegisters;
};

/* 4696 */
struct $345138E7AE76ED1FC824C1BE61BB6FD6
{
  unsigned __int64 EnableVtlProtection : 1;
  unsigned __int64 DefaultVtlProtectionMask : 4;
  unsigned __int64 ZeroMemoryOnReset : 1;
  unsigned __int64 ReservedZ : 58;
};

/* 4697 */
union _HV_REGISTER_VSM_PARTITION_CONFIG
{
  unsigned __int64 AsUINT64;
  $345138E7AE76ED1FC824C1BE61BB6FD6 __s1;
};

/* 4949 */
struct $E1F76BD6070F30024AD71EC1D3E97394
{
  unsigned __int64 VtlCallOffset : 12;
  unsigned __int64 VtlReturnOffset : 12;
  unsigned __int64 ReservedZ : 40;
};

/* 4950 */
union _HV_REGISTER_VSM_CODE_PAGE_OFFSETS
{
  unsigned __int64 AsUINT64;
  $E1F76BD6070F30024AD71EC1D3E97394 __s1;
};

/* 5033 */
struct $E40A898125F12467A4105D9FBACA6083
{
  unsigned __int64 Enable : 1;
  unsigned __int64 ReservedP : 11;
  unsigned __int64 GpaPageNumber : 52;
};

/* 5034 */
union _HV_REGISTER_VP_ASSIST_PAGE
{
  unsigned __int64 AsUINT64;
  $E40A898125F12467A4105D9FBACA6083 __s1;
};

/* 5134 */
struct $D832DE7733A49B13559E48FC17DEDC03
{
  unsigned __int64 Reserved : 63;
  unsigned __int64 CrashNotify : 1;
};

/* 5135 */
union _HV_CRASH_CTL_REG_CONTENTS
{
  unsigned __int64 AsUINT64;
  $D832DE7733A49B13559E48FC17DEDC03 __s1;
};

/* 5282 */
struct $C8C71A3554795C5A34C0B8E41DA6C5FE
{
  unsigned __int64 Vector : 8;
  unsigned __int64 Enabled : 1;
  unsigned __int64 AutoReset : 1;
  unsigned __int64 AutoEoi : 1;
  unsigned __int64 ReservedP : 53;
};

/* 5283 */
union _HV_REGISTER_VSM_VINA
{
  unsigned __int64 AsUINT64;
  $C8C71A3554795C5A34C0B8E41DA6C5FE __s1;
};

/* 5360 */
struct $7FC1A2B0BAA403ECCCE4A9F4765A6963
{
  unsigned __int64 Dr6Shared : 1;
  unsigned __int64 MbecVtlMask : 16;
  unsigned __int64 ReservedZ : 47;
};

/* 5361 */
union _HV_REGISTER_VSM_CAPABILITIES
{
  unsigned __int64 AsUINT64;
  $7FC1A2B0BAA403ECCCE4A9F4765A6963 __s1;
};

/* 5476 */
struct $B10584B2A335FF3BCC7C6AC2DEDFD761
{
  unsigned __int64 Vector : 8;
  unsigned __int64 RsvdZ1 : 8;
  unsigned __int64 Enabled : 1;
  unsigned __int64 RsvdZ2 : 15;
  unsigned __int64 TargetVp : 32;
};

/* 5477 */
union _HV_REENLIGHTENMENT_CONTROL
{
  unsigned __int64 AsUINT64;
  $B10584B2A335FF3BCC7C6AC2DEDFD761 __s1;
};

/* 5500 */
struct $AD16F5AD0D79B0B966E2A6967F68291E
{
  unsigned __int64 ActiveVtl : 4;
  unsigned __int64 ActiveMbecEnabled : 1;
  unsigned __int64 ReservedZ0 : 11;
  unsigned __int64 EnabledVtlSet : 16;
  unsigned __int64 ReservedZ1 : 32;
};

/* 5501 */
union _HV_REGISTER_VSM_VP_STATUS
{
  unsigned __int64 AsUINT64;
  $AD16F5AD0D79B0B966E2A6967F68291E __s1;
};

/* 5557 */
struct $665D16390830E1750BE3CF386BE04F7B
{
  unsigned __int64 InProgress : 1;
  unsigned __int64 RsvdP1 : 63;
};

/* 5558 */
union _HV_TSC_EMULATION_STATUS
{
  unsigned __int64 AsUINT64;
  $665D16390830E1750BE3CF386BE04F7B __s1;
};

/* 5643 */
struct $DB15C8D79598A375F3FDFABA2117B30A
{
  unsigned __int64 EnabledVtlSet : 16;
  unsigned __int64 MaximumVtl : 4;
  unsigned __int64 ReservedZ : 44;
};

/* 5644 */
union _HV_REGISTER_VSM_PARTITION_STATUS
{
  unsigned __int64 AsUINT64;
  $DB15C8D79598A375F3FDFABA2117B30A __s1;
};

/* 5669 */
struct $F244B3B4672D2F4E33F1DF388E1ACD8F
{
  unsigned __int64 FastReturn : 1;
  unsigned __int64 ReservedZ : 63;
};

/* 5670 */
union _HV_VTL_RETURN_INPUT
{
  unsigned __int64 AsUINT64;
  $F244B3B4672D2F4E33F1DF388E1ACD8F __s1;
};

/* 6174 */
struct _HVLP_POWER_POLICY_MAPPING
{
  const _GUID *SettingGuid;
  _HV_PPM_POWER_POLICY_SETTING_ID HvSetting;
};

/* 6184 */
struct $A5881D183D407EF6CAA925D48F187397
{
  unsigned __int32 CallCode : 15;
  unsigned __int32 IsExtended : 1;
  unsigned __int32 IsFast : 1;
  unsigned __int32 VariableHeaderSize : 9;
  unsigned __int32 Reserved1 : 5;
  unsigned __int32 IsNested : 1;
  unsigned __int32 CountOfElements : 12;
  unsigned __int32 Reserved2 : 4;
  unsigned __int32 RepStartIndex : 12;
  unsigned __int32 Reserved3 : 4;
};

/* 6185 */
union _HV_HYPERCALL_INPUT_PRIVATE
{
  $A5881D183D407EF6CAA925D48F187397 __s0;
  unsigned __int64 AsUINT64;
};

/* 6249 */
struct $D95064D84F36E57B283ED8F33E22A0FC
{
  unsigned int Eax;
  unsigned int Ecx;
};

/* 6250 */
union _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS
{
  $D95064D84F36E57B283ED8F33E22A0FC __s0;
  unsigned int MsrIndex;
};

/* 6251 */
struct _HV_LOGICAL_PROCESSOR_REGISTER_ID
{
  unsigned int LpIndex;
  _HV_LOGICAL_PROCESSOR_REGISTER_TYPE Type;
  _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS Address;
};

/* 6252 */
union _HV_LOGICAL_PROCESSOR_REGISTER_VALUE
{
  _HV_UINT128 Reg128;
  unsigned __int64 Reg64;
  unsigned int Reg32;
  unsigned __int16 Reg16;
  unsigned __int8 Reg8;
  _HV_CPUID_RESULT Cpuid;
};

/* 6253 */
struct _HV_LOGICAL_PROCESSOR_REGISTER_ASSOC
{
  _HV_LOGICAL_PROCESSOR_REGISTER_ID Id;
  _HV_LOGICAL_PROCESSOR_REGISTER_VALUE Value;
};

/* 6271 */
struct _HV_MCUPDATE_DATA_HEADER
{
  unsigned int DataSize;
  unsigned int TableOffset;
};

/* 6295 */
union $DBA3D336E9EB974719CB8C3475C80BD1
{
  unsigned __int16 IoPort;
  unsigned __int64 RegistersSpa;
};

/* 6296 */
struct __declspec(align(8)) $0139F1E188FB5B111FF8F184CFEFA80C
{
  _HV_BOOT_DEBUG_COM_PORT_TYPE ComPortType;
  $DBA3D336E9EB974719CB8C3475C80BD1 ___u1;
  unsigned int BaudRate;
};

/* 6297 */
struct $621265030E7E319C86E68DD161F108DD
{
  unsigned int Bus;
  unsigned int Slot;
  unsigned __int16 Flags;
  unsigned __int8 HvChannelId;
  unsigned __int8 RootChannelId;
  unsigned __int64 OhciRegistersSpa;
};

/* 6298 */
struct $70ACE71447E674491A39C7488D9167A7
{
  unsigned int Bus;
  unsigned int Slot;
  unsigned int HostIP;
  unsigned int Flags;
  unsigned __int16 VendorID;
  unsigned __int16 DeviceID;
  unsigned __int16 HostHvPort;
  unsigned __int16 HostRootPort;
  unsigned __int64 Key[4];
  unsigned __int64 BaseAddressRegisterSPA[6];
  unsigned int BaseAddressRegisterByteCount[6];
  unsigned __int16 BaseAddressRegisterType[6];
  unsigned int KdNetDataSize;
};

/* 6299 */
union $670C960F2A0DAAD3E1F5E0212146DAC6
{
  $0139F1E188FB5B111FF8F184CFEFA80C Com;
  $621265030E7E319C86E68DD161F108DD Firewire;
  $70ACE71447E674491A39C7488D9167A7 Net;
};

/* 6300 */
struct _HV_BOOT_DEBUG_PARAMETERS
{
  _HV_BOOT_DEBUG_PORT_TYPE PortType;
  unsigned __int64 TransferPagesSpa;
  unsigned int TransferPagesCount;
  $670C960F2A0DAAD3E1F5E0212146DAC6 ___u3;
};

/* 6301 */
struct __declspec(align(8)) _HV_BOOT_PARAMETERS
{
  _HV_BOOT_DEBUG_PARAMETERS DebugParams;
  unsigned int Flags;
};

/* 6302 */
struct _HV_MINI_LOADER_BLOCK
{
  unsigned int LoaderBlockSize;
  unsigned int LoaderBlockVersion;
  unsigned __int64 LoaderBlockPhysicalAddress;
  unsigned __int64 HypervisorEntryPoint;
  unsigned __int64 HypervisorTransTabBasePhys;
  _HV_BOOT_PARAMETERS BootParameters;
  unsigned int RootPartitionProcessorCount;
  unsigned int RootPartitionProcessorsContextsOffset;
  unsigned int VpContextSize;
  unsigned int MiniVpContextSize;
  unsigned int HypervisorCrashdumpAreaPageCount;
  unsigned __int64 HypervisorCrashdumpAreaSpa;
  unsigned __int64 Below1MbPage;
};

/* 6310 */
struct $DE8B26E4790C6258A28237437B23B98C
{
  unsigned __int64 VersionNumber : 8;
  unsigned __int64 RsvdZ : 54;
  unsigned __int64 Available : 1;
  unsigned __int64 Locked : 1;
};

/* 6311 */
union _HV_CPU_MANAGEMENT_VERSION_REGISTER
{
  unsigned __int64 AsUINT64;
  $DE8B26E4790C6258A28237437B23B98C __s1;
};

/* 6317 */
struct $B1B289F858741040D59CB5B3B26D1590
{
  unsigned __int64 AdditionalPages : 11;
  unsigned __int64 LargePage : 1;
  unsigned __int64 BasePfn : 52;
};

/* 6318 */
struct $8BCE1229B5E00C1C77B75EB8EDACB382
{
  unsigned __int64 : 12;
  unsigned __int64 PageSize : 1;
  unsigned __int64 Reserved : 8;
  unsigned __int64 BaseLargePfn : 43;
};

/* 6319 */
union _HV_GPA_PAGE_RANGE
{
  $B1B289F858741040D59CB5B3B26D1590 __s0;
  unsigned __int64 AsUINT64;
  $8BCE1229B5E00C1C77B75EB8EDACB382 __s2;
};

/* 6321 */
struct $CF6426CC8F5C0B5FC8C212F6D143BB63
{
  unsigned __int16 Rid;
  unsigned __int16 Segment;
};

/* 6322 */
union _HV_PCI_ID
{
  unsigned int AsUINT32;
  $CF6426CC8F5C0B5FC8C212F6D143BB63 __s1;
  _HV_PCI_BDF Bdf;
};

/* 6346 */
struct $3CD7DDAFA1E726BB8D747DF6F71C35DB
{
  unsigned int LpIndex;
  unsigned int Reserved;
};

/* 6347 */
union _HV_MCA_FAULTING_LP_MSR
{
  unsigned __int64 AsUINT64;
  $3CD7DDAFA1E726BB8D747DF6F71C35DB __s1;
};

/* 6348 */
struct $B2AA39715C45E895DB87F66B5E9E85FC
{
  unsigned __int64 Reserved2 : 61;
  unsigned __int64 InvalidRequest : 1;
  unsigned __int64 ValidateGpa : 1;
  unsigned __int64 SendResponse : 1;
};

/* 6349 */
struct $18B4558E05C81A70F55DBFCD3950FC9F
{
  unsigned __int64 : 63;
  unsigned __int64 Overflow : 1;
};

/* 6350 */
union $66A00931D2028C4A0E1B26932CEE062F
{
  $B2AA39715C45E895DB87F66B5E9E85FC __s0;
  $18B4558E05C81A70F55DBFCD3950FC9F __s1;
};

/* 6351 */
struct _HV_DEVICE_PAGE_REQUEST
{
  unsigned int DeviceId;
  unsigned __int32 Pasid : 20;
  unsigned __int32 Virtual : 1;
  unsigned __int32 GroupIndex : 9;
  unsigned __int32 LastInGroup : 1;
  unsigned __int32 StreamRequest : 1;
  unsigned __int64 Read : 1;
  unsigned __int64 Write : 1;
  unsigned __int64 Execute : 1;
  unsigned __int64 Privileged : 1;
  unsigned __int64 Reserved0 : 8;
  unsigned __int64 PageNumber : 52;
  unsigned __int64 Reserved1;
  $66A00931D2028C4A0E1B26932CEE062F ___u13;
};

/* 6368 */
struct _HV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED
{
  unsigned __int8 InterruptMasked;
  unsigned __int8 Reserved0;
  unsigned __int16 Reserved1;
  unsigned int Reserved2;
};

/* 6376 */
struct _HV_X64_VOLATILE_GP_REGS
{
  unsigned __int64 Rax;
  unsigned __int64 Rcx;
  unsigned __int64 Rdx;
  unsigned __int64 R8;
  unsigned __int64 R9;
  unsigned __int64 R10;
  unsigned __int64 R11;
};

/* 6378 */
struct $A884C835E5FA3C7EFC849C097925A7E3
{
  unsigned __int8 Function : 3;
  unsigned __int8 Device : 5;
};

/* 6379 */
union $F6F56C1DCA1FE4FF2CB9A163BBAAA1B0
{
  $A884C835E5FA3C7EFC849C097925A7E3 __s0;
  unsigned __int8 AsUINT8;
};

/* 6380 */
struct __declspec(align(2)) _HV_PCI_PATH
{
  unsigned __int8 PathLength;
  unsigned __int16 Segment;
  unsigned __int8 StartBus;
  $F6F56C1DCA1FE4FF2CB9A163BBAAA1B0 Path[];
};

/* 6381 */
struct __declspec(align(2)) _HV_DEVICE_PRQ_HEADER
{
  unsigned int Head;
  unsigned int Tail;
  unsigned __int8 Pending;
  unsigned __int8 Stalled;
  unsigned __int8 Error;
};

/* 6396 */
struct _HVLP_LPCB
{
  volatile unsigned int Started;
  unsigned int LpIndex;
  unsigned int ApicId;
  unsigned __int16 NodeNumber;
  unsigned int PackageId;
  unsigned int CoreId;
  unsigned int NtProcessorIndex;
  void *StatisticsPage;
  unsigned int IsSelectedForVpStart;
  _HV_LP_STARTUP_STATUS StartupStatusInfo;
};

/* 8500 */
struct _PPM_HV_STATS
{
  unsigned __int64 CurrentTime;
  unsigned __int64 IdleAccumulation;
  unsigned __int64 ActiveCycleSnap;
};

/* 12193 */
typedef _HV_BOOT_DEBUG_PARAMETERS *PHV_BOOT_DEBUG_PARAMETERS;

/* 12282 */
typedef unsigned __int8 HV_IOAPIC_ID;

/* 12598 */
typedef _HV_ENABLE_PARTITION_VTL_FLAGS *PHV_ENABLE_PARTITION_VTL_FLAGS;

/* 12820 */
typedef const _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS *PCHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 12882 */
typedef _HV_PORT_ID *PHV_PORT_ID;

/* 13027 */
typedef unsigned int *PHV_LOGICAL_DEVICE_ID;

/* 13175 */
typedef _HV_X64_XSAVE_XFEM_REGISTER *PHV_X64_XSAVE_XFEM_REGISTER;

/* 13193 */
typedef _HV_MINI_LOADER_BLOCK *PHV_MINI_LOADER_BLOCK;

/* 13235 */
typedef unsigned __int16 *PHV_PCI_SEGMENT;

/* 13258 */
typedef _HV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED *PHV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED;

/* 13314 */
typedef _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS *PHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 13606 */
typedef _HV_X64_XSAVE_HEADER *PHV_X64_XSAVE_HEADER;

/* 13667 */
typedef unsigned __int16 *PHV_STATUS;

/* 13683 */
typedef _HV_BOOT_PARAMETERS *PHV_BOOT_PARAMETERS;

/* 13699 */
typedef _HV_MESSAGE *PHV_MESSAGE;

/* 13752 */
typedef unsigned int HV_APIC_ID;

/* 13809 */
typedef unsigned int HV_VP_INDEX;

/* 13945 */
typedef unsigned int *PHV_LOGICAL_PROCESSOR_INDEX;

/* 14174 */
typedef _HV_TIMER_MESSAGE_PAYLOAD *PHV_TIMER_MESSAGE_PAYLOAD;

/* 14221 */
typedef _HV_GPA_PAGE_RANGE *PHV_GPA_PAGE_RANGE;

/* 14334 */
typedef _HV_VTL_RETURN_INPUT *PHV_VTL_RETURN_INPUT;

/* 14380 */
typedef _HV_REGISTER_VSM_VINA *PHV_REGISTER_VSM_VINA;

/* 14392 */
typedef unsigned __int64 *PHV_NANO100_DURATION;

/* 14418 */
typedef unsigned __int8 HV_VTL;

/* 14440 */
typedef unsigned __int64 HV_NANO100_TIME;

/* 14498 */
typedef _HV_EVENTLOG_MESSAGE_PAYLOAD *PHV_EVENTLOG_MESSAGE_PAYLOAD;

/* 14581 */
typedef _HV_REGISTER_VSM_CODE_PAGE_OFFSETS *PHV_REGISTER_VSM_CODE_PAGE_OFFSETS;

/* 14695 */
typedef unsigned int HAL_HV_VIRTUAL_PROCESSOR_INDEX;

/* 14710 */
typedef _HV_REENLIGHTENMENT_CONTROL *PHV_REENLIGHTENMENT_CONTROL;

/* 14792 */
typedef unsigned __int16 HV_STATUS;

/* 14929 */
typedef const _HV_LOGICAL_PROCESSOR_REGISTER_ASSOC *PCHV_LOGICAL_PROCESSOR_REGISTER_ASSOC;

/* 15403 */
typedef unsigned __int64 HV_DEVICE_VA;

/* 15502 */
typedef unsigned int HV_LOGICAL_DEVICE_ID;

/* 15601 */
typedef _HV_LOGICAL_PROCESSOR_REGISTER_VALUE *PHV_LOGICAL_PROCESSOR_REGISTER_VALUE;

/* 15972 */
typedef unsigned __int16 *PHV_PCI_RID;

/* 16131 */
typedef const _HV_LOGICAL_PROCESSOR_REGISTER_ID *PCHV_LOGICAL_PROCESSOR_REGISTER_ID;

/* 16303 */
typedef _HV_MESSAGE_FLAGS *PHV_MESSAGE_FLAGS;

/* 16323 */
typedef unsigned int HV_DEVICE_DOMAIN_ID;

/* 16379 */
typedef unsigned int *PHAL_HV_VIRTUAL_PROCESSOR_INDEX;

/* 16381 */
typedef unsigned __int64 *PHV_PARTITION_ID;

/* 16395 */
typedef _HV_REGISTER_CR_INTERCEPT_CONTROL *PHV_REGISTER_CR_INTERCEPT_CONTROL;

/* 16410 */
typedef _HV_REGISTER_VSM_CAPABILITIES *PHV_REGISTER_VSM_CAPABILITIES;

/* 16480 */
typedef _PPM_HV_STATS *PPPM_HV_STATS;

/* 16532 */
typedef unsigned __int64 *PHV_NANO100_TIME;

/* 16860 */
typedef unsigned int *PHV_DEVICE_PR_QUEUE_ID;

/* 16930 */
typedef _HV_HYPERCALL_OUTPUT (__stdcall *PHVCALL_HYPERCALL_ROUTINE)(_HV_HYPERCALL_INPUT, unsigned __int64, unsigned __int64);

/* 17174 */
typedef _HV_MCA_FAULTING_LP_MSR *PHV_MCA_FAULTING_LP_MSR;

/* 17210 */
typedef unsigned __int64 *PHV_DEVICE_VA;

/* 17334 */
typedef unsigned int HV_SYNIC_SINT_INDEX;

/* 17346 */
typedef unsigned int HV_PASID;

/* 17357 */
typedef unsigned __int16 HV_PCI_SEGMENT;

/* 17517 */
typedef _HV_REGISTER_VP_ASSIST_PAGE *PHV_REGISTER_VP_ASSIST_PAGE;

/* 17519 */
typedef _HV_LOGICAL_PROCESSOR_REGISTER_ASSOC *PHV_LOGICAL_PROCESSOR_REGISTER_ASSOC;

/* 17579 */
typedef unsigned __int64 *PHV_ADDRESS_SPACE_ID;

/* 17584 */
typedef _HV_SYNIC_SINT *PHV_SYNIC_SINT;

/* 17670 */
typedef _HV_VIRTUAL_APIC_ASSIST *PHV_VIRTUAL_APIC_ASSIST;

/* 17698 */
typedef unsigned __int64 HV_GPA_PAGE_NUMBER;

/* 17717 */
typedef unsigned __int64 HV_GVA_PAGE_NUMBER;

/* 17746 */
typedef unsigned int HV_PASID_SPACE_ID;

/* 17778 */
typedef _HV_DEVICE_PAGE_REQUEST *PHV_DEVICE_PAGE_REQUEST;

/* 17797 */
typedef int (__stdcall *PHAL_SVM_GET_DEVICE_CAPABILITIES)(unsigned int, _HAL_HV_SVM_DEVICE_CAPABILITIES *);

/* 17914 */
typedef unsigned __int64 *PHV_GVA_PAGE_NUMBER;

/* 17998 */
typedef _HV_PCI_ID *PHV_PCI_ID;

/* 18088 */
typedef _HV_TSC_EMULATION_STATUS *PHV_TSC_EMULATION_STATUS;

/* 18177 */
typedef _HV_REFERENCE_TSC_PAGE *PHV_REFERENCE_TSC_PAGE;

/* 18310 */
typedef unsigned int HV_INTERCEPT_ACCESS_TYPE_MASK;

/* 18327 */
typedef unsigned int HV_LOGICAL_PROCESSOR_INDEX;

/* 18478 */
typedef _HV_REGISTER_NESTED_CONTROL *PHV_REGISTER_NESTED_CONTROL;

/* 18487 */
typedef _HV_HYPERCALL_INPUT_PRIVATE *PHV_HYPERCALL_INPUT_PRIVATE;

/* 18536 */
typedef unsigned int *PHV_MAP_GPA_FLAGS;

/* 18603 */
typedef _HV_LOGICAL_PROCESSOR_REGISTER_ID *PHV_LOGICAL_PROCESSOR_REGISTER_ID;

/* 18727 */
typedef unsigned __int64 *PHV_GPA;

/* 18741 */
typedef _HAL_HV_SVM_SYSTEM_CAPABILITIES *PHAL_HV_SVM_SYSTEM_CAPABILITIES;

/* 18782 */
typedef unsigned __int64 *PHV_SPA;

/* 18815 */
typedef _HV_MESSAGE_PAGE *PHV_MESSAGE_PAGE;

/* 18967 */
typedef _HV_REGISTER_VSM_VP_SECURE_VTL_CONFIG *PHV_REGISTER_VSM_VP_SECURE_VTL_CONFIG;

/* 19070 */
typedef _HV_CRASH_CTL_REG_CONTENTS *PHV_CRASH_CTL_REG_CONTENTS;

/* 19208 */
typedef _HV_REGISTER_VSM_PARTITION_STATUS *PHV_REGISTER_VSM_PARTITION_STATUS;

/* 19267 */
typedef _HV_REGISTER_VSM_VP_STATUS *PHV_REGISTER_VSM_VP_STATUS;

/* 19315 */
typedef unsigned __int16 HV_STATS_OBJECT_FLAG;

/* 19588 */
typedef unsigned int *PHV_APIC_ID;

/* 19720 */
typedef _HV_REGISTER_VSM_PARTITION_CONFIG *PHV_REGISTER_VSM_PARTITION_CONFIG;

/* 19822 */
typedef _HV_CPU_MANAGEMENT_VERSION_REGISTER *PHV_CPU_MANAGEMENT_VERSION_REGISTER;

/* 19830 */
typedef _HV_X64_XSAVE_AREA *PHV_X64_XSAVE_AREA;

/* 19979 */
typedef _HV_MCUPDATE_DATA_HEADER *PHV_MCUPDATE_DATA_HEADER;

/* 20117 */
typedef unsigned __int64 HV_SPA;

/* 20252 */
typedef unsigned int *PHV_DEVICE_DOMAIN_ID;

/* 20256 */
typedef unsigned int *PHV_PASID;

/* 20442 */
typedef _HV_SYNIC_SIMP *PHV_SYNIC_SIMP;

/* 20531 */
typedef unsigned __int64 HV_SPA_PAGE_NUMBER;

/* 20985 */
typedef _HV_X64_VOLATILE_GP_REGS *PHV_X64_VOLATILE_GP_REGS;

/* 21133 */
typedef unsigned __int64 HV_ADDRESS_SPACE_ID;

/* 21213 */
typedef unsigned __int16 HV_PCI_RID;

/* 21243 */
typedef _HV_TSC_EMULATION_CONTROL *PHV_TSC_EMULATION_CONTROL;

/* 21582 */
typedef unsigned __int8 *PHV_VTL;

/* 21752 */
typedef unsigned int HV_MAP_GPA_FLAGS;

/* 21836 */
typedef unsigned int *PHV_SYNIC_SINT_INDEX;

/* 21841 */
typedef unsigned int *PHV_PASID_SPACE_ID;

/* 22014 */
typedef _HV_MESSAGE_HEADER *PHV_MESSAGE_HEADER;

/* 22121 */
typedef _HV_REGISTER_VSM_VP_VTL_CONTROL *PHV_REGISTER_VSM_VP_VTL_CONTROL;

/* 22124 */
typedef unsigned __int64 *PHV_GPA_PAGE_NUMBER;

/* 22156 */
typedef unsigned __int64 *PHV_SPA_PAGE_NUMBER;

/* 22186 */
typedef unsigned int HAL_HV_LOGICAL_PROCESSOR_INDEX;

/* 22326 */
typedef void (__stdcall *PHAL_SVM_GET_SYSTEM_CAPABILITIES)(_HAL_HV_SVM_SYSTEM_CAPABILITIES *);

/* 22532 */
typedef unsigned int *PHAL_HV_LOGICAL_PROCESSOR_INDEX;

/* 22555 */
typedef unsigned __int8 HV_INTERCEPT_ACCESS_TYPE;

/* 22627 */
typedef unsigned __int8 *PHV_IOAPIC_ID;

/* 22722 */
typedef _HV_PCI_PATH *PHV_PCI_PATH;

/* 22762 */
typedef unsigned int *PHV_VP_INDEX;

/* 22773 */
typedef unsigned __int64 HV_PARTITION_ID;

/* 22790 */
typedef unsigned __int64 HV_NANO100_DURATION;

/* 22860 */
typedef unsigned __int64 HV_GVA;

/* 22865 */
typedef unsigned __int64 HV_GPA;

/* 22917 */
typedef const _HV_LOGICAL_PROCESSOR_REGISTER_VALUE *PCHV_LOGICAL_PROCESSOR_REGISTER_VALUE;

/* 22953 */
typedef unsigned __int64 *PHV_GVA;

/* 22955 */
typedef unsigned int HV_DEVICE_PR_QUEUE_ID;

/* 22984 */
typedef _HV_DEVICE_PRQ_HEADER *PHV_DEVICE_PRQ_HEADER;
