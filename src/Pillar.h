#pragma once

#include "../FlyFish.h"
#include "../Utils.h"


class Pillar
{
public:
	Pillar();
	Pillar(float x, float y, const Color4f& color = Color4f(1, 0, 0, 1));
	Pillar(const ThreeBlade& position, const Color4f& color = Color4f(0, 1, 0, 1) );

	void Draw() const;
	void Update(float elapsedSec);

	const ThreeBlade& GetPos() const;
	void SetPos(const ThreeBlade& position);

private:
	ThreeBlade	m_Position;
	Color4f		m_Color;


};