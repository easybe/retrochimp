#include <TextUtils.h>
#include <stdio.h>
#include <string.h>

#include "form.h"
#include "serial.h"

enum {
    kButton = 1,
    kButtonBorder,
    kLabelFirst,
    kFieldFirst,
    kLabelLast,
    kFieldLast,
    kLabelEmail,
    kFieldEmail,
    kLabelEamil2,
    kFieldEmail2
};

pascal void drawButtonFrame(DialogRef dlg, DialogItemIndex itemNo)
{
    DialogItemType type;
    Handle itemH;
    Rect box;

    GetDialogItem(dlg, 1, &type, &itemH, &box);
    InsetRect(&box, -4, -4);
    PenSize(3, 3);
    FrameRoundRect(&box, 16, 16);
}

DialogRef showForm()
{
    DialogRef form = GetNewDialog(128, 0, (WindowPtr)-1);
    SelectDialogItemText(form, kFieldFirst, 0, 32767);
    Rect box;
    Handle itemHandle;
    DialogItemType type;
    GetDialogItem(form, kButtonBorder, &type, &itemHandle, &box);
    SetDialogItem(form, kButtonBorder, type,
                  (Handle)NewUserItemUPP(&drawButtonFrame), &box);
    return form;
}

void getFieldVal(DialogRef form, int key, char *val)
{
    DialogItemType type;
    Handle itemH;
    Rect box;
    Str255 fieldVal;

    GetDialogItem(form, key, &type, &itemH, &box);
    GetDialogItemText(itemH, fieldVal);
    strcpy(val, p2cstr(fieldVal));
}

void sendFormData(DialogRef form)
{
    char val[255];
    char json[1024] = "{";

    getFieldVal(form, kFieldFirst, val);
    sprintf(json, "%s\"first\":\"%s\",", json, val);
    getFieldVal(form, kFieldLast, val);
    sprintf(json, "%s\"last\":\"%s\",", json, val);
    getFieldVal(form, kFieldEmail, val);
    sprintf(json, "%s\"email\":\"%s@", json, val);
    getFieldVal(form, kFieldEmail2, val);
    sprintf(json, "%s%s\"", json, val);
    strcat(json, "}");
    println(json);
}

void handleFormEvent(DialogRef form, short item)
{
    if (item == 1) {
        sendFormData(form);
        DisposeDialog(form);
    }
}
