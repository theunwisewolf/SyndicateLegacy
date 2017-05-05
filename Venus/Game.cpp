#include "Game.h"

Game::Game() :
	m_Shader(nullptr),
	m_Layer(),
	m_Camera()
{

}

bool Game::Initialize()
{
	AudioManager::i()->Load(synnew Audio("Thor Ragnarok", ResourceManager::i()->LoadAudio("res/Sounds/ThorR.ogg")));
	AudioManager::i()->Get("Thor Ragnarok")->Play();

	KeyEvent::i()->BindKeyPress(Keys::KEY_RETURN, Callback([]() {
		if (AudioManager::i()->Get("Thor Ragnarok")->IsPlaying() == true)
			AudioManager::i()->Get("Thor Ragnarok")->Pause();
		else
			AudioManager::i()->Get("Thor Ragnarok")->Play();
	}));

	MouseEvent::i()->BindMousePress(MouseButtons::BUTTON_LEFT, Callback([&]() {
		Maths::Vector2 coords = m_Camera.screenToWorld(Maths::Vector2(MouseEvent::i()->getX(), MouseEvent::i()->getY()));

		std::cout << "Mouse down: " << coords.x << ", " << coords.y << std::endl;
	}));

	MouseEvent::i()->BindMouseDown(MouseButtons::BUTTON_LEFT, Callback([]() {
		//std::cout << "LEGIT!" << std::endl;
	}));

	m_Shader = synnew Shader("Shaders/VertexShader.vert", "Shaders/FragmentShader.frag");
	GLint textureSlots[] = { 0,1,2,3,4,5,6,7,8,9 };

	m_Camera.Initialize(Maths::Vector2(0.0f, 0.0f), Maths::Vector2(1.0f, 1.0f));
	m_Camera.setMovementSpeed(1.0f);

	m_Shader->Enable();
	m_Shader->setUniform2f("light_pos", Vector2(0.0, 0.0));

	m_Shader->setUniformMat4("pr_matrix", m_Camera.getCameraMatrix());
	m_Shader->setUniform1iv("textures", textureSlots, 10);
	m_Shader->Disable();

	FontManager::loadFont("RalewayLight", "res/Fonts/Raleway/Raleway-Light.ttf");

	m_Layer.SetShader(m_Shader);
	m_Layer.SetRenderer(synnew BatchRenderer2D());
	//m_Layer.SetProjectionMatrix();

	m_Layer.Add(synnew Sprite(Vector3(255.0f, 25.0f, 0), Vector2(50.0f, 50.0f), Maths::Vector4(41, 128, 185, 255)));

	Group *logo = synnew Group(Matrix4::Translation(Vector3(0.0f, 0.0f + 30.0f, 0)));
	logo->Add(synnew Sprite(Position::CENTER, Vector2(450, 50), Maths::Vector4(26, 26, 26, 255)));

	Group* text = synnew Group(Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f)));
	logo->Add(synnew Label("SYNDICATE", Position::CENTER, Font("RalewayLight", 60, Maths::Vector4(52, 152, 219, 255), Vector2(2.0f, 2.0f))));

	logo->Add(text);

	m_Layer.Add(logo);

	return true;
}

bool Game::Update()
{
	m_Camera.Update();
	return true;
}

bool Game::Render()
{
	m_Layer.SetProjectionMatrix(m_Camera.getCameraMatrix());
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