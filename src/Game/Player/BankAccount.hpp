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
    void pay(int amount);

    //add money to account
    int gain(int amount);

    ///retrieve amount of money in account
    int getMoney() const;

    //used for fast games
    void setMoney(int new_money);

    // return true if the account can pay this amount, else false
    bool canPay(int amount);
};


#endif //INFO_F209_GR5_2022_BANKACCOUNT_HPP
