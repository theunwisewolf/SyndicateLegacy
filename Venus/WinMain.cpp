#include "WinMain.h"

#include "Game.h"
#include "TileLayer.h"

#include <Systems/Engine.h>

#include <Utilities\Packaging\ZLib.h>
#include <Utilities\Packaging\Package.h>
#include <Utilities\FileSystem\FileSystem.h>

using namespace Syndicate;

int main(int argc, char* argv[])
{
	SYNDICATE_SUCCESS(FileSystem::i()->getTempDirectory());

	Package package("AmN");

	SoundData sound, sound2;

	File mp3File = Syndicate::Utilities::File("res/Sounds/01.ogg", true);

	std::string data = mp3File.Read().getData();

	sound.setData(data);
	sound.length = mp3File.getFileSize();
	sound.setFormat("ogg");

	int id = package.AddSound( "The Trail", sound );

	File anotherFile = Syndicate::Utilities::File("res/Sounds/ThorR.ogg", true);

	std::string data2 = anotherFile.Read().getData();

	sound2.setData(data2);
	sound2.length = anotherFile.getFileSize();
	sound2.setFormat("ogg");

	package.AddSound( "Thor Ragnarok", sound2);

	package.Pack("res/amn");

	Package cpkg;
	cpkg.Unpack("res/amn");

	SoundData *storedSound = cpkg.GetSound(id);

	Engine engine(synnew Game());

	engine.Initialize();
	engine.Run();
	engine.Shutdown();

	return 0;
}