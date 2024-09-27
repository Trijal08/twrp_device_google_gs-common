PRODUCT_VENDOR_PROPERTIES += ro.vendor.touch.dump.sys=/sys/class/spi_master/spi20/spi20.0/synaptics_tcm.0/sysfs

BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/touch/syna/sepolicy

PRODUCT_PACKAGES += dump_syna.sh
