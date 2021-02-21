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
   <device id="/dev/buses/qup/blsp1_qup0_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7575000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x07563000, 0x07564000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp1_uart0_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x756F000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x07557000, 0x07558000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp1_qup1_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7576000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x07565000, 0x07566000, end</var_seq>
   </device>
   <device id="/dev/buses/uart/blsp1_uart1_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7570000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x07559000, 0x0755A000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp1_qup2_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7577000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x07567000, 0x07568000, end</var_seq>
   </device>
   <device id="/dev/buses/uart/blsp1_uart2_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7571000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x0755B000, 0x0755C000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp1_qup3_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7578000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x07569000, 0x0756A000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp1_uart3_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7572000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x0755D000, 0x0755E000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp1_qup4_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7579000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x0756B000, 0x0756C000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp1_uart4_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7573000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x0755F000,0x07560000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp1_qup5_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x757A000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x0756D000, 0x0756E000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp1_uart5_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x7574000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x07561000, 0x07562000, end </var_seq>
   </device>
  <device id="/dev/buses/qup/blsp2_qup0_cfg">
     <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B5000 </props>
     <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x075A3000, 0x075A4000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp2_uart0_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75AF000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x07597000, 0x07598000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp2_qup1_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B6000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x075A5000, 0x075A6000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp2_uart1_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75b0000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x07599000, 0x0759A000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp2_qup2_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B7000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x075A7000, 0x075A8000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp2_uart2_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B1000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x0759B000, 0x0759C000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp2_qup3_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B8000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x075A9000, 0x075AA000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp2_uart3_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B2000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x0759D000, 0x0759E000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp2_qup4_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B9000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x075AB000,0x075AC000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp2_uart4_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B3000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x0759F000, 0x075A0000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/blsp2_qup5_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75BA000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x075AD000, 0x075AE000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/blsp2_uart5_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x75B4000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x075A1000, 0x075A2000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/ssc_qup0_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1EB5000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x01E9D000, 0x01E9E000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/ssc_uart0_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1EAF000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ> 0x01E97000, 0x01E98000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/ssc_qup1_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1EB6000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x01E9F000, 0x01EA0000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/ssc_uart1_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1EB0000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x01E99000, 0x01E9A000, end </var_seq>
   </device>
   <device id="/dev/buses/qup/ssc_qup2_cfg">
      <props name="QUP_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1EB7000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x01EA1000, 0x01EA2000, end </var_seq>
   </device>
   <device id="/dev/buses/uart/ssc_uart2_cfg">
      <props name="UART_OFFSET" type=DALPROP_ATTR_TYPE_UINT32> 0x1EB1000 </props>
      <var_seq name="BAM pipe offsets" type=DALPROP_ATTR_TYPE_UINT32_SEQ>0x01E9B000,0x01E9B000, end </var_seq>
   </device>
</driver>
