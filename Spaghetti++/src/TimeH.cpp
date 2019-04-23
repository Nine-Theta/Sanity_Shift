#include "TimeH.h"
#include "SFML/System/Clock.hpp"
#include <iostream>
namespace sge {
	//unsigned long Time::MicroTime();

	sf::Clock _timer;
	unsigned long TimeH::MicroTime()
	{
		return (unsigned long)_timer.getElapsedTime().asMicroseconds();
	}
	
	unsigned long TimeH::_timeStarted = TimeH::MicroTime();
	unsigned long TimeH::_lastUpdate = _timeStarted;
	float TimeH::_lastDelta = 0;
	float TimeH::_lastDeltaPhys = 0;
	float TimeH::_fixedDelta = 0.00833333333f;
	float TimeH::_maxGap = 0.2f;
	float TimeH::_timeScale = 1.0f;
	int TimeH::_frameRate = 0;
	int TimeH::_frameLast = 0;
	int TimeH::_frameNow = 0;

	unsigned long TimeH::_frame = 0;
	unsigned long TimeH::_physicsStep = 0;
	int TimeH::_stepsToComplete = 0;
	float TimeH::_fixedTimeToComplete = 0;

	static float _speedMult = 1;

	TimeH::TimeH()
	{
	}

	TimeH::~TimeH()
	{
	}

	void TimeH::Update()
	{
		unsigned long newTime = MicroTime();
		_lastDelta = (float)(newTime - _lastUpdate) * 0.000001f;
		_lastUpdate = newTime;
		_fixedTimeToComplete += UnscaledDelta();
		_stepsToComplete = (int)(_fixedTimeToComplete / _fixedDelta);
		_fixedTimeToComplete -= _stepsToComplete * _fixedDelta;
		_frameRate = (int)(1.f / _lastDelta);
		_frame++;
		if (_physicsStep % 120 == 0 && _stepsToComplete != 0) {
			_frameLast = _frameNow;
			_frameNow = _frame;
			//std::cout << "Updated framerate avg" << std::endl;
		}
	}

	void TimeH::SetTimeScale(float scale = 1.0f)
	{
		if(scale >= 0) _timeScale = scale;
	}

	float TimeH::UnscaledDelta()
	{
		float delta = _lastDelta;
		if (delta < _maxGap) return delta;
		return _maxGap;
	}

	float TimeH::FixedDelta() {
		return (TimeH::_fixedDelta * _timeScale);
	}

	float TimeH::UnscaledFixedDelta() {
		return (TimeH::_fixedDelta);
	}

	float TimeH::GetTimeScale()
	{
		return _timeScale;
	}

	bool TimeH::DoFixedStep() {
		if (_stepsToComplete > 0) {
			_physicsStep++;
			_stepsToComplete--;
			return true;
		}
		return false;
	}

	int TimeH::GetFramerate()
	{
		return _frameRate;
	}

	int TimeH::GetFramerateAvg()
	{
		return _frameNow - _frameLast;
	}

	float TimeH::DeltaTime()
	{
		return _lastDelta;
	}

	float TimeH::TimeRunning() {
		return TimeH::MicroTime()*0.000001f;
	}
	unsigned TimeH::GetFrame()
	{
		return _frame;
	}
	unsigned TimeH::GetFixedFrame()
	{
		return _physicsStep;
	}
}