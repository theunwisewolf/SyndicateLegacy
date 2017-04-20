#include "Engine.h"

namespace Syndicate {

Engine::Engine(IGame* game, Settings settings) : 
	window(settings.gameTitle, settings.width, settings.height, settings.color, settings.VSync),
	m_Frames(0),
	m_Updates(0),
	m_Settings(settings),
	m_LastTime(0),
	m_Game(game),
	m_DebugLayer()
{
#ifdef SYNDICATE_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// Initilize the Window
	Window::i()->Initialize();

	// Initialize Audio Manager
	AudioManager::i()->Initialize();

	// Initialize the Event Manager
	EventManager::i()->Initialize();
}

bool Engine::Initialize()
{
	// We store it, for the engine timer
	m_LastTime = m_EngineTimer.getElapsedTime();
	
	// If debug mode is on, we initialize the debug layer
	if (m_Settings.debugMode)
	{
		this->InitializeDebugLayer();
	}

	// Initialize the game!
	m_Game->Initialize();

	// All good...
	return true;
}

void Engine::InitializeDebugLayer()
{
	// Debug layer parameters
	m_DebugLayer.SetShader(synnew Shader());
	m_DebugLayer.SetRenderer(synnew BatchRenderer2D());
	m_DebugLayer.SetProjectionMatrix(Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f, -1.0f, 1.0f));

	// Set font's scaling relative to window
	Font::setScale(Window::i()->getWidth() / 16.0f, Window::i()->getHeight() / 9.0f);

	// Our fonts for debug layer
	FontManager::loadFont("RalewayLight", "res/Fonts/Raleway/Raleway-Light.ttf");

	Label* fps = synnew Label("0 fps", Vector2(0.5f, 0.35f), Font("RalewayLight", 60, Color(0xffffff)));
	Group* group = synnew Group(Matrix4::Translation(Vector3(-16.0f, 7.0f, 0.0f)));

	group->Add(synnew Sprite(Vector3(0, 0, 0), Vector2(5, 1.2f), Maths::Vector4(41, 128, 185,255)));

	group->Add("FPSGroup", fps);
	m_DebugLayer.Add("FPS", group);
}

bool Engine::Run()
{
	this->Update();

	return true;
}

void Engine::Update()
{
	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		// Update frames
		m_Frames++;

		// Win32 Messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Clear the window
		Window::i()->Clear();

		// Render the game
		m_Game->Render();
		m_DebugLayer.Render();

		// Update Events
		Window::i()->Update();

		// Update the fps counter
		this->UpdateFrameCounter();
	}
}

bool Engine::Shutdown()
{
	m_Game->Shutdown();
	return true;
}

void Engine::UpdateFrameCounter()
{
	if (m_EngineTimer.getElapsedTime() - m_LastTime >= 1.0f)
	{
		// Should we display the framerate?
		if (m_Settings.debugMode == true)
		{
			Window::i()->setTitle(Window::i()->getTitle() + " (" + std::to_string(m_Frames) + " fps)");
			((Label*)((Group*)m_DebugLayer.GetSprite("FPS"))->GetSprite("FPSGroup"))->setText(std::to_string(m_Frames) + " fps");
		}

		m_LastTime = m_EngineTimer.getElapsedTime();
		m_Frames = 0;
	}
}

Engine::~Engine()
{
	// Release the game
	delete m_Game;

	// Shutdown the event manager
	EventManager::i()->ShutDown();

	// Release all fonts
	FontManager::Clear();

	// Stop the audio thread
	AudioManager::i()->Stop();

	// Clear all textures
	ResourceManager::i()->Shutdown();

	// Free the debug layer
	m_DebugLayer.Free();

	// Shutdown the the window
	Window::i()->Close();
}

}