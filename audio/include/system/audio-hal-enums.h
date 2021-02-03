/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This header contains definitions of enums that are passed through
// the system <-> vendor (also known as framework <-> HAL) boundary.
// On the HAL side they are defined in the Audio Policy config schema:
// h/i/audio/x.x/config/audio_policy_configuration.xsd
//
// These enums are passed between the framework and the HAL as
// strings. Because of that, functions for to/from string conversion
// are also defined here. The enums are defined in a way that
// allows having only one list of values which is then used to
// generate both enum definitions and to/from string converters.
// As this header needs to be compatible with C, preprocessor
// macros are used for templating.
//
// Some enums have framework-only extensions. They are disabled
// for vendor code by means of AUDIO_NO_SYSTEM_DECLARATIONS define.
// Framework-only enum values can not be received from HAL, thus
// string -> enum conversion is not generated for them. However,
// since enum -> string conversion is also useful for debugging
// purposes, the corresponding cases are handled in conversion
// functions.
//
// There is no automatic update of enum symbols list from the
// audio HAL schema, or vice versa. Any new enum value used at
// the system <-> vendor boundary must be added to both locations.
//
// No special functions are provided for dealing with enums that
// constitute flags, e.g. to convert a mask into a list of strings.
// String conversion functions only support individual flag values.
// The only exception is 'audio_channel_mask_from_string' function
// which only deals with masks, not with individual channels.

#ifndef ANDROID_AUDIO_HAL_ENUMS_H
#define ANDROID_AUDIO_HAL_ENUMS_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

#define AUDIO_ENUM_QUOTE(x) #x
#define AUDIO_ENUM_STRINGIFY(x) AUDIO_ENUM_QUOTE(x)
// Simple enums are the ones relying on default values.
// Enums that specify values need to use '_V' versions of macros.
#define AUDIO_DEFINE_ENUM_SYMBOL(symbol) symbol,
#define AUDIO_DEFINE_ENUM_SYMBOL_V(symbol, value) symbol = value,
#define AUDIO_DEFINE_BIT_MASK(symbol) symbol |
#define AUDIO_DEFINE_BIT_MASK_V(symbol, _) AUDIO_DEFINE_BIT_MASK(symbol)
#define AUDIO_DEFINE_STRINGIFY_CASE(symbol) case symbol: return AUDIO_ENUM_STRINGIFY(symbol);
#define AUDIO_DEFINE_STRINGIFY_CASE_V(symbol, _) AUDIO_DEFINE_STRINGIFY_CASE(symbol)
#define AUDIO_DEFINE_PARSE_CASE(symbol) \
    if (strcmp(s, AUDIO_ENUM_STRINGIFY(symbol)) == 0) { *t = symbol; return true; } else
#define AUDIO_DEFINE_PARSE_CASE_V(symbol, _) AUDIO_DEFINE_PARSE_CASE(symbol)


// These are individual output channel flags, only one bit must be set.
#define AUDIO_CHANNEL_OUT_DISCRETE_CHANNEL_LIST_DEF(V) \
    V(AUDIO_CHANNEL_OUT_FRONT_LEFT, 0x1u) \
    V(AUDIO_CHANNEL_OUT_FRONT_RIGHT, 0x2u) \
    V(AUDIO_CHANNEL_OUT_FRONT_CENTER, 0x4u) \
    V(AUDIO_CHANNEL_OUT_LOW_FREQUENCY, 0x8u) \
    V(AUDIO_CHANNEL_OUT_BACK_LEFT, 0x10u) \
    V(AUDIO_CHANNEL_OUT_BACK_RIGHT, 0x20u) \
    V(AUDIO_CHANNEL_OUT_FRONT_LEFT_OF_CENTER, 0x40u) \
    V(AUDIO_CHANNEL_OUT_FRONT_RIGHT_OF_CENTER, 0x80u) \
    V(AUDIO_CHANNEL_OUT_BACK_CENTER, 0x100u) \
    V(AUDIO_CHANNEL_OUT_SIDE_LEFT, 0x200u) \
    V(AUDIO_CHANNEL_OUT_SIDE_RIGHT, 0x400u) \
    V(AUDIO_CHANNEL_OUT_TOP_CENTER, 0x800u) \
    V(AUDIO_CHANNEL_OUT_TOP_FRONT_LEFT, 0x1000u) \
    V(AUDIO_CHANNEL_OUT_TOP_FRONT_CENTER, 0x2000u) \
    V(AUDIO_CHANNEL_OUT_TOP_FRONT_RIGHT, 0x4000u) \
    V(AUDIO_CHANNEL_OUT_TOP_BACK_LEFT, 0x8000u) \
    V(AUDIO_CHANNEL_OUT_TOP_BACK_CENTER, 0x10000u) \
    V(AUDIO_CHANNEL_OUT_TOP_BACK_RIGHT, 0x20000u) \
    V(AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT, 0x40000u) \
    V(AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT, 0x80000u) \
    V(AUDIO_CHANNEL_OUT_HAPTIC_A, 0x20000000u) \
    V(AUDIO_CHANNEL_OUT_HAPTIC_B, 0x10000000u)
// These are individual input channel flags, only one bit must be set.
#define AUDIO_CHANNEL_IN_DISCRETE_CHANNEL_LIST_DEF(V) \
    V(AUDIO_CHANNEL_IN_LEFT, 0x4u) \
    V(AUDIO_CHANNEL_IN_RIGHT, 0x8u) \
    V(AUDIO_CHANNEL_IN_FRONT, 0x10u) \
    V(AUDIO_CHANNEL_IN_BACK, 0x20u) \
    V(AUDIO_CHANNEL_IN_LEFT_PROCESSED, 0x40u) \
    V(AUDIO_CHANNEL_IN_RIGHT_PROCESSED, 0x80u) \
    V(AUDIO_CHANNEL_IN_FRONT_PROCESSED, 0x100u) \
    V(AUDIO_CHANNEL_IN_BACK_PROCESSED, 0x200u) \
    V(AUDIO_CHANNEL_IN_PRESSURE, 0x400u) \
    V(AUDIO_CHANNEL_IN_X_AXIS, 0x800u) \
    V(AUDIO_CHANNEL_IN_Y_AXIS, 0x1000u) \
    V(AUDIO_CHANNEL_IN_Z_AXIS, 0x2000u) \
    V(AUDIO_CHANNEL_IN_VOICE_UPLINK, 0x4000u) \
    V(AUDIO_CHANNEL_IN_VOICE_DNLINK, 0x8000u) \
    V(AUDIO_CHANNEL_IN_BACK_LEFT, 0x10000u) \
    V(AUDIO_CHANNEL_IN_BACK_RIGHT, 0x20000u) \
    V(AUDIO_CHANNEL_IN_CENTER, 0x40000u) \
    V(AUDIO_CHANNEL_IN_LOW_FREQUENCY, 0x100000u) \
    V(AUDIO_CHANNEL_IN_TOP_LEFT, 0x200000u) \
    V(AUDIO_CHANNEL_IN_TOP_RIGHT, 0x400000u)
