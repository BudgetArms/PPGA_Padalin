#pragma once
#include <unordered_map>

#include "ShootingEntity.h"


class Player final : public ShootingEntity
{
public:

	Player();
	Player(const Point2f& position, std::shared_ptr<std::unordered_map<std::string, bool>> sKeyDownMap);

	Player(Player&)				= delete;	// Copy constructor
	Player(Player&&)			= delete;	// Move constructor
	Player operator&=(Player&)	= delete;	// Copy Assignment
	Player operator&=(Player&&)	= delete;	// Move Assignment

	virtual ~Player();


	virtual void Update(float elapsedSec) override;
	

private:

	std::shared_ptr<std::unordered_map<std::string, bool>> m_sMapbKeyDown;

	const float	m_Speed;


};





