# ===============================================================================
#
#  Copyright (c) 2013-2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#
# ===============================================================================
import re

from sectools.common.crypto import crypto_functions
from sectools.common.utils import c_misc
from sectools.common.utils.c_attribute import Attribute
from sectools.common.utils.c_misc import properties_repr


class Certificate(object):
    SIGNATTR_HW_ID = "HW_ID"
    SIGNATTR_SOC_HW_VERSION = "SOC_HW_VERSION"
    SIGNATTR_MASK_SOC_HW_VERSION = "MASK_SOC_HW_VERSION"
    SIGNATTR_IN_USE_SOC_HW_VERSION = "IN_USE_SOC_HW_VERSION"
    SIGNATTR_USE_SERIAL_NUMBER_IN_SIGNING = "USE_SERIAL_NUMBER_IN_SIGNING"
    SIGNATTR_OEM_ID_INDEPENDENT = "OEM_ID_INDEPENDENT"
    SIGNATTR_SN = "SN"
    SIGNATTR_OEM_ID = "OEM_ID"
    SIGNATTR_MODEL_ID = "MODEL_ID"
    SIGNATTR_SW_ID = "SW_ID"
    SIGNATTR_DEBUG = "DEBUG"
    SIGNATTR_CRASH_DUMP = "CRASH_DUMP"
    SIGNATTR_ROT_EN = "ROT_EN"
    SIGNATTR_APP_ID = "APP_ID"
    SIGNATTR_SW_SIZE = "SW_SIZE"
    SIGNATTR_SHA256 = "SHA256"
    SIGNATTR_TCG_MIN = "TCG_MIN"
    SIGNATTR_TCG_MAX = "TCG_MAX"
    SIGNATTR_FID_MIN = "FID_MIN"
    SIGNATTR_FID_MAX = "FID_MAX"
    SIGNATTR_ROOT_CERT_SEL = "ROOT_CERT_SEL"
    SIGNATTR_REVOCATION_ENABLEMENT = "REVOCATION_ENABLEMENT"
    SIGNATTR_ACTIVATION_ENABLEMENT = "ACTIVATION_ENABLEMENT"

    # OID defined for TCG in attestation certificate
    TCG_OID = "1.3.6.1.4.1.1449.9.6.3"
    TCG_OID_NAME = "tcg"

    FID_OID = "1.3.6.1.4.1.1449.10.1"
    FID_OID_NAME = "feature_id"

    '''
    Certificate class
    inputs:
        cert_blob: certificate binary blob (DER/PEM)
        path: certificate binary path (DER/PEM)
        cert_blob will take precedence of cert_path

    Attributes for query:
        tcg_min
        tcg_max
    '''
    def __init__(self, cert_blob=None, path=None):
        if cert_blob is not None:
            self.cert_blob = cert_blob
        elif path is not None:
            self.cert_blob = c_misc.load_data_from_file(path)
        else:
            raise RuntimeError("cert_blob and path cannot be both None")

        self.certificate_text = crypto_functions.get_certificate_text_from_binary(self.cert_blob)
        self.asn1_text = crypto_functions.get_asn1_text_from_binary(self.cert_blob)

        self.tcg_min, self.tcg_max = self._get_oid(self.asn1_text, name="tcg")
        self.fid_min, self.fid_max = self._get_oid(self.asn1_text, name="feature_id")

    @classmethod
    def GetOIDByName(cls, name):
        if name == cls.TCG_OID_NAME:
            oid = cls.TCG_OID
        elif name == cls.FID_OID_NAME:
            oid = cls.FID_OID
        else:
            raise RuntimeError("OID name={0} is not supported".format(name))

        return oid

    @classmethod
    def GetOIDAttrName(cls, name):
        if name == cls.TCG_OID_NAME:
            attr_min = cls.SIGNATTR_TCG_MIN
            attr_max = cls.SIGNATTR_TCG_MAX
        elif name == cls.FID_OID_NAME:
            attr_min = cls.SIGNATTR_FID_MIN
            attr_max = cls.SIGNATTR_FID_MAX
        else:
            raise RuntimeError("OID name={0} is not supported".format(name))

        return attr_min, attr_max

    def _get_oid(self, asn1_text, name):
        _min = None
        _max = None

        oid = self.GetOIDByName(name)

        oid_ext = asn1_text.find(oid)
        if oid_ext > -1:
            oid_pattern = re.compile(r'\[HEX DUMP\]:([a-fA-F\d]+)')
            oid_match = oid_pattern.search(asn1_text[oid_ext:])
            if oid_match is not None:
                # tcg_str = tcg_match.group(1).replace(' ', '') #remove spaces
                oid_str = oid_match.group(1)
                _min = Attribute.init(num_bits=32, string="0x" + oid_str[0:8])
                _max = Attribute.init(num_bits=32, string="0x" + oid_str[8:16])

        return _min, _max

    def _get_ou_attr(self, attr_name, certificate_text):
        attr = None

        ou_id = Certificate_OU.GetID(attr_name)
        attr_pattern = re.compile(r'OU={0} ([a-fA-F\d]+) {1}'.format(ou_id, attr_name))
        attr_match = attr_pattern.search(certificate_text)
        if attr_match is not None:
            attr_str = attr_match.group(1)
            if len(attr_str) in [4, 8, 16]:
                attr = Attribute.init(num_bits=len(attr_str) * 4, string="0x" + attr_str)
            else:
                attr = attr_str

        return attr

    # Return Attribute object
    def get_attr(self, attr_name):
        attr = None
        if attr_name == self.SIGNATTR_TCG_MIN:
            attr = self.tcg_min
        elif attr_name == self.SIGNATTR_TCG_MAX:
            attr = self.tcg_max
        else:
            attr = self._get_ou_attr(attr_name, self.certificate_text)

        return attr

    # Return attribute as string
    def get_attr_str(self, attr_name):
        attr = self.get_attr(attr_name)
        return None if attr is None else attr.str

    # Return attribute as int/long value
    def get_attr_value(self, attr_name):
        attr = self.get_attr(attr_name)
        return None if attr is None else attr.value

    def _get_exponent(self, certificate_text):
        _exponent = None
        exponent_pattern = re.compile(r'Exponent: (.*) ')
        exponent_match = exponent_pattern.search(certificate_text)
        if exponent_match is not None:
            exponent_str = exponent_match.group(1)
            _exponent = int(exponent_str)

        return _exponent

    def _repr_properties(self):
        properties = [(self.SIGNATTR_SW_ID, self.sw_id),
                      (self.SIGNATTR_HW_ID, self.hw_id)
                     ]

        if self.in_use_soc_hw_version is not None:
            properties += [(self.SIGNATTR_IN_USE_SOC_HW_VERSION, self.in_use_soc_hw_version)]

        if self.in_use_soc_hw_version == 1 or (self.soc_hw_version is not None and self.in_use_soc_hw_version is None):
            properties += [(self.SIGNATTR_SOC_HW_VERSION, self.soc_hw_version),
                           (self.SIGNATTR_MASK_SOC_HW_VERSION, self.mask_soc_hw_version)
                          ]
        if self.use_serial_number_in_signing is not None:
            properties += [(self.SIGNATTR_USE_SERIAL_NUMBER_IN_SIGNING, self.use_serial_number_in_signing)]
        if self.oem_id_independent is not None:
            properties += [(self.SIGNATTR_OEM_ID_INDEPENDENT, self.oem_id_independent)]

        properties += [(self.SIGNATTR_DEBUG, self.debug),
                       (self.SIGNATTR_OEM_ID, self.oem_id),
                       (self.SIGNATTR_SW_SIZE, self.sw_size),
                       (self.SIGNATTR_MODEL_ID, self.model_id),
                       (self.SIGNATTR_SHA256, self.sha256),
                       (self.SIGNATTR_APP_ID, self.app_id),
                       (self.SIGNATTR_CRASH_DUMP, self.crash_dump),
                       (self.SIGNATTR_ROT_EN, self.rot_en),
                       ('Exponent', self.exponent),
                       ('TCG_MIN', self.tcg_min),
                       ('TCG_MAX', self.tcg_max),
                       ('FID_MIN', self.fid_min),
                       ('FID_MAX', self.fid_max)
                      ]

        if self.root_cert_sel is not None:
            properties += [(self.SIGNATTR_ROOT_CERT_SEL, self.root_cert_sel)]
        if self.revocation_enablement is not None:
            properties += [(self.SIGNATTR_REVOCATION_ENABLEMENT, self.revocation_enablement)]
        if self.activation_enablement is not None:
            properties += [(self.SIGNATTR_ACTIVATION_ENABLEMENT, self.activation_enablement)]

        return properties

    def __repr__(self):
        return properties_repr(self._repr_properties())

    @property
    def tcg_min(self):
        return self._tcg_min

    @tcg_min.setter
    def tcg_min(self, value):
        self._tcg_min = value

    @property
    def tcg_max(self):
        return self._tcg_max

    @tcg_max.setter
    def tcg_max(self, value):
        self._tcg_max = value

    @property
    def fid_min(self):
        return self._fid_min

    @fid_min.setter
    def fid_min(self, value):
        self._fid_min = value

    @property
    def fid_max(self):
        return self._fid_max

    @fid_max.setter
    def fid_max(self, value):
        self._fid_max = value

    @property
    def hw_id(self):
        return self.get_attr(self.SIGNATTR_HW_ID)

    @property
    def soc_hw_version(self):
        return self.get_attr(self.SIGNATTR_SOC_HW_VERSION)

    @property
    def mask_soc_hw_version(self):
        return self.get_attr(self.SIGNATTR_MASK_SOC_HW_VERSION)

    @property
    def in_use_soc_hw_version(self):
        return self.get_attr(self.SIGNATTR_IN_USE_SOC_HW_VERSION)

    @property
    def use_serial_number_in_signing(self):
        return self.get_attr(self.SIGNATTR_USE_SERIAL_NUMBER_IN_SIGNING)

    @property
    def oem_id_independent(self):
        return self.get_attr(self.SIGNATTR_OEM_ID_INDEPENDENT)

    @property
    def root_cert_sel(self):
        return self.get_attr(self.SIGNATTR_ROOT_CERT_SEL)

    @property
    def revocation_enablement(self):
        return self.get_attr(self.SIGNATTR_REVOCATION_ENABLEMENT)

    @property
    def activation_enablement(self):
        return self.get_attr(self.SIGNATTR_ACTIVATION_ENABLEMENT)

    @property
    def oem_id(self):
        return self.get_attr(self.SIGNATTR_OEM_ID)

    @property
    def model_id(self):
        return self.get_attr(self.SIGNATTR_MODEL_ID)

    @property
    def sw_id(self):
        return self.get_attr(self.SIGNATTR_SW_ID)

    @property
    def debug(self):
        return self.get_attr(self.SIGNATTR_DEBUG)

    @property
    def crash_dump(self):
        return self.get_attr(self.SIGNATTR_CRASH_DUMP)

    @property
    def rot_en(self):
        return self.get_attr(self.SIGNATTR_ROT_EN)

    @property
    def app_id(self):
        return self.get_attr(self.SIGNATTR_APP_ID)

    @property
    def exponent(self):
        return self._get_exponent(self.certificate_text)

    @property
    def sw_size(self):
        return self.get_attr_value(self.SIGNATTR_SW_SIZE)

    @property
    def sha256(self):
        sha256 = self.get_attr_value(self.SIGNATTR_SHA256)
        return True if sha256 == 1 else False

    @property
    def text(self):
        return self.certificate_text

