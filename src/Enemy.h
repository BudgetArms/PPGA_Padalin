#pragma once

#include "../Utils.h"
#include "../FlyUtils.h"

class Player;

class Enemy
{
public:
	Enemy();
	Enemy(const ThreeBlade& position, Player* target = nullptr);

	void Draw() const;
	void Update(float elapsedSec);


	const ThreeBlade& GetPos() const;
	void SetPos(const ThreeBlade& pos);
	void SetTarget(Player* target);



private:
	ThreeBlade	m_Position;
	Color4f		m_Color;
	Player*		m_Target;

	float		m_Speed;

	TwoBlade m_Line;

};