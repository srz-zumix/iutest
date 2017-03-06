LOCAL_PATH := $(call my-dir)/../../../../samples

include $(CLEAR_VARS)

LOCAL_MODULE    := iutest_sample
LOCAL_SRC_FILES := main.cpp \
                   assertion.cpp \
                   disabledtest.cpp \
                   exception.cpp \
                   fixture.cpp \
                   matcher.cpp \
                   parameterized.cpp \
                   printto.cpp \
                   simple.cpp \
                   typed.cpp

ifdef SNAP_CI                   
LOCAL_CFLAGS := -Wno-psabi
endif

include $(BUILD_EXECUTABLE)
