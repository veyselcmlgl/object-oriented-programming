#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Grid.h"

using namespace std;

const int INITIAL_ROBOT = 5; // initial value for each robot type
const int ROBOT_TYPES = 5;   // number of robot types

extern int TOTAL_ROBOT; //  total number of robots present on the grid

class Grid; // Forward decleration

class Robot
{
friend class Grid;
public:
    Robot();
    Robot(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string newName);
    virtual ~Robot();
    virtual int getDamage() = 0;  /* for abstract class */
    virtual string getType() = 0;  /* for abstract class */
    int get_type() const;  /* this function returns the type types integer */
    int getStrength() const;  /* this function returns the strength */
    int getHitpoint() const;  /* this function returns the hitpoint */
    string getName() const;
    void setType(int newType);  /* this function sets the type */
    void setStrength(int newStrength);  /* this function sets the strength */
    void setHitpoint(int newHitpoint);  /* this function sets the hitpoint */
    void setName(string newName);
    int getX() const;
    int getY() const;
    void setX(int newX);
    void setY(int newY);
    void move();  /* moves the Robot object along the Grid */
    friend void match(Robot* rbt1, Robot* rbt2);  /* simulates a match between two given robots */
    friend void kill_robot(Grid* grd, int x, int y);  /* deletes the given robot from the grid */
protected:
    int type;  /* these are data members */
    int strength;
    int hitpoint;
    string name;
    int x, y;
    Grid* grid;
    bool moved;
};

#endif