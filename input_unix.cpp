#ifdef __linux__ // and X11
#include "input.hpp"
#include "mapper.hpp"

namespace Input
{
    Input::Input()
    {
        display = XOpenDisplay(0);
        root = DefaultRootWindow(display);
    }

    Input::~Input()
    {
        XFlush(display);
        XCloseDisplay(display);
    }

    void Input::MouseDown(MouseButton key)
    {
        XTestFakeButtonEvent(display, mapMouseButton(key), true, 0);
        XFlush(display);
    }

    void Input::MouseUp(MouseButton key)
    {
        XTestFakeButtonEvent(display, mapMouseButton(key), false, 0);
        XFlush(display);
    }

    void Input::MouseMove(int x, int y)
    {
        XTestFakeRelativeMotionEvent(display, x, y, 0);
        XFlush(display);
    }

    void Input::KeyDown(KeyType key)
    {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, mapKey(key)), true, 0);
        XFlush(display);
    }

    void Input::KeyUp(KeyType key)
    {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, mapKey(key)), false, 0);
        XFlush(display);
    }
};

#endif