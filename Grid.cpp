#include <cmath>
#include <vector>

#include "Grid.hpp"

Grid::Grid(int width, int height, std::pair<int, int> startPosition, std::pair<int, int> goalPosition)
{

	this->width = width;
	this->height = height;
	this->startPosition = startPosition;
	this->goalPosition = goalPosition;

	for (int x = 0; x < width; x++)
	{
		std::vector<GridTile> temp;

		for (int y = 0; y < height; y++)
		{
			GridTile tempTile;
			tempTile.content = empty;
			temp.push_back(tempTile);
		}

		gridTiles.push_back(temp);
	}

	gridTiles[startPosition.first][startPosition.second].content = start;
	gridTiles[startPosition.first][startPosition.second].distanceToStart = 0;
	gridTiles[goalPosition.first][goalPosition.second].content = goal;
}

int Grid::getWidth()
{
	return width;
}

int Grid::getHeight()
{
	return height;
}

std::pair<int, int> Grid::getStartPosition() {
	return startPosition;
}

GridTile Grid::get(int x, int y)
{
	return gridTiles[x][y];
}

void Grid::generateGrid()
{
	{

		int wallCount = 16;

		// Generates random walls
		for (int i = 0; i < wallCount; i++)
		{
			int x = rand() % (width - 4) + 2;
			int y = rand() % (height - 4) + 2;
			int x2 = rand() % 2;
			int y2 = rand() % 2;

			if (x2 == 0)
			{
				generateWallBlock(x, y, x + 1, y + 2);
			}
			else
			{
				generateWallBlock(x, y, x + 2, y + 1);
			}
		}
	}
}

void Grid::generateWallBlock(int x1, int y1, int x2, int y2)
{

	for (int i = 0; i < abs(x2 - x1) + 1; i++)
	{
		for (int j = 0; j < abs(y2 - y1) + 1; j++)
		{
			if (gridTiles[std::min(x1, x2) + i][std::min(y1, y2) + j].content != start && gridTiles[std::min(x1, x2) + i][std::min(y1, y2) + j].content != goal)
			{
				gridTiles[std::min(x1, x2) + i][std::min(y1, y2) + j].content = wall;
			}
		}
	}
}

std::vector<int> Grid::getClosestAndUpdate(int x, int y)
{

	std::vector<int> closestTile = {-1, -1};

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{

			// Check if the tile is within the grid
			if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height)
			{

				// Checks if the tile needs to be updated
				if (gridTiles[x + i][y + j].content != wall && gridTiles[x + i][y + j].content != start && gridTiles[x + i][y + j].isClosest == false)
				{

					// Calculate the distance to the start
					gridTiles[x + i][y + j].distanceToStart = gridTiles[x][y].distanceToStart + getDistance(x, y, x + i, y + j);
					// Calculate the distance to the goal
					gridTiles[x + i][y + j].distanceToGoal = getDistance(x + i, y + j, goalPosition.first, goalPosition.second);
					// Updates the total distance of the tile
					gridTiles[x + i][y + j].totalDistance = gridTiles[x + i][y + j].distanceToStart + gridTiles[x + i][y + j].distanceToGoal;

					// Updates the closest tile if it is closer to the start than the current closest til
					if (closestTile[0] == -1 || gridTiles[x + i][y + j].totalDistance < gridTiles[closestTile[0]][closestTile[1]].totalDistance)
					{
						closestTile = {x + i, y + j};
					}
				}
			}
		}
	}

	if (gridTiles[closestTile[0]][closestTile[1]].content != goal && closestTile[0] != -1)
	{
		gridTiles[closestTile[0]][closestTile[1]].isClosest = true;
		return {closestTile[0], closestTile[1]};
	}

	return {-1, -1};
}

float Grid::getDistance(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int min = std::min(dx, dy);
	int max = std::max(dx, dy);

	int diagonalSteps = min;
	int straightSteps = max - min;

	return sqrt(2) * diagonalSteps + straightSteps;
}