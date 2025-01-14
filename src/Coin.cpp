#include "Coin.h"

#include <iostream>
#include "../Utils.h"
#include "../Globals.h"



Coin::Coin() :
	Coin(ThreeBlade(0, 0, 0))
{
}

Coin::Coin(const ThreeBlade& position) :
	PickUp(position, 10)
{
	m_LifeTime = 3.f;

	m_Color		= Color4f(0.9f, 0.8f, 0.2f, 1.f);
	m_ColorBack = Color4f(0.6f, 0.5f, 0.5f, 1.f);

}



void Coin::Draw() const
{
	if (m_IsDisabled)
		return;

	utils::SetColor(m_ColorBack);
	utils::FillEllipse(m_Position[0], m_Position[1], m_Size, m_Size);
 
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Position[0], m_Position[1], m_Size - 3, m_Size - 3);

} 








