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

#include <Systems/Graphics/Layers/TileLayer.h>

#include <Windows.h>

using namespace Venus;
using namespace Maths;
using namespace Graphics;

int main( int argc, char* argv[] )
{
	//MessageBox(NULL, "This is weird!", "Error", MB_OK);
	Window window("Venus", 960, 540);

	Matrix4 ortho = Matrix4::Orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Shader *shader = new Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	Shader *shader2 = new Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	
	//shader->enable();
	shader->setUniform2f("light_pos", Vector2(0.0, 0.0));

	TileLayer layer(shader);
	TileLayer layer2(shader2);
	//layer2.Add(new Sprite(Vector3(2, 2, 0), Vector2(4, 4), Vector4(150, 40, 27, 255)));
#define ROWS 9
#define COLS 16
#define SIZE 1.0f

	/*
	Vector4 color = rgba(142, 68, 173, 255);
	//std::vector<Renderable2D*> sprites;

	for (float i = -ROWS; i < ROWS; i += SIZE)
	{
		for (float j = -COLS; j < COLS; j += SIZE)
		{
			layer2.Add( new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), Vector4(142, 68, 173, 255)) );
		}
	}

	*/

	layer.Add( new Sprite( Vector3(-2, -2, 1), Vector2(4,4), Vector4(34, 49, 63, 255) ) );
	std::cout << "Rendered " << 1 << " sprites." << std::endl;
	
	Utilities::Timer timer;
	int frames = 0;
	double lastTime = timer.getElapsedTime();

	while (!window.Closed())
	{
		double x, y;
		window.getMousePosition(x, y);

		shader->enable();
		shader->setUniform2f("light_pos", Vector2(x * 32.0f / window.getWidth() - 16.0f, 9.0f - y * 18.0f / (window.getHeight())));
		shader2->enable();
		shader2->setUniform2f("light_pos", Vector2(x * 32.0f / window.getWidth() - 16.0f, 9.0f - y * 18.0f / (window.getHeight())));

		window.Clear();

		layer2.Render();
		layer.Render();

		window.Update();
		frames++;

		// Print the number of frames
		if (timer.getElapsedTime() - lastTime >= 1.0f)
		{	
			window.setTitle( window.getTitle() + " (" + std::to_string(frames) + " fps)" );
			frames = 0;
			lastTime = timer.getElapsedTime();
		}
	}

	//delete shader;

	window.Close();

	return 0;
}