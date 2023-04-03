#pragma once

#ifdef __linux__ // and X11
#include <X11/Xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#elif _WIN32
#include <Windows.h>
#else
#error Platform unsupported
#endif

#include <iostream>

namespace Input
{
    enum class MouseButton
    {
        LeftButton,
        MiddleButton,
        RightButton,
    };

    enum class KeyType { // :)
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        X,
        Y,
        Z
    };

    class Input
    {
    public:
        Input();
        ~Input();

        void MouseDown(MouseButton key);
        void MouseUp(MouseButton key);
        void MouseMove(int x, int y);

        void KeyDown(KeyType key);
        void KeyUp(KeyType key);

    private:
#ifdef __linux__ // and X11
        Display *display = nullptr;
        Window root = 0;
#endif
    };
};
