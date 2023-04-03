#if _WIN32
#include "input.hpp"
#include "mapper.hpp"

namespace Input
{
    Input::Input()
    {
    }

    Input::~Input()
    {
    }

    void Input::MouseDown(MouseButton key)
    {
        INPUT inputs = {0};

        inputs.type = INPUT_MOUSE;
        inputs.mi.dwFlags = mapMouseButton(key);

        SendInput(1, &inputs, sizeof(INPUT));
    }

    void Input::MouseUp(MouseButton key)
    {
        INPUT inputs = {0};

        inputs.type = INPUT_MOUSE;
        inputs.mi.dwFlags = mapMouseButton(key) << 1;

        SendInput(1, &inputs, sizeof(INPUT));
    }

    void Input::MouseMove(int x, int y)
    {
        INPUT inputs = {0};
        inputs.type = INPUT_MOUSE;

        inputs.mi.dx = x;
        inputs.mi.dy = y;

        inputs.mi.dwFlags = MOUSEEVENTF_MOVE;
        SendInput(1, &inputs, sizeof(INPUT));
    }

    void Input::KeyDown(KeyType key)
    {
        INPUT inputs = { 0 };
		inputs.type = INPUT_KEYBOARD;
		inputs.ki.wVk = mapKey(key);
		inputs.ki.wScan = 0;
		inputs.ki.dwFlags = 0;
		inputs.ki.time = 0;
		inputs.ki.dwExtraInfo = 0;
        
        SendInput(1, &inputs, sizeof(INPUT));
    }

    void Input::KeyUp(KeyType key)
    {
        INPUT inputs = { 0 };

        inputs.type = INPUT_KEYBOARD;
		inputs.ki.wVk = mapKey(key);
		inputs.ki.wScan = 0;
		inputs.ki.dwFlags = KEYEVENTF_KEYUP;
		inputs.ki.time = 0;
		inputs.ki.dwExtraInfo = 0;

        SendInput(1, &inputs, sizeof(INPUT));
    }
};
#endif