#ifdef _WIN32
#include "mapper.hpp"

namespace Input
{
    static long mouseTable[] = {
        MOUSEEVENTF_LEFTDOWN,   // left
        MOUSEEVENTF_MIDDLEDOWN, // middle
        MOUSEEVENTF_RIGHTDOWN,  // right
    };

    static long keyTable[] = {
        0x41, // A
        0x42, // B
        0x43, // C...
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A, // Z
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