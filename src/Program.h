#pragma once
#include <iostream>
#include <format>

#include "glm.hpp"
#include "SDL3/SDL.h"
#include "glad/glad.h"


class Program
{
public:
	Program(uint32_t pWindowWidth = 1280, uint32_t pWindowHeight = 720);
	~Program();

	void run();

private:
	uint32_t mWindowWidth, mWindowHeight;
	SDL_Window* mWindow;
	SDL_GLContext mContext;

};

