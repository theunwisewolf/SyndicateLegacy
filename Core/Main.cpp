#include "Main.h"
#include <Utilities/File.h>
#include <Utilities/VException.h>
#include <Systems/Graphics/Graphics.h>
#include <Systems/Graphics/Shader.h>
#include <Utilities/Maths/Maths.h>
#include <Utilities/Timer.h>

#include <Systems/Graphics/SimpleRenderer2D.h>
#include <Systems/Graphics/BatchRenderer2D.h>
#include <Systems/Graphics/StaticSprite.h>
#include <Systems/Graphics/Sprite.h>

#define BATCH_RENDERER 1

using namespace Venus;
using namespace Maths;
using namespace Graphics;

int main( char* argv[], int argc )
{
	Window window("Venus", 960, 540);

	//window.setColor(44, 62, 80);

	Matrix4 ortho = Matrix4::Orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Shader shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	shader.enable();
	shader.setUniformMat4( "pr_matrix", ortho );
	shader.setUniform2f("light_pos", Vector2(0.0, 0.0));

#define ROWS 9
#define COLS 16
#define SIZE 0.05f

	float _i = 0.0f;
	float _j = 0.0f;

	Vector4 color = rgba(142, 68, 173, 255);
	std::vector<Renderable2D*> sprites;
#if BATCH_RENDERER
	BatchRenderer2D renderer;
	for (double i = 0; i < ROWS; i += SIZE, _i += SIZE)
	{
		for (double j = 0; j < COLS; j += SIZE, _j += SIZE)
		{

			sprites.push_back( new Sprite(Vector3(j + j * 0.1f, i + i * 0.1f, 0.0f), Vector2(SIZE, SIZE), Vector4(142, 68, 173, 255)) );
		}

		_j = 0.0f;
	}
#else
	SimpleRenderer2D renderer;
	for (double i = 0; i < ROWS; i += SIZE, _i += SIZE)
	{
		for (double j = 0; j < COLS; j += SIZE, _j += SIZE)
		{
			
			if( j / 2 )
				color = rgba(155, 89, 182, 255);
			else
				color = rgba(142, 68, 173, 255);
			sprites.push_back( new StaticSprite(Vector3(_j + _j * 0.1f, _i + _i * 0.1f, 0.0f), Vector2(SIZE, SIZE), color, shader) );
		}

		_j = 0.0f;
	}
#endif

	std::cout << "Rendered " << sprites.size() << " sprites." << std::endl;
	//Renderable2D sprite = Renderable2D(Vector3(6.0f, 3.0f, 0.0f), Vector2(4, 4), rgba(142, 68, 173, 255), shader);

	Utilities::Timer timer;
	int frames = 0;
	double lastTime = timer.getElapsedTime();

	while (!window.Closed())
	{
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Vector2(x * 16.0f / window.getWidth(), 9.0f - y * 9.0f / (window.getHeight())));

		window.Clear();

#if BATCH_RENDERER 
		renderer.start();
#endif
		for (auto sprite : sprites)
		{
			renderer.submit(sprite);
		}
#if BATCH_RENDERER 
		renderer.end();
#endif
		renderer.flush();

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

	for (auto sprite : sprites)
	{
		delete sprite;
	}

	window.Close();

	return 0;
}