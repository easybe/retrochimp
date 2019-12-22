#include "mailchimp.h"

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#include "config.h"
#include "wifi.h"

namespace mailchimp {

String formatRequestData(String inStr)
{
    StaticJsonDocument<256> inData;
    DeserializationError res = deserializeJson(inData, inStr);
    if (res != DeserializationError::Ok) {
        return "";
    }
    StaticJsonDocument<256> outData;
    outData["email_address"] = inData["email"];
    outData["status"] = "subscribed";
    outData["merge_fields"]["FNAME"] = inData["first"];
    outData["merge_fields"]["LNAME"] = inData["last"];
    String outString;
    serializeJson(outData, outString);
    return outString;
}

bool signUp(String userInfo)
{
    HTTPClient http;
    Config& config = Config::getInstance();
    String url = String(config.mcURL) + "/members";
    http.begin(wifi::getClient(), url);
    http.addHeader("Content-Type", "application/json");
    http.setAuthorization(config.mcUser , config.mcKey);
    String data = formatRequestData(userInfo);
    if (data.length() == 0) {
        return false;
    }
    return http.POST(data) > 0;
}

}
