#include "Window.h"

Window* Window::instance = nullptr;

Window::Window(std::string title, int width, int height, int r, int g, int b, int a) :
	m_Title{title},
	m_Width{width},
	m_Height{height}
{
	glfwSetErrorCallback(&Window::glfwErrorCallback);

	if (!this->Init())
	{
		glfwTerminate();
	}

	this->setColor(r, g, b, a);
}

void APIENTRY Window::glDebugMessageCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

bool Window::Init()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW." << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the OpenGL Window
	this->m_Window = glfwCreateWindow( this->m_Width, this->m_Height, this->m_Title.c_str(), nullptr, nullptr );
	Window::instance = this;

	if (!this->m_Window)
	{
		std::cout << "Failed to create window or OpenGL context." << std::endl;
		return false;
	}

	// Callbacks
	glfwSetKeyCallback(this->m_Window, &Window::glfwKeyCallback);
	glfwSetCursorPosCallback(this->m_Window, &Window::glfwCursorPositionCallBack);
	glfwSetFramebufferSizeCallback(this->m_Window, &Window::glfwWindowSizeCallback);
	glfwSetMouseButtonCallback(this->m_Window, &Window::glfwMouseButtonCallback);

	// Pass our "Window" class SYNDICATE_API object to the glfw for callbacks to use
	glfwSetWindowUserPointer(this->m_Window, this);

	// Make the context current
	glfwMakeContextCurrent(this->m_Window);

	// Buffer swap interval
	glfwSwapInterval(0);

	// This function centers the window
	this->centerWindow();

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW.";
		return false;
	}
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// And finally print some fancy OpenGL Info
	std::string OPENGL_VERSION(reinterpret_cast<char const*>(glGetString(GL_VERSION)));
	std::string OPENGL_VENDOR(reinterpret_cast<char const*>(glGetString(GL_VENDOR)));
	std::string OPENGL_RENDERER(reinterpret_cast<char const*>(glGetString(GL_RENDERER)));

	SYNDICATE_INFO_NH("OpenGL Version: " + OPENGL_VERSION);
	SYNDICATE_INFO_NH("Vendor: " + OPENGL_VENDOR);
	SYNDICATE_INFO_NH("Renderer: " + OPENGL_RENDERER);
	SYNDICATE_INFO_NH(""); // For a new line

	// Initialize AudioManager
	SYNDICATE_INFO("Initializing Audio Manager...");
	SYNDICATE_SUCCESS("Successfully Initialized Audio Manager.");

	return true;
}

void Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	GLenum error;

	if (( error = glGetError() ) != GL_NO_ERROR)
	{
		std::cout << "OpenGL error[" << error << "]: " << this->errors[error] << std::endl;
		system("PAUSE");
	}

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		m_KeysTyped[i] = m_Keys[i] && !m_KeyState[i];
	}

	memcpy(m_KeyState, m_Keys, MAX_KEYS * sizeof(bool));

	glfwSwapBuffers(this->m_Window);
	glfwPollEvents();
}

void Window::setTitle(std::string title)
{
	glfwSetWindowTitle(this->m_Window, title.c_str());
}

void Window::glfwErrorCallback(int error, const char* description)
{
	std::cout << description;
}

void Window::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window *w = (Window*)glfwGetWindowUserPointer(window);
	w->m_Keys[key] = (action != GLFW_RELEASE);
	w->m_KeysTyped[key] = (action == GLFW_RELEASE);
}

void Window::glfwWindowSizeCallback(GLFWwindow * window, int width, int height)
{
	Window *w = (Window*)glfwGetWindowUserPointer(window);
	w->m_Width = width;
	w->m_Height = height;
	glViewport(0, 0, width, height);
}

void Window::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window *w = (Window*)glfwGetWindowUserPointer(window);
	w->m_MouseButtons[button] = (action != GLFW_RELEASE);
}

void Window::glfwCursorPositionCallBack(GLFWwindow* window, double xpos, double ypos)
{
	Window *w = (Window*)glfwGetWindowUserPointer(window);
	w->mouseX = xpos;
	w->mouseY = ypos;
}

bool Window::Closed() const
{
	return glfwWindowShouldClose(this->m_Window) == 1;
}

void Window::Close() const
{
	Syndicate::Graphics::FontManager::Clear();
	Syndicate::AudioManager::i()->Stop();

	glfwDestroyWindow(this->m_Window);
	glfwTerminate();
}

void Window::setColor(int r, int g, int b, int a) const
{
	std::tuple<float, float, float, float> colors = std::make_tuple((float)r/255, (float)g/255, (float)b/255, (float)a/255);
	glClearColor(std::get<0>(colors), std::get<1>(colors), std::get<2>(colors), std::get<3>(colors));
}

void Window::centerWindow() const
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int x, y;

	x = ( mode->width - this->m_Width ) / 2;
	y = ( mode->height - this->m_Height ) / 2;

	glfwSetWindowPos( this->m_Window, x, y );
}

void Window::getMousePosition(double &x, double &y) const
{
	x = this->mouseX;
	y = this->mouseY;
}

Window::~Window()
{
	SYNDICATE_INFO("Shutting Down.");
	//this->Close();
}
