#include "Game.h"

Game::Game() :
	m_Shader(nullptr),
	m_Layer(),
	m_Camera(),
	m_GameState(GameState::PAUSED)
{
}

bool Game::Initialize()
{
	// Load the required resource packages
	this->LoadPackages();

	AudioManager::i()->Load(synnew Audio("The Trail"));
	AudioManager::i()->Load(synnew Audio("The Beast of Beauclair"));
	//AudioManager::i()->Get("The Beast of Beauclair")->Play();
	//AudioManager::i()->Get("The Trail")->Play();

	KeyEvent::i()->BindKeyPress(Keys::KEY_RETURN, Callback([]() {
		if (AudioManager::i()->Get("The Beast of Beauclair")->IsPlaying() == true)
			AudioManager::i()->Get("The Beast of Beauclair")->Pause();
		else
			AudioManager::i()->Get("The Beast of Beauclair")->Play();
	}));

	KeyEvent::i()->BindKeyPress(Keys::KEY_SPACE, Callback([&]() {
		Engine::i()->ToggleRendering();
	}));

	MouseEvent::i()->BindMousePress(MouseButtons::BUTTON_LEFT, Callback([&]() {
		glm::vec2 coords = m_Camera.screenToWorld(glm::vec2(MouseEvent::i()->getX(), MouseEvent::i()->getY()));

		std::cout << "Mouse down: " << coords.x << ", " << coords.y << std::endl;
	}));

	MouseEvent::i()->BindMouseDown(MouseButtons::BUTTON_LEFT, Callback([]() {
		//std::cout << "LEGIT!" << std::endl;
	}));

	m_Shader = synnew Shader("VertexShader.vert", "FragmentShader.frag");
	GLint textureSlots[] = { 0,1,2,3,4,5,6,7,8,9 };

	m_Camera.Initialize(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	m_Camera.setMovementSpeed(1.0f);

	m_Shader->Enable();
	m_Shader->setUniform2f("light_pos", glm::vec2(0.0, 0.0));

	m_Shader->setUniformMat4("pr_matrix", m_Camera.getCameraMatrix());
	m_Shader->setUniform1iv("textures", textureSlots, 10);
	m_Shader->Disable();

	FontManager::loadFont("RalewayLight", "res/Fonts/Raleway/Raleway-Light.ttf");

	m_Layer.SetShader(m_Shader);
	m_Layer.SetRenderer(synnew BatchRenderer2D());
	m_Layer.SetProjectionMatrix();

	m_Layer.Add("Test", synnew Sprite(glm::vec3(0.0f, 0.0f, 0), glm::vec2(50.0f, 50.0f), "texture_b.png"));
	m_Layer.GetSprite("Test")->setAngle(45.0f);

	Group *logo = synnew Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 30.0f, 0.0f)));
	logo->Add(synnew Sprite(Position::CENTER, glm::vec2(450, 50), Color(26, 26, 26, 255U)));

	Group* text = synnew Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	logo->Add(synnew Label("SYNDICATE", Position::CENTER, Font("RalewayLight", 60, Color(52, 152, 219, 255U), glm::vec2(2.0f, 2.0f))));

	logo->Add(text);

	m_Layer.Add(logo);

	// The Box2D World!
	b2Vec2 gravity(0.0f, -9.81f);

	// DebugDraw
	m_World = std::make_unique<b2World>(gravity);

#if defined(DEBUG) | defined(_DEBUG) | defined(DEBUG_DRAW)
	m_DebugDraw.Init();

	m_World->SetDebugDraw(&m_DebugDraw);

	m_DebugDraw.SetFlags(DebugDraw::e_shapeBit);
#endif

	b2BodyDef groundDef;
	groundDef.position.Set(0.0f, -Window::i()->getHeight() / 2);

	b2Body* ground = m_World->CreateBody(&groundDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(Window::i()->getWidth(), 25.0f);

	ground->CreateFixture(&groundShape, 0.0f);

	// Initialize our boxes!
	std::random_device device;
	std::mt19937 rd(device());
	std::uniform_int_distribution<int> xPos(0.0f, 100.0f);
	std::uniform_int_distribution<int> yPos(25.0f, 100.0f);
	std::uniform_int_distribution<int> size(10, 30);
	std::uniform_int_distribution<int> color(0, 255);
	std::uniform_int_distribution<int> texture(1, 14);
	const int NUMBOXES = 10;
	float _x = 0.0f;
	float _y = 0.0f;
	int s = 50;

	for (int i = 0; i < NUMBOXES; ++i)
	{	
		Color c = Color(color(rd), color(rd), color(rd), 255U);
		std::string tex = "res_" + std::to_string( texture(rd) );

		_x = xPos(rd);
		_y = yPos(rd);
		Box box(this->m_World.get(), glm::vec3(_x, _y, 0), glm::vec2(s, s), c);
		m_Boxes.push_back(box);

		m_Layer.Add("Box" + std::to_string(i), synnew Sprite(glm::vec3(_x, _y, 0.0f), glm::vec2(s, s), tex));
	}

	return true;
}

bool Game::Update(double deltatime)
{
	m_Camera.Update();

	if (this->m_GameState != GameState::PAUSED)
		m_World.get()->Step(1.0f / 60.0f, 8, 3);

	return true;
}

bool Game::Render(bool state)
{
	m_Layer.SetProjectionMatrix(m_Camera.getCameraMatrix());

	if (state)
	{
		for (int i = 0; i < m_Boxes.size(); ++i)
		{
			Box box = m_Boxes[i];

			glm::vec3 position;
			position.x = box.GetBody()->GetPosition().x - box.GetSize().x / 2.0f;
			position.y = box.GetBody()->GetPosition().y - box.GetSize().y / 2.0f;
			position.z = 0.0f;

			float angle = box.GetBody()->GetAngle();

			angle = Math::toDegrees(angle);

			((Sprite*)m_Layer.GetSprite("Box" + std::to_string(i)))->setPosition(position);
			((Sprite*)m_Layer.GetSprite("Box" + std::to_string(i)))->setAngle(angle);
		}

		if (this->IsPaused())
		{
			this->UnPause();
		}
	}
	else
	{
		this->Pause();
	}

	m_Layer.Render();

#if defined(DEBUG) | defined(_DEBUG) | defined(DEBUG_DRAW)
	m_DebugDraw.setPrMatrix(m_Camera.getCameraMatrix());
	m_World->DrawDebugData();
#endif
	
	return true;
}

bool Game::Shutdown()
{
	m_Layer.Free(); 

#if defined(DEBUG) | defined(_DEBUG) | defined(DEBUG_DRAW)
	m_DebugDraw.End();
#endif

	return true;
}

void Game::LoadPackages()
{
	ResourceManager::i()->LoadPackage("packages/amn.spkg");
}

void Game::Pause()
{
	this->m_GameState = GameState::PAUSED;
}

void Game::UnPause()
{
	this->m_GameState = GameState::RUNNING;
}

Game::~Game()
{
	for (int i = 0; i < m_Boxes.size(); ++i)
	{
		m_World.get()->DestroyBody(m_Boxes[i].GetBody());
	}
}