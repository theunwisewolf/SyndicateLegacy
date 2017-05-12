#include "Engine.h"

namespace Syndicate {

Engine::Engine(IGame* game, int argc, char *argv[], Settings settings) : 
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

	this->m_CommandLineArgs.reserve(argc);
	for (int i = 0; i < argc; ++i)
	{
		this->m_CommandLineArgs.push_back(std::string( argv[i] ));
	}

	SyndicateRoot = this->m_SyndicateRoot = FileSystem::i()->GetDirectoryName(this->m_CommandLineArgs[0]);

	// Initilize the Window
	Window::i()->Initialize();

	// Initialize Audio Manager
	SYNDICATE_INFO("Initializing Audio Manager...");
	if (AudioManager::i()->Initialize())
	{
		SYNDICATE_SUCCESS("Successfully Initialized Audio Manager.");
	}

	// Initialize the Event Manager
	SYNDICATE_INFO("Initializing Event Manager...");
	if (EventManager::i()->Initialize())
	{
		SYNDICATE_SUCCESS("Successfully Initialized Event Manager.");
	}

	// Initialize Resource Manager
	SYNDICATE_INFO("Initializing Resource Manager...");
	if (ResourceManager::i()->Initialize())
	{
		SYNDICATE_SUCCESS("Successfully Initialized Resource Manager.");
	}

	// Initialize the Input Manager
	SYNDICATE_INFO("Initializing Input Manager...");
	if (InputManager::i()->Initialize())
	{
		SYNDICATE_SUCCESS("Successfully Initialized Input Manager.");
	}
}

bool Engine::Initialize()
{
	// Load resources
	ResourceManager::i()->LoadPackage("packages/syndicate.spkg");

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
	m_DebugLayer.SetProjectionMatrix(Matrix4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	// Our fonts for debug layer
	FontManager::loadFontFromPackage("RalewayLight");
	Font font = Font("RalewayLight", 60, Color(0xffffff));

	// Set font's scaling relative to window
	font.setScale(Window::i()->getWidth() / 16.0f, Window::i()->getHeight() / 9.0f);

	Label* fps = synnew Label("0 fps", Vector2(0.5f, 0.35f), font);
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

		// Poll events
		InputManager::i()->Update();

		// Clear the window
		Window::i()->Clear();

		// Update the game
		m_Game->Update();

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
	// Shutdown the input manager
	InputManager::i()->ShutDown();

	// Stop the audio thread
	AudioManager::i()->Stop();

	// Release the game
	delete m_Game;

	// Shutdown the event manager
	EventManager::i()->ShutDown();

	// Release all fonts
	FontManager::Clear();

	// Clear all textures
	ResourceManager::i()->Shutdown();

	// Free the debug layer
	m_DebugLayer.Free();

	// Shutdown the the window
	Window::i()->Close();

	// Shutdown the Audio Manager
	AudioManager::i()->ShutDown();
}

}