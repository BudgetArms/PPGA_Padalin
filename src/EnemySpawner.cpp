#include "EnemySpawner.h"

#include "Enemy.h"
#include "MovingEnemy.h"




EnemySpawner::EnemySpawner(const Point2f& position, float spawnRatePerSecond) :
	Entity(Shape::Triangle, 2000.f),
	//m_sArrEnemies{ std::make_shared<std::vector<std::unique_ptr<Enemy>>>() },
	m_sArrEnemies{ std::make_shared<std::vector<std::unique_ptr<MovingEnemy>>>() },
	m_SpawnRatePerSecond{ spawnRatePerSecond },
	m_SpawnAccumlatedSec{ 0.f }
{
	SetPosition(position);
	SetSize(20);

	std::cout<< "Created EnemySpawner" << "\n";
}

EnemySpawner::~EnemySpawner()
{
	std::cout<< "Destroyed EnemySpawner" << "\n";
}


void EnemySpawner::Draw() const
{
	Entity::Draw();

	for (const auto& uEnemy : *m_sArrEnemies)
		uEnemy->Draw();

}

void EnemySpawner::Update(float elapsedSec)
{

	m_SpawnAccumlatedSec += elapsedSec;

	m_sArrEnemies->erase(
		std::remove_if(m_sArrEnemies->begin(), m_sArrEnemies->end(),
			[](auto& uEnemy)
			{
				return uEnemy->IsDead();
			}
		),
		m_sArrEnemies->end()
	);

	for (auto& uEnemy : *m_sArrEnemies)
		uEnemy->Update(elapsedSec);


	if (1 / m_SpawnRatePerSecond < m_SpawnAccumlatedSec && m_sArrEnemies->size() < 7)
	{
		m_SpawnAccumlatedSec = 0.0f;

		//m_sArrEnemies->push_back(std::make_unique<Enemy>(Point2f(m_Position.x + (rand() % 300) - 50, m_Position.y + (rand() % 200) - 50), Color4f(0.4f, 0.4f, 0.4f, 1.f )));
		m_sArrEnemies->push_back(std::make_unique<MovingEnemy>(Point2f(m_Position.x + (rand() % 300) - 50, m_Position.y + (rand() % 200) - 50)));

		for (auto& enemy : *m_sArrEnemies)
			enemy->SetSize(12);
	}


}


//
//std::shared_ptr<std::vector<std::unique_ptr<Enemy>>> EnemySpawner::GetSharedEnemies() const
//{
//	return m_sArrEnemies;
//}
// 

std::shared_ptr<std::vector<std::unique_ptr<MovingEnemy>>> EnemySpawner::GetSharedEnemies() const
{
	return m_sArrEnemies;
}


