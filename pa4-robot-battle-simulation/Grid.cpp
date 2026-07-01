#include "Grid.h"

// default constructor for Grid class
// sets all the members of the grid to nullptr
Grid::Grid(){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            grid[i][j] = nullptr;
        }
    }
}


// destructor of the Grid class
// deletes the remaining robots
Grid::~Grid(){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] != nullptr)
                delete (grid[i][j]);
        }
    }

}

// returns the pointer to a Robot or nullptr
Robot *Grid::getAt(int x, int y)
{
    if((x >= 0) && ( x < GRID_SIZE) && (y >= 0) && ( y < GRID_SIZE) )
        return grid[x][y];

    return nullptr;

}

// sets the grid member at the given x-y positions to the rbt value
void Grid::setRobot(Robot *robot, int x, int y)
{
    if((x >= 0) && ( x < GRID_SIZE) && (y >= 0) && ( y < GRID_SIZE) )
        grid[x][y] = robot;
}

// simulates a one step of interaction between the robots
void Grid::simulate(){
    if(TOTAL_ROBOT == 1)
        return;
    //  First reset all robots to not moved
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] != nullptr) grid[i][j]->moved = false;

        }
    }

    // Loop through the cells and move the robots one by one
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] != nullptr){
                if(grid[i][j]->moved == false){
                    //cout << "Moving "<<grids[i][j]->getName() << " at position "<< grids[i][j]->getX() << " "<<grids[i][j]->getY() << endl;
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }

}


/// @brief display the current picture of the grid  
//  for debugging purposes  
void Grid::display(){

    cout << endl;

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] == nullptr)
                cout << ".";
            else if(grid[i][j]->get_type() == 0)
                cout << "o";
            else if(grid[i][j]->get_type() == 1)
                cout << "r";
            else if(grid[i][j]->get_type() == 2)
                cout << "R";
            else if(grid[i][j]->get_type() == 3)
                cout << "b";
            else if(grid[i][j]->get_type() == 4)
                cout << "k";
        }

        cout << endl;

    }


}