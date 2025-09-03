#include "Program.h"

Program::Program(uint32_t pWindowWidth, uint32_t pWindowHeight)
	: mWindowWidth(pWindowWidth),
	  mWindowHeight(pWindowHeight)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Couldnt initialize the window!\n";
		exit(1);
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mWindow = SDL_CreateWindow("Batch Renderer", mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!mWindow)
		std::cout << "Couldnt set the window!\n";
	mContext = SDL_GL_CreateContext(mWindow);
	if (!mContext)
		std::cout << "Couldnt set the context!\n";
	if (!SDL_GL_MakeCurrent(mWindow, mContext))
		std::cout << "Couldnt set the window and the context current!\n";
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		std::cout << "Couldnt load the glad loader!\n";
}

Program::~Program()
{
	SDL_GL_DestroyContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Program::run()
{
	std::vector<Vertex> vertices =
	{
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f},
		{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), 0.0f}, 
		{glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), 0.0f}, 
		{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), 0.0f} 
	};
	std::vector<uint32_t> indices =
	{
		0, 1, 2,
		2, 3, 0,
	};
	Mesh mMesh;
	mMesh.init(vertices, indices);

	Shader shader;
	std::string resourcePath = RESOURCES_PATH;
	shader.init(resourcePath + "vert.glsl", resourcePath + "frag.glsl");

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 model(1.0f);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), float(mWindowWidth) / float(mWindowHeight), 0.1f, 1000.0f);
	mMesh.setMVP(model, view, proj);

	bool whiteScreen{ false };
	SDL_Event event;
	while (mProgIsRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT ||
				event.key.key == SDLK_ESCAPE)
			{
				mProgIsRunning = false;
				break;
			}
			if (event.key.key == SDLK_V)
				whiteScreen = true;
			if (event.key.key == SDLK_B)
				whiteScreen = false;

		}
		glViewport(0, 0, mWindowWidth, mWindowHeight);
		if (whiteScreen)
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		else
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mMesh.draw("uMVP", shader);

		SDL_GL_SwapWindow(mWindow);
	}
}
