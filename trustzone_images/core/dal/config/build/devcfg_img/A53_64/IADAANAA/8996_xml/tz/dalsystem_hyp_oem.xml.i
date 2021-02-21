<driver name="System_OEM">
    <global_def>
        <var_seq name="g_target_cfg" type=DALPROP_DATA_TYPE_UINT32_SEQ>
            0x8996, DAL_CONFIG_ARCH, end
        </var_seq>
    </global_def>
    <device id="0x1">
        <props name="DalEnv" type=DALPROP_ATTR_TYPE_UINT32>
            DALPROP_MOD_ENV_OEM
        </props>
        <props name=DALPROP_TARGET_PROP_NAME type=DALPROP_ATTR_TYPE_UINT32_SEQ_PTR>
          g_target_cfg
        </props>
    </device>
</driver>
