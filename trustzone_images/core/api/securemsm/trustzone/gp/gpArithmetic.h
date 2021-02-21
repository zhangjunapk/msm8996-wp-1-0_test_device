#ifndef GPARITHMETIC_H
#define GPARITHMETIC_H

/* ------------------------------------------------------------------------
** Includes
** ------------------------------------------------------------------------ */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "gpTypes.h"

/* ------------------------------------------------------------------------
** Defines and Typedefs
** ------------------------------------------------------------------------ */

#define QTEE_ERR_OSSL  0X1
#define QTEE_ERR_LEN   0x2

#define BIGINT_DATA_OFFSET 1
#define TEE_TAIL_SIZE 1
#define DATA_LEN_MAX ((unsigned int)(0x0FFE))

#define TEE_BigIntSizeInU32(n) ((((n)+31)/32)+2)

typedef struct
{
  int err            :  3;  /* 3 bits */
  unsigned int neg   :  1;  /* 0 is positive, 1 is negative */
  unsigned int flags :  4;
  unsigned int top   : 12;
  unsigned int dmax  : 12;  /* this means at most 32 * (1<<12-1) bits, i.e. 131040 */
} TEE_BigIntHead;

extern size_t TEE_BigIntFMMSizeInU32(size_t modulusSizeInBits);

size_t TEE_BigIntFMMContextSizeInU32(size_t modulusSizeInBits);
/*==============================================================

                  General API's

===============================================================*/
/**
 * Initialization Functions
 */

/**
 * @brief The TEE_BigIntInit function initializes bigInt
 *        and sets its represented value to zero. This function
 *        assumes that bigInt points to a memory area of len uint32_t
 *        This can be done for example with the following memory allocation
 *        TEE_BigInt *a;
 *        size_t len;
 *        len = TEE_BigIntSizeInU32(bitSize);
 *        a =(TEE_BigInt *)TEE_Malloc(len * sizeof(TEE_BigInt));
 *        ret = TEE_BigIntInit(a,len);
 *
 * @param[out]  bigInt   A pointer to TEE_BigInt to be initialized,
 *                       memory has to be allocated by caller
 * @param[in]   len      The size in uint32_t of the memory pointed to by
 *                       bigInt
 *
 * @return
 *
 */
void TEE_BigIntInit(TEE_BigInt *bigInt,
                    size_t len);

/**
 * @brief The TEE_BigIntInitFMMContext function calculates the
 *        necessary prerequisites for the fast modular
 *        multiplication and stores them in a context. This
 *        function assumes that context points to a memory area
 *        of len uint32_t This can be done for example with the
 *        following memory allocation:
 *
 *       TEE_BigIntFMMContext* ctx;
 *       size_t len = TEE_BigIntFMMContextSizeInU32(bitsize);
 *       ctx=(TEE_BigIntFMMContext)TEE_Malloc
 *       (len * sizeof(TEE_BigIntFFMContext));
 *       //Code for initializing modulus
 *       TEE_BigIntInitFMMContext (ctx, len, modulus);
 *
 *       Eventhough a fast multiplication might be
 *       mathematically defined for any modulus,
 *       normally there are restrictions in order
 *       for it to be fast on a computer. This specification
 *       mandates that all implementations
 *       MUST work for all odd moduli larger than 2 and less
 *       than 2 to the power of the implementation defined
 *       property gpd.tee.arith.maxBigIntSize.
 *
 * @param[out]  context  A pointer to the TEE_BigIntFMMContext
 *                       to be initialized, memory has to be
 *                       allocated by caller
 * @param[in]   len      The size in uint32_t of the memory pointed to by
 *                       context
 * @param[in]   modulus  The modulus, an odd integer larger than
 *                       2 and less than 2 to the power of
 *                       gpd.tee.arith.maxBigIntSize
 *
 * @return
 *
 */
