BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/gps/lsi/sepolicy

PRODUCT_SOONG_NAMESPACES += \
    vendor/samsung_slsi/gps/s5400

PRODUCT_PACKAGES += \
    android.hardware.location.gps.prebuilt.xml \
    gnssd \
    android.hardware.gnss-service \
    ca.pem \
    gnss_check.sh \
    kepler.bin

ifneq (,$(filter userdebug eng, $(TARGET_BUILD_VARIANT)))
    PRODUCT_VENDOR_PROPERTIES += vendor.gps.aol.enabled=true
endif

# Enable Pixel GNSS HAL
include device/google/gs-common/gps/pixel/pixel_gnss_hal.mk