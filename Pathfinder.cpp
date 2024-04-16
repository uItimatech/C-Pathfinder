#include <iostream>
#include <string>
#include <random>
#include <time.h>

#include "Grid.hpp"
#include "GraphWin.hpp"



// ----------------------------------------------------------------------------------- Main

int main() {

	// Sets the random seed
	srand(time(NULL));

	// Setups the main window
	GraphWin mainWin;
	std::string winTitle = "Pathfinding algorithm test v1.2 - Created by ultimatech";
	std::pair<int, int> winSize = { 1440, 1440 };

	// Creates a grid
	Grid worldGrid(20, 20, { 1, 1 }, { 18, 18 });
	
	// Generates a grid with random walls using the Randomized depth-first search algorithm
	worldGrid.generateGrid();
	mainWin.setWorldGrid(worldGrid);

	mainWin.createWindow(winSize.first, winSize.second, winTitle);

	return 0;
}