void TEE_BigIntInitFMMContext(TEE_BigIntFMMContext *context,
                              size_t len, TEE_BigInt *modulus);

/**
 * @brief The TEE_BigIntInitFMM function initializes bigIntFMM
 * and sets its represented value to zero. This function assumes
 * that bigIntFMM points to a memory area of len uint32_t This
 * can be done for example with the following memory allocation:
 *
 * TEE_BigIntFMM *a;
 * size_t len;
 * len = TEE_BigIntFMMSizeInU32(modulusSizeinBits);
 * a = * (TEE_BigIntFMM *)TEE_Malloc
 * (len * sizeof(TEE_BigIntFMM));
 * TEE_InitFMMInt(a, len);
 *
 * @param[out]  bigIntFMM A pointer to the TEE_BigIntFMM
 *                        to be initialized, memory has to be
 *                        allocated by caller
 * @param[in]   len       The size in uint32_t of the memory
 *                        pointed to by bigIntFMM
 *
 * @return
 *
 */
void TEE_BigIntInitFMM(TEE_BigIntFMM *bigIntFMM, size_t len);

/**
 * Converter Functions
 */

/**
 * @brief The TEE_BigIntConvertFromOctetString function converts
 * a bufferLen byte octet string buffer into a TEE_BigInt
 * format. The octet string is in most significant byte first
 * representation. The input parameter sign will set the sign of
 * dest. It will be set to negative if sign <0 and to positive
 * if sign >=0
 *
 * @param[out]  dest      Pointer to a TEE_BigInt to hold the
 *                        result, memory has to be allocated by
 *                        caller
 * @param[in]   buffer    Pointerto the buffer containing the
 *                        octet string representation of the
 *                        integer
 * @param[in]   bufferLen The length of buffer in bytes
 * @param[in]   sign      The sign of dest is set to the sign of
 *                        sign
 *
 * @return
 * TEE_SUCCESS        : In case of success
 * TEE_ERROR_OVERFLOW : If memory allocation for the  dest is
 *                      too small
 *
 */
TEE_Result TEE_BigIntConvertFromOctetString(TEE_BigInt *dest,
                                            uint8_t *buffer, size_t bufferLen,
                                            int32_t sign);

/**
 * @brief The TEE_BigIntConvertToOctetString function converts
 *        the absolute value of an integer in TEE_BigInt format
 *        into an octet string. The octet string is written in a
 *        most significant byte first representation.
 *
 * @param[out]  buffer    Output buffer where converted octet
 *                        string representation of the integer
 *                        is written
 * @param[in]   bufferLen The length of buffer in bytes
 * @param[in]   bigInt    Pointer to the integer that will be
 *                        converted to an octet string
 *
 * @return
 * TEE_SUCCESS            : In case of success
 * TEE_ERROR_SHORT_BUFFER : If the output buffer is too small to
 *                          contain the octet string
 *
 */
TEE_Result TEE_BigIntConvertToOctetString(void *buffer, size_t *bufferLen,
                                          TEE_BigInt *bigInt);

/**
 * @brief The TEE_BigIntConvertFromS32 function sets *dest to
 *        the value shortVal
 *
 * @param[out]  dest      Pointer to a TEE_BigInt to store the
 *                        result, The result must have memory allocation
 *                        for holding a 32 bit signed value
 * @param[in]   shortVal  Input Value
 *
 * @return
 *
 */
void TEE_BigIntConvertFromS32(TEE_BigInt *dest, int32_t shortVal);


/**
 * @brief The TEE_BigIntConvertToS32 function sets *dest to the
 * value of src ,including the sign of src. If src does not fit
 * within an int32_t, the value of *dest is undefined
 *
 * @param[out]  dest      Pointer to an int32_t to store the
 *                        result
 * @param[in]   src       Pointer to an input value
 *
 * @return
 * TEE_SUCCESS            : In case of success
 * TEE_ERROR_OVERFLOW     : If the source does not fit within an
 *                          int32_t
 *
 */
