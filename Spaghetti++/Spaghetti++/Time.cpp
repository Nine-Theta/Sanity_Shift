#include "Time.h"
#include "SFML/System/Clock.hpp"
namespace sge {
	//unsigned long Time::MicroTime();

	sf::Clock _timer;
	unsigned long Time::MicroTime()
	{
		return (unsigned long)_timer.getElapsedTime().asMicroseconds();
	}
	
	unsigned long Time::_timeStarted = Time::MicroTime();
	unsigned long Time::_lastUpdate = _timeStarted;
	float Time::_lastDelta = 0;
	float Time::_lastDeltaPhys = 0;
	float Time::_fixedDelta = 0.00833333333f;
	float Time::_maxGap = 0.2f;
	int Time::_frameRate = 0;

	unsigned long Time::_frame = 0;
	unsigned long Time::_physicsStep = 0;
	int Time::_stepsToComplete = 0;
	float Time::_fixedTimeToComplete = 0;


	static float _speedMult = 1;
	Time::Time()
	{
	}


	Time::~Time()
	{
	}

	void Time::Update()
	{
		unsigned long newTime = MicroTime();
		_lastDelta = (float)(newTime - _lastUpdate) * 0.000001f;
		_lastUpdate = newTime;
		_fixedTimeToComplete += UnscaledDelta();
		_stepsToComplete = (int)(_fixedTimeToComplete / _fixedDelta);
		_fixedTimeToComplete -= _stepsToComplete * _fixedDelta;
		_frameRate = (int)(1.f / _lastDelta);
		_frame++;
	}

	float Time::UnscaledDelta()
	{
		float delta = _lastDelta;
		if (delta < _maxGap) return delta;
		return _maxGap;
	}

	float Time::FixedDelta() {
		return Time::_fixedDelta;
	}

	bool Time::DoFixedStep() {
		if (_stepsToComplete > 0) {
			_physicsStep++;
			_stepsToComplete--;
			return true;
		}
		return false;
	}

	int Time::GetFramerate()
	{
		return _frameRate;
	}

	float Time::DeltaTime()
	{
		return _lastDelta;
	}

	float Time::TimeRunning() {
		return Time::MicroTime()*0.000001f;
	}
}