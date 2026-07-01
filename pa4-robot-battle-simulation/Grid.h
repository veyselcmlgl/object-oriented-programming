#ifndef __GRID_H
#define __GRID_H
#include "Robot.h"

const int GRID_SIZE = 10;
// forward defitions
class Robot;
class humanic;
class optimusPrime;
class robocop;
class roomba;
class bulldozer;
class kamikaze;

/* every robot class is a friend to grid    */
class Grid{
    friend class Robot;
    friend class humanic;
    friend class optimusPrime;
    friend class robocop;
    friend class roomba;
    friend class bulldozer;
    friend class kamikaze;
    public:
        Grid();
        ~Grid();
        Robot* getAt(int x, int y);
        void setRobot(Robot* robot, int x, int y);
        void simulate();    //simulates one step 
        void display();     //displays the robots in the grid
        friend void kill_robot(Grid* grd, int x, int y); 
    private:
        Robot* grid[GRID_SIZE][GRID_SIZE];

};


#endif