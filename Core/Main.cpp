#include "Main.h"

#include <Utilities/File.h>
#include <Utilities/VException.h>
#include <Systems/Graphics/Graphics.h>
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

#include <freetype-gl.h>

using namespace Venus;
using namespace Maths;
using namespace Graphics;

#if 1
int main( int argc, char* argv[] )
{
	//MessageBox(NULL, "This is weird!", "Error", MB_OK);
	Window window("Venus", 960, 540);
	//window.setColor(0, 255, 0);

	Shader *shader = new Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	
	GLint textureSlots[] = { 0,1,2,3,4,5,6,7,8,9 };
	shader->enable();
	shader->setUniform2f("light_pos", Vector2(0.0, 0.0));
	shader->setUniformMat4("pr_matrix", Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f, 1.0f, -1.0f));
	//shader->setUniformMat4("pr_matrix", Matrix4::Orthographic(0, 960, 540, 0, 1.0f, -1.0f));
	shader->setUniform1iv("textures", textureSlots, 10);

	TileLayer layer(shader);
#if 0

#define ROWS 9
#define COLS 16
#define SIZE 1.0f

	//StaticSprite sprite(Vector3(0,0,0), Vector2(4,4), texturea, *shader);
	//SimpleRenderer2D renderer;

	//std::vector<Renderable2D*> sprites;
	srand(time(NULL));
	for (float i = -ROWS; i < ROWS; i += SIZE)
	{
		for (float j = -COLS; j < COLS; j += SIZE)
		{
			int num = 0 + (std::rand() % (2 - 0 + 1));

			if (num == 0)
			{
				//std::cout << "Texture a" << std::endl;
				layer.Add(new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), "b.png"));
			}
			else if (num == 1)
			{
				//std::cout << "Texture b" << std::endl;
				layer.Add(new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), "Image.png"));
			}
			else
			{
				//std::cout << "Color" << std::endl;
				layer.Add(new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), Vector4(142, 68, 173, 255)));
			}
		}
	}

#else

	Label* label = new Label("", Vector2(0.7f, 0.3f));
	Group *group = new Group(Matrix4::Translation(Vector3(-16.0f, 7.0f, 0.0f )));
	group->Add(new Sprite(Vector3(0, 0, 0), Vector2(5, 2), "Image.png"));
	//group->Add(new Sprite(Vector3(0.5f, 0.5f, 0), Vector2(2, 2), Vector4(150, 40, 27, 255)));
	group->Add(label);

	/*Group *button2 = new Group(Maths::Matrix4::Translation(Vector3(0, 0, 0)));
	button2->Add(new Sprite(Vector3(0, 0, 0), Vector2(1, 1), Vector4(0, 0, 255, 255)));
	Group *button = new Group(Maths::Matrix4::Translation(Vector3( 0,0,0 )));

	button->Add( new Sprite( Vector3(0,0,0), Vector2(2,2), Vector4(255,255,255,255) ) );
	button->Add(button2);*/

	//group->Add(button);
	layer.Add(group);
#endif

	Utilities::Timer timer;
	int frames = 0;
	double lastTime = timer.getElapsedTime();

	std::cout << "Textures loaded: " << ResourceManager::i()->getTextureCount();

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

		// Print the number of frames
		if (timer.getElapsedTime() - lastTime >= 1.0f)
		{	
			window.setTitle( window.getTitle() + " (" + std::to_string(frames) + " fps)" );
			label->setText(std::to_string(frames));
			frames = 0;
			lastTime = timer.getElapsedTime();
		}
	}

	window.Close();

	return 0;
}

#endif