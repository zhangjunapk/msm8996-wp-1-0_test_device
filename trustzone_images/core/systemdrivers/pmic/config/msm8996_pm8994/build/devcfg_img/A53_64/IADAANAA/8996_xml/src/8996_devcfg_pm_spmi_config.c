#include "../src/devcfg_tz_config.h"
#include "../src/devcfg_pm_spmi_config.h"
typedef unsigned long uintptr_t;
typedef long intptr_t;
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;
typedef long intmax_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef unsigned long uintmax_t;
typedef int8_t int_fast8_t;
typedef int64_t int_fast64_t;
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_fast8_t;
typedef uint64_t uint_fast64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef unsigned char boolean;
typedef uint32_t bool32;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef unsigned long uintnt;
typedef uint8_t byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned char uint1;
typedef unsigned short uint2;
typedef unsigned int uint4;
typedef signed char int1;
typedef signed short int2;
typedef long int int4;
typedef signed int sint31;
typedef signed short sint15;
typedef signed char sint7;
typedef uint16 UWord16 ;
typedef uint32 UWord32 ;
typedef int32 Word32 ;
typedef int16 Word16 ;
typedef uint8 UWord8 ;
typedef int8 Word8 ;
typedef int32 Vect32 ;
      typedef long long int64;
      typedef unsigned long long uint64;
        typedef struct __attribute__((packed))
        { uint16 x; }
        unaligned_uint16;
        typedef struct __attribute__((packed))
        { uint32 x; }
        unaligned_uint32;
        typedef struct __attribute__((packed))
        { uint64 x; }
        unaligned_uint64;
        typedef struct __attribute__((packed))
        { int16 x; }
        unaligned_int16;
        typedef struct __attribute__((packed))
        { int32 x; }
        unaligned_int32;
        typedef struct __attribute__((packed))
        { int64 x; }
        unaligned_int64;
  extern dword rex_int_lock(void);
  extern dword rex_int_free(void);
    extern dword rex_fiq_lock(void);
    extern void rex_fiq_free(void);
   extern void rex_task_lock( void);
   extern void rex_task_free( void);
static inline uint8 spmiEncodeVSid(uint8 busId, uint8 slaveId) {
    return (busId << 4) | (slaveId & 0x0F);
}
static inline void spmiDecodeVSid(uint8 vSlaveId, uint8* busId, uint8* slaveId) {
    if(busId) *busId = vSlaveId >> 4;
    if(slaveId) *slaveId = vSlaveId & 0x0F;
}
typedef enum
{
    SPMI_SUCCESS,
    SPMI_FAILURE_BUS_BUSY,
    SPMI_FAILURE_BUS_DISABLED,
    SPMI_FAILURE_COMMAND_NOT_SUPPORTED,
    SPMI_FAILURE_COMMAND_NOT_ALLOWED,
    SPMI_FAILURE_TRANSACTION_FAILED,
    SPMI_FAILURE_TRANSACTION_DENIED,
    SPMI_FAILURE_TRANSACTION_DROPPED,
    SPMI_FAILURE_TRANSACTION_TIMEOUT,
    SPMI_FAILURE_SERIAL_CLK_IS_OFF,
    SPMI_FAILURE_AHB_CLK_IS_OFF,
    SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED,
    SPMI_FAILURE_INVALID_PARAMETER,
    SPMI_FAILURE_INIT_FAILED,
    SPMI_FAILURE_NOT_INITIALIZED,
    SPMI_FAILURE_INVALID_BUFFER,
    SPMI_FAILURE_TOO_MANY_ENTRIES,
    SPMI_FAILURE_NOT_ENOUGH_RGS,
    SPMI_FAILURE_INVALID_BUS_ID,
    SPMI_FAILURE_INVALID_MASTER_ID,
    SPMI_FAILURE_INVALID_SLAVE_ID,
    SPMI_FAILURE_INVALID_ADDRESS,
    SPMI_FAILURE_INVALID_PERIPH_ID,
    SPMI_FAILURE_INVALID_PORT_ID,
    SPMI_FAILURE_INVALID_OWNER,
    SPMI_FAILURE_INVALID_CHAN_NUM,
    SPMI_FAILURE_CHANNEL_RESERVED,
    SPMI_FAILURE_CHANNEL_NOT_FOUND,
    SPMI_FAILURE_MEMORY_NOT_AVAILABLE,
    SPMI_FAILURE_INVALID_TOKEN,
    SPMI_RESULT_MAX
} Spmi_Result;
typedef enum
{
    SPMI_ACCESS_PRIORITY_LOW = 0,
    SPMI_ACCESS_PRIORITY_HIGH = 1,
    SPMI_ACCESS_PRIORITY_COUNT = 2
} Spmi_AccessPriority;
typedef enum
{
    SPMI_COMMAND_RESET,
    SPMI_COMMAND_SLEEP,
    SPMI_COMMAND_SHUTDOWN,
    SPMI_COMMAND_WAKEUP,
    SPMI_COMMAND_COUNT
} Spmi_Command;
typedef void* (*SpmiIsr)(void* ctx, uint32 mask);
typedef Spmi_Result SpmiBus_ResultType;
typedef Spmi_Result SpmiCfg_ResultType;
typedef Spmi_Result SpmiIntrCtlr_ResultType;
typedef Spmi_Command SpmiBus_CommandType;
typedef Spmi_AccessPriority SpmiBus_AccessPriorityType;
typedef struct
{
    uint8 slaveId;
    uint8 periphId;
    uint16 channel;
    uint8 intOwner;
    uint8 periphOwner;
} SpmiBusCfg_ChannelCfg;
typedef struct
{
    uint8 slaveId;
    uint16 address;
} SpmiBusCfg_Ppid;
typedef struct
{
    uint8 pvcPortId;
    Spmi_AccessPriority priority;
    SpmiBusCfg_Ppid* ppids;
    uint32 numPpids;
} SpmiBusCfg_PvcPortCfg;
typedef struct
{
    uint8 owner;
    uint32 startAddr;
    uint32 size;
    uint8 startIdx;
    uint8 endIdx;
} SpmiBusCfg_RGConfig;
Spmi_Result SpmiBusCfg_Init(boolean initHw);
Spmi_Result SpmiBusCfg_DeInit(void);
Spmi_Result SpmiBusCfg_GetChannelInfo(uint8 busId, uint16 channel, uint8* slaveId, uint8* periphId, uint8* owner);
Spmi_Result SpmiBusCfg_GetPeripherialInfo(uint8 busId, uint8 slaveId, uint8 periphId, uint16* channel, uint8* owner);
Spmi_Result SpmiBusCfg_SetDynamicChannelMode(uint8 busId, boolean enabled);
Spmi_Result SpmiBusCfg_ConfigureChannels(SpmiBusCfg_ChannelCfg* entries, uint32 numEntries);
Spmi_Result SpmiBusCfg_ConfigurePeripherals(uint8 busId, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries,
                                            SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount);