TEE_Result TEE_BigIntConvertToS32(int32_t *dest, TEE_BigInt *src);

/**
 * Logical Operations
 */

/**
 * @brief The TEE_BigIntCmp function checks whether op1 > op2 ,
 * op1 == op2 , or op1 < op2
 *
 * @param[in]  op1      Pointer to first operand
 * @param[in]  op2      Pointer to second operand
 *
 * @return
 *     This function returns a negative number if op1 < op2,
 *                             0 if op1 == op2,
 *                             positive number if op1 > op2
 *
 */
int32_t TEE_BigIntCmp(TEE_BigInt *op1, TEE_BigInt *op2);

/**
 * @brief The TEE_BigIntCmpS32 function checks whether
 * op > shortVal , op == shortVal , or op < shortVal
 *
 * @param[in]  op       Pointer to first operand
 * @param[in]  shortVal Pointer to second operand
 *
 * @return
 *     This function returns a negative number if op < shortVal,
 *                             0 if op == shortVal,
 *                             positive number if op > shortVal
 *
 */
int32_t TEE_BigIntCmpS32(TEE_BigInt *op, int32_t shortVal);

/**
 * @brief The TEE_BigIntShiftRight function computes
 * |dest| = | op | >> bits and dest will have the same sign as
 * op. If bits is greater than the bit length of op then the
 * result is zero. It is allowed that dest and op point to the
 * same memory region.
 *
 * @param[out] dest     Pointer to TEE_BigInt to hold the
 *                      shifted result, memory allocated by
 *                      caller
 * @param[in]  op       Pointer to operand to be shifted
 * @param[in]  bits     Number of bits to shift
 *
 * @return
 *
 */
void TEE_BigIntShiftRight(TEE_BigInt *dest, TEE_BigInt *op,
                          size_t bits);


/**
 *  @brief The TEE_BigIntGetBit function returns the bitIndexth
 *   bit of thenatural binary representation of |src|. A true
 *   return value indicates a “1” and a false return value
 *   indicates a “0” in the bitIndexth position. If bitIndex is
 *   larger than the number of bits in op , the return value is
 *   false, thus indicating a “0
 *
 * @param[in]  src      Pointer to the integer
 * @param[in]  bitIndex The offset of the bit to be read,
 *                      starting at offset 0 for the least
 *                      significant bit
 *
 * @return
 * The Boolean value of the bitIndexth bit in | src |
 * True represents a “1” and false represents a “0”.
 *
 */
bool TEE_BigIntGetBit(TEE_BigInt *src, uint32_t bitIndex);


/**
 *  @brief The TEE_BigIntGetBitCount function returns the number
 *  of bits in the natural binary representation of |src|; that
 *  is, the magnitude of src
 *
 * @param[in]  src      Pointer to the integer
 *
 * @return
 * The number of bits in the natural binary representation of
 * |src |. If src equals zero, it will return 0
 *
 */
uint32_t TEE_BigIntGetBitCount(TEE_BigInt *src);


/**
 * Basic Arithmetic Operations
 */

/**
 *  @brief The TEE_BigIntAdd function computes dest = op1 + op2
 *  It is allowed that all or some of dest, op1, and op2 point
 *  to the same memory region.
 *  Result Size, Depending on the sign of op1 and op2, the
 *  result may be larger or smaller than op1 and op2. For the
 *  worst case, dest must have memory allocation for holding
 *  max(magnitude( op1), magnitude( op2 ))+ 1 bits
 *
 * @param[out]  dest      Pointer to TEE_BigInt to store the
 *                        result op1 + op2, pointer allocated by
 *                        caller
 * @param[in]   op1       Pointer to the first operand
 * @param[in]   op2       Pointer to the second operand
 *
 * @return
 *
 */
void TEE_BigIntAdd(TEE_BigInt *dest, TEE_BigInt *op1, TEE_BigInt *op2);

