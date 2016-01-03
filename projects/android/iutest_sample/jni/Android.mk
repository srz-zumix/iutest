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
                   
LOCAL_CFLAGS := -Wno-psabi

include $(BUILD_EXECUTABLE)
