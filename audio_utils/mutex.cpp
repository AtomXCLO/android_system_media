/*
 * Copyright (C) 2023 The Android Open Source Project
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

#define LOG_TAG "audio_utils::mutex"
#include <utils/Log.h>

#include <com_android_media_audio_flags.h>

namespace android::audio_utils {

bool mutex_get_enable_flag() {
    static const bool enable = []() {
        const bool flag = com::android::media::audio::flags::mutex_priority_inheritance();
        ALOGD("get_enable_flag: mutex_priority_inheritance: %s", flag ? "true" : "false");
        return flag;
    }();
    return enable;
}

}  // namespace android::audio_utils
