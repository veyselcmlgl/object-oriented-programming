#ifndef OPTIMUSPRIME_H
#define OPTIMUSPRIME_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"
#include "humanic.h"

using namespace std;

class optimusprime : public humanic
{
    friend class Grid;
public:
    optimusprime();  /* no parameter constructor */
    optimusprime(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string name);  /* constructor which takes 3 parameter */
    int getDamage();  /* this function calculates the damage */
    string getType();  /* this function returns type */
};

#endif