#define AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF(V) \
    V(AUDIO_CHANNEL_NONE, 0x0u)
// Input and output masks are defined via individual channels.
#define AUDIO_CHANNEL_OUT_MASK_LIST_UNIQUE_DEF(V) \
    V(AUDIO_CHANNEL_OUT_MONO, AUDIO_CHANNEL_OUT_FRONT_LEFT) \
    V(AUDIO_CHANNEL_OUT_STEREO, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT) \
    V(AUDIO_CHANNEL_OUT_2POINT1, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_OUT_TRI, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER) \
    V(AUDIO_CHANNEL_OUT_TRI_BACK, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_BACK_CENTER) \
    V(AUDIO_CHANNEL_OUT_3POINT1, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_OUT_2POINT0POINT2, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT | AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_2POINT1POINT2, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT | AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT | AUDIO_CHANNEL_OUT_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_OUT_3POINT0POINT2, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT | AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_3POINT1POINT2, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT | AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT | AUDIO_CHANNEL_OUT_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_OUT_QUAD, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_BACK_LEFT | AUDIO_CHANNEL_OUT_BACK_RIGHT) \
    V(AUDIO_CHANNEL_OUT_QUAD_SIDE, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_SIDE_LEFT | AUDIO_CHANNEL_OUT_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_SURROUND, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_BACK_CENTER) \
    V(AUDIO_CHANNEL_OUT_PENTA, AUDIO_CHANNEL_OUT_QUAD | AUDIO_CHANNEL_OUT_FRONT_CENTER) \
    V(AUDIO_CHANNEL_OUT_5POINT1, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_LOW_FREQUENCY | AUDIO_CHANNEL_OUT_BACK_LEFT | AUDIO_CHANNEL_OUT_BACK_RIGHT) \
    V(AUDIO_CHANNEL_OUT_5POINT1_SIDE, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_LOW_FREQUENCY | AUDIO_CHANNEL_OUT_SIDE_LEFT | AUDIO_CHANNEL_OUT_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_5POINT1POINT2, AUDIO_CHANNEL_OUT_5POINT1 | AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT | AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_5POINT1POINT4, AUDIO_CHANNEL_OUT_5POINT1 | AUDIO_CHANNEL_OUT_TOP_FRONT_LEFT | AUDIO_CHANNEL_OUT_TOP_FRONT_RIGHT | AUDIO_CHANNEL_OUT_TOP_BACK_LEFT | AUDIO_CHANNEL_OUT_TOP_BACK_RIGHT) \
    V(AUDIO_CHANNEL_OUT_6POINT1, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_LOW_FREQUENCY | AUDIO_CHANNEL_OUT_BACK_LEFT | AUDIO_CHANNEL_OUT_BACK_RIGHT | AUDIO_CHANNEL_OUT_BACK_CENTER) \
    V(AUDIO_CHANNEL_OUT_7POINT1, AUDIO_CHANNEL_OUT_FRONT_LEFT | AUDIO_CHANNEL_OUT_FRONT_RIGHT | AUDIO_CHANNEL_OUT_FRONT_CENTER | AUDIO_CHANNEL_OUT_LOW_FREQUENCY | AUDIO_CHANNEL_OUT_BACK_LEFT | AUDIO_CHANNEL_OUT_BACK_RIGHT | AUDIO_CHANNEL_OUT_SIDE_LEFT | AUDIO_CHANNEL_OUT_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_7POINT1POINT2, AUDIO_CHANNEL_OUT_7POINT1 | AUDIO_CHANNEL_OUT_TOP_SIDE_LEFT | AUDIO_CHANNEL_OUT_TOP_SIDE_RIGHT) \
    V(AUDIO_CHANNEL_OUT_7POINT1POINT4, AUDIO_CHANNEL_OUT_7POINT1 | AUDIO_CHANNEL_OUT_TOP_FRONT_LEFT | AUDIO_CHANNEL_OUT_TOP_FRONT_RIGHT | AUDIO_CHANNEL_OUT_TOP_BACK_LEFT | AUDIO_CHANNEL_OUT_TOP_BACK_RIGHT) \
    V(AUDIO_CHANNEL_OUT_MONO_HAPTIC_A, AUDIO_CHANNEL_OUT_MONO | AUDIO_CHANNEL_OUT_HAPTIC_A) \
    V(AUDIO_CHANNEL_OUT_STEREO_HAPTIC_A, AUDIO_CHANNEL_OUT_STEREO | AUDIO_CHANNEL_OUT_HAPTIC_A) \
    V(AUDIO_CHANNEL_OUT_HAPTIC_AB, AUDIO_CHANNEL_OUT_HAPTIC_A | AUDIO_CHANNEL_OUT_HAPTIC_B) \
    V(AUDIO_CHANNEL_OUT_MONO_HAPTIC_AB, AUDIO_CHANNEL_OUT_MONO | AUDIO_CHANNEL_OUT_HAPTIC_AB) \
    V(AUDIO_CHANNEL_OUT_STEREO_HAPTIC_AB, AUDIO_CHANNEL_OUT_STEREO | AUDIO_CHANNEL_OUT_HAPTIC_AB)
// Some of the channel masks have aliases. They can not appear in the 'to string'
// converter as case values must be unique.
#define AUDIO_CHANNEL_OUT_MASK_LIST_DEF(V) \
    AUDIO_CHANNEL_OUT_MASK_LIST_UNIQUE_DEF(V) \
    V(AUDIO_CHANNEL_OUT_5POINT1_BACK, AUDIO_CHANNEL_OUT_5POINT1) \
    V(AUDIO_CHANNEL_OUT_QUAD_BACK, AUDIO_CHANNEL_OUT_QUAD)
