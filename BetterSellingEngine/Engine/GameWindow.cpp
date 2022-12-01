#include "engineIncludes.h"

GameWindow::GameWindow() {
	windowInstance = this;
}

void GameWindow::SetAspectRatio(unsigned int width, unsigned int height) {
	if(window){
		aspectRatio = std::make_pair(width, height);
		glfwSetWindowAspectRatio(window, width, height);

		// sets min size with new aspect ratio, based on prev call
		if (minSize.first != -1) {
			SetMinWindowHeight(minSize.first);
		}
		else if (minSize.second != -1) {
			SetMinWindowWidth(minSize.second);
		}
	}
}
void GameWindow::SetMinWindowWidth(unsigned int minY) {
	if (window) {
		minSize = std::make_pair(-1, (int)minY);
		unsigned int minX = minY * ((float)aspectRatio.first / aspectRatio.second);
		glfwSetWindowSizeLimits(window, minX, minY, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
}
void GameWindow::SetMinWindowHeight(unsigned int minX) {
	if (window){
		minSize = std::make_pair((int)minX, -1);
		unsigned int minY = (float)minX / ((float)aspectRatio.first / aspectRatio.second);
		glfwSetWindowSizeLimits(window, minX, minY, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
}


void GameWindow::Init(std::string title, int width, int height) {
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window){
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);

	SetAspectRatio(1, 1);
	SetMinWindowHeight(100);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_dispatch);
	
}

void GameWindow::SwapBuffer() {
	glfwSwapBuffers(window); 
}

bool GameWindow::ShouldClose() {
	return glfwWindowShouldClose(window);
}

GameWindow* GameWindow::windowInstance = nullptr;
//GameWindow* GameWindow::GetInstance(){
//	if (!windowInstance)
//		windowInstance = new GameWindow();
//	return windowInstance;
//}
