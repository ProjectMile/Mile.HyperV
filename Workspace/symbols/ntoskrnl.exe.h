/* 2943 */
union _HV_REGISTER_NESTED_CONTROL
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned __int64 MsrInterceptMode : 2;
        unsigned __int64 MsrBitmapDirty : 1;
        unsigned __int64 RsvdZ : 61;
    };
};

/* 3725 */
union _HV_REGISTER_VSM_VP_VTL_CONTROL
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned __int64 Mapped : 1;
        unsigned __int64 ReservedP : 11;
        unsigned __int64 GpaPageNumber : 52;
    };
};

/* 4588 */
union _HV_X64_XSAVE_AREA
{
    _HV_X64_FX_REGISTERS LegacyFxRegisters;
    _HV_X64_X_REGISTERS XRegisters;
};

/* 5034 */
union _HV_REGISTER_VP_ASSIST_PAGE
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned __int64 Enable : 1;
        unsigned __int64 ReservedP : 11;
        unsigned __int64 GpaPageNumber : 52;
    };
};

/* 5361 */
union _HV_REGISTER_VSM_CAPABILITIES
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned __int64 Dr6Shared : 1;
        unsigned __int64 MbecVtlMask : 16;
        unsigned __int64 ReservedZ : 47;
    };
};

/* 5670 */
union _HV_VTL_RETURN_INPUT
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned __int64 FastReturn : 1;
        unsigned __int64 ReservedZ : 63;
    };
};

/* 6185 */
union _HV_HYPERCALL_INPUT_PRIVATE
{
    unsigned __int64 AsUINT64;
    struct
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
};

/* 6250 */
union _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS
{
    unsigned int MsrIndex;
    struct
    {
        unsigned int Eax;
        unsigned int Ecx;
    };
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

/* 6300 */
struct _HV_BOOT_DEBUG_PARAMETERS
{
    _HV_BOOT_DEBUG_PORT_TYPE PortType;
    unsigned __int64 TransferPagesSpa;
    unsigned int TransferPagesCount;
    union
    {
        struct __declspec(align(8))
        {
            _HV_BOOT_DEBUG_COM_PORT_TYPE ComPortType;
            union
            {
                unsigned __int16 IoPort;
                unsigned __int64 RegistersSpa;
            };
            unsigned int BaudRate;
        } Com;
        struct
        {
            unsigned int Bus;
            unsigned int Slot;
            unsigned __int16 Flags;
            unsigned __int8 HvChannelId;
            unsigned __int8 RootChannelId;
            unsigned __int64 OhciRegistersSpa;
        } Firewire;
        struct
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
        } Net;
    };
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

/* 6311 */
union _HV_CPU_MANAGEMENT_VERSION_REGISTER
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned __int64 VersionNumber : 8;
        unsigned __int64 RsvdZ : 54;
        unsigned __int64 Available : 1;
        unsigned __int64 Locked : 1;
    };
};

/* 6322 */
union _HV_PCI_ID
{
    unsigned int AsUINT32;
    struct
    {
        unsigned __int16 Rid;
        unsigned __int16 Segment;
    };
    _HV_PCI_BDF Bdf;
};

