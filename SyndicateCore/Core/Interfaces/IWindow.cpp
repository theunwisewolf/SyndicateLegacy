#include "IWindow.h"

namespace Syndicate {

IWindow::IWindow(std::string title, long width, long height, Color color, bool VSync) :
	m_Title(title),
	m_Width(width),
	m_Height(height),
	m_Color(color),
	m_WindowClassName(title),
	m_FullScreen(false),
	m_Window(NULL),
	m_DeviceContext(NULL),
	m_Instance(GetModuleHandle(NULL)),
	m_WindowStyle(WS_CLIPSIBLINGS | WS_CLIPCHILDREN),
	m_WindowExtendedStyle(0),
	m_PixelFormat(0),
	m_IsActive(true),
	m_IsMinimized(false),
	m_VSync(VSync)
{
	// We don't want any spaces in the window class name
	std::replace(m_WindowClassName.begin(), m_WindowClassName.end(), ' ', '_');

	// Put our name marker in the class name
	m_WindowClassName = "Syndicate_Window_" + m_WindowClassName;

	// The window rectangle
	this->m_WindowRectangle = RECT{
		(long)0,
		(long)0,
		(long) this->getWidth(),
		(long) this->getHeight()
	};
}  

LRESULT CALLBACK IWindow::WndProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		// We retrieve the window pointer and store it 
		CREATESTRUCT *pCS = (CREATESTRUCT*)lParam;
		SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR)pCS->lpCreateParams);
	}
	else
	{
		// Retrieve the previously stored poitner
		IWindow* window = (IWindow*)(GetWindowLongPtr(hWindow, GWLP_USERDATA));
		
		if (window)
		{
			return window->handleEvents(hWindow, message, wParam, lParam);
		}
	}

	return DefWindowProc(hWindow, message, wParam, lParam);
}

bool IWindow::createWindow()
{
	// Register window class
	if (!RegisterClassExA(&this->createWindowClass()))
	{
		SYNDICATE_ERROR("Failed to Register window class.");
		return false;
	}

	AdjustWindowRectEx(&this->m_WindowRectangle, this->getWindowStyle(), false, this->getWindowExtendedStyle());

	// Create the window
	this->m_Window = CreateWindowExA(
		this->getWindowExtendedStyle(),
		this->m_WindowClassName.c_str(),
		this->m_Title.c_str(),
		this->getWindowStyle(),
		this->getWindowCenterPosition().x,
		this->getWindowCenterPosition().y,
		this->m_WindowRectangle.right - this->m_WindowRectangle.left,
		this->m_WindowRectangle.bottom - this->m_WindowRectangle.top,
		NULL,
		NULL,
		this->m_Instance,
		this
	);

	if (this->m_Window == NULL)
	{
		SYNDICATE_ERROR( "Failed to create Window." );
		return false;
	}

	// Create the device context
	this->m_DeviceContext = GetDC(this->m_Window);

	if (this->m_DeviceContext == NULL)
	{
		SYNDICATE_ERROR( "Failed to create device context." );
		return false;
	}

	// Create the pixel format descriptor
	PIXELFORMATDESCRIPTOR pfd = this->createPixelFormatDescriptor();

	this->m_PixelFormat = ChoosePixelFormat(this->m_DeviceContext, &pfd);

	if (this->m_PixelFormat == NULL)
	{
		SYNDICATE_ERROR( "Cannot find a suitable Pixel Format." );
		return false;
	}

	if (!SetPixelFormat(this->m_DeviceContext, this->m_PixelFormat, &pfd))
	{
		SYNDICATE_ERROR( "Can't set the pixel format." );
		return false;
	}

	return true;
}

void IWindow::fullScreen()
{
	// TODO
}

void IWindow::centerWindow()
{
	int windowWidth = this->m_WindowRectangle.right - this->m_WindowRectangle.left;
	int windowHeight = this->m_WindowRectangle.bottom - this->m_WindowRectangle.top;

	POINT position = POINT
	{
		GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2
	};

	SetWindowPos(this->m_Window, HWND_TOP, position.x, position.y, windowWidth, windowHeight, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

void IWindow::destroyWindow()
{
	if (m_FullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	LPCSTR windowClassName = this->m_WindowClassName.c_str();

	if (this->m_DeviceContext && !ReleaseDC(this->m_Window, this->m_DeviceContext))
	{
		SYNDICATE_ERROR("Failed to release device context.");
	}

	if (this->m_Window && !DestroyWindow(this->m_Window))
	{
		SYNDICATE_ERROR("Failed to destroy window.");
	}

	if (!UnregisterClass(windowClassName, this->m_Instance))
	{
		SYNDICATE_ERROR("Failed to unregister window class.");
	}

	this->m_DeviceContext = NULL;
	this->m_Window = NULL;
	this->m_Instance = NULL;
}

PIXELFORMATDESCRIPTOR IWindow::createPixelFormatDescriptor()
{
	return PIXELFORMATDESCRIPTOR{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		getWindowBitsPerPixel(),
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,			// Number of bits for the depthbuffer
		8,			// Number of bits for the stencilbuffer
		0,			// Number of Aux buffers in the framebuffer
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

}

WNDCLASSEX IWindow::createWindowClass()
{
	LPCSTR windowClassName = this->m_WindowClassName.c_str();

	WNDCLASSEX windowClass;
	memset(&windowClass, NULL, sizeof(windowClass));

	windowClass.cbSize = sizeof(windowClass);
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;

	windowClass.hbrBackground = NULL;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hInstance = this->m_Instance;

	windowClass.lpfnWndProc = IWindow::WndProc;
	windowClass.lpszClassName = windowClassName;
	windowClass.lpszMenuName = NULL;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	return windowClass;
}

IWindow::~IWindow()
{

}

}