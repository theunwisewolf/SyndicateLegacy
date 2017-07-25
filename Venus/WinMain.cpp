#include "WinMain.h"

#include "Game.h"
#include "TileLayer.h"

//#include <Systems/Engine.h>

#include <Utilities\Packaging\ZLib.h>
#include <Utilities\Packaging\Package.h>
#include <Utilities\FileSystem\FileSystem.h>

#define NOPACK

using namespace Syndicate;

int main(int argc, char* argv[])
{
#ifdef PACK
	SYNDICATE_INFO( "Creating Package..." );
	std::map<std::string, std::string> packageData;
	packageData.emplace("The Trail", "res/Sounds/01.ogg");
	packageData.emplace("Thor Ragnarok", "res/Sounds/ThorR.ogg");
	packageData.emplace("The Beast of Beauclair", "res/Sounds/21.ogg");

	Package package("AmN");

	for (auto pair : packageData)
	{
		File file = Utilities::File(pair.second, true);
		std::string data = file.Read().getData();
		SoundData sound(data, data.length(), "ogg");

		package.AddSound(pair.first, sound);
	}

	packageData.clear();

	packageData.emplace("texture_a.png", "res/Textures/a.png");
	packageData.emplace("texture_b.png", "res/Textures/texture_b.png");
	
	for (int i = 0; i < 15; i++)
	{
		packageData.emplace("res_" + std::to_string(i+1), "res/Textures/active" + std::to_string(i+1) + ".png");
	}

	for (auto pair : packageData)
	{
		unsigned int width, height;

		std::vector<char> buffer = Utilities::File(pair.second, true).Read().getRawData();

		BYTE* pixels = Utilities::loadImageFromMemory((unsigned char*)&buffer[0], buffer.size(), &width, &height);
		std::string data(buffer.begin(), buffer.end());

		ImageData image(data, buffer.size(), width, height);

		package.AddImage(pair.first, image);

		delete pixels;
	}

	packageData.clear();

	packageData.emplace("FragmentShader.frag", "Shaders/FragmentShader.frag");
	packageData.emplace("VertexShader.vert", "Shaders/VertexShader.vert");

	for (auto pair : packageData)
	{
		std::vector<char> buffer = Utilities::File(pair.second, true).Read().getRawData();
		std::string data(buffer.begin(), buffer.end());

		ShaderData shader(data, buffer.size());
		shader.setFormat( pair.first.substr( pair.first.find_last_of(".") + 1 ) );

		package.AddShader(pair.first, shader);
	}

	packageData.clear();

	package.Pack("packages/amn");
	SYNDICATE_INFO("Package created: packages/amn.spkg");

	Package enginePackage("SYN");

	packageData.emplace("FragmentShader.frag", "Shaders/FragmentShader.frag");
	packageData.emplace("VertexShader.vert", "Shaders/VertexShader.vert");

	for (auto pair : packageData)
	{
		std::vector<char> buffer = Utilities::File(pair.second, true).Read().getRawData();
		std::string data(buffer.begin(), buffer.end());

		ShaderData shader(data, buffer.size());
		shader.setFormat(pair.first.substr(pair.first.find_last_of(".") + 1));

		enginePackage.AddShader(pair.first, shader);
	}

	packageData.clear();

	packageData.emplace("RalewayLight", "res/Fonts/Raleway/Raleway-Light.ttf");

	for (auto pair : packageData)
	{
		std::vector<char> buffer = Utilities::File(pair.second, true).Read().getRawData();
		std::string data(buffer.begin(), buffer.end());

		FontData font(data, buffer.size());
		font.setFormat(pair.first.substr(pair.first.find_last_of(".") + 1));

		enginePackage.AddFont(pair.first, font);
	}

	packageData.clear();

	enginePackage.Pack("packages/syndicate");
#endif

	Engine engine(synnew Game(), argc, argv);

	engine.Initialize();
	engine.Run();
	engine.Shutdown();

	return 0;
}