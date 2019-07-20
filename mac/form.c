#include <TextUtils.h>
#include <stdio.h>
#include <string.h>

#include "form.h"
#include "serial.h"

typedef enum {
    kNone = 0,
    kButton,
    kButtonBorder,
    kLabelFirst,
    kFieldFirst,
    kLabelLast,
    kFieldLast,
    kLabelEmail,
    kFieldEmail,
    kLabelEamil2,
    kFieldEmail2
} ItemId;

pascal void drawButtonFrame(DialogRef dlg, DialogItemIndex itemNo)
{
    DialogItemType type;
    Handle itemH;
    Rect box;

    GetDialogItem(dlg, kButton, &type, &itemH, &box);
    InsetRect(&box, -4, -4);
    PenSize(3, 3);
    FrameRoundRect(&box, 16, 16);
}

void selectItem(DialogRef form, ItemId item) {
    SelectDialogItemText(form, item, 0, 32767);
}

DialogRef showForm()
{
    DialogRef form = GetNewDialog(128, 0, (WindowPtr)-1);
    selectItem(form, kFieldFirst);
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

ItemId validateForm(DialogRef form)
{
    char val[255];
    getFieldVal(form, kFieldFirst, val);
    if (strcmp(val, "") == 0) {
        return kFieldFirst;
    }
    getFieldVal(form, kFieldLast, val);
    if (strcmp(val, "") == 0) {
        return kFieldLast;
    }
    getFieldVal(form, kFieldEmail, val);
    if (strcmp(val, "") == 0) {
        return kFieldEmail;
    }
    getFieldVal(form, kFieldEmail2, val);
    if (strcmp(val, "") == 0) {
        return kFieldEmail2;
    }
    return kNone;
}

bool handleFormEvent(DialogRef form, short item)
{
    if (item != kButton) {
        return false;
    }

    ItemId emptyItem = validateForm(form);
    if (emptyItem == kNone) {
        sendFormData(form);
        return true;
    } else {
        selectItem(form, emptyItem);
    }
    return false;
}
