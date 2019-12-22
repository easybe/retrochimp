#include "wifi.h"

#include <Timeout.h>

namespace wifi {

WiFiClient client;

bool setup(Config& config)
{
    WiFi.hostname(config.name);
    WiFi.mode(WIFI_STA);
    Serial.println(String("Trying to connect to ") + config.ssid);
    WiFi.begin(config.ssid, config.pw);
    bool connected = true;
    synergy::Timeout timeout{5000};
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        delay(1000);
        if (timeout.check()) {
            connected = false;
            break;
        }
    }
    IPAddress ip;
    if (connected) {
        ip = WiFi.localIP();
    } else {
        Serial.println("Could not connect to Wi-Fi, going into AP mode");
        WiFi.softAP(config.name);
        ip = WiFi.softAPIP();
    }
    Serial.println("IP address: " + ip.toString());
    return connected;
}

WiFiClient& getClient()
{
    return client;
}

}
