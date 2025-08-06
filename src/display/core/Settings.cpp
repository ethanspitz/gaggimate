#include "Settings.h"
#include "ArduinoJson.h"

#include <utility>

Settings::Settings() {
    xTaskCreate(loopTask, "Settings::loop", configMINIMAL_STACK_SIZE * 6, this, 1, &taskHandle);
}

void Settings::batchUpdate(const SettingsCallback &callback) {
    callback(this);
    save();
}

void Settings::save(bool noDelay) {
    if (noDelay) {
        doSave();
        return;
    }
    dirty = true;
}

void Settings::setTargetBrewTemp(const int target_brew_temp) {
    targetBrewTemp = target_brew_temp;
    save();
}

void Settings::setTargetSteamTemp(const int target_steam_temp) {
    targetSteamTemp = target_steam_temp;
    save();
}

void Settings::setTargetWaterTemp(const int target_water_temp) {
    targetWaterTemp = target_water_temp;
    save();
}

void Settings::setTemperatureOffset(const int temperature_offset) {
    temperatureOffset = temperature_offset;
    save();
}

void Settings::setPressureScaling(const float pressure_scaling) {
    pressureScaling = pressure_scaling;
    save();
}

void Settings::setTargetDuration(const int target_duration) {
    targetDuration = target_duration;
    save();
}

void Settings::setTargetVolume(int target_volume) {
    targetVolume = target_volume;
    save();
}

void Settings::setTargetGrindVolume(double target_grind_volume) {
    targetGrindVolume = target_grind_volume;
    save();
}

void Settings::setTargetGrindDuration(const int target_duration) {
    targetGrindDuration = target_duration;
    save();
}

void Settings::setBrewDelay(double brew_Delay) {
    brewDelay = std::clamp(brew_Delay, 0.0, 4000.0);
    save();
}

void Settings::setGrindDelay(double grind_Delay) {
    grindDelay = std::clamp(grind_Delay, 0.0, 4000.0);
    save();
}

void Settings::setDelayAdjust(bool delay_adjust) {
    delayAdjust = delay_adjust;
    save();
}

void Settings::setStartupMode(const int startup_mode) {
    startupMode = startup_mode;
    save();
}

void Settings::setStandbyTimeout(int standby_timeout) {
    standbyTimeout = standby_timeout;
    save();
}

void Settings::setInfuseBloomTime(int infuse_bloom_time) {
    infuseBloomTime = infuse_bloom_time;
    save();
}

void Settings::setInfusePumpTime(int infuse_pump_time) {
    infusePumpTime = infuse_pump_time;
    save();
}

void Settings::setPressurizeTime(int pressurize_time) {
    pressurizeTime = pressurize_time;
    save();
}

void Settings::setPid(const String &pid) {
    this->pid = pid;
    save();
}

void Settings::setWifiSsid(const String &wifiSsid) {
    this->wifiSsid = wifiSsid;
    save();
}

void Settings::setWifiPassword(const String &wifiPassword) {
    this->wifiPassword = wifiPassword;
    save();
}

void Settings::setMdnsName(const String &mdnsName) {
    this->mdnsName = mdnsName;
    save();
}

void Settings::setHomekit(const bool homekit) {
    this->homekit = homekit;
    save();
}

void Settings::setVolumetricTarget(bool volumetric_target) {
    this->volumetricTarget = volumetric_target;
    save();
}

void Settings::setOTAChannel(const String &otaChannel) {
    this->otaChannel = otaChannel;
    save();
}

void Settings::setSavedScale(const String &savedScale) {
    this->savedScale = savedScale;
    save();
}

void Settings::setBoilerFillActive(bool boiler_fill_active) {
    boilerFillActive = boiler_fill_active;
    save();
}

void Settings::setStartupFillTime(int startup_fill_time) {
    startupFillTime = startup_fill_time;
    save();
}

void Settings::setSteamFillTime(int steam_fill_time) {
    steamFillTime = steam_fill_time;
    save();
}

