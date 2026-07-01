#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"

using namespace std;

class kamikaze : public Robot
{
friend class Grid;
public:
    kamikaze();    /* no parameter constructor */
    kamikaze(Grid *grd, int x, int y, int newType, int newStrength, int newHit, string newName);    /* constructor which takes 4 parameter */
    int getDamage();    /* this function calculates the damage */
    string getType();    /* this function returns type */
};

#endif