Spmi_Result SpmiBusCfg_CalculateRGConfig(uint8 busId, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries,
                                         SpmiBusCfg_RGConfig* rgCfg, uint32* rgCount);
Spmi_Result SpmiBusCfg_ConfigurePvcPort(uint8 busId, const SpmiBusCfg_PvcPortCfg* portCfg);
Spmi_Result SpmiBusCfg_SetPortPriorities(uint8 busId, uint8* ports, uint32 numPorts);
Spmi_Result SpmiBusCfg_SetPVCPortsEnabled(uint8 busId, boolean enable);
typedef SpmiBusCfg_ChannelCfg SpmiCfg_ChannelCfg;
typedef SpmiBusCfg_Ppid SpmiCfg_Ppid;
typedef SpmiBusCfg_PvcPortCfg SpmiCfg_PvcPortCfg;
typedef SpmiBusCfg_RGConfig SpmiCfg_RGConfig;
inline Spmi_Result SpmiCfg_Init(boolean initHw)
{
    return SpmiBusCfg_Init(initHw);
}
inline Spmi_Result SpmiCfg_DeInit(void)
{
    return SpmiBusCfg_DeInit();
}
inline Spmi_Result SpmiCfg_GetChannelInfo(uint16 channel, uint8* slaveId, uint8* periphId, uint8* owner)
{
    return SpmiBusCfg_GetChannelInfo(0, channel, slaveId, periphId, owner);
}
inline Spmi_Result SpmiCfg_GetPeripherialInfo(uint8 slaveId, uint8 periphId, uint16* channel, uint8* owner)
{
    return SpmiBusCfg_GetPeripherialInfo(0, slaveId, periphId, channel, owner);
}
inline Spmi_Result SpmiCfg_SetDynamicChannelMode(boolean enabled)
{
    return SpmiBusCfg_SetDynamicChannelMode(0, enabled);
}
inline Spmi_Result SpmiCfg_ConfigureChannels(SpmiCfg_ChannelCfg* entries, uint32 numEntries)
{
    return SpmiBusCfg_ConfigureChannels(entries, numEntries);
}
inline Spmi_Result SpmiCfg_ConfigurePeripherals(SpmiCfg_ChannelCfg* entries, uint32 numEntries,
                                                SpmiCfg_RGConfig* rgCfg, uint32* rgCount)
{
    return SpmiBusCfg_ConfigurePeripherals(0, entries, numEntries, rgCfg, rgCount);
}
inline Spmi_Result SpmiCfg_CalculateRGConfig(SpmiCfg_ChannelCfg* entries, uint32 numEntries,
                                             SpmiCfg_RGConfig* rgCfg, uint32* rgCount)
{
    return SpmiBusCfg_CalculateRGConfig(0, entries, numEntries, rgCfg, rgCount);
}
inline Spmi_Result SpmiCfg_ConfigurePvcPort(const SpmiCfg_PvcPortCfg* portCfg)
{
    return SpmiBusCfg_ConfigurePvcPort(0, portCfg);
}
inline Spmi_Result SpmiCfg_SetPortPriorities(uint8* ports, uint32 numPorts)
{
    return SpmiBusCfg_SetPortPriorities(0, ports, numPorts);
}
inline Spmi_Result SpmiCfg_SetPVCPortsEnabled(boolean enable)
{
    return SpmiBusCfg_SetPVCPortsEnabled(0, enable);
}
typedef enum {
  PM_APPS_HLOS_OWNER = 0,
  PM_APPS_TZ_OWNER,
  PM_MSS_OWNER,
  PM_LPASS_OWNER,
  PM_RPM_OWNER,
  PM_WCONNECT_OWNER
} pm_periph_owner;
SpmiCfg_ChannelCfg pm_spmi_pheriph_cfg [] =
{
  {0, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x1C, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x28, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x31, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x32, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x34, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x50, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x51, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x52, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x54, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x55, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x58, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x5C, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x5D, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x60, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x61, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x62, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {0, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x72, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x75, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x76, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x77, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x7A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x7B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x7C, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0x7D, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x7E, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x7F, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0x80, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {0, 0xA1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xA2, 0, PM_MSS_OWNER, 0xFF },
  {0, 0xA3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xA4, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xA5, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xA6, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xA7, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC0, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC2, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC4, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC5, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER },
  {0, 0xC6, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC7, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC8, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xC9, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xCA, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xCB, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xCC, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xCD, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xCE, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xCF, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xD0, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xD1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xD2, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xD3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {0, 0xD4, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {0, 0xD5, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {1, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x17, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x19, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x1A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x1C, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x1D, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x1F, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x20, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x22, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x26, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {1, 0x28, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {1, 0x29, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x2B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x32, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0x34, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0x35, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x37, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x41, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x42, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x43, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x45, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x46, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x47, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x48, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {1, 0x49, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {1, 0x4A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x4B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x4C, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x4D, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x4E, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x4F, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x50, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x51, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x52, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x53, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x54, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x55, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x56, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x57, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x58, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x5C, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x5D, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x5E, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x5F, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x80, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0x81, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {1, 0xB0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xB1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xB2, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xB3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xB4, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xB5, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xB6, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {1, 0xBC, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x10, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x11, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x12, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x13, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x14, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x16, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x1B, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x31, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x40, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x41, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x42, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x43, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {2, 0x44, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {2, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x74, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x75, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x76, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x77, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x79, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x7A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x7B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0x7C, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0xA0, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xA1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xA2, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {2, 0xA3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC0, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC2, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC4, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC5, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC6, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC7, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC8, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {2, 0xC9, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {3, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0x17, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER },
  {3, 0x19, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER },
  {3, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0xA1, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0xA2, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {3, 0xB0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xB1, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xB2, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xB3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xB4, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xC0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xD0, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xD3, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xD8, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xD9, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xDC, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {3, 0xDE, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {4, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {4, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {4, 0x24, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {4, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0x76, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0x77, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0x78, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0xA0, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {4, 0xA1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {4, 0xA2, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {4, 0xA3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {5, 0x10, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {5, 0x14, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {5, 0x16, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {5, 0x17, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER },
  {5, 0x19, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER },
  {5, 0x20, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {5, 0x22, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {5, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {6, 0x09, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {6, 0x50, 0, PM_MSS_OWNER, PM_MSS_OWNER },
  {6, 0x54, 0, PM_RPM_OWNER, PM_MSS_OWNER },
  {6, 0x55, 0, PM_RPM_OWNER, PM_MSS_OWNER },
  {6, 0x58, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x59, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x5A, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x5B, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x5C, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x5D, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x5E, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x60, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x61, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {6, 0x62, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER},
  {6, 0x70, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x74, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0x75, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {6, 0xC0, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {6, 0xC1, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {6, 0xC2, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {6, 0xC3, 0, PM_APPS_HLOS_OWNER, 0xFF },
  {7, 0x01, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {7, 0x40, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {7, 0x41, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {14, 0x05, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {14, 0x06, 0, PM_RPM_OWNER, PM_RPM_OWNER },
  {14, 0x08, 0, PM_APPS_HLOS_OWNER, PM_APPS_HLOS_OWNER },
};
uint32 pm_spmi_pheriph_cfg_sz = sizeof(pm_spmi_pheriph_cfg) / sizeof(SpmiCfg_ChannelCfg);