/* 6347 */
union _HV_MCA_FAULTING_LP_MSR
{
    unsigned __int64 AsUINT64;
    struct
    {
        unsigned int LpIndex;
        unsigned int Reserved;
    };
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
    union
    {
        struct
        {
            unsigned __int64 Reserved2 : 61;
            unsigned __int64 InvalidRequest : 1;
            unsigned __int64 ValidateGpa : 1;
            unsigned __int64 SendResponse : 1;
        };
        struct
        {
            unsigned __int64 : 63;
            unsigned __int64 Overflow : 1;
        };
    };
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

/* 6380 */
struct __declspec(align(2)) _HV_PCI_PATH
{
    unsigned __int8 PathLength;
    unsigned __int16 Segment;
    unsigned __int8 StartBus;
    union
    {
        unsigned __int8 AsUINT8;
        struct
        {
            unsigned __int8 Function : 3;
            unsigned __int8 Device : 5;
        };
    } Path[];
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

/* 8500 */
struct _PPM_HV_STATS
{
    unsigned __int64 CurrentTime;
    unsigned __int64 IdleAccumulation;
    unsigned __int64 ActiveCycleSnap;
};

/* 12193 */
typedef _HV_BOOT_DEBUG_PARAMETERS* PHV_BOOT_DEBUG_PARAMETERS;

/* 12282 */
typedef unsigned __int8 HV_IOAPIC_ID;

/* 12820 */
typedef const _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS* PCHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 13027 */
typedef unsigned int* PHV_LOGICAL_DEVICE_ID;

/* 13193 */
typedef _HV_MINI_LOADER_BLOCK* PHV_MINI_LOADER_BLOCK;

/* 13235 */
typedef unsigned __int16* PHV_PCI_SEGMENT;

/* 13258 */
typedef _HV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED* PHV_DEVICE_PRQ_PROPERTY_INTERRUPT_MASKED;

/* 13314 */
typedef _HV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS* PHV_X64_LOGICAL_PROCESSOR_REGISTER_ADDRESS;

/* 13667 */
typedef unsigned __int16* PHV_STATUS;

/* 13683 */
typedef _HV_BOOT_PARAMETERS* PHV_BOOT_PARAMETERS;

/* 13752 */
typedef unsigned int HV_APIC_ID;

/* 13809 */
typedef unsigned int HV_VP_INDEX;

/* 13945 */
typedef unsigned int* PHV_LOGICAL_PROCESSOR_INDEX;

/* 14334 */
typedef _HV_VTL_RETURN_INPUT* PHV_VTL_RETURN_INPUT;

/* 14392 */
typedef unsigned __int64* PHV_NANO100_DURATION;

/* 14418 */
typedef unsigned __int8 HV_VTL;

/* 14440 */
typedef unsigned __int64 HV_NANO100_TIME;

/* 14498 */
typedef _HV_EVENTLOG_MESSAGE_PAYLOAD* PHV_EVENTLOG_MESSAGE_PAYLOAD;

/* 14695 */
typedef unsigned int HAL_HV_VIRTUAL_PROCESSOR_INDEX;

/* 14792 */
typedef unsigned __int16 HV_STATUS;

/* 14929 */
typedef const _HV_LOGICAL_PROCESSOR_REGISTER_ASSOC* PCHV_LOGICAL_PROCESSOR_REGISTER_ASSOC;

/* 15403 */
typedef unsigned __int64 HV_DEVICE_VA;

/* 15502 */
typedef unsigned int HV_LOGICAL_DEVICE_ID;

/* 15601 */
typedef _HV_LOGICAL_PROCESSOR_REGISTER_VALUE* PHV_LOGICAL_PROCESSOR_REGISTER_VALUE;

/* 15972 */
typedef unsigned __int16* PHV_PCI_RID;

/* 16131 */
typedef const _HV_LOGICAL_PROCESSOR_REGISTER_ID* PCHV_LOGICAL_PROCESSOR_REGISTER_ID;

/* 16323 */
typedef unsigned int HV_DEVICE_DOMAIN_ID;

/* 16379 */
typedef unsigned int* PHAL_HV_VIRTUAL_PROCESSOR_INDEX;

/* 16381 */
typedef unsigned __int64* PHV_PARTITION_ID;

/* 16410 */
typedef _HV_REGISTER_VSM_CAPABILITIES* PHV_REGISTER_VSM_CAPABILITIES;

/* 16480 */
typedef _PPM_HV_STATS* PPPM_HV_STATS;

/* 16532 */
typedef unsigned __int64* PHV_NANO100_TIME;

/* 16860 */
typedef unsigned int* PHV_DEVICE_PR_QUEUE_ID;

/* 16930 */
typedef _HV_HYPERCALL_OUTPUT(__stdcall* PHVCALL_HYPERCALL_ROUTINE)(_HV_HYPERCALL_INPUT, unsigned __int64, unsigned __int64);

/* 17174 */
typedef _HV_MCA_FAULTING_LP_MSR* PHV_MCA_FAULTING_LP_MSR;

/* 17210 */
typedef unsigned __int64* PHV_DEVICE_VA;

/* 17334 */
typedef unsigned int HV_SYNIC_SINT_INDEX;

/* 17346 */
typedef unsigned int HV_PASID;

/* 17357 */
typedef unsigned __int16 HV_PCI_SEGMENT;

/* 17517 */
typedef _HV_REGISTER_VP_ASSIST_PAGE* PHV_REGISTER_VP_ASSIST_PAGE;

/* 17519 */
typedef _HV_LOGICAL_PROCESSOR_REGISTER_ASSOC* PHV_LOGICAL_PROCESSOR_REGISTER_ASSOC;

/* 17579 */
typedef unsigned __int64* PHV_ADDRESS_SPACE_ID;

/* 17698 */
typedef unsigned __int64 HV_GPA_PAGE_NUMBER;

/* 17717 */
typedef unsigned __int64 HV_GVA_PAGE_NUMBER;

/* 17746 */
typedef unsigned int HV_PASID_SPACE_ID;

/* 17778 */
typedef _HV_DEVICE_PAGE_REQUEST* PHV_DEVICE_PAGE_REQUEST;

/* 17797 */
typedef int(__stdcall* PHAL_SVM_GET_DEVICE_CAPABILITIES)(unsigned int, _HAL_HV_SVM_DEVICE_CAPABILITIES*);

/* 17914 */
typedef unsigned __int64* PHV_GVA_PAGE_NUMBER;

/* 17998 */
typedef _HV_PCI_ID* PHV_PCI_ID;

/* 18310 */
typedef unsigned int HV_INTERCEPT_ACCESS_TYPE_MASK;

/* 18327 */
typedef unsigned int HV_LOGICAL_PROCESSOR_INDEX;

/* 18478 */
typedef _HV_REGISTER_NESTED_CONTROL* PHV_REGISTER_NESTED_CONTROL;

/* 18487 */
typedef _HV_HYPERCALL_INPUT_PRIVATE* PHV_HYPERCALL_INPUT_PRIVATE;

/* 18536 */
typedef unsigned int* PHV_MAP_GPA_FLAGS;

/* 18603 */
typedef _HV_LOGICAL_PROCESSOR_REGISTER_ID* PHV_LOGICAL_PROCESSOR_REGISTER_ID;

/* 18727 */
typedef unsigned __int64* PHV_GPA;

/* 18782 */
typedef unsigned __int64* PHV_SPA;

/* 19315 */
typedef unsigned __int16 HV_STATS_OBJECT_FLAG;

/* 19588 */
typedef unsigned int* PHV_APIC_ID;

/* 19822 */
typedef _HV_CPU_MANAGEMENT_VERSION_REGISTER* PHV_CPU_MANAGEMENT_VERSION_REGISTER;

/* 19830 */
typedef _HV_X64_XSAVE_AREA* PHV_X64_XSAVE_AREA;

/* 19979 */
typedef _HV_MCUPDATE_DATA_HEADER* PHV_MCUPDATE_DATA_HEADER;

/* 20117 */
typedef unsigned __int64 HV_SPA;

/* 20252 */
typedef unsigned int* PHV_DEVICE_DOMAIN_ID;

/* 20256 */
typedef unsigned int* PHV_PASID;

/* 20531 */
typedef unsigned __int64 HV_SPA_PAGE_NUMBER;

/* 20985 */
typedef _HV_X64_VOLATILE_GP_REGS* PHV_X64_VOLATILE_GP_REGS;

/* 21133 */
typedef unsigned __int64 HV_ADDRESS_SPACE_ID;

/* 21213 */
typedef unsigned __int16 HV_PCI_RID;

/* 21582 */
typedef unsigned __int8* PHV_VTL;

/* 21752 */
typedef unsigned int HV_MAP_GPA_FLAGS;

/* 21836 */
typedef unsigned int* PHV_SYNIC_SINT_INDEX;

/* 21841 */
typedef unsigned int* PHV_PASID_SPACE_ID;

/* 22121 */
typedef _HV_REGISTER_VSM_VP_VTL_CONTROL* PHV_REGISTER_VSM_VP_VTL_CONTROL;

/* 22124 */
typedef unsigned __int64* PHV_GPA_PAGE_NUMBER;

/* 22156 */
typedef unsigned __int64* PHV_SPA_PAGE_NUMBER;

/* 22186 */
typedef unsigned int HAL_HV_LOGICAL_PROCESSOR_INDEX;

/* 22532 */
typedef unsigned int* PHAL_HV_LOGICAL_PROCESSOR_INDEX;

/* 22555 */
typedef unsigned __int8 HV_INTERCEPT_ACCESS_TYPE;

/* 22627 */
typedef unsigned __int8* PHV_IOAPIC_ID;

/* 22722 */
typedef _HV_PCI_PATH* PHV_PCI_PATH;

/* 22762 */
typedef unsigned int* PHV_VP_INDEX;

/* 22773 */
typedef unsigned __int64 HV_PARTITION_ID;

/* 22790 */
typedef unsigned __int64 HV_NANO100_DURATION;

/* 22860 */
typedef unsigned __int64 HV_GVA;

/* 22865 */
typedef unsigned __int64 HV_GPA;

/* 22917 */
typedef const _HV_LOGICAL_PROCESSOR_REGISTER_VALUE* PCHV_LOGICAL_PROCESSOR_REGISTER_VALUE;

/* 22953 */
typedef unsigned __int64* PHV_GVA;

/* 22955 */
typedef unsigned int HV_DEVICE_PR_QUEUE_ID;

/* 22984 */
typedef _HV_DEVICE_PRQ_HEADER* PHV_DEVICE_PRQ_HEADER;
