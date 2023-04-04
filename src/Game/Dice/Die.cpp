#include "Die.hpp"
#include <random>


//créé grâce aux infos trouvées ici:     //https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

Die::Die() {}

int Die::roll(){
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);

    result = distrib(gen);
    result = 5;
    return result;
}
int Die::getResult() const { return result; }

void Die::setResult(int new_result) { this->result = new_result; }