PRODUCT_PACKAGES += android.hardware.thermal-service.pixel

# Thermal utils
PRODUCT_PACKAGES += thermal_symlinks

# Thermal logd
ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += thermal_logd
endif
PRODUCT_PACKAGES_ENG += thermal_logd

BOARD_SEPOLICY_DIRS += device/google/gs-common/thermal/sepolicy/thermal_hal
