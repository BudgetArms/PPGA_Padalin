#include "PickUp.h"

#include "../Utils.h"
#include "../Globals.h"


PickUp::PickUp() :
	PickUp(m_Position, 10)
{
}

PickUp::PickUp(const ThreeBlade& position, float size) :
	m_Position{ position },
	m_Size{ size },
	m_LifeTime{ 4.f },
	m_RespawnDelay{ 5.f },
	m_IsDisabled{ false },
	m_Color{ Color4f(0.f, 1.f, 1.f, 1.f) }
{
}



void PickUp::Draw() const
{
	if (m_IsDisabled)
		return;

	utils::SetColor(m_Color);
	utils::FillEllipse(m_Position[0], m_Position[1], m_Size, m_Size);

}
 

void PickUp::Update(float elapsedSec)
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


const ThreeBlade& PickUp::GetPos() const
{
	return m_Position;
}
 
void PickUp::SetPos(const ThreeBlade& position)
{
	m_Position = position;
}


bool PickUp::IsOverlapping(const ThreeBlade& position) const
{
	return ( (position & m_Position).Norm() <= m_Size );
}

bool PickUp::IsDisabled() const
{
	return m_IsDisabled;
}


