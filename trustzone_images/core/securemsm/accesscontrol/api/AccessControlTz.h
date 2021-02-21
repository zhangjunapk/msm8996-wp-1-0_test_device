#ifndef ACCESS_CONTROL_TZ_H
#define ACCESS_CONTROL_TZ_H

/*===========================================================================
Copyright (c) 2010-2013 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.tz/1.0.3.c1/securemsm/accesscontrol/api/AccessControlTz.h#1 $
$DateTime: 2016/12/02 01:46:26 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/14/10   tk      First version.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>
#include "tz_syscall_pub.h"
#include "tzbsp_syscall.h"
#include <HALxpu2.h>
#include "ACCommon.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define MEMORY_OWNERSHIP_TABLE_BUFFER_SIZE               0x180000
#define MEMORY_OWNERSHIP_TABLE_BUFFER_MAX_IDX            0x180000
#define PARITY_BUFFER_SIZE                             0x30000
#define PARITY_BUFFER_MAX_IDX                          0x30000 
#define MAGIC_COOKIE                                   0x41473ACD


#define TZBSP_XPU_ENABLE          0x01 /**< Enables an XPU. */
#define TZBSP_XPU_NO_INTERRUPTS   0x02 /**< Disables XPU error interrupts. */
#define TZBSP_XPU_MODEM_PROT      0x04 /**< Marks modem only items. */
#define TZBSP_XPU_SEC             0x08 /**< Secure partition */
#define TZBSP_XPU_NON_SEC         0x10 /**< Non Secure partition */
#define TZBSP_XPU_UMR_MSACLROE    (1 << 5) /**< MSA unmapped read-access  */
#define TZBSP_XPU_UMR_MSACLRWE    (1 << 6) /**< MSA unmapped read/write-access  */
#define TZBSP_XPU_CR_MSAE         (1 << 7) /**< Check MSA bit for non-secure registers */

#define TZBSP_RWGE                0x0100 /**< Read/write global enable. */
#define TZBSP_ROGE                0x0200 /**< Read-only global enable. */
#define TZBSP_RWE                 0x0400 /**< Read/write VMID enable. */
#define TZBSP_ROE                 0x0800 /**< Read-only VMID enable. */
#define TZBSP_VMIDCLROE           0x1000 /**< VMID based Read-Only enable for Secure/MSA resource. */
#define TZBSP_VMIDCLRWE           0x2000 /**< VMID based Read-Write enable for Secure/MSA resource. */
#define TZBSP_MSACLROE            0x4000 /**< MSA Read-only enable for secure partitions. */
#define TZBSP_MSACLRWE            0x8000 /**< MSA Read-Write enable for secure partitions. */

#define TZBSP_XPU_READ_ACCESS     1 /**< Read only access */
#define TZBSP_XPU_RW_ACCESS       2 /**< Read/Write access */
#define TZBSP_XPU_WRITE_ACCESS    3 /**< Write only access */

#define TZBSP_XPU_DYN_AREA_CERT   1 /**< Dynamic area ID for PIL certificate. */

/* EBI channel interleaving related constants. */
#define TZBSP_EBI_CH_NONE             0x0
#define TZBSP_EBI_CH_0                0x1
#define TZBSP_EBI_CH_1                0x2
#define TZBSP_EBI_CH_BOTH             0x3 /* Interleaved. */

#define TZBSP_BLIST_DEVICE_MEMORY       0       /* Non-DDR memory, set at boot */
#define TZBSP_BLIST_DEVICE_MEMORY1      1       /* Device Memory, set at boot. */
#define TZBSP_BLIST_UNUSED              2       /* Unused */
#define TZBSP_BLIST_SECCHANNEL_MSS      3       /* MSS Secure Channel */
#define TZBSP_BLIST_SECCHANNEL_LPASS    4       /* LPASS Secure Channel */
#define TZBSP_BLIST_TZ_STATIC_MEMORY    5       /* Static Memory . */
#define TZBSP_BLIST_ALLOC_0             6       /* Dynamically allocated. */
#define TZBSP_BLIST_ALLOC_1             7       /* Dynamically allocated. */
#define TZBSP_BLIST_ALLOC_2             8       /* Dynamically allocated. */
#define TZBSP_BLIST_ALLOC_3             9       /* Dynamically allocated. */
#define TZBSP_BLIST_ALLOC_4             10      /* Dynamically allocated. */
#define TZBSP_BLIST_ALLOC_5             11      /* Dynamically allocated. */
#define TZBSP_BLIST_FIXED_SEC_DDR       12      /* Fixed secure DDR, static */
#define TZBSP_BLIST_SHARED_IMEM         13      /* Shared imem, static. */
#define TZBSP_BLIST_TZ_DDR              14      /* Statically allocated. */
#define TZBSP_BLIST_PIL_ALLOC_0			15		/* Dynamically allocated. */
#define TZBSP_BLIST_PIL_ALLOC_1			16		/* Dynamically allocated. */
#define TZBSP_BLIST_PIL_ALLOC_2			17		/* Dynamically allocated. */
#define TZBSP_BLIST_PIL_ALLOC_3			18		/* Dynamically allocated. */	
#define TZBSP_BLIST_PIL_ALLOC_4         19      /* Dynamically allocated. */