#define AUDIO_CHANNEL_IN_MASK_LIST_DEF(V) \
    V(AUDIO_CHANNEL_IN_MONO, AUDIO_CHANNEL_IN_FRONT) \
    V(AUDIO_CHANNEL_IN_STEREO, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_RIGHT) \
    V(AUDIO_CHANNEL_IN_FRONT_BACK, AUDIO_CHANNEL_IN_FRONT | AUDIO_CHANNEL_IN_BACK) \
    V(AUDIO_CHANNEL_IN_6, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_RIGHT | AUDIO_CHANNEL_IN_FRONT | AUDIO_CHANNEL_IN_BACK | AUDIO_CHANNEL_IN_LEFT_PROCESSED | AUDIO_CHANNEL_IN_RIGHT_PROCESSED) \
    V(AUDIO_CHANNEL_IN_2POINT0POINT2, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_RIGHT | AUDIO_CHANNEL_IN_TOP_LEFT | AUDIO_CHANNEL_IN_TOP_RIGHT) \
    V(AUDIO_CHANNEL_IN_2POINT1POINT2, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_RIGHT | AUDIO_CHANNEL_IN_TOP_LEFT | AUDIO_CHANNEL_IN_TOP_RIGHT | AUDIO_CHANNEL_IN_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_IN_3POINT0POINT2, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_CENTER | AUDIO_CHANNEL_IN_RIGHT | AUDIO_CHANNEL_IN_TOP_LEFT | AUDIO_CHANNEL_IN_TOP_RIGHT) \
    V(AUDIO_CHANNEL_IN_3POINT1POINT2, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_CENTER | AUDIO_CHANNEL_IN_RIGHT | AUDIO_CHANNEL_IN_TOP_LEFT | AUDIO_CHANNEL_IN_TOP_RIGHT | AUDIO_CHANNEL_IN_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_IN_5POINT1, AUDIO_CHANNEL_IN_LEFT | AUDIO_CHANNEL_IN_CENTER | AUDIO_CHANNEL_IN_RIGHT | AUDIO_CHANNEL_IN_BACK_LEFT | AUDIO_CHANNEL_IN_BACK_RIGHT | AUDIO_CHANNEL_IN_LOW_FREQUENCY) \
    V(AUDIO_CHANNEL_IN_VOICE_UPLINK_MONO, AUDIO_CHANNEL_IN_VOICE_UPLINK | AUDIO_CHANNEL_IN_MONO) \
    V(AUDIO_CHANNEL_IN_VOICE_DNLINK_MONO, AUDIO_CHANNEL_IN_VOICE_DNLINK | AUDIO_CHANNEL_IN_MONO) \
    V(AUDIO_CHANNEL_IN_VOICE_CALL_MONO, AUDIO_CHANNEL_IN_VOICE_UPLINK_MONO | AUDIO_CHANNEL_IN_VOICE_DNLINK_MONO)

enum {
    AUDIO_CHANNEL_COUNT_MAX = 30u,
    // Can't use AUDIO_CHANNEL_REPRESENTATION_INDEX because audio.h depends on this header.
    AUDIO_CHANNEL_INDEX_HDR = 0x80000000u, // AUDIO_CHANNEL_REPRESENTATION_INDEX << COUNT_MAX
};

// Channel index representation definitions.
#define AUDIO_CHANNEL_INDEX_MASK_LIST_DEF(V) \
    V(AUDIO_CHANNEL_INDEX_MASK_1, AUDIO_CHANNEL_INDEX_HDR | (1 << 1) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_2, AUDIO_CHANNEL_INDEX_HDR | (1 << 2) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_3, AUDIO_CHANNEL_INDEX_HDR | (1 << 3) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_4, AUDIO_CHANNEL_INDEX_HDR | (1 << 4) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_5, AUDIO_CHANNEL_INDEX_HDR | (1 << 5) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_6, AUDIO_CHANNEL_INDEX_HDR | (1 << 6) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_7, AUDIO_CHANNEL_INDEX_HDR | (1 << 7) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_8, AUDIO_CHANNEL_INDEX_HDR | (1 << 8) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_9, AUDIO_CHANNEL_INDEX_HDR | (1 << 9) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_10, AUDIO_CHANNEL_INDEX_HDR | (1 << 10) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_11, AUDIO_CHANNEL_INDEX_HDR | (1 << 11) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_12, AUDIO_CHANNEL_INDEX_HDR | (1 << 12) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_13, AUDIO_CHANNEL_INDEX_HDR | (1 << 13) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_14, AUDIO_CHANNEL_INDEX_HDR | (1 << 14) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_15, AUDIO_CHANNEL_INDEX_HDR | (1 << 15) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_16, AUDIO_CHANNEL_INDEX_HDR | (1 << 16) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_17, AUDIO_CHANNEL_INDEX_HDR | (1 << 17) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_18, AUDIO_CHANNEL_INDEX_HDR | (1 << 18) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_19, AUDIO_CHANNEL_INDEX_HDR | (1 << 19) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_20, AUDIO_CHANNEL_INDEX_HDR | (1 << 20) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_21, AUDIO_CHANNEL_INDEX_HDR | (1 << 21) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_22, AUDIO_CHANNEL_INDEX_HDR | (1 << 22) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_23, AUDIO_CHANNEL_INDEX_HDR | (1 << 23) - 1) \
    V(AUDIO_CHANNEL_INDEX_MASK_24, AUDIO_CHANNEL_INDEX_HDR | (1 << 24) - 1)

// The "channel mask" enum is comprised of discrete channels,
// their combinations (masks), and special values.
typedef enum {
    AUDIO_CHANNEL_OUT_DISCRETE_CHANNEL_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    AUDIO_CHANNEL_IN_DISCRETE_CHANNEL_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    AUDIO_CHANNEL_OUT_MASK_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    AUDIO_CHANNEL_IN_MASK_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    AUDIO_CHANNEL_INDEX_MASK_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    AUDIO_CHANNEL_OUT_ALL =
        AUDIO_CHANNEL_OUT_DISCRETE_CHANNEL_LIST_DEF(AUDIO_DEFINE_BIT_MASK_V) 0,
    AUDIO_CHANNEL_HAPTIC_ALL = AUDIO_CHANNEL_OUT_HAPTIC_B |
                               AUDIO_CHANNEL_OUT_HAPTIC_A,
    AUDIO_CHANNEL_IN_ALL =
        AUDIO_CHANNEL_IN_DISCRETE_CHANNEL_LIST_DEF(AUDIO_DEFINE_BIT_MASK_V) 0,
    // This value must be part of the enum, but it is not a valid mask,
    // and thus it does not participate in to/from string conversions.
    AUDIO_CHANNEL_INVALID = 0xC0000000u,
} audio_channel_mask_t;

// Due to the fact that flag values for input and output channels
// intersect, to string conversions must be defined separately.
inline const char* audio_channel_out_mask_to_string(audio_channel_mask_t t) {
    switch (t) {
    AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    AUDIO_CHANNEL_OUT_MASK_LIST_UNIQUE_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    default:
        return "";
    }
}

inline const char* audio_channel_in_mask_to_string(audio_channel_mask_t t) {
    switch (t) {
    AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    AUDIO_CHANNEL_IN_MASK_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    default:
        return "";
    }
}

inline const char* audio_channel_index_mask_to_string(audio_channel_mask_t t) {
    switch (t) {
    AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    AUDIO_CHANNEL_INDEX_MASK_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    default:
        return "";
    }
}

