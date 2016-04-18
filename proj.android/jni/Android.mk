LOCAL_PATH := $(call \
my-dir)



include $(CLEAR_VARS)

LOCAL_MODULE    := libprotobuf

LOCAL_SRC_FILES :=\
	../../Classes/google/protobuf/descriptor_database.cc \
	../../Classes/google/protobuf/descriptor.cc \
	../../Classes/google/protobuf/descriptor.pb.cc \
	../../Classes/google/protobuf/dynamic_message.cc \
	../../Classes/google/protobuf/extension_set_heavy.cc \
	../../Classes/google/protobuf/extension_set.cc \
	../../Classes/google/protobuf/generated_message_reflection.cc \
	../../Classes/google/protobuf/generated_message_util.cc \
	../../Classes/google/protobuf/io/coded_stream.cc \
	../../Classes/google/protobuf/io/gzip_stream.cc \
	../../Classes/google/protobuf/io/printer.cc \
	../../Classes/google/protobuf/io/tokenizer.cc \
	../../Classes/google/protobuf/io/zero_copy_stream_impl_lite.cc \
	../../Classes/google/protobuf/io/zero_copy_stream_impl.cc \
	../../Classes/google/protobuf/io/zero_copy_stream.cc \
	../../Classes/google/protobuf/message_lite.cc \
	../../Classes/google/protobuf/message.cc \
	../../Classes/google/protobuf/reflection_ops.cc \
	../../Classes/google/protobuf/repeated_field.cc \
	../../Classes/google/protobuf/stubs/common.cc \
	../../Classes/google/protobuf/stubs/once.cc \
	../../Classes/google/protobuf/stubs/stringprintf.cc \
	../../Classes/google/protobuf/stubs/structurally_valid.cc \
	../../Classes/google/protobuf/stubs/strutil.cc \
	../../Classes/google/protobuf/stubs/substitute.cc \
	../../Classes/google/protobuf/text_format.cc \
	../../Classes/google/protobuf/unknown_field_set.cc \
	../../Classes/google/protobuf/wire_format_lite.cc \
	../../Classes/google/protobuf/wire_format.cc

#$(warning $(TARGET_ARCH))

ifeq ($(TARGET_ARCH),x86)
	LOCAL_SRC_FILES := $(LOCAL_SRC_FILES) \
										 ../../Classes/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
endif
ifeq ($(TARGET_ARCH),x86_64)
	LOCAL_SRC_FILES := $(LOCAL_SRC_FILES) \
										 ../../Classes/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
endif

LOCAL_CFLAGS := -D GOOGLE_PROTOBUF_NO_RTTI=1
LOCAL_CPPFLAGS := -std=c++11
LOCAL_C_INCLUDES = $(LOCAL_PATH)/../../Classes/ \
				$(LOCAL_PATH)/../../Classes/google/ \
				$(LOCAL_PATH)/../../Classes/google/protobuf/ \
				$(LOCAL_PATH)/../../Classes/protobufObject/ 

LOCAL_EXPORT_LDLIBS := -lz
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

include $(BUILD_STATIC_LIBRARY)



include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \ ../../cocos2d/cocos/platform/android/jni/JniLink.cpp

DELEGATE_FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
LOCAL_SRC_FILES += $(DELEGATE_FILE_LIST:$(LOCAL_PATH)/%=%)


# DELEGATE_FILE_LIST := $(DELEGATE_FILE_LIST:$(LOCAL_PATH)/%=%)

PROTOBUF_FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/protobufObject/*.pb.cc)
LOCAL_SRC_FILES += $(PROTOBUF_FILE_LIST:$(LOCAL_PATH)/%=%)

# PROTOBUF_FILE_LIST := $(PROTOBUF_FILE_LIST:$(LOCAL_PATH)/%=%)

SCENE_FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/Scenes/*.cpp)
LOCAL_SRC_FILES += $(SCENE_FILE_LIST:$(LOCAL_PATH)/%=%)

# SCENE_FILE_LIST  := $(SCENE_FILE_LIST:$(LOCAL_PATH)/%=%)

UI_FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/UI/*.cpp)
LOCAL_SRC_FILES += $(UI_FILE_LIST:$(LOCAL_PATH)/%=%)

# UI_FILE_LIST  := $(UI_FILE_LIST:$(LOCAL_PATH)/%=%)

UTILS_FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/Utils/*.cpp)
LOCAL_SRC_FILES += $(UTILS_FILE_LIST:$(LOCAL_PATH)/%=%)

# UTILS_FILE_LIST  := $(UTILS_FILE_LIST:$(LOCAL_PATH)/%=%)

OBJECTS_FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/Objects/*.cpp)
LOCAL_SRC_FILES += $(OBJECTS_FILE_LIST:$(LOCAL_PATH)/%=%)

# OBJECTS_FILE_LIST  := $(OBJECTS_FILE_LIST:$(LOCAL_PATH)/%=%)



# LOCAL_SRC_FILES += $(DELEGATE_FILE_LIST)











# LOCAL_SRC_FILES += $(SCENE_FILE_LIST)

# LOCAL_SRC_FILES += $(UI_FILE_LIST)

# LOCAL_SRC_FILES += $(UTILS_FILE_LIST)

# LOCAL_SRC_FILES += $(OBJECTS_FILE_LIST)

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := PluginFacebook \
sdkbox

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += libprotobuf

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module, .)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginfacebook)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END