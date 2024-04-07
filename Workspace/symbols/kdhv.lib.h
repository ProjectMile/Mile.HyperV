/* 20 */
enum _HV_SUBNODE_TYPE : __int32
{
  HvSubnodeAny = 0x0,
  HvSubnodeSocket = 0x1,
  HvSubnodeCluster = 0x2,
  HvSubnodeL3 = 0x3,
  HvSubnodeCount = 0x4,
  HvSubnodeInvalid = 0xFFFFFFFF,
};

/* 26 */
struct $C92FC4024801A24FDE3C12FD3BB730C7
{
  unsigned __int64 GhcbLow : 32;
  unsigned __int64 GhcbHigh : 32;
};

/* 27 */
struct $2917D3E75CF851386C6AE0775BF4AC0B
{
  unsigned __int64 GhcbInfo : 12;
  unsigned __int64 GpaPageNumber : 40;
  unsigned __int64 ExtraData : 12;
};

/* 28 */
union _GHCB_MSR
{
  unsigned __int64 AsUINT64;
  unsigned __int16 AsUINT16[4];
  $C92FC4024801A24FDE3C12FD3BB730C7 __s2;
  $2917D3E75CF851386C6AE0775BF4AC0B __s3;
};
