
#include "Pillar.h"


Pillar::Pillar() :
	Pillar(ThreeBlade(0, 0, 0))
{
}
 
Pillar::Pillar(float x, float y, const Color4f& color) :
	Pillar(ThreeBlade(x, y, 0), color)
{
}
 
Pillar::Pillar(const ThreeBlade& position, const Color4f& color) :
	m_Position{ position },
	m_Color{ color }
{
}


void Pillar::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Position[0], m_Position[1], 10, 10);

}


void Pillar::Update(float elapsedSec)
{


}


const ThreeBlade& Pillar::GetPos() const
{
	return m_Position;
}
 
 void Pillar::SetPos(const ThreeBlade& position)
{
	 m_Position = position;
}





