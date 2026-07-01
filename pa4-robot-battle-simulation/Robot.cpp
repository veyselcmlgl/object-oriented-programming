#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Robot.h"

using namespace std;

/* no parameter constructor for the Robot class */
Robot::Robot() : strength(10), hitpoint(10), name("ROBOT") {
    grid = nullptr;
    moved = false;
    x = 0; 
    y = 0;
}

/* parametered constructor of the Robot class */
Robot::Robot(Grid* grd, int x, int y, int newType, int newStrength, int newHit, string newName) : grid(grd), strength(newStrength), hitpoint(newHit), name(newName)
{
    setType(newType);
    moved = false;
    this->x = x;
    this->y = y;
    grd->setRobot(this, x, y); /* set the robot in the grid object */
}

Robot::~Robot()
{}

int Robot::getX() const
{
    return x;
}

int Robot::getY() const
{
    return y;
}

void Robot::setX(int newX)
{
    x = newX;
}

void Robot::setY(int newY)
{
    y = newY;
}

int Robot::get_type() const
{
    return type;  /* returns type */
}

int Robot::getStrength() const
{
    return strength;  /* returns strength */
}

int Robot::getHitpoint() const
{
    return hitpoint;  /* returns hitpoint */
}

string Robot::getName() const
{
    return name;
}

void Robot::setType(int newType)
{
    type = newType;  /* sets type */
}

void Robot::setStrength(int newStrength)
{
    strength = newStrength;  /* sets strength */
}

void Robot::setHitpoint(int newHitpoint)
{
    hitpoint = newHitpoint;  /* sets hitpoint */
}

void Robot::setName(string newName)
{
    name = newName;
}

void hit_message(string attacker, int attackerhit, string victim, int victimhit, int damage){

    cout << attacker << " (" << attackerhit << ") hits "<< victim;
    cout << " (" << victimhit << ") with "<< damage << endl;

    cout << "The new hitpoints of "<< victim << " is " << victimhit - damage << endl;

}

void Robot::move(){

    int dir;
    bool hitrobot = false;

    if(TOTAL_ROBOT == 1)
        return;

    /* keep moving along the grid until robot fights another robot*/
    while(!hitrobot){

        dir = rand() % 4;   /* pick a random direction to move */
        if(dir == 0){
            /* if the left cell is empty move there */
            if((y > 0) && (grid->getAt(x, y - 1) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x, y - 1);
                grid->setRobot(nullptr, x, y);
                y--;
            }
            /* if left cell is occupied by another robot start the fight */
            else if((y > 0) && (grid->getAt(x, y - 1) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x, y - 1));
            }
        }

        if(dir == 1){
            /* if the right cell is empty move there */
            if((y < GRID_SIZE - 1) && (grid->getAt(x, y + 1) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x, y + 1);
                grid->setRobot(nullptr, x, y);
                y++;
            }
            /* if cell is occupied fight with that robot */
            else if((y < GRID_SIZE - 1) && (grid->getAt(x, y + 1) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x, y + 1));
            }

        }

        if(dir == 2){
            /* if lower cell is empty move there */
            if((x > 0) && (grid->getAt(x - 1, y) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x - 1, y);
                grid->setRobot(nullptr, x, y);
                x--;
            }
            /* or fight with robot */
            else if((x > 0) && (grid->getAt(x - 1, y) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x - 1, y));
            }

        }

        if(dir == 3){
            /* if upper cell is empty move there */
            if((x < GRID_SIZE - 1) && (grid->getAt(x + 1, y) == nullptr)){
                grid->setRobot(grid->getAt(x, y), x + 1, y);
                grid->setRobot(nullptr, x, y);
                x++;
            }
            /* if it is full, fight with that robot */
            else if((x < GRID_SIZE - 1) && (grid->getAt(x + 1, y) != nullptr)){
                hitrobot = true;
                match(this, grid->getAt(x + 1, y));
            }

        }
        
    }
}

