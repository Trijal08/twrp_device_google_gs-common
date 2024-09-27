BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/wlan/sepolicy/

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_wlan
endif
