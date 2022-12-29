#include <node.h>
#include "napi.h"

#include "PSMC.hpp"

PSMC::ControllerManager* controllerManager;

PSMC::PSMove* GetControllerByID(int ID)
{
    for (int i = 0; i < controllerManager->controllers.size(); i++)
    {
        if (controllerManager->controllers[i]->GetController()->ControllerID == ID) return controllerManager->controllers[i];
    }

    return nullptr;
}

Napi::Boolean IsInitialized(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    return Napi::Boolean::New(env, PSM_GetIsInitialized());
}

Napi::Boolean IsConnected(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    return Napi::Boolean::New(env, PSM_GetIsConnected());
}

Napi::Boolean Start(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (controllerManager) return Napi::Boolean::New(env, false);

    try {
        controllerManager = new PSMC::ControllerManager();
        if (controllerManager) return Napi::Boolean::New(env, true);
    }
    catch (...) {

    }
    return Napi::Boolean::New(env, false);
}

Napi::Boolean Stop(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (!controllerManager) return Napi::Boolean::New(env, false);

    delete controllerManager;
    controllerManager = nullptr;
    return Napi::Boolean::New(env, true);
}

void Update(const Napi::CallbackInfo& info)
{
    if (PSM_GetIsConnected())
    {
        controllerManager->Process();
    }
}

Napi::Object GetInfo(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    Napi::Array controllers = Napi::Array::New(env);
    for (int i = 0; i < controllerManager->controllers.size(); i++)
    {
        Napi::Object controller = Napi::Object::New(env);
        PSMC::PSMove* psmove = controllerManager->controllers.at(i);
        controller.Set("Battery", controllerManager->GetBatteryText(i));
        controller.Set("ID", psmove->GetController()->ControllerID);
        controller.Set("IsMainPad", psmove->GetController()->ControllerID == controllerManager->mainPadID);
        controller.Set("RefreshRate", psmove->GetController()->DataFrameAverageFPS);
        controllers[i] = controller;
    }
    
    return controllers;
}

Napi::Number GetForce(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    return Napi::Number::New(env, controllerManager->force);
}

void SetForce(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    controllerManager->force = info[0].As<Napi::Number>().FloatValue();
}

Napi::Boolean GetIsADOFAIMode(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    return Napi::Boolean::New(env, controllerManager->ADOFAI_Mode);
}

void SetIsADOFAIMode(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    controllerManager->ADOFAI_Mode = info[0].As<Napi::Boolean>().Value();
}

Napi::Value GetControllerColor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    int ID = info[0].As<Napi::Number>().Int32Value();
    PSMC::PSMove* controller = GetControllerByID(ID);
    if (!controller) return env.Null();

    PSMC::RGB controllerColor = controller->GetColor();
    Napi::Object color = Napi::Object::New(env);
    color.Set("r", controllerColor.r);
    color.Set("g", controllerColor.g);
    color.Set("b", controllerColor.b);

    return color;
}

Napi::Value SetControllerColor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    int ID = info[0].As<Napi::Number>().Int32Value();
    PSMC::PSMove* controller = GetControllerByID(ID);
    if (!controller) return env.Null();

    unsigned char r = info[1].As<Napi::Number>().Uint32Value();
    unsigned char g = info[2].As<Napi::Number>().Uint32Value();
    unsigned char b = info[3].As<Napi::Number>().Uint32Value();

    controller->SetColor(r, g, b);
    return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "IsInitialized"), Napi::Function::New(env, IsInitialized));
    exports.Set(Napi::String::New(env, "IsConnected"), Napi::Function::New(env, IsConnected));
    exports.Set(Napi::String::New(env, "Start"), Napi::Function::New(env, Start));
    exports.Set(Napi::String::New(env, "Stop"), Napi::Function::New(env, Stop));
    exports.Set(Napi::String::New(env, "Update"), Napi::Function::New(env, Update));
    exports.Set(Napi::String::New(env, "GetInfo"), Napi::Function::New(env, GetInfo));
    exports.Set(Napi::String::New(env, "GetForce"), Napi::Function::New(env, GetForce));
    exports.Set(Napi::String::New(env, "SetForce"), Napi::Function::New(env, SetForce));
    exports.Set(Napi::String::New(env, "GetIsADOFAIMode"), Napi::Function::New(env, GetIsADOFAIMode));
    exports.Set(Napi::String::New(env, "SetIsADOFAIMode"), Napi::Function::New(env, SetIsADOFAIMode));
    exports.Set(Napi::String::New(env, "GetControllerColor"), Napi::Function::New(env, GetControllerColor));
    exports.Set(Napi::String::New(env, "SetControllerColor"), Napi::Function::New(env, SetControllerColor));
    return exports;
}

NODE_API_MODULE(PSMoveClickerAPI, Init)