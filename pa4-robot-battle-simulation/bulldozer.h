#ifndef BULLDOZER_H
#define BULLDOZER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"

using namespace std;

class bulldozer : public Robot
{
friend class Grid;
public:
    bulldozer();  /* no parameter constructor */
    bulldozer(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string newName);  /* constructor which takes 4 parameter */
    int getDamage();  /* this function calculates the damage */
    string getType();  /* this function returns type */
};

#endif