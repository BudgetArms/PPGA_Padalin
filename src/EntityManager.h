#pragma once

#include <vector>
#include <unordered_map>

class Entity;
class Player;


class EntityManager final
{
public:

	EntityManager(std::shared_ptr<std::unordered_map<std::string, bool>> sMapKeysDownMap);
	//EntityManager(std::shared_ptr<std::unordered_map<std::string, bool>> sMapKeysDownMap);

	~EntityManager();


	void Draw() const;
	void Update(float elapsedSec);


	void AddPlayer(const Point2f& position);

	void AddEnemy(const Point2f& position);
	void AddShootingEnemy(const Point2f& position);
	void AddEnemySpawner(const Point2f& position);

	std::shared_ptr<std::vector<std::unique_ptr<Entity>>> GetSharedEntities() const;
	const std::shared_ptr<std::vector<std::unique_ptr<Player>>>& GetSharedPlayers() const;


	void Reset();


	bool IsLevelDone() const;


private:
	std::shared_ptr<std::unordered_map<std::string, bool>> m_sMapKeysDown;

	std::shared_ptr<std::vector<std::unique_ptr<Entity>>> m_sArrEntities;
	std::shared_ptr<std::vector<std::unique_ptr<Player>>> m_sArrPlayers;

	
	bool m_bLevelComplete;


};

