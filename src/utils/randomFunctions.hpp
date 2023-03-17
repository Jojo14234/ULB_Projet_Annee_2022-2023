//
// Created by Rémy Ryckeboer on 15/03/2023.
//

#ifndef INFO_F209_GR5_2022_RANDOMFUNCTIONS_HPP
#define INFO_F209_GR5_2022_RANDOMFUNCTIONS_HPP
#include <string>

/*
 * Return a string with the exact size asked.
 * str < size -> add [c] to fit the size
 * str > size -> erase char to fit the size
 */
std::string changeStringSize(std::string str, int size, char c = ' ') {
    if ( str.size() > size ) { str.erase(size); }
    if ( str.size() < size ) { str.append(size-str.size(), c); }
    return str;
}

int stringToInt(std::string str) {
    int i = 0;
    int nb = 0;
    while (i < str.size()) {
        char c = str[i];
        int tmp = int(c) - int('0');
        if (tmp >= 0) {
            nb += (tmp * i - str.size());
        }
        i++;
    }
    return nb;
}

#endif //INFO_F209_GR5_2022_RANDOMFUNCTIONS_HPP
