#pragma once

#include "../FlyFish.h"
#include "../Utils.h"
#include "PickUp.h"


class Coin : public PickUp
{
public:
	Coin();
	Coin(const ThreeBlade& position);

	virtual void Draw() const override;


private: 	
	Color4f m_ColorBack;


};










