# ===============================================================================
#
#  Copyright (c) 2013-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#
# ===============================================================================

"""
Created on Mar 18, 2013

@author: francisg

This module provides a rule class for secimage config rules.
"""

from sectools.common.utils.c_data import get_duplicates
from sectools.common.utils.c_logging import logger
from sectools.common.utils.c_rule import CoreRuleBase
from sectools.common.utils import c_path
from auto_gen_xml_config import complex_metadata, complex_signing, complex_images_list, complex_general_properties
from sectools.features.isc.cfgparser.defines import JTAGID_SIGN_IDS, IOT_MRC_CHIPSETS

MAX_NUM_SERIALS = 201

class ConfigRulesManager(CoreRuleBase):
    """
    This is the main SecImage config rules manager that runs the rules
    """

    def __init__(self):
        self.configs = {}
        self.configs['signing'] = _Signing()
        self.configs['images_list'] = _ImageList()
        self.configs['general_properties'] = _GeneralProperties()
        self.configs['metadata'] = None
        self.configs['parsegen'] = None
        self.configs['post_process'] = None
        pass

    def validate(self, data, data_dict):
        retval = True
        error_str = ''


        # based on the dictionary structure, go through each section from root
        for name in data_dict:
            # check if there's a registered rule object for this config section
            if name in self.configs and self.configs[name] is not None:
                config = getattr(data.root, name)
                if name == 'general_properties':
                    ret, error = self.configs[name].validate(config, getattr(data.root, 'signing'))
                elif name == 'images_list':
                    ret, error = self.configs[name].validate(config, getattr(data.root, 'general_properties'), getattr(data.root, 'metadata'))
                else:
                    ret, error = self.configs[name].validate(config, config)

                # accumulate the return values
                if ret == False:
                    retval &= ret
                    error_str += '\n\n <%s>%s' % (name, error)

        if retval == False:
            raise RuntimeError('\nSecImage config validation failed with following error(s): %s' % error_str)



class _Signing(object):
    """
    Defines the rules for signing default attributes
    """

    def __init__(self):
        pass

    def validate(self, signing, *args):
        assert(isinstance(signing, complex_signing))

        retval = True
        error_str = ''
        '''
        self.debug = debug
        '''

        # debug rule
        # self.debug = default_attr.get_debug()
        # if (self.debug is None) or (not int(self.debug, 16)):
        #    retval = False
        #    error_str += '\n debug is not set: %s' %self.debug

        # signing paths for trust_keystore and keystore_file from cass_signer_attributes
        cass_signer_attr = signing.get_signer_attributes().get_cass_signer_attributes()
        if cass_signer_attr is not None:
            # keystore rule, they must all exists
            if cass_signer_attr.get_server():
                self.trust_keystore = cass_signer_attr.get_server().get_trust_keystore()
                if c_path.validate_file(self.trust_keystore) is False:
                    retval = False
                    error_str += '\n trust_keystore is invalid, path = %s' % self.trust_keystore

            self.keystore_file = cass_signer_attr.get_user_identity().get_keystore_file()
            if self.keystore_file and c_path.validate_file(self.keystore_file) is False:
                retval = False
                error_str += '\n keystore_file is invalid, path = %s' % self.keystore_file

        return retval, error_str


class _GeneralProperties(object):
    """
    Defines the rules for general properties
    """

    def __init__(self):
        pass

    def validate(self, general_properties, *args):
        assert(isinstance(general_properties, complex_general_properties))

        retval = True
        error_str = ''

        # check dependency rule for num_root_certs
        # need to make sure the multirootcert's index doesn't go beyond avail num_root_certs
        num_root_certs = general_properties.get_num_root_certs()

        if num_root_certs == 0:
            retval = False
            error_str += '\n num_root_certs must not be 0'

        if num_root_certs > 16:
            retval = False
            error_str += '\n num_root_certs must not be greater than 16'

        if not (general_properties.mrc_index < num_root_certs):
            retval = False
            error_str += '\n Index out of range: mrc_index=%s, num_root_certs=%s' % (general_properties.mrc_index, num_root_certs)

        return retval, error_str


