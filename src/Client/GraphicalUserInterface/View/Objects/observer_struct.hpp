#pragma once
#include <vector>

struct Observer{
    virtual void update(int change)=0;
};


class Subject{
    std::vector<Observer *> obsList;
public:
    void registerObserver(Observer *observer){
    obsList.push_back(observer);
 }
 void removeObserver(Observer *observer){
    remove(begin(obsList), end(obsList), observer);
 }
 void notifyObserver(int change)const{
    for (auto &o:obsList)o->update(change);
 }
};