void Settings::setSmartGrindActive(bool smart_grind_active) {
    smartGrindActive = smart_grind_active;
    save();
}

void Settings::setSmartGrindIp(String smart_grind_ip) {
    this->smartGrindIp = std::move(smart_grind_ip);
    save();
}

void Settings::setSmartGrindMode(int smart_grind_mode) {
    this->smartGrindMode = smart_grind_mode;
    save();
}

void Settings::setHomeAssistant(const bool homeAssistant) {
    this->homeAssistant = homeAssistant;
    save();
}

void Settings::setHomeAssistantIP(const String &homeAssistantIP) {
    this->homeAssistantIP = homeAssistantIP;
    save();
}

void Settings::setHomeAssistantPort(const int homeAssistantPort) {
    this->homeAssistantPort = homeAssistantPort;
    save();
}
void Settings::setHomeAssistantUser(const String &homeAssistantUser) {
    this->homeAssistantUser = homeAssistantUser;
    save();
}
void Settings::setHomeAssistantPassword(const String &homeAssistantPassword) {
    this->homeAssistantPassword = homeAssistantPassword;
    save();
}

void Settings::setMomentaryButtons(bool momentary_buttons) {
    momentaryButtons = momentary_buttons;
    save();
}

void Settings::setTimezone(String timezone) {
    this->timezone = std::move(timezone);
    save();
}

void Settings::setClockFormat(bool clock_24h_format) {
    this->clock24hFormat = clock_24h_format;
    save();
}

void Settings::setSelectedProfile(String selected_profile) {
    this->selectedProfile = std::move(selected_profile);
    save();
}

void Settings::setProfilesMigrated(bool profiles_migrated) {
    profilesMigrated = profiles_migrated;
    save();
}

void Settings::setFavoritedProfiles(std::vector<String> favorited_profiles) {
    favoritedProfiles = std::move(favorited_profiles);
    save();
}

void Settings::addFavoritedProfile(String profile) {
    favoritedProfiles.emplace_back(profile);
    save();
}

void Settings::removeFavoritedProfile(String profile) {
    favoritedProfiles.erase(std::remove(favoritedProfiles.begin(), favoritedProfiles.end(), profile), favoritedProfiles.end());
    favoritedProfiles.shrink_to_fit();
    save();
}

void Settings::setMainBrightness(int main_brightness) {
    mainBrightness = main_brightness;
    save();
}

void Settings::setStandbyBrightness(int standby_brightness) {
    standbyBrightness = standby_brightness;
    save();
}

void Settings::setStandbyBrightnessTimeout(int standby_brightness_timeout) {
    standbyBrightnessTimeout = standby_brightness_timeout;
    save();
}

void Settings::setWifiApTimeout(int timeout) {
    wifiApTimeout = timeout;
    save();
}

void Settings::setSteamPumpPercentage(float steam_pump_percentage) {
    steamPumpPercentage = steam_pump_percentage;
    save();
}

void Settings::setThemeMode(int theme_mode) {
    themeMode = theme_mode;
    save();
}

void Settings::setHistoryIndex(int history_index) {
    historyIndex = history_index;
    save();
}

void Settings::setSunriseR(int sunrise_r) {
    sunriseR = sunrise_r;
    save();
}

void Settings::setSunriseG(int sunrise_g) {
    sunriseG = sunrise_g;
    save();
}

void Settings::setSunriseB(int sunrise_b) {
    sunriseB = sunrise_b;
    save();
}

void Settings::setSunriseW(int sunrise_w) {
    sunriseW = sunrise_w;
    save();
}

void Settings::setSunriseExtBrightness(int sunrise_ext_brightness) {
    sunriseExtBrightness = sunrise_ext_brightness;
    save();
}

void Settings::setEmptyTankDistance(int empty_tank_distance) {
    emptyTankDistance = empty_tank_distance;
    save();
}

void Settings::setFullTankDistance(int full_tank_distance) {
    fullTankDistance = full_tank_distance;
    save();
}

