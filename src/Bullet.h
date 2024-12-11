#pragma once
#include "Object.h"

#include <unordered_map>



class Bullet final : public Object
{
public:

	Bullet(const Point2f& centerPos, float angleDirection, float speed = 400);

	Bullet(const Bullet&)				= default;	// Copy constructor
	Bullet(Bullet&&)					= delete;	// Move constructor

	Bullet operator&=(const Bullet&)	= delete;	// Copy Assignment
	Bullet operator&=(Bullet&&)			= delete;	// Move Assignment
	//you can't move data if you have all 4 deleted

	virtual ~Bullet() {};


	virtual void Update(float elapsedSec) override;

	float GetDamage() const;

	void Destroy();

private:

	const float m_BulletSpeed;
	const float m_AngleDirection;

	float		m_AccumulatedSec;
	const float m_MaxAccumulatedSec;

	const float	m_Damage;

};


