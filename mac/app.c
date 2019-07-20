#include <Dialogs.h>
#include <MacWindows.h>

#include "form.h"
#include "menu.h"
#include "serial.h"

void update(WindowRef w)
{
    SetPort(w);
    BeginUpdate(w);

    EndUpdate(w);
}

int main()
{
    println("Hello");

    EventRecord event;
    WindowRef win = NULL;
    DialogRef form = NULL;

#if !TARGET_API_MAC_CARBON
    InitGraf(&qd.thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(NULL);
#endif
    InitCursor();
    SetMenuBar(GetNewMBar(128));
    DrawMenuBar();
    enableMenuItems();

    for (;;) {
        if (form == NULL) {
            form = showForm();
        }

        SystemTask();

        GetNextEvent(everyEvent, &event);

        if (IsDialogEvent(&event)) {
            DialogRef dialog;
            short item;
            DialogSelect(&event, &dialog, &item);
            if (dialog == form) {
                if (handleFormEvent(dialog, item)) {
                    DisposeWindow(form);
                    form = NULL;
                }
            }
        }

        switch (event.what) {
            case keyDown:
                if (event.modifiers & cmdKey) {
                    handleMenuCommand(MenuKey(event.message & charCodeMask));
                }
                break;
            case mouseDown:
                switch (FindWindow(event.where, &win)) {
                    case inGoAway:
                        if (TrackGoAway(win, event.where)) {
                            DisposeWindow(win);
                            if (win == form) {
                                form = NULL;
                            }
                        }
                        break;
                    case inDrag:
                        DragWindow(win, event.where, &qd.screenBits.bounds);
                        break;
                    case inMenuBar:
                        handleMenuCommand(MenuSelect(event.where));
                        break;
                    case inContent:
                        SelectWindow(win);
                        break;
                    case inSysWindow:
                        SystemClick(&event, win);
                        break;
                }
                break;
            case updateEvt:
                update((WindowRef)event.message);
                break;
        }
    }
    return 0;
}
