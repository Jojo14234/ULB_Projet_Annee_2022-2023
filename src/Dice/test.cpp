#include  <iostream>
#include <ctime>


#include "Dice.h"
#include "Die.h"

using namespace std;

int main(){
    Dice set;
    for (int i = 0; i < 10 ; i++){
       set.roll();
        cout << "Dé:" << set.getDoubleCounter()<< endl;
        cout << set.isDouble() << endl; 
    }

    
}