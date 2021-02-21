#ifndef CHIPINFO_H
#define CHIPINFO_H
/*===========================================================================

                         Chipinfo Header File

DESCRIPTION
  This header file contains the public API for the chipinfo driver.

      Copyright (c) 2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.tz/1.0.3.c1/api/systemdrivers/Chipinfo.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/17/12   pbitra  Initial version.
01/24/13   pbitra  Added support for Chipinfo_GetVersion

===========================================================================*/

#include "comdef.h"     /* Common Definitions and Types */
#include "DALSysTypes.h"


/*===========================================================================

                        DATA DECLARATIONS

===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif
/**
Chip Family type.  The family type of the chip we are running on.
Each family may include multiple chip ids.
*/
typedef enum
{ 
  CHIPINFO_FAMILY_UNKNOWN     = 0,
  CHIPINFO_FAMILY_MSM8974     = 32,
  CHIPINFO_FAMILY_MDM9x25     = 35,
  CHIPINFO_FAMILY_MSM8x10     = 38,
  CHIPINFO_FAMILY_MPQ8092     = 39,
  CHIPINFO_FAMILY_MSM8x26     = 40,
  CHIPINFO_FAMILY_APQ8084     = 43,
  CHIPINFO_FAMILY_APQ8x94     = CHIPINFO_FAMILY_APQ8084,
  CHIPINFO_FAMILY_MSM8x32     = 44,
  CHIPINFO_FAMILY_MDM9x35     = 45,
  CHIPINFO_FAMILY_MSM8974_PRO = 46,
  CHIPINFO_FAMILY_FSM9900     = 47,
  CHIPINFO_FAMILY_MSM8x62     = 48,
  CHIPINFO_FAMILY_MSM8926     = 49,
  CHIPINFO_FAMILY_MSM8994     = 50,
  CHIPINFO_FAMILY_IPQ8064     = 51,
  CHIPINFO_FAMILY_MSM8916     = 52,
  CHIPINFO_FAMILY_MSM8936     = 53,
  CHIPINFO_FAMILY_MDM9x45     = 54,
  CHIPINFO_FAMILY_MSM8996     = 56,
  CHIPINFO_FAMILY_APQ8096     = CHIPINFO_FAMILY_MSM8996,
  CHIPINFO_FAMILY_MSM8992     = 57,
  CHIPINFO_FAMILY_MSM8909     = 58,
  CHIPINFO_FAMILY_FSM90xx     = 59,
  CHIPINFO_FAMILY_MSM8952     = 60,
  CHIPINFO_FAMILY_QDF2432     = 61,
  CHIPINFO_FAMILY_MSM8929     = 62,
  CHIPINFO_FAMILY_MSM8956     = 63,
  CHIPINFO_FAMILY_IPQ401x     = 64,
  CHIPINFO_FAMILY_MDM9x55     = 65,
  CHIPINFO_FAMILY_MDM9x07     = 66,
  CHIPINFO_FAMILY_MSM8998     = 67,
  CHIPINFO_FAMILY_MSM8953     = 68,
  CHIPINFO_FAMILY_MSM8993     = 69,
  CHIPINFO_FAMILY_MSM8937     = 70,
  CHIPINFO_FAMILY_MSM8917     = 71,
  CHIPINFO_FAMILY_MSM8996SG   = 72,
  CHIPINFO_FAMILY_MSM8997     = 73,

  CHIPINFO_NUM_FAMILIES       = 74,
  CHIPINFO_FAMILY_32BITS      = 0x7FFFFFF
} ChipInfoFamilyType;

/**
 * Chip version type with major number in the upper 16 bits and minor
 * number in the lower 16 bits.  For example:
 *   1.0 -> 0x00010000
 *   2.3 -> 0x00020003
 * The CHIPINFO_VERSION macro should be used to generate the 
 * appropriate comparison value as the format is not guaranteed 
 * to remain unchanged. 
 */
typedef uint32 ChipInfoVersionType;

