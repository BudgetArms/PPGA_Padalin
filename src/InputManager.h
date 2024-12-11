#pragma once

#include <SDL.h>
#include <vector>
#include "Sprite.h"

#include <memory>
#include <unordered_map>
#include "Object.h"


class InputManager final
{

public:

	InputManager();

	~InputManager();


	std::shared_ptr<std::unordered_map<std::string, bool>> GetSharedKeyDownMap();

	bool IsGameRestart() const;


	void ManageKeyDown(const SDL_KeyboardEvent& event);
	void ManageKeyUp(const SDL_KeyboardEvent& event); 

	void ManageMouseDown(const SDL_MouseButtonEvent& event);
	void ManageMouseUp(const SDL_MouseButtonEvent& event);

	void ManageMouseMotion(const SDL_MouseMotionEvent& event);

	
private:

	std::shared_ptr<std::unordered_map<std::string, bool>>	m_sMapKeyDown;


};

