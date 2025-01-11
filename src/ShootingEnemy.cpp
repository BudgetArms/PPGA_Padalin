#include "ShootingEnemy.h"
#include "../Globals.h"


ShootingEnemy::ShootingEnemy(const Point2f& position) :
	ShootingEntity(Shape::Triangle, position, 1, 300, 20)
{
}


void ShootingEnemy::Update(float elapsedSec)
{
	float directionAngle { utils::g_toDegrees * atan2f(m_PlayerLocation.y - m_Position.y, m_PlayerLocation.x - m_Position.x) };

	ShootingEntity::Update(elapsedSec);
	Shoot(directionAngle);

}

void ShootingEnemy::SetPlayerLocation(Point2f playerLoc)
{
	m_PlayerLocation = playerLoc;
}



