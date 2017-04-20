#include "Game.h"

Game::Game() :
	m_Shader(nullptr),
	m_Layer()
{

}

bool Game::Initialize()
{
	EventManager::i()->AddEvent(Events::TESTEVENT, Callback([]() {
		std::cout << "Hello!" << std::endl;
	}));

	AudioManager::i()->Load(synnew Audio("Thor Ragnarok", "res/Sounds/ThorR.ogg"));
	AudioManager::i()->Get("Thor Ragnarok")->Play();

	m_Shader = synnew Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	GLint textureSlots[] = { 0,1,2,3,4,5,6,7,8,9 };

	m_Shader->Enable();
	m_Shader->setUniform2f("light_pos", Vector2(0.0, 0.0));
	m_Shader->setUniformMat4("pr_matrix", Matrix4::Orthographic(-16.0f, 16.0f, 9.0f, -9.0f, 1.0f, -1.0f));
	m_Shader->setUniform1iv("textures", textureSlots, 10);
	m_Shader->Disable();

	FontManager::loadFont("RalewayLight", "res/Fonts/Raleway/Raleway-Light.ttf");

	m_Layer.SetShader(m_Shader);
	m_Layer.SetRenderer(synnew BatchRenderer2D());
	m_Layer.SetProjectionMatrix();

	Group *logo = synnew Group(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	logo->Add(synnew Sprite(Vector3(-9.0f, 0, 0), Vector2(20, 1.5f), Maths::Vector4(26, 26, 26, 255)));
	logo->Add(synnew Label("SYNDICATE", Label::Position::CENTER, Font("RalewayLight", 100, Maths::Vector4(52, 152, 219, 255))));
	m_Layer.Add(logo);

	EventManager::i()->DispatchEvent(Events::TESTEVENT);

	return true;
}

bool Game::Render()
{
	m_Layer.Render();
	return true;
}

bool Game::Shutdown()
{
	m_Layer.Free();
	return true;
}

Game::~Game()
{

}