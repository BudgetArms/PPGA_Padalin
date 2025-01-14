#include "Enemy.h"

#include <iostream>
#include "Player.h"


Enemy::Enemy() :
	Enemy(ThreeBlade(0, 0, 0))
{
}

 

Enemy::Enemy(const ThreeBlade& position, Player* target) :
	m_Position{ position },
	m_Color{ Color4f(1,0,0,1) },
	m_Target{ target },
	m_Speed{ 150 }
{
	//std::cout << "Created Enemy" << "\n";
}

void Enemy::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillRect(m_Position[0] - 10, m_Position[1] - 10, 20, 20);

	utils::SetColor(1, 0, 1, 1);
	utils::DrawLine(m_Line[0], m_Line[1], m_Line[3], m_Line[4], 5);

}

void Enemy::Update(float elapsedSec)
{
	if (m_Target == nullptr)
		return;

	ThreeBlade pos = m_Target->GetPos();

	float test = m_Position | pos;
	//float test = m_Position | m_Target->GetPos();

	TwoBlade target  = TwoBlade::LineFromPoints(m_Position[0], m_Position[1], 0, pos[0], pos[1], 0);
	target[2] = 0;
	//target[5] = 0;
	target = target.Normalize();


	m_Position[0] += m_Speed * target[3] * elapsedSec;
	m_Position[1] += m_Speed * target[4] * elapsedSec;


}


const ThreeBlade& Enemy::GetPos() const
{
	return m_Position;
}

void Enemy::SetPos(const ThreeBlade& position)
{
	m_Position = position;
}

void Enemy::SetTarget(Player* target)
{
	m_Target = target;
}






