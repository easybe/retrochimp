#include <Arduino.h>
#include <ESP8266mDNS.h>

#include <Timeout.h>

#include "config.h"
#include "webif.h"
#include "wifi.h"

Config& config = Config::getInstance();
bool netOK = false;

void setup()
{
    Serial.begin(9600);
    Serial.println("Booting");
    netOK = wifi::setup(config);
    MDNS.begin(config.name);
    webif::setup();
}

void loop()
{
    static synergy::Timeout configTimeout{30000};

    if (configTimeout.check()) {
        config.save();
    }
}
