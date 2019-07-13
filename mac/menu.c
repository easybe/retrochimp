#include "menu.h"

#include <Devices.h>
#include <MacWindows.h>
#include <Menus.h>
#include <Resources.h>
#include <TextEdit.h>

enum
{
    kMenuApple = 128,
    kMenuFile,
    kMenuEdit
};

enum
{
    kItemAbout = 1,
    kItemQuit = 1
};

void enableMenuItems()
{
    MenuRef m = GetMenu(kMenuEdit);
    EnableItem(m, 1);
    EnableItem(m, 3);
    EnableItem(m, 4);
    EnableItem(m, 5);
    EnableItem(m, 6);
}

void showAboutBox()
{
    WindowRef w = GetNewWindow(128, NULL, (WindowPtr)-1);
    MacMoveWindow(w, qd.screenBits.bounds.right / 2 - w->portRect.right / 2,
                  qd.screenBits.bounds.bottom / 2 - w->portRect.bottom / 2,
                  false);
    ShowWindow(w);
    SetPort(w);

    Handle h = GetResource('ABUT', 128);
    HLock(h);
    Rect r = w->portRect;
    InsetRect(&r, 10, 10);
    TETextBox(*h, GetHandleSize(h), &r, teJustLeft);

    ReleaseResource(h);
    while (!Button())
        ;
    while (Button())
        ;
    FlushEvents(everyEvent, 0);
    DisposeWindow(w);
}

void handleMenuCommand(long menuCommand)
{
    Str255 str;
    WindowRef w;
    short menuID = menuCommand >> 16;
    short menuItem = menuCommand & 0xFFFF;
    if (menuID == kMenuApple) {
        if (menuItem == kItemAbout) {
            showAboutBox();
        } else {
            GetMenuItemText(GetMenu(128), menuItem, str);
            OpenDeskAcc(str);
        }
    }
    else if (menuID == kMenuFile) {
        switch (menuItem) {
            case kItemQuit:
                ExitToShell();
                break;
        }
    }
    HiliteMenu(0);
}
