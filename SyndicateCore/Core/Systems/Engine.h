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

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <Utilities/Packaging/Package.h>

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

static struct SYNDICATE_API Settings {
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
	static Engine* instance;
public:
	static Engine* i()
	{
		return instance;
	}

private:
	Window window;

	Settings m_Settings;

	unsigned int m_Updates;
	unsigned int m_Frames;
	Timer m_EngineTimer;

	double m_LastTime;
	double m_DeltaTime;

	IGame* m_Game;

	// For displaying FPS and what and what not
	Layer m_DebugLayer;

	// Internal Resources
	Package m_ResourcePackage;

	// Command line arguments
	std::vector<std::string> m_CommandLineArgs;

	// Root
	std::string m_SyndicateRoot;

	// Rendering state
	bool m_Rendering;

public:
	Engine(IGame* game, int argc, char* argv[], Settings settings = defaultSettings);
	~Engine();

	bool Initialize();
	bool Run();
	void Update();
	bool Shutdown();

	void UpdateFrameCounter();
	void InitializeDebugLayer();

	void ToggleRendering();
	void PauseRendering();
	void StartRendering();

	const std::string& RootDirectory() const { return this->m_SyndicateRoot; }
};

}

#endif