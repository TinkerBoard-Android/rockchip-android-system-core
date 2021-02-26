/*
 * Copyright (C) 2008 The Android Open Source Project
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

#include <android-base/logging.h>
#include <fs_mgr.h>

#include "util.h"
#include "vendor.h"

namespace android::vendor {
    std::string RKBootMode::getRKBootDevice() {
        auto boot_devices = android::fs_mgr::GetBootDevices();
        std::string  boot_mode;
        std::string  boot_device;
        init::import_kernel_cmdline(false,
                                    [&](const std::string& key,
                                    const std::string& value, bool in_qemu) {
            if (key == "androidboot.storagemedia") {
                boot_mode = value;
            }
        });

        auto iter = boot_devices.begin();
        if ("emmc" == boot_mode && boot_devices.size() >= 2) {
            iter ++;
        }
        boot_device = *iter;
        return boot_device;
    }
}
