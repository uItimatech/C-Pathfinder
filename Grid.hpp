#pragma once

enum tileContents
{
	empty,
	wall,
	start,
	goal
};

struct GridTile
{
	tileContents content{};
	int distanceToStart{};
	int distanceToGoal{};
	int totalDistance = -1;
	bool isClosest = false;
};

// A world grid containing all the tiles
class Grid
{

private:
	int width;
	int height;
	std::vector<std::vector<GridTile>> gridTiles;
	std::pair<int, int> startPosition;
	std::pair<int, int> goalPosition;

public:
	// --- Constructor ---

	Grid(int width = 25, int height = 25, std::pair<int, int> startPosition = std::make_pair(0,0), std::pair<int, int> goalPosition = std::make_pair(1,1));

	// --- Methods ---

	float getDistance(int x1, int y1, int x2, int y2);

	int getWidth();

	int getHeight();

	std::pair<int, int> getStartPosition();

	GridTile get(int x, int y);

	// Generates a grid with random walls
	void generateGrid();

	// Generates a line of walls between two points
	void generateWallBlock(int x1, int y1, int x2, int y2);

	// Calculates the distance from the start to the goal of each tile and updates the tiles
	// Returns the coordinates of the closest tile
	std::vector<int> getClosestAndUpdate(int x, int y);
};