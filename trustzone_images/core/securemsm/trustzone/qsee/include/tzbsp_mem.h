#ifndef TZBSP_MEM_H
#define TZBSP_MEM_H

/**
@file tzbsp_mem.h
@brief Provide memory bound checking and managment
*/

/*===========================================================================
   Copyright (c) 2010 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                            EDIT HISTORY FOR FILE

  $Header: //components/rel/core.tz/1.0.3.c1/securemsm/trustzone/qsee/include/tzbsp_mem.h#1 $
  $DateTime: 2016/12/02 01:46:26 $
  $Author: pwbldsvc $

when       who      what, where, why
--------   ---      ------------------------------------
06/01/12   sg       Added tzbsp_mem_is_tagged_area API
10/18/10   cap      Renamed file from tzbsp_sys.h to tzbsp_mem.h
05/24/10   tk       Initial version.

===========================================================================*/

/*------------------------------------------------------------------------
                            PUBLIC TYPES
------------------------------------------------------------------------*/

/*===========================================================================

                              DEFINES

===========================================================================*/
#include <stdint.h>
#include <comdef.h>
#include "tz_syscall_pub.h"
#include "IxErrno.h"
#include "tzbsp_syscall.h"

/**
 * Macro \c TZBSP_ALWAYS is an alias for assert. By default it is
 * compiled as empty. Use of \c TZBSP_ALWAYS can be enabled by
 * defining \c TZBSP_STRICT compile time.
 */
#ifdef TZBSP_STRICT
#define TZBSP_ALWAYS(x) assert(x)
#else
#define TZBSP_ALWAYS(x)
#endif

/*@}*/

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

#define TZBSP_ROUNDUP(type, val, multiple) (((val) + (multiple)-1) & \
               ~(type)((multiple)-1))

#define TZBSP_ROUNDDOWN(type, val, multiple) ((val) & \
               ~(type)((multiple)-1))

#define TZBSP_MIN(a,b) ((a)>(b)?(b):(a))
#define TZBSP_MAX(a,b) ((a)>(b)?(a):(b))
#define TZBSP_DIFF(a,b) ((a)>(b)?(a)-(b):(b)-(a))

#define TZBSP_ARRAY_SIZE(xx) (sizeof(xx) / sizeof((xx)[0]))

#define TZBSP_PAGE_4K           4096
/* Clears the lowest 12 bits on xx. */
#define TZBSP_FLOOR_4K(xx)      (((uint64_t) (xx)) & ~(TZBSP_PAGE_4K-1))

/* Clears all apart from the lowest 12 bits on xx. */
#define TZBSP_PAGE_4K_OFFSET(xx) (((uintnt) (xx)) & (TZBSP_PAGE_4K-1))

#define TZBSP_SECTION_1M        0x100000
#define TZBSP_FLOOR_1M(xx)      ((uint64_t) (xx) & ~(TZBSP_SECTION_1M-1))

#define TZBSP_SECTION_2M        0x200000
#define TZBSP_FLOOR_2M(xx)      ((uint64_t) (xx) & ~(TZBSP_SECTION_2M-1))

#define TZBSP_FLOOR(xx,size)   (((uint64_t)(xx)) & ~((size)-1))

/* Clears all apart from the lowest 20 bits on xx. */
#define TZBSP_SECTION_1M_OFFSET(xx) ((uint64_t) (xx) & (TZBSP_SECTION_1M-1))

#define TZBSP_PAGE_1K           1024
/* Clears the lowest 10 bits on xx. */
#define TZBSP_FLOOR_1K(xx)      ((xx) & ~(TZBSP_PAGE_1K-1))

#define TZBSP_ALIGN_4BYTE(xx)   ((xx) & ~0x3)

/**
 * Structure for mapping the DDR regions, which will be used for DDR pagetable
 * entries, and verifying pointers/structures reside in DDR.
 */
typedef struct tzbsp_ddr_region_s
{
  /* Start address of the DDR region */
  uint64 start;
  /* Size of the memory region, in bytes */
  uint64 size;
} tzbsp_ddr_region_t;

/**
 * Prints the arguments as \c tzbsp_log would and starts waiting in an infinite
 * loop.
 */
void tzbsp_abort(const char* fmt, ...);

/**
 * Tests whether all of the range [\c start, \c start + \c len] 
 * is owned by HLOS. \c NULL is a valid value for \c start, 
 * because physical addressing is used. 
 *
 * @param [in] start Start of the memory range, physical address,
 * included in the range.
 *
 * @param [in] len Length of the memory range in bytes.
 *
 * @return \c TRUE if the entire area is owned by HLOS.
 * \c FALSE otherwise. 
 */
boolean tzbsp_is_hlos_range(const void* start, uint64 len);

/**
 * Tests whether all of the range [\c start, \c start + \c len] 
 * is owned by HYP. \c NULL is a valid value for \c start, 
 * because physical addressing is used. 
 *
 * @param [in] start Start of the memory range, physical address,
 * included in the range.
 *
 * @param [in] len Length of the memory range in bytes.
 *
 * @return \c TRUE if the entire area is owned by HYP.
 * \c FALSE otherwise. 
 */
boolean tzbsp_is_hyp_range(const void* start, uint64 len);

