#include "PSMC.hpp"

namespace PSMC
{
    void ControllerManager::Start()
    {
        if (!psmove_init(PSMOVE_CURRENT_VERSION))
        {
            fprintf(stderr, "PS Move API init failed (wrong version?)\n");
            exit(1);
        }

        
    }
}