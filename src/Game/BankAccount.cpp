//
// Created by Joachim on 14/02/2023.
//

#include "BankAccount.hpp"

BankAccount::BankAccount(int money) : money{money} {}

bool BankAccount::pay(int amount) {

    bool can_pay = (amount > money) ? false : true;
    money = (can_pay) ? money - amount : -1;
    return can_pay;

}

void BankAccount::gain(int amount) {money += amount;}

int BankAccount::getMoney() {return money;}