/**
 *  @brief The TEE_BigIntSub function computes dest = op1 – op2.
 *  It is allowed that all or some of dest, op1, and op2 point
 *  to the same memory region.
 *  Result Size, Depending on the sign of op1 and op2, the
 *  result may be larger or smaller than op1 and op2. For the
 *  worst case, dest must have memory allocation for holding
 *  max(magnitude( op1), magnitude( op2 ))+ 1 bits
 *
 * @param[out]  dest      Pointer to TEE_BigInt to store the
 *                        result op1 - op2
 * @param[in]   op1       Pointer to the first operand
 * @param[in]   op2       Pointer to the second operand
 *
 * @return
 *
 */
void TEE_BigIntSub(TEE_BigInt *dest, TEE_BigInt *op1, TEE_BigInt *op2);

/**
 *  @brief The TEE_BigIntNeg function negates an operand:
 *  dest = -op. It is allowed that dest and op point to the
 *  same memory region
 *  ResultSize, The result must have memory allocation for
 *  magnitude(op) bits.
 *
 * @param[out]  dest      Pointer to TEE_BigInt to store the
 *                        result -op
 * @param[in]   op        Pointer to the operand to be negated
 *
 * @return
 *
 */
void TEE_BigIntNeg(TEE_BigInt *dest, TEE_BigInt *op);

/**
 *  @brief The TEE_BigIntMul function computes
 *  dest= op1 * op2. It is allowed that all or some of dest,
 *  op1 , and op2 point to the same memory region
 *  ResultSize, The result must have memory allocation for
 *  (magnitude(op1)+magnitude(op2)) bits.
 *
 * @param[out]  dest      Pointer to TEE_BigInt to store the
 *                        result op1 * op2
 * @param[in]   op1       Pointer to the first operand
 * @param[in]   op2       Pointer to the second operand
 *
 * @return
 *
 */
void TEE_BigIntMul(TEE_BigInt *dest, TEE_BigInt *op1, TEE_BigInt *op2);

/**
 *  @brief The TEE_BigIntSquare function computes
 *  dest = op * op. . It is allowed that dest and op point to
 *  the same memory region
 *  ResultSize, The result must have memory allocation for
 *  2*magnitude(op) bits
 *
 * @param[out]  dest      Pointer to TEE_BigInt to store the
 *                        result op * op
 * @param[in]   op        Pointer to the operand to be squared
 *
 * @return
 *
 */
void TEE_BigIntSquare(TEE_BigInt *dest, TEE_BigInt *op);


/**
 *  @brief The TEE_BigIntDiv function computes dest_r and dest_q
 *  such that op1 = dest_q * op2 + dest_r. It will round dest_q
 *  towards zero and dest_r will have the same sign as op1
 *
 *  If op2 equals zero this function will execute a divide by
 *  zero operation using the normal / operator for integers.
 *  This function has the limitation that the memory pointed to
 *  by dest_q and dest_r MUST NOT overlap. However it is
 *  possible that dest_q==op1 , dest_q==op2, dest_r==op1,
 *  dest_r==op2, when dest_q and dest_r do not overlap. It is
 *  allowed to pass a NULL pointer for either dest_q or dest_r
 *  in which case the implementation MAY take advantage of the
 *  fact that it is only required to calculate either dest_q or
 *  dest_r
 *  Result Sizes, The quotient, dest_q , must have memory
 *  allocation for
 *  0 bytes if |op1 | <= |op2| and
 *  magnitude(op1)– magnitude(op2) if|op1| >| op2 |
 *  The remainder dest_r must have memory allocation to hold
 *  magnitude(op2) bits.
 *
 * @param[out]  dest_q      Pointer to a  TEE_BigInt  to store
 *                          the quotient. dest_q can be NULL
 * @param[out]  dest_r      Pointer to a  TEE_BigInt  to store
 *                          the remainder. dest_r can be NULL
 * @param[in]   op1         Pointer to the first operand, the
 *                          dividend
 * @param[in]   op1         Pointer to the second operand, the
 *                          divisor
 *
 * @return
 *
 */
