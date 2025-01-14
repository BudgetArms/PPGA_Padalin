#include "PickUpPower.h"

#include "../Globals.h"



PickUpPower::PickUpPower()
	: PickUpPower(ThreeBlade(0, 0, 0))
{
}
 

PickUpPower::PickUpPower(const ThreeBlade& position)
	: PickUp(position, 10)
	, m_PowerUpType{ PowerUpType::Dash }
{
	m_PowerUpType = PowerUpType(rand() % 2);
}


void PickUpPower::Draw() const
{
	if (m_IsDisabled)
		return;

	if(m_PowerUpType== PowerUpType::Dash)
		utils::SetColor(0, 0, 0.5f, 1);
	else
		utils::SetColor(1, 1, 0, 1);


	//utils::SetColor(m_Color);
	utils::FillEllipse(m_Position[0], m_Position[1], m_Size, m_Size);

}


void PickUpPower::Update(float elapsedSec)
{
	m_LifeTime -= elapsedSec;

	if (m_LifeTime < 0.f)
	{
		m_IsDisabled = true;
		m_Position = ThreeBlade(-100.f, -100.f, 0.f);

		if (m_LifeTime < -m_RespawnDelay)
		{
			m_Position = ThreeBlade(float(rand() % int(g_Window.width)), float(rand() % int(g_Window.height)), 0.f);
			m_LifeTime = float(rand() % 5) + 3.f;
			m_RespawnDelay = float(rand() % 5) + 5.f;
			m_IsDisabled = false;
		}
	}

}

