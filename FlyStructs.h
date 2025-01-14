#pragma once
#include "FlyFish.h"


struct FlyRect
{
	FlyRect();
	explicit FlyRect(const ThreeBlade& leftBottom, const ThreeBlade& leftTop, const ThreeBlade& rightTop, const ThreeBlade& rightBottom);

	ThreeBlade leftBottom;
	ThreeBlade leftTop;
	ThreeBlade rightBottom;
	ThreeBlade rightTop;


}; 

struct FlySquare
{
	FlySquare();
	explicit FlySquare(const ThreeBlade& center, float sideLenngth);

	ThreeBlade center;
	float sideLength;


};
 

struct FlyCircle
{
	FlyCircle();
	explicit FlyCircle(const ThreeBlade& center, float radius);

	ThreeBlade center;
	float radius;



};