/**
Chip identification type.  Any new ids must be added to the end.
*/
typedef enum
{
  CHIPINFO_ID_UNKNOWN    = 0,
  CHIPINFO_ID_MDM1000    = 1,
  CHIPINFO_ID_ESM6235    = 2,
  CHIPINFO_ID_QSC6240    = 3,
  CHIPINFO_ID_MSM6245    = 4,
  CHIPINFO_ID_MSM6255    = 5,
  CHIPINFO_ID_MSM6255A   = 6,
  CHIPINFO_ID_MSM6260    = 7,
  CHIPINFO_ID_MSM6246    = 8,
  CHIPINFO_ID_QSC6270    = 9,
  CHIPINFO_ID_MSM6280    = 10,
  CHIPINFO_ID_MSM6290    = 11,
  CHIPINFO_ID_MSM7200    = 12,
  CHIPINFO_ID_MSM7201    = 13,
  CHIPINFO_ID_ESM7205    = 14,
  CHIPINFO_ID_ESM7206    = 15,
  CHIPINFO_ID_MSM7200A   = 16,
  CHIPINFO_ID_MSM7201A   = 17,
  CHIPINFO_ID_ESM7205A   = 18,
  CHIPINFO_ID_ESM7206A   = 19,
  CHIPINFO_ID_ESM7225    = 20,
  CHIPINFO_ID_MSM7225    = 21,
  CHIPINFO_ID_MSM7500    = 22,
  CHIPINFO_ID_MSM7500A   = 23,
  CHIPINFO_ID_MSM7525    = 24,
  CHIPINFO_ID_MSM7600    = 25,
  CHIPINFO_ID_MSM7601    = 26,
  CHIPINFO_ID_MSM7625    = 27,
  CHIPINFO_ID_MSM7800    = 28,
  CHIPINFO_ID_MDM8200    = 29,
  CHIPINFO_ID_QSD8650    = 30,
  CHIPINFO_ID_MDM8900    = 31,
  CHIPINFO_ID_QST1000    = 32,
  CHIPINFO_ID_QST1005    = 33,
  CHIPINFO_ID_QST1100    = 34,
  CHIPINFO_ID_QST1105    = 35,
  CHIPINFO_ID_QST1500    = 40,
  CHIPINFO_ID_QST1600    = 41,
  CHIPINFO_ID_QST1700    = 42,
  CHIPINFO_ID_QSD8250    = 36,
  CHIPINFO_ID_QSD8550    = 37,
  CHIPINFO_ID_QSD8850    = 38,
  CHIPINFO_ID_MDM2000    = 39,
  CHIPINFO_ID_MSM7227    = 43,
  CHIPINFO_ID_MSM7627    = 44,
  CHIPINFO_ID_QSC6165    = 45,
  CHIPINFO_ID_QSC6175    = 46,
  CHIPINFO_ID_QSC6185    = 47,
  CHIPINFO_ID_QSC6195    = 48,
  CHIPINFO_ID_QSC6285    = 49,
  CHIPINFO_ID_QSC6295    = 50,
  CHIPINFO_ID_QSC6695    = 51,
  CHIPINFO_ID_ESM6246    = 52,
  CHIPINFO_ID_ESM6290    = 53,
  CHIPINFO_ID_ESC6270    = 54,
  CHIPINFO_ID_ESC6240    = 55,
  CHIPINFO_ID_MDM8220    = 56,
  CHIPINFO_ID_MDM9200    = 57,
  CHIPINFO_ID_MDM9600    = 58,
  CHIPINFO_ID_MSM7630    = 59,
  CHIPINFO_ID_MSM7230    = 60,
  CHIPINFO_ID_ESM7227    = 61,
  CHIPINFO_ID_MSM7625D1  = 62,
  CHIPINFO_ID_MSM7225D1  = 63,
  CHIPINFO_ID_QSD8250A   = 64,
  CHIPINFO_ID_QSD8650A   = 65,
  CHIPINFO_ID_MSM7625D2  = 66,
  CHIPINFO_ID_MSM7227D1  = 67,
  CHIPINFO_ID_MSM7627D1  = 68,
  CHIPINFO_ID_MSM7627D2  = 69,
  CHIPINFO_ID_MSM8260    = 70,
  CHIPINFO_ID_MSM8660    = 71,
  CHIPINFO_ID_MDM8200A   = 72,
  CHIPINFO_ID_QSC6155    = 73,
  CHIPINFO_ID_MSM8255    = 74,
  CHIPINFO_ID_MSM8655    = 75,
  CHIPINFO_ID_ESC6295    = 76,
  CHIPINFO_ID_MDM3000    = 77,
  CHIPINFO_ID_MDM6200    = 78,
  CHIPINFO_ID_MDM6600    = 79,
  CHIPINFO_ID_MDM6210    = 80,
  CHIPINFO_ID_MDM6610    = 81,
  CHIPINFO_ID_QSD8672    = 82,
  CHIPINFO_ID_MDM6215    = 83,
  CHIPINFO_ID_MDM6615    = 84,
  CHIPINFO_ID_APQ8055    = 85,
  CHIPINFO_ID_APQ8060    = 86,
  CHIPINFO_ID_MSM8960    = 87,
  CHIPINFO_ID_MSM7225A   = 88,
  CHIPINFO_ID_MSM7625A   = 89,
  CHIPINFO_ID_MSM7227A   = 90,
  CHIPINFO_ID_MSM7627A   = 91,
  CHIPINFO_ID_ESM7227A   = 92,
  CHIPINFO_ID_QSC6195D2  = 93,
  CHIPINFO_ID_FSM9200    = 94,
  CHIPINFO_ID_FSM9800    = 95,
  CHIPINFO_ID_MSM7225AD1 = 96,
  CHIPINFO_ID_MSM7227AD1 = 97,
  CHIPINFO_ID_MSM7225AA   = 98,
  CHIPINFO_ID_MSM7225AAD1 = 99,
  CHIPINFO_ID_MSM7625AA   = 100,
  CHIPINFO_ID_MSM7227AA   = 101,
  CHIPINFO_ID_MSM7227AAD1 = 102,
  CHIPINFO_ID_MSM7627AA   = 103,
  CHIPINFO_ID_MDM9615     = 104,
  CHIPINFO_ID_MDM9615M    = CHIPINFO_ID_MDM9615,
  CHIPINFO_ID_MDM8215     = 106,
  CHIPINFO_ID_MDM9215     = 107,
  CHIPINFO_ID_MDM9215M    = CHIPINFO_ID_MDM9215,
  CHIPINFO_ID_APQ8064     = 109,
  CHIPINFO_ID_QSC6270D1   = 110,
  CHIPINFO_ID_QSC6240D1   = 111,
  CHIPINFO_ID_ESC6270D1   = 112,
  CHIPINFO_ID_ESC6240D1   = 113,
  CHIPINFO_ID_MDM6270     = 114,
  CHIPINFO_ID_MDM6270D1   = 115,
  CHIPINFO_ID_MSM8930     = 116,
  CHIPINFO_ID_MSM8630     = 117,
  CHIPINFO_ID_MSM8230     = 118,
  CHIPINFO_ID_APQ8030     = 119,
  CHIPINFO_ID_MSM8627     = 120,
  CHIPINFO_ID_MSM8227     = 121,
  CHIPINFO_ID_MSM8660A    = 122,
  CHIPINFO_ID_MSM8260A    = 123,
  CHIPINFO_ID_APQ8060A    = 124,
  CHIPINFO_ID_MPQ8062     = 125,
  CHIPINFO_ID_MSM8974     = 126,
  CHIPINFO_ID_MSM8225     = 127,
  CHIPINFO_ID_MSM8225D1   = 128,
  CHIPINFO_ID_MSM8625     = 129,
  CHIPINFO_ID_MPQ8064     = 130,
  CHIPINFO_ID_MSM7225AB   = 131,
  CHIPINFO_ID_MSM7225ABD1 = 132,
  CHIPINFO_ID_MSM7625AB   = 133,
  CHIPINFO_ID_MDM9625     = 134,
  CHIPINFO_ID_MSM7125A    = 135,
  CHIPINFO_ID_MSM7127A    = 136,
  CHIPINFO_ID_MSM8125AB   = 137,
  CHIPINFO_ID_MSM8960AB   = 138,
  CHIPINFO_ID_APQ8060AB   = 139,
  CHIPINFO_ID_MSM8260AB   = 140,
  CHIPINFO_ID_MSM8660AB   = 141,
  CHIPINFO_ID_MSM8930AA   = 142,
  CHIPINFO_ID_MSM8630AA   = 143,
  CHIPINFO_ID_MSM8230AA   = 144,
  CHIPINFO_ID_MSM8626     = 145,
  CHIPINFO_ID_MPQ8092     = 146,
  CHIPINFO_ID_MSM8610     = 147,
  CHIPINFO_ID_MDM8225     = 148,
  CHIPINFO_ID_MDM9225     = 149,
  CHIPINFO_ID_MDM9225M    = 150,
  CHIPINFO_ID_MDM8225M    = 151,
  CHIPINFO_ID_MDM9625M    = 152,
  CHIPINFO_ID_APQ8064_V2PRIME   = 153,
  CHIPINFO_ID_MSM8930AB   = 154,
  CHIPINFO_ID_MSM8630AB   = 155,
  CHIPINFO_ID_MSM8230AB   = 156,
  CHIPINFO_ID_APQ8030AB   = 157,
  CHIPINFO_ID_MSM8226     = 158,
  CHIPINFO_ID_MSM8526     = 159,
  CHIPINFO_ID_APQ8030AA   = 160,
  CHIPINFO_ID_MSM8110     = 161,
  CHIPINFO_ID_MSM8210     = 162,
  CHIPINFO_ID_MSM8810     = 163,
  CHIPINFO_ID_MSM8212     = 164,
  CHIPINFO_ID_MSM8612     = 165,
  CHIPINFO_ID_MSM8112     = 166,
  CHIPINFO_ID_MSM8125     = 167,
  CHIPINFO_ID_MSM8225Q    = 168,
  CHIPINFO_ID_MSM8625Q    = 169,
  CHIPINFO_ID_MSM8125Q    = 170,
  CHIPINFO_ID_MDM9310     = 171,
  CHIPINFO_ID_APQ8064_SLOW_PRIME = 172,
  CHIPINFO_ID_MDM8110M    = 173,
  CHIPINFO_ID_MDM8615M    = 174,
  CHIPINFO_ID_MDM9320     = 175,
  CHIPINFO_ID_MDM9225_1   = 176,
  CHIPINFO_ID_MDM9225M_1  = 177,
  CHIPINFO_ID_APQ8084     = 178,
  CHIPINFO_ID_MSM8130     = 179,
  CHIPINFO_ID_MSM8130AA   = 180,
  CHIPINFO_ID_MSM8130AB   = 181,
  CHIPINFO_ID_MSM8627AA   = 182,
  CHIPINFO_ID_MSM8227AA   = 183,
  CHIPINFO_ID_APQ8074     = 184,
  CHIPINFO_ID_MSM8274     = 185,
  CHIPINFO_ID_MSM8674     = 186,
  CHIPINFO_ID_MDM9635     = 187,
  CHIPINFO_ID_FSM9900     = 188,
  CHIPINFO_ID_FSM9965     = 189,
  CHIPINFO_ID_FSM9955     = 190,
  CHIPINFO_ID_FSM9950     = 191,
  CHIPINFO_ID_FSM9915     = 192,
  CHIPINFO_ID_FSM9910     = 193,
  CHIPINFO_ID_MSM8974_PRO = 194,
  CHIPINFO_ID_MSM8962     = 195,
  CHIPINFO_ID_MSM8262     = 196,
  CHIPINFO_ID_APQ8062     = 197,
  CHIPINFO_ID_MSM8126     = 198,
  CHIPINFO_ID_APQ8026     = 199,
  CHIPINFO_ID_MSM8926     = 200,
  CHIPINFO_ID_MSM8326     = 205,
  CHIPINFO_ID_MSM8916     = 206,
  CHIPINFO_ID_MSM8994     = 207,
  CHIPINFO_ID_APQ8074_AA  = 208,
  CHIPINFO_ID_APQ8074_AB  = 209,
  CHIPINFO_ID_APQ8074_PRO = 210,
  CHIPINFO_ID_MSM8274_AA  = 211,
  CHIPINFO_ID_MSM8274_AB  = 212,
  CHIPINFO_ID_MSM8274_PRO = 213,
  CHIPINFO_ID_MSM8674_AA  = 214,
  CHIPINFO_ID_MSM8674_AB  = 215,
  CHIPINFO_ID_MSM8674_PRO = 216,
  CHIPINFO_ID_MSM8974_AA  = 217,
  CHIPINFO_ID_MSM8974_AB  = 218,
  CHIPINFO_ID_APQ8028     = 219,
  CHIPINFO_ID_MSM8128     = 220,
  CHIPINFO_ID_MSM8228     = 221,
  CHIPINFO_ID_MSM8528     = 222,
  CHIPINFO_ID_MSM8628     = 223,
  CHIPINFO_ID_MSM8928     = 224,
  CHIPINFO_ID_MSM8510     = 225,
  CHIPINFO_ID_MSM8512     = 226,
  CHIPINFO_ID_MDM9630     = 227,
  CHIPINFO_ID_MDM9635M    = CHIPINFO_ID_MDM9635,
  CHIPINFO_ID_MDM9230     = 228,
  CHIPINFO_ID_MDM9235M    = 229,
  CHIPINFO_ID_MDM8630     = 230,
  CHIPINFO_ID_MDM9330     = 231,
  CHIPINFO_ID_MPQ8091     = 232,
  CHIPINFO_ID_MSM8936     = 233,
  CHIPINFO_ID_MDM9240     = 234,
  CHIPINFO_ID_MDM9340     = 235,
  CHIPINFO_ID_MDM9640     = 236,
  CHIPINFO_ID_MDM9245     = 237,
  CHIPINFO_ID_MDM9645     = 238,
  CHIPINFO_ID_MSM8939     = 239,
  CHIPINFO_ID_APQ8036     = 240,
  CHIPINFO_ID_APQ8039     = 241,
  CHIPINFO_ID_MSM8236     = 242,
  CHIPINFO_ID_MSM8636     = 243,
  CHIPINFO_ID_APQ8064_AU  = 244,
  CHIPINFO_ID_MSM8909     = 245,
  CHIPINFO_ID_MSM8996     = 246,
  CHIPINFO_ID_APQ8016     = 247,
  CHIPINFO_ID_MSM8216     = 248,
  CHIPINFO_ID_MSM8116     = 249,
  CHIPINFO_ID_MSM8616     = 250,
  CHIPINFO_ID_MSM8992     = 251,
  CHIPINFO_ID_APQ8092     = 252,
  CHIPINFO_ID_APQ8094     = 253,
  CHIPINFO_ID_FSM9008     = 254,
  CHIPINFO_ID_FSM9010     = 255,
  CHIPINFO_ID_FSM9016     = 256,
  CHIPINFO_ID_FSM9055     = 257,
  CHIPINFO_ID_MSM8209     = 258,
  CHIPINFO_ID_MSM8208     = 259,
  CHIPINFO_ID_MDM9209     = 260,
  CHIPINFO_ID_MDM9309     = 261,
  CHIPINFO_ID_MDM9609     = 262,
  CHIPINFO_ID_MSM8239     = 263,
  CHIPINFO_ID_MSM8952     = 264,
  CHIPINFO_ID_APQ8009     = 265,
  CHIPINFO_ID_MSM8956     = 266,
  CHIPINFO_ID_QDF2432     = 267,
  CHIPINFO_ID_MSM8929     = 268,
  CHIPINFO_ID_MSM8629     = 269,
  CHIPINFO_ID_MSM8229     = 270,
  CHIPINFO_ID_APQ8029     = 271,
  CHIPINFO_ID_QCA9618     = 272,
  CHIPINFO_ID_QCA9619     = 273,
  CHIPINFO_ID_APQ8056     = 274,
  CHIPINFO_ID_MSM8609     = 275,
  CHIPINFO_ID_FSM9916     = 276,
  CHIPINFO_ID_APQ8076     = 277,
  CHIPINFO_ID_MSM8976     = 278,
  CHIPINFO_ID_MDM9650     = 279,
  CHIPINFO_ID_IPQ8065     = 280,
  CHIPINFO_ID_IPQ8069     = 281,
  CHIPINFO_ID_MSM8939_BC  = 282,
  CHIPINFO_ID_MDM9250     = 283,
  CHIPINFO_ID_MDM9255     = 284,
  CHIPINFO_ID_MDM9350     = 285,
  CHIPINFO_ID_MDM9655     = 286,
  CHIPINFO_ID_IPQ4028     = 287,
  CHIPINFO_ID_IPQ4029     = 288,
  CHIPINFO_ID_APQ8052     = 289,
  CHIPINFO_ID_MDM9607     = 290,
  CHIPINFO_ID_APQ8096     = 291,
  CHIPINFO_ID_MSM8998     = 292,
  CHIPINFO_ID_MSM8953     = 293,
  CHIPINFO_ID_MSM8937     = 294,
  CHIPINFO_ID_APQ8037     = 295,
  CHIPINFO_ID_MDM8207     = 296,
  CHIPINFO_ID_MDM9207     = 297,
  CHIPINFO_ID_MDM9307     = 298,
  CHIPINFO_ID_MDM9628     = 299,
  CHIPINFO_ID_MSM8909W    = 300,
  CHIPINFO_ID_APQ8009W    = 301,
  CHIPINFO_ID_MSM8996L    = 302,
  CHIPINFO_ID_MSM8917     = 303,
  CHIPINFO_ID_APQ8053     = 304,
  CHIPINFO_ID_MSM8996_PRO = 305,
  CHIPINFO_ID_MSM8997     = 306,
  CHIPINFO_ID_APQ8017     = 307,
  CHIPINFO_ID_MSM8217     = 308,
  CHIPINFO_ID_MSM8617     = 309,
  CHIPINFO_ID_MSM8996AU   = 310,
  CHIPINFO_ID_APQ8096AU   = 311,
  CHIPINFO_ID_APQ8096SG   = 312,

  CHIPINFO_NUM_IDS        = 313,
  CHIPINFO_ID_32BITS     = 0x7FFFFFF
} ChipInfoIdType;
/*===========================================================================

                      MACROS

===========================================================================*/
/**
 * Macro to generate the hardware version number from a given major
 * and minor number.  For example to check if this is at least version 1.2:
 *   ChipInfo_GetVersion(h, &version);
 *   if (version >= CHIPINFO_VERSION(1,2)) ...
 */
