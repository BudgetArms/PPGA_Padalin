
#pragma once

#include "../FlyFish.h"
#include "../Structs.h"


class PickUp abstract
{
public:
	PickUp();
	PickUp(const ThreeBlade& position, float size);


	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	const ThreeBlade& GetPos() const;
	void SetPos(const ThreeBlade& position);

	bool IsOverlapping(const ThreeBlade& position) const;
	bool IsDisabled() const;

protected:
	ThreeBlade m_Position;
	float m_Size;
	float m_LifeTime;
	float m_RespawnDelay;
	bool m_IsDisabled;
	Color4f m_Color;

};