#ifndef QUPAC_COMMONIDS_H
#define QUPAC_COMMONIDS_H

/*===========================================================================
         Copyright (c) 2015 by QUALCOMM Technologies, Incorporated.  
              All Rights Reserved.
            QUALCOMM Confidential & Proprietary
===========================================================================*/

/*===========================================================================

  EDIT HISTORY FOR FILE


  when       who     what, where, why
  --------   ---     ------------------------------------------------------------
  2/03/15   sk      Created
  =============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>

#define MAX_MINICORE_COUNT 15 // 12 BLSP QUP/UART cores + 3 SSC cores 

#define BLSP1_QUP0_DEV_ACCESS "/dev/buses/qup/blsp1_qup0"
#define BLSP1_QUP1_DEV_ACCESS "/dev/buses/qup/blsp1_qup1"
#define BLSP1_QUP2_DEV_ACCESS "/dev/buses/qup/blsp1_qup2"
#define BLSP1_QUP3_DEV_ACCESS "/dev/buses/qup/blsp1_qup3"
#define BLSP1_QUP4_DEV_ACCESS "/dev/buses/qup/blsp1_qup4"
#define BLSP1_QUP5_DEV_ACCESS "/dev/buses/qup/blsp1_qup5"
#define BLSP2_QUP0_DEV_ACCESS "/dev/buses/qup/blsp2_qup0"
#define BLSP2_QUP1_DEV_ACCESS "/dev/buses/qup/blsp2_qup1"
#define BLSP2_QUP2_DEV_ACCESS "/dev/buses/qup/blsp2_qup2"
#define BLSP2_QUP3_DEV_ACCESS "/dev/buses/qup/blsp2_qup3"
#define BLSP2_QUP4_DEV_ACCESS "/dev/buses/qup/blsp2_qup4"
#define BLSP2_QUP5_DEV_ACCESS "/dev/buses/qup/blsp2_qup5"
#define SSC_QUP0_DEV_ACCESS  "/dev/buses/qup/ssc_qup0"
#define SSC_QUP1_DEV_ACCESS  "/dev/buses/qup/ssc_qup1"
#define SSC_QUP2_DEV_ACCESS  "/dev/buses/qup/ssc_qup2"

#define BLSP1_UART0_DEV_ACCESS "/dev/buses/uart/blsp1_uart0"
#define BLSP1_UART1_DEV_ACCESS "/dev/buses/uart/blsp1_uart1"
#define BLSP1_UART2_DEV_ACCESS "/dev/buses/uart/blsp1_uart2"
#define BLSP1_UART3_DEV_ACCESS "/dev/buses/uart/blsp1_uart3"
#define BLSP1_UART4_DEV_ACCESS "/dev/buses/uart/blsp1_uart4"
#define BLSP1_UART5_DEV_ACCESS "/dev/buses/uart/blsp1_uart5"
#define BLSP2_UART0_DEV_ACCESS "/dev/buses/uart/blsp2_uart0"
#define BLSP2_UART1_DEV_ACCESS "/dev/buses/uart/blsp2_uart1"
#define BLSP2_UART2_DEV_ACCESS "/dev/buses/uart/blsp2_uart2"
#define BLSP2_UART3_DEV_ACCESS "/dev/buses/uart/blsp2_uart3"
#define BLSP2_UART4_DEV_ACCESS "/dev/buses/uart/blsp2_uart4"
#define BLSP2_UART5_DEV_ACCESS "/dev/buses/uart/blsp2_uart5"
#define SSC_UART0_DEV_ACCESS  "/dev/buses/uart/ssc_uart0"
#define SSC_UART1_DEV_ACCESS  "/dev/buses/uart/ssc_uart1"
#define SSC_UART2_DEV_ACCESS  "/dev/buses/uart/ssc_uart2"


#define BLSP1_QUP0_DEV_CONFIG "/dev/buses/qup/blsp1_qup0_cfg"
#define BLSP1_QUP1_DEV_CONFIG "/dev/buses/qup/blsp1_qup1_cfg"
#define BLSP1_QUP2_DEV_CONFIG "/dev/buses/qup/blsp1_qup2_cfg"
#define BLSP1_QUP3_DEV_CONFIG "/dev/buses/qup/blsp1_qup3_cfg"
#define BLSP1_QUP4_DEV_CONFIG "/dev/buses/qup/blsp1_qup4_cfg"
#define BLSP1_QUP5_DEV_CONFIG "/dev/buses/qup/blsp1_qup5_cfg"
#define BLSP2_QUP0_DEV_CONFIG "/dev/buses/qup/blsp2_qup0_cfg"
#define BLSP2_QUP1_DEV_CONFIG "/dev/buses/qup/blsp2_qup1_cfg"
#define BLSP2_QUP2_DEV_CONFIG "/dev/buses/qup/blsp2_qup2_cfg"
#define BLSP2_QUP3_DEV_CONFIG "/dev/buses/qup/blsp2_qup3_cfg"
#define BLSP2_QUP4_DEV_CONFIG "/dev/buses/qup/blsp2_qup4_cfg"
#define BLSP2_QUP5_DEV_CONFIG "/dev/buses/qup/blsp2_qup5_cfg"
#define SSC_QUP0_DEV_CONFIG "/dev/buses/qup/ssc_qup0_cfg"
#define SSC_QUP1_DEV_CONFIG "/dev/buses/qup/ssc_qup1_cfg"
#define SSC_QUP2_DEV_CONFIG "/dev/buses/qup/ssc_qup2_cfg"

#define BLSP1_UART0_DEV_CONFIG "/dev/buses/uart/blsp1_uart0_cfg"
#define BLSP1_UART1_DEV_CONFIG "/dev/buses/uart/blsp1_uart1_cfg"
#define BLSP1_UART2_DEV_CONFIG "/dev/buses/uart/blsp1_uart2_cfg"
#define BLSP1_UART3_DEV_CONFIG "/dev/buses/uart/blsp1_uart3_cfg"
#define BLSP1_UART4_DEV_CONFIG "/dev/buses/uart/blsp1_uart4_cfg"
#define BLSP1_UART5_DEV_CONFIG "/dev/buses/uart/blsp1_uart5_cfg"
#define BLSP2_UART0_DEV_CONFIG "/dev/buses/uart/blsp2_uart0_cfg"
#define BLSP2_UART1_DEV_CONFIG "/dev/buses/uart/blsp2_uart1_cfg"
#define BLSP2_UART2_DEV_CONFIG "/dev/buses/uart/blsp2_uart2_cfg"
#define BLSP2_UART3_DEV_CONFIG "/dev/buses/uart/blsp2_uart3_cfg"
#define BLSP2_UART4_DEV_CONFIG "/dev/buses/uart/blsp2_uart4_cfg"
#define BLSP2_UART5_DEV_CONFIG "/dev/buses/uart/blsp2_uart5_cfg"
#define SSC_UART0_DEV_CONFIG "/dev/buses/uart/ssc_uart0_cfg"
#define SSC_UART1_DEV_CONFIG "/dev/buses/uart/ssc_uart1_cfg"
#define SSC_UART2_DEV_CONFIG "/dev/buses/uart/ssc_uart2_cfg"


/* TODO: If AccessControl.h is visible to both TZ and Hyp, we may be able to use the enum defines from there directly.
 * Though, DAL properties cannot be enum value if its an array type
 */