/* Just adding temporarily so compilation works: REMOVEME*/
#define TZBSP_BLIST_LPASS   TZBSP_BLIST_PIL_ALLOC_0
#define TZBSP_BLIST_VIDEO   TZBSP_BLIST_PIL_ALLOC_1
#define TZBSP_BLIST_WLAN    TZBSP_BLIST_PIL_ALLOC_2
#define TZBSP_BLIST_VPU     TZBSP_BLIST_PIL_ALLOC_3
#define TZBSP_BLIST_GPU     TZBSP_BLIST_PIL_ALLOC_4
#define TZBSP_BLIST_LPASS_DY_HEAP TZBSP_BLIST_ALLOC_5


/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

struct _ACMemoryVmInfo
{
    uint64 uStart;
    uint32 uSize;
    uint32 uReadVmMask;
    uint32 uWriteVmMask;
};

typedef struct _ACMemoryVmInfo ACMemoryVmInfo;

struct _ACPagesInfo
{
    uint32 uNumExclusivePages;
    uint32 uNumSharedPages;
};

typedef struct _ACPagesInfo ACPagesInfo;

/**
 * Resource group configuration for MPUs. All MPUs are multi-VMID.
 */
typedef struct tzbsp_mpu_rg_s
{
  uint16 index;      /* Index of the MPU resource group. */
  /** XPU status bits, currently \c TZBSP_XPU_ENABLE, \c
   * TZBSP_XPU_NO_INTERRUPTS, \c TZBSP_XPU_SEC, \c TZBSP_XPU_NON_SEC and
   * \c TZBSP_XPU_MODEM_PROT are supported.
   */
  uint16 flags;
  uint32 read_vmid;  /* VMIDs able to read this partition. */
  uint32 write_vmid; /* VMIDs able to write this partition. */
  uint64 start;  /* Start of the partition. */
  uint64 end;    /* End of the partition, not included in the range */
} tzbsp_mpu_rg_t;

/**
 * Resource group configuration for APUs/RPUs. Depending on APU/RPU, a resource
 * group is single VMID or multi VMID.
 */
typedef struct tzbsp_rpu_rg_s
{
  /** Index of the APU/RPU resource group. */
  uint16 index;
  /**
   * Valid for single VMID resource groups only. Bits \c TZBSP_RWGE and \c
   * TZBSP_ROGE allow defining read/write global enable and read-only global
   * enable. Bit \c TZBSP_RWE enables the read/write access VMID(s). Bit \c
   * TZBSP_ROE enables the read access VMID(s).
   */
  uint16 flags;
  /**
   * For multi VMID resource groups contains a bitmap of VMIDs that can read
   * the resource. For single VMID resource groups contains a VMID value that
   * can read the resource.
   */
  uint32 read_vmid;
  /**
   * For multi VMID resource groups contains a bitmap of VMIDs that can
   * read/write the resource. For single VMID resource groups contains a VMID
   * value that can read/write the resource.
   */
  uint32 write_vmid;
} tzbsp_rpu_rg_t;

/**
 * Root level structure for XPU configuration.
 */
