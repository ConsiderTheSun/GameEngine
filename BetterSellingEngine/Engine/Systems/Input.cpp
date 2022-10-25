#include "../engineIncludes.h"


GameWindow* Input::gameWindow = nullptr; 
double Input::xPos = 0, Input::yPos = 0;
glm::vec2 Input::mousePosition = glm::vec2(0, 0);
glm::vec2 Input::deltaMouse = glm::vec2(0, 0);

bool Input::scrollChange = false;
float Input::deltaScroll = 0.0f;

std::unordered_map<int, Input::ButtonState> Input::buttonTracker;

void Input::Init(GameWindow* _gameWindow) {
	
	gameWindow = _gameWindow;
	glfwGetCursorPos(gameWindow->window, &xPos, &yPos);
	mousePosition = glm::vec2(xPos, yPos);

	glfwSetScrollCallback(gameWindow->window, scroll_callback_dispatch);
}

void Input::Update() {

	// updates the mouse tracker
	glfwGetCursorPos(gameWindow->window, &xPos, &yPos);
	deltaMouse.x = xPos - mousePosition.x;
	deltaMouse.y = mousePosition.y - yPos;
	mousePosition = glm::vec2(xPos, yPos);

	

	if (scrollChange) {
		scrollChange = false;
	}
	else {
		deltaScroll = 0;
	}

	// updates the keys
	for (auto itr = buttonTracker.begin(); itr != buttonTracker.end(); ++itr) {
		// checks for mouse button
		if (itr->first <= GLFW_MOUSE_BUTTON_LAST) {
			itr->second.prevIsDown = itr->second.isDown;
			itr->second.isDown = glfwGetMouseButton(gameWindow->window, itr->first);
		}
		else {
			itr->second.prevIsDown = itr->second.isDown;
			itr->second.isDown = glfwGetKey(gameWindow->window, itr->first) == GLFW_PRESS;
		}
		
		if (itr->second.isDown && !itr->second.prevIsDown) {
			itr->second.currentState = State::Enter;
		}
		else if (itr->second.isDown && itr->second.prevIsDown) {
			itr->second.currentState = State::Down;
		}
		else if (!itr->second.isDown && itr->second.prevIsDown) {
			itr->second.currentState = State::Release;
		}
		else if (!itr->second.isDown && !itr->second.prevIsDown) {
			itr->second.currentState = State::Up;
		}
	}
}
void Input::AddTracking(int count ...) {
	va_list list;
	va_start(list, count);

	for (int i = 0; i < count; i++) {
		int key = va_arg(list, int);

		// checks if the key is already being tracked
		if (buttonTracker.find(key) != buttonTracker.end()) {
			return;
		}

		buttonTracker.insert(
			{ key,
			ButtonState{false,false, State::Up} });
	}
	va_end(list);
}

void Input::LockMouse() {
	glfwSetInputMode(gameWindow->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

	glfwGetCursorPos(gameWindow->window, &xPos, &yPos);
	mousePosition = glm::vec2(xPos, yPos);
}