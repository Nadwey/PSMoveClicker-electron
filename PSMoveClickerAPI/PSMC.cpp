#include "PSMC.hpp"

namespace PSMC
{
    ControllerManager::ControllerManager()
    {
    }

    ControllerManager::~ControllerManager()
    {
    }

    void ControllerManager::Start()
    {
        if (!psmove_init(PSMOVE_CURRENT_VERSION))
        {
            fprintf(stderr, "PS Move API init failed (wrong version?)\n");
            exit(1);
        }

        handler = new ControllerHandler();
        api = new psmoveapi::PSMoveAPI(handler);
        input = new Input::Input();
    }

    void ControllerManager::Stop()
    {
        delete api;
        delete handler;
        delete input;
    }

    void ControllerManager::Update()
    {
        api->update();
    }

    std::unordered_map<const char*, Controller> ControllerManager::controllers;
    float ControllerManager::swingForce = -5;
    Input::Input* ControllerManager::input = nullptr;
}