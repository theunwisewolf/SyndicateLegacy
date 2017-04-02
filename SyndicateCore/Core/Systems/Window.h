#ifndef WINDOW_H_
#define WINDOW_H_

#include <Common.h>

#define MAX_KEYS 1024
#define MAX_BTNS 32

#include <glew.h>
#include <glfw3.h>

#include <string>
#include <iostream>
#include <tuple>
#include <map>

#include <Systems/Graphics/FontManager.h>
#include <Systems/Audio/AudioManager.h>
#include <Utilities/Logger.h>

class SYNDICATE_API Window
{
public:
	static Window* i() {
		return instance;
	}
private:
	static Window* instance;

private: 
	std::map<GLenum, std::string> errors{
		{ GL_INVALID_ENUM, "[GL_INVALID_ENUM] An unacceptable value is specified for an enumerated argument." },
		{ GL_INVALID_VALUE, "[GL_INVALID_VALUE] A numeric argument is out of range." },
		{ GL_INVALID_OPERATION, "[GL_INVALID_OPERATION] The specified operation is not allowed in the current state." },
		{ GL_INVALID_FRAMEBUFFER_OPERATION, "[GL_INVALID_FRAMEBUFFER_OPERATION] The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete." },
		{ GL_OUT_OF_MEMORY, "[GL_OUT_OF_MEMORY] There is not enough memory left to execute the command." }
	};

	GLFWwindow* m_Window;
	std::string m_Title;
	int m_Width;
	int m_Height;

	bool m_Keys[MAX_KEYS] = { false };
	bool m_KeyState[MAX_KEYS] = { false };
	bool m_KeysTyped[MAX_KEYS] = { false };
	bool m_MouseButtons[MAX_BTNS] = { false };
	double mouseX;
	double mouseY;

	bool Init();
public:
	Window( std::string, int, int, int r = 0, int g = 0, int b = 0, int a = 255 );
	~Window();

	bool Closed() const;
	void Clear() const;
	void Close() const;
	void Update();

	void setTitle(std::string title);

	void setColor(int, int, int, int a = 255) const;
	void centerWindow() const;
	void getMousePosition(double&, double&) const;

	bool IsKeyPressed(size_t keyCode) const { return m_Keys[keyCode]; }
	bool IsKeyTyped(size_t keyCode)	const { return m_KeysTyped[keyCode]; }

	void clearTypedKeys() { memset(m_KeysTyped, false, MAX_KEYS * sizeof(bool)); }

	inline double getMouseX() const { return this->mouseX; }
	inline double getMouseY() const { return this->mouseY; }
	inline double getWidth()  const { return this->m_Width; }
	inline double getHeight() const { return this->m_Height; }
	inline std::string getTitle() const { return this->m_Title; }

	GLFWwindow* getWindow() const { return this->m_Window; }
private: 
	static void glfwErrorCallback(int error, const char* description);
	static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
	static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void glfwCursorPositionCallBack(GLFWwindow* window, double xpos, double ypos);
	static void APIENTRY glDebugMessageCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};

#endif