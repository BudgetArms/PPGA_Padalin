#pragma once

#include "PickUp.h"

class PickUpPower : public PickUp
{
public:

	PickUpPower();
	PickUpPower(const ThreeBlade& position);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	bool IsDash() const { return (m_PowerUpType == PowerUpType::Dash); }

private:

	enum class PowerUpType
	{
		Dash,
		Mirror
	};

	PowerUpType m_PowerUpType;
	

};


