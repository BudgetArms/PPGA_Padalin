#pragma once

#include "ShootingEntity.h"
#include "Enemy.h"


class ShootingEnemy : public ShootingEntity
{
public:

	ShootingEnemy(const Point2f& position);


	ShootingEnemy(ShootingEnemy&)				= delete;
	ShootingEnemy(ShootingEnemy&&)				= delete;
	ShootingEnemy operator&=(ShootingEnemy&)	= delete;
	ShootingEnemy operator&=(ShootingEnemy&&)	= delete;

	virtual ~ShootingEnemy() {};


	// go to player
	virtual void Update(float elapsedSec) override;

	void SetPlayerLocation(Point2f playerloc);

private:

	Point2f m_PlayerLocation;




};

