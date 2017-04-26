#ifndef WINDOW_H_
#define WINDOW_H_

#include <Common.h>

#define BYTES_PER_PIXEL 32

#include <glew.h>

#if defined(WIN32) | defined(_WIN32) 
	#include <wglew.h>
#endif

#include <string>
#include <iostream>
#include <tuple>
#include <map>

#include <Utilities/Logger.h>

#include <Interfaces/IWindow.h>
#include <Interfaces/ISystem.h>

#include <Systems/Graphics/Font.h>
#include <Systems/Graphics/Color.h>
#include <Systems/Audio/AudioManager.h>
#include <Systems/Graphics/FontManager.h>

#include <Systems/Input/InputManager.h>
#include <Systems/Event/Events.h>

namespace Syndicate {

class SYNDICATE_API Window : public Syndicate::IWindow, public Syndicate::ISystem
{
public:
	static Window* i() {
		return instance;
	}
private:
	static Window* instance;

private: 
	HGLRC m_RenderingContext;

	std::map<GLenum, std::string> errors{
		{ GL_INVALID_ENUM, "[GL_INVALID_ENUM] An unacceptable value is specified for an enumerated argument." },
		{ GL_INVALID_VALUE, "[GL_INVALID_VALUE] A numeric argument is out of range." },
		{ GL_INVALID_OPERATION, "[GL_INVALID_OPERATION] The specified operation is not allowed in the current state." },
		{ GL_INVALID_FRAMEBUFFER_OPERATION, "[GL_INVALID_FRAMEBUFFER_OPERATION] The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete." },
		{ GL_OUT_OF_MEMORY, "[GL_OUT_OF_MEMORY] There is not enough memory left to execute the command." }
	};

public:
	Window( std::string, int, int, Color color = Color(0x000000ff), bool VSync = false);
	virtual ~Window();

	void setColor(int r, int g, int b, int a) const;
	virtual void centerWindow();

	virtual bool Initialize();
	virtual void Update();
	virtual bool ShutDown();

	virtual POINT getWindowPosition() const override;
	virtual POINT getWindowCenterPosition() const override;
	virtual void resizeWindow(long width, long height) override;

	virtual BYTE getWindowBitsPerPixel() const override { return BYTES_PER_PIXEL; }

	virtual LRESULT CALLBACK handleEvents(HWND, UINT, WPARAM, LPARAM) override;

	void Clear() const;
	void Close();

	virtual void setTitle(std::string title) override;
	virtual void setVSync(bool value) override;

	virtual inline std::string getTitle() const { return this->m_Title; }
};

}

#endif
