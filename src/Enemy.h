#pragma once
#include "Globals.h"
#include "Entity.h"


class Enemy : public Entity
{
public:

	Enemy(const Point2f& position, const Color4f& color = Color4f(1.f, 1.f, 1.f, 1.f) );

	Enemy(Enemy&)				= delete;
	Enemy(Enemy&&)				= delete;
	Enemy operator&=(Enemy&)	= delete;
	Enemy operator&=(Enemy&&)	= delete;

	virtual ~Enemy() {};


	// go to player
	//virtual void Update(float elapsedSec) override;

private:



};



