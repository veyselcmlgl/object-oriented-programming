#include <iostream>
#include <cstdlib>
#include <string>
#include "kamikaze.h"

using namespace std;

kamikaze::kamikaze()
{
    setX(0);
    setY(0);
    grid = nullptr;
    moved = false;
    setType(4);
    setStrength(10);
    setHitpoint(10);
    setName("kamikaze");
}

kamikaze::kamikaze(Grid *grd, int x, int y, int newType, int newStrength, int newHit, string newName)
{
    setX(x);
    setY(y);
    grid = grd;
    moved = false;
    setType(newType);
    setStrength(newStrength);
    setHitpoint(newHit);
    setName(newName);
    grd->setRobot(this, x, y);
}

string kamikaze::getType()
{
    if(get_type() == 4)    return getName();
    return "unknown";
}

int kamikaze::getDamage()
{
    int damage = getHitpoint();
    cout << getType() << " attacks for " << damage << " points!" << endl;
    // setHitpoint(0);
    return damage;
}