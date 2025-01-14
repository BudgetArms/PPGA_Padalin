#pragma once

#include "FlyFish.h"

// Templates would make it less code :/

namespace FlyUtils
{

#if 0

	//TwoBlade
	ThreeBlade Project(const ThreeBlade& point, const OneBlade& projection)
	{
		return ((projection | point) * ~projection).Grade3();
	}
	
	ThreeBlade Project(const ThreeBlade& point, const TwoBlade& projection)
	{
		return ((projection | point) * ~projection).Grade3();
	}
 
	ThreeBlade Project(const ThreeBlade& point, const ThreeBlade& projection)
	{
		return ((projection | point) * ~projection);
	} 


	// TwoBlade
	TwoBlade Project(const TwoBlade& line, const OneBlade& projection)
	{
		return ((projection | line) * ~projection).Grade2();
	}
	
	TwoBlade Project(const TwoBlade& line, const TwoBlade& projection)
	{
		return ((projection | line) * ~projection);
	}
 
	TwoBlade Project(const TwoBlade& line, const ThreeBlade& projection)
	{
		return ((projection | line) * ~projection).Grade2();
	}


	// TwoBlade
	OneBlade Project(const OneBlade& plane, const OneBlade& projection)
	{
		return ((projection | plane) * ~projection);
	}
	
	OneBlade Project(const OneBlade& plane, const TwoBlade& projection)
	{
		return ((projection | plane) * ~projection).Grade1();
	}
 
	OneBlade Project(const OneBlade& plane, const ThreeBlade& projection)
	{
		return ((projection | plane) * ~projection).Grade1();
	}


#endif



	//float GetDistance(OneBlade& plane1,		OneBlade& plane2);
	//float GetDistance(TwoBlade& line1,		TwoBlade& line2);
	//float GetDistance(ThreeBlade& point1,	ThreeBlade& point2);
	//
	//float GetDistance(OneBlade& plane,		TwoBlade& line);
	//float GetDistance(OneBlade& plane,		ThreeBlade& point);
	//float GetDistance(TwoBlade& line,		ThreeBlade& point);


}


