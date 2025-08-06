#pragma once
#ifndef STORAGE_H
#define STORAGE_H

#include <FS.h>
#include "Settings.h"

class Storage {
public:
    Storage(Settings& settings);
    void begin();
    fs::FS& getFS();
    bool isSDAvailable();

private:
    void migrateSettings();

    Settings& _settings;
    fs::FS* _fs;
    bool _sdAvailable = false;
};

#endif // STORAGE_H
