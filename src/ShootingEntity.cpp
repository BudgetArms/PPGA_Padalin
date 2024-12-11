#include "ShootingEntity.h"

#include <execution>



ShootingEntity::ShootingEntity(const Shape& shape, const Point2f& position, int bulletsPerSecond, float maxHealth, float healingPerSecond) :
	Entity(shape, position, maxHealth, healingPerSecond),
	m_uArrBullets{ },
	//m_uArrBullets{ std::vector<std::unique_ptr<Bullet>>() },
	m_BulletsPerSecond{ bulletsPerSecond },
	m_AccumulatedSecBullets{ 0.0f }
{
}


void ShootingEntity::Draw() const
{
	Entity::Draw();


	for (const auto& bullet : m_uArrBullets)
		bullet->Draw();

}


void ShootingEntity::Update(float elapsedSec)
{
	Entity::Update(elapsedSec);


	m_AccumulatedSecBullets += elapsedSec;



	//Delete old bullets
	m_uArrBullets.erase(
		std::remove_if(m_uArrBullets.begin(), m_uArrBullets.end(),
			[](const auto& bullet)
			{
				return bullet->IsDead();
			}),
		m_uArrBullets.end() 
	);



	for (auto& bullet : m_uArrBullets)
		bullet->Update(elapsedSec);


}




const std::vector<std::unique_ptr<Bullet>>& ShootingEntity::GetBullets() const
{
	return m_uArrBullets;
}


void ShootingEntity::Shoot(float directionAngle)
{
	if(m_AccumulatedSecBullets < (1.f / m_BulletsPerSecond) )
		return;

	m_AccumulatedSecBullets = 0;
	m_uArrBullets.push_back(std::make_unique<Bullet>(m_Position, directionAngle));



	//m_uArrBullets.erase(m_uArrBullets.begin());

}





