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
        LeftButton = 0,
        RightButton,
    };

    class Input
    {
    public:
        Input();
        ~Input();

        void MouseDown(MouseButton key);
        void MouseUp(MouseButton key);
        void MouseMove(int x, int y);

    private:
        Display *display = nullptr;
        Window root = 0;

#ifdef __linux__
        int keyToX11Key(MouseButton key);
#elif _WIN32
        something keyToWinApiKey(MouseButton key);
#endif
    };
};
