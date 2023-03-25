#ifdef __linux__ // and X11
#include "mapper.hpp"
#include <X11/Xlib.h>
#include <X11/keysym.h>

namespace Input {
    static long mouseTable[] = {
        Button1, // left
        Button2, // middle
        Button3, // right
    };

    static long keyTable[] = {
        XK_A,
        XK_B,
        XK_C,
        XK_D,
        XK_E,
        XK_F,
        XK_G,
        XK_H,
        XK_I,
        XK_J,
        XK_K,
        XK_L,
        XK_M,
        XK_N,
        XK_O,
        XK_P,
        XK_Q,
        XK_R,
        XK_S,
        XK_T,
        XK_U,
        XK_V,
        XK_W,
        XK_X,
        XK_Y,
        XK_Z,
    };

    long mapMouseButton(MouseButton mouseBtn)
    {
        return mouseTable[static_cast<int>(mouseBtn)];
    }

    unsigned long mapKey(KeyType key)
    {
        return keyTable[static_cast<int>(key)];
    }
};

#endif