typedef struct
{
  /** Physical base address of the XPU. */
  uintptr_t phys_addr;
  /** Index of the XPU, @see \c HAL_xpu_XPUType. */
  uint16 id;
  /** XPU status bits, currently \c TZBSP_XPU_ENABLE, \c
   * TZBSP_XPU_NO_INTERRUPTS and \c TZBSP_XPU_MODEM_PROT are supported.
   */
  uint16 flags;
  /** Read access VMIDs for unmapped area */
  uint32 unmapped_rvmid;
  /** Write access VMIDs for unmapped area */
  uint32 unmapped_wvmid;
  /** Superusers */
  uint32 superuser_vmid;
  /** Number of configured resource groups. */
  uint16 nrg;
  union
  {
    const void* any;           /* A dummy to keep compiler happy. */
    const tzbsp_rpu_rg_t* rpu; /* Can be NULL. */
    const tzbsp_mpu_rg_t* mpu; /* Can be NULL. */
  } rg;
} tzbsp_xpu_cfg_t;

/**
 * Root level structure for QRIB configuration.
 */
typedef struct
{
  uint64 xpu2_qrib_init_addr; /* *_QRIB_XPU2_INIT register address */
  uint64 xpu2_qrib_acr_addr;  /* *_QRIB_XPU2_ACR register address */
  uint64 xpu2_qrib_vmid_en_init_addr; /* *_QRIB_VMIDEN_INIT register address */
  uint8 nsen_init; /* Value of *_XPU2_NSEN_INIT field in *_QRIB_XPU2_INIT register */ 
  uint8 en_tz;  /* Value of *_XPU2_EN_TZ field in *_QRIB_XPU2_INIT register */
  uint32 xpu_acr_vmid; /* Value of *_XPU2_ACR field in *_QRIB_XPU2_ACR register */
  uint8 vmiden_init;   /* Value of *_XPU2_VMIDEN_INIT field in *_QRIB_VMIDEN_INIT register */
  uint32 vmiden_init_en_hv;   /* Value of *_XPU2_VMIDEN_INIT_EN_HV field in *_QRIB_VMIDEN_INIT register */ 
}tzbsp_qrib_cfg_t;

typedef enum
{
  XPU_DISABLE_NONE,
  XPU_DISABLE_NON_MSS,
  XPU_DISABLE_ALL
} xpu_level_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
@brief ACInit - Initializes AC static configs 
@return AC_SUCCESS on success, failure values on Failure
*/
int ACTzInit(void);

#if 0
/**
 * Converts 16-bit VMID read/write bitmasks to 32-bit access bitmask for XPU
 * HAL API, which uses 2-bits per VMID for read/write access bits.
 *
 * @param read_vmids  VMID bitmap for read access.
 *
 * @param write_vmids VMID bitmap for write access.
 *
 * @return The expanded access bitmap, 2-bits per VMID.
 */
uint32 tzbsp_vmids_to_perm(uint16 read_vmids, uint16 write_vmids);
#endif

/**
 * Locks an EBI1 memory region and enables it as a secure area in the
 * blacklist.
 *
 * @param [in] id  The area to be locked. Must be one of the blacklist
 *                 item IDs. Currently \c TZBSP_BLIST_MSS and
 *                 \c TZBSP_BLIST_LPASS are supported.
 * @param [in] start  Start address of the region to be locked.
 * @param [in] end    End address of the region to be locked.
 *
 * @return Zero on success, otherwise an error code.
 */
int tzbsp_xpu_lock_area(uint32 id, uintnt start, uintnt end,
                               uint32 rvmid, uint32 wvmid);

/**
 * Unlocks an EBI1 memory region and disables it as a secure area in the
 * blacklist.
 *
 * @param [in] id  The area to be unlocked. Must be one of the blacklist
 *                 item IDs. Currently \c TZBSP_BLIST_MSS and
 *                 \c TZBSP_BLIST_LPASS are supported.
 *
 * @return Zero on success, otherwise an error code.
 */
int tzbsp_xpu_unlock_area(uint32 id);

/**
 * Dynamically reconfigures an RPU/APU resource group VMID assignment. If the
 * configuration is for secure partition, then setting \c TZBSP_ROGE in the RPU
 * flags will enable \c VMIDCLROE and setting \c TZBSP_RWGE in the RPU flags
 * will enable \c VMIDCLRWE.
 *
 * @param [in] xpu_id   HAL ID of the RPU/APU.
 * @param [in] rpu      The RPU to reconfigure
 * @param [in] sec      If \c TRUE, then partition is configured as secure
 *                      partition. If \c FALSE, then partition is configured
 *                      as VMID based partition.
 *
 * @return Zero on success, otherwise an error code.
 */
int tzbsp_rpu_reconfigure(uint32 xpu_id, const tzbsp_rpu_rg_t *rpu,
                          boolean sec);

