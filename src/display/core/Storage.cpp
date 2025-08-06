#include "Storage.h"
#include <SD_MMC.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

Storage::Storage(Settings& settings) : _settings(settings), _fs(&SPIFFS) {}

void Storage::begin() {
    if (SD_MMC.begin("/sdcard", true)) {
        _fs = &SD_MMC;
        _sdAvailable = true;
        ESP_LOGI("Storage", "SD card mounted");
    } else {
        ESP_LOGW("Storage", "SD card mount failed, using SPIFFS");
        SPIFFS.begin(true);
        _fs = &SPIFFS;
        _sdAvailable = false;
    }
    migrateSettings();
}

fs::FS& Storage::getFS() {
    return *_fs;
}

bool Storage::isSDAvailable() {
    return _sdAvailable;
}

void Storage::migrateSettings() {
    _settings.setFS(*_fs);
    if (_fs->exists("/settings.json")) {
        if (!_settings.load()) {
            ESP_LOGE("Storage", "Failed to load settings, creating new one");
            _settings.save(true);
        }
    } else {
        ESP_LOGI("Storage", "No settings.json found, creating one");
        _settings.save(true); // Force save to the new filesystem
    }
}
