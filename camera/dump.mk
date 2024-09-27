BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/camera/sepolicy/vendor
PRODUCT_PUBLIC_SEPOLICY_DIRS += device/google/gs-common/camera/sepolicy/product/public
PRODUCT_PRIVATE_SEPOLICY_DIRS += device/google/gs-common/camera/sepolicy/product/private

ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += dump_camera
endif
