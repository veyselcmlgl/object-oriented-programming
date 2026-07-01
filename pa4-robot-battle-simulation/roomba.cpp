#include <iostream>
#include <cstdlib>
#include <string>
#include "roomba.h"

using namespace std;

roomba::roomba()  /* no parameter constructor */
{
    setX(0);
    setY(0);
    grid = nullptr;
    moved = false;
    setType(2);  /* sets type 2 */
    setStrength(3);  /* sets strength 50 */
    setHitpoint(10);  /* sets hitpoint 100 */
    setName("roomba");
}

roomba::roomba(Grid *grd, int x, int y, int newType, int newStrength, int newHit, string newName)  /* constructor which takes 3 parameter */
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

string roomba::getType()  /* returns the type */
{
    if(get_type() == 2)    return getName();
    return "unknown";
}

int roomba::getDamage()  /* calculates the damage and returns it */
{
    int first_damage, second_damage, damage;
    first_damage = (rand() % getStrength()) + 1;  /* calculate damage range (0, strength] */
    second_damage = (rand() % getStrength()) + 1;  /* calculate damage range (0, strength] */
    damage = first_damage + second_damage;
    cout << getType() << " attacks for " << damage << " points!" << endl;
    return damage;  /* returns damage */
}