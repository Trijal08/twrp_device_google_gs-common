#!/vendor/bin/sh
#
# SPDX-FileCopyrightText: 2024 The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

if [ ! -f /data/vendor/slog/erased ]; then
    rm -rf /data/vendor/slog
    mkdir /data/vendor/slog
    chmod 771 /data/vendor/slog
    chown -hR system.system /data/vendor/slog
    touch /data/vendor/slog/erased
fi
