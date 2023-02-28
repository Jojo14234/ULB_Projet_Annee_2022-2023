#include "Die.h"



Die::Die(){
    std::srand(time(0));
    result = std::rand()% 6 + 1;
}

int Die::roll(){
    result = std::rand()% 6 + 1;
    return result;
}

int Die::getResult(){
    return result;
}