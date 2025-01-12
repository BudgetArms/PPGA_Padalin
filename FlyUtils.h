#pragma once

#include "FlyFish.h"


namespace FlyUtils
{
	

	float GetDistance(OneBlade& plane1,		OneBlade& plane2);
	float GetDistance(TwoBlade& line1,		TwoBlade& line2);
	float GetDistance(ThreeBlade& point1,	ThreeBlade& point2);
	
	float GetDistance(OneBlade& plane,		TwoBlade& line);
	float GetDistance(OneBlade& plane,		ThreeBlade& point);

	float GetDistance(TwoBlade& line,		ThreeBlade& point);


}


