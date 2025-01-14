#include "FlyStructs.h"



FlyRect::FlyRect() :
	leftBottom	{},
	leftTop		{},
	rightBottom	{},
	rightTop	{}
{
}

FlyRect::FlyRect(const ThreeBlade& leftBottom, const ThreeBlade& leftTop, const ThreeBlade& rightTop, const ThreeBlade& rightBottom) : 
	leftBottom	{ leftBottom },
	leftTop		{ leftTop },
	rightTop	{ rightTop },
	rightBottom	{ rightBottom }
{
}



FlySquare::FlySquare() :
	center		{},
	sideLength	{ 10 }
{
}
 
FlySquare::FlySquare(const ThreeBlade& center, float sideLength) :
	center		{ center },
	sideLength	{ sideLength }
{
}



FlyCircle::FlyCircle() :
	center{},
	radius{ 10 }
{
}

FlyCircle::FlyCircle(const ThreeBlade& center, float radius) :
	center{ center },
	radius{ radius }
{
}





