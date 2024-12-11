#include "Globals.h"
#include "MovingEnemy.h"


MovingEnemy::MovingEnemy(const Point2f& position) :
	Enemy(position),
	m_PlayerLocation{ 0.f, 0.f },
	m_MaxSpeed{ 300.f }
{
}


void MovingEnemy::Update(float elapsedSec)
{

	float directionAngle{ atan2f(m_PlayerLocation.y - m_Position.y, m_PlayerLocation.x - m_Position.x) };


	m_Position.x += m_MaxSpeed * elapsedSec * cosf(directionAngle);
	m_Position.y += m_MaxSpeed * elapsedSec * sinf(directionAngle);

}

void MovingEnemy::SetPlayerLocation(Point2f playerLoc)
{
	m_PlayerLocation = playerLoc;
}


