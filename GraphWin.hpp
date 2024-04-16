#pragma once

struct WinColorReference
{
	// --- Colors ---
	const Pixel BorderColor = Pixel(0, 0, 0);
	const Pixel WallColor = Pixel(0, 0, 0);
	const Pixel StartColor = Pixel(41, 155, 195);
	const Pixel GoalColor = Pixel(41, 155, 195);
	const Pixel PathBuildColor = Pixel(107, 191, 3);
	const Pixel PathFinalColor = Pixel(255, 132, 0);
	const Pixel PathWrongColor = Pixel(191, 19, 6);
};

class GraphWin : public PixelGameEngine
{

private:
	// ----------------------------------------------------------------------------------- Attributes
	Grid worldGrid;

	std::vector<int> tileDisplacement = {0, 0};

	// --- Render Options ---
	int SCREEN_WIDTH = 720;
	int SCREEN_HEIGHT = 720;
	Pixel BACKGROUND_COLOR = Pixel(255, 255, 255);
	bool DISPLAY_DISTANCE = true;

	// --- Tile size ---
	const int TILE_WIDTH = 50;
	const int TILE_HEIGHT = 50;

	// --- Colors ---
	const WinColorReference WinColors;

	std::vector<int> nextClosestTile = {0, 0};

public:
	// ----------------------------------------------------------------------------------- Main methods

	GraphWin();

	void setWorldGrid(Grid worldGrid);

	// ----------------------------------------------------------------------------------- Rendering

	void renderGrid();

	bool createWindow(int width = 720, int height = 720, std::string title = "Graphic Window");

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};