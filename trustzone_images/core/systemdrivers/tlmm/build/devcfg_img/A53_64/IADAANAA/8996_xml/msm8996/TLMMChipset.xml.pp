# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/msm8996/TLMMChipset.xml"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 170 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/msm8996/TLMMChipset.xml" 2
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h" 1
# 33 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h"
# 1 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/dal/DALStdDef.h" 1
# 28 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned int uint32;




typedef unsigned short uint16;




typedef unsigned char uint8;




typedef signed int int32;




typedef signed short int16;




typedef signed char int8;
# 64 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned long long uint64;




typedef long long int64;





typedef unsigned char byte;





typedef unsigned long UINTN;






typedef uint32 DALBOOL;
typedef uint32 DALDEVICEID;
typedef uint32 DalPowerCmd;
typedef uint32 DalPowerDomain;
typedef uint32 DalSysReq;
typedef UINTN DALHandle;
typedef int DALResult;
typedef void * DALEnvHandle;
typedef void * DALSYSEventHandle;
typedef uint32 DALMemAddr;
typedef UINTN DALSYSMemAddr;
typedef uint32 DALInterfaceVersion;
# 108 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/api/dal/DALStdDef.h"
typedef unsigned char * DALDDIParamPtr;

typedef struct DALEventObject DALEventObject;
struct DALEventObject
{
    uint32 obj[8];
};
typedef DALEventObject * DALEventHandle;

typedef struct _DALMemObject
{
   uint32 memAttributes;
   uint32 sysObjInfo[2];
   uint32 dwLen;
   uint32 ownerVirtAddr;
   uint32 virtAddr;
   uint32 physAddr;
}
DALMemObject;

typedef struct _DALDDIMemBufDesc
{
   uint32 dwOffset;
   uint32 dwLen;
   uint32 dwUser;
}
DALDDIMemBufDesc;


typedef struct _DALDDIMemDescList
{
   uint32 dwFlags;
   uint32 dwNumBufs;
   DALDDIMemBufDesc bufList[1];
}
DALDDIMemDescList;





typedef struct DALSysMemDescBuf DALSysMemDescBuf;
struct DALSysMemDescBuf
{
   DALSYSMemAddr VirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   uint32 size;
   uint32 user;
};

typedef struct DALSysMemDescList DALSysMemDescList;
struct DALSysMemDescList
{
   uint32 dwObjInfo; uint32 hOwnerProc; DALSYSMemAddr thisVirtualAddr;
   DALSYSMemAddr PhysicalAddr;
   DALSYSMemAddr VirtualAddr;
   uint32 dwCurBufIdx;
   uint32 dwNumDescBufs;
   DALSysMemDescBuf BufInfo[1];
};
# 34 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h" 2
# 52 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/TlmmPropDef.h"
typedef struct {
   uint32 nGpioNumber;
   uint32 nFunctionSelect;
}TLMMGpioIdType;
# 2 "/local/mnt/workspace/CRMBuilds/TZ.BF.4.0.3.c1-00005-M8996AAAAANAZT-1_20170110_230814/b/HK11/trustzone_images/core/systemdrivers/tlmm/config/msm8996/TLMMChipset.xml" 2
<driver name="NULL">
  <device id="/tlmm/configs">
    <props name="blsp_spi_mosi[5]" type="TLMMGpioIdType">{81, 2}</props>
    <props name="blsp_spi_miso[5]" type="TLMMGpioIdType">{82, 2}</props>
    <props name="blsp_spi_cs_n[5]" type="TLMMGpioIdType">{83, 2}</props>
    <props name="blsp_spi_clk[5]" type="TLMMGpioIdType">{84, 1}</props>
    <props name="blsp_spi_mosi[1]" type="TLMMGpioIdType">{0, 1}</props>
    <props name="blsp_spi_miso[1]" type="TLMMGpioIdType">{1, 1}</props>
    <props name="blsp_spi_cs_n[1]" type="TLMMGpioIdType">{2, 1}</props>
    <props name="blsp_spi_clk[1]" type="TLMMGpioIdType">{3, 1}</props>
    <props name="blsp_spi_mosi[7]" type="TLMMGpioIdType">{41, 1}</props>
    <props name="blsp_spi_miso[7]" type="TLMMGpioIdType">{42, 1}</props>
    <props name="blsp_spi_cs_n[7]" type="TLMMGpioIdType">{43, 1}</props>
    <props name="blsp_spi_clk[7]" type="TLMMGpioIdType">{44, 1}</props>

    <props name="blsp_i2c_sda[1]" type="TLMMGpioIdType">{2, 3}</props>
    <props name="blsp_i2c_scl[1]" type="TLMMGpioIdType">{3, 3}</props>

    <props name="blsp_i2c_sda[2]" type="TLMMGpioIdType">{43, 3}</props>
    <props name="blsp_i2c_scl[2]" type="TLMMGpioIdType">{44, 3}</props>

    <props name="blsp_i2c_sda[3]" type="TLMMGpioIdType">{47, 3}</props>
    <props name="blsp_i2c_scl[3]" type="TLMMGpioIdType">{48, 3}</props>

    <props name="blsp_i2c_sda[4]" type="TLMMGpioIdType">{67, 4}</props>
    <props name="blsp_i2c_scl[4]" type="TLMMGpioIdType">{68, 4}</props>

    <props name="blsp_i2c_sda[5]" type="TLMMGpioIdType">{83, 4}</props>
    <props name="blsp_i2c_scl[5]" type="TLMMGpioIdType">{84, 3}</props>

    <props name="blsp_i2c_sda[6]" type="TLMMGpioIdType">{27, 3}</props>
    <props name="blsp_i2c_scl[6]" type="TLMMGpioIdType">{28, 3}</props>

    <props name="blsp_i2c_sda[7]" type="TLMMGpioIdType">{55, 3}</props>
    <props name="blsp_i2c_scl[7]" type="TLMMGpioIdType">{56, 3}</props>

    <props name="blsp_i2c_sda[8]" type="TLMMGpioIdType">{6, 3}</props>
    <props name="blsp_i2c_scl[8]" type="TLMMGpioIdType">{6, 3}</props>

    <props name="blsp_i2c_sda[9]" type="TLMMGpioIdType">{51, 4}</props>
    <props name="blsp_i2c_scl[9]" type="TLMMGpioIdType">{52, 4}</props>

    <props name="blsp_i2c_sda[10]" type="TLMMGpioIdType">{10, 4}</props>
    <props name="blsp_i2c_scl[10]" type="TLMMGpioIdType">{11, 4}</props>

    <props name="blsp_i2c_sda[11]" type="TLMMGpioIdType">{60, 5}</props>
    <props name="blsp_i2c_scl[11]" type="TLMMGpioIdType">{61, 5}</props>

    <props name="blsp_i2c_sda[12]" type="TLMMGpioIdType">{87, 3}</props>
    <props name="blsp_i2c_scl[12]" type="TLMMGpioIdType">{88, 3}</props>

    <props name="blsp1_spi_cs1_n" type="TLMMGpioIdType">{90, 2}</props>

    <props name="tlmm_gpio_test_pin" type="TLMMGpioIdType">{81, 2}</props>

    <props name="tlmm_base" type=DALPROP_ATTR_TYPE_UINT32>
      0x01000000
    </props>
    <props name="tlmm_offset" type=DALPROP_ATTR_TYPE_UINT32>
      0x00010000
    </props>
    <props name="tlmm_total_gpio" type=DALPROP_ATTR_TYPE_UINT32>
      150
    </props>
  </device>
</driver>
