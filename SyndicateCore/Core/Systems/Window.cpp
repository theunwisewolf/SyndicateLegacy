#include "Window.h"

namespace Syndicate {

Window* Window::instance = nullptr;

Window::Window(std::string title, int width, int height, Color color, bool VSync) :
	IWindow(title, width, height, color, VSync),
	ISystem( "SYNDICATE_SYS_WINDOW" )
{
	Window::instance = this;
}

bool Window::Initialize()
{
	this->setWindowStyle(WS_OVERLAPPEDWINDOW);
	this->setWindowExtendedStyle(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	if (!this->createWindow())
	{
		SYNDICATE_ERROR("Failed to initialize Window!");
		this->ShutDown();
		return false;
	}

	ShowWindow(this->getWindowHandle(), SW_SHOW); 
	//SetForegroundWindow(this->getWindowHandle()); 
	SetFocus(this->getWindowHandle());
	// This function centers the window
	//this->centerWindow();

	this->m_RenderingContext = wglCreateContext(this->getDeviceContext());

	if (!this->m_RenderingContext)
	{
		SYNDICATE_ERROR( "Failed to created a rendering context..." );
		return false;
	}

	if (!wglMakeCurrent(this->getDeviceContext(), this->m_RenderingContext))
	{
		SYNDICATE_ERROR("Failed to activate the rendering context...");
		return false;
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		SYNDICATE_ERROR( "Failed to initialize GLEW." );
		return false;
	}

	this->setVSync(this->m_VSync);
		
	//this->resizeWindow(this->m_Width, this->m_Height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// And finally print some fancy OpenGL Info
	std::string OPENGL_VERSION(reinterpret_cast<char const*>(glGetString(GL_VERSION)));
	std::string OPENGL_VENDOR(reinterpret_cast<char const*>(glGetString(GL_VENDOR)));
	std::string OPENGL_RENDERER(reinterpret_cast<char const*>(glGetString(GL_RENDERER)));

	SYNDICATE_INFO_NH("OpenGL Version: " + OPENGL_VERSION);
	SYNDICATE_INFO_NH("Vendor: " + OPENGL_VENDOR);
	SYNDICATE_INFO_NH("Renderer: " + OPENGL_RENDERER);
	SYNDICATE_INFO_NH(""); // For a synnew line

	// Initialize AudioManager
	SYNDICATE_INFO("Initializing Audio Manager...");
	SYNDICATE_SUCCESS("Successfully Initialized Audio Manager.");

	return true;
}

void Window::setVSync(bool value)
{
#if defined(WIN32) | defined(_WIN32) 
	wglSwapIntervalEXT(value);
#endif
}

void Window::resizeWindow(long width, long height)
{
	this->m_Width = width;
	this->m_Height = height;

	glViewport( 0, 0, (GLsizei)width, (GLsizei)height);
	//Syndicate::Graphics::Font::setScale(Window::i()->getWidth() / 32.0f, Window::i()->getHeight() / 18.0f);
}

LRESULT CALLBACK Window::handleEvents(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
	{
		if (!HIWORD(wParam)) // A nonzero value indicates the window is minimized.
			this->m_IsMinimized = true;
		else
			this->m_IsMinimized = false;

		if(LOWORD(wParam) != WA_INACTIVE)
			this->m_IsActive = true; 
		else
			this->m_IsActive = false;

		return 0;
	}
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}

		break;
	} break;
	case WM_MOUSEMOVE:
		InputManager::i()->DispatchEvents(Events::MOUSEMOVE, message, wParam, lParam);
		return 0;
	case WM_SETFOCUS:
		//FocusCallback(window, true);
		return 0;
	case WM_KILLFOCUS:
		//FocusCallback(window, false);
		return 0;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		InputManager::i()->DispatchEvents(Events::KEYDOWN, message, wParam, lParam);
		return 0;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		InputManager::i()->DispatchEvents(Events::KEYUP, message, wParam, lParam);
		return 0;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		ReleaseCapture();
		InputManager::i()->DispatchEvents(Events::MOUSEUP, message, wParam, lParam);
		return 0;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		SetCapture(hWindow);
		InputManager::i()->DispatchEvents(Events::MOUSEDOWN, message, wParam, lParam);
		return 0;
	case WM_SIZE:
		this->resizeWindow( LOWORD(lParam), HIWORD(lParam) );
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWindow, message, wParam, lParam);
}

bool Window::ShutDown()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(this->m_RenderingContext);

	this->destroyWindow();

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
		SYNDICATE_ERROR("OpenGL error[" + std::to_string(error) + "]: " + this->errors[error]);
		system("PAUSE");
	}

	SwapBuffers(this->getDeviceContext());
}

void Window::setTitle(std::string title)
{
	Syndicate::IWindow::setTitle(title);
}

void Window::Close()
{
	this->ShutDown();
}

void Window::setColor(int r, int g, int b, int a) const
{
	std::tuple<float, float, float, float> colors = std::make_tuple((float)r/255, (float)g/255, (float)b/255, (float)a/255);
	glClearColor(std::get<0>(colors), std::get<1>(colors), std::get<2>(colors), std::get<3>(colors));
}

void Window::centerWindow()
{
	IWindow::centerWindow();
}

POINT Window::getWindowCenterPosition() const
{
	int windowwidth = this->getWindowRect().right - this->getWindowRect().left;
	int windowheight = this->getWindowRect().bottom - this->getWindowRect().top;

	return POINT
	{
		GetSystemMetrics(SM_CXSCREEN) / 2 - windowwidth / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - windowheight / 2
	};
}

POINT Window::getWindowPosition() const
{
	return POINT {
		this->getWindowRect().left,
		this->getWindowRect().bottom
	};
}

Window::~Window()
{
	SYNDICATE_INFO("Shutting Down.");
}

}