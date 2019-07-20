#ifndef _FORM_H_
#define _FORM_H_

#include <Dialogs.h>
#include <stdbool.h>

DialogRef showForm();
bool handleFormEvent(DialogRef form, short item);

#endif
