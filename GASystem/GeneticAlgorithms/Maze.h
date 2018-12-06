#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Directions.h"
namespace aie
{
	class Renderer2D;
}
class Maze
{
public:
	enum Nodes
	{
		EMPTY,
		BLOCKED,
		START,
		END,
	};

	struct MazePosition
	{
		int x;
		int y;
	};

	Maze(int width , int height);

	void Render(aie::Renderer2D* renderer, glm::vec2 center, float Nodeswidth);
	void GenerateMaze();
	void RenderAtLocation(aie::Renderer2D* renderer, MazePosition position,  glm::vec2 center,glm::vec3 Colour, float Nodeswidth);

	MazePosition getStartlocation() { return m_startLocation; }
	MazePosition getEndlocation() { return m_EndLocation; }
	MazePosition getLastLocation() { return m_lastLocation; }
	
	MazePosition FollowDirections(std::vector<DIRECTION> followdirections, int& distanceTraveled);
	MazePosition m_lastLocation;
private:
	std::vector<std::vector<Nodes>> m_maze; 
	int m_width;  
	int m_height;
	MazePosition m_startLocation;
	MazePosition m_EndLocation;

	
};

