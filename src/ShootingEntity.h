#pragma once
#include <memory>

#include "Entity.h"
#include "Bullet.h"


class ShootingEntity : public Entity
{
public:

	ShootingEntity(const Shape& shape, const Point2f& position, int bulletsPerSecond, float maxHealth = 100.f, float healingPerSecond = 5.f);

	ShootingEntity(ShootingEntity&)				= delete;
	ShootingEntity(ShootingEntity&&)			= delete;
	ShootingEntity operator&=(ShootingEntity&)	= delete;
	ShootingEntity operator&=(ShootingEntity&&)	= delete; 


	virtual ~ShootingEntity() {};

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	const std::vector<std::unique_ptr<Bullet>>& GetBullets() const;

private:

	std::vector<std::unique_ptr<Bullet>>	m_uArrBullets;

	const int	m_BulletsPerSecond;
	float		m_AccumulatedSecBullets;


protected:

	void Shoot(float directionAngle);


};



