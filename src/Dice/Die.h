#ifndef DIE_H
#define DIE_H

#include  <iostream>
#include <ctime>

class Die{
    int result;
    public:
        Die();
        int roll();
        int getResult();

};


#endif