/**
 * Dynamically reconfigures an RPU/APU resource group VMID and domain assignment. 
 * This api is an extension to tzbsp_rpu_reconfigure() api. This API can be used
 * to assign the domain TZBSP_XPU_MODEM_PROT  or  TZBSP_XPU_SEC or TZBSP_XPU_NON_SEC
 * to a particular resource group or partition. 
 * Note : Domain cannot be changed by TZ if it is already TZBSP_XPU_MODEM_PROT.
 *
 * @param [in] xpu_id   HAL ID of the RPU/APU.
 * @param [in] rpu      The RPU to reconfigure
 * @param [in] domain   TZBSP_XPU_MODEM_PROT  or  TZBSP_XPU_SEC or TZBSP_XPU_NON_SEC
 *
 * @return Zero on success, otherwise an error code.
 */
int tzbsp_rpu_reconfigure_ext(uint32 xpu_id, const tzbsp_rpu_rg_t *rpu,
                              uint32 domain);


/**
 * Locks a dynamic XPU partition.
 *
 * @param [in] area_id  Dynamic area id, one of TZBSP_XPU_DYN_AREA_*.
 * @param [in] start    Start address of the dynamic area. Alignment is
 *                      dependent on the DDR memory MPU configuration at HW
 *                      level.
 * @param [in] end      End address of the dynamic area, exclusive of the
 *                      memory range.  Alignment is dependent on the DDR memory
 *                      MPU configuration at HW level.
 *
 * @return \c E_SUCCESS if successful, error code otherwise.
 */
int tzbsp_mpu_lock_dyn_area(uint32 area_id, uintnt start, uintnt end);

/**
 * Unlocks a dynamic XPU partition.
 *
 * @param [in] area_id  Dynamic area id, one of TZBSP_XPU_DYN_AREA_*.
 *
 * @return \c E_SUCCESS if successful, error code otherwise.
 */
int tzbsp_mpu_unlock_dyn_area(uint32 area_id);

/**
 * Syscall API to enable/disable xpu violations becoming error fatals
 * This can also be used to check if xpu violations are currently error fatals
 * or not by sending \c TZ_XPU_VIOLATION_ERR_FATAL_NOOP as the parameter
 * TZ may choose to force enable/disable xpu violations as error fatals by
 * default. It may also choose to disallow HLOS from overriding this
 * configuration. So, HLOS must always check the output parameter (enabled)
 * to see the current behavior and the return code to see if it was allowed to
 * carry out the operation (-E_NOT_SUPPORTED is returned if HLOS isn't allowed
 * to change the behavior).
 *
 * @param [in] config     Enable/Disable/Noop
 * @param [in] spare      Unused
 *
 * @param[out] status     Enable/Disable
 *
 * @param [in] buf_size_sz   Size of the response buffer.
 *
 * @return  Zero on success.
 *          Negative error code otherwise.
 */
int tzbsp_xpu_config_violation_err_fatal(
                               tz_xpu_violation_err_fatal_t  config,
                               uint32                        spare,
                               tzbsp_smc_rsp_t               *rsp );
/**
 * API to configure a MPU partition 
 *
 * @param [in] xpu_id   HAL ID of the MPU.
 * @param [in] mpu      The MPU to reconfigure
 *
 * @return  Zero on success.
 *          Negative error code otherwise.
 */
int tzbsp_xpu_mpu_reconfigure(uint32 xpu_id, const tzbsp_mpu_rg_t *mpu); 


/**
 * API to read if xPU violation are treated as fatal or not 
 *
 * @return  tz_xpu_violation_err_fatal_t status
 *          
 */
tz_xpu_violation_err_fatal_t tzbsp_xpu_get_violation_err_fatal_status(void);

/**
 * API to disable a particular XPU
 *
 * @param [in] address  Base address of the XPU to disable
 *
 * @return  Zero on success.
 *          Negative error code otherwise.
 */
int tzbsp_xpu_disable(uintptr_t xpu_base_address);

/**
 * Restore full VMIDMT configuration for all the VMIDMT instances
 * corresponding to a device.
 */
int ACVmidmtRestoreDevice(tz_device_e_type device);

int ACXpuRestoreConfig(tz_device_e_type device);

/**
  @brief ACPrintXpuLogs - Print XPU logs without error fatal 
  @return AC_SUCCESS on success, failure values on Failure
  */
uint32 ACPrintXpuLogs(void);

