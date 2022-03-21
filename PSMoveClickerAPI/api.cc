#include <node.h>
#include "napi.h"

#include "PSMC.h"

PSMC::ControllerManager* controllerManager;

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
    return Napi::Boolean::New(env, true);
}

void Update(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    controllerManager->Process();
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

Napi::Object GetControllerColor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    int index = info[0].As<Napi::Number>().Int32Value();

    PSMC::RGB controllerColor = controllerManager->controllers.at(index)->GetColor();
    Napi::Object color = Napi::Object::New(env);
    color.Set("r", controllerColor.r);
    color.Set("g", controllerColor.g);
    color.Set("b", controllerColor.b);

    return color;
}

void SetControllerColor(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    int index = info[0].As<Napi::Number>().Int32Value();
    unsigned char r = info[1].As<Napi::Number>().Uint32Value();
    unsigned char g = info[2].As<Napi::Number>().Uint32Value();
    unsigned char b = info[3].As<Napi::Number>().Uint32Value();

    controllerManager->controllers.at(index)->SetColor(r, g, b);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
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