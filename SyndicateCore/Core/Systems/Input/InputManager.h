#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#define MAX_KEYS 256
#define MAX_BUTTONS 5

#include <Common.h>
#include <Windowsx.h>

#include <Systems/Event/Events.h>
#include <Systems/Event/KeyEvent.h>
#include <Systems/Event/MouseEvent.h>
#include <Systems/Event/EventManager.h>

#include <Utilities/Maths/Maths.h>

namespace Syndicate {

class SYNDICATE_API InputManager 
{
public:
	static InputManager* i()
	{
		static InputManager instance;
		return &instance;
	}

private:
	bool m_KeysDown[MAX_KEYS];
	Maths::Vector2 m_MouseCoordinates;

	InputManager();
	InputManager(const InputManager& copy) = delete;
	InputManager operator=(const InputManager& copy) = delete;

public:
	void Initialize();

	void DispatchEvents(Events type, UINT message, WPARAM keycode, LPARAM eventInfo);
	MouseButtons GetMouseButton(UINT message);
	Maths::Vector2 getMouseCoordinates() const { return this->m_MouseCoordinates; }

	void Update();

	void ShutDown();

	bool isKeyDown(Keys key);
	bool isKeyUp(Keys key);
};

}

#endif