/**
 * Tests whether all of the range [\c start, \c start + \c len] 
 * is owned by PIL or Subsystems. \c NULL is a valid value for 
 * \c start, because physical addressing is used. 
 *
 * @param [in] start Start of the memory range, physical address,
 * included in the range.
 *
 * @param [in] len Length of the memory range in bytes.
 *
 * @return \c TRUE if the entire area is owned by PIL or 
 *         Subsystems.
 * \c FALSE otherwise. 
 */
boolean tzbsp_is_pil_range(const void* start, uint64 len);

/**
 * Tests whether all of the range [\c start, \c start + \c len] 
 * is owned by TZ. \c NULL is a valid value for \c start, 
 * because physical addressing is used. 
 *
 * @param [in] start Start of the memory range, physical address,
 * included in the range.
 *
 * @param [in] len Length of the memory range in bytes.
 *
 * @return \c TRUE if the entire area is owned by TZ.
 * \c FALSE otherwise. 
 */
boolean tzbsp_is_tz_range(const void* start, uint64 len);

/**
 * Tests whether all of the range [\c start, \c start + \c len] is in
 * secure memory. This is a convenience function to access \c
 * tzbsp_is_s_area. \c NULL is a valid value for start, because
 * physical addressing is used.
 *
 * @param [in] start Start of the memory range, physical addrss,
 * included in the range.
 *
 * @param [in] len Length of the memory range in bytes.
 *
 * @return \c TRUE if the entire area is in secure memory. \c FALSE if
 * the area contains non-secure memory.
 */
boolean tzbsp_is_s_range(const void* start, uint64 len);

/**
 * Initialize TZBSP heap.
 */
void tzbsp_heap_init(void);

/**
 * Allocates memory from TZBSP heap.
 *
 * @param [in] The amount of memory bytes to allocate.
 *
 * @return A valid pointer to the allocated memory if allocation
 * succeeded, \c NULL if allocation failed. The returned address is
 * physical.
 */
void* tzbsp_malloc(uint64_t size);

/**
 * Frees memory allocated from TZBSP heap.
 *
 * @param [in] The memory buffer to be deallocated, physical
 * address. If \c NULL, then freeing is ignored.
 */
void tzbsp_free(void* ptr);

/**
 * Takes a virtual memory buffer and converts it in to an iovec list of
 * physical memory pointers
 *
 * @param [in]  a virtual address
 *
 * @param [in]  the length of the virtual buffer to examine
 *
 * @param [out] Returns the virtual address as an array of type ioVec. The
 *              calling function needs to have allocated the ioVecPhys for
 *              population by this function.
 *
 * @return E_SUCCESS if successful
 *         E_INVALID_ARG if ioVecPhys is invalid
 *         E_FAILURE otherwise
 */
int tzbsp_vtop_iovec(uint64 v_addr, uint32 length, const void *pIoVecPhys);

/**
   Checks to see if the given memory range is completely within the
   range of DDR

   @param[in] start_ptr Start of the address range to check
   @param[in] len       Length of the address range to check

   @return \c TRUE iff the given memory region is contained in the area.
           \c FALSE otherwise.

*/
boolean tzbsp_ddr_contains_area(const void* start_ptr, uint32 len);

/**
   Populates the start and end address of the DDR region

   @param[in] start     Pointer to populate the start address in
   @param[in] end       Pointer to populate the end address in

   @return \c TRUE iff the DDR start and end address were populated
           \c FALSE otherwise.

*/
boolean tzbsp_ddr_get_range(uint64 * start, uint64 * end);

/**
 * Takes an array of DDR regions and coalesces them into the smallest set of
 * continuous regions
 *
 * @param [in/out]  array of DDR regions, which will be merged in-place
 *
 * @param [in]      number of elements in the DDR regions array
 *
 * @return Number of remaining DDR regions
 */
uint32 tzbsp_coalesce_ddr_regions( tzbsp_ddr_region_t *regions, uint32 num_regions );

/**
   Takes a given memory memory mapped peripheral type and maps it into
   the virtual address space

   @param  mmp Enumerated value of memory mapped peripheral to map

   @return \c E_SUCCESS if mapping was successful
           \c E_FAILURE if mapping was not successful
 */
int tzbsp_mem_map_device(uint32 mmp);

/**
   Takes a given memory memory mapped peripheral type and unmaps it
   from the virtual address space

   @param  mmp Enumerated value of memory mapped peripheral to unmap

   @return \c E_SUCCESS if mapping was successful
           \c E_FAILURE if mapping was not successful
 */
int tzbsp_mem_unmap_device(uint32 mmp);

/**
   This unnmaps all peripherals from from the virtual address space

   @return \c E_SUCCESS if mapping was successful
           \c E_FAILURE if mapping was not successful
 */
int tzbsp_mem_unmap_all_devices(void);

/**
   This initializes the DDR translation tables and reads the DDR
   region configuration information
 */
int tzbsp_ddr_init(void);

/**
 * Tests whether Shared Buffer from non-secure domain or not.
 *
 * @param [in] start Start of the memory range, physical address,
 * included in the range.
 *
 * @param [in] end Length of the memory range in bytes.
 *
 * @return \c TRUE if shared buffer from non-secure domain. \c
 * FALSE if shared buffer from secure domain.
 */
boolean tzbsp_validate_security_for_shared_buffer(const void* start, uint64 len);

#endif /* TZBSP_MEM_H */