void TEE_BigIntDiv(TEE_BigInt *dest_q, TEE_BigInt *dest_r, TEE_BigInt *op1, TEE_BigInt *op2);

/**
 * Modular Arithmetic Operations
 */

/**
 *  @brief The TEE_BigIntMod function computes dest = op(modn)
 *  such that 0 <= dest < n.
 *  It is allowed that dest and op point to the same memory
 *  region but n MUST point to a unique memory region. For
 *  negative op it follows the normal convention that
 *  -1 = (n-1)mod n
 *  Result Sizes, The result dest must have memory allocation
 *  for magnitude(n) bits
 *  Panic Reasons, n<2
 *
 * @param[out]  dest        Pointer to TEE_BigInt to hold the
 *                          result op * (modn). The result dest
 *                          will be in the interval [0, n - 1]
 * @param[in]   op          Pointer to the operand, to be
 *                          reduced mod n
 * @param[in]   n           Pointer to the modulus. Modulus must be larger than 1
 *
 * @return
 *
 */
void TEE_BigIntMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n);

/**
 *  @brief The TEE_BigIntAddMod function computes
 *  dest=op1+op2(modn). It is allowed that all or some of dest,
 *  op1 , and op2 point to the same memory region but n MUST
 *  point to a unique memory region.
 *  Result Sizes, The result dest must have memory allocation
 *  for magnitude(n) bits
 *  Panic Reasons, n<2
 *
 * @param[out]  dest        Pointer to TEE_BigInt to hold the
 *                          result op1 + op2 (modn).
 * @param[in]   op1         Pointer to the first operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   op2         Pointer to the second operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   n           Pointer to the modulus. Modulus must be larger than 1
 *
 * @return
 *
 */
void TEE_BigIntAddMod(TEE_BigInt *dest, TEE_BigInt *op1, TEE_BigInt *op2, TEE_BigInt *n);

/**
 *  @brief The TEE_BigIntSubMod function computes
 *  dest = op1 - op2 (modn)
 *  It is allowed that all or some of dest , op1, and op2
 *  points to the same memory region but n MUST point to a
 *  unique memory region.
 *  Result Sizes, The result dest must have memory allocation
 *  for magnitude(n) bits
 *  Panic Reasons, n<2
 *
 * @param[out]  dest        Pointer to TEE_BigInt to hold the
 *                          result op1 - op2 (modn).
 * @param[in]   op1         Pointer to the first operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   op2         Pointer to the second operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   n           Pointer to the modulus. Modulus must be larger than 1
 *
 * @return
 *
 */
void TEE_BigIntSubMod(TEE_BigInt *dest, TEE_BigInt *op1, TEE_BigInt *op2, TEE_BigInt *n);

/**
 *  @brief The TEE_BigIntMulMod function computes
 *  dest=op1*op2(modn). It is allowed that all or some of dest,
 *  op1 , and op2 point to the same memory region but n  MUST
 *  point to a unique memory region
 *  Result Sizes, The result dest must have memory allocation
 *  for magnitude(n) bits
 *  Panic Reasons, n<2
 *
 * @param[out]  dest        Pointer to TEE_BigInt to hold the
 *                          result op1 * op2 (modn).
 * @param[in]   op1         Pointer to the first operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   op2         Pointer to the second operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   n           Pointer to the modulus. Modulus must be larger than 1
 *
 * @return
 *
 */
void TEE_BigIntMulMod(TEE_BigInt *dest, TEE_BigInt *op1, TEE_BigInt *op2, TEE_BigInt *n);

