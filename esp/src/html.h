#ifndef RETROCHIMP_HTML_H
#define RETROCHIMP_HTML_H

// ggrep -oP '(?<=").+(?="$)' html.h | sed 's/\\//g;s/%.//g' | wc -c
// + enough space for values
constexpr int kHTMLMaxLength = 1280;

constexpr char kHTML[] =
"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>%s</title>"
        "<style>"
            "body { font-family: Sans-Serif; }"
            "form { display: grid; grid-template-columns: 150px 200px; "
                   "grid-gap: 10px; }"
            "label { grid-column: 1 / 2; }"
            "input { grid-column: 2 / 3; }"
        "</style>"
    "</head>"
    "<body>"
        "<form method=\"post\">"
            "<label for=\"ssid\">WLAN:</label>"
            "<input type=\"text\" name=\"ssid\" value=\"%s\">"
            "<label for=\"pw\">WLAN Password:</label>"
            "<input type=\"text\" name=\"pw\" value=\"%s\">"
            "<input type=\"submit\" value=\"Save\">"
       "</form>"
    "</body>"
"</html>"
    ;

#endif
