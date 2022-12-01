#pragma once

#include <unordered_map>
#include <cstdarg>

class Input {
public:
	enum State { Enter, Down, Release, Up };
	struct ButtonState {
		bool isDown;
		bool prevIsDown;
		State currentState;
	};


	static void Init(GameWindow* _gameWindow);

	
	static void Update();

	static State KeyDown(int key) {
		auto button = buttonTracker.find(key);
		if (button == buttonTracker.end()) return State::Up;
		return button->second.currentState;
	}

	static bool MouseDown(int mouseKey) { return glfwGetMouseButton(gameWindow->window, mouseKey); }

	static void AddTracking(int count ...);

	static void LockMouse();
	static void UnlockMouse() { glfwSetInputMode(gameWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

	static const glm::vec2 DeltaMouse() { return deltaMouse; };
	static float DeltaScroll() { return deltaScroll; };

	static void GetMousePos(double& xpos, double& ypos);

	static void Reset();
private:

	static GameWindow* gameWindow;

	static double xPos, yPos;
	static glm::vec2 mousePosition;
	static glm::vec2 deltaMouse;

	static bool scrollChange;
	static float deltaScroll;

	static std::unordered_map<int, ButtonState>  buttonTracker;

	static void scroll_callback_dispatch(GLFWwindow* window, double xoffset, double yoffset) {
		scrollChange = true;
		deltaScroll = yoffset;
	}
};