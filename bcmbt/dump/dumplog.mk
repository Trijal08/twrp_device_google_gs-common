BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/bcmbt/dump/sepolicy/

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_bcmbt
endif
