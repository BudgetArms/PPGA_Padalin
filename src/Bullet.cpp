#include "Bullet.h"



Bullet::Bullet(const Point2f& position, const float angleDirection, float speed) :
	Object(Shape::Circle, position),
	m_BulletSpeed		{ speed },
	m_AngleDirection	{ angleDirection },
	m_AccumulatedSec	{ 0.0f	},
	m_MaxAccumulatedSec	{ 10.f	},
	m_Damage			{ 50.f	}
{
	SetSize(7);
	SetColor(1.f, 1.f, 1.f, 0.9f);
}





void Bullet::Update(float elapsedSec)
{
	m_AccumulatedSec += elapsedSec;
	
	m_Position.x += m_BulletSpeed * elapsedSec * cosf(m_AngleDirection * utils::g_toRadians);
	m_Position.y += m_BulletSpeed * elapsedSec * sinf(m_AngleDirection * utils::g_toRadians);

	if (m_AccumulatedSec > m_MaxAccumulatedSec)
		m_bDead = true;
}



float Bullet::GetDamage() const
{
	return m_Damage;
}


void Bullet::Destroy()
{
	m_bDead = true;
}



