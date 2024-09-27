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
#pragma once

#include <PowerStatsAidl.h>

namespace aidl {
namespace android {
namespace hardware {
namespace power {
namespace stats {

class DisplayMrrStateResidencyDataProvider : public PowerStats::IStateResidencyDataProvider {
  public:
    DisplayMrrStateResidencyDataProvider(const std::string& name, const std::string& path);
    ~DisplayMrrStateResidencyDataProvider() = default;

    /*
     * See IStateResidencyDataProvider::getStateResidencies
     */
    bool getStateResidencies(
        std::unordered_map<std::string, std::vector<StateResidency>> *residencies) override;

    /*
     * See IStateResidencyDataProvider::getInfo
     */
    std::unordered_map<std::string, std::vector<State>> getInfo() override;

  private:
    struct Config {
      int32_t state; // Display state (On, HBM, LP, Off)
      int32_t resX;  // Resolution X
      int32_t resY;  // Resolution Y
      int32_t rr;    // Refresh rate

      bool operator==(const Config& r) const {
        return state == r.state && resX == r.resX && resY == r.resY && rr == r.rr;
      }
    };

    bool parseConfig(char const *line, Config *config, uint64_t *duration);
    bool parseAvailableState(char const *line, Config *config);
    bool parseTimeInState(char const *line, Config *config, uint64_t *duration);
    bool loadAvailableState();

    const std::string mName;
    const std::string mPath;
    std::vector<Config> mConfigs;
};

}  // namespace stats
}  // namespace power
}  // namespace hardware
}  // namespace android
}  // namespace aidl
