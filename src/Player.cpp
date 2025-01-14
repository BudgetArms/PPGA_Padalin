
#include "Player.h"

#include <iostream>
#include "../Globals.h"
#include "../Utils.h"
#include "../FlyStructs.h"
#include "../FlyUtils.h"




Player::Player() :
	Player(FlyCircle(ThreeBlade(0, 0, 0), 10.f), Color4f(1.f, 1.f, 1.f, 1.f) )
{
}


Player::Player(const ThreeBlade& position, float radius, const Color4f& color = Color4f(1.f, 1.f, 1.f, 1.f)) :
	Player(FlyCircle(position, radius), color)
{
	
}

 
Player::Player(const FlyCircle& circle, const Color4f& color = Color4f(1.f, 1.f, 1.f, 1.f)) :
	m_Circle{ circle },
	m_Color{ color },
	m_State{ PlayerState::Idle },
	m_Speed{ 100 },
	m_DashSpeed{ 300 },
	m_Friction{ 0.6f },
	m_GrappleElapseSec{ 0.f },
	m_DashingElapseSec{ 0.f },
	m_ReflectionElapseSec{ 0.f },
	m_GrappleTime{ 3.f },
	m_DashingTime{ 0.5f },
	m_ReflectionTime{ 0.5f },
	m_PillarPosition{ ThreeBlade(300, 300, 0) },
	m_Score{ 0 }
{
	//std::cout << "Created Player" << "\n";

	m_WindowLeft	= OneBlade(-m_Circle.radius, 1, 0, 0);
	m_WindowRight	= OneBlade(m_Circle.radius - g_Window.width, 1, 0, 0);
	m_WindowBottom	= OneBlade(-m_Circle.radius, 0, 1, 0);
	m_WindowTop		= OneBlade(m_Circle.radius - g_Window.height, 0, 1, 0);
}


Player::~Player()
{
	//std::cout << "Destroyed Player" << "\n";
}



void Player::Draw() const 
{
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Circle.center[0], m_Circle.center[1], m_Circle.radius, m_Circle.radius);

	//utils::SetColor(1, 0, 0, 1);
	//utils::DrawLine(g_Window.width/2, g_Window.height/2, 
	//				g_Window.width/2 + 20 * m_DebugLine[3], g_Window.height/2 + 20 * m_DebugLine[4]);
}


void Player::Update(float elapsedSec)
{
	//if (m_State == PlayerState::Dead)
		//return;

	HandleEvent(elapsedSec);
	HandleWallCollision();

	switch (m_State)
	{
	case Player::PlayerState::Grappling:
	{
		m_GrappleElapseSec += elapsedSec;

		if (m_GrappleElapseSec >= m_GrappleTime)
		{
			m_State = PlayerState::Idle;
			m_GrappleElapseSec = 0.f;
		}

	} break;
	case Player::PlayerState::Dashing:
	{
		m_DashingElapseSec += elapsedSec;

		if (m_DashingElapseSec >= m_DashingTime)
		{
			m_State = PlayerState::Idle;
			m_DashingElapseSec = 0.f;

			

		}

	} break;
	}

	m_Velocity[0] *= (1 - m_Friction * elapsedSec);
	m_Velocity[1] *= (1 - m_Friction * elapsedSec);


	if (m_State == PlayerState::Dashing || m_State == PlayerState::Grappling)
	{
		m_Circle.center[0] += m_Velocity[0] * m_DashSpeed * elapsedSec;
		m_Circle.center[1] += m_Velocity[1] * m_DashSpeed * elapsedSec;

	}
	else
	{
		m_Circle.center[0] += m_Velocity[0] * m_Speed * elapsedSec;
		m_Circle.center[1] += m_Velocity[1] * m_Speed * elapsedSec;
	}

}

void Player::Print() const
{
	//std::cout << "Player Printing Hello World" << "\n";
	std::cout << "PosX: " << m_Circle.center[0] << "\tPosY:" << m_Circle.center[1] << "\n";
}


const ThreeBlade& Player::GetPos() const
{
	return m_Circle.center;
}
 

void Player::SetPillar(const ThreeBlade& position)
{
	m_PillarPosition = position;
}

 
void Player::IncrementScore()
{
	++m_Score;
	std::cout << "Score Now: " << m_Score << "\n";
}

bool Player::IsDead() const
{
	return false;
	//return (m_State == PlayerState::Dead);
}


void Player::ActivateDash()
{
	m_State = PlayerState::Dashing;
	m_DashingElapseSec = 0.f;

}
 

