BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/led/sepolicy

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_led
endif
