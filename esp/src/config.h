#ifndef RETROCHIMP_CONFIG_H
#define RETROCHIMP_CONFIG_H

#include <Storage.h>

struct Config_ {
    char name[32];
    char ssid[32];
    char pw[32];
};

class Config : public synergy::Storage<Config_> {
public:
    static Config& getInstance();

    void markDirty();
    void save();

private:
    Config();
    void loadDefaults();

    static Config instance_;

    bool dirty_;
};

#endif
