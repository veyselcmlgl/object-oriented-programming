#include <iostream>
#include <cstdlib>
#include <string>
#include "robocop.h"

using namespace std;

robocop::robocop()  /* no parameter constructor */
{
    setX(0);
    setY(0);
    grid = nullptr;
    moved = false;
    setType(1);  /* sets type 1 */
    setStrength(30);  /* sets strength 50 */
    setHitpoint(40);  /* sets hitpoint 100 */
    setName("robocop");
}

robocop::robocop(Grid *grd, int x, int y, int newType, int newStrength, int newHit, string newName) /* constructor which takes 3 parameter */
{
    setX(x);
    setY(y);
    grid = grd;
    moved = false;
    setType(newType);  /* sets type */
    setStrength(newStrength);  /* sets strength */
    setHitpoint(newHit);  /* sets hitpoint */
    setName(newName);
    grd->setRobot(this, x, y);
}

string robocop::getType()  /* returns type */
{
    if(get_type() == 1)    return getName();
    return "unknown";
}

int robocop::getDamage() /* calculate damage and returns it */
{
    int damage, possibility;
    damage = (rand() % getStrength()) + 1;  /* calculate damage range (0, strength] */
    possibility = rand() % 10;  /* for chance 10% */
    if(possibility == 1)
        damage = damage + 50;  /* if it is lucky it gain 50 extra damage points */
    cout << getType() << " attacks for " << damage << " points!" << endl;
    return damage;  /* returns damage */
}