//
// Created by Rémy Ryckeboer on 29/03/2023.
//

#ifndef INFO_F209_GR5_2022_INPUTPARSER_HPP
#define INFO_F209_GR5_2022_INPUTPARSER_HPP

#include <vector>
#include <iostream>
#include <string>
#include <sstream>


class InputParser {

    std::string input;

protected:

    std::vector<std::string> inputs;

    virtual void parse() { this->split(); }

public:

    InputParser(const std::string &input) : input{input} { this->split(); }

    virtual ~InputParser()=default;

    const std::string &operator[](int n) const { return this->inputs[n]; }

    int size() const { return this->inputs.size(); }

    void split() {
        this->inputs.clear();
        std::istringstream input;
        if (this->input.size() < 1) { this->input = "None"; }
        input.str(this->input);
        for (std::string word; std::getline(input, word, ' ');) {
            this->inputs.push_back(word);
        }
    }

    std::string regroup(int idx_b, int idx_e, char join = ' ' ) {
        std::string ret = "";
        if ( idx_b > this->size() || idx_e > this->size() || idx_b > idx_e ) return ret;
        for ( int idx = idx_b; idx <= idx_e; idx++ ) {
            ret += this->inputs[idx] + join;
        }
        return ret;
    }

};


#endif //INFO_F209_GR5_2022_INPUTPARSER_HPP
