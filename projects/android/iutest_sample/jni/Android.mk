LOCAL_PATH := $(call my-dir)/../../../../samples

include $(CLEAR_VARS)

LOCAL_MODULE    := iutest_sample
LOCAL_SRC_FILES := main.cpp \
                   sub.cpp
                   
LOCAL_CFLAGS := -Wno-psabi

include $(BUILD_EXECUTABLE)
