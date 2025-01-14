#pragma once

#include "../FlyFish.h"
#include "../FlyStructs.h"
#include "../Structs.h"

#include <SDL.h>

class Player
{
public:
	Player();
	//explicit Player();
	Player(const ThreeBlade& position, float radius, const Color4f& color);
	Player(const FlyCircle& circle, const Color4f& color);
	~Player();

	void Draw() const;
	void Update(float elapsedSec);

	void Print() const;

	const ThreeBlade& GetPos() const;
	void SetPillar(const ThreeBlade& position);
	void IncrementScore();
	bool IsDead() const;

	bool WonGame() const { return m_Score > 4; };

	void ActivateDash();
	void ActivateMirror();


	void HandleMouseInput(const SDL_MouseButtonEvent& event);

	enum class PlayerState
	{
		Idle,
		Grappling,
		Dashing,
		Reflection
	};


private:

	FlyCircle	m_Circle;
	ThreeBlade	m_Velocity;
	Color4f		m_Color;
	PlayerState m_State;
	const float m_Speed;
	const float m_DashSpeed;
	const float m_Friction;

	float m_GrappleElapseSec;
	float m_DashingElapseSec;
	float m_ReflectionElapseSec;
	const float m_GrappleTime;
	const float m_DashingTime;
	const float m_ReflectionTime;
	int m_Score;

	ThreeBlade m_PillarPosition;

	OneBlade m_WindowLeft;
	OneBlade m_WindowRight;
	OneBlade m_WindowBottom;
	OneBlade m_WindowTop;

	TwoBlade m_DebugLine;


	void MoveY(float y);
	void MoveX(float x);

	void HandleEvent(float elapsedSec);
	void HandleWallCollision();


};





