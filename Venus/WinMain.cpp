#include "WinMain.h"

#include <Common.h>

#include <Utilities/File.h>
#include <Utilities/VException.h>
#include <Systems/Graphics/Shader.h>
#include <Utilities/Maths/Maths.h>
#include <Utilities/Timer.h>

#include <Systems/Graphics/Renderers/SimpleRenderer2D.h>
#include <Systems/Graphics/Renderers/BatchRenderer2D.h>
#include <Systems/Graphics/Sprites/StaticSprite.h>
#include <Systems/Graphics/Sprites/Sprite.h>

#include <Systems/Graphics/Layers/Group.h>
#include <Systems/Graphics/Layers/Label.h>
#include <Systems/Graphics/Layers/TileLayer.h>

#include <Systems/Graphics/Texture.h>

#include <time.h>
#include <Systems/Graphics/FontManager.h>
#include <Systems/Graphics/Font.h>

#include <gorilla/ga.h>
#include <gorilla/gau.h>

#include <thread>
#include <Systems/Audio/AudioManager.h>

#include <Utilities/Logger.h>

using namespace Syndicate;
using namespace Maths;
using namespace Graphics;

#if 1
int main(int argc, char* argv[])
{
	Window window("Syndicate", 960, 540);

	std::vector<Audio*> queue;

	Syndicate::AudioManager audioManager;

	Syndicate::AudioManager::i()->Init();

	//queue.push_back(new Audio("res/Sounds/loopaaa.ogg"));
	//queue.push_back(new Audio("res/Sounds/23.ogg"));
	//queue.push_back(new Audio("res/Sounds/BloodAndWine/01.ogg"));
	//queue.push_back(new Audio("res/Sounds/35.ogg"));
	//queue.push_back(new Audio("res/Sounds/testsong.ogg"));

	//int queueIndex = AudioManager::LoadQueue(queue);

	//std::thread audioThread(&AudioManager::PlayQueue, queueIndex);

	AudioManager::i()->Load(new Audio("The Trail", "res/Sounds/01.ogg"));
	AudioManager::i()->Get("The Trail")->Play();

	AudioManager::i()->Load(new Audio("Priscilla's Song", "res/Sounds/song.ogg"));
	//AudioManager::i()->Get("Priscilla's Song")->Play();

	//window.setColor(0, 255, 0);

	Shader *shader = new Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");

	GLint textureSlots[] = { 0,1,2,3,4,5,6,7,8,9 };
	shader->enable();
	shader->setUniform2f("light_pos", Vector2(0.0, 0.0));
	shader->setUniformMat4("pr_matrix", Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f, 1.0f, -1.0f));
	//shader->setUniformMat4("pr_matrix", Matrix4::Orthographic(0, 960, 540, 0, 1.0f, -1.0f));
	shader->setUniform1iv("textures", textureSlots, 10);

	TileLayer layer(shader);
#if 1

#define ROWS 9
#define COLS 16
#define SIZE 1.0f

	//StaticSprite sprite(Vector3(0,0,0), Vector2(4,4), texturea, *shader);
	//SimpleRenderer2D renderer;

	//std::vector<Renderable2D*> sprites;
	int sprites = 0;
	srand(time(NULL));
	for (float i = -ROWS; i < ROWS; i += SIZE)
	{
		for (float j = -COLS; j < COLS; j += SIZE)
		{
			int num = 0 + (std::rand() % (2 - 0 + 1));

			if (num == 0)
			{
				//std::cout << "Texture a" << std::endl;
				layer.Add(new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), "res/Textures/a.png"));
			}
			else if (num == 1)
			{
				//std::cout << "Texture b" << std::endl;
				layer.Add(new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), "res/Textures/b.png"));
			}
			else
			{
				//std::cout << "Color" << std::endl;
				layer.Add(new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), Vector4(142, 68, 173, 255)));
			}

			sprites++;
		}
	}

	SYNDICATE_INFO("Rendered " + std::to_string(sprites) + " sprites." );

