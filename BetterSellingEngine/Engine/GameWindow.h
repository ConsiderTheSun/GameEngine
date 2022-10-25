#pragma once

#include <iostream>
class GameWindow{
public:
	GameWindow();
	void SetAspectRatio(unsigned int width, unsigned int height);
	void SetMinWindowHeight(unsigned int minX);
	void SetMinWindowWidth(unsigned int minY);

	std::pair<unsigned int, unsigned int> GetAspectRatio() { return aspectRatio; };
private:
	GLFWwindow* window;

	static GameWindow* windowInstance;

	std::pair<unsigned int, unsigned int> aspectRatio = std::make_pair(1,1);
	std::pair<int, int> minSize = std::make_pair(100, -1);
	void Init(std::string title = "Untitled", int width = 1000, int height = 1000);

	void SwapBuffer();
	bool ShouldClose();
	
	void framebuffer_size_callback(GLFWwindow* window, int width, int height){
		glViewport( 0, 0, width, height);
	}

	static void framebuffer_size_callback_dispatch(GLFWwindow* window, int width, int height){
		windowInstance->framebuffer_size_callback(window, width, height);
	}

	friend class BetterSellingEngine;
	friend class Input;
};

