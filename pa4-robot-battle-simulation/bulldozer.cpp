#include <iostream>
#include <cstdlib>
#include <string>
#include "bulldozer.h"

using namespace std;

bulldozer::bulldozer()  /* no parameter constructor */
{
    setX(0);
    setY(0);
    grid = nullptr;
    moved = false;
    setType(3);  /* sets type 3 */
    setStrength(50);  /* sets strength 10 */
    setHitpoint(200);  /* sets hitpoint 10 */
    setName("bulldozer");
}

bulldozer::bulldozer(Grid *grd, int x, int y, int newType, int newStrength, int newHit, string newName)  /* constructor which takes 3 parameter */
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

string bulldozer::getType()  /* returns type */
{
    if(get_type() == 3)    return getName();
    return "unknown";
}

int bulldozer::getDamage()  /* calculates the damage and returns it */
{
    int damage;
    damage = (rand() % getStrength()) + 1;  /* calculate damage range (0,strength] */
    cout << getType() << " attacks for " << damage << " points!" << endl;
    return damage;  /* returns damage */
}