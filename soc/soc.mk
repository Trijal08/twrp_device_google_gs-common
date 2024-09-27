BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/soc/sepolicy/soc

PRODUCT_PACKAGES += dump_soc
ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_memory
endif
