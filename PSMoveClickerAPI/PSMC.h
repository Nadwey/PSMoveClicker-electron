#pragma once

#ifndef PSMC_H
#define PSMC_H

#include "PSMoveClient_CAPI/PSMoveClient_CAPI.h"
#include <vector>
#include <sstream>
#include <Windows.h>

namespace PSMC {
	class PSMove;

	class ControllerManager {
	public:
		ControllerManager();
		~ControllerManager();

		void Process();
		static std::string GetBatteryText(int controllerIndex);

		static bool ADOFAI_Mode;
		static PSMControllerID mainPadID;
		static float force;
		static std::vector<PSMove*> controllers; // :eyes:
	private:
		void RebuildControllerList();

		void InitializeControllers();
		void UninitializeControllers();

		static PSMControllerList controllerList;

		friend class PSMove;
	};

	// True == down, False == up
	struct PSMoveButtons {
		bool CircleButton;
		bool CrossButton;
		bool MoveButton;
		bool PSButton;
		bool SelectButton;
		bool SquareButton;
		bool StartButton;
		bool TriangleButton;
	};

	struct RGB {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	class PSMove {
	public:
		PSMove(PSMController* controller);
		~PSMove();

		void Process();
		void SetColor(unsigned char r, unsigned char g, unsigned char b);
		RGB GetColor();

		const PSMController* GetController();
	private:
		void UpdateButtonStates();

		
		void UpdateColor();

		PSMoveButtons buttonPrevStates = { 0 };
		PSMVector3f gyroPrevState;
		PSMController* controller = nullptr;
		RGB color = { 0, 0, 0 };

		friend class ControllerManager;
	};
}



// Copy and pase .cpp file
// Best solution

namespace PSMC {
	//
	// public:
	//

	ControllerManager::ControllerManager()
	{
		if (PSM_Initialize(PSMOVESERVICE_DEFAULT_ADDRESS, PSMOVESERVICE_DEFAULT_PORT, PSM_DEFAULT_TIMEOUT) != PSMResult_Success)
		{
			throw std::runtime_error("Failed to initialize client");
		}
		RebuildControllerList();
		InitializeControllers();
	}

	ControllerManager::~ControllerManager()
	{
		UninitializeControllers();
	}

	void ControllerManager::Process()
	{
		if (PSM_GetIsConnected())
		{
			PSM_Update();
			
			if (PSM_HasControllerListChanged())
			{
				UninitializeControllers();
				RebuildControllerList();
				InitializeControllers();
			}

			for (int i = 0; i < controllers.size(); i++)
			{
				controllers.at(i)->Process();
			}
		}
	}

	std::string ControllerManager::GetBatteryText(int controllerIndex)
	{
		PSMController* controller = controllers[controllerIndex]->controller;
		std::string batteryText;
		if (controller->ControllerState.PSMoveState.BatteryValue == PSMBattery_Charging) batteryText = "Charging...";
		else if (controller->ControllerState.PSMoveState.BatteryValue == PSMBattery_Charged) batteryText = "Charged";
		else {
			batteryText = std::to_string(controller->ControllerState.PSMoveState.BatteryValue * 20);
			batteryText += "%";
		}

		return batteryText;
	}

	bool ControllerManager::ADOFAI_Mode = false;
	PSMControllerID ControllerManager::mainPadID = 0;
	float ControllerManager::force = -4.0f;

	//
	// private:
	//

	void ControllerManager::RebuildControllerList()
	{
		memset(&controllerList, 0, sizeof(PSMControllerList));
		PSM_GetControllerList(&controllerList, PSM_DEFAULT_TIMEOUT);
	}

	void ControllerManager::InitializeControllers()
	{
		controllers.resize(controllerList.count);
		for (int i = 0; i < controllerList.count; i++)
		{
			PSM_AllocateControllerListener(controllerList.controller_id[i]);
			PSM_StartControllerDataStream(
				controllerList.controller_id[i],
				PSMControllerDataStreamFlags::PSMStreamFlags_defaultStreamOptions | PSMControllerDataStreamFlags::PSMStreamFlags_includeCalibratedSensorData,
				PSM_DEFAULT_TIMEOUT
			);

			controllers[i] = new PSMove(PSM_GetController(controllerList.controller_id[i]));
		}
	}