#define AC_NONE  0
#define AC_TZ  1
#define AC_RPM  2
#define AC_HLOS  3
#define AC_HYP  4
#define AC_SSC_Q6_ELF 5
#define AC_ADSP_Q6_ELF 6 // Single 
#define AC_SSC_HLOS 7   // ??, may be we combine this with other SSC one //
#define AC_CP_TOUCH 8
#define AC_CP_BITSTREAM 9
#define AC_CP_PIXEL 10
#define AC_CP_NON_PIXEL 11
#define AC_VIDEO_FW 12
#define AC_CP_CAMERA 13
#define AC_HLOS_UNMAPPED 14
#define AC_MSS_MSA 15
#define AC_MSS_NONMSA 16
#define AC_UNMAPPED 17
#define BLSP_AC_LAST 18
#define AC_DEFAULT 0xFF// Default as in retain whatever in SMMU static config table

//TODO: Check if below enum list is still needed 
typedef enum {
   PERIPH_ENUM_MIN = 0 ,
   BLSP1_QUP0 = PERIPH_ENUM_MIN,
   BLSP1_QUP1,
   BLSP1_QUP2,
   BLSP1_QUP3,
   BLSP1_QUP4,
   BLSP1_QUP5,
   BLSP2_QUP0,
   BLSP2_QUP1,
   BLSP2_QUP2,
   BLSP2_QUP3,
   BLSP2_QUP4,
   BLSP2_QUP5,
   SSC_QUP0,
   SSC_QUP1,
   SSC_QUP2,
   BLSP_UARTID_START,
   BLSP1_UART0 = BLSP_UARTID_START,
   BLSP1_UART1,
   BLSP1_UART2,
   BLSP1_UART3,
   BLSP1_UART4,
   BLSP1_UART5,
   BLSP2_UART0,
   BLSP2_UART1,
   BLSP2_UART2,
   BLSP2_UART3,
   BLSP2_UART4,
   BLSP2_UART5,
   SSC_UART0,
   SSC_UART1,
   SSC_UART2,
   PERIPH_MAX_ID
} BLSP_PERIPHID;

typedef enum {
   PERIPH_BLSP1 = 1, // first 6 QUPs above
   PERIPH_BLSP2 = 2, //next 6 QUPs
   SSC_BLSP = 3 // remaining 3 QUPs on SSC
}QUPAC_BLSPID;


#endif

