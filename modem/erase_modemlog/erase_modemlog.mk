#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

ifneq (,$(filter userdebug eng, $(TARGET_BUILD_VARIANT)))
BOARD_VENDOR_SEPOLICY_DIRS += device/google/gs-common/modem/erase_modemlog/sepolicy

PRODUCT_PACKAGES += erase_modemlog.sh
endif
