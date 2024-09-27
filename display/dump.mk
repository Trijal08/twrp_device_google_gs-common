BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/display/sepolicy

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_display_userdebug.sh
endif
PRODUCT_PACKAGES += dump_display