//#else
	Font::setScale(Window::i()->getWidth() / 16.0f, Window::i()->getHeight() / 9.0f);

	FontManager::loadFont("RalewayLight", "res/Fonts/Raleway/Raleway-Light.ttf");
	//FontManager::loadFont("Roboto-Bold", "res/Fonts/Roboto-Bold.ttf");

	Label* fps = new Label("0 fps", Vector2(0.5f, 0.35f), Font("RalewayLight", 60, Color(0xffffff)));
	Group *group = new Group(Matrix4::Translation(Vector3(-16.0f, 7.0f, 0.0f)));
	//group->Add(new Sprite(Vector3(0, 0, 0), Vector2(5, 1.2f), "Image.png"));

	group->Add(new Sprite(Vector3(0, 0, 0), Vector2(5, 1.2f), Maths::Vector4(192, 57, 43, 255)));

	group->Add(fps);
	layer.Add(group);

	Group *logo = new Group(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	logo->Add(new Sprite(Vector3(-9.0f, 0, 0), Vector2(20, 1.5f), Maths::Vector4(0, 0, 0, 255)));
	logo->Add(new Label("SYNDICATE, A Game Engine", Label::Position::CENTER, Font("RalewayLight", 100, Maths::Vector4(52, 152, 219, 255))));

	layer.Add(logo);

	//Label* label2 = new Label("Hii", Vector2(0.7f, 0.3f), Font("Roboto-Regular", 100, 1));
	//group->Add(new Sprite(Vector3(0.5f, 0.5f, 0), Vector2(2, 2), Vector4(150, 40, 27, 255)));

	/*Group *button2 = new Group(Maths::Matrix4::Translation(Vector3(0, 0, 0)));
	button2->Add(new Sprite(Vector3(0, 0, 0), Vector2(1, 1), Vector4(0, 0, 255, 255)));
	Group *button = new Group(Maths::Matrix4::Translation(Vector3( 0,0,0 )));

	button->Add( new Sprite( Vector3(0,0,0), Vector2(2,2), Vector4(255,255,255,255) ) );
	button->Add(button2);*/

	//group->Add(button);
	//layer.Add(label2);

	//layer.Add(new Label("Hi", Maths::Vector2(0.0f,0), Font("Roboto-Regular", 100, 1)) );
#endif

	Utilities::Timer timer;
	int frames = 0;
	double lastTime = timer.getElapsedTime();

	SYNDICATE_SUCCESS("Textures loaded: " + std::to_string(ResourceManager::i()->getTextureCount()));

	while (!window.Closed())
	{
		double x, y;
		window.getMousePosition(x, y);

		window.Clear();

		shader->enable();
		shader->setUniform2f("light_pos", Vector2(x * 32.0f / window.getWidth() - 16.0f, 9.0f - y * 18.0f / (window.getHeight())));

		layer.Render();

		window.Update();
		frames++;

		if (Window::i()->IsKeyTyped(GLFW_KEY_DOWN))
		{
			AudioManager::i()->VolumeDown(1);
			//AudioManager::GetQueue(queueIndex)[0]->VolumeDown(1);
			//AudioManager::Get("Priscilla's Song")->VolumeDown(1);
		}

		if (Window::i()->IsKeyTyped(GLFW_KEY_UP))
		{
			AudioManager::i()->VolumeUp(1);
			//AudioManager::GetQueue(queueIndex)[0]->VolumeUp(1);
			//AudioManager::Get("Priscilla's Song")->VolumeUp(1);
		}

		if (Window::i()->IsKeyTyped(GLFW_KEY_P))
		{
			AudioManager::i()->StopAll();
			AudioManager::i()->Load(new Audio("Blood And Wine", "res/Sounds/23.ogg"));
			AudioManager::i()->Get("Blood And Wine")->Play();
		}

		// Print the number of frames
		if (timer.getElapsedTime() - lastTime >= 1.0f)
		{
			//Window::i()->clearTypedKeys();
			window.setTitle(window.getTitle() + " (" + std::to_string(frames) + " fps)");
			fps->setText(std::to_string(frames) + " fps");
			frames = 0;
			lastTime = timer.getElapsedTime();
		}
	}

	window.Close();

	return 0;
}

#endif