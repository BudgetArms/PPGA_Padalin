#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <chrono>

#include "Game.h"

#include "FlyFish.h"
#include "Globals.h"
#include "utils.h"

#include "src/Object.h"
//#include "src/Sprite.h"
//#include "src/MovingEnemy.h"
//#include "src/Player.h"
//#include "src/ShootingEnemy.h"

//#include "src/InputManager.h"
//#include "src/EntityManager.h"



Game::Game(const Window& window)
	: m_Window{ window }
	, m_Viewport{ 0, 0, window.width, window.height }
	, m_pWindow{ nullptr }
	, m_pContext{ nullptr }
	, m_Initialized{ false }
	, m_MaxElapsedSeconds{ 0.1f }
	//, m_Player { std::make_unique<Player> () }
	//, m_Player{ Player()}
{
	g_Window = m_Viewport;
	g_StartPosition = Point2f(100, 200);


	InitializeGameEngine();
	InitializeGame();
}

Game::~Game()
{
	CleanupGameEngine();
}

void Game::InitializeGameEngine()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_Init: " << SDL_GetError() << std::endl;
		return;
	}

	// Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Create window
	m_pWindow = SDL_CreateWindow(
		m_Window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(m_Window.width),
		int(m_Window.height),
		SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_CreateWindow: " << SDL_GetError() << std::endl;
		return;
	}

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return;
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_Window.isVSyncOn)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cerr << "BaseGame::Initialize( ), error when calling SDL_GL_SetSwapInterval: " << SDL_GetError() << std::endl;
			return;
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	glOrtho(0, m_Window.width, 0, m_Window.height, -1, 1); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(m_Window.width), int(m_Window.height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cerr << "BaseGame::Initialize( ), error when calling TTF_Init: " << TTF_GetError() << std::endl;
		return;
	}

	m_Initialized = true;
}

void Game::Run()
{
	if (!m_Initialized)
	{
		std::cerr << "BaseGame::Run( ), BaseGame not correctly initialized, unable to run the BaseGame\n";
		std::cin.get();
		return;
	}

	// Main loop flag
	bool quit{ false };

	// Set start time
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

	//The event loop
	SDL_Event e{};
	while (!quit)
	{
		// Poll next event from queue
		while (SDL_PollEvent(&e) != 0)
		{
			// Handle the polled event
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				this->ProcessKeyDownEvent(e.key);
				break;
			case SDL_KEYUP:
				this->ProcessKeyUpEvent(e.key);
				break;
			case SDL_MOUSEMOTION:
				e.motion.y = int(m_Window.height) - e.motion.y;
				this->ProcessMouseMotionEvent(e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				e.button.y = int(m_Window.height) - e.button.y;
				this->ProcessMouseDownEvent(e.button);
				break;
			case SDL_MOUSEBUTTONUP:
				e.button.y = int(m_Window.height) - e.button.y;
				this->ProcessMouseUpEvent(e.button);
				break;
			}
		}

		if (!quit)
		{
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

			// Calculate elapsed time
			float elapsedSeconds = std::chrono::duration<float>(t2 - t1).count();

			// Update current time
			t1 = t2;

			// Prevent jumps in time caused by break points
			elapsedSeconds = std::min(elapsedSeconds, m_MaxElapsedSeconds);

			// Call the BaseGame object 's Update function, using time in seconds (!)
			this->Update(elapsedSeconds);

			// Draw in the back buffer
			this->Draw();

			// Update screen: swap back and front buffer
			SDL_GL_SwapWindow(m_pWindow);
		}
	}
}

void Game::CleanupGameEngine()
{
	SDL_GL_DeleteContext(m_pContext);

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();

}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::InitializeGame()
{
	std::cout << g_Window.width << std::endl;

	//m_uInputManager = std::make_unique<InputManager>();
	//m_sEntityManager = (m_uInputManager ? std::make_shared<EntityManager>(m_uInputManager->GetSharedKeyDownMap()) : nullptr);

	//m_Player = std::make_unique<Player>(Point2f(200, 100), m_uInputManager->GetSharedKeyDownMap());


}

void Game::Update(float elapsedSec)
{
	//GAElement<, 20> object;
	TwoBlade line { 1.f, 1.f, 1.f, 1.f, 1.f, 1.f };
	ThreeBlade point{ 1, 2, 3, 1 };

	Rectf rect{ 10, 10, 100, 100 };

	
	
	
}

void Game::Draw() const
{
	// clear and set background color
	ClearBackground();
	glClearColor(1.f, 1.f, 1.f, 1.f);

	// draw ellipse at (0,0), radius 30, outline 3
	utils::DrawEllipse(Ellipsef(Point2f(0, 0), 30, 30), 3);

	//Object testObject{ Shape::Circle, Point2f(100, 100) };
	//testObject.Draw();

	fireObject.Draw();

}



// Event handling
#pragma region Events

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{

	if (e.keysym.sym == SDLK_e)
		exit(0);


	//if(e.keysym.sym == SDLK_W)


}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{


}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{


}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{


}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{


}

#pragma endregion Events
