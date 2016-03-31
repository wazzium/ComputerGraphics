#include "Game.h"


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle), 
	_screenWidth(screenWidth), 
	_screenHeight(screenHeight),
	_gameState(GameState::INIT), 
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS) {


}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);		
		//Compile and Link shader
	loadShaders();
		//Load the current scenario
	_openGLBuffers.initializeBuffers(_colorProgram);
		//Create several vertex
	createPrimitivesToRender();
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::loadShaders() {
		//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPositionGame");
	_colorProgram.addAttribute("vertexColor");
		//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Initialize the position and the color of the different vertices that have to be rendered
*/
void Game::createPrimitivesToRender() {
	data[0].setPosition(0.0f, 0.3f, 0.0f);
	data[0].setColor(0, 255, 0, 255);

	data[1].setPosition(-0.8f, -0.8f, 0.0f);
	data[1].setColor(255, 0, 0, 255);

	data[2].setPosition(0.8f, -0.8f, 0.0f);
	data[2].setColor(0, 0, 255, 255);

	data[3].setPosition(0.0f, 0.8f, 0.0f);
	data[3].setColor(255, 255, 255, 255);

	data[4].setPosition(0.4f, 0.0f, 0.0f);
	data[4].setColor(255, 255, 255, 255);

	data[5].setPosition(0.8f, 0.3f, 0.0f);
	data[5].setColor(255, 255, 255, 255);
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {		
			//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
			//Process the input information (keyboard and mouse)
		processInput();
			//Draw the objects on the screen
		drawGame();	
			//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		default:
			break;
		}
	}
}

/**
* Draw the sprites on the screen
*/
void Game::drawGame() {
		//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();

		//Send data to GPU
	_openGLBuffers.sendDataToGPU(data,MAX_VERTICES);

		//Unbind the program
	_colorProgram.unuse();

		//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

