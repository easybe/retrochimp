#include "Dialogs.r"

#define SPACE_H 5
#define SPACE_V 20
#define LABEL_X 10
#define LABEL_W 100
#define LABEL_H 16
#define FIELD_X (LABEL_X + LABEL_W)
#define FIELD_W 300
#define FIELD_H LABEL_H

#define LABEL_F_Y 20
#define FIELD_F_Y LABEL_F_Y

#define LABEL_L_Y (LABEL_F_Y + LABEL_H + SPACE_V)
#define FIELD_L_Y LABEL_L_Y

#define LABEL_E_Y (LABEL_L_Y + LABEL_H + SPACE_V)
#define FIELD_E_Y LABEL_E_Y
#define FIELD_E_W (FIELD_W / 2 - LABEL_E2_W / 2 - SPACE_H)

#define LABEL_E2_X (FIELD_X + FIELD_E_W + SPACE_H)
#define LABEL_E2_Y LABEL_E_Y
#define LABEL_E2_W 10
#define FIELD_E2_X (LABEL_E2_X + LABEL_E2_W + SPACE_H)
#define FIELD_E2_Y LABEL_E2_Y
#define FIELD_E2_W FIELD_E_W

#define WINDOW_X 100
#define WINDOW_Y 50
#define WINDOW_W (LABEL_X + LABEL_W + FIELD_W + LABEL_X)
#define WINDOW_H (3 * LABEL_H + 3 * SPACE_V + 70)

#define BUTTON_X (WINDOW_W - BUTTON_W - 10)
#define BUTTON_Y (WINDOW_H - BUTTON_H - 15)
#define BUTTON_W 200
#define BUTTON_H 30

resource 'DLOG' (128) {
    { WINDOW_Y, WINDOW_X, WINDOW_Y + WINDOW_H, WINDOW_X + WINDOW_W },
    noGrowDocProc,
    visible,
    goAway,
    0,
    128,
    "Retrochimp",
    centerMainScreen
};

resource 'DITL' (128) {
    {
        { BUTTON_Y, BUTTON_X, BUTTON_Y + BUTTON_H, BUTTON_X + BUTTON_W },
        Button { enabled, "Subscribe" };

        { BUTTON_Y - 5, BUTTON_X - 5, BUTTON_Y + BUTTON_H + 5, BUTTON_X + BUTTON_W + 5 },
        UserItem { enabled };

        { LABEL_F_Y, LABEL_X, LABEL_F_Y + LABEL_H, LABEL_X + LABEL_W },
        StaticText { enabled, "First Name" };

        { FIELD_F_Y, FIELD_X, FIELD_F_Y + FIELD_H, FIELD_X + FIELD_W },
        EditText { enabled, "" };

        { LABEL_L_Y, LABEL_X, LABEL_L_Y + LABEL_H, LABEL_X + LABEL_W },
        StaticText { enabled, "Last Name" };

        { FIELD_L_Y, FIELD_X, FIELD_L_Y + FIELD_H, FIELD_X + FIELD_W },
        EditText { enabled, "" };

        { LABEL_E_Y, LABEL_X, LABEL_E_Y + LABEL_H, LABEL_X + LABEL_W },
        StaticText { enabled, "Email" };

        { FIELD_E_Y, FIELD_X, FIELD_E_Y + FIELD_H, FIELD_X + FIELD_E_W },
        EditText { enabled, "" };

        { LABEL_E2_Y, LABEL_E2_X, LABEL_E2_Y + LABEL_H, LABEL_E2_X + LABEL_E2_W },
        StaticText { enabled, "@" };

        { FIELD_E2_Y, FIELD_E2_X, FIELD_E2_Y + FIELD_H, FIELD_E2_X + FIELD_E2_W },
        EditText { enabled, "" };
    }
};