	void ControllerManager::UninitializeControllers()
	{
		controllers.clear();
		for (int i = 0; i < controllerList.count; i++)
		{
			PSM_StopControllerDataStream(controllerList.controller_id[i], PSM_DEFAULT_TIMEOUT);
			PSM_FreeControllerListener(controllerList.controller_id[i]);
		}
	}

	PSMControllerList ControllerManager::controllerList = { 0 };
	std::vector<PSMove*> ControllerManager::controllers;
}

namespace PSMC {
	//
	// public:
	//

	PSMove::PSMove(PSMController* controller) : controller(controller)
	{

	}

	PSMove::~PSMove()
	{

	}

	void PSMove::Process()
	{
		PSMPSMove& psMoveState = controller->ControllerState.PSMoveState;


		// Left Mouse Button
		if (psMoveState.CrossButton == PSMButtonState_PRESSED || psMoveState.CrossButton == PSMButtonState_DOWN && !buttonPrevStates.CrossButton)
		{
			INPUT Inputs[1] = { 0 };
			Inputs[0].type = INPUT_MOUSE;
			Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, Inputs, sizeof(INPUT));
		}
		if (psMoveState.CrossButton == PSMButtonState_RELEASED || psMoveState.CrossButton == PSMButtonState_UP && buttonPrevStates.CrossButton)
		{
			INPUT Inputs[1] = { 0 };
			Inputs[0].type = INPUT_MOUSE;
			Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, Inputs, sizeof(INPUT));
		}
		if (psMoveState.CrossButton == PSMButtonState_PRESSED || psMoveState.CrossButton == PSMButtonState_DOWN) SetColor(255, 255, 255);


		// Right Mouse Button
		if (psMoveState.CircleButton == PSMButtonState_PRESSED || psMoveState.CircleButton == PSMButtonState_DOWN && !buttonPrevStates.CircleButton)
		{
			INPUT Inputs[1] = { 0 };
			Inputs[0].type = INPUT_MOUSE;
			Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			SendInput(1, Inputs, sizeof(INPUT));
		}
		if (psMoveState.CircleButton == PSMButtonState_RELEASED || psMoveState.CircleButton == PSMButtonState_UP && buttonPrevStates.CircleButton)
		{
			INPUT Inputs[1] = { 0 };
			Inputs[0].type = INPUT_MOUSE;
			Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			SendInput(1, Inputs, sizeof(INPUT));
		}
		if (psMoveState.CircleButton == PSMButtonState_PRESSED || psMoveState.CircleButton == PSMButtonState_DOWN) SetColor(0, 0, 255);


		// Escape
		if (psMoveState.SelectButton == PSMButtonState_PRESSED || psMoveState.SelectButton == PSMButtonState_DOWN && !buttonPrevStates.SelectButton)
		{
			INPUT Inputs[1] = { 0 };
			Inputs[0].type = INPUT_KEYBOARD;
			Inputs[0].ki.wVk = VK_ESCAPE;
			Inputs[0].ki.wScan = 0;
			Inputs[0].ki.dwFlags = 0;
			Inputs[0].ki.time = 0;
			Inputs[0].ki.dwExtraInfo = 0;
			SendInput(1, Inputs, sizeof(INPUT));
		}
		if (psMoveState.SelectButton == PSMButtonState_RELEASED || psMoveState.SelectButton == PSMButtonState_UP && buttonPrevStates.SelectButton)
		{
			INPUT Inputs[1] = { 0 };
			Inputs[0].type = INPUT_KEYBOARD;
			Inputs[0].ki.wVk = VK_ESCAPE;
			Inputs[0].ki.wScan = 0;
			Inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
			Inputs[0].ki.time = 0;
			Inputs[0].ki.dwExtraInfo = 0;
			SendInput(1, Inputs, sizeof(INPUT));
		}
		if (psMoveState.SelectButton == PSMButtonState_PRESSED || psMoveState.SelectButton == PSMButtonState_DOWN) SetColor(255, 0, 0);