/**
  @brief ACLogMutexLock - Grabs the lock 
  @return AC_SUCCESS on success, failure values on Failure
  */
uint32 ACLogMutexLock(void);

/**
  @brief ACLogMutexUnLock - Grabs the lock 
  @return AC_SUCCESS on success, failure values on Failure
  */
uint32 ACLogMutexUnLock(void);

/**
 * @brief ACTZAssign - Maintains the bookkeeping in TZ for HLOS owned memory
 * @param [in] IPAinfo              The mappings information
 * @param [in] IPAinfolistsize      Size of it mappings
 * @param [in] sourceVMlist         Source VM list
 * @param [in] srcVMlistsize        Size of the source VM list
 * @param [in] destVMlist           Destination List
 * @param [in] dstVMlistsize        Destination List size
 * @return AC_SUCCESS on success, failure values on Failure
 */
uint64 ACTZAssign(const hyp_memprot_ipa_info_t                 *IPAinfo,
        uint32                                       IPAinfolistsize,
        const uint32                                 *sourceVMlist,
        uint32                                       srcVMlistsize,
        const hyp_memprot_dstVM_perm_info_t          *destVMlist,
        uint32                                       dstVMlistsize);

/**
 * @brief ACGetMemoryVmPerm - Gets the permission for the particular mapping & VM
 * @param [in] uStart              Start address
 * @param [in] uSize               Size 
 * @param [in] uVm                 VM whose permission is to be found
 * @param [out] pRetVal            Returns the permission here
 * @return AC_ERROR_CODE
 */
uint32 ACGetMemoryVmPerm(uint64 uStart, uint64 uSize, uint32 uVm, uint32 *pRetVal);


/**
 * @brief ACMarkMemoryInUse - Mark a particular region in use or not in use by TZ
 * @param [in] uStart              Start address
 * @param [in] uSize               Size 
 * @param [in] uInUse              Boolean to set in use or not in use
 * @return AC_SUCCESS on success, failure values on Failure
 */
uint32 ACMarkMemoryInUse(uint64 uStart, uint64 uSize, bool32 uInUse);

/**
 * @brief ACGetMemoryPerm - Gets a list of information for the memory range passed
 * @param [in] uStart              Start address
 * @param [in] uSize               Size 
 * @param [in] pVMInfo             pointer to struct ACMemoryVmInfo, where the results will be stored (Initialized to 0)
 * @param [in] uVMInfoSize         size of the array passed
 * @return Error code, if the size of the struct is not enough to populate the information
 */
uint32 ACGetMemoryPerm(uint64 uStart, uint64 uSize, ACMemoryVmInfo *pVMInfo, uint32 uVMInfoSize);


/**
 * @brief ACGetNumPagesOwnedByVM - Returns the number of pages owned by the VM
 * @param [in] uVm                 VM
 * @param [in] pPagesInfo          pointer to struct ACPagesInfo, where the results will be stored
 * @return AC error codes
 */
uint32 ACGetNumPagesOwnedByVM(uint32 uVm, ACPagesInfo *pPagesInfo);

/**
 * @brief ACIsMemoryOwnedByVMs - Used to check if VMs own the region or not, also can check for exclusivity
 * @param [in] uStart              Start address
 * @param [in] uSize               Size 
 * @param [in] uVmMask             VM Mask
 * @param [in] bExclusive          Checks if memory is exclusively owned by VMs specified in uVmMask
 * @param [out] pRetVal            TRUE or FALSE depending on the result
 * @return AC_ERROR_CODE
 */
uint32 ACIsMemoryOwnedByVMs(uint64 uStart,
        uint64 uSize,
        uint32 uVmMask,
        boolean bExclusive,
        boolean *pRetVal);

/**
 * @brief ACIsMemoryOwnedByAnyVMs - Used to check if any specified VMs own the region or not, also can check for exclusivity ownership
 * @param [in] uStart              Start address
 * @param [in] uSize               Size 
 * @param [in] uVmMask             VM Mask (1<<VM1) | (1<<VM2) 
 * @param [in] bExclusive          Check for exclusive ownership flag
 * @param [out] pRetVal            TRUE or FALSE depending on the result
 * @return AC_ERROR_CODE
 */
uint32 ACIsMemoryOwnedByAnyVMs(uint64 uStart,
        uint64 uSize,
        uint32 uVmMask,
        boolean bExclusive,
        boolean *pRetVal);

#endif /* ACCESS_CONTROL_TZ_H */
