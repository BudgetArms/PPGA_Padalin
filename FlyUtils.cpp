#include "FlyUtils.h"

#include <iostream>


// fucked

#pragma region GetDistance


float FlyUtils::GetDistance(OneBlade& plane1, OneBlade& plane2)
{
	


}

float FlyUtils::GetDistance(TwoBlade& line1, TwoBlade& line2)
{
	MultiVector tester = line1 ^ line2;

	std::cout << tester.toString() << "\n";
}

float FlyUtils::GetDistance(ThreeBlade& point1, ThreeBlade& point2)
{
	GANull tester = point1 ^ point2;

	tester.toString();


}


// meet = poindcaredual(point1), poincaredual(p2))
float FlyUtils::GetDistance(OneBlade& plane, TwoBlade& line)
{



}

float FlyUtils::GetDistance(OneBlade& plane, ThreeBlade& point)
{


}

float FlyUtils::GetDistance(TwoBlade& line, ThreeBlade& point)
{



} 

float FlyUtils::GetDistance(TwoBlade& line, ThreeBlade& point)
{



}


#pragma endregion


