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

#include "src/Player.h"


Game::Game(const Window& window)
	: m_Window{ window }
	, m_Viewport{ 0, 0, window.width, window.height }
	, m_pWindow{ nullptr }
	, m_pContext{ nullptr }
	, m_Initialized{ false }
	, m_MaxElapsedSeconds{ 0.1f }
	, m_uPlayer { nullptr }
	, m_PlayerMirror { }
	, m_Pillar { }
	, m_Enemy { }
	, m_Line{ TwoBlade() }
	, m_Coin{ ThreeBlade(100, 200, 0) }
	, m_PickUp{ ThreeBlade(-100, -100, 0)}
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
		SDL_WINDOW_OPENGL
	);

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
	//std::cout << "Window Width:  " << g_Window.width  << "\n";
	//std::cout << "Window Height: " << g_Window.height << "\n";
	std::cout << "KeyBinds:" << "\n";
	std::cout << "Forward: W or Z, Backwards: S, Left: A or Q, Right: D" << "\n";
	std::cout << "LMB: " << "Grapple, grapples in the direction your mouse is to the closes wall" << "\n";
	std::cout << "MMB: " << "Reflection, does a point reflection on the player witht he green pillar in the middle" << "\n";
	std::cout << "RMB: " << "Rotation, rotates you around the enemy, this is not a animation" << "\n";
	std::cout << "\n";
	std::cout << "Goal: " << "Pickup 5  Coin " << "\n";


	m_Pillar.SetPos(ThreeBlade(g_Window.width / 2, g_Window.height / 2, 0));

	m_uPlayer = std::make_unique<Player>(ThreeBlade(200, g_Window.height/2.f, 0), 
											10, Color4f(1.f, 1.f, 1.f, 1.f));
	m_uPlayer->SetPillar(m_Pillar.GetPos());
	m_Enemy.SetPos(ThreeBlade(g_Window.width - 500, g_Window.height - 400, 0));
	m_Enemy.SetTarget(m_uPlayer.get());

	m_PickUp.SetPos(ThreeBlade(float(rand() % int(g_Window.width)), float(rand() % int(g_Window.height)), 0));

	auto rejPlayerPillar{ (m_Pillar.GetPos() * m_uPlayer->GetPos() * ~m_Pillar.GetPos()).Grade3() };
	m_PlayerMirror = rejPlayerPillar;

}

void Game::Update(float elapsedSec)
{

	m_uPlayer->Update(elapsedSec);
	m_Enemy.Update(elapsedSec);
	m_Coin.Update(elapsedSec);
	m_PickUp.Update(elapsedSec);

	if (m_Coin.IsOverlapping(m_uPlayer->GetPos()))
	{
		m_uPlayer->IncrementScore();
		m_Coin = Coin(ThreeBlade(float(rand() % int(g_Window.width)),	
								float(rand() % int(g_Window.height)), 0)); 	
	} 

	if (m_PickUp.IsOverlapping(m_uPlayer->GetPos()))
	{
		if (m_PickUp.IsDash())
			m_uPlayer->ActivateDash();
		else
			m_uPlayer->ActivateMirror();

		m_PickUp = PickUpPower(ThreeBlade(float(rand() % int(g_Window.width)),	
								float(rand() % int(g_Window.height)), 0));
	}


	auto rejPlayerPillar{ (m_Pillar.GetPos() * m_uPlayer->GetPos() * ~m_Pillar.GetPos()).Grade3() };
	m_PlayerMirror = rejPlayerPillar;


	ThreeBlade origin{ 0, 0, 0, 1 };
	m_Line = origin & m_PlayerMirror;

	if ((m_uPlayer->GetPos() & m_Enemy.GetPos()).Norm() < 10)
	{
		std::cout << "Game Over" << "\n";
		exit(0);
	}

}

void Game::Draw() const
{
	// clear and set background color
	ClearBackground();
	glClearColor(1.f, 1.f, 1.f, 1.f);

	//utils::DrawEllipse(Ellipsef(Point2f(200, 0), 30, 30), 3);
	
	
	m_Pillar.Draw();
	m_Coin.Draw();
	m_PickUp.Draw();

	utils::SetColor(0, 0.f, 1.f, 1.f);
	utils::FillRect(m_PlayerMirror[0] - 10, m_PlayerMirror[1] - 10, 20, 20);

	

	m_uPlayer->Draw();
	m_Enemy.Draw();


}



// Event handling
#pragma region Events

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{

	if (e.keysym.sym == SDLK_ESCAPE)
		exit(0);

	if (e.keysym.sym == SDLK_e)
		m_uPlayer->ActivateMirror();
 

	if (e.keysym.sym == SDLK_r)
		m_uPlayer->ActivateDash();


}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{


}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{


}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	m_uPlayer->HandleMouseInput(e);
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	m_uPlayer->HandleMouseInput(e);
}

#pragma endregion Events
