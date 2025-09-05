#pragma once
#include <iostream>
#include <format>
#include <unordered_map>

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SDL3/SDL.h"
#include "glad/glad.h"

#include "Mesh.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

class Program
{
public:
	Program(uint32_t pWindowWidth = 1280, uint32_t pWindowHeight = 720);
	~Program();

	void run();
	
private:
	static void debugOutput(GLenum source,
							GLenum type,
							GLuint id,
							GLenum severity,
							GLsizei length,
							const GLchar* message,
							const void* userParam);
private:
	bool mProgIsRunning{ true };
	uint32_t mWindowWidth, mWindowHeight;
	SDL_Window* mWindow;
	SDL_GLContext mContext;

};