// Note: parsing is only done for masks, individual channels are not used by HAL.
inline bool audio_channel_mask_from_string(const char* s, audio_channel_mask_t* t) {
    AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    AUDIO_CHANNEL_OUT_MASK_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    AUDIO_CHANNEL_IN_MASK_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    AUDIO_CHANNEL_INDEX_MASK_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_CHANNEL_INDEX_MASK_LIST_DEF
#undef AUDIO_CHANNEL_IN_MASK_LIST_DEF
#undef AUDIO_CHANNEL_OUT_MASK_LIST_DEF
#undef AUDIO_CHANNEL_OUT_MASK_LIST_UNIQUE_DEF
#undef AUDIO_CHANNEL_IN_OUT_MASK_LIST_DEF
#undef AUDIO_CHANNEL_IN_DISCRETE_CHANNEL_LIST_DEF
#undef AUDIO_CHANNEL_OUT_DISCRETE_CHANNEL_LIST_DEF


#define AUDIO_CONTENT_TYPE_LIST_DEF(V) \
    V(AUDIO_CONTENT_TYPE_UNKNOWN) \
    V(AUDIO_CONTENT_TYPE_SPEECH) \
    V(AUDIO_CONTENT_TYPE_MUSIC) \
    V(AUDIO_CONTENT_TYPE_MOVIE) \
    V(AUDIO_CONTENT_TYPE_SONIFICATION)

typedef enum {
    AUDIO_CONTENT_TYPE_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL)
} audio_content_type_t;

inline const char* audio_content_type_to_string(audio_content_type_t t) {
    switch (t) {
    AUDIO_CONTENT_TYPE_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE)
    }
    return "";
}

inline bool audio_content_type_from_string(const char* s, audio_content_type_t* t) {
    AUDIO_CONTENT_TYPE_LIST_DEF(AUDIO_DEFINE_PARSE_CASE)
    return false;
}

#undef AUDIO_CONTENT_TYPE_LIST_DEF


// Flags that never appear on their own.
enum {
    AUDIO_DEVICE_BIT_IN = 0x80000000u,
    AUDIO_DEVICE_BIT_DEFAULT = 0x40000000u,
};

#define AUDIO_DEVICE_LIST_UNIQUE_DEF(V) \
    V(AUDIO_DEVICE_NONE, 0x0u) \
    V(AUDIO_DEVICE_OUT_EARPIECE, 0x1u) \
    V(AUDIO_DEVICE_OUT_SPEAKER, 0x2u) \
    V(AUDIO_DEVICE_OUT_WIRED_HEADSET, 0x4u) \
    V(AUDIO_DEVICE_OUT_WIRED_HEADPHONE, 0x8u) \
    V(AUDIO_DEVICE_OUT_BLUETOOTH_SCO, 0x10u) \
    V(AUDIO_DEVICE_OUT_BLUETOOTH_SCO_HEADSET, 0x20u) \
    V(AUDIO_DEVICE_OUT_BLUETOOTH_SCO_CARKIT, 0x40u) \
    V(AUDIO_DEVICE_OUT_BLUETOOTH_A2DP, 0x80u) \
    V(AUDIO_DEVICE_OUT_BLUETOOTH_A2DP_HEADPHONES, 0x100u) \
    V(AUDIO_DEVICE_OUT_BLUETOOTH_A2DP_SPEAKER, 0x200u) \
    V(AUDIO_DEVICE_OUT_HDMI, 0x400u) \
    V(AUDIO_DEVICE_OUT_ANLG_DOCK_HEADSET, 0x800u) \
    V(AUDIO_DEVICE_OUT_DGTL_DOCK_HEADSET, 0x1000u) \
    V(AUDIO_DEVICE_OUT_USB_ACCESSORY, 0x2000u) \
    V(AUDIO_DEVICE_OUT_USB_DEVICE, 0x4000u) \
    V(AUDIO_DEVICE_OUT_REMOTE_SUBMIX, 0x8000u) \
    V(AUDIO_DEVICE_OUT_TELEPHONY_TX, 0x10000u) \
    V(AUDIO_DEVICE_OUT_LINE, 0x20000u) \
    V(AUDIO_DEVICE_OUT_HDMI_ARC, 0x40000u) \
    V(AUDIO_DEVICE_OUT_SPDIF, 0x80000u) \
    V(AUDIO_DEVICE_OUT_FM, 0x100000u) \
    V(AUDIO_DEVICE_OUT_AUX_LINE, 0x200000u) \
    V(AUDIO_DEVICE_OUT_SPEAKER_SAFE, 0x400000u) \
    V(AUDIO_DEVICE_OUT_IP, 0x800000u) \
    V(AUDIO_DEVICE_OUT_BUS, 0x1000000u) \
    V(AUDIO_DEVICE_OUT_PROXY, 0x2000000u) \
    V(AUDIO_DEVICE_OUT_USB_HEADSET, 0x4000000u) \
    V(AUDIO_DEVICE_OUT_HEARING_AID, 0x8000000u) \
    V(AUDIO_DEVICE_OUT_ECHO_CANCELLER, 0x10000000u) \
    V(AUDIO_DEVICE_OUT_BLE_HEADSET, 0x20000000u) \
    V(AUDIO_DEVICE_OUT_BLE_SPEAKER, 0x20000001u) \
    V(AUDIO_DEVICE_OUT_DEFAULT, AUDIO_DEVICE_BIT_DEFAULT) \
    V(AUDIO_DEVICE_IN_COMMUNICATION, AUDIO_DEVICE_BIT_IN | 0x1u) \
    V(AUDIO_DEVICE_IN_AMBIENT, AUDIO_DEVICE_BIT_IN | 0x2u) \
    V(AUDIO_DEVICE_IN_BUILTIN_MIC, AUDIO_DEVICE_BIT_IN | 0x4u) \
    V(AUDIO_DEVICE_IN_BLUETOOTH_SCO_HEADSET, AUDIO_DEVICE_BIT_IN | 0x8u) \
    V(AUDIO_DEVICE_IN_WIRED_HEADSET, AUDIO_DEVICE_BIT_IN | 0x10u) \
    V(AUDIO_DEVICE_IN_HDMI, AUDIO_DEVICE_BIT_IN | 0x20u) \
    V(AUDIO_DEVICE_IN_TELEPHONY_RX, AUDIO_DEVICE_BIT_IN | 0x40u) \
    V(AUDIO_DEVICE_IN_BACK_MIC, AUDIO_DEVICE_BIT_IN | 0x80u) \
    V(AUDIO_DEVICE_IN_REMOTE_SUBMIX, AUDIO_DEVICE_BIT_IN | 0x100u) \
    V(AUDIO_DEVICE_IN_ANLG_DOCK_HEADSET, AUDIO_DEVICE_BIT_IN | 0x200u) \
    V(AUDIO_DEVICE_IN_DGTL_DOCK_HEADSET, AUDIO_DEVICE_BIT_IN | 0x400u) \
    V(AUDIO_DEVICE_IN_USB_ACCESSORY, AUDIO_DEVICE_BIT_IN | 0x800u) \
    V(AUDIO_DEVICE_IN_USB_DEVICE, AUDIO_DEVICE_BIT_IN | 0x1000u) \
    V(AUDIO_DEVICE_IN_FM_TUNER, AUDIO_DEVICE_BIT_IN | 0x2000u) \
    V(AUDIO_DEVICE_IN_TV_TUNER, AUDIO_DEVICE_BIT_IN | 0x4000u) \
    V(AUDIO_DEVICE_IN_LINE, AUDIO_DEVICE_BIT_IN | 0x8000u) \
    V(AUDIO_DEVICE_IN_SPDIF, AUDIO_DEVICE_BIT_IN | 0x10000u) \
    V(AUDIO_DEVICE_IN_BLUETOOTH_A2DP, AUDIO_DEVICE_BIT_IN | 0x20000u) \
    V(AUDIO_DEVICE_IN_LOOPBACK, AUDIO_DEVICE_BIT_IN | 0x40000u) \
    V(AUDIO_DEVICE_IN_IP, AUDIO_DEVICE_BIT_IN | 0x80000u) \
    V(AUDIO_DEVICE_IN_BUS, AUDIO_DEVICE_BIT_IN | 0x100000u) \
    V(AUDIO_DEVICE_IN_PROXY, AUDIO_DEVICE_BIT_IN | 0x1000000u) \
    V(AUDIO_DEVICE_IN_USB_HEADSET, AUDIO_DEVICE_BIT_IN | 0x2000000u) \
    V(AUDIO_DEVICE_IN_BLUETOOTH_BLE, AUDIO_DEVICE_BIT_IN | 0x4000000u) \
    V(AUDIO_DEVICE_IN_HDMI_ARC, AUDIO_DEVICE_BIT_IN | 0x8000000u) \
    V(AUDIO_DEVICE_IN_ECHO_REFERENCE, AUDIO_DEVICE_BIT_IN | 0x10000000u) \
    V(AUDIO_DEVICE_IN_BLE_HEADSET, AUDIO_DEVICE_BIT_IN | 0x20000000u) \
    V(AUDIO_DEVICE_IN_DEFAULT, AUDIO_DEVICE_BIT_IN | AUDIO_DEVICE_BIT_DEFAULT)
