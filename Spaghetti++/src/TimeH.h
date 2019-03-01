#pragma once
#include "SFML/System/Clock.hpp"
namespace sge {
	class TimeH
	{
	public:
		TimeH();
		~TimeH();
		static unsigned long MicroTime();
		static void Update();
		static float UnscaledDelta();
		static bool DoFixedStep();
		static int GetFramerate();
		static float DeltaTime();
		static float FixedDelta();
		static float TimeRunning();
		static unsigned GetFrame();
		/*protected:
			static unsigned long _timeStarted;
			static unsigned long _lastUpdate;*/
	private:
		static unsigned long _timeStarted;// = Time::MicroTime();
		static unsigned long _lastUpdate;// = _timeStarted;
		static float _lastDelta;// = 0;
		static float _lastDeltaPhys;// = 0;
		static float _fixedDelta;// = 0.01;
		static float _maxGap;// = 0.2;
		static int _frameRate;// = 0;

		static unsigned long _frame;// = 0;
		static unsigned long _physicsStep;// = 0;
		static int _stepsToComplete;// = 0;
		static float _fixedTimeToComplete;// = 0;
	};
}

