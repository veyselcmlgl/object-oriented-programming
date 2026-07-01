#ifndef ROBOCOP_H
#define ROBOCOP_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"
#include "humanic.h"

using namespace std;

class robocop : public humanic
{
friend class Grid;
public:
    robocop();  /* no parameter constructor */
    robocop(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string newName);  /* constructor which takes 3 parameter */
    int getDamage();  /* this function calculates the damage */
    string getType();  /* this function returns type */
};

#endif