/**
 *  @brief The TEE_BigIntSquareMod function computes
 *  dest = op * op (modn). It is allowed that dest and op1 point
 *  to the same memory region but n MUST point to a unique
 *  memory region
 *  Result Sizes, The result dest must have memory allocation
 *  for magnitude(n) bits
 *  Panic Reasons, n<2
 *
 * @param[out]  dest        Pointer to TEE_BigInt to hold the
 *                          result op * op (modn).
 * @param[in]   op          Pointer to the operand, must
 *                          be in the interval [0, n - 1]
 * @param[in]   n           Pointer to the modulus. Modulus must be larger than 1
 *
 * @return
 *
 */
void TEE_BigIntSquareMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n);

/**
 *  @brief The TEE_BigIntInvMod function computes dest such that
 *         dest * op = 1 (modn). It is allowed that dest and op
 *  point to the same memory region. This function assumes that
 *  gcd(op,n) is equal to 1, which can be checked by using the
 *  function in section 8.10.1. If gcd(op,n) is greater than 1
 *  then the result is unreliable
 *  Result Sizes, The result dest must have memory allocation
 *  for magnitude(n) bits
 *  Panic Reasons, n<2, op = 0
 *
 * @param[out]  dest        Pointer to TEE_BigInt to hold the
 *                          result op^-1 (modn).
 * @param[in]   op          Pointer to the operand, must
 *                          be in the interval [1, n - 1]
 * @param[in]   n           Pointer to the modulus. Modulus must be larger than 1
 *
 * @return
 *
 */
void TEE_BigIntInvMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n);

/**
 * Other Arithmetic Operations
 */

/**
 *  @brief The TEE_BigIntRelativePrime function
 *  determines whether gcd(op1, op2)==1.
 *  It is allowed that op1 and op2 point to the same memory
 *  region
 *
 * @param[in]   op1          Pointer to the first operand
 * @param[in]   op2          Pointer to the second operand
 *
 * @return
 * true if gcd(op1,op2) == 1
 * false otherwise
 *
 */
bool TEE_BigIntRelativePrime(TEE_BigInt *op1, TEE_BigInt *op2);

/**
 *  @brief The TEE_BigIntComputeExtendedGcd function computes
 *  the greatest common divisor of the input parameters op1 and
 *  op2. Furthermore it computes the coefficients u and v such
 *  that u*op1+v*op2 == gcd It is allowed that op1 and op2 point
 *  to the same memory region. It is allowed that u , v , or
 *  both can be NULL. If both of them are NULL then the function
 *  only computes the gcd of op1 and op2.
 *  ResultSizes, The gcd result must be able to hold
 *  max(magnitude(op1),magnitude( op2 )) bits
 *  The absolute value of u is in the range [0, |op2/gcd|-1]
 *  The absolute value of v is in the range [0, |op2/gcd|-1]
 *
 * @param[out]   gcd          Pointer to TEE_BigInt to hold the
 *                            greatest common divisor of op1 and
 *                            op2
 * @param[out]   u            Pointer to TEE_BigInt to hold the
 *                            first coefficient
 * @param[out]   v            Pointer to TEE_BigInt to hold the
 *                            second coefficient
 * @param[in]    op1          Pointer to the first operand
 * @param[in]    op2          Pointer to the second operand
 *
 * @return
 *
 */
void TEE_BigIntComputeExtendedGcd(TEE_BigInt *gcd, TEE_BigInt *u,
                                  TEE_BigInt *v, TEE_BigInt *op1,
                                  TEE_BigInt *op2);

