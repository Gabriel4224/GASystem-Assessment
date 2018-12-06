#include "Maze.h"
#include <Renderer2D.h>
#include <iostream>
Maze::Maze(int width, int height)
	: m_width(width)
	,m_height(height)
{

}
//Generates the world space for the maze
void Maze::GenerateMaze()
{
	m_maze.resize(m_width);
	for (int x = 0; x < m_width; x++)
	{
		m_maze[x].resize(m_height);
		for (int y = 0; y < m_height; y++)
		{
			int random = rand() % 1000; 
			if (random < 100)
			{
				m_maze[x][y] = Nodes::BLOCKED;
			}
			else
			{
				m_maze[x][y] = Nodes::EMPTY;
			}
		}
	}

	int StartX = rand() % m_width; 
	int StartY = rand() % m_height;
	m_maze[StartX][StartY] = Nodes::START;

	m_startLocation.x = StartX;
	m_startLocation.y = StartY;

	int endX;
	int endY; 
	do
	{
		endX = rand() % m_width;
		endY = rand() % m_height;
	} while (endX == StartX && endY == StartY);

	m_maze[endX][endY] = Nodes::END;
	m_EndLocation.x = endX;
	m_EndLocation.y = endY; 
	
}
//Draws the maze
void Maze::Render(aie::Renderer2D * renderer, glm::vec2 center, float Nodeswidth)
{
	glm::vec2 drawlocation = center;

	drawlocation.x -= (m_width / 2) * Nodeswidth;
	drawlocation.y += (m_height / 2) * Nodeswidth;

	for (int x = 0; x < m_width; x++)
	{
		float baseYlocation = drawlocation.y; 
		for (int y = 0; y < m_height; y++)
		{
			switch (m_maze[x][y])
			{
			case EMPTY:
				renderer->setRenderColour(1.0f, 1.0f, 1.0f);
				break;
			case BLOCKED:
				renderer->setRenderColour(1.0f, 0.0f, 0.0f);
				break;	
			case START:
				renderer->setRenderColour(0.0f, 1.0f, 0.0f);
				break;
			case END:
				renderer->setRenderColour(0.0f, 0.0f, 1.0f);
				break;
			default:
				renderer->setRenderColour(1.0f, 0.0f, 1.0f);
				break;
			}
			renderer->drawBox(drawlocation.x, drawlocation.y, Nodeswidth, Nodeswidth);
			drawlocation.y -= Nodeswidth;

		}
		drawlocation.y = baseYlocation;
		drawlocation.x += Nodeswidth; 
	}
}
// Writes directions into the maze
Maze::MazePosition Maze::FollowDirections(std::vector<DIRECTION> followdirections, int& distanceTraveled)
{
	MazePosition currentlocation = getStartlocation();
	MazePosition endLocation = getEndlocation();
	int moveCounter = 0;
 	for (DIRECTION& directions : followdirections)
 	{
 		if (directions == DIRECTION::UP)
 		{
 			if (currentlocation.y >= 1 && m_maze[currentlocation.x][currentlocation.y - 1] != Nodes::BLOCKED)
 			{
 				currentlocation.y -= 1;
				++moveCounter;
 			}

 		}
		if (directions == DIRECTION::DOWN)
		{
			if (currentlocation.y < m_height - 1 && m_maze[currentlocation.x][currentlocation.y + 1] != Nodes::BLOCKED)
			{
				currentlocation.y += 1;
				++moveCounter;
			}

		}
		if (directions == DIRECTION::RIGHT)
		{
			if (currentlocation.x < m_width - 1 && m_maze[currentlocation.x + 1 ][currentlocation.y] != Nodes::BLOCKED)
			{
				currentlocation.x += 1;
				++moveCounter;
			}
		
		}
		if (directions == DIRECTION::LEFT)
		{
			if (currentlocation.x >= 1 && m_maze[currentlocation.x - 1][currentlocation.y] != Nodes::BLOCKED)
			{
				currentlocation.x -= 1;
				++moveCounter;
			}

		}
		m_lastLocation = currentlocation; 
		if (currentlocation.x == endLocation.x && currentlocation.y == endLocation.y)
		{
			break;
		}
 	}

	distanceTraveled = moveCounter; 
	return currentlocation;
}
//Renders the LastLocation of the node
void Maze::RenderAtLocation(aie::Renderer2D* renderer, MazePosition position, glm::vec2 center, glm::vec3 Colour, float Nodeswidth)
 {
	 glm::vec2 location = center;
	 MazePosition LastLocation = getLastLocation();

	 location.x -= (m_width / 2) * Nodeswidth;
	 location.x += (Nodeswidth * position.x);
	 location.y += (m_height / 2) * Nodeswidth;
	 location.y -= (Nodeswidth * position.y);

	 renderer->setRenderColour(Colour.r, Colour.g, Colour.b);
	 renderer->drawBox(location.x, location.y, Nodeswidth, Nodeswidth);

}
