#include "webif.h"

#include <ESP8266WebServer.h>

#include "config.h"
#include "html.h"

namespace webif {

ESP8266WebServer webserver(80);

Config& config = Config::getInstance();

String getHTTPArg(const char* key)
{
    String s;
    s = webserver.arg(key);
    s.trim();
    return s;
}

String getHTML()
{
    char buf[kHTMLMaxLength];

    snprintf(buf, kHTMLMaxLength, kHTML, config.name, config.ssid, config.pw,
             config.mcURL, config.mcUser, config.mcKey);
    return buf;
}

void handleHTTPRequest()
{
    if (webserver.hasArg("ssid")) {
        String val = getHTTPArg("ssid");
        strcpy(config.ssid, val.c_str());
        val = getHTTPArg("pw");
        strcpy(config.pw, val.c_str());
        val = getHTTPArg("mc_url");
        strcpy(config.mcURL, val.c_str());
        val = getHTTPArg("mc_user");
        strcpy(config.mcUser, val.c_str());
        val = getHTTPArg("mc_key");
        strcpy(config.mcKey, val.c_str());
        config.save();
        Serial.println("Config saved");
    }
    webserver.send(200, "text/html", getHTML());
}

void setup()
{
    webserver.on("/", handleHTTPRequest);
    webserver.begin();
}

}
