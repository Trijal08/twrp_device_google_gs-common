BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/aoc/sepolicy

PRODUCT_PACKAGES += dump_aoc \
		    aocd \
		    aocxd

ifeq (,$(filter aosp_%,$(TARGET_PRODUCT)))
# IAudioMetricExt HIDL
PRODUCT_PACKAGES += \
    vendor.google.audiometricext@1.0-service-vendor
endif

# If AoC Daemon is not present on this build, load firmware at boot via rc
PRODUCT_COPY_FILES += \
	device/google/gs-common/aoc/conf/init.aoc.daemon.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/init.aoc.rc

# AoC debug support
ifneq (,$(filter eng, $(TARGET_BUILD_VARIANT)))
PRODUCT_PACKAGES_DEBUG += \
	aocdump \
	aocutil \
	aoc_audio_cfg \
	vp_util \
	aocx_tool
endif