void Settings::doSave() {
    if (!dirty) {
        return;
    }
    dirty = false;

    if (_fs == nullptr) {
        ESP_LOGE("Settings", "Filesystem not set");
        return;
    }

    ESP_LOGI("Settings", "Saving settings to settings.json");
    File file = _fs->open("/settings.json", "w");
    if (!file) {
        ESP_LOGE("Settings", "Failed to open settings.json for writing");
        return;
    }

    JsonDocument doc;
    doc["sm"] = startupMode;
    doc["tb"] = targetBrewTemp;
    doc["ts"] = targetSteamTemp;
    doc["tw"] = targetWaterTemp;
    doc["td"] = targetDuration;
    doc["tv"] = targetVolume;
    doc["tgv"] = targetGrindVolume;
    doc["tgd"] = targetGrindDuration;
    doc["del_br"] = brewDelay;
    doc["del_gd"] = grindDelay;
    doc["del_ad"] = delayAdjust;
    doc["to"] = temperatureOffset;
    doc["ps"] = pressureScaling;
    doc["pid"] = pid;
    doc["ws"] = wifiSsid;
    doc["wp"] = wifiPassword;
    doc["mn"] = mdnsName;
    doc["hk"] = homekit;
    doc["vt"] = volumetricTarget;
    doc["oc"] = otaChannel;
    doc["ipt"] = infusePumpTime;
    doc["ibt"] = infuseBloomTime;
    doc["pt"] = pressurizeTime;
    doc["ssc"] = savedScale;
    doc["bf_a"] = boilerFillActive;
    doc["bf_su"] = startupFillTime;
    doc["bf_st"] = steamFillTime;
    doc["sg_a"] = smartGrindActive;
    doc["sg_i"] = smartGrindIp;
    doc["sg_t"] = smartGrindToggle;
    doc["sg_m"] = smartGrindMode;
    doc["ha_a"] = homeAssistant;
    doc["ha_i"] = homeAssistantIP;
    doc["ha_p"] = homeAssistantPort;
    doc["ha_u"] = homeAssistantUser;
    doc["ha_pw"] = homeAssistantPassword;
    doc["tz"] = timezone;
    doc["clk_24h"] = clock24hFormat;
    doc["sp"] = selectedProfile;
    doc["sbt"] = standbyTimeout;
    doc["pm"] = profilesMigrated;
    doc["mb"] = momentaryButtons;
    JsonArray fp = doc["fp"].to<JsonArray>();
    for (const auto& profile : favoritedProfiles) {
        fp.add(profile);
    }
    doc["spp"] = steamPumpPercentage;
    doc["hi"] = historyIndex;

    // Display settings
    doc["main_b"] = mainBrightness;
    doc["standby_b"] = standbyBrightness;
    doc["standby_bt"] = standbyBrightnessTimeout;
    doc["wifi_apt"] = wifiApTimeout;
    doc["theme"] = themeMode;

    // Sunrise Settings
    doc["sr_r"] = sunriseR;
    doc["sr_g"] = sunriseG;
    doc["sr_b"] = sunriseB;
    doc["sr_w"] = sunriseW;
    doc["sr_exb"] = sunriseExtBrightness;
    doc["sr_ed"] = emptyTankDistance;
    doc["sr_fd"] = fullTankDistance;

    if (serializeJson(doc, file) == 0) {
        ESP_LOGE("Settings", "Failed to write to settings.json");
    }
    file.close();
}

