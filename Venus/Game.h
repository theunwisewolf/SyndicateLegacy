#ifndef GAME_H_
#define GAME_H_

#include <Interfaces/IGame.h> 
#include <Systems/Audio/AudioManager.h>
#include <Systems/Graphics/Shader.h>
#include <Systems/Graphics/Camera2D.h>
#include <Systems/Graphics/Layers/Group.h>
#include <Systems/Graphics/Layers/Label.h>
#include <Systems/Graphics/Sprites/Sprite.h>
#include <Systems/Event/EventManager.h>

#include <Utilities/Maths/Maths.h>
#include <Utilities/Callback.h>

#include "TileLayer.h"

using namespace Syndicate;
using namespace Graphics;
using namespace Utilities;
using namespace Maths;

class Game : public IGame
{
private:
	Camera2D m_Camera;
	Shader* m_Shader;
	TileLayer m_Layer;

public:
	Game();
	~Game();

	void LoadPackages();

	bool Initialize() override;
	bool Render() override;
	bool Update() override;
	bool Shutdown() override;

};

#endif