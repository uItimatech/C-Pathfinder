#define OLC_PGE_APPLICATION
#include "OlcPixelGameEngine.hpp"

using namespace olc;

#include "Grid.hpp"
#include "GraphWin.hpp"

GraphWin::GraphWin()
{
	PixelGameEngine();
}

void GraphWin::setWorldGrid(Grid worldGrid)
{
	this->worldGrid = worldGrid;
}

void GraphWin::renderGrid()
{

	for (int x = 0; x < worldGrid.getWidth(); x++)
	{
		for (int y = 0; y < worldGrid.getHeight(); y++)
		{

			// Switch case for the tile contents
			switch (worldGrid.get(x, worldGrid.getHeight() - 1 - y).content)
			{
			case empty:
				DrawRect(x * TILE_WIDTH + tileDisplacement[0], y * TILE_HEIGHT + tileDisplacement[1], TILE_WIDTH, TILE_HEIGHT, WinColors.BorderColor);
				break;

			case wall:
				FillRect(x * TILE_WIDTH + tileDisplacement[0], y * TILE_HEIGHT + tileDisplacement[1], TILE_WIDTH, TILE_HEIGHT, WinColors.WallColor);
				break;

			case start:
				FillRect(x * TILE_WIDTH + tileDisplacement[0], y * TILE_HEIGHT + tileDisplacement[1], TILE_WIDTH, TILE_HEIGHT, WinColors.StartColor);

				// Writes a black "S" in the middle of the tile
				DrawString(x * TILE_WIDTH + tileDisplacement[0] + TILE_WIDTH / 2 - 3, y * TILE_HEIGHT + tileDisplacement[1] + TILE_HEIGHT / 2 - 3, "S", Pixel(0, 0, 0), 1);
				break;

			case goal:
				FillRect(x * TILE_WIDTH + tileDisplacement[0], y * TILE_HEIGHT + tileDisplacement[1], TILE_WIDTH, TILE_HEIGHT, WinColors.GoalColor);

				// Writes a black "G" in the middle of the tile
				DrawString(x * TILE_WIDTH + tileDisplacement[0] + TILE_WIDTH / 2 - 3, y * TILE_HEIGHT + tileDisplacement[1] + TILE_HEIGHT / 2 - 3, "G", Pixel(0, 0, 0), 1);
				break;

			default:
				break;
			}

			// Draws the path
			if (worldGrid.get(x, worldGrid.getHeight() - 1 - y).isClosest)
			{
				FillRect(x * TILE_WIDTH + tileDisplacement[0], y * TILE_HEIGHT + tileDisplacement[1], TILE_WIDTH, TILE_HEIGHT, WinColors.PathFinalColor);
			}

			// Writes the tile's distance informations
			if (DISPLAY_DISTANCE && worldGrid.get(x, worldGrid.getHeight() - 1 - y).totalDistance != -1 && worldGrid.get(x, worldGrid.getHeight() - 1 - y).content != start && worldGrid.get(x, worldGrid.getHeight() - 1 - y).content != goal)
			{

				// Draws the tile background
				if (!worldGrid.get(x, worldGrid.getHeight() - 1 - y).isClosest)
					FillRect(x * TILE_WIDTH + tileDisplacement[0] + 1, y * TILE_HEIGHT + tileDisplacement[1] + 1, TILE_WIDTH - 1, TILE_HEIGHT - 1, WinColors.PathBuildColor);

				// The distance to start in the top left corner
				DrawString(x * TILE_WIDTH + tileDisplacement[0] + 2, y * TILE_HEIGHT + tileDisplacement[1] + 2, std::to_string(worldGrid.get(x, worldGrid.getHeight() - 1 - y).distanceToStart), Pixel(0, 0, 0), 1);

				// The distance to goal in the top right corner
				DrawString(x * TILE_WIDTH + tileDisplacement[0] + TILE_WIDTH - 16, y * TILE_HEIGHT + tileDisplacement[1] + 2, std::to_string(worldGrid.get(x, worldGrid.getHeight() - 1 - y).distanceToGoal), Pixel(0, 0, 0), 1);

				// The total distance in the middle
				DrawString(x * TILE_WIDTH + tileDisplacement[0] + TILE_WIDTH / 2 - 9, y * TILE_HEIGHT + tileDisplacement[1] + TILE_HEIGHT / 2 - 3, std::to_string(worldGrid.get(x, worldGrid.getHeight() - 1 - y).totalDistance), Pixel(0, 0, 0), 1);
			}
		}
	}
}

bool GraphWin::createWindow(int width, int height, std::string title)
{
	if (Construct(width, height, 1, 1, false, false, true))
	{
		sAppName = title;
		Start();
	}

	return true;
}

// [Called once at the start]
bool GraphWin::OnUserCreate()
{ 

	tileDisplacement = {(SCREEN_WIDTH - worldGrid.getWidth() * TILE_WIDTH) / 2, (SCREEN_HEIGHT - worldGrid.getHeight() * TILE_HEIGHT) / 2};

	FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);

	renderGrid();

	nextClosestTile = {worldGrid.getStartPosition().first, worldGrid.getStartPosition().second};

	return true;
}

// [Called once per frame]
bool GraphWin::OnUserUpdate(float fElapsedTime)
{

	// Clears the screen
	FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);

	// Draws the grid
	renderGrid();

	// Updates the closest tile
	if (GetKey(SPACE).bPressed && nextClosestTile[0] != -1)
	{
		nextClosestTile = worldGrid.getClosestAndUpdate(nextClosestTile[0], nextClosestTile[1]);
	}

	// Exits if the user presses the escape key
	if (GetKey(ESCAPE).bPressed)
		return false;

	return true;
}