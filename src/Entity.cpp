#include "../Globals.h"
#include "Entity.h"


Entity::Entity(const Shape& shape, const Point2f& position, float maxHealth, float healingPerSecond) :
	Object(shape, position),
	m_HealthbarColor{ Color4f(1.f, 0.f, 0.f, 1.f) },
	m_MaxHealth		{ maxHealth			},
	m_Health		{ m_MaxHealth		},
	m_HealingPerSec	{ healingPerSecond	},
	m_bHealthbar	{ true	}, 
	m_bCanHeal		{ true	},
	m_AccumulatedSec{ 0.f	}
{
	if (m_Health <= 0)
		m_bDead = true;

	SetSize(15);
} 


Entity::Entity(const Shape& shape, float maxHealth, float healingPerSecond) :
	Entity(shape, Point2f(0.f, 0.f), maxHealth, healingPerSecond)
{
}




void Entity::Draw() const
{
	Object::Draw();

	if (m_bHealthbar)
		DrawHealthbar();

}

void Entity::Update(float elapsedSec)
{
	Heal(m_HealingPerSec * elapsedSec);
	utils::SetColor(Color4f(1, 0, 0, 1));
}




void Entity::Heal(float healingAmount)
{
	if (m_bDead || m_Health == m_MaxHealth || !m_bCanHeal )
		return;

	m_Health += healingAmount;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;

}

void Entity::TakeDamage(float damageTaken)
{
	m_Health -= damageTaken;

	if (m_Health <= 0)
		m_bDead = true;
}




void Entity::DrawHealthbar() const
{
	const float percentageHealth{ m_Health / m_MaxHealth };
	
	const float size{ GetSize() };


	Rectf healthbar{	
						m_Position.x - size, m_Position.y + size * 1.5f, 
						2 * size, 5 
					};

	// White outline
	utils::SetColor(1.f, 1.f, 1.f, 1.f);
	utils::DrawRect(healthbar, 2);

	utils::SetColor(m_HealthbarColor);
	utils::FillRect(healthbar.left, healthbar.bottom, percentageHealth * healthbar.width, healthbar.height);
	
}




void Entity::ShowHealthbar(bool showHealthbar)
{
	m_bHealthbar = showHealthbar;
}


void Entity::SetHealthbarColor(const Color4f& color)
{
	m_HealthbarColor = color;
}
 

void Entity::SetHealthbarColor(float r, float g, float b, float a)
{
	SetHealthbarColor(Color4f(r, g, b, a));
}





