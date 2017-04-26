#ifndef ENGINE_H_
#define ENGINE_H_

#include <Common.h>

#include <mutex>
#include <condition_variable>

#include <Windows.h>

#include <Interfaces/IGame.h>

#include <Systems/Window.h>

#include <Systems/Graphics/FontManager.h>
#include <Systems/Event/EventManager.h>
#include <Systems/Audio/AudioManager.h>
#include <Systems/ResourceManager.h>

#include <Utilities/Timer.h>
#include <Utilities/Maths/Maths.h>

#include <Systems/Graphics/Color.h>
#include <Systems/Graphics/Shader.h>
#include <Systems/Graphics/Layers/Layer.h>
#include <Systems/Graphics/Layers/Group.h>
#include <Systems/Graphics/Layers/Label.h>
#include <Systems/Graphics/Sprites/Sprite.h>
#include <Systems/Graphics/Renderers/BatchRenderer2D.h>

namespace Syndicate {

using namespace Graphics;
using namespace Utilities;
using namespace Maths;

struct SYNDICATE_API Settings {
	std::string gameTitle = "Syndicate";

	// Window Params
	long width = 960;
	long height = 540;

	Color color = Color(0x000000ff);
	bool VSync = false;

	bool debugMode = true;
} defaultSettings;

class SYNDICATE_API Engine 
{
private:
	Window window;

	Settings m_Settings;

	unsigned int m_Updates;
	unsigned int m_Frames;
	Timer m_EngineTimer;

	double m_LastTime;

	IGame* m_Game;

	// For displaying FPS and what and what not
	Layer m_DebugLayer;

public:
	Engine(IGame* game, Settings settings = defaultSettings);
	~Engine();

	bool Initialize();
	bool Run();
	void Update();
	bool Shutdown();

	void UpdateFrameCounter();
	void InitializeDebugLayer();
};

}

#endif