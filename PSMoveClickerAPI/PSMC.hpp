#pragma once

#ifndef PSMC_H
#define PSMC_H

#include "psmoveapi/include/psmove.h"
#include <vector>
#include <sstream>
#include "input.hpp"

namespace PSMC {
	class ControllerManager {
	public:
		ControllerManager();
		~ControllerManager();

		void Start();
	private:
		
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
}


#endif // !PSMC_H
