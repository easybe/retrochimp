#include "input.h"

namespace input {

String getUserInfo()
{
    static String inputStr;
    String userInfo;

    int available = Serial.available();
    if (available) {
        byte buf[available + 1];
        buf[available] = '\0';
        inputStr += reinterpret_cast<const char*> (buf);
    }
    int end = inputStr.indexOf('\n');
    if (end != -1) {
        userInfo = inputStr.substring(0, end);
        userInfo.trim();
        inputStr.remove(0, end + 1);
    }

    return userInfo;
}

}
