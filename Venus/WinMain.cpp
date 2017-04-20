#include "WinMain.h"

#include "Game.h"
#include "TileLayer.h"

#include <Systems/Engine.h>

using namespace Syndicate;

int main(int argc, char* argv[])
{
	Engine engine(synnew Game());

	engine.Initialize();
	engine.Run();
	engine.Shutdown();

	return 0;
}