class Certificate_OU(object):
    OU_DICT = {Certificate.SIGNATTR_SW_ID:"01",
               Certificate.SIGNATTR_HW_ID: "02",
               Certificate.SIGNATTR_DEBUG: "03",
               Certificate.SIGNATTR_OEM_ID: "04",
               Certificate.SIGNATTR_SW_SIZE: "05",
               Certificate.SIGNATTR_MODEL_ID: "06",
               Certificate.SIGNATTR_SHA256: "07",
               Certificate.SIGNATTR_APP_ID: "08",
               Certificate.SIGNATTR_CRASH_DUMP: "09",
               Certificate.SIGNATTR_ROT_EN: "10",
               Certificate.SIGNATTR_SOC_HW_VERSION: "11",
               Certificate.SIGNATTR_MASK_SOC_HW_VERSION: "12",
               Certificate.SIGNATTR_IN_USE_SOC_HW_VERSION: "13",
               Certificate.SIGNATTR_USE_SERIAL_NUMBER_IN_SIGNING: "14",
               Certificate.SIGNATTR_OEM_ID_INDEPENDENT: "15",
               Certificate.SIGNATTR_SN: "16",
               Certificate.SIGNATTR_ROOT_CERT_SEL: "17",
               Certificate.SIGNATTR_REVOCATION_ENABLEMENT: "18",
               Certificate.SIGNATTR_ACTIVATION_ENABLEMENT: "19",
               }

    @classmethod
    def _validate(cls, attribute_name):
        if not cls.OU_DICT.has_key(attribute_name):
            raise RuntimeError("Attribute name {0} is not supported in Certificate_OU".format(attribute_name))

    @classmethod
    def GetID(cls, attribute_name):
        cls._validate(attribute_name)

        return cls.OU_DICT.get(attribute_name)

    @classmethod
    def GetText(cls, attribute_name, attribute):
        cls._validate(attribute_name)
        assert(isinstance(attribute, Attribute))

        ou_text = "{0} {1} {2}".format(cls.OU_DICT.get(attribute_name),
                             attribute.str[2:],  # exclude 0x
                             attribute_name)
        return ou_text
