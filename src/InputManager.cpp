#include "Globals.h"
#include "InputManager.h"
#include "AnimatedSprite.h"


InputManager::InputManager() :
	m_sMapKeyDown { std::make_shared<std::unordered_map<std::string, bool>>() }
{
	std::cout<< "Created InputManager" << "\n";

	m_sMapKeyDown->insert({ "D", false });
	m_sMapKeyDown->insert({ "S", false });
	m_sMapKeyDown->insert({ "W", false });
	m_sMapKeyDown->insert({ "A", false });
	m_sMapKeyDown->insert({ "K", false });

	m_sMapKeyDown->insert({ "R", false }); // restart

	m_sMapKeyDown->insert({ "0", false });
	m_sMapKeyDown->insert({ "1", false });
	m_sMapKeyDown->insert({ "2", false });
	m_sMapKeyDown->insert({ "3", false });
	m_sMapKeyDown->insert({ "4", false });
	m_sMapKeyDown->insert({ "5", false });
	m_sMapKeyDown->insert({ "6", false });
	m_sMapKeyDown->insert({ "7", false });
	m_sMapKeyDown->insert({ "8", false });
	m_sMapKeyDown->insert({ "9", false });

	m_sMapKeyDown->insert({ "LMouse", false });
	m_sMapKeyDown->insert({ "MMouse", false });
	m_sMapKeyDown->insert({ "RMouse", false });

}

InputManager::~InputManager()
{
	std::cout<< "Destroyed InputManager" << "\n";
}


std::shared_ptr<std::unordered_map<std::string, bool>> InputManager::GetSharedKeyDownMap()
{
	if (m_sMapKeyDown == nullptr)
		std::abort();

	return m_sMapKeyDown;

}

bool InputManager::IsGameRestart() const
{
	if (auto it{ m_sMapKeyDown->find("R") }; it != m_sMapKeyDown->end())
		if (it->second)
		{
			it->second = false;
			return true;
		}
	return false;
}

void InputManager::ManageKeyDown(const SDL_KeyboardEvent& event)
{ 
	//std::cout << "KEYd event: " << event.keysym.sym << std::endl;

	switch (event.keysym.sym)
	{
		case SDLK_UP:
		case SDLK_w:
		{
			if (auto it{ m_sMapKeyDown->find("W") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}


		} break;
		case SDLK_DOWN:
		case SDLK_s:
		{

			if (auto it{ m_sMapKeyDown->find("S") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}

		} break;
		case SDLK_LEFT:
		case SDLK_a:
		{

			if (auto it{ m_sMapKeyDown->find("A") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}

		} break;
		case SDLK_RIGHT:
		case SDLK_d:
		{

			if (auto it{ m_sMapKeyDown->find("D") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}

		} break;
		
		case SDLK_r:
		{

			if (auto it{ m_sMapKeyDown->find("R") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}

		} break;

		case SDLK_1:
		case SDLK_KP_1:
		{
			if (auto it{ m_sMapKeyDown->find("1") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}

		} break;
		case SDLK_k:
		{

			if (auto it{ m_sMapKeyDown->find("k") }; it != m_sMapKeyDown->end())
			{
				if (it->second)
					return;

				it->second = true;
			}

		} break;

	}
}
 
void InputManager::ManageKeyUp(const SDL_KeyboardEvent& event)
{ 
	//std::cout << "KEYUP event: " << event.keysym.sym << std::endl;
	switch (event.keysym.sym)
	{
	case SDLK_UP:
	case SDLK_w:
	{
		if (auto it{ m_sMapKeyDown->find("W") }; it != m_sMapKeyDown->end())
			it->second = false;

	} break;
	case SDLK_DOWN:
	case SDLK_s:
	{
		if (auto it{ m_sMapKeyDown->find("S") }; it != m_sMapKeyDown->end())
			it->second = false;

	} break;
	case SDLK_LEFT:
	case SDLK_a:
	{
		if (auto it{ m_sMapKeyDown->find("A") }; it != m_sMapKeyDown->end())
			it->second = false;

	} break;
	case SDLK_RIGHT:
	case SDLK_d:
	{
		if (auto it{ m_sMapKeyDown->find("D") }; it != m_sMapKeyDown->end())
			it->second = false;

	} break; 

	case SDLK_r:
	{
		if (auto it{ m_sMapKeyDown->find("R") }; it != m_sMapKeyDown->end())
			it->second = false;

	} break;

	case SDLK_1:
	case SDLK_KP_1:
	{
		if (auto it{ m_sMapKeyDown->find("1") }; it != m_sMapKeyDown->end())
			it->second = false;

	} break;
	case SDLK_k:
	{

		if (auto it{ m_sMapKeyDown->find("K") }; it != m_sMapKeyDown->end())
		{
			it->second = false;
		}

	} break;
	}
}

void InputManager::ManageMouseDown(const SDL_MouseButtonEvent& event)
{
	//std::cout << "MOUSE DOWN event: ";
	switch (event.button)
	{
		case SDL_BUTTON_LEFT:
		{
			if (auto it{ m_sMapKeyDown->find("LMouse") }; it != m_sMapKeyDown->end())
			{
				if (it->second == true)
					return;

				it->second = true;

			}
		} break;
		case SDL_BUTTON_RIGHT:
		{

			if (auto it{ m_sMapKeyDown->find("RMouse") }; it != m_sMapKeyDown->end())
			{
				if (it->second == true)
					return;

				it->second = true;

			}
		} break;
		case SDL_BUTTON_MIDDLE:
		{

			if (auto it{ m_sMapKeyDown->find("MMouse") }; it != m_sMapKeyDown->end())
			{
				if (it->second == true)
					return;

				it->second = true;

			}
		} break;

	}
	

}

void InputManager::ManageMouseUp(const SDL_MouseButtonEvent& event)
{
	//std::cout << "MOUSEBUTTONUP event: ";

	switch (event.button)
	{
		case SDL_BUTTON_LEFT:
		{

			if (auto it{ m_sMapKeyDown->find("LMouse") }; it != m_sMapKeyDown->end())
				it->second = false;


		} break;
		case SDL_BUTTON_RIGHT:
		{

			if (auto it{ m_sMapKeyDown->find("RMouse") }; it != m_sMapKeyDown->end())
				it->second = false;

		} break;
		case SDL_BUTTON_MIDDLE:
		{

			if (auto it{ m_sMapKeyDown->find("MMouse") }; it != m_sMapKeyDown->end())
				it->second = false;

		} break;

	}
	

}

void InputManager::ManageMouseMotion(const SDL_MouseMotionEvent& event)
{

}