// Some of the device enums have aliases. They can not appear in the 'to string'
// converter as case values must be unique.
#define AUDIO_DEVICE_LIST_DEF(V) \
    AUDIO_DEVICE_LIST_UNIQUE_DEF(V) \
    V(AUDIO_DEVICE_OUT_AUX_DIGITAL, AUDIO_DEVICE_OUT_HDMI) \
    V(AUDIO_DEVICE_OUT_STUB, AUDIO_DEVICE_OUT_DEFAULT) \
    V(AUDIO_DEVICE_IN_VOICE_CALL, AUDIO_DEVICE_IN_TELEPHONY_RX) \
    V(AUDIO_DEVICE_IN_AUX_DIGITAL, AUDIO_DEVICE_IN_HDMI) \
    V(AUDIO_DEVICE_IN_STUB, AUDIO_DEVICE_IN_DEFAULT)

typedef enum {
    AUDIO_DEVICE_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_devices_t;

inline const char* audio_device_to_string(audio_devices_t t) {
    switch (t) {
    AUDIO_DEVICE_LIST_UNIQUE_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_device_from_string(const char* s, audio_devices_t* t) {
    AUDIO_DEVICE_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_DEVICE_LIST_DEF
#undef AUDIO_DEVICE_LIST_UNIQUE_DEF


#define AUDIO_OUTPUT_FLAG_LIST_DEF(V) \
    V(AUDIO_OUTPUT_FLAG_NONE, 0x0) \
    V(AUDIO_OUTPUT_FLAG_DIRECT, 0x1) \
    V(AUDIO_OUTPUT_FLAG_PRIMARY, 0x2) \
    V(AUDIO_OUTPUT_FLAG_FAST, 0x4) \
    V(AUDIO_OUTPUT_FLAG_DEEP_BUFFER, 0x8) \
    V(AUDIO_OUTPUT_FLAG_COMPRESS_OFFLOAD, 0x10) \
    V(AUDIO_OUTPUT_FLAG_NON_BLOCKING, 0x20) \
    V(AUDIO_OUTPUT_FLAG_HW_AV_SYNC, 0x40) \
    V(AUDIO_OUTPUT_FLAG_TTS, 0x80) \
    V(AUDIO_OUTPUT_FLAG_RAW, 0x100) \
    V(AUDIO_OUTPUT_FLAG_SYNC, 0x200) \
    V(AUDIO_OUTPUT_FLAG_IEC958_NONAUDIO, 0x400) \
    V(AUDIO_OUTPUT_FLAG_DIRECT_PCM, 0x2000) \
    V(AUDIO_OUTPUT_FLAG_MMAP_NOIRQ, 0x4000) \
    V(AUDIO_OUTPUT_FLAG_VOIP_RX, 0x8000) \
    V(AUDIO_OUTPUT_FLAG_INCALL_MUSIC, 0x10000) \
    V(AUDIO_OUTPUT_FLAG_GAPLESS_OFFLOAD, 0x20000)

typedef enum {
    AUDIO_OUTPUT_FLAG_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_output_flags_t;

inline const char* audio_output_flag_to_string(audio_output_flags_t t) {
    switch (t) {
    AUDIO_OUTPUT_FLAG_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_output_flag_from_string(const char* s, audio_output_flags_t* t) {
    AUDIO_OUTPUT_FLAG_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_OUTPUT_FLAG_LIST_DEF


#define AUDIO_INPUT_FLAG_LIST_DEF(V) \
    V(AUDIO_INPUT_FLAG_NONE, 0x0) \
    V(AUDIO_INPUT_FLAG_FAST, 0x1) \
    V(AUDIO_INPUT_FLAG_HW_HOTWORD, 0x2) \
    V(AUDIO_INPUT_FLAG_RAW, 0x4) \
    V(AUDIO_INPUT_FLAG_SYNC, 0x8) \
    V(AUDIO_INPUT_FLAG_MMAP_NOIRQ, 0x10) \
    V(AUDIO_INPUT_FLAG_VOIP_TX, 0x20) \
    V(AUDIO_INPUT_FLAG_HW_AV_SYNC, 0x40) \
    V(AUDIO_INPUT_FLAG_DIRECT, 0x80)

typedef enum {
    AUDIO_INPUT_FLAG_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_input_flags_t;

inline const char* audio_input_flag_to_string(audio_input_flags_t t) {
    switch (t) {
    AUDIO_INPUT_FLAG_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_input_flag_from_string(const char* s, audio_input_flags_t* t) {
    AUDIO_INPUT_FLAG_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_INPUT_FLAG_LIST_DEF


// Anonymous enum that provides building blocks for audio format enums.
// Because some of them are used on their own (e.g. masks), they retain 'AUDIO_FORMAT_' prefix.
enum {
    AUDIO_FORMAT_MAIN_MASK             = 0xFF000000u,
    AUDIO_FORMAT_SUB_MASK              = 0x00FFFFFFu,

    AUDIO_FORMAT_PCM_MAIN              = 0u,
    AUDIO_FORMAT_PCM_SUB_16_BIT        = 0x1u,
    AUDIO_FORMAT_PCM_SUB_8_BIT         = 0x2u,
    AUDIO_FORMAT_PCM_SUB_32_BIT        = 0x3u,
    AUDIO_FORMAT_PCM_SUB_8_24_BIT      = 0x4u,
    AUDIO_FORMAT_PCM_SUB_FLOAT         = 0x5u,
    AUDIO_FORMAT_PCM_SUB_24_BIT_PACKED = 0x6u,

    AUDIO_FORMAT_AAC_SUB_MAIN          = 0x1u,
    AUDIO_FORMAT_AAC_SUB_LC            = 0x2u,
    AUDIO_FORMAT_AAC_SUB_SSR           = 0x4u,
    AUDIO_FORMAT_AAC_SUB_LTP           = 0x8u,
    AUDIO_FORMAT_AAC_SUB_HE_V1         = 0x10u,
    AUDIO_FORMAT_AAC_SUB_SCALABLE      = 0x20u,
    AUDIO_FORMAT_AAC_SUB_ERLC          = 0x40u,
    AUDIO_FORMAT_AAC_SUB_LD            = 0x80u,
    AUDIO_FORMAT_AAC_SUB_HE_V2         = 0x100u,
    AUDIO_FORMAT_AAC_SUB_ELD           = 0x200u,
    AUDIO_FORMAT_AAC_SUB_XHE           = 0x300u,

    AUDIO_FORMAT_E_AC3_SUB_JOC         = 0x1u,

    AUDIO_FORMAT_MAT_SUB_1_0           = 0x1u,
    AUDIO_FORMAT_MAT_SUB_2_0           = 0x2u,
    AUDIO_FORMAT_MAT_SUB_2_1           = 0x3u,

    AUDIO_FORMAT_MPEGH_SUB_BL_L3       = 0x13u,
    AUDIO_FORMAT_MPEGH_SUB_BL_L4       = 0x14u,
    AUDIO_FORMAT_MPEGH_SUB_LC_L3       = 0x23u,
    AUDIO_FORMAT_MPEGH_SUB_LC_L4       = 0x24u,
};

#define AUDIO_FORMAT_LIST_DEF(V) \
    V(AUDIO_FORMAT_DEFAULT, AUDIO_FORMAT_PCM_MAIN) \
    V(AUDIO_FORMAT_PCM_16_BIT, AUDIO_FORMAT_PCM_MAIN | AUDIO_FORMAT_PCM_SUB_16_BIT) \
    V(AUDIO_FORMAT_PCM_8_BIT, AUDIO_FORMAT_PCM_MAIN | AUDIO_FORMAT_PCM_SUB_8_BIT) \
    V(AUDIO_FORMAT_PCM_32_BIT, AUDIO_FORMAT_PCM_MAIN | AUDIO_FORMAT_PCM_SUB_32_BIT) \
    V(AUDIO_FORMAT_PCM_8_24_BIT, AUDIO_FORMAT_PCM_MAIN | AUDIO_FORMAT_PCM_SUB_8_24_BIT) \
    V(AUDIO_FORMAT_PCM_FLOAT, AUDIO_FORMAT_PCM_MAIN | AUDIO_FORMAT_PCM_SUB_FLOAT) \
    V(AUDIO_FORMAT_PCM_24_BIT_PACKED, AUDIO_FORMAT_PCM_MAIN | AUDIO_FORMAT_PCM_SUB_24_BIT_PACKED) \
    V(AUDIO_FORMAT_MP3, 0x01000000u) \
    V(AUDIO_FORMAT_AMR_NB, 0x02000000u) \
    V(AUDIO_FORMAT_AMR_WB, 0x03000000u) \
    V(AUDIO_FORMAT_AAC, 0x04000000u) \
    V(AUDIO_FORMAT_AAC_MAIN, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_MAIN) \
    V(AUDIO_FORMAT_AAC_LC, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_LC) \
    V(AUDIO_FORMAT_AAC_SSR, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_SSR) \
    V(AUDIO_FORMAT_AAC_LTP, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_LTP) \
    V(AUDIO_FORMAT_AAC_HE_V1, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_HE_V1) \
    V(AUDIO_FORMAT_AAC_SCALABLE, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_SCALABLE) \
    V(AUDIO_FORMAT_AAC_ERLC, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_ERLC) \
    V(AUDIO_FORMAT_AAC_LD, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_LD) \
    V(AUDIO_FORMAT_AAC_HE_V2, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_HE_V2) \
    V(AUDIO_FORMAT_AAC_ELD, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_ELD) \
    V(AUDIO_FORMAT_AAC_XHE, AUDIO_FORMAT_AAC | AUDIO_FORMAT_AAC_SUB_XHE) \
    V(AUDIO_FORMAT_HE_AAC_V1, 0x05000000u) \
    V(AUDIO_FORMAT_HE_AAC_V2, 0x06000000u) \
    V(AUDIO_FORMAT_VORBIS, 0x07000000u) \
    V(AUDIO_FORMAT_OPUS, 0x08000000u) \
    V(AUDIO_FORMAT_AC3, 0x09000000u) \
    V(AUDIO_FORMAT_E_AC3, 0x0A000000u) \
    V(AUDIO_FORMAT_E_AC3_JOC, AUDIO_FORMAT_E_AC3 | AUDIO_FORMAT_E_AC3_SUB_JOC) \
    V(AUDIO_FORMAT_DTS, 0x0B000000u) \
    V(AUDIO_FORMAT_DTS_HD, 0x0C000000u) \
    V(AUDIO_FORMAT_IEC61937, 0x0D000000u) \
    V(AUDIO_FORMAT_DOLBY_TRUEHD, 0x0E000000u) \
    V(AUDIO_FORMAT_EVRC, 0x10000000u) \
    V(AUDIO_FORMAT_EVRCB, 0x11000000u) \
    V(AUDIO_FORMAT_EVRCWB, 0x12000000u) \
    V(AUDIO_FORMAT_EVRCNW, 0x13000000u) \
    V(AUDIO_FORMAT_AAC_ADIF, 0x14000000u) \
    V(AUDIO_FORMAT_WMA, 0x15000000u) \
    V(AUDIO_FORMAT_WMA_PRO, 0x16000000u) \
    V(AUDIO_FORMAT_AMR_WB_PLUS, 0x17000000u) \
    V(AUDIO_FORMAT_MP2, 0x18000000u) \
    V(AUDIO_FORMAT_QCELP, 0x19000000u) \
    V(AUDIO_FORMAT_DSD, 0x1A000000u) \
    V(AUDIO_FORMAT_FLAC, 0x1B000000u) \
    V(AUDIO_FORMAT_ALAC, 0x1C000000u) \
    V(AUDIO_FORMAT_APE, 0x1D000000u) \
    V(AUDIO_FORMAT_AAC_ADTS, 0x1E000000u) \
    V(AUDIO_FORMAT_AAC_ADTS_MAIN, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_MAIN) \
    V(AUDIO_FORMAT_AAC_ADTS_LC, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_LC) \
    V(AUDIO_FORMAT_AAC_ADTS_SSR, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_SSR) \
    V(AUDIO_FORMAT_AAC_ADTS_LTP, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_LTP) \
    V(AUDIO_FORMAT_AAC_ADTS_HE_V1, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_HE_V1) \
    V(AUDIO_FORMAT_AAC_ADTS_SCALABLE, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_SCALABLE) \
    V(AUDIO_FORMAT_AAC_ADTS_ERLC, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_ERLC) \
    V(AUDIO_FORMAT_AAC_ADTS_LD, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_LD) \
    V(AUDIO_FORMAT_AAC_ADTS_HE_V2, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_HE_V2) \
    V(AUDIO_FORMAT_AAC_ADTS_ELD, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_ELD) \
    V(AUDIO_FORMAT_AAC_ADTS_XHE, AUDIO_FORMAT_AAC_ADTS | AUDIO_FORMAT_AAC_SUB_XHE) \
    V(AUDIO_FORMAT_SBC, 0x1F000000u) \
    V(AUDIO_FORMAT_APTX, 0x20000000u) \
    V(AUDIO_FORMAT_APTX_HD, 0x21000000u) \
    V(AUDIO_FORMAT_AC4, 0x22000000u) \
    V(AUDIO_FORMAT_LDAC, 0x23000000u) \
    V(AUDIO_FORMAT_MAT, 0x24000000u) \
    V(AUDIO_FORMAT_MAT_1_0, AUDIO_FORMAT_MAT | AUDIO_FORMAT_MAT_SUB_1_0) \
    V(AUDIO_FORMAT_MAT_2_0, AUDIO_FORMAT_MAT | AUDIO_FORMAT_MAT_SUB_2_0) \
    V(AUDIO_FORMAT_MAT_2_1, AUDIO_FORMAT_MAT | AUDIO_FORMAT_MAT_SUB_2_1) \
    V(AUDIO_FORMAT_AAC_LATM, 0x25000000u) \
    V(AUDIO_FORMAT_AAC_LATM_LC, AUDIO_FORMAT_AAC_LATM | AUDIO_FORMAT_AAC_SUB_LC) \
    V(AUDIO_FORMAT_AAC_LATM_HE_V1, AUDIO_FORMAT_AAC_LATM | AUDIO_FORMAT_AAC_SUB_HE_V1) \
    V(AUDIO_FORMAT_AAC_LATM_HE_V2, AUDIO_FORMAT_AAC_LATM | AUDIO_FORMAT_AAC_SUB_HE_V2) \
    V(AUDIO_FORMAT_CELT, 0x26000000u) \
    V(AUDIO_FORMAT_APTX_ADAPTIVE, 0x27000000u) \
    V(AUDIO_FORMAT_LHDC, 0x28000000u) \
    V(AUDIO_FORMAT_LHDC_LL, 0x29000000u) \
    V(AUDIO_FORMAT_APTX_TWSP, 0x2A000000u) \
    V(AUDIO_FORMAT_LC3, 0x2B000000u) \
    V(AUDIO_FORMAT_MPEGH, 0x2C000000u) \
    V(AUDIO_FORMAT_MPEGH_BL_L3, AUDIO_FORMAT_MPEGH | AUDIO_FORMAT_MPEGH_SUB_BL_L3) \
    V(AUDIO_FORMAT_MPEGH_BL_L4, AUDIO_FORMAT_MPEGH | AUDIO_FORMAT_MPEGH_SUB_BL_L4) \
    V(AUDIO_FORMAT_MPEGH_LC_L3, AUDIO_FORMAT_MPEGH | AUDIO_FORMAT_MPEGH_SUB_LC_L3) \
    V(AUDIO_FORMAT_MPEGH_LC_L4, AUDIO_FORMAT_MPEGH | AUDIO_FORMAT_MPEGH_SUB_LC_L4)

typedef enum {
    AUDIO_FORMAT_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
    // These values must be part of the enum, but they are not valid formats,
    // and thus don't participate in to/from string conversions.
    AUDIO_FORMAT_INVALID = 0xFFFFFFFFu,
    AUDIO_FORMAT_PCM = AUDIO_FORMAT_PCM_MAIN,
} audio_format_t;

inline const char* audio_format_to_string(audio_format_t t) {
    switch (t) {
    AUDIO_FORMAT_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    default:
        return "";
    }
}

inline bool audio_format_from_string(const char* s, audio_format_t* t) {
    AUDIO_FORMAT_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_FORMAT_LIST_DEF


#define AUDIO_GAIN_MODE_LIST_DEF(V) \
    V(AUDIO_GAIN_MODE_JOINT, 1) \
    V(AUDIO_GAIN_MODE_CHANNELS, 2) \
    V(AUDIO_GAIN_MODE_RAMP, 4)

typedef enum {
    AUDIO_GAIN_MODE_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_gain_mode_t;

inline const char* audio_gain_mode_to_string(audio_gain_mode_t t) {
    switch (t) {
    AUDIO_GAIN_MODE_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_gain_mode_from_string(const char* s, audio_gain_mode_t* t) {
    AUDIO_GAIN_MODE_LIST_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_GAIN_MODE_LIST_DEF


#define AUDIO_SOURCE_LIST_NO_SYS_DEF(V) \
    V(AUDIO_SOURCE_DEFAULT, 0) \
    V(AUDIO_SOURCE_MIC, 1) \
    V(AUDIO_SOURCE_VOICE_UPLINK, 2) \
    V(AUDIO_SOURCE_VOICE_DOWNLINK, 3) \
    V(AUDIO_SOURCE_VOICE_CALL, 4) \
    V(AUDIO_SOURCE_CAMCORDER, 5) \
    V(AUDIO_SOURCE_VOICE_RECOGNITION, 6) \
    V(AUDIO_SOURCE_VOICE_COMMUNICATION, 7) \
    V(AUDIO_SOURCE_REMOTE_SUBMIX, 8) \
    V(AUDIO_SOURCE_UNPROCESSED, 9) \
    V(AUDIO_SOURCE_VOICE_PERFORMANCE, 10) \
    V(AUDIO_SOURCE_ECHO_REFERENCE, 1997) \
    V(AUDIO_SOURCE_FM_TUNER, 1998) \
    V(AUDIO_SOURCE_HOTWORD, 1999)
#ifdef AUDIO_NO_SYSTEM_DECLARATIONS
#define AUDIO_SOURCE_LIST_DEF AUDIO_SOURCE_LIST_NO_SYS_DEF
#else
#define AUDIO_SOURCE_LIST_DEF(V) \
    AUDIO_SOURCE_LIST_NO_SYS_DEF(V) \
    V(AUDIO_SOURCE_INVALID, -1)
#endif  // AUDIO_NO_SYSTEM_DECLARATIONS

typedef enum {
    AUDIO_SOURCE_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_source_t;

inline const char* audio_source_to_string(audio_source_t t) {
    switch (t) {
    AUDIO_SOURCE_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_source_from_string(const char* s, audio_source_t* t) {
    AUDIO_SOURCE_LIST_NO_SYS_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_SOURCE_LIST_DEF
#undef AUDIO_SOURCE_LIST_NO_SYS_DEF

#define AUDIO_STREAM_LIST_NO_SYS_DEF(V) \
    V(AUDIO_STREAM_VOICE_CALL, 0) \
    V(AUDIO_STREAM_SYSTEM, 1) \
    V(AUDIO_STREAM_RING, 2) \
    V(AUDIO_STREAM_MUSIC, 3) \
    V(AUDIO_STREAM_ALARM, 4) \
    V(AUDIO_STREAM_NOTIFICATION, 5) \
    V(AUDIO_STREAM_BLUETOOTH_SCO, 6) \
    V(AUDIO_STREAM_ENFORCED_AUDIBLE, 7) \
    V(AUDIO_STREAM_DTMF, 8) \
    V(AUDIO_STREAM_TTS, 9) \
    V(AUDIO_STREAM_ACCESSIBILITY, 10) \
    V(AUDIO_STREAM_ASSISTANT, 11) \
    V(AUDIO_STREAM_REROUTING, 12) \
    V(AUDIO_STREAM_PATCH, 13) \
    V(AUDIO_STREAM_CALL_ASSISTANT, 14)
#ifdef AUDIO_NO_SYSTEM_DECLARATIONS
#define AUDIO_STREAM_LIST_DEF AUDIO_STREAM_LIST_NO_SYS_DEF
#else
#define AUDIO_STREAM_LIST_DEF(V) \
    AUDIO_STREAM_LIST_NO_SYS_DEF(V) \
    V(AUDIO_STREAM_DEFAULT, -1)
#endif  // AUDIO_NO_SYSTEM_DECLARATIONS

typedef enum {
    AUDIO_STREAM_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_stream_type_t;

inline const char* audio_stream_type_to_string(audio_stream_type_t t) {
    switch (t) {
    AUDIO_STREAM_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_stream_type_from_string(const char* s, audio_stream_type_t* t) {
    AUDIO_STREAM_LIST_NO_SYS_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_STREAM_LIST_DEF
#undef AUDIO_STREAM_LIST_NO_SYS_DEF


#define AUDIO_USAGE_LIST_NO_SYS_DEF(V) \
    V(AUDIO_USAGE_UNKNOWN, 0) \
    V(AUDIO_USAGE_MEDIA, 1) \
    V(AUDIO_USAGE_VOICE_COMMUNICATION, 2) \
    V(AUDIO_USAGE_VOICE_COMMUNICATION_SIGNALLING, 3) \
    V(AUDIO_USAGE_ALARM, 4) \
    V(AUDIO_USAGE_NOTIFICATION, 5) \
    V(AUDIO_USAGE_NOTIFICATION_TELEPHONY_RINGTONE, 6) \
    V(AUDIO_USAGE_ASSISTANCE_ACCESSIBILITY, 11) \
    V(AUDIO_USAGE_ASSISTANCE_NAVIGATION_GUIDANCE, 12) \
    V(AUDIO_USAGE_ASSISTANCE_SONIFICATION, 13) \
    V(AUDIO_USAGE_GAME, 14) \
    V(AUDIO_USAGE_VIRTUAL_SOURCE, 15) \
    V(AUDIO_USAGE_ASSISTANT, 16) \
    V(AUDIO_USAGE_CALL_ASSISTANT, 17) \
    V(AUDIO_USAGE_EMERGENCY, 1000) \
    V(AUDIO_USAGE_SAFETY, 1001) \
    V(AUDIO_USAGE_VEHICLE_STATUS, 1002) \
    V(AUDIO_USAGE_ANNOUNCEMENT, 1003)
#ifdef AUDIO_NO_SYSTEM_DECLARATIONS
#define AUDIO_USAGE_LIST_DEF AUDIO_USAGE_LIST_NO_SYS_DEF
#else
#define AUDIO_USAGE_LIST_DEF(V) \
    AUDIO_USAGE_LIST_NO_SYS_DEF(V) \
    V(AUDIO_USAGE_NOTIFICATION_COMMUNICATION_REQUEST, 7) \
    V(AUDIO_USAGE_NOTIFICATION_COMMUNICATION_INSTANT, 8) \
    V(AUDIO_USAGE_NOTIFICATION_COMMUNICATION_DELAYED, 9) \
    V(AUDIO_USAGE_NOTIFICATION_EVENT, 10)
#endif  // AUDIO_NO_SYSTEM_DECLARATIONS

typedef enum {
    AUDIO_USAGE_LIST_DEF(AUDIO_DEFINE_ENUM_SYMBOL_V)
} audio_usage_t;

inline const char* audio_usage_to_string(audio_usage_t t) {
    switch (t) {
    AUDIO_USAGE_LIST_DEF(AUDIO_DEFINE_STRINGIFY_CASE_V)
    }
    return "";
}

inline bool audio_usage_from_string(const char* s, audio_usage_t* t) {
    AUDIO_USAGE_LIST_NO_SYS_DEF(AUDIO_DEFINE_PARSE_CASE_V)
    return false;
}

#undef AUDIO_USAGE_LIST_NO_SYS_DEF
#undef AUDIO_USAGE_LIST_DEF

#undef AUDIO_DEFINE_PARSE_CASE_V
#undef AUDIO_DEFINE_PARSE_CASE
#undef AUDIO_DEFINE_STRINGIFY_CASE_V
#undef AUDIO_DEFINE_STRINGIFY_CASE
#undef AUDIO_DEFINE_BIT_MASK_V
#undef AUDIO_DEFINE_BIT_MASK
#undef AUDIO_DEFINE_ENUM_SYMBOL_V
#undef AUDIO_DEFINE_ENUM_SYMBOL
#undef AUDIO_ENUM_STRINGIFY
#undef AUDIO_ENUM_QUOTE

__END_DECLS

#endif  // ANDROID_AUDIO_HAL_ENUMS_H
