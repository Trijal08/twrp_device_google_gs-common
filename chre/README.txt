This folder contains the common settings for CHRE shared by various platforms.

Dependencies among types can happen. For example, hal_contexthub_default
depends on sysfs_aoc at the moment. When setting up a device with CHRE
we should make sure rules of dependent types are included too.
