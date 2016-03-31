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
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS),
	_dinamicColor(1.0),
	_time(0){
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
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.vert");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.frag");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
		//Link the compiled shaders
	_colorProgram.linkShaders();
}

/**
* Initialize the position and the color of the different vertices that have to be rendered
*/
void Game::createPrimitivesToRender() {

	float x = 0.5;
	float y = 0.5;

	float width = 1;
	float height = 1;

	//First triangle
	data[0].setPosition(-x/2, -y/2, 0.0f);
	data[0].setColor(0, 255, 0, 255);

	data[1].setPosition(x/width, -y/2, 0.0f);
	data[1].setColor(255, 0, 0, 255);

	data[2].setPosition(x/2-width, y/2-height, 0.0f);
	data[2].setColor(0, 0, 255 , 255);

	//Second triangle
	data[3].setPosition(-x/2, -y/2, 0.0f);
	data[8].setColor(0, 0, 255, 255);

	data[4].setPosition(x/2 - width, y/2-height, 0.0f);
	data[8].setColor(0, 0, 255, 255);

	data[5].setPosition(-x/2, y/2 - height, 0.0f);
	data[8].setColor(0, 0, 255, 255);

	//Third triangle
	data[6].setPosition(width - x/3, y/2, 0.0f);
	data[8].setColor(0, 0, 255, 255);

	data[7].setPosition(width - x, height -y/3, 0.0f);
	data[8].setColor(0, 0, 255, 255);

	data[8].setPosition(x/3, y/2, 0.0f);
	data[8].setColor(0, 0, 255, 255);

	//Fourth triangle
	data[9].setPosition(width - x / 3, y / 2, 0.0f);
	data[9].setColor(0, 0, 255, 255);

	data[10].setPosition(width - x, height - y / 3, 0.0f);
	data[10].setColor(0, 0, 255, 255);

	data[11].setPosition(x / 3, y / 2, 0.0f);
	data[11].setColor(0, 0, 255, 255);

	//Set the color to magenta
	for (int i = 0; i < 9; i++) {
		data[i].setColor(255, 0, 255, 255);
	}

	//Set the color of the 1st coordinate to blue
	data[1].setColor(0, 0, 255, 255);
	//Set the color of the 4th coordinate to green
	data[4].setColor(0, 255, 0, 255);

	data[6].setColor(255, 255, 255, 255);
	data[7].setColor(255, 255, 255, 255);
	data[8].setColor(255, 255, 255, 255);
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

		//Set the new value for the uniform variable
		//Important: If time is not used in the shader, we will get an error because GLSL will delete it for us. Then, we need to comment the following three lines
	
	_time = _time+0.05f;
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation,_time);


	//Per no pintar el color dinamic
	GLuint dinamicColorLocation = _colorProgram.getUniformLocation("dinamicColor");
	glUniform1i(dinamicColorLocation, 0);
	//Per pintar el color dinamic
	    //GLuint dinamicColorLocation = _colorProgram.getUniformLocation("dinamicColor");


	//Send data to GPU
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	_openGLBuffers.sendDataToGPU(GL_TRIANGLES, data, 6);
	
	glUniform1i(dinamicColorLocation, 1);
	_openGLBuffers.sendDataToGPU(GL_LINES, &data[9], 3); //vaig a la posicio i l hi dic quants vertex
	


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	
	//Unbind the program
	_colorProgram.unuse();

	//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

