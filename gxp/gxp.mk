# GXP logging service
PRODUCT_PACKAGES += \
	android.hardware.gxp.logging@service-gxp-logging
# GXP metrics logger library
PRODUCT_PACKAGES += \
	gxp_metrics_logger
# GXP C-API library
PRODUCT_PACKAGES += libgxp
# GXP Debug dump.
ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_gxp
endif

BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/gxp/sepolicy

