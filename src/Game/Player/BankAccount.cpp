//
// Created by Joachim on 14/02/2023.
//

#include "BankAccount.hpp"

BankAccount::BankAccount(int money) : money{money} {}

void BankAccount::pay(int amount) { money = money - amount; }

int BankAccount::gain(int amount) { money += amount; return amount; }

int BankAccount::getMoney() const { return money; }

void BankAccount::setMoney(int new_money) { money = new_money; }

bool BankAccount::canPay(int amount) {
    return this->money >= amount;
}
