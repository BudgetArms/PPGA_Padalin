#pragma once
#include "Enemy.h"


class MovingEnemy final : public Enemy 
{

public:

	MovingEnemy(const Point2f& position);


	MovingEnemy(MovingEnemy&)				= delete;
	MovingEnemy(MovingEnemy&&)				= delete;
	MovingEnemy operator&=(MovingEnemy&)	= delete;
	MovingEnemy operator&=(MovingEnemy&&)	= delete;

	virtual ~MovingEnemy() {};

	// go to player
	virtual void Update(float elapsedSec) override;

	void SetPlayerLocation(Point2f playerloc);

private:

	Point2f m_PlayerLocation;

	const float m_MaxSpeed;


};



