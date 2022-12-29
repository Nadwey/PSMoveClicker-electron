#include "input.hpp"

namespace Input
{
    Input::Input()
    {
#ifdef __linux__
        display = XOpenDisplay(0);
        root = DefaultRootWindow(display);
#elif _WIN32

#endif
    }

    Input::~Input()
    {
#ifdef __linux__
        XFlush(display);
        XCloseDisplay(display);
#elif _WIN32

#endif
    }

    void Input::MouseDown(MouseButton key)
    {
#ifdef __linux__
        XTestFakeButtonEvent(display, keyToX11Key(key), true, 0);
        XFlush(display);
#elif _WIN32
        // TODO, use version 1.x.x
#endif
    }

    void Input::MouseUp(MouseButton key)
    {

#ifdef __linux__
        XTestFakeButtonEvent(display, keyToX11Key(key), false, 0);
        XFlush(display);
#elif _WIN32
        // TODO, use version 1.x.x
#endif
    }

    void Input::MouseMove(int x, int y)
    {
        XTestFakeRelativeMotionEvent(display, x, y, 0);
        XFlush(display);
    }

#ifdef __linux__
    int Input::keyToX11Key(MouseButton key)
    {
        switch (key)
        {
        case MouseButton::LeftButton:
            return Button1;
        case MouseButton::RightButton:
            return Button3;
        };
#elif _WIN32

#endif
    };
};