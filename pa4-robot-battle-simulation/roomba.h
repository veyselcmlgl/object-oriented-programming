#ifndef ROOMBA_H
#define ROOMBA_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"

using namespace std;

class roomba : public Robot
{
friend class Grid;
public:
    roomba();  /* no parameter constructor */
    roomba(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string newName);  /* constructor which takes 3 parameter */
    int getDamage();  /* this function calculates the damage */
    string getType();  /* this function returns type */
};

#endif