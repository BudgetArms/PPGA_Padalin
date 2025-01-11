#pragma once
#include "Entity.h"

class Enemy;
class MovingEnemy;


class EnemySpawner final : public Entity
{
public:

	EnemySpawner(const Point2f& position, float spawnRatePerSecond = 1);
	
	~EnemySpawner();


	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	


	std::shared_ptr<std::vector<std::unique_ptr<MovingEnemy>>> GetSharedEnemies() const;
	//std::shared_ptr<std::vector<std::unique_ptr<Enemy>>> GetSharedEnemies() const;


private:
	std::shared_ptr<std::vector<std::unique_ptr<MovingEnemy>>> m_sArrEnemies;
	//std::shared_ptr<std::vector<std::unique_ptr<Enemy>>> m_sArrEnemies;
	

	const float m_SpawnRatePerSecond;
	float m_SpawnAccumlatedSec;







};

