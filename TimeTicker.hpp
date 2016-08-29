#pragma once
#include <iostream>
struct TimeTicker
{
	TimeTicker(float lifeLength = 0) : duration(lifeLength), lifeTime(0) {}
	bool tick(float delta)
	{
		lifeTime += delta;
		if (lifeTime > duration)
		{
			lifeTime = 0; // reset
			return false;
		}
		return true;
	}

	void reset(float duration)
	{
		lifeTime = 0;
		this->duration = duration;
	}


	friend std::ostream &operator<< (std::ostream &os, const TimeTicker &ticker)
	{
		os << ticker.duration << " / " << ticker.lifeTime;
		return os;
	}

	float lifeTime;
	float duration;
};

