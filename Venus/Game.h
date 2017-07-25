#ifndef GAME_H_
#define GAME_H_

#include <random>

#include <Interfaces/IGame.h> 
#include <Systems/Engine.h>
#include <Systems/Audio/AudioManager.h>
#include <Systems/Graphics/Shader.h>
#include <Systems/Graphics/Camera2D.h>
#include <Systems/Graphics/Layers/Group.h>
#include <Systems/Graphics/Layers/Label.h>
#include <Systems/Graphics/Sprites/Sprite.h>
#include <Systems/Graphics/Box2DDebugDraw.h>
#include <Systems/Event/EventManager.h>

#include <Utilities/Maths/Maths.h>
#include <Utilities/Callback.h>

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

#include <Box2D/Box2D.h>

#include "TileLayer.h"
#include "Box.h"

using namespace Syndicate;
using namespace Graphics;
using namespace Utilities;
using namespace Maths;

enum class GameState {
	RUNNING, 
	PAUSED
};

class Game : public IGame
{
private:
	Box2DDebugDraw m_DebugDraw;
	std::unique_ptr<b2World> m_World;
	Camera2D m_Camera;
	Shader* m_Shader;
	TileLayer m_Layer;

	std::vector<Box> m_Boxes;

	GameState m_GameState;
public:
	Game();
	~Game();

	void LoadPackages();

	bool Initialize() override;
	bool Render(bool state) override;
	bool Update(double deltatime) override;
	bool Shutdown() override;

	// Custom functions!
	void Pause();
	void UnPause();
	bool IsPaused() const { return (this->m_GameState == GameState::PAUSED); };
};

#endif