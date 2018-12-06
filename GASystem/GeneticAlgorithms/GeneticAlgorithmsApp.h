#pragma once
#include "Application.h"
#include <Renderer2D.h>
#include "GASystem.h"
#include "Maze.h"


class GeneticAlgorithmsApp : public aie::Application {
public:


	GeneticAlgorithmsApp();
	virtual ~GeneticAlgorithmsApp();

	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

	void Movement(); 

	void FitnessScore();

protected:
	using MyGASystem = GASystem<DIRECTION, 40, 100, 1>;
	Maze			MazeRender;
	Maze::MazePosition MazePos;

	MyGASystem* ga_system;
	aie::Renderer2D*	m_2dRenderer;
};