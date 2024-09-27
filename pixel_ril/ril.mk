BOARD_SEPOLICY_DIRS += device/google/gs-common/pixel_ril/sepolicy

ifeq ($(SIM_COUNT), 2)
    DEVICE_MANIFEST_FILE += device/google/gs-common/pixel_ril/manifest_ril_ds.xml
else
    DEVICE_MANIFEST_FILE += device/google/gs-common/pixel_ril/manifest_ril.xml
endif
DEVICE_PRODUCT_COMPATIBILITY_MATRIX_FILE += device/google/gs-common/pixel_ril/compatibility_matrix.xml

PRODUCT_PACKAGES += ril-extension

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += libgooglerilmemmonitor
endif

PRODUCT_SOONG_NAMESPACES += \
    vendor/google/tools/ril-extension-service \
    vendor/google/tools/ril-mem-monitor

USE_GOOGLE_RIL_EXT := true
