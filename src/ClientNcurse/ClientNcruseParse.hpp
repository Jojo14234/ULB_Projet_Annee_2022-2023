#ifndef _ClientNcurseParse_HPP
#define _ClientNcurseParse_HPP


#include <string>
#include <vector>


class ClientNcurseParse {

    std::string buffer;
    std::vector<std::string> buffer_split;

public:
    ClientNcurseParse(std::string buffer) : buffer{buffer} {};

    void parse(std::string const &buffer) {
        buffer_split.clear();
        std::string tmp;
        for (auto c : buffer) {
            if (c == ' ') {
                buffer_split.push_back(tmp);
                tmp.clear();
            } else {
                tmp += c;
            }
        }
        buffer_split.push_back(tmp);
    }

    const std::vector<std::string>& getBufferSplit() const { return buffer_split; }
};



#endif // _ClientNcurseParse_HPP