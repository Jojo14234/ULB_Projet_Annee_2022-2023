//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_BANKACCOUNT_HPP
#define INFO_F209_GR5_2022_BANKACCOUNT_HPP


class BankAccount {
    int money;
public:
    //amount of money in account
    BankAccount(int money);

    //remove money from account, return false if player cannot pay
    bool pay(int amount);

    //add money to account
    void gain(int amount);

    ///retrieve amount of money in account
    int getMoney();
};


#endif //INFO_F209_GR5_2022_BANKACCOUNT_HPP