void Player::ActivateMirror()
{
	OneBlade horizontalPlane{ -g_Window.height / 2, 0, 1, 0 };
	auto rejPlayerPlane{ (horizontalPlane * m_Circle.center * ~horizontalPlane).Grade3() };
	m_Circle.center = rejPlayerPlane;

}




void Player::HandleMouseInput(const SDL_MouseButtonEvent& e)
{
	if (m_State != PlayerState::Idle)
		return;

	// Grapple
	if (e.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
	{
		m_State = PlayerState::Grappling;
		std::cout << "Grapple" << "\n";
		int x, y;
		SDL_GetMouseState(&x, &y);
		//std::cout << "x: " << x << " , y: " << g_Window.height - y << std::endl;

		//ThreeBlade mousePos{ float(x), g_Window.height - float(y), 0 };

		m_DebugLine = TwoBlade::LineFromPoints(m_Circle.center[0], m_Circle.center[1], 0, x, g_Window.height - y, 0);

		m_DebugLine = m_DebugLine.Normalize();

		m_Velocity[0] = m_DebugLine[3];
		m_Velocity[1] = m_DebugLine[4];



	}

	//  Reflection
	if (e.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "Reflection" << "\n";

		auto rejPlayerPillar{ (m_PillarPosition * m_Circle.center * ~m_PillarPosition).Grade3() };
		m_Circle.center = rejPlayerPillar;


		m_State = PlayerState::Idle;
	}

	// Rotation
	if (e.button == SDL_BUTTON_MIDDLE && e.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "Rotation" << "\n";
		m_State = PlayerState::Idle;

	}


}



void Player::MoveX(float x)
{
	m_Circle.center[0] += x;
}


void Player::MoveY(float y)
{
	m_Circle.center[1] += y;
}



void Player::HandleEvent(float elapsedSec)
{

	const Uint8* keyboardState{ SDL_GetKeyboardState(NULL) };

	if (keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_Z])
		m_Velocity[1] = 1;
		//MoveY(m_Speed * elapsedSec);
 
	if (keyboardState[SDL_SCANCODE_S])
		m_Velocity[1] = -1;
		//MoveY(-m_Speed * elapsedSec);
 
	if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_Q])
		m_Velocity[0] = -1;
		//MoveX(-m_Speed * elapsedSec);
 
	if (keyboardState[SDL_SCANCODE_D])
		m_Velocity[0] = 1;
		//MoveX(m_Speed * elapsedSec);


}


void Player::HandleWallCollision()
{
	// circle hits left window
	if ((m_Circle.center & m_WindowLeft)  < 0.f)
	{
		//std::cout << "Past L Wall" << "\n";
		ThreeBlade projPlayer = ((m_WindowLeft | m_Circle.center) * ~m_WindowLeft).Grade3();
		m_Circle.center = projPlayer;
	
		if (m_State == PlayerState::Grappling)
		{
			m_Velocity[0] *= -1;
			m_GrappleElapseSec = m_GrappleTime - 0.5f;
		}


	}
 
	// circle hits right window
	if ((m_Circle.center & m_WindowRight)  > 0.f)
	{
		//std::cout << "Past R wall" << "\n";
		ThreeBlade projPlayer = ((m_WindowRight | m_Circle.center) * ~m_WindowRight).Grade3();
		m_Circle.center = projPlayer;

		if (m_State == PlayerState::Grappling)
		{
			m_Velocity[0] *= -1;
			m_GrappleElapseSec = m_GrappleTime - 0.5f;
		}
	}
 
 
	// circle hits bottom window
	if ((m_Circle.center & m_WindowBottom)  < 0.f)
	{
		//std::cout << "Past B wall" << "\n";
		ThreeBlade projPlayer = ((m_WindowBottom | m_Circle.center) * ~m_WindowBottom).Grade3();
		m_Circle.center = projPlayer;

		if (m_State == PlayerState::Grappling)
		{
			m_Velocity[1] *= -1;
			m_GrappleElapseSec = m_GrappleTime - 0.5f;
		}

	}
 
	// circle hits top window
	if ((m_Circle.center & m_WindowTop) > 0.f)
	{
		//std::cout << "Past T wall" << "\n";
		ThreeBlade projPlayer = ((m_WindowTop | m_Circle.center) * ~m_WindowTop).Grade3();
		m_Circle.center = projPlayer;

		if (m_State == PlayerState::Grappling)
		{
			m_Velocity[1] *= -1;
			m_GrappleElapseSec = m_GrappleTime - 0.5f;
		}

	}



}




