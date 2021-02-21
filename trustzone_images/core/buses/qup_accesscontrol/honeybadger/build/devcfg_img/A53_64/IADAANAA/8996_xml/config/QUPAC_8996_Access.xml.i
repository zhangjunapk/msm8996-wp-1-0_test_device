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
   PERIPH_BLSP1 = 1,
   PERIPH_BLSP2 = 2,
   SSC_BLSP = 3
}QUPAC_BLSPID;
<driver name="NULL">
   <device id="/dev/buses/qup/blsp1_qup0">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_QUP0 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> 0, 1 ,2, 3, end </props>
       <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp1_uart0">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_UART0 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
       <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
       </props>
   </device>
   <device id="/dev/buses/qup/blsp1_qup1">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_QUP1 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
         3, end
       </props>
   </device>
   <device id="/dev/buses/uart/blsp1_uart1">
     <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_UART1 </props>
     <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
       </props>
   </device>
   <device id="/dev/buses/qup/blsp1_qup2">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_QUP2 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> 45, 46, 47, 48, end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
         3, end
      </props>
   </device>
   <device id="/dev/buses/uart/blsp1_uart2">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_UART2 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          6, end
      </props>
   </device>
   <device id="/dev/buses/qup/blsp1_qup3">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_QUP3 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
            0xFF, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp1_uart3">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_UART3 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/blsp1_qup4">
     <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_QUP4 </props>
     <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          6, end
       </props>
   </device>
   <device id="/dev/buses/uart/blsp1_uart4">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_UART4 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
         6, end
       </props>
   </device>
   <device id="/dev/buses/qup/blsp1_qup5">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_QUP5 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp1_uart5">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP1_UART5 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/blsp2_qup0">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_QUP0 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp2_uart0">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_UART0 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
       </props>
   </device>
   <device id="/dev/buses/qup/blsp2_qup1">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_QUP1 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> 4, 5, 6, 7, end </props>
     <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp2_uart1">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_UART1 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
        </props>
   </device>
   <device id="/dev/buses/qup/blsp2_qup2">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_QUP2 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> 49, 50, 51, 52, end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp2_uart2">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_UART2 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/blsp2_qup3">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_QUP3 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> 8, 9, 10, 11, end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
         0xFF, end
      </props>
   </device>
   <device id="/dev/buses/uart/blsp2_uart3">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_UART3 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
      </props>
   </device>
   <device id="/dev/buses/qup/blsp2_qup4">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_QUP4 </props>
      <props name = "GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp2_uart4">
     <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_UART4 </props>
     <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/blsp2_qup5">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_QUP5 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> 85, 86, 87, 88, end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          3, end
        </props>
   </device>
   <device id="/dev/buses/uart/blsp2_uart5">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> BLSP2_UART5 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/ssc_qup0">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> SSC_QUP0 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/uart/ssc_uart0">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> SSC_UART0 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/ssc_qup1">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> SSC_QUP1 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/uart/ssc_uart1">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> SSC_UART1 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/qup/ssc_qup2">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> SSC_QUP2 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="/dev/buses/uart/ssc_uart2">
      <props name="PERIPH ID" type=DALPROP_ATTR_TYPE_UINT32> SSC_UART2 </props>
      <props name="GPIO range" type=DALPROP_ATTR_TYPE_BYTE_SEQ> end </props>
      <props name="RW_ACCESS_LIST" type=DALPROP_ATTR_TYPE_BYTE_SEQ>
          0xFF, end
        </props>
   </device>
   <device id="BLSP_GLOBAL_PROP">
      <props name="PERIPH_BLSP1QUP_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 13 </props>
      <props name="PERIPH_BLSP2QUP_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 13 </props>
      <props name="PERIPH_BLSP1UART_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
      <props name="PERIPH_BLSP2UART_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
      <props name="SSC_BLSPQUP_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 10 </props>
      <props name="SSC_BLSPUART_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 7 </props>
      <props name="PERIPH_GPIO_RG_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 0 </props>
      <props name="NUM_PERIPH_BLSP_CORES" type=DALPROP_ATTR_TYPE_UINT32> 2 </props>
      <props name="NUM_BLSP_MINICORES" type=DALPROP_ATTR_TYPE_UINT32> 6 </props>
      <props name="NUM_SSC_MINICORES" type=DALPROP_ATTR_TYPE_UINT32> 3 </props>
      <props name="PERIPH_SS_BLSP1_BLSP_BAM BASE" type=DALPROP_ATTR_TYPE_UINT32> 0x7544000 </props>
      <props name="PERIPH_SS_BLSP2_BLSP_BAM BASE" type=DALPROP_ATTR_TYPE_UINT32> 0x7584000 </props>
      <props name="SSC_BLSP_BLSP_BAM BASE" type=DALPROP_ATTR_TYPE_UINT32> 0x1E84000 </props>
      <props name="PERIPH_SS_BLSP1_BAMPIPE_SID_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 0x80 </props>
      <props name="PERIPH_SS_BLSP2_BAMPIPE_SID_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 0xC0 </props>
      <props name="SSC_BLSP_BAMPIPE_SID_INDEX_START" type=DALPROP_ATTR_TYPE_UINT32> 0x8 </props>
      <props name="PERIPH_SS_BLSP_SMMU_INSTANCE" type=DALPROP_ATTR_TYPE_UINT32> 24 </props>
      <props name="SSC_BLSP_SMMU_INSTANCE" type=DALPROP_ATTR_TYPE_UINT32> 25 </props>
   </device>
</driver>
