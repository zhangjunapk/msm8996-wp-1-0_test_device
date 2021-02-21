#===============================================================================
#
# Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#===============================================================================
"""Definitions for the crypto module.

**MOD_* Modules:** IDs available for discovery. These are passed to the factory.

.. data::  MOD_OPENSSL

    OpenSSL binary

.. data::  MOD_M2CRYPTO

    M2Crypto python library

.. data::  MOD_CRYPTO_CBC

    Crypto CBC binary

.. data::  MOD_CRYPTO_CCM

    Crypto CCM binary

"""


#==============================================================================
# ID for the modules available for discovery
#==============================================================================
MOD_OPENSSL = 'openssl'
MOD_M2CRYPTO = 'm2crypto'
MOD_CRYPTO_CBC = 'crypto_cbc'
MOD_CRYPTO_CCM = 'crypto_ccm'