bool Settings::load() {
    if (_fs == nullptr) {
        ESP_LOGE("Settings", "Filesystem not set");
        return false;
    }

    ESP_LOGI("Settings", "Loading settings from settings.json");
    File file = _fs->open("/settings.json", "r");
    if (!file) {
        ESP_LOGE("Settings", "Failed to open settings.json for reading");
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        ESP_LOGE("Settings", "Failed to parse settings.json: %s", error.c_str());
        file.close();
        return false;
    }

    startupMode = doc["sm"] | MODE_STANDBY;
    targetBrewTemp = doc["tb"] | 90;
    targetSteamTemp = doc["ts"] | 145;
    targetWaterTemp = doc["tw"] | 80;
    targetDuration = doc["td"] | 25000;
    targetVolume = doc["tv"] | 36;
    targetGrindVolume = doc["tgv"] | 18.0;
    targetGrindDuration = doc["tgd"] | 25000;
    brewDelay = doc["del_br"] | 1000.0;
    grindDelay = doc["del_gd"] | 1000.0;
    delayAdjust = doc["del_ad"] | true;
    temperatureOffset = doc["to"] | DEFAULT_TEMPERATURE_OFFSET;
    pressureScaling = doc["ps"] | DEFAULT_PRESSURE_SCALING;
    pid = doc["pid"] | DEFAULT_PID;
    wifiSsid = doc["ws"] | "";
    wifiPassword = doc["wp"] | "";
    mdnsName = doc["mn"] | DEFAULT_MDNS_NAME;
    homekit = doc["hk"] | false;
    volumetricTarget = doc["vt"] | false;
    otaChannel = doc["oc"] | DEFAULT_OTA_CHANNEL;
    infusePumpTime = doc["ipt"] | 0;
    infuseBloomTime = doc["ibt"] | 0;
    pressurizeTime = doc["pt"] | 0;
    savedScale = doc["ssc"] | "";
    momentaryButtons = doc["mb"] | false;
    boilerFillActive = doc["bf_a"] | false;
    startupFillTime = doc["bf_su"] | 5000;
    steamFillTime = doc["bf_st"] | 5000;
    smartGrindActive = doc["sg_a"] | false;
    smartGrindIp = doc["sg_i"] | "";
    smartGrindToggle = doc["sg_t"] | false;
    smartGrindMode = doc["sg_m"] | (smartGrindToggle ? 1 : 0);
    homeAssistant = doc["ha_a"] | false;
    homeAssistantIP = doc["ha_i"] | "";
    homeAssistantPort = doc["ha_p"] | 1883;
    homeAssistantUser = doc["ha_u"] | "";
    homeAssistantPassword = doc["ha_pw"] | "";
    standbyTimeout = doc["sbt"] | DEFAULT_STANDBY_TIMEOUT_MS;
    timezone = doc["tz"] | DEFAULT_TIMEZONE;
    clock24hFormat = doc["clk_24h"] | true;
    selectedProfile = doc["sp"] | "";
    profilesMigrated = doc["pm"] | false;
    favoritedProfiles.clear();
    for (JsonVariant v : doc["fp"].as<JsonArray>()) {
        favoritedProfiles.push_back(v.as<String>());
    }
    steamPumpPercentage = doc["spp"] | DEFAULT_STEAM_PUMP_PERCENTAGE;
    historyIndex = doc["hi"] | 0;

    // Display settings
    mainBrightness = doc["main_b"] | 16;
    standbyBrightness = doc["standby_b"] | 8;
    standbyBrightnessTimeout = doc["standby_bt"] | 60000;
    wifiApTimeout = doc["wifi_apt"] | DEFAULT_WIFI_AP_TIMEOUT_MS;
    themeMode = doc["theme"] | 0;

    // Sunrise Settings
    sunriseR = doc["sr_r"] | 0;
    sunriseG = doc["sr_g"] | 0;
    sunriseB = doc["sr_b"] | 255;
    sunriseW = doc["sr_w"] | 50;
    sunriseExtBrightness = doc["sr_exb"] | 255;
    emptyTankDistance = doc["sr_ed"] | 200;
    fullTankDistance = doc["sr_fd"] | 50;

    file.close();
    return true;
}

void Settings::loopTask(void *arg) {
    auto *settings = static_cast<Settings *>(arg);
    while (true) {
        settings->doSave();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void Settings::setFS(fs::FS &fs) {
    _fs = &fs;
}
