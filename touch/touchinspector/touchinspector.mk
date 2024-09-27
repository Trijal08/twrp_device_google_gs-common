BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/touch/touchinspector/sepolicy

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += TouchInspector
endif
