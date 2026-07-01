#include <iostream>
#include <cstdlib>
#include <string>
#include "optimusprime.h"

using namespace std;

optimusprime::optimusprime()  /* no parameter constructor */
{
    setX(0);
    setY(0);
    grid = nullptr;
    moved = false;
    setType(0);  /* sets type 0 */
    setStrength(100);  /* sets strength 50 */
    setHitpoint(100);  /* sets hitpoint 100 */
    setName("optimusprime");
}

optimusprime::optimusprime(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string name)  /* constructor which takes 3 parameter */
{
    setX(x);
    setY(y);
    grid = grd;
    moved = false;
    setType(newType);  /* sets type */
    setStrength(newStrength);  /* sets strength */
    setHitpoint(newHit);  /* sets hitpoint */
    setName(name);
    grd->setRobot(this, x, y); /* set the robot in the grid object */
}

string optimusprime::getType()  /* this function returns type */
{
    if(get_type() == 0)    return getName();
    return "unknown";
}

int optimusprime::getDamage()  /* calculates the damage and returns it */
{
    int damage, possibility;
    damage = (rand() % getStrength()) + 1;  /* calculate damage range (0, strength] */
    possibility = rand() % 10;  /* for chance 10% */
    if(possibility == 1)
        damage = damage + 50;  /* if it is lucky it gain 50 extra damage point */
    possibility = rand() % 20;  /* for chance 15% which is 3/20 */
    if(possibility < 3)
        damage = damage * 2;  /* if it is lucky it doubles the damage poits */
    cout << getType() << " attacks for " << damage << " points!" << endl;
    return damage;  /* returns the damage */
}