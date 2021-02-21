#include "tzbsp_cfg_prop.h"

#define TZBSP_INT_SPI(xx) ((xx)+32)
#define TZBSP_INT_VMIDMT_ERR_CLT_SEC            TZBSP_INT_SPI(198)
#define TZBSP_INT_VMIDMT_ERR_CLT_NONSEC         TZBSP_INT_SPI(199)
#define TZBSP_INT_VMIDMT_ERR_CFG_SEC            TZBSP_INT_SPI(200)
#define TZBSP_INT_VMIDMT_ERR_CFG_NONSEC         TZBSP_INT_SPI(201)
#define TZBSP_INT_XPU_SEC                       TZBSP_INT_SPI(195)
#define TZBSP_INT_XPU_NON_SEC                   TZBSP_INT_SPI(196)
#define TZBSP_INT_NON_SEC_WDOG_BITE             TZBSP_INT_SPI(29)
#define TZBSP_INT_RPM_ERR_IND                   TZBSP_INT_SPI(174)
#define TZBSP_INT_RPM_WDOG_BITE                 TZBSP_INT_SPI(237)
#define TZBSP_INT_PIMEM_NON_FATAL               TZBSP_INT_SPI(325)
#define TZBSP_INT_PIMEM_FATAL                   TZBSP_INT_SPI(328)

#define TZBSP_NON_OF_THE_ABOVE                  0

tzbsp_reset_reason_pair_t rst_reason_list[] =
{
  {TZBSP_INT_VMIDMT_ERR_CLT_SEC    , 0x1},
  {TZBSP_INT_VMIDMT_ERR_CLT_NONSEC , 0x2},
  {TZBSP_INT_VMIDMT_ERR_CFG_SEC    , 0x3},
  {TZBSP_INT_VMIDMT_ERR_CFG_NONSEC , 0x4},
  {TZBSP_INT_XPU_SEC               , 0x5},
  {TZBSP_INT_XPU_NON_SEC           , 0x6},
  {TZBSP_INT_NON_SEC_WDOG_BITE     , 0x7},
  {TZBSP_INT_RPM_ERR_IND           , 0x8},
  {TZBSP_INT_RPM_WDOG_BITE         , 0x9},
  {TZBSP_INT_PIMEM_NON_FATAL       , 0xA},
  {TZBSP_INT_PIMEM_FATAL           , 0xB},
  {TZBSP_NON_OF_THE_ABOVE          , 0xDEADD00D},
};

tzbsp_cfg_oem_reset_reason_t oem_rst_reason_list = 
{
  sizeof(rst_reason_list)/sizeof(tzbsp_reset_reason_pair_t),
  rst_reason_list
};