		// Cursor move
		if (controller->ControllerState.PSMoveState.TriggerValue > 200)
		{
			INPUT Input = { 0 };
			Input.type = INPUT_MOUSE;

			Input.mi.dx = controller->ControllerState.PSMoveState.CalibratedSensorData.Gyroscope.z * -10.0f;
			Input.mi.dy = controller->ControllerState.PSMoveState.CalibratedSensorData.Gyroscope.x * -12.5f;

			Input.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &Input, sizeof(INPUT));
			SetColor(0, 255, 0);
		}
		else if (controller->ControllerState.PSMoveState.CalibratedSensorData.Gyroscope.x < ControllerManager::force && gyroPrevState.x > ControllerManager::force) { // Click
			if (ControllerManager::mainPadID == controller->ControllerID || !ControllerManager::ADOFAI_Mode)
			{
				INPUT Inputs[2] = { 0 };
				Inputs[0].type = INPUT_MOUSE;
				Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				Inputs[1].type = INPUT_MOUSE;
				Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(2, Inputs, sizeof(INPUT));
			}
			else {
				INPUT Inputs[2] = { 0 };
				Inputs[0].type = INPUT_KEYBOARD;
				Inputs[0].ki.wVk = 0x41 + controller->ControllerID;
				Inputs[0].ki.wScan = 0;
				Inputs[0].ki.dwFlags = 0;
				Inputs[0].ki.time = 0;
				Inputs[0].ki.dwExtraInfo = 0;

				Inputs[1].type = INPUT_KEYBOARD;
				Inputs[1].ki.wVk = 0x41 + controller->ControllerID;
				Inputs[1].ki.wScan = 0;
				Inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
				Inputs[1].ki.time = 0;
				Inputs[1].ki.dwExtraInfo = 0;

				SendInput(2, Inputs, sizeof(INPUT));
			}
			SetColor(255, 255, 255);
		}

		// Main pad
		if (psMoveState.PSButton == PSMButtonState_DOWN)
		{
			ControllerManager::mainPadID = controller->ControllerID;
		}


		UpdateButtonStates();
		UpdateColor();
		gyroPrevState = controller->ControllerState.PSMoveState.CalibratedSensorData.Gyroscope;
	}

	void PSMove::SetColor(unsigned char r, unsigned char g, unsigned char b)
	{
		color.r = r;
		color.g = g;
		color.b = b;
	}

	RGB PSMove::GetColor()
	{
		return color;
	}

	const PSMController* PSMove::GetController()
	{
		return controller;
	}

	//
	// private:
	//

	void PSMove::UpdateButtonStates()
	{
		buttonPrevStates.CircleButton = controller->ControllerState.PSMoveState.CircleButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.CircleButton == PSMButtonState_PRESSED;
		buttonPrevStates.CrossButton = controller->ControllerState.PSMoveState.CrossButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.CrossButton == PSMButtonState_PRESSED;
		buttonPrevStates.MoveButton = controller->ControllerState.PSMoveState.MoveButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.MoveButton == PSMButtonState_PRESSED;
		buttonPrevStates.PSButton = controller->ControllerState.PSMoveState.PSButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.PSButton == PSMButtonState_PRESSED;
		buttonPrevStates.SelectButton = controller->ControllerState.PSMoveState.SelectButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.SelectButton == PSMButtonState_PRESSED;
		buttonPrevStates.SquareButton = controller->ControllerState.PSMoveState.SquareButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.SquareButton == PSMButtonState_PRESSED;
		buttonPrevStates.StartButton = controller->ControllerState.PSMoveState.StartButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.StartButton == PSMButtonState_PRESSED;
		buttonPrevStates.TriangleButton = controller->ControllerState.PSMoveState.TriangleButton == PSMButtonState_DOWN || controller->ControllerState.PSMoveState.TriangleButton == PSMButtonState_PRESSED;
	}

	void PSMove::UpdateColor()
	{
		PSM_SetControllerLEDOverrideColor(controller->ControllerID, color.r, color.g, color.b);

		const unsigned char minus = 15.0f;
		const unsigned char brightness = ControllerManager::ADOFAI_Mode ? (controller->ControllerID == ControllerManager::mainPadID ? 5 : 0) : 0;

		const unsigned char r = static_cast<unsigned char>(color.r - minus) > color.r ? 0 : static_cast<unsigned char>(color.r - minus);
		const unsigned char g = static_cast<unsigned char>(color.g - minus) > color.g ? 0 : static_cast<unsigned char>(color.g - minus);
		const unsigned char b = static_cast<unsigned char>(color.b - minus) > color.b ? 0 : static_cast<unsigned char>(color.b - minus);

		color.r = r < brightness ? brightness : r;
		color.g = g < brightness ? brightness : g;
		color.b = b < brightness ? brightness : b;
	}
}

#endif // !PSMC_H
