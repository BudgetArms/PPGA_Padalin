#include "EntityManager.h"

#include "ShootingEnemy.h"
#include "MovingEnemy.h"
#include "EnemySpawner.h"
#include "Player.h"

#include <execution>


EntityManager::EntityManager(std::shared_ptr<std::unordered_map<std::string, bool>> sMapKeysDownMap) :
	m_sMapKeysDown	{ sMapKeysDownMap },
	m_sArrEntities	{ std::make_shared<std::vector<std::unique_ptr<Entity>>>() },
	m_sArrPlayers	{ std::make_shared<std::vector<std::unique_ptr<Player>>>() },
	m_bLevelComplete{ false }
{
	std::cout<< "Created EntityManger" << "\n";
}


EntityManager::~EntityManager()
{
	std::cout<< "Destroyed EntittyManger" << "\n";
}



void EntityManager::Draw() const
{
	for (const std::unique_ptr<Entity>& uEntity : *m_sArrEntities)
		uEntity->Draw();


	for (const std::unique_ptr<Player>& uPlayer : *m_sArrPlayers)
		uPlayer->Draw();


}

void EntityManager::Update(float elapsedSec)
{

	// check if entities get hit player(s) and otherwise
	m_sArrEntities->erase(
		std::remove_if(m_sArrEntities->begin(), m_sArrEntities->end(),
			[](std::unique_ptr<Entity>& entity)
			{
				return entity->IsDead();
			}
		),
		m_sArrEntities->end()
	);
 
	m_sArrPlayers->erase(
		std::remove_if(m_sArrPlayers->begin(), m_sArrPlayers->end(),
			[](std::unique_ptr<Player>& player)
			{
				return player->IsDead();
			}
		),
		m_sArrPlayers->end()
	);

	if (m_sArrPlayers->empty())
		return;


	// update entities
	for (auto& uPlayer : *m_sArrPlayers)
		uPlayer->Update(elapsedSec);

	for (auto& uEntity : *m_sArrEntities)
		uEntity->Update(elapsedSec);



	// killed all enemies
	if (m_sArrEntities->empty())
	{
		m_bLevelComplete = true;
		return;
	}



	// Hitboxes checkers, bullets checkers
	for (auto& uPlayer : *m_sArrPlayers)
	{
		auto& arrPlayerBullets{ uPlayer->GetBullets() };
		auto playerHitbox{ uPlayer->GetHitBox() };

		std::for_each(std::execution::par, m_sArrEntities->begin(), m_sArrEntities->end(),
			[&](std::unique_ptr<Entity>& uEnemy)
			{

				if (utils::IsOverlapping(playerHitbox, uEnemy->GetHitBox()))
				{
					uPlayer->TakeDamage(100); // gets taken damage
					uPlayer->SetPosition(g_StartPosition);
					return;
				}

				// enemy gets hit by bullet from player
				for (auto& playerBullet : arrPlayerBullets)
				{
					if (utils::IsOverlapping(playerBullet->GetHitBox(), uEnemy->GetHitBox()))
					{
						uEnemy->TakeDamage(playerBullet->GetDamage());
						playerBullet->Destroy();
					}
				}


				if (auto* pShootingEnemy{ dynamic_cast<ShootingEnemy*>(uEnemy.get()) }; pShootingEnemy != nullptr)
				{
					auto& arrEnemyBullets{ pShootingEnemy->GetBullets() };

					pShootingEnemy->SetPlayerLocation(uPlayer->GetPosition());

					for (auto& enemyBullet : arrEnemyBullets)
						if (utils::IsOverlapping(enemyBullet->GetHitBox(), uPlayer->GetHitBox()))
						{
							uPlayer->TakeDamage(enemyBullet->GetDamage());
							enemyBullet->Destroy();
						}
				} 




			});

	}

}



void EntityManager::AddPlayer(const Point2f& position)
{
	m_sArrPlayers->push_back(std::make_unique<Player>(position, m_sMapKeysDown));
}

void EntityManager::AddEnemy(const Point2f& position)
{
	m_sArrEntities->push_back(std::make_unique<Enemy>(position));
}

void EntityManager::AddShootingEnemy(const Point2f& position)
{
	m_sArrEntities->push_back(std::make_unique<ShootingEnemy>(position));
}

void EntityManager::AddEnemySpawner(const Point2f& position)
{
	m_sArrEntities->push_back(std::make_unique<EnemySpawner>(position, 0.3f));
}



std::shared_ptr<std::vector<std::unique_ptr<Entity>>> EntityManager::GetSharedEntities() const
{
	return m_sArrEntities;
} 

const std::shared_ptr<std::vector<std::unique_ptr<Player>>>& EntityManager::GetSharedPlayers() const
{
	return m_sArrPlayers;
}




void EntityManager::Reset()
{
	m_sArrPlayers->clear();
	m_sArrEntities->clear();

	m_bLevelComplete = false;
}



bool EntityManager::IsLevelDone() const
{
	return m_bLevelComplete;
}








