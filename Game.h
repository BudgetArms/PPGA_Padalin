#pragma once

#include <memory>
#include "Globals.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include "src/Player.h"
#include "src/Pillar.h"
#include "src/Enemy.h"
#include "src/Coin.h"
#include "src/PickUp.h"
#include "src/PickUpPower.h"



class Game
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	~Game();

	void Run();

	void Update(float elapsedSec);

	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

	const Rectf& GetViewPort() const
	{
		return m_Viewport;
	}

private:
	// DATA MEMBERS
	// The window properties
	const Window m_Window;
	const Rectf m_Viewport;
	// The window we render to
	SDL_Window* m_pWindow;
	// OpenGL context
	SDL_GLContext m_pContext;
	// Init info
	bool m_Initialized;
	// Prevent timing jumps when debugging
	const float m_MaxElapsedSeconds;

	// FUNCTIONS
	void InitializeGameEngine();
	void InitializeGame();
	void CleanupGameEngine();

	void ClearBackground() const;


	// member variables

	std::unique_ptr<Player> m_uPlayer;
	ThreeBlade	m_PlayerMirror;
	Pillar		m_Pillar;
	Enemy		m_Enemy;
	TwoBlade	m_Line;
	Coin		m_Coin;
	PickUpPower	m_PickUp;

	float m_CoinSpawnDelay;

};



