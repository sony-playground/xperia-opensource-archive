LOCAL_PATH:= $(call my-dir)

common_src_files := \
	VolumeManager.cpp \
	CommandListener.cpp \
	CryptCommandListener.cpp \
	VoldCommand.cpp \
	NetlinkManager.cpp \
	NetlinkHandler.cpp \
	EventLogTags.logtags \
	log.cpp \
	Process.cpp \
	fs/Filesystems.cpp \
	fs/Ext4.cpp \
	fs/F2fs.cpp \
	fs/Vfat.cpp \
	fs/ExFat.cpp \
	fs/Ntfs.cpp \
	fs/HfsPlus.cpp \
	Loop.cpp \
	Devmapper.cpp \
	ResponseCode.cpp \
	CheckBattery.cpp \
	Ext4Crypt.cpp \
	VoldUtil.c \
	cryptfs.c \
	filecrypt.c \
	Disk.cpp \
	VolumeBase.cpp \
	PublicVolume.cpp \
	PrivateVolume.cpp \
	EmulatedVolume.cpp \
	Utils.cpp \
	MoveTask.cpp \
	Benchmark.cpp \
	TrimTask.cpp \
	Keymaster.cpp \
	KeyStorage.cpp \
	ScryptParameters.cpp \
	secontext.cpp \

common_c_includes := \
	system/extras/ext4_utils \
	system/extras/f2fs_utils \
	vendor/semc/system/core/fips/uscl \
	external/scrypt/lib/crypto \
	frameworks/native/include \
	system/security/keystore \
	hardware/libhardware/include/hardware \
	system/security/softkeymaster/include/keymaster \
	vendor/semc/system/core/libasb/startup-reason/src \
	vendor/sony/sony-tpm/include \

common_shared_libraries := \
	libsysutils \
	libbinder \
	libcutils \
	liblog \
	libdiskconfig \
	libhardware_legacy \
	liblogwrap \
	libext4_utils \
	libf2fs_sparseblock \
	libcrypto \
	libselinux \
	libutils \
	libhardware \
	libsoftkeymaster \
	libbase \
	libkeymaster_messages \
	libstartup-reason \
	libtpm \

ifneq ($(filter sdk semcsdk,$(TARGET_PRODUCT)),)
	NOT_USE_SONY_FIPS := true
endif

ifndef NOT_USE_SONY_FIPS
common_c_includes += vendor/semc/system/core/fips/include
common_shared_libraries += libcrypto_fips
else
common_c_includes += external/openssl/include
common_shared_libraries += libcrypto
endif

ifndef NOT_USE_SONY_FIPS
common_static_libraries := \
	libbootloader_message \
	libfs_mgr \
	libfec \
	libfec_rs \
	libuscl-static \
	libsquashfs_utils \
	libscrypt_static \
	libmincrypt \
	libbatteryservice
else
common_static_libraries := \
	libbootloader_message \
	libfs_mgr \
	libfec \
	libfec_rs \
	libsquashfs_utils \
	libscrypt_static \
	libmincrypt \
	libbatteryservice \

endif

vold_conlyflags := -std=c11
vold_cflags := -Werror -Wall -Wno-missing-field-initializers -Wno-unused-variable -Wno-unused-parameter
VOLD_SRC_DIR := system/vold
common_src_files  := $(addprefix ../../../../$(VOLD_SRC_DIR)/,$(common_src_files))
common_c_includes += system/vold

include $(CLEAR_VARS)

LOCAL_MODULE := libvold_ramdump
LOCAL_CLANG := true
LOCAL_MULTILIB := 64
LOCAL_SRC_FILES := $(common_src_files)
LOCAL_C_INCLUDES := $(common_c_includes)
LOCAL_SHARED_LIBRARIES := $(common_shared_libraries)
LOCAL_STATIC_LIBRARIES := $(common_static_libraries)
LOCAL_MODULE_TAGS := eng tests
LOCAL_CFLAGS := $(vold_cflags)
LOCAL_CONLYFLAGS := $(vold_conlyflags)

ifeq ($(TARGET_HW_DISK_ENCRYPTION),true)
LOCAL_C_INCLUDES += $(TARGET_CRYPTFS_HW_PATH)
common_shared_libraries += libcryptfs_hw
LOCAL_CFLAGS += -DCONFIG_HW_DISK_ENCRYPTION
endif

include $(BUILD_STATIC_LIBRARY)
