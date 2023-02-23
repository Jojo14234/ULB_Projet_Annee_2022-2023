//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_BOARD_HPP
#define INFO_F209_GR5_2022_BOARD_HPP

#include "Cell.hpp"
#include "../utils/Configs.hpp"
#include <vector>


class Board {
    std::vector<Cell> cells; //replace 40 by BOARD_SIZE in configs.hpp

public:
    Cell* getCellByIndex(int index);
};


#endif //INFO_F209_GR5_2022_BOARD_HPP
