#pragma once
#include "Object.h"


class Entity : public Object
{
public:

	Entity(const Shape& shape, const Point2f& position, float maxHealth = 300.f, float healingPerSec = 20.f);
	Entity(const Shape& shape, float maxHealth = 300.f, float m_HealingPerSec = 20.f);

	Entity(const Entity&)		= default;
	Entity(Entity&&)			= delete;
	Entity operator=(Entity&)	= delete;
	Entity operator=(Entity&&)	= delete;

	virtual ~Entity() {};


	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	void Heal(float healingAmount);
	void TakeDamage(float damageTaken);


private:

	void DrawHealthbar() const;


	Color4f	m_HealthbarColor;
	float	m_MaxHealth;
	float	m_Health;

	float	m_HealingPerSec;

	bool	m_bHealthbar;
	bool	m_bCanHeal;

	float	m_AccumulatedSec;


protected:

	void ShowHealthbar(bool showHealthbar);
	void SetHealthbarColor(const Color4f& color);
	void SetHealthbarColor(float r, float g, float b, float a = 1.f);


};