/**
 *  @brief The TEE_BigIntComputeExtendedGcd function computes
 *  the greatest common divisor of the input parameters op1 and
 *  op2. Furthermore it computes the coefficients u and v such
 *  that u*op1+v*op2 == gcd It is allowed that op1 and op2 point
 *  to the same memory region. It is allowed that u , v , or
 *  both can be NULL. If both of them are NULL then the function
 *  only computes the gcd of op1 and op2.
 *  ResultSizes, The gcd result must be able to hold
 *  max(magnitude(op1),magnitude( op2 )) bits
 *  The absolute value of u is in the range [0, |op2/gcd|-1]
 *  The absolute value of v is in the range [0, |op2/gcd|-1]
 *
 * @param[in] op              Candidate number that is tested
 *                            for primality
 * @param[in] confidenceLevel The desired confidence level for a
 *                            non conclusive test. This
 *                            parameter (usually) maps to the
 *                            number of iterations and thus to
 *                            the running time of the test.
 *                            Values smaller than 80 will be
 *                            treated as 80
 *
 * @return
 *  0 : If op is a composite number
 *  1 : If op is a prime number
 *  -1: If the test is nonconclusive but the probability that op
 *  is composite is less than 2^(-confidenceLevel)
 *
 */
int32_t TEE_BigIntIsProbablePrime(TEE_BigInt *op, uint32_t confidenceLevel);

/**
 * Fast Modular Multiplication Operations
 */

/**
 *  @brief The TEE_BigIntConvertToFMM function converts src in
 *  to a representation suitable for doing fast modular
 *  multiplication. If the operation is successful , the result
 *  will be written in implementation specific format into
 *  the buffer dest , which must have been allocated by the TA
 *  and initialized using TEE_BigIntInitFMM
 *
 * @param[out]   dest         Pointer to an initialized
 *                            TEE_BigIntFMM memory area
 * @param[in]    src          Pointer to TEE_BigInt to convert
 * @param[in]    n            Pointer to modulus
 * @param[in]    context      Pointer to the context previously
 *                            initialized using
 *                            TEE_BigIntInitFMMContext
 *
 * @return
 *
 */
void TEE_BigIntConvertToFMM(TEE_BigIntFMM *dest, TEE_BigInt *src,
                            TEE_BigInt *n, TEE_BigIntFMMContext *context);

/**
 *  @brief The TEE_BigIntConvertFromFMM function converts src in
 *  the fast modular multiplication representation back to a
 *  TEE_BigIntrepresentation.
 *
 * @param[out]   dest         Pointer to an initialized
 *                            TEE_BigInt memory area to hold the
 *                            converted result
 * @param[in]    src          Pointer to a TEE_BigIntFMM holding
 *                            the value in the fast modular
 *                            multiplication representation
 * @param[in]    n            Pointer to modulus
 * @param[in]    context      Pointer to the context previously
 *                            initialized using
 *                            TEE_BigIntInitFMMContext
 *
 * @return
 *
 */
void TEE_BigIntConvertFromFMM(TEE_BigInt *dest, TEE_BigIntFMM *src,
                              TEE_BigInt *n, TEE_BigIntFMMContext *context);

/**
 *  @brief The TEE_BigIntComputeFMM function calculates
 *  dest = op 1 * op2 in the fast modular multiplication
 *  representation. The pointers dest, op1 and op2 MUST all
 *  point to a TEE_BigIntFMM which has been previously
 *  initialized with the same modulus and context as used in
 *  this function call; otherwise the result is undefined. It is
 *  allowed that all or some of dest, op1, and op2 point to the
 *  same memory region.
 *
 * @param[out]   dest         Pointer to TEE_BigIntFMM to hold
 *                            the result op1 * op2 in the fast
 *                            modular multiplication
 *                            representation
 * @param[in]    op1          Pointer to the first operand
 * @param[in]    op2          Pointer to the second operand
 * @param[in]    n            Pointer to modulus
 * @param[in]    context      Pointer to the context previously
 *                            initialized using
 *                            TEE_BigIntInitFMMContext
 *
 * @return
 *
 */
void TEE_BigIntComputeFMM(TEE_BigIntFMM *dest, TEE_BigIntFMM *op1,
                          TEE_BigIntFMM *op2, TEE_BigInt *n, TEE_BigIntFMMContext *context);

#endif /* GPARITHMETIC_H */

