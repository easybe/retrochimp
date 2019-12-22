#ifndef RETROCHIMP_WIFI_H
#define RETROCHIMP_WIFI_H

#include <ESP8266WiFi.h>

#include "config.h"

namespace wifi {

bool setup(Config& config);
WiFiClient& getClient();

}

#endif
