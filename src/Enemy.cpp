#include "../Globals.h"
#include "Enemy.h"


Enemy::Enemy(const Point2f& centerPos, const Color4f& color) :
	Entity(Shape::Square, centerPos, 100)
{
	SetSize(10);
	SetColor(color);
}