class _ImageList(object):
    """
    Defines the rules for image parameters to be signed
    """

    def __init__(self):
        self.mask_warning = True
        self.version_warning = True
        pass

    def validate(self, images, *args):
        assert(isinstance(images, complex_images_list))

        image_list = images.get_image()
        retval = True
        error_str = ''

        # expect args[0] to be instance of signing
        # the following default signing attributes are checked if signing is TCG
        assert(isinstance(args[0], complex_general_properties))
        general_properties = args[0]
        default_sw_id = general_properties.get_sw_id()
        default_app_id = general_properties.get_app_id()
        default_rot_en = general_properties.get_rot_en()
        default_crash_dump = general_properties.get_crash_dump()
        default_msm_part = general_properties.get_msm_part()
        default_soc_hw_version = general_properties.get_soc_hw_version()
        default_mask_soc_hw_version = general_properties.get_mask_soc_hw_version()
        default_in_use_soc_hw_version = general_properties.get_in_use_soc_hw_version()
        default_use_serial_number_in_signing = general_properties.get_use_serial_number_in_signing()
        default_serial_number = general_properties.get_serial_number()
        default_revocation_enablement = general_properties.get_revocation_enablement()
        default_activation_enablement = general_properties.get_activation_enablement()
        default_oem_id = general_properties.get_oem_id()
        default_model_id = general_properties.get_model_id()
        default_debug = general_properties.get_debug()
        default_debug_serials = general_properties.get_debug_serials().get_serial() if general_properties.get_debug_serials() is not None else []
        default_oid = general_properties.get_object_id()
        default_oid_min = default_oid.min if default_oid is not None else None
        default_oid_max = default_oid.max if default_oid is not None else None
        default_hash_algorithm = general_properties.get_hash_algorithm()
        default_oem_id_independent = general_properties.get_oem_id_independent()
        default_hmac = general_properties.get_hmac()
        default_rsa_padding = general_properties.get_rsa_padding()

        assert(isinstance(args[1], complex_metadata))
        metadata = args[1]
        chipset = metadata.get_chipset()

        for image in image_list:
            sign_id = image.get_sign_id()
            overrides = image.get_general_properties_overrides()

            sw_id = overrides.get_sw_id() if overrides.get_sw_id() is not None else default_sw_id
            app_id = overrides.get_app_id() if overrides.get_app_id() is not None else default_app_id
            rot_en = overrides.get_rot_en() if overrides.get_rot_en() is not None else default_rot_en
            crash_dump = overrides.get_crash_dump() if overrides.get_crash_dump() is not None else default_crash_dump
            msm_part = overrides.get_msm_part() if overrides.get_msm_part() is not None else default_msm_part
            soc_hw_version = overrides.get_soc_hw_version() if overrides.get_soc_hw_version() is not None else default_soc_hw_version
            mask_soc_hw_version = overrides.get_mask_soc_hw_version() if overrides.get_mask_soc_hw_version() is not None else default_mask_soc_hw_version
            in_use_soc_hw_version = overrides.get_in_use_soc_hw_version() if overrides.get_in_use_soc_hw_version() is not None else default_in_use_soc_hw_version
            use_serial_number_in_signing = overrides.get_use_serial_number_in_signing() if overrides.get_use_serial_number_in_signing() is not None else default_use_serial_number_in_signing
            serial_number = overrides.get_serial_number() if overrides.get_serial_number() is not None else default_serial_number
            revocation_enablement = overrides.get_revocation_enablement() if overrides.get_revocation_enablement() is not None else default_revocation_enablement
            activation_enablement = overrides.get_activation_enablement() if overrides.get_activation_enablement() is not None else default_activation_enablement
            oem_id = overrides.get_oem_id() if overrides.get_oem_id() is not None else default_oem_id
            model_id = overrides.get_model_id() if overrides.get_model_id() is not None else default_model_id
            debug = overrides.get_debug() if overrides.get_debug() is not None else default_debug
            debug_serials = list(overrides.get_debug_serials().get_serial() if overrides.get_debug_serials() is not None else default_debug_serials)
            override_oid = overrides.get_object_id() if overrides.get_object_id() is not None else default_oid
            oid_min = override_oid.min if override_oid is not None else default_oid_min
            oid_max = override_oid.max if override_oid is not None else default_oid_max
            oem_id_independent = overrides.get_oem_id_independent() if overrides.get_oem_id_independent() is not None else default_oem_id_independent
            rsa_padding = overrides.get_rsa_padding() if overrides.get_rsa_padding() is not None else default_rsa_padding
            hash_algorithm = overrides.get_hash_algorithm() if overrides.get_hash_algorithm() is not None else default_hash_algorithm

            # RSAPSS requires SHA256 hash
            if rsa_padding == 'pss':
                if hash_algorithm is not None and hash_algorithm != 'sha256':
                    retval = False
                    error_str += '\n RSAPSS requires SHA256 hash. sign_id=%s, hash_algorithm=%s' % (sign_id, hash_algorithm)

            # OEM_ID check for non-TCG CASS use case: OEM_ID 0x0000 is invalid
            if general_properties.get_selected_signer() == 'cass' and general_properties.get_cass_capability().startswith('secboot'):
                if int(oem_id, 16) == 0:
                    retval = False
                    error_str += '\n sign_id=%s: oem_id 0x0000 is invalid for CASS signing' % (sign_id)

            # TZ apps rule, must have app_id set
            if (int(sw_id, 16) & 0xFFFFFFFF) == 0xC:
                if app_id is None or int(app_id, 16) == 0:
                    retval = False
                    error_str += '\n app_id is not set for TZ apps: sign_id=%s, sw_id=%s' % (sign_id, sw_id)
            #TODO: app_id is image specific, current rule checking will cover all the images in the config file
            """
            # other than tz, app_id must not be present
            else:
                if app_id is not None:
                    retval = False
                    error_str += '\n app_id is set for Non-TZ image: sign_id=%s, sw_id=%s, app_id=%s' % (sign_id, sw_id, app_id)
            """

            # crash_dump rule, LSB 32bits must not be greater than 1
            if crash_dump is not None and (int(crash_dump, 16) & 0xFFFFFFFF) > 1:
                retval = False
                error_str += '\n crash_dump 32bit LSB must be 0 or 1: sign_id=%s, crash_dump=%s' % (sign_id, crash_dump)

            # rot_en rule, LSB 32bits must not be greater than 1
            if rot_en is not None and (int(rot_en, 16) & 0xFFFFFFFF) > 1:
                retval = False
                error_str += '\n rot_en 32bit LSB must be 0 or 1: sign_id=%s, rot_en=%s' % (sign_id, rot_en)

            # At least one of MSM_PART or SOC_HW_VERSION must be specified
            if msm_part is None and soc_hw_version is None:
                retval = False
                error_str += "\nsign_id=%s: MSM_PART and SOC_HW_VERSION are missing from config. At least one must exist" % (sign_id)

            # Check if any sign_ids in SOC-chipset need to sign with JTAG ID
            if soc_hw_version is not None and (chipset in JTAGID_SIGN_IDS):
                if sign_id in JTAGID_SIGN_IDS[chipset]:

                    # Use JTAG instead of SOC_HW_VERSION #
                    if msm_part is None:
                        retval = False
                        error_str += "\nsign_id=%s: MSM_PART must be used to sign this image but MSM_PART is missing" % (sign_id)

                    image.general_properties_overrides.in_use_soc_hw_version = 0

            # Assure in_use_soc_hw_version exists if both msm_part and soc_hw_version are given
            if soc_hw_version is not None and msm_part is not None:
                if in_use_soc_hw_version is None:
                    retval = False
                    error_str += "\nsign_id=%s: IN_USE_SOC_HW_VERSION must exist to chose between MSM_PART and SOC_HW_VERSION" % (sign_id)

            # in_use_soc_hw_version must exist with soc_hw_version
            if soc_hw_version is not None and in_use_soc_hw_version is None:
                retval = False
                error_str += "\nsign_id=%s: IN_USE_SOC_HW_VERSION must be set when using SOC_HW_VERSION" % (sign_id)

            # Make sure in_use_soc_hw_version's specification exists
            if in_use_soc_hw_version == 1 and soc_hw_version is None:
                retval = False
                error_str += "\nsign_id=%s: IN_USE_SOC_HW_VERSION specifies SOC_HW_VERSION is used but SOC_HW_VERSION tag is missing" % (sign_id)
            elif in_use_soc_hw_version == 0 and msm_part is None:
                retval = False
                error_str += "\nsign_id=%s: IN_USE_SOC_HW_VERSION specifies SOC_HW_VERSION is NOT used but MSM_PART tag is missing" % (sign_id)

            # mask_soc_hw_version may only exist if soc_hw_version exists
            if soc_hw_version is None:
                if mask_soc_hw_version is not None:
                    retval = False
                    error_str += "\nsign_id=%s: MASK_SOC_HW_VERSION can not exist without the SOC_HW_VERSION tag" % (sign_id)

            if mask_soc_hw_version is not None and in_use_soc_hw_version == 1 and self.mask_warning is True:
                logger.warning("The mask_soc_hw_version field is set and will mask the soc_hw_version during signing. Please ensure this is the desired result.")
                self.mask_warning = False

            # use_serial_number_in_signing rule: serial number must be set
            if use_serial_number_in_signing == 1:
                if serial_number is None or int(serial_number, 16) == 0:
                    retval = False
                    error_str += '\nsign_id=%s: serial_number must be set when use_serial_number_in_signing is enabled' % (sign_id)

            if revocation_enablement is not None:
                if chipset not in IOT_MRC_CHIPSETS:
                    raise RuntimeError("revocation_enablement is only allowed to be set in: " + ', '.join(IOT_MRC_CHIPSETS))

                if int(revocation_enablement, 16) & 0xFFFFFFFF not in [0, 1, 2]:
                    retval = False
                    error_str += '\nsign_id=%s: revocation_enablement must ends with 0, 1 or 2. revocation_enablement = %s' % (sign_id, revocation_enablement)

                # If last 8 bytes = 0 (disabled), then override revocation field to None (since OU field wont be present)
                elif int(revocation_enablement, 16) & 0xFFFFFFFF == 0:
                    image.general_properties_overrides.revocation_enablement = None

                # if last 8 bytes = 1, for enabling revocation without binding it to the serial number, use as is
                # if last 8 bytes = 2, for enabling revocation with binding it to the serial number, check upper 8 bytes
                elif int(revocation_enablement, 16) & 0xFFFFFFFF00000000 == 0 and int(revocation_enablement, 16) & 0xFFFFFFFF == 2:
                    retval = False
                    error_str += '\nsign_id=%s: to enable revocation with binding to serial number, upper 8 bytes must contain serial number. revocation_enablement = %s' \
                                    % (sign_id, revocation_enablement)

            if activation_enablement is not None:
                if chipset not in IOT_MRC_CHIPSETS:
                    raise RuntimeError("activation_enablement is only allowed to be set in: " + ', '.join(IOT_MRC_CHIPSETS))

                if int(activation_enablement, 16) & 0xFFFFFFFF not in [0, 1, 2]:
                    retval = False
                    error_str += '\nsign_id=%s: activation_enablement must ends with 0, 1 or 2. activation_enablement = %s' % (sign_id, activation_enablement)

                # If last 8 bytes = 0 (disabled), then override activation field to None (since OU field wont be present)
                elif int(activation_enablement, 16) & 0xFFFFFFFF == 0:
                    image.general_properties_overrides.activation_enablement = None

                # if last 8 bytes = 1, for enabling activation without binding it to the serial number, use as is
                # if last 8 bytes = 2, for enabling activation with binding it to the serial number, check upper 8 bytes
                elif int(activation_enablement, 16) & 0xFFFFFFFF00000000 == 0 and int(activation_enablement, 16) & 0xFFFFFFFF == 2:
                    retval = False
                    error_str += '\nsign_id=%s: to enable activation with binding to serial number, upper 8 bytes must contain serial number. activation_enablement = %s' \
                                    % (sign_id, activation_enablement)

            # oem independent rule: if oem_id_independent = 1 make oem_id=1 regardless
            if oem_id_independent == 1:
                image.general_properties_overrides.oem_id = '0x0001'
                image.general_properties_overrides.model_id = '0x0000'

            # Format and validate debug
            if debug is not None:
                if len(debug) > 18:
                    retval = False
                    error_str += '\n Debug value must be 18 characters or less in length'
                elif len(debug) < 18:
                    padding_len = 18 - len(debug)
                    debug = debug[:2] + "0"*padding_len + debug[2:]
                    image.general_properties_overrides.debug = debug

            # Validate the debug_serials
            if len(debug_serials) > 0:
                if debug is None:
                    retval = False
                    error_str += '\n Debug serials were provides but debug field was not provided'
                elif debug[:-8] in debug_serials:
                    retval = False
                    error_str += '\n Duplicate serial value of %s in debug and debug_serials' % debug[:-8]
                else:
                    debug_serials.append(debug[:-8])

                if len(debug_serials) > MAX_NUM_SERIALS:
                    retval = False
                    error_str += '\n %d provided serials exceeds allowed maximum of %d' % (len(debug_serials), MAX_NUM_SERIALS)

                for serial in debug_serials:
                    try:
                        if serial[: 2] != '0x' or len(serial) != 10 or serial == "0x00000000":
                            raise ValueError('Serial is malformed')
                        int(serial, 16)
                    except ValueError:
                        retval = False
                        error_str += '\n Provided serial value %s is not a valid serial number' % serial

                duplicates = get_duplicates(debug_serials)
                if len(duplicates) > 0:
                    retval = False
                    if len(duplicates) == 1:
                        error_str += '\n debug_serials contains a duplicate of the following serial number:'
                    else:
                        error_str += '\n debug_serials contains duplicates of the following serial numbers:'
                    for serial in duplicates:
                        error_str += ' ' + serial

            # TCG rules
            if oid_min is not None and oid_max is None:
                retval = False
                error_str += '\n In sign_id = %s, %s min is set, must also set max' % (sign_id, default_oid.name)
            elif oid_max is not None and oid_min is None:
                retval = False
                error_str += '\n In sign_id = %s, %s max is set, must also set min' % (sign_id, default_oid.name)
            elif default_oid is not None:
                # Move the min > max checking to signer. It should be validated after valid 32
                # bit integer is checked. Otherwise, int() conversion will throw an exception

                oid_min_config_str = oid_min
                oid_max_config_str = oid_max
                if oid_min_config_str and oid_max_config_str:
                    oid_min = int(oid_min, 16) if '0x' in oid_min else int(oid_min)
                    oid_max = int(oid_max, 16) if '0x' in oid_max else int(oid_max)

                    if oid_min > oid_max:
                        retval = False
                        error_str += '\n For sign_id = %s, %s min must be less than max, min=%s max=%s' \
                                        % (sign_id, default_oid.name, oid_min_config_str, oid_max_config_str)
                if int(sw_id, 16) != 0:
                    retval = False
                    error_str += '\n For %s sign_id = %s, sw_id must be 0, sw_id = %s' \
                                    % (default_oid.name, sign_id, sw_id)
                if int(msm_part, 16) != 0:
                    retval = False
                    error_str += '\n For %s sign_id = %s, msm_part must be 0, msm_part = %s' \
                                    % (default_oid.name, sign_id, msm_part)
                if int(oem_id, 16) != 0:
                    retval = False
                    error_str += '\n For %s sign_id = %s, oem_id must be 0, oem_id = %s' \
                                    % (default_oid.name, sign_id, oem_id)
                if int(model_id, 16) != 0:
                    retval = False
                    error_str += '\n For %s sign_id = %s, model_id must be 0, model_id = %s' \
                                    % (default_oid.name, sign_id, model_id)
                if int(debug, 16) != 2:
                    retval = False
                    error_str += '\n For %s sign_id = %s, debug must be 2, debug = %s' \
                                    % (default_oid.name, sign_id, debug)

        return retval, error_str