#define CHIPINFO_VERSION(major, minor)  (((major) << 16) | (minor))

/*===========================================================================

                      FUNCTION DECLARATIONS

===========================================================================*/

/*==========================================================================

  FUNCTION      CHIPINFO_GETFAMILY

  DESCRIPTION   This function retrieves the Chip Family
                from the SOC_HW_VERSION register.

  PARAMETERS    None

  DEPENDENCIES  None.

  RETURN VALUE  Chip Family

  SIDE EFFECTS  None.

==========================================================================*/

ChipInfoFamilyType Chipinfo_GetFamily (void);


/*==========================================================================

  FUNCTION      CHIPINFO_GETVERSION

  DESCRIPTION   This function retrieves the Chip Version
                from the SOC_HW_VERSION register.

  PARAMETERS    None

  DEPENDENCIES  None.

  RETURN VALUE  Chip Version

  SIDE EFFECTS  None.

==========================================================================*/
ChipInfoVersionType Chipinfo_GetVersion (void);

/*==========================================================================

  FUNCTION      Chipinfo_Init

  DESCRIPTION   This function reads chipID from smem area and initializes 
                Chip_ID variable.This function gets called in 
                tzbsp_cold_init_pre_mmu() and only after the call to this
                function Chipinfo_GetId call shall return correct chipID 

  PARAMETERS    None

  DEPENDENCIES  smem had to be initialized.

  RETURN VALUE  DALResult

  SIDE EFFECTS  None.

==========================================================================*/

DALResult Chipinfo_Init(void);

/*==========================================================================

  FUNCTION      Chipinfo_GetId

  DESCRIPTION   This function returns chip ID 

  PARAMETERS    None

  DEPENDENCIES  ChipInfo_Init need be called prior to it atleast once.

  RETURN VALUE  DALResult

  SIDE EFFECTS  None.

==========================================================================*/

ChipInfoIdType Chipinfo_GetId (void);

#ifdef __cplusplus
}
#endif

#endif /* CHIPINFO_H */