void match(Robot *rbt1, Robot *rbt2){

    cout << endl;

    int hitpoints1 = rbt1->getHitpoint();
    int hitpoints2 = rbt2->getHitpoint();
    string name1 = rbt1->getName();
    string name2 = rbt2->getName();

    //int alive;  /* keeps track of which robot is alive */

    /*  if the first robot has 0 or negative hitpoints value */
    /*  it cannot fight and should be removed from the grid */
    if(hitpoints1 <= 0){
        cout << name1 << " has minus or 0 hitpoints and cannot match!\n";
        int x = rbt1->getX();
        int y = rbt1->getY();
        /* delete the robot */
        if(rbt1->grid->getAt(x, y) != nullptr){
            delete (rbt1->grid->getAt(x, y));
            rbt2->grid->setRobot(nullptr, x, y);
        }
        return;
    }
    /*  if the second robot has 0 or negative hitpoints value   */
    /*  it cannot fight and should be removed from the grid */
    if(hitpoints2 <= 0){
        cout << name2 << " has minus or 0 hitpoints and cannot match!\n";
        int x = rbt2->getX();
        int y = rbt2->getY();
        /*  delete it from the grid */
        if(rbt2->grid->getAt(x, y) != nullptr){
            delete (rbt2->grid->getAt(x, y));
            rbt1->grid->setRobot(nullptr, x, y);
        }
        return;
    }

    int damage1, damage2;
    /* loop until one of the robots is announced as dead    */
    while(true){
        /*  calculate the damage the first robot will inflict on the second one   */
        damage1 = rbt1->getDamage();
        hit_message(name1, hitpoints1, name2, hitpoints2, damage1);
        /*  hitpoints of the second robot deccremented accordingly  */
        hitpoints2 -= damage1;
        rbt2->setHitpoint(hitpoints2);
        if(rbt1->get_type() == 4) {
            rbt1->setHitpoint(0);
            hitpoints1 = rbt1->getHitpoint();
            kill_robot(rbt1->grid, rbt1->getX(), rbt1->getY());
            if(hitpoints2 <= 0){
                kill_robot(rbt2->grid, rbt2->getX(), rbt2->getY());
                break;
            }
            break;
        }
        /* if the hitpoints of the second robot is now negative or 0 */
        /* remove it from the grid and announce its death */
        if(hitpoints2 <= 0){
            int rbt2x = rbt2->getX();
            int rbt2y = rbt2->getY();
            /*  call the kill robot function for the second robot */
            kill_robot(rbt2->grid, rbt2->getX(), rbt2->getY());
           
            /*  the first robot should move to the second robots position in the grid   */
            /*  after killing it    */
            
            rbt1->grid->setRobot(rbt1, rbt2x, rbt2y);
            rbt1->grid->setRobot(nullptr, rbt1->x, rbt1->y);
            rbt1->x = rbt2x;
            rbt1->y = rbt2y;

            /*  the first robot is left alive    */
            //alive = 1;
            break;
        }

        /*  damage value the second robot will inflict on the first one */
        damage2 = rbt2->getDamage();
        /*  print the hit_message   */
        hit_message(name2, hitpoints2, name1, hitpoints1, damage2);
        /*  decrement the hitpoints value of the first robot accordingly    */
        hitpoints1 -= damage2;
        rbt1->setHitpoint(hitpoints1);
        if(rbt2->get_type() == 4) {
            rbt2->setHitpoint(0);
            hitpoints2 = rbt2->getHitpoint();
            kill_robot(rbt2->grid, rbt2->getX(), rbt2->getY());
            if(hitpoints1 <= 0){
                kill_robot(rbt1->grid, rbt1->getX(), rbt1->getY());
                break;
            }
            break;
        }
        /*  if the hitpoints of the first robot is negative or 0  */
        /*  it is announced as dead and removed from the grid   */
        if(hitpoints1 <= 0){
            /*  call the kill robot function for the first robot   */
            kill_robot(rbt1->grid, rbt1->getX(), rbt1->getY());
            /*  the second robot is left alive  */
            //alive = 2;
            break;
        }
    }

    /*  display the match results   */
    // if(alive == 1){
    //     cout << "printing match results:\n";
    //     rbt1->grid->display();
    // }
    // else{
    //     cout << "printing match results:\n";
    //     rbt2->grid->display();
    // }

}

void kill_robot(Grid* grd, int x, int y){

    /*  if it is not nullptr    */
    if(grd->grid[x][y]){
        delete (grd->grid[x][y]);
        grd->grid[x][y] = nullptr;

    --TOTAL_ROBOT;
    }

}