//
// Created by Joachim on 14/02/2023.
//

#include "Board.hpp"
#include "Cell.hpp"

Cell *Board::getCellByIndex(int index) {
        return &cells.at(index);
}