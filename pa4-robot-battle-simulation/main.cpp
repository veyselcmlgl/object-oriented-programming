#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"
#include "Grid.h"
#include "bulldozer.h"
#include "roomba.h"
#include "humanic.h"
#include "optimusprime.h"
#include "robocop.h"
#include "kamikaze.h"

int TOTAL_ROBOT = INITIAL_ROBOT * ROBOT_TYPES;

using namespace std;

/* the program works steps 1) make pa4  2) ./pa4  */


int main(){

    srand(time(NULL));
    Grid myGrid;

    int robocount = 0;
    int opticount = 0;
    int roombacount = 0;
    int bullcount = 0;
    int kamicount = 0;

    /*  construct and place every new robot in the grid*/
    while(opticount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        /*  name the robots according to their construction */
        if(myGrid.getAt(x, y) == nullptr){  /* if there is no other robot at x-y    */
            string str = to_string(opticount);
            string name = "optimusprime_" + str;
            optimusprime* opti = new optimusprime(&myGrid, x, y, 0, 100, 100, name);
            opticount++;    
        }
    }

    while(robocount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            string str = to_string(robocount);
            string name = "robocop_" + str;
            robocop* robo = new robocop(&myGrid, x, y, 1, 30, 40, name);
            robocount++;
        }
    }

    while(roombacount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            string str = to_string(roombacount);
            string name = "roomba_" + str;
            roomba* room = new roomba(&myGrid, x, y, 2, 3, 10, name);
            roombacount++;
        }
    }

    while(bullcount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            string str = to_string(bullcount);
            string name = "bulldozer_" +str;
            bulldozer* bull = new bulldozer(&myGrid, x, y, 3, 50, 200, name);
            bullcount++;
        }
    }

    while(kamicount < INITIAL_ROBOT){
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        if(myGrid.getAt(x, y) == nullptr){
            string str = to_string(kamicount);
            string name = "kamikaze_" +str;
            kamikaze* bull = new kamikaze(&myGrid, x, y, 4, 10, 10, name);
            kamicount++;
        }
    }
    /*  while the number of robots is greater than one  */
    /*  keep displaying and simulating */
        // myGrid.display();
    while(TOTAL_ROBOT > 1){
        //string s;
        //myGrid.display();
        myGrid.simulate();
        //cout << endl << "Press enter for the next step" << endl;
        //getline(cin, s);
    }
    // myGrid.display();
    if(TOTAL_ROBOT == 1) {
        for(int i = 0; i<GRID_SIZE; i++){
            for(int j = 0; j<GRID_SIZE; j++){
                if(myGrid.getAt(i, j) != nullptr) {
                    cout << "\nWinner is: " << myGrid.getAt(i, j)->getName() << "!\n";
                }
            }
        }
    }
    return 0;

}