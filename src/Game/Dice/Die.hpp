#ifndef DIE_HPP
#define DIE_HPP


class Die{

    int result;

public:
    Die();
    int roll();
    int getResult() const;
    void setResult(int new_result);
};


#endif