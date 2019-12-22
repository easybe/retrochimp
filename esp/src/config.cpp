#include <Arduino.h>

#include <Storage.h>

#include "config.h"

Config Config::instance_{};

Config&
Config::getInstance()
{
    return instance_;
}

Config::Config() : dirty_{false}
{
    if (!load()) {
        Serial.println("No config found, using defaults");
        loadDefaults();
    }
}

void
Config::loadDefaults()
{
    strcpy(name, "retrochimp");
    strcpy(ssid, WIFI_SSID);
    strcpy(pw, WIFI_PW);
    dirty_ = true;
}

void
Config::markDirty()
{
    dirty_ = true;
}

void
Config::save()
{
    if (dirty_) {
        Storage::save();
        dirty_ = false;
    }
}
