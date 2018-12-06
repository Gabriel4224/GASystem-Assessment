#include "GeneticAlgorithmsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "GASystem.h"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "Directions.h"
#include <Gizmos.h>
#include <ctime>
GeneticAlgorithmsApp::GeneticAlgorithmsApp()
	:MazeRender(20 ,20)
{
	

}

GeneticAlgorithmsApp::~GeneticAlgorithmsApp() {

}
bool GeneticAlgorithmsApp::startup() {
	
	//srand(5);

	m_2dRenderer = new aie::Renderer2D();
	//MUTATEs map
	srand(time(NULL));
		
	
	//MazeRender->GenerateMaze(); 
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	//m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	MazeRender.GenerateMaze();
	ga_system = new MyGASystem;
	//ga_system.Population();
	ga_system->Population(); 


	return true;
}

void GeneticAlgorithmsApp::shutdown() {

	delete m_2dRenderer;
}



void GeneticAlgorithmsApp::update(float deltaTime) {
	//m_2dRenderer->drawSprite(nullptr, 400, 400, xPos, yPos, 3.14159f * 0.25f, 1);
	// input example
	aie::Input* input = aie::Input::getInstance();
	//if(input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	
	Movement();
	
	float bestScore = -1000000;
	for (int i = 0; i < ga_system->getpopulation().size(); ++i)
	{
		int score = ga_system->fitnessscore[i];
		if (score > bestScore)
			bestScore = score;
	}
	std::cout << "Best score: " << bestScore << std::endl;

	//Movement(); 
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GeneticAlgorithmsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
		
	MazeRender.Render(m_2dRenderer, { getWindowWidth() * 0.5f, getWindowHeight() * 0.5f }, 30);
	
	MazeRender.RenderAtLocation(m_2dRenderer, MazePos, { getWindowWidth() * 0.5f, getWindowHeight()  *0.5f }, { 1,0, 1 }, 30);

	// done drawing sprites
	m_2dRenderer->end();
}



void GeneticAlgorithmsApp::Movement()
{
	auto& population = ga_system->getpopulation();
	for (auto& direction : population)
	{
		int moveCounter;
		MazePos = MazeRender.FollowDirections(direction, moveCounter);
	}
		MazeRender.RenderAtLocation(m_2dRenderer, MazePos, { getWindowWidth() * 0.5f, getWindowHeight()  *0.5f }, { 1,0, 1 }, 30);
		FitnessScore();

}



void GeneticAlgorithmsApp::FitnessScore()
{	

	Maze::MazePosition targetLocation = MazeRender.getEndlocation();

	auto population = ga_system->getpopulation();
	for (int index = 0; index < population.size(); ++index)
	{
		std::vector<DIRECTION> directions = population[index];

		int moveCounter = 0;

		Maze::MazePosition endLocation = MazeRender.FollowDirections(directions, moveCounter);
		


		float xDist = (float)(targetLocation.x - endLocation.x);
		float yDist = (float)(targetLocation.y - endLocation.y);
		float distance = sqrt(xDist * xDist + yDist * yDist);
		ga_system->fitnessscore[index] = distance  ;
	}
	// Resets Box back to startig position
	//xPos = 400;
	//yPos = 500;
	ga_system->FitnessFunction(); 	
}