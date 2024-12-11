

#include "Player.h"

Player::Player() :
	ShootingEntity(Shape::Circle, position, 3, 300.f, 10.f),
{
	std::cout<< "Created Player" << "\n";

	SetSize(20);
	SetColor(1.f, 1.f, 1.f, 1.f);
	SetHealthbarColor(0.f, 1.f, 0.f, 0.8f);
}

Player::Player(const Point2f& position, std::shared_ptr<std::unordered_map<std::string, bool>> sKeyDownMap) :
	ShootingEntity(Shape::Circle, position, 3, 300.f, 10.f),
	m_sMapbKeyDown{ sKeyDownMap },
	m_Speed{ 100.f }
{
	std::cout << "Created Player" << "\n";

	SetSize(20);
	SetColor(1.f, 1.f, 1.f, 1.f);
	SetHealthbarColor(0.f, 1.f, 0.f, 0.8f);

}

Player::~Player()
{
	std::cout<< "Destroyed Player" << "\n";
}



void Player::Update(float elapsedSec)
{
	ShootingEntity::Update(elapsedSec);

	for (const auto& pair : *m_sMapbKeyDown)
	{
		if (pair.second == false)
			continue;

		
		
		if (pair.first == "LMouse")
		{
			int x{}, y{};
			SDL_GetMouseState(&x, &y);


			y = -y + int(g_Window.height);

			float directionAngle{ utils::g_toDegrees * atan2f(y - m_Position.y, x - m_Position.x) };

			Shoot(directionAngle);
			
		}



		if (pair.first == "W")
			m_Position.y += m_Speed * elapsedSec;

		if (pair.first == "S")
			m_Position.y -= m_Speed * elapsedSec;

		if (pair.first == "D")
			m_Position.x += m_Speed * elapsedSec;

		if (pair.first == "A")
			m_Position.x -= m_Speed * elapsedSec;

	}
	


}












