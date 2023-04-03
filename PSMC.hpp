#pragma once

#ifndef PSMC_H
#define PSMC_H

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "psmoveapi/include/psmoveapi.h"
#include <unordered_map>
#include <sstream>
#include <string>
#include "input.hpp"
#include <cmath>

struct ControllerHandler;

namespace PSMC
{
	class Controller;
	class ControllerManager;

	struct Controller
	{
		Vec3 prevGyroscope;
		bool clicked = false;
		int prevButtons;
	};

	class ControllerManager
	{
	public:
		ControllerManager();
		~ControllerManager();

		void Start();
		void Stop();

		void Update();

		static std::unordered_map<const char *, Controller> controllers; // stored by serial
		static float swingForce;
		static Input::Input *input;
		static bool adofaiMode;

	private:
		ControllerHandler *handler;
		psmoveapi::PSMoveAPI *api;
	};
}

struct ControllerHandler : public psmoveapi::Handler
{
	virtual void connect(Controller *controller)
	{
		printf("Connect: %s\n", controller->serial);
	}

	virtual void update(Controller *controller)
	{
		if (!PSMC::ControllerManager::controllers.count(controller->serial))
			PSMC::ControllerManager::controllers[controller->serial] = PSMC::Controller();

		PSMC::Controller *controllerEx = &PSMC::ControllerManager::controllers[controller->serial];

		controller->color.r = std::max(controller->color.r - 0.07f, 0.0f);
		controller->color.g = std::max(controller->color.g - 0.07f, 0.0f);
		controller->color.b = std::max(controller->color.b - 0.07f, 0.0f);

		// Left Click
		if (
			controller->gyroscope.x < PSMC::ControllerManager::swingForce && !controllerEx->clicked && controller->trigger <= 0.5f)
		{
			controller->color.r = 1.0f;
			controller->color.g = 1.0f;
			controller->color.b = 1.0f;
			controllerEx->clicked = true;

			if (PSMC::ControllerManager::adofaiMode)
			{
				PSMC::ControllerManager::input->KeyDown(static_cast<Input::KeyType>(static_cast<int>(Input::KeyType::A) + controller->index));
				PSMC::ControllerManager::input->KeyUp(static_cast<Input::KeyType>(static_cast<int>(Input::KeyType::A) + controller->index));
			}
			else
			{
				PSMC::ControllerManager::input->MouseDown(Input::MouseButton::LeftButton);
				PSMC::ControllerManager::input->MouseUp(Input::MouseButton::LeftButton);
			}
		}
		if (controller->buttons & Btn_CROSS && !(controllerEx->prevButtons & Btn_CROSS)) // Left button down
		{
			PSMC::ControllerManager::input->MouseDown(Input::MouseButton::LeftButton);
		}
		if (!(controller->buttons & Btn_CROSS) && controllerEx->prevButtons & Btn_CROSS) // Left button up
		{
			PSMC::ControllerManager::input->MouseUp(Input::MouseButton::LeftButton);
		}

		// Right click
		if (controller->buttons & Btn_CIRCLE && !(controllerEx->prevButtons & Btn_CIRCLE)) // Right button down
		{
			PSMC::ControllerManager::input->MouseDown(Input::MouseButton::RightButton);
		}
		if (!(controller->buttons & Btn_CIRCLE) && controllerEx->prevButtons & Btn_CIRCLE) // Right button up
		{
			PSMC::ControllerManager::input->MouseUp(Input::MouseButton::RightButton);
		}

		if (controller->gyroscope.x >= PSMC::ControllerManager::swingForce)
			controllerEx->clicked = false;

		// Mouse
		if (controller->trigger > 0.5f)
		{
			PSMC::ControllerManager::input->MouseMove(
				controller->gyroscope.z * -14.0f * (std::abs(controller->gyroscope.z) * 0.5f + 0.5f),
				controller->gyroscope.x * -10.0f * (std::abs(controller->gyroscope.x) * 0.5f + 0.5f));
			controller->color.g = 1.0f;
		}

		controllerEx->prevButtons = controller->buttons;
		PSMC::ControllerManager::controllers[controller->serial].prevGyroscope = controller->gyroscope;
	}

	virtual void disconnect(Controller *controller)
	{
		printf("Disconnect: %s\n", controller->serial);
	}
};

#endif // !PSMC_H
