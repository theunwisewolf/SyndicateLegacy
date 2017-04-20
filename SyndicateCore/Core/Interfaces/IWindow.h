#ifndef IWINDOW_H_
#define IWINDOW_H_

#include <Common.h>

#include <Windows.h>
#include <Windowsx.h>

#include <string>

#include <Utilities/Logger.h>
#include <Systems/Graphics/Color.h>

namespace Syndicate {

using namespace Graphics;

class SYNDICATE_API IWindow
{
protected: 
	WNDCLASSEX createWindowClass();
	bool createWindow();
	void destroyWindow();

	PIXELFORMATDESCRIPTOR createPixelFormatDescriptor();

	inline std::string getWindowClassName() const		{ return this->m_WindowClassName; }
	inline RECT getWindowRect() const					{ return this->m_WindowRectangle; }

	void setWindowStyle(DWORD style)					{ this->m_WindowStyle |= style; }
	void setWindowExtendedStyle(DWORD style)			{ this->m_WindowExtendedStyle |= style; }

	inline DWORD getWindowStyle() const					{ return this->m_WindowStyle; }
	inline DWORD getWindowExtendedStyle() const			{ return this->m_WindowExtendedStyle; }

private:
	std::string		m_WindowClassName;
	Color			m_Color;

	DWORD			m_WindowExtendedStyle;
	DWORD			m_WindowStyle;

	unsigned int	m_PixelFormat;

protected:
	std::string		m_Title;

	long			m_Width;
	long			m_Height;

	HWND			m_Window;
	HDC				m_DeviceContext;
	HINSTANCE		m_Instance;

	RECT			m_WindowRectangle;

	bool			m_FullScreen;
	bool			m_IsActive;
	bool			m_IsMinimized;

	bool			m_VSync;

public:
	IWindow(std::string title, long width, long height, Color color, bool VSync);
	virtual ~IWindow();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// This function handles all the events
	virtual LRESULT CALLBACK handleEvents(HWND, UINT, WPARAM, LPARAM) = 0;

	virtual void setTitle(std::string title)		{ SetWindowText(this->m_Window, title.c_str()); };
	virtual void centerWindow();
	virtual void resizeWindow(long width, long height) = 0;

	virtual inline std::string getTitle() const = 0;
	virtual BYTE getWindowBitsPerPixel() const = 0;

	virtual inline long getWidth() const			{ return this->m_Width; }
	virtual inline long getHeight() const			{ return this->m_Height; }

	virtual POINT getWindowPosition() const = 0;
	virtual POINT getWindowCenterPosition() const = 0;

	virtual void setVSync(bool value) = 0;

	inline HDC			getDeviceContext() const	{ return m_DeviceContext; }
	inline HWND			getWindowHandle() const		{ return m_Window; }
	inline HINSTANCE	getInstance() const			{ return m_Instance; }

	void fullScreen();
};

}

#endif