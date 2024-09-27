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
#include "DisplayMrrStateResidencyDataProvider.h"

#include <android-base/logging.h>
#include <android-base/parseint.h>
#include <android-base/strings.h>

using android::base::ParseInt;
using android::base::ParseUint;
using android::base::Split;
using android::base::Trim;

static const std::string TIME_IN_STATE = "time_in_state";
static const std::string AVAILABLE_STATE = "available_disp_stats";
static const std::vector<std::string> DISP_STATE = { "On", "HBM", "LP", "Off" };

namespace aidl {
namespace android {
namespace hardware {
namespace power {
namespace stats {

DisplayMrrStateResidencyDataProvider::DisplayMrrStateResidencyDataProvider(
        const std::string& name, const std::string& path) : mName(name), mPath(path) {
    mConfigs = std::vector<Config>();
    std::string statePath = mPath + AVAILABLE_STATE;
    std::unique_ptr<FILE, decltype(&fclose)> fp(fopen(statePath.c_str(), "r"), fclose);
    if (fp) {
        char *line = nullptr;
        size_t len = 0;
        Config config = { .state = 0, .resX = 0, .resY = 0, .rr = 0 };
        while (getline(&line, &len, fp.get()) != -1) {
            if (parseAvailableState(line, &config)) {
                mConfigs.push_back(config);
            } else {
                PLOG(ERROR) << "Failed to parse display config for [" << std::string(line)
                            << "] from " << statePath;
                mConfigs.clear();
                break;
            }
        }
        free(line);
    } else {
        PLOG(ERROR) << "Failed to open file " << statePath;
    }
}

bool DisplayMrrStateResidencyDataProvider::parseConfig(
        char const *line, Config *config, uint64_t *duration) {
    std::vector<std::string> parts = Split(line, " ");

    if (duration == nullptr) {
        if (parts.size() != 4) return false;
    } else {
        if (parts.size() != 5) return false;

        if (!ParseUint(Trim(parts[4]), duration)) return false;
    }

    if (!ParseInt(Trim(parts[0]), &config->state)) return false;
    if (!ParseInt(Trim(parts[1]), &config->resX)) return false;
    if (!ParseInt(Trim(parts[2]), &config->resY)) return false;
    if (!ParseInt(Trim(parts[3]), &config->rr)) return false;

    return true;
}

bool DisplayMrrStateResidencyDataProvider::parseAvailableState(
        char const *line, Config *config) {
    return parseConfig(line, config, nullptr);
}

bool DisplayMrrStateResidencyDataProvider::parseTimeInState(
        char const *line, Config *config, uint64_t *duration) {
    return parseConfig(line, config, duration);
}

bool DisplayMrrStateResidencyDataProvider::getStateResidencies(
        std::unordered_map<std::string, std::vector<StateResidency>> *residencies) {
    if (mConfigs.empty()) {
        LOG(ERROR) << "Display MRR state list is empty!";
        return false;
    }

    std::string path = mPath + TIME_IN_STATE;
    std::unique_ptr<FILE, decltype(&fclose)> fp(fopen(path.c_str(), "r"), fclose);
    if (!fp) {
        PLOG(ERROR) << "Failed to open file " << path;
        return false;
    }

    std::vector<StateResidency> stateResidencies;
    for (int i = 0; i < mConfigs.size(); i++) {
        StateResidency s = {.id = i, .totalTimeInStateMs = 0};
        stateResidencies.push_back(s);
    }

    char *line = nullptr;
    size_t len = 0;
    Config config = { .state = 0, .resX = 0, .resY = 0, .rr = 0 };
    uint64_t duration;
    std::vector<Config>::const_iterator found;
    while (getline(&line, &len, fp.get()) != -1) {
        if (parseTimeInState(line, &config, &duration)) {
            found = std::find(mConfigs.begin(), mConfigs.end(), config);
            if (found != mConfigs.end()) {
                stateResidencies[found - mConfigs.begin()].totalTimeInStateMs = duration;
            } else {
                LOG(ERROR) << "Failed to find config for [" << std::string(line)
                           << "] in display MRR state list";
            }
        } else {
            LOG(ERROR) << "Failed to parse state and duration from [" << std::string(line) << "]";
            free(line);
            return false;
        }
    }

    residencies->emplace(mName, stateResidencies);

    free(line);

    return true;
}

std::unordered_map<std::string, std::vector<State>> DisplayMrrStateResidencyDataProvider::getInfo()
{
    int32_t dispId;
    std::string name;
    std::vector<State> states;
    for (int32_t id = 0; id < mConfigs.size(); id++) {
        dispId = mConfigs[id].state;
        if (dispId >= DISP_STATE.size()) {
            LOG(ERROR) << "Display state id " << dispId << " is out of bound";
            return {};
        }

        name = DISP_STATE[dispId];
        if (dispId != DISP_STATE.size() - 1) {
            name += ": " + std::to_string(mConfigs[id].resX) +
                    "x" + std::to_string(mConfigs[id].resY) +
                    "@" + std::to_string(mConfigs[id].rr);
        }
        State s = { .id = id, .name = name };
        states.push_back(s);
    }

    return {{ mName, states }};
}

}  // namespace stats
}  // namespace power
}  // namespace hardware
}  // namespace android
}  // namespace aidl
