# Include this file to enable Pixel GNSS HAL

$(call soong_config_set, pixel_gnss, enable_pixel_gnss_aidl_service, true)

BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/gps/pixel/sepolicy

PRODUCT_PACKAGES += \
    android.hardware.gnss-service.pixel

PRODUCT_VENDOR_PROPERTIES += \
    persist.vendor.gps.hal.service.name=vendor

# Compatibility matrix
DEVICE_PRODUCT_COMPATIBILITY_MATRIX_FILE += \
    device/google/gs-common/gps/pixel/device_framework